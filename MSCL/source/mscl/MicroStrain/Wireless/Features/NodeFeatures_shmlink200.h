/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures_200series.h"

namespace mscl
{
    //Class: NodeFeatures_shmlink200
    //    Contains information on features for the SHM-Link 200 node.
    class NodeFeatures_shmlink200 : public NodeFeatures_200series
    {
    private:
        NodeFeatures_shmlink200();    //disabled default constructor

    public:
        virtual ~NodeFeatures_shmlink200() {};

        //Constructor: NodeFeatures_shmlink200
        //    Creates a NodeFeatures_shmlink200 object.
        NodeFeatures_shmlink200(const NodeInfo& info);

    public:
        virtual const WirelessTypes::DataFormats dataFormats() const final;

        virtual const WirelessTypes::SamplingModes samplingModes() const final;

        virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        virtual bool supportsHistogramConfig() const final;

        virtual bool supportsHistogramRateConfig() const final;

        virtual bool supportsHistogramEnableConfig() const;

        virtual bool supportsActivitySense() const final;

        virtual bool supportsAutoCal_shm() const;

        virtual bool supportsSensorDelayConfig() const override;

        virtual bool supportsSensorDelayAlwaysOn() const override;

        virtual const WirelessTypes::WirelessSampleRates histogramTransmitRates() const final;
    };
}