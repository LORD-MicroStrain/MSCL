/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "NodeFeatures.h"

namespace mscl
{    
    //API Class: NodeFeatures
    //    Contains information on which features are supported by a <WirelessNode>.
    class NodeFeatures_200series : public NodeFeatures
    {
    private:
        NodeFeatures_200series();                                           //disabled default constructor
        NodeFeatures_200series(const NodeFeatures_200series&);              //disabled copy constructor
        NodeFeatures_200series& operator=(const NodeFeatures_200series&);   //disable assignment operator

    public:
        virtual ~NodeFeatures_200series() {};

    protected:
        //Constructor: NodeFeatures_200series
        //    Creates a NodeFeatures_200series object.
        //
        //Parameters:
        //    info - A <NodeInfo> object representing standard information of the <WirelessNode>.
        NodeFeatures_200series(const NodeInfo& info);

    public:
        virtual WirelessTypes::TransmitPower maxTransmitPower(WirelessTypes::RegionCode region, WirelessTypes::CommProtocol commProtocol) const override;
        virtual WirelessTypes::TransmitPower minTransmitPower(WirelessTypes::RegionCode region, WirelessTypes::CommProtocol commProtocol) const override;
        virtual const WirelessTypes::TransmitPowers transmitPowers(WirelessTypes::CommProtocol commProtocol) const override;
        virtual const WirelessTypes::SamplingModes samplingModes() const override;
        virtual const WirelessTypes::DataFormats dataFormats() const override;
        virtual const WirelessTypes::StorageLimitModes storageLimitModes() const override;
    };
}