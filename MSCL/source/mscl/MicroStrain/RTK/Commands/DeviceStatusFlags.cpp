/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "DeviceStatusFlags.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

namespace mscl
{
    ByteStream DeviceStatusFlags::buildCommand_get()
    {
        mscl::Bytes fieldData;

        return buildCommand(MipTypes::CMD_RTK_DEVICE_STATUS_FLAGS, fieldData);
    }

    DeviceStatusFlags::Response::Response(std::weak_ptr<ResponseCollector> collector) :
        GenericMipCommand::Response(MipTypes::CMD_RTK_DEVICE_STATUS_FLAGS, collector, true, true, "Get RTK Device Status Flags")
    {
    }

    RTKDeviceStatusFlags DeviceStatusFlags::Response::parseResponse(const GenericMipCmdResponse& response) const
    {
        return RTKDeviceStatusFlags(response.data().read_uint32(0));
    }
}
