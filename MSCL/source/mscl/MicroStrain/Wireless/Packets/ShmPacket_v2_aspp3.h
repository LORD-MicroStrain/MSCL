/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "WirelessDataPacket.h"

namespace mscl
{

    //Class: ShmPacket_v2_aspp3
    //    A <WirelessDataPacket> derived class representing a Structural Health Monitoring Packet
    class ShmPacket_v2_aspp3 : public WirelessDataPacket
    {
    public:
        //Constructor: ShmPacket_v2_aspp3
        //    Creates an ShmPacket_v2_aspp3 from the passed in <WirelessPacket>.
        //
        //Parameters:
        //    packet - A <WirelessPacket> determined to be a ShmPacket_v2_aspp3.
        explicit ShmPacket_v2_aspp3(const WirelessPacket& packet);

    private:
        //Variable: m_binCount
        //    The number of bins in the packet.
        size_t m_binCount;

    private:
        ShmPacket_v2_aspp3();    //default constructor disabled

        //Function: parseSweeps
        //    Parses the passed in WirelessPacket for all the sweep information and adds a sweep to the sweeps container.
        void parseSweeps();

    public:
        //Function: integrityCheck
        //    Verifies that the packet is a well formed Shm-Link packet.
        //
        //Parameters:
        //    packet - The fully formed Wireless Packet to check the integrity of.
        //
        //Returns:
        //    true if the packet is a well formed SHM packet, false otherwise.
        static bool integrityCheck(const WirelessPacket& packet);

        //Function: buildChannelName
        //  Builds a channel name for the SHM data.
        //
        //Parameters:
        //  angle - The angle of the data.
        static std::string buildChannelName(float angle);
    };

}