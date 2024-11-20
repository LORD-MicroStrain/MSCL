/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "MIP_Commands.h"

#include "mscl/Utils.h"

namespace mscl
{
    bool MIP_Commands::parseData_singleBool(const GenericMipCmdResponse& response)
    {
        //cast to comm mode and return
        return static_cast<bool>(response.data().read_uint8(0) == 1);
    }

    void MIP_Commands::parseData_GetDeviceInfo(const GenericMipCmdResponse& response, MipDeviceInfo& result)
    {
        //all the positions of the info in the fieldData
        static const size_t FWVERS_POS = 0;
        static const size_t MODELNAME_POS = 2;
        static const size_t MODELNUM_POS = 18;
        static const size_t SERIALNUM_POS = 34;
        static const size_t LOTNUM_POS = 50;
        static const size_t DEVOPTS_POS = 66;

        ByteStream fieldData = response.data();

        //load the firmware version
        uint16 fw = fieldData.read_uint16(FWVERS_POS);

        //firmware version is in the form: 3487 = 3.4.87
        uint16 major = (fw / 1000);
        uint16 minorAndPatch = (fw - (major * 1000));
        uint16 minor = (minorAndPatch / 100);
        uint16 patch = (minorAndPatch - (minor * 100));

        result.fwVersion = Version(major, minor, patch);

        //load the model name and trim any whitespace
        result.modelName = fieldData.read_string(MODELNAME_POS, 16);
        Utils::strTrimLeft(result.modelName);

        //load the model number and trim any whitespace
        result.modelNumber = fieldData.read_string(MODELNUM_POS, 16);
        Utils::strTrimLeft(result.modelNumber);

        //load the serial number and trim any whitespace
        result.serialNumber = fieldData.read_string(SERIALNUM_POS, 16);
        Utils::strTrimLeft(result.serialNumber);

        //load the load number and trim any whitespace
        result.lotNumber = fieldData.read_string(LOTNUM_POS, 16);
        Utils::strTrimLeft(result.lotNumber);

        //load the device options and trim any whitespace
        result.deviceOptions = fieldData.read_string(DEVOPTS_POS, 16);
        Utils::strTrimLeft(result.deviceOptions);
    }

    void MIP_Commands::parseData_GetDeviceDescriptorSets(const GenericMipCmdResponse& response, std::vector<uint16>& result)
    {
        MipPacket::Payload fieldData(response.data());

        size_t fieldLength = fieldData.size();
        size_t itr = 0;

        //loop over all the bytes in the field data
        while(itr < fieldLength)
        {
            //read the descriptor and add it to the vector
            result.push_back(fieldData.read_uint16(itr));
            itr += 2;
        }
    }

    uint16 MIP_Commands::parseData_DataRateBase(const GenericMipCmdResponse& response)
    {
        //return the value from the response
        return response.data().read_uint16(0);
    }

    DeviceCommPort MIP_Commands::parseData_InterfaceControl(const GenericMipCmdResponse& response)
    {
        //use a DataBuffer to make reading nicer
        DataBuffer db(response.data());

        //read the interface ID value
        uint8 interfaceId =  db.read_uint8();

        //read the input protocols
        DeviceCommPort::Protocol inputProtocols = static_cast<DeviceCommPort::Protocol>(db.read_uint32());

        //read the output protocols
        DeviceCommPort::Protocol outputProtocols = static_cast<DeviceCommPort::Protocol>(db.read_uint32());

        return DeviceCommPort(interfaceId, inputProtocols, outputProtocols);
    }

    uint8 MIP_Commands::parseData_CommunicationMode(const GenericMipCmdResponse& response)
    {
        //cast to comm mode and return
        return response.data().read_uint8(0);
    }

    //uint8 MIP_Commands::parseData_AssistedFixOptions(const GenericMipCmdResponse& response)
    //{
    //    //cast to comm mode and return
    //    return response.data().read_uint8(0);
    //}

    MipChannels MIP_Commands::parseData_MessageFormat(const GenericMipCmdResponse& response, uint8 descSet, uint16 sampleRateBase)
    {
        MipChannels result;

        //use a DataBuffer to make reading nicer
        DataBuffer db(response.data());

        //first byte is the total number of descriptors (channels) that are in the data
        uint8 numDescriptors = db.read_uint8();

        //loop through all the descriptors
        for(uint8 desc = 0; desc < numDescriptors; ++desc)
        {
            //field descriptor followed by the rate decimation
            uint8 fieldDesc = db.read_uint8();
            uint16 rateDecimation = db.read_uint16();

            MipTypes::ChannelField channelId = static_cast<MipTypes::ChannelField>(Utils::make_uint16(descSet, fieldDesc));

            //create a MipChannel and add to the result
            result.push_back(MipChannel(channelId,
                SampleRate::FromInertialRateDecimationInfo(sampleRateBase, rateDecimation)));
        }

        //return the MipChannels result
        return result;
    }

    bool MIP_Commands::parseData_ContinuousDataStream(const GenericMipCmdResponse& response)
    {
        //return true if enabled, false if disabled
        return (response.data().read_uint8(1) == 1);    //Note: position 0 is the device selector, which can be ignored here.
    }

    EulerAngles MIP_Commands::parseData_EulerAngles(const GenericMipCmdResponse& response)
    {
        //use a DataBuffer to make reading nicer
        DataBuffer db(response.data());

        //read the euler angles and store in the result
        float roll = db.read_float();
        float pitch = db.read_float();
        float yaw = db.read_float();

        EulerAngles result(roll, pitch, yaw);

        return result;
    }

    PositionOffset MIP_Commands::parseData_PositionOffset(const GenericMipCmdResponse& response)
    {
        //use a DataBuffer to make reading nicer
        DataBuffer db(response.data());

        //read the euler angles and store in the result
        float x = db.read_float();
        float y = db.read_float();
        float z = db.read_float();

        PositionOffset result(x, y, z);

        return result;
    }

    ZUPTSettingsData MIP_Commands::parseData_ZUPTControl(const GenericMipCmdResponse& response)
    {
        //use a DataBuffer to make reading nicer
        DataBuffer db(response.data());

        //read the enable value
        bool enabled =  static_cast<bool>(db.read_uint8() == 1);

        //read the ZUPT Threshold
        float threshold = db.read_float();

        return ZUPTSettingsData(enabled, threshold);
    }
}
