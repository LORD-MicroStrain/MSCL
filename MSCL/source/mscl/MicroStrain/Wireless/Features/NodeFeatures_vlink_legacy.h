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
#pragma once

#include "NodeFeatures.h"

namespace mscl
{
	//Class: NodeFeatures_vlink_legacy
	//	Contains information on features for the V-Link (legacy) node. Inherits from <NodeFeatures>.
	class NodeFeatures_vlink_legacy : public NodeFeatures
	{
	private:
		NodeFeatures_vlink_legacy();	//disabled default constructor

	public:
		virtual ~NodeFeatures_vlink_legacy(){};

		//Constructor: NodeFeatures_vlink_legacy
		//	Creates a NodeFeatures_vlink_legacy object.
		NodeFeatures_vlink_legacy(const NodeInfo& info);

	public:
		//Function: sampleRates
		//	Gets a list of the <WirelessTypes::WirelessSampleRate>s that are supported by this Node for the given sampling mode.
		virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode) const override;
	};
}