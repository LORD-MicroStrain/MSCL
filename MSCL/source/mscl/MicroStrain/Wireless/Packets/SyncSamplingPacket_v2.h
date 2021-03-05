/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "WirelessDataPacket.h"

namespace mscl
{

    //Class: SyncSamplingPacket_v2
    //    A <WirelessDataPacket> derived class representing a Synchronized Sampling 16 channel packet
    class SyncSamplingPacket_v2 : public WirelessDataPacket
    {
    private:
        //=====================================================================================================
        //Constants: Synchronized Sampling Packet Information
        //    PAYLOAD_OFFSET_CHANNEL_MASK                    - 0        - The offset into the payload to get the channel mask
        //    PAYLOAD_OFFSET_SAMPLE_RATE                    - 2        - The offset into the payload to get the sample rate
        //    PAYLOAD_OFFSET_SAMPLEMODE_AND_DATA_TYPE        - 3        - The offset into the payload to get the sample mode and data type
        //    PAYLOAD_OFFSET_TICK                            - 4        - The offset into the payload to get the tick (2 bytes)
        //    PAYLOAD_OFFSET_TS_SEC                        - 6        - The offset into the payload to get the timestamp seconds (4 bytes)
        //    PAYLOAD_OFFSET_TS_NANOSEC                    - 10    - The offset into the payload to get the timestamp nanoseconds (4 bytes)
        //    PAYLOAD_OFFSET_CHANNEL_DATA                    - 14    - The offset into the payload where the channel data starts
        //=====================================================================================================
        static const uint16 PAYLOAD_OFFSET_CHANNEL_MASK                = 0;
        static const uint16 PAYLOAD_OFFSET_SAMPLE_RATE                = 2;
        static const uint16 PAYLOAD_OFFSET_SAMPLEMODE_AND_DATA_TYPE    = 3;
        static const uint16 PAYLOAD_OFFSET_TICK                        = 4;
        static const uint16 PAYLOAD_OFFSET_TS_SEC                    = 6;
        static const uint16 PAYLOAD_OFFSET_TS_NANOSEC                = 10;
        static const uint16 PAYLOAD_OFFSET_CHANNEL_DATA                = 14;

    public:
        //=====================================================================================================
        //Enums: SampleMode
        //    sampleMode_first                - 0x00        - The first sample mode enum
        //    sampleMode_legacy                - 0x00        - Legacy Sync Sampling LDC sample mode
        //    sampleMode_burst                - 0x01        - Burst Sync Sampling Mode
        //    sampleMode_continuous            - 0x02        - Continuous (non-burst) Sync Sampling mode
        //    sampleMode_last                    - 0x02        - The last sample mode enum
        //=====================================================================================================
        enum SampleMode
        {
            sampleMode_first                = 0x00,
            
            sampleMode_legacy                = 0x00,
            sampleMode_burst                = 0x01,
            sampleMode_continuous            = 0x02,
            
            sampleMode_last                    = 0x02
        };

    public:
        //Constructor: SyncSamplingPacket_v2
        //    Creates a SyncSamplingPacket_v2 from the passed in <WirelessPacket>
        //
        //Parameters:
        //    packet - A <WirelessPacket> determined to be a SyncSamplingPacket_v2
        explicit SyncSamplingPacket_v2(const WirelessPacket& packet);

    private:
        SyncSamplingPacket_v2();    //default constructor disabled

        //Function: parseSweeps
        //    Parses the passed in WirelessPacket for all the sweep information and adds a sweep to the sweeps container
        //
        //Exceptions:
        //    - <Error_UnknownSampleRate>: failed to find the sample rate in the list
        void parseSweeps();

    public:
        //Function: integrityCheck
        //    Verifies that the packet is a well formed Synchronized Sampling packet
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