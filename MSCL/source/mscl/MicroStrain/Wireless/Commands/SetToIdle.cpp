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

        uint16 response = data.read_uint16();

        //response of 0x9001 is a success response
        if(response == 0x9001)
        {
            //success response
            m_result = SetToIdleStatus::setToIdleResult_success;
            m_success = true;
        }
        //response of 0x2101 is a canceled response
        else if(response == 0x2101)
        {
            //fail/canceled response
            m_result = SetToIdleStatus::setToIdleResult_canceled;
        }
        else
        {
            //no match found, just return
            return false;
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
        
        //retry to cancel a few times unless the status changes
        const uint8 MAX_RETRIES = 3;
        uint8 retryCount = 0;
        while(m_result == SetToIdleStatus::setToIdleResult_notCompleted && retryCount <= MAX_RETRIES)
        {
            Utils::threadSleep(100);
            m_baseStation.connection().write(cancel);
            retryCount++;
        }
    }

    SetToIdleStatus::SetToIdleResult SetToIdle::Response::result()
    {
        //create a lock for thread safety
        mutex_lock_guard lock(m_setToIdleMutex);

        return m_result;
    }
}