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
#include "stdafx.h"
#include "SyncNetworkInfo.h"
#include "Configuration/WirelessNodeConfig.h"

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
		m_maxRetxPerBurst(0),
		m_status(status_DoesNotFit),
		m_optimized(false),
		m_configApplied(false),
		m_startedSampling(false),
		m_hasPendingConfig(false)
	{
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

	void SyncNetworkInfo::setPendingConfig(const WirelessNodeConfig& config)
	{
		try
		{
			//get the samplingMode, if it is set
			WirelessTypes::SamplingMode mode = config.samplingMode();

			//if we got here, the mode was set in the config (no exception thrown)

			//the mode was set, check the mode is what we want
			if(mode != WirelessTypes::samplingMode_sync && mode != WirelessTypes::samplingMode_syncBurst)
			{
				//nodes must have their configuration be in Sync Sampling mode.
				ConfigIssues issues;
				issues.push_back(ConfigIssue(ConfigIssue::CONFIG_SAMPLING_MODE, "Configuration is not set for Synchronized Sampling mode."));
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

	void SyncNetworkInfo::clearPendingConfig()
	{
		m_hasPendingConfig = false;

		//set to a blank WirelessNodeConfig
		m_pendingConfig = WirelessNodeConfig();
	}
}