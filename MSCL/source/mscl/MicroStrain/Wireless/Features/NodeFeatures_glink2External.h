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
	//Class: NodeFeatures_glink2External
	//	Contains information on features for the G-Link 2 (External Accel) nodes.
	class NodeFeatures_glink2External : public NodeFeatures
	{
	public:
		virtual ~NodeFeatures_glink2External(){};

		//Constructor: NodeFeatures_glink2External
		//	Creates a NodeFeatures_glink2External object.
		NodeFeatures_glink2External(const NodeInfo& info);

	public:
		//Function: sampleRates
		//	Gets a list of the <WirelessTypes::WirelessSampleRates> that are supported by this Node for the given sampling mode.
		virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode) const override;
	};
}