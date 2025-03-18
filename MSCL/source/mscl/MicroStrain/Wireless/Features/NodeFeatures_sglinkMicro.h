/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_sglinkMicro
    //    Contains information on features for the SG-Link-Micro node. Inherits from <NodeFeatures>.
    class NodeFeatures_sglinkMicro: public NodeFeatures
    {
        NodeFeatures_sglinkMicro();    //disabled default constructor

    public:
        ~NodeFeatures_sglinkMicro() override = default;

        //Constructor: NodeFeatures_sglinkMicro
        //    Creates a NodeFeatures_sglinkMicro object.
        NodeFeatures_sglinkMicro(const NodeInfo& info);

        bool supportsSensorDelayConfig() const override;

        const WirelessTypes::DataCollectionMethods dataCollectionMethods() const final;

        const WirelessTypes::DataFormats dataFormats() const override;

        const WirelessTypes::SamplingModes samplingModes() const override;
    };
}
