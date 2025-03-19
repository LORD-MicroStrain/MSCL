/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_shmlink2
    //    Contains information on features for the SHM-Link 2 node. Inherits from <NodeFeatures>.
    class NodeFeatures_shmlink2 : public NodeFeatures
    {
        NodeFeatures_shmlink2();    //disabled default constructor

    public:
        ~NodeFeatures_shmlink2() override = default;

        //Constructor: NodeFeatures_shmlink2
        //    Creates a NodeFeatures_shmlink2 object.
        NodeFeatures_shmlink2(const NodeInfo& info);

        const WirelessTypes::DataCollectionMethods dataCollectionMethods() const final;

        const WirelessTypes::DataFormats dataFormats() const final;

        const WirelessTypes::SamplingModes samplingModes() const final;

        const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        bool supportsLimitedDuration() const override;

        bool supportsFatigueConfig() const final;

        bool supportsYoungsModConfig() const final;

        bool supportsPoissonsRatioConfig() const final;

        bool supportsFatigueDebugModeConfig() const final;

        bool supportsFatigueModeConfig() const final;

        bool supportsHistogramConfig() const final;

        bool supportsHistogramRateConfig() const final;

        bool supportsHistogramEnableConfig() const override;

        bool supportsActivitySense() const final;

        bool supportsAutoCal_shm() const override;

        bool supportsSensorDelayConfig() const override;

        bool supportsSensorDelayAlwaysOn() const override;

        uint8 numDamageAngles() const final;

        uint8 numSnCurveSegments() const final;

        const WirelessTypes::WirelessSampleRates histogramTransmitRates() const final;

        const WirelessTypes::FatigueModes fatigueModes() const final;

        const uint32 minSensorDelay() const override;

        const uint32 defaultSensorDelay() const override;
    };
} // namespace mscl
