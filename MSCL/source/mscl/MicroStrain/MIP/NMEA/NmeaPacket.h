/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#pragma once

#include "mscl/Types.h"
#include "mscl/MicroStrain/ByteStream.h"

namespace mscl
{
    //API Class: NmeaPacket
    //    A class that contains packet information about a NMEA packet
    class NmeaPacket
    {
    public:
        //Default Constructor: NmeaPacket
        //    The default constructor for a NmeaPacket object
        NmeaPacket();

#ifndef SWIG
    public:
        //Typedef: Payload
        //    typedef for the bytes that make up a payload in a packet
        typedef ByteStream Payload;

    protected:
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
#endif

        //API Function: payload
        //    Gets the payload bytes of the packet
        //
        //Returns:
        //    The payload of the packet, as a vector of bytes
        const std::vector<uint8> payload() const;
    };

#ifndef SWIG
    //Struct: NmeaPacketInfo
    //    Contains constants representing information on NMEA Packets
    struct NmeaPacketInfo
    {
        //=====================================================================================================
        //Constants: NMEA identifiers
        //    NMEA_START_OF_PACKET      - "$"    - The start of a NMEA packet/sentence
        //    NMEA_END_OF_PACKET        - "\r\n" - The end of a NMEA packet/sentence
        //=====================================================================================================
        const std::string NMEA_START_OF_PACKET  = "$";
        const std::string NMEA_END_OF_PACKET    = "\r\n";

        //=====================================================================================================
        //Enums: NMEA Packet Information
        //  NMEA_MIN_PACKET_SIZE             - 8        - The minimum number of bytes to make a valid MIP packet (0x75, 0x65, Descriptor Set, Payload Len, Payload, Checksum)
        //  NMEA_NUM_BYTES_BEFORE_PAYLOAD    - 4        - The number of bytes in the MIP packets before the payload
        //  NMEA_NUM_BYTES_AFTER_PAYLOAD     - 2        - The number of bytes in the MIP packets after the payload
        //=====================================================================================================
        enum
        {
            NMEA_MIN_PACKET_SIZE             = 8,
            NMEA_NUM_BYTES_BEFORE_PAYLOAD    = 4,
            NMEA_NUM_BYTES_AFTER_PAYLOAD     = 2
        };
    };
#endif
}