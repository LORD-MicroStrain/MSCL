/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/Timestamp.h"
#include "WirelessTypes.h"
#include "BaseStation.h"
#include "SyncNetworkInfo.h"
#include <map>

namespace mscl
{
    class WirelessNode;

    //API Class: SyncSamplingNetwork
    //    Used to configure and start a Synchronized Sampling network of wireless nodes.
    class SyncSamplingNetwork
    {
    public:
        SyncSamplingNetwork() = delete;                                         //default constructor disabled
        SyncSamplingNetwork(const SyncSamplingNetwork&) = delete;               //copy constructor disabled
        SyncSamplingNetwork& operator=(const SyncSamplingNetwork&) = delete;    //assignment operator disabled

    public:
        //API Constructor: SyncSamplingNetwork
        //    Creates a SyncSamplingNetwork object used to configure and start a Synchronized Sampling network.
        //
        //Parameters:
        //    networkBaseStation - The master <BaseStation> that will be the parent base station for this network, performing all the communication with the Nodes.
        //
        //Exceptions:
        //    - <Error_Communication>: Failed to communicate with the parent BaseStation to retrieve network information.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        explicit SyncSamplingNetwork(const BaseStation& networkBaseStation);

    private:
        //Variable: m_networkBase
        //    The <BaseStation> that will act as the parent base station for this network, performing all the communication with the Nodes.
        BaseStation m_networkBase;

        //Variable: m_nodes
        //    A map of node addresses to <SyncNetworkInfo>s containing all the nodes that were added to the network.
        std::map<NodeAddress, std::unique_ptr<SyncNetworkInfo> > m_nodes;

        //Variable: m_allNodes
        //    A vector of node addresses for every node in the network.
        std::vector<NodeAddress> m_allNodes;

        //Variable: m_eventNodes
        //  A vector of node addresses for every node in Event-Driven mode.
        std::vector<NodeAddress> m_eventNodes;

        //Variable: m_nonEventNodes
        //  A vector of node addresses for every node Not in Event-Driven mode.
        std::vector<NodeAddress> m_nonEventNodes;

        //Variable: m_slots
        //    A vector of bools representing all of the transmission slots. If a slot is set (true), it it taken. If a slot is unset (false), it is available.
        std::vector<bool> m_slots;

        //Variable: m_lossless
        //    Whether the lossless option is enabled or not.
        bool m_lossless;

        //Variable: m_commProtocol
        //  The <WirelessTypes::CommProtocol> that the network is using (based off of the master BaseStation's comm protocol when this network was created).
        WirelessTypes::CommProtocol m_commProtocol;

        //Variable: m_percentBandwidth
        //    The percent of bandwidth for the entire Sync Sampling Network. 
        //    This includes nodes that could not find TDMA slots, but does not include nodes who failed to communicate.
        float m_percentBandwidth;
        
        //Variable: m_networkOk
        //    Whether the Sync Sampling Network is OK (true) or has problems (false).
        bool m_networkOk;

        //Variable: m_configApplied
        //    Whether the calculated network configuration values have been applied to all of the nodes in the network.
        bool m_configApplied;

        //Variable: m_disabledBeacon
        //    Whether the beacon has already been disabled or not by this object.
        bool m_disabledBeacon;

        //Variable: m_availableSlotCount
        //    The number of remaining available slots.
        uint16 m_availableSlotCount;

    public:
        //API Function: addNode
        //    Adds a <WirelessNode> to the Sync Sampling network. If the Node already exists in the network, it will not be added.
        //    The Node's parent <BaseStation> should be the same as the network's master <BaseStation>.
        //    The Node should have its sampling configuration set to a Synchronized Sampling mode prior to adding to be successfully added.
        //
        //Parameters:
        //    node - The <WirelessNode> to add to the network.
        //
        //Exceptions:
        //    - <Error>: The Node's parent <BaseStation> is different than the network's master <BaseStation>.
        //    - <Error_InvalidNodeConfig>: The configuration is not set for Synchronized Sampling mode.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        //    - <Error_UnknownSampleRate>: The sample rate value read from the Node is not a valid SampleRate.
        void addNode(WirelessNode& node);

