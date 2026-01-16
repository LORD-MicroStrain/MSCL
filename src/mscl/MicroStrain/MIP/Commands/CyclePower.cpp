/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/MIP/Commands/CyclePower.h"

namespace mscl
{
    ByteStream CyclePower::buildCommand()
    {
        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID);
    }

    CyclePower::Response::Response(std::weak_ptr<ResponseCollector> collector) :
        GenericMipCommand::Response(MipTypes::CMD_RESET, collector, true, false, "CyclePower")
    {}
} // namespace mscl
