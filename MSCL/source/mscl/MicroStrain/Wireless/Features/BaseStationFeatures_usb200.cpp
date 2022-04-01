/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "BaseStationFeatures_usb200.h"

namespace mscl
{
    BaseStationFeatures_usb200::BaseStationFeatures_usb200(const BaseStationInfo& info):
        BaseStationFeatures(info)
    {
    }

    bool BaseStationFeatures_usb200::supportsRfSweepMode() const
    {
        static const Version MIN_RF_SWEEP_FW(5, 39166);

        return (m_baseInfo.firmwareVersion() >= MIN_RF_SWEEP_FW);
    }

    bool BaseStationFeatures_usb200::supportsCustomRfSweepMode() const
    {
        static const Version MIN_RF_SWEEP_FW(5, 39166);

        return (m_baseInfo.firmwareVersion() >= MIN_RF_SWEEP_FW);
    }
}