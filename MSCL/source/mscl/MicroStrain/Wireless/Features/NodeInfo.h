/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
//PUBLIC_HEADER
#pragma once

#include "mscl/Version.h"
#include "mscl/MicroStrain/Wireless/WirelessModels.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"
#include "mscl/MicroStrain/Wireless/RadioFeatures.h"

namespace mscl
{
	class WirelessNode_Impl;	//forward declarations

	//Struct: NodeInfo
	//	Holds information (read from eeprom) about a <WirelessNode>.
	struct NodeInfo
	{
	public:
#ifndef SWIG
		//Constructor: NodeInfo
		//	Creates a NodeInfo object from a <WirelessNode>.
		//
		//Parameters:
		//	node - The <WirelessNode_Impl> to get the info for.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		NodeInfo(const WirelessNode_Impl& node);
		
		//Constructor: NodeInfo
		//	Creates a NodeInfo object.
		//
		//Parameters:
		//	fw - The firmware <Version> of the Node.
		//	model - The <WirelessModels::NodeModel> of the Node.
		//	storageSize - The maximum number of bytes that can be stored to the Node.
		//	region - The <WirelessTypes::RegionCode> of the Node.
		NodeInfo(const Version& fw, WirelessModels::NodeModel model, uint64 storageSize, WirelessTypes::RegionCode region);
#endif

	private:
		NodeInfo();		//disabled default constructor

	public:
		//Variable: firmwareVersion
		//	The firmware <Version> of the node.
		Version firmwareVersion;

		//Variable: model
		//	The <WirelessModels::NodeModel> of the node.
		WirelessModels::NodeModel model;

		//Variable: dataStorageSize
		//	The maximum number of bytes that can be stored to the node.
		uint64 dataStorageSize;

		//Variable: regionCode
		//	The <WirelessTypes::RegionCode> of the node.
		WirelessTypes::RegionCode regionCode;
	};
}