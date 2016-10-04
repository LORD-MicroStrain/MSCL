/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "NodeFeatures_mvpervlink.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "mscl/Utils.h"

namespace mscl
{
    NodeFeatures_mvpervlink::NodeFeatures_mvpervlink(const NodeInfo& info):
        NodeFeatures(info)
    {
        static const ChannelMask DIFFERENTIAL_CHS(BOOST_BINARY(00000011));    //ch1 - ch2
        static const ChannelMask DIFFERENTIAL_CH1(BOOST_BINARY(00000001));    //ch1
        static const ChannelMask DIFFERENTIAL_CH2(BOOST_BINARY(00000010));    //ch2

        m_channelGroups.emplace_back(DIFFERENTIAL_CHS, "Differential Channels",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_inputRange, NodeEepromMap::HW_GAIN_1}}
        );

        m_channelGroups.emplace_back(DIFFERENTIAL_CH1, "Differential Channel 1",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_hardwareOffset, NodeEepromMap::HW_OFFSET_1},
                                         {WirelessTypes::chSetting_autoBalance, NodeEepromMap::HW_OFFSET_1}}
        );

        m_channelGroups.emplace_back(DIFFERENTIAL_CH2, "Differential Channel 2",
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_hardwareOffset, NodeEepromMap::HW_OFFSET_2},
                                         {WirelessTypes::chSetting_autoBalance, NodeEepromMap::HW_OFFSET_2}}
        );

        //Channels
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_fullDifferential);
    }

    bool NodeFeatures_mvpervlink::supportsLimitedDuration() const
    {
        return false;
    }

    bool NodeFeatures_mvpervlink::supportsSensorDelayConfig() const
    {
        return true;
    }

    const WirelessTypes::DataCollectionMethods NodeFeatures_mvpervlink::dataCollectionMethods() const
    {
        //build and return the data collection methods that are supported
        WirelessTypes::DataCollectionMethods result;
        result.push_back(WirelessTypes::collectionMethod_transmitOnly);
        return result;
    }

    const WirelessTypes::DataFormats NodeFeatures_mvpervlink::dataFormats() const
    {
        //build and return the data formats that are supported
        WirelessTypes::DataFormats result;
        result.push_back(WirelessTypes::dataFormat_raw_uint16);
        return result;
    }

    const WirelessTypes::SamplingModes NodeFeatures_mvpervlink::samplingModes() const
    {
        //build and return the sampling modes that are supported
        WirelessTypes::SamplingModes result;

        result.push_back(WirelessTypes::samplingMode_nonSync);

        return result;
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_mvpervlink::sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod) const
    {
        //the list of sample rates varies for each sampling mode
        switch(samplingMode)
        {
            case WirelessTypes::samplingMode_nonSync:
            {
                static const WirelessTypes::WirelessSampleRates continuousRates = {
                    {WirelessTypes::sampleRate_16Hz},
                    {WirelessTypes::sampleRate_8Hz},
                    {WirelessTypes::sampleRate_4Hz},
                    {WirelessTypes::sampleRate_2Hz},
                    {WirelessTypes::sampleRate_1Hz},
                    {WirelessTypes::sampleRate_2Sec}
                };
                return continuousRates;
            }

            default:
                throw Error_NotSupported("The sampling mode is not supported by this Node");
        }
    }
}