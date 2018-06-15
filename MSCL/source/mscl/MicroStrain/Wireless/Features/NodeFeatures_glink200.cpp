/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "NodeFeatures_glink200.h"

#include "mscl/Exceptions.h"
#include "AvailableSampleRates.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"

namespace mscl
{
    NodeFeatures_glink200::NodeFeatures_glink200(const NodeInfo& info):
        NodeFeatures_200series(info)
    {
        addCalCoeffChannelGroup(1, NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
        addCalCoeffChannelGroup(2, NodeEepromMap::CH_ACTION_SLOPE_2, NodeEepromMap::CH_ACTION_ID_2);
        addCalCoeffChannelGroup(3, NodeEepromMap::CH_ACTION_SLOPE_3, NodeEepromMap::CH_ACTION_ID_3);

        static const ChannelMask ACCEL_CHS(BOOST_BINARY(00000111)); //ch1 - ch3
        m_channelGroups.emplace_back(ACCEL_CHS, "Accel Channels", 
                                     ChannelGroup::SettingsMap {
                                         {WirelessTypes::chSetting_lowPassFilter, NodeEepromMap::LOW_PASS_FILTER_1},
                                         {WirelessTypes::chSetting_highPassFilter, NodeEepromMap::HIGH_PASS_FILTER_1},
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_1}
                                     });

        //Channels
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_acceleration, "Acceleration X", 20);
        m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_acceleration, "Acceleration Y", 20);
        m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_acceleration, "Acceleration Z", 20);
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_glink200::sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const
    {
        //special rates for derived mode only
        if(dataMode == WirelessTypes::dataMode_derived)
        {
            return AvailableSampleRates::derivedOnly_glink200;
        }

        //the list of sample rates varies for each sampling mode
        switch(samplingMode)
        {
        case WirelessTypes::samplingMode_nonSync:
            if(dataCollectionMethod == WirelessTypes::collectionMethod_logOnly)
            {
                return AvailableSampleRates::continuous_log_glink200;
            }
            else
            {
                return AvailableSampleRates::continuous_nonSync_glink200;
            }

        case WirelessTypes::samplingMode_sync:
            if(dataCollectionMethod == WirelessTypes::collectionMethod_logOnly) 
            {
                return AvailableSampleRates::continuous_log_glink200;
            }
            else
            {
                return AvailableSampleRates::continuous_sync_glink200;
            }

        case WirelessTypes::samplingMode_syncBurst:
        case WirelessTypes::samplingMode_syncEvent:
            return AvailableSampleRates::burst_glink200;

        default:
            throw Error_NotSupported("The sampling mode is not supported by this Node");
        }
    }

    const WirelessTypes::DataFormats NodeFeatures_glink200::dataFormats() const
    {
        //build and return the data formats that are supported
        WirelessTypes::DataFormats result;
        result.push_back(WirelessTypes::dataFormat_raw_int16);
        result.push_back(WirelessTypes::dataFormat_raw_int24);
        result.push_back(WirelessTypes::dataFormat_cal_float);
        return result;
    }

    const WirelessTypes::Filters NodeFeatures_glink200::lowPassFilters() const
    {
        static const WirelessTypes::Filters filters = {
            {WirelessTypes::filter_800hz},
            {WirelessTypes::filter_418hz},
            {WirelessTypes::filter_209hz},
            {WirelessTypes::filter_104hz},
            {WirelessTypes::filter_52hz},
            {WirelessTypes::filter_26hz}
        };
        return filters;
    }

    const WirelessTypes::HighPassFilters NodeFeatures_glink200::highPassFilters() const
    {
        static const WirelessTypes::HighPassFilters filters = {
            {WirelessTypes::highPass_off},
            {WirelessTypes::highPass_auto}
        };
        return filters;
    }

    const WirelessTypes::DerivedChannelTypes NodeFeatures_glink200::derivedChannelTypes() const
    {
        static const WirelessTypes::DerivedChannelTypes channels = {
            {WirelessTypes::derived_rms},
            {WirelessTypes::derived_peakToPeak},
            {WirelessTypes::derived_ips},
            {WirelessTypes::derived_crestFactor}
        };

        return channels;
    }
}