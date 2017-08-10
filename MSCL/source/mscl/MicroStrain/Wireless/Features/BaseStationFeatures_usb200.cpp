/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "BaseStationFeatures_usb200.h"

namespace mscl
{
    BaseStationFeatures_usb200::BaseStationFeatures_usb200(BaseStationInfo& info):
        BaseStationFeatures(info)
    {
    }

    bool BaseStationFeatures_usb200::supportsRfSweepMode() const
    {
        //temporarily disabling rf sweep mode until we know a firmware version that officially supports it
        return false;
    }

    bool BaseStationFeatures_usb200::supportsCustomRfSweepMode() const
    {
        //temporarily disabling rf sweep mode until we know a firmware version that officially supports it
        return false;
    }
}