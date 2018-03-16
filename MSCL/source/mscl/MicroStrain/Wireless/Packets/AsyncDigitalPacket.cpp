/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "mscl/Exceptions.h"
#include "AsyncDigitalPacket.h"
#include "mscl/MicroStrain/SampleUtils.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"
#include "mscl/TimeSpan.h"
#include "mscl/Types.h"

namespace mscl
{

    AsyncDigitalPacket::AsyncDigitalPacket(const WirelessPacket& packet)
    {
        //construct the data packet from the wireless packet passed in
        m_nodeAddress        = packet.nodeAddress();
        m_deliveryStopFlags = packet.deliveryStopFlags();
        m_type                = packet.type();
        m_nodeRSSI            = packet.nodeRSSI();
        m_baseRSSI            = packet.baseRSSI();
        m_frequency            = packet.frequency();
        m_payload            = packet.payload();
        m_payloadOffsetChannelData = PAYLOAD_OFFSET_CHANNEL_DATA;

        //parse the data sweeps in the packet
        parseSweeps();
    }

    void AsyncDigitalPacket::parseSweeps()
    {
        //read the values from the payload
        uint16 channelMask        = m_payload.read_uint16(PAYLOAD_OFFSET_CHANNEL_MASK);
        uint16 tick                = m_payload.read_uint16(PAYLOAD_OFFSET_TICK);
        uint64 timestampSeconds    = m_payload.read_uint32(PAYLOAD_OFFSET_TS_SEC);        //the timestamp (UTC) seconds part
        uint64 timestampNanos    = m_payload.read_uint32(PAYLOAD_OFFSET_TS_NANOSEC);    //the timestamp (UTC) nanoseconds part

        //build the full nanosecond resolution timestamp from the seconds and nanoseconds values read above
        uint64 packetTimestamp = (timestampSeconds * TimeSpan::NANOSECONDS_PER_SECOND) + timestampNanos;

        if(!timestampWithinRange(Timestamp(packetTimestamp)))
        {
            throw Error("Timestamp is out of range");
        }

        //build the ChannelMask from the channel mask
        ChannelMask channels(channelMask);

        //set the data type of the packet (always the same for this packet)
        m_dataType = WirelessTypes::dataType_uint16_12bitRes;

        //set the size of a single sweep (always 2 bytes of timestamp offset, 2 bytes of digital data)
        m_sweepSize = 4;

        //calculate the number of sweeps in this packet
        m_numSweeps = (m_payload.size() - PAYLOAD_OFFSET_CHANNEL_DATA) / m_sweepSize;

        //if we have no sweeps, there was an error in the packet
        if(m_numSweeps == 0) { throw Error("Invalid Packet"); }

        //create a sample rate for this data
        SampleRate digitalRate = SampleRate::Event();

        //there are multiple sweeps (events) in this packet
        for(uint32 sweepItr = 0; sweepItr < m_numSweeps; sweepItr++)
        {
            //build a sweep to add
            DataSweep sweep;
            sweep.samplingType(DataSweep::samplingType_AsyncDigital);
            sweep.frequency(m_frequency);
            sweep.tick(tick++);
            sweep.nodeAddress(m_nodeAddress);
            sweep.sampleRate(digitalRate);

            //find the offset into the payload to get the data
            uint32 readPos = (sweepItr * m_sweepSize) + PAYLOAD_OFFSET_CHANNEL_DATA;

            //get this sweep's timestamp offset
            uint64 timeOffset = m_payload.read_uint16(readPos);

            //get this sweep's digital data value
            uint16 digitalData = m_payload.read_uint16(readPos + 2);

            //the digital data is represented as the same structure as a channel mask (16 values, 1 or 0)
            ChannelMask digitalDataMask(digitalData);

            //build this sweep's timestamp
            sweep.timestamp(Timestamp(packetTimestamp + ((timeOffset * TimeSpan::NANOSECONDS_PER_SECOND) / 32768) ));            

            //get this sweep's node and base rssi values
            sweep.nodeRssi(m_nodeRSSI);
            sweep.baseRssi(m_baseRSSI);
            sweep.calApplied(true);
        
            ChannelData chData;

            uint8 lastActiveCh = channels.lastChEnabled();

            //loop through all the channels
            for(uint8 chItr = 1; chItr <= lastActiveCh; ++chItr)
            {    
                //if the current channel is enabled
                if(channels.enabled(chItr))
                {
                    //get the digital value (as a bool)
                    bool dataVal = digitalDataMask.enabled(chItr);

                    //add a WirelessDataPoint from the digital data to the ChannelData vector
                    chData.push_back(WirelessDataPoint(wirelessChannelFromChNum(chItr), chItr, valueType_bool, anyType(dataVal)));
                }
            }

            //add the channel data to the sweep
            sweep.data(chData);

            //add the sweep to the container of sweeps
            addSweep(sweep);
        }
    }

    WirelessChannel::ChannelId AsyncDigitalPacket::wirelessChannelFromChNum(int channelNum)
    {
        //the offset into the WirelessChannel::ChannelId enum 
        const int DIGITAL_CHANNEL_OFFSET = WirelessChannel::channel_digital_1 - 1;

        //call the WirelessDataPacket's same function with the new offset
        return WirelessDataPacket::wirelessChannelFromChNum(channelNum + DIGITAL_CHANNEL_OFFSET);
    }

    bool AsyncDigitalPacket::integrityCheck(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //verify the payload size
        if(payload.size() < PAYLOAD_OFFSET_CHANNEL_DATA)
        {
            //payload is too small to be valid
            return false;
        }

        //verify the delivery stop flags are what we expected
        if(!packet.deliveryStopFlags().pc)
        {
            //packet not intended for the PC
            return false;
        }

        //verify the packet type is correct
        if(packet.type() != packetType_AsyncDigital)
        {
            //packet is not an Async Digital packet
            return false;
        }

        //there are 4 bytes per record (per event)
        uint32 recordSize = 4;

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

    UniqueWirelessPacketId AsyncDigitalPacket::getUniqueId(const WirelessPacket& packet)
    {
        //return the tick value
        return packet.payload().read_uint16(PAYLOAD_OFFSET_TICK);
    }
}