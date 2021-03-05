/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "BaseStationFeatures.h"

namespace mscl
{    
    //Class: BaseStationFeatures_wsda2000
    //    Contains information on features for the WSDA-2000.
    class BaseStationFeatures_wsda2000 : public BaseStationFeatures
    {
    public:
        virtual ~BaseStationFeatures_wsda2000() {}

        //Constructor: BaseStationFeatures_wsda2000
        //    Creates a BaseStationFeatures_wsda2000 object.
        //
        //Parameters:
        //    info - A <BaseStationInfo> object representing standard information of the <BaseStation>.
        BaseStationFeatures_wsda2000(const BaseStationInfo& info);

        virtual bool supportsRfSweepMode() const final;
        virtual bool supportsCustomRfSweepMode() const final;
    };
}