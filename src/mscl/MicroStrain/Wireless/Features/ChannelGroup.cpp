/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Features/ChannelGroup.h"

namespace mscl
{
    ChannelGroup::ChannelGroup()
    {}

    ChannelGroup::ChannelGroup(const ChannelMask& channelMask, const std::string& groupName, const SettingsMap& settings) :
        m_channels(channelMask),
        m_name(groupName),
        m_settingsMap(settings)
    {
        //add all of the setting ids to a vector of settings
        for(const auto& setting : m_settingsMap)
        {
            m_settings.push_back(setting.first);
        }

        //append channel numbers to the end of the group name
        const uint8 lastChEnabled = channelMask.lastChEnabled();
        if(channelMask.count() == 1)
        {
            m_name += " (ch" + Utils::toStr(lastChEnabled) + ")";
        }
        else
        {
            //find the first channel enabled
            uint8 firstChEnabled = 0;
            for(uint8 i = 1; i <= lastChEnabled; i++)
            {
                if(channelMask.enabled(i))
                {
                    firstChEnabled = i;
                    break;
                }
            }

            if(firstChEnabled != 0)
            {
                m_name += " (ch" + Utils::toStr(firstChEnabled) + "-ch" + Utils::toStr(lastChEnabled) + ")";
            }
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

    uint16 ChannelGroup::eepromLocation(WirelessTypes::ChannelGroupSetting setting) const
    {
        return getSettingEeprom(setting).location();
    }

    const WirelessTypes::ChannelGroupSettings& ChannelGroup::settings() const
    {
        return m_settings;
    }

    bool ChannelGroup::hasSetting(WirelessTypes::ChannelGroupSetting setting) const
    {
        return m_settingsMap.find(setting) != m_settingsMap.end();
    }

    bool ChannelGroup::hasSettingAndChannel(WirelessTypes::ChannelGroupSetting setting, uint8 channelNumber) const
    {
        return hasSetting(setting) && m_channels.enabled(channelNumber);
    }
} // namespace mscl
