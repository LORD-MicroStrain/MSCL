/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "SyncNetworkInfo.h"
#include "Configuration/WirelessNodeConfig.h"
#include "Features/NodeFeatures.h"
#include "mscl/Version.h"

namespace mscl
{
    SyncNetworkInfo::SyncNetworkInfo(WirelessNode& node) :
        m_node(node),
        m_nodeAddress(node.nodeAddress()),
        m_model(node.model()),
        m_percentBandwidth(0.0f),
        m_percentBandwidth_optimized(0.0f),
        m_tdmaAddress(0),
        m_slotSize(0),
        m_maxTdmaAddress(0),
        m_txPerGroup(0),
        m_groupSize(0),
        m_bytesPerSweep(0),
        m_bytesPerBurst(0),
        m_maxBytesPerPacket(0),
        m_bytesPerSecond(0.0),
        m_maxRetxPerBurst(0),
        m_status(status_DoesNotFit),
        m_syncSamplingVersion(1),
        m_optimized(false),
        m_configApplied(false),
        m_startedSampling(false),
        m_hasPendingConfig(false)
    {
        if(m_node.firmwareVersion() >= Version(10, 0))
        {
            m_syncSamplingVersion = 2;
        }
    }

    SyncNetworkInfo::NodeStatus SyncNetworkInfo::status() const
    {
        return m_status;
    }

    bool SyncNetworkInfo::configurationApplied() const
    {
        return m_configApplied;
    }

    float SyncNetworkInfo::percentBandwidth() const
    {
        return m_percentBandwidth;
    }

    uint32 SyncNetworkInfo::tdmaAddress() const
    {
        return m_tdmaAddress;
    }

    uint32 SyncNetworkInfo::maxTdmaAddress() const
    {
        return m_maxTdmaAddress;
    }

    uint32 SyncNetworkInfo::transmissionPerGroup() const
    {
        return m_txPerGroup;
    }

    uint32 SyncNetworkInfo::groupSize() const
    {
        return m_groupSize;
    }


    bool SyncNetworkInfo::hasPendingConfig() const
    {
        return m_hasPendingConfig;
    }

    uint8 SyncNetworkInfo::syncSamplingVersion() const
    {
        return m_syncSamplingVersion;
    }

    float SyncNetworkInfo::dutyCycle() const
    {
        return static_cast<float>((m_txPerGroup * m_maxBytesPerPacket) / m_bytesPerSecond);
    }

    void SyncNetworkInfo::dutyCycle(float percent)
    {
        m_txPerGroup = Utils::ceilBase2(percent * m_bytesPerSecond / m_maxBytesPerPacket);
    }

    WirelessTypes::DerivedChannelMasks SyncNetworkInfo::supportedDerivedCategories() const
    {
        return m_node.features().channelsPerDerivedCategory();
    }

    void SyncNetworkInfo::setPendingConfig(const WirelessNodeConfig& config)
    {
        try
        {
            //get the samplingMode, if it is set
            WirelessTypes::SamplingMode mode = config.samplingMode();

            //if we got here, the mode was set in the config (no exception thrown)

            //the mode was set, check the mode is what we want
            if(mode != WirelessTypes::samplingMode_sync &&
               mode != WirelessTypes::samplingMode_syncBurst &&
               mode != WirelessTypes::samplingMode_syncEvent)
            {
                //nodes must have their configuration be in Sync Sampling mode.
                ConfigIssues issues;
                issues.push_back(ConfigIssue(ConfigIssue::CONFIG_SAMPLING_MODE, "Pending configuration is not set for Synchronized Sampling mode."));
                throw Error_InvalidNodeConfig(issues, m_nodeAddress);
            }
        }
        catch(Error_NoData&)
        { 
        }

        //copy the config into the pending config
        m_pendingConfig = config;

        m_hasPendingConfig = true;
    }

    const WirelessNodeConfig& SyncNetworkInfo::getPendingConfig() const
    {
        //return the pending configuration
        return m_pendingConfig;
    }

    ChannelGroups SyncNetworkInfo::channelGroups() const
    {
        return m_node.features().channelGroups();
    }
}