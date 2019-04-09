/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "NodeFeatures_shmlink201FullBridge.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "AvailableSampleRates.h"
#include "mscl/Utils.h"

namespace mscl
{
    NodeFeatures_shmlink201FullBridge::NodeFeatures_shmlink201FullBridge(const NodeInfo& info):
        NodeFeatures_200series(info)
    {
        static const ChannelMask DIFF_CH1(BOOST_BINARY(00000001));  //ch1
        static const ChannelMask DIFF_CH2(BOOST_BINARY(00000010));  //ch2
        static const ChannelMask DIFF_CH3(BOOST_BINARY(00000100));  //ch3
        static const ChannelMask ALL_CHS(BOOST_BINARY(00000111));   //ch1 - ch3

        m_channelGroups.emplace_back(ALL_CHS, "Differential",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_lowPassFilter, NodeEepromMap::LOW_PASS_FILTER_1}}
        );

        m_channelGroups.emplace_back(DIFF_CH1, "Differential",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_gaugeFactor, NodeEepromMap::GAUGE_FACTOR_1}}
        );

        m_channelGroups.emplace_back(DIFF_CH2, "Differential",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_gaugeFactor, NodeEepromMap::GAUGE_FACTOR_2}}
        );

        m_channelGroups.emplace_back(DIFF_CH3, "Differential",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_gaugeFactor, NodeEepromMap::GAUGE_FACTOR_3}}
        );

        addCalCoeffChannelGroup(1, "Differential", NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
        addCalCoeffChannelGroup(2, "Differential", NodeEepromMap::CH_ACTION_SLOPE_2, NodeEepromMap::CH_ACTION_ID_2);
        addCalCoeffChannelGroup(3, "Differential", NodeEepromMap::CH_ACTION_SLOPE_3, NodeEepromMap::CH_ACTION_ID_3);

        //Channels
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_fullDifferential, "Differential", 24);
        m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_fullDifferential, "Differential", 24);
        m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_fullDifferential, "Differential", 24);
        m_channels.emplace_back(5, WirelessChannel::channel_5, WirelessTypes::chType_acceleration, "Acceleration X", 24);
        m_channels.emplace_back(6, WirelessChannel::channel_6, WirelessTypes::chType_acceleration, "Acceleration Y", 24);
        m_channels.emplace_back(7, WirelessChannel::channel_7, WirelessTypes::chType_acceleration, "Acceleration Z", 24);
    }
    
    const WirelessTypes::DataCollectionMethods NodeFeatures_shmlink201FullBridge::dataCollectionMethods() const
    {
        //build and return the data collection methods that are supported
        WirelessTypes::DataCollectionMethods result;
        result.push_back(WirelessTypes::collectionMethod_transmitOnly);
        return result;
    }

    const WirelessTypes::DataFormats NodeFeatures_shmlink201FullBridge::dataFormats() const
    {
        //build and return the data formats that are supported
        WirelessTypes::DataFormats result;
        result.push_back(WirelessTypes::dataFormat_cal_float);
        return result;
    }

    const WirelessTypes::Filters NodeFeatures_shmlink201FullBridge::lowPassFilters() const
    {
        static const WirelessTypes::Filters filters = {
            {WirelessTypes::filter_5222hz},
            {WirelessTypes::filter_4416hz},
            {WirelessTypes::filter_2208hz},
            {WirelessTypes::filter_1104hz},
            {WirelessTypes::filter_552hz}
        };
        return filters;
    }

    const WirelessTypes::SamplingModes NodeFeatures_shmlink201FullBridge::samplingModes() const
    {
        //build and return the sampling modes that are supported
        WirelessTypes::SamplingModes result;
        result.push_back(WirelessTypes::samplingMode_nonSync);
        result.push_back(WirelessTypes::samplingMode_sync);
        return result;
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_shmlink201FullBridge::sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const
    {
        //the list of sample rates varies for each sampling mode
        switch(samplingMode)
        {
            case WirelessTypes::samplingMode_sync:
            case WirelessTypes::samplingMode_nonSync:
            {
                return AvailableSampleRates::continuous_shmLink201;
            }

            default:
                throw Error_NotSupported("The sampling mode is not supported by this Node");
        }
    }

    bool NodeFeatures_shmlink201FullBridge::supportsHistogramConfig() const
    {
        return false;
    }

    bool NodeFeatures_shmlink201FullBridge::supportsHistogramRateConfig() const
    {
        return false;
    }

    bool NodeFeatures_shmlink201FullBridge::supportsHistogramEnableConfig() const
    {
        return false;
    }

    bool NodeFeatures_shmlink201FullBridge::supportsActivitySense() const
    {
        return true;
    }

    bool NodeFeatures_shmlink201FullBridge::supportsAutoCal_shm201() const
    {
        return true;
    }

    bool NodeFeatures_shmlink201FullBridge::supportsSensorDelayConfig() const
    {
        return false;
    }

    bool NodeFeatures_shmlink201FullBridge::supportsSensorDelayAlwaysOn() const
    {
        return false;
    }

    const WirelessTypes::VoltageType NodeFeatures_shmlink201FullBridge::adcVoltageInputType() const
    {
        return WirelessTypes::VoltageType::voltageType_differential;
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_shmlink201FullBridge::histogramTransmitRates() const
    {
        static const WirelessTypes::WirelessSampleRates HistogramRates = {
            {WirelessTypes::sampleRate_1Hz},
            {WirelessTypes::sampleRate_2Sec},
            {WirelessTypes::sampleRate_5Sec},
            {WirelessTypes::sampleRate_10Sec},
            {WirelessTypes::sampleRate_30Sec},
            {WirelessTypes::sampleRate_1Min},
            {WirelessTypes::sampleRate_2Min},
            {WirelessTypes::sampleRate_5Min},
            {WirelessTypes::sampleRate_10Min},
            {WirelessTypes::sampleRate_30Min},
            {WirelessTypes::sampleRate_60Min}};

        return HistogramRates;
    }

    bool NodeFeatures_shmlink201FullBridge::supportsGaugeResistance() const
    {
        return true;
    }

    bool NodeFeatures_shmlink201FullBridge::supportsNumActiveGauges() const
    {
        return true;
    }
}