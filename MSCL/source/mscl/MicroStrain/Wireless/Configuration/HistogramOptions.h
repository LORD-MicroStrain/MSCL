/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/MicroStrain/SampleRate.h"

namespace mscl
{
    //API Class: HistogramOptions
    //    Contains all of the Histogram options that can be configured for a WirelessNode.
    class HistogramOptions
    {
    public:
        //API Default Constructor: HistogramOptions
        //    Creates a default constructed HistogramOptions object.
        HistogramOptions();

    private:
        //Variable: m_transmitRate
        //    The transmit rate of the Histogram.
        WirelessTypes::WirelessSampleRate m_transmitRate;

        //Variable: m_binStart
        //    The start of the first bin in the Histogram.
        uint16 m_binStart;

        //Variable: m_binSize
        //    The size of each bin in the Histogram.
        uint16 m_binSize;

    public:
        //API Function: transmitRate
        //    Gets the transmit rate set in this options object, as a <WirelessTypes::WirelessSampleRate>.
        WirelessTypes::WirelessSampleRate transmitRate() const;

        //API Function: transmitRate
        //    Sets the transmit rate in this options object.
        //
        //Parameters:
        //    rate - The transmit rate (as a <WirelessTypes::WirelessSampleRate>) to set.
        void transmitRate(WirelessTypes::WirelessSampleRate rate);

        //API Function: binsStart
        //    Gets the bins start set in this options object.
        uint16 binsStart() const;

        //API function: binsStart
        //    Sets the bins start in this options object.
        //
        //Parameters:
        //    start - The start of the first bin in the Histogram.
        void binsStart(uint16 start);

        //API Function: binsSize
        //    Gets the bins size set in this options object.
        uint16 binsSize() const;

        //API function: binsSize
        //    Sets the bins size in this options object.
        //
        //Parameters:
        //    size - The size of each bin in the Histogram.
        void binsSize(uint16 size);
    };
}