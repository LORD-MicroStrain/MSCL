/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_tclink3ch
    //    Contains information on features for the CF-Bearing-Temp-Link Node.
    class NodeFeatures_cfBearing : public NodeFeatures
    {
    public:
        virtual ~NodeFeatures_cfBearing() {};

        //Constructor: NodeFeatures_cfBearing
        //    Creates a NodeFeatures_cfBearing object.
        NodeFeatures_cfBearing(const NodeInfo& info);

        virtual const WirelessTypes::DataCollectionMethods dataCollectionMethods() const final;

        virtual const WirelessTypes::SamplingModes samplingModes() const override;

        virtual const WirelessTypes::DataFormats dataFormats() const override;

        virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;
    };
}