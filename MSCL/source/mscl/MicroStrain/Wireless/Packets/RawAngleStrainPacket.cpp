/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "RawAngleStrainPacket.h"
#include "mscl/MicroStrain/SampleUtils.h"
#include "mscl/Utils.h"

namespace {
std::string channelName(mscl::WirelessChannel::ChannelId id, float angle)
{
  return mscl::WirelessChannel::channelName(mscl::WirelessChannel::channel_rawAngleStrain) + "_angle" + mscl::Utils::toStrWithPrecision(angle, 2, true);
}
}

namespace mscl
{
    RawAngleStrainPacket::RawAngleStrainPacket(const WirelessPacket& packet)
    {
        //construct the data packet from the wireless packet passed in
        m_nodeAddress              = packet.nodeAddress();
        m_deliveryStopFlags        = packet.deliveryStopFlags();
        m_type                     = packet.type();
        m_nodeRSSI                 = WirelessTypes::UNKNOWN_RSSI;
        m_baseRSSI                 = packet.baseRSSI();
        m_frequency                = packet.frequency();
        m_payload                  = packet.payload();
        m_payloadOffsetChannelData = 0; //not used for these packets

        //parse the data sweeps in the packet
        parseSweeps();
    }

    void RawAngleStrainPacket::parseSweeps()
    {
        typedef WirelessChannel WC;

        DataBuffer payload(m_payload);

        //read the values from the payload
        uint8 appId = payload.read_uint8();
        uint8 sampleRate = payload.read_uint8();
        uint16 tick = payload.read_uint16();

        //set the data type of the packet
        m_dataType = WirelessTypes::dataType_4ByteFloat;

        //build the 1 sweep that we need to add
        DataSweep sweep;
        sweep.samplingType(DataSweep::samplingType_NonSync);
        sweep.frequency(m_frequency);
        sweep.tick(tick);
        sweep.nodeAddress(m_nodeAddress);
        sweep.sampleRate(SampleUtils::convertToSampleRate(sampleRate));

        //No timestamp comes with the packet, so just stamp it with the current time
        sweep.timestamp(Timestamp::timeNow());

        //get this sweep's node and base rssi values
        sweep.nodeRssi(m_nodeRSSI);
        sweep.baseRssi(m_baseRSSI);

        static const uint8 SPECIFIC_ANGLE_MODE = 0x00;
        static const uint8 DIST_ANGLE_MODE = 0x01;

        ChannelData chData;
        float angle, chVal;

        //parse the specific angle mode payload
        if(appId == SPECIFIC_ANGLE_MODE)
        {
            //the number of angles in the packet
            uint8 numAngles = payload.read_uint8();

            //get the name and angle data per angle
            for(uint8 i = 0; i < numAngles; ++i)
            {
                angle = payload.read_float();
                chVal = payload.read_float();
                auto chName = bind(channelName, WC::channel_rawAngleStrain, angle);
                
                WirelessDataPoint::ChannelProperties properties({std::make_pair(WirelessDataPoint::channelPropertyId_angle, Value::FLOAT(angle))});
                chData.emplace_back(WC::channel_rawAngleStrain, i, chName, valueType_float, anyType(chVal), properties);
            }
        }
        //parse the distributed angle mode payload
        else if(appId == DIST_ANGLE_MODE)
        {
            //the lower bound angle
            float lowerBound = payload.read_float();

            //the upper bound angle
            float upperBound = payload.read_float();

            //the number of angles in the packet
            uint8 numAngles = payload.read_uint8();

            //determine the angles based on the distribution
            std::vector<float> angles = distributeAngles(lowerBound, upperBound, numAngles);

            //get the name and angle data per angle
            for(uint8 i = 0; i < angles.size(); ++i)
            {
                angle = angles.at(i);

                //read the channel value from the payload
                chVal = payload.read_float();

                auto chName = bind(channelName, WC::channel_rawAngleStrain, angle);

                WirelessDataPoint::ChannelProperties properties({std::make_pair(WirelessDataPoint::channelPropertyId_angle, Value::FLOAT(angle))});
                chData.emplace_back(WC::channel_rawAngleStrain, i, chName, valueType_float, anyType(chVal), properties);
            }
        }

        //add the channel data to the sweep
        sweep.data(chData);

        //add the sweep to the container of sweeps
        addSweep(sweep);
    }

    bool RawAngleStrainPacket::integrityCheck(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //verify the payload size
        if(payload.size() < 13)
        {
            //payload must have at least 13 bytes to be valid
            return false;
        }

        //verify the delivery stop flags are what we expected
        if(!packet.deliveryStopFlags().pc)
        {
            //packet not intended for the PC
            return false;
        }

        //verify the packet type is correct
        if(packet.type() != packetType_rawAngleStrain)
        {
            return false;
        }

        //packet looks valid
        return true;
    }

    UniqueWirelessPacketId RawAngleStrainPacket::getUniqueId(const WirelessPacket& packet)
    {
        //return the tick value
        return packet.payload().read_uint16(2);
    }

    std::vector<float> RawAngleStrainPacket::distributeAngles(float low, float high, uint8 count)
    {
        std::vector<float> angles;

        //make sure we have enough angles to calculate
        if(count <= 1)
        {
            return angles;
        }

        angles.reserve(count);

        //normalize the lower and upper bounds
        low = Utils::normalizeAngle(low);
        high = Utils::normalizeAngle(high);

        float step;

        if(low < high)
        {
            step = (high - low) / (count - 1);
        }
        else
        {
            step = (360 + high - low) / (count - 1);
        }

        //calculate and add each angle to the vector
        for(uint8 i = 0; i < count; ++i)
        {
            angles.emplace_back(Utils::normalizeAngle(low + (i * step)));
        }

        return angles;
    }
}
