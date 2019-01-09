/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "BaseStation_SetBeacon_v2.h"
#include "WirelessProtocol.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{
    ByteStream BaseStation_SetBeacon_v2::buildCommand(WirelessPacket::AsppVersion asppVer, uint32 utcTime)
    {
        //build the command ByteStream
        ByteStream cmd;

        if(asppVer == WirelessPacket::aspp_v3)
        {
            cmd.append_uint8(WirelessPacket::ASPP_V3_SOP);                      //Start of packet
            cmd.append_uint8(0x01);                                             //Delivery Stop Flag
            cmd.append_uint8(WirelessPacket::packetType_baseCommand);           //App Data Type
            cmd.append_uint32(WirelessProtocol::BASE_STATION_ADDRESS);          //Base Station Address
            cmd.append_uint16(0x0006);                                          //Payload length
            cmd.append_uint16(WirelessProtocol::cmdId_base_setBeacon_v2);       //Command ID
            cmd.append_uint32(utcTime);                                         //Timestamp for Beacon
            cmd.append_uint16(0x7F7F);                                          //dummy rssi bytes
            cmd.append_uint32(cmd.calculateCrcChecksum());                      //checksum
        }
        else
        {
            cmd.append_uint8(WirelessPacket::ASPP_V1_SOP);                        //Start of packet
            cmd.append_uint8(0x0E);                                               //Delivery Stop Flag
            cmd.append_uint8(0x30);                                               //App Data Type
            cmd.append_uint16(WirelessProtocol::BASE_STATION_ADDRESS);            //Base Station Address
            cmd.append_uint8(0x06);                                               //Payload length
            cmd.append_uint16(WirelessProtocol::cmdId_base_setBeacon_v2);         //Command ID
            cmd.append_uint32(utcTime);                                           //Timestamp for Beacon
            cmd.append_uint16(cmd.calculateSimpleChecksum(1, 11));                //checksum
        }

        //return the built command bytes
        return cmd;
    }

    BaseStation_SetBeacon_v2::Response::Response(uint32 utcTime, std::weak_ptr<ResponseCollector> collector):
        WirelessResponsePattern(collector, WirelessProtocol::cmdId_base_setBeacon_v2, WirelessProtocol::BASE_STATION_ADDRESS),
        m_beaconStartTime(utcTime)
    {
    }

    bool BaseStation_SetBeacon_v2::Response::matchSuccessResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(!packet.deliveryStopFlags().pc ||                                              //delivery stop flag
           packet.type() != WirelessPacket::packetType_baseSuccessReply ||               //app data type
           packet.nodeAddress() != WirelessProtocol::BASE_STATION_ADDRESS ||             //node address
           payload.size() != 0x06 ||                                                     //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_base_setBeacon_v2 ||       //command ID
           payload.read_uint32(2) != m_beaconStartTime                                   //beacon timestamp
           )
        {
            //failed to match some of the bytes
            return false;
        }

        return true;
    }

    bool BaseStation_SetBeacon_v2::Response::matchFailResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(!packet.deliveryStopFlags().pc ||                                              //delivery stop flag
           packet.type() != WirelessPacket::packetType_baseErrorReply ||                 //app data type
           packet.nodeAddress() != WirelessProtocol::BASE_STATION_ADDRESS ||             //node address
           payload.size() != 0x07 ||                                                     //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_base_setBeacon_v2 ||           //command ID
           payload.read_uint32(2) != m_beaconStartTime                                   //beacon timestamp
           )
        {
            //failed to match some of the bytes
            return false;
        }

        //Not doing anything with the error code as of now
        //uint8 errorCode = payload.read_uint8(6);

        return true;
    }

    Timestamp BaseStation_SetBeacon_v2::Response::beaconStartTime() const
    {
        return Timestamp(static_cast<uint64>(m_beaconStartTime) * TimeSpan::NANOSECONDS_PER_SECOND);
    }
}