/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "ActivationCode.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

namespace mscl
{
    ByteStream ActivationCode::buildCommand_get()
    {
        mscl::Bytes fieldData;

        return buildCommand(MipTypes::CMD_RTK_ACTIVATION_CODE, fieldData);
    }

    ActivationCode::Response::Response(std::weak_ptr<ResponseCollector> collector) :
        GenericMipCommand::Response(MipTypes::CMD_RTK_ACTIVATION_CODE, collector, true, true, "Get RTK Activation Code")
    {
    }

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
}