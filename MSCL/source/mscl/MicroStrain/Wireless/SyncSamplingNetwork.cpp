/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "SyncSamplingNetwork.h"

#include "mscl/Utils.h"
#include "WirelessNode.h"
#include "WirelessTypes.h"
#include "WirelessModels.h"
#include "mscl/MicroStrain/Wireless/Configuration/SyncNodeConfig.h"
#include "SyncSamplingFormulas.h"
#include "mscl/MicroStrain/SampleUtils.h"

namespace mscl
{
	SyncSamplingNetwork::SyncSamplingNetwork(const BaseStation& networkBaseStation):
		m_networkBase(networkBaseStation),
		m_lossless(true),
		m_highCapacity(false),
		m_percentBandwidth(0.0f),
		m_networkOk(true),
		m_configApplied(false)
	{
	}

	void SyncSamplingNetwork::addNodeToNetwork(WirelessNode& node, const WirelessNodeConfig* pendingConfig)
	{
		try
		{
			//verify that the node's basestation is the same as the network basestation
			if(!node.hasBaseStation(m_networkBase))
			{
				throw Error("The Node's parent BaseStation is different than the network's master BaseStation.");
			}

			//create the network info
			std::unique_ptr<SyncNetworkInfo> info(new SyncNetworkInfo(node));

			//if there is a pending config to set
			if(pendingConfig != nullptr)
			{
				//set the pending config on the info
				info->setPendingConfig(*pendingConfig);
			}

			//verify that the sampling mode is Sync Sampling
			SyncNodeConfig config(info.get());
			WirelessTypes::SamplingMode samplingMode = config.samplingMode();
			if(samplingMode != WirelessTypes::samplingMode_sync && samplingMode != WirelessTypes::samplingMode_syncBurst)
			{
				//nodes being added to the network must have their configuration be in Sync Sampling mode.
				ConfigIssues issues;
				issues.push_back(ConfigIssue(ConfigIssue::CONFIG_SAMPLING_MODE, "Configuration is not set for Synchronized Sampling mode."));
				throw Error_InvalidNodeConfig(issues, node.nodeAddress());
			}

			//add the node to the map of nodes in the network
			auto result = m_nodes.insert(std::pair<NodeAddress, std::unique_ptr<SyncNetworkInfo> >(node.nodeAddress(), std::move(info)));

			//if the node failed to be inserted (already exists in the map)
			if(!result.second)
			{
				return;
			}

			//add the node address to the network order container
			m_networkOrder.push_back(node.nodeAddress());

			//refresh the entire network
			refresh();
		}
		catch(...)
		{
			//there was a problem adding the node, remove it from the lists if it was added
			removeNode(node.nodeAddress());

			//forward the same exception
			throw;
		}
	}

	void SyncSamplingNetwork::addNode(WirelessNode& node)
	{
		//add the node to the network (no pending config)
		addNodeToNetwork(node);
	}

	void SyncSamplingNetwork::addNode(WirelessNode& node, const WirelessNodeConfig& pendingConfig)
	{
		//add the node to the network with the pending config
		addNodeToNetwork(node, &pendingConfig);
	}

	void SyncSamplingNetwork::removeNode(NodeAddress nodeAddress)
	{
		//remove from the SyncNetworkInfos map
		m_nodes.erase(nodeAddress);

		//find the node address in the networkOrder vector
		auto node = std::find(m_networkOrder.begin(), m_networkOrder.end(), nodeAddress);

		//if we found the node
		if(node != m_networkOrder.end())
		{
			//remove from the network order vector
			m_networkOrder.erase(node);
		}

		//refresh the entire network
		refresh();
	}

	float SyncSamplingNetwork::percentBandwidth() const
	{
		return m_percentBandwidth;
	}

	bool SyncSamplingNetwork::ok() const
	{
		return m_networkOk;
	}

	void SyncSamplingNetwork::refresh()
	{
		//the configuration has no longer been applied to any nodes
		m_configApplied = false;

		try
		{
			//loop through each node in the network
			for(NodeAddress nodeAddress : m_networkOrder)
			{
				//calculate the values and store in the SyncNetworkInfo map, not optimizing at this point
				calculateNetworkValues(nodeAddress, false);
			}

			//sort the network by bandwidth
			sortByBandwidth();

			//find slots for each node in the network 
			//Note: node's status are set to OK or Does Not Fit in this function
			findSlotsForNodes();

			//update the status of each node, and calculate the total percent bandwidth
			updateNetworkStatus();

			//if lossless is enabled for the network
			if(m_lossless)
			{
				//try to optimize bandwidth for all the nodes in the network
				optimizeBandwidth();

				//update the status of each node, and calculate the total percent bandwidth
				updateNetworkStatus();
			}
		}
		catch(Error)
		{
			//update the status of each node, and calculate the total percent bandwidth
			updateNetworkStatus();

			//pass on the exception
			throw;
		}
	}

