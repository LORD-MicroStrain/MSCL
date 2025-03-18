/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_shmlink
    //    Contains information on features for the SHM-Link node. Inherits from <NodeFeatures>.
    class NodeFeatures_shmlink : public NodeFeatures
    {
        NodeFeatures_shmlink();    //disabled default constructor

    public:
        ~NodeFeatures_shmlink() override = default;

        //Constructor: NodeFeatures_shmlink
        //    Creates a NodeFeatures_shmlink object.
        NodeFeatures_shmlink(const NodeInfo& info);

        bool supportsFatigueConfig() const final;

        bool supportsYoungsModConfig() const final;

        bool supportsPoissonsRatioConfig() const final;

        bool supportsFatigueDebugModeConfig() const final;

        bool supportsHistogramConfig() const final;

        bool supportsHistogramRateConfig() const final;

        bool supportsHistogramEnableConfig() const final;

        bool supportsSensorDelayConfig() const final;

        bool supportsSensorDelayAlwaysOn() const final;

        uint8 numDamageAngles() const final;

        uint8 numSnCurveSegments() const final;

        const WirelessTypes::WirelessSampleRates histogramTransmitRates() const final;

        const WirelessTypes::FatigueModes fatigueModes() const final;
    };
}
