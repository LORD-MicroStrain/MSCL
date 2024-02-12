/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "WirelessProtocol.h"
#include "Erase.h"

namespace mscl
{
    ByteStream Erase::buildCommand(NodeAddress nodeAddress)
    {
        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint8(WirelessProtocol::cmdId_erase);    //Command ID
        cmd.append_uint16(static_cast<uint16>(nodeAddress));//Node address  (2 bytes)
        cmd.append_uint32(0x08100CFF);                      //Command Bytes (4 bytes)

        return cmd;
    }

    Erase::Response::Response(std::weak_ptr<ResponseCollector> collector):
        WirelessResponsePattern(collector, WirelessProtocol::cmdId_erase, 0)    //note: passing 0 since this response doesn't check node address :(
    {
    }

    bool Erase::Response::match(DataBuffer& data)
    {
        //get a lock on the parsing mutex
        mutex_lock_guard lock(m_parsingMutex);

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
        //single byte 0x06 is a success response
        else if(resultByte == WirelessProtocol::cmdId_erase)
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