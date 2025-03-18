/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_envlinkMini
    //    Contains information on features for the ENV-Link Mini Node.
    class NodeFeatures_envlinkMini : public NodeFeatures
    {
    public:
        ~NodeFeatures_envlinkMini() override = default;

        //Constructor: NodeFeatures_envlinkMini
        //    Creates a NodeFeatures_envlinkMini object.
        NodeFeatures_envlinkMini(const NodeInfo& info);

        bool supportsSensorDelayConfig() const override;

        const WirelessTypes::SamplingModes samplingModes() const override;

        const WirelessTypes::DataFormats dataFormats() const override;

        const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        WirelessTypes::SettlingTime maxFilterSettlingTime(const SampleRate& rate) const override;

        WirelessTypes::WirelessSampleRate maxSampleRateForSettlingTime(WirelessTypes::SettlingTime filterSettlingTime, WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;
    };
}
