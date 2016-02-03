/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "ResponsePattern.h"

#include "mscl/Exceptions.h"
#include "Wireless/Packets/WirelessPacket.h"
#include "Inertial/InertialDataField.h"
#include "DataBuffer.h"
#include "ResponseCollector.h"

namespace mscl
{
    ResponsePattern::ResponsePattern():
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
            assert(false);
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

    bool ResponsePattern::match(DataBuffer& data)
    {
        return false;
    }

    bool ResponsePattern::match(const WirelessPacket& packet)
    {
        return false;
    }

    bool ResponsePattern::match(const InertialDataField& field)
    {
        return false;
    }

    bool ResponsePattern::fullyMatched() const
    {
        return m_fullyMatched;
    }

    bool ResponsePattern::success() const
    {
        return m_success;
    }
}