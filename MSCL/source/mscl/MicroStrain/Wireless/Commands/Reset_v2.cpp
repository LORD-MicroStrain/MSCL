/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "Reset_v2.h"
#include "WirelessProtocol.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"


namespace mscl
{
    ByteStream Reset_v2::buildCommand(NodeAddress nodeAddress, ResetType resetType)
    {
        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint8(WirelessPacket::ASPP_V3_SOP);              //Start of Packet
        cmd.append_uint8(0x04);                                     //Delivery Stop Flag
        cmd.append_uint8(WirelessPacket::packetType_nodeCommand);   //App Data Type
        cmd.append_uint32(nodeAddress);                             //Node address
        cmd.append_uint16(0x0003);                                  //Payload length
        cmd.append_uint16(WirelessProtocol::cmdId_reset_v2);        //Command ID
        cmd.append_uint8(static_cast<uint8>(resetType));            //Reset Type
        cmd.append_uint16(0x7F7F);                                  //dummy RSSI bytes
        cmd.append_uint32(cmd.calculateCrcChecksum());              //Checksum

        return cmd;
    }

    Reset_v2::Response::Response(NodeAddress nodeAddress, ResetType resetType, std::weak_ptr<ResponseCollector> collector):
        WirelessResponsePattern(collector, WirelessProtocol::cmdId_reset_v2, nodeAddress),
        m_nodeAddress(nodeAddress),
        m_resetType(resetType)
    {
    }

    bool Reset_v2::Response::matchSuccessResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if( packet.deliveryStopFlags().toByte() != 0x08 ||                      //delivery stop flag
            packet.type() != WirelessPacket::packetType_nodeSuccessReply ||     //app data type
            packet.nodeAddress() != m_nodeAddress ||                            //node address
            payload.size() != 3 ||                                              //payload length
            payload.read_uint16(0) != WirelessProtocol::cmdId_reset_v2 ||       //command ID
            payload.read_uint8(2) != m_resetType                                //reset type
            )
        {
            //failed to match some of the bytes
            return false;
        }

        //if we made it here, the packet matches the response pattern
        return true;
    }
}
