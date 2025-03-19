/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_wirelessImpactSensor
    //    Contains information on features for the Wireless Impact nodes.
    class NodeFeatures_wirelessImpactSensor: public NodeFeatures
    {
    public:
        ~NodeFeatures_wirelessImpactSensor() override = default;

        //Constructor: NodeFeatures_wirelessImpactSensor
        //    Creates a NodeFeatures_wirelessImpactSensor object.
        NodeFeatures_wirelessImpactSensor(const NodeInfo& info);

    private:
        uint32 ramBufferSize() const override;

    public:
        const WirelessTypes::SamplingModes samplingModes() const override;

        const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        const WirelessTypes::Filters antiAliasingFilters() const override;

        const WirelessTypes::StorageLimitModes storageLimitModes() const override;
    };
} // namespace mscl
