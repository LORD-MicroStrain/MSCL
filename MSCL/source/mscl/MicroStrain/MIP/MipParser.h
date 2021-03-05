/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/Types.h"
#include "Packets/MipPacket.h"
#include "../../Communication/RawBytePacketCollector.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include <memory>

namespace mscl
{
    class DataBuffer;
    class MipPacketCollector;
    class ResponseCollector;

    //Title: MipParser

    //Enums: MipParseResult
    //    mipParserResult_completePacket    - 0            - The packet has been verified as a complete MIP packet
    //    mipParserResult_invalidPacket     - 1            - The packet is not a valid MIP packet, at least one byte was incorrect
    //    mipParserResult_badChecksum       - 2            - The packet looks like a valid MIP packet, but the checksums do not match
    //    mipParserResult_notEnoughData     - 3            - There is not enough data in the DataBuffer to determine if this is a valid/invalid MIP packet
    enum MipParseResult
    {
        mipParserResult_completePacket,
        mipParserResult_invalidPacket,
        mipParserResult_badChecksum,
        mipParserResult_notEnoughData
    };

    //Class: MipParser
    //    Parsers all MIP data and stores it in a corresponding container
    class MipParser
    {
    public:
        //Constructor: MipParser
        //    Constructor for MipParser
        //
        //Parameters:
        //    packetCollector - the <MipPacketCollector> to be associated with this parser
        //    rawBytePacketCollector - the <RawBytePacketCollector> to be associated with this parser
        MipParser(MipPacketCollector* packetCollector, std::weak_ptr<ResponseCollector> responseCollector, RawBytePacketCollector* rawBytePacketCollector);

    private:
        MipParser(const MipParser&);                //copy constructor disabled
        MipParser& operator=(const MipParser&);    //assignment operator disabled

    private:
        //Variable: m_packetCollector
        //    The <MipPacketCollector> associated with this parser and its parent device
        MipPacketCollector* m_packetCollector;

        //Variable: m_responseCollector
        //    The <ResponseCollector> associated with this parser and its parent device
        std::weak_ptr<ResponseCollector> m_responseCollector;

        //Variable: m_rawBytePacketCollector
        //    The <RawBytePacketCollector> associated with this parser and its parent device
        RawBytePacketCollector* m_rawBytePacketCollector;

    private:
        //Function: processPacket
        //    Takes an <MipPacket>, adds it to the data container if it is a data packet,
        //    or adds it to the appropriate handler depending on the packet type
        //
        //Parameters:
        //    packet - A verified, valid <MipPacket> 
        void processPacket(MipPacket& packet);

        //Function: findMatchingResponse
        //    Takes an <MipPacket> and checks if the packet collector has any responses it is waiting on.
        //    If it does, and the packet matches the expected response, the packet is "given" to the packet collector.
        //
        //Parameters:
        //    packet - An <MipPacket> to match against expected responses
        void findMatchingResponse(MipPacket& packet);

        //Function: parseFields
        //    Parses the <MipDataField>s out of the <MipPacket> and returns them in a container.
        //
        //Parameters:
        //    packet - The <MipPacket> to parse the fields from
        //
        //Returns:
        //    A vector of <MipDataField>s parsed from the packet
        MipDataFields parseFields(MipPacket& packet);

    public:
        //Function: parseAsPacket
        //    Takes a DataBuffer that has had its read position moved to the start of a packet 
        //    and verifies that the bytes form a valid MIP packet
        //
        //Parameters:
        //    data - A <DataBuffer> with its read position at the start of a packet (0x7565)
        //    packet - An <MipPacket> to hold all the packet information if the packet is verified from the DataBuffer
        //
        //Returns:
        //    An <MipParseResult> describing if the packet was verified, or why it failed verification
        MipParseResult parseAsPacket(DataBuffer& data, MipPacket& packet);

        //Function: findPacketInBytes
        //    Checks for packets after the current bytes buffer's read position (starting at the next byte, not the current one).
        //    If a packet is found, the packet is processed and the byte buffer's read position is moved.
        //    If a packet is not found, nothing changes in the byte buffer
        //
        //Parameters:
        //    data - The bytes to look through for a packet
        //
        //Returns:
        //    true if a MIP packet is found, false otherwise
        bool findPacketInBytes(DataBuffer& data);

        //Function: parse
        //    Takes a <DataBuffer> and finds the next MIP Packet, 
        //    or the next command response that is expected by the base station.
        //
        //    If a packet is found, the packet will be stored in the <MipPacketCollector>
        //    If a command response is found and is expected, it will be handled and passed to the base station directly.
        //
        //Parameters:
        //    data - A <DataBuffer> containing bytes that should be parsed for MIP packets
        void parse(DataBuffer& data);

        //Function: getCommandDescriptor
        //    Takes a <Bytes> and finds the command descriptor.
        //
        //    If a command descriptor is found, return the command descriptor
        //    If a command descriptor is not found, return 0x0.
        //
        //Parameters:
        //    packet - A <Bytes> containing bytes of a raw MIP Packet.
        static uint8 getCommandDescriptor(Bytes packet);

        void addRawBytePacket(Bytes& rawBytePacket, bool valid, bool packetFound);
    };
}