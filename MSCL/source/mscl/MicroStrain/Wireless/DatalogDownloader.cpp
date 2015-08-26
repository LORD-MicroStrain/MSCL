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
#include "DatalogDownloader.h"

#include "Configuration/NodeEepromHelper.h"
#include "NodeMemory.h"
#include "WirelessDataPoint.h"
#include "mscl/Utils.h"

namespace mscl
{
	const Version DatalogDownloader::HEADER_VERSION_1_0(1, 0);
	const Version DatalogDownloader::HEADER_VERSION_2_0(2, 0);
	const Version DatalogDownloader::HEADER_VERSION_2_1(2, 1);

	DatalogDownloader::DatalogDownloader(const WirelessNode& node):
		m_node(node),
		m_foundFirstTrigger(false),
		m_outOfMemory(false),
		m_currentByte(0),
		m_sweepCount(0)
	{
		//get the datalogging information from the Node
		m_logPage = m_node.eepromHelper().read_logPage();
		m_pageOffset = m_node.eepromHelper().read_logPageOffset();

		//create the NodeMemory object
		m_nodeMemory.reset(new NodeMemory(m_node, m_logPage, m_pageOffset));
	}

	DatalogDownloader::~DatalogDownloader()
	{
		m_nodeMemory.reset(nullptr);
	}

	uint8 DatalogDownloader::read_uint8(uint64& position) 
	{
		//read the single byte from Node's memory
		uint8 result = m_nodeMemory->at(position);

		//increment the position
		position += 1;

		return result;
	}

	uint16 DatalogDownloader::read_uint16(uint64& position)
	{
		//read single bytes from the Node's memory
		uint8 b1 = m_nodeMemory->at(position);
		uint8 b2 = m_nodeMemory->at(position + 1);

		//increment the position
		position += 2;

		//build into a uint16 and return
		return Utils::make_uint16(b1, b2);
	}

	uint32 DatalogDownloader::read_uint32(uint64& position)
	{
		//read single bytes from the Node's memory
		uint8 b1 = m_nodeMemory->at(position);
		uint8 b2 = m_nodeMemory->at(position + 1);
		uint8 b3 = m_nodeMemory->at(position + 2);
		uint8 b4 = m_nodeMemory->at(position + 3);

		//increment the position
		position += 4;

		//build into a uint32 and return
		return Utils::make_uint32(b1, b2, b3, b4);
	}

	float DatalogDownloader::read_float(uint64& position)
	{
		//read single bytes from the Node's memory
		uint8 b1 = m_nodeMemory->at(position);
		uint8 b2 = m_nodeMemory->at(position + 1);
		uint8 b3 = m_nodeMemory->at(position + 2);
		uint8 b4 = m_nodeMemory->at(position + 3);

		//increment the position
		position += 4;

		//build into a float and return (device data in big endian)
		return Utils::make_float_big_endian(b1, b2, b3, b4);
	}

	std::string DatalogDownloader::read_string(uint64& position, uint64 length)
	{
		std::string result;

		//read 1 byte for the length of the string
		for(uint64 itr = 0; itr < length; ++itr)
		{
			//append the characters to the string
			result.append(1, m_nodeMemory->at(position + itr));
		}

		//increment the position
		position += length;

		return result;
	}

	bool DatalogDownloader::isStartOfTrigger(uint64 position)
	{
		uint64 byteItr = position;

		static const uint16 START_OF_TRIGGER = 0xFFFF;			//the start of trigger
		static const uint8 TRIGGER_HEADER_ID = 0xFD;			//the trigger header id
		static const uint8 MAX_TRIGGER_TYPE = 0x04;				//the max trigger type supported
		static const uint16 MIN_BYTES_B4_DATA = 0x0A;			//the minimum value ever supported for '# bytes before data'
		static const uint16 MAX_BYTES_B4_DATA = 0x3E;			//the maximum value ever supported for '# bytes before data'

		try
		{
			//verify the start of trigger
			if(read_uint16(byteItr) != START_OF_TRIGGER)
			{
				return false;
			}

			//verify the trigger header id
			if(read_uint8(byteItr) != TRIGGER_HEADER_ID)
			{
				return false;
			}

			//verify the trigger type is within range
			if(read_uint8(byteItr) > MAX_TRIGGER_TYPE)
			{
				return false;
			}

			uint8 versionMajor = read_uint8(byteItr);
			uint8 versionMinor = read_uint8(byteItr);

			//verify the header version is one that we support
			Version headerVersion(versionMajor, versionMinor);
			if(headerVersion != HEADER_VERSION_2_1 &&
			   headerVersion != HEADER_VERSION_2_0 &&
			   headerVersion != HEADER_VERSION_1_0)
			{
				return false;
			}

			//verify the # of bytes before channel data value
			uint16 bytesBeforeData = read_uint16(byteItr);
			if(bytesBeforeData < MIN_BYTES_B4_DATA ||
			   bytesBeforeData > MAX_BYTES_B4_DATA)
			{
				return false;
			}

			byteItr += 6;	//move to the sample rate bytes

			//verify the sample rate is a valid rate
			uint16 sampleRateVal = read_uint16(byteItr);
			try
			{
				//if it is an armed datalogging rate, we need to convert it to a WirelessSampleRate
				//Note: if not a datalogging rate, this will just cast it to a WirelessSampleRate without conversion.
				WirelessTypes::WirelessSampleRate rate = WirelessTypes::dataloggingRateToSampleRate(sampleRateVal);

				//check that we can convert it to a SampleRate object
				SampleRate::FromWirelessEepromValue(rate);
			}
			catch(Error_UnknownSampleRate&)
			{
				return false;
			}

			//everthing looks like it is the start of a trigger
			return true;
		}
		catch(Error_NoData&)
		{
			//we attempted to read passed the end of the data
			m_outOfMemory = true;

			//don't throw the exception, just return false as this isn't the start of a trigger
			return false;
		}
	}

