/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "NodeFeatures_shmlink.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "mscl/Utils.h"

namespace mscl
{
    NodeFeatures_shmlink::NodeFeatures_shmlink(const NodeInfo& info):
        NodeFeatures(info)
    {
        addCalCoeffChannelGroup(1, "Differential", NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
        addCalCoeffChannelGroup(2, "Differential", NodeEepromMap::CH_ACTION_SLOPE_2, NodeEepromMap::CH_ACTION_ID_2);
        addCalCoeffChannelGroup(3, "Differential", NodeEepromMap::CH_ACTION_SLOPE_3, NodeEepromMap::CH_ACTION_ID_3);
        addCalCoeffChannelGroup(5, "Acceleration X", NodeEepromMap::CH_ACTION_SLOPE_5, NodeEepromMap::CH_ACTION_ID_5);
        addCalCoeffChannelGroup(6, "Acceleration Y", NodeEepromMap::CH_ACTION_SLOPE_6, NodeEepromMap::CH_ACTION_ID_6);
        addCalCoeffChannelGroup(7, "Acceleration Z", NodeEepromMap::CH_ACTION_SLOPE_7, NodeEepromMap::CH_ACTION_ID_7);
        addCalCoeffChannelGroup(8, "Internal Temperature", NodeEepromMap::CH_ACTION_SLOPE_8, NodeEepromMap::CH_ACTION_ID_8);

        static const ChannelMask DIFFERENTIAL_CHS(BOOST_BINARY(00000111));    //ch1-ch3
        static const ChannelMask DIFF_CH1(BOOST_BINARY(00000001));    //ch1
        static const ChannelMask DIFF_CH2(BOOST_BINARY(00000010));    //ch2
        static const ChannelMask DIFF_CH3(BOOST_BINARY(00000100));    //ch3

        m_channelGroups.emplace_back(DIFFERENTIAL_CHS, "Differential",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_1}}
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

        //Channels
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_fullDifferential, "Differential", 12);
        m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_fullDifferential, "Differential", 12);
        m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_fullDifferential, "Differential", 12);
        m_channels.emplace_back(5, WirelessChannel::channel_5, WirelessTypes::chType_acceleration, "Acceleration X", 12);
        m_channels.emplace_back(6, WirelessChannel::channel_6, WirelessTypes::chType_acceleration, "Acceleration Y", 12);
        m_channels.emplace_back(7, WirelessChannel::channel_7, WirelessTypes::chType_acceleration, "Acceleration Z", 12);
        m_channels.emplace_back(8, WirelessChannel::channel_8, WirelessTypes::chType_temperature, "Internal Temperature");
    }

    bool NodeFeatures_shmlink::supportsFatigueConfig() const
    {
        return true;
    }

    bool NodeFeatures_shmlink::supportsYoungsModConfig() const
    {
        return false;    //this version of the shm-link has a hard-coded Young's Modulus
    }

    bool NodeFeatures_shmlink::supportsPoissonsRatioConfig() const
    {
        return false;    //this version of the shm-link has a hard-coded Poisson's Ratio
    }

    bool NodeFeatures_shmlink::supportsFatigueDebugModeConfig() const
    {
        return false;    //this version of the shm-link does not allow eeprom configuration of raw mode
    }

    bool NodeFeatures_shmlink::supportsHistogramConfig() const
    {
        return true;
    }

    bool NodeFeatures_shmlink::supportsHistogramRateConfig() const
    {
        return false;    //this version of the shm-link has a hard-coded Histogram Rate
    }

    bool NodeFeatures_shmlink::supportsHistogramEnableConfig() const
    {
        return false;    //this version of the shm-link does not allow turning the histogram on and off
    }

    bool NodeFeatures_shmlink::supportsSensorDelayConfig() const
    {
        return true;
    }

    bool NodeFeatures_shmlink::supportsSensorDelayAlwaysOn() const
    {
        return false;
    }

    uint8 NodeFeatures_shmlink::numDamageAngles() const
    {
        return 3;
    }

    uint8 NodeFeatures_shmlink::numSnCurveSegments() const
    {
        return 2;
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_shmlink::histogramTransmitRates() const
    {
        static const WirelessTypes::WirelessSampleRates HistogramRates = {
            {WirelessTypes::sampleRate_30Sec}
        };

        return HistogramRates;
    }

    const WirelessTypes::FatigueModes NodeFeatures_shmlink::fatigueModes() const
    {
        static const WirelessTypes::FatigueModes modes = {
            {WirelessTypes::fatigueMode_angleStrain}
        };

        return modes;
    }
}