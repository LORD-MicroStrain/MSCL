/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Packets/LdcPacket_v2_aspp3.h"

#include "mscl/MicroStrain/SampleUtils.h"
#include "mscl/MicroStrain/Wireless/DataSweep.h"

namespace mscl
{
    LdcPacket_v2_aspp3::LdcPacket_v2_aspp3(const WirelessPacket& packet)
    {
        //construct the data packet from the wireless packet passed in
        m_nodeAddress              = packet.nodeAddress();
        m_deliveryStopFlags        = packet.deliveryStopFlags();
        m_type                     = packet.type();
        m_nodeRSSI                 = WirelessTypes::UNKNOWN_RSSI;
        m_baseRSSI                 = packet.baseRSSI();
        m_frequency                = packet.frequency();
        m_payload                  = packet.payload();
        m_payloadOffsetChannelData = PAYLOAD_OFFSET_CHANNEL_DATA;

        //parse the data sweeps in the packet
        parseSweeps();
    }

    void LdcPacket_v2_aspp3::parseSweeps()
    {
        //read the values from the payload
        //uint32 model = m_payload.read_uint32(0);
        uint16 channelMask = m_payload.read_uint16(PAYLOAD_OFFSET_CHANNEL_MASK);
        uint8 sampleRate = m_payload.read_uint8(PAYLOAD_OFFSET_SAMPLE_RATE);
        uint8 dataType = m_payload.read_uint8(PAYLOAD_OFFSET_DATA_TYPE);
        uint16 tick = m_payload.read_uint16(PAYLOAD_OFFSET_TICK);

        //set the data type of the packet
        m_dataType = static_cast<WirelessTypes::DataType>(dataType);

        //build the ChannelMask from the channel mask
        ChannelMask channels(channelMask);

        //calculate the size of a single sweep
        m_sweepSize = channels.count() * WirelessTypes::dataTypeSize(m_dataType);

        //only 1 sweep in a LDC packet
        m_numSweeps = 1;

        //build the 1 sweep that we need to add
        DataSweep sweep;
        sweep.samplingType(DataSweep::samplingType_NonSync);
        sweep.frequency(m_frequency);
        sweep.tick(tick);
        sweep.nodeAddress(m_nodeAddress);
        sweep.sampleRate(SampleUtils::convertToSampleRate(sampleRate));

        //No timestamp comes with the LDC packet, so stamp it with the current time
        sweep.timestamp(Timestamp::timeNow());

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
                addDataPoint(chData, chItr, chDataIndex, 0, wirelessChannelFromChNum(chItr));

                chDataIndex++;
            }
        }

        //add the channel data to the sweep
        sweep.data(chData);

        //add the sweep to the container of sweeps
        addSweep(sweep);
    }

    bool LdcPacket_v2_aspp3::integrityCheck(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //verify the payload size
        if(payload.size() < PAYLOAD_OFFSET_CHANNEL_DATA)
        {
            //payload must have at least 6 bytes to be valid
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
        if(packet.type() != packetType_LDC_16ch)
        {
            //packet is not an LDC 16ch packet
            return false;
        }

        //calculate the number of active channels
        uint32 channels = ChannelMask(payload.read_uint16(PAYLOAD_OFFSET_CHANNEL_MASK)).count();

        //calculate the size of a single data point
        uint32 dataSize = WirelessTypes::dataTypeSize(static_cast<WirelessTypes::DataType>(dataType));

        //if the packet contains no channels, we want to throw it out
        if(channels == 0)
        {
            return false;
        }

        //the payload should contain the exact number of bytes for the data specified in the packet
        if(channels * dataSize != payload.size() - PAYLOAD_OFFSET_CHANNEL_DATA)
        {
            return false;
        }

        //packet looks valid
        return true;
    }

    UniqueWirelessPacketId LdcPacket_v2_aspp3::getUniqueId(const WirelessPacket& packet)
    {
        //return the tick value
        return packet.payload().read_uint16(PAYLOAD_OFFSET_TICK);
    }
} // namespace mscl