	bool SyncSamplingNetwork::lossless() const
	{
		return m_lossless;
	}

	void SyncSamplingNetwork::lossless(bool enable)
	{
		//if we aren't changing anything, just return
		if(m_lossless == enable)
		{
			return;
		}

		m_lossless = enable;

		//refresh the network, now using the updated lossless option
		refresh();
	}

	bool SyncSamplingNetwork::highCapacity() const
	{
		return m_highCapacity;
	}

	void SyncSamplingNetwork::highCapacity(bool enable)
	{
		//if we aren't changing anything, just return
		if(m_highCapacity == enable)
		{
			return;
		}

		m_highCapacity = enable;

		//refresh the network, now using the updated high capacity option
		refresh();
	}

	void SyncSamplingNetwork::applyConfiguration()
	{
		//clear any pending configurations (refreshes the network if cleared any)
		clearAllPendingConfigs();

		//if the network is not OK
		if(!m_networkOk)
		{
			//throw an exception
			throw Error("Network status is not OK. Configuration cannot be applied.");
		}

		//determine which retransmission value to write to the nodes
		WirelessTypes::NodeRetransmission reTx_toWrite = WirelessTypes::retransmission_on;
		if(!m_lossless)
		{
			reTx_toWrite = WirelessTypes::retransmission_off;
		}

		//go through each node in the network
		for(NodeAddress nodeAddress : m_networkOrder)
		{
			SyncNetworkInfo& nodeInfo = getNodeNetworkInfo(nodeAddress);

			//if this node already had its configuration applied
			if(nodeInfo.m_configApplied)
			{
				//move to the next node
				continue;
			}

			SyncNodeConfig config(&nodeInfo);

			//write the tx per group value that we calculated
			config.txPerGroup(nodeInfo.m_txPerGroup);

			//write the group size value that we calculated
			config.groupSize(nodeInfo.m_groupSize);

			//write the TDMA address that we found
			config.tdmaAddress(nodeInfo.m_tdmaAddress);

			//get the node's current retransmission (lossless) value
			WirelessTypes::NodeRetransmission reTx = config.retransmission();

			//if retransmission (lossless) is not set to "disabled (do not touch)" on the node
			if(reTx != WirelessTypes::retransmission_disabled)
			{
				//if the node needs to change its retransmission value (not already set to what we want)
				if(reTx != reTx_toWrite)
				{
					//write the retransmission value 
					config.retransmission(reTx_toWrite);
				}
			}

			//if lossless is enabled and we are in burst mode
			if(m_lossless && config.syncSamplingMode() == WirelessTypes::syncMode_burst)
			{
				//write the max retransmissions per burst that we calculated
				config.maxRetransPerBurst(nodeInfo.m_maxRetxPerBurst);
			}

			//flag the node info that this configuration has been applied
			//In this way, successive calls to this function will only write to the nodes that haven't been applied, if any
			nodeInfo.m_configApplied = true;
		}

		//the configuration was applied successfully
		m_configApplied = true;
	}

	void SyncSamplingNetwork::startSampling()
	{
		if(!m_configApplied)
		{
			throw Error("Network configuration has not been applied. Cannot start sampling.");
		}

		//disable the beacon on the master base station
		//	Note: The beacon is the key to starting the network. 
		//		  Each node should be sent the start command, then the beacon should be enabled.
		m_networkBase.disableBeacon();

		//send the start sync sampling command to all nodes in the network
		sendStartToAllNodes();
		
		//enable the beacon on the master base station, with the system time
		m_networkBase.enableBeacon();
	}

	void SyncSamplingNetwork::startSampling(Timestamp startTime)
	{
		if(!m_configApplied)
		{
			throw Error("Network configuration has not been applied. Cannot start sampling.");
		}

		//disable the beacon on the master base station
		//	Note: The beacon is the key to starting the network. 
		//		  Each node should be sent the start command, then the beacon should be enabled.
		m_networkBase.disableBeacon();

		//send the start sync sampling command to all nodes in the network
		sendStartToAllNodes();
		
		//enable the beacon on the master base station, with the user specified time
		m_networkBase.enableBeacon(static_cast<uint32>(startTime.seconds()));
	}

	void SyncSamplingNetwork::startSampling_noBeacon()
	{
		if(!m_configApplied)
		{
			throw Error("Network configuration has not been applied. Cannot start sampling.");
		}

		//send the start sync sampling command to all nodes in the network
		sendStartToAllNodes();
	}

	SyncNetworkInfo& SyncSamplingNetwork::getNodeNetworkInfo(uint16 nodeAddress)
	{
		//find the node in the map
		auto result = m_nodes.find(nodeAddress);

		//if we didn't find the node in the map
		if(result == m_nodes.end())
		{
			throw Error("Node " + Utils::toStr(nodeAddress) + " was not found in the network.");
		}

		return *(result->second.get());
	}

