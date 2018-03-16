/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

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
        if(m_baseInfo.model() == WirelessModels::base_wsda_2000)
        {
            static const Version MIN_RF_SWEEP_FW(5, 39166);

            return (m_baseInfo.firmwareVersion() >= MIN_RF_SWEEP_FW);
        }

        return false;
    }

    bool BaseStationFeatures_wsda::supportsCustomRfSweepMode() const
    {
        if(m_baseInfo.model() == WirelessModels::base_wsda_2000)
        {
            static const Version MIN_RF_SWEEP_FW(5, 39166);

            return (m_baseInfo.firmwareVersion() >= MIN_RF_SWEEP_FW);
        }

        return false;
    }

    WirelessTypes::TransmitPower BaseStationFeatures_wsda::maxTransmitPower(WirelessTypes::RegionCode region, WirelessTypes::CommProtocol commProtocol) const
    {
        if(region == WirelessTypes::region_japan)
        {
            WirelessTypes::TransmitPowers result;

            if(commProtocol == WirelessTypes::commProtocol_lxrs)
            {
                return WirelessTypes::power_16dBm;
            }

            return WirelessTypes::power_10dBm;
        }

        return BaseStationFeatures::maxTransmitPower(region, commProtocol);
    }

    WirelessTypes::TransmitPower BaseStationFeatures_wsda::minTransmitPower(WirelessTypes::RegionCode region, WirelessTypes::CommProtocol commProtocol) const
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
}