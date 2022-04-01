/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "PollData.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"

namespace mscl
{
    ByteStream PollImuData::buildCommand(const MipTypes::MipChannelFields& fields)
    {
        ByteStream fieldData;
        fieldData.append_uint8(0x00);                               //option - normal ack/nack reply
        fieldData.append_uint8(static_cast<uint8>(fields.size()));  //number of descriptors

        for(MipTypes::ChannelField field : fields)
        {
            uint8 dataClass;
            uint8 descriptor;
            Utils::split_uint16(static_cast<uint16>(field), dataClass, descriptor);

            if(static_cast<MipTypes::DataClass>(dataClass) != MipTypes::CLASS_AHRS_IMU)
            {
                throw Error_NotSupported("Invalid Mip ChannelField used in the Poll IMU Data command. Be sure to only send fields that are part of the AHRS/IMU DataClass.");
            }

            fieldData.append_uint8(descriptor); //descriptor
            fieldData.append_uint16(0x0000);    //reserved
        }

        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    PollImuData::Response::Response(std::weak_ptr<ResponseCollector> collector):
        GenericMipCommand::Response(MipTypes::CMD_POLL_SENSOR_DATA, collector, true, false, "Poll IMU Data")
    {
    }




    ByteStream PollGnssData::buildCommand(const MipTypes::MipChannelFields& fields)
    {
        ByteStream fieldData;
        fieldData.append_uint8(0x00);                               //option - normal ack/nack reply
        fieldData.append_uint8(static_cast<uint8>(fields.size()));  //number of descriptors

        for(MipTypes::ChannelField field : fields)
        {
            uint8 dataClass;
            uint8 descriptor;
            Utils::split_uint16(static_cast<uint16>(field), dataClass, descriptor);

            if(static_cast<MipTypes::DataClass>(dataClass) != MipTypes::CLASS_GNSS)
            {
                throw Error_NotSupported("Invalid Mip ChannelField used in the Poll GNSS Data command. Be sure to only send fields that are part of the GNSS DataClass.");
            }

            fieldData.append_uint8(descriptor); //descriptor
            fieldData.append_uint16(0x0000);    //reserved
        }

        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    PollGnssData::Response::Response(std::weak_ptr<ResponseCollector> collector):
        GenericMipCommand::Response(MipTypes::CMD_POLL_GNSS_DATA, collector, true, false, "Poll GNSS Data")
    {
    }




    ByteStream PollEstFilterData::buildCommand(const MipTypes::MipChannelFields& fields)
    {
        ByteStream fieldData;
        fieldData.append_uint8(0x00);                               //option - normal ack/nack reply
        fieldData.append_uint8(static_cast<uint8>(fields.size()));  //number of descriptors

        for(MipTypes::ChannelField field : fields)
        {
            uint8 dataClass;
            uint8 descriptor;
            Utils::split_uint16(static_cast<uint16>(field), dataClass, descriptor);

            if(static_cast<MipTypes::DataClass>(dataClass) != MipTypes::CLASS_ESTFILTER)
            {
                throw Error_NotSupported("Invalid Mip ChannelField used in the Poll Estimation Filter Data command. Be sure to only send fields that are part of the Estimation Filter DataClass.");
            }

            fieldData.append_uint8(descriptor); //descriptor
            fieldData.append_uint16(0x0000);    //reserved
        }

        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    PollEstFilterData::Response::Response(std::weak_ptr<ResponseCollector> collector):
        GenericMipCommand::Response(MipTypes::CMD_POLL_EF_DATA, collector, true, false, "Poll Estimation Filter Data")
    {
    }
}