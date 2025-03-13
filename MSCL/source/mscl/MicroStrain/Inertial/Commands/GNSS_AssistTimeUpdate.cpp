/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "GNSS_AssistTimeUpdate.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

namespace mscl
{
    GNSS_AssistTimeUpdate::GNSS_AssistTimeUpdate()
    { }

    ByteStream GNSS_AssistTimeUpdate::buildCommand_get()
    {
        ByteStream fieldData;
        fieldData.append_uint8(MipTypes::READ_BACK_CURRENT_SETTINGS);

        return buildCommand(fieldData.data());
    }

    ByteStream GNSS_AssistTimeUpdate::buildCommand_set(const TimeUpdate& timeUpdateData)
    {
        //create the field to add to the packet
        ByteStream fieldData;
        fieldData.append_uint8(MipTypes::USE_NEW_SETTINGS);
        fieldData.append_double(timeUpdateData.timeOfWeek());
        fieldData.append_uint16(timeUpdateData.weekNumber());
        fieldData.append_float(timeUpdateData.timeAccuracy());
        return buildCommand(fieldData.data());
    }

    GNSS_AssistTimeUpdate::Response::Response(std::weak_ptr<ResponseCollector> collector, bool ackNackExpected, bool dataResponseExpected) :
        GenericMipCommand::Response(MipTypes::CMD_GNSS_ASSIST_TIME_UPDATE, collector, ackNackExpected, dataResponseExpected, "GNSS_AssistTimeUpdate")
    { }

    TimeUpdate GNSS_AssistTimeUpdate::Response::parseResponse(const GenericMipCmdResponse& response) const
    {
        TimeUpdate returnData( response.data().read_double(0), response.data().read_uint16(4), response.data().read_float(6) );
        return returnData;
    }
}
