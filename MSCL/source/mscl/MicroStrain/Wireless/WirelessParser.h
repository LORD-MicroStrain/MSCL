/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include <map>
#include <memory>

#include "mscl/Types.h"
#include "Packets/WirelessPacket.h"

#include "../../Communication/RawBytePacketCollector.h"

namespace mscl
{
    class DataBuffer;
    class WirelessPacketCollector;
    class ResponseCollector;

    //Class: WirelessParser
    //    Parses all wireless data and stores it in a corresponding container
    class WirelessParser
    {
    public:
        //Enums: ParsePacketResult
        //    parsePacketResult_completePacket        - The packet has been verified as a complete ASPP packet
        //    parsePacketResult_invalidPacket            - The packet is not a valid ASPP packet, at least one byte was incorrect
        //    parsePacketResult_badChecksum            - The packet looks like a valid ASPP packet, but the checksums do not match
        //    parsePacketResult_notEnoughData            - There is not enough data in the DataBuffer to determine if this is a valid/invalid ASPP packet
        //    parsePacketResult_duplicate                - The packet was a duplicate data packet of the last received packet
        enum ParsePacketResult
        {
            parsePacketResult_completePacket,
            parsePacketResult_invalidPacket,
            parsePacketResult_badChecksum,
            parsePacketResult_notEnoughData,
            parsePacketResult_duplicate
        };

        struct DuplicateCheckKey
        {
            NodeAddress nodeAddress;
            WirelessPacket::PacketType packetType;

            DuplicateCheckKey(NodeAddress address, WirelessPacket::PacketType packet):
                nodeAddress(address),
                packetType(packet)
            { }
        };

    public:
        //Constructor: WirelessParser
        //    Constructor for WirelessParser
        //
        //Parameters:
        //    packetCollector - the <WirelessPacketCollector> to be associated with this parser
        //    responseCollector - the <ResponseCollector> to be associated with this parser
        //    rawBytePacketCollector - the <RawBytePacketCollector> to be associated with this parser
        WirelessParser(WirelessPacketCollector& packetCollector, std::weak_ptr<ResponseCollector> responseCollector, RawBytePacketCollector& rawBytePacketCollector);

        WirelessParser() = delete;
        WirelessParser(const WirelessParser&) = delete;
        WirelessParser& operator=(const WirelessParser&) = delete;

    private:
        //Typedef: DuplicateCheckMap
        //    A typedef for a map of <DuplicateCheckKey>s to a timestamp or tick value to check for packet duplication
        typedef std::map<DuplicateCheckKey, uint16> DuplicateCheckMap;

        //Variable: m_packetCollector
        //    The <WirelessPacketCollector> associated with this parser and it's parent base station
        WirelessPacketCollector& m_packetCollector;

        //Variable: m_responseCollector
        //    The <ResponseCollector> associated with this parser and it's parent base station
        std::weak_ptr<ResponseCollector> m_responseCollector;

        //Variable: m_rawBytePacketCollector
        //    The <RawBytePacketCollector> associated with this parser and its parent device
        RawBytePacketCollector& m_rawBytePacketCollector;

        //Variable: m_lastPacketMap
        //    A <DuplicateCheckMap> containing node addresses and their uniqueId values
        DuplicateCheckMap m_lastPacketMap;

    private:
        //Function: processPacket
        //    Takes a <WirelessPacket>, adds it to the data container if it is a data packet,
        //    or adds it to the appropriate handler depending on the packet type
        //
        //Parameters:
        //    packet - A verified, valid <WirelessPacket>
        //    lastReadPos - The last read position where the packet was parsed from.
        //
        //Returns:
        //  true if the packet was processed successfully (was data or a response we expected), false if it failed to be processed.
        bool processPacket(const WirelessPacket& packet, std::size_t lastReadPos);

        //Function: findMatchingResponse
        //    Takes a <DataBuffer> of bytes and checks if the packet collector has any responses it is waiting on.
        //    If it does, and the bytes match the expected response, the bytes are "given" to the packet collector and the read position is moved.
        //
        //Parameters:
        //    data - A <DataBuffer> containing bytes to parse
        //
        //Returns:
        //    true if the bytes matched an expected response, false otherwise
        bool findMatchingResponse(DataBuffer& data);

        //Function: findMatchingResponse
        //    Takes a <WirelessPacket> and checks if the packet collector has any responses it is waiting on.
        //    If it does, and the packet matches the expected response, the packet is "given" to the packet collector.
        //
        //Parameters:
        //    packet - A <WirelessPacket> to match against expected responses
        //    lastReadPos - The last read position where the packet was parsed from.
        //
        //Returns:
        //    true if the packet matched an expected response, false otherwise
        bool findMatchingResponse(const WirelessPacket& packet, std::size_t lastReadPos);

