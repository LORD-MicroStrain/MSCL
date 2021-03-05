/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/Types.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"

namespace mscl
{
    //API Class: RawBytePacket
    //    A class that contains packet information about an Inertial packet
    class RawBytePacket
    {

    public:
        //=====================================================================================================
        //Enums: MIP Packet Bytes
        //    INVALID_PACKET            - Start of packet found, but packet was invalid
        //    DATA_PACKET               - Complete data packet
        //    COMMAND_PACKET            - Complete command or command response packet
        //    NO_PACKET_FOUND           - No packet was found in these bytes
        //=====================================================================================================
        enum PacketType
        {
            INVALID_PACKET,
            DATA_PACKET,
            COMMAND_PACKET,
            NO_PACKET_FOUND
        };

        //=====================================================================================================
        //Enums: MIP Packet Information
        //  FROM_READ            - The packet was read from the device
        //  FROM_SEND            - The packet was sent to the device
        //=====================================================================================================
        enum PacketSource
        {
            FROM_READ,
            FROM_SEND
        };

        //Default Constructor: RawBytePacket
        //    The default constructor for a RawBytePacket object
        RawBytePacket();

    public:
        //Typedef: Payload
        //    typedef for the bytes that make up a payload in a packet
        typedef ByteStream Payload;

    protected:
        //Variable: m_packetType
        //    The packet type of the RawBytePacket
        PacketType m_packetType;

        //Variable: m_packetType
        //    The source of the RawBytePacket
        PacketSource m_source;

        //Variable: m_payload
        //    The payload bytes in the packet
        Payload m_payload;

    public:
        //Function: payload
        //    Sets the payload bytes of the packet
        //
        //Parameters:
        //    bytes - The payload of the packet, as a vector of bytes
        void payload(const Bytes& bytes);

        //Function: type
        //    Sets the PacketType of the RawBytePacket
        //
        //Parameters:
        //    set - The PacketType value to set
        void type(PacketType type);

        //Function: source
        //    Sets the PacketSource of the RawBytePacket
        //
        //Parameters:
        //    set - The PacketSource value to set
        void source(PacketSource source);

        //API Function: type
        //    Gets the PacketType of the packet
        //
        //Returns:
        //    PacketType of the packet
        PacketType type() const;

        //API Function: source
        //    Gets the PacketSource of the packet
        //
        //Returns:
        //    PacketSource of the packet
        PacketSource source() const;

        //API Function: payload
        //    Gets the payload bytes of the packet
        //
        //Returns:
        //    The payload of the packet, as a vector of bytes
        const std::vector<uint8> payload() const;
    };

    //API Typedef: RawBytePackets
    //    Typedef for a vector of <RawBytePacket> objects.
    typedef std::vector<RawBytePacket> RawBytePackets;
}