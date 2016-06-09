/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "SetToIdle.h"
#include "WirelessProtocol.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{
    ByteStream SetToIdle::buildCommand(NodeAddress nodeAddress)
    {
        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint8(0xAA);                                     //Start of Packet
        cmd.append_uint8(0xFE);                                     //Delivery Stop Flag
        cmd.append_uint8(0x00);                                     //App Data Type
        cmd.append_uint16(nodeAddress);                             //Node address    (2 bytes)
        cmd.append_uint8(0x02);                                     //Payload Length
        cmd.append_uint16(WirelessProtocol::cmdId_stopNode);        //Command ID    (2 bytes)

        //calculate the checksum of bytes 2-8
        uint16 checksum = cmd.calculateSimpleChecksum(1, 7);

        cmd.append_uint16(checksum);    //Checksum        (2 bytes)

        return cmd;
    }

    SetToIdle::Response::Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector, const BaseStation& baseStation):
        ResponsePattern(collector),
        m_nodeAddress(nodeAddress),
        m_result(SetToIdleStatus::setToIdleResult_notCompleted),
        m_baseStation(baseStation)
    {
    }

    SetToIdle::Response::~Response()
    {
        try
        {
            //cancel the set to idle command if needed
            cancel();
        }
        catch(...)
        {
            //make sure desctructor doesn't throw an exception
        }
    }

    bool SetToIdle::Response::match(DataBuffer& data)
    {
        const uint16 TOTAL_BYTES = 2;

        size_t bytesInBuffer = data.bytesRemaining();

        //if there aren't enough bytes for a complete response
        if(bytesInBuffer < TOTAL_BYTES)
        {
            return false;
        }

        //create a save point with the data
        ReadBufferSavePoint savePoint(&data);

        //create a lock for thread safety
        mutex_lock_guard lock(m_setToIdleMutex);

        bool done = false;
        while(!done)
        {
            uint8 response = data.read_uint8();
            uint8 response2 = data.peekByte();    //only want to peek in case it isn't right and then the next loop we want to look at it again

            //response of 0x9001 is a success response
            if(response == 0x90 && (response2 == 0x01))
            {
                //consume the byte we peeked at
                data.read_uint8();

                //success response
                m_result = SetToIdleStatus::setToIdleResult_success;
                m_success = true;
                done = true;
            }
            //response of 0x2101 is a canceled response
            else if(response == 0x21 && (response2 == 0x01))
            {
                //fail/canceled response
                m_result = SetToIdleStatus::setToIdleResult_canceled;
                done = true;
            }
            //some other bytes
            else
            {
                //if we don't have enough bytes left to check
                if(data.bytesRemaining() < TOTAL_BYTES)
                {
                    //no match found, just return
                    return false;
                }
            }
        }

        //if we made it this far, the bytes match the expected response (success or fail)

        //commit the current read position
        savePoint.commit();

        //we have fully matched the response
        m_fullyMatched = true;

        //notify that the response was matched
        m_matchCondition.notify();

        return true;
    }

    void SetToIdle::Response::cancel()
    {
        //if the Set to Idle process has already completed/canceled
        if(m_result != SetToIdleStatus::setToIdleResult_notCompleted)
        {
            //don't do anything, just return
            return;
        }

        //send any byte to the Base Station to cancel the operation
        static const Bytes cancel{0x01};
        m_baseStation.connection().write(cancel);
        
        //wait for the response to be met (trying to match the "canceled" response)
        if(!wait(m_baseStation.timeout() + 100))
        {
            throw Error_Communication("Failed to cancel the Set to Idle operation.");
        }
        else
        {
            m_result = SetToIdleStatus::setToIdleResult_canceled;
        }
    }

    SetToIdleStatus::SetToIdleResult SetToIdle::Response::result()
    {
        //create a lock for thread safety
        mutex_lock_guard lock(m_setToIdleMutex);

        return m_result;
    }
}