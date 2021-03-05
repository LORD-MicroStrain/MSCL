/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "WirelessDataPacket.h"

namespace mscl
{
    //Class: DiagnosticPacket
    //    A <WirelessDataPacket> derived class representing a Diagnostic packet.
    class DiagnosticPacket: public WirelessDataPacket
    {
    public:
        //Constructor: DiagnosticPacket
        //    Creates a DiagnosticPacket from the passed in <WirelessPacket>.
        //
        //Parameters:
        //    packet - A <WirelessPacket> determined to be an DiagnosticPacket.
        explicit DiagnosticPacket(const WirelessPacket& packet);

    private:
        DiagnosticPacket();        //default constructor disabled

        //Function: parseSweeps
        //    Parses the passed in WirelessPacket for all the sweep information and adds a sweep to the sweeps container
        void parseSweeps();

    public:
        //Function: addDataPoint
        //    Adds a <WirelessDataPoint> from the payload to the given <ChannelData> container.
        //
        //Parameters:
        //    container - The <ChannelData> container to add the data point to.
        //    payload - The <DataBuffer> containing the payload, moved to the position of the info bytes to read.
        //    infoLength - The number of bytes that make up the info item.
        //    infoId - The id of the info item.
        //    nodeAddress - The NodeAddress of the Node this data point was from.
        static void addDataPoint(ChannelData& container, DataBuffer& payload, uint8 infoLength, uint8 infoId, NodeAddress nodeAddress);

    public:
        //Function: integrityCheck
        //    Verifies that the packet is a well formed Diagnostic packet.
        //
        //Parameters:
        //    packet - The fully formed Wireless Packet to check the integrity of.
        //
        //Returns:
        //    true if the packet is a well formed Diagnostic, false otherwise
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