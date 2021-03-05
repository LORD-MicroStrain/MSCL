/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/Types.h"
#include "WirelessModels.h"
#include "WirelessNode.h"
#include "WirelessTypes.h"
#include "Configuration/WirelessNodeConfig.h"
#include "mscl/MicroStrain/Wireless/Features/ChannelGroup.h"

#include <memory>

namespace mscl
{
    //API Class: SyncNetworkInfo
    //    Contains network information for a <WirelessNode> that has been added to the Sync Sampling Network.
    class SyncNetworkInfo
    {
        friend class SyncSamplingNetwork;    //allow SyncSamplingNetwork to access private variables
        friend class SyncNodeConfig;        //allow SyncNodeConfig to access private variables

    public:
        //====================================================================================================
        //API Enum: NodeStatus
        //    The status of an individual node.
        //
        //status_OK                    = 0 - The node successfully fits in the network.
        //status_PoorCommunication    = 1 - The node failed to communicate.
        //status_DoesNotFit            = 2 - The node is out of the network, as the bandwidth does not allow it.
        //status_Contention            = 3 - The node is out of the network, as network contention does not allow it.
        //====================================================================================================
        enum NodeStatus
        {
            status_OK                    = 0,
            status_PoorCommunication    = 1,
            status_DoesNotFit            = 2,
            status_Contention            = 3
        };

    private:
        SyncNetworkInfo();    //disable default constructor

    public:
        //Constructor: SyncNetworkInfo
        //    Creates a SyncNetworkInfo object
        //    
        //Parameters:
        //    wirelessNode - The <WirelessNode> that this SyncNetworkInfo will belong to.
        SyncNetworkInfo(WirelessNode& node);

    private:
        //Variable: m_node
        //    The <WirelessNode> that this info belongs to
        WirelessNode m_node;

        //Variable: m_nodeAddress
        //    The <NodeAddress> of the Node that this info belongs to.
        NodeAddress m_nodeAddress;

        //Variable: m_model
        //    The <WirelessModels::NodeModel> of the Node that this info belongs to.
        WirelessModels::NodeModel m_model;

        //Variable: m_percentBandwidth
        //    The standard percent of bandwidth that this node takes up
        float m_percentBandwidth;

        //Variable: m_percentBandwidth_optimized
        //    The space-optimized percent of bandwidth that this node takes up
        float m_percentBandwidth_optimized;

        //Variable: m_tdmaAddress
        //    The TDMA address that was found for this node
        uint32 m_tdmaAddress;

        //Variable: m_slotSize
        //    The number of individual slots that the node takes up per transmission
        uint16 m_slotSize;

        //Variable: m_maxTdmaAddress
        //    The maximum TDMA address that can be assigned for the node
        uint32 m_maxTdmaAddress;

        //Variable: m_txPerGroup
        //    The number of transmissions per group
        uint32 m_txPerGroup;

        //Variable: m_groupSize
        //    The size of the group
        uint32 m_groupSize;

        //Variable: m_bytesPerSweep
        //  The number of bytes per data sweep.
        uint32 m_bytesPerSweep;

        //Variable: m_bytesPerBurst
        //  The number of bytes per burst (only valid if in Burst mode).
        uint32 m_bytesPerBurst;

        //Variable: m_maxBytesPerPacket
        //  The maximum number of bytes per packet.
        uint32 m_maxBytesPerPacket;

        //Variable: m_bytesPerSecond
        //  The number of bytes per second (continuous sampling).
        double m_bytesPerSecond;

        //Variable: m_maxRetxPerBurst
        //    The number of maximum retransmissions per burst (if burst)
        uint32 m_maxRetxPerBurst;

        //Variable: m_status
        //    The status of the node
        NodeStatus m_status;

        //Variable: m_syncSamplingVersion
        //     The version of the Sync Sampling formulas to use.
        uint8 m_syncSamplingVersion;

        //Variable: m_optimized
        //    Whether or not this node has attempted optimization
        bool m_optimized;

