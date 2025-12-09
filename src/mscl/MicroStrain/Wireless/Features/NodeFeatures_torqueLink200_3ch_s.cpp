/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures_torqueLink200_3ch_s.h"

#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"

namespace mscl
{
    NodeFeatures_torqueLink200_3ch_s::NodeFeatures_torqueLink200_3ch_s(const NodeInfo& info) :
        NodeFeatures_torqueLink200_3ch(info, true)
    {
        addCalCoeffChannelGroup(1, "Differential", NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
        addCalCoeffChannelGroup(2, "Differential", NodeEepromMap::CH_ACTION_SLOPE_2, NodeEepromMap::CH_ACTION_ID_2);
        addCalCoeffChannelGroup(3, "Differential", NodeEepromMap::CH_ACTION_SLOPE_3, NodeEepromMap::CH_ACTION_ID_3);

        static const ChannelMask DIFFERENTIAL_CHS(BOOST_BINARY(00000001));  //ch1
        static const ChannelMask DIFFERENTIAL_CH2(BOOST_BINARY(00000010));  //ch2
        static const ChannelMask DIFFERENTIAL_CH3(BOOST_BINARY(00000100));  //ch3
        static const ChannelMask DIFFERENTIAL_ALL(BOOST_BINARY(00000111));  // all differential (1, 2, 3)

        m_channelGroups.emplace_back(DIFFERENTIAL_CHS, "Differential",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_1},
                                         {WirelessTypes::chSetting_autoShuntCal, NodeEepromMap::CH_ACTION_SLOPE_1}}
        );

        m_channelGroups.emplace_back(DIFFERENTIAL_CH2, "Differential",
                                    ChannelGroup::SettingsMap{
                                        { WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_2 },
                                        { WirelessTypes::chSetting_autoShuntCal, NodeEepromMap::CH_ACTION_SLOPE_2 } }
        );

        m_channelGroups.emplace_back(DIFFERENTIAL_CH3, "Differential",
                                    ChannelGroup::SettingsMap{
                                        { WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_3 },
                                        { WirelessTypes::chSetting_autoShuntCal, NodeEepromMap::CH_ACTION_SLOPE_3 } }
        );

        //Channels
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_fullDifferential, "Differential", 24);
        m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_fullDifferential, "Differential", 24);
        m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_fullDifferential, "Differential", 24);
    }

    const WirelessTypes::DerivedChannelMasks NodeFeatures_torqueLink200_3ch_s::channelsPerDerivedCategory() const
    {
        const ChannelMask ALL_CHS(BOOST_BINARY(00000111));

        const WirelessTypes::DerivedChannelMasks result = {
            { std::make_pair(WirelessTypes::derivedCategory_rms, ALL_CHS) },
            { std::make_pair(WirelessTypes::derivedCategory_peakToPeak, ALL_CHS) },
            { std::make_pair(WirelessTypes::derivedCategory_mean, ALL_CHS) }
        };

        return result;
    }

    bool NodeFeatures_torqueLink200_3ch_s::supportsPullUpResistor() const
    {
        return false;
    }

    bool NodeFeatures_torqueLink200_3ch_s::supportsDebounceFilter() const
    {
        return false;
    }

    bool NodeFeatures_torqueLink200_3ch_s::supportsExcitationVoltageConfig() const
    {
        return false;
    }

    const WirelessTypes::Voltages NodeFeatures_torqueLink200_3ch_s::excitationVoltages() const
    {
        return {};
    }
} // namespace mscl
