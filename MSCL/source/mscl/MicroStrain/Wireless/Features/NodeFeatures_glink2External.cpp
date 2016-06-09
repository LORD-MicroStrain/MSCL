/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "NodeFeatures_glink2External.h"

#include "mscl/Exceptions.h"
#include "AvailableSampleRates.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"

namespace mscl
{
    NodeFeatures_glink2External::NodeFeatures_glink2External(const NodeInfo& info):
        NodeFeatures(info)
    {
        addCalCoeffChannelGroup(1, NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
        addCalCoeffChannelGroup(4, NodeEepromMap::CH_ACTION_SLOPE_4, NodeEepromMap::CH_ACTION_ID_4);

        static const ChannelMask CH1(BOOST_BINARY(00000001)); //ch1
        m_channelGroups.emplace_back(CH1, "Accel Channel 1", ChannelGroup::SettingsMap{{WirelessTypes::chSetting_lowPassFilter, NodeEepromMap::LOW_PASS_FILTER_1}});

        //Channels
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_acceleration);   //accel
        m_channels.emplace_back(4, WirelessChannel::channel_4, WirelessTypes::chType_temperature);    //temp
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_glink2External::sampleRates(WirelessTypes::SamplingMode samplingMode) const
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
            throw Error("Invalid SamplingMode");
        }
    }

    const WirelessTypes::Filters NodeFeatures_glink2External::lowPassFilters() const
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