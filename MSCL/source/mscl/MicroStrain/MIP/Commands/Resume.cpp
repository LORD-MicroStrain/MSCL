/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/MIP/Commands/Resume.h"

namespace mscl
{
    ByteStream Resume::buildCommand()
    {
        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID);
    }

    Resume::Response::Response(std::weak_ptr<ResponseCollector> collector) :
        GenericMipCommand::Response(MipTypes::CMD_RESUME, collector, true, false, "Resume")
    {}
} // namespace mscl
