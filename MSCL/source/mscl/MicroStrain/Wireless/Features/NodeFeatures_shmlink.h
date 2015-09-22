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