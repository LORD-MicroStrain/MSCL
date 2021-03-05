/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include <bitset>
#include <functional>
#include <iomanip>
#include <string>
#include "Types.h"

namespace mscl
{
#ifndef SWIG

    //Namespace: Utils
    //    Contains many commonly used utility functions.
    //    Note: Communication with our devices (wireless and inertial) is done in Big Endian.
    namespace Utils
    {
        //Enum: Endianness
        //  The possible endians that a value can be in.
        enum Endianness
        {
            bigEndian = 0,
            littleEndian = 1
        };

        //Function: valueTypeSize
        //    Gets the size of the <ValueType>
        //
        //Parameters:
        //    type - The <ValueType> to get the size of
        //
        //Returns:
        //    The size of the given <ValueType>
        //
        //Exceptions:
        //    - <Error>: The value type requested does not have a given size
        uint32 valueTypeSize(ValueType type);

        //Function: msb
        //    Gets the Most Significant Byte from the 2-Byte unsigned integer
        //    
        //Parameters:
        //    value - the 2-Byte unsigned integer (in system endianness) to find the MSB from
        //
        //Returns:
        //    The Most Significant Byte of the passed in value
        uint8 msb(uint16 value);

        //Function: lsb
        //    Gets the Least Significant Byte from the 2-Byte unsigned integer
        //    
        //Parameters:
        //    value - the 2-Byte unsigned integer (in system endianness) to find the LSB from
        //
        //Returns:
        //    The Least Significant Byte of the passed in value
        uint8 lsb(uint16 value);

        //Function: msNibble
        //    Gets the Most Significant Nibble (4-bits) from the 1-Byte value
        //
        //Parameters:
        //    value - the 1-Byte value to find the Most Significant Nibble from
        //
        //Returns:
        //    The Most Significant Nibble of the passed in value
        uint8 msNibble(uint8 value);

        //Function: lsNibble
        //    Gets the Least Significant Nibble (4-bits) from the 1-Byte value
        //
        //Parameters:
        //    value - the 1-Byte value to find the Least Significant Nibble from
        //
        //Returns:
        //    The Least Significant Nibble of the passed in value
        uint8 lsNibble(uint8 value);

        //Function: split_int16
        //    Converts the 2-byte signed integer into its individual 2 bytes.
        //
        //Parameters:
        //    value - the 2 byte int16 (in system endianness) to convert into bytes
        //    low - holds the low memory location result
        //    high - holds the high memory location result
        //    endian - The <Endianness> that the result bytes should be in.
        //             ie. Big endian means low will be the msb, high will be the lsb. Little endian means low will be the lsb, high will be the msb.
        void split_int16(int16 value, uint8& low, uint8& high, Endianness endian = bigEndian);

        //Function: make_int16
        //    Gets the 2-byte signed integer (in system endianness) from 2 individual bytes
        //
        //Parameters:
        //    low - the low memory location byte
        //    high - the high memory location byte
        //    endian - The <Endianness> that the passed in bytes are in.
        //             ie. Big endian means low = msb, high = lsb. Little endian means low = lsb, high = msb
        //
        //Returns:
        //    The 2-byte int16 (in system endianness) built from the given bytes.
        int16 make_int16(uint8 low, uint8 high, Endianness endian = bigEndian);

        //Function: make_int32
        //    Gets the 4-byte signed integer (in system endianness) from 4 individual bytes
        //
        //Parameters:
        //    low - the low memory location byte
        //    byte2 - the second byte to be used
        //    byte3 - the third byte to be used
        //    high - the high memory location byte
        //    endian - The <Endianness> that the passed in bytes are in.
        //             ie. Big endian means low = msb, high = lsb. Little endian means low = lsb, high = msb
        //
        //Returns:
        //    The 4-byte int32 (in system endianness) built from the given bytes.
        int32 make_int32(uint8 low, uint8 byte2, uint8 byte3, uint8 high, Endianness endian = bigEndian);

        //Function: split_uint16
        //    Converts the 2-byte unsigned integer into its individual 2 bytes.
        //
        //Parameters:
        //    value - the 2 byte uint16 (in system endianness) to convert into bytes
        //    low - holds the low memory location result
        //    high - holds the high memory location result
        //    endian - The <Endianness> that the result bytes should be in.
        //             ie. Big endian means low will be the msb, high will be the lsb. Little endian means low will be the lsb, high will be the msb.
        void split_uint16(uint16 value, uint8& low, uint8& high, Endianness endian = bigEndian);

