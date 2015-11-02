/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "InertialNodeFeatures.h"

namespace mscl
{
	//Class: InertialNodeFeatures_3dm
	//	Contains information on features for the 3DM Node. Inherits from <InertialNodeFeatures>.
	class InertialNodeFeatures_3dm: public InertialNodeFeatures
	{
	public:
		virtual ~InertialNodeFeatures_3dm() {};

		//Constructor: InertialNodeFeatures_3dm
		//	Creates a InertialNodeFeatures_3dm object.
		InertialNodeFeatures_3dm(const InertialNodeInfo& info);
	};
}