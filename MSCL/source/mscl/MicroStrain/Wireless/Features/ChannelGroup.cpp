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
#include "ChannelGroup.h"

namespace mscl
{
	ChannelGroup::ChannelGroup()
	{
	}

	ChannelGroup::ChannelGroup(const ChannelMask& channelMask, const std::string& groupName, const SettingsMap& settings):
		m_channels(channelMask),
		m_name(groupName),
		m_settingsMap(settings)
	{
		//add all of the setting ids to a vector of settings
		for(const auto& setting : m_settingsMap)
		{
			m_settings.push_back(setting.first);
		}
	}

	const EepromLocation& ChannelGroup::getSettingEeprom(WirelessTypes::ChannelGroupSetting setting) const
	{
		try
		{
			return m_settingsMap.at(setting);
		}
		catch(std::out_of_range&)
		{
			throw Error_NotSupported("The requested setting is not supported for this ChannelGroup.");
		}
	}

	const ChannelMask& ChannelGroup::channels() const
	{
		return m_channels;
	}

	const std::string& ChannelGroup::name() const
	{
		return m_name;
	}

	const WirelessTypes::ChannelGroupSettings& ChannelGroup::settings() const
	{
		return m_settings;
	}
}