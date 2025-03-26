/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures_glink200.h"

#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "mscl/MicroStrain/Wireless/Features/AvailableSampleRates.h"

namespace mscl
{
    const Version NodeFeatures_glink200::VER_TILT_SUPPORTED(12, 41495);

    NodeFeatures_glink200::NodeFeatures_glink200(const NodeInfo& info) :
        NodeFeatures_200series(info)
    {
        addCalCoeffChannelGroup(1, "Acceleration X", NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
        addCalCoeffChannelGroup(2, "Acceleration Y", NodeEepromMap::CH_ACTION_SLOPE_2, NodeEepromMap::CH_ACTION_ID_2);
        addCalCoeffChannelGroup(3, "Acceleration Z", NodeEepromMap::CH_ACTION_SLOPE_3, NodeEepromMap::CH_ACTION_ID_3);

        bool supportsTilt = m_nodeInfo.firmwareVersion() >= VER_TILT_SUPPORTED;
        if(supportsTilt)
        {
            //add the tilt channels
            addCalCoeffChannelGroup(4, "Pitch", NodeEepromMap::CH_ACTION_SLOPE_4, NodeEepromMap::CH_ACTION_ID_4);
            addCalCoeffChannelGroup(5, "Roll", NodeEepromMap::CH_ACTION_SLOPE_5, NodeEepromMap::CH_ACTION_ID_5);
        }

        const ChannelMask ACCEL_CHS(BOOST_BINARY(00000111)); //ch1 - ch3
        m_channelGroups.emplace_back(ACCEL_CHS, "Acceleration X,Y,Z",
                                     ChannelGroup::SettingsMap {
                                         {WirelessTypes::chSetting_lowPassFilter, NodeEepromMap::LOW_PASS_FILTER_1},
                                         {WirelessTypes::chSetting_highPassFilter, NodeEepromMap::HIGH_PASS_FILTER_1},
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_1}
                                     });

        //Channels
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_acceleration, "Acceleration X", 20);
        m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_acceleration, "Acceleration Y", 20);
        m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_acceleration, "Acceleration Z", 20);

        if(supportsTilt)
        {
            m_channels.emplace_back(4, WirelessChannel::channel_4, WirelessTypes::chType_tilt, "Pitch", 20);
            m_channels.emplace_back(5, WirelessChannel::channel_5, WirelessTypes::chType_tilt, "Roll", 20);
        }
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

            return AvailableSampleRates::continuous_nonSync_glink200;

        case WirelessTypes::samplingMode_sync:
            if(dataCollectionMethod == WirelessTypes::collectionMethod_logOnly)
            {
                return AvailableSampleRates::continuous_log_glink200;
            }

            return AvailableSampleRates::continuous_sync_glink200;

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

    const WirelessTypes::DerivedChannelMasks NodeFeatures_glink200::channelsPerDerivedCategory() const
    {
        const ChannelMask ACCEL_CHS(BOOST_BINARY(00000111)); //ch1 - ch3

        static const WirelessTypes::DerivedChannelMasks result{
            {std::make_pair(WirelessTypes::derivedCategory_rms, ACCEL_CHS)},
            {std::make_pair(WirelessTypes::derivedCategory_peakToPeak, ACCEL_CHS)},
            {std::make_pair(WirelessTypes::derivedCategory_velocity, ACCEL_CHS)},
            {std::make_pair(WirelessTypes::derivedCategory_crestFactor, ACCEL_CHS)}
        };

        return result;
    }

    const WirelessTypes::SensorOutputModes NodeFeatures_glink200::sensorOutputModes() const
    {
        WirelessTypes::SensorOutputModes modes;

        if(m_nodeInfo.firmwareVersion() >= VER_TILT_SUPPORTED)
        {
            modes.push_back(WirelessTypes::sensorOutputMode_accel);
            modes.push_back(WirelessTypes::sensorOutputMode_tilt);
        }

        return modes;
    }
} // namespace mscl
