/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Commands/Sleep_v2.h"

#include "mscl/MicroStrain/Wireless/Commands/WirelessProtocol.h"

namespace mscl
{
    ByteStream Sleep_v2::buildCommand(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress)
    {
        //build the command ByteStream
        ByteStream cmd;

        if(asppVer == WirelessPacket::aspp_v3)
        {
            cmd.append_uint8(WirelessPacket::ASPP_V3_SOP);              //Start of Packet
            cmd.append_uint8(0x04);                                     //Delivery Stop Flag
            cmd.append_uint8(WirelessPacket::packetType_nodeCommand);   //App Data Type
            cmd.append_uint32(nodeAddress);                             //Node address
            cmd.append_uint16(0x0002);                                  //Payload length
            cmd.append_uint16(WirelessProtocol::cmdId_sleep);           //Command ID
            cmd.append_uint16(0x7F7F);                                  //dummy RSSI bytes
            cmd.append_uint32(cmd.calculateCrcChecksum());              //Checksum
        }
        else
        {
            cmd.append_uint8(WirelessPacket::ASPP_V1_SOP);              //Start of Packet
            cmd.append_uint8(0x05);                                     //Delivery Stop Flag
            cmd.append_uint8(WirelessPacket::packetType_nodeCommand);   //App Data Type
            cmd.append_uint16(static_cast<uint16>(nodeAddress));        //Node address
            cmd.append_uint8(0x02);                                     //Payload length
            cmd.append_uint16(WirelessProtocol::cmdId_sleep);           //Command ID
            cmd.append_uint16(cmd.calculateSimpleChecksum(1, 7));       //Checksum
        }

        return cmd;
    }

    Sleep_v2::Response::Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector):
        WirelessResponsePattern(collector, WirelessProtocol::cmdId_sleep, nodeAddress),
        m_nodeAddress(nodeAddress)
    {
    }

    bool Sleep_v2::Response::matchSuccessResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(packet.nodeAddress() != m_nodeAddress ||                             //node address
           !packet.deliveryStopFlags().pc ||                                    //delivery stop flag
           packet.type() != WirelessPacket::packetType_nodeSuccessReply ||      //packet type
           payload.size() != 2 ||                                               //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_sleep              //command ID
           )
        {
            //failed to match some of the bytes
            return false;
        }

        //if we made it here, the packet matches the response pattern
        return true;
    }
}
