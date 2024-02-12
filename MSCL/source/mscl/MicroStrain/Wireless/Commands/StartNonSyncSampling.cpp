/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "StartNonSyncSampling.h"
#include "WirelessProtocol.h"

namespace mscl
{
    ByteStream StartNonSyncSampling::buildCommand(NodeAddress nodeAddress)
    {
        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint8(0xAA);                              //Start of Packet
        cmd.append_uint8(0x05);                              //Delivery Stop Flag
        cmd.append_uint8(0x00);                              //App Data Type
        cmd.append_uint16(static_cast<uint16>(nodeAddress)); //Node address    (2 bytes)
        cmd.append_uint8(0x02);                              //Payload length
        cmd.append_uint16(WirelessProtocol::cmdId_startLdc_v1); //Command ID    (2 bytes)

        //calculate the checksum of bytes 2-10
        uint16 checksum = cmd.calculateSimpleChecksum(1, 7);

        cmd.append_uint16(checksum);        //Checksum        (2 bytes)

        return cmd;
    }
}