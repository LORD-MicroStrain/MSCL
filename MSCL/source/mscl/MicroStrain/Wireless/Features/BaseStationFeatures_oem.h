/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "BaseStationFeatures.h"

namespace mscl
{    
    //Class: BaseStationFeatures_oem
    //    Contains information on features for the oem BaseStation.
    class BaseStationFeatures_oem : public BaseStationFeatures
    {
    public:
        virtual ~BaseStationFeatures_oem() {}

        //Constructor: BaseStationFeatures_oem
        //    Creates a BaseStationFeatures_oem object.
        //
        //Parameters:
        //    info - A <BaseStationInfo> object representing standard information of the <BaseStation>.
        BaseStationFeatures_oem(BaseStationInfo& info);
    };
}