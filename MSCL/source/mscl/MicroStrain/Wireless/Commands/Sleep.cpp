/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Commands/Sleep.h"

#include "mscl/MicroStrain/Wireless/Commands/WirelessProtocol.h"

namespace mscl
{
    ByteStream Sleep::buildCommand(NodeAddress nodeAddress)
    {
        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint8(static_cast<uint8>(WirelessProtocol::cmdId_sleep));    //Start of Packet
        cmd.append_uint16(static_cast<uint16>(nodeAddress));                    //Node address

        return cmd;
    }
} // namespace mscl
