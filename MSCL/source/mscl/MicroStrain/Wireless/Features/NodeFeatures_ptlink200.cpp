/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures_ptlink200.h"

#include "mscl/MicroStrain/SampleRate.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "mscl/MicroStrain/Wireless/Features/AvailableSampleRates.h"

namespace mscl
{
    NodeFeatures_ptlink200::NodeFeatures_ptlink200(const NodeInfo& info) :
        NodeFeatures_200series(info)
    {
        addCalCoeffChannelGroup_withFactoryCal(1, "Differential", NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1, NodeEepromMap::FACTORY_CH_ACTION_SLOPE_1, NodeEepromMap::FACTORY_CH_ACTION_ID_1);

        const ChannelMask DIFFERENTIAL_CHS(BOOST_BINARY(00000001));  //ch1

        m_channelGroups.emplace_back(DIFFERENTIAL_CHS, "Differential",
                                        ChannelGroup::SettingsMap{
                                            {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_1},
                                            { WirelessTypes::chSetting_lowPassFilter, NodeEepromMap::LOW_PASS_FILTER_1 }}
        );

        //Channels
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_fullDifferential, "Differential", 24);
    }

    bool NodeFeatures_ptlink200::supportsSensorDelayConfig() const
    {
        return true;
    }

    const WirelessTypes::DerivedChannelMasks NodeFeatures_ptlink200::channelsPerDerivedCategory() const
    {
        const ChannelMask ALL_CHS(BOOST_BINARY(00000001));

        const WirelessTypes::DerivedChannelMasks result = {
            {std::make_pair(WirelessTypes::derivedCategory_rms, ALL_CHS)},
            {std::make_pair(WirelessTypes::derivedCategory_peakToPeak, ALL_CHS)},
            {std::make_pair(WirelessTypes::derivedCategory_mean, ALL_CHS)}
        };

        return result;
    }

    const WirelessTypes::Filters NodeFeatures_ptlink200::lowPassFilters() const
    {
        static const WirelessTypes::Filters filters = {
            {WirelessTypes::filter_4416hz},
            {WirelessTypes::filter_1104hz},
            {WirelessTypes::filter_12_66hz}
        };
        return filters;
    }

    WirelessTypes::WirelessSampleRate NodeFeatures_ptlink200::maxSampleRateForLowPassFilter(WirelessTypes::Filter lowPassFilter,
                                                                                               WirelessTypes::SamplingMode samplingMode,
                                                                                               WirelessTypes::DataCollectionMethod dataCollectionMethod,
                                                                                               WirelessTypes::DataMode dataMode,
                                                                                               const ChannelMask& channels) const
    {
        (void)channels;

        //find the max sample rate allowed for the settling time
        SampleRate maxRate;

        switch(lowPassFilter)
        {
            case WirelessTypes::filter_4416hz:
                maxRate = SampleRate::Hertz(1024);
                break;

            case WirelessTypes::filter_1104hz:
                maxRate = SampleRate::Hertz(256);
                break;

            case WirelessTypes::filter_12_66hz:
                maxRate = SampleRate::Hertz(4);
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

    const WirelessTypes::VoltageType NodeFeatures_ptlink200::adcVoltageInputType() const
    {
        return WirelessTypes::VoltageType::voltageType_differential;
    }

    bool NodeFeatures_ptlink200::supportsPoll() const
    {
        return true;
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_ptlink200::sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const
    {
        (void)dataCollectionMethod;
        (void)dataMode;

        //the list of sample rates varies for each sampling mode
        switch(samplingMode)
        {
            case WirelessTypes::samplingMode_nonSync:
                return AvailableSampleRates::continuous;

            case WirelessTypes::samplingMode_sync:
                return AvailableSampleRates::continuous_sglink200;

            case WirelessTypes::samplingMode_syncBurst:
            case WirelessTypes::samplingMode_syncEvent:
                return AvailableSampleRates::burst_sglink200;

            default:
                throw Error_NotSupported("The sampling mode is not supported by this Node");
        }
    }

    const uint32 NodeFeatures_ptlink200::minSensorDelay() const
    {
        if (!supportsSensorDelayConfig())
        {
            throw Error_NotSupported("Sensor Delay is not supported by this Node.");
        }

        return static_cast<uint32>(TimeSpan::MilliSeconds(5).getMicroseconds());    //5 milliseconds
    }

    const uint32 NodeFeatures_ptlink200::defaultSensorDelay() const
    {
        if (!supportsSensorDelayConfig())
        {
            throw Error_NotSupported("Sensor Delay is not supported by this Node.");
        }

        return static_cast<uint32>(TimeSpan::MilliSeconds(10).getMicroseconds());    //10 milliseconds
    }
} // namespace mscl
