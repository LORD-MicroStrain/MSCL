/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "ArmForDatalogging.h"
#include "WirelessProtocol.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{

    ByteStream ArmForDatalogging::buildCommand(NodeAddress nodeAddress, const std::string& message)
    {
        std::string messageCpy = message;

        //the max message length supported by the command
        static const size_t MAX_MESSAGE_LENGTH = 50;

        //get the length of the user's message
        size_t messageLen = messageCpy.length();

        //if the message is greater than the max length
        if(messageLen > MAX_MESSAGE_LENGTH)
        {
            //we want to trim any text after the max length
            messageCpy.resize(MAX_MESSAGE_LENGTH);
            messageLen = MAX_MESSAGE_LENGTH;
        }

        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint8(WirelessPacket::ASPP_V1_SOP); //Start of Packet
        cmd.append_uint8(0x05);                                         //Delivery Stop Flag
        cmd.append_uint8(0x00);                                         //App Data Type
        cmd.append_uint16(static_cast<uint16>(nodeAddress));            //Node Address
        cmd.append_uint8(0x02 + static_cast<uint8>(messageLen));        //Payload Length
        cmd.append_uint16(WirelessProtocol::cmdId_armForDatalog);       //Command ID
        cmd.append_string(messageCpy);                                  //User Message

        //calculate the checksum of bytes 2-8
        uint16 checksum = cmd.calculateSimpleChecksum(1, 7 + messageLen);

        cmd.append_uint16(checksum);                                    //Checksum        (2 bytes)

        return cmd;
    }

    ArmForDatalogging::Response::Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector):
        WirelessResponsePattern(collector, WirelessProtocol::cmdId_armForDatalog, nodeAddress),
        m_nodeAddress(nodeAddress)
    {
    }

    bool ArmForDatalogging::Response::matchSuccessResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if( packet.deliveryStopFlags().toInvertedByte() != 0x07 ||                  //delivery stop flag
            packet.type() != WirelessPacket::packetType_nodeCommand ||              //app data type
            packet.nodeAddress() != m_nodeAddress ||                                //node address
            payload.size() != 0x03 ||                                               //payload length
            payload.read_uint16(0) != WirelessProtocol::cmdId_armForDatalog         //Command ID
            )            
        {
            //failed to match some of the bytes
            return false;
        }

        //if we made it here, the packet matches the response pattern
        m_success = true;

        //we have fully matched the response
        m_fullyMatched = true;

        //notify that the response was matched
        m_matchCondition.notify();

        return true;
    }
}