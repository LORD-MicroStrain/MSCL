/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Packets/WirelessDataPacket.h"

namespace mscl
{
    //Class: BeaconEchoPacket
    //    A <WirelessDataPacket> derived class representing a Beacon Echo packet.
    class BeaconEchoPacket : public WirelessDataPacket
    {
    public:
        //Constructor: BeaconEchoPacket
        //    Creates a BeaconEchoPacket from the passed in <WirelessPacket>.
        //
        //Parameters:
        //    packet - A <WirelessPacket> determined to be a BeaconEchoPacket.
        explicit BeaconEchoPacket(const WirelessPacket& packet);

    private:
        BeaconEchoPacket();        //default constructor disabled

        //Function: parseSweeps
        //    Parses the passed in WirelessPacket for all the sweep information and adds a sweep to the sweeps container
        void parseSweeps();

    public:
        //Function: integrityCheck
        //    Verifies that the packet is a well-formed BeaconEchoPacket packet.
        //
        //Parameters:
        //    packet - The fully formed Wireless Packet to check the integrity of.
        //
        //Returns:
        //    true if the packet is a well-formed BeaconEchoPacket, false otherwise
        static bool integrityCheck(const WirelessPacket& packet);
    };
} // namespace mscl
