/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/Bin.h"

namespace mscl
{
    Bin::Bin(const Value& start, const Value& end, const Value& count) :
        m_start(start),
        m_end(end),
        m_count(count)
    {}

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
} // namespace mscl
