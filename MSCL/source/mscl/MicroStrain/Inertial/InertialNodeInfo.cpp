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
#include "stdafx.h"
#include "InertialNodeInfo.h"

#include "InertialNode.h"
#include "Commands/GetDeviceInfo.h"
#include "mscl/Utils.h"

#include <string>

namespace mscl
{
	InertialNodeInfo::InertialNodeInfo(const InertialDeviceInfo& info, const std::vector<uint16>& supportedDescriptors) :
		m_firmwareVersion(info.fwVersion),
		m_model(InertialModels::nodeFromModelString(info.modelNumber)),
		m_modelName(info.modelName),
		m_modelNumber(info.modelNumber),
		m_serialNumber(info.serialNumber),
		m_lotNumber(info.lotNumber),
		m_deviceOptions(info.deviceOptions),
		m_supportedDescriptors(supportedDescriptors)
	{
	}

	Version InertialNodeInfo::firmwareVersion() const
	{
		return m_firmwareVersion;
	}

	InertialModels::NodeModel InertialNodeInfo::model() const
	{
		return m_model;
	}

	std::string InertialNodeInfo::modelName() const
	{
		return m_modelName;
	}

	std::string InertialNodeInfo::modelNumber() const
	{
		return m_modelNumber;
	}

	std::string InertialNodeInfo::serialNumber() const
	{
		return m_serialNumber;
	}

	std::string InertialNodeInfo::lotNumber() const
	{
		return m_lotNumber;
	}

	std::string InertialNodeInfo::deviceOptions() const
	{
		return m_deviceOptions;
	}

	InertialTypes::ChannelFields InertialNodeInfo::supportedChannelFields(InertialTypes::InertialCategory type) const
	{
		InertialTypes::ChannelFields result;

		//loop over all the descriptors we have
		for(auto desc : m_supportedDescriptors)
		{
			//if ths MSB of the descriptor matches the InertialCategory being requested
			if(Utils::msb(static_cast<uint16>(desc)) == static_cast<uint16>(type))
			{
				//cast the descriptor to a ChannelField, and add it to the result container
				result.push_back(static_cast<InertialTypes::ChannelField>(desc));
			}
		}

		return result;
	}

	bool InertialNodeInfo::supportsCategory(InertialTypes::InertialCategory type) const
	{
		//loop over all the descriptors we have
		for(auto desc : m_supportedDescriptors)
		{
			//if ths MSB of the descriptor matches the InertialCategory being requested
			if(Utils::msb(static_cast<uint16>(desc)) == static_cast<uint16>(type))
			{
				//the device supports this category
				return true;
			}
		}

		//no descriptors found that match the requested category
		return false;
	}

	bool InertialNodeInfo::supportsCommand(InertialTypes::Command commandId) const
	{
		return (std::find(m_supportedDescriptors.begin(), m_supportedDescriptors.end(), static_cast<uint16>(commandId)) != m_supportedDescriptors.end());
	}
}