        //Function: make_uint16
        //    Gets the 2-byte unsigned integer (in system endianness) from 2 individual bytes.
        //Parameters:
        //    low - the low memory location byte
        //    high - the high memory location byte
        //    endian - The <Endianness> that the passed in bytes are in.
        //             ie. Big endian means low = msb, high = lsb. Little endian means low = lsb, high = msb
        //
        //Returns:
        //    The 2-byte uint16 (in system endianness) built from the given bytes.
        uint16 make_uint16(uint8 low, uint8 high, Endianness endian = bigEndian);

        //Function: split_uint32
        //    Converts the 4-byte unsigned integer into its 4 individual bytes.
        //
        //Parameters:
        //    value - the 4 byte uint32 (in system endianness) to convert into bytes
        //    low - holds the low memory location result 
        //    byte2 - holds the second byte result
        //    byte3 - holds the third byte result
        //    high - holds the high memory location result
        //    endian - The <Endianness> that the result bytes should be in.
        //             ie. Big endian means low will be the msb, high will be the lsb. Little endian means low will be the lsb, high will be the msb.
        void split_uint32(uint32 value, uint8& low, uint8& byte2, uint8& byte3, uint8& high, Endianness endian = bigEndian);

        //Function: split_uint64
        //    Converts the 4-byte unsigned integer into its 4 individual bytes.
        //
        //Parameters:
        //    value - the 4 byte uint32 (in system endianness) to convert into bytes
        //    low - holds the low memory location result 
        //    byte2 - holds the second byte result
        //    byte3 - holds the third byte result
        //    byte4 - holds the fourth byte result
        //    byte5 - holds the fifth byte result
        //    byte6 - holds the sixth byte result
        //    byte7 - holds the seventh byte result
        //    high - holds the high memory location result
        //    endian - The <Endianness> that the result bytes should be in.
        //             ie. Big endian means low will be the msb, high will be the lsb. Little endian means low will be the lsb, high will be the msb.
        void split_uint64(uint64 value, uint8& low, uint8& byte2, uint8& byte3, uint8& byte4, uint8& byte5, uint8& byte6, uint8& byte7, uint8& high, Endianness endian = bigEndian);

        //Function: make_uint32
        //    gets the 4-byte unsigned integer from the 4 individual bytes
        //
        //Parameters:
        //    low - the lowest memory location byte to be used
        //    byte2 - the second byte to be used
        //    byte3 - the third byte to be used
        //    high - the highest memory location byte to be used
        //    endian - The <Endianness> that the passed in bytes are in.
        //             ie. Big endian means low = msb, high = lsb. Little endian means low = lsb, high = msb
        //
        //Returns:
        //    the 4-byte uint32 built from the 4 bytes
        uint32 make_uint32(uint8 low, uint8 byte2, uint8 byte3, uint8 high, Endianness endian = bigEndian);

        //Function: make_uint64
        //    gets the 8-byte unsigned integer from the 8 individual bytes
        //
        //Parameters:
        //    low - the lowest memory location byte to be used
        //    byte2 - the second byte to be used
        //    byte3 - the third byte to be used
        //    byte4 - the fourth byte to be used
        //    byte5 - the fifth byte to be used
        //    byte6 - the sixth byte to be used
        //    byte7 - the seventh byte to be used
        //    high - the highest memory location byte to be used
        //    endian - The <Endianness> that the passed in bytes are in.
        //             ie. Big endian means low = msb, high = lsb. Little endian means low = lsb, high = msb
        //
        //Returns:
        //    the 4-byte uint32 built from the 4 bytes
        uint64 make_uint64(uint8 low, uint8 byte2, uint8 byte3, uint8 byte4, uint8 byte5, uint8 byte6, uint8 byte7, uint8 high, Endianness endian = bigEndian);

        //Function: split_float
        //    Converts the 4-byte float (in system endian) into its 4 individual bytes.
        //
        //Parameters:
        //    value - the 4 byte float (in system endian) to convert into bytes
        //    low - holds the lowest memory byte result
        //    byte2 - holds the second byte result
        //    byte3 - holds the third byte result
        //    high - holds the highest memory byte result
        //    endian - The <Endianness> that the result bytes should be in.
        //             ie. Big endian means low will be the msb, high will be the lsb. Little endian means low will be the lsb, high will be the msb.
        void split_float(float value, uint8& low, uint8& byte2, uint8& byte3, uint8& high, Endianness endian = bigEndian);

