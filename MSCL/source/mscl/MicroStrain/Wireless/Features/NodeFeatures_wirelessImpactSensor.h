/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_wirelessImpactSensor
    //    Contains information on features for the Wireless Impact nodes.
    class NodeFeatures_wirelessImpactSensor: public NodeFeatures
    {
    public:
        virtual ~NodeFeatures_wirelessImpactSensor(){};

        //Constructor: NodeFeatures_wirelessImpactSensor
        //    Creates a NodeFeatures_wirelessImpactSensor object.
        NodeFeatures_wirelessImpactSensor(const NodeInfo& info);

    private:
        virtual uint32 ramBufferSize() const override;

    public:
        virtual const WirelessTypes::SamplingModes samplingModes() const override;

        virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        virtual const WirelessTypes::Filters antiAliasingFilters() const override;

        virtual const WirelessTypes::StorageLimitModes storageLimitModes() const;
    };
}