/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "ChecksumBuilder.h"

namespace mscl
{
	void ChecksumBuilder::append_uint8(uint8 value)
	{
		//append the value to the ByteStream
		m_bytes.append_uint8(value);
	}

	void ChecksumBuilder::append_uint16(uint16 value)
	{
		//append the value to the ByteStream
		m_bytes.append_uint16(value);
	}

	void ChecksumBuilder::append_uint32(uint32 value)
	{
		//append the value to the ByteStream
		m_bytes.append_uint32(value);
	}

	void ChecksumBuilder::appendBytes(const Bytes& bytes)
	{
		//append the Bytes to the ByteStream
		m_bytes.appendBytes(bytes);
	}

	void ChecksumBuilder::appendByteStream(const ByteStream& otherStream)
	{
		//append the other ByteStream to the existing ByteStream
		m_bytes.appendByteStream(otherStream);
	}

	uint16 ChecksumBuilder::simpleChecksum() const
	{
		//calculate the checkum of all the bytes that are in m_bytes
		return m_bytes.calculateSimpleChecksum(0, m_bytes.size() - 1);
	}

	uint16 ChecksumBuilder::fletcherChecksum() const
	{
		//calculate the fletcher checkum of all the bytes that are in m_bytes
		return m_bytes.calculateFletcherChecksum(0, m_bytes.size() - 1);
	}
}