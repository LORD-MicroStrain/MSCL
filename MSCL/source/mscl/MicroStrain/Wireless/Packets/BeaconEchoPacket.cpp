/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"

#include "BeaconEchoPacket.h"

namespace mscl
{

    BeaconEchoPacket::BeaconEchoPacket(const WirelessPacket& packet)
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

    void BeaconEchoPacket::parseSweeps()
    {
        static const uint16 BEACON_ECHO = 0;
        static const uint16 BEACON_CONFLICT = 1;

        m_numSweeps = 1;

        //build the 1 sweep that we need to add
        DataSweep sweep;
        sweep.samplingType(DataSweep::samplingType_BeaconEcho);
        sweep.frequency(m_frequency);
        sweep.tick(0);  //no tick
        sweep.nodeAddress(m_nodeAddress);
        sweep.sampleRate(SampleRate::Hertz(1));

        //the data itself is the beacon timestamp. 
        //use this for the current PC time
        sweep.timestamp(Timestamp::timeNow());

        //get this sweep's node and base rssi values
        sweep.nodeRssi(m_nodeRSSI);
        sweep.baseRssi(m_baseRSSI);

        sweep.calApplied(true);

        ChannelData chData;

        //determine if it was a beacon from this BaseStation, or another Base on the same frequency
        WirelessChannel::ChannelId chId;
        uint16 beaconType = m_payload.read_uint16(0);
        switch(beaconType)
        {
            case BEACON_CONFLICT:
                chId = WirelessChannel::channel_beaconConflict;
                break;

            case BEACON_ECHO:
            default:
                chId = WirelessChannel::channel_beaconEcho;
                break;
        }

        //build the current beacon timestamp
        uint64 timestampSec = m_payload.read_uint32(2);
        Timestamp time((timestampSec * TimeSpan::NANOSECONDS_PER_SECOND)); //no nanoseconds provided in this packet

        static const auto chName = std::bind(WirelessChannel::channelName, chId);

        chData.emplace_back(chId, 1, chName, valueType_Timestamp, anyType(time));

        //add the channel data to the sweep
        sweep.data(chData);

        //add the sweep to the container of sweeps
        addSweep(sweep);
    }

    bool BeaconEchoPacket::integrityCheck(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //verify the payload size
        if(payload.size() != 6)
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
        if(packet.type() != packetType_beaconEcho)
        {
            //packet is not an LDC packet
            return false;
        }

        //packet looks valid
        return true;
    }
}
