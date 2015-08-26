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
	//Class: NodeFeatures_iepeLink
	//	Contains information on features for the IEPE-Link.
	class NodeFeatures_iepeLink : public NodeFeatures
	{
	public:
		virtual ~NodeFeatures_iepeLink(){};

		//Constructor: NodeFeatures_iepeLink
		//	Creates a NodeFeatures_iepeLink object.
		NodeFeatures_iepeLink(const NodeInfo& info);

	public:
		//Function: defaultModes
		//	Gets a list of the <WirelessTypes::DefaultMode>s that are supported by this Node.
		virtual const WirelessTypes::DefaultModes defaultModes() const override;

		//Function: samplingModes
		//	Gets a list of the <WirelessTypes::SamplingMode>s that are supported by this Node.
		virtual const WirelessTypes::SamplingModes samplingModes() const override;

		//Function: dataFormats
		//	Gets a list of the <WirelessTypes::DataFormat>s that are supported by this Node.
		virtual const WirelessTypes::DataFormats dataFormats() const override;

		//Function: sampleRates
		//	Gets a list of the <WirelessTypes::WirelessSampleRates> that are supported by this Node for the given sampling mode.
		virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode) const override;

		//Function: maxSweepsPerBurst
		//	Gets the maximum number of sweeps per burst that can be assigned for a Burst Sync Sampling session.
		virtual uint32 maxSweepsPerBurst(WirelessTypes::DataFormat dataFormat, const ChannelMask& channels) const override;
	};
}