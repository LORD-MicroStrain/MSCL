/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

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

        //API Function: settings
        //    Gets the <WirelessTypes::ChannelGroupSettings> that this group supports.
        const WirelessTypes::ChannelGroupSettings& settings() const;
    };

    //API Typedef: ChannelGroups
    //    A typedef for a vector of <ChannelGroup>s.
    typedef std::vector<ChannelGroup> ChannelGroups;
}