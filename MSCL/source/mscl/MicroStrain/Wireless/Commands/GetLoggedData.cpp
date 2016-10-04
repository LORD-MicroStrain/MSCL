/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "GetLoggedData.h"
#include "WirelessProtocol.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{
    ByteStream GetLoggedData::buildCommand(NodeAddress nodeAddress, uint32 flashAddress)
    {
        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint8(0xAA);                                     //Start of Packet
        cmd.append_uint8(0x05);                                     //Delivery Stop Flag
        cmd.append_uint8(0x00);                                     //App Data Type
        cmd.append_uint16(nodeAddress);                             //Node address  (2 bytes)
        cmd.append_uint8(0x06);                                     //Payload length
        cmd.append_uint16(WirelessProtocol::cmdId_getLogData);      //Command ID    (2 bytes)
        cmd.append_uint32(flashAddress);                            //Flash Address (4 bytes)

        //calculate the checksum of bytes 2-12
        uint16 checksum = cmd.calculateSimpleChecksum(1, 11);

        cmd.append_uint16(checksum);    //Checksum        (2 bytes)

        return cmd;
    }

    GetLoggedData::Response::Response(NodeAddress nodeAddress, uint32 flashAddress, std::weak_ptr<ResponseCollector> collector):
        ResponsePattern(collector),
        m_nodeAddress(nodeAddress),
        m_flashAddress(flashAddress)
    {
    }

    bool GetLoggedData::Response::matchSuccessResponse(const WirelessPacket& packet)
    {
        //the number of data bytes in every success response
        static const uint8 NUM_DATA_BYTES = 102;

        //the offset into the payload where data starts
        static const uint8 DATA_BYTE_OFFSET = 6;

        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(packet.deliveryStopFlags().toInvertedByte() != 0x07 ||                       //delivery stop flag
           packet.type() != WirelessPacket::packetType_nodeSuccessReply ||              //app data type
           packet.nodeAddress() != m_nodeAddress ||                                     //node address
           payload.size() != 108 ||                                                     //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_getLogData ||              //command ID
           payload.read_uint32(2) != m_flashAddress                                     //flash address
           )
        {
            //failed to match some of the bytes
            return false;
        }

        //store the data bytes
        for(uint8 i = 0; i < NUM_DATA_BYTES; i++)
        {
            m_data.append_uint8(payload.read_uint8(i + DATA_BYTE_OFFSET));
        }

        m_success = true;

        return true;
    }

    bool GetLoggedData::Response::matchFailResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(packet.deliveryStopFlags().toInvertedByte() != 0x07 ||                       //delivery stop flag
           packet.type() != WirelessPacket::packetType_nodeErrorReply ||              //app data type
           packet.nodeAddress() != m_nodeAddress ||                                     //node address
           payload.size() != 7 ||                                                     //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_getLogData ||              //command ID
           payload.read_uint32(2) != m_flashAddress                                     //flash address
           )
        {
            //failed to match some of the bytes
            return false;
        }

        //m_statusCode = payload.read_uint8(2);

        m_success = false;

        return true;
    }

    bool GetLoggedData::Response::match(const WirelessPacket& packet)
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

    const ByteStream& GetLoggedData::Response::data() const
    {
        return m_data;
    }
}