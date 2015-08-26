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

#include <iomanip>
#include <string>
#include "Types.h"

namespace mscl
{ 
#ifndef SWIG
	//Namespace: Utils
	//	Contains many commonly used utility functions.
	//	Note: Communication with our devices (wireless and inertial) is done in Big Endian.
	namespace Utils
	{
		//Function: valueTypeSize
		//	Gets the size of the <ValueType>
		//
		//Parameters:
		//	type - The <ValueType> to get the size of
		//
		//Returns:
		//	The size of the given <ValueType>
		//
		//Exceptions:
		//	- <Error>: The value type requested does not have a given size
		uint32 valueTypeSize(ValueType type);

		//Function: msb
		//	Gets the Most Significant Byte from the 2-Byte WORD
		//	
		//Parameters:
		//	value - the 2-Byte unsigned integer to find the MSB from
		//
		//Returns:
		//	The Most Significant Byte of the passed in value
		uint8 msb(uint16 value);

		//Function: lsb
		//	Gets the Least Significant Byte from the 2-Byte WORD
		//	
		//Parameters:
		//	value - the 2-Byte unsigned integer to find the LSB from
		//
		//Returns:
		//	The Least Significant Byte of the passed in value
		uint8 lsb(uint16 value);

		//Function: msNibble
		//	Gets the Most Significant Nibble (4-bits) from the 1-Byte value
		//
		//Parameters:
		//	value - the 1-Byte value to find the Most Significant Nibble from
		//
		//Returns:
		//	The Most Significant Nibble of the passed in value
		uint8 msNibble(uint8 value);

		//Function: lsNibble
		//	Gets the Least Significant Nibble (4-bits) from the 1-Byte value
		//
		//Parameters:
		//	value - the 1-Byte value to find the Least Significant Nibble from
		//
		//Returns:
		//	The Least Significant Nibble of the passed in value
		uint8 lsNibble(uint8 value);

		//Function: make_int16
		//	Gets the 2-byte nsigned integer from 2 individual MSB and LSB bytes
		//
		//Parameters:
		//	msb - the Most Significant Byte
		//	lsb - the Lease Significant Byte
		//
		//Returns:
		//	The 2-byte int16 built from the MSB and LSB bytes
		int16 make_int16(uint8 msb, uint8 lsb);

		//Function: split_uint16
		//	Converts the 2-byte unsigned integer into its individual 2 bytes
		//
		//Parameters:
		//	value - the 2 byte uint16 to convert into bytes
		//	msb - holds the Most Significant Byte result
		//	lsb - holds the Least Significant Byte result
		void split_uint16(uint16 value, uint8& msb, uint8& lsb);

		//Function: make_uint16
		//	Gets the 2-byte unsigned integer from 2 individual MSB and LSB bytes
		//
		//Parameters:
		//	msb - the Most Significant Byte
		//	lsb - the Lease Significant Byte
		//
		//Returns:
		//	The 2-byte uint16 built from the MSB and LSB bytes
		uint16 make_uint16(uint8 msb, uint8 lsb);

		//Function: split_uint32
		//	Converts the 4-byte unsigned integer into its 4 individual bytes
		//
		//Parameters:
		//	value - the 4 byte uint32 to convert into bytes
		//	msb - holds the msb result 
		//	byte2 - holds the second byte result
		//	byte3 - holds the third byte result
		//	lsb - holds the lsb result
		void split_uint32(uint32 value, uint8& msb, uint8& byte2, uint8& byte3, uint8& lsb);

		//Function: split_uint32
		//	Converts the 4-byte unsigned integer into its 2 uint16 values.
		//
		//Parameters:
		//	value - the 4 byte uint32 to convert into bytes.
		//	msw - holds the msw result.
		//	lsw - holds the lsw result.
		void split_uint32(uint32 value, uint16& msw, uint16& lsw);

		//Function: make_uint32
		//	gets the 4-byte unsigned integer from the 4 individual bytes
		//
		//Parameters:
		//	msb - the msb to be used
		//	byte2 - the second byte to be used
		//	byte3 - the third byte to be used
		//	lsb - the lsb to be used
		//
		//Returns:
		//	the 4-byte uint32 built from the 4 bytes
		uint32 make_uint32(uint8 msb, uint8 byte2, uint8 byte3, uint8 lsb);

		//Function: make_uint32
		//	gets the 4-byte unsigned integer from the 2 uint16 words.
		//
		//Parameters:
		//	msw - the most significant word to be used.
		//	lsw - the lease significant word to be used.
		//
		//Returns:
		//	the 4-byte uint32 built from the 2 uint16 words.
		uint32 make_uint32(uint16 msw, uint16 lsw);

		//Function: split_float_big_endian
		//	Converts the 4-byte float (in system endian) into its 4 individual bytes in big endian
		//
		//Parameters:
		//	value - the 4 byte float (in system endian) to convert into bytes
		//	msb - holds the msb result
		//	byte2 - holds the second byte result
		//	byte3 - holds the third byte result
		//	lsb - holds the lsb result
		void split_float_big_endian(float value, uint8& msb, uint8& byte2, uint8& byte3, uint8& lsb);

