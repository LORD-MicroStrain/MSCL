/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_envlinkPro
    //    Contains information on features for the ENV-Link Pro Node.
    class NodeFeatures_envlinkPro : public NodeFeatures
    {
    public:
        ~NodeFeatures_envlinkPro() override = default;

        //Constructor: NodeFeatures_envlinkPro
        //    Creates a NodeFeatures_envlinkPro object.
        NodeFeatures_envlinkPro(const NodeInfo& info);

        bool supportsSensorDelayConfig() const override;

        const WirelessTypes::SamplingModes samplingModes() const override;

        const WirelessTypes::DataFormats dataFormats() const override;

        const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        WirelessTypes::SettlingTime maxFilterSettlingTime(const SampleRate& rate) const override;

        WirelessTypes::WirelessSampleRate maxSampleRateForSettlingTime(WirelessTypes::SettlingTime filterSettlingTime, WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;
    };
} // namespace mscl
