/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "SyncSamplingNetwork.h"

#include "mscl/Utils.h"
#include "WirelessNode.h"
#include "WirelessTypes.h"
#include "WirelessModels.h"
#include "Configuration/SyncNodeConfig.h"
#include "Configuration/WirelessNodeConfig.h"
#include "SyncSamplingFormulas.h"
#include "mscl/MicroStrain/SampleUtils.h"
#include "mscl/MicroStrain/Wireless/NodeCommTimes.h"

namespace mscl
{
    SyncSamplingNetwork::SyncSamplingNetwork(const BaseStation& networkBaseStation):
        m_networkBase(networkBaseStation),
        m_lossless(true),
        m_commProtocol(m_networkBase.communicationProtocol()),
        m_percentBandwidth(0.0f),
        m_networkOk(true),
        m_configApplied(false),
        m_disabledBeacon(false),
        m_availableSlotCount(0)
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
            if(samplingMode != WirelessTypes::samplingMode_sync &&
               samplingMode != WirelessTypes::samplingMode_syncBurst &&
               samplingMode != WirelessTypes::samplingMode_syncEvent)
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
            m_allNodes.push_back(node.nodeAddress());

            //add the node to the correct container based on event driven or not
            if(samplingMode == WirelessTypes::samplingMode_syncEvent)
            {
                m_eventNodes.push_back(node.nodeAddress());
            }
            else
            {
                m_nonEventNodes.push_back(node.nodeAddress());
            }

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
        auto node = std::find(m_allNodes.begin(), m_allNodes.end(), nodeAddress);

        //if we found the node
        if(node != m_allNodes.end())
        {
            //remove from the network order vector
            m_allNodes.erase(node);
        }

