/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/ResponsePattern.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"
#include "mscl/Types.h"

namespace mscl
{
    //API Class: AutoBalanceResult
    //    Represents the result from an AutoBalance command.
    class AutoBalanceResult
    {
        friend class AutoBalance_v2;
        friend class AutoBalance_v3;
        friend class BaseStation_Impl;
        friend class WirelessNode_Impl;

    protected:
        //Variable: m_errorCode
        //    The error code from the response.
        WirelessTypes::AutoBalanceErrorFlag m_errorCode;

        //Variable: m_percentAchieved
        //    The percentage (0 - 100) achieved from the response.
        float m_percentAchieved;

        //Variable: m_hardwareOffset
        //    The new hardware offset from the response.
        uint16 m_hardwareOffset;

    public:
        //API Default Constructor: AutoBalanceResult
        //    Creates an empty AutoBalanceResult object.
        AutoBalanceResult();

        //API Function: errorCode
        //    Gets the <WirelessTypes::AutoBalanceErrorFlag> from the response.
        //
        //Returns:
        //    The <WirelessTypes::AutoBalanceErrorFlag> from the autobalance response.
        WirelessTypes::AutoBalanceErrorFlag errorCode() const;

        //API Function: percentAchieved
        //    Gets the percentage that the channel was balanced to from the response.
        //
        //Returns:
        //    The the percentage that the channel was balanced to.
        float percentAchieved() const;

        //API Function: hardwareOffset
        //    Get the new hardware offset from the response.
        //
        //Returns:
        //    The new hardware offset value after the autobalance.
        uint16 hardwareOffset() const;
    };
}