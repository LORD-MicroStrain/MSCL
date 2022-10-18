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
        typedef ByteStream Message;

    protected:
        //Variable: m_message
        //    The message in bytes
        Message m_message;

        //Variable: m_talkerId
        //    The talker ID string from the message
        std::string m_talkerID;

        //Variable: m_sentenceType

    public:
        //Function: message
        //    Sets the message bytes
        //
        //Parameters:
        //    bytes - The message as a vector of bytes
        void message(const Bytes& bytes);
#endif

        //API Function: message
        //    Gets the message string
        //
        //Returns:
        //    The message as a string
        const std::string message() const;

        //API Function: message
        //    Gets the message in bytes
        //
        //Returns:
        //    The message as a vector of bytes
        const Bytes message_asBytes() const;
    };

#ifndef SWIG
    //Struct: NmeaPacketInfo
    //    Contains constants representing information on NMEA Packets
    struct NmeaPacketInfo
    {
        //=====================================================================================================
        //Enum: NMEA identifiers
        //    NMEA_START_OF_PACKET      - "$"       - The start of a NMEA packet/sentence
        //    NMEA_START_OF_PACKET_ALT  - "!"       - The start of a NMEA encapsulation sentence
        //    NMEA_END_OF_PACKET        - "\r\n"    - The end of a NMEA packet/sentence
        //    NMEA_DATA_START_DELIM     - ","       - Characters before first instance is header info, ',' delimiter used throughout message
        //    NMEA_CHECKSUM_DELIM       - "*"       - NMEA checksum delimiter
        //=====================================================================================================
        enum
        {
            NMEA_START_OF_PACKET        = '$',
            NMEA_START_OF_PACKET_ALT    = '!',
            NMEA_END_OF_PACKET          = ('\r' << 8) + '\n',
            NMEA_DATA_START_DELIM       = ',', // before first instance is header info, ',' delimiter used throughout message
            NMEA_CHECKSUM_DELIM         = '*',
            NMEA_PROPRIETARY_INDICATOR  = 'P'
        };

        //=====================================================================================================
        //Enum: NMEA Packet Information
        //  NMEA_MIN_PACKET_SIZE             - 8        - The minimum number of bytes to make a valid NMEA packet
        //=====================================================================================================
        enum
        {
            NMEA_MIN_PACKET_SIZE    = 8,
            NMEA_TALKER_ID_LEN      = 2, // ONLY IF NOT PROPRIETY (first char 'P')
            NMEA_PROPRIETY_ID_LEN   = 1, // If proprietary (first char 'P'), no talker id
        };


    };
#endif
}