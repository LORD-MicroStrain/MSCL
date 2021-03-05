/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/Wireless/WirelessTypes.h"
#include "NodeInfo.h"

namespace mscl
{
    //Class: AvailableTransmitPowers
    //  contains functions for getting the available transmit powers for devices
    class AvailableTransmitPowers
    {
    public:
        //Function: get
        //  Gets a list of transmit powers for the given <NodeInfo> and <WirelessTypes::CommProtocol>.
        //  Note: this function should only be used for the old, pre-200-series, nodes.
        static const WirelessTypes::TransmitPowers get(const NodeInfo& info, WirelessTypes::CommProtocol commProtocol);

        //Function: get200series
        //  Gets a list of transmit powers for the given <NodeInfo> and <WirelessTypes::CommProtocol>.
        //  Note: this function should only be used for the 200-series nodes.
        static const WirelessTypes::TransmitPowers get200series(const NodeInfo& info, WirelessTypes::CommProtocol commProtocol);

        //Function: get
        //  Gets a list of transmit powers for the given information.
        static const WirelessTypes::TransmitPowers get(WirelessTypes::RegionCode region, WirelessModels::BaseModel model, const Version& fwVersion, WirelessTypes::CommProtocol commProtocol);
    };
}