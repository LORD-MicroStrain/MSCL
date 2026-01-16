/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Packets/WirelessDataPacket.h"

namespace mscl
{
    //Class: RfSweepPacket
    //    A <WirelessDataPacket> derived class representing an RF Sweep packet.
    class RfSweepPacket: public WirelessDataPacket
    {
    public:
        //Constructor: RfSweepPacket
        //    Creates a RfSweepPacket from the passed in <WirelessPacket>.
        //
        //Parameters:
        //    packet - A <WirelessPacket> determined to be an RfSweepPacket.
        explicit RfSweepPacket(const WirelessPacket& packet);

    private:
        RfSweepPacket();        //default constructor disabled

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
