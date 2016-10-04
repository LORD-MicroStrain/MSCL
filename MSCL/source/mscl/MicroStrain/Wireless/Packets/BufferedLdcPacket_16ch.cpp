/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "mscl/Exceptions.h"
#include "BufferedLdcPacket_16ch.h"
#include "mscl/MicroStrain/SampleUtils.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"
#include "mscl/Types.h"
#include "mscl/Utils.h"


namespace mscl
{

    BufferedLdcPacket_16ch::BufferedLdcPacket_16ch(const WirelessPacket& packet)
    {
        //construct the data packet from the wireless packet passed in
        m_nodeAddress        = packet.nodeAddress();
        m_deliveryStopFlags = packet.deliveryStopFlags();
        m_type                = packet.type();
        m_nodeRSSI            = WirelessTypes::UNKNOWN_RSSI;
        m_baseRSSI            = packet.baseRSSI();
        m_frequency            = packet.frequency();
        m_payload            = packet.payload();
        m_payloadOffsetChannelData = PAYLOAD_OFFSET_CHANNEL_DATA;

        //parse the data sweeps in the packet
        parseSweeps();
    }

    void BufferedLdcPacket_16ch::parseSweeps()
    {
        //read the values from the payload
        uint16 channelMask    = m_payload.read_uint16(PAYLOAD_OFFSET_CHANNEL_MASK);
        uint8 sampleRate    = m_payload.read_uint8(PAYLOAD_OFFSET_SAMPLE_RATE);
        uint8 dataType        = Utils::lsNibble(m_payload.read_uint8(PAYLOAD_OFFSET_APPID_AND_DATA_TYPE));
        uint16 tick            = m_payload.read_uint16(PAYLOAD_OFFSET_TICK);

        //set the data type of the packet
        m_dataType = static_cast<WirelessTypes::DataType>(dataType);

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

        //build the full nanosecond resolution timestamp from the seconds and nanoseconds values read above
        uint64 recievedTime = Timestamp::timeNow().nanoseconds();

        //create a SampleRate object from the sampleRate byte
        SampleRate currentRate = SampleUtils::convertToSampleRate(sampleRate);

        //get the value to increment the timestamp by for each sweep (the timestamp from the packet only applies to the first sweep)
        const uint64 TS_INCREMENT = currentRate.samplePeriod().getNanoseconds();

        //there are multiple sweeps in this packet (buffered)
        for(uint32 sweepItr = 0; sweepItr < m_numSweeps; sweepItr++)
        {
            //build a sweep to add
            DataSweep sweep;
            sweep.samplingType(DataSweep::samplingType_NonSync_Buffered);
            sweep.frequency(m_frequency);
            sweep.tick(tick++);
            sweep.nodeAddress(m_nodeAddress);
            sweep.sampleRate(currentRate);

            //calculate the timestamp to use for this sweep (last sweep gets PC timestamp, count backwards for the other sweeps)
            sweep.timestamp(Timestamp(recievedTime - (TS_INCREMENT * (m_numSweeps - (sweepItr + 1)))));

            //get this sweep's node and base rssi values
            sweep.nodeRssi(m_nodeRSSI);
            sweep.baseRssi(m_baseRSSI);

            //cals applied if the data type is float
            sweep.calApplied(m_dataType == WirelessTypes::dataType_float32);
        
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

    bool BufferedLdcPacket_16ch::integrityCheck(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //verify the payload size
        if(payload.size() < PAYLOAD_OFFSET_CHANNEL_DATA)
        {
            //payload must be at least a certain length
            return false;
        }

        //verify the app id
        uint8 appId = Utils::msNibble(payload.read_uint8(PAYLOAD_OFFSET_APPID_AND_DATA_TYPE));
        if(appId != APP_ID_VAL)
        {
            //application id is incorrect
            return false;
        }

        //verify the delivery stop flags are what we expected
        if(!packet.deliveryStopFlags().pc)
        {
            //packet not intended for the PC
            return false;
        }

        //read the data type
        uint8 dataType = Utils::lsNibble(payload.read_uint8(PAYLOAD_OFFSET_APPID_AND_DATA_TYPE));

        //verify the data type
        if(dataType < WirelessTypes::dataType_first || dataType > WirelessTypes::dataType_last)
        {
            //the data type is invalid
            return false;
        }

        //verify the packet type is correct
        if(packet.type() != packetType_BufferedLDC_16ch)
        {
            //packet is not a Buffered LDC packet
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

    UniqueWirelessPacketId BufferedLdcPacket_16ch::getUniqueId(const WirelessPacket& packet)
    {
        //return the tick value
        return packet.payload().read_uint16(PAYLOAD_OFFSET_TICK);
    }
}