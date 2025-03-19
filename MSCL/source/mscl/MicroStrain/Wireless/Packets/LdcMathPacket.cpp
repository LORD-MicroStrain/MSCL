/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Packets/LdcMathPacket.h"

#include "mscl/MicroStrain/Wireless/DataSweep.h"

namespace mscl
{
    LdcMathPacket::LdcMathPacket(const WirelessPacket& packet)
    {
        //construct the data packet from the wireless packet passed in
        m_nodeAddress              = packet.nodeAddress();
        m_deliveryStopFlags        = packet.deliveryStopFlags();
        m_type                     = packet.type();
        m_nodeRSSI                 = WirelessTypes::UNKNOWN_RSSI;
        m_baseRSSI                 = packet.baseRSSI();
        m_frequency                = packet.frequency();
        m_payload                  = packet.payload();

        //parse the data sweeps in the packet
        parseSweeps();
    }

    void LdcMathPacket::parseSweeps()
    {
        DataBuffer payload(m_payload);

        //read the values from the payload
        payload.skipBytes(1);       //Rate at which raw data was sampled (throwing away for now)
        uint32 calculationRate      = payload.read_uint32();    //Rate at which processed data was sampled
        uint16 tick                 = payload.read_uint16();
        const uint8 numAlgorithms   = payload.read_uint8();     //The number of algorithms being used

        SampleRate rate;

        //the upper bit determines hz (1) vs seconds (0)
        bool isHertz = Utils::bitIsSet(calculationRate, 31);
        if(isHertz)
        {
            //turn off the bit to get the real value
            Utils::setBit(calculationRate, 31, false);
            rate = SampleRate::Hertz(calculationRate);
        }
        else
        {
            rate = SampleRate::Seconds(calculationRate);
        }

        //build up the Algorithm Metadata
        std::vector<WirelessDataPacket::AlgorithmMetaData> metaData;
        metaData.reserve(numAlgorithms);
        for(uint8 i = 0; i < numAlgorithms; ++i)
        {
            metaData.emplace_back(static_cast<WirelessTypes::DerivedDataPacketAlgorithmId>(payload.read_uint8()),
                                  ChannelMask(payload.read_uint16())
            );
        }

        //build a sweep to add
        DataSweep sweep;
        sweep.samplingType(DataSweep::samplingType_NonSync);
        sweep.frequency(m_frequency);
        sweep.tick(tick);
        sweep.nodeAddress(m_nodeAddress);
        sweep.sampleRate(rate);
        sweep.calApplied(true);

        //build this sweep's timestamp
        sweep.timestamp(Timestamp::timeNow());

        //get this sweep's node and base rssi values
        sweep.nodeRssi(m_nodeRSSI);
        sweep.baseRssi(m_baseRSSI);

        ChannelData chData;
        uint8 lastChEnabled = 0;

        //loop over each algorithm
        for(auto alg : metaData)
        {
            lastChEnabled = alg.channelMask.lastChEnabled();

            //loop over each active channel
            for(uint8 chItr = 1; chItr <= lastChEnabled; ++chItr)
            {
                //skip any channels not enabled
                if(!alg.channelMask.enabled(chItr)) { continue; }

                //add channel data
                WirelessChannel::ChannelId channelId = WirelessDataPacket::getMathChannelId(alg.algorithmId, chItr);

                //create the ChannelMask property indicating which channel it was derived from
                ChannelMask propertyChMask;
                propertyChMask.enable(chItr);
                WirelessDataPoint::ChannelProperties properties({
                    {std::make_pair(WirelessDataPoint::channelPropertyId_derivedFrom, Value(valueType_ChannelMask, propertyChMask))},
                    {std::make_pair(WirelessDataPoint::channelPropertyId_derivedAlgorithmId, Value(valueType_uint8, static_cast<uint8>(alg.algorithmId)))}
                });

                chData.emplace_back(channelId, chItr, valueType_float, anyType(payload.read_float()), properties);
            }
        }

        //add the channel data to the sweep
        sweep.data(chData);

        //add the sweep to the container of sweeps
        addSweep(sweep);
    }

    bool LdcMathPacket::integrityCheck(const WirelessPacket& packet)
    {
        const WirelessPacket::Payload& payload = packet.payload();

        //verify the payload size
        if(payload.size() < 15)
        {
            //payload must have at least 15 bytes to be valid
            //(required bytes + 1 algorithm + 1 value)
            return false;
        }

        //verify the delivery stop flags are what we expected
        if(!packet.deliveryStopFlags().pc)
        {
            //packet not intended for the PC
            return false;
        }

        //verify the packet type is correct
        if(packet.type() != packetType_LDC_math)
        {
            return false;
        }

        //add up the total number of channel bytes we expect to be in the packet
        const uint8 numAlgorithms = payload.read_uint8(7);
        uint8 readPos = 8;
        uint8 expectedChannelBytes = 0;
        WirelessTypes::DerivedDataPacketAlgorithmId tempId;
        ChannelMask tempMask;
        for(uint8 i = 0; i < numAlgorithms; ++i)
        {
            tempId = static_cast<WirelessTypes::DerivedDataPacketAlgorithmId>(payload.read_uint8(readPos));
            readPos += 1;
            tempMask.fromMask(payload.read_uint16(readPos));
            readPos += 2;

            expectedChannelBytes += tempMask.count() * WirelessTypes::bytesPerDerivedAlgorithmId(tempId);
        }

        //verify we have the expected number of channel bytes
        //  payload length - (# algorithms * 3 bytes per algorithm) - 8 standard payload bytes
        if(expectedChannelBytes != payload.size() - numAlgorithms * 3 - 8)
        {
            return false;
        }

        //packet looks valid
        return true;
    }

    UniqueWirelessPacketId LdcMathPacket::getUniqueId(const WirelessPacket& packet)
    {
        static const std::size_t PAYLOAD_OFFSET_TICK = 5;

        //return the tick value
        return packet.payload().read_uint16(PAYLOAD_OFFSET_TICK);
    }
} // namespace mscl
