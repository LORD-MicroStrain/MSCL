/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures_200series.h"

namespace mscl
{
    //Class: NodeFeatures_glink200
    //    Contains information on features for the G-Link 200 node.
    class NodeFeatures_glink200: public NodeFeatures_200series
    {
    public:
        ~NodeFeatures_glink200() override = default;

        //Constructor: NodeFeatures_glink200
        //    Creates a NodeFeatures_glink200 object.
        NodeFeatures_glink200(const NodeInfo& info);

    private:
        static const Version VER_TILT_SUPPORTED;

    public:
        const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        const WirelessTypes::DataFormats dataFormats() const override;

        const WirelessTypes::Filters lowPassFilters() const override;

        const WirelessTypes::HighPassFilters highPassFilters() const override;

        const WirelessTypes::DerivedChannelMasks channelsPerDerivedCategory() const override;

        const WirelessTypes::SensorOutputModes sensorOutputModes() const override;
    };
} // namespace mscl
