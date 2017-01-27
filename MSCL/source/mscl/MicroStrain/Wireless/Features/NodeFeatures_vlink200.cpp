/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

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
        NodeFeatures(info)
    {
        //Channels
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_fullDifferential);     //full diff
        m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_fullDifferential);     //full diff
        m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_fullDifferential);     //full diff
        m_channels.emplace_back(4, WirelessChannel::channel_4, WirelessTypes::chType_fullDifferential);     //full diff
        m_channels.emplace_back(5, WirelessChannel::channel_5, WirelessTypes::chType_singleEnded);          //single ended
        m_channels.emplace_back(6, WirelessChannel::channel_6, WirelessTypes::chType_singleEnded);          //single ended
        m_channels.emplace_back(7, WirelessChannel::channel_7, WirelessTypes::chType_singleEnded);          //single ended
        m_channels.emplace_back(8, WirelessChannel::channel_8, WirelessTypes::chType_singleEnded);          //single ended


        //Channel Groups
        static const ChannelMask DIFFERENTIAL_CH1(BOOST_BINARY(00000001));    //ch1
        static const ChannelMask DIFFERENTIAL_CH2(BOOST_BINARY(00000010));    //ch2
        static const ChannelMask DIFFERENTIAL_CH3(BOOST_BINARY(00000100));    //ch3
        static const ChannelMask DIFFERENTIAL_CH4(BOOST_BINARY(00001000));    //ch4
        static const ChannelMask SINGLEENDED_CH5(BOOST_BINARY(00010000));    //ch5
        static const ChannelMask SINGLEENDED_CH6(BOOST_BINARY(00100000));    //ch6
        static const ChannelMask SINGLEENDED_CH7(BOOST_BINARY(01000000));    //ch7
        static const ChannelMask SINGLEENDED_CH8(BOOST_BINARY(10000000));    //ch8

        m_channelGroups.emplace_back(DIFFERENTIAL_CH1, "Differential Channel 1",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_1},
                                         {WirelessTypes::chSetting_hardwareOffset, NodeEepromMap::HW_OFFSET_1},
                                         {WirelessTypes::chSetting_autoBalance, NodeEepromMap::HW_OFFSET_1},
                                         {WirelessTypes::chSetting_autoShuntCal, NodeEepromMap::CH_ACTION_SLOPE_1},
                                         {WirelessTypes::chSetting_antiAliasingFilter, NodeEepromMap::ANTI_ALIASING_FILTER_1}}
        );

        m_channelGroups.emplace_back(DIFFERENTIAL_CH2, "Differential Channel 2",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_2},
                                         {WirelessTypes::chSetting_hardwareOffset, NodeEepromMap::HW_OFFSET_2},
                                         {WirelessTypes::chSetting_autoBalance, NodeEepromMap::HW_OFFSET_2},
                                         {WirelessTypes::chSetting_autoShuntCal, NodeEepromMap::CH_ACTION_SLOPE_2},
                                         {WirelessTypes::chSetting_antiAliasingFilter, NodeEepromMap::ANTI_ALIASING_FILTER_2}}
        );

        m_channelGroups.emplace_back(DIFFERENTIAL_CH3, "Differential Channel 3",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_3},
                                         {WirelessTypes::chSetting_hardwareOffset, NodeEepromMap::HW_OFFSET_3},
                                         {WirelessTypes::chSetting_autoBalance, NodeEepromMap::HW_OFFSET_3},
                                         {WirelessTypes::chSetting_autoShuntCal, NodeEepromMap::CH_ACTION_SLOPE_3},
                                         {WirelessTypes::chSetting_antiAliasingFilter, NodeEepromMap::ANTI_ALIASING_FILTER_3}}
        );

        m_channelGroups.emplace_back(DIFFERENTIAL_CH4, "Differential Channel 4",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_4},
                                         {WirelessTypes::chSetting_hardwareOffset, NodeEepromMap::HW_OFFSET_4},
                                         {WirelessTypes::chSetting_autoBalance, NodeEepromMap::HW_OFFSET_4},
                                         {WirelessTypes::chSetting_autoShuntCal, NodeEepromMap::CH_ACTION_SLOPE_4},
                                         {WirelessTypes::chSetting_antiAliasingFilter, NodeEepromMap::ANTI_ALIASING_FILTER_4}}
        );

        m_channelGroups.emplace_back(SINGLEENDED_CH5, "Single Ended Channel 5",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_5}}
        );

        m_channelGroups.emplace_back(SINGLEENDED_CH6, "Single Ended Channel 6",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_6}}
        );

        m_channelGroups.emplace_back(SINGLEENDED_CH7, "Single Ended Channel 7",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_7}}
        );

        m_channelGroups.emplace_back(SINGLEENDED_CH8, "Single Ended Channel 8",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_8}}
        );

        addCalCoeffChannelGroup(1, NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
        addCalCoeffChannelGroup(2, NodeEepromMap::CH_ACTION_SLOPE_2, NodeEepromMap::CH_ACTION_ID_2);
        addCalCoeffChannelGroup(3, NodeEepromMap::CH_ACTION_SLOPE_3, NodeEepromMap::CH_ACTION_ID_3);
        addCalCoeffChannelGroup(4, NodeEepromMap::CH_ACTION_SLOPE_4, NodeEepromMap::CH_ACTION_ID_4);
        addCalCoeffChannelGroup(5, NodeEepromMap::CH_ACTION_SLOPE_5, NodeEepromMap::CH_ACTION_ID_5);
        addCalCoeffChannelGroup(6, NodeEepromMap::CH_ACTION_SLOPE_6, NodeEepromMap::CH_ACTION_ID_6);
        addCalCoeffChannelGroup(7, NodeEepromMap::CH_ACTION_SLOPE_7, NodeEepromMap::CH_ACTION_ID_7);
        addCalCoeffChannelGroup(8, NodeEepromMap::CH_ACTION_SLOPE_8, NodeEepromMap::CH_ACTION_ID_8);
    }

    bool NodeFeatures_vlink200::supportsSensorDelayConfig() const
    {
        return true;
    }

    const WirelessTypes::TransmitPowers NodeFeatures_vlink200::transmitPowers() const
    {
        if(m_nodeInfo.regionCode() == WirelessTypes::region_japan)
        {
            WirelessTypes::TransmitPowers result;
            result.push_back(WirelessTypes::power_16dBm);
            result.push_back(WirelessTypes::power_10dBm);
            result.push_back(WirelessTypes::power_5dBm);
            return result;
        }
        else
        {
            return NodeFeatures::transmitPowers();
        }
    }

    const WirelessTypes::DataFormats NodeFeatures_vlink200::dataFormats() const
    {
        //build and return the data formats that are supported
        WirelessTypes::DataFormats result;
        result.push_back(WirelessTypes::dataFormat_raw_uint16);
        result.push_back(WirelessTypes::dataFormat_raw_uint24);
        result.push_back(WirelessTypes::dataFormat_cal_float);
        return result;
    }

    const WirelessTypes::SamplingModes NodeFeatures_vlink200::samplingModes() const
    {
        //build and return the sampling modes that are supported
        WirelessTypes::SamplingModes result;

        result.push_back(WirelessTypes::samplingMode_sync);
        result.push_back(WirelessTypes::samplingMode_syncBurst);
        result.push_back(WirelessTypes::samplingMode_nonSync);
        result.push_back(WirelessTypes::samplingMode_syncEvent);

        return result;
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_vlink200::sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod) const
    {
        //the list of sample rates varies for each sampling mode
        switch(samplingMode)
        {
        case WirelessTypes::samplingMode_nonSync:
            if(dataCollectionMethod == WirelessTypes::collectionMethod_logOnly)
            {
                return AvailableSampleRates::continuous_log_gen2;
            }
            else
            {
                return AvailableSampleRates::continuous_nonSync_gen2;
            }

        case WirelessTypes::samplingMode_sync:
            if(dataCollectionMethod == WirelessTypes::collectionMethod_logOnly) 
            {
                return AvailableSampleRates::continuous_log_gen2;
            }
            else
            {
                return AvailableSampleRates::continuous_sync_gen2;
            }

        case WirelessTypes::samplingMode_syncBurst:
        case WirelessTypes::samplingMode_syncEvent:
            return AvailableSampleRates::burst_gen2;

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

    const WirelessTypes::StorageLimitModes NodeFeatures_vlink200::storageLimitModes() const
    {
        WirelessTypes::StorageLimitModes modes;
        modes.push_back(WirelessTypes::storageLimit_stop);
        modes.push_back(WirelessTypes::storageLimit_overwrite);
        return modes;
    }
}