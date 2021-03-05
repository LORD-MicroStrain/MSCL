/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "WirelessDataPacket.h"

namespace mscl
{

    //Class: AsyncDigitalPacket
    //    A <WirelessDataPacket> derived class representing an Asynchronouse Digital packet
    class AsyncDigitalPacket : public WirelessDataPacket
    {
    private:
        //=====================================================================================================
        //Constants: Synchronized Sampling Packet Information
        //    PAYLOAD_OFFSET_CHANNEL_MASK        - 0        - The offset into the payload to get the digital channel mask (2 bytes)
        //    PAYLOAD_OFFSET_TICK                - 2        - The offset into the payload to get the tick (2 bytes)
        //    PAYLOAD_OFFSET_TS_SEC            - 4        - The offset into the payload to get the timestamp seconds (4 bytes)
        //    PAYLOAD_OFFSET_TS_NANOSEC        - 8        - The offset into the payload to get the timestamp nanoseconds (4 bytes)
        //    PAYLOAD_OFFSET_CHANNEL_DATA        - 12    - The offset into the payload where the channel data starts
        //=====================================================================================================
        static const uint16 PAYLOAD_OFFSET_CHANNEL_MASK = 0;
        static const uint16 PAYLOAD_OFFSET_TICK            = 2;
        static const uint16 PAYLOAD_OFFSET_TS_SEC        = 4;
        static const uint16 PAYLOAD_OFFSET_TS_NANOSEC    = 8;
        static const uint16 PAYLOAD_OFFSET_CHANNEL_DATA    = 12;

    public:
        //Constructor: AsyncDigitalPacket
        //    Creates a AsyncDigitalPacket from the passed in <WirelessPacket>
        //
        //Parameters:
        //    packet - A <WirelessPacket> determined to be a AsyncDigitalPacket
        explicit AsyncDigitalPacket(const WirelessPacket& packet);

    private:
        AsyncDigitalPacket();    //default constructor disabled

        //Function: parseSweeps
        //    Parses the passed in WirelessPacket for all the sweep information and adds a sweep to the sweeps container
        //
        //Exceptions:
        //    - <Error_UnknownSampleRate>: failed to find the sample rate in the list
        void parseSweeps();

        //Function: wirelessChannelFromChNum
        //    Converts a digital channel number to a <WirelessChannel::ChannelId>
        //
        //Parameters:
        //    channelNum - The digital channel number to convert (digital channel 1 = 1, digital channel 16 = 16)
        //
        //Returns:
        //    The <WirelessChannel::ChannelId> representing the passed in digital channel number
        virtual WirelessChannel::ChannelId wirelessChannelFromChNum(int channelNum) override;

    public:
        //Function: integrityCheck
        //    Verifies that the packet is a well formed Async Digital packet
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