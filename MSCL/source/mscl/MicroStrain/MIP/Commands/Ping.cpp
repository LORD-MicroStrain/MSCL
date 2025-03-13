/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "Ping.h"

#include "mscl/Utils.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacket.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"

namespace mscl
{
    ByteStream Ping::buildCommand()
    {
        static const uint8 DESC_SET = 0x01;
        static const uint8 FIELD_DESC = 0x01;

        //create the field to add to the packet
        MipDataField field(Utils::make_uint16(DESC_SET, FIELD_DESC));

        //create a packet builder with field
        MipPacketBuilder builder(DESC_SET, field);

        //build the packet and return the ByteStream result
        return builder.buildPacket();
    }

    Ping::Response::Response(std::weak_ptr<ResponseCollector> collector):
        GenericMipCommand::Response(MipTypes::CMD_PING, collector, true, false, "Ping")
    {
    }
}
