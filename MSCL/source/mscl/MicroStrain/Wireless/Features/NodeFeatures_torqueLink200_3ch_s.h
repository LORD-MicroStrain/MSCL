/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#pragma once

#include "NodeFeatures_torqueLink200_3ch.h"

namespace mscl
{
    //Class: NodeFeatures_torqueLink200_3ch_s_s
    //    Contains information on features for the Torque-Link-200-3ch nodes. Inherits from <NodeFeatures>.
    class NodeFeatures_torqueLink200_3ch_s: public NodeFeatures_torqueLink200_3ch
    {
    private:
        NodeFeatures_torqueLink200_3ch_s();    //disabled default constructor

    public:
        virtual ~NodeFeatures_torqueLink200_3ch_s(){};

        //Constructor: NodeFeatures_torqueLink200_3ch_s
        //    Creates a NodeFeatures_torqueLink200_3ch_s object.
        NodeFeatures_torqueLink200_3ch_s(const NodeInfo& info);

        virtual const WirelessTypes::DerivedChannelMasks channelsPerDerivedCategory() const override;

        virtual bool supportsPullUpResistor() const override;

        virtual bool supportsDebounceFilter() const override;

        virtual bool supportsExcitationVoltageConfig() const override;

        virtual const WirelessTypes::Voltages excitationVoltages() const override;
    };
}

