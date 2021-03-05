/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "BaseStationFeatures.h"

namespace mscl
{    
    //Class: BaseStationFeatures_usb
    //    Contains information on features for the usb BaseStation.
    class BaseStationFeatures_usb : public BaseStationFeatures
    {
    public:
        virtual ~BaseStationFeatures_usb() {}

        //Constructor: BaseStationFeatures_usb
        //    Creates a BaseStationFeatures_usb object.
        //
        //Parameters:
        //    info - A <BaseStationInfo> object representing standard information of the <BaseStation>.
        BaseStationFeatures_usb(const BaseStationInfo& info);
    };
}