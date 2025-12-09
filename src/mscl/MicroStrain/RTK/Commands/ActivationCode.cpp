/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/RTK/Commands/ActivationCode.h"

namespace mscl
{
    ByteStream ActivationCode::buildCommand_get()
    {
        Bytes fieldData;

        return buildCommand(MipTypes::CMD_RTK_ACTIVATION_CODE, fieldData);
    }

    ActivationCode::Response::Response(std::weak_ptr<ResponseCollector> collector) :
        GenericMipCommand::Response(MipTypes::CMD_RTK_ACTIVATION_CODE, collector, true, true, "Get RTK Activation Code")
    {}

    std::string ActivationCode::Response::parseResponse(const GenericMipCmdResponse& response) const
    {
        size_t count = 32;

        std::string str;
        for (size_t i = 0; i < count; i++)
        {
            char c = response.data().read_uint8(i);
            if (!c)
            {
                break;
            }
            str += c;
        }
        return str;
    }
} // namespace mscl
