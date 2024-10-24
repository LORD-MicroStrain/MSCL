/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "NodeFeatures_iepeLink.h"

#include "mscl/Exceptions.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"
#include "AvailableSampleRates.h"

namespace mscl
{
    NodeFeatures_iepeLink::NodeFeatures_iepeLink(const NodeInfo& info):
        NodeFeatures(info)
    {
        addCalCoeffChannelGroup(1, "Acceleration", NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
        addCalCoeffChannelGroup(4, "Internal Temperature", NodeEepromMap::CH_ACTION_SLOPE_4, NodeEepromMap::CH_ACTION_ID_4);

        static const ChannelMask CH1(BOOST_BINARY(00000001)); //ch1
        m_channelGroups.emplace_back(CH1, "Acceleration", ChannelGroup::SettingsMap{{WirelessTypes::chSetting_antiAliasingFilter, NodeEepromMap::ANTI_ALIASING_FILTER_1}});

        //Channels
        //    Note: Channel 4 is unique in that it doesn't follow the sample rate of the node.
        //          Instead, it is sent once every burst, with a provided sample rate of once every 24 hours.
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_acceleration, "Acceleration", 23);
        m_channels.emplace_back(4, WirelessChannel::channel_4, WirelessTypes::chType_temperature, "Internal Temperature");
    }

    uint32 NodeFeatures_iepeLink::ramBufferSize() const
    {
        return 600000;
    }

    bool NodeFeatures_iepeLink::supportsSensorDelayConfig() const
    {
        return true;
    }

    const WirelessTypes::SamplingModes NodeFeatures_iepeLink::samplingModes() const
    {
        //build and return the sampling modes that are supported
        WirelessTypes::SamplingModes result;

        result.push_back(WirelessTypes::samplingMode_syncBurst);

        //no support for sync continuous
        //no support for non sync
        //no support for armed datalogging

        return result;
    }

    const WirelessTypes::DataFormats NodeFeatures_iepeLink::dataFormats() const
    {
        //build and return the data formats that are supported
        WirelessTypes::DataFormats result;

        result.push_back(WirelessTypes::dataFormat_cal_float);

        //no support for uint16

        return result;
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_iepeLink::sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const
    {
        //the list of sample rates varies for each sampling mode
        switch(samplingMode)
        {
        case WirelessTypes::samplingMode_syncBurst:
            return AvailableSampleRates::burst_iepeLink;

        default:
            throw Error_NotSupported("The sampling mode is not supported by this Node");
        }
    }

    const WirelessTypes::Filters NodeFeatures_iepeLink::antiAliasingFilters() const
    {
        static const WirelessTypes::Filters filters = {
            {WirelessTypes::filter_33000hz},
            {WirelessTypes::filter_20000hz},
            {WirelessTypes::filter_10000hz},
            {WirelessTypes::filter_5000hz},
            {WirelessTypes::filter_2000hz},
            {WirelessTypes::filter_1000hz},
            {WirelessTypes::filter_500hz},
            {WirelessTypes::filter_200hz},
            {WirelessTypes::filter_100hz},
            {WirelessTypes::filter_50hz},
            {WirelessTypes::filter_26hz}
        };
        return filters;
    }
}
