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

#include "mscl/MicroStrain/ResponsePattern.h"
#include "mscl/Timestamp.h"

namespace mscl
{
#ifndef SWIG

	//Class: BaseStation_SetBeacon
	//	Contains logic for the base station set (enable/disable) beacon command
	class BaseStation_SetBeacon
	{
	private:
		BaseStation_SetBeacon();											//default constructor disabled
		BaseStation_SetBeacon(const BaseStation_SetBeacon&);				//copy constructor disabled
		BaseStation_SetBeacon& operator=(const BaseStation_SetBeacon&);		//assignement operator disabled

	public:
		//=====================================================================================================
		//Constants: Packet Information
		//	COMMAND_ID	- 0xBEAC		- The Command ID for the set beacon command
		//=====================================================================================================
		static const uint16 COMMAND_ID	= 0xBEAC;


		//Function: buildCommand
		//	Builds the set beacon command packet, using the passed in seconds as the start time
		//
		//Parameters:
		//	utcTime - The start time for the beacon in UTC seconds from the Unix Epoch (01/01/1970)
		//
		//Returns:
		//	A <ByteStream> containing the base station set beacon command
		static ByteStream buildCommand(uint32 utcTime);

		//Class: Response
		//	Handles the response to the base station write eeprom command
		class Response : public ResponsePattern
		{
		public:
			//Constructor: Response
			//	Creates a set beacon Response object
			//
			//Parameters:
			//	utcTime - The start time for the beacon in UTC seconds from the Unix Epoch (01/01/1970)
			//	collector - The <ResponseCollector> used to register and unregister the response
			Response(uint64 utcTime, std::weak_ptr<ResponseCollector> collector);

		private:
			//Variable: m_beaconStartTime
			//	The start time that was sent to the beacon as a Timestamp object
			Timestamp m_beaconStartTime;

		public:
			//Function: match
			//	Checks if the bytes passed in match the response pattern from their current read position
			//
			//Parameters:
			//	data - The <DataBuffer> containing the bytes in which to try to find the pattern
			//
			//Returns:
			//	true if the response pattern was found, false otherwise
			virtual bool match(DataBuffer& data) override;

			//Function: beaconStartTime
			//	Gets the start time that was sent to enable the beacon 
			//
			//Returns:
			//	a <Timestamp> representing the start time that was sent to enable the beacon
			Timestamp beaconStartTime() const;
		};
	};

#endif

}