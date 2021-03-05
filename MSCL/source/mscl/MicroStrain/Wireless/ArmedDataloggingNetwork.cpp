/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "ArmedDataloggingNetwork.h"

#include "WirelessNode.h"
#include "WirelessTypes.h"
#include "Configuration/NodeEepromHelper.h"

namespace mscl
{
    ArmedDataloggingNetwork::ArmedDataloggingNetwork(const BaseStation& networkBaseStation) :
        m_networkBase(networkBaseStation)
    {
    }

    void ArmedDataloggingNetwork::addNode(const WirelessNode& node, const std::string& message)
    {
        try
        {
            //verify that the node's basestation is the same as the network basestation
            if(!node.hasBaseStation(m_networkBase))
            {
                throw Error("The Node's parent BaseStation is different than the network's master BaseStation.");
            }

            //verify that the sampling mode is Armed Datalogging
            if(node.eepromHelper().read_samplingMode() != WirelessTypes::samplingMode_armedDatalog)
            {
                //nodes being added to the network must have their configuration be in Armed Datalogging mode.
                ConfigIssues issues;
                issues.push_back(ConfigIssue(ConfigIssue::CONFIG_SAMPLING_MODE, "Configuration is not set for Armed Datalogging mode."));
                throw Error_InvalidNodeConfig(issues, node.nodeAddress());
            }

            //attempt to insert the node into the map. If it already exists, just silently fail.
            m_nodes.insert(std::pair<NodeAddress, std::string>(node.nodeAddress(), message));
        }
        catch(...)
        {
            //forward the same exception
            throw;
        }
    }

    void ArmedDataloggingNetwork::removeNode(NodeAddress nodeAddress)
    {
        //remove the node from the map
        m_nodes.erase(nodeAddress);
    }

    void ArmedDataloggingNetwork::startSampling()
    {
        //attempt to arm all the nodes in the network
        armNodes();

        //trigger all of the armed nodes at the same time
        triggerArmedNodes();
    }

    void ArmedDataloggingNetwork::armNodes()
    {
        //for every node in the network
        for(auto nodeItr : m_nodes)
        {
            //arm each node individually
            if(!m_networkBase.node_armForDatalogging(nodeItr.first, nodeItr.second))
            {
                //if the command has failed, throw an exception
                throw Error_NodeCommunication(nodeItr.first, "Failed to arm the node for Armed Datalogging.");
            }
        }
    }

    void ArmedDataloggingNetwork::triggerArmedNodes()
    {
        //send a broadcast start command. All armed nodes in the network will start datalogging.
        m_networkBase.node_triggerArmedDatalogging(BaseStation::BROADCAST_NODE_ADDRESS);
    }
}