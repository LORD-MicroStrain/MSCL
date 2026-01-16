/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/BaseStationFeatures.h"

namespace mscl
{
    //Class: BaseStationFeatures_usb200
    //    Contains information on features for the WSDA-200 USB BaseStation.
    class BaseStationFeatures_usb200 : public BaseStationFeatures
    {
    public:
        ~BaseStationFeatures_usb200() override = default;

        //Constructor: BaseStationFeatures_usb200
        //    Creates a BaseStationFeatures_usb200 object.
        //
        //Parameters:
        //    info - A <BaseStationInfo> object representing standard information of the <BaseStation>.
        BaseStationFeatures_usb200(const BaseStationInfo& info);

        bool supportsRfSweepMode() const final;
        bool supportsCustomRfSweepMode() const final;
    };
} // namespace mscl
