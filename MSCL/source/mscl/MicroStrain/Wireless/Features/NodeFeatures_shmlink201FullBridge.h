/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures_200series.h"

namespace mscl
{
    //Class: NodeFeatures_shmlink201FullBridge
    //    Contains information on features for the SHM-Link-201 Full Bridge node.
    class NodeFeatures_shmlink201FullBridge : public NodeFeatures_200series
    {
    private:
        NodeFeatures_shmlink201FullBridge() = delete;    //disabled default constructor

    public:
        virtual ~NodeFeatures_shmlink201FullBridge() {};
        NodeFeatures_shmlink201FullBridge(const NodeInfo& info);

    public:
        virtual const WirelessTypes::DataCollectionMethods dataCollectionMethods() const final;

        virtual const WirelessTypes::DataFormats dataFormats() const final;

        virtual const WirelessTypes::Filters lowPassFilters() const override;

        virtual const WirelessTypes::SamplingModes samplingModes() const final;

        virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        virtual bool supportsHistogramConfig() const final;

        virtual bool supportsHistogramRateConfig() const final;

        virtual bool supportsHistogramEnableConfig() const;

        virtual bool supportsActivitySense() const final;

        virtual bool supportsAutoCal_shm201() const;

        virtual bool supportsSensorDelayConfig() const override;

        virtual bool supportsSensorDelayAlwaysOn() const override;

        virtual const WirelessTypes::VoltageType adcVoltageInputType() const override;

        virtual const WirelessTypes::WirelessSampleRates histogramTransmitRates() const final;

        virtual bool supportsGaugeResistance() const final;

        virtual bool supportsNumActiveGauges() const final;
    };
}