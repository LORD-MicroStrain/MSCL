/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "BaseStationFeatures.h"

namespace mscl
{    
    //Class: BaseStationFeatures_rs232
    //    Contains information on features for the rs232 BaseStation.
    class BaseStationFeatures_rs232 : public BaseStationFeatures
    {
    public:
        virtual ~BaseStationFeatures_rs232() {}

        //Constructor: BaseStationFeatures_rs232
        //    Creates a BaseStationFeatures_rs232 object.
        //
        //Parameters:
        //    info - A <BaseStationInfo> object representing standard information of the <BaseStation>.
        BaseStationFeatures_rs232(const BaseStationInfo& info);
    };
}