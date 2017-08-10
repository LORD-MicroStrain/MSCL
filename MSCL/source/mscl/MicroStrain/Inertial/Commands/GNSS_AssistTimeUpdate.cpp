#include "stdafx.h"
#include "GNSS_AssistTimeUpdate.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketBuilder.h"
#include "mscl/MicroStrain/Inertial/InertialTypes.h"
#include "Inertial_Commands.h"

namespace mscl
{
    GNSS_AssistTimeUpdate::GNSS_AssistTimeUpdate()
    { }

    ByteStream GNSS_AssistTimeUpdate::buildCommand_get()
    {
        ByteStream fieldData;
        fieldData.append_uint8(InertialTypes::READ_BACK_CURRENT_SETTINGS);

        return buildCommand(fieldData.data());
    }

    ByteStream GNSS_AssistTimeUpdate::buildCommand_set(const TimeUpdate& timeUpdateData)
    {
        //create the field to add to the packet
        ByteStream fieldData;
        fieldData.append_uint8(InertialTypes::USE_NEW_SETTINGS);
        fieldData.append_double(timeUpdateData.timeOfWeek());
        fieldData.append_uint16(timeUpdateData.weekNumber());
        fieldData.append_float(timeUpdateData.timeAccuracy());
        return buildCommand(fieldData.data());
    }

    GNSS_AssistTimeUpdate::Response::Response(std::weak_ptr<ResponseCollector> collector, bool ackNackExpected, bool dataResponseExpected) :
        GenericInertialCommand::Response(InertialTypes::CMD_GNSS_ASSIST_TIME_UPDATE, collector, ackNackExpected, dataResponseExpected, "GNSS_AssistTimeUpdate")
    { }

    TimeUpdate GNSS_AssistTimeUpdate::Response::parseResponse(const GenericInertialCommandResponse& response) const
    {
        TimeUpdate returnData( response.data().read_double(0), response.data().read_uint16(4), response.data().read_float(6) );
        return returnData;
    }
}