/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "ConfigIssue.h"

namespace mscl
{
    ConfigIssue::ConfigIssue():
        m_optionId(ConfigIssue::CONFIG_SAMPLING_MODE),
        m_description(""),
        m_isChannelGroupIssue(false)
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