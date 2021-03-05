/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

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

        virtual bool supportsSensorDelayConfig() const override;

        virtual const WirelessTypes::DataCollectionMethods dataCollectionMethods() const final;

        virtual const WirelessTypes::DataFormats dataFormats() const override;

        virtual const WirelessTypes::SamplingModes samplingModes() const override;
    };
}