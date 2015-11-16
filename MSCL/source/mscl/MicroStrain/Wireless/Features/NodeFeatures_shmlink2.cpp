/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "NodeFeatures_shmlink2.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "AvailableSampleRates.h"
#include "mscl/Utils.h"

namespace mscl
{
    NodeFeatures_shmlink2::NodeFeatures_shmlink2(const NodeInfo& info):
        NodeFeatures(info)
    {
        static const ChannelMask DIFF_CH1(BOOST_BINARY(00000001));    //ch1
        static const ChannelMask DIFF_CH2(BOOST_BINARY(00000010));    //ch2
        static const ChannelMask DIFF_CH3(BOOST_BINARY(00000100));    //ch3

        m_channelGroups.emplace_back(DIFF_CH1, "Differential Channel 1",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_gaugeFactor, NodeEepromMap::GAUGE_FACTOR_1}}
        );

        m_channelGroups.emplace_back(DIFF_CH2, "Differential Channel 2",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_gaugeFactor, NodeEepromMap::GAUGE_FACTOR_2}}
        );

        m_channelGroups.emplace_back(DIFF_CH3, "Differential Channel 3",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_gaugeFactor, NodeEepromMap::GAUGE_FACTOR_3}}
        );

        //Channels
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_fullDifferential);    //full diff
        m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_fullDifferential);    //full diff
        m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_fullDifferential);    //full diff
        m_channels.emplace_back(5, WirelessChannel::channel_5, WirelessTypes::chType_acceleration);        //accel x
        m_channels.emplace_back(6, WirelessChannel::channel_6, WirelessTypes::chType_acceleration);        //accel y
        m_channels.emplace_back(7, WirelessChannel::channel_7, WirelessTypes::chType_acceleration);        //accel z
        m_channels.emplace_back(8, WirelessChannel::channel_8, WirelessTypes::chType_temperature);        //temp
    }

    const WirelessTypes::DataCollectionMethods NodeFeatures_shmlink2::dataCollectionMethods() const
    {
        //build and return the data collection methods that are supported
        WirelessTypes::DataCollectionMethods result;
        result.push_back(WirelessTypes::collectionMethod_transmitOnly);
        return result;
    }

    const WirelessTypes::DataFormats NodeFeatures_shmlink2::dataFormats() const
    {
        //build and return the data formats that are supported
        WirelessTypes::DataFormats result;
        result.push_back(WirelessTypes::dataFormat_4byte_float);
        return result;
    }

    const WirelessTypes::SamplingModes NodeFeatures_shmlink2::samplingModes() const
    {
        //build and return the sampling modes that are supported
        WirelessTypes::SamplingModes result;

        result.push_back(WirelessTypes::samplingMode_nonSync);

        return result;
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_shmlink2::sampleRates(WirelessTypes::SamplingMode samplingMode) const
    {
        //the list of sample rates varies for each sampling mode
        switch(samplingMode)
        {
            case WirelessTypes::samplingMode_nonSync:
                return AvailableSampleRates::continuous_shmLink2;

            default:
                throw Error("Invalid SamplingMode");
        }
    }

    bool NodeFeatures_shmlink2::supportsLimitedDuration() const
    {
        return false;
    }

    bool NodeFeatures_shmlink2::supportsFatigueConfig() const
    {
        return true;
    }

    bool NodeFeatures_shmlink2::supportsYoungsModConfig() const
    {
        return true;
    }

    bool NodeFeatures_shmlink2::supportsPoissonsRatioConfig() const
    {
        return true;
    }

    bool NodeFeatures_shmlink2::supportsFatigueDebugModeConfig() const
    {
        return true;
    }

    bool NodeFeatures_shmlink2::supportsFatigueModeConfig() const
    {
        return true;
    }

    bool NodeFeatures_shmlink2::supportsHistogramConfig() const
    {
        return true;
    }

    bool NodeFeatures_shmlink2::supportsHistogramRateConfig() const
    {
        return true;
    }

    bool NodeFeatures_shmlink2::supportsHistogramEnableConfig() const
    {
        return true;
    }

    bool NodeFeatures_shmlink2::supportsActivitySense() const
    {
        return true;
    }

    bool NodeFeatures_shmlink2::supportsAutoCal() const
    {
        return true;
    }

    uint8 NodeFeatures_shmlink2::numDamageAngles() const
    {
        return 3;
    }

    uint8 NodeFeatures_shmlink2::numSnCurveSegments() const
    {
        return 3;
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_shmlink2::histogramTransmitRates() const
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

    const WirelessTypes::FatigueModes NodeFeatures_shmlink2::fatigueModes() const
    {
        static const WirelessTypes::FatigueModes modes = {
            {WirelessTypes::fatigueMode_angleStrain},
            {WirelessTypes::fatigueMode_distributedAngle},
            {WirelessTypes::fatigueMode_rawGaugeStrain}
        };

        return modes;
    }
}