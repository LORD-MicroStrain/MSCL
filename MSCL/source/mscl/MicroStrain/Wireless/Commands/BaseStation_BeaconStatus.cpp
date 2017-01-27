/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "BaseStation_BeaconStatus.h"
#include "WirelessProtocol.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{
    BeaconStatus::BeaconStatus():
        m_enabled(false),
        m_timestamp(0)
    {
    }

    BeaconStatus::BeaconStatus(bool beaconEnabled, const Timestamp& currentTimestamp):
        m_enabled(beaconEnabled),
        m_timestamp(currentTimestamp)
    {
    }

    bool BeaconStatus::enabled()
    {
        return m_enabled;
    }

    const Timestamp& BeaconStatus::timestamp()
    {
        return m_timestamp;
    }

    ByteStream BaseStation_BeaconStatus::buildCommand()
    {
        //build the command ByteStream
        ByteStream cmd;

        cmd.append_uint8(0xAA);                                                     //Start of packet
        cmd.append_uint8(0x0E);                                                     //Delivery Stop Flag
        cmd.append_uint8(0x30);                                                     //App Data Type
        cmd.append_uint16(WirelessProtocol::BASE_STATION_ADDRESS);                  //Base Station Address
        cmd.append_uint8(0x02);                                                     //Payload length
        cmd.append_uint16(WirelessProtocol::cmdId_base_getBeaconStatus);            //Command ID
        cmd.append_uint16(cmd.calculateSimpleChecksum(1, 7));                       //checksum

        //return the built command bytes
        return cmd;
    }


    BaseStation_BeaconStatus::Response::Response(std::weak_ptr<ResponseCollector> collector):
        ResponsePattern(collector)
    {
    }

    bool BaseStation_BeaconStatus::Response::matchSuccessResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(packet.deliveryStopFlags().toInvertedByte() != 0x07 ||                   //delivery stop flag
           packet.type() != WirelessPacket::packetType_baseSuccessReply ||          //app data type
           packet.nodeAddress() != WirelessProtocol::BASE_STATION_ADDRESS ||        //node address
           payload.size() != 11 ||                                                  //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_base_getBeaconStatus   //command ID
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

        //set the result to success
        m_success = true;

        return true;
    }

    bool BaseStation_BeaconStatus::Response::matchFailResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(packet.deliveryStopFlags().toInvertedByte() != 0x07 ||                   //delivery stop flag
           packet.type() != WirelessPacket::packetType_baseErrorReply ||            //app data type
           packet.nodeAddress() != WirelessProtocol::BASE_STATION_ADDRESS ||        //node address
           payload.size() != 3 ||                                                   //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_base_getBeaconStatus   //command ID
           )
        {
            //failed to match some of the bytes
            return false;
        }

        //Not doing anything with the error code as of now
        //uint8 errorCode = payload.read_uint8(2);

        //set the result to failure
        m_success = false;

        return true;
    }

    bool BaseStation_BeaconStatus::Response::match(const WirelessPacket& packet)
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

    BeaconStatus BaseStation_BeaconStatus::Response::result()
    {
        return m_result;
    }
}