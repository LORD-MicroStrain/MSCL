/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/NodeCommTimes.h"

namespace mscl
{
    std::map<NodeAddress, Timestamp> NodeCommTimes::m_nodesLastCommTime;
    std::map<NodeAddress, DeviceState> NodeCommTimes::m_nodesLastState;

    void NodeCommTimes::updateCommTime(NodeAddress nodeAddress)
    {
        m_nodesLastCommTime[nodeAddress].setTimeNow();
    }

    void NodeCommTimes::updateDeviceState(NodeAddress nodeAddress, DeviceState state)
    {
        m_nodesLastState[nodeAddress] = state;
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

    DeviceState NodeCommTimes::getLastDeviceState(NodeAddress nodeAddress)
    {
        try
        {
            return m_nodesLastState.at(nodeAddress);
        }
        catch(const std::out_of_range&)
        {
            return deviceState_unknown;
        }
    }
} // namespace mscl
