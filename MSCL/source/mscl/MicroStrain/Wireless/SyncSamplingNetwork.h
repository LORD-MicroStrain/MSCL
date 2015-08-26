/*****************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the included
LICENSE.txt file for a copy of the full GNU General Public License.
*****************************************************************************/
//PUBLIC_HEADER
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
	//	Used to configure and start a Synchronized Sampling network of wireless nodes.
	class SyncSamplingNetwork
	{
	private:
		SyncSamplingNetwork();										//default constructor disabled
		SyncSamplingNetwork(const SyncSamplingNetwork&);			//copy constructor disabled
		SyncSamplingNetwork& operator=(const SyncSamplingNetwork&);	//assignment operator disabled

	public:
		//API Constructor: SyncSamplingNetwork
		//	Creates a SyncSamplingNetwork object used to configure and start a Synchronized Sampling network.
		//
		//Parameters:
		//	networkBaseStation - The master <BaseStation> that will be the parent base station for this network, performing all the communication with the Nodes.
		explicit SyncSamplingNetwork(const BaseStation& networkBaseStation);

	private:
		//Variable: m_networkBase
		//	The <BaseStation> that will act as the parent base station for this network, performing all the communication with the Nodes.
		BaseStation m_networkBase;

		//Variable: m_nodes
		//	A map of node addresses to <SyncNetworkInfo>s containing all the nodes that were added to the network.
		std::map<uint16, std::unique_ptr<SyncNetworkInfo> > m_nodes;

		//Variable: m_networkOrder
		//	A vector of node addresses that will be sorted to hold the order of how the nodes should be structured in the network.
		std::vector<NodeAddress> m_networkOrder;

		//Variable: m_slots
		//	A vector of bools representing all of the transmission slots. If a slot is set (true), it it taken. If a slot is unset (false), it is available.
		std::vector<bool> m_slots;

		//Variable: m_lossless
		//	Whether the lossless option is enabled or not.
		bool m_lossless;

		//Variable: m_highCapacity
		//	Whether the high capacity option is enabled or not.
		bool m_highCapacity;

		//Variable: m_percentBandwidth
		//	The percent of bandwidth for the entire Sync Sampling Network. 
		//	This includes nodes that could not find TDMA slots, but does not include nodes who failed to communicate.
		float m_percentBandwidth;
		
		//Variable: m_networkOk
		//	Whether the Sync Sampling Network is OK (true) or has problems (false).
		bool m_networkOk;

		//Variable: m_configApplied
		//	Whether the calculated network configuration values have been applied to all of the nodes in the network.
		bool m_configApplied;

	public:
		//API Function: addNode
		//	Adds a <WirelessNode> to the Sync Sampling network. If the Node already exists in the network, it will not be added.
		//	The Node's parent <BaseStation> should be the same as the network's master <BaseStation>.
		//	The Node should have its sampling configuration set to a Synchronized Sampling mode prior to adding to be successfully added.
		//
		//Parameters:
		//	node - The <WirelessNode> to add to the network.
		//
		//Exceptions:
		//	- <Error>: The Node's parent <BaseStation> is different than the network's master <BaseStation>.
		//	- <Error_InvalidNodeConfig>: The configuration is not set for Synchronized Sampling mode.
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		//	- <Error_UnknownSampleRate>: The sample rate value read from the Node is not a valid SampleRate.
		void addNode(WirelessNode& node);

		//API Function: addNode
		//	Adds a <WirelessNode> to the Sync Sampling network. If the Node already exists in the network, it will not be added.
		//	The Node's parent <BaseStation> should be the same as the network's master <BaseStation>.
		//	The Node should have its sampling configuration set to a Synchronized Sampling mode prior to adding to be successfully added.
		//
		//Parameters:
		//	node - The <WirelessNode> to add to the network.
		//	pendingConfig - A pending <WirelessNodeConfig> to set for the node. This will be used in all network calculations.
		//
		//Exceptions:
		//	- <Error>: The Node's parent <BaseStation> is different than the network's master <BaseStation>.
		//	- <Error_InvalidNodeConfig>: The configuration is not set for Synchronized Sampling mode.
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		//	- <Error_UnknownSampleRate>: The sample rate value read from the Node is not a valid SampleRate.
		void addNode(WirelessNode& node, const WirelessNodeConfig& pendingConfig);

		//API Function: removeNode
		//	Removes a <WirelessNode> from the Sync Sampling network, if it exists in the network.
		//
		//Parameters:
		//	nodeAddress - The node address of the <WirelessNode> to be removed.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to communicate with a Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void removeNode(NodeAddress nodeAddress);

		//API Function: percentBandwidth
		//	Gets the total percent bandwidth for the Sync Sampling Network.
		//	This includes nodes that could not find TDMA slots, but does not include nodes who failed to communicate (status of <status_PoorCommunication>).
		//
		//Returns:
		//	The percent of bandwidth for the entire Sync Sampling Network.
		float percentBandwidth() const;

		//API Function: ok
		//	Gets whether the Sync Sampling Network is OK (true), or has problems such as exceeding bandwidth (false).
		//
		//Returns:
		//	true if the network is OK (all nodes fit in the network, no communication issues, etc.), false if the network has a problem.
		bool ok() const;

		//API Function: refresh
		//	Refreshes the Sync Sampling Network. 
		//	This function must be called when any WirelessNode has changed its configuration after being added to the network!
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to communicate with a Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		//	- <Error_UnknownSampleRate>: The sample rate value read from a Node is not a valid SampleRate.
		void refresh();

		//API Function: lossless
		//	Gets whether the lossless option is enabled or not for the entire network (default of enabled).
		//	The lossless feature enables buffering and retransmissions in order to provide 100% packet success rate under most operating conditions.
		//	This does, however, have a possible increase in latency, especially in poor RF environments.
		//	
		//Returns:
		//	true if the lossless option is enabled, false if it is disabled.
		bool lossless() const;

		//API Function: lossless
		//	Enables or Disables the lossless option for the entire network. If changed, <refresh> will be called.
		//	The lossless feature enables buffering and retransmissions in order to provide 100% packet success rate under most operating conditions.
		//	This can, however, cause a possible increase in latency, especially in poor RF environments.
		//
		//Parameters:
		//	enable - Whether the lossless option should be enabled (true) or disabled (false).
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to communicate with a Node.
		//	- <Error_Connection>: A connection error has occurred a BaseStation.
		//	- <Error_UnknownSampleRate>: The sample rate value read from a Node is not a valid SampleRate.
		void lossless(bool enable);

		//API Function: highCapacity
		//	Gets whether the high capacity option is enabled or not for the entire network (default of false).
		//	The high capacity feature reduces transmit rates in order to optimize bandwidth and power savings among nodes with slower sample rates.
		//	This can, however, increase the transmit interval from 1 second to (1 to 16) seconds.
		//
		//Returns:
		//	true if the high capacity option is enabled, false if it is disabled.
		bool highCapacity() const;

		//API Function: highCapacity
		//	Enables or Disables the high capacity option for the entire network. If changed, <refresh> will be called.
		//	The high capacity feature reduces transmit rates in order to optimize bandwidth and power savings among nodes with slower sample rates.
		//	This can, however, increase the transmit interval from 1 second to (1 to 16) seconds.
		//
		//Parameters:
		//	enable - Whether the high capacity option should be enabled (true) or disabled (false).
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to communicate with a Node.
		//	- <Error_Connection>: A connection error has occurred with a BaseStation.
		//	- <Error_UnknownSampleRate>: The sample rate value read from a Node is not a valid SampleRate.
		void highCapacity(bool enable);

		//API Function: applyConfiguration
		//	Applies the Sync Sampling network settings to all of the nodes in the network.
		//	This action is required before starting a Sync Sampling network. The network status must be OK before this can be called.
		//	Calling this function repeatedly will only affect the node's that haven't had their configuration applied successfully. This can be useful if some nodes successfully apply, while others fail to communicate.
		//	Note: This will clear any "pending" configurations that any nodes have in the network.
		//		  You must manually apply those configuration templates to the nodes if you want them to actually be applied to the devices.
		//
		//Exceptions:
		//	- <Error>: The network status is not OK. Configuration cannot be applied.
		//	- <Error_NodeCommunication>: Failed to communicate with a Node.
		//	- <Error_Connection>: A connection error has occurred with a BaseStation.
		void applyConfiguration();

		//API Function: startSampling
		//	Starts the network sampling by sending the start command to each node, and then starting the beacon on the master basestation with the current system time.
		//	<applyConfiguration> must be called before this function is called.
		//	Calling this function repeatedly will only start the node's that haven't been started already. This can be useful if some nodes successfully start, while others fail to communicate. The beacon will not be started until all nodes have started.
		//
		//Exceptions:
		//	- <Error>: The network configuration has not been applied. Cannot start sampling.
		//			  The enable beacon command has failed. The beacon has not been started.
		//	- <Error_NodeCommunication>: Failed to start a Node Synchronized Sampling.
		//	- <Error_Connection>: A connection error has occurred.
		void startSampling();

		//API Function: startSampling
		//	Starts the network sampling by sending the start command to each node, and then starting the beacon on the master basestation with the given <Timestamp>.
		//	<applyConfiguration> must be called before this function is called.
		//	Calling this function repeatedly will only start the node's that haven't been started already. This can be useful if some nodes successfully start, while others fail to communicate. The beacon will not be started until all nodes have started.
		//
		//Parameters:
		//	startTime - The <Timestamp> to enable the beacon with, which ultimately determines the times for the nodes in the network.
		//
		//Exceptions:
		//	- <Error>: The network configuration has not been applied. Cannot start sampling.
		//			  The enable beacon command has failed. The beacon has not been started.
		//	- <Error_NodeCommunication>: Failed to start a Node Synchronized Sampling.
		//	- <Error_Connection>: A connection error has occurred.
		void startSampling(Timestamp startTime);

		//API Function: startSampling_noBeacon
		//	Sends the start command to each node in the network. The beacon is not started. Note: The nodes will not actually start sampling until they hear a beacon.
		//	<applyConfiguration> must be called before this function is called.
		//	Calling this function repeatedly will only start the node's that haven't been started already. This can be useful if some nodes successfully start, while others fail to communicate.
		//
		//Exceptions:
		//	- <Error>: The network configuration has not been applied. Cannot start sampling.
		//			  The enable beacon command has failed. The beacon has not been started.
		//	- <Error_NodeCommunication>: Failed to start a Node Synchronized Sampling.
		//	- <Error_Connection>: A connection error has occurred.
		void startSampling_noBeacon();

		//API Function: getNodeNetworkInfo
		//	Gets the <SyncNetworkInfo> object containing network information on the specified <WirelessNode> within the Sync Sampling network.
		//
		//Parameters:
		//	nodeAddress - The node address of the <WirelessNode> to find the network info of. This node must already be in the network.
		//
		//Returns:
		//	A constant reference to the <SyncNetworkInfo> containing the networking information for the specified node in the network.
		//
		//Exceptions:
		//	- <Error>: The node address was not found in the map.
		SyncNetworkInfo& getNodeNetworkInfo(uint16 nodeAddress);

		//API Function: setPendingConfig
		//	Sets a pending configuration for a specific <WirelessNode> in the network.
		//	This is a configuration that is not actually applied to the Node, but
		//	used in all network calculations. In this way, you may see how some configuration
		//	changes affect the network bandwidth before applying the configuration.
		//	This function automatically calls <refresh> on the network.
		//
		//Parameters:
		//	nodeAddress - The node address of the <WirelessNode> to set the pending config for.
		//	config - The <WirelessNodeConfig> to set for the Node.
		//
		//Exceptions:
		//	- <Error>: The node address was not found in the network. The configuration has not been set.
		//	- <Error_InvalidNodeConfig>: The configuration is not set for Synchronized Sampling mode.
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void setPendingConfig(uint16 nodeAddress, const WirelessNodeConfig& config);

		//API Function: clearPendingConfig
		//	Clears a pending config that is currently set for a specific <WirelessNode> in the network.
		//	By clearing the pending config, the network will recalculate using the configuration
		//	that is currently set on the Wireless Node.
		//	This function automatically calls <refresh> on the network.
		//
		//Parameters:
		//	nodeAddress - The node address of the <WirelessNode> to set the pending config for.
		//
		//Exceptions:
		//	- <Error>: The node address was not found in the network. No changes have been made.
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void clearPendingConfig(uint16 nodeAddress);

		//API Function: clearAllPendingConfigs
		//	Clears all pending configurations that are currently set in the network.
		//	By clearing the pending configs, the network will recalculate using the
		//	configurations currently set on the Wireless Nodes.
		//	This function automatically calls <refresh> on the network if any pending configurations were cleared.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to communicate with a Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void clearAllPendingConfigs();

	private:
		//API Function: addNodeToNetwork
		//	Adds a <WirelessNode> to the Sync Sampling network, with or without a given pending <WirelessNodeConfig>. 
		//	If the Node already exists in the network, it will not be added.
		//	The Node's parent <BaseStation> should be the same as the network's master <BaseStation>.
		//	The Node should have its sampling configuration, or the provided pending configuration, set to a Synchronized Sampling mode prior to adding to be successfully added.
		//
		//Parameters:
		//	node - The <WirelessNode> to add to the network.
		//	pendingConfig - The <WirelessNodeConfig> to add to the network (default of null).
		//
		//Exceptions:
		//	- <Error>: The Node's parent <BaseStation> is different than the network's master <BaseStation>.
		//	- <Error_InvalidNodeConfig>: The configuration is not set for Synchronized Sampling mode.
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		//	- <Error_UnknownSampleRate>: The sample rate value read from the Node is not a valid SampleRate.
		void addNodeToNetwork(WirelessNode& node, const WirelessNodeConfig* pendingConfig = nullptr);

		//Function: calculateNetworkValues
		//	Calculates the network values for a single node, such as transmissions per group and group size.
		//	This reads values that are stored on the node to use in the calculations.
		//
		//Parameters:
		//	nodeAddress - The <NodeAddress> of the Node to calculate the values for.
		//	optimizeBandwidth - Whether we are attempting to optimize bandwidth or not
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred.
		//	- <Error_UnknownSampleRate>: The sample rate value read from the node is not a valid SampleRate.
		void calculateNetworkValues(NodeAddress nodeAddress, bool optimizeBandwidth);

		//Function: updateNetworkStatus
		//	Updates the status of each Node and calculates the total percent of bandwidth
		void updateNetworkStatus();

		//Function: sortByBandwidth
		//	Sorts the networkorder container by the percent of bandwidth (and by node address is bandwidth is the same).
		void sortByBandwidth();

		//Function: sortingFunction
		//	The function used as a predicate to sort the networkorder container by bandwidth
		//
		//Parameters:
		//	address1 - The first address
		//	address2 - The second address
		//
		//Returns:
		//	true if the first address should go first, false if the second address should go first
		bool sortingFunction(NodeAddress address1, NodeAddress address2);

		//Function: findSlotsForNodes
		//	Finds TDMA slots for every Node in the network. 
		//	Note that this clears m_slots before finding new slots for all of the Nodes.
		//
		//Returns:
		//	true if a slot was found for every node in the network, false if any of the nodes failed to find a slot.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to communicate with a Node.
		//	- <Error_Connection>: A connection error has occurred.
		bool findSlotsForNodes();

		//Function: getTdmaSlot
		//	Finds a TDMA slot for a single Node.
		//
		//Parameters:
		//	nodeAddress - The <NodeAddress> of the <WirelessNode> to find the TDMA slot for.
		//
		//Returns:
		//	true if a TDMA slot was found for the Node, false otherwise.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred.
		bool getTdmaSlot(NodeAddress nodeAddress);

		//Function: optimizeBandwidth
		//	Tries to optimize the bandwidth to give lossless nodes more time to transmit. 
		//	Nodes may be given different slots and the network order rearranged.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to communicate with a Node.
		//	- <Error_Connection>: A connection error has occurred.
		void optimizeBandwidth();

		//Function: findSamplingDelay
		//	Calculates the sampling delay for a node in the network.
		//
		//Parameters:
		//	nodeAddress- The <NodeAddress> of the <WirelessNode> to find the sampling delay for.
		//
		//Returns:
		//	The sampling delay to use for the given Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with a Node's parent BaseStation.
		uint32 findSamplingDelay(NodeAddress nodeAddress);

		//Function: sendStartToAllNodes
		//	Sends the start sync sampling command to all nodes in the network.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to start a Node Synchronized Sampling.
		//	- <Error_Connection>: A connection error has occurred.
		void sendStartToAllNodes();
	};
}