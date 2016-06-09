/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_iepeLink
    //    Contains information on features for the IEPE-Link.
    class NodeFeatures_iepeLink : public NodeFeatures
    {
    public:
        virtual ~NodeFeatures_iepeLink(){};

        //Constructor: NodeFeatures_iepeLink
        //    Creates a NodeFeatures_iepeLink object.
        NodeFeatures_iepeLink(const NodeInfo& info);

    public:
        virtual const WirelessTypes::SamplingModes samplingModes() const override;

        virtual const WirelessTypes::DataFormats dataFormats() const override;

        virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode) const override;

        virtual const WirelessTypes::Filters lowPassFilters() const override;

        virtual uint32 maxSweepsPerBurst(WirelessTypes::DataFormat dataFormat, const ChannelMask& channels) const override;
    };
}