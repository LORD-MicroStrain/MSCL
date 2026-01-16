/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/BaseStationFeatures.h"

namespace mscl
{
    //Class: BaseStationFeatures_wsda2000
    //    Contains information on features for the WSDA-2000.
    class BaseStationFeatures_wsda2000 : public BaseStationFeatures
    {
    public:
        ~BaseStationFeatures_wsda2000() override = default;

        //Constructor: BaseStationFeatures_wsda2000
        //    Creates a BaseStationFeatures_wsda2000 object.
        //
        //Parameters:
        //    info - A <BaseStationInfo> object representing standard information of the <BaseStation>.
        BaseStationFeatures_wsda2000(const BaseStationInfo& info);

        bool supportsRfSweepMode() const final;
        bool supportsCustomRfSweepMode() const final;
    };
} // namespace mscl
