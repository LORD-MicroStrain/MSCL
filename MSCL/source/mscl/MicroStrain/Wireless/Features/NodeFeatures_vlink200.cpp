/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "NodeFeatures_vlink200.h"
#include "AvailableSampleRates.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"

namespace mscl
{
    NodeFeatures_vlink200::NodeFeatures_vlink200(const NodeInfo& info):
        NodeFeatures_200series(info)
    {
        //Channels
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_fullDifferential, "Differential", 18);
        m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_fullDifferential, "Differential", 18);
        m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_fullDifferential, "Differential", 18);
        m_channels.emplace_back(4, WirelessChannel::channel_4, WirelessTypes::chType_fullDifferential, "Differential", 18);
        m_channels.emplace_back(5, WirelessChannel::channel_5, WirelessTypes::chType_singleEnded, "Single-ended", 18);
        m_channels.emplace_back(6, WirelessChannel::channel_6, WirelessTypes::chType_singleEnded, "Single-ended", 18);
        m_channels.emplace_back(7, WirelessChannel::channel_7, WirelessTypes::chType_singleEnded, "Single-ended", 18);
        m_channels.emplace_back(8, WirelessChannel::channel_8, WirelessTypes::chType_singleEnded, "Single-ended", 18);


        //Channel Groups
        static const ChannelMask DIFFERENTIAL_CH1(BOOST_BINARY(00000001));    //ch1
        static const ChannelMask DIFFERENTIAL_CH2(BOOST_BINARY(00000010));    //ch2
        static const ChannelMask DIFFERENTIAL_CH3(BOOST_BINARY(00000100));    //ch3
        static const ChannelMask DIFFERENTIAL_CH4(BOOST_BINARY(00001000));    //ch4
        static const ChannelMask SINGLEENDED_CH5(BOOST_BINARY(00010000));    //ch5
        static const ChannelMask SINGLEENDED_CH6(BOOST_BINARY(00100000));    //ch6
        static const ChannelMask SINGLEENDED_CH7(BOOST_BINARY(01000000));    //ch7
        static const ChannelMask SINGLEENDED_CH8(BOOST_BINARY(10000000));    //ch8

        m_channelGroups.emplace_back(DIFFERENTIAL_CH1, "Differential",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_1},
                                         {WirelessTypes::chSetting_hardwareOffset, NodeEepromMap::HW_OFFSET_1},
                                         {WirelessTypes::chSetting_autoBalance, NodeEepromMap::HW_OFFSET_1},
                                         {WirelessTypes::chSetting_autoShuntCal, NodeEepromMap::CH_ACTION_SLOPE_1},
                                         {WirelessTypes::chSetting_antiAliasingFilter, NodeEepromMap::ANTI_ALIASING_FILTER_1}}
        );

        m_channelGroups.emplace_back(DIFFERENTIAL_CH2, "Differential",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_2},
                                         {WirelessTypes::chSetting_hardwareOffset, NodeEepromMap::HW_OFFSET_2},
                                         {WirelessTypes::chSetting_autoBalance, NodeEepromMap::HW_OFFSET_2},
                                         {WirelessTypes::chSetting_autoShuntCal, NodeEepromMap::CH_ACTION_SLOPE_2},
                                         {WirelessTypes::chSetting_antiAliasingFilter, NodeEepromMap::ANTI_ALIASING_FILTER_2}}
        );

        m_channelGroups.emplace_back(DIFFERENTIAL_CH3, "Differential",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_3},
                                         {WirelessTypes::chSetting_hardwareOffset, NodeEepromMap::HW_OFFSET_3},
                                         {WirelessTypes::chSetting_autoBalance, NodeEepromMap::HW_OFFSET_3},
                                         {WirelessTypes::chSetting_autoShuntCal, NodeEepromMap::CH_ACTION_SLOPE_3},
                                         {WirelessTypes::chSetting_antiAliasingFilter, NodeEepromMap::ANTI_ALIASING_FILTER_3}}
        );

        m_channelGroups.emplace_back(DIFFERENTIAL_CH4, "Differential",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_4},
                                         {WirelessTypes::chSetting_hardwareOffset, NodeEepromMap::HW_OFFSET_4},
                                         {WirelessTypes::chSetting_autoBalance, NodeEepromMap::HW_OFFSET_4},
                                         {WirelessTypes::chSetting_autoShuntCal, NodeEepromMap::CH_ACTION_SLOPE_4},
                                         {WirelessTypes::chSetting_antiAliasingFilter, NodeEepromMap::ANTI_ALIASING_FILTER_4}}
        );

        m_channelGroups.emplace_back(SINGLEENDED_CH5, "Single-ended",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_5}}
        );

        m_channelGroups.emplace_back(SINGLEENDED_CH6, "Single-ended",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_6}}
        );

        m_channelGroups.emplace_back(SINGLEENDED_CH7, "Single-ended",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_7}}
        );

        m_channelGroups.emplace_back(SINGLEENDED_CH8, "Single-ended",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_8}}
        );

        addCalCoeffChannelGroup(1, "Differential", NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
        addCalCoeffChannelGroup(2, "Differential", NodeEepromMap::CH_ACTION_SLOPE_2, NodeEepromMap::CH_ACTION_ID_2);
        addCalCoeffChannelGroup(3, "Differential", NodeEepromMap::CH_ACTION_SLOPE_3, NodeEepromMap::CH_ACTION_ID_3);
        addCalCoeffChannelGroup(4, "Differential", NodeEepromMap::CH_ACTION_SLOPE_4, NodeEepromMap::CH_ACTION_ID_4);
        addCalCoeffChannelGroup(5, "Single-ended", NodeEepromMap::CH_ACTION_SLOPE_5, NodeEepromMap::CH_ACTION_ID_5);
        addCalCoeffChannelGroup(6, "Single-ended", NodeEepromMap::CH_ACTION_SLOPE_6, NodeEepromMap::CH_ACTION_ID_6);
        addCalCoeffChannelGroup(7, "Single-ended", NodeEepromMap::CH_ACTION_SLOPE_7, NodeEepromMap::CH_ACTION_ID_7);
        addCalCoeffChannelGroup(8, "Single-ended", NodeEepromMap::CH_ACTION_SLOPE_8, NodeEepromMap::CH_ACTION_ID_8);
    }

    bool NodeFeatures_vlink200::supportsSensorDelayConfig() const
    {
        return true;
    }

    bool NodeFeatures_vlink200::supportsPoll() const
    {
        static const Version MIN_POLL_FW(12, 45139);

        return (m_nodeInfo.firmwareVersion() >= MIN_POLL_FW);
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_vlink200::sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const
    {
        //the list of sample rates varies for each sampling mode
        switch(samplingMode)
        {
        case WirelessTypes::samplingMode_nonSync:
            if(dataCollectionMethod == WirelessTypes::collectionMethod_logOnly)
            {
                return AvailableSampleRates::continuous_log_vlink200;
            }
            else
            {
                return AvailableSampleRates::continuous_nonSync_vlink200;
            }

        case WirelessTypes::samplingMode_sync:
            if(dataCollectionMethod == WirelessTypes::collectionMethod_logOnly) 
            {
                return AvailableSampleRates::continuous_log_vlink200;
            }
            else
            {
                return AvailableSampleRates::continuous_sync_vlink200;
            }

        case WirelessTypes::samplingMode_syncBurst:
        case WirelessTypes::samplingMode_syncEvent:
            return AvailableSampleRates::burst_vlink200;

        default:
            throw Error_NotSupported("The sampling mode is not supported by this Node");
        }
    }

    const WirelessTypes::Filters NodeFeatures_vlink200::antiAliasingFilters() const
    {
        static const WirelessTypes::Filters filters = {
            {WirelessTypes::filter_4000hz},
            {WirelessTypes::filter_2000hz},
            {WirelessTypes::filter_1024hz},
            {WirelessTypes::filter_500hz},
            {WirelessTypes::filter_256hz},
            {WirelessTypes::filter_128hz}
        };
        return filters;
    }
}