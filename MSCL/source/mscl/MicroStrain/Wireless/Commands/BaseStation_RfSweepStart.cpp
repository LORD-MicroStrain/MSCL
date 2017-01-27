/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "BaseStation_RfSweepStart.h"
#include "WirelessProtocol.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{
    ByteStream BaseStation_RfSweepStart::buildCommand(uint32 min, uint32 max, uint32 interval, uint16 options)
    {
        //build the command ByteStream
        ByteStream cmd;

        cmd.append_uint8(0xAA);                                             //Start of packet
        cmd.append_uint8(0x0E);                                             //Delivery Stop Flag
        cmd.append_uint8(WirelessPacket::packetType_baseCommand);           //App Data Type
        cmd.append_uint16(WirelessProtocol::BASE_STATION_ADDRESS);          //Base Station Address
        cmd.append_uint8(0x10);                                             //Payload length
        cmd.append_uint16(WirelessProtocol::cmdId_base_rfScan);             //Command ID
        cmd.append_uint16(options);
        cmd.append_uint32(min);
        cmd.append_uint32(max);
        cmd.append_uint32(interval);
        cmd.append_uint16(cmd.calculateSimpleChecksum(1, 21));              //checksum

        //return the built command bytes
        return cmd;
    }


    BaseStation_RfSweepStart::Response::Response(std::weak_ptr<ResponseCollector> collector, uint32 min, uint32 max, uint32 interval, uint16 options):
        ResponsePattern(collector),
        m_min(min),
        m_max(max),
        m_interval(interval),
        m_options(options)
    {
    }

    bool BaseStation_RfSweepStart::Response::matchSuccessResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(packet.deliveryStopFlags().toInvertedByte() != 0x07 ||                   //delivery stop flag
           packet.type() != WirelessPacket::packetType_baseSuccessReply ||          //app data type
           packet.nodeAddress() != WirelessProtocol::BASE_STATION_ADDRESS ||        //node address
           payload.size() != 16 ||                                                  //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_base_rfScan ||         //command ID
           payload.read_uint16(2) != m_options ||
           payload.read_uint32(4) != m_min ||
           payload.read_uint32(8) != m_max ||
           payload.read_uint32(12) != m_interval
           )
        {
            //failed to match some of the bytes
            return false;
        }

        //set the result to success
        m_success = true;

        return true;
    }

    bool BaseStation_RfSweepStart::Response::match(const WirelessPacket& packet)
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

        //the bytes don't match any response
        return false;
    }
}