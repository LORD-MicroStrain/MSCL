/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#pragma once

#include "mscl/Types.h"
#include "NmeaPacket.h"
#include <memory>

namespace mscl
{
    class DataBuffer;
    class NmeaPacketCollector;
    class ResponseCollector;

    //Title: NmeaParser

    //Enums: NmeaParserResult
    //    NmeaParserResult_completePacket    - 0            - The packet has been verified as a complete MIP packet
    //    NmeaParserResult_invalidPacket     - 1            - The packet is not a valid MIP packet, at least one byte was incorrect
    //    NmeaParserResult_badChecksum       - 2            - The packet looks like a valid MIP packet, but the checksums do not match
    //    NmeaParserResult_notEnoughData     - 3            - There is not enough data in the DataBuffer to determine if this is a valid/invalid MIP packet
    enum NmeaParserResult
    {
        NmeaParserResult_completePacket,
        NmeaParserResult_invalidPacket,
        NmeaParserResult_badChecksum,
        NmeaParserResult_notEnoughData
    };

    //Class: NmeaParser
    //    Parsers all MIP data and stores it in a corresponding container
    class NmeaParser
    {
    public:
        //Constructor: NmeaParser
        //    Constructor for NmeaParser
        //
        //Parameters:
        //    packetCollector - the <NmeaPacketCollector> to be associated with this parser
        NmeaParser(NmeaPacketCollector* packetCollector);

    private:
        NmeaParser(const NmeaParser&);                //copy constructor disabled
        NmeaParser& operator=(const NmeaParser&);    //assignment operator disabled

    private:
        //Variable: m_packetCollector
        //    The <NmeaPacketCollector> associated with this parser and its parent device
        NmeaPacketCollector* m_packetCollector;

    private:
        //Function: processPacket
        //    Takes an <NmeaPacket>, adds it to the data container if it is a data packet,
        //    or adds it to the appropriate handler depending on the packet type
        //
        //Parameters:
        //    packet - A verified, valid <NmeaPacket> 
        void processPacket(NmeaPacket& packet);

        //Function: isNmeaStartByte
        //    Checks specified u8 to determine if it's one of the possible valid NMEA start characters
        bool isNmeaStartByte(uint8 byte);

    public:
        //Function: parseAsPacket
        //    Takes a DataBuffer that has had its read position moved to the start of a packet 
        //    and verifies that the bytes form a valid MIP packet
        //
        //Parameters:
        //    data - A <DataBuffer> with its read position at the start of a packet (0x7565)
        //    packet - An <NmeaPacket> to hold all the packet information if the packet is verified from the DataBuffer
        //
        //Returns:
        //    An <NmeaParseresult> describing if the packet was verified, or why it failed verification
        NmeaParserResult parseAsPacket(DataBuffer& data, NmeaPacket& packet);

        //Function: parse
        //    Takes a <DataBuffer> and finds the next MIP Packet, 
        //    or the next command response that is expected by the base station.
        //
        //    If a packet is found, the packet will be stored in the <NmeaPacketCollector>
        //    If a command response is found and is expected, it will be handled and passed to the base station directly.
        //
        //Parameters:
        //    data - A <DataBuffer> containing bytes that should be parsed for MIP packets
        void parse(DataBuffer& data);
    };
}