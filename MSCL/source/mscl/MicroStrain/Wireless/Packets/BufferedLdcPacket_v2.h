/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Packets/WirelessDataPacket.h"

namespace mscl
{
    //Class: BufferedLdcPacket_v2
    //    A <WirelessDataPacket> derived class representing a Synchronized Sampling (Buffered LDC) packet
    class BufferedLdcPacket_v2 : public WirelessDataPacket
    {
        //=====================================================================================================
        //Constants: Buffered LDC Packet Information
        //    PAYLOAD_OFFSET_CHANNEL_MASK          - 0  - The offset into the payload to get the channel mask
        //    PAYLOAD_OFFSET_SAMPLE_RATE           - 2  - The offset into the payload to get the sample rate
        //    PAYLOAD_OFFSET_APPID_AND_DATA_TYPE   - 3  - The offset into the payload to get the app id and data type
        //    PAYLOAD_OFFSET_TICK                  - 4  - The offset into the payload to get the tick (2 bytes)
        //    PAYLOAD_OFFSET_CHANNEL_DATA          - 6  - The offset into the payload where the channel data starts
        //=====================================================================================================
        static const uint16 PAYLOAD_OFFSET_CHANNEL_MASK        = 0;
        static const uint16 PAYLOAD_OFFSET_SAMPLE_RATE         = 2;
        static const uint16 PAYLOAD_OFFSET_APPID_AND_DATA_TYPE = 3;
        static const uint16 PAYLOAD_OFFSET_TICK                = 4;
        static const uint16 PAYLOAD_OFFSET_CHANNEL_DATA        = 6;

        //=====================================================================================================
        //Constants: Packet values
        //    APP_ID_VAL    - 0x02    - The App ID of the Packet
        //=====================================================================================================
        static const uint16 APP_ID_VAL    = 0x02;

    public:
        //Constructor: BufferedLdcPacket_v2
        //    Creates a BufferedLdcPacket_v2 from the passed in <WirelessPacket>
        //
        //Parameters:
        //    packet - A <WirelessPacket> determined to be a BufferedLdcPacket_v2
        explicit BufferedLdcPacket_v2(const WirelessPacket& packet);

    private:
        BufferedLdcPacket_v2();    //default constructor disabled

        //Function: parseSweeps
        //    Parses the passed in WirelessPacket for all the sweep information and adds a sweep to the sweeps container
        //
        //Exceptions:
        //    - <Error_UnknownSampleRate>: failed to find the sample rate in the list
        void parseSweeps();

    public:
        //Function: integrityCheck
        //    Verifies that the packet is a well-formed Buffered LDC packet
        //
        //Parameters:
        //    packet - The fully formed Wireless Packet to check the integrity of
        //
        //Returns:
        //    true if the packet is a well-formed Buffered LDC packet, false otherwise
        static bool integrityCheck(const WirelessPacket& packet);

        //Function: getUniqueId
        //    Gets the unique ID of the <WirelessPacket> passed in
        //
        //Parameters:
        //    packet - The <WirelessPacket> to get the unique id of
        //
        //Returns:
        //    The <UniqueWirelessPacketId> of the passed in packet
        static UniqueWirelessPacketId getUniqueId(const WirelessPacket& packet);
    };
} // namespace mscl
