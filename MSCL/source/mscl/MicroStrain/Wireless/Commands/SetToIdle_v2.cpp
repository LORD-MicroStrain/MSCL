/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "SetToIdle_v2.h"
#include "WirelessProtocol.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{
    ByteStream SetToIdle_v2::buildCommand(NodeAddress nodeAddress)
    {
        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint8(WirelessPacket::ASPP_V1_SOP);              //Start of Packet
        cmd.append_uint8(0x0E);                                     //Delivery Stop Flag
        cmd.append_uint8(WirelessPacket::packetType_baseCommand);   //App Data Type
        cmd.append_uint16(WirelessProtocol::BASE_STATION_ADDRESS);  //Base Station Address
        cmd.append_uint8(0x04);                                     //Payload Length
        cmd.append_uint16(WirelessProtocol::cmdId_stopNode_v2);     //Command ID
        cmd.append_uint16(static_cast<uint16>(nodeAddress));        //Node address

        //calculate the checksum of bytes 2-10
        uint16 checksum = cmd.calculateSimpleChecksum(1, 9);

        cmd.append_uint16(checksum);    //Checksum

        return cmd;
    }

    ByteStream SetToIdle_v2::buildCommand_aspp3(NodeAddress nodeAddress)
    {
        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint8(WirelessPacket::ASPP_V3_SOP);              //Start of Packet
        cmd.append_uint8(0x01);                                     //Delivery Stop Flag
        cmd.append_uint8(WirelessPacket::packetType_baseCommand);   //App Data Type
        cmd.append_uint32(WirelessProtocol::BASE_STATION_ADDRESS);  //Base Station Address
        cmd.append_uint16(0x0006);                                  //Payload Length
        cmd.append_uint16(WirelessProtocol::cmdId_stopNode_v2);     //Command ID
        cmd.append_uint32(nodeAddress);                             //Node address
        cmd.append_uint16(0x7F7F);                                  //dummy rssi bytes
        cmd.append_uint32(cmd.calculateCrcChecksum());              //checksum

        return cmd;
    }

    SetToIdle_v2::Response::Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector, const BaseStation& baseStation):
        SetToIdle::Response(nodeAddress, collector, baseStation),
        m_started(false)
    {
    }

    SetToIdle_v2::Response::~Response()
    {
        //will be canceled in the parent class's destructor
    }

    bool SetToIdle_v2::Response::match(const WirelessPacket& packet)
    {
        //get a lock on the parsing mutex
        mutex_lock_guard lock(m_parsingMutex);

        //if the BaseStation hasn't reported that the operation has started
        if(!m_started)
        {
            //check if this matches the Base Station received response
            if(match_baseReceived(packet))
            {
                //successfully started, not complete so don't set the fullyMatched flag

                //notify that the response was matched
                m_matchCondition.notify();

                return true;
            }
        }

        //check if this matches the completion response
        if(match_completion(packet))
        {
            m_fullyMatched = true;

            m_matchCondition.notify();

            return true;
        }

        return false;
    }

    bool SetToIdle_v2::Response::match_baseReceived(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(!packet.deliveryStopFlags().pc ||                                    //delivery stop flag
           packet.type() != WirelessPacket::packetType_baseReceived             //app data type
           )
        {
            //failed to match some of the bytes
            return false;
        }

        if(packet.asppVersion() == mscl::WirelessPacket::aspp_v3)
        {
            if(payload.size() != 11 ||
               payload.read_uint16(0) != WirelessProtocol::cmdId_stopNode_v2 ||     //command ID
               payload.read_uint32(3) != 0x7F800000 ||                              //infinite time until completion (indefinite)
               payload.read_uint32(7) != m_nodeAddress                              //node address
               )
            {
                return false;
            }
        }
        else
        {
            if(payload.size() != 9 ||
               payload.read_uint16(0) != WirelessProtocol::cmdId_stopNode_v2 ||     //command ID
               payload.read_uint32(3) != 0x7F800000 ||                              //infinite time until completion (indefinite)
               payload.read_uint16(7) != m_nodeAddress                              //node address
               )
            {
                return false;
            }
        }

        m_started = true;

        return true;
    }

    bool SetToIdle_v2::Response::match_completion(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();
        uint8 status;

        //check the main bytes of the packet
        if(!packet.deliveryStopFlags().pc ||                                    //delivery stop flag
           packet.type() != WirelessPacket::packetType_baseSuccessReply         //app data type
           )
        {
            //failed to match some of the bytes
            return false;
        }

        if(packet.asppVersion() == mscl::WirelessPacket::aspp_v3)
        {
            if(payload.size() != 7 ||                                               //payload length
               payload.read_uint16(0) != WirelessProtocol::cmdId_stopNode_v2 ||     //command ID
               payload.read_uint32(2) != m_nodeAddress                              //eeprom address
               )
            {
                return false;
            }

            status = payload.read_uint8(6);
        }
        else
        {
            if(payload.size() != 5 ||                                               //payload length
               payload.read_uint16(0) != WirelessProtocol::cmdId_stopNode_v2 ||     //command ID
               payload.read_uint16(2) != m_nodeAddress                              //eeprom address
               )
            {
                return false;
            }

            status = payload.read_uint8(4);
        }

        //create a lock for thread safety
        mutex_lock_guard lock(m_setToIdleMutex);

        //check the status flag for the result
        static const uint8 SUCCESS = 0;
        static const uint8 CANCELED = 1;

        if(status == SUCCESS)
        {
            m_result = SetToIdleStatus::setToIdleResult_success;
            m_success = true;
        }
        else if(status == CANCELED)
        {
            m_result = SetToIdleStatus::setToIdleResult_canceled;
        }
        else
        {
            //need to handle another status byte
            assert(false);
            return false;
        }

        //we have fully matched the response
        m_fullyMatched = true;

        //notify that the response was matched
        m_matchCondition.notify();

        return true;
    }

    bool SetToIdle_v2::Response::started()
    {
        return m_started;
    }
}