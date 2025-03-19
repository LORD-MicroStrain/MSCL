/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Commands/BaseStation_BeaconStatus.h"

#include "mscl/MicroStrain/Wireless/Commands/WirelessProtocol.h"

namespace mscl
{
    ByteStream BaseStation_BeaconStatus::buildCommand(WirelessPacket::AsppVersion asppVer)
    {
        //build the command ByteStream
        ByteStream cmd;

        if(asppVer == WirelessPacket::aspp_v3)
        {
            cmd.append_uint8(WirelessPacket::ASPP_V3_SOP);                              //Start of packet
            cmd.append_uint8(0x01);                                                     //Delivery Stop Flag
            cmd.append_uint8(WirelessPacket::packetType_baseCommand);                   //App Data Type
            cmd.append_uint32(WirelessProtocol::BASE_STATION_ADDRESS);                  //Base Station Address
            cmd.append_uint16(0x0002);                                                  //Payload length
            cmd.append_uint16(WirelessProtocol::cmdId_base_getBeaconStatus_v1);         //Command ID
            cmd.append_uint16(0x7F7F);                                                  //dummy rssi bytes
            cmd.append_uint32(cmd.calculateCrcChecksum());                              //checksum
        }
        else
        {
            cmd.append_uint8(WirelessPacket::ASPP_V1_SOP);                              //Start of packet
            cmd.append_uint8(0x0E);                                                     //Delivery Stop Flag
            cmd.append_uint8(0x30);                                                     //App Data Type
            cmd.append_uint16(WirelessProtocol::BASE_STATION_ADDRESS);                  //Base Station Address
            cmd.append_uint8(0x02);                                                     //Payload length
            cmd.append_uint16(WirelessProtocol::cmdId_base_getBeaconStatus_v1);         //Command ID
            cmd.append_uint16(cmd.calculateSimpleChecksum(1, 7));                       //checksum
        }

        //return the built command bytes
        return cmd;
    }

    BaseStation_BeaconStatus::Response::Response(std::weak_ptr<ResponseCollector> collector) :
        WirelessResponsePattern(collector, WirelessProtocol::cmdId_base_getBeaconStatus_v1, WirelessProtocol::BASE_STATION_ADDRESS)
    {}

    bool BaseStation_BeaconStatus::Response::matchSuccessResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(!packet.deliveryStopFlags().pc ||                                         //delivery stop flag
           packet.type() != WirelessPacket::packetType_baseSuccessReply ||          //app data type
           packet.nodeAddress() != WirelessProtocol::BASE_STATION_ADDRESS ||        //node address
           payload.size() != 11 ||                                                  //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_base_getBeaconStatus_v1//command ID
           )
        {
            //failed to match some of the bytes
            return false;
        }

        //beacon status flag
        bool enabled = payload.read_uint8(2) == 1;

        //build the current beacon timestamp
        uint64 timestampSec = payload.read_uint32(3);
        uint64 timestampNano = payload.read_uint32(7);
        Timestamp time((timestampSec * TimeSpan::NANOSECONDS_PER_SECOND) + timestampNano);

        //build the BeaconStatus result object
        m_result = BeaconStatus(enabled, time);

        return true;
    }

    bool BaseStation_BeaconStatus::Response::matchFailResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(!packet.deliveryStopFlags().pc ||                                         //delivery stop flag
           packet.type() != WirelessPacket::packetType_baseErrorReply ||            //app data type
           packet.nodeAddress() != WirelessProtocol::BASE_STATION_ADDRESS ||        //node address
           payload.size() != 3 ||                                                   //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_base_getBeaconStatus_v1//command ID
           )
        {
            //failed to match some of the bytes
            return false;
        }

        //Not doing anything with the error code as of now
        //uint8 errorCode = payload.read_uint8(2);

        return true;
    }

    BeaconStatus BaseStation_BeaconStatus::Response::result()
    {
        return m_result;
    }
} // namespace mscl
