/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "NodeFeatures_rtdlink.h"

#include "mscl/Exceptions.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "AvailableSampleRates.h"

namespace mscl
{
    NodeFeatures_rtdlink::NodeFeatures_rtdlink(const NodeInfo& info) :
        NodeFeatures(info)
    {
        addCalCoeffChannelGroup(1, NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
        addCalCoeffChannelGroup(2, NodeEepromMap::CH_ACTION_SLOPE_2, NodeEepromMap::CH_ACTION_ID_2);
        addCalCoeffChannelGroup(7, NodeEepromMap::CH_ACTION_SLOPE_7, NodeEepromMap::CH_ACTION_ID_7);
        addCalCoeffChannelGroup(8, NodeEepromMap::CH_ACTION_SLOPE_8, NodeEepromMap::CH_ACTION_ID_8);

        static const ChannelMask THERMOCPL_CHS(BOOST_BINARY(00000011)); //ch1 - ch2

        m_channelGroups.emplace_back(THERMOCPL_CHS, "Thermocouple Channels",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_1},
                                         {WirelessTypes::chSetting_filterSettlingTime, NodeEepromMap::FILTER_1}}
        );

        //Channels
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_diffTemperature, "RTD (4-wire)");    //4-wire
        m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_diffTemperature, "RTD (2-wire)");    //2-wire
        m_channels.emplace_back(7, WirelessChannel::channel_7, WirelessTypes::chType_temperature, "Internal Temperature");
        m_channels.emplace_back(8, WirelessChannel::channel_8, WirelessTypes::chType_rh, "Relative Humidity");
    }

    const WirelessTypes::SamplingModes NodeFeatures_rtdlink::samplingModes() const
    {
        //build and return the sampling modes that are supported
        WirelessTypes::SamplingModes result;

        result.push_back(WirelessTypes::samplingMode_sync);
        result.push_back(WirelessTypes::samplingMode_nonSync);

        //no support for burst
        //no support for armed datalogging

        return result;
    }

    const WirelessTypes::DataFormats NodeFeatures_rtdlink::dataFormats() const
    {
        //build and return the data formats that are supported
        WirelessTypes::DataFormats result;

        result.push_back(WirelessTypes::dataFormat_cal_float);

        //no support for uint16

        return result;
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_rtdlink::sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const
    {
        //the list of sample rates varies for each sampling mode
        switch(samplingMode)
        {
            case WirelessTypes::samplingMode_nonSync:
            case WirelessTypes::samplingMode_sync:
                return AvailableSampleRates::continuous_tclink1ch;

            default:
                throw Error_NotSupported("The sampling mode is not supported by this Node");
        }
    }

    WirelessTypes::SettlingTime NodeFeatures_rtdlink::maxFilterSettlingTime(const SampleRate& rate) const
    {
        return maxFilterSettlingTime_B(rate);
    }

    WirelessTypes::WirelessSampleRate NodeFeatures_rtdlink::maxSampleRateForSettlingTime(WirelessTypes::SettlingTime filterSettlingTime, WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const
    {
        return maxSampleRateForSettlingTime_B(filterSettlingTime, sampleRates(samplingMode, dataCollectionMethod, dataMode));
    }
}