        //remove from the event nodes if its in that container
        node = std::find(m_eventNodes.begin(), m_eventNodes.end(), nodeAddress);
        if(node != m_eventNodes.end())
        {
            m_eventNodes.erase(node);
        }
        else
        {
            //remove from the non-event nodes if its in that container
            node = std::find(m_nonEventNodes.begin(), m_nonEventNodes.end(), nodeAddress);
            if(node != m_nonEventNodes.end())
            {
                m_nonEventNodes.erase(node);
            }
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
            for(NodeAddress nodeAddress : m_allNodes)
            {
                //calculate the values and store in the SyncNetworkInfo map, not optimizing at this point
                calculateNetworkValues(nodeAddress, false);
            }

            //sort the non-event nodes by bandwidth
            sortByBandwidth( m_nonEventNodes );

            //find slots for each non-event node in the network
            //  Note: node's status are set to OK or Does Not Fit in this function
            findSlotsForNodes( m_nonEventNodes );

            //recalculate transmissions per group and bandwidth for event nodes
            divvyUpEventTransmissions();

            //sort the full list of nodes (event and non-event) by bandwidth
            sortByBandwidth(m_allNodes);

            //find slots for full list of nodes
            findSlotsForNodes(m_allNodes);

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

    WirelessTypes::CommProtocol SyncSamplingNetwork::communicationProtocol() const
    {
        return m_commProtocol;
    }

    void SyncSamplingNetwork::communicationProtocol(WirelessTypes::CommProtocol protocol)
    {
        //if we aren't changing anything, just return
        if(m_commProtocol == protocol)
        {
            return;
        }

        m_commProtocol = protocol;

        //refresh the network, now using the updated comm protocol
        refresh();
    }

    void SyncSamplingNetwork::applyConfiguration()
    {
        static const uint8 LEGACY_MODE_TDMA_OFFSET = 4;

        if(m_networkBase.communicationProtocol() != m_commProtocol)
        {
            throw Error("The BaseStation is configured for a different Communication Protocol than the network is set to.");
        }

        for(auto &nodeItr : m_nodes)
        {
            SyncNodeConfig config(nodeItr.second.get());
            if(config.commProtocol() != m_commProtocol)
            {
                throw Error("A Node is configured for a different Communication Protocol than the network is set to.");
            }
        }

        for(auto &nodeItr : m_nodes)
        {
            if(nodeItr.second->hasPendingConfig())
            {
                throw Error("Cannot apply network settings with a pending config.");
            }
        }

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

        bool legacyMode = inLegacyMode();

        //go through each node in the network
        for(NodeAddress nodeAddress : m_allNodes)
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

            //if we have a mixed legacy network,
            if(legacyMode && nodeInfo.syncSamplingVersion() == 2)
            {
                //write the TDMA address that we found, adding in the offset for legacy mode
                config.tdmaAddress(nodeInfo.m_tdmaAddress + LEGACY_MODE_TDMA_OFFSET);
            }
            else
            {
                //write the TDMA address that we found
                config.tdmaAddress(nodeInfo.m_tdmaAddress);
            }

            //write the retransmission value 
            config.retransmission(reTx_toWrite);

            //if lossless is enabled and we are in burst mode
            if(m_lossless && config.samplingMode() == WirelessTypes::samplingMode_syncBurst)
            {
                //write the max retransmissions per burst that we calculated
                config.maxRetransPerBurst(nodeInfo.m_maxRetxPerBurst);
            }

            //reset the node to apply changes
            config.applyEepromChanges();

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

        if(!m_disabledBeacon)
        {
            //disable the beacon on the master base station
            //    Note: The beacon is the key to starting the network. 
            //          Each node should be sent the start command, then the beacon should be enabled.
            m_networkBase.disableBeacon();
            m_disabledBeacon = true;
        }

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

        if(!m_disabledBeacon)
        {
            //disable the beacon on the master base station
            //    Note: The beacon is the key to starting the network. 
            //          Each node should be sent the start command, then the beacon should be enabled.
            m_networkBase.disableBeacon();
            m_disabledBeacon = true;
        }

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

    SyncNetworkInfo& SyncSamplingNetwork::getNodeNetworkInfo(NodeAddress nodeAddress)
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

    void SyncSamplingNetwork::calculateNetworkValues(NodeAddress nodeAddress, bool optimizeBandwidth)
    {
        SyncNetworkInfo& nodeInfo = getNodeNetworkInfo(nodeAddress);

        try
        {
            SyncNodeConfig config(&nodeInfo);

            uint32 groupSize = 0;
            uint32 txPerGroup = 0;
            double burstSampleDuration = 0.0;

            uint16 totalChannels = config.activeChannelCount();
            SampleRate sampleRate = config.sampleRate();
            bool diagnosticPacketEnabled = (config.diagnosticInterval() > 0);
            uint8 bytesPerSample = WirelessTypes::dataFormatSize(config.dataFormat());

            uint32 maxRetransmissionPerBurst = 0;

            //calculate the number of bytes per sweep
            nodeInfo.m_bytesPerSweep = SyncSamplingFormulas::bytesPerSweep(bytesPerSample, totalChannels);

            float rawPacketsPerGroup = 0.0;
            float derivedPacketsPerGroup = 0.0;

            DataModeMask mode = config.dataMode();

            bool isBurstMode = (config.samplingMode() == WirelessTypes::samplingMode_syncBurst);

            uint16 maxBytes;
            float derivedMaxBytes;
            switch(m_commProtocol)
            {
                case WirelessTypes::commProtocol_lxrsPlus:
                    maxBytes = 207;
                    derivedMaxBytes = 207.0f;
                    break;

                case WirelessTypes::commProtocol_lxrs:
                default:
                    maxBytes = 96;
                    derivedMaxBytes = 94.0f;
                    break;
            }

            if(isBurstMode)
            {
                //burst mode has a pre-defined group size
                groupSize = 1;

                //get the number of sweeps per session set on the Node
                uint32 sweepsPerSession = config.sweepsPerSession();

                //calculate the total number of bytes
                nodeInfo.m_bytesPerBurst = totalChannels * sweepsPerSession * bytesPerSample;

                //calculate the sample duration
                burstSampleDuration = SyncSamplingFormulas::sampleDuration(sweepsPerSession, sampleRate);

                //calculate the maximum number of bytes per packet
                nodeInfo.m_maxBytesPerPacket = SyncSamplingFormulas::maxBytesPerBurstPacket(nodeInfo.m_bytesPerSweep, m_lossless, m_commProtocol);
            }
            //Continuous mode
            else
            {
                //calculate the total number of bytes per second
                nodeInfo.m_bytesPerSecond = SyncSamplingFormulas::bytesPerSecond(sampleRate, totalChannels, bytesPerSample);

                //calculate the maximum bytes per packet
                nodeInfo.m_maxBytesPerPacket = SyncSamplingFormulas::maxBytesPerPacket(sampleRate, m_lossless, optimizeBandwidth, nodeInfo.syncSamplingVersion(), m_commProtocol);

                groupSize = SyncSamplingFormulas::groupSize();

                if(mode.rawModeEnabled)
                {
                    if(nodeInfo.m_bytesPerSweep > (maxBytes / 2u))
                    {
                        nodeInfo.m_bytesPerSweep = static_cast<uint32>(maxBytes * std::ceil(static_cast<float>(nodeInfo.m_bytesPerSweep) / static_cast<float>(maxBytes)));
                    }

                    rawPacketsPerGroup = static_cast<float>(sampleRate.samplesPerSecond() * groupSize * nodeInfo.m_bytesPerSweep / maxBytes);
                }
            }

            //Derived Channels enabled
            if(mode.derivedModeEnabled)
            {
                uint8 derivedChannelCount = 0;
                uint8 numDerivedNonChBytes = 0;

                const WirelessTypes::DerivedChannelMasks& chs = nodeInfo.supportedDerivedCategories();

                uint8 count = 0;
                for(const auto& ch : chs)
                {
                    count = config.derivedChannelMask(ch.first).count();

                    if(count > 0)
                    {
                        derivedChannelCount += count;
                        numDerivedNonChBytes += 3;  //3 per Derived Channel (may change based on channel in the future)
                    }
                }

                derivedMaxBytes -= numDerivedNonChBytes;

                uint16 derivedSweepSize = 4 * derivedChannelCount;

                if(derivedSweepSize > (derivedMaxBytes / 2.0f))
                {
                    derivedSweepSize = static_cast<uint16>(derivedMaxBytes * std::ceil(derivedSweepSize / derivedMaxBytes));
                }

                //Note: the +1 accounts for overhead needed because the Node isn't buffering multiple derived sweeps into one packet
                derivedPacketsPerGroup = (static_cast<float>(config.derivedDataRate().samplesPerSecond()) * groupSize * derivedSweepSize / derivedMaxBytes) + 1;
            }

            if(isBurstMode)
            {
                uint32 totalNeededTx = 0;

                if(mode.derivedModeEnabled)
                {
                    totalNeededTx += static_cast<uint32>(ceil(derivedPacketsPerGroup));
                }

                if(mode.rawModeEnabled)
                {
                    totalNeededTx += SyncSamplingFormulas::totalNeededBurstTx(nodeInfo.m_bytesPerBurst, nodeInfo.m_maxBytesPerPacket);
                }

                maxRetransmissionPerBurst = totalNeededTx;

                //if there are not bytes per burst
                if(nodeInfo.m_bytesPerBurst == 0 && !mode.derivedModeEnabled)
                {
                    //the transmissions per group is 0
                    txPerGroup = 0;
                }
                else
                {
                    //get the time between bursts set on the Node
                    uint32 timeBetweenBursts = static_cast<uint32>(config.timeBetweenBursts().getSeconds());

                    //calculate the number of transmissions per second
                    uint32 burstTxPerSecond = SyncSamplingFormulas::burstTxPerSecond(totalNeededTx, timeBetweenBursts, burstSampleDuration, m_lossless);

                    //calculate the number of transmissions per group
                    txPerGroup = burstTxPerSecond * groupSize;
                }
            }
            else
            {
                //update transmissions per group for continuous mode
                float overheadFactor = SyncSamplingFormulas::overheadFactor(m_lossless, optimizeBandwidth, diagnosticPacketEnabled, sampleRate, nodeInfo.syncSamplingVersion());
                txPerGroup = Utils::ceilBase2(std::ceil((rawPacketsPerGroup + derivedPacketsPerGroup) * overheadFactor));
            }

            //calculate the maximum TDMA address
            uint32 maxTdma = SyncSamplingFormulas::maxTdmaAddress(txPerGroup, groupSize, inLegacyMode(), m_commProtocol);

            //calculate the transmissions per second
            float txPerSecond = SyncSamplingFormulas::txPerSecond(txPerGroup, groupSize);

            float percentBandwidth = 0.0f;

            //if there are no active channels or the node is set to log only
            if(config.collectionMethod() == WirelessTypes::collectionMethod_logOnly)
            {
                //takes up 0% bandwidth
                percentBandwidth = 0.0f;
            }
            else
            {
                //calculate the percent of total bandwidth
                percentBandwidth = SyncSamplingFormulas::percentBandwidth(txPerSecond, inLegacyMode(), m_commProtocol);
            }

            //if the configuration was previously applied, it isn't any longer
            nodeInfo.m_configApplied = false;

            //store the calculated values in the nodeInfo
            nodeInfo.m_slotSize = SyncSamplingFormulas::slotSpacing(m_commProtocol);
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

    void SyncSamplingNetwork::divvyUpEventTransmissions()
    {
        if(m_eventNodes.size() == 0)
        {
            return;
        }

        //convert the "mini-slots" to real slots
        uint16 largeSlotsLeft = m_availableSlotCount / SyncSamplingFormulas::slotSpacing(m_commProtocol);

        //if all nodes only have 1 slot available to them, make sure they can still fit
        if(m_eventNodes.size() > largeSlotsLeft)
        {
            return;
        }

        double totalBytesPerSec = 0.0;

        //calculate the total Bytes per Second for all event nodes
        for(auto nodeAddress : m_eventNodes)
        {
            SyncNetworkInfo& nodeInfo = getNodeNetworkInfo(nodeAddress);

            //add up the continuous bytes per second for each event node (as if sampling continuously)
            totalBytesPerSec += nodeInfo.m_bytesPerSecond;
        }

        //calculate the slots per second for all event nodes
        for(auto nodeAddress : m_eventNodes)
        {
            SyncNetworkInfo& nodeInfo = getNodeNetworkInfo(nodeAddress);

            nodeInfo.m_txPerGroup = Utils::floorBase2(largeSlotsLeft * (nodeInfo.m_bytesPerSecond / totalBytesPerSec));

            if(nodeInfo.dutyCycle() > 1.0)
            {
                nodeInfo.dutyCycle(1.0f);
            }

            if(nodeInfo.m_txPerGroup == 0)
            {
                nodeInfo.m_txPerGroup = 1;
            }
        }

        float highestDutyCycle = 0.0;
        SyncNetworkInfo* highestDutyCycleNodeInfo = nullptr;

        //make sure we aren't over using our slots
        while(totalEventTxPerGroup() > largeSlotsLeft)
        {
            //divide the slots of the node with the highest duty cycle in half (ignoring nodes with 1 slot)

            highestDutyCycle = 0.0;

            for(auto nodeAddress : m_eventNodes)
            {
                SyncNetworkInfo& nodeInfo = getNodeNetworkInfo(nodeAddress);

                //only look at nodes with more than 1 tx per group
                if(nodeInfo.m_txPerGroup > 1)
                {
                    //keep track of the highest duty cycle
                    if(nodeInfo.dutyCycle() > highestDutyCycle)
                    {
                        highestDutyCycle = nodeInfo.dutyCycle();
                        highestDutyCycleNodeInfo = &nodeInfo;
                    }
                }
            }

            highestDutyCycleNodeInfo->m_txPerGroup /= 2;
        }

        float txPerSecond = 0.0f;
        bool legacyMode = inLegacyMode();
        
        //update other values that were affected by txPerGroup changing
        for(auto nodeAddress : m_eventNodes)
        {
            SyncNetworkInfo& nodeInfo = getNodeNetworkInfo(nodeAddress);

            //don't update on log-only nodes
            if(nodeInfo.m_percentBandwidth != 0.0f)
            {
                txPerSecond = SyncSamplingFormulas::txPerSecond(nodeInfo.m_txPerGroup, nodeInfo.m_groupSize);

                nodeInfo.m_maxTdmaAddress = SyncSamplingFormulas::maxTdmaAddress(nodeInfo.m_txPerGroup, nodeInfo.m_groupSize, legacyMode, m_commProtocol);
                nodeInfo.m_percentBandwidth = SyncSamplingFormulas::percentBandwidth(txPerSecond, legacyMode, m_commProtocol);
                nodeInfo.m_percentBandwidth_optimized = nodeInfo.m_percentBandwidth;
            }
        }
    }

    double SyncSamplingNetwork::totalEventTxPerGroup()
    {
        double result = 0.0;
        for(auto nodeAddress : m_eventNodes)
        {
            SyncNetworkInfo& nodeInfo = getNodeNetworkInfo(nodeAddress);
            result += nodeInfo.m_txPerGroup;
        }

        return result;
    }

    void SyncSamplingNetwork::updateNetworkStatus()
    {
        float okStatusBandwidth = 0.0f;

        //reset the network bandwidth value
        m_percentBandwidth = 0.0f;

        //loop through each node in the network
        for(NodeAddress nodeAddress : m_allNodes)
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
        for(NodeAddress nodeAddress : m_allNodes)
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

    void SyncSamplingNetwork::sortByBandwidth(std::vector<NodeAddress>& container)
    {
        //sort the passed in container of node addresses, using the sortingFunction
        std::sort(container.begin(), container.end(), std::bind(&SyncSamplingNetwork::sortingFunction, this, std::placeholders::_1, std::placeholders::_2));
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

    bool SyncSamplingNetwork::findSlotsForNodes(const std::vector<NodeAddress>& nodes)
    {
        bool result = true;

        //find the correct number of total slots that we should use
        uint16 totalSlots = SyncSamplingFormulas::MAX_SLOTS;

        //clear, than resize the slots container to the total slots
        m_slots.clear();
        m_slots.resize(totalSlots, false);
        m_availableSlotCount = totalSlots;

        //loop through all the node addresses (in network order)
        for(NodeAddress nodeAddress : nodes)
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
        bool checkSamplingDelay = false;
        if(nodeInfo.syncSamplingVersion() == 1)
        {
            checkSamplingDelay = SyncSamplingFormulas::checkSamplingDelay(config.samplingMode(), sampleRate, model);
        }
        
        //find the sampling delay for this node
        uint32 samplingDelay = 0;
        if(checkSamplingDelay)
        {
            samplingDelay = findSamplingDelay(nodeAddress);
        }

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

        //check if the node can be assigned the first slot
        bool canHaveFirstSlot = SyncSamplingFormulas::canHaveFirstSlot(model, nodeInfo.syncSamplingVersion());

        bool foundTakenSlot = false;
        uint16 resultSlot = 0;
        
        uint16 slotItr;
        uint16 extraSlotItr;
        uint16 checkSlotsItr;

        //need to reserve the last 8 slots (in each second [16 if high cap]) if we are in legacy mode
        if(inLegacyMode())
        {
            slotItr = 1016;
            uint16 i = 0;
            while(slotItr < totalSlots)
            {
                for(i = 0; i < slotSize; i++)
                {
                    m_slots.at(slotItr + i) = true;
                }

                slotItr += SyncSamplingFormulas::MAX_SLOTS;
            }

        }

        //loop through all the slots up to a max of the maxAddress
        for(slotItr = 0; slotItr < totalSlots && slotItr <= maxAddress - 1; slotItr += slotSize)
        {
            //if this slot is available
            if(m_slots.at(slotItr) == false)
            {
                //if this is the first slot and this node is not allowed to have it
                if(slotItr == 0 && !canHaveFirstSlot)
                {
                    //move on to the next slot
                    continue;
                }

                //if we need to check the sampling delay
                if(checkSamplingDelay)
                {
                    //check if this slot is ok with the sampling delay
                    if((slotItr + 1) % samplingDelayCheck <= samplingDelay)
                    {
                        //node can't have this slot, move on to the next slot
                        continue;
                    }
                }

                checkSlotsItr = slotItr;

                while( ((checkSlotsItr + slotSize - 1) < slotTotalPerNode) &&    //while there is room to continue looking
                       (numTxFound < totalTxRequired) &&                         //and we haven't found all the transmission slots that are required
                       !foundTakenSlot)                                          //and we haven't found a taken slot
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
                    //Note: the Nodes use slots starting at 1 (not 0) so add 1
                    resultSlot = slotItr + 1;

                    //need to fill in all the slots that this node will be using (all the way up the line)
                    while((slotItr + slotSize - 1) < totalSlots)
                    {
                        //loop through [slotSize] number of slots
                        for(uint16 writeSlot = 0; writeSlot < slotSize; ++writeSlot)
                        {
                            assert(m_slots.at(slotItr + writeSlot) == false);    //none of these slots should already be taken

                            //set the slot to true to signify it is taken
                            m_slots.at(slotItr + writeSlot) = true;
                            m_availableSlotCount--;
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
        for(NodeAddress nodeAddress : m_allNodes)
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
            for(auto networkItr = m_allNodes.rbegin(); networkItr != m_allNodes.rend(); ++networkItr)
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
                if( config.samplingMode() == WirelessTypes::samplingMode_syncBurst ||
                    config.samplingMode() == WirelessTypes::samplingMode_syncEvent ||
                    config.sampleRate() >= HIGH_SAMPLERATE ||
                    SyncSamplingFormulas::txPerSecond(nodeInfo.m_txPerGroup, nodeInfo.m_groupSize) >= 64.0f
                  )
                {
                    //set this node to optimized so we don't attempt it again, and move to the next node
                    nodeInfo.m_optimized = true;
                    continue;
                }

                //re-calculate the network values, with optimizeBandwidth set to true
                calculateNetworkValues(nodeAddress, true);

                //re-sort the network by bandwidth
                sortByBandwidth(m_allNodes);

                //find slots for all the nodes again, using their newly calculated values
                bool allNodesFoundSlots = findSlotsForNodes(m_allNodes);

                //if the network is no longer OK (slots not found for all nodes)
                if(!allNodesFoundSlots)
                {
                    //change back to not optimizing and re-calculate
                    calculateNetworkValues(nodeAddress, false);

                    //re-sort the network by bandwidth
                    sortByBandwidth(m_allNodes);

                    //find slots for all the nodes again
                    findSlotsForNodes(m_allNodes);

                    //stop and return on the first node that fails to optimize
                    //    Note: this is ok because we are working in reverse order of % bandwidth
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

                            settlingTime = WirelessTypes::settlingTime(config.filterSettlingTime(chanItr));

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
                            settlingTime = WirelessTypes::settlingTime(config.filterSettlingTime(chanItr));

                            delayResult += settlingTime + 3;
                        }
                        //channels 3 - 6
                        else if(chanItr <= 6)
                        {
                            addVoltageExtra = true;

                            //second filter (voltage)
                            settlingTime = WirelessTypes::settlingTime(config.filterSettlingTime(chanItr));

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
                            settlingTime = WirelessTypes::settlingTime(config.filterSettlingTime(chanItr));

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
            case WirelessModels::node_shmLink200:
            case WirelessModels::node_shmLink201:
            case WirelessModels::node_shmLink201_qbridge_1K:
            case WirelessModels::node_shmLink201_qbridge_348:
            case WirelessModels::node_shmLink201_hbridge_1K:
            case WirelessModels::node_shmLink201_hbridge_348:
            case WirelessModels::node_shmLink201_fullbridge:
            case WirelessModels::node_shmLink2_cust1_oldNumber:
            case WirelessModels::node_shmLink2_cust1:
            case WirelessModels::node_sgLink_herm:
            case WirelessModels::node_sgLink_herm_2600:
            case WirelessModels::node_sgLink_herm_2700:
            case WirelessModels::node_sgLink_herm_2800:
            case WirelessModels::node_sgLink_herm_2900:
            case WirelessModels::node_sgLink_rgd:
            {
                //get the sampling delay stored in EEPROM (this node uses this values as microseconds instead of milliseconds).
                uint16 delayEepromVal = static_cast<uint16>(config.sensorDelay());

                //delay (in microseconds) = (eeprom delay + 5.0) * # active channels
                float delayInMicrosec = static_cast<float>((delayEepromVal + 5.0) * config.activeChannels().count());

                //round down to nearest millisecond
                delayResult = static_cast<int>(delayInMicrosec / 1000.0);

                break;
            }

            default:
            {
                uint32 delayInMicrosec = config.sensorDelay();

                if(delayInMicrosec == WirelessNodeConfig::SENSOR_DELAY_ALWAYS_ON)
                {
                    //set to no delay
                    return 0;
                }

                //change from microseconds to milliseconds
                delayResult = static_cast<int>(delayInMicrosec / 1000.0);

                if(delayResult > 1000)    
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
        static const uint8 MAX_ATTEMPTS = 3;
        uint8 retryCount = 0;
        bool atLeastOneFailed = false;

        do
        {
            atLeastOneFailed = false;

            //go through each node in the network
            for(NodeAddress nodeAddress : m_allNodes)
            {
                SyncNetworkInfo& nodeInfo = getNodeNetworkInfo(nodeAddress);

                //only want to start nodes that haven't already been started (in previous calls to this function)
                if(!nodeInfo.m_startedSampling)
                {
                    if(m_networkBase.node_startSyncSampling(nodeInfo.m_node.protocol(m_networkBase.communicationProtocol()), nodeAddress))
                    {
                        NodeCommTimes::updateDeviceState(nodeAddress, DeviceState::deviceState_sampling);

                        //mark this node as started sampling so that we don't apply it again on successive calls to this function
                        nodeInfo.m_startedSampling = true;

                        //sleep between each node start sampling command for good measure
                        Utils::threadSleep(20);
                    }
                    else
                    {
                        //no longer throwing an exception here as we want to continue on to the next nodes
                        //and no response is not necessarily indicative of a failure, which can mess things up if the node really started
                        nodeInfo.m_startedSampling = false;

                        atLeastOneFailed = true;
                    }
                }
            }

            retryCount++;
        }
        while(atLeastOneFailed && retryCount <= MAX_ATTEMPTS);
    }

    bool SyncSamplingNetwork::inLegacyMode()
    {
        //go through each node in the network
        for(NodeAddress nodeAddress : m_allNodes)
        {
            SyncNetworkInfo& nodeInfo = getNodeNetworkInfo(nodeAddress);

            //if we find any node with v1 sync version, the network is in legacy mode
            if(nodeInfo.syncSamplingVersion() == 1)
            {
                return true;
            }
        }

        return false;
    }
    
    //TODO: possibly don't optimize nodes that already have extra bandwidth (are slow)
}