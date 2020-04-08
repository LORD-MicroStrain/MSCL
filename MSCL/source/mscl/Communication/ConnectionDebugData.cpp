/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "ConnectionDebugData.h"

namespace mscl
{
    ConnectionDebugData::ConnectionDebugData() :
        m_fromRead(true)
    {
    }

    ConnectionDebugData::ConnectionDebugData(bool fromRead, const Bytes& data) :
        m_fromRead(fromRead),
        m_loggedTime(Timestamp::timeNow()),
        m_data(data)
    {
    }

    bool ConnectionDebugData::fromRead() const
    {
        return m_fromRead;
    }

    const Timestamp& ConnectionDebugData::timestamp() const
    {
        return m_loggedTime;
    }

    const Bytes& ConnectionDebugData::data() const
    {
        return m_data;
    }
}