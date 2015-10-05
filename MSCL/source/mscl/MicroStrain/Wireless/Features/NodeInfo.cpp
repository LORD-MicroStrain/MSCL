/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "NodeInfo.h"
#include "mscl/MicroStrain/Wireless/WirelessNode_Impl.h"

namespace mscl
{
	//read the required information from the node and store in the NodeInfo
	NodeInfo::NodeInfo(const WirelessNode_Impl& node):
		firmwareVersion(node.firmwareVersion()),
		model(node.model()),
		dataStorageSize(node.dataStorageSize()),
		regionCode(node.regionCode())
	{
	}

	NodeInfo::NodeInfo(const Version& fw, WirelessModels::NodeModel model, uint64 storageSize, WirelessTypes::RegionCode region):
		firmwareVersion(fw),
		model(model),
		dataStorageSize(storageSize),
		regionCode(region)
	{
	}
}