/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "NodeCommTimes.h"

namespace mscl
{
    std::map<uint32, Timestamp> NodeCommTimes::m_nodesLastCommTime;

    void NodeCommTimes::updateCommTime(uint32 nodeAddress)
    {
        m_nodesLastCommTime[nodeAddress].setTimeNow();
    }

    const Timestamp& NodeCommTimes::getLastCommTime(uint32 nodeAddress)
    {
        try
        {
            return m_nodesLastCommTime.at(nodeAddress);
        }
        catch(std::out_of_range&)
        {
            throw Error_NoData("The Node has not yet been communicated with.");
        }
    }
}