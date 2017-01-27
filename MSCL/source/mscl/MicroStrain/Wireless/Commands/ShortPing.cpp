/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "ShortPing.h"
#include "WirelessProtocol.h"
#include "mscl/MicroStrain/ByteStream.h"


namespace mscl
{
    ByteStream ShortPing::buildCommand(NodeAddress nodeAddress)
    {
        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint8(WirelessProtocol::cmdId_shortPing);
        cmd.append_uint16(nodeAddress);    //Node address    (2 bytes)

        return cmd;
    }

    ShortPing::Response::Response(std::weak_ptr<ResponseCollector> collector):
        ResponsePattern(collector)
    {
    }

    bool ShortPing::Response::match(DataBuffer& data)
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

        uint8 resultByte = data.read_uint8();

        //single byte 0x21 is a fail response
        if(resultByte == 0x21)
        {
            //legitimate fail response
            m_success = false;
        }
        //single byte 0x02 is a success response
        else if(resultByte == WirelessProtocol::cmdId_shortPing)
        {
            //success response
            m_success = true;
        }
        else
        {
            //non-matching response
            m_success = false;
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
}