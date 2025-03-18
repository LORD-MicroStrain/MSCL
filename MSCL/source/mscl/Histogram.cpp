/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/Histogram.h"

namespace mscl
{
    Histogram::Histogram(const Value& binsStart, const Value& binsSize) :
        m_binsStart(binsStart),
        m_binsSize(binsSize)
    {
    }

    Value Histogram::binsStart() const
    {
        return m_binsStart;
    }

    Value Histogram::binsSize() const
    {
        return m_binsSize;
    }

    Bins Histogram::bins() const
    {
        return m_bins;
    }

    void Histogram::addBin(const Bin& bin)
    {
        m_bins.push_back(bin);
    }
}
