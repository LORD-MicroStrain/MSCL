/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Displacement/Commands/DeviceTime.h"

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
    {}
} // namespace mscl
