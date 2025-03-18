/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_iepeLink
    //    Contains information on features for the IEPE-Link.
    class NodeFeatures_iepeLink : public NodeFeatures
    {
    public:
        ~NodeFeatures_iepeLink() override = default;

        //Constructor: NodeFeatures_iepeLink
        //    Creates a NodeFeatures_iepeLink object.
        NodeFeatures_iepeLink(const NodeInfo& info);

    private:
        uint32 ramBufferSize() const override;

    public:
        bool supportsSensorDelayConfig() const override;

        const WirelessTypes::SamplingModes samplingModes() const override;

        const WirelessTypes::DataFormats dataFormats() const override;

        const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        const WirelessTypes::Filters antiAliasingFilters() const override;
    };
}