	void SyncSamplingNetwork::setPendingConfig(uint16 nodeAddress, const WirelessNodeConfig& config)
	{
		//set the pending config for the given node
		getNodeNetworkInfo(nodeAddress).setPendingConfig(config);

		//refresh the entire network
		refresh();
	}

	void SyncSamplingNetwork::clearPendingConfig(uint16 nodeAddress)
	{
		//clear the pending config for the given node
		getNodeNetworkInfo(nodeAddress).clearPendingConfig();

		//refresh the entire network
		refresh();
	}

	void SyncSamplingNetwork::clearAllPendingConfigs()
	{
		bool clearedConfig = false;

		//loop through each configuration 
		for(auto &nodeItr : m_nodes)
		{
			if(nodeItr.second->hasPendingConfig())
			{
				//clear the configuration
				nodeItr.second->clearPendingConfig();

				//we've cleared at least 1 pending config
				clearedConfig = true;
			}
		}

		if(clearedConfig)
		{
			//refresh the entire network
			refresh();
		}
	}


	void SyncSamplingNetwork::calculateNetworkValues(NodeAddress nodeAddress, bool optimizeBandwidth)
	{
		SyncNetworkInfo& nodeInfo = getNodeNetworkInfo(nodeAddress);

		try
		{
			SyncNodeConfig config(&nodeInfo);

			uint32 groupSize = 0;
			uint32 txPerGroup = 0;

			//only use lossless if lossless is enabled for the network AND the node isn't set to "retransmission_disabled"
			bool useLossless = (m_lossless && config.retransmission() != WirelessTypes::retransmission_disabled);

			ChannelMask activeChs = config.activeChannels();

			//get the total number of active channels set on the Node
			uint16 totalChannels = activeChs.count();

			WirelessModels::NodeModel model = getNodeNetworkInfo(nodeAddress).m_model;

			//if this is the iepe-link, and channel 4 (temp) is enabled
			if(activeChs.enabled(4) && model == WirelessModels::node_iepeLink)
			{
				//channel 4 doesn't count as a channel in calculations (it transmits at a rate of once per burst)
				totalChannels -= 1;
			}

			//get the SampleRate set on the Node
			SampleRate sampleRate = config.sampleRate();

			uint32 maxRetransmissionPerBurst = 0;
		
			//if the sampling mode is Burst
			if(config.syncSamplingMode() == WirelessTypes::syncMode_burst)
			{
				//burst mode has a pre-defined group size
				groupSize = 1;

				//get the number of bytes per sample
				uint8 bytesPerSample = WirelessTypes::dataFormatSize(config.dataFormat());

				//calculate the number of bytes per sweep
				uint32 bytesPerSweep = SyncSamplingFormulas::bytesPerSweep(bytesPerSample, totalChannels);

				//get the number of sweeps per session set on the Node
				uint32 sweepsPerSession = config.sweepsPerSession();

				//calculate the total number of bytes
				uint32 totalBytesPerBurst = totalChannels * sweepsPerSession * bytesPerSample;

				//calculate the sample duration
				double sampleDuration = SyncSamplingFormulas::sampleDuration(sweepsPerSession, sampleRate);

				//calculate the maximum number of bytes per packet
				uint32 maxBytesPerPacket = SyncSamplingFormulas::maxDataBytesPerPacket(bytesPerSweep, useLossless);

				//calculate the total number of needed transmissions
				uint32 totalNeededTx = SyncSamplingFormulas::totalNeededBurstTx(totalBytesPerBurst, maxBytesPerPacket);
				maxRetransmissionPerBurst = totalNeededTx;

				//if there are not bytes per burst
				if(totalBytesPerBurst == 0)
				{
					//the transmissions per group is 0
					txPerGroup = 0;
				}
				else
				{
					//get the time between bursts set on the Node
					uint32 timeBetweenBursts = static_cast<uint32>(config.timeBetweenBursts().getSeconds());

					//calculate the number of transmissions per second
					uint32 burstTxPerSecond = SyncSamplingFormulas::burstTxPerSecond(totalNeededTx, timeBetweenBursts, sampleDuration, useLossless);

					//calculate the number of transmissions per group
					txPerGroup = burstTxPerSecond * groupSize;
				}
			}
			//if the sampling mode is "Continuous"
			else
			{
				//default to false
				bool useHighCapacity = false;
			
				//if the network has high capacity enabled
				if(m_highCapacity)
				{
					//if the sample rate is less than 16hz OR the sample rate is 16Hz with 1 channel active
					if( (sampleRate < SampleRate::Hertz(16)) ||
						(sampleRate == SampleRate::Hertz(16) && totalChannels == 1)
					  )
					{
						//we want to use high capacity mode for this node
						useHighCapacity = true;
					}
				}

				//get the number of bytes per sample
				uint8 bytesPerSample = WirelessTypes::dataFormatSize(config.dataFormat());

				//calculate the total number of bytes per second
				double bytesPerSecond = SyncSamplingFormulas::bytesPerSecond(sampleRate, totalChannels, bytesPerSample);

				//calculate the maximum bytes per packet
				uint32 maxBytesPerPacket = SyncSamplingFormulas::maxBytesPerPacket(sampleRate, useLossless, optimizeBandwidth);

				//calculate the group size
				groupSize = SyncSamplingFormulas::groupSize(bytesPerSecond, maxBytesPerPacket, useHighCapacity);

				//calculate the number of transmissions per group
				txPerGroup = SyncSamplingFormulas::txPerGroup(bytesPerSecond, maxBytesPerPacket, groupSize);
			}

			//calculate the maximum TDMA address
			uint32 maxTdma = SyncSamplingFormulas::maxTdmaAddress(txPerGroup, groupSize);

			//calculate the transmissions per second
			float txPerSecond = SyncSamplingFormulas::txPerSecond(txPerGroup, groupSize);

			float percentBandwidth = 0.0f;

			//if there are no active channels or the node is set to log only
			if(totalChannels == 0 || config.collectionMethod() == WirelessTypes::collectionMethod_logOnly)
			{
				//takes up 0% bandwidth
				percentBandwidth = 0.0f;
			}
			else
			{
				//calculate the percent of total bandwidth
				percentBandwidth = SyncSamplingFormulas::percentBandwidth(txPerSecond);
			}

			//if the configuration was previously applied, it isn't any longer
			nodeInfo.m_configApplied = false;

			//store the calculated values in the nodeInfo
			nodeInfo.m_slotSize = SyncSamplingFormulas::slotSpacing();
			nodeInfo.m_maxTdmaAddress = maxTdma;
			nodeInfo.m_txPerGroup = txPerGroup;
			nodeInfo.m_groupSize = groupSize;
			nodeInfo.m_maxRetxPerBurst = maxRetransmissionPerBurst;

			//only update the standard percent bandwidth if we are not trying to optimize the network
			if(!optimizeBandwidth)
			{
				//store the standard percent bandwidth
				nodeInfo.m_percentBandwidth = percentBandwidth;
			}

			//store the optimized percent bandwidth
			nodeInfo.m_percentBandwidth_optimized = percentBandwidth;
		}
		catch(Error)
		{
			//if anything throws here, we failed to calculate values for this node
			
			//we need to update the status of the node
			nodeInfo.m_configApplied = false;
			nodeInfo.m_status = SyncNetworkInfo::status_PoorCommunication;

			//pass on the same exception
			throw;
		}
	}

