/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#pragma once

#include "NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_sglinkoem
    //    Contains information on features for the SG-Link-OEM node. Inherits from <NodeFeatures>.
    class NodeFeatures_sglinkoem : public NodeFeatures
    {
    private:
        NodeFeatures_sglinkoem();    //disabled default constructor

    public:
        virtual ~NodeFeatures_sglinkoem(){};

        //Constructor: NodeFeatures_sglinkoem
        //    Creates a NodeFeatures_sglinkoem object.
        NodeFeatures_sglinkoem(const NodeInfo& info);

        virtual bool supportsSensorDelayConfig() const override;

        const uint32 minSensorDelay() const override;

        const uint32 maxSensorDelay() const override;

        const uint32 defaultSensorDelay() const override;
    };
}