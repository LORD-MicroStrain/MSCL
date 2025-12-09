/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures_wirelessImpactSensor.h"

#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "mscl/MicroStrain/Wireless/Features/AvailableSampleRates.h"

namespace mscl
{
    NodeFeatures_wirelessImpactSensor::NodeFeatures_wirelessImpactSensor(const NodeInfo& info) :
        NodeFeatures(info)
    {
        addCalCoeffChannelGroup(1, "Acceleration X", NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
        addCalCoeffChannelGroup(2, "Acceleration Y", NodeEepromMap::CH_ACTION_SLOPE_2, NodeEepromMap::CH_ACTION_ID_2);
        addCalCoeffChannelGroup(3, "Acceleration Z", NodeEepromMap::CH_ACTION_SLOPE_3, NodeEepromMap::CH_ACTION_ID_3);

        static const ChannelMask CH1(BOOST_BINARY(00000001)); //ch1
        static const ChannelMask CH2(BOOST_BINARY(00000010)); //ch2
        static const ChannelMask CH3(BOOST_BINARY(00000100)); //ch3
        m_channelGroups.emplace_back(CH1, "Acceleration X", ChannelGroup::SettingsMap{{WirelessTypes::chSetting_antiAliasingFilter, NodeEepromMap::ANTI_ALIASING_FILTER_1}});
        m_channelGroups.emplace_back(CH2, "Acceleration Y", ChannelGroup::SettingsMap{{WirelessTypes::chSetting_antiAliasingFilter, NodeEepromMap::ANTI_ALIASING_FILTER_2}});
        m_channelGroups.emplace_back(CH3, "Acceleration Z", ChannelGroup::SettingsMap{{WirelessTypes::chSetting_antiAliasingFilter, NodeEepromMap::ANTI_ALIASING_FILTER_3}});

        //Channels
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_acceleration, "Acceleration X", 16);    //accel x
        m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_acceleration, "Acceleration Y", 16);    //accel y
        m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_acceleration, "Acceleration Z", 16);    //accel z
    }

    uint32 NodeFeatures_wirelessImpactSensor::ramBufferSize() const
    {
        return 524288;  // 2^19
    }

    const WirelessTypes::SamplingModes NodeFeatures_wirelessImpactSensor::samplingModes() const
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

    const WirelessTypes::WirelessSampleRates NodeFeatures_wirelessImpactSensor::sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const
    {
        (void)dataCollectionMethod;
        (void)dataMode;

        //the list of sample rates varies for each sampling mode
        switch(samplingMode)
        {
        case WirelessTypes::samplingMode_nonSync:
            return AvailableSampleRates::continuous_nonSync_impact;

        case WirelessTypes::samplingMode_sync:
            return AvailableSampleRates::continuous_sync_impact;

        case WirelessTypes::samplingMode_syncBurst:
        case WirelessTypes::samplingMode_nonSyncEvent:
        case WirelessTypes::samplingMode_syncEvent:
            return AvailableSampleRates::burst_impact;

        default:
            throw Error_NotSupported("The sampling mode is not supported by this Node");
        }
    }

    const WirelessTypes::Filters NodeFeatures_wirelessImpactSensor::antiAliasingFilters() const
    {
        static const WirelessTypes::Filters filters = {
            {WirelessTypes::filter_4096hz},
            {WirelessTypes::filter_2048hz},
            {WirelessTypes::filter_1024hz},
            {WirelessTypes::filter_512hz},
            {WirelessTypes::filter_256hz},
            {WirelessTypes::filter_128hz}
        };
        return filters;
    }

    const WirelessTypes::StorageLimitModes NodeFeatures_wirelessImpactSensor::storageLimitModes() const
    {
        WirelessTypes::StorageLimitModes modes;
        modes.push_back(WirelessTypes::storageLimit_overwrite);
        return modes;
    }
} // namespace mscl
