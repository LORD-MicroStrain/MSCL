/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "GetLoggedData.h"
#include "WirelessProtocol.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{
    ByteStream GetLoggedData::buildCommand(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, uint32 flashAddress)
    {
        //build the command ByteStream
        ByteStream cmd;

        if(asppVer == WirelessPacket::aspp_v3)
        {
            cmd.append_uint8(WirelessPacket::ASPP_V3_SOP);              //Start of Packet
            cmd.append_uint8(0x04);                                     //Delivery Stop Flag
            cmd.append_uint8(0x00);                                     //App Data Type
            cmd.append_uint32(nodeAddress);                             //Node address
            cmd.append_uint16(0x0006);                                  //Payload length
            cmd.append_uint16(WirelessProtocol::cmdId_getLogData_v1);   //Command ID
            cmd.append_uint32(flashAddress);                            //Flash Address
            cmd.append_uint16(0x7f7f);                                  //dummy RSSI bytes
            cmd.append_uint32(cmd.calculateCrcChecksum());              //Checksum
        }
        else
        {
            cmd.append_uint8(WirelessPacket::ASPP_V1_SOP);              //Start of Packet
            cmd.append_uint8(0x05);                                     //Delivery Stop Flag
            cmd.append_uint8(0x00);                                     //App Data Type
            cmd.append_uint16(static_cast<uint16>(nodeAddress));        //Node address
            cmd.append_uint8(0x06);                                     //Payload length
            cmd.append_uint16(WirelessProtocol::cmdId_getLogData_v1);   //Command ID
            cmd.append_uint32(flashAddress);                            //Flash Address
            cmd.append_uint16(cmd.calculateSimpleChecksum(1, 11));      //Checksum
        }

        return cmd;
    }

    GetLoggedData::Response::Response(NodeAddress nodeAddress, uint32 flashAddress, std::weak_ptr<ResponseCollector> collector):
        WirelessResponsePattern(collector, WirelessProtocol::cmdId_getLogData_v1, nodeAddress),
        m_nodeAddress(nodeAddress),
        m_flashAddress(flashAddress)
    {
    }

    bool GetLoggedData::Response::matchSuccessResponse(const WirelessPacket& packet)
    {
        //the offset into the payload where data starts
        static const uint8 DATA_BYTE_OFFSET = 6;

        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(!packet.deliveryStopFlags().pc ||                                            //delivery stop flag
           packet.type() != WirelessPacket::packetType_nodeSuccessReply ||              //app data type
           packet.nodeAddress() != m_nodeAddress ||                                     //node address
           payload.size() < 6 ||                                                       //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_getLogData_v1 ||           //command ID
           payload.read_uint32(2) != m_flashAddress                                     //flash address
           )
        {
            //failed to match some of the bytes
            return false;
        }

        //Note: numDataBytes should always be 102 for this packet (payload always 108 bytes)
        uint16 numDataBytes = static_cast<uint16>(payload.size() - 6);

        //store the data bytes
        for(uint8 i = 0; i < numDataBytes; i++)
        {
            m_data.append_uint8(payload.read_uint8(i + DATA_BYTE_OFFSET));
        }

        return true;
    }

    bool GetLoggedData::Response::matchFailResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(!packet.deliveryStopFlags().pc ||                                        //delivery stop flag
           packet.type() != WirelessPacket::packetType_nodeErrorReply ||            //app data type
           packet.nodeAddress() != m_nodeAddress ||                                 //node address
           payload.size() != 7 ||                                                   //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_getLogData_v1 ||       //command ID
           payload.read_uint32(2) != m_flashAddress                                 //flash address
           )
        {
            //failed to match some of the bytes
            return false;
        }

        //m_statusCode = payload.read_uint8(6);

        return true;
    }

    const ByteStream& GetLoggedData::Response::data() const
    {
        //get a lock on the parsing mutex
        mutex_lock_guard lock(m_parsingMutex);

        return m_data;
    }
}
