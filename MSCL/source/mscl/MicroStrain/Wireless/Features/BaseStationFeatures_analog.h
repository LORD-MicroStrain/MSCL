/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/BaseStationFeatures.h"

namespace mscl
{
    //Class: BaseStationFeatures_analog
    //    Contains information on features for the analog BaseStation.
    class BaseStationFeatures_analog : public BaseStationFeatures
    {
    public:
        ~BaseStationFeatures_analog() override = default;

        //Constructor: BaseStationFeatures_analog
        //    Creates a BaseStationFeatures_analog object.
        //
        //Parameters:
        //    info - A <BaseStationInfo> object representing standard information of the <BaseStation>.
        BaseStationFeatures_analog(const BaseStationInfo& info);

        //Function: buttonCount
        //    Gets the total number of buttons that are supported.
        //
        //Returns:
        //    The total number of buttons that are supported.
        uint8 buttonCount() const override;

        //Function: analogPortCount
        //    Gets the total number of analog ports that are supported.
        //
        //Returns:
        //    The total number of analog ports that are supported.
        uint8 analogPortCount() const override;
    };
} // namespace mscl
