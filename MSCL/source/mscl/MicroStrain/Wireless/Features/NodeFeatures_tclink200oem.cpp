/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "NodeFeatures_tclink200oem.h"

#include "mscl/Exceptions.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "AvailableSampleRates.h"

namespace mscl
{
    NodeFeatures_tclink200oem::NodeFeatures_tclink200oem(const NodeInfo& info) :
        NodeFeatures_200series(info)
    {
        addCalCoeffChannelGroup(1, "Temperature", NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
        addCalCoeffChannelGroup(2, "CJC Temperature", NodeEepromMap::CH_ACTION_SLOPE_2, NodeEepromMap::CH_ACTION_ID_2);

        static const ChannelMask TEMP_CHS(BOOST_BINARY(00000001)); //ch1

        m_channelGroups.emplace_back(TEMP_CHS, "Temperature",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_tempSensorOptions, NodeEepromMap::TEMP_SENSOR_CONFIG_1},
                                         {WirelessTypes::chSetting_lowPassFilter, NodeEepromMap::LOW_PASS_FILTER_1},
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_1}}
        );

        //Channels
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_diffTemperature, "Temperature", 24);  //TODO: WHATS THE ADC RESOLUTION FOR THIS CHANNEL?
        m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_temperature, "CJC Temperature", 12);   //TODO: WHATS THE ADC RESOLUTION FOR THIS CHANNEL?
    }

    const WirelessTypes::SamplingModes NodeFeatures_tclink200oem::samplingModes() const
    {
        //build and return the sampling modes that are supported
        WirelessTypes::SamplingModes result;

        result.push_back(WirelessTypes::samplingMode_sync);
        result.push_back(WirelessTypes::samplingMode_nonSync);
        result.push_back(WirelessTypes::samplingMode_syncEvent);

        //no support for burst
        //no support for armed datalogging

        return result;
    }

    const WirelessTypes::TransducerTypes NodeFeatures_tclink200oem::transducerTypes() const
    {
        WirelessTypes::TransducerTypes result;
        result.push_back(WirelessTypes::transducer_thermocouple);
        result.push_back(WirelessTypes::transducer_rtd);
        result.push_back(WirelessTypes::transducer_thermistor);
        return result;
    }

    const WirelessTypes::DataFormats NodeFeatures_tclink200oem::dataFormats() const
    {
        //build and return the data formats that are supported
        WirelessTypes::DataFormats result;

        result.push_back(WirelessTypes::dataFormat_cal_float);

        //no support for uint16

        return result;
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_tclink200oem::sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const
    {
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

    const WirelessTypes::Filters NodeFeatures_tclink200oem::lowPassFilters() const
    {
        static const WirelessTypes::Filters filters = {
            {WirelessTypes::filter_294hz},
            {WirelessTypes::filter_12_66hz},
            {WirelessTypes::filter_2_6hz}
        };
        return filters;
    }

    WirelessTypes::WirelessSampleRate NodeFeatures_tclink200oem::maxSampleRateForLowPassFilter(WirelessTypes::Filter lowPassFilter,
                                                                                               WirelessTypes::SamplingMode samplingMode,
                                                                                               WirelessTypes::DataCollectionMethod dataCollectionMethod,
                                                                                               WirelessTypes::DataMode dataMode,
                                                                                               const ChannelMask& channels) const
    {
        //find the max sample rate allowed for the settling time
        SampleRate maxRate;

        switch(lowPassFilter)
        {
            case WirelessTypes::filter_294hz:
                maxRate = SampleRate::Hertz(128);
                break;

            case WirelessTypes::filter_12_66hz:
                maxRate = SampleRate::Hertz(8);
                break;

            case WirelessTypes::filter_2_6hz:
                maxRate = SampleRate::Hertz(2);
                break;

            default:
                throw Error_NotSupported("Invalid Low Pass Filter");
        }

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
}
