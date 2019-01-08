/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "HistogramOptions.h"

namespace mscl
{
    HistogramOptions::HistogramOptions():
        m_transmitRate(WirelessTypes::sampleRate_30Sec),
        m_binStart(0),
        m_binSize(5)
    {
    }

    WirelessTypes::WirelessSampleRate HistogramOptions::transmitRate() const
    {
        return m_transmitRate;
    }

    void HistogramOptions::transmitRate(WirelessTypes::WirelessSampleRate rate)
    {
        m_transmitRate = rate;
    }

    uint16 HistogramOptions::binsStart() const
    {
        return m_binStart;
    }

    void HistogramOptions::binsStart(uint16 start)
    {
        m_binStart = start;
    }

    uint16 HistogramOptions::binsSize() const
    {
        return m_binSize;
    }

    void HistogramOptions::binsSize(uint16 size)
    {
        m_binSize = size;
    }
}