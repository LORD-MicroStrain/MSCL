/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "BaseStationFeatures.h"

namespace mscl
{    
    //Class: BaseStationFeatures_wsda
    //    Contains information on features for the WSDA.
    class BaseStationFeatures_wsda : public BaseStationFeatures
    {
    public:
        virtual ~BaseStationFeatures_wsda() {}

        //Constructor: BaseStationFeatures_wsda
        //    Creates a BaseStationFeatures_wsda object.
        //
        //Parameters:
        //    info - A <BaseStationInfo> object representing standard information of the <BaseStation>.
        BaseStationFeatures_wsda(const BaseStationInfo& info);

        virtual WirelessTypes::TransmitPower maxTransmitPower(WirelessTypes::RegionCode region, WirelessTypes::CommProtocol commProtocol) const final;
        virtual WirelessTypes::TransmitPower minTransmitPower(WirelessTypes::RegionCode region, WirelessTypes::CommProtocol commProtocol) const final;
        virtual bool supportsRfSweepMode() const final;
        virtual bool supportsCustomRfSweepMode() const final;
    };
}