        //Function: make_float
        //    Builds a 4-byte float (in system endian) from 4 bytes given
        //
        //Parameters:
        //    low - the lowest memory location byte to be used
        //    byte2 - the second byte to be used
        //    byte3 - the third byte to be used
        //    high - the highest memory location byte to be used
        //    endian - The <Endianness> that the passed in bytes are in.
        //             ie. Big endian means low = msb, high = lsb. Little endian means low = lsb, high = msb
        //
        //Returns:
        //    A 4-byte float in system-endianess built from the 4 given bytes
        float make_float(uint8 low, uint8 byte2, uint8 byte3, uint8 high, Endianness endian = bigEndian);

        //Function: split_double
        //    Converts the 8-byte double (in system endian) into its 8 individual bytes.
        //
        //Parameters:
        //    value - the 8 byte double (in system endian) to convert into bytes
        //    low - holds the lowest memory byte result
        //    byte2 - holds the second byte result
        //    byte3 - holds the third byte result
        //    byte4 - holds the fourth byte result
        //    byte5 - holds the fifth byte result
        //    byte6 - holds the sixth byte result
        //    byte7 - holds the seventh byte result
        //    high - holds the highest memory byte result
        //    endian - The <Endianness> that the result bytes should be in.
        //             ie. Big endian means low will be the msb, high will be the lsb. Little endian means low will be the lsb, high will be the msb.
        void split_double(double value, uint8& low, uint8& byte2, uint8& byte3, uint8& byte4, uint8& byte5, uint8& byte6, uint8& byte7, uint8& high, Endianness endian = bigEndian);

        //Function: make_double
        //    Builds a 8-byte double (in system endian) from the bytes given.
        //
        //Parameters:
        //    low - the lowest memory byte to be used
        //    byte2 - the 2nd byte to be used
        //    byte3 - the 3rd byte to be used
        //    byte4 - the 4th byte to be used
        //    byte5 - the 5th byte to be used
        //    byte6 - the 6th byte to be used
        //    byte7 - the 7th byte to be used
        //    high - the highest memory byte to be used
        //    endian - The <Endianness> that the passed in bytes are in.
        //             ie. Big endian means low = msb, high = lsb. Little endian means low = lsb, high = msb
        //
        //Returns:
        //    the 8-byte double (in system endian) built from the 8 bytes
        double make_double(uint8 low, uint8 byte2, uint8 byte3, uint8 byte4, uint8 byte5, uint8 byte6, uint8 byte7, uint8 high, Endianness endian = bigEndian);

        //Function: getCurrentSystemTime
        //    Gets the current system time in nanoseconds since unix epoch
        //
        //Returns:
        //    The nanoseconds representation of the current system time in UTC
        uint64 getCurrentSystemTime();

        //Function: threadSleep
        //    Sleeps for a specified amount of milliseconds on the current thread.
        //
        //Parameters:
        //    milli - The number of milliseconds to sleep for.
        void threadSleep(uint64 milli);

        //Function: round
        //    Returns the value that is nearest to the provided value to round. (ie. round(2.5) == 3, round(2.4) == 2)
        //
        //Parameters:
        //    value - The value to round
        //
        //Returns:
        //    The rounded result.
        float round(float value);

        //Function: floorBase2
        //    Rounds down to the nearest base 2 value
        //
        //Parameters:
        //    value - The value to round down to the nearest base 2
        //
        //Returns:
        //    The value rounded down to the nearest base 2
        uint32 floorBase2(double value);

        //Function: ceilBase2
        //    Rounds up to the nearest base 2 value
        //
        //Parameters:
        //    value - The value to round up to the nearest base 2
        //
        //Returns:
        //    The value rounded up to the nearest base 2
        uint32 ceilBase2(double value);

        //Function: radiansToDegrees
        //    Converts the radian angle to degrees.
        //
        //Parameters:
        //    angle - The angle in radians.
        //
        //Returns:
        //    The angle in degrees.
        double radiansToDegrees(float angle);

        //Function: removeChar
        //    Removes all found instances of a char from a string.
        //
        //Parameters:
        //    src - The string to remove the character from. This will be changed to hold the result.
        //    charToRemove - The character to remove all instances of from the string.
        void removeChar(std::string& src, char charToRemove);

        //Function: removeStr
        //    Removes all found instances of a string from another string.
        //
        //Parameters:
        //    str - The string to remove the substring from. This will be changed to hold the result.
        //    strtoRemove - The substring to remove all instances of from the string.
        void removeStr(std::string& src, const std::string& strToRemove);