	void SyncSamplingNetwork::updateNetworkStatus()
	{
		float okStatusBandwidth = 0.0f;

		//reset the network bandwidth value
		m_percentBandwidth = 0.0f;

		//loop through each node in the network
		for(NodeAddress nodeAddress : m_networkOrder)
		{
			SyncNetworkInfo& nodeInfo = getNodeNetworkInfo(nodeAddress);

			//don't include nodes that failed to communicate
			if(nodeInfo.m_status != SyncNetworkInfo::status_PoorCommunication)
			{
				//add each node's bandwidth 
				m_percentBandwidth += nodeInfo.m_percentBandwidth;
			}

			//if the node has an OK status (found a slot)
			if(nodeInfo.m_status == SyncNetworkInfo::status_OK)
			{
				//keep track of the bandwidth for all nodes that found a slot
				okStatusBandwidth += nodeInfo.m_percentBandwidth;
			}
		}

		bool foundNodeNotInNetwork = false;

		//loop through each node in the network again
		for(NodeAddress nodeAddress : m_networkOrder)
		{
			SyncNetworkInfo& nodeInfo = getNodeNetworkInfo(nodeAddress);

			if(nodeInfo.m_status != SyncNetworkInfo::status_OK)
			{
				foundNodeNotInNetwork = true;

				//for nodes that didn't fit in the network (couldn't find a slot)
				if(nodeInfo.m_status == SyncNetworkInfo::status_DoesNotFit)
				{
					//if the node looks like it should be able to fit as far as bandwidth is concerned
					if((nodeInfo.m_percentBandwidth + okStatusBandwidth) < 99.0)
					{
						//the node's status is labeled as "contention" (didn't find a slot due to other reasons besides bandwidth)
						nodeInfo.m_status = SyncNetworkInfo::status_Contention;
					}
				}
			}
		}

		//set the network OK indicator (false if we found any nodes not in the network)
		m_networkOk = !foundNodeNotInNetwork;
	}

