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
#include "InertialDataPacket.h"

#include "mscl/Utils.h"
#include "InertialFieldParser.h"
#include "mscl/MicroStrain/DataBuffer.h"

namespace mscl
{					
	InertialDataPacket::InertialDataPacket():
		m_timeStamp(0)
	{
	}

	InertialDataPacket::InertialDataPacket(const InertialPacket& packet)
	{
		//construct the data packet from the InertialPacket passed in
		m_descriptorSet		= packet.descriptorSet();
		m_payload			= Payload(packet.payload());
		m_timeStamp			= Timestamp::timeNow();

		//parse the data fields in the packet
		parseDataFields();
	}

	void InertialDataPacket::parseDataFields()
	{
		uint8 fieldDescriptor;
		uint16 fieldType;
		uint32 fieldLen;

		//create a DataBuffer to make parsing easier
		DataBuffer payloadData(m_payload.data());

		while(payloadData.moreToRead())
		{
			Bytes fieldBytes;

			//read the field length byte
			fieldLen = payloadData.read_uint8();

			//read the field descriptor byte
			fieldDescriptor = payloadData.read_uint8();

			//read all the bytes for the current field (up to the field length)
			for(uint32 itr = 0; itr < fieldLen - 2; itr++)
			{
				//add the field bytes to a container
				fieldBytes.push_back(payloadData.read_uint8());
			} 

			fieldType = Utils::make_uint16(m_descriptorSet, fieldDescriptor);

			//add the field to the m_dataFields vector
			InertialDataField tempField(fieldType, fieldBytes);
			m_dataFields.push_back(tempField);

			//parse the data points that are in the existing field that we just created
			parsePointsInField(tempField);
		}
	}

	void InertialDataPacket::parsePointsInField(const InertialDataField& field)
	{
		InertialFieldParser::parseField(field, m_points);
	}

	const InertialDataPoints& InertialDataPacket::data() const
	{
		return m_points;
	}

	Timestamp InertialDataPacket::timestamp() const
	{
		return m_timeStamp;
	}
}