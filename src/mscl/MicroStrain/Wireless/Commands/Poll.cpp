/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Commands/Poll.h"

#include "mscl/MicroStrain/Wireless/Commands/WirelessProtocol.h"

namespace mscl
{
    ByteStream Poll::buildCommand(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, const ChannelMask& chMask)
    {
        //build the command ByteStream
        ByteStream cmd;

        if(asppVer == WirelessPacket::aspp_v3)
        {
            cmd.append_uint8(WirelessPacket::ASPP_V3_SOP);          //Start of Packet
            cmd.append_uint8(0x04);                                 //Delivery Stop Flag
            cmd.append_uint8(0x00);                                 //App Data Type
            cmd.append_uint32(nodeAddress);                         //Node address
            cmd.append_uint16(0x0004);                              //Payload length
            cmd.append_uint16(WirelessProtocol::cmdId_poll);        //Command ID
            cmd.append_uint16(chMask.toMask());                     //Channel Mask
            cmd.append_uint16(0x7F7F);                              //dummy RSSI bytes
            cmd.append_uint32(cmd.calculateCrcChecksum());          //Checksum
        }
        else
        {
            cmd.append_uint8(WirelessPacket::ASPP_V1_SOP);              //Start of Packet
            cmd.append_uint8(0x05);                                     //Delivery Stop Flag
            cmd.append_uint8(0x00);                                     //App Data Type
            cmd.append_uint16(static_cast<uint16>(nodeAddress));        //Node address
            cmd.append_uint8(0x04);                                     //Payload length
            cmd.append_uint16(WirelessProtocol::cmdId_poll);            //Command ID
            cmd.append_uint16(chMask.toMask());                         //Channel Mask
            cmd.append_uint16(cmd.calculateSimpleChecksum(1, 9));       //Checksum
        }

        return cmd;
    }

    Poll::Response::Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector) :
        WirelessResponsePattern(collector, WirelessProtocol::cmdId_poll, nodeAddress),
        m_nodeAddress(nodeAddress),
        m_started(false),
        m_timeUntilCompletion(0.0f)
    {}

    bool Poll::Response::started() const
    {
        return m_started;
    }

    float Poll::Response::timeToComplete() const
    {
        return m_timeUntilCompletion;
    }

    const WirelessPollData& Poll::Response::result() const
    {
        return m_result;
    }

    bool Poll::Response::match(const WirelessPacket& packet)
    {
        //get a lock on the parsing mutex
        mutex_lock_guard lock(m_parsingMutex);

        //if the Node hasn't said it started yet
        if(!m_started)
        {
            //check if this matches the "Node Received Command" response
            if(match_nodeReceived(packet))
            {
                //if the autocal has now started
                if(m_started)
                {
                    //successfully started, not complete so don't set the fullyMatched flag

                    //notify that the response was matched
                    m_matchCondition.notify();

                    return true;
                }

                //got a bad status, so poll won't be started (not expecting another packet)
                m_fullyMatched = true;

                //notify that the response was matched
                m_matchCondition.notify();

                return true;
            }
        }

        if(matchSuccessResponse(packet))
        {
            //we have fully matched the response
            m_fullyMatched = true;

            m_success = true;

            //notify that the response was matched
            m_matchCondition.notify();

            return true;
        }

        return false;
    }

    bool Poll::Response::match_nodeReceived(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(!packet.deliveryStopFlags().pc ||                            //delivery stop flag
           packet.type() != WirelessPacket::packetType_nodeReceived ||  //app data type
           packet.nodeAddress() != m_nodeAddress ||                     //node address
           payload.size() != 7 ||                                       //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_poll       //command id
           )
        {
            //failed to match some of the bytes
            return false;
        }

        //if the status flag is success (0)
        if(payload.read_uint8(2) == 0)
        {
            m_started = true;

            //only want to read the time until completion if the cal has started
            m_timeUntilCompletion = payload.read_float(3);
        }

        return true;
    }

    bool Poll::Response::matchSuccessResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        std::size_t payloadLen = payload.size();

        //check the main bytes of the packet
        if(!packet.deliveryStopFlags().pc ||                                        //delivery stop flag
           packet.type() != WirelessPacket::packetType_nodeSuccessReply ||          //app data type
           packet.nodeAddress() != m_nodeAddress ||                                 //node address
           payloadLen < 4 ||                                                       //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_poll                   //command id
           )
        {
            //failed to match some of the bytes
            return false;
        }

        try
        {
            //parse out all the channel data
            ChannelMask pollMask(payload.read_uint16(2));

            size_t payloadPos = 4;

            for(uint8 i = 0; i <= pollMask.lastChEnabled(); i++)
            {
                if(pollMask.enabled(i))
                {
                    m_result[static_cast<WirelessChannel::ChannelId>(i)] = payload.read_float(payloadPos);
                    payloadPos += 4;    //move the payload position the size of a float
                }
            }
        }
        catch(...)
        {
            return false;
        }

        return true;
    }
} // namespace mscl
