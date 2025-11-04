/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures_tclink200.h"

#include "mscl/MicroStrain/SampleRate.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "mscl/MicroStrain/Wireless/Features/AvailableSampleRates.h"

namespace mscl
{
    NodeFeatures_tclink200::NodeFeatures_tclink200(const NodeInfo& info) :
        NodeFeatures_200series(info)
    {
        addCalCoeffChannelGroup(1, "Temperature", NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
        addCalCoeffChannelGroup(2, "Temperature", NodeEepromMap::CH_ACTION_SLOPE_2, NodeEepromMap::CH_ACTION_ID_2);
        addCalCoeffChannelGroup(3, "Temperature", NodeEepromMap::CH_ACTION_SLOPE_3, NodeEepromMap::CH_ACTION_ID_3);
        addCalCoeffChannelGroup(4, "Temperature", NodeEepromMap::CH_ACTION_SLOPE_4, NodeEepromMap::CH_ACTION_ID_4);
        addCalCoeffChannelGroup(5, "Temperature", NodeEepromMap::CH_ACTION_SLOPE_5, NodeEepromMap::CH_ACTION_ID_5);
        addCalCoeffChannelGroup(6, "Temperature", NodeEepromMap::CH_ACTION_SLOPE_6, NodeEepromMap::CH_ACTION_ID_6);
        addCalCoeffChannelGroup(7, "Temperature", NodeEepromMap::CH_ACTION_SLOPE_7, NodeEepromMap::CH_ACTION_ID_7);
        addCalCoeffChannelGroup(8, "Temperature", NodeEepromMap::CH_ACTION_SLOPE_8, NodeEepromMap::CH_ACTION_ID_8);
        addCalCoeffChannelGroup(9, "Temperature", NodeEepromMap::CH_ACTION_SLOPE_9, NodeEepromMap::CH_ACTION_ID_9);
        addCalCoeffChannelGroup(10, "Temperature", NodeEepromMap::CH_ACTION_SLOPE_10, NodeEepromMap::CH_ACTION_ID_10);
        addCalCoeffChannelGroup(11, "Temperature", NodeEepromMap::CH_ACTION_SLOPE_11, NodeEepromMap::CH_ACTION_ID_11);
        addCalCoeffChannelGroup(12, "Temperature", NodeEepromMap::CH_ACTION_SLOPE_12, NodeEepromMap::CH_ACTION_ID_12);
        addCalCoeffChannelGroup(13, "CJC Temperature", NodeEepromMap::CH_ACTION_SLOPE_13, NodeEepromMap::CH_ACTION_ID_13);

        m_channelGroups.emplace_back(ChannelMask(BOOST_BINARY(00000000 00111111)), "Temperature",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_tempSensorOptions, NodeEepromMap::TEMP_SENSOR_CONFIG_1},
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_1}
                                     }
        );

        m_channelGroups.emplace_back(ChannelMask(BOOST_BINARY(00001111 11000000)), "Temperature",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_tempSensorOptions, NodeEepromMap::TEMP_SENSOR_CONFIG_2},
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_2}
                                     }
        );

        m_channelGroups.emplace_back(ChannelMask(BOOST_BINARY(00001111 11111111)), "Temperature",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_lowPassFilter, NodeEepromMap::LOW_PASS_FILTER_1}
                                     }
        );

        //Channels
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_diffTemperature, "Temperature", 24);
        m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_diffTemperature, "Temperature", 24);
        m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_diffTemperature, "Temperature", 24);
        m_channels.emplace_back(4, WirelessChannel::channel_4, WirelessTypes::chType_diffTemperature, "Temperature", 24);
        m_channels.emplace_back(5, WirelessChannel::channel_5, WirelessTypes::chType_diffTemperature, "Temperature", 24);
        m_channels.emplace_back(6, WirelessChannel::channel_6, WirelessTypes::chType_diffTemperature, "Temperature", 24);
        m_channels.emplace_back(7, WirelessChannel::channel_7, WirelessTypes::chType_diffTemperature, "Temperature", 24);
        m_channels.emplace_back(8, WirelessChannel::channel_8, WirelessTypes::chType_diffTemperature, "Temperature", 24);
        m_channels.emplace_back(9, WirelessChannel::channel_9, WirelessTypes::chType_diffTemperature, "Temperature", 24);
        m_channels.emplace_back(10, WirelessChannel::channel_10, WirelessTypes::chType_diffTemperature, "Temperature", 24);
        m_channels.emplace_back(11, WirelessChannel::channel_11, WirelessTypes::chType_diffTemperature, "Temperature", 24);
        m_channels.emplace_back(12, WirelessChannel::channel_12, WirelessTypes::chType_diffTemperature, "Temperature", 24);
        m_channels.emplace_back(13, WirelessChannel::channel_13, WirelessTypes::chType_temperature, "CJC Temperature", 12);
    }

    const WirelessTypes::SamplingModes NodeFeatures_tclink200::samplingModes() const
    {
        //build and return the sampling modes that are supported
        WirelessTypes::SamplingModes result;
        result.push_back(WirelessTypes::samplingMode_sync);
        result.push_back(WirelessTypes::samplingMode_nonSync);
        result.push_back(WirelessTypes::samplingMode_syncEvent);
        return result;
    }

    const WirelessTypes::TransducerTypes NodeFeatures_tclink200::transducerTypes() const
    {
        WirelessTypes::TransducerTypes result;
        result.push_back(WirelessTypes::transducer_thermocouple);
        return result;
    }

    const WirelessTypes::DataFormats NodeFeatures_tclink200::dataFormats() const
    {
        //build and return the data formats that are supported
        WirelessTypes::DataFormats result;
        result.push_back(WirelessTypes::dataFormat_cal_float);
        return result;
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_tclink200::sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const
    {
        (void)dataCollectionMethod;
        (void)dataMode;

        //the list of sample rates varies for each sampling mode
        switch(samplingMode)
        {
            case WirelessTypes::samplingMode_nonSync:
            case WirelessTypes::samplingMode_syncEvent:
            case WirelessTypes::samplingMode_sync:
                return AvailableSampleRates::continuous_tclink200;

            default:
                throw Error_NotSupported("The sampling mode is not supported by this Node");
        }
    }

    const WirelessTypes::Filters NodeFeatures_tclink200::lowPassFilters() const
    {
        static const WirelessTypes::Filters filters = {
            {WirelessTypes::filter_294hz},
            {WirelessTypes::filter_12_66hz},
            {WirelessTypes::filter_2_6hz}
        };
        return filters;
    }

    WirelessTypes::WirelessSampleRate NodeFeatures_tclink200::maxSampleRateForLowPassFilter(WirelessTypes::Filter lowPassFilter,
                                                                                            WirelessTypes::SamplingMode samplingMode,
                                                                                            WirelessTypes::DataCollectionMethod dataCollectionMethod,
                                                                                            WirelessTypes::DataMode dataMode,
                                                                                            const ChannelMask& channels) const
    {
        SampleRate maxRate = SampleRate::FromWirelessEepromValue(maxRateForFilter(lowPassFilter, channels));

        const WirelessTypes::WirelessSampleRates rates = sampleRates(samplingMode, dataCollectionMethod, dataMode);

        //even though we found the max rate, that sample rate might not actually be supported by the Node.
        //look through all the supported rates and find the max one supported below the given rate.
        for(const auto& rate : rates)
        {
            if(SampleRate::FromWirelessEepromValue(rate) <= maxRate)
            {
                return rate;
            }
        }

        //should never get to this if this function is used correctly (passed in valid sample rates)
        //and node features are built correctly.
        assert(false);
        return rates.at(rates.size() - 1);
    }

    const WirelessTypes::WirelessSampleRate NodeFeatures_tclink200::maxRateForFilter(WirelessTypes::Filter lowPassFilter, const ChannelMask& channels)
    {
        //the max rate depends on how many channels are enabled per ADC
        const uint8 LAST_CH_ADC_1 = 6;  //ADC1 = ch1-ch6
        const uint8 LAST_CH_ADC_2 = 12; //ADC2 = ch7-ch12

        const std::map<uint8, WirelessTypes::WirelessSampleRate> filterRates_294hz = {
            {1, WirelessTypes::sampleRate_128Hz},
            {2, WirelessTypes::sampleRate_64Hz},
            {3, WirelessTypes::sampleRate_64Hz},
            {4, WirelessTypes::sampleRate_32Hz},
            {5, WirelessTypes::sampleRate_32Hz},
            {6, WirelessTypes::sampleRate_32Hz}
        };

        const std::map<uint8, WirelessTypes::WirelessSampleRate> filterRates_12hz = {
            {1, WirelessTypes::sampleRate_8Hz},
            {2, WirelessTypes::sampleRate_4Hz},
            {3, WirelessTypes::sampleRate_4Hz},
            {4, WirelessTypes::sampleRate_2Hz},
            {5, WirelessTypes::sampleRate_2Hz},
            {6, WirelessTypes::sampleRate_2Hz}
        };

        const std::map<uint8, WirelessTypes::WirelessSampleRate> filterRates_2hz = {
            {1, WirelessTypes::sampleRate_2Hz},
            {2, WirelessTypes::sampleRate_1Hz},
            {3, WirelessTypes::sampleRate_2Sec},
            {4, WirelessTypes::sampleRate_2Sec},
            {5, WirelessTypes::sampleRate_5Sec},
            {6, WirelessTypes::sampleRate_5Sec}
        };

        uint8 adc1Count = 0;
        uint8 adc2Count = 0;
        for(uint8 chNum = 1; chNum <= channels.lastChEnabled(); chNum++)
        {
            if(channels.enabled(chNum))
            {
                if(chNum <= LAST_CH_ADC_1)
                {
                    adc1Count++;
                }
                else if(chNum <= LAST_CH_ADC_2)
                {
                    adc2Count++;
                }
            }
        }

        const uint8 maxAdcChannelCount = std::max(adc1Count, adc2Count);

        switch(lowPassFilter)
        {
            case WirelessTypes::filter_294hz:
                return filterRates_294hz.at(maxAdcChannelCount);
                break;

            case WirelessTypes::filter_12_66hz:
                return filterRates_12hz.at(maxAdcChannelCount);
                break;

            case WirelessTypes::filter_2_6hz:
                return filterRates_2hz.at(maxAdcChannelCount);
                break;

            default:
                throw Error_NotSupported("Invalid Low Pass Filter");
        }
    }

    bool NodeFeatures_tclink200::supportsNewTransmitPowers() const
    {
        return true;
    }

    bool NodeFeatures_tclink200::supportsLowBatteryThresholdConfig() const
    {
        return m_nodeInfo.firmwareVersion() >= Version(12, 42296);
    }
} // namespace mscl
