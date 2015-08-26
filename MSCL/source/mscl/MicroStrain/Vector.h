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

#include "Matrix.h"

namespace mscl
{
	//API Class: Vector
	//	Represents a Vector of values
	class Vector
	{
	public:
		//Default Constructor: Vector
		//	Create a Vector object with default values
		Vector();

#ifndef SWIG
		//Constructor: Vector
		//	Creates a Vector object given its data
		Vector(ValueType storedAs, const ByteStream& data);
#endif

	private:
		//Constant: COLUMN_POS = 0
		//	The column position for all (row,column) Matrix functions
		static const uint16 COLUMN_POS = 0;

	private:
		//Variable: m_size
		//	The number of elements that are within the Vector
		uint16 m_size;

		//Variable: m_valuesType
		//	The <ValueType> representing how each value within the Vector is stored
		ValueType m_valuesType;

		//Variable: m_data
		//	A <Matrix> used to store and access the underlying values in the Vector
		Matrix m_data;

	public:
		//API Function: valuesType
		//	Gets how each value within the Vector is stored
		//
		//Returns:
		//	A <ValueType> representing how each value in the Vector is stored
		ValueType valuesType() const;

		//API Function: size
		//	Gets how many values are within the Vector
		//
		//Returns:
		//	The number of values within the Vector
		uint16 size() const;

		//API Function: as_floatAt
		//	Gets the value stored at the given 0-based index, as a 4-byte float
		//
		//Parameters:
		//	index - The 0-based index of which to get the value
		//
		//Returns:
		//	The value stored at the given index, as a float
		//
		//Exceptions:
		//	- std::out_of_range: The position requested is out of range
		float as_floatAt(uint16 index) const;

		//API Function: as_uint16At
		//	Gets the value stored at the given 0-based index, as a 2-byte unsigned integer
		//
		//Parameters:
		//	index - The 0-based index of which to get the value
		//
		//Returns:
		//	The value stored at the given index, as an uint16
		//
		//Exceptions:
		//	- std::out_of_range: The position requested is out of range
		uint16 as_uint16At(uint16 index) const;

		//API Function: as_uint8At
		//	Gets the value stored at the given 0-based index, as a 1-byte uint8
		//
		//Parameters:
		//	index - The 0-based index of which to get the value
		//
		//Returns:
		//	The value stored at the given index, as an uint8
		//
		//Exceptions:
		//	- std::out_of_range: The position requested is out of range
		uint8 as_uint8At(uint16 index) const;

		//API Function: str
		//	Creates a string from the Vector
		//
		//Returns:
		//	A string representing the entire Vector object (ex. "[1.2,3.4,5.6]")
		std::string str() const;
	};
}