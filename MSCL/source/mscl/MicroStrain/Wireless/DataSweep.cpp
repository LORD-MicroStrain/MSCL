/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"

#include "DataSweep.h"

namespace mscl
{
    DataSweep::DataSweep():
        m_timestamp(0),
        m_tick(0),
        m_sampleRate(SampleRate::rateType_hertz, 1),
        m_nodeAddress(0),
        m_samplingMode(samplingType_SyncSampling),
        m_nodeRssi(0),
        m_baseRssi(0),
        m_frequency(WirelessTypes::freq_unknown),
        m_calsApplied(true)
    {
    }

    const Timestamp& DataSweep::timestamp() const
    {
        return m_timestamp;
    }

    void DataSweep::timestamp(const Timestamp& time)
    {
        m_timestamp = time;
    }

    uint32 DataSweep::tick() const
    {
        return m_tick;
    }

    void DataSweep::tick(uint32 tick)
    {
        m_tick = tick;
    }

    SampleRate DataSweep::sampleRate() const
    {
        return m_sampleRate;
    }

    void DataSweep::sampleRate(SampleRate rate)
    {
        m_sampleRate = rate;
    }

    NodeAddress DataSweep::nodeAddress() const
    {
        return m_nodeAddress;
    }

    void DataSweep::nodeAddress(NodeAddress address)
    {
        m_nodeAddress = address;
    }
    
    const ChannelData& DataSweep::data() const
    {
        return m_data;
    }

    void DataSweep::data(const ChannelData& data)
    {
        m_data = data;
    }

    DataSweep::SamplingType DataSweep::samplingType() const
    {
        return m_samplingMode;
    }

    void DataSweep::samplingType(DataSweep::SamplingType type)
    {
        m_samplingMode = type;
    }

    int16 DataSweep::nodeRssi() const
    {
        return m_nodeRssi;
    }

    void DataSweep::nodeRssi(int16 rssi)
    {
        m_nodeRssi = rssi;
    }

    int16 DataSweep::baseRssi() const
    {
        return m_baseRssi;
    }

    void DataSweep::baseRssi(int16 rssi)
    {
        m_baseRssi = rssi;
    }

    WirelessTypes::Frequency DataSweep::frequency() const
    {
        return m_frequency;
    }

    void DataSweep::frequency(WirelessTypes::Frequency freq)
    {
        m_frequency = freq;
    }

    bool DataSweep::calApplied() const
    {
        return m_calsApplied;
    }

    void DataSweep::calApplied(bool applied)
    {
        m_calsApplied = applied;
    }
}
