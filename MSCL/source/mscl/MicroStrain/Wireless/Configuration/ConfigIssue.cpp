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
#include "ConfigIssue.h"

namespace mscl
{
	ConfigIssue::ConfigIssue():
		m_optionId(ConfigIssue::CONFIG_SAMPLING_MODE),
		m_description("")
	{
	}

	ConfigIssue::ConfigIssue(ConfigIssue::ConfigOption optionId, const std::string& description):
		m_optionId(optionId),
		m_description(description),
		m_isChannelGroupIssue(false)
	{
	}

	ConfigIssue::ConfigIssue(ConfigIssue::ConfigOption optionId, const std::string& description, const ChannelMask& mask):
		m_optionId(optionId),
		m_description(description),
		m_isChannelGroupIssue(true),
		m_channelMask(mask)
	{
	}

	ConfigIssue::ConfigOption ConfigIssue::id() const
	{
		return m_optionId;
	}

	const std::string& ConfigIssue::description() const 
	{
		return m_description;
	}

	bool ConfigIssue::isChannelGroupIssue() const
	{
		return m_isChannelGroupIssue;
	}

	const ChannelMask& ConfigIssue::channelMask() const
	{
		return m_channelMask;
	}
}