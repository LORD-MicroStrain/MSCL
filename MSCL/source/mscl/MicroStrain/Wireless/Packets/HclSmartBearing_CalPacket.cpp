/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "mscl/Exceptions.h"
#include "HclSmartBearing_CalPacket.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"
#include "mscl/MicroStrain/SampleUtils.h"
#include "mscl/MicroStrain/Vector.h"
#include "mscl/TimeSpan.h"
#include "mscl/Types.h"

namespace mscl
{

    HclSmartBearing_CalPacket::HclSmartBearing_CalPacket(const WirelessPacket& packet)
    {
        //construct the data packet from the wireless packet passed in
        m_nodeAddress              = packet.nodeAddress();
        m_deliveryStopFlags        = packet.deliveryStopFlags();
        m_type                     = packet.type();
        m_nodeRSSI                 = packet.nodeRSSI();
        m_baseRSSI                 = packet.baseRSSI();
        m_frequency                = packet.frequency();
        m_payload                  = packet.payload();
        m_payloadOffsetChannelData = 0;    //not used for these packets

        //parse the data sweeps in the packet
        parseSweeps();
    }

    void HclSmartBearing_CalPacket::parseSweeps()
    {
        typedef WirelessChannel WC;

        //read the values from the payload
        uint8 sampleRate = m_payload.read_uint8(PAYLOAD_OFFSET_SAMPLE_RATE);
        uint16 tick = m_payload.read_uint16(PAYLOAD_OFFSET_TICK);
        uint64 timestampSeconds = m_payload.read_uint32(PAYLOAD_OFFSET_TS_SEC);      //the timestamp (UTC) seconds part
        uint64 timestampNanos = m_payload.read_uint32(PAYLOAD_OFFSET_TS_NANOSEC);    //the timestamp (UTC) nanoseconds part

        //build the full nanosecond resolution timestamp from the seconds and nanoseconds values read above
        uint64 realTimestamp = (timestampSeconds * TimeSpan::NANOSECONDS_PER_SECOND) + timestampNanos;

        //create a SampleRate object from the sampleRate byte
        SampleRate currentRate = SampleUtils::convertToSampleRate(sampleRate);

        //the number of bytes in a single sweep
        m_sweepSize = 29;

        static const uint16 DATA_START = 13;

        m_numSweeps = (m_payload.size() - DATA_START) / m_sweepSize;

        //get the value to increment the timestamp by for each sweep (the timestamp from the packet only applies to the first sweep)
        const uint64 TS_INCREMENT = currentRate.samplePeriod().getNanoseconds();

        //if we still have no sweeps, there was an error in the packet
        if(m_numSweeps == 0) { throw Error("Invalid Packet"); }

        uint32 readOffset = DATA_START;

        //there are multiple sweeps in this packet
        for(uint32 sweepItr = 0; sweepItr < m_numSweeps; sweepItr++)
        {
            DataSweep sweep;
            sweep.samplingType(DataSweep::samplingType_SyncSampling);
            sweep.frequency(m_frequency);
            sweep.tick(tick++);
            sweep.nodeAddress(m_nodeAddress);
            sweep.sampleRate(currentRate);
            sweep.nodeRssi(m_nodeRSSI);
            sweep.baseRssi(m_baseRSSI);
            sweep.calApplied(true);

            //build this sweep's timestamp
            sweep.timestamp(Timestamp(realTimestamp + (TS_INCREMENT * sweepItr)));

            ChannelData chData;
            chData.reserve(15);
            chData.emplace_back(WC::channel_hcl_axialLoadX, 1, valueType_int16, anyType(m_payload.read_int16(readOffset + 0)));
            chData.emplace_back(WC::channel_hcl_axialLoadY, 2, valueType_int16, anyType(m_payload.read_int16(readOffset + 2)));
            chData.emplace_back(WC::channel_hcl_axialLoadZ, 3, valueType_float, anyType(static_cast<float>(m_payload.read_int16(readOffset + 4)) * 10));
            chData.emplace_back(WC::channel_hcl_bendingMomentFlap, 4, valueType_int16, anyType(m_payload.read_int16(readOffset + 6)));
            chData.emplace_back(WC::channel_hcl_bendingMomentLag, 5, valueType_int16, anyType(m_payload.read_int16(readOffset + 8)));
            chData.emplace_back(WC::channel_hcl_bendingMomentPitch, 6, valueType_int16, anyType(m_payload.read_int16(readOffset + 10)));
            chData.emplace_back(WC::channel_hcl_motionFlap_mag, 7, valueType_float, anyType(static_cast<float>(m_payload.read_int16(readOffset + 12) / 1000.0)));
            chData.emplace_back(WC::channel_hcl_motionLag_mag, 8, valueType_float, anyType(static_cast<float>(m_payload.read_int16(readOffset + 14) / 1000.0)));
            chData.emplace_back(WC::channel_hcl_motionPitch_mag, 9, valueType_float, anyType(static_cast<float>(m_payload.read_int16(readOffset + 16) / 1000.0)));
            chData.emplace_back(WC::channel_hcl_motionFlap_inertial, 10, valueType_float, anyType(static_cast<float>(m_payload.read_int16(readOffset + 18) / 1000.0)));
            chData.emplace_back(WC::channel_hcl_motionLag_inertial, 11, valueType_float, anyType(static_cast<float>(m_payload.read_int16(readOffset + 20) / 1000.0)));
            chData.emplace_back(WC::channel_hcl_motionPitch_inertial, 12, valueType_float, anyType(static_cast<float>(m_payload.read_int16(readOffset + 22) / 1000.0)));
            chData.emplace_back(WC::channel_hcl_cockingStiffness_mag, 13, valueType_int16, anyType(m_payload.read_int16(readOffset + 24)));
            chData.emplace_back(WC::channel_hcl_cockingStiffness_inertial, 14, valueType_int16, anyType(m_payload.read_int16(readOffset + 26)));
            chData.emplace_back(WC::channel_hcl_temperature, 15, valueType_int16, anyType(static_cast<int16>(m_payload.read_int8(readOffset + 28))));

            readOffset += m_sweepSize;

            //add all of the channel data to the sweep
            sweep.data(chData);

            //add the sweep to the container of sweeps
            addSweep(sweep);
        }
    }

    bool HclSmartBearing_CalPacket::integrityCheck(const WirelessPacket& packet)
    {
        //verify the delivery stop flags are what we expected
        if(!packet.deliveryStopFlags().pc)
        {
            //packet not intended for the PC
            return false;
        }

        //verify the packet type is correct
        if(packet.type() != packetType_HclSmartBearing_Calibrated)
        {
            //packet is not a Sync Sampling packet
            return false;
        }

        const WirelessPacket::Payload& payload = packet.payload();

        //verify the payload size
        if(payload.size() < 42)
        {
            return false;
        }

        return true;
    }

    UniqueWirelessPacketId HclSmartBearing_CalPacket::getUniqueId(const WirelessPacket& packet)
    {
        //return the tick value
        return packet.payload().read_uint16(PAYLOAD_OFFSET_TICK);
    }
}