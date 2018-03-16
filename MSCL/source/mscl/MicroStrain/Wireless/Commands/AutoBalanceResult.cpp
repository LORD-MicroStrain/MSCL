/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "AutoBalanceResult.h"

namespace mscl
{
    AutoBalanceResult::AutoBalanceResult():
        m_errorCode(WirelessTypes::autobalance_notComplete),
        m_percentAchieved(0),
        m_hardwareOffset(0)
    {
    }

    WirelessTypes::AutoBalanceErrorFlag AutoBalanceResult::errorCode() const
    {
        return m_errorCode;
    }

    float AutoBalanceResult::percentAchieved() const
    {
        return m_percentAchieved;
    }

    uint16 AutoBalanceResult::hardwareOffset() const
    {
        return m_hardwareOffset;
    }
}