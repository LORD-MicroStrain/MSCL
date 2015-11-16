/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "BaseStation_SetBeacon.h"

namespace mscl
{
    ByteStream BaseStation_SetBeacon::buildCommand(uint32 utcTime)
    {
        uint32 beaconTime = utcTime;

        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint16(COMMAND_ID);
        cmd.append_uint32(beaconTime);                    

        return cmd;
    }


    BaseStation_SetBeacon::Response::Response(uint64 utcTime, std::weak_ptr<ResponseCollector> collector):
        ResponsePattern(collector),
        m_beaconStartTime(utcTime * TimeSpan::NANOSECONDS_PER_SECOND)
    {
    }

    bool BaseStation_SetBeacon::Response::match(DataBuffer& data)
    {
        const uint16 TOTAL_SUCCESS_BYTES = 2;

        //create a save point with the data
        ReadBufferSavePoint savePoint(&data);

        //if there aren't enough bytes in the buffer to match the response
        if(data.bytesRemaining() < TOTAL_SUCCESS_BYTES) 
        { 
            return false; 
        }

        //if it doesn't match the command Id
        if(data.read_uint16() != COMMAND_ID) 
        { 
            return false; 
        }

        //if we made it this far, we successfully matched everything

        //commit the current read position
        savePoint.commit();

        //set the result to success
        m_success = true;

        //we have fully matched the response
        m_fullyMatched = true;

        //notify that the response was matched
        m_matchCondition.notify();

        return true;
    }

    Timestamp BaseStation_SetBeacon::Response::beaconStartTime() const
    {
        return m_beaconStartTime;
    }
}