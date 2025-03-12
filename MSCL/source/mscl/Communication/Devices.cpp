/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/Communication/Devices.h"

#ifdef _WIN32
#include "mscl/Utils_Win32.h"
#include "mscl/WMI_Helper.h"
#else
// #include "mscl/Utils.h"
#endif // _WIN32

namespace mscl
{
    Devices::DeviceList Devices::listBaseStations()
    {
        return listDevices(TYPE_BASESTATION);
    }

    Devices::DeviceList Devices::listInertialDevices()
    {
        return listDevices(TYPE_INERTIALDEVICE);
    }

    Devices::DeviceList Devices::listPorts()
    {
        return listDevices(TYPE_ALL);
    }

    DeviceInfo::DeviceInfo():
        m_description(""),
        m_serial(""),
        m_baudRate(0),
        m_connectionType(ConnectionType::connectionType_serial)
    {}

    DeviceInfo::DeviceInfo(std::string description, std::string serial, uint32 baudRate, DeviceInfo::ConnectionType type):
        m_description(description),
        m_serial(serial),
        m_baudRate(baudRate),
        m_connectionType(type)
    {}

    std::string DeviceInfo::description() const
    {
        return m_description;
    }

    std::string DeviceInfo::serial() const
    {
        return m_serial;
    }

    uint32 DeviceInfo::baudRate() const
    {
        return m_baudRate;
    }

    DeviceInfo::ConnectionType DeviceInfo::connectionType() const
    {
        return m_connectionType;
    }

    std::string Devices::wsdaProIPAddress(const std::string& serial)
    {
        if(serial.length() != 16)
        {
            throw Error("unsupported serial");
        }

        if(serial.at(0) == 'W')
        {
            //this is a real WSDA

            //get the uint32 serial of the link transmitter
            uint32 linkTxSerial = std::stoul(serial.substr(6));

            //convert to an 8-digit hex string
            std::stringstream stream;
            stream << std::setfill('0') << std::setw(8) << std::hex << linkTxSerial;
            std::string serialHexStr = stream.str();

            //add a separator
            serialHexStr.insert(4, ":");

            return "fd7a:cafa:0eb7:6578:" + serialHexStr + "::1";
        }
        else
        {
            //this is a WSDA without an SAP number

            uint32 linkTxSerial = 0;

            for(uint16 i = 15; i >= 10; i--)
            {
                char c = serial.at(i);
                if(c >= '0' && c <= '9')
                {
                    linkTxSerial += static_cast<uint32>(std::pow(36u, 15-i)) * (c - '0');
                }
                else
                {
                    linkTxSerial += static_cast<uint32>(std::pow(36u, 15-i)) * ((c - 'A') + 10);
                }
            }

            //convert to an 8-digit hex string
            std::stringstream stream;
            stream << std::setfill('0') << std::setw(8) << std::hex << linkTxSerial;
            std::string serialHexStr = stream.str();

            //add a separator
            serialHexStr.insert(4, ":");

            return "fd7a:cafa:0eb7:6579:" + serialHexStr + "::1";
        }
    }

