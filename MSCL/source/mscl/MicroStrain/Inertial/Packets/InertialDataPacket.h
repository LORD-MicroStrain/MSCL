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
//PUBLIC_HEADER
#pragma once

#include "InertialPacket.h"
#include "mscl/Timestamp.h"
#include "mscl/Types.h"
#include "mscl/MicroStrain/Inertial/InertialDataPoint.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "InertialPacket.h"

#include <memory>
#include <vector>

namespace mscl
{
	class InertialFieldParser;

	//API Class: InertialDataPacket
	//	An Inertial Data Packet that contains both valid and invalid data from an Inertial Device.
	class InertialDataPacket : public InertialPacket
	{
	public:
		//Constructor: InertialDataPacket
		//	Creates a default constructed InertialDataPacket
		InertialDataPacket();

		//Constructor: InertialDataPacket
		//	Creates an InertialDataPacket object
		//
		//Parameters:
		//	packet - The <InertialPacket> that was found to be an InertialDataPacket
		explicit InertialDataPacket(const InertialPacket& packet);

	private:
		//Variable: m_dataFields
		//	The <InertialDataFields> that are contained within this packet
		InertialDataFields m_dataFields;

		//Variable: m_points
		//	The <InertialDataPoints> within this packet
		InertialDataPoints m_points;

		//Variable: m_timeStamp
		//	The <Timestamp> of when this packet was received
		Timestamp m_timeStamp;

	private:
		//Function: parseDataFields
		//	Parses the passed in InertialPacket for all the field information and adds a data field to the <InertialDataFields> container
		//	Also parses out all the <InertialDataPoints> in the fields that were created and adds them to m_points
		void parseDataFields();

		//Function: parsePointsInField
		//	Parses an <InertialDataField> for InertialDataPoints and puts them into m_points
		//
		//Parameters:
		//	field - The <InertialDataField> to parse for data points
		void parsePointsInField(const InertialDataField& field);

	public:
		//API Function: data
		//	Gets all the <InertialDataPoints> that are contained within this packet
		//
		//Returns:
		//	The <InertialDataPoints> that are contained within this packet
		//
		//Example Use:
		//	(start code)
		//		SerialConnection connection("COM25");
		//		InertialNode device(&connection);
		//		InertialDataPacket packet = device.getNextDataPacket();
		//		InertialDataPoints data = packet.data();
		//	(end code)
		const InertialDataPoints& data() const;

		//API Function: timestamp
		//	Gets the <Timestamp> representing when the packet was received by MSCL
		//	Note: This is not the same as when the user asked for the "nextDataPacket"
		//
		//Returns:
		//	A <Timestamp> representing when the packet was received by MSCL
		Timestamp timestamp() const;
	};

	//API Typedef: InertialDataPackets
	//	Typedef for a vector of <InertialDataPacket> objects.
	typedef std::vector<InertialDataPacket> InertialDataPackets;
}