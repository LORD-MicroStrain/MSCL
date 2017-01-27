/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

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
        NodeFeatures(info)
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
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_acceleration);    //accel x
        m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_acceleration);    //accel y
        m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_acceleration);    //accel z
    }

    bool NodeFeatures_glink200::isChannelSettingReadOnly(WirelessTypes::ChannelGroupSetting setting) const
    {
        if(setting == WirelessTypes::chSetting_linearEquation ||
           setting == WirelessTypes::chSetting_equationType ||
           setting == WirelessTypes::chSetting_unit)
        {
            return true;
        }

        return false;
    }

    const WirelessTypes::TransmitPowers NodeFeatures_glink200::transmitPowers() const
    {
        if(m_nodeInfo.regionCode() == WirelessTypes::region_japan)
        {
            WirelessTypes::TransmitPowers result;
            result.push_back(WirelessTypes::power_16dBm);
            result.push_back(WirelessTypes::power_10dBm);
            result.push_back(WirelessTypes::power_5dBm);
            return result;
        }
        else
        {
            return NodeFeatures::transmitPowers();
        }
    }

    const WirelessTypes::SamplingModes NodeFeatures_glink200::samplingModes() const
    {
        //build and return the sampling modes that are supported
        WirelessTypes::SamplingModes result;

        result.push_back(WirelessTypes::samplingMode_sync);
        result.push_back(WirelessTypes::samplingMode_syncBurst);
        result.push_back(WirelessTypes::samplingMode_nonSync);
        result.push_back(WirelessTypes::samplingMode_syncEvent);

        //no support for armed datalogging

        return result;
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_glink200::sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod) const
    {
        //TODO: these sample rates copied from v-link 200 -- make needed adjustments before final release

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
        //TODO: update these filters

        static const WirelessTypes::Filters filters = {
            {WirelessTypes::filter_1000hz},
            {WirelessTypes::filter_500hz},
            {WirelessTypes::filter_250hz},
            {WirelessTypes::filter_125hz},
            {WirelessTypes::filter_62hz},
            {WirelessTypes::filter_31hz}
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

    const WirelessTypes::DerivedChannels NodeFeatures_glink200::derivedChannels() const
    {
        static const WirelessTypes::DerivedChannels channels = {
            {WirelessTypes::derived_rms},
            {WirelessTypes::derived_peakToPeak},
            {WirelessTypes::derived_ips},
            {WirelessTypes::derived_crestFactor}
        };

        return channels;
    }

    const WirelessTypes::StorageLimitModes NodeFeatures_glink200::storageLimitModes() const
    {
        WirelessTypes::StorageLimitModes modes;
        modes.push_back(WirelessTypes::storageLimit_stop);
        modes.push_back(WirelessTypes::storageLimit_overwrite);
        return modes;
    }
}