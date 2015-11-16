/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "Sleep.h"

namespace mscl
{
    ByteStream Sleep::buildCommand(NodeAddress nodeAddress)
    {
        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint8(0x32);                //Start of Packet
        cmd.append_uint16(nodeAddress);        //Node address    (2 bytes)

        return cmd;
    }
}