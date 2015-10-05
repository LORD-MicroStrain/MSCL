/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
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