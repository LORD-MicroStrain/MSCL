/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include <map>
#include <vector>

#include "mscl/MicroStrain/Wireless/ChannelMask.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"
#include "mscl/MicroStrain/Wireless/Configuration/EepromLocation.h"

namespace mscl
{    
    //API Class: ChannelGroup
    //    Represents a group of channels that have combined settings.
    class ChannelGroup
    {
        friend class NodeFeatures;

    public:
        //Default Constructor: ChannelGroup
        //    Creates a default constructed ChannelGroup object.
        ChannelGroup();

#ifndef SWIG

        typedef std::map<WirelessTypes::ChannelGroupSetting, EepromLocation> SettingsMap;

        //Constructor: ChannelGroup
        //    Creates a ChannelGroup object.
        //
        //Parameters:
        //    channelMask - The <ChannelMask> representing which channels are part of this group.
        //    groupName - The name of the group.
        //    settings - A map of <WirelessTypes::ChannelGroupSettings> to <EepromLocation>s.
        ChannelGroup(const ChannelMask& channelMask, const std::string& groupName, const SettingsMap& settings);
#endif

    private:
        //Variable: m_channels
        //    The <ChannelMask> representing which channels are part of this group.
        ChannelMask m_channels;

        //Variable: m_name
        //    The name of the group.
        std::string m_name;

        //Variable: m_options
        //    The <WirelessTypes::ChannelGroupSettings> that this group supports.
        WirelessTypes::ChannelGroupSettings m_settings;

        //Variable: m_settingsMap
        //    A map of <WirelessTypes::ChannelGroupSetting> to <EepromLocation> pairs.
        SettingsMap m_settingsMap;

    protected:
        //Function: getSettingEeprom
        //    Gets the <EepromLocation> for the given <Setting>.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The setting is not supported by this Channel Group.
        const EepromLocation& getSettingEeprom(WirelessTypes::ChannelGroupSetting setting) const;

    public:
        //API Function: channels
        //    Gets the <ChannelMask> representing which channels are part of this group.
        const ChannelMask& channels() const;

        //API Function: name
        //    Gets the name of the channel group.
        const std::string& name() const;

        //API Function: eepromLocation
        //  Gets the eeprom location that the ChannelGroup uses for a specified setting.
        //
        //Parameters:
        //  setting - The <WirelessTypes::ChannelGroupSetting> to find the eeprom location for.
        //
        //Returns:
        //  The eeprom location for the specified setting.
        //
        //Exceptions:
        //  - <Error_NotSupported>: The requested <WirelessTypes::ChannelGroupSetting> is not supported by this ChannelGroup.
        uint16 eepromLocation(WirelessTypes::ChannelGroupSetting setting) const;

        //API Function: settings
        //    Gets the <WirelessTypes::ChannelGroupSettings> that this group supports.
        //
        //Returns:
        //  The <WirelessTypes::ChannelGroupSettings> for this group.
        const WirelessTypes::ChannelGroupSettings& settings() const;

        //API Function: hasSetting
        //  Helper function for quick check if setting is present in this channel group.
        //
        //Parameters:
        //  setting - The <WirelessTypes::ChannelGroupSetting> to look for.
        //
        //Returns:
        //  true if the ChannelGroup has the given setting, false otherwise.
        bool hasSetting(WirelessTypes::ChannelGroupSetting setting) const;

        //API Function: hasChannel
        //  Helper function to check if this channel group has a specific setting and channel included in it.
        //
        //Parameters:
        //  setting - The <WirelessTypes::ChannelGroupSetting> to look for.
        //  channelNumber - The channel number (ch1 = 1, ch16 = 16) to check for.
        //
        //Returns:
        //  true if the ChannelGroup has the given setting and channel, false otherwise.
        bool hasSettingAndChannel(WirelessTypes::ChannelGroupSetting setting, uint8 channelNumber) const;
    };

    //API Typedef: ChannelGroups
    //    A typedef for a vector of <ChannelGroup>s.
    typedef std::vector<ChannelGroup> ChannelGroups;
}