/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "WirelessDataPacket.h"

namespace mscl
{

    //Class: HclSmartBearing_RawPacket
    //    A <WirelessDataPacket> derived class representing a HclSmartBearing Raw data packet.
    class HclSmartBearing_RawPacket: public WirelessDataPacket
    {
    private:
        //=====================================================================================================
        //Constants: HclSmartBearing_RawPacket Information
        //    PAYLOAD_OFFSET_APP_ID            - 0        - The offset into the payload to get the application ID
        //    PAYLOAD_OFFSET_ERROR_MASK        - 1        - The offset into the payload to get the sensor board error mask.
        //    PAYLOAD_OFFSET_SAMPLE_RATE        - 2        - The offset into the payload to get the sample rate
        //    PAYLOAD_OFFSET_TICK                - 3        - The offset into the payload to get the tick (2 bytes)
        //    PAYLOAD_OFFSET_TS_SEC            - 5        - The offset into the payload to get the timestamp seconds (4 bytes)
        //    PAYLOAD_OFFSET_TS_NANOSEC        - 9        - The offset into the payload to get the timestamp nanoseconds (4 bytes)
        //=====================================================================================================
        static const uint16 PAYLOAD_OFFSET_APP_ID        = 0;
        static const uint16 PAYLOAD_OFFSET_ERROR_MASK    = 1;
        static const uint16 PAYLOAD_OFFSET_SAMPLE_RATE    = 2;
        static const uint16 PAYLOAD_OFFSET_TICK            = 3;
        static const uint16 PAYLOAD_OFFSET_TS_SEC        = 5;
        static const uint16 PAYLOAD_OFFSET_TS_NANOSEC    = 9;

        //Enums: RawPacketId
        //    The possible raw packet types.
        //
        //    rawPacket_baseBoard        - 0 - HclSmartBearing Raw Base Board data packet
        //    rawPacket_strainBoard    - 1 - HclSmartBearing Raw Strain Board data packet
        //    rawPacket_inertialBoard - 2 - HclSmartBearing Raw Inertial Board data packet
        enum RawPacketId
        {
            rawPacket_baseBoard        = 0,
            rawPacket_strainBoard    = 1,
            rawPacket_inertialBoard = 2
        };

    public:
        //Constructor: HclSmartBearing_RawPacket
        //    Creates a HclSmartBearing_RawPacket from the passed in <WirelessPacket>.
        //
        //Parameters:
        //    packet - A <WirelessPacket> determined to be a HclSmartBearing_RawPacket.
        explicit HclSmartBearing_RawPacket(const WirelessPacket& packet);

    private:
        //Variable: m_magConversionVal
        //    The conversion value for magnetometer data from the raw base board packet.
        float m_magConversionVal;

    private:
        HclSmartBearing_RawPacket();    //default constructor disabled

        //Function: parseSweeps
        //    Parses the packet for all the sweep information and adds a sweep to the sweeps container
        //
        //Exceptions:
        //    - <Error_UnknownSampleRate>: failed to find the sample rate in the list
        void parseSweeps();

        //Function: parseSweeps_baseBoard
        //    Parses the packet for Raw Base Board data.
        void parseSweeps_baseBoard();

        //Function: parseSweeps_strainBoard
        //    Parses the packet for Raw Strain Board data.
        void parseSweeps_strainBoard();

        //Function: parseSweeps_inertialBoard
        //    Parses the packet for Raw Inertial Board data.
        void parseSweeps_inertialBoard();

        //Function: getMagChValue
        //    Gets the magnetometer data for a channel from the raw base board packet,
        //    taking into account the mag conversion val.
        //
        //Parameters:
        //    packetVal - The raw channel value received from the packet.
        //
        //Returns:
        //    An <anyType> containing the value to store with the data.
        anyType getMagChValue(int16 packetVal);

        //Function: integrityCheck_baseBoard
        //    Verifies that the packet is a well formed HclSmartBearing_RawPacket Base Board packet.
        //
        //Parameters:
        //    packet - The fully formed Wireless Packet to check the integrity of.
        //
        //Returns:
        //    true if the packet is a well formed HclSmartBearing_RawPacket Base Board packet, false otherwise.
        static bool integrityCheck_baseBoard(const WirelessPacket::Payload& payload);

        //Function: integrityCheck_strainBoard
        //    Verifies that the packet is a well formed HclSmartBearing_RawPacket Strain Board packet.
        //
        //Parameters:
        //    packet - The fully formed Wireless Packet to check the integrity of.
        //
        //Returns:
        //    true if the packet is a well formed HclSmartBearing_RawPacket Strain Board packet, false otherwise.
        static bool integrityCheck_strainBoard(const WirelessPacket::Payload& payload);

        //Function: integrityCheck_inertialBoard
        //    Verifies that the packet is a well formed HclSmartBearing_RawPacket Inertial Board packet.
        //
        //Parameters:
        //    packet - The fully formed Wireless Packet to check the integrity of.
        //
        //Returns:
        //    true if the packet is a well formed HclSmartBearing_RawPacket Inertial Board packet, false otherwise.
        static bool integrityCheck_inertialBoard(const WirelessPacket::Payload& payload);

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