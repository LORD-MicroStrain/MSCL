/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_sglinkMicro
    //    Contains information on features for the SG-Link-Micro node. Inherits from <NodeFeatures>.
    class NodeFeatures_sglinkMicro: public NodeFeatures
    {
    private:
        NodeFeatures_sglinkMicro();    //disabled default constructor

    public:
        virtual ~NodeFeatures_sglinkMicro() {};

        //Constructor: NodeFeatures_sglinkMicro
        //    Creates a NodeFeatures_sglinkMicro object.
        NodeFeatures_sglinkMicro(const NodeInfo& info);

        virtual const WirelessTypes::DataCollectionMethods dataCollectionMethods() const final;

        virtual const WirelessTypes::DataFormats dataFormats() const;

        virtual const WirelessTypes::SamplingModes samplingModes() const;
    };
}