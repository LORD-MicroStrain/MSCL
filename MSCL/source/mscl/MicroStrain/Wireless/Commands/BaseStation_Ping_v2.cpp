/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Commands/BaseStation_Ping_v2.h"

#include "mscl/MicroStrain/Wireless/Commands/WirelessProtocol.h"

namespace mscl
{
    ByteStream BaseStation_Ping_v2::buildCommand(WirelessPacket::AsppVersion asppVer)
    {
        //build the command ByteStream
        ByteStream cmd;

        if(asppVer == WirelessPacket::aspp_v3)
        {
            cmd.append_uint8(WirelessPacket::ASPP_V3_SOP);                  //Start of Packet
            cmd.append_uint8(0x01);                                         //Delivery Stop Flag
            cmd.append_uint8(WirelessPacket::packetType_baseCommand);       //App Data Type
            cmd.append_uint32(WirelessProtocol::BASE_STATION_ADDRESS);      //Base Station Address
            cmd.append_uint16(0x0002);                                      //Payload length
            cmd.append_uint16(WirelessProtocol::cmdId_basePing_v2);         //Command ID
            cmd.append_uint16(0x7F7F);                                      //dummy rssi bytes
            cmd.append_uint32(cmd.calculateCrcChecksum());                  //checksum
        }
        else
        {
            cmd.append_uint8(WirelessPacket::ASPP_V1_SOP);                  //Start of Packet
            cmd.append_uint8(0x0E);                                         //Delivery Stop Flag
            cmd.append_uint8(WirelessPacket::packetType_baseCommand);       //App Data Type
            cmd.append_uint16(WirelessProtocol::BASE_STATION_ADDRESS);      //Base Station Address
            cmd.append_uint8(0x02);                                         //Payload length
            cmd.append_uint16(WirelessProtocol::cmdId_basePing_v2);         //Command ID
            cmd.append_uint16(cmd.calculateSimpleChecksum(1, 7));           //Checksum
        }

        return cmd;
    }

    BaseStation_Ping_v2::Response::Response(std::weak_ptr<ResponseCollector> collector):
        WirelessResponsePattern(collector, WirelessProtocol::cmdId_basePing_v2, WirelessProtocol::BASE_STATION_ADDRESS)
    {
    }

    bool BaseStation_Ping_v2::Response::matchSuccessResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(!packet.deliveryStopFlags().pc ||                                    //delivery stop flag
           packet.type() != WirelessPacket::packetType_baseSuccessReply ||      //app data type
           packet.nodeAddress() != WirelessProtocol::BASE_STATION_ADDRESS ||    //node address
           payload.size() != 0x02 ||                                            //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_basePing_v2        //command id
           )
        {
            //failed to match some of the bytes
            return false;
        }

        //if we made it here, the packet matches the response pattern
        return true;
    }
}
