/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures_200series.h"

namespace mscl
{
    //Class: NodeFeatures_shmlink210
    //    Contains information on features for the SHM-Link 2 node.
    class NodeFeatures_shmlink210 : public NodeFeatures_200series
    {
        NodeFeatures_shmlink210();    //disabled default constructor

    public:
        ~NodeFeatures_shmlink210() override = default;

        //Constructor: NodeFeatures_shmlink210
        //    Creates a NodeFeatures_shmlink210 object.
        NodeFeatures_shmlink210(const NodeInfo& info);

        const WirelessTypes::DataCollectionMethods dataCollectionMethods() const final;

        const WirelessTypes::DataFormats dataFormats() const final;

        const WirelessTypes::Filters lowPassFilters() const override;

        const WirelessTypes::SamplingModes samplingModes() const final;

        const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        bool supportsExcitationVoltageConfig() const override;

        bool supportsFatigueConfig() const final;

        bool supportsYoungsModConfig() const final;

        bool supportsPoissonsRatioConfig() const final;

        bool supportsFatigueDebugModeConfig() const final;

        bool supportsFatigueModeConfig() const final;

        bool supportsHistogramConfig() const final;

        bool supportsHistogramRateConfig() const final;

        bool supportsHistogramEnableConfig() const override;

        bool supportsActivitySense() const final;

        bool supportsAutoCal_shm201() const override;

        bool supportsSensorDelayConfig() const override;

        bool supportsSensorDelayAlwaysOn() const override;

        uint8 numDamageAngles() const final;

        uint8 numSnCurveSegments() const final;

        const WirelessTypes::Voltages excitationVoltages() const override;

        WirelessTypes::VoltageType adcVoltageInputType() const override;

        const WirelessTypes::WirelessSampleRates histogramTransmitRates() const final;

        const WirelessTypes::FatigueModes fatigueModes() const final;

        uint32 minSensorDelay() const override;

        uint32 defaultSensorDelay() const override;
    };
} // namespace mscl
