/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Inertial/Commands/DeviceStartupSettings.h"

namespace mscl
{
    ByteStream DeviceStartupSettings::buildCommand_saveAsStartup()
    {
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::SAVE_CURRENT_SETTINGS));

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    ByteStream DeviceStartupSettings::buildCommand_loadStartup()
    {
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::LOAD_STARTUP_SETTINGS));

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    ByteStream DeviceStartupSettings::buildCommand_loadDefault()
    {
        ByteStream fieldData;

        //add the command selector byte
        fieldData.append_uint8(static_cast<uint8>(MipTypes::RESET_TO_DEFAULT));

        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID, fieldData.data());
    }

    DeviceStartupSettings::Response::Response(std::weak_ptr<ResponseCollector> collector) :
        GenericMipCommand::Response(MipTypes::CMD_SAVE_STARTUP_SETTINGS, collector, true, false, "Device Startup Settings")
    {
    }
}
