/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures_sglink200oem.h"

#include "mscl/MicroStrain/SampleRate.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "mscl/MicroStrain/Wireless/Features/AvailableSampleRates.h"

namespace mscl
{
    NodeFeatures_sglink200oem::NodeFeatures_sglink200oem(const NodeInfo& info) :
        NodeFeatures_200series(info)
    {
        addCalCoeffChannelGroup(1, "Differential", NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
        addCalCoeffChannelGroup(2, "Single-ended", NodeEepromMap::CH_ACTION_SLOPE_2, NodeEepromMap::CH_ACTION_ID_2);
        addCalCoeffChannelGroup(5, "Pulse Frequency", NodeEepromMap::CH_ACTION_SLOPE_5, NodeEepromMap::CH_ACTION_ID_5);
        addCalCoeffChannelGroup(6, "Total Pulses", NodeEepromMap::CH_ACTION_SLOPE_6, NodeEepromMap::CH_ACTION_ID_6);

        const ChannelMask DIFFERENTIAL_CHS(BOOST_BINARY(00000001));  //ch1
        const ChannelMask SINGLE_ENDED_CHS(BOOST_BINARY(00000010));  //ch2
        const ChannelMask PULSE_CHS(BOOST_BINARY(00110000));         //ch5 and ch6

        if(info.firmwareVersion() >= Version(12, 42801))
        {
            m_channelGroups.emplace_back(DIFFERENTIAL_CHS, "Differential",
                                         ChannelGroup::SettingsMap{
                                             {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_1},
                                             {WirelessTypes::chSetting_autoShuntCal, NodeEepromMap::CH_ACTION_SLOPE_1}}
            );

            m_channelGroups.emplace_back(SINGLE_ENDED_CHS, "Single-ended",
                                         ChannelGroup::SettingsMap{
                                             {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_2}}
            );

            //ch1 and ch2 configured with 1 low pass filter setting in this firmware
            m_channelGroups.emplace_back(ChannelMask(BOOST_BINARY(00000011)), "Analog Input",
                                         ChannelGroup::SettingsMap{
                                             {WirelessTypes::chSetting_lowPassFilter, NodeEepromMap::LOW_PASS_FILTER_1}}
            );
        }
        else
        {
            m_channelGroups.emplace_back(DIFFERENTIAL_CHS, "Differential",
                                         ChannelGroup::SettingsMap{
                                             {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_1},
                                             {WirelessTypes::chSetting_lowPassFilter, NodeEepromMap::LOW_PASS_FILTER_1},
                                             {WirelessTypes::chSetting_autoShuntCal, NodeEepromMap::CH_ACTION_SLOPE_1}}
            );

            m_channelGroups.emplace_back(SINGLE_ENDED_CHS, "Single-ended",
                                         ChannelGroup::SettingsMap{
                                             {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_2},
                                             {WirelessTypes::chSetting_lowPassFilter, NodeEepromMap::LOW_PASS_FILTER_2}}
            );
        }

        m_channelGroups.emplace_back(PULSE_CHS, "Pulse Input",
                                     ChannelGroup::SettingsMap{
                                     {WirelessTypes::chSetting_debounceFilter, NodeEepromMap::DEBOUNCE_FILTER},
                                     {WirelessTypes::chSetting_pullUpResistor, NodeEepromMap::INTERNAL_PULLUP_RESISTOR}}
        );

        //Channels
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_fullDifferential, "Differential", 24);
        m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_singleEnded, "Single-ended", 24);
        m_channels.emplace_back(5, WirelessChannel::channel_5, WirelessTypes::chType_digital, "Pulse Frequency");
        m_channels.emplace_back(6, WirelessChannel::channel_6, WirelessTypes::chType_digital, "Total Pulses");
    }

    bool NodeFeatures_sglink200oem::supportsSensorDelayConfig() const
    {
        return true;
    }

    const WirelessTypes::DerivedChannelMasks NodeFeatures_sglink200oem::channelsPerDerivedCategory() const
    {
        const ChannelMask ALL_CHS(BOOST_BINARY(00110011));

        const WirelessTypes::DerivedChannelMasks result = {
            {std::make_pair(WirelessTypes::derivedCategory_rms, ALL_CHS)},
            {std::make_pair(WirelessTypes::derivedCategory_peakToPeak, ALL_CHS)},
            {std::make_pair(WirelessTypes::derivedCategory_mean, ALL_CHS)}
        };

        return result;
    }

    const WirelessTypes::Filters NodeFeatures_sglink200oem::lowPassFilters() const
    {
        static const WirelessTypes::Filters filters = {
            {WirelessTypes::filter_4416hz},
            {WirelessTypes::filter_1104hz},
            {WirelessTypes::filter_12_66hz}
        };
        return filters;
    }

    WirelessTypes::WirelessSampleRate NodeFeatures_sglink200oem::maxSampleRateForLowPassFilter(WirelessTypes::Filter lowPassFilter,
                                                                                               WirelessTypes::SamplingMode samplingMode,
                                                                                               WirelessTypes::DataCollectionMethod dataCollectionMethod,
                                                                                               WirelessTypes::DataMode dataMode,
                                                                                               const ChannelMask& channels) const
    {
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

    const WirelessTypes::Voltages NodeFeatures_sglink200oem::excitationVoltages() const
    {
        static const WirelessTypes::Voltages excitationVoltages = {
            {WirelessTypes::voltage_2500mV},
            {WirelessTypes::voltage_1500mV}
        };
        return excitationVoltages;
    }

    const WirelessTypes::VoltageType NodeFeatures_sglink200oem::adcVoltageInputType() const
    {
        return WirelessTypes::VoltageType::voltageType_differential;
    }

    bool NodeFeatures_sglink200oem::supportsPullUpResistor() const
    {
        return true;
    }

    bool NodeFeatures_sglink200oem::supportsExcitationVoltageConfig() const
    {
        return true;
    }

    bool NodeFeatures_sglink200oem::supportsPoll() const
    {
        static const Version MIN_POLL_FW(12, 44849);

        return m_nodeInfo.firmwareVersion() >= MIN_POLL_FW;
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_sglink200oem::sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const
    {
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
} // namespace mscl
