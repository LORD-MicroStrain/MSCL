/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures_200series.h"

namespace mscl
{
    //Class: NodeFeatures_shmlink201FullBridge
    //    Contains information on features for the SHM-Link-201 Full Bridge node.
    class NodeFeatures_shmlink201FullBridge : public NodeFeatures_200series
    {
        NodeFeatures_shmlink201FullBridge() = delete;    //disabled default constructor

    public:
        ~NodeFeatures_shmlink201FullBridge() override = default;
        NodeFeatures_shmlink201FullBridge(const NodeInfo& info);

        const WirelessTypes::DataCollectionMethods dataCollectionMethods() const final;

        const WirelessTypes::DataFormats dataFormats() const final;

        const WirelessTypes::Filters lowPassFilters() const override;

        const WirelessTypes::SamplingModes samplingModes() const final;

        const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        bool supportsHistogramConfig() const final;

        bool supportsHistogramRateConfig() const final;

        virtual bool supportsHistogramEnableConfig() const;

        bool supportsActivitySense() const final;

        virtual bool supportsAutoCal_shm201() const;

        bool supportsSensorDelayConfig() const override;

        bool supportsSensorDelayAlwaysOn() const override;

        const WirelessTypes::VoltageType adcVoltageInputType() const override;

        const WirelessTypes::WirelessSampleRates histogramTransmitRates() const final;

        bool supportsGaugeResistance() const final;

        bool supportsNumActiveGauges() const final;

        const uint32 minSensorDelay() const override;

        const uint32 defaultSensorDelay() const override;
    };
} // namespace mscl
