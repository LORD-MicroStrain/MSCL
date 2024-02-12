/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"

#include <math.h>

#include "ShmPacket_v2_aspp3.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"
#include "mscl/MicroStrain/Wireless/StructuralHealth.h"
#include "mscl/MicroStrain/SampleUtils.h"
#include "mscl/Histogram.h"
#include "mscl/TimeSpan.h"
#include "mscl/Types.h"

namespace mscl
{
    ShmPacket_v2_aspp3::ShmPacket_v2_aspp3(const WirelessPacket& packet)
    {
        //construct the data packet from the wireless packet passed in
        m_nodeAddress          = packet.nodeAddress();
        m_deliveryStopFlags    = packet.deliveryStopFlags();
        m_type                 = packet.type();
        m_nodeRSSI             = WirelessTypes::UNKNOWN_RSSI;
        m_baseRSSI             = packet.baseRSSI();
        m_frequency            = packet.frequency();
        m_payload              = packet.payload();

        //parse the data sweeps in the packet
        parseSweeps();
    }

    void ShmPacket_v2_aspp3::parseSweeps()
    {
        static const uint16 PAYLOAD_OFFSET_TX_RATE = 1;
        static const uint16 PAYLOAD_OFFSET_PROC_RATE = 2;
        static const uint16 PAYLOAD_OFFSET_TICK = 3;
        static const uint16 PAYLOAD_OFFSET_ANGLE = 7;
        static const uint16 PAYLOAD_OFFSET_DAMAGE = 11;
        static const uint16 PAYLOAD_OFFSET_BIN_START = 15;
        static const uint16 PAYLOAD_OFFSET_BIN_SIZE = 17;
        static const uint16 PAYLOAD_OFFSET_BIN_DATA = 19;

        //read the values from the payload
        auto txRate = static_cast<WirelessTypes::WirelessSampleRate>(m_payload.read_uint8(PAYLOAD_OFFSET_TX_RATE));
        auto processingRate = static_cast<WirelessTypes::WirelessSampleRate>(m_payload.read_uint8(PAYLOAD_OFFSET_PROC_RATE));
        uint32 tick = m_payload.read_uint32(PAYLOAD_OFFSET_TICK);
        float angle = m_payload.read_float(PAYLOAD_OFFSET_ANGLE);    //already in degrees
        float damage = m_payload.read_float(PAYLOAD_OFFSET_DAMAGE);
        uint16 binStart = m_payload.read_uint16(PAYLOAD_OFFSET_BIN_START);
        uint16 binSize = m_payload.read_uint16(PAYLOAD_OFFSET_BIN_SIZE);

        if(!angleWithinRange(angle))
        {
            throw Error("Angle is out of range");
        }

        //this packet always stores the bin data as uint32s
        m_dataType = WirelessTypes::dataType_uint32;
        const uint16 DATA_SIZE = WirelessTypes::dataTypeSize(m_dataType);

        m_sweepSize = 1;
        m_numSweeps = 1;

        //build the sweep to be added
        DataSweep sweep;
        sweep.samplingType(DataSweep::samplingType_SHM);
        sweep.frequency(m_frequency);
        sweep.tick(tick);
        sweep.nodeAddress(m_nodeAddress);
        sweep.sampleRate(SampleRate::FromWirelessEepromValue(txRate));

        //no timestamp comes with the histogram packet, so just stamp it with the current time
        sweep.timestamp(Timestamp::timeNow());

        sweep.nodeRssi(m_nodeRSSI);
        sweep.baseRssi(m_baseRSSI);
        sweep.calApplied(true);

        Histogram histogram(Value::UINT32(static_cast<uint32>(binStart)), Value::UINT32(static_cast<uint32>(binSize)));
        uint32 start = binStart;
        uint32 end = binStart + binSize;
        uint32 count;

        static const uint16 NUM_STATIC_BYTES_IN_PAYLOAD = 19;
        m_binCount = (m_payload.size() - NUM_STATIC_BYTES_IN_PAYLOAD) / DATA_SIZE;

        //loop through all the bins in the packet and build up the Histogram object
        for(size_t i = 0; i < m_binCount; i++)
        {
            //read the bin's count from the payload
            count = m_payload.read_uint32(PAYLOAD_OFFSET_BIN_DATA + (i * DATA_SIZE));

            //create the bin to add to the Histogram
            Bin bin(Value::UINT32(start), Value::UINT32(end), Value::UINT32(count));

            //add the bin to the Histogram
            histogram.addBin(bin);

            //update the start and end values for the next bin
            start = end;
            end = start + binSize;
        }

        //create a StructuralHealth object
        StructuralHealth shm(angle, tick, damage, SampleRate::FromWirelessEepromValue(processingRate), histogram);

        //create and add the WirelessDataPoint to the ChannelData vector
        ChannelData chData;
        auto chName = std::bind(ShmPacket_v2_aspp3::buildChannelName, angle);
        chData.push_back(WirelessDataPoint(WirelessChannel::channel_structuralHealth, 0, chName, valueType_StructuralHealth, anyType(shm)));

        //add the channel data to the sweep
        sweep.data(chData);

        //add the sweep to the container of sweeps
        addSweep(sweep);
    }

    bool ShmPacket_v2_aspp3::integrityCheck(const WirelessPacket& packet)
    {
        //the minimum payload that this packet has to be
        static const uint16 MIN_PAYLOAD_SIZE = 19;

        WirelessPacket::Payload payload = packet.payload();

        //verify the payload size
        if(payload.size() < MIN_PAYLOAD_SIZE)
        {
            //payload doesn't have enough bytes to be valid
            return false;
        }

        //verify the delivery stop flags are what we expected
        if(!packet.deliveryStopFlags().pc)
        {
            //packet not intended for the PC
            return false;
        }

        //verify the packet type is correct
        if(packet.type() != packetType_SHM)
        {
            //packet is not a Structural Health Monitoring packet
            return false;
        }

        //verify app ID
        if(payload.read_uint8(0) != 0x00)
        {
            //invalid app id
            return false;
        }

        //packet looks valid
        return true;
    }

    std::string ShmPacket_v2_aspp3::buildChannelName(float angle)
    {
        return WirelessChannel::channelName(WirelessChannel::channel_structuralHealth) + "_angle" + Utils::toStrWithPrecision(angle, 2, true);
    }
}
