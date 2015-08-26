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
	//Class: NodeFeatures_envlinkMini
	//	Contains information on features for the ENV-Link Mini Node.
	class NodeFeatures_envlinkMini : public NodeFeatures
	{
	public:
		virtual ~NodeFeatures_envlinkMini() {};

		//Constructor: NodeFeatures_envlinkMini
		//	Creates a NodeFeatures_envlinkMini object.
		NodeFeatures_envlinkMini(const NodeInfo& info);

		//Function: samplingModes
		//	Gets a list of the <WirelessTypes::SamplingMode>s that are supported by this Node.
		virtual const WirelessTypes::SamplingModes samplingModes() const override;

		//Function: dataFormats
		//	Gets a list of the <WirelessTypes::DataFormat>s that are supported by this Node.
		virtual const WirelessTypes::DataFormats dataFormats() const override;

		//Function: sampleRates
		//	Gets a list of the <WirelessTypes::WirelessSampleRates> that are supported by this Node for the given sampling mode.
		virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode) const override;

		//Function: maxFilterSettlingTime
		//	Gets the maximum <WirelessTypes::SettlingTime> available for the given <SampleRate>.	
		virtual WirelessTypes::SettlingTime maxFilterSettlingTime(const SampleRate& rate) const override;
	};
}