/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Packets/WirelessDataPacket.h"

#include "mscl/MicroStrain/Wireless/DataSweep.h"

namespace mscl
{
    WirelessDataPacket::WirelessDataPacket() :
        m_sweepPos(0),
        m_dataType(WirelessTypes::dataType_uint16),
        m_sweepSize(0),
        m_numSweeps(0),
        m_payloadOffsetChannelData(0)
    {}

    //    Adds a single DataSweep to the data packet
    void WirelessDataPacket::addSweep(const DataSweep& sweep)
    {
        m_dataSweeps.push_back(sweep);
    }

    void WirelessDataPacket::addDataPoint(ChannelData& container, uint8 channelNumber, int channelDataIndex, int sweepIndex, WirelessChannel::ChannelId channelId) const
    {
        //find the offset into the payload to get the data
        uint32 offset = sweepIndex * m_sweepSize + channelDataIndex * WirelessTypes::dataTypeSize(m_dataType) + m_payloadOffsetChannelData;

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
        return numSweepsRemaining() > 0;
    }



    //    Gets the WirelessChannel::ChannelId enum from the channel number
    WirelessChannel::ChannelId WirelessDataPacket::wirelessChannelFromChNum(int channelNum)
    {
        return static_cast<WirelessChannel::ChannelId>(channelNum);
    }

    WirelessChannel::ChannelId WirelessDataPacket::getMathChannelId(WirelessTypes::DerivedDataPacketAlgorithmId algorithmId, uint8 channelNumber)
    {
        uint16 algorithmIdStart = 0;

        if(channelNumber < 1 || channelNumber > 16)
        {
            assert(false);
            throw Error("Invalid channel number");
        }

        //determine where the start offset is in the enum list
        switch(algorithmId)
        {
            case WirelessTypes::derivedAlgId_rms:
                algorithmIdStart = WirelessChannel::channel_1_rms;
                break;

            case WirelessTypes::derivedAlgId_peakToPeak:
                algorithmIdStart = WirelessChannel::channel_1_peakToPeak;
                break;

            case WirelessTypes::derivedAlgId_ips:
                algorithmIdStart = WirelessChannel::channel_1_ips;
                break;

            case WirelessTypes::derivedAlgId_mmps:
                algorithmIdStart = WirelessChannel::channel_1_mmps;
                break;

            case WirelessTypes::derivedAlgId_crestFactor:
                algorithmIdStart = WirelessChannel::channel_1_crestFactor;
                break;

            case WirelessTypes::derivedAlgId_mean:
                algorithmIdStart = WirelessChannel::channel_1_mean;
                break;

            default:
                assert(false);  //need to add support for a new algorithm ID
                throw Error("Invalid Algorithm Id");
                break;
        }

        //use the channel number to move to the correct enum offset
        return static_cast<WirelessChannel::ChannelId>(algorithmIdStart + channelNumber - 1);
    }

    bool WirelessDataPacket::timestampWithinRange(const Timestamp& timestamp)
    {
        //timestamp is out of range if it is over an hour in the future
        static const uint64 NANOS_IN_1_HOUR = 3600000000000;
        Timestamp now = Timestamp::timeNow();

        if(timestamp <= now)
        {
            //we aren't checking for past timestamps
            return true;
        }

        return (now - timestamp).getNanoseconds() < NANOS_IN_1_HOUR;
    }

    bool WirelessDataPacket::angleWithinRange(float angle)
    {
        return angle >= 0.0f && angle <= 360.0f;
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
                result = val << 2;
                break;
            }

            //uint16 value (from 24-bit node, needs shifted left)
            case WirelessTypes::dataType_uint16_24bitTrunc:
            {
                uint32 val = static_cast<uint32>(m_payload.read_uint16(payloadPosition));
                result = val << 8;
                break;
            }

            //int16 value (from 20-bit node, needs shifted left)
            case WirelessTypes::dataType_int16_20bitTrunc:
            {
                int32 val = static_cast<int32>(m_payload.read_int16(payloadPosition));
                result = val << 6;
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
            case WirelessTypes::dataType_uint24_18bitRes:
                result = m_payload.read_uint24(payloadPosition);
                break;

            //int24 value (we store this as an int32)
            case WirelessTypes::dataType_int24_20bit:
                result = m_payload.read_int24(payloadPosition);
                break;

            //int16 value (calibrated value multiplied by 10, needs divided by 10)
            case WirelessTypes::dataType_int16_x10:
                result = static_cast<float>(m_payload.read_int16(payloadPosition)) / 10.0f;
                break;
        }
    }
} // namespace mscl
