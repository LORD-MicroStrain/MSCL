/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "Inertial_Commands.h"
#include "DeviceStartupSettings.h"

namespace mscl
{
    ByteStream DeviceStartupSettings::buildCommand_saveAsStartup()
    {
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(InertialTypes::SAVE_CURRENT_SETTINGS));

        //build and return the command bytes
        return GenericInertialCommand::buildCommand(CMD_ID, fieldData.data());
    }

    ByteStream DeviceStartupSettings::buildCommand_loadStartup()
    {
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(InertialTypes::LOAD_STARTUP_SETTINGS));

        //build and return the command bytes
        return GenericInertialCommand::buildCommand(CMD_ID, fieldData.data());
    }

    ByteStream DeviceStartupSettings::buildCommand_loadDefault()
    {
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(InertialTypes::RESET_TO_DEFAULT));

        //build and return the command bytes
        return GenericInertialCommand::buildCommand(CMD_ID, fieldData.data());
    }

    DeviceStartupSettings::Response::Response(std::weak_ptr<ResponseCollector> collector):
        GenericInertialCommand::Response(InertialTypes::CMD_SAVE_STARTUP_SETTINGS, collector, true, false, "Device Startup Settings")
    {
    }
}