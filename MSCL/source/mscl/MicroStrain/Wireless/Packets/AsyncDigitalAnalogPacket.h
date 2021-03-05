/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "WirelessDataPacket.h"

namespace mscl
{

    //Class: AsyncDigitalAnalogPacket
    //    A <WirelessDataPacket> derived class representing an Asynchronouse Digital packet
    class AsyncDigitalAnalogPacket : public WirelessDataPacket
    {
    private:
        //=====================================================================================================
        //Constants: Synchronized Sampling Packet Information
        //    PAYLOAD_OFFSET_CHANNEL_MASK        - 0        - The offset into the payload to get the digital channel mask (2 bytes)
        //    PAYLOAD_OFFSET_DATA_TYPE        - 2        - The offset into the payload to get the data type
        //    PAYLOAD_OFFSET_TICK                - 3        - The offset into the payload to get the tick (2 bytes)
        //    PAYLOAD_OFFSET_TS_SEC            - 5        - The offset into the payload to get the timestamp seconds (4 bytes)
        //    PAYLOAD_OFFSET_TS_NANOSEC        - 9        - The offset into the payload to get the timestamp nanoseconds (4 bytes)
        //    PAYLOAD_OFFSET_CHANNEL_DATA        - 13    - The offset into the payload where the channel data starts
        //=====================================================================================================
        static const uint16 PAYLOAD_OFFSET_CHANNEL_MASK = 0;
        static const uint16 PAYLOAD_OFFSET_DATA_TYPE    = 2;
        static const uint16 PAYLOAD_OFFSET_TICK            = 3;
        static const uint16 PAYLOAD_OFFSET_TS_SEC        = 5;
        static const uint16 PAYLOAD_OFFSET_TS_NANOSEC    = 9;
        static const uint16 PAYLOAD_OFFSET_CHANNEL_DATA    = 13;

    public:
        //Constructor: AsyncDigitalAnalogPacket
        //    Creates a AsyncDigitalAnalogPacket from the passed in <WirelessPacket>
        //
        //Parameters:
        //    packet - A <WirelessPacket> determined to be a AsyncDigitalAnalogPacket
        explicit AsyncDigitalAnalogPacket(const WirelessPacket& packet);

    private:
        AsyncDigitalAnalogPacket();    //default constructor disabled

        //Function: parseSweeps
        //    Parses the passed in WirelessPacket for all the sweep information and adds a sweep to the sweeps container
        //
        //Exceptions:
        //    - <Error_UnknownSampleRate>: failed to find the sample rate in the list
        void parseSweeps();

        //Function: wirelessChannelFromDigitalChNum
        //    Converts a digital channel number to a <WirelessChannel::ChannelId>
        //
        //Parameters:
        //    channelNum - The digital channel number to convert (digital channel 1 = 1, digital channel 16 = 16)
        //
        //Returns:
        //    The <WirelessChannel::ChannelId> representing the passed in digital channel number
        WirelessChannel::ChannelId wirelessChannelFromDigitalChNum(int channelNum);

        //Function: createAnalogDataPoint
        //    Creates a <WirelessDataPoint> for Analog data from the current payload given a data type and channel index
        //
        //Parameters:
        //    channelNumber - The channel number associated with the data point (ch1 = 1, ch8 = 8).
        //    bytePos - The position into the payload data that we are reading from.
        //
        //Returns:
        //    A <WirelessDataPoint> built from the channel information provided
        WirelessDataPoint createAnalogDataPoint(uint8 channelNumber, uint32 bytePos);

    public:
        //Function: integrityCheck
        //    Verifies that the packet is a well formed Async Digital and Analog packet
        //
        //Parameters:
        //    packet - The fully formed Wireless Packet to check the integrity of
        //
        //Returns:
        //    true if the packet is a well formed Sync Sampling packet, false otherwise
        static bool integrityCheck(const WirelessPacket& packet);

        //Function: getUniqueId
        //    Gets the unique Id of the <WirelessPacket> passed in
        //
        //Parameters:
        //    packet - The <WirelessPacket> to get the unique id of
        //
        //Returns:
        //    The <UniqueWirelessPacketId> of the passed in packet
        static UniqueWirelessPacketId getUniqueId(const WirelessPacket& packet);
    };

}