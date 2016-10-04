/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "AutoCal.h"
#include "AutoCalInfo.h"
#include "WirelessProtocol.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/Wireless/Configuration/InputRange.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{
    //=====================================================
    //AutoCal
    //=====================================================
    ByteStream AutoCal::buildCommand_shmLink(NodeAddress nodeAddress)
    {
        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint8(0xAA);                                    //Start of Packet
        cmd.append_uint8(0x05);                                    //Delivery Stop Flag
        cmd.append_uint8(0x00);                                    //App Data Type
        cmd.append_uint16(nodeAddress);                            //Node address    (2 bytes)
        cmd.append_uint8(0x02);                                    //Payload length
        cmd.append_uint16(WirelessProtocol::cmdId_autoCal);        //Command ID    (2 bytes)

        //calculate the checksum of bytes 2-8
        uint16 checksum = cmd.calculateSimpleChecksum(1, 7);

        cmd.append_uint16(checksum);        //Checksum        (2 bytes)

        return cmd;
    }

    ByteStream AutoCal::buildCommand_shuntCal(NodeAddress nodeAddress, const ShuntCalCmdInfo& info, uint8 chNum, WirelessModels::NodeModel nodeType, WirelessTypes::ChannelType chType)
    {
        uint16 inputRangeEepromVal = InputRange::inputRangeToEepromVal(info.inputRange, nodeType, chType);

        uint8 internalShunt = (info.useInternalShunt) ? 1 : 0;

        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint8(0xAA);                                    //Start of Packet
        cmd.append_uint8(0x05);                                    //Delivery Stop Flag
        cmd.append_uint8(0x00);                                    //App Data Type
        cmd.append_uint16(nodeAddress);                            //Node address
        cmd.append_uint8(18);                                      //Payload length
        cmd.append_uint16(WirelessProtocol::cmdId_autoCal);        //Command ID
        cmd.append_uint8(chNum);
        cmd.append_uint8(internalShunt);
        cmd.append_uint8(static_cast<uint8>(inputRangeEepromVal));
        cmd.append_uint16(info.hardwareOffset);
        cmd.append_uint8(info.numActiveGauges);
        cmd.append_uint16(info.gaugeResistance);
        cmd.append_uint32(info.shuntResistance);
        cmd.append_float(info.gaugeFactor);

        //calculate the checksum of bytes 2-24
        uint16 checksum = cmd.calculateSimpleChecksum(1, 23);

        cmd.append_uint16(checksum);        //Checksum        (2 bytes)

        return cmd;
    }

    AutoCal::Response::Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector, AutoCalType type):
        ResponsePattern(collector),
        m_nodeAddress(nodeAddress),
        m_calType(type),
        m_calStarted(false),
        m_completionFlag(WirelessTypes::autocal_notComplete),
        m_timeUntilCompletion(0.0f)
    {
    }

    bool AutoCal::Response::calStarted() const
    {
        return m_calStarted;
    }

    float AutoCal::Response::calTime() const
    {
        return m_timeUntilCompletion;
    }

    WirelessTypes::AutoCalCompletionFlag AutoCal::Response::completionFlag() const
    {
        return m_completionFlag;
    }

    const Bytes& AutoCal::Response::infoBytes() const
    {
        return m_infoBytes;
    }

    bool AutoCal::Response::match(const WirelessPacket& packet)
    {
        //if the Node hasn't said it started yet
        if(!m_calStarted)
        {
            //check if this matches the "Node Received AutoCal Command" response
            if(match_nodeReceived(packet))
            {
                //if the autocal has now started
                if(m_calStarted)
                {
                    //successfully started, not complete so don't set the fullyMatched flag

                    //notify that the response was matched
                    m_matchCondition.notify();

                    return true;
                }
                else
                {
                    //got a bad status, so autocal won't be started (not expecting another packet)
                    m_fullyMatched = true;

                    //notify that the response was matched
                    m_matchCondition.notify();

                    return true;
                }
            }
        }

        //if we made it here, the autocal has started and we are looking for a completion packet
        switch(m_calType)
        {
            case AutoCalType::calType_shm:
            {
                if(!match_shmLink(packet))
                {
                    return false;
                }
                break;
            }

            case AutoCalType::calType_shunt:
            {
                if(!match_shuntCal(packet))
                {
                    return false;
                }
                break;
            }

            default:
                return false;
        }

        //we have fully matched the response
        m_fullyMatched = true;

        //notify that the response was matched
        m_matchCondition.notify();

        return true;
    }

    bool AutoCal::Response::match_nodeReceived(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(packet.deliveryStopFlags().toInvertedByte() != 0x07 ||       //delivery stop flag
           packet.type() != 0x20 ||                                     //app data type
           packet.nodeAddress() != m_nodeAddress ||                     //node address
           payload.size() != 0x07 ||                                    //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_autoCal    //command id
           )
        {
            //failed to match some of the bytes
            return false;
        }

        //if the status flag is success (0)
        if(payload.read_uint8(2) == 0)
        {
            m_calStarted = true;

            //only want to read the time until completion if the cal has started
            m_timeUntilCompletion = payload.read_float(3);
        }

        return true;
    }

    bool AutoCal::Response::match_shmLink(const WirelessPacket& packet)
    {
        return false;
    }

    bool AutoCal::Response::match_shuntCal(const WirelessPacket& packet)
    {
        return false;
    }

    AutoCal::ShmResponse::ShmResponse(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector):
        AutoCal::Response(nodeAddress, collector, AutoCalType::calType_shm)
    {
    }

    bool AutoCal::ShmResponse::match_shmLink(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        std::size_t payloadLen = payload.size();

        //check the main bytes of the packet
        if(packet.deliveryStopFlags().toInvertedByte() != 0x07 ||                    //delivery stop flag
           packet.type() != WirelessPacket::packetType_nodeSuccessReply ||           //app data type
           packet.nodeAddress() != m_nodeAddress ||                                  //node address
           payloadLen != 22 ||                                                       //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_autoCal                 //command id
           )
        {
            //failed to match some of the bytes
            return false;
        }

        //Pass/Fail Flag
        m_completionFlag = static_cast<WirelessTypes::AutoCalCompletionFlag>(payload.read_uint8(2));
        
        //Info Bytes
        for(std::size_t i = 3; i < payloadLen; ++i)
        {
            //add all of the payload info bytes to m_infoBytes
            m_infoBytes.push_back(payload.read_uint8(i));
        }

        //setting success to true if it got this packet, even if the cals applied might be bad
        m_success = true;

        return true;
    }

    AutoCal::ShuntCalResponse::ShuntCalResponse(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector, uint8 channelNumber):
        AutoCal::Response(nodeAddress, collector, AutoCalType::calType_shunt),
        m_channelNumber(channelNumber)
    {
    }

    bool AutoCal::ShuntCalResponse::match_shuntCal(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        std::size_t payloadLen = payload.size();

        //check the main bytes of the packet
        if(packet.deliveryStopFlags().toInvertedByte() != 0x07 ||                   //delivery stop flag
           packet.type() != WirelessPacket::packetType_nodeSuccessReply ||          //app data type
           packet.nodeAddress() != m_nodeAddress ||                                 //node address
           payloadLen != 37 ||                                                      //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_autoCal ||             //command id
           payload.read_uint8(3) != m_channelNumber                                 //channel number
           )
        {
            //failed to match some of the bytes
            return false;
        }

        //Pass/Fail Flag
        m_completionFlag = static_cast<WirelessTypes::AutoCalCompletionFlag>(payload.read_uint8(2));

        //Info Bytes
        for(std::size_t i = 3; i < payloadLen; ++i)
        {
            //add all of the payload info bytes to m_infoBytes
            m_infoBytes.push_back(payload.read_uint8(i));
        }

        //setting success to true if it got this packet, even if the cals applied might be bad
        m_success = true;

        return true;
    }
}