		//Function: split_float_little_endian
		//	Converts the 4-byte float (in system endian) into its 4 individual bytes in little endian
		//
		//Parameters:
		//	value - the 4 byte float (in system endian) to convert into bytes
		//	lsb - holds the lsb result
		//	byte2 - holds the second byte result
		//	byte3 - holds the third byte result
		//	msb - holds the msb result
		void split_float_little_endian(float value, uint8& lsb, uint8& byte2, uint8& byte3, uint8& msb);

		//Function: make_float_big_endian
		//	Builds a 4-byte float (in system endian) from 4 bytes given in big endian
		//
		//Parameters:
		//	msb - the most significant byte
		//	byte2 - the second byte
		//	byte3 - the third byte
		//	lsb - the least significant byte
		//
		//Returns:
		//	A 4-byte float in system-endianess built from the 4 given bytes
		float make_float_big_endian(uint8 msb, uint8 byte2, uint8 byte3, uint8 lsb);

		//Function: make_float_little_endian
		//	Builds a 4-byte float (in system endian) from 4 bytes given in little endian
		//
		//Parameters:
		//	lsb - the least significant byte
		//	byte2 - the second byte
		//	byte3 - the third byte
		//	msb - the most significant byte
		//
		//Returns:
		//	A 4-byte float in system-endianess built from the 4 given bytes
		float make_float_little_endian(uint8 lsb, uint8 byte2, uint8 byte3, uint8 msb);

		//Function: split_double_big_endian
		//	Converts the 8-byte double (in system endian) into its 8 individual bytes in big endian
		//
		//Parameters:
		//	value - the 8 byte double (in system endian) to convert into bytes
		//	msb - holds the msb result
		//	byte2 - holds the second byte result
		//	byte3 - holds the third byte result
		//	byte4 - holds the fourth byte result
		//	byte5 - holds the fifth byte result
		//	byte6 - holds the sixth byte result
		//	byte7 - holds the seventh byte result
		//	lsb - holds the lsb result
		void split_double_big_endian(double value, uint8& msb, uint8& byte2, uint8& byte3, uint8& byte4, uint8& byte5, uint8& byte6, uint8& byte7, uint8& lsb);

		//Function: split_double_little_endian
		//	Converts the 8-byte double (in system endian) into its 8 individual bytes in little endian
		//
		//Parameters:
		//	value - the 8 byte double (in system endian) to convert into bytes
		//	lsb - holds the lsb result
		//	byte2 - holds the second byte result
		//	byte3 - holds the third byte result
		//	byte4 - holds the fourth byte result
		//	byte5 - holds the fifth byte result
		//	byte6 - holds the sixth byte result
		//	byte7 - holds the seventh byte result
		//	msb - holds the msb result
		void split_double_little_endian(double value, uint8& lsb, uint8& byte2, uint8& byte3, uint8& byte4, uint8& byte5, uint8& byte6, uint8& byte7, uint8& msb);

		//Function: make_double_big_endian
		//	Builds a 8-byte double (in system endian) from the bytes given in big endian
		//
		//Parameters:
		//	msb - the msb to be used
		//	byte2 - the 2nd byte to be used
		//	byte3 - the 3rd byte to be used
		//	byte4 - the 4th byte to be used
		//	byte5 - the 5th byte to be used
		//	byte6 - the 6th byte to be used
		//	byte7 - the 7th byte to be used
		//	lsb - the lsb to be used
		//
		//Returns:
		//	the 8-byte double (in system endian) built from the 8 bytes
		double make_double_big_endian(uint8 msb, uint8 byte2, uint8 byte3, uint8 byte4, uint8 byte5, uint8 byte6, uint8 byte7, uint8 lsb);

		//Function: make_double_little_endian
		//	Builds a 8-byte double (in system endian) from the bytes given in little endian
		//
		//Parameters:
		//	lsb - the lsb to be used
		//	byte2 - the 2nd byte to be used
		//	byte3 - the 3rd byte to be used
		//	byte4 - the 4th byte to be used
		//	byte5 - the 5th byte to be used
		//	byte6 - the 6th byte to be used
		//	byte7 - the 7th byte to be used
		//	msb - the msb to be used
		//
		//Returns:
		//	the 8-byte double (in system endian) built from the 8 bytes
		double make_double_little_endian(uint8 lsb, uint8 byte2, uint8 byte3, uint8 byte4, uint8 byte5, uint8 byte6, uint8 byte7, uint8 msb);

		//Function: getCurrentSystemTime
		//	Gets the current system time in nanoseconds since unix epoch
		//
		//Returns:
		//	The nanoseconds representation of the current system time in UTC
		uint64 getCurrentSystemTime();

		//Function: threadSleep
		//	Sleeps for a specified amount of milliseconds on the current thread.
		//
		//Parameters:
		//	milli - The number of milliseconds to sleep for.
		void threadSleep(uint64 milli);

