/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

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