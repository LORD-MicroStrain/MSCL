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
//PUBLIC_HEADER
#pragma once

namespace mscl
{
	//API Class: InertialModels
	//	Contains the models of Inertial hardware.
	class InertialModels
	{
	public:
		//=========================================================================
		//API Enum: NodeModel
		//	The model numbers for each of the Inertial Nodes.
		//
		//	node_3dm			= 6201 - 3DM
		//	node_fasA			= 6207 - FAS-A
		//	node_3dm_gx2		= 6215 - 3DM-GX2
		//	node_3dm_dh3		= 6219 - 3DM-DH3
		//	node_3dm_gx3_15		= 6227 - 3DM-GX3-15
		//	node_3dm_gx3_25		= 6223 - 3DM-GX3-25
		//	node_3dm_gx3_35		= 6225 - 3DM-GX3-35
		//	node_3dm_gx3_45		= 6228 - 3DM-GX3-45
		//	node_3dm_rq1_45		= 6232 - 3DM-RQ1-45
		//	node_3dm_gx4_15		= 6233 - 3DM-GX4-15
		//	node_3dm_gx4_25		= 6234 - 3DM-GX4-25
		//	node_3dm_gx4_45		= 6236 - 3DM-GX4-45
		//=========================================================================
		enum NodeModel
		{
			node_3dm			= 6201,		//3DM
			node_fasA			= 6207,		//FAS-A
			node_3dm_gx2		= 6215,		//3DM-GX2
			node_3dm_dh3		= 6219,		//3DM-DH3
			node_3dm_gx3_15		= 6227,		//3DM-GX3-15
			node_3dm_gx3_25		= 6223,		//3DM-GX3-25
			node_3dm_gx3_35		= 6225,		//3DM-GX3-35
			node_3dm_gx3_45		= 6228,		//3DM-GX3-45
			node_3dm_rq1_45		= 6232,		//3DM-RQ1-45
			node_3dm_gx4_15		= 6233,		//3DM-GX4-15
			node_3dm_gx4_25		= 6234,		//3DM-GX4-25
			node_3dm_gx4_45		= 6236		//3DM-GX4-45
		};

#ifndef SWIG
		
		//Function: nodeFromModelString
		//	Converts the model number string received from an InertialNode to a <NodeModel> enum.
		//
		//Parameters:
		//	modelNumberString - The model number string recieved in an InertialNode's Get Device Info packet.
		//
		//Returns:
		//	A <NodeModel> enum created from the string.
		static NodeModel nodeFromModelString(const std::string& modelNumberString);
#endif
	};
}