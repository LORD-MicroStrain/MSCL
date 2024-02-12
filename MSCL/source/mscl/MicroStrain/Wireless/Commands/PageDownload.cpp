/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "PageDownload.h"
#include "WirelessProtocol.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/DataBuffer.h"

#include <algorithm>

namespace mscl
{
    ByteStream PageDownload::buildCommand(NodeAddress nodeAddress, uint16 pageIndex)
    {
        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint8(WirelessProtocol::cmdId_pageDownload);        //Command ID
        cmd.append_uint16(static_cast<uint16>(nodeAddress));           //Node address    (2 bytes)
        cmd.append_uint16(pageIndex);                                  //Page index    (2 bytes)

        return cmd;
    }

    PageDownload::Response::Response(std::weak_ptr<ResponseCollector> collector):
        WirelessResponsePattern(collector, WirelessProtocol::cmdId_pageDownload, 0),    //note: passing 0 since this response doesn't check node address :(
        m_matchedPart1(false)
    {
    }

    bool PageDownload::Response::match(DataBuffer& data)
    {
        //get a lock on the parsing mutex
        mutex_lock_guard lock(m_parsingMutex);

        //===============================================================================================================
        //Note: The Page Download command is unique in that the node sends 3 separate packets to the
        //        base station, which get concatenated and sent back. Unfortunately, this is not an ASPP
        //        packet. The initial Command ID byte (0x05) gets initially received, then there is a delay,
        //        then the first of 3 sets of bytes gets received, then a delay, then the second, delay,
        //        then the third. If handled normally, the data will get parsed too quickly and get thrown out
        //        as it is not a full response when it comes in. So we need to do some special parsing
        //        by matching the initial Command ID, then storing data until we get enough bytes to be a full response.
        //===============================================================================================================

        //if we haven't matched part 1 yet
        if(!m_matchedPart1)
        {
            //try to match part 1 of the command response
            if(matchSuccessResponsePart1(data))
            {
                //return success, but not complete so don't set the fully matched flag or notify
                return true;
            }

            return false;
        }

        //if the bytes match the fail response (must match perfectly, no extra bytes)
        /*if(matchFailResponse(data))
        {
            //we have fully matched the response
            m_fullyMatched = true;

            //notify that the response was matched
            m_matchCondition.notify();
            return true;
        }*/
        //if the bytes match the success response
        if(matchSuccessResponse(data))
        {
            //we have fully matched the response
            m_fullyMatched = true;

            //notify that the response was matched
            m_matchCondition.notify();
            return true;
        }

        //the bytes don't match any response
        return false;
    }

    ByteStream PageDownload::Response::dataPoints()
    {
        //get a lock on the parsing mutex
        mutex_lock_guard lock(m_parsingMutex);

        return m_dataPoints;
    }

    bool PageDownload::Response::matchSuccessResponsePart1(DataBuffer& data)
    {
        //create a save point with the data
        ReadBufferSavePoint savePoint(&data);

        //verify that we have enough bytes to match the success response (part 1)
        if(data.bytesRemaining() < 1)
        {
            return false;
        }

        //check if the first byte (Command ID) is correct
        if(data.read_uint8() != WirelessProtocol::cmdId_pageDownload)
        {
            return false;
        }

        //commit the current read position
        savePoint.commit();

        //mark that we have matched the first part of the response
        m_matchedPart1 = true;

        return true;
    }

    bool PageDownload::Response::matchSuccessResponse(DataBuffer& data)
    {
        static const uint16 TOTAL_SUCCESS_BYTES = 266;    //total bytes in the response, not including the 0x05
        static const uint16 TOTAL_DATA_BYTES = 264;        //total bytes of actual data

        //create a save point with the data
        ReadBufferSavePoint savePoint(&data);

        //calc the number of bytes to read (all the bytes in the buffer, up to 266 total including what is in the buffer already)
        size_t bytesToRead = std::min(data.bytesRemaining(), (TOTAL_SUCCESS_BYTES - m_dataPoints.size()));

        //go through the chunk of data bytes
        for(size_t byteItr = 0; byteItr < bytesToRead; ++byteItr)
        {
            //read the data bytes into the ByteStream
            m_dataPoints.append_uint8(data.read_uint8());
        }

        //commit the current read position
        savePoint.commit();

        //if we've read all the bytes that we need for the response
        if(m_dataPoints.size() == TOTAL_SUCCESS_BYTES)
        {
            //read the checksum that was transmitted with the data, should be the last 2 bytes in the buffer
            uint16 txChecksum = m_dataPoints.read_uint16(TOTAL_DATA_BYTES);

            //chop the checksum bytes off of the data
            m_dataPoints.resize(TOTAL_DATA_BYTES);

            //calculate our own checksum from the data points
            uint16 calculatedChecksum = m_dataPoints.calculateSimpleChecksum(0, (TOTAL_DATA_BYTES-1));

            //verify that the checksums are equal
            if(txChecksum != calculatedChecksum)
            {
                //clear out all the data in the buffer, its junk at this point
                m_dataPoints.clear();
                return false;
            }

            //set success to true
            m_success = true;
            return true;
        }

        return false;
    }

    bool PageDownload::Response::matchFailResponse(DataBuffer& data)
    {
        static const uint16 TOTAL_FAIL_BYTES = 1;//not including the 0x05

        //create a save point with the data
        ReadBufferSavePoint savePoint(&data);

        //verify that we have enough bytes for the fail response
        //Note:    Due to the poor structure of this command's response bytes
        //        we are enforcing that we only match this fail response
        //        if we ONLY have a single byte of 0x21. If more than 1 byte is present,
        //        it is possible that it is just part of a successful packet.
        //        This means that if other data is present with the 0x21, the command will
        //        need to timeout before we know that it has failed.
        if(data.bytesRemaining() != TOTAL_FAIL_BYTES)
        {
            return false;
        }

        //check if the second byte (Fail Response ID) is correct
        if(data.read_uint8() != 0x21)
        {
            return false;
        }

        //commit the current read position
        savePoint.commit();

        //set success to false
        m_success = false;

        return true;
    }
}