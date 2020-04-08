/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "Bin.h"

namespace mscl
{
    Bin::Bin(const Value& start, const Value& end, const Value& count):
        m_start(start),
        m_end(end),
        m_count(count)
    {
    }

    Value Bin::start() const
    {
        return m_start;
    }

    Value Bin::end() const
    {
        return m_end;
    }

    Value Bin::count() const
    {
        return m_count;
    }
}