/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "AutoBalance_v2.h"
#include "WirelessProtocol.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{
    ByteStream AutoBalance_v2::buildCommand(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, uint8 channelNumber, float targetPercent)
    {
        //build the command ByteStream
        ByteStream cmd;

        if(asppVer == WirelessPacket::aspp_v3)
        {
            cmd.append_uint8(WirelessPacket::ASPP_V3_SOP);                      //Start of Packet
            cmd.append_uint8(0x04);                                             //Delivery Stop Flag
            cmd.append_uint8(0x00);                                             //App Data Type
            cmd.append_uint32(nodeAddress);                                     //Node address
            cmd.append_uint16(0x0007);                                          //Payload Length
            cmd.append_uint16(WirelessProtocol::cmdId_autoBalance_v2);          //Command Id
            cmd.append_uint8(channelNumber);                                    //Channel Number
            cmd.append_float(targetPercent);                                    //Target Percentage Value
            cmd.append_uint16(0x7F7F);                                          //dummy RSSI bytes
            cmd.append_uint32(cmd.calculateCrcChecksum());                      //Checksum
        }
        else
        {
            cmd.append_uint8(0xAA);                                               //Start of Packet
            cmd.append_uint8(0x05);                                               //Delivery Stop Flag
            cmd.append_uint8(0x00);                                               //App Data Type
            cmd.append_uint16(static_cast<uint16>(nodeAddress));                  //Node address
            cmd.append_uint8(0x07);                                               //Payload Length
            cmd.append_uint16(WirelessProtocol::cmdId_autoBalance_v2);            //Command Id
            cmd.append_uint8(channelNumber);                                      //Channel Number
            cmd.append_float(targetPercent);                                      //Target Percentage Value
            cmd.append_uint16(cmd.calculateSimpleChecksum(1, 12));                //Checksum
        }

        return cmd;
    }

    AutoBalance_v2::Response::Response(NodeAddress nodeAddress, uint8 channelNumber, float targetPercent, std::weak_ptr<ResponseCollector> collector):
        WirelessResponsePattern(collector, WirelessProtocol::cmdId_autoBalance_v2, nodeAddress),
        m_nodeAddress(nodeAddress),
        m_channelNumber(channelNumber),
        m_targetPercent(targetPercent)
    {
    }

    bool AutoBalance_v2::Response::match(const WirelessPacket& packet)
    {
        //get a lock on the parsing mutex
        mutex_lock_guard lock(m_parsingMutex);

        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(!packet.deliveryStopFlags().pc ||                                    //delivery stop flag
           packet.type() != WirelessPacket::packetType_nodeSuccessReply ||      //app data type
           packet.nodeAddress() != m_nodeAddress ||                             //node address
           payload.size() != 0x10 ||                                            //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_autoBalance_v2 ||  //command id
           payload.read_uint8(2) != m_channelNumber ||                          //channel number (echo)
           payload.read_float(3) != m_targetPercent                             //target percent (echo)
           )
        {
            //failed to match some of the bytes
            return false;
        }

        //if we made it here, the packet matches the response pattern

        //error code
        m_result.m_errorCode = static_cast<WirelessTypes::AutoBalanceErrorFlag>(payload.read_uint8(7));

        //sampled value
        m_result.m_percentAchieved = payload.read_float(8);

        //hardware offset
        m_result.m_hardwareOffset = static_cast<uint16>(payload.read_uint32(12));

        switch(m_result.m_errorCode)
        {
            case WirelessTypes::autobalance_success:
            case WirelessTypes::autobalance_maybeInvalid:
                m_success = true;
                break;

            default:
                m_success = false;
        }

        //we have fully matched the response
        m_fullyMatched = true;

        //notify that the response was matched
        m_matchCondition.notify();

        return true;
    }

    const AutoBalanceResult& AutoBalance_v2::Response::result() const
    {
        return m_result;
    }
}