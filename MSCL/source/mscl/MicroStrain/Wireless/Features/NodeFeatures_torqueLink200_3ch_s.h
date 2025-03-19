/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures_torqueLink200_3ch.h"

namespace mscl
{
    //Class: NodeFeatures_torqueLink200_3ch_s_s
    //    Contains information on features for the Torque-Link-200-3ch nodes. Inherits from <NodeFeatures>.
    class NodeFeatures_torqueLink200_3ch_s : public NodeFeatures_torqueLink200_3ch
    {
        NodeFeatures_torqueLink200_3ch_s();    //disabled default constructor

    public:
        ~NodeFeatures_torqueLink200_3ch_s() override = default;

        //Constructor: NodeFeatures_torqueLink200_3ch_s
        //    Creates a NodeFeatures_torqueLink200_3ch_s object.
        NodeFeatures_torqueLink200_3ch_s(const NodeInfo& info);

        const WirelessTypes::DerivedChannelMasks channelsPerDerivedCategory() const override;

        bool supportsPullUpResistor() const override;

        bool supportsDebounceFilter() const override;

        bool supportsExcitationVoltageConfig() const override;

        const WirelessTypes::Voltages excitationVoltages() const override;
    };
} // namespace mscl