        //API Function: addNode
        //    Adds a <WirelessNode> to the Sync Sampling network. If the Node already exists in the network, it will not be added.
        //    The Node's parent <BaseStation> should be the same as the network's master <BaseStation>.
        //    The Node should have its sampling configuration set to a Synchronized Sampling mode prior to adding to be successfully added.
        //
        //Parameters:
        //    node - The <WirelessNode> to add to the network.
        //    pendingConfig - A pending <WirelessNodeConfig> to set for the node. This will be used in all network calculations.
        //
        //Exceptions:
        //    - <Error>: The Node's parent <BaseStation> is different than the network's master <BaseStation>.
        //    - <Error_InvalidNodeConfig>: The configuration is not set for Synchronized Sampling mode.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        //    - <Error_UnknownSampleRate>: The sample rate value read from the Node is not a valid SampleRate.
        void addNode(WirelessNode& node, const WirelessNodeConfig& pendingConfig);

        //API Function: removeNode
        //    Removes a <WirelessNode> from the Sync Sampling network, if it exists in the network.
        //
        //Parameters:
        //    nodeAddress - The node address of the <WirelessNode> to be removed.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to communicate with a Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        void removeNode(NodeAddress nodeAddress);

        //API Function: percentBandwidth
        //    Gets the total percent bandwidth for the Sync Sampling Network.
        //    This includes nodes that could not find TDMA slots, but does not include nodes who failed to communicate (status of <status_PoorCommunication>).
        //
        //Returns:
        //    The percent of bandwidth for the entire Sync Sampling Network.
        float percentBandwidth() const;

        //API Function: ok
        //    Gets whether the Sync Sampling Network is OK (true), or has problems such as exceeding bandwidth (false).
        //
        //Returns:
        //    true if the network is OK (all nodes fit in the network, no communication issues, etc.), false if the network has a problem.
        bool ok() const;

        //API Function: refresh
        //    Refreshes the Sync Sampling Network. 
        //    This function must be called when any WirelessNode has changed its configuration after being added to the network!
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to communicate with a Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        //    - <Error_UnknownSampleRate>: The sample rate value read from a Node is not a valid SampleRate.
        void refresh();

        //API Function: lossless
        //    Gets whether the lossless option is enabled or not for the entire network (default of enabled).
        //    The lossless feature enables buffering and retransmissions in order to provide 100% packet success rate under most operating conditions.
        //    This does, however, have a possible increase in latency, especially in poor RF environments.
        //    
        //Returns:
        //    true if the lossless option is enabled, false if it is disabled.
        bool lossless() const;

        //API Function: lossless
        //    Enables or Disables the lossless option for the entire network. If changed, <refresh> will be called.
        //    The lossless feature enables buffering and retransmissions in order to provide 100% packet success rate under most operating conditions.
        //    This can, however, cause a possible increase in latency, especially in poor RF environments.
        //
        //Parameters:
        //    enable - Whether the lossless option should be enabled (true) or disabled (false).
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to communicate with a Node.
        //    - <Error_Connection>: A connection error has occurred a BaseStation.
        //    - <Error_UnknownSampleRate>: The sample rate value read from a Node is not a valid SampleRate.
        void lossless(bool enable);

        //API Function: communicationProtocol
        //  Gets the <WirelessTypes::CommProtocol> that is set for the network.
        //  This setting initially gets loaded from the protocol that the BaseStation is configured for when the network is first created.
        //
        //Returns:
        //  The <WirelessTypes::CommProtocol> that is set for the network.
        WirelessTypes::CommProtocol communicationProtocol() const;

        //API Function: communicationProtocol
        //  Sets the <WirelessTypes::CommProtocol> for the network.
        //  The initial communicationProtocol is set to whichever mode the BaseStation was configured for when the network was first created.
        //  Changing this setting will call <refresh> and the network calculations (such as percentBandwidth) will be updated.
        //  Note: Changing this does not actually change the protocol of the BaseStation or Nodes in the network. All devices must be changed to the same
        //        <WirelessTypes::CommProtocol> that the network is set to before <applyConfiguration> is called, or else an exception will be thrown.
        //
        //Parameters:
        //  protocol - The <WirelessTypes::CommProtocol> to use for network calculations.
        //
        //Exceptions:
        //  - <Error_NodeCommunication>: Failed to communicate with a Node.
        //  - <Error_Connection>: A connection error has occurred a BaseStation.
        //  - <Error_UnknownSampleRate>: The sample rate value read from a Node is not a valid SampleRate.
        void communicationProtocol(WirelessTypes::CommProtocol protocol);

