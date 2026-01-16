/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

namespace mscl
{
    class WirelessPacket;

    //Class: WirelessPacketUtils
    //    Contains useful utility functions for interfacing with MicroStrain's Wireless packets
    class WirelessPacketUtils
    {
    public:
        //Function: correctPacketType
        //    Some packets are not properly identified.
        //    This function looks for special cases of misidentified packets and corrects them.
        //
        //Parameters:
        //    packet - A reference to a <WirelessPacket> which contains all the wireless packet data and info
        static void correctPacketType(WirelessPacket& packet);

        //Function: packetIntegrityCheck
        //    Verifies that the packet matches the packet type that it is currently set to
        //
        //Parameters:
        //    packet - A reference to the <WirelessPacket> to check the integrity of
        //
        //Returns:
        //    true if the packet's bytes are what they should be for its current type, false otherwise
        static bool packetIntegrityCheck(const WirelessPacket& packet);
    };
} // namespace mscl
