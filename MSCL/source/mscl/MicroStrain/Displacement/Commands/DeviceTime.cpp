/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "DeviceTime.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

namespace mscl
{
    ByteStream DeviceTime::buildCommand_get(uint64 nanoseconds)
    {
        ByteStream fieldData;
        fieldData.append_uint8(MipTypes::USE_NEW_SETTINGS);
        fieldData.append_uint64(nanoseconds);

        return buildCommand(MipTypes::CMD_DISPLACEMENT_DEVICE_TIME, fieldData.data());
    }

    DeviceTime::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponseExpected) :
        GenericMipCommand::Response(MipTypes::CMD_DISPLACEMENT_DEVICE_TIME, collector, true, dataResponseExpected, "Device Time")
    {
    }
}