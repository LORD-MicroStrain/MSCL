/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "Types.h"

namespace mscl
{
    //API Class: Value
    //    Represents a single value that can be stored/accessed in multiple ways.
    //
    //See Also:
    //    <DataPoint>
    class Value
    {
    private:
        Value();    //default constructor disabled
        
    public:
        virtual ~Value(){}

#ifndef SWIG
        //Constructor: Value
        //    Creates a Value object
        //
        //Parameters:
        //    type - The <ValueType> of the data that is stored
        //    value - The data that is to be stored
        Value(ValueType type, const anyType& value);

        Value(const Value& other);
        Value& operator=(const Value& other);
        bool operator==(const Value& other) const;

        static Value UINT16(uint16 value);
        static Value UINT32(uint32 value);
        static Value FLOAT(float value);
#endif

    protected:
        //Variable: m_value
        //    Holds the actual value as an anyType
        anyType m_value;

        //Variable: m_storedAs
        //    The type that the value is stored as.
        //    This type should be inspected to determine how to read the m_value member
        ValueType m_storedAs;

    private:
        bool isSameValue(const Value& other) const;

    public:
        //API Function: storedAs
        //    Gets the <ValueType> that the data value is stored as. This type should be inspected to determine how to read the data value.
        //
        //Returns:
        //    A <ValueType> representing how the data is stored, and should be read.
        const ValueType storedAs() const;

        //API Function: as_float
        //    Gets the data value as a 4-byte float
        //
        //Returns:
        //    The data value as a 4-byte float
        //
        //Exceptions:
        //    - <Error_BadDataType>: The type in which the value was stored could not be converted to a 4-byte float
        virtual float as_float() const;

        //API Function: as_double
        //    Gets the data value as an 8-byte double
        //
        //Returns:
        //    The data value as an 8-byte double
        //
        //Exceptions:
        //    - <Error_BadDataType>: The type in which the value was stored could not be converted to an 8-byte double
        virtual double as_double() const;

        //API Function: as_uint8
        //    Gets the data value as a 1-byte unsigned integer
        //
        //Returns:
        //    The data value as a 1-byte unsigned integer
        //
        //Exceptions:
        //    - <Error_BadDataType>: The type in which the value was stored could not be converted to a 1-byte unsigned integer
        virtual uint8 as_uint8() const;

        //API Function: as_uint16
        //    Gets the data value as a 2-byte unsigned integer
        //
        //Returns:
        //    The data value as a 2-byte unsigned integer
        //
        //Exceptions:
        //    - <Error_BadDataType>: The type in which the value was stored could not be converted to a 2-byte unsigned integer
        virtual uint16 as_uint16() const;

        //API Function: as_uint32
        //    Gets the data value as a 4-byte unsigned integer
        //
        //Returns:
        //    The data value as a 4-byte unsigned integer
        //
        //Exceptions:
        //    - <Error_BadDataType>: The type in which the value was stored could not be converted to a 4-byte unsigned integer
        virtual uint32 as_uint32() const;

        //API Function: as_int16
        //    Gets the data value as a 2-byte signed integer
        //
        //Returns:
        //    The data value as a 2-byte signed integer
        //
        //Exceptions:
        //    - <Error_BadDataType>: The type in which the value was stored could not be converted to a 2-byte signed integer
        virtual short as_int16() const;

        //API Function: as_int32
        //    Gets the data value as a 4-byte signed integer
        //
        //Returns:
        //    The data value as a 4-byte signed integer
        //
        //Exceptions:
        //    - <Error_BadDataType>: The type in which the value was stored could not be converted to a 4-byte signed integer
        virtual int as_int32() const;

        //API Function: as_int32
        //    Gets the data value as a 1-byte boolean
        //
        //Returns:
        //    The data value as a boolean
        //
        //Exceptions:
        //    - <Error_BadDataType>: The type in which the value was stored could not be converted to a bool
        virtual bool as_bool() const;

        //API Function: as_string
        //    Gets the data value as a string
        //
        //Returns:
        //    A string representing the data value. This will be created using the value's current valueType.
        //    So a value stored as a float will return a string as so: "1.2345".
        //
        //Exceptions:
        //    - <Error_BadDataType>: The type to string conversion is not supported by this function
        virtual std::string as_string() const;
    };

}