/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures.h"

namespace mscl
{
	//Class: NodeFeatures_shmlink
	//	Contains information on features for the SHM-Link node. Inherits from <NodeFeatures>.
	class NodeFeatures_shmlink : public NodeFeatures
	{
	private:
		NodeFeatures_shmlink();	//disabled default constructor

	public:
		virtual ~NodeFeatures_shmlink(){};

		//Constructor: NodeFeatures_shmlink
		//	Creates a NodeFeatures_shmlink object.
		NodeFeatures_shmlink(const NodeInfo& info);

	public:
		virtual bool supportsAutoBalance(uint8 channelNumber) const final;

		virtual bool supportsFatigueConfig() const final;

		virtual bool supportsYoungsModConfig() const final;

		virtual bool supportsPoissonsRatioConfig() const final;

		virtual bool supportsFatigueRawModeConfig() const final;

		virtual bool supportsHistogramConfig() const final;

		virtual bool supportsHistogramRateConfig() const final;

		virtual uint8 numDamageAngles() const final;

		virtual uint8 numSnCurveSegments() const final;

		virtual const WirelessTypes::WirelessSampleRates histogramTransmitRates() const final;
	};
}