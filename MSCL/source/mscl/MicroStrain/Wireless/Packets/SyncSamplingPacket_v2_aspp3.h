/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Packets/WirelessDataPacket.h"

namespace mscl
{
    //Class: SyncSamplingPacket_v2_aspp3
    //    A <WirelessDataPacket> derived class representing a Synchronized Sampling 16 channel packet
    class SyncSamplingPacket_v2_aspp3 : public WirelessDataPacket
    {
        //=====================================================================================================
        //Constants: Synchronized Sampling Packet Information
        //    PAYLOAD_OFFSET_CHANNEL_MASK - 4  - The offset into the payload to get the channel mask
        //    PAYLOAD_OFFSET_SAMPLE_RATE  - 6  - The offset into the payload to get the sample rate
        //    PAYLOAD_OFFSET_DATA_TYPE    - 7  - The offset into the payload to get the sample mode and data type
        //    PAYLOAD_OFFSET_TICK         - 8  - The offset into the payload to get the tick
        //    PAYLOAD_OFFSET_TS           - 10 - The offset into the payload to get the timestamp seconds
        //    PAYLOAD_OFFSET_CHANNEL_DATA - 18 - The offset into the payload where the channel data starts
        //=====================================================================================================
        static const uint16 PAYLOAD_OFFSET_CHANNEL_MASK = 4;
        static const uint16 PAYLOAD_OFFSET_SAMPLE_RATE  = 6;
        static const uint16 PAYLOAD_OFFSET_DATA_TYPE    = 7;
        static const uint16 PAYLOAD_OFFSET_TICK         = 8;
        static const uint16 PAYLOAD_OFFSET_TS           = 10;
        static const uint16 PAYLOAD_OFFSET_CHANNEL_DATA = 18;

    public:
        //Constructor: SyncSamplingPacket_v2_aspp3
        //    Creates a SyncSamplingPacket_v2_aspp3 from the passed in <WirelessPacket>
        //
        //Parameters:
        //    packet - A <WirelessPacket> determined to be a SyncSamplingPacket_v2_aspp3
        explicit SyncSamplingPacket_v2_aspp3(const WirelessPacket& packet);

    private:
        SyncSamplingPacket_v2_aspp3();    //default constructor disabled

        //Function: parseSweeps
        //    Parses the passed in WirelessPacket for all the sweep information and adds a sweep to the sweeps container
        //
        //Exceptions:
        //    - <Error_UnknownSampleRate>: failed to find the sample rate in the list
        void parseSweeps();

    public:
        //Function: integrityCheck
        //    Verifies that the packet is a well-formed Synchronized Sampling packet
        //
        //Parameters:
        //    packet - The fully formed Wireless Packet to check the integrity of
        //
        //Returns:
        //    true if the packet is a well-formed Sync Sampling packet, false otherwise
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