        //Function: isDuplicate
        //    Checks whether the passed in packet is a duplicate of the previous packet that came in.
        //
        //Parameters:
        //    packet - The <WirelessPacket> to check for duplicate.
        //
        //Returns:
        //    true if the packet is a duplicate, false otherwise.
        bool isDuplicate(const WirelessPacket& packet);

        //Function: parseAsPacket_ASPP_v1
        //    Takes a DataBuffer that has had its read position moved to the start of a packet 
        //    and verifies that the bytes form a valid ASPP v1 packet.
        //
        //Parameters:
        //    data - A <DataBuffer> with its read position at the start of a an ASPP v1 packet (0xAA).
        //    packet - A <WirelessPacket> to hold all the packet information if the packet is verified from the DataBuffer.
        //    freq - A <WirelessTypes::Frequency> representing the frequency that this data was collected on.
        //
        //Returns:
        //    A <ParsePacketResult> describing if the packet was verified, or why it failed verification.
        WirelessParser::ParsePacketResult parseAsPacket_ASPP_v1(DataBuffer& data, WirelessPacket& packet, WirelessTypes::Frequency freq);

        //Function: parseAsPacket_ASPP_v2
        //    Takes a DataBuffer that has had its read position moved to the start of a packet 
        //    and verifies that the bytes form a valid ASPP v2 packet.
        //
        //Parameters:
        //    data - A <DataBuffer> with its read position at the start of a an ASPP v2 packet (0xAB).
        //    packet - A <WirelessPacket> to hold all the packet information if the packet is verified from the DataBuffer.
        //    freq - A <WirelessTypes::Frequency> representing the frequency that this data was collected on.
        //
        //Returns:
        //    A <ParsePacketResult> describing if the packet was verified, or why it failed verification.
        WirelessParser::ParsePacketResult parseAsPacket_ASPP_v2(DataBuffer& data, WirelessPacket& packet, WirelessTypes::Frequency freq);

        //Function: parseAsPacket_ASPP_v3
        //    Takes a DataBuffer that has had its read position moved to the start of a packet 
        //    and verifies that the bytes form a valid ASPP v3 packet.
        //
        //Parameters:
        //    data - A <DataBuffer> with its read position at the start of a an ASPP v3 packet (0xAC).
        //    packet - A <WirelessPacket> to hold all the packet information if the packet is verified from the DataBuffer.
        //    freq - A <WirelessTypes::Frequency> representing the frequency that this data was collected on.
        //
        //Returns:
        //    A <ParsePacketResult> describing if the packet was verified, or why it failed verification.
        WirelessParser::ParsePacketResult parseAsPacket_ASPP_v3(DataBuffer& data, WirelessPacket& packet, WirelessTypes::Frequency freq);

    public:
        //Function: parseAsPacket
        //    Takes a DataBuffer that has had its read position moved to the start of a packet 
        //    and verifies that the bytes form a valid ASPP v1 or v2 packet.
        //
        //Parameters:
        //    data - A <DataBuffer> with its read position at the start of a packet (0xAA).
        //    packet - A <WirelessPacket> to hold all the packet information if the packet is verified from the DataBuffer.
        //    freq - A <WirelessTypes::Frequency> representing the frequency that this data was collected on.
        //
        //Returns:
        //    A <ParsePacketResult> describing if the packet was verified, or why it failed verification.
        WirelessParser::ParsePacketResult parseAsPacket(DataBuffer& data, WirelessPacket& packet, WirelessTypes::Frequency freq);

        //Function: findPacketInBytes
        //    Checks for packets after the current bytes buffer's read position (starting at the next byte, not the current one).
        //    If a packet is found, the packet is processed and the byte buffer's read position is moved.
        //    If a packet is not found, nothing changes in the byte buffer
        //
        //Parameters:
        //    data - The bytes to look through for a packet
        //    freq - The <WirelessTypes::Frequency> that this data was collected on
        //
        //Returns:
        //    type of ASPP Packet found
        WirelessPacket::PacketType findPacketInBytes(DataBuffer& data, WirelessTypes::Frequency freq);

        //Function: parse
        //    Takes a <DataBuffer> and finds the next ASPP Wireless Packet, 
        //    or the next command response that is expected by the base station.
        //
        //    If an ASPP packet is found, the packet will be stored in the <WirelessPacketCollector>.
        //    If a command response is found and is expected, it will be handled and passed to the base station directly.
        //
        //Parameters:
        //    data - A <DataBuffer> containing bytes that should be parsed for MicroStrain packets.
        //    freq - The <WirelessTypes::Frequency> representing the radio frequency that this data was collected on.
        void parse(DataBuffer& data, WirelessTypes::Frequency freq);

        void addRawBytePacket(Bytes& rawBytePacket, bool valid, bool packetFound, WirelessPacket::PacketType wirelessType);
    };

    //Function: operator <
    //  Less than operator for <WirelessPareser::DuplicateCheckKey> so that it can be used in a map.
    const bool operator < (const WirelessParser::DuplicateCheckKey& key1, const WirelessParser::DuplicateCheckKey& key2);
}