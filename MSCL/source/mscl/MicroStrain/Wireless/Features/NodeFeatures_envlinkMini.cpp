/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "NodeFeatures_envlinkMini.h"

#include "mscl/Exceptions.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "AvailableSampleRates.h"

namespace mscl
{
    NodeFeatures_envlinkMini::NodeFeatures_envlinkMini(const NodeInfo& info) :
        NodeFeatures(info)
    {
        addCalCoeffChannelGroup(1, "Temperature", NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
        addCalCoeffChannelGroup(2, "Temperature", NodeEepromMap::CH_ACTION_SLOPE_2, NodeEepromMap::CH_ACTION_ID_2);
        addCalCoeffChannelGroup(3, "Temperature", NodeEepromMap::CH_ACTION_SLOPE_3, NodeEepromMap::CH_ACTION_ID_3);
        addCalCoeffChannelGroup(7, "Internal Temperature", NodeEepromMap::CH_ACTION_SLOPE_7, NodeEepromMap::CH_ACTION_ID_7);
        addCalCoeffChannelGroup(8, "Relative Humidity", NodeEepromMap::CH_ACTION_SLOPE_8, NodeEepromMap::CH_ACTION_ID_8);

        static const ChannelMask THERMOCPL_CHS(BOOST_BINARY(00000111)); //ch1 - ch3

        m_channelGroups.emplace_back(THERMOCPL_CHS, "Temperature",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_1},
                                         {WirelessTypes::chSetting_filterSettlingTime, NodeEepromMap::FILTER_1},
                                         {WirelessTypes::chSetting_thermocoupleType, NodeEepromMap::THERMOCPL_TYPE}}
        );

        //Channels
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_diffTemperature, "Temperature", 24);
        m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_diffTemperature, "Temperature", 24);
        m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_diffTemperature, "Temperature", 24);
        m_channels.emplace_back(7, WirelessChannel::channel_7, WirelessTypes::chType_temperature, "Internal Temperature");
        m_channels.emplace_back(8, WirelessChannel::channel_8, WirelessTypes::chType_rh, "Relative Humidity");
    }

    bool NodeFeatures_envlinkMini::supportsSensorDelayConfig() const
    {
        return true;
    }

    const WirelessTypes::SamplingModes NodeFeatures_envlinkMini::samplingModes() const
    {
        //build and return the sampling modes that are supported
        WirelessTypes::SamplingModes result;

        result.push_back(WirelessTypes::samplingMode_sync);
        result.push_back(WirelessTypes::samplingMode_nonSync);

        //no support for burst
        //no support for armed datalogging

        return result;
    }

    const WirelessTypes::DataFormats NodeFeatures_envlinkMini::dataFormats() const
    {
        //build and return the data formats that are supported
        WirelessTypes::DataFormats result;

        result.push_back(WirelessTypes::dataFormat_cal_float);

        //no support for uint16

        return result;
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_envlinkMini::sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const
    {
        //the list of sample rates varies for each sampling mode
        switch(samplingMode)
        {
            case WirelessTypes::samplingMode_nonSync:
            case WirelessTypes::samplingMode_sync:
                return AvailableSampleRates::continuous_envlink;

            default:
                throw Error_NotSupported("The sampling mode is not supported by this Node");
        }
    }

    WirelessTypes::SettlingTime NodeFeatures_envlinkMini::maxFilterSettlingTime(const SampleRate& rate) const
    {
        return maxFilterSettlingTime_B(rate);
    }

    WirelessTypes::WirelessSampleRate NodeFeatures_envlinkMini::maxSampleRateForSettlingTime(WirelessTypes::SettlingTime filterSettlingTime, WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const
    {
        return maxSampleRateForSettlingTime_A(filterSettlingTime, sampleRates(samplingMode, dataCollectionMethod, dataMode));
    }
}
