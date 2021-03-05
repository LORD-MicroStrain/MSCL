/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "WirelessDataPacket.h"

namespace mscl
{

    //Class: SyncSamplingMathPacket
    //    A <WirelessDataPacket> derived class representing a Synchronized Sampling Math packet
    class SyncSamplingMathPacket : public WirelessDataPacket
    {
    public:
        //Constructor: SyncSamplingMathPacket
        //    Creates a SyncSamplingMathPacket from the passed in <WirelessPacket>
        //
        //Parameters:
        //    packet - A <WirelessPacket> determined to be a SyncSamplingMathPacket
        explicit SyncSamplingMathPacket(const WirelessPacket& packet);

    private:
        SyncSamplingMathPacket();    //default constructor disabled

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