/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/Timestamp.h"
#include "mscl/Types.h"
#include <map>

namespace mscl
{
    //Class: NodeCommTimes
    //  Contains a global map of Wireless Node addresses to last communication times.
    class NodeCommTimes
    {
    private:
        NodeCommTimes() {};

    public:
        NodeCommTimes(const NodeCommTimes&)             = delete;
        NodeCommTimes& operator=(const NodeCommTimes&)  = delete;

    private:
        //Variable: m_nodesLastCommTime
        //  A map of node address to <Timestamp> objects, holding the last communication time for nodes.
        static std::map<NodeAddress, Timestamp> m_nodesLastCommTime;

        //Variable: m_nodesLastState
        //  A mpa of node address to <DeviceState> objects, holding the last known state for nodes.
        static std::map<NodeAddress, DeviceState> m_nodesLastState;

    public:
        //Function: updateCommTime
        //  Sets the communication time for the given node address to the current system time.
        //
        //Parameters:
        //  nodeAddress - The node address to update the last communication time for.
        static void updateCommTime(NodeAddress nodeAddress);

        //Function: updateDeviceState
        //  Sets the <DeviceState> for the given node address.
        //
        //Parameters:
        //  nodeAddress - The node address to update
        //  state - The <DeviceState> to set.
        static void updateDeviceState(NodeAddress nodeAddress, DeviceState state);

        //Function: getLastCommTime
        //  Gets the last communication time for the given node address.
        //
        //Parameters:
        //  nodeAddress - The node address to get the last communication time for.
        //
        //Exceptions:
        //  - <Error_NoData>: There is no communication time logged for the given node address.
        static const Timestamp& getLastCommTime(NodeAddress nodeAddress);

        //Function: getLastDeviceState
        //  Gets the last device state for the given node address.
        //
        //Parameters:
        //  nodeAddress - The node address to get the last device state for.
        //
        //Returns:
        //  The <DeviceState> of the node address.
        static DeviceState getLastDeviceState(NodeAddress nodeAddress);
    };
}