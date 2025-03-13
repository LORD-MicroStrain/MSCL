/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "NodeFeatures_shmlink210.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "AvailableSampleRates.h"
#include "mscl/Utils.h"

namespace mscl
{
    NodeFeatures_shmlink210::NodeFeatures_shmlink210(const NodeInfo& info):
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
    }

    const WirelessTypes::DataCollectionMethods NodeFeatures_shmlink210::dataCollectionMethods() const
    {
        //build and return the data collection methods that are supported
        WirelessTypes::DataCollectionMethods result;
        result.push_back(WirelessTypes::collectionMethod_transmitOnly);
        return result;
    }

    const WirelessTypes::DataFormats NodeFeatures_shmlink210::dataFormats() const
    {
        //build and return the data formats that are supported
        WirelessTypes::DataFormats result;
        result.push_back(WirelessTypes::dataFormat_cal_float);
        result.push_back(WirelessTypes::dataFormat_cal_int16_x10);
        return result;
    }

    const WirelessTypes::Filters NodeFeatures_shmlink210::lowPassFilters() const
    {
        static const WirelessTypes::Filters filters = {
            {WirelessTypes::filter_4416hz},
            {WirelessTypes::filter_1104hz},
            {WirelessTypes::filter_12_66hz}
        };
        return filters;
    }

    const WirelessTypes::SamplingModes NodeFeatures_shmlink210::samplingModes() const
    {
        //build and return the sampling modes that are supported
        WirelessTypes::SamplingModes result;
        result.push_back(WirelessTypes::samplingMode_nonSync);
        result.push_back(WirelessTypes::samplingMode_sync);
        return result;
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_shmlink210::sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const
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

    bool NodeFeatures_shmlink210::supportsExcitationVoltageConfig() const
    {
        return true;
    }

    bool NodeFeatures_shmlink210::supportsFatigueConfig() const
    {
        return true;
    }

    bool NodeFeatures_shmlink210::supportsYoungsModConfig() const
    {
        return true;
    }

    bool NodeFeatures_shmlink210::supportsPoissonsRatioConfig() const
    {
        return true;
    }

    bool NodeFeatures_shmlink210::supportsFatigueDebugModeConfig() const
    {
        return true;
    }

    bool NodeFeatures_shmlink210::supportsFatigueModeConfig() const
    {
        return true;
    }

    bool NodeFeatures_shmlink210::supportsHistogramConfig() const
    {
        return true;
    }

    bool NodeFeatures_shmlink210::supportsHistogramRateConfig() const
    {
        return true;
    }

    bool NodeFeatures_shmlink210::supportsHistogramEnableConfig() const
    {
        return true;
    }

    bool NodeFeatures_shmlink210::supportsActivitySense() const
    {
        return true;
    }

    bool NodeFeatures_shmlink210::supportsAutoCal_shm201() const
    {
        return true;
    }

    bool NodeFeatures_shmlink210::supportsSensorDelayConfig() const
    {
        return false;
    }

    bool NodeFeatures_shmlink210::supportsSensorDelayAlwaysOn() const
    {
        return false;
    }

    uint8 NodeFeatures_shmlink210::numDamageAngles() const
    {
        return 3;
    }

    uint8 NodeFeatures_shmlink210::numSnCurveSegments() const
    {
        return 5;
    }

    const WirelessTypes::Voltages NodeFeatures_shmlink210::excitationVoltages() const
    {
        static const WirelessTypes::Voltages excitationVoltages = {
            {WirelessTypes::voltage_2500mV},
            {WirelessTypes::voltage_1500mV}
        };
        return excitationVoltages;
    }

    const WirelessTypes::VoltageType NodeFeatures_shmlink210::adcVoltageInputType() const
    {
        return WirelessTypes::VoltageType::voltageType_differential;
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_shmlink210::histogramTransmitRates() const
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

    const WirelessTypes::FatigueModes NodeFeatures_shmlink210::fatigueModes() const
    {
        static const WirelessTypes::FatigueModes modes = {
            {WirelessTypes::fatigueMode_angleStrain},
            {WirelessTypes::fatigueMode_distributedAngle},
            {WirelessTypes::fatigueMode_rawGaugeStrain}
        };

        return modes;
    }

    const uint32 NodeFeatures_shmlink210::minSensorDelay() const
    {
        if (!supportsSensorDelayConfig())
        {
            throw Error_NotSupported("Sensor Delay is not supported by this Node.");
        }

        //V1 - Milliseconds
        //V4 - Seconds, Milliseconds, or Microseconds
        switch (sensorDelayVersion())
        {
            case WirelessTypes::delayVersion_v1:
                return static_cast<uint32>(TimeSpan::MilliSeconds(1).getMicroseconds());    //1 millisecond

            case WirelessTypes::delayVersion_v4:
                return 350;     //350 microseconds

            default:
                assert(false);  //need to add a case for a new sensor delay version
                throw Error_NotSupported("Unknown Sensor Delay Version");
        }
    }

    const uint32 NodeFeatures_shmlink210::defaultSensorDelay() const
    {
        if (!supportsSensorDelayConfig())
        {
            throw Error_NotSupported("Sensor Delay is not supported by this Node.");
        }

        //V1 - Milliseconds
        //V4 - Seconds, Milliseconds, or Microseconds
        switch (sensorDelayVersion())
        {
            case WirelessTypes::delayVersion_v1:
                return static_cast<uint32>(TimeSpan::MilliSeconds(1).getMicroseconds());    //1 millisecond

            case WirelessTypes::delayVersion_v4:
                return 350;     //350 microseconds

            default:
                assert(false);  //need to add a case for a new sensor delay version
                throw Error_NotSupported("Unknown Sensor Delay Version");
        }
    }
}
