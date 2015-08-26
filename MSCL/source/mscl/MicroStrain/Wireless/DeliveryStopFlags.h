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

#include "mscl/Types.h"

namespace mscl
{
	//Class: DeliveryStopFlags
	//	The delivery stop flags indicate which stops on the pipeline act on the application data
	class DeliveryStopFlags
	{
	public:
		//Constructor: DeliveryStopFlags
		//	Initializes a DeliveryStopFlags object
		DeliveryStopFlags();

		//Constructor: DeliveryStopFlags
		//	Initializes a DeliveryStopFlags object given specific values
		DeliveryStopFlags(bool pc, bool appBoard, bool linkBoard, bool baseStation);

	public:
		//Variable: pc
		//	A stop flag representing the pc
		bool pc:			1;	//only occupy 1 bit

		//Variable: appBoard
		//	A stop flag representing the appBoard
		bool appBoard:		1;	//only occupy 1 bit

		//Variable: linkBoard
		//	A stop flag representing the linkBoard
		bool linkBoard:		1;	//only occupy 1 bit

		//Variable: baseStation
		//	A stop flag representing the baseStation
		bool baseStation:	1;	//only occupy 1 bit

	public:
		//Operator: ==
		//	Checks that two DeliveryStopFlags objects are equal
		//
		//Returns:
		//	true if the two DeliveryStopFlags are identical, false otherwise
		bool operator==(const DeliveryStopFlags& src) const;

		//Operator: !=
		//	Checks that two DeliveryStopFlags objects are not equal
		//
		//Returns:
		//	true if the two DeliveryStopFlags are not identical, false otherwise
		bool operator!=(const DeliveryStopFlags& src) const;

		//Function: compare
		//	Checks that two DeliveryStopFlags are identical
		//
		//Returns:
		//	true if the two DeliveryStopFlags are identical, false otherwise
		bool compare(const DeliveryStopFlags& src) const;

		//Function: fromByte
		//	Sets all the stop flags based on the byte value passed in
		//
		//Parameters:
		//	dsf - The delivery stop flag byte
		static DeliveryStopFlags fromByte(uint8 dsf);

		//Function: toByte
		//	Gets the delivery stop flag byte value based on the current stop flags set
		//
		//Returns:
		//	The delivery stop flag byte built from the current set stop flags
		uint8 toByte() const;
	};
}