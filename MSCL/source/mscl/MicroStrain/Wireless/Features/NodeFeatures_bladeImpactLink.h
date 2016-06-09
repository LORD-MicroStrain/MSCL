/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_bladeImpactLink
    //    Contains information on features for the Blade Impact nodes.
    class NodeFeatures_bladeImpactLink: public NodeFeatures
    {
    public:
        virtual ~NodeFeatures_bladeImpactLink(){};

        //Constructor: NodeFeatures_bladeImpactLink
        //    Creates a NodeFeatures_bladeImpactLink object.
        NodeFeatures_bladeImpactLink(const NodeInfo& info);

    public:
        virtual const WirelessTypes::SamplingModes samplingModes() const override;

        virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode) const override;

        virtual const WirelessTypes::Filters lowPassFilters() const override;

        virtual const WirelessTypes::StorageLimitModes storageLimitModes() const;
    };
}