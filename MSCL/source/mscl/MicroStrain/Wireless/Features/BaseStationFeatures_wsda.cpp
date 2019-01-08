/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "BaseStationFeatures_wsda.h"

namespace mscl
{
    BaseStationFeatures_wsda::BaseStationFeatures_wsda(const BaseStationInfo& info):
        BaseStationFeatures(info)
    {
    }

    bool BaseStationFeatures_wsda::supportsRfSweepMode() const
    {
        return false;
    }

    bool BaseStationFeatures_wsda::supportsCustomRfSweepMode() const
    {
        return false;
    }

    WirelessTypes::TransmitPower BaseStationFeatures_wsda::maxTransmitPower(WirelessTypes::RegionCode region, WirelessTypes::CommProtocol commProtocol) const
    {
        if(region == WirelessTypes::region_japan)
        {
            return WirelessTypes::power_10dBm;
        }

        return BaseStationFeatures::maxTransmitPower(region, commProtocol);
    }

    WirelessTypes::TransmitPower BaseStationFeatures_wsda::minTransmitPower(WirelessTypes::RegionCode region, WirelessTypes::CommProtocol commProtocol) const
    {
        if(region == WirelessTypes::region_japan)
        {
            return WirelessTypes::power_5dBm;
        }

        return BaseStationFeatures::minTransmitPower(region, commProtocol);
    }
}