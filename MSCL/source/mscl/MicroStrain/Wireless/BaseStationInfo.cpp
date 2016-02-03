/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "BaseStationInfo.h"
#include "BaseStation_Impl.h"

namespace mscl
{
    //read the required information from the BaseStation and store in the BaseStationInfo
    BaseStationInfo::BaseStationInfo(const BaseStation_Impl& base) :
        firmwareVersion(base.firmwareVersion()),
        model(base.model()),
        regionCode(base.regionCode())
    {
    }

    BaseStationInfo::BaseStationInfo(Version fw, WirelessModels::BaseModel model, WirelessTypes::RegionCode region):
        firmwareVersion(fw),
        model(model),
        regionCode(region)
    {
    }
}