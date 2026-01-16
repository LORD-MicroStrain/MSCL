/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/BaseStationFeatures.h"

namespace mscl
{
    //Class: BaseStationFeatures_usb
    //    Contains information on features for the usb BaseStation.
    class BaseStationFeatures_usb : public BaseStationFeatures
    {
    public:
        ~BaseStationFeatures_usb() override = default;

        //Constructor: BaseStationFeatures_usb
        //    Creates a BaseStationFeatures_usb object.
        //
        //Parameters:
        //    info - A <BaseStationInfo> object representing standard information of the <BaseStation>.
        BaseStationFeatures_usb(const BaseStationInfo& info);
    };
} // namespace mscl
