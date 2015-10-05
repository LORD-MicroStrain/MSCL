/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "Devices.h"
#include "mscl/Utils.h"

#include <vector>

#ifdef _WIN32

#include "mscl/WMI_Helper.h"
#include "mscl/Utils_Win32.h"

#else

#include <boost/filesystem.hpp>
#include <fstream>      // std::ifstream

#endif

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
		m_status(STATUS_UNKNOWN),
		m_serial("")
	{
	}

	DeviceInfo::DeviceInfo(DeviceStatus status, std::string serial):
		m_status(status),
		m_serial(serial)
	{
	}

	DeviceInfo::DeviceStatus DeviceInfo::status() const
	{
		return m_status;
	}

	std::string DeviceInfo::serial() const
	{
		return m_serial;
	}

#ifdef _WIN32

	Devices::DeviceList Devices::listDevices(DeviceType devType)
	{
		DeviceList result;

		const std::string DEVICE_ID = "DeviceID";
		const std::string PNP_DEV_ID = "PNPDeviceID";
		const std::string STATUS_INFO = "StatusInfo";
		const std::string DESCRIP = "Description";

		const std::string NAME = "Name";
		const std::string IS_BUSY = "IsBusy";


		try
		{
			std::map<std::string, bool> serialConfigMap;

			//Note: We first need to request Win32_SerialPortConfiguration because if a device was unplugged
			//		but a process still has the connection to it open, the Win32_SerialPort request will
			//		still list it as an available port, which is incorrect.
			{
				//create a WMI_Helper object with the namespace and class we want to access
				WMI_Helper wmi2("root\\CIMV2", "Win32_SerialPortConfiguration");

				//create the values we want to request
				std::vector<std::string> request2;
				request2.push_back(NAME);
				request2.push_back(IS_BUSY);

				//make the request for the given values
				WMI_Helper::wmiValues entries2 = wmi2.request(request2);

				//loop through all the entries that were found
				for(WMI_Helper::wmiValue valueMap2 : entries2)
				{
					//get the name (COM Port)
					std::string name(Utils_Win32::wstring_to_string(valueMap2[NAME].bstrVal));

					//add the name and availability to the map
					serialConfigMap[name] = (valueMap2[IS_BUSY].boolVal == VARIANT_FALSE);
				}
			}


			//create a WMI_Helper object with the namespace and class we want to access
			WMI_Helper wmi("root\\CIMV2", "Win32_SerialPort");

			//create the values we want to request
			std::vector<std::string> request;
			request.push_back(DEVICE_ID);
			request.push_back(PNP_DEV_ID);
			request.push_back(STATUS_INFO);
			request.push_back(DESCRIP);

			//make the request for the given values
			WMI_Helper::wmiValues entries = wmi.request(request);

			//loop through all the entries that were found
			for(WMI_Helper::wmiValue valueMap : entries)
			{				
				//get the PNPDeviceID value
				std::string pnpDevId(Utils_Win32::wstring_to_string(valueMap[PNP_DEV_ID].bstrVal));

				//get the Description value
				std::string deviceDescription(Utils_Win32::wstring_to_string(valueMap[DESCRIP].bstrVal));

				//if this device matches what we are looking for
				if(matchesDevice(pnpDevId, deviceDescription, devType))
				{
					//find the start position of the serial number
					size_t serialPos = pnpDevId.find_last_of("/\\") + 1;
					std::string serial = pnpDevId.substr(serialPos);

					//this padding is on some inertial devices, strip it off
					Utils::removeStr(serial, "0000__");

					//strip off any underscores from the serial
					Utils::removeChar(serial, '_');

					//get the DeviceID (COM Port)
					std::string deviceId(Utils_Win32::wstring_to_string(valueMap[DEVICE_ID].bstrVal));

					auto config = serialConfigMap.find(deviceId);

					//if we didn't find the device in the list found from interrogating Win32_SerialPortConfiguration
					if(config == serialConfigMap.end())
					{
						//move on to the next found device
						continue;
					}

					//the config map contains whether the device is available or not
					bool available = config->second;

					//create the DeviceStatus
					DeviceInfo::DeviceStatus devStatus = DeviceInfo::STATUS_UNAVAILABLE;
					if(available)
					{
						devStatus = DeviceInfo::STATUS_AVAILABLE;
					}

					//create the Device Info
					DeviceInfo info(devStatus, serial);

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

	bool Devices::matchesDevice(std::string pnpID, std::string description, DeviceType devType)
	{
		//all device types means we should match all devices that we found listed
		if(devType == TYPE_ALL)
		{
			return true;
		}
		//BaseStation device type
		else if(devType == TYPE_BASESTATION)
		{
			//check for the basestation description (currently this is all we have to go on, not very strong)
			if(Utils::containsStr(description, "Silicon Labs CP210x"))
			{
				return true;
			}

			//check for the micro usb base station
			if(Utils::containsStr(pnpID, "VID_199B&PID_BA2E"))
			{
				return true;
			}
		}
		//InertialDevice device type
		else if(devType == TYPE_INERTIALDEVICE)
		{
			//check for the STM vendor ID (this is the best we can do right now for GX4's)
			if(Utils::containsStr(pnpID, "VID_0483&PID_5740"))
			{
				return true;
			}

			//check for the inertial VID
			if(Utils::containsStr(pnpID, "VID_199B"))
			{
				return true;
			}
		}

		return false;
	}

#else //LINUX SPECIFIC CODE

	bool Devices::getDeviceInfo(std::string devicePath, std::string& serial, std::string& manufacturer, std::string& vendorId)
	{
		namespace fs = boost::filesystem;

		//get the path to the device (should be "/sys/bus/___/devices/___")
		fs::path pathToDevice(devicePath);

		//get the full symlink path
		fs::path deviceSymLink = fs::read_symlink(pathToDevice);

		//create the path to the connected devices (concatenate paths)
		fs::path fullDevicePath = (pathToDevice.parent_path()) / deviceSymLink;

		//check that the device path isn't empty
		if(fullDevicePath.string() != "")
		{
			//move up 1 directory to the device info directory
			fs::path deviceInfoPath = fullDevicePath.parent_path();

			fs::path serialFilePath = deviceInfoPath / fs::path("serial");

			//if the "serial" file does not exist 
			if(!fs::exists(serialFilePath))
			{
				//try to move up another directory and find it
				deviceInfoPath = deviceInfoPath.parent_path();
				serialFilePath = deviceInfoPath / fs::path("serial");
			}

			//open the /serial file and read the first line 
			std::ifstream serialStream(serialFilePath.string().c_str());
			std::getline(serialStream, serial);

			//open the /manufacturer file and read the first line
			std::ifstream manufStream( (deviceInfoPath / fs::path("manufacturer")).string().c_str() );
			std::getline(manufStream, manufacturer);

			//open the /idVendor file and read the first line
			std::ifstream vendorStream( (deviceInfoPath / fs::path("idVendor")).string().c_str() );
			std::getline(vendorStream, vendorId);

			return true;
		}

		//we didn't get any info
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
				std::string serial, manufacturer, vendorId;
				getDeviceInfo(deviceItemPath, serial, manufacturer, vendorId);

				//if this matches the device we are looking for
				if(matchesDevice(manufacturer, vendorId, devType))
				{
					//get the first directory in this directory (should be the only one?)
					fs::directory_iterator ttyItr(ttyPath);

					std::string realDeviceName = (*ttyItr).path().string();

					size_t pos = realDeviceName.find_last_of("/\\");

					//build the true path to the COM port
					std::string trueDevicePath = "/dev/" + realDeviceName.substr(pos+1);

					//create the Device Info
					DeviceInfo info(DeviceInfo::STATUS_UNKNOWN, serial);

					//add the device to the result map
					result[trueDevicePath] = info;
				}
			}
		}

		//return the map we created
		return result;
	}

	bool Devices::matchesDevice(std::string manufacturer, std::string vendorId, DeviceType devType)
	{
		//all device types means we should match all devices that we found listed
		if(devType == TYPE_ALL)
		{
			return true;
		}
		//BaseStation device type
		else if(devType == TYPE_BASESTATION)
		{
			//currently, checking the base station information isn't a very strong search
			if(Utils::containsStr(manufacturer, "Silicon Labs") && Utils::containsStr(vendorId, "10c4"))
			{
				return true;
			}
		}
		//InertialDevice device type
		else if(devType == TYPE_INERTIALDEVICE)
		{
			//check for the STM vendor ID (this is the best we can do right now for GX4's)
			if( Utils::containsStr(manufacturer, "Lord Microstrain") && Utils::containsStr(vendorId, "0483"))
			{
				return true;
			}

			//check for the inertial information
			if( Utils::containsStr(manufacturer, "MicroStrain, Inc.") && Utils::containsStr(vendorId, "199b"))
			{
				return true;
			}
		}

		return false;
	}

#endif
}