	void SyncSamplingNetwork::sortByBandwidth()
	{
		//sort the network order container, using the sortingFunction
		std::sort(m_networkOrder.begin(), m_networkOrder.end(), std::bind(&SyncSamplingNetwork::sortingFunction, this, std::placeholders::_1, std::placeholders::_2));
	}

	bool SyncSamplingNetwork::sortingFunction(NodeAddress address1, NodeAddress address2)
	{
		//find the percent bandwidth for each of these node addresses in the SyncNetworkInfo list
		float bandwidth1 = getNodeNetworkInfo(address1).m_percentBandwidth_optimized;
		float bandwidth2 = getNodeNetworkInfo(address2).m_percentBandwidth_optimized;

		if(bandwidth2 < bandwidth1)
		{
			return true;
		}
		else if(bandwidth2 > bandwidth1)
		{
			return false;
		}
		else
		{
			//bandwidth is equal, so now we are sorting by Node Address
			if(address2 < address1)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}

	bool SyncSamplingNetwork::findSlotsForNodes()
	{
		bool result = true;

		//find the correct number of total slots that we should use
		uint16 totalSlots = SyncSamplingFormulas::MAX_SLOTS;
		if(m_highCapacity)
		{
			//high capacity has more slots
			totalSlots = SyncSamplingFormulas::MAX_SLOTS_HIGH_CAPACITY;
		}

		//clear, than resize the slots container to the total slots
		m_slots.clear();
		m_slots.resize(totalSlots, false);

		//loop through all the node addresses (in network order)
		for(NodeAddress nodeAddress : m_networkOrder)
		{
			SyncNetworkInfo& nodeInfo = getNodeNetworkInfo(nodeAddress);
			SyncNodeConfig config(&nodeInfo);

			//if the node is set to log only
			if(config.collectionMethod() == WirelessTypes::collectionMethod_logOnly)
			{
				//the node shouldn't take up any slots in the network
				nodeInfo.m_tdmaAddress = 0;
				nodeInfo.m_txPerGroup = 0;
				nodeInfo.m_groupSize = 0;
				nodeInfo.m_status = SyncNetworkInfo::status_OK;
			}
			else
			{
				//attempt to find a TDMA address for this node
				bool foundSlot = getTdmaSlot(nodeAddress);

				//if a node failed to find a slot
				if(!foundSlot)
				{
					//a single node failing to find a slot should return false from this function
					result = false;
				}
			}
		}

		return result;
	}

	bool SyncSamplingNetwork::getTdmaSlot(NodeAddress nodeAddress)
	{
		SyncNetworkInfo& nodeInfo = getNodeNetworkInfo(nodeAddress);

		//create a SyncNodeConfig to access the node's values
		SyncNodeConfig config(&nodeInfo);

		//get the model of this node
		WirelessModels::NodeModel model = getNodeNetworkInfo(nodeAddress).m_model;

		SampleRate sampleRate = config.sampleRate();

		//find out if we need to check the sampling delay before finding a slot
		bool checkSamplingDelay = SyncSamplingFormulas::checkSamplingDelay(config.syncSamplingMode(), sampleRate, model);
		
		//find the sampling delay for this node
		uint32 samplingDelay = findSamplingDelay(nodeAddress);

		//get the txPerGroup and groupSize from the SyncNetworkInfo list
		uint32 txPerGroup = nodeInfo.m_txPerGroup;
		uint32 groupSize = nodeInfo.m_groupSize;
		uint32 maxAddress = nodeInfo.m_maxTdmaAddress;
		uint16 slotSize = nodeInfo.m_slotSize;

		//calculate the transmissions per second
		float txPerSecond = SyncSamplingFormulas::txPerSecond(txPerGroup, groupSize);

		//if there are no transmissions per second
		if(txPerSecond <= 0.0f) 
		{ 
			//set the TDMA address to 0 and return
			nodeInfo.m_tdmaAddress = 0;
			nodeInfo.m_status = SyncNetworkInfo::status_OK;
			return true; 
		}

		//calculate the number of slots between each transmission
		uint16 slotsBetweenTx = SyncSamplingFormulas::slotsBetweenTx(txPerGroup, groupSize);

		//if the number of slots between (the start of) transmissions is greater than the amount of slots each transmission takes up
		if(slotsBetweenTx < slotSize)
		{
			//this node does not fit in the network
			nodeInfo.m_status = SyncNetworkInfo::status_DoesNotFit;
			return false;
		}

		//determine the total number of slots
		uint16 totalSlots = static_cast<uint16>(m_slots.size());

		//determine the number of slots to look up to for this node
		uint16 slotTotalPerNode = SyncSamplingFormulas::MAX_SLOTS;
		if(txPerSecond < 1.0)
		{
			//for low tx/second, the number of slots to look
			//up to for this node is the total number of slots
			slotTotalPerNode = totalSlots;
		}

		//determine the total number of transmissions required
		uint16 totalTxRequired = (slotTotalPerNode / slotsBetweenTx);
		uint16 numTxFound = 0;

		uint32 samplingDelayCheck = static_cast<uint32>(SyncSamplingFormulas::MAX_SLOTS / sampleRate.samplesPerSecond());

		//check if the node can be assigned slot 1 or not
		bool canHaveSlot1 = SyncSamplingFormulas::canHaveSlot1(model);

		bool foundTakenSlot = false;
		uint16 resultSlot = 0;
		
		uint16 slotItr;
		uint16 extraSlotItr;
		uint16 checkSlotsItr;

		//loop through all the slots up to a max of the maxAddress
		for(slotItr = SyncSamplingFormulas::MIN_TDMA; slotItr < totalSlots && slotItr <= maxAddress; slotItr += slotSize)
		{
			//if this slot is available
			if(m_slots.at(0) == false)
			{
				//if this is slot 1 and this node is not allowed to have slot 1
				if(slotItr == 1 && !canHaveSlot1)
				{
					//move on to the next slot
					continue;
				}

				//if we need to check the sampling delay
				if(checkSamplingDelay)
				{
					//check if this slot is ok with the sampling delay
					if(slotItr % samplingDelayCheck <= samplingDelay)
					{
						//node can't have this slot, move on to the next slot
						continue;
					}
				}

				checkSlotsItr = slotItr;

				while( ((checkSlotsItr + slotSize) < slotTotalPerNode) &&		//while there is room to continue looking
					(numTxFound < totalTxRequired) &&							//and we haven't found all the transmission slots that are required
					!foundTakenSlot)											//and we haven't found a taken slot
				{
					//check that the next [slotSize] spaces are available
					for(extraSlotItr = 1; extraSlotItr < slotSize; ++extraSlotItr)
					{
						//if we find a taken slot
						if(m_slots.at(checkSlotsItr + extraSlotItr) == true)
						{
							//stop looking at this slot
							foundTakenSlot = true;
							break;
						}
					}

					//move the required number of slots between each transmission
					checkSlotsItr += slotsBetweenTx;

					//if we found a slot
					if(!foundTakenSlot)
					{
						//increment the number of transmissions found
						numTxFound++;
					}
				}

				//if we found the required number of transmission slots
				if(!foundTakenSlot && (numTxFound >= totalTxRequired))
				{
					//this is the slot that will be assigned to the node
					resultSlot = slotItr;

					//need to fill in all the slots that this node will be using (all the way up the line)
					while((slotItr + slotSize) < totalSlots)
					{
						//loop through [slotSize] number of slots
						for(uint16 writeSlot = 0; writeSlot < slotSize; ++writeSlot)
						{
							assert(m_slots.at(slotItr + writeSlot) == false);	//none of these slots should already be taken

							//set the slot to 1 to signify it is taken
							m_slots.at(slotItr + writeSlot) = true;
						}

						//move the slotItr the number of slots between transmissions
						slotItr += slotsBetweenTx;
					}
					
					//store the found TDMA address and return
					nodeInfo.m_tdmaAddress = resultSlot;
					nodeInfo.m_status = SyncNetworkInfo::status_OK;
					return true;
				}
			}

			//reset the foundTakenSlot flag
			foundTakenSlot = false;
		}

		//failed to find a slot for the node
		nodeInfo.m_status = SyncNetworkInfo::status_DoesNotFit;
		return false;
	}

	void SyncSamplingNetwork::optimizeBandwidth()
	{
		//only optimize bandwidth if network is OK (all nodes in network)
		if(!m_networkOk)
		{
			return;
		}

		//reset the "optimized" flags for all the nodes
		for(NodeAddress nodeAddress : m_networkOrder)
		{
			getNodeNetworkInfo(nodeAddress).m_optimized = false;
		}

		bool complete = false;
		bool optimizationNeeded = false;

		//512Hz and above should not attempt optimization
		static const SampleRate HIGH_SAMPLERATE = SampleRate::Hertz(512);

		//while we haven't finished optimizing
		while(!complete)
		{
			optimizationNeeded = false;

			//loop through nodes from lowest %BW to highest %BW
			for(auto networkItr = m_networkOrder.rbegin(); networkItr != m_networkOrder.rend(); ++networkItr)
			{
				NodeAddress nodeAddress = *networkItr;

				//get the SyncNetworkInfo
				SyncNetworkInfo& nodeInfo = getNodeNetworkInfo(nodeAddress);

				//if this node has already attempted optimization
				if(nodeInfo.m_optimized)
				{
					//skip to the next node
					continue;
				}

				//found a node that needs optimized
				optimizationNeeded = true;

				//get the WirelessNode and create a SyncNodeConfig object to access its eeprom values
				SyncNodeConfig config(&nodeInfo);

				//don't optimize in the following situations
				if( config.syncSamplingMode() == WirelessTypes::syncMode_burst || 
					config.sampleRate() >= HIGH_SAMPLERATE ||
					SyncSamplingFormulas::txPerSecond(nodeInfo.m_txPerGroup, nodeInfo.m_groupSize) >= 64.0f ||
					config.retransmission() == WirelessTypes::retransmission_disabled
				  )
				{
					//set this node to optimized so we don't attempt it again, and move to the next node
					nodeInfo.m_optimized = true;
					continue;
				}

				//re-calculate the network values, with optimizeBandwidth set to true
				calculateNetworkValues(nodeAddress, true);

				//re-sort the network by bandwidth
				sortByBandwidth();

				//find slots for all the nodes again, using their newly calculated values
				bool allNodesFoundSlots = findSlotsForNodes();

				//if the network is no longer OK (slots not found for all nodes)
				if(!allNodesFoundSlots)
				{
					//change back to not optimizing and re-calculate
					calculateNetworkValues(nodeAddress, false);

					//re-sort the network by bandwidth
					sortByBandwidth();

					//find slots for all the nodes again
					findSlotsForNodes();

					//stop and return on the first node that fails to optimize
					//	Note: this is ok because we are working in reverse order of % bandwidth
					return;
				}
				else
				{
					//the network is still OK (slots found for all nodes)
					nodeInfo.m_optimized = true;

					//break out of the for loop once we found a node that was optimized
					//because the networkOrder vector was resorted. The while loop will force us to continue on.
					break;
				}
			}

			//if we didn't find any nodes that needed optimizations
			if(!optimizationNeeded)
			{
				complete = true;
			}
		}
	}

	uint32 SyncSamplingNetwork::findSamplingDelay(NodeAddress nodeAddress)
	{
		uint32 delayResult = 0;
		int32 settlingTime = 0;

		//get the SyncNetworkInfo
		SyncNetworkInfo& nodeInfo = getNodeNetworkInfo(nodeAddress);

		//get the WirelessNode and create a SyncNodeConfig object to access its eeprom values
		SyncNodeConfig config(&nodeInfo);

		//get the active channels
		ChannelMask channels = config.activeChannels();

		//different models have different formulas for determining the sampling delay value
		WirelessModels::NodeModel model = getNodeNetworkInfo(nodeAddress).m_model;
		switch(model)
		{
			case WirelessModels::node_tcLink_1ch:
			case WirelessModels::node_tcLink_3ch:
			case WirelessModels::node_tcLink_6ch:
			case WirelessModels::node_tcLink_6ch_ip67:
			case WirelessModels::node_rtdLink:
			{
				bool addThermoExtra = false;
				uint8 extraThermo = 14;
				uint8 extraPerCh = 3;

				//certain nodes with sample rates 32Hz and above need special delays
				bool useSampleRate = false, tcLink6ch = false;
				if((model == WirelessModels::node_tcLink_1ch || model == WirelessModels::node_rtdLink) && (config.sampleRate() >= SampleRate::Hertz(32)))
				{
					useSampleRate = true;
				}
				else if(model == WirelessModels::node_tcLink_6ch || model == WirelessModels::node_tcLink_6ch_ip67)
				{
					tcLink6ch = true;
				}

				uint8 lastActiveCh = channels.lastChEnabled();

				//loop through all the possible active channels
				for(uint8 chanItr = 1; chanItr <= lastActiveCh; ++chanItr)
				{
					//if this channel is enabled
					if(channels.enabled(chanItr))
					{
						//channels 1 - 6
						if(chanItr <= 6)
						{
							//this is a thermocouple channel
							addThermoExtra = true;

							settlingTime = WirelessTypes::settlingTime(config.filter1());

							//certain nodes need special delays
							if(useSampleRate)
							{
								settlingTime *= 2;
								settlingTime -= static_cast<int32>((config.sampleRate().samplesPerSecond() * 1000) + 0.5);

								//settling time can't be less than 0
								Utils::checkBounds_min(settlingTime, static_cast<int32>(0));

								extraThermo = 0;
								extraPerCh = 0;
							}
							else if(tcLink6ch)
							{
								settlingTime += 6;
								extraPerCh = 0;
							}

							//add to the delayResult
							delayResult += (settlingTime + extraPerCh);
						}
						//channel 8
						else if(chanItr == 8)
						{
							//add to the delayResult
							delayResult += 80;
						}
					}
				}

				//if we need to add extra because we are using thermocouples
				if(addThermoExtra)
				{
					//add to the delayResult
					delayResult += extraThermo;
				}

				break;
			}

			case WirelessModels::node_envLink_pro:
			{
				bool addThermoExtra = false, addVoltageExtra = false;

				uint8 lastActiveCh = channels.lastChEnabled();

				//loop through all the possible active channels
				for(uint8 chanItr = 1; chanItr <= lastActiveCh; ++chanItr)
				{
					//if this channel is enabled
					if(channels.enabled(chanItr))
					{
						//channels 1 - 2
						if(chanItr <= 2)
						{
							addThermoExtra = true;

							//first filter (thermocouple)
							settlingTime = WirelessTypes::settlingTime(config.filter1());

							delayResult += settlingTime + 3;
						}
						//channels 3 - 6
						else if(chanItr <= 6)
						{
							addVoltageExtra = true;

							//second filter (voltage)
							settlingTime = WirelessTypes::settlingTime(config.filter2());

							delayResult += settlingTime + 8;
						}
						//channel 7
						else if(chanItr == 7)
						{
							delayResult += 225;
						}
						//channel 8
						else if(chanItr == 8)
						{
							delayResult += 80;
						}
					}
				}

				if(addThermoExtra)
				{
					delayResult += 14;
				}

				if(addVoltageExtra)
				{
					delayResult += 5;
				}

				break;
			}

			case WirelessModels::node_envLink_mini:
			{
				bool addVoltageExtra = false;

				uint8 lastActiveCh = channels.lastChEnabled();

				//loop through all the possible active channels
				for(uint8 chanItr = 1; chanItr <= lastActiveCh; ++chanItr)
				{
					//if this channel is enabled
					if(channels.enabled(chanItr))
					{
						//channels 1 - 6
						if(chanItr <= 6)
						{
							addVoltageExtra = true;

							//first filter (voltage)
							settlingTime = WirelessTypes::settlingTime(config.filter1());

							delayResult += settlingTime + 8;
						}
						//channel 7
						else if(chanItr == 7)
						{
							delayResult += 225;
						}
						//channel 8
						else if(chanItr == 8)
						{
							delayResult += 80;
						}
					}
				}

				if(addVoltageExtra)
				{
					delayResult += 5;
				}

				break;
			}

			case WirelessModels::node_wattLink:
			case WirelessModels::node_wattLink_3Y600:
			case WirelessModels::node_wattLink_3Y480:
			case WirelessModels::node_wattLink_3Y400:
			case WirelessModels::node_wattLink_3Y208:
			case WirelessModels::node_wattLink_3D480:
			case WirelessModels::node_wattLink_3D400:
			case WirelessModels::node_wattLink_3D240:
			{
				//watt-link always has a delay of 75 milliseconds
				delayResult = 75;

				break;
			}

			case WirelessModels::node_shmLink:
			case WirelessModels::node_shmLink2:
			case WirelessModels::node_shmLink2_cust1:
			case WirelessModels::node_sgLink_herm:
			case WirelessModels::node_sgLink_herm_2600:
			case WirelessModels::node_sgLink_herm_2700:
			case WirelessModels::node_sgLink_herm_2800:
			case WirelessModels::node_sgLink_rgd:
			{
				//get the sampling delay stored in EEPROM (this node uses this values as microseconds instead of milliseconds).
				uint16 delayEepromVal = static_cast<uint16>(config.samplingDelay().getMicroseconds());

				//delay (in microseconds) = (eeprom delay + 5.0) * # active channels
				float delayInMicrosec = static_cast<float>((delayEepromVal + 5.0) * config.activeChannels().count());

				//round down to nearest millisecond
				delayResult = static_cast<int>(delayInMicrosec / 1000.0);

				break;
			}

			default:
			{
				delayResult = static_cast<uint32>(config.samplingDelay().getMilliseconds());

				//10000 = no delay
				if(delayResult == 10000)		
				{ 
					//set to no delay
					delayResult = 0; 
				}	
				else if(delayResult > 1000)	
				{ 
					//max delay is 1s, default to delay of 5ms
					delayResult = 5; 
				}

				break;
			}
		}

		return delayResult;
	}

	void SyncSamplingNetwork::sendStartToAllNodes()
	{
		//go through each node in the network
		for(NodeAddress nodeAddress : m_networkOrder)
		{
			SyncNetworkInfo& nodeInfo = getNodeNetworkInfo(nodeAddress);

			//only want to start nodes that haven't already been started (in previous calls to this function)
			if(!nodeInfo.m_startedSampling)
			{
				//send the start sync sampling command to each node individually
				if(!m_networkBase.node_startSyncSampling(nodeAddress))
				{
					//if the command has failed, throw an exception
					throw Error_NodeCommunication(nodeAddress, "Failed to start Synchronized Sampling on the Node");
				}
				//the command succeeded
				else
				{
					//mark this node as started sampling so that we don't apply it again on successive calls to this function
					nodeInfo.m_startedSampling = true;

					//sleep between each node start sampling command for good measure
					Utils::threadSleep(50);
				}
			}
		}
	}
	
	//TODO: possibly don't optimize nodes that already have extra bandwidth (are slow)
}