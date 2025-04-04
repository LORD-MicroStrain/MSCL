/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Commands/AutoBalance.h"

#include "mscl/MicroStrain/Wireless/Commands/WirelessProtocol.h"

namespace mscl
{
    ByteStream AutoBalance::buildCommand(NodeAddress nodeAddress, uint8 channelNumber, uint16 targetValue)
    {
        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint8(WirelessProtocol::cmdId_autoBalance);      //Command ID
        cmd.append_uint16(static_cast<uint16>(nodeAddress));        //Node address    (2 bytes)
        cmd.append_uint8(channelNumber);                            //channel number
        cmd.append_uint16(targetValue);                             //target balance value

        return cmd;
    }
} // namespace mscl