	void DatalogDownloader::parseTriggerHeader()
	{
		uint64 byteItr = m_currentByte;

		//TODO: What if an exception is thrown in here??

		//reset the sweep count
		m_sweepCount = 0;

		//move passed the start of header bytes
		byteItr += 3;

		//read the trigger type
		m_sessionInfo.triggerType = static_cast<WirelessTypes::TriggerType>(read_uint8(byteItr));

		//read the header version
		uint8 versionMajor = read_uint8(byteItr);
		uint8 versionMinor = read_uint8(byteItr);
		Version headerVersion(versionMajor, versionMinor);

		//read the number of bytes before the channel data
		uint16 bytesBeforeData = read_uint16(byteItr);
		uint64 byteCounter = byteItr;	//used to calculate if we need to later consume (throw out) bytes that we don't know how to parse

		//read the number of sweeps
		m_sessionInfo.numSweeps = read_uint16(byteItr);

		//Header Version 2.1+
		if(headerVersion >= HEADER_VERSION_2_1)
		{
			//the number of sweeps in the header should be multiplied by 100
			m_sessionInfo.numSweeps *= 100;
		}

		//read the session index
		m_sessionInfo.sessionIndex = read_uint16(byteItr);

		//read the active channel mask
		m_sessionInfo.activeChannels = ChannelMask(read_uint16(byteItr));

		//read the sample rate
		uint16 sampleRateVal = read_uint16(byteItr);

		//if it is an armed datalogging rate, we need to convert it to a WirelessSampleRate
		//Note: if not a datalogging rate, this will just cast it to a WirelessSampleRate without conversion.
		WirelessTypes::WirelessSampleRate rate = WirelessTypes::dataloggingRateToSampleRate(sampleRateVal);
		m_sessionInfo.sampleRate = SampleRate::FromWirelessEepromValue(rate);
		m_sessionInfo.timeBetweenSweeps = m_sessionInfo.sampleRate.samplePeriod().getNanoseconds();

		if(headerVersion >= HEADER_VERSION_2_0)
		{
			//read the data type
			m_sessionInfo.dataType = static_cast<WirelessTypes::DataType>(read_uint8(byteItr));

			byteItr += 1;	//unused byte
		}
		else
		{
			//no data type in the header, always uint16
			m_sessionInfo.dataType = WirelessTypes::dataType_2byteUInt_12bitRes;
		}

		m_sessionInfo.valueType = WirelessTypes::dataTypeToValueType(m_sessionInfo.dataType);

		//read the number of user entered bytes
		uint16 numUserBytes = read_uint16(byteItr);

		//read the user entered string
		m_sessionInfo.userString = read_string(byteItr, numUserBytes);

		//if the user string is an odd number of bytes
		if(m_sessionInfo.userString.length() % 2 != 0)
		{
			//the data has 1 extra byte (always even), need to throw it out
			byteItr += 1;

			if(headerVersion <= HEADER_VERSION_2_1)
			{
				//there is a bug in header version 2.1 and below where the
				//extra user byte isn't added to the bytesBeforeData count
				bytesBeforeData += 1;
			}
		}

		//====================================================
		//MOVE PASSED ANY EXTRA BYTES
		byteItr += (bytesBeforeData - (byteItr - byteCounter));
		//====================================================

		//read the number of bytes per channel
		uint16 bytesPerChannel = read_uint16(byteItr);

		//loop through all of the active channels to get channel action information
		uint16 channelItr = 0;
		uint16 totalChannelMask = m_sessionInfo.activeChannels.count();
		for(channelItr = 0; channelItr < totalChannelMask; ++channelItr)
		{
			byteCounter = byteItr;

			//TODO: read the channel action equation
			byteItr += 1;

			//TODO: read the channel action unit
			byteItr += 1;

			//TODO: read the channel action slope
			byteItr += 4;

			//TODO: read the channel action offset
			byteItr += 4;

			//====================================================
			//MOVE PASSED ANY EXTRA BYTES
			byteItr += (bytesPerChannel - (byteItr - byteCounter));
			//====================================================
		}

		//read the number of bytes before the end of the header
		uint16 bytesBeforeEnd = read_uint16(byteItr);
		byteCounter = byteItr;

		//read the timestamp bytes
		uint32 timestampSeconds = read_uint32(byteItr);
		uint32 timestampNanos = read_uint32(byteItr);

		//build the full nanosecond resolution timestamp
		m_sessionInfo.timestamp = ((static_cast<uint64>(timestampSeconds) * TimeSpan::NANOSECONDS_PER_SECOND) + timestampNanos);

		//====================================================
		//MOVE PASSED ANY EXTRA BYTES
		byteItr += (bytesBeforeEnd - (byteItr - byteCounter));
		//====================================================

		//read everything successfully, move m_currentByte to the new position
		m_currentByte = byteItr;
	}

