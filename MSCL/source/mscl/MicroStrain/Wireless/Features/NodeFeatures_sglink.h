/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures.h"

namespace mscl
{
	//Class: NodeFeatures_sglink
	//	Contains information on features for the SG-Link node. Inherits from <NodeFeatures>.
	class NodeFeatures_sglink : public NodeFeatures
	{
	private:
		NodeFeatures_sglink();	//disabled default constructor

	public:
		virtual ~NodeFeatures_sglink(){};

		//Constructor: NodeFeatures_sglink
		//	Creates a NodeFeatures_sglink object.
		NodeFeatures_sglink(const NodeInfo& info);

		virtual bool supportsAutoBalance(uint8 channelNumber) const final;
	};
}