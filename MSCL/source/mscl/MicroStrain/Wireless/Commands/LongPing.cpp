/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "LongPing.h"
#include "WirelessProtocol.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"


namespace mscl
{
    ByteStream LongPing::buildCommand(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress)
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
            cmd.append_uint16(WirelessProtocol::cmdId_longPing_v1);     //Command ID
            cmd.append_uint16(0x7F7F);                                  //dummy RSSI bytes
            cmd.append_uint32(cmd.calculateCrcChecksum());              //Checksum
        }
        else
        {
            cmd.append_uint8(WirelessPacket::ASPP_V1_SOP);              //Start of Packet
            cmd.append_uint8(0x05);                                     //Delivery Stop Flag
            cmd.append_uint8(0x00);                                     //App Data Type
            cmd.append_uint16(static_cast<uint16>(nodeAddress));        //Node address    (2 bytes)
            cmd.append_uint8(0x02);                                     //Payload length
            cmd.append_uint16(WirelessProtocol::cmdId_longPing_v1);     //Command ID    (2 bytes)
            cmd.append_uint16(cmd.calculateSimpleChecksum(1, 7));       //checksum
        }

        return cmd;
    }

    LongPing::Response::Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector):
        WirelessResponsePattern(collector, WirelessProtocol::cmdId_longPing_v1, nodeAddress),
        m_nodeAddress(nodeAddress),
        m_result(PingResponse::ResponseFail())
    {
    }

    bool LongPing::Response::matchSuccessResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(!packet.deliveryStopFlags().pc ||                                    //delivery stop flag
           packet.nodeAddress() != m_nodeAddress ||                             //node address
           payload.size() != 2                                                  //payload length
           )
        {
            //failed to match some of the bytes
            return false;
        }

        if(packet.asppVersion() == WirelessPacket::aspp_v3)
        {
            //check the main bytes of the packet
            if(packet.type() != WirelessPacket::packetType_nodeSuccessReply ||      //app data type
               payload.read_uint16(0) != WirelessProtocol::cmdId_longPing_v1        //command ID
               )
            {
                //failed to match some of the bytes
                return false;
            }
        }
        else
        {
            //check the main bytes of the packet
            if(packet.type() != 0x02 ||                                 //app data type
               payload.read_uint16(0) != 0x0000
               )
            {
                //failed to match some of the bytes
                return false;
            }
        }

        //if we made it here, the packet matches the response pattern

        //store the node and base RSSI values with the PingResponse
        m_result = PingResponse::ResponseSuccess(packet.nodeRSSI(), packet.baseRSSI());

        return true;
    }

    PingResponse LongPing::Response::result()
    {
        return m_result;
    }
}
