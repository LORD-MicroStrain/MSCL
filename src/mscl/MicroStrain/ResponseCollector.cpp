/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/ResponseCollector.h"

#include "mscl/MicroStrain/ResponsePattern.h"

namespace mscl
{
    ResponseCollector::ResponseCollector() :
      m_connection(nullptr)
    {}

    void ResponseCollector::setConnection(Connection* connection)
    {
        m_connection = connection;
    }

    void ResponseCollector::registerResponse(ResponsePattern* response)
    {
        //get a lock on the response mutex
        mutex_lock_guard lock(m_responseMutex);

        //determine the minimum byte position for the response
        std::size_t minBytePos = 0;
        if(m_connection)
        {
            minBytePos = m_connection->byteAppendPos();
        }

        //add the ResponsePattern to the vector of expected responses
        m_expectedResponses.emplace_back(response, minBytePos);
    }

    void ResponseCollector::unregisterResponse(ResponsePattern* response)
    {
        //get a lock on the response mutex
        mutex_lock_guard lock(m_responseMutex);

        //find the ResponsePattern in the vector of expected responses
        for(auto itr = m_expectedResponses.begin(); itr < m_expectedResponses.end(); ++itr)
        {
            if(itr->pattern == response)
            {
                //remove the response from the vector
                m_expectedResponses.erase(itr);
                return;
            }
        }
    }

    bool ResponseCollector::waitingForResponse()
    {
        //get a lock on the response mutex
        mutex_lock_guard lock(m_responseMutex);

        return !m_expectedResponses.empty();
    }

    void ResponseCollector::adjustResponsesMinBytePos(std::size_t bytesToSubtract)
    {
        //get a lock on the response mutex
        mutex_lock_guard lock(m_responseMutex);

        //subtract the byte position from each expected response
        for(auto itr = m_expectedResponses.begin(); itr < m_expectedResponses.end(); ++itr)
        {
            if(bytesToSubtract > itr->minBytePosition)
            {
                //don't let the position go negative
                itr->minBytePosition = 0;
            }
            else
            {
                itr->minBytePosition -= bytesToSubtract;
            }
        }
    }

    bool ResponseCollector::matchExpected(DataBuffer& data)
    {
        //make a save point so we can revert if need be
        ReadBufferSavePoint savepoint(&data);

        size_t startBytesRemaining = 0;

        //get a lock on the response mutex
        mutex_lock_guard lock(m_responseMutex);

        //need to loop over all of the bytes to check for responses
        while(data.moreToRead())
        {
            //log the bytes remaining in the data before we attempt to match
            startBytesRemaining = data.bytesRemaining();

            //look through all the expected responses
            for(auto itr = m_expectedResponses.begin(); itr < m_expectedResponses.end(); ++itr)
            {
                //don't try to match bytes that were in the buffer before the command was sent
                if(data.readPosition() < itr->minBytePosition)
                {
                    continue;
                }

                //if we found a match
                if(itr->pattern->match(data))
                {
                    //match functions move the data pointer on success (even if not fully matched)
                    //need to make sure we don't roll back to our previous savepoint.
                    savepoint.commit();

                    if(itr->pattern->fullyMatched())
                    {
                        //unregister the response
                        m_expectedResponses.erase(itr);
                    }

                    return true;
                }

                //if any match function moved the data pointer, we don't want to move it back here
                if(startBytesRemaining != data.bytesRemaining())
                {
                    savepoint.commit();
                }
            }

            //if we can move to the next byte and the byte position hasn't been moved elsewhere (internally by a match function).
            if(data.moreToRead() && startBytesRemaining == data.bytesRemaining())
            {
                //move to the next byte and check for the response again
                data.read_uint8();
            }
        }

        return false;
    }

    bool ResponseCollector::matchExpected(const WirelessPacket& packet, std::size_t lastReadPos)
    {
        //get a lock on the response mutex
        mutex_lock_guard lock(m_responseMutex);

        //look through all the expected responses
        for(auto itr = m_expectedResponses.begin(); itr < m_expectedResponses.end(); ++itr)
        {
            //don't try to match bytes/packets that were in the buffer before the command was sent
            if(lastReadPos < itr->minBytePosition)
            {
                continue;
            }

            //if we found a match
            if(itr->pattern->match(packet))
            {
                if(itr->pattern->fullyMatched())
                {
                    //unregister the response
                    m_expectedResponses.erase(itr);
                }

                return true;
            }
        }

        return false;
    }

    bool ResponseCollector::matchExpected(MipDataField& field)
    {
        //get a lock on the response mutex
        mutex_lock_guard lock(m_responseMutex);

        //look through all the expected responses
        for(auto itr = m_expectedResponses.begin(); itr < m_expectedResponses.end(); ++itr)
        {
            //if we found a match
            if(itr->pattern->match(field))
            {
                if(itr->pattern->fullyMatched() )
                {
                    //unregister the response
                    m_expectedResponses.erase(itr);
                }

                return true;
            }
        }

        return false;
    }
} // namespace mscl
