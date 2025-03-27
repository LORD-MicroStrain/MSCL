/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/CalCoefficients.h"

namespace mscl
{
    CalCoefficients::CalCoefficients() :
        m_eqType(WirelessTypes::equation_standard),
        m_unit(WirelessTypes::unit_none)
    {}

    CalCoefficients::CalCoefficients(WirelessTypes::CalCoef_EquationType eqType, WirelessTypes::CalCoef_Unit unit, const LinearEquation& linearEq) :
        m_eqType(eqType),
        m_unit(unit),
        m_linearEq(linearEq)
    {}

    bool CalCoefficients::operator==(const CalCoefficients& src) const
    {
        return m_eqType == src.m_eqType &&
               m_unit == src.m_unit &&
               m_linearEq.slope() == src.m_linearEq.slope() &&
               m_linearEq.offset() == src.m_linearEq.offset();
    }

    bool CalCoefficients::operator!=(const CalCoefficients& src) const
    {
        return !(*this == src);
    }

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
} // namespace mscl
