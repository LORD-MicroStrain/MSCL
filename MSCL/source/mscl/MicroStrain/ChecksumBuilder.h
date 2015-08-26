/*****************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the included
LICENSE.txt file for a copy of the full GNU General Public License.
*****************************************************************************/
#pragma once

#include "ByteStream.h"
#include "mscl/Types.h"

namespace mscl
{
	//Class: ChecksumBuilder
	//	A class used to simply perform checksums on data
	class ChecksumBuilder
	{
	public:
		//Default Constructor: ChecksumBuilder
		//	Creates a ChecksumBuilder object
		ChecksumBuilder(){};

	private:
		//Variable: m_bytes
		//	The <ByteStream> that holds the data that needs checksummed
		ByteStream m_bytes;

	public:
		//Function: append_uint8
		//	Appends a 1-byte unsigned integer to the ChecksumBuilder
		//
		//Parameters:
		//	value - The uint8 to be added to the ChecksumBuilder
		void append_uint8(uint8 value);

		//Function: append_uint16
		//	Appends a 2-byte unsigned integer to the ChecksumBuilder
		//
		//Parameters:
		//	value - The uint16 to be added to the ChecksumBuilder
		void append_uint16(uint16 value);

		//Function: append_uint32
		//	Appends a 4-byte unsigned integer to the ChecksumBuilder
		//
		//Parameters:
		//	value - The uint32 to be added to the ChecksumBuilder
		void append_uint32(uint32 value);

		//Function: appendBytes
		//	Appends a vector of bytes to the end of the current ChecksumBuilder
		//
		//Parameters:
		//	bytes - The bytes to be appended to the ChecksumBuilder
		void appendBytes(const Bytes& bytes);

		//Function: appendByteStream
		//	Appends the entire contents of a ByteStream to the end of the current ChecksumBuilder
		//
		//Parameters:
		//	otherStream - The ByteStream to be appended to the current ChecksumBuilder
		void appendByteStream(const ByteStream& otherStream);

		//Function: simpleChecksum
		//	Returns a simple checksum of all the bytes in the ChecksumBuilder
		//
		//Returns
		//	The simple checksum of all the bytes in the ChecksumBuilder
		uint16 simpleChecksum() const;

		//Function: fletcherChecksum
		//	Returns the Fletcher checksum of all the bytes in the ChecksumBuilder
		//
		//Returns
		//	The Fletcher checksum of all the bytes in the ChecksumBuilder
		uint16 fletcherChecksum() const;
	};

}