        //API Function: applyConfiguration
        //    Applies the Sync Sampling network settings to all of the nodes in the network.
        //    This action is required before starting a Sync Sampling network. The network status must be OK before this can be called.
        //    Calling this function repeatedly will only affect the node's that haven't had their configuration applied successfully. This can be useful if some nodes successfully apply, while others fail to communicate.
        //    Note: This will clear any "pending" configurations that any nodes have in the network.
        //          You must manually apply those configuration templates to the nodes if you want them to actually be applied to the devices.
        //
        //Exceptions:
        //    - <Error>: The network status is not OK. Configuration cannot be applied.
        //    - <Error_NodeCommunication>: Failed to communicate with a Node.
        //    - <Error_Connection>: A connection error has occurred with a BaseStation.
        void applyConfiguration();

        //API Function: startSampling
        //    Starts the network sampling by sending the start command to each node, and then starting the beacon on the master basestation with the current system time.
        //    <applyConfiguration> must be called before this function is called.
        //    Calling this function repeatedly will only start the node's that haven't been started already. This can be useful if some nodes successfully start, while others fail to communicate. The beacon will not be started until all nodes have started.
        //
        //Exceptions:
        //    - <Error>: The network configuration has not been applied. Cannot start sampling.
        //    - <Error_Communication>: The disable/enable beacon command has failed. The beacon has not been started.
        //    - <Error_Connection>: A connection error has occurred.
        void startSampling();

        //API Function: startSampling
        //    Starts the network sampling by sending the start command to each node, and then starting the beacon on the master basestation with the given <Timestamp>.
        //    <applyConfiguration> must be called before this function is called.
        //    Calling this function repeatedly will only start the node's that haven't been started already. This can be useful if some nodes successfully start, while others fail to communicate. The beacon will not be started until all nodes have started.
        //
        //Parameters:
        //    startTime - The <Timestamp> to enable the beacon with, which ultimately determines the times for the nodes in the network.
        //
        //Exceptions:
        //    - <Error>: The network configuration has not been applied. Cannot start sampling.
        //    - <Error_Communication>: The disable/enable beacon command has failed. The beacon has not been started.
        //    - <Error_Connection>: A connection error has occurred.
        void startSampling(Timestamp startTime);

        //API Function: startSampling_noBeacon
        //    Sends the start command to each node in the network. The beacon is not started. Note: The nodes will not actually start sampling until they hear a beacon.
        //    <applyConfiguration> must be called before this function is called.
        //    Calling this function repeatedly will only start the node's that haven't been started already. This can be useful if some nodes successfully start, while others fail to communicate.
        //
        //Exceptions:
        //    - <Error>: The network configuration has not been applied. Cannot start sampling.
        //    - <Error_Connection>: A connection error has occurred.
        void startSampling_noBeacon();

        //API Function: getNodeNetworkInfo
        //    Gets the <SyncNetworkInfo> object containing network information on the specified <WirelessNode> within the Sync Sampling network.
        //
        //Parameters:
        //    nodeAddress - The node address of the <WirelessNode> to find the network info of. This node must already be in the network.
        //
        //Returns:
        //    A constant reference to the <SyncNetworkInfo> containing the networking information for the specified node in the network.
        //
        //Exceptions:
        //    - <Error>: The node address was not found in the map.
        SyncNetworkInfo& getNodeNetworkInfo(NodeAddress nodeAddress);