	bool DatalogDownloader::complete()
	{
		//if the m_outOfMemory flag was set indicating that we are out of memory
		if(m_outOfMemory)
		{
			return true;
		}

		//check if there are no bytes remaining in the Node's datalogging memory
		if(m_nodeMemory->bytesRemaining(m_currentByte) == 0)
		{
			m_outOfMemory = true;
			return true;
		}

		//we still have bytes remaining
		return false;
	}

	LoggedDataSweep DatalogDownloader::getNextData()
	{
		if(complete())
		{
			throw Error_NoData("There is no more data available to download from the Node.");
		}

		//check if the bytes starting at m_currentByte look like the start of a trigger
		if(isStartOfTrigger(m_currentByte))
		{
			//parse the trigger header and update all of the trigger session info
			parseTriggerHeader();

			//set the startOfTrigger flag to true
			m_sessionInfo.startOfTrigger = true;

			m_foundFirstTrigger = true;
		}
		else
		{
			//if the first trigger hasn't been found yet
			if(!m_foundFirstTrigger)
			{
				//the start of trigger isn't at the first memory location on the Node
				m_outOfMemory = true;
				throw Error_NoData("No triggers were found on the Node.");
			}

			//set the startOfTrigger flag to false
			m_sessionInfo.startOfTrigger = false;
		}

		uint64 byteItr = m_currentByte;

		ChannelData chData;

		uint8 lastActiveCh = m_sessionInfo.activeChannels.lastChEnabled();

		//loop through all the channels
		for(uint8 chItr = 1; chItr <= lastActiveCh; ++chItr)
		{
			//if the current channel is enabled
			if(m_sessionInfo.activeChannels.enabled(chItr))
			{
				anyType dataPoint;

				switch(m_sessionInfo.dataType)
				{
					//4 byte float value
					case WirelessTypes::dataType_4ByteFloat:
						dataPoint = read_float(byteItr);
						break;

					//4 byte uint32 value
					case WirelessTypes::dataType_4byteUInt:
						dataPoint = read_uint32(byteItr);
						break;

					//2 byte uint16 value
					case WirelessTypes::dataType_2byteUInt_shifted:
					case WirelessTypes::dataType_2byteUInt_12bitRes:
					case WirelessTypes::dataType_2byteUInt_16bitRes:
					default:
						dataPoint = read_uint16(byteItr);
						break;
				}

				//create a WirelessDataPoint and add it to the ChannelData vector
				chData.push_back(WirelessDataPoint(static_cast<WirelessChannel::ChannelId>(chItr), chItr, m_sessionInfo.valueType, dataPoint));
			}
		}

		//read everything successfully, move m_currentByte to the new position
		m_currentByte = byteItr;

		//calculate the timestamp and tick for the sweep
		uint64 sweepTime = m_sessionInfo.timestamp + (m_sessionInfo.timeBetweenSweeps * m_sweepCount);
		uint64 sweepTick = m_sweepCount;

		//increment the sweep count
		m_sweepCount++;

		//return the LoggedDataSweep object containing the data that was downloaded
		return LoggedDataSweep(Timestamp(sweepTime), sweepTick, chData);
	}

	bool DatalogDownloader::startOfSession()
	{
		return m_sessionInfo.startOfTrigger;
	}

	WirelessTypes::TriggerType DatalogDownloader::triggerType()
	{
		return m_sessionInfo.triggerType;
	}

	uint32 DatalogDownloader::totalSweeps()
	{
		return m_sessionInfo.numSweeps;
	}

	uint16 DatalogDownloader::sessionIndex()
	{
		return m_sessionInfo.sessionIndex;
	}

	const SampleRate& DatalogDownloader::sampleRate()
	{
		return m_sessionInfo.sampleRate;
	}

	const std::string& DatalogDownloader::userString()
	{
		return m_sessionInfo.userString;
	}
}