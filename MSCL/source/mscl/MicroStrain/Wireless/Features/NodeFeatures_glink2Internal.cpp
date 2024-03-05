/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "NodeFeatures_glink2Internal.h"

#include "mscl/Exceptions.h"
#include "AvailableSampleRates.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"

namespace mscl
{
    NodeFeatures_glink2Internal::NodeFeatures_glink2Internal(const NodeInfo& info):
        NodeFeatures(info)
    {
        addCalCoeffChannelGroup(1, "Acceleration X", NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
        addCalCoeffChannelGroup(2, "Acceleration Y", NodeEepromMap::CH_ACTION_SLOPE_2, NodeEepromMap::CH_ACTION_ID_2);
        addCalCoeffChannelGroup(3, "Acceleration Z", NodeEepromMap::CH_ACTION_SLOPE_3, NodeEepromMap::CH_ACTION_ID_3);
        addCalCoeffChannelGroup(4, "Internal Temperature", NodeEepromMap::CH_ACTION_SLOPE_4, NodeEepromMap::CH_ACTION_ID_4);

        static const ChannelMask ACCEL_CHS(BOOST_BINARY(00000111)); //ch1 - ch3
        m_channelGroups.emplace_back(ACCEL_CHS, "Acceleration X,Y,Z", ChannelGroup::SettingsMap{{WirelessTypes::chSetting_antiAliasingFilter, NodeEepromMap::ANTI_ALIASING_FILTER_1}});

        //Channels
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_acceleration, "Acceleration X", 16);
        m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_acceleration, "Acceleration Y", 16);
        m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_acceleration, "Acceleration Z", 16);
        m_channels.emplace_back(4, WirelessChannel::channel_4, WirelessTypes::chType_temperature, "Internal Temperature");
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_glink2Internal::sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const
    {
        //the list of sample rates varies for each sampling mode
        switch(samplingMode)
        {
        case WirelessTypes::samplingMode_nonSync:
        case WirelessTypes::samplingMode_sync:
            return AvailableSampleRates::continuous_glink2;

        case WirelessTypes::samplingMode_syncBurst:
            return AvailableSampleRates::burst_glink2;

        case WirelessTypes::samplingMode_armedDatalog:
            return AvailableSampleRates::armedDatalog_glink2;

        default:
            throw Error_NotSupported("The sampling mode is not supported by this Node");
        }
    }

    const WirelessTypes::Filters NodeFeatures_glink2Internal::antiAliasingFilters() const
    {
        static const WirelessTypes::Filters filters = {
            {WirelessTypes::filter_1000hz},
            {WirelessTypes::filter_2000hz},
            {WirelessTypes::filter_500hz},
            {WirelessTypes::filter_200hz},
            {WirelessTypes::filter_100hz},
            {WirelessTypes::filter_50hz},
            {WirelessTypes::filter_26hz}
        };
        return filters;
    }
}
