/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "BaseStationFeatures.h"

namespace mscl
{    
    //Class: BaseStationFeatures_usb200
    //    Contains information on features for the WSDA-200 USB BaseStation.
    class BaseStationFeatures_usb200 : public BaseStationFeatures
    {
    public:
        virtual ~BaseStationFeatures_usb200() {}

        //Constructor: BaseStationFeatures_usb200
        //    Creates a BaseStationFeatures_usb200 object.
        //
        //Parameters:
        //    info - A <BaseStationInfo> object representing standard information of the <BaseStation>.
        BaseStationFeatures_usb200(const BaseStationInfo& info);

        virtual WirelessTypes::TransmitPower maxTransmitPower(WirelessTypes::RegionCode region, WirelessTypes::CommProtocol commProtocol) const final;
        virtual WirelessTypes::TransmitPower minTransmitPower(WirelessTypes::RegionCode region, WirelessTypes::CommProtocol commProtocol) const final;
        virtual const WirelessTypes::TransmitPowers transmitPowers(WirelessTypes::CommProtocol commProtocol) const final;
        virtual bool supportsRfSweepMode() const final;
        virtual bool supportsCustomRfSweepMode() const final;
    };
}