    private:
        //Function: addNodeToNetwork
        //    Adds a <WirelessNode> to the Sync Sampling network, with or without a given pending <WirelessNodeConfig>. 
        //    If the Node already exists in the network, it will not be added.
        //    The Node's parent <BaseStation> should be the same as the network's master <BaseStation>.
        //    The Node should have its sampling configuration, or the provided pending configuration, set to a Synchronized Sampling mode prior to adding to be successfully added.
        //
        //Parameters:
        //    node - The <WirelessNode> to add to the network.
        //    pendingConfig - The <WirelessNodeConfig> to add to the network (default of null).
        //
        //Exceptions:
        //    - <Error>: The Node's parent <BaseStation> is different than the network's master <BaseStation>.
        //    - <Error_InvalidNodeConfig>: The configuration is not set for Synchronized Sampling mode.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        //    - <Error_UnknownSampleRate>: The sample rate value read from the Node is not a valid SampleRate.
        void addNodeToNetwork(WirelessNode& node, const WirelessNodeConfig* pendingConfig = nullptr);

        //Function: calculateNetworkValues
        //    Calculates the network values for a single node, such as transmissions per group and group size.
        //    This reads values that are stored on the node to use in the calculations.
        //
        //Parameters:
        //    nodeAddress - The <NodeAddress> of the Node to calculate the values for.
        //    optimizeBandwidth - Whether we are attempting to optimize bandwidth or not
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred.
        //    - <Error_UnknownSampleRate>: The sample rate value read from the node is not a valid SampleRate.
        void calculateNetworkValues(NodeAddress nodeAddress, bool optimizeBandwidth);

        void divvyUpEventTransmissions();

        double totalEventTxPerGroup();

        //Function: updateNetworkStatus
        //    Updates the status of each Node and calculates the total percent of bandwidth
        void updateNetworkStatus();

        //Function: sortByBandwidth
        //    Sorts the vector of nodes by the percent of bandwidth (and by node address is bandwidth is the same).
        //
        //Parameters:
        //  container - The container of node addresses to sort by bandwidth.
        //              Each node in this container needs to have already had its percent bandwidth calculated.
        void sortByBandwidth( std::vector<NodeAddress>& container );

        //Function: sortingFunction
        //    The function used as a predicate to sort the networkorder container by bandwidth
        //
        //Parameters:
        //    address1 - The first address
        //    address2 - The second address
        //
        //Returns:
        //    true if the first address should go first, false if the second address should go first
        bool sortingFunction(NodeAddress address1, NodeAddress address2);

        //Function: findSlotsForNodes
        //    Finds TDMA slots for every Node in the given vector of nodes. 
        //    Note that this clears m_slots before finding new slots for all of the Nodes.
        //
        //Parameters:
        //  container - The container of node addresses to find slots for, sorted in order of priority.
        //
        //Returns:
        //    true if a slot was found for every node in the network, false if any of the nodes failed to find a slot.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to communicate with a Node.
        //    - <Error_Connection>: A connection error has occurred.
        bool findSlotsForNodes(const std::vector<NodeAddress>& nodes);

        //Function: getTdmaSlot
        //    Finds a TDMA slot for a single Node.
        //
        //Parameters:
        //    nodeAddress - The <NodeAddress> of the <WirelessNode> to find the TDMA slot for.
        //
        //Returns:
        //    true if a TDMA slot was found for the Node, false otherwise.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred.
        bool getTdmaSlot(NodeAddress nodeAddress);

        //Function: optimizeBandwidth
        //    Tries to optimize the bandwidth to give lossless nodes more time to transmit. 
        //    Nodes may be given different slots and the network order rearranged.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to communicate with a Node.
        //    - <Error_Connection>: A connection error has occurred.
        void optimizeBandwidth();

        //Function: findSamplingDelay
        //    Calculates the sampling delay for a node in the network.
        //
        //Parameters:
        //    nodeAddress- The <NodeAddress> of the <WirelessNode> to find the sampling delay for.
        //
        //Returns:
        //    The sampling delay to use for the given Node.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with a Node's parent BaseStation.
        uint32 findSamplingDelay(NodeAddress nodeAddress);

        //Function: sendStartToAllNodes
        //    Sends the start sync sampling command to all nodes in the network.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred.
        void sendStartToAllNodes();

        //Function: inLegacyMode
        //  Gets whether the network is in legacy mode (has at least 1 sync v1 node) or not.
        //
        //Returns:
        //  true if in legacy mode, false otherwise.
        bool inLegacyMode();
    };
}