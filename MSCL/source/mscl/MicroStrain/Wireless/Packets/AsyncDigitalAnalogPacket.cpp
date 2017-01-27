/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "mscl/Exceptions.h"
#include "AsyncDigitalAnalogPacket.h"
#include "mscl/MicroStrain/SampleUtils.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"
#include "mscl/Types.h"
#include "mscl/TimeSpan.h"

namespace mscl
{

    AsyncDigitalAnalogPacket::AsyncDigitalAnalogPacket(const WirelessPacket& packet)
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

    void AsyncDigitalAnalogPacket::parseSweeps()
    {
        const uint32 TS_OFFSET_LEN = 2;    //timestamp offset is always 2 bytes
        const uint32 DIGITAL_LEN = 2;        //digital data is always 2 bytes

        //read the values from the payload
        uint16 channelMask        = m_payload.read_uint16(PAYLOAD_OFFSET_CHANNEL_MASK);
        uint8 dataType            = m_payload.read_uint8(PAYLOAD_OFFSET_DATA_TYPE);
        uint16 tick                = m_payload.read_uint16(PAYLOAD_OFFSET_TICK);
        uint64 timestampSeconds    = m_payload.read_uint32(PAYLOAD_OFFSET_TS_SEC);        //the timestamp (UTC) seconds part
        uint64 timestampNanos    = m_payload.read_uint32(PAYLOAD_OFFSET_TS_NANOSEC);    //the timestamp (UTC) nanoseconds part

        //build the full nanosecond resolution timestamp from the seconds and nanoseconds values read above
        uint64 packetTimestamp = (timestampSeconds * TimeSpan::NANOSECONDS_PER_SECOND) + timestampNanos;

        //build the ChannelMask from the channel mask
        ChannelMask channels(channelMask);

        //set the data type of the packet
        m_dataType = static_cast<WirelessTypes::DataType>(dataType);

        //create a sample rate for this data
        static const SampleRate digitalRate = SampleRate::Event();

        std::size_t payloadLen = m_payload.size();
        uint16 sweepItr = 0;

        //find the offset into the payload to get the data
        uint32 byteItr = PAYLOAD_OFFSET_CHANNEL_DATA;

        //while there is still more data for us to read
        while(byteItr < payloadLen)
        {
            //build a sweep to add
            DataSweep sweep;
            sweep.samplingType(DataSweep::samplingType_AsyncDigitalAnalog);
            sweep.frequency(m_frequency);
            sweep.tick(tick++);
            sweep.nodeAddress(m_nodeAddress);
            sweep.sampleRate(digitalRate);

            //get this sweep's timestamp offset
            uint64 timeOffset = m_payload.read_uint16(byteItr);
            byteItr += TS_OFFSET_LEN;

            //get this sweep's digital data value
            uint16 digitalData = m_payload.read_uint16(byteItr);
            byteItr += DIGITAL_LEN;

            //build this sweep's timestamp
            sweep.timestamp(Timestamp(packetTimestamp + ((timeOffset * TimeSpan::NANOSECONDS_PER_SECOND) / 32768) ));            

            //get this sweep's node and base rssi values
            sweep.nodeRssi(m_nodeRSSI);
            sweep.baseRssi(m_baseRSSI);
            sweep.calApplied(m_dataType == WirelessTypes::dataType_float32);

            //the digital data is represented as the same structure as a channel mask (16 values, 1 or 0)
            ChannelMask digitalDataMask(digitalData);

            ChannelData chData;

            uint8 lastActiveCh = channels.lastChEnabled();

            //loop through all the channels
            for(uint8 chItr = 1; chItr <= lastActiveCh; ++chItr)
            {
                //if the current channel is enabled
                if(channels.enabled(chItr))
                {
                    //if the digital value is enabled (active) for this channel
                    if(digitalDataMask.enabled(chItr))
                    {
                        //create a WirelessDataPoint from the analog data
                        WirelessDataPoint analogPoint = createAnalogDataPoint(chItr, byteItr);

                        //move the byteItr forward for the amount of bytes we read
                        byteItr += WirelessTypes::dataTypeSize(m_dataType);

                        //add the point to the ChannelData vector
                        chData.push_back(analogPoint);
                    }
                }
            }

            //add the channel data to the sweep
            sweep.data(chData);

            //add the sweep to the container of sweeps
            addSweep(sweep);

            //moving on to the next sweep in the packet
            sweepItr++;
        }

        //if we didn't add any sweeps, there was an error in the packet
        if(sweepItr == 0) { throw Error("Invalid Packet"); }
    }

    WirelessDataPoint AsyncDigitalAnalogPacket::createAnalogDataPoint(uint8 channelNumber, uint32 bytePos)
    {
        anyType data;

        //parse the data from the payload
        getPayloadData(bytePos, data);

        return WirelessDataPoint(wirelessChannelFromChNum(channelNumber), channelNumber, WirelessTypes::dataTypeToValueType(m_dataType), data);
    }

    WirelessChannel::ChannelId AsyncDigitalAnalogPacket::wirelessChannelFromDigitalChNum(int channelNum)
    {
        //the offset into the WirelessChannel::ChannelId enum 
        const int DIGITAL_CHANNEL_OFFSET = WirelessChannel::channel_digital_1 - 1;

        //call the WirelessDataPacket's same function with the new offset
        return WirelessDataPacket::wirelessChannelFromChNum(channelNum + DIGITAL_CHANNEL_OFFSET);
    }

    bool AsyncDigitalAnalogPacket::integrityCheck(const WirelessPacket& packet)
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

        //read the data type
        uint8 dataType = payload.read_uint8(PAYLOAD_OFFSET_DATA_TYPE);

        //verify the data type
        if(dataType < WirelessTypes::dataType_first || dataType > WirelessTypes::dataType_last)
        {
            //the data type is invalid
            return false;
        }

        //verify the packet type is correct
        if(packet.type() != packetType_AsyncDigitalAnalog)
        {
            //packet is not an Async Digital packet
            return false;
        }

        //calculate the number of active channels
        uint32 channels = ChannelMask(payload.read_uint16(PAYLOAD_OFFSET_CHANNEL_MASK)).count();

        //check that there are active channels
        if(channels == 0)
        {
            //no active channels
            return false;
        }

        //packet looks valid
        return true;
    }

    UniqueWirelessPacketId AsyncDigitalAnalogPacket::getUniqueId(const WirelessPacket& packet)
    {
        //return the tick value
        return packet.payload().read_uint16(PAYLOAD_OFFSET_TICK);
    }
}