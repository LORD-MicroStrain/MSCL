/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures_200series.h"

namespace mscl
{
    //Class: NodeFeatures_vlink200
    //    Contains information on features for the V-Link2 node. Inherits from <NodeFeatures>.
    class NodeFeatures_vlink200 : public NodeFeatures_200series
    {
        NodeFeatures_vlink200();    //disabled default constructor

    public:
        ~NodeFeatures_vlink200() override = default;

        //Constructor: NodeFeatures_vlink200
        //    Creates a NodeFeatures_vlink200 object.
        NodeFeatures_vlink200(const NodeInfo& info);

        bool supportsSensorDelayConfig() const override;

        bool supportsPoll() const override;

        const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        const WirelessTypes::Filters antiAliasingFilters() const override;

        uint32 minSensorDelay() const override;

        uint32 defaultSensorDelay() const override;
    };
} // namespace mscl
