/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_tclink3ch
    //    Contains information on features for the CF-Bearing-Temp-Link Node.
    class NodeFeatures_cfBearing : public NodeFeatures
    {
    public:
        ~NodeFeatures_cfBearing() override = default;

        //Constructor: NodeFeatures_cfBearing
        //    Creates a NodeFeatures_cfBearing object.
        NodeFeatures_cfBearing(const NodeInfo& info);

        const WirelessTypes::DataCollectionMethods dataCollectionMethods() const final;

        const WirelessTypes::SamplingModes samplingModes() const override;

        const WirelessTypes::DataFormats dataFormats() const override;

        const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;
    };
} // namespace mscl
