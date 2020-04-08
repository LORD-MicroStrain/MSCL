/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "BaseStation_Reset_v2.h"
#include "WirelessProtocol.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"


namespace mscl
{
    ByteStream BaseStation_Reset_v2::buildCommand(ResetType resetType)
    {
        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint8(WirelessPacket::ASPP_V3_SOP);              //Start of Packet
        cmd.append_uint8(0x01);                                     //Delivery Stop Flag
        cmd.append_uint8(WirelessPacket::packetType_baseCommand);   //App Data Type
        cmd.append_uint32(WirelessProtocol::BASE_STATION_ADDRESS);  //Node address
        cmd.append_uint16(0x0003);                                  //Payload length
        cmd.append_uint16(WirelessProtocol::cmdId_baseReset_v2);    //Command ID
        cmd.append_uint8(static_cast<uint8>(resetType));            //Reset Type
        cmd.append_uint16(0x7F7F);                                  //dummy RSSI bytes
        cmd.append_uint32(cmd.calculateCrcChecksum());              //Checksum

        return cmd;
    }

    BaseStation_Reset_v2::Response::Response(ResetType resetType, std::weak_ptr<ResponseCollector> collector):
        WirelessResponsePattern(collector, WirelessProtocol::cmdId_baseReset_v2, WirelessProtocol::BASE_STATION_ADDRESS),
        m_resetType(resetType)
    {
    }

    bool BaseStation_Reset_v2::Response::matchSuccessResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if( packet.deliveryStopFlags().toByte() != 0x08 ||                      //delivery stop flag
            packet.type() != WirelessPacket::packetType_baseSuccessReply ||     //app data type
            packet.nodeAddress() != WirelessProtocol::BASE_STATION_ADDRESS ||   //node address
            payload.size() != 3 ||                                              //payload length
            payload.read_uint16(0) != WirelessProtocol::cmdId_baseReset_v2 ||   //command ID
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