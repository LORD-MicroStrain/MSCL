/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "BaseStationFeatures_analog.h"

namespace mscl
{
    BaseStationFeatures_analog::BaseStationFeatures_analog(const BaseStationInfo& info):
        BaseStationFeatures(info)
    {
    }

    uint8 BaseStationFeatures_analog::buttonCount() const
    {
        return 2;    //supports 2 buttons
    }

    uint8 BaseStationFeatures_analog::analogPortCount() const
    {
        return 8;    //supports 8 analog out ports
    }
}