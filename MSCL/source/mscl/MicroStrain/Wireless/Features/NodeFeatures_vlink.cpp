/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures_vlink.h"

#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "mscl/MicroStrain/Wireless/Features/AvailableSampleRates.h"

namespace mscl
{
    NodeFeatures_vlink::NodeFeatures_vlink(const NodeInfo& info) :
        NodeFeatures(info)
    {
        //Channels
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_fullDifferential, "Differential", 16);
        m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_fullDifferential, "Differential", 16);
        m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_fullDifferential, "Differential", 16);
        m_channels.emplace_back(4, WirelessChannel::channel_4, WirelessTypes::chType_fullDifferential, "Differential", 16);
        m_channels.emplace_back(5, WirelessChannel::channel_5, WirelessTypes::chType_singleEnded, "Single-ended", 16);
        m_channels.emplace_back(6, WirelessChannel::channel_6, WirelessTypes::chType_singleEnded, "Single-ended", 16);
        m_channels.emplace_back(7, WirelessChannel::channel_7, WirelessTypes::chType_singleEnded, "Single-ended", 16);
        m_channels.emplace_back(8, WirelessChannel::channel_8, WirelessTypes::chType_temperature, "Internal Temperature");

        //Channel Groups
        static const ChannelMask DIFFERENTIAL_CH1(BOOST_BINARY(00000001));    //ch1
        static const ChannelMask DIFFERENTIAL_CH2(BOOST_BINARY(00000010));    //ch2
        static const ChannelMask DIFFERENTIAL_CH3(BOOST_BINARY(00000100));    //ch3
        static const ChannelMask DIFFERENTIAL_CH4(BOOST_BINARY(00001000));    //ch4

        m_channelGroups.emplace_back(DIFFERENTIAL_CH1, "Differential",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_1},
                                         {WirelessTypes::chSetting_hardwareOffset, NodeEepromMap::HW_OFFSET_1},
                                         {WirelessTypes::chSetting_autoBalance, NodeEepromMap::HW_OFFSET_1},
                                         {WirelessTypes::chSetting_legacyShuntCal, NodeEepromMap::CH_ACTION_SLOPE_1}}
        );

        m_channelGroups.emplace_back(DIFFERENTIAL_CH2, "Differential",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_2},
                                         {WirelessTypes::chSetting_hardwareOffset, NodeEepromMap::HW_OFFSET_2},
                                         {WirelessTypes::chSetting_autoBalance, NodeEepromMap::HW_OFFSET_2},
                                         {WirelessTypes::chSetting_legacyShuntCal, NodeEepromMap::CH_ACTION_SLOPE_2}}
        );

        m_channelGroups.emplace_back(DIFFERENTIAL_CH3, "Differential",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_3},
                                         {WirelessTypes::chSetting_hardwareOffset, NodeEepromMap::HW_OFFSET_3},
                                         {WirelessTypes::chSetting_autoBalance, NodeEepromMap::HW_OFFSET_3},
                                         {WirelessTypes::chSetting_legacyShuntCal, NodeEepromMap::CH_ACTION_SLOPE_3}}
        );

        m_channelGroups.emplace_back(DIFFERENTIAL_CH4, "Differential",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_4},
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

    bool NodeFeatures_vlink::supportsSensorDelayConfig() const
    {
        return true;
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_vlink::sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const
    {
        (void)dataCollectionMethod;
        (void)dataMode;

        //the list of sample rates varies for each sampling mode
        switch(samplingMode)
        {
        case WirelessTypes::samplingMode_nonSync:
        case WirelessTypes::samplingMode_sync:
            return AvailableSampleRates::continuous;

        case WirelessTypes::samplingMode_syncBurst:
            return AvailableSampleRates::burst_vlink;

        case WirelessTypes::samplingMode_armedDatalog:
            return AvailableSampleRates::armedDatalog_vlink;

        default:
            throw Error_NotSupported("The sampling mode is not supported by this Node");
        }
    }

    WirelessTypes::WirelessSampleRate NodeFeatures_vlink::maxSampleRate(WirelessTypes::SamplingMode samplingMode, const ChannelMask& channels, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const
    {
        uint16 channelCount = channels.count();

        if(samplingMode == WirelessTypes::samplingMode_syncBurst)
        {
            //determine the actual max rate based on the # of active channels
            switch(channelCount)
            {
                case 1:
                    return WirelessTypes::sampleRate_10kHz;
                case 2:
                    return WirelessTypes::sampleRate_9kHz;
                case 3:
                    return WirelessTypes::sampleRate_7kHz;
                case 4:
                    return WirelessTypes::sampleRate_6kHz;
                case 5:
                    return WirelessTypes::sampleRate_5kHz;
                case 6:
                    return WirelessTypes::sampleRate_4kHz;
                case 7:
                    return WirelessTypes::sampleRate_3kHz;
                default:
                    return WirelessTypes::sampleRate_2kHz;
            }
        }

        if(samplingMode == WirelessTypes::samplingMode_armedDatalog)
        {
            //determine the actual max rate based on the # of active channels
            switch(channelCount)
            {
                case 1:
                    return WirelessTypes::sampleRate_10kHz;
                case 2:
                    return WirelessTypes::sampleRate_7kHz;
                case 3:
                    return WirelessTypes::sampleRate_6kHz;
                case 4:
                    return WirelessTypes::sampleRate_5kHz;
                case 5:
                    return WirelessTypes::sampleRate_4kHz;
                case 6:
                    return WirelessTypes::sampleRate_4kHz;
                case 7:
                    return WirelessTypes::sampleRate_3kHz;
                default:
                    return WirelessTypes::sampleRate_3kHz;
            }
        }

        //number of channels has no affect on sample rate
        //just return the result of the parent class' function
        return NodeFeatures::maxSampleRate(samplingMode, channels, dataCollectionMethod, dataMode);
    }

    const uint32 NodeFeatures_vlink::minSensorDelay() const
    {
        if (!supportsSensorDelayConfig())
        {
            throw Error_NotSupported("Sensor Delay is not supported by this Node.");
        }

        return static_cast<uint32>(TimeSpan::MilliSeconds(1).getMicroseconds());     //1 millisecond
    }

    const uint32 NodeFeatures_vlink::maxSensorDelay() const
    {
        if (!supportsSensorDelayConfig())
        {
            throw Error_NotSupported("Sensor Delay is not supported by this Node.");
        }

        return static_cast<uint32>(TimeSpan::Seconds(1).getMicroseconds());                      //1 second
    }

    const uint32 NodeFeatures_vlink::defaultSensorDelay() const
    {
        if (!supportsSensorDelayConfig())
        {
            throw Error_NotSupported("Sensor Delay is not supported by this Node.");
        }

        return static_cast<uint32>(TimeSpan::MilliSeconds(10).getMicroseconds());     //10 milliseconds
    }
} // namespace mscl
