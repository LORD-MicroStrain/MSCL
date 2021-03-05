/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "WirelessDataPacket.h"

namespace mscl
{

    //Class: BufferedLdcPacket
    //    A <WirelessDataPacket> derived class representing a Buffered LDC packet
    class BufferedLdcPacket : public WirelessDataPacket
    {
    private:
        //=====================================================================================================
        //Constants: Buffered LDC Packet Information
        //    PAYLOAD_OFFSET_APP_ID            - 0        - The offset into the payload to get the application ID
        //    PAYLOAD_OFFSET_CHANNEL_MASK        - 1        - The offset into the payload to get the channel mask
        //    PAYLOAD_OFFSET_SAMPLE_RATE        - 2        - The offset into the payload to get the sample rate
        //    PAYLOAD_OFFSET_DATA_TYPE        - 3        - The offset into the payload to get the data type
        //    PAYLOAD_OFFSET_TICK                - 4        - The offset into the payload to get the tick (2 bytes)
        //    PAYLOAD_OFFSET_CHANNEL_DATA        - 6        - The offset into the payload where the channel data starts
        //=====================================================================================================
        static const uint16 PAYLOAD_OFFSET_APP_ID        = 0;
        static const uint16 PAYLOAD_OFFSET_CHANNEL_MASK = 1;
        static const uint16 PAYLOAD_OFFSET_SAMPLE_RATE    = 2;
        static const uint16 PAYLOAD_OFFSET_DATA_TYPE    = 3;
        static const uint16 PAYLOAD_OFFSET_TICK            = 4;
        static const uint16 PAYLOAD_OFFSET_CHANNEL_DATA    = 6;

        //=====================================================================================================
        //Constants: Packet values
        //    APP_ID_VAL    - 0x02    - The App ID of the Packet
        //=====================================================================================================
        static const uint16 APP_ID_VAL    = 0x02;

    public:
        //Constructor: BufferedLdcPacket
        //    Creates a BufferedLdcPacket from the passed in <WirelessPacket>
        //
        //Parameters:
        //    packet - A <WirelessPacket> determined to be a BufferedLdcPacket
        explicit BufferedLdcPacket(const WirelessPacket& packet);

    private:
        BufferedLdcPacket();    //default constructor disabled

    private:
        //Function: parseSweeps
        //    Parses the passed in WirelessPacket for all the sweep information and adds a sweep to the sweeps container
        //
        //Exceptions:
        //    - <Error_UnknownSampleRate>: failed to find the sample rate in the list
        void parseSweeps();

    public:
        //Function: integrityCheck
        //    Verifies that the packet is a well formed Buffered LDC packet
        //
        //Parameters:
        //    packet - The fully formed Wireless Packet to check the integrity of
        //
        //Returns:
        //    true if the packet is a well formed Buffered LDC packet, false otherwise
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