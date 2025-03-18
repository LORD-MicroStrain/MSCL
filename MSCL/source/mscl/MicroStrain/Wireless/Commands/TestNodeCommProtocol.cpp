/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Commands/TestNodeCommProtocol.h"

#include "mscl/MicroStrain/Wireless/Commands/WirelessProtocol.h"

namespace mscl
{
    ByteStream TestNodeCommProtocol::buildCommand(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, WirelessTypes::CommProtocol protocol)
    {
        //build the command ByteStream
        ByteStream cmd;

        if(asppVer == WirelessPacket::aspp_v3)
        {
            cmd.append_uint8(WirelessPacket::ASPP_V3_SOP);                  //Start of Packet
            cmd.append_uint8(0x01);                                         //Delivery Stop Flag
            cmd.append_uint8(WirelessPacket::packetType_baseCommand);       //App Data Type
            cmd.append_uint32(WirelessProtocol::BASE_STATION_ADDRESS);      //Base address
            cmd.append_uint16(0x0008);                                      //Payload length
            cmd.append_uint16(WirelessProtocol::cmdId_testNodeCommProtocol);//Command ID
            cmd.append_uint32(nodeAddress);                                 //Node Address
            cmd.append_uint16(static_cast<uint16>(protocol));               //Communication Protocol
            cmd.append_uint16(0x7F7F);                                      //dummy RSSI bytes
            cmd.append_uint32(cmd.calculateCrcChecksum());                  //Checksum
        }
        else
        {
            cmd.append_uint8(WirelessPacket::ASPP_V1_SOP);                  //Start of Packet
            cmd.append_uint8(0x0E);                                         //Delivery Stop Flag
            cmd.append_uint8(WirelessPacket::packetType_baseCommand);       //App Data Type
            cmd.append_uint16(WirelessProtocol::BASE_STATION_ADDRESS);      //Base address
            cmd.append_uint8(0x06);                                         //Payload length
            cmd.append_uint16(WirelessProtocol::cmdId_testNodeCommProtocol);//Command ID
            cmd.append_uint16(static_cast<uint16>(nodeAddress));            //Node Address
            cmd.append_uint16(static_cast<uint16>(protocol));               //Communication Protocol
            cmd.append_uint16(cmd.calculateSimpleChecksum(1, 11));          //Checksum
        }

        return cmd;
    }

    TestNodeCommProtocol::Response::Response(NodeAddress nodeAddress, WirelessTypes::CommProtocol protocol, std::weak_ptr<ResponseCollector> collector) :
        WirelessResponsePattern(collector, WirelessProtocol::cmdId_testNodeCommProtocol, nodeAddress),
        m_nodeAddress(nodeAddress),
        m_protocol(protocol)
    {
    }

    bool TestNodeCommProtocol::Response::matchSuccessResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(!packet.deliveryStopFlags().pc ||                                            //delivery stop flag
           packet.type() != WirelessPacket::packetType_baseSuccessReply ||              //app data type
           packet.nodeAddress() != WirelessProtocol::BASE_STATION_ADDRESS               //base address
           )
        {
            //failed to match some of the bytes
            return false;
        }

        if(packet.asppVersion() == WirelessPacket::aspp_v3)
        {
            if(payload.size() != 8 ||                                                       //payload length
               payload.read_uint16(0) != WirelessProtocol::cmdId_testNodeCommProtocol ||    //command ID
               payload.read_uint32(2) != m_nodeAddress ||                                   //node address
               payload.read_uint16(6) != m_protocol                                         //protocol
               )
            {
                return false;
            }
        }
        else
        {
            if(payload.size() != 6 ||                                                       //payload length
               payload.read_uint16(0) != WirelessProtocol::cmdId_testNodeCommProtocol ||    //command ID
               payload.read_uint16(2) != m_nodeAddress ||                                   //node address
               payload.read_uint16(4) != m_protocol                                         //protocol
               )
            {
                return false;
            }
        }

        return true;
    }

    bool TestNodeCommProtocol::Response::matchFailResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(!packet.deliveryStopFlags().pc ||                                        //delivery stop flag
           packet.type() != WirelessPacket::packetType_baseErrorReply ||            //app data type
           packet.nodeAddress() != WirelessProtocol::BASE_STATION_ADDRESS           //base address
           )
        {
            //failed to match some of the bytes
            return false;
        }

        if(packet.asppVersion() == WirelessPacket::aspp_v3)
        {
            if(payload.size() != 9 ||                                                      //payload length
               payload.read_uint16(0) != WirelessProtocol::cmdId_testNodeCommProtocol ||    //command ID
               payload.read_uint32(2) != m_nodeAddress ||                                   //node address
               payload.read_uint16(6) != m_protocol                                         //protocol
               )
            {
                return false;
            }

            //m_statusCode = payload.read_uint8(8);
        }
        else
        {
            if(payload.size() != 6 ||                                                       //payload length
               payload.read_uint16(0) != WirelessProtocol::cmdId_testNodeCommProtocol ||    //command ID
               payload.read_uint16(2) != m_nodeAddress ||                                   //node address
               payload.read_uint16(4) != m_protocol                                         //protocol
               )
            {
                return false;
            }

            //m_statusCode = payload.read_uint8(6);
        }

        return true;
    }
}
