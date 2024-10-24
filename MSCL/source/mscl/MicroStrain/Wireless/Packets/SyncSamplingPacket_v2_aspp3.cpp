/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"

#include "mscl/Exceptions.h"
#include "SyncSamplingPacket_v2_aspp3.h"
#include "mscl/MicroStrain/SampleUtils.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"
#include "mscl/TimeSpan.h"
#include "mscl/TimestampCounter.h"
#include "mscl/Types.h"
#include "mscl/Utils.h"


namespace mscl
{

    SyncSamplingPacket_v2_aspp3::SyncSamplingPacket_v2_aspp3(const WirelessPacket& packet)
    {
        //construct the data packet from the wireless packet passed in
        m_nodeAddress              = packet.nodeAddress();
        m_deliveryStopFlags        = packet.deliveryStopFlags();
        m_type                     = packet.type();
        m_nodeRSSI                 = packet.nodeRSSI();
        m_baseRSSI                 = packet.baseRSSI();
        m_frequency                = packet.frequency();
        m_payload                  = packet.payload();
        m_payloadOffsetChannelData = PAYLOAD_OFFSET_CHANNEL_DATA;

        //parse the data sweeps in the packet
        parseSweeps();
    }

    void SyncSamplingPacket_v2_aspp3::parseSweeps()
    {
        //read the values from the payload
        //model number
        uint16 channelMask          = m_payload.read_uint16(PAYLOAD_OFFSET_CHANNEL_MASK);
        uint8 sampleRate            = m_payload.read_uint8(PAYLOAD_OFFSET_SAMPLE_RATE);
        uint16 tick                 = m_payload.read_uint16(PAYLOAD_OFFSET_TICK);
        uint64 timestamp            = m_payload.read_uint64(PAYLOAD_OFFSET_TS);

        m_dataType = static_cast<WirelessTypes::DataType>(m_payload.read_uint8(PAYLOAD_OFFSET_DATA_TYPE));

        if(!timestampWithinRange(Timestamp(timestamp)))
        {
            throw Error("Timestamp is out of range");
        }

        //build the ChannelMask from the channel mask
        ChannelMask channels(channelMask);

        //calculate the size of a single sweep
        m_sweepSize = channels.count() * WirelessTypes::dataTypeSize(m_dataType);

        //if the sweep size is 0 (no channels active)
        if(m_sweepSize == 0)
        {
            //we only want to insert 1 sweep
            m_numSweeps = 1;
        }
        else
        {
            //calculate the number of sweeps in this packet
            m_numSweeps = (m_payload.size() - PAYLOAD_OFFSET_CHANNEL_DATA) / m_sweepSize;
        }

        //if we still have no sweeps, there was an error in the packet
        if(m_numSweeps == 0) { throw Error("Invalid Packet"); }

        //create a SampleRate object from the sampleRate byte
        SampleRate currentRate = SampleUtils::convertToSampleRate(sampleRate);

        TimestampCounter tsCounter(currentRate, timestamp);

        //there are multiple sweeps in a Sync Sampling (buffered) packet
        for(uint32 sweepItr = 0; sweepItr < m_numSweeps; sweepItr++)
        {
            //build a sweep to add
            DataSweep sweep;
            sweep.samplingType(DataSweep::samplingType_SyncSampling);
            sweep.frequency(m_frequency);
            sweep.tick(tick++);
            sweep.nodeAddress(m_nodeAddress);
            sweep.sampleRate(currentRate);

            //build this sweep's timestamp
            sweep.timestamp(Timestamp(tsCounter.time()));
            tsCounter.advance();

            //get this sweep's node and base rssi values
            sweep.nodeRssi(m_nodeRSSI);
            sweep.baseRssi(m_baseRSSI);

            //cals applied if the data type is float
            sweep.calApplied(WirelessTypes::isCalApplied(m_dataType));

            ChannelData chData;

            //the index of the channel data
            int chDataIndex = 0;

            uint8 lastActiveCh = channels.lastChEnabled();

            //loop through all the channels
            for(uint8 chItr = 1; chItr <= lastActiveCh; ++chItr)
            {
                //if the current channel is enabled
                if(channels.enabled(chItr))
                {
                    //insert the data point into the ChannelData object for the wireless channel
                    addDataPoint(chData, (chItr), chDataIndex, sweepItr, wirelessChannelFromChNum(chItr));

                    chDataIndex++;
                }
            }

            //add the channel data to the sweep
            sweep.data(chData);

            //add the sweep to the container of sweeps
            addSweep(sweep);
        }
    }

    bool SyncSamplingPacket_v2_aspp3::integrityCheck(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //verify the payload size
        if(payload.size() < PAYLOAD_OFFSET_CHANNEL_DATA)
        {
            //payload must have at least 14 bytes to be valid
            return false;
        }

        //verify the delivery stop flags are what we expected
        if(!packet.deliveryStopFlags().pc)
        {
            //packet not intended for the PC
            return false;
        }

        //read the data type
        uint8 dataType = payload.read_uint8(PAYLOAD_OFFSET_DATA_TYPE);

        //verify the data type
        if(dataType < WirelessTypes::dataType_first || dataType > WirelessTypes::dataType_last)
        {
            //the data type is invalid
            return false;
        }

        //verify the packet type is correct
        if(packet.type() != packetType_SyncSampling_16ch)
        {
            //packet is not a Sync Sampling packet
            return false;
        }

        //calculate the number of active channels
        uint32 channels = ChannelMask(payload.read_uint16(PAYLOAD_OFFSET_CHANNEL_MASK)).count();

        //calculate the size of a single data point
        uint32 dataSize = WirelessTypes::dataTypeSize(static_cast<WirelessTypes::DataType>(dataType));

        uint32 recordSize = channels * dataSize;

        //if record size is zero, something is wrong. Bail now before divide by zero
        if(recordSize <= 0)
        {
            return false;
        }

        //the number of channel data bytes
        size_t numChannelBytes = payload.size() - PAYLOAD_OFFSET_CHANNEL_DATA;

        //verify that there are actually channel data bytes
        if(numChannelBytes == 0)
        {
            return false;
        }

        //verify the payload contains a correct number of bytes
        if(numChannelBytes % recordSize != 0)
        {
            return false;
        }

        //packet looks valid
        return true;
    }

    UniqueWirelessPacketId SyncSamplingPacket_v2_aspp3::getUniqueId(const WirelessPacket& packet)
    {
        //return the tick value
        return packet.payload().read_uint16(PAYLOAD_OFFSET_TICK);
    }
}
