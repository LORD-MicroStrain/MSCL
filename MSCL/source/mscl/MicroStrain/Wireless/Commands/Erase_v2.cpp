/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "Erase_v2.h"
#include "WirelessProtocol.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{
    ByteStream Erase_v2::buildCommand(NodeAddress nodeAddress)
    {
        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint8(0xAA);                                 //Start of Packet
        cmd.append_uint8(0x05);                                 //Delivery Stop Flag
        cmd.append_uint8(0x00);                                 //App Data Type
        cmd.append_uint16(nodeAddress);                         //Node address  (2 bytes)
        cmd.append_uint8(0x02);                                 //Payload length
        cmd.append_uint16(WirelessProtocol::cmdId_erase_v2);    //Command ID    (2 bytes)

        //calculate the checksum of bytes 2-8
        uint16 checksum = cmd.calculateSimpleChecksum(1, 7);

        cmd.append_uint16(checksum);    //Checksum        (2 bytes)

        return cmd;
    }

    Erase_v2::Response::Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector):
        ResponsePattern(collector),
        m_nodeAddress(nodeAddress)
    {
    }

    bool Erase_v2::Response::matchSuccessResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(packet.deliveryStopFlags().toInvertedByte() != 0x07 ||                       //delivery stop flag
           packet.type() != WirelessPacket::packetType_nodeSuccessReply ||              //app data type
           packet.nodeAddress() != m_nodeAddress ||                                     //node address
           payload.size() != 2 ||                                                       //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_erase_v2                   //command ID
           )
        {
            //failed to match some of the bytes
            return false;
        }

        m_success = true;

        return true;
    }

    bool Erase_v2::Response::matchFailResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(packet.deliveryStopFlags().toInvertedByte() != 0x07 ||                   //delivery stop flag
           packet.type() != WirelessPacket::packetType_nodeErrorReply ||            //app data type
           packet.nodeAddress() != m_nodeAddress ||                                 //node address
           payload.size() != 3 ||                                                   //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_erase_v2               //command ID
           )
        {
            //failed to match some of the bytes
            return false;
        }

        //m_statusCode = payload.read_uint8(2);

        m_success = false;

        return true;
    }

    bool Erase_v2::Response::match(const WirelessPacket& packet)
    {
        //if the bytes match the success response
        if(matchSuccessResponse(packet))
        {
            //we have fully matched the response
            m_fullyMatched = true;

            //notify that the response was matched
            m_matchCondition.notify();
            return true;
        }
        //if the bytes match the fail response
        else if(matchFailResponse(packet))
        {
            //we have fully matched the response
            m_fullyMatched = true;

            //notify that the response was matched
            m_matchCondition.notify();
            return true;
        }

        //the bytes don't match any response
        return false;
    }
}