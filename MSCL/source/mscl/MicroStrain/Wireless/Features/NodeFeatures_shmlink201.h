/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures_200series.h"

namespace mscl
{
    //Class: NodeFeatures_shmlink201
    //    Contains information on features for the SHM-Link 2 node.
    class NodeFeatures_shmlink201 : public NodeFeatures_200series
    {
    private:
        NodeFeatures_shmlink201();    //disabled default constructor

    public:
        virtual ~NodeFeatures_shmlink201() {};

        //Constructor: NodeFeatures_shmlink201
        //    Creates a NodeFeatures_shmlink201 object.
        NodeFeatures_shmlink201(const NodeInfo& info);

    public:
        virtual const WirelessTypes::DataCollectionMethods dataCollectionMethods() const final;

        virtual const WirelessTypes::DataFormats dataFormats() const final;

        virtual const WirelessTypes::Filters lowPassFilters() const override;

        virtual const WirelessTypes::SamplingModes samplingModes() const final;

        virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        virtual bool supportsFatigueConfig() const final;

        virtual bool supportsYoungsModConfig() const final;

        virtual bool supportsPoissonsRatioConfig() const final;

        virtual bool supportsFatigueDebugModeConfig() const final;

        virtual bool supportsFatigueModeConfig() const final;

        virtual bool supportsHistogramConfig() const final;

        virtual bool supportsHistogramRateConfig() const final;

        virtual bool supportsHistogramEnableConfig() const;

        virtual bool supportsActivitySense() const final;

        virtual bool supportsAutoCal_shm201() const;

        virtual bool supportsSensorDelayConfig() const override;

        virtual bool supportsSensorDelayAlwaysOn() const override;

        virtual uint8 numDamageAngles() const final;

        virtual uint8 numSnCurveSegments() const final;

        virtual const WirelessTypes::VoltageType adcVoltageInputType() const override;

        virtual const WirelessTypes::WirelessSampleRates histogramTransmitRates() const final;

        virtual const WirelessTypes::FatigueModes fatigueModes() const final;
    };
}