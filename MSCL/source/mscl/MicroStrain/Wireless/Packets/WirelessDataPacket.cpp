/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "WirelessDataPacket.h"

#include <assert.h>
#include <boost/numeric/conversion/cast.hpp>

namespace mscl
{
    WirelessDataPacket::WirelessDataPacket() :
        m_sweepPos(0),
        m_dataType(WirelessTypes::dataType_uint16),
        m_sweepSize(0),
        m_numSweeps(0),
        m_payloadOffsetChannelData(0)
    {
    }

    //    Adds a single DataSweep to the data packet
    void WirelessDataPacket::addSweep(const DataSweep& sweep)
    {
        m_dataSweeps.push_back(sweep);
    }

    void WirelessDataPacket::addDataPoint(ChannelData& container, uint8 channelNumber, int channelDataIndex, int sweepIndex, WirelessChannel::ChannelId channelId) const
    {
        //find the offset into the payload to get the data
        uint32 offset = (sweepIndex * m_sweepSize) + (channelDataIndex * WirelessTypes::dataTypeSize(m_dataType)) + m_payloadOffsetChannelData;

        anyType data;

        //parse the data from the payload
        getPayloadData(offset, data);

        container.emplace_back(channelId, channelNumber, WirelessTypes::dataTypeToValueType(m_dataType), data);
    }

    //    Gets the next DataSweep in the packet
    void WirelessDataPacket::getNextSweep(DataSweep& sweepResult)
    {
        //check if the current sweep position is out of range
        assert(m_sweepPos < m_dataSweeps.size());

        //return the current data sweep, and then increment the sweep position
        sweepResult = m_dataSweeps.at(m_sweepPos++);
    }

    std::size_t WirelessDataPacket::numSweepsRemaining() const
    {
        return numSweeps() - m_sweepPos;
    }

    //    Gets the number of sweeps
    std::size_t WirelessDataPacket::numSweeps() const
    {
        return m_dataSweeps.size();
    }

    bool WirelessDataPacket::moreSweeps() const
    {
        return (numSweepsRemaining() > 0);
    }


    
    //    Gets the WirelessChannel::ChannelId enum from the channel number
    WirelessChannel::ChannelId WirelessDataPacket::wirelessChannelFromChNum(int channelNum)
    {
        return static_cast<WirelessChannel::ChannelId>(channelNum);
    }

    void WirelessDataPacket::getPayloadData(size_t payloadPosition, anyType& result) const
    {
        switch(m_dataType)
        {
            //float 32
            case WirelessTypes::dataType_float32:
            case WirelessTypes::dataType_float32_noCals:
                result = m_payload.read_float(payloadPosition);
                break;

            //uint32
            case WirelessTypes::dataType_uint32:
                result = m_payload.read_uint32(payloadPosition);
                break;

            //uint16 value (shifted, needs shifted right)
            case WirelessTypes::dataType_uint16_shifted:
                result = boost::numeric_cast<uint16>(m_payload.read_uint16(payloadPosition) >> 1);
                break;

            //uint16 value (from 18-bit node, needs shifted left)
            case WirelessTypes::dataType_uint16_18bitTrunc:
            {
                uint32 val = static_cast<uint32>(m_payload.read_uint16(payloadPosition));
                result = (val << 2);
                break;
            }

            //uint16 value
            case WirelessTypes::dataType_uint16_12bitRes:
            case WirelessTypes::dataType_uint16:
            default:
                result = m_payload.read_uint16(payloadPosition);
                break;

            //uint24 value (we store this as a uint32)
            case WirelessTypes::dataType_uint24:
                result = m_payload.read_uint24(payloadPosition);
                break;
        }
    }
}