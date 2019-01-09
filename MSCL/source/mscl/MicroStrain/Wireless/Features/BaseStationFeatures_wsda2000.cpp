/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "BaseStationFeatures_wsda2000.h"

namespace mscl
{
    BaseStationFeatures_wsda2000::BaseStationFeatures_wsda2000(const BaseStationInfo& info):
        BaseStationFeatures(info)
    {
    }

    bool BaseStationFeatures_wsda2000::supportsRfSweepMode() const
    {
        static const Version MIN_RF_SWEEP_FW(5, 39166);

        return (m_baseInfo.firmwareVersion() >= MIN_RF_SWEEP_FW);
    }

    bool BaseStationFeatures_wsda2000::supportsCustomRfSweepMode() const
    {
        static const Version MIN_RF_SWEEP_FW(5, 39166);

        return (m_baseInfo.firmwareVersion() >= MIN_RF_SWEEP_FW);
    }

    WirelessTypes::TransmitPower BaseStationFeatures_wsda2000::maxTransmitPower(WirelessTypes::RegionCode region, WirelessTypes::CommProtocol commProtocol) const
    {
        if(region == WirelessTypes::region_japan)
        {
            WirelessTypes::TransmitPowers result;

            if(commProtocol == WirelessTypes::commProtocol_lxrs)
            {
                return WirelessTypes::power_16dBm;
            }

            return WirelessTypes::power_11dBm;
        }

        return BaseStationFeatures::maxTransmitPower(region, commProtocol);
    }

    WirelessTypes::TransmitPower BaseStationFeatures_wsda2000::minTransmitPower(WirelessTypes::RegionCode region, WirelessTypes::CommProtocol commProtocol) const
    {
        if(region == WirelessTypes::region_japan)
        {
            WirelessTypes::TransmitPowers result;

            if(commProtocol == WirelessTypes::commProtocol_lxrs)
            {
                return WirelessTypes::power_5dBm;
            }

            return WirelessTypes::power_0dBm;
        }

        return BaseStationFeatures::minTransmitPower(region, commProtocol);
    }

    const WirelessTypes::TransmitPowers BaseStationFeatures_wsda2000::transmitPowers(WirelessTypes::CommProtocol commProtocol) const
    {
        WirelessTypes::RegionCode region = m_baseInfo.regionCode();

        //japan has a custom list of transmit powers for this Node
        if(region == WirelessTypes::region_japan)
        {
            WirelessTypes::TransmitPowers result{
                WirelessTypes::power_16dBm,
                WirelessTypes::power_11dBm,
                WirelessTypes::power_5dBm,
                WirelessTypes::power_0dBm
            };

            WirelessTypes::TransmitPower maxPower = maxTransmitPower(region, commProtocol);
            WirelessTypes::TransmitPower minPower = minTransmitPower(region, commProtocol);

            narrowDownTxPowers(result, minPower, maxPower);

            return result;
        }

        return BaseStationFeatures::transmitPowers(commProtocol);
    }
}