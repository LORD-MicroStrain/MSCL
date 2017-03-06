/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_mvpervlink
    //    Contains information on features for the mV/V-Link node. Inherits from <NodeFeatures>.
    class NodeFeatures_mvpervlink: public NodeFeatures
    {
    private:
        NodeFeatures_mvpervlink();    //disabled default constructor

    public:
        virtual ~NodeFeatures_mvpervlink() {};

        //Constructor: NodeFeatures_mvpervlink
        //    Creates a NodeFeatures_mvpervlink object.
        NodeFeatures_mvpervlink(const NodeInfo& info);

        virtual bool supportsLimitedDuration() const;

        virtual bool supportsSensorDelayConfig() const override;

        virtual const WirelessTypes::DataCollectionMethods dataCollectionMethods() const final;

        virtual const WirelessTypes::DataFormats dataFormats() const final;

        virtual const WirelessTypes::SamplingModes samplingModes() const final;

        virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const final;
    };
}