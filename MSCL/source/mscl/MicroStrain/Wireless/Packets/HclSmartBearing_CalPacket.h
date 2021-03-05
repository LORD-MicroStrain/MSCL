/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "WirelessDataPacket.h"

namespace mscl
{

    //Class: HclSmartBearing_CalPacket
    //    A <WirelessDataPacket> derived class representing a HclSmartBearing Raw data packet.
    class HclSmartBearing_CalPacket: public WirelessDataPacket
    {
    private:
        //=====================================================================================================
        //Constants: HclSmartBearing_CalPacket Information
        //    PAYLOAD_OFFSET_APP_ID            - 0        - The offset into the payload to get the application ID
        //    PAYLOAD_OFFSET_ERROR_MASK        - 1        - The offset into the payload to get the sensor board error mask.
        //    PAYLOAD_OFFSET_SAMPLE_RATE       - 2        - The offset into the payload to get the sample rate
        //    PAYLOAD_OFFSET_TICK              - 3        - The offset into the payload to get the tick (2 bytes)
        //    PAYLOAD_OFFSET_TS_SEC            - 5        - The offset into the payload to get the timestamp seconds (4 bytes)
        //    PAYLOAD_OFFSET_TS_NANOSEC        - 9        - The offset into the payload to get the timestamp nanoseconds (4 bytes)
        //=====================================================================================================
        static const uint16 PAYLOAD_OFFSET_APP_ID        = 0;
        static const uint16 PAYLOAD_OFFSET_ERROR_MASK    = 1;
        static const uint16 PAYLOAD_OFFSET_SAMPLE_RATE    = 2;
        static const uint16 PAYLOAD_OFFSET_TICK            = 3;
        static const uint16 PAYLOAD_OFFSET_TS_SEC        = 5;
        static const uint16 PAYLOAD_OFFSET_TS_NANOSEC    = 9;

    public:
        //Constructor: HclSmartBearing_CalPacket
        //    Creates a HclSmartBearing_CalPacket from the passed in <WirelessPacket>.
        //
        //Parameters:
        //    packet - A <WirelessPacket> determined to be a HclSmartBearing_CalPacket.
        explicit HclSmartBearing_CalPacket(const WirelessPacket& packet);

    private:
        HclSmartBearing_CalPacket();    //default constructor disabled

        //Function: parseSweeps
        //    Parses the packet for all the sweep information and adds a sweep to the sweeps container
        //
        //Exceptions:
        //    - <Error_UnknownSampleRate>: failed to find the sample rate in the list
        void parseSweeps();

    public:
        //Function: integrityCheck
        //    Verifies that the packet is a well formed HclSmartBearing_RawPacket packet.
        //
        //Parameters:
        //    packet - The fully formed Wireless Packet to check the integrity of.
        //
        //Returns:
        //    true if the packet is a well formed HclSmartBearing_RawPacket packet, false otherwise.
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