    bool Devices::matchesDevice(const std::string& info, const std::string& name, DeviceType devType, uint32& baudRate,
        DeviceInfo::ConnectionType& type)
    {
        const bool validName = Utils::containsStr(name, "(COM") ||
           Utils::containsStr(name, "LORD") ||
           Utils::containsStr(name, "Lord") ||
           Utils::containsStr(name, "Microstrain") ||
           Utils::containsStr(name, "MicroStrain") ||
           Utils::containsStr(name, "Silicon Labs");

        if (!validName)
        {
            return false;
        }

        // BaseStation device type
        if (devType == TYPE_BASESTATION || devType == TYPE_ALL)
        {
            // Check for the BaseStation name (currently this is all we have to go on, not very strong)
            if (Utils::containsStr(name, "Silicon Labs CP210x"))
            {
                baudRate = 921600;
                type = DeviceInfo::connectionType_serial;
                return true;
            }

            // Check for the micro usb base station
            if (Utils::containsStr(info, "VID_199B&PID_BA2E"))
            {
                baudRate = 921600;
                type = DeviceInfo::connectionType_serial;
                return true;
            }

            // Check for the WSDA-Base-200
            if (Utils::containsStr(info, "VID_199B&PID_BA30"))
            {
                baudRate = 3000000;
                type = DeviceInfo::connectionType_serial;
                return true;
            }

            // Check for a WSDA as a USB connected ethernet port
            if (Utils::containsStr(info, "VID_199B&PID_306B"))
            {
                baudRate = 0;
                type = DeviceInfo::connectionType_tcp;
                return true;
            }
        }

        // InertialDevice device type
        if (devType == TYPE_INERTIALDEVICE || devType == TYPE_ALL)
        {
            // Check for the inertial VID/PIDs
            if (Utils::containsStr(info, "VID_199B&PID_0001&MI_00") || // CV7-GNSS/INS
               Utils::containsStr(info, "VID_199B&PID_3065") ||        // Inertial
               Utils::containsStr(info, "VID_0483&PID_5740") ||        // check for the STM vendor ID (this is the best we can do right now for GX4's)
               Utils::containsStr(info, "VID_199B&PID_3A65") ||        // 3DM-GX3-45
               Utils::containsStr(info, "VID_199B&PID_3D65"))          // Inertial in DFU (usb updater) mode
            {
                baudRate = 921600;
                type = DeviceInfo::connectionType_serial;
                return true;
            }
        }

        if (devType == TYPE_ALL)
        {
            // All other devices we are returning true
            baudRate = 0;
            return true;
        }

        return false;
    }

#ifdef _WIN32
    Devices::DeviceList Devices::listDevices(DeviceType devType)
    {
        DeviceList result;

        static const std::string PNP_DEV_ID = "PNPDeviceID";
        static const std::string NAME = "Name";

        try
        {
            //create a WMI_Helper object with the namespace and class we want to access
            WMI_Helper wmi("root\\CIMV2", "Win32_PnPEntity");

            //create the values we want to request
            std::vector<std::string> request;
            request.push_back(PNP_DEV_ID);
            request.push_back(NAME);

            //make the request for the given values
            WMI_Helper::wmiValues entries = wmi.request(request);

            //loop through all the entries that were found
            for(WMI_Helper::wmiValue valueMap : entries)
            {
                //make sure we can inspect all the values
                if(valueMap[PNP_DEV_ID].bstrVal == NULL ||
                   valueMap[NAME].bstrVal == NULL)
                {
                    continue;
                }

                //get the PNPDeviceID value
                std::string pnpDevId(Utils_Win32::wstring_to_string(valueMap[PNP_DEV_ID].bstrVal));

                //get the Name value
                std::string deviceName(Utils_Win32::wstring_to_string(valueMap[NAME].bstrVal));

                uint32 baudRate = 0;
                DeviceInfo::ConnectionType connectionType;

                //if this device matches what we are looking for
                if(matchesDevice(pnpDevId, deviceName, devType, baudRate, connectionType))
                {
                    //find the start position of the serial number
                    size_t serialPos = pnpDevId.find_last_of("/\\") + 1;
                    std::string serial = pnpDevId.substr(serialPos);

                    //this padding is on some inertial devices, strip it off
                    Utils::removeStr(serial, "0000__");

                    //strip off any underscores from the serial
                    Utils::removeChar(serial, '_');

                    std::string deviceId;

                    if(connectionType == DeviceInfo::connectionType_tcp)
                    {
                        try
                        {
                            deviceId = wsdaProIPAddress(serial);
                        }
                        catch(mscl::Error&)
                        {
                            continue;
                        }
                    }
                    else
                    {
                        //device ID is the COM port, parse from the deviceName
                        size_t comStartPos = deviceName.find_last_of("(") + 1;
                        size_t comEndPos = deviceName.find_last_of(")") - 1;
                        deviceId = deviceName.substr(comStartPos, comEndPos + 1 - comStartPos);
                    }

                    //create the Device Info
                    DeviceInfo info(deviceName, serial, baudRate, connectionType);

                    //add the device and info to the map
                    result[deviceId] = info;
                }
            }
        }
        catch(std::exception&)
        {
            //failed to get device list
            return result;
        }

        //return the map of all found items
        return result;
    }
#else // LINUX SPECIFIC CODE
    bool Devices::getDeviceInfo(const std::string& devicePath, std::string& serial, std::string& manufacturer, std::string& pnpID)
    {
        namespace fs = boost::filesystem;

        // Get the path to the device (should be "/sys/bus/___/devices/___")
        fs::path pathToDevice(devicePath);

        // Get the full symlink path
        fs::path deviceSymLink = fs::read_symlink(pathToDevice);

        // Create the path to the connected devices (concatenate paths)
        fs::path fullDevicePath = (pathToDevice.parent_path()) / deviceSymLink;

        // Check that the device path isn't empty
        if (!fullDevicePath.string().empty())
        {
            // Move up 1 directory to the device info directory
            fs::path deviceInfoPath = fullDevicePath.parent_path();

            fs::path serialFilePath = deviceInfoPath / fs::path("serial");

            // If the "serial" file does not exist
            if (!fs::exists(serialFilePath))
            {
                // Try to move up another directory and find it
                deviceInfoPath = deviceInfoPath.parent_path();
                serialFilePath = deviceInfoPath / fs::path("serial");
            }

            // Open the /serial file and read the first line
            std::ifstream serialStream(serialFilePath.string().c_str());
            std::getline(serialStream, serial);

            // Open the /manufacturer file and read the first line
            std::ifstream manufStream( (deviceInfoPath / fs::path("manufacturer")).string().c_str() );
            std::getline(manufStream, manufacturer);

            // Open the /idVendor file and read the first line
            std::ifstream vendorStream( (deviceInfoPath / fs::path("idVendor")).string().c_str() );
            std::string vendorId;
            std::getline(vendorStream, vendorId);
            if (!vendorId.empty())
            {
                std::transform(vendorId.begin(), vendorId.end(), vendorId.begin(), ::toupper);
            }

            // Open the /idProduct file and read the first line
            std::ifstream productStream( (deviceInfoPath / fs::path("idProduct")).string().c_str() );
            std::string productId;
            std::getline(productStream, productId);
            if (!productId.empty())
            {
                std::transform(productId.begin(), productId.end(), productId.begin(), ::toupper);
            }

            // Pack all the info into a similar interface as Windows for fewer variables to pass around and to use a common lookup function
            pnpID = "VID_" + vendorId + "&PID_" + productId;

            // Check for multiple interfaces (I.E, CV7-GNSS/INS)
            std::ifstream interfaceCountStream( (deviceInfoPath / fs::path("bNumInterfaces")).string().c_str() );
            std::string interfaceCount;
            std::getline(interfaceCountStream, interfaceCount);

            // Get the interface number for the device
            if (!interfaceCount.empty())
            {
                // Open the /bInterfaceNumber file and read the first line
                std::ifstream interfaceNumberStream( (fullDevicePath / fs::path("bInterfaceNumber")).string().c_str() );
                std::string interfaceNumber;
                std::getline(interfaceNumberStream, interfaceNumber);
                if (!interfaceNumber.empty())
                {
                    std::transform(interfaceNumber.begin(), interfaceNumber.end(), interfaceNumber.begin(), ::toupper);
                    pnpID += "&MI_" + interfaceNumber;
                }
            }

            return true;
        }

        // We didn't get any info
        return false;
    }

