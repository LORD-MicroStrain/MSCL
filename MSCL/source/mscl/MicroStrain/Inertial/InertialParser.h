/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/Types.h"
#include "Packets/InertialPacket.h"
#include "InertialDataField.h"
#include <memory>

namespace mscl
{
	class DataBuffer;
	class InertialPacketCollector;
	class ResponseCollector;

	//Title: InertialParser

	//Enums: InertialParseResult
	//	inertialParserResult_completePacket	- 0			- The packet has been verified as a complete MIP packet
	//	inertialParserResult_invalidPacket	- 1			- The packet is not a valid MIP packet, at least one byte was incorrect
	//	inertialParserResult_badChecksum	- 2			- The packet looks like a valid MIP packet, but the checksums do not match
	//	inertialParserResult_notEnoughData	- 3			- There is not enough data in the DataBuffer to determine if this is a valid/invalid MIP packet
	enum InertialParseResult
	{
		inertialParserResult_completePacket,
		inertialParserResult_invalidPacket,
		inertialParserResult_badChecksum,
		inertialParserResult_notEnoughData
	};

	//Class: InertialParser
	//	Parsers all inertial data and stores it in a corresponding container
	class InertialParser
	{
	public:
		//Constructor: InertialParser
		//	Constructor for InertialParser
		//
		//Parameters:
		//	packetCollector - the <InertialPacketCollector> to be associated with this parser
		InertialParser(InertialPacketCollector* packetCollector, std::weak_ptr<ResponseCollector> responseCollector);

	private:
		InertialParser(const InertialParser&);				//copy constructor disabled
		InertialParser& operator=(const InertialParser&);	//assignement operator disabled

	private:
		//Variable: m_packetCollector
		//	The <InertialPacketCollector> associated with this parser and it's parent device
		InertialPacketCollector* m_packetCollector;

		//Variable: m_responseCollector
		//	The <ResponseCollector> associated with this parser and it's parent device
		std::weak_ptr<ResponseCollector> m_responseCollector;

	private:
		//Function: processPacket
		//	Takes an <InertialPacket>, adds it to the data container if it is a data packet,
		//	or adds it to the appropriate handler depending on the packet type
		//
		//Parameters:
		//	packet - A verified, valid <InertialPacket> 
		void processPacket(InertialPacket& packet);

		//Function: findMatchingResponse
		//	Takes an <InertialPacket> and checks if the packet collector has any responses it is waiting on.
		//	If it does, and the packet matches the expected response, the packet is "given" to the packet collector.
		//
		//Parameters:
		//	packet - An <InertialPacket> to match against expected responses
		void findMatchingResponse(InertialPacket& packet);

		//Function: parseFields
		//	Parses the <InertialDataField>s out of the <InertialPacket> and returns them in a container.
		//
		//Parameters:
		//	packet - The <InertialPacket> to parse the fields from
		//
		//Returns:
		//	A vector of <InertialDataField>s parsed from the packet
		InertialDataFields parseFields(InertialPacket& packet);

	public:
		//Function: parseAsPacket
		//	Takes a DataBuffer that has had its read position moved to the start of a packet 
		//	and verifies that the bytes form a valid Inertial (MIP) packet
		//
		//Parameters:
		//	data - A <DataBuffer> with its read position at the start of a packet (0x7565)
		//	packet - An <InertialPacket> to hold all the packet information if the packet is verified from the DataBuffer
		//
		//Returns:
		//	An <InertialParseResult> describing if the packet was verified, or why it failed verification
		InertialParseResult parseAsPacket(DataBuffer& data, InertialPacket& packet);

		//Function: findPacketInBytes
		//	Checks for packets after the current bytes buffer's read position (starting at the next byte, not the current one).
		//	If a packet is found, the packet is processed and the byte buffer's read position is moved.
		//	If a packet is not found, nothing changes in the byte buffer
		//
		//Parameters:
		//	data - The bytes to look through for a packet
		//
		//Returns:
		//	true if a MIP Inertial packet is found, false otherwise
		bool findPacketInBytes(DataBuffer& data);

		//Function: parse
		//	Takes a <DataBuffer> and finds the next MIP Inertial Packet, 
		//	or the next command response that is expected by the base station.
		//
		//	If an ASPP packet is found, the packet will be stored in the <WirelessPacketCollector>
		//	If a command response is found and is expected, it will be handled and passed to the base station directly.
		//
		//Parameters:
		//	data - A <DataBuffer> containing bytes that should be parsed for MicroStrain packets
		void parse(DataBuffer& data);
	};
}