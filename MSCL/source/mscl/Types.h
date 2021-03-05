/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "simple_any.h"

#include <cstdint>
#include <mutex>
#include <vector>
#include <sstream>

namespace mscl
{
    //API Title: Types
    //    Contains various typedefs that are used throughout MSCL.

    //API Typedef: int8
    //    typedef for a 1-byte signed integer.
    typedef std::int8_t int8;

    //API Typedef: int16
    //    typedef for a 2-byte signed integer.
    typedef std::int16_t int16;

    //API Typedef: int32
    //    typedef for a 4-byte signed integer.
    typedef std::int32_t int32;

    //API Typedef: int64
    //    typedef for an 8-byte signed integer.
    typedef std::int64_t int64;

    //API Typedef: uint8 
    //    typedef for a 1-byte unsigned integer.
    typedef std::uint8_t uint8;

    //API Typedef: uint16 
    //    typedef for a 2-byte unsigned integer.
    typedef std::uint16_t uint16;

    //API Typedef: uint32 
    //    typedef for a 4-byte unsigned integer.
    typedef std::uint32_t uint32;

    //API Typedef: uint64
    //    typedef for an 8-byte unsigned integer.
    typedef std::uint64_t uint64;

    //API Typedef: NodeAddress
    //    typedef for a Node's node address.
    typedef std::uint32_t NodeAddress;

#ifndef SWIG
    
    //verify some standard information at compile time
    static_assert(sizeof(int) >= 4, "int is less than 4 bytes");
    static_assert(sizeof(std::int8_t) == sizeof(signed char), "int8_t != signed char");
    static_assert(sizeof(std::uint8_t) == sizeof(unsigned char), "uint8_t != unsigned char");
    static_assert(sizeof(std::int16_t) == sizeof(signed short), "int16_t != signed short");
    static_assert(sizeof(std::uint16_t) == sizeof(unsigned short), "uint16_t != unsigned short");
    static_assert(sizeof(std::int32_t) == sizeof(signed int), "int32_t != signed int");
    static_assert(sizeof(std::uint32_t) == sizeof(unsigned int), "uint32_t != unsigned int");
    static_assert(sizeof(std::int64_t) == sizeof(long long), "int64_t != long long");
    static_assert(sizeof(std::uint64_t) == sizeof(unsigned long long), "uint64_t != unsigned long long");

    //Typedef: mutex_lock_guard
    //    Typedef for a lock_gaurd (automatically locks and unlocks) to a mutex.
    typedef std::lock_guard<std::mutex> mutex_lock_guard;

    //Typedef: rec_mutex_lock_guard
    //    Typedef for a lock_gaurd (automatically locks and unlocks) to a recursive mutex.
    typedef std::lock_guard<std::recursive_mutex> rec_mutex_lock_guard;

    //Typedef: UniqueWirelessPacketId
    //    Typedef for an id that uniquely identifies a wireless packet.
    typedef uint16 UniqueWirelessPacketId;

    //Typedef: anyType
    //    Typedef for a simple_any type
    typedef simple_any anyType;


    //Function: checked_cast
    //    Safely casts one type to another type using static_cast
    //    by checking the limit of the cast first
    //
    //Parameters:
    //    value - the value to be casted
    //    valueName - a description of the value that you are attempting to cast
    //
    //Returns:
    //    The value statically cast to the type requested
    //
    //Exceptions:
    //    - std::out_of_range: The cast is invalid, as the resulting data type is out of range.
    template <class Tout, class Tin>
    Tout checked_cast(Tin value, const std::string& valueName, Tout min = std::numeric_limits<Tout>::min(), Tout max = std::numeric_limits<Tout>::max())
    {
        if( value < min || value > max)
        {
            std::stringstream error;
            error << valueName << " must be in the range [" << min << "," << max << "]";

            throw std::out_of_range(error.str().c_str());
        }

        return static_cast<Tout>(value);
    }

#endif

    //API Typedef: Bytes
    //    typedef for a vector of bytes.
    typedef std::vector<uint8> Bytes;

    //API Typedef: BytesCollection
    //    A vector of <Bytes> objects.
    typedef std::vector<Bytes> BytesCollection;
    
    //================================================================================================================
    //API Enums: ValueType
    //  valueType_float                     - 0     - The value is stored as a 4-byte float .
    //  valueType_double                    - 1     - The value is stored as an 8-byte double.
    //  valueType_uint8                     - 2     - The value is stored as a 1-byte unsigned integer.
    //  valueType_uint16                    - 3     - The value is stored as a 2-byte unsigned integer.
    //  valueType_uint32                    - 4     - The value is stored as a 4-byte unsigned integer.
    //  valueType_int8                      - 16    - The value is stored as a 1-byte signed integer.
    //  valueType_int16                     - 5     - The value is stored as a 2-byte signed integer.
    //  valueType_int32                     - 6     - The value is stored as a 4-byte signed integer.
    //  valueType_bool                      - 7     - The value is stored as a 1-byte boolean.
    //  valueType_Vector                    - 8     - The value is stored as a <Vector> object.
    //  valueType_Matrix                    - 9     - The value is stored as a <Matrix> object.
    //  valueType_Timestamp                 - 10    - The value is stored as a <Timestamp> object.
    //  valueType_string                    - 11    - The value is stored as a string.
    //  valueType_Bytes                     - 12    - The value is stored as a <Bytes> object.
    //  valueType_StructuralHealth          - 13    - The value is stored as a <StructuralHealth> object.
    //  valueType_RfSweep                   - 14    - The value is stored as an <RfSweep> object.
    //  valueType_ChannelMask               - 15    - The value is stored as a <ChannelMask> object.
    //================================================================================================================
    enum ValueType
    {
        valueType_float                     = 0,
        valueType_double                    = 1,
        valueType_uint8                     = 2,
        valueType_uint16                    = 3,
        valueType_uint32                    = 4,
        valueType_int8                      = 16,
        valueType_int16                     = 5,
        valueType_int32                     = 6,
        valueType_bool                      = 7,
        valueType_Vector                    = 8,
        valueType_Matrix                    = 9,
        valueType_Timestamp                 = 10,
        valueType_string                    = 11,
        valueType_Bytes                     = 12,
        valueType_StructuralHealth          = 13,
        valueType_RfSweep                   = 14,
        valueType_ChannelMask               = 15
    };

    //API Enum: DeviceState
    //  The possible states a device can be in.
    //
    //  deviceState_idle                - 0 - Idle state
    //  deviceState_sleep               - 1 - Sleep state
    //  deviceState_sampling            - 2 - Sampling state
    //  deviceState_sampling_lostBeacon - 3 - Sampling state, but lost the beacon
    //  deviceState_inactive            - 4 - Sampling state, but with no activity (in activity detect mode)
    //  deviceState_unknown             - 255 - Unknown
    enum DeviceState
    {
        deviceState_idle                = 0,
        deviceState_sleep               = 1,
        deviceState_sampling            = 2,
        deviceState_sampling_lostBeacon = 3,
        deviceState_sampling_inactive   = 4,
        deviceState_unknown             = 255
    };
}
