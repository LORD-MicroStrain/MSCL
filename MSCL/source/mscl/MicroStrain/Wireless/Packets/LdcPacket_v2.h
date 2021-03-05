/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "WirelessDataPacket.h"

namespace mscl
{

    //Class: LdcPacket_v2
    //    A <WirelessDataPacket> derived class representing a Low Duty Cycle packet
    class LdcPacket_v2 : public WirelessDataPacket
    {
    private:
        //=====================================================================================================
        //Constants: Low Duty Cycle Packet Information
        //    PAYLOAD_OFFSET_CHANNEL_MASK                - 0        - The offset into the payload to get the channel mask
        //    PAYLOAD_OFFSET_SAMPLE_RATE                - 2        - The offset into the payload to get the sample rate
        //    PAYLOAD_OFFSET_APPID_AND_DATA_TYPE        - 3        - The offset into the payload to get the app id and data type
        //    PAYLOAD_OFFSET_TICK                        - 4        - The offset into the payload to get the tick (2 bytes)
        //    PAYLOAD_OFFSET_CHANNEL_DATA                - 6        - The offset into the payload where the channel data starts
        //=====================================================================================================
        static const uint16 PAYLOAD_OFFSET_CHANNEL_MASK            = 0;
        static const uint16 PAYLOAD_OFFSET_SAMPLE_RATE            = 2;
        static const uint16 PAYLOAD_OFFSET_APPID_AND_DATA_TYPE    = 3;
        static const uint16 PAYLOAD_OFFSET_TICK                    = 4;
        static const uint16 PAYLOAD_OFFSET_CHANNEL_DATA            = 6;

    public:
        //Constructor: LdcPacket_v2
        //    Creates an LdcPacket_v2 from the passed in <WirelessPacket>
        //
        //Parameters:
        //    packet - A <WirelessPacket> determined to be an LdcPacket_v2
        explicit LdcPacket_v2(const WirelessPacket& packet);

    private:
        LdcPacket_v2();        //default constructor disabled

        //Function: parseSweeps
        //    Parses the passed in WirelessPacket for all the sweep information and adds a sweep to the sweeps container
        //
        //Exceptions:
        //    - <Error_UnknownSampleRate>: failed to find the sample rate in the list
        void parseSweeps();

    public:
        //Function: integrityCheck
        //    Verifies that the packet is a well formed Low Duty Cycle packet
        //
        //Parameters:
        //    packet - The fully formed Wireless Packet to check the integrity of
        //
        //Returns:
        //    true if the packet is a well formed LDC packet, false otherwise
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