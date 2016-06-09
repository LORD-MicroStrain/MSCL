/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "CalCoefficients.h"

namespace mscl
{
    CalCoefficients::CalCoefficients():
        m_eqType(WirelessTypes::equation_standard),
        m_unit(WirelessTypes::unit_none)
    { }

    CalCoefficients::CalCoefficients(WirelessTypes::CalCoef_EquationType eqType, WirelessTypes::CalCoef_Unit unit, const LinearEquation& linearEq):
        m_eqType(eqType),
        m_unit(unit),
        m_linearEq(linearEq)
    { }

    WirelessTypes::CalCoef_EquationType CalCoefficients::equationType() const
    {
        return m_eqType;
    }

    WirelessTypes::CalCoef_Unit CalCoefficients::unit() const
    {
        return m_unit;
    }

    const LinearEquation& CalCoefficients::linearEquation() const
    {
        return m_linearEq;
    }
}