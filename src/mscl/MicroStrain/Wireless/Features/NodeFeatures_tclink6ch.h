/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_tclink6ch
    //    Contains information on features for the TC-Link 6CH Node.
    class NodeFeatures_tclink6ch : public NodeFeatures
    {
    public:
        ~NodeFeatures_tclink6ch() override = default;

        //Constructor: NodeFeatures_tclink6ch
        //    Creates a NodeFeatures_tclink6ch object.
        NodeFeatures_tclink6ch(const NodeInfo& info);

        const WirelessTypes::SamplingModes samplingModes() const override;

        const WirelessTypes::DataFormats dataFormats() const override;

        const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        WirelessTypes::SettlingTime maxFilterSettlingTime(const SampleRate& rate) const override;

        WirelessTypes::WirelessSampleRate maxSampleRateForSettlingTime(WirelessTypes::SettlingTime filterSettlingTime, WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;
    };
} // namespace mscl
