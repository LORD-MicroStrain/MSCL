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
	//Class: NodeFeatures_sglinkrgd
	//	Contains information on features for the SG-Link node. Inherits from <NodeFeatures>.
	class NodeFeatures_sglinkrgd : public NodeFeatures
	{
	private:
		NodeFeatures_sglinkrgd();	//disabled default constructor

	public:
		virtual ~NodeFeatures_sglinkrgd(){};

		//Constructor: NodeFeatures_sglinkrgd
		//	Creates a NodeFeatures_sglinkrgd object.
		NodeFeatures_sglinkrgd(const NodeInfo& info);
	};
}