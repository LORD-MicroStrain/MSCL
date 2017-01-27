/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "GetDiagnosticInfo.h"
#include "WirelessProtocol.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/DiagnosticPacket.h"

namespace mscl
{
    ByteStream GetDiagnosticInfo::buildCommand(NodeAddress nodeAddress)
    {
        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint8(0xAA);                                     //Start of Packet
        cmd.append_uint8(0x05);                                     //Delivery Stop Flag
        cmd.append_uint8(0x00);                                     //App Data Type
        cmd.append_uint16(nodeAddress);                             //Node address    (2 bytes)
        cmd.append_uint8(0x02);                                     //Payload length
        cmd.append_uint16(WirelessProtocol::cmdId_getDiagInfo);     //Command ID    (2 bytes)

        //calculate the checksum of bytes 2-8
        uint16 checksum = cmd.calculateSimpleChecksum(1, 7);

        cmd.append_uint16(checksum);        //Checksum        (2 bytes)

        return cmd;
    }

    GetDiagnosticInfo::Response::Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector):
        ResponsePattern(collector),
        m_nodeAddress(nodeAddress)
    {
    }

    bool GetDiagnosticInfo::Response::match(const WirelessPacket& packet)
    {
        //check the main bytes of the packet
        if( packet.deliveryStopFlags().toInvertedByte() != 0x07 ||          //delivery stop flag
            packet.type() != WirelessPacket::packetType_nodeSuccessReply || //app data type
            packet.nodeAddress() != m_nodeAddress                           //node address
            )            
        {
            //failed to match some of the bytes
            return false;
        }

        DataBuffer bytes(packet.payload());
        
        if(bytes.read_uint16() != WirelessProtocol::cmdId_getDiagInfo)
        {
            return false;
        }

        //verify the payload is correct
        while(bytes.moreToRead())
        {
            uint8 infoLen = bytes.read_uint8();

            if(infoLen == 0)
            {
                //no info length should be 0 (invalid payload)
                return false;
            }

            //verify we can read all the bytes in the length described
            if(bytes.bytesRemaining() < infoLen)
            {
                //can't read all the bytes (invalid payload)
                return false;
            }

            //skip passed the bytes being asked to read
            bytes.skipBytes(infoLen);
        }

        //if we made it here, the packet matches the response pattern

        //get the payload again so we can actually parse the bytes out
        DataBuffer payload(packet.payload());
        size_t numInfoItemBytes = payload.size() - 2;
        payload.skipBytes(2);   //skip the command id bytes
        size_t infoByteCounter = 0;

        //add all the data to the result vector
        uint8 infoLen = 0;
        uint8 infoId = 0;
        while(infoByteCounter < numInfoItemBytes)
        {
            infoLen = payload.read_uint8();

            infoId = payload.read_uint8();

            DiagnosticPacket::addDataPoint(m_result, payload, infoLen - 1, infoId);

            infoByteCounter += (infoLen + 1);
        }

        //we have fully matched the response
        m_fullyMatched = true;

        //notify that the response was matched
        m_matchCondition.notify();

        m_success = true;

        return true;
    }

    const ChannelData& GetDiagnosticInfo::Response::result() const
    {
        return m_result;
    }
}