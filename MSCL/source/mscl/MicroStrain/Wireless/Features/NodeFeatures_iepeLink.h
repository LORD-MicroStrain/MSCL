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
        //Function: samplingModes
        //    Gets a list of the <WirelessTypes::SamplingMode>s that are supported by this Node.
        virtual const WirelessTypes::SamplingModes samplingModes() const override;

        //Function: dataFormats
        //    Gets a list of the <WirelessTypes::DataFormat>s that are supported by this Node.
        virtual const WirelessTypes::DataFormats dataFormats() const override;

        //Function: sampleRates
        //    Gets a list of the <WirelessTypes::WirelessSampleRates> that are supported by this Node for the given sampling mode.
        virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode) const override;

        //Function: maxSweepsPerBurst
        //    Gets the maximum number of sweeps per burst that can be assigned for a Burst Sync Sampling session.
        virtual uint32 maxSweepsPerBurst(WirelessTypes::DataFormat dataFormat, const ChannelMask& channels) const override;
    };
}