/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
//PUBLIC_HEADER
#pragma once

#include <string>
#include "mscl/Types.h"
#include "mscl/Version.h"
#include "InertialTypes.h"
#include "InertialModels.h"

namespace mscl
{
	struct InertialDeviceInfo;

	//API Class: InertialNodeInfo
	//	Contains basic information about an InertialNode.
	class InertialNodeInfo
	{
	private:
		InertialNodeInfo();	//disabled default constructor

	public:
#ifndef SWIG
		//Constructor: InertialNodeInfo
		//	Creates an InertialNodeInfo object.
		//
		//Parameters:
		//	info - The <InertialDeviceInfo> containing information about the device.
		//	supportedDescriptors - The descriptor set ids that are supported by this device.
		InertialNodeInfo(const InertialDeviceInfo& info, const std::vector<uint16>& supportedDescriptors);
#endif

	private:
		//Variable: m_firmwareVersion
		//	The firmware <Version> of the InertialNode (ie. 1.1.14).
		Version m_firmwareVersion;

		//Variable: m_model
		//	The <InertialModels::NodeModel> of the InertialNode.
		InertialModels::NodeModel m_model;

		//Variable: m_modelName
		//	The model name of the InertialNode (ie. "3DM-GX3-35").
		std::string m_modelName;

		//Variable: m_modelNumber
		//	The model number of the InertialNode (ie. "6225-4220").
		std::string m_modelNumber;

		//Variable: m_serialNumber
		//	The serial number of the InertialNode (ie. "6225-01319").
		std::string m_serialNumber;

		//Variable: m_lotNumber
		//	The lot number of the InertialNode (ie. "I042Y").
		std::string m_lotNumber;

		//Variable: m_deviceOptions
		//	The device options of the InertialNode (ie. "5g, 300d/s").
		std::string m_deviceOptions;

		//Variable: m_supportedDescriptors
		//	A vector that contains all the descriptor ids (commands, data types) that the InertialNode supports.
		std::vector<uint16> m_supportedDescriptors;

	public:
		//API Function: firmwareVersion
		//	Gets the firmware <Version> of the InertialNode.
		//
		//Returns:
		//	The firmware <Version> of the InertialNode.
		Version firmwareVersion() const;

		//API Function: model
		//	Gets the <InertialModels::NodeModel> of the InertialNode.
		//
		//Returns:
		//	The <InertialModels::NodeModel> of the InertialNode.
		InertialModels::NodeModel model() const;

		//API Function: modelName
		//	Gets the model name of the InertialNode (ie. "3DM-GX3-45").
		//
		//Returns:
		//	The model name of the InertialNode.
		std::string modelName() const;

		//API Function: modelNumber
		//	Gets the model number of the InertialNode (ie. "6225-4220").
		//
		//Returns:
		//	The model number of the InertialNode.
		std::string modelNumber() const;

		//API Function: serialNumber
		//	Gets the serial number of the InertialNode (ie. "6225-01319").
		//
		//Returns:
		//	The serial number of the InertialNode.
		std::string serialNumber() const;

		//API Function: lotNumber
		//	Gets the lot number of the InertialNode (ie. "I042Y").
		//
		//Returns:
		//	The lot number of the InertialNode.
		std::string lotNumber() const;

		//API Function: deviceOptions
		//	Gets the device options of the InertialNode (ie. "5g, 300d/s").
		//
		//Returns:
		//	The device options of the InertialNode.
		std::string deviceOptions() const;

		//API Function: supportedChannelFields
		//	Gets a list of the supported channel fields for a given <InertialTypes::InertialCategory>.
		//
		//Parameters:
		//	type - The <InertialTypes::InertialCategory> to get the list of supported channels for.
		//
		//Returns:
		//	A <InertialTypes::ChannelFields> object containing the list of supported channel fields.
		InertialTypes::ChannelFields supportedChannelFields(InertialTypes::InertialCategory type) const;

		//API Function: supportsCategory
		//	Checks whether or not a given <InertialTypes::InertialCategory> is supported by the InertialNode.
		//
		//Parameters:
		//	type - The <InertialTypes::InertialCategory> to check if supported.
		bool supportsCategory(InertialTypes::InertialCategory type) const;

		//API Function: supports
		//	Checks whether or not the given <InertialTypes::Command> is supported by the InertialNode.
		//
		//Parameters:
		//	commandId - The <InertialTypes::Command> to check if supported.
		//
		//Returns:
		//	true if the <InertialFieldId::ID> is supported by the InertialNode, false otherwise.
		bool supportsCommand(InertialTypes::Command commandId) const;
	};

}