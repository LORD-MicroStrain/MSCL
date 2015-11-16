/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "BaseStation_Ping.h"

namespace mscl
{

    ByteStream BaseStation_Ping::buildCommand()
    {
        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint8(0x01);

        return cmd;
    }

    BaseStation_Ping::Response::Response(std::weak_ptr<ResponseCollector> collector):
        ResponsePattern(collector)
    {
    }

    bool BaseStation_Ping::Response::match(DataBuffer& data)
    {
        const uint16 TOTAL_BYTES = 1;

        //if there aren't enough bytes in the buffer to match the response
        if(data.bytesRemaining() < TOTAL_BYTES)
        {
            //not a good response
            m_success = false;
            return false;
        }

        //create a save point with the data
        ReadBufferSavePoint savePoint(&data);

        //single byte response of 0x01
        if(data.read_uint8() != 0x01)
        {
            //not a good response
            m_success = false;
            return false;
        }

        //if we made it this far, the bytes match the response

        //commit the current read position
        savePoint.commit();

        //the ping was a success
        m_success = true;

        //we have fully matched the response
        m_fullyMatched = true;

        //notify that the response was matched
        m_matchCondition.notify();

        return true;
    }
}