		//Function: logBase2
		//	Gets the log base 2 of a value
		//
		//Parameters:
		//	value - The value to get the log of
		//
		//Returns:
		//	The log base 2 of the value
		double logBase2(double value);

		//Function: round
		//	Returns the value that is nearest to the provided value to round. (ie. round(2.5) == 3, round(2.4) == 2)
		//
		//Parameters:
		//	value - The value to round
		//
		//Returns:
		//	The rounded result.
		float round(float value);

		//Function: roundDownToNearestBase2
		//	Rounds down to the nearest base 2 value
		//
		//Parameters:
		//	value - The value to round down to the nearest base 2
		//
		//Returns:
		//	The value rounded down to the nearest base 2
		uint32 roundDownToNearestBase2(double value);

		//Function: roundUpToNearestBase2
		//	Rounds up to the nearest base 2 value
		//
		//Parameters:
		//	value - The value to round up to the nearest base 2
		//
		//Returns:
		//	The value rounded up to the nearest base 2
		uint32 roundUpToNearestBase2(double value);

		//Function: radiansToDegrees
		//	Converts the radian angle to degrees.
		//
		//Parameters:
		//	angle - The angle in radians.
		//
		//Returns:
		//	The angle in degrees.
		double radiansToDegrees(float angle);

		//Function: bitIsSet
		//	Checks if a specific bit is set in the given value.
		//
		//Parameters:
		//	value - The value to check the bit of.
		//	bitPos - The bit position to check if it is set. (0 = far right)
		//
		//Returns:
		//	true if the bit is set, false if it is not set.
		bool bitIsSet(uint32 value, size_t bitPos);

		//Function: removeChar
		//	Removes all found instances of a char from a string.
		//
		//Parameters:
		//	src - The string to remove the character from. This will be changed to hold the result.
		//	charToRemove - The character to remove all instances of from the string.
		void removeChar(std::string& src, char charToRemove);

		//Function: removeStr
		//	Removes all found instances of a string from another string.
		//
		//Parameters:
		//	str - The string to remove the substring from. This will be changed to hold the result.
		//	strtoRemove - The substring to remove all instances of from the string.
		void removeStr(std::string& src, const std::string& strToRemove);

		//Function: containsStr
		//	Checks whether or not a string contains another string.
		//
		//Parameters:
		//	src - The source string.
		//	containsThis - The string to attempt to find in the source string.
		//
		//Returns:
		//	true if the string was found in the source string, false if it was not found.
		bool containsStr(const std::string& src, const std::string& containsThis);

		//Function: strTrimLeft
		//	Trims all whitespace from the left of a string.
		//
		//Parameters:
		//	src - The string to trim whitespace from. This will be changed to hold the result.
		void strTrimLeft(std::string& src);

		//Function: strTrimRight
		//	Trims all whitespace from the right of a string.
		//
		//Parameters:
		//	src - The string to trim whitespace from. This will be changed to hold the result.
		void strTrimRight(std::string& src);

		//Function: filterSensorcloudName
		//	Replaces characters that are not supported by SensorCloud with a '-' character.
		//
		//Parameters:
		//	str - The string to filter. This will hold the result.
		void filterSensorcloudName(std::string& str);

		//Function: isNaN
		//	Checks whether the given value is NaN or not.
		//
		//Parameters:
		//	value - The value to check if it is a NaN.
		//
		//Returns:
		//	true if the value is a NaN, false otherwise.
		template<typename T>
		bool isNaN(T value)
		{
			return value != value;
		}

		//Function: checkBounds_min
		//	Checks that a value is not below a minimum value. If the value is less than the min, the value is changed to that min value.
		//
		//Parameters:
		//	value - The value to check
		//	min - The minimum value to make sure the value is greater than or equal to
		template<typename T>
		void checkBounds_min(T& value, T min)
		{
			if(value < min)
			{
				value = min;
			}
		}

		//Function: checkBounds_max
		//	Checks that a value is not above a maximum value. If the value is greater than the max, the value is changed to that max value.
		//
		//Parameters:
		//	value - The value to check
		//	max - The maximum value to make sure the value is less than or equal to.
		template<typename T>
		void checkBounds_max(T& value, T max)
		{
			if(value > max)
			{
				value = max;
			}
		}

		//Function: toStr
		//	Performs a boost::lexical_cast from a value to an std::string
		//
		//Parameters:
		//	value - The value to convert to a string.
		//
		//Returns:
		//	The string result of the lexical cast.
		template<typename T>
		std::string toStr(T value)
		{
			return std::to_string(value);
			//return boost::lexical_cast<std::string>(value);
		}

		template<typename T>
		std::string toStrWithPrecision(T value, uint8 precision = 6, bool fixed = false)
		{
			std::ostringstream s;
			s.precision(precision);

			if(fixed)
			{
				s << std::fixed;
			}

			s << value;
			return s.str();
		}
	}
#endif
}