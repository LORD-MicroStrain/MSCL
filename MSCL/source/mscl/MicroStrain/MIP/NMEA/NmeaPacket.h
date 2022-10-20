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
        //    The sentence type from the message
        std::string m_sentenceType;

    public:
        //Function: message
        //    Sets the message bytes
        //
        //Parameters:
        //    bytes - The message as a vector of bytes
        void message(const Bytes& bytes);

        //Function: talkerId
        //    Sets the talker ID string
        void talkerId(std::string id) { m_talkerID = id; }

        //Function: sentenceType
        //    Sets the sentence type string
        void sentenceType(std::string type) { m_sentenceType = type; }
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

        //API Function: talkerId
        //    Gets the talker ID string
        //
        //Returns:
        //    The talker ID string from the message
        const std::string talkerId() const { return m_talkerID; }

        //API Function: sentenceTypes
        //    Gets the sentence type string
        //
        //Returns:
        //    The sentence type string from the message
        const std::string sentenceType() const { return m_sentenceType; }

        //API Function: size
        //    Gets the length of the message
        //
        //Returns:
        //    The length of the message
        const size_t size() const { return m_message.size(); }
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
            NMEA_END_OF_PACKET          = 0x0D0A, // "\r\n"
            NMEA_DATA_START_DELIM       = ',', // before first instance is header info, ',' delimiter used throughout message
            NMEA_CHECKSUM_DELIM         = '*',
            NMEA_PROPRIETARY_INDICATOR  = 'P'
        };

        //=====================================================================================================
        //Enum: NMEA Packet Information
        //  NMEA_MAX_PACKET_SIZE             - 82      - The maximum number of bytes a NMEA message can have (including start, checksum, end bytes)
        //  NMEA_MIN_PACKET_SIZE             - 8        - The minimum number of bytes to make a valid NMEA packet
        //  NMEA_TALKER_ID_LEN               - 2        - Talker ID length ONLY IF NOT PROPRIETY (first char 'P')
        //=====================================================================================================
        enum
        {
            NMEA_MAX_PACKET_SIZE    = 82,
            NMEA_MIN_PACKET_SIZE    = 8,
            NMEA_TALKER_ID_LEN      = 2, // ONLY IF NOT PROPRIETY (first char 'P')
        };

        //=====================================================================================================
        //Constants: Talker ID strings
        //  TALKER_ID_PROPRIETARY   - "P"
        //  TALKER_ID_GNSS          - "GN"
        //  TALKER_ID_GPS           - "GP"
        //  TALKER_ID_GALILEO       - "GA"
        //  TALKER_ID_GLONASS       - "GL"
        //=====================================================================================================
        static const std::string TALKER_ID_PROPRIETARY;
        static const std::string TALKER_ID_GNSS;
        static const std::string TALKER_ID_GPS;
        static const std::string TALKER_ID_GALILEO;
        static const std::string TALKER_ID_GLONASS;

        //=====================================================================================================
        //Enum: NMEA Packet Information
        //  SENTENCE_GGA    - "GGA"
        //  SENTENCE_GLL    - "GLL"
        //  SENTENCE_GSV    - "GSV"
        //  SENTENCE_RMC    - "RMC"
        //  SENTENCE_VTG    - "VTG"
        //  SENTENCE_HDT    - "HDT"
        //  SENTENCE_ZDA    - "ZDA"
        //  SENTENCE_PKRA   - "PKRA"
        //  SENTENCE_PKRR   - "PKRR"
        //=====================================================================================================
        static const std::string SENTENCE_GGA;
        static const std::string SENTENCE_GLL;
        static const std::string SENTENCE_GSV;
        static const std::string SENTENCE_RMC;
        static const std::string SENTENCE_VTG;
        static const std::string SENTENCE_HDT;
        static const std::string SENTENCE_ZDA;
        static const std::string SENTENCE_PKRA;
        static const std::string SENTENCE_PKRR;
    };
#endif
}