/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"

#include "RollerPacket.h"
#include "mscl/MicroStrain/SampleUtils.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"


namespace mscl
{

    RollerPacket::RollerPacket(const WirelessPacket& packet)
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

    void RollerPacket::parseSweeps()
    {
        //read the values from the payload
        uint16 tick = m_payload.read_uint16(0);
        uint16 rpmChannel = m_payload.read_uint16(2);
        int16 temperatureChannel = static_cast<int16>(m_payload.read_int8(4));

        //only 1 sweep in this packet
        m_numSweeps = 1;

        //build the 1 sweep that we need to add
        DataSweep sweep;
        sweep.samplingType(DataSweep::samplingType_NonSync);
        sweep.frequency(m_frequency);
        sweep.tick(tick);
        sweep.nodeAddress(m_nodeAddress);
        sweep.sampleRate(mscl::SampleRate::Seconds(900));   //this packet has a hard coded sample rate of: 15 minutes (900 seconds)

        //No timestamp comes with the packet, so just stamp it with the current time
        sweep.timestamp(Timestamp::timeNow());

        //get this sweep's node and base rssi values
        sweep.nodeRssi(m_nodeRSSI);
        sweep.baseRssi(m_baseRSSI);

        sweep.calApplied(true);

        //this packet has hard coded channel data
        ChannelData chData;
        chData.emplace_back(WirelessChannel::channel_1, 1, ValueType::valueType_uint16, anyType(rpmChannel));
        chData.emplace_back(WirelessChannel::channel_2, 2, ValueType::valueType_int16, anyType(temperatureChannel));

        //add the channel data to the sweep
        sweep.data(chData);

        //add the sweep to the container of sweeps
        addSweep(sweep);
    }

    bool RollerPacket::integrityCheck(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //verify the payload size
        if(payload.size() != 5)
        {
            return false;
        }

        //verify the delivery stop flags are what we expected
        if(!packet.deliveryStopFlags().pc)
        {
            return false;
        }

        //verify the packet type is correct
        if(packet.type() != packetType_roller)
        {
            //packet is not an LDC packet
            return false;
        }

        //packet looks valid
        return true;
    }

    UniqueWirelessPacketId RollerPacket::getUniqueId(const WirelessPacket& packet)
    {
        //return the tick value
        return packet.payload().read_uint16(0);
    }
}
