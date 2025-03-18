/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/RTK/Commands/DeviceStatusFlags.h"

namespace mscl
{
    ByteStream DeviceStatusFlags::buildCommand_get()
    {
        Bytes fieldData;

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
