/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Features/BaseStationFeatures_analog.h"

namespace mscl
{
    BaseStationFeatures_analog::BaseStationFeatures_analog(const BaseStationInfo& info) :
        BaseStationFeatures(info)
    {}

    uint8 BaseStationFeatures_analog::buttonCount() const
    {
        return 2;    //supports 2 buttons
    }

    uint8 BaseStationFeatures_analog::analogPortCount() const
    {
        return 8;    //supports 8 analog out ports
    }
} // namespace mscl
