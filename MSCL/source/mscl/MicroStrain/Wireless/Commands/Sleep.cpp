/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "Sleep.h"
#include "WirelessProtocol.h"

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
}