    Devices::DeviceList Devices::listDevices(DeviceType devType)
    {
        DeviceList result;

        namespace fs = boost::filesystem;

        //create the path to the /sys/bus directory
        fs::path busPath("/sys/bus");

        fs::directory_iterator endItr;

        //check that the /bus directory exists
        if(!fs::exists(busPath) || !fs::is_directory(busPath))
        {
            return result;
        }

        //loop through all the items in the directory
        for(fs::directory_iterator busItr(busPath) ; busItr != endItr ; ++busItr)
        {
            std::string busItemPath = (*busItr).path().string();

            //if this item is not a directory, and don't include the "platform" directory, as this contains a bunch of fake serial ports
            if(!fs::is_directory(busItemPath) || Utils::containsStr(busItemPath, "/platform"))
            {
                //move on to the next item
                continue;
            }

            std::string devicesPath = busItemPath + "/devices";

            //check that /devices exists
            if(!fs::exists(devicesPath) || !fs::is_directory(devicesPath))
            {
                //move on to the next item
                continue;
            }

            //loop through all the items in the /devices directory
            for(fs::directory_iterator deviceItr(devicesPath); deviceItr != endItr ; ++deviceItr)
            {
                std::string deviceItemPath = (*deviceItr).path().string();

                //if this item is not a directory
                if(!fs::is_directory(deviceItemPath))
                {
                    //move on to the next item
                    continue;
                }

                std::string ttyPath = deviceItemPath + "/tty";

                //if /tty does not exist
                if(!fs::exists(ttyPath) || !fs::is_directory(ttyPath))
                {
                    //move on to the next item
                    continue;
                }

                //get the information for the device
                std::string serial, manufacturer, pnpID/*, vendorId, productId*/;
                // getDeviceInfo(deviceItemPath, serial, manufacturer, vendorId, productId);
                getDeviceInfo(deviceItemPath, serial, manufacturer, pnpID);

                uint32 baudRate = 0;
                DeviceInfo::ConnectionType connectionType = DeviceInfo::connectionType_serial;

                //if this matches the device we are looking for
                // if(matchesDevice(manufacturer, vendorId, devType, baudRate, connectionType))
                if(matchesDevice(pnpID, manufacturer, devType, baudRate, connectionType))
                {
                    //get the first directory in this directory (should be the only one?)
                    fs::directory_iterator ttyItr(ttyPath);

                    std::string realDeviceName = (*ttyItr).path().string();

                    size_t pos = realDeviceName.find_last_of("/\\");

                    //build the true path to the COM port
                    std::string trueDevicePath = "/dev/" + realDeviceName.substr(pos+1);

                    //create the Device Info
                    DeviceInfo info("", serial, baudRate, connectionType);

                    //add the device to the result map
                    result[trueDevicePath] = info;
                }
            }
        }

        //return the map we created
        return result;
    }
#endif // _WIN32
} // namespace mscl
