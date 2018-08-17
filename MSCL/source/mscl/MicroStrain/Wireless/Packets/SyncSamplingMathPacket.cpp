/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "mscl/Exceptions.h"
#include "SyncSamplingMathPacket.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"
#include "mscl/MicroStrain/SampleUtils.h"
#include "mscl/TimeSpan.h"
#include "mscl/TimestampCounter.h"
#include "mscl/Types.h"


namespace mscl
{

    SyncSamplingMathPacket::SyncSamplingMathPacket(const WirelessPacket& packet)
    {
        //construct the data packet from the wireless packet passed in
        m_nodeAddress              = packet.nodeAddress();
        m_deliveryStopFlags        = packet.deliveryStopFlags();
        m_type                     = packet.type();
        m_nodeRSSI                 = packet.nodeRSSI();
        m_baseRSSI                 = packet.baseRSSI();
        m_frequency                = packet.frequency();
        m_payload                  = packet.payload();

        //parse the data sweeps in the packet
        parseSweeps();
    }

    void SyncSamplingMathPacket::parseSweeps()
    {
        DataBuffer payload(m_payload);

        //read the values from the payload
        payload.skipBytes(1);       //Rate at which raw data was sampled (throwing away for now)
        uint32 calculationRate      = payload.read_uint32();    //Rate at which processed data was sampled
        uint16 tick                 = payload.read_uint16();
        uint64 timestamp            = payload.read_uint64();
        const uint8 numAlgorithms   = payload.read_uint8();     //The number of algorithms being used

        if(!timestampWithinRange(Timestamp(timestamp)))
        {
            throw Error("Timestamp is out of range");
        }

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

        TimestampCounter tsCounter(rate, timestamp);

        //build up the Algorithm Meta Data
        std::vector<WirelessDataPacket::AlgorithmMetaData> metaData;
        metaData.reserve(numAlgorithms);
        for(uint8 i = 0; i < numAlgorithms; ++i)
        {
            metaData.emplace_back(static_cast<WirelessTypes::DerivedDataPacketAlgorithmId>(payload.read_uint8()),
                                  ChannelMask(payload.read_uint16())
            );
        }

        const uint8 NUM_CHANNEL_BYTES = static_cast<uint8>(payload.bytesRemaining());

        //build a sweep to add
        DataSweep sweep;
        sweep.samplingType(DataSweep::samplingType_SyncSampling);
        sweep.frequency(m_frequency);
        sweep.nodeAddress(m_nodeAddress);
        sweep.sampleRate(rate);
        sweep.calApplied(true);

        //get this sweep's node and base rssi values
        sweep.nodeRssi(m_nodeRSSI);
        sweep.baseRssi(m_baseRSSI);

        uint8 lastChEnabled = 0;

        //while there are more sweeps remaining
        while(payload.bytesRemaining() >= NUM_CHANNEL_BYTES)
        {
            ChannelData chData;

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

            sweep.tick(tick++);

            sweep.timestamp(Timestamp(tsCounter.time()));
            tsCounter.advance();

            //add the current sweep to the container of sweeps
            sweep.data(chData);
            addSweep(sweep);
        }
    }

    bool SyncSamplingMathPacket::integrityCheck(const WirelessPacket& packet)
    {
        const WirelessPacket::Payload& payload = packet.payload();

        //verify the payload size
        if(payload.size() < 23)
        {
            //payload must have at least 23 bytes to be valid
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
        if(packet.type() != packetType_SyncSampling_math)
        {
            return false;
        }

        //add up the total number of channel bytes we expect to be in the packet
        const uint8 numAlgorithms = payload.read_uint8(15);
        uint8 readPos = 16;
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

        //verify we have the expected number of channel bytes (could be more than 1 sweep, so checking mod operator)
        //  payload length - (# algorithms * 3 bytes per algorithm) - 16 standard payload bytes
        if((payload.size() - (numAlgorithms * 3) - 16) % expectedChannelBytes != 0)
        {
            return false;
        }

        //packet looks valid
        return true;
    }

    UniqueWirelessPacketId SyncSamplingMathPacket::getUniqueId(const WirelessPacket& packet)
    {
        static const std::size_t PAYLOAD_OFFSET_TICK = 5;

        //return the tick value
        return packet.payload().read_uint16(PAYLOAD_OFFSET_TICK);
    }
}