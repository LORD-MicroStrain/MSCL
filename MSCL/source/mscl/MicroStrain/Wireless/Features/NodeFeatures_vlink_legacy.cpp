/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "NodeFeatures_vlink_legacy.h"
#include "AvailableSampleRates.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"

namespace mscl
{
    NodeFeatures_vlink_legacy::NodeFeatures_vlink_legacy(const NodeInfo& info):
        NodeFeatures(info)
    {
        //Channels
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_fullDifferential, "Differential", 12);
        m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_fullDifferential, "Differential", 12);
        m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_fullDifferential, "Differential", 12);
        m_channels.emplace_back(4, WirelessChannel::channel_4, WirelessTypes::chType_fullDifferential, "Differential", 12);
        m_channels.emplace_back(5, WirelessChannel::channel_5, WirelessTypes::chType_singleEnded, "Single-ended", 12);
        m_channels.emplace_back(6, WirelessChannel::channel_6, WirelessTypes::chType_singleEnded, "Single-ended", 12);
        m_channels.emplace_back(7, WirelessChannel::channel_7, WirelessTypes::chType_singleEnded, "Single-ended", 12);
        m_channels.emplace_back(8, WirelessChannel::channel_8, WirelessTypes::chType_temperature, "Internal Temperature");


        //Channel Groups
        static const ChannelMask DIFFERENTIAL_1(BOOST_BINARY(00000011));    //ch1 + 2
        static const ChannelMask DIFFERENTIAL_2(BOOST_BINARY(00001100));    //ch3 + 4
        static const ChannelMask DIFF_CH1(BOOST_BINARY(00000001));    //ch1
        static const ChannelMask DIFF_CH2(BOOST_BINARY(00000010));    //ch2
        static const ChannelMask DIFF_CH3(BOOST_BINARY(00000100));    //ch3
        static const ChannelMask DIFF_CH4(BOOST_BINARY(00001000));    //ch4

        m_channelGroups.emplace_back(DIFFERENTIAL_1, "Differential",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_1}}
        );

        m_channelGroups.emplace_back(DIFFERENTIAL_2, "Differential",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_2}}
        );

        m_channelGroups.emplace_back(DIFF_CH1, "Differential",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_hardwareOffset, NodeEepromMap::HW_OFFSET_1},
                                         {WirelessTypes::chSetting_autoBalance, NodeEepromMap::HW_OFFSET_1},
                                         {WirelessTypes::chSetting_legacyShuntCal, NodeEepromMap::CH_ACTION_SLOPE_1}}
        );

        m_channelGroups.emplace_back(DIFF_CH2, "Differential",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_hardwareOffset, NodeEepromMap::HW_OFFSET_2},
                                         {WirelessTypes::chSetting_autoBalance, NodeEepromMap::HW_OFFSET_2},
                                         {WirelessTypes::chSetting_legacyShuntCal, NodeEepromMap::CH_ACTION_SLOPE_2}}
        );

        m_channelGroups.emplace_back(DIFF_CH3, "Differential",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_hardwareOffset, NodeEepromMap::HW_OFFSET_3},
                                         {WirelessTypes::chSetting_autoBalance, NodeEepromMap::HW_OFFSET_3},
                                         {WirelessTypes::chSetting_legacyShuntCal, NodeEepromMap::CH_ACTION_SLOPE_3}}
        );

        m_channelGroups.emplace_back(DIFF_CH4, "Differential",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_hardwareOffset, NodeEepromMap::HW_OFFSET_4},
                                         {WirelessTypes::chSetting_autoBalance, NodeEepromMap::HW_OFFSET_4},
                                         {WirelessTypes::chSetting_legacyShuntCal, NodeEepromMap::CH_ACTION_SLOPE_4}}
        );

        addCalCoeffChannelGroup(1, "Differential", NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
        addCalCoeffChannelGroup(2, "Differential", NodeEepromMap::CH_ACTION_SLOPE_2, NodeEepromMap::CH_ACTION_ID_2);
        addCalCoeffChannelGroup(3, "Differential", NodeEepromMap::CH_ACTION_SLOPE_3, NodeEepromMap::CH_ACTION_ID_3);
        addCalCoeffChannelGroup(4, "Differential", NodeEepromMap::CH_ACTION_SLOPE_4, NodeEepromMap::CH_ACTION_ID_4);
        addCalCoeffChannelGroup(5, "Single-ended", NodeEepromMap::CH_ACTION_SLOPE_5, NodeEepromMap::CH_ACTION_ID_5);
        addCalCoeffChannelGroup(6, "Single-ended", NodeEepromMap::CH_ACTION_SLOPE_6, NodeEepromMap::CH_ACTION_ID_6);
        addCalCoeffChannelGroup(7, "Single-ended", NodeEepromMap::CH_ACTION_SLOPE_7, NodeEepromMap::CH_ACTION_ID_7);
        addCalCoeffChannelGroup(8, "Internal Temperature", NodeEepromMap::CH_ACTION_SLOPE_8, NodeEepromMap::CH_ACTION_ID_8);
    }

    bool NodeFeatures_vlink_legacy::supportsSensorDelayConfig() const
    {
        return true;
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_vlink_legacy::sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const
    {
        //the list of sample rates varies for each sampling mode
        switch(samplingMode)
        {
        case WirelessTypes::samplingMode_nonSync:
        case WirelessTypes::samplingMode_sync:
            return AvailableSampleRates::continuous;

        case WirelessTypes::samplingMode_syncBurst:
            return AvailableSampleRates::burst;

        case WirelessTypes::samplingMode_armedDatalog:
            return AvailableSampleRates::armedDatalog;

        default:
            throw Error_NotSupported("The sampling mode is not supported by this Node");
        }
    }
}
