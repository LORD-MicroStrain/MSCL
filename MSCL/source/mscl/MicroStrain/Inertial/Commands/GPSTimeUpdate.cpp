#include "stdafx.h"
#include "GPSTimeUpdate.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketBuilder.h"
#include "mscl/MicroStrain/Inertial/InertialTypes.h"
#include "Inertial_Commands.h"

namespace mscl
{
    GPSTimeUpdate::GPSTimeUpdate()
    { }

    ByteStream GPSTimeUpdate::GetWeekValue()
    {

        ByteStream fieldData;
        fieldData.append_uint8(InertialTypes::READ_BACK_CURRENT_SETTINGS);
        fieldData.append_uint8(GPS_WEEK_NUMBER);

        return buildCommand(fieldData.data());;
    }

    ByteStream GPSTimeUpdate::GetSecondsValue()
    {
        ByteStream fieldData;
        fieldData.append_uint8(InertialTypes::READ_BACK_CURRENT_SETTINGS);
        fieldData.append_uint8(GPS_SECONDS);

        return buildCommand(fieldData.data());
    }

    ByteStream GPSTimeUpdate::resetToFactorySettings()
    {
        ByteStream fieldData;
        fieldData.append_uint8(InertialTypes::RESET_TO_DEFAULT);
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
        fieldData.append_uint8(InertialTypes::USE_NEW_SETTINGS);
        fieldData.append_uint8(GPS_WEEK_NUMBER);
        fieldData.append_uint32(timeData);
        return buildCommand(fieldData.data());
    }

    ByteStream GPSTimeUpdate::SetSecondsValue(uint32 timeData)
    {
        ////create the field to add to the packet
        ByteStream fieldData;
        fieldData.append_uint8(InertialTypes::USE_NEW_SETTINGS);
        fieldData.append_uint8(GPS_SECONDS);
        fieldData.append_uint32(timeData);
        return buildCommand(fieldData.data());
    }

    GPSTimeUpdate::Response::Response(const uint8 fieldDataByte,
                                      std::weak_ptr<ResponseCollector> collector,
                                      bool ackNackExpected,
                                      bool dataResponseExpected) :
        GenericInertialCommand::Response(InertialTypes::CMD_GPS_TIME_UPDATE,
                                         collector,
                                         ackNackExpected,
                                         dataResponseExpected,
                                         "GPSTimeUpdate"),
        m_fieldDataByte(fieldDataByte)
    { }

    unsigned long GPSTimeUpdate::Response::parseResponse(const GenericInertialCommandResponse& response) const
    {
        const ByteStream& byteStream = response.data();
        uint32 timeValue = byteStream.read_uint32(0);
        return timeValue;
    }
}