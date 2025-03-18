/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/ResponsePattern.h"

#include "mscl/MicroStrain/ResponseCollector.h"

namespace mscl
{
    ResponsePattern::ResponsePattern() :
        m_fullyMatched(false),
        m_success(false)
    {
    }

    ResponsePattern::ResponsePattern(std::weak_ptr<ResponseCollector> collector) :
        m_collector(collector),
        m_fullyMatched(false),
        m_success(false)
    {
        //attempt to get the pointer from the weak_ptr
        std::shared_ptr<ResponseCollector> shCollector(m_collector.lock());

        //if we got the shared_ptr
        if(shCollector)
        {
            //register this response with the collector
            shCollector->registerResponse(this);
        }
    }

    ResponsePattern::~ResponsePattern()
    {
        //attempt to get the pointer from the weak_ptr
        std::shared_ptr<ResponseCollector> shCollector(m_collector.lock());

        //if we got the shared_ptr
        if(shCollector)
        {
            //unregister this response with the collector
            shCollector->unregisterResponse(this);
        }
    }

    void ResponsePattern::setResponseCollector(std::weak_ptr<ResponseCollector> collector)
    {
        //verify we don't already have a collector
        if(!m_collector.expired())
        {
            //not allowing the response collector to get reassigned (shouldn't be needed)
            return;
        }

        m_collector = collector;

        //attempt to get the pointer from the weak_ptr
        std::shared_ptr<ResponseCollector> shCollector(m_collector.lock());

        //if we got the shared_ptr
        if(shCollector)
        {
            //register this response with the collector
            shCollector->registerResponse(this);
        }
    }

    bool ResponsePattern::wait(uint64 timeout)
    {
        //perform a timedWait on the matchCondition, returning the result
        return m_matchCondition.timedWait(timeout);
    }

    void ResponsePattern::throwIfFailed(const std::string& commandName) const
    {
        if(!m_success)
        {
            throw Error("The " + commandName + " command has failed.");
        }
    }

    bool ResponsePattern::matchSuccessResponse(DataBuffer& data)
    {
        return false;
    }

    bool ResponsePattern::matchSuccessResponse(const WirelessPacket& packet)
    {
        return false;
    }

    bool ResponsePattern::matchFailResponse(DataBuffer& data)
    {
        return false;
    }

    bool ResponsePattern::matchFailResponse(const WirelessPacket& packet)
    {
        return false;
    }

    bool ResponsePattern::matchBaseReceivedResponse(const WirelessPacket& packet)
    {
        return false;
    }

    bool ResponsePattern::match(DataBuffer& data)
    {
        //get a lock on the parsing mutex
        mutex_lock_guard lock(m_parsingMutex);

        //if the bytes match the success response
        if(matchSuccessResponse(data))
        {
            //we have fully matched the response
            m_fullyMatched = true;

            m_success = true;

            //notify that the response was matched
            m_matchCondition.notify();
            return true;
        }
        //if the bytes match the fail response
        else if(matchFailResponse(data))
        {
            //we have fully matched the response
            m_fullyMatched = true;

            m_success = false;

            //notify that the response was matched
            m_matchCondition.notify();
            return true;
        }

        //the bytes don't match any response
        return false;
    }

    bool ResponsePattern::match(const WirelessPacket& packet)
    {
        //get a lock on the parsing mutex
        mutex_lock_guard lock(m_parsingMutex);

        if(matchBaseReceivedResponse(packet))
        {
            //successfully started, not complete so don't set the fullyMatched flag

            //notify that the response was matched
            m_matchCondition.notify();
            return true;
        }

        //if the bytes match the success response
        if(matchSuccessResponse(packet))
        {
            //we have fully matched the response
            m_fullyMatched = true;

            m_success = true;

            //notify that the response was matched
            m_matchCondition.notify();
            return true;
        }
        //if the bytes match the fail response
        else if(matchFailResponse(packet))
        {
            //we have fully matched the response
            m_fullyMatched = true;

            m_success = false;

            //notify that the response was matched
            m_matchCondition.notify();
            return true;
        }

        //the bytes don't match any response
        return false;
    }

    bool ResponsePattern::match(const MipDataField& field)
    {
        return false;
    }

    bool ResponsePattern::fullyMatched() const
    {
        //get a lock on the parsing mutex
        mutex_lock_guard lock(m_parsingMutex);

        return m_fullyMatched;
    }

    bool ResponsePattern::success() const
    {
        //get a lock on the parsing mutex
        mutex_lock_guard lock(m_parsingMutex);

        return m_success;
    }
}
