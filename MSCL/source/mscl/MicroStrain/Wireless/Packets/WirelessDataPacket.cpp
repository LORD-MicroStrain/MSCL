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
#include "stdafx.h"
#include "WirelessDataPacket.h"

#include <assert.h>
#include <boost/numeric/conversion/cast.hpp>

namespace mscl
{
	WirelessDataPacket::WirelessDataPacket() :
		m_sweepPos(0),
		m_dataType(WirelessTypes::dataType_2byteUInt_16bitRes),
		m_sweepSize(0),
		m_numSweeps(0),
		m_payloadOffsetChannelData(0)
	{
	}

	//	Adds a single DataSweep to the data packet
	void WirelessDataPacket::addSweep(const DataSweep& sweep)
	{
		m_dataSweeps.push_back(sweep);
	}

	void WirelessDataPacket::addDataPoint(ChannelData& container, uint8 channelNumber, int channelDataIndex, int sweepIndex, WirelessChannel::ChannelId channelName) const
	{
		//find the offset into the payload to get the data
		uint32 offset = (sweepIndex * m_sweepSize) + (channelDataIndex * WirelessTypes::dataTypeSize(m_dataType)) + m_payloadOffsetChannelData;

		anyType data;

		//parse the data from the payload
		getPayloadData(offset, data);

		container.emplace_back(channelName, channelNumber, WirelessTypes::dataTypeToValueType(m_dataType), data);
	}

	//	Gets the next DataSweep in the packet
	void WirelessDataPacket::getNextSweep(DataSweep& sweepResult)
	{
		//check if the current sweep position is out of range
		assert(m_sweepPos < m_dataSweeps.size());

		//return the current data sweep, and then increment the sweep position
		sweepResult = m_dataSweeps.at(m_sweepPos++);
	}

	std::size_t WirelessDataPacket::numSweepsRemaining() const
	{
		return numSweeps() - m_sweepPos;
	}

	//	Gets the number of sweeps
	std::size_t WirelessDataPacket::numSweeps() const
	{
		return m_dataSweeps.size();
	}

	bool WirelessDataPacket::moreSweeps() const
	{
		return (numSweepsRemaining() > 0);
	}


	
	//	Gets the WirelessChannel::ChannelId enum from the channel number
	WirelessChannel::ChannelId WirelessDataPacket::wirelessChannelFromChNum(int channelNum)
	{
		return static_cast<WirelessChannel::ChannelId>(channelNum);
	}

	void WirelessDataPacket::getPayloadData(size_t payloadPosition, anyType& result) const
	{
		typedef WirelessTypes WT;

		switch(m_dataType)
		{
			//4 byte float value
			case WT::dataType_4ByteFloat:
				result = m_payload.read_float(payloadPosition);
				break;

			//4 byte uint32 value
			case WT::dataType_4byteUInt:
				result = m_payload.read_uint32(payloadPosition);
				break;

			//2 byte uint16 value (shifted, needs shifted right)
			case WT::dataType_2byteUInt_shifted:
				result = boost::numeric_cast<uint16>(m_payload.read_uint16(payloadPosition) >> 1);
				break;

			//2 byte uint16 value
			case WT::dataType_2byteUInt_12bitRes:
			case WT::dataType_2byteUInt_16bitRes:
			default:
				result = m_payload.read_uint16(payloadPosition);
				break;
		}
	}
}