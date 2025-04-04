/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Commands/TriggerArmedDatalogging.h"

#include "mscl/MicroStrain/Wireless/Commands/WirelessProtocol.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{
    ByteStream TriggerArmedDatalogging::buildCommand(NodeAddress nodeAddress)
    {
        //get the current system time
        uint64 timeNow = Utils::getCurrentSystemTime();
        uint32 secondsPart = static_cast<uint32>(timeNow / 1000000000);
        uint32 nanosPart = static_cast<uint32>(timeNow % 1000000000);

        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint8(WirelessPacket::ASPP_V1_SOP);    //Start of Packet
        cmd.append_uint8(0x05);                                            //Delivery Stop Flag
        cmd.append_uint8(0x00);                                            //App Data Type
        cmd.append_uint16(static_cast<uint16>(nodeAddress));               //Node Address
        cmd.append_uint8(0x0A);                                            //Payload Length
        cmd.append_uint16(WirelessProtocol::cmdId_triggerArmedLog);        //Command ID
        cmd.append_uint32(secondsPart);                                    //UTC Timestamp (seconds)
        cmd.append_uint32(nanosPart);                                      //UTC Timestamp (nanoseconds)

        //calculate the checksum of bytes 2-8
        uint16 checksum = cmd.calculateSimpleChecksum(1, 15);

        cmd.append_uint16(checksum);                                    //Checksum        (2 bytes)

        return cmd;
    }
} // namespace mscl
