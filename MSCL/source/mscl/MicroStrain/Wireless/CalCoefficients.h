/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include <map>

#include "mscl/MicroStrain/LinearEquation.h"
#include "WirelessChannel.h"
#include "WirelessTypes.h"

namespace mscl
{
    //API Class: CalCoefficients
    //  Represents calibration coefficients that can be applied to a Wireless Node.
    class CalCoefficients
    {
    public:
        //API Constructor: CalCoefficients
        //    Creates a default constructed CalCoefficients object.
        CalCoefficients();

        //API Constructor: CalCoefficients
        //  Creates a CalCoefficients object.
        //
        //Parameters:
        //  eqType - The <WirelessTypes::CalCoef_EquationType> of the Cal Coefficients.
        //  unit - The <WirelessTypes::CalCoef_Unit> of the Cal Coefficients.
        //  linearEq - The <LinearEquation> of the Cal Coefficients.
        CalCoefficients(WirelessTypes::CalCoef_EquationType eqType, WirelessTypes::CalCoef_Unit unit, const LinearEquation& linearEq);

    private:
        //Variable: m_eqType
        //  The <WirelessTypes::CalCoef_EquationType> of the Cal Coefficients.
        WirelessTypes::CalCoef_EquationType m_eqType;

        //Variable: m_unit
        //  The <WirelessTypes::CalCoef_Unit> of the Cal Coefficients.
        WirelessTypes::CalCoef_Unit m_unit;

        //Variable: m_linearEq
        //  The <LinearEquation> of the Cal Coefficients.
        LinearEquation m_linearEq;

    public:
#ifndef SWIG
        //Operator: ==
        //    Checks that two CalCoefficients objects are equal
        //
        //Returns:
        //    true if the two CalCoefficients are identical, false otherwise
        bool operator==(const CalCoefficients& src) const;

        //Operator: !=
        //    Checks that two CalCoefficients objects are not equal
        //
        //Returns:
        //    true if the two CalCoefficients are different, false if they are identical
        bool operator!=(const CalCoefficients& src) const;
#endif

        //API Function: equationType
        //  Gets the <WirelessTypes::CalCoef_EquationType> of the Cal Coefficients.
        WirelessTypes::CalCoef_EquationType equationType() const;

        //API Function: unit
        //  Gets the <WirelessTypes::CalCoef_Unit> of the Cal Coefficients.
        WirelessTypes::CalCoef_Unit unit() const;

        //API Function: linearEquation
        //  Gets the <LinearEquation> of the Cal Coefficients.
        const LinearEquation& linearEquation() const;
    };

    //API Typedef: ChannelCalMap
    //  A typedef for a map of <WirelessChannel::ChannelId>s to <CalCoefficients>.
    typedef std::map<mscl::WirelessChannel::ChannelId, CalCoefficients> ChannelCalMap;
}