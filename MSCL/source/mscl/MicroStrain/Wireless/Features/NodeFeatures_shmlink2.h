/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_shmlink2
    //    Contains information on features for the SHM-Link 2 node. Inherits from <NodeFeatures>.
    class NodeFeatures_shmlink2 : public NodeFeatures
    {
    private:
        NodeFeatures_shmlink2();    //disabled default constructor

    public:
        virtual ~NodeFeatures_shmlink2() {};

        //Constructor: NodeFeatures_shmlink2
        //    Creates a NodeFeatures_shmlink2 object.
        NodeFeatures_shmlink2(const NodeInfo& info);

    public:
        virtual WirelessTypes::TransmitPower maxTransmitPower(WirelessTypes::RegionCode region, WirelessTypes::CommProtocol commProtocol) const final;

        virtual WirelessTypes::TransmitPower minTransmitPower(WirelessTypes::RegionCode region, WirelessTypes::CommProtocol commProtocol) const final;

        virtual const WirelessTypes::DataCollectionMethods dataCollectionMethods() const final;

        virtual const WirelessTypes::DataFormats dataFormats() const final;

        virtual const WirelessTypes::SamplingModes samplingModes() const final;

        virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        virtual bool supportsLimitedDuration() const;

        virtual bool supportsFatigueConfig() const final;

        virtual bool supportsYoungsModConfig() const final;

        virtual bool supportsPoissonsRatioConfig() const final;

        virtual bool supportsFatigueDebugModeConfig() const final;

        virtual bool supportsFatigueModeConfig() const final;

        virtual bool supportsHistogramConfig() const final;

        virtual bool supportsHistogramRateConfig() const final;

        virtual bool supportsHistogramEnableConfig() const;

        virtual bool supportsActivitySense() const final;

        virtual bool supportsAutoCal_shm() const override;

        virtual bool supportsSensorDelayConfig() const override;

        virtual bool supportsSensorDelayAlwaysOn() const override;

        virtual uint8 numDamageAngles() const final;

        virtual uint8 numSnCurveSegments() const final;

        virtual const WirelessTypes::WirelessSampleRates histogramTransmitRates() const final;

        virtual const WirelessTypes::FatigueModes fatigueModes() const final;
    };
}