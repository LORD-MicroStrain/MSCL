/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures.h"

namespace mscl
{
	//Class: NodeFeatures_vlink
	//	Contains information on features for the V-Link node. Inherits from <NodeFeatures>.
	class NodeFeatures_vlink : public NodeFeatures
	{
	private:
		NodeFeatures_vlink();	//disabled default constructor

	public:
		virtual ~NodeFeatures_vlink(){};

		//Constructor: NodeFeatures_vlink
		//	Creates a NodeFeatures_vlink object.
		NodeFeatures_vlink(const NodeInfo& info);

	public:
		//Function: sampleRates
		//	Gets a list of the <WirelessTypes::WirelessSampleRate>s that are supported by this Node for the given sampling mode.
		virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode) const override;

		//Function: maxSampleRate
		//	Gets the maximum <SampleRate> value that is supported by this Node with the given <SamplingMode> and <ChannelMask>.
		virtual WirelessTypes::WirelessSampleRate maxSampleRate(WirelessTypes::SamplingMode samplingMode, const ChannelMask& channels) const override;
	};
}