        //Function: containsStr
        //    Checks whether or not a string contains another string.
        //
        //Parameters:
        //    src - The source string.
        //    containsThis - The string to attempt to find in the source string.
        //
        //Returns:
        //    true if the string was found in the source string, false if it was not found.
        bool containsStr(const std::string& src, const std::string& containsThis);

        //Function: strTrimLeft
        //    Trims all whitespace from the left of a string.
        //
        //Parameters:
        //    src - The string to trim whitespace from. This will be changed to hold the result.
        void strTrimLeft(std::string& src);

        //Function: strTrimRight
        //    Trims all whitespace from the right of a string.
        //
        //Parameters:
        //    src - The string to trim whitespace from. This will be changed to hold the result.
        void strTrimRight(std::string& src);

        //Function: filterSensorcloudName
        //    Replaces characters that are not supported by SensorCloud with a '-' character.
        //
        //Parameters:
        //    str - The string to filter. This will hold the result.
        void filterSensorcloudName(std::string& str);

        //Function: normalizeAngle
        //    Normalizes an angle value to be between 0 and 360 degrees.
        //
        //Parameters:
        //    angle - The angle to normalize.
        //
        //Returns:
        //    The normalized angle within 0 and 360 degrees.
        float normalizeAngle(float angle);

        //Function: bitIsSet
        //    Checks if a specific bit is set in the given value.
        //
        //Parameters:
        //    value - The value to check the bit of.
        //    bitPos - The bit position to check if it is set. (0 = far right)
        //
        //Returns:
        //    true if the bit is set, false if it is not set.
        template<typename T>
        bool bitIsSet(T value, size_t bitPos)
        {
            std::bitset<64> bitset(value);

            return bitset.test(bitPos);
        }

        //Function: setBit
        //  Sets a specific bit to on or off.
        //
        //Parameters:
        //  value - The value to update (will be updated with the result).
        //  bitPos - The bit position to set. (0 = far right)
        //  enable - true to set the bit to on, false to set the bit to off.
        template<typename T>
        void setBit(T& value, size_t bitPos, bool enable)
        {
            std::bitset<64> bitset(value);

            bitset.set(bitPos, enable);

            value = static_cast<T>(bitset.to_ullong());
        }

        //Function: isNaN
        //    Checks whether the given value is NaN or not.
        //
        //Parameters:
        //    value - The value to check if it is a NaN.
        //
        //Returns:
        //    true if the value is a NaN, false otherwise.
        template<typename T>
        bool isNaN(T value)
        {
            return value != value;
        }

        //Function: checkBounds_min
        //    Checks that a value is not below a minimum value. If the value is less than the min, the value is changed to that min value.
        //
        //Parameters:
        //    value - The value to check
        //    min - The minimum value to make sure the value is greater than or equal to
        template<typename T>
        void checkBounds_min(T& value, T min)
        {
            if(value < min)
            {
                value = min;
            }
        }

        //Function: checkBounds_max
        //    Checks that a value is not above a maximum value. If the value is greater than the max, the value is changed to that max value.
        //
        //Parameters:
        //    value - The value to check
        //    max - The maximum value to make sure the value is less than or equal to.
        template<typename T>
        void checkBounds_max(T& value, T max)
        {
            if(value > max)
            {
                value = max;
            }
        }

        //Function: eraseIf
        //  Takes a container (such as a vector) and removes elements from it if they don't match a certain predicate.
        //
        //Parameters:
        //  c - The container to check and remove elements from, as a reference.
        //  t - The predicate that will return false for elements that should be removed from the container.
        template<typename Container, class T>
        void eraseIf(Container& c, T&& t)
        {
            c.erase(
                std::remove_if(c.begin(), c.end(), std::forward<T>(t)),
                c.end());
        }

        //Function: toStr
        //    Performs a boost::lexical_cast from a value to an std::string
        //
        //Parameters:
        //    value - The value to convert to a string.
        //
        //Returns:
        //    The string result of the lexical cast.
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

        template<typename T>
        class Lazy
        {
        public:
          template<typename LoadFn>
          Lazy(LoadFn loadFn) :
            m_loadFn(loadFn),
            m_loaded(false)
          {}

          Lazy(T value):
            m_loadFn(nullptr),
            m_value(value),
            m_loaded(true)
          {
          }

          const T& operator*() const
          {
            if(!m_loaded)
            {
                m_value = m_loadFn();
            }
            m_loaded = true;
            return m_value;
          }

        private:
          std::function<T()> m_loadFn;
          mutable T m_value;
          mutable bool m_loaded;
        };
    }
#endif
}
