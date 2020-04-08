/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "NodeFeatures_shmlink200.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "AvailableSampleRates.h"
#include "mscl/Utils.h"

namespace mscl
{
    NodeFeatures_shmlink200::NodeFeatures_shmlink200(const NodeInfo& info):
        NodeFeatures_200series(info)
    {
        addCalCoeffChannelGroup(1, "Differential", NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
        addCalCoeffChannelGroup(2, "Differential", NodeEepromMap::CH_ACTION_SLOPE_2, NodeEepromMap::CH_ACTION_ID_2);
        addCalCoeffChannelGroup(3, "Differential", NodeEepromMap::CH_ACTION_SLOPE_3, NodeEepromMap::CH_ACTION_ID_3);
        addCalCoeffChannelGroup(5, "Acceleration X", NodeEepromMap::CH_ACTION_SLOPE_5, NodeEepromMap::CH_ACTION_ID_5);
        addCalCoeffChannelGroup(6, "Acceleration Y", NodeEepromMap::CH_ACTION_SLOPE_6, NodeEepromMap::CH_ACTION_ID_6);
        addCalCoeffChannelGroup(7, "Acceleration Z", NodeEepromMap::CH_ACTION_SLOPE_7, NodeEepromMap::CH_ACTION_ID_7);

        static const ChannelMask DIFF_CH1(BOOST_BINARY(00000001));    //ch1
        static const ChannelMask DIFF_CH2(BOOST_BINARY(00000010));    //ch2
        static const ChannelMask DIFF_CH3(BOOST_BINARY(00000100));    //ch3

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

        //Channels
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_fullDifferential, "Differential");
        m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_fullDifferential, "Differential");
        m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_fullDifferential, "Differential");
        m_channels.emplace_back(5, WirelessChannel::channel_5, WirelessTypes::chType_acceleration, "Acceleration X");
        m_channels.emplace_back(6, WirelessChannel::channel_6, WirelessTypes::chType_acceleration, "Acceleration Y");
        m_channels.emplace_back(7, WirelessChannel::channel_7, WirelessTypes::chType_acceleration, "Acceleration Z");
    }

    const WirelessTypes::DataFormats NodeFeatures_shmlink200::dataFormats() const
    {
        //build and return the data formats that are supported
        WirelessTypes::DataFormats result;
        result.push_back(WirelessTypes::dataFormat_cal_float);
        return result;
    }

    const WirelessTypes::SamplingModes NodeFeatures_shmlink200::samplingModes() const
    {
        //build and return the sampling modes that are supported
        WirelessTypes::SamplingModes result;

        if(m_nodeInfo.firmwareVersion() >= Version(10, 34589))
        {
            result.push_back(WirelessTypes::samplingMode_sync);
            result.push_back(WirelessTypes::samplingMode_syncEvent);
        }

        result.push_back(WirelessTypes::samplingMode_nonSync);

        return result;
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_shmlink200::sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const
    {
        //the list of sample rates varies for each sampling mode
        switch(samplingMode)
        {
            case WirelessTypes::samplingMode_sync:
            case WirelessTypes::samplingMode_syncEvent:
            {
                return AvailableSampleRates::continuous_shmLink2;
            }

            case WirelessTypes::samplingMode_nonSync:
            {
                if(m_nodeInfo.firmwareVersion() >= Version(10, 34589))
                {
                    return AvailableSampleRates::continuous_shmLink2_2;
                }
                else
                {
                    return AvailableSampleRates::continuous_shmLink2;
                }
            }

            default:
                throw Error_NotSupported("The sampling mode is not supported by this Node");
        }
    }

    bool NodeFeatures_shmlink200::supportsHistogramConfig() const
    {
        return true;
    }

    bool NodeFeatures_shmlink200::supportsHistogramRateConfig() const
    {
        return true;
    }

    bool NodeFeatures_shmlink200::supportsHistogramEnableConfig() const
    {
        return true;
    }

    bool NodeFeatures_shmlink200::supportsActivitySense() const
    {
        return false;
    }

    bool NodeFeatures_shmlink200::supportsAutoCal_shm() const
    {
        return true;
    }

    bool NodeFeatures_shmlink200::supportsSensorDelayConfig() const
    {
        return true;
    }

    bool NodeFeatures_shmlink200::supportsSensorDelayAlwaysOn() const
    {
        return false;
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_shmlink200::histogramTransmitRates() const
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
}