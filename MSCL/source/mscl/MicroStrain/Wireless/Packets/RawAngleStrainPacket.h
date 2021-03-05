/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "WirelessDataPacket.h"

namespace mscl
{

    //Class: RawAngleStrainPacket
    //    A <WirelessDataPacket> derived class representing a Raw Angle Strain packet.
    class RawAngleStrainPacket : public WirelessDataPacket
    {
    public:
        //Constructor: RawAngleStrainPacket
        //    Creates an RawAngleStrainPacket from the passed in <WirelessPacket>.
        //
        //Parameters:
        //    packet - A <WirelessPacket> determined to be an RawAngleStrainPacket.
        explicit RawAngleStrainPacket(const WirelessPacket& packet);

    private:
        RawAngleStrainPacket();        //default constructor disabled

        static const uint8 SPECIFIC_ANGLE_MODE = 0x00;
        static const uint8 SPECIFIC_ANGLE_MODE_SYNC = 0x10;
        static const uint8 DIST_ANGLE_MODE = 0x01;
        static const uint8 DIST_ANGLE_MODE_SYNC = 0x11;

        //Function: parseSweeps
        //    Parses the passed in WirelessPacket for all the sweep information and adds a sweep to the sweeps container
        //
        //Exceptions:
        //    - <Error_UnknownSampleRate>: failed to find the sample rate in the list
        void parseSweeps();

        void parseSweepsSync();

    public:
        //Function: integrityCheck
        //    Verifies that the packet is a well formed RawAngleStrainPacket
        //
        //Parameters:
        //    packet - The fully formed Wireless Packet to check the integrity of
        //
        //Returns:
        //    true if the packet is a well formed RawAngleStrainPacket, false otherwise
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

        //Function: distributeAngles
        //    Gets a list of angles based on a low, high, and number of angles.
        //
        //Parameters:
        //    low - The lower bound angle (inclusive).
        //    high - The higher bound angle (inclusive).
        //    count - The total number of angles.
        //
        //Returns:
        //  The angles determined from the distribution range.
        static std::vector<float> distributeAngles(float low, float high, uint8 count);

        //Function: buildChannelName
        //  Builds a channel name for the Raw Angle Strain data.
        //
        //Parameters:
        //  angle - The angle of the data.
        static std::string buildChannelName(float angle);
    };

}