        //Variable: m_configApplied
        //    Whether or not the configuration has been applied for this node
        bool m_configApplied;

        //Variable: m_startedSampling
        //    Whether or not the Node has been send the Start Sync Sampling command.
        bool m_startedSampling;

        //Variable: m_hasPendingConfig
        //    Whether or not there is a "pending" configuration set for this Node.
        bool m_hasPendingConfig;

        //Variable: m_pendingConfig
        //    A <WirelessNodeConfig> set to be used in all sync network calculations, without actually being applied to the Node.
        WirelessNodeConfig m_pendingConfig;

    public:
        //API Function: status
        //    Gets the node's network status.
        //
        //Returns:
        //    The <NodeStatus> of the node.
        NodeStatus status() const;

        //API Function: startedSampling
        //  Checks whether a Node has successfully started sampling.
        //  Note: if this returns false, its not 100% gauranteed that the Node isn't sampling. It's possible the
        //        node was successfully started, but that the response never got to the BaseStation.
        bool startedSampling() const;

        //API Function: configurationApplied
        //    Gets whether or not the network configuration has been successfully applied to this node.
        //
        //Returns:
        //    true if the network configuration has been successfully applied, false otherwise.
        bool configurationApplied() const;

        //API Function: percentBandwidth
        //    Gets the node's individual percent of bandwidth in the network.
        //
        //Returns:
        //    The node's individual percent of bandwidth.
        float percentBandwidth() const;

        //API Function: tdmaAddress
        //    Gets the TDMA address that was found and assigned to the node.
        //
        //Returns:
        //    The TDMA address that was assigned to the node.
        uint32 tdmaAddress() const;

        //API Function: maxTdmaAddress
        //    Gets the maximum TDMA address that can be assigned to this node. (Advanced)
        //
        //Returns:
        //    The maximum TDMA address allowed for this node in its current configuration.
        uint32 maxTdmaAddress() const;

        //API Function: transmissionsPerGroup
        //    Gets the number of transmissions per group for this node. (Advanced)
        //
        //Returns:
        //    The number of transmissions per group for this node.
        uint32 transmissionPerGroup() const;

        //API Function: groupSize
        //    Gets the group size for this node. (Advanced)
        //
        //Returns:
        //    The group size for this node.
        uint32 groupSize() const;

    private:
        //Function: syncSamplingVersion
        //     The version of the Sync Sampling formulas to use.
        uint8 syncSamplingVersion() const;

        //Function: dutyCycle
        //  Gets the duty cycle currently set (for Event Driven).
        float dutyCycle() const;

        //Function: dutyCycle
        //  Takes a duty cycle percentage (0 - 1) and updates the m_txPerGroup value.
        //
        //Parameters:
        //  percent - The duty cycle percentage (0.0 - 1.0).
        void dutyCycle(float percent);

        WirelessTypes::DerivedChannelMasks supportedDerivedCategories() const;

        //Function: hasPendingConfig
        //    Gets whether or not this network info has a pending configuration set.
        //
        //Returns:
        //    true if a pending config has been set, false otherwise
        bool hasPendingConfig() const;

        //Function: setPendingConfig
        //    Sets a pending configuration for the Node in this network info.
        //    This is a configuration that is not actually applied to the Node, but
        //    should be used in all sync network calculations.
        //
        //Parameters:
        //    config - The <WirelessNodeConfig> to set for the Node.
        //
        //Exceptions:
        //    - <Error_InvalidNodeConfig>: The configuration is not set for Synchronized Sampling mode.
        void setPendingConfig(const WirelessNodeConfig& config);

        //Function: getPendingConfig
        //    Gets the current pending configuration that is set.
        //
        //Returns:
        //    The <WirelessNodeConfig> pointer that is currently set.
        const WirelessNodeConfig& getPendingConfig() const;

        //Function: channelGroups
        //  Gets the <ChannelGroups> for the Wireless Node.
        ChannelGroups channelGroups() const;
    };

}