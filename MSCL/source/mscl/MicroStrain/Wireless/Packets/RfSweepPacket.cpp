/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"

#include "RfSweepPacket.h"
#include "mscl/Bin.h"

namespace mscl
{

    RfSweepPacket::RfSweepPacket(const WirelessPacket& packet)
    {
        //construct the data packet from the wireless packet passed in
        m_nodeAddress              = packet.nodeAddress();
        m_deliveryStopFlags        = packet.deliveryStopFlags();
        m_type                     = packet.type();
        m_nodeRSSI                 = WirelessTypes::UNKNOWN_RSSI;
        m_baseRSSI                 = WirelessTypes::UNKNOWN_RSSI;
        m_frequency                = packet.frequency();
        m_payload                  = packet.payload();

        //parse the data sweeps in the packet
        parseSweeps();
    }

    void RfSweepPacket::parseSweeps()
    {
        static const uint8 PAYLOAD_OFFSET_CHANNEL_DATA = 13;
        m_numSweeps = 1;

        //build the 1 sweep that we need to add
        DataSweep sweep;
        sweep.samplingType(DataSweep::samplingType_RfSweep);
        sweep.frequency(m_frequency);
        sweep.tick(0);  //no tick
        sweep.nodeAddress(m_nodeAddress);
        sweep.sampleRate(SampleRate::Event());
        sweep.timestamp(Timestamp::timeNow());

        //get this sweep's node and base rssi values
        sweep.nodeRssi(m_nodeRSSI);
        sweep.baseRssi(m_baseRSSI);

        sweep.calApplied(true);

        //determine the sweep information
        uint32 minFreq = m_payload.read_uint32(1);
        //uint32 maxFreq = m_payload.read_uint32(5);
        uint32 freqInterval = m_payload.read_uint32(9);

        RfSweep rfSweep;

        uint32 curFreq = minFreq;
        std::size_t numBins = m_payload.size() - PAYLOAD_OFFSET_CHANNEL_DATA;

        for(std::size_t binItr = 0; binItr < numBins; ++binItr)
        {            
            //add the bin to the sweep (each value needs to be made negative before stored)
            rfSweep[curFreq] = static_cast<int16>(m_payload.read_uint8(PAYLOAD_OFFSET_CHANNEL_DATA + binItr)) * -1;

            curFreq += freqInterval;
        }

        ChannelData chData;
        chData.emplace_back(WirelessChannel::channel_rfSweep, 1, valueType_RfSweep, anyType(rfSweep));

        //add the channel data to the sweep
        sweep.data(chData);

        //add the sweep to the container of sweeps
        addSweep(sweep);
    }

    bool RfSweepPacket::integrityCheck(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //verify the minimum payload size
        if(payload.size() < 14)
        {
            return false;
        }

        //verify the delivery stop flags are what we expected
        if(!packet.deliveryStopFlags().pc)
        {
            //packet not intended for the PC
            return false;
        }

        //verify the packet type is correct
        if(packet.type() != packetType_rfScanSweep)
        {
            //packet is not an LDC packet
            return false;
        }

        //packet looks valid
        return true;
    }
}
