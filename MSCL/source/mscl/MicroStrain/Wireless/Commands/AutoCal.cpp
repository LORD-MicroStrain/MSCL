/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

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
    ByteStream AutoCal::buildCommand_shmLink(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress)
    {
        //build the command ByteStream
        ByteStream cmd;

        if(asppVer == WirelessPacket::aspp_v3)
        {
            cmd.append_uint8(WirelessPacket::ASPP_V3_SOP);          //Start of Packet
            cmd.append_uint8(0x04);                                 //Delivery Stop Flag
            cmd.append_uint8(0x00);                                 //App Data Type
            cmd.append_uint32(nodeAddress);                         //Node address
            cmd.append_uint16(0x0002);                              //Payload length
            cmd.append_uint16(WirelessProtocol::cmdId_autoCal_v1);  //Command ID
            cmd.append_uint16(0x7F7F);                              //dummy RSSI bytes
            cmd.append_uint32(cmd.calculateCrcChecksum());          //Checksum
        }
        else
        {
            cmd.append_uint8(WirelessPacket::ASPP_V1_SOP);              //Start of Packet
            cmd.append_uint8(0x05);                                     //Delivery Stop Flag
            cmd.append_uint8(0x00);                                     //App Data Type
            cmd.append_uint16(static_cast<uint16>(nodeAddress));        //Node address
            cmd.append_uint8(0x02);                                     //Payload length
            cmd.append_uint16(WirelessProtocol::cmdId_autoCal_v1);      //Command ID
            cmd.append_uint16(cmd.calculateSimpleChecksum(1, 7));       //Checksum
        }

        return cmd;
    }

    ByteStream AutoCal::buildCommand_shmLink201(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress)
    {
        //uses the same command packet as the SHM-Link
        return buildCommand_shmLink(asppVer, nodeAddress);
    }

    ByteStream AutoCal::buildCommand_shuntCal(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, const ShuntCalCmdInfo& info, uint8 chNum, WirelessModels::NodeModel nodeType, WirelessTypes::ChannelType chType)
    {
        uint16 inputRangeEepromVal = InputRange::inputRangeToEepromVal(info.inputRange, nodeType, chType);

        uint8 internalShunt = (info.useInternalShunt) ? 1 : 0;

        //build the command ByteStream
        ByteStream cmd;

        if(asppVer == WirelessPacket::aspp_v3)
        {
            cmd.append_uint8(WirelessPacket::ASPP_V3_SOP);              //Start of Packet
            cmd.append_uint8(0x04);                                     //Delivery Stop Flag
            cmd.append_uint8(0x00);                                     //App Data Type
            cmd.append_uint32(nodeAddress);                             //Node address
            cmd.append_uint16(18);                                      //Payload length
            cmd.append_uint16(WirelessProtocol::cmdId_autoCal_v1);      //Command ID
            cmd.append_uint8(chNum);
            cmd.append_uint8(internalShunt);
            cmd.append_uint8(static_cast<uint8>(inputRangeEepromVal));
            cmd.append_uint16(info.hardwareOffset);
            cmd.append_uint8(info.numActiveGauges);
            cmd.append_uint16(info.gaugeResistance);
            cmd.append_uint32(info.shuntResistance);
            cmd.append_float(info.gaugeFactor);
            cmd.append_uint16(0x7F7F);                                  //dummy RSSI bytes
            cmd.append_uint32(cmd.calculateCrcChecksum());              //Checksum
        }
        else
        {
            cmd.append_uint8(WirelessPacket::ASPP_V1_SOP);              //Start of Packet
            cmd.append_uint8(0x05);                                     //Delivery Stop Flag
            cmd.append_uint8(0x00);                                     //App Data Type
            cmd.append_uint16(static_cast<uint16>(nodeAddress));        //Node address
            cmd.append_uint8(18);                                       //Payload length
            cmd.append_uint16(WirelessProtocol::cmdId_autoCal_v1);      //Command ID
            cmd.append_uint8(chNum);
            cmd.append_uint8(internalShunt);
            cmd.append_uint8(static_cast<uint8>(inputRangeEepromVal));
            cmd.append_uint16(info.hardwareOffset);
            cmd.append_uint8(info.numActiveGauges);
            cmd.append_uint16(info.gaugeResistance);
            cmd.append_uint32(info.shuntResistance);
            cmd.append_float(info.gaugeFactor);
            cmd.append_uint16(cmd.calculateSimpleChecksum(1, 23));      //Checksum
        }

        return cmd;
    }

    AutoCal::Response::Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector):
        WirelessResponsePattern(collector, WirelessProtocol::cmdId_autoCal_v1, nodeAddress),
        m_nodeAddress(nodeAddress),
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
        //get a lock on the parsing mutex
        mutex_lock_guard lock(m_parsingMutex);

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

    bool AutoCal::Response::match_nodeReceived(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(!packet.deliveryStopFlags().pc ||                            //delivery stop flag
           packet.type() != WirelessPacket::packetType_nodeReceived ||  //app data type
           packet.nodeAddress() != m_nodeAddress ||                     //node address
           payload.size() != 7 ||                                       //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_autoCal_v1 //command id
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

    AutoCal::ShmResponse::ShmResponse(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector):
        AutoCal::Response(nodeAddress, collector)
    {
    }

    bool AutoCal::ShmResponse::matchSuccessResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        std::size_t payloadLen = payload.size();

        //check the main bytes of the packet
        if(!packet.deliveryStopFlags().pc ||                                        //delivery stop flag
           packet.type() != WirelessPacket::packetType_nodeSuccessReply ||          //app data type
           packet.nodeAddress() != m_nodeAddress ||                                 //node address
           payloadLen != 22 ||                                                      //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_autoCal_v1             //command id
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

        return true;
    }

    AutoCal::Shm201Response::Shm201Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector):
        AutoCal::Response(nodeAddress, collector)
    {
    }

    bool AutoCal::Shm201Response::matchSuccessResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        std::size_t payloadLen = payload.size();

        //check the main bytes of the packet
        if(!packet.deliveryStopFlags().pc ||                                        //delivery stop flag
           packet.type() != WirelessPacket::packetType_nodeSuccessReply ||          //app data type
           packet.nodeAddress() != m_nodeAddress ||                                 //node address
           payloadLen != 34 ||                                                      //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_autoCal_v1             //command id
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

        return true;
    }

    AutoCal::ShuntCalResponse::ShuntCalResponse(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector, uint8 channelNumber):
        AutoCal::Response(nodeAddress, collector),
        m_channelNumber(channelNumber)
    {
    }

    bool AutoCal::ShuntCalResponse::matchSuccessResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        std::size_t payloadLen = payload.size();

        //check the main bytes of the packet
        if(!packet.deliveryStopFlags().pc ||                                        //delivery stop flag
           packet.type() != WirelessPacket::packetType_nodeSuccessReply ||          //app data type
           packet.nodeAddress() != m_nodeAddress ||                                 //node address
           payloadLen != 37 ||                                                      //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_autoCal_v1 ||          //command id
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

        return true;
    }
}