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