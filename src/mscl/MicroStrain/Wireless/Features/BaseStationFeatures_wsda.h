/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/BaseStationFeatures.h"

namespace mscl
{
    //Class: BaseStationFeatures_wsda
    //    Contains information on features for the WSDA.
    class BaseStationFeatures_wsda : public BaseStationFeatures
    {
    public:
        ~BaseStationFeatures_wsda() override = default;

        //Constructor: BaseStationFeatures_wsda
        //    Creates a BaseStationFeatures_wsda object.
        //
        //Parameters:
        //    info - A <BaseStationInfo> object representing standard information of the <BaseStation>.
        BaseStationFeatures_wsda(const BaseStationInfo& info);

        bool supportsRfSweepMode() const final;
        bool supportsCustomRfSweepMode() const final;
    };
} // namespace mscl
