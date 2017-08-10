/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "NodeCommTimes.h"

namespace mscl
{
    std::map<NodeAddress, Timestamp> NodeCommTimes::m_nodesLastCommTime;

    void NodeCommTimes::updateCommTime(NodeAddress nodeAddress)
    {
        m_nodesLastCommTime[nodeAddress].setTimeNow();
    }

    const Timestamp& NodeCommTimes::getLastCommTime(NodeAddress nodeAddress)
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