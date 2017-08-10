/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

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
        //  A map of node address to <Timestamp> objects, holding the last communication time for nodes with this BaseStation.
        static std::map<NodeAddress, Timestamp> m_nodesLastCommTime;

    public:
        //Function: updateCommTime
        //  Sets the communication time for the given node address to the current system time.
        //
        //Parameters:
        //  nodeAddress - The node address to update the last communication time for.
        static void updateCommTime(NodeAddress nodeAddress);

        //Function: getLastCommTime
        //  Gets the last communication time for the given node address.
        //
        //Parameters:
        //  nodeAddress - The node address to get the last communication time for.
        //
        //Exceptions:
        //  - <Error_NoData>: There is no communication time logged for the given node address.
        static const Timestamp& getLastCommTime(NodeAddress nodeAddress);
    };
}