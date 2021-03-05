/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
/*
 * Endianness.h
 *
 * Helper functions to convert between endianness.
 *
 * !!! Note !!!
 * Benchmarking two methods for byte swapping: binary shifting vs std::swap
 *
 * Hypothesis:
 * Binary shifting is faster than std::swap
 *
 * Method:
 * Run both methods simultaneously in different threads.  Use a condition to start both threads
 * and a reference to a boolean to stop them.  Run for 60 sec, counting the number of times the
 * method was able to run. Each iteration the method would byte-swap 0x0123456789ABCDEFull.
 *
 * Test 1: Run on Gumstix Verdex Pro Marvell pxa270 600 MHz (g++ 4.3.3)
 * Trial 1: std::swap 14673040, shift 20183977
 * Trial 2: std::swap 17438625, shift 23938981
 * Trial 3: std::swap 14781441, shift 20304302
 *
 * Test 2: Run on Intel Core 2 Duo 6600 2.4 GHz x 2 (g++ 4.6.3)
 * Trial 1: std::swap 425702346, shift 214479561
 * Trial 2: std::swap 445304733, shift 198929287
 * Trial 3: std::swap 444895078, shift 201440733
 *
 * Conclusion:
 * Shift is only marginally faster on gumstix, but std::swap is consistently over twice as fast
 * on an x86 CPU.  The likely cause of the difference is that the Intel chip has much more
 * sophisticated branch prediction and dma facilities.  Std::swap should be used for byte-
 * swapping as it will likely be faster on future platforms.
 *
 *  Created on: Jan 18, 2012
 *      Author: j_herbst
 *     Edited on: Sept 26, 2013 by r_stoneback
 */

#pragma once

#include <boost/detail/endian.hpp>
#include <algorithm>

namespace mscl
{

//Function: BigEndian
//    Converts a type with a static size to or from big endian
//
//Parameters:
//    val - the value to convert
//
//Returns:
//    The converted value
template<typename StaticType>
inline StaticType BigEndian(StaticType val);


//Function: LittleEndian
//    Converts a type with a static size to or from little endian
//
//Parameters:
//    val - the value to convert
//
//Returns:
//    The converted value
template<typename StaticType>
inline StaticType LittleEndian(StaticType val);

//Function: BigEndian_To_SystemEndian
//    Converts the value from Big Endian to System Endian
//
//Parameters:
//    val - the value to convert
//
//Returns:
//    The value in System Endianess
template<typename StaticType>
inline StaticType BigEndian_To_SystemEndian(StaticType val);


//Function: SystemEndian_To_BigEndian
//    Converts the value from System Endian to Big Endian
//
//Parameters:
//    val - the value to convert
//
//Returns:
//    The value in Big Endian
template<typename StaticType>
inline StaticType SystemEndian_To_BigEndian(StaticType val);

//Function: LittleEndian_To_SystemEndian
//    Converts the value from Little Endian to System Endian
//
//Parameters:
//    val - the value to convert
//
//Returns:
//    The value in System Endianess
template<typename StaticType>
inline StaticType LittleEndian_To_SystemEndian(StaticType val);


//Function: SystemEndian_To_LittleEndian
//    Converts the value from System Endian to Little Endian
//
//Parameters:
//    val - the value to convert
//
//Returns:
//    The value in Little Endian
template<typename StaticType>
inline StaticType SystemEndian_To_LittleEndian(StaticType val);


#ifdef BOOST_LITTLE_ENDIAN
// Little endian system

template<typename StaticType>
inline StaticType BigEndian(StaticType val)
{
    for(int i = 0, j = sizeof(val) - 1; i < j; i++, j--)
    {
        std::swap(reinterpret_cast<char*>(&val)[i], reinterpret_cast<char*>(&val)[j]);
    }
    return val;
}

template<typename StaticType>
inline StaticType LittleEndian(StaticType val)
{
    return val;
}

template<typename StaticType>
inline StaticType BigEndian_To_SystemEndian(StaticType val)
{
    //little endian system, so swap from big endian to little endian
    return BigEndian(val);
}

template<typename StaticType>
inline StaticType SystemEndian_To_BigEndian(StaticType val)
{
    //little endian system, swap to big endian
    return BigEndian(val);
}

template<typename StaticType>
inline StaticType LittleEndian_To_SystemEndian(StaticType val)
{
    //little endian system, so keep bytes the same
    return LittleEndian(val);
}

template<typename StaticType>
inline StaticType SystemEndian_To_LittleEndian(StaticType val)
{
    //little endian system, so keep bytes the same
    return LittleEndian(val);
}

#else
// Big endian system

template<typename StaticType>
inline StaticType BigEndian(StaticType val)
{
    return val;
}

template<typename StaticType>
inline StaticType LittleEndian(StaticType val)
{
    for(int i = 0, j = sizeof(val) - 1; i < j; i++, j--)
    {
        std::swap(reinterpret_cast<char*>(&val)[i], reinterpret_cast<char*>(&val)[j]);
    }
    return val;
}

template<typename StaticType>
inline StaticType BigEndian_To_SystemEndian(StaticType val)
{
    //big endian system, so keep bytes the same
    return BigEndian(val);
}

template<typename StaticType>
inline StaticType SystemEndian_To_BigEndian(StaticType val)
{
    //big endian system, so keep bytes the same
    return BigEndian(val);
}

template<typename StaticType>
inline StaticType LittleEndian_To_SystemEndian(StaticType val)
{
    //big endian system, swap bytes to little endian
    return LittleEndian(val);
}

template<typename StaticType>
inline StaticType SystemEndian_To_LittleEndian(StaticType val)
{
    //big endian system, swap bytes to little endian
    return LittleEndian(val);
}

#endif

}