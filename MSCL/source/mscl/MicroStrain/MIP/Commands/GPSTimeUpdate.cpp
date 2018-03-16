#include "stdafx.h"
#include "GPSTimeUpdate.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "MIP_Commands.h"

namespace mscl
{
    GPSTimeUpdate::GPSTimeUpdate()
    { }

    ByteStream GPSTimeUpdate::GetWeekValue()
    {

        ByteStream fieldData;
        fieldData.append_uint8(MipTypes::READ_BACK_CURRENT_SETTINGS);
        fieldData.append_uint8(GPS_WEEK_NUMBER);

        return buildCommand(fieldData.data());;
    }

    ByteStream GPSTimeUpdate::GetSecondsValue()
    {
        ByteStream fieldData;
        fieldData.append_uint8(MipTypes::READ_BACK_CURRENT_SETTINGS);
        fieldData.append_uint8(GPS_SECONDS);

        return buildCommand(fieldData.data());
    }

    ByteStream GPSTimeUpdate::resetToFactorySettings()
    {
        ByteStream fieldData;
        fieldData.append_uint8(MipTypes::RESET_TO_DEFAULT);
        fieldData.append_uint8(2);  // Number of descriptors is 0.
        fieldData.append_uint8(3);
        fieldData.append_uint16(4);
        fieldData.append_uint8(5);
        fieldData.append_uint16(4);

        return buildCommand(fieldData.data());
    }

    ByteStream GPSTimeUpdate::SetWeekValue(uint32 timeData)
    {
        ////create the field to add to the packet
        ByteStream fieldData;
        fieldData.append_uint8(MipTypes::USE_NEW_SETTINGS);
        fieldData.append_uint8(GPS_WEEK_NUMBER);
        fieldData.append_uint32(timeData);
        return buildCommand(fieldData.data());
    }

    ByteStream GPSTimeUpdate::SetSecondsValue(uint32 timeData)
    {
        ////create the field to add to the packet
        ByteStream fieldData;
        fieldData.append_uint8(MipTypes::USE_NEW_SETTINGS);
        fieldData.append_uint8(GPS_SECONDS);
        fieldData.append_uint32(timeData);
        return buildCommand(fieldData.data());
    }

    GPSTimeUpdate::Response::Response(const uint8 fieldDataByte,
                                      std::weak_ptr<ResponseCollector> collector,
                                      bool ackNackExpected,
                                      bool dataResponseExpected) :
        GenericMipCommand::Response(MipTypes::CMD_GPS_TIME_UPDATE,
                                         collector,
                                         ackNackExpected,
                                         dataResponseExpected,
                                         "GPSTimeUpdate"),
        m_fieldDataByte(fieldDataByte)
    { }

    unsigned long GPSTimeUpdate::Response::parseResponse(const GenericMipCmdResponse& response) const
    {
        const ByteStream& byteStream = response.data();
        uint32 timeValue = byteStream.read_uint32(0);
        return timeValue;
    }
}