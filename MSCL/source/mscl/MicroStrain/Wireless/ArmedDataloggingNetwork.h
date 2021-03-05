/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "BaseStation.h"
#include <map>

namespace mscl
{
    class WirelessNode;    //forward declarations

    //API Class: ArmedDataloggingNetwork
    //    Used to setup and start an Armed Datalogging network of wireless nodes.
    class ArmedDataloggingNetwork
    {
    private:
        ArmedDataloggingNetwork(const ArmedDataloggingNetwork&);            //copy constructor disabled
        ArmedDataloggingNetwork& operator=(const ArmedDataloggingNetwork&);    //assignment operator disabled

    public:
        //API Constructor: ArmedDataloggingNetwork
        //    Creates an ArmedDataloggingNetwork object used to setup and start an Armed Datalogging network.
        //
        //Parameters:
        //    networkBaseStation - The master <BaseStation> for this network. All <WirelessNode>s that are added must have this as their parent <BaseStation>.
        ArmedDataloggingNetwork(const BaseStation& networkBaseStation);

    private:
        //Variable: m_networkBase
        //    The <BaseStation> that will act as the parent base station for this network.
        BaseStation m_networkBase;

        //Variable: m_nodes
        //    A map of node addresses to messages to be set for datalogging. This serves as the list of nodes in the network.
        std::map<NodeAddress, std::string> m_nodes;

    public:
        //API Function: addNode
        //    Adds a <WirelessNode> to the Armed Datalogging network. If the Node already exists in the network, it will not be added.
        //    The Node's parent <BaseStation> should be the same as the network's master <BaseStation>.
        //    The Node should have its sampling configuration set to Armed Datalogging mode prior to adding to be successfully added.
        //
        //Parameters:
        //    node - The <WirelessNode> to add to the network.
        //    message - A message to be set with the <WirelessNode>. This message can be retrieved when downloading the data from the Node. Will be trimmed to 50 chars if longer. (Default of "")
        //
        //Exceptions:
        //    - <Error>: The Node's parent <BaseStation> is different than the network's master <BaseStation>.
        //    - <Error_InvalidNodeConfig>: The configuration is not set for Armed Datalogging mode.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        void addNode(const WirelessNode& node, const std::string& message = "");

        //API Function: removeNode
        //    Removes a <WirelessNode> from the Armed Datalogging network, if it exists in the network.
        //
        //Parameters:
        //    nodeAddress - The node address of the <WirelessNode> to be removed.
        void removeNode(NodeAddress nodeAddress);

        //API Function: startSampling
        //    Starts the network sampling by individually arming each Node and then broadcasting the trigger to all Nodes that are armed.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to start a Node Synchronized Sampling.
        //    - <Error_Connection>: A connection error has occurred.
        void startSampling();

    private:
        //Function: armNodes
        //    Sends the ArmForDatalogging command to each Node in the network.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to send the ArmForDatalogging command to a Node.
        //    - <Error_Connection>: A connection error has occurred.
        void armNodes();

        //Function: triggerArmedNodes
        //    Sends a broadcast trigger to start all Nodes that are currently armed.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred.
        void triggerArmedNodes();
    };
}