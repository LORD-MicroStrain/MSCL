/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_vlink
    //    Contains information on features for the V-Link node. Inherits from <NodeFeatures>.
    class NodeFeatures_vlink : public NodeFeatures
    {
        NodeFeatures_vlink();    //disabled default constructor

    public:
        ~NodeFeatures_vlink() override = default;

        //Constructor: NodeFeatures_vlink
        //    Creates a NodeFeatures_vlink object.
        NodeFeatures_vlink(const NodeInfo& info);

        bool supportsSensorDelayConfig() const override;

        const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        WirelessTypes::WirelessSampleRate maxSampleRate(WirelessTypes::SamplingMode samplingMode, const ChannelMask& channels, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        const uint32 minSensorDelay() const override;

        const uint32 maxSensorDelay() const override;

        const uint32 defaultSensorDelay() const override;
    };
} // namespace mscl
