/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "Value.h"

#include <boost/numeric/conversion/cast.hpp>

#include "Utils.h"
#include "Exceptions.h"

namespace mscl
{
    Value::Value(ValueType type, const anyType& value):
        m_value(value),
        m_storedAs(type)
    {
    }

    Value::Value(const Value& other):
        m_value(other.m_value),
        m_storedAs(other.m_storedAs)
    {
    }

    Value& Value::operator=(const Value& other)
    {
        m_value = other.m_value;
        m_storedAs = other.m_storedAs;
        return *this;
    }

    bool Value::operator==(const Value& other) const
    {
        return ((m_storedAs == other.m_storedAs) && (isSameValue(other) ));
    }

    Value Value::UINT16(uint16 value)
    {
        return Value(valueType_uint16, value);
    }

    Value Value::UINT32(uint32 value)
    {
        return Value(valueType_uint32, value);
    }

    Value Value::FLOAT(float value)
    {
        return Value(valueType_float, value);
    }

    bool Value::isSameValue(const Value& other) const
    {
        switch(m_storedAs)
        {
            case valueType_float:       return as_float() == other.as_float();
            case valueType_double:      return as_double() == other.as_double();
            case valueType_uint16:      return as_uint16() == other.as_uint16();
            case valueType_uint32:      return as_uint32() == other.as_uint32();
            case valueType_int16:       return as_int16() == other.as_int16();
            case valueType_int32:       return as_int32() == other.as_int32();
            case valueType_uint8:       return as_uint8() == other.as_uint8();
            case valueType_bool:        return as_bool() == other.as_bool();
            case valueType_string:      return as_string() == other.as_string();

            default:
                return false;
        }
    }

    const ValueType Value::storedAs() const
    {
        return m_storedAs;
    }

    //    Gets the data point value as a float
    float Value::as_float() const
    {
        try
        {
            switch(m_storedAs)
            {
                case valueType_float:       return (any_cast<float>(m_value));
                case valueType_double:      return static_cast<float>(any_cast<double>(m_value));
                case valueType_uint16:      return static_cast<float>(any_cast<uint16>(m_value));
                case valueType_uint32:      return static_cast<float>(any_cast<uint32>(m_value));
                case valueType_int16:       return static_cast<float>(any_cast<short>(m_value));
                case valueType_int32:       return static_cast<float>(any_cast<int>(m_value));
                case valueType_uint8:       return static_cast<float>(any_cast<uint8>(m_value));
                case valueType_bool:        return static_cast<float>(any_cast<bool>(m_value));
                case valueType_string:      return std::stof(any_cast<std::string>(m_value));

                default:
                    throw Error_BadDataType();
            }
        }
        catch(...)
        {
            throw Error_BadDataType();
        }
    }

    //    Gets the data point value as a double
    double Value::as_double() const
    {
        try
        {
            switch(m_storedAs)
            {
                case valueType_double:      return (any_cast<double>(m_value));
                case valueType_float:       return static_cast<double>(any_cast<float>(m_value));
                case valueType_uint16:      return static_cast<double>(any_cast<uint16>(m_value));
                case valueType_uint32:      return static_cast<double>(any_cast<uint32>(m_value));
                case valueType_int16:       return static_cast<double>(any_cast<short>(m_value));
                case valueType_int32:       return static_cast<double>(any_cast<int>(m_value));
                case valueType_uint8:       return static_cast<double>(any_cast<uint8>(m_value));
                case valueType_bool:        return static_cast<double>(any_cast<bool>(m_value));
                case valueType_string:      return std::stod(any_cast<std::string>(m_value));

                default:
                    throw Error_BadDataType();
            }
        }
        catch(...)
        {
            throw Error_BadDataType();
        }
    }

    //    Gets the data point value as an uint8
    uint8 Value::as_uint8() const
    {
        try
        {
            switch(m_storedAs)
            {
                case valueType_uint8:       return any_cast<uint8>(m_value);
                case valueType_uint32:      return static_cast<uint8>(any_cast<uint32>(m_value));
                case valueType_int16:       return static_cast<uint8>(any_cast<short>(m_value));
                case valueType_int32:       return static_cast<uint8>(any_cast<int>(m_value));
                case valueType_float:       return static_cast<uint8>(any_cast<float>(m_value));
                case valueType_double:      return static_cast<uint8>(any_cast<double>(m_value));
                case valueType_uint16:      return static_cast<uint8>(any_cast<uint16>(m_value));
                case valueType_bool:        return static_cast<uint8>(any_cast<bool>(m_value));
                case valueType_string:      return static_cast<uint8>(std::stoi(any_cast<std::string>(m_value)));

                default:
                    throw Error_BadDataType();
            }
        }
        catch(...)
        {
            throw Error_BadDataType();
        }
    }

    //    Gets the data point value as an uint16
    uint16 Value::as_uint16() const
    {
        try
        {
            switch(m_storedAs)
            {
                case valueType_uint16:      return any_cast<uint16>(m_value);
                case valueType_uint32:      return static_cast<uint16>(any_cast<uint32>(m_value));
                case valueType_int16:       return static_cast<uint16>(any_cast<short>(m_value));
                case valueType_int32:       return static_cast<uint16>(any_cast<int>(m_value));
                case valueType_float:       return static_cast<uint16>(any_cast<float>(m_value));
                case valueType_double:      return static_cast<uint16>(any_cast<double>(m_value));
                case valueType_uint8:       return static_cast<uint16>(any_cast<uint8>(m_value));
                case valueType_bool:        return static_cast<uint16>(any_cast<bool>(m_value));
                case valueType_string:      return static_cast<uint16>(std::stoi(any_cast<std::string>(m_value)));

                default:
                    throw Error_BadDataType();
            }
        }
        catch(...)
        {
            throw Error_BadDataType();
        }
    }

    //    Gets the data point value as an uint32
    uint32 Value::as_uint32() const
    {
        try
        {
            switch(m_storedAs)
            {
                case valueType_uint32:      return any_cast<uint32>(m_value);
                case valueType_uint16:      return static_cast<uint32>(any_cast<uint16>(m_value));
                case valueType_int16:       return static_cast<uint32>(any_cast<short>(m_value));
                case valueType_int32:       return static_cast<uint32>(any_cast<int>(m_value));
                case valueType_float:       return static_cast<uint32>(any_cast<float>(m_value));
                case valueType_double:      return static_cast<uint32>(any_cast<double>(m_value));
                case valueType_uint8:       return static_cast<uint32>(any_cast<uint8>(m_value));
                case valueType_bool:        return static_cast<uint32>(any_cast<bool>(m_value));
                case valueType_string:      return static_cast<uint32>(std::stoul(any_cast<std::string>(m_value)));

                default:
                    throw Error_BadDataType();
            }
        }
        catch(...)
        {
            throw Error_BadDataType();
        }
    }

    //    Gets the data point value as a signed int
    short Value::as_int16() const
    {
        try
        {
            switch(m_storedAs)
            {
                case valueType_int16:       return(any_cast<short>(m_value));
                case valueType_int32:       return static_cast<short>(any_cast<int>(m_value));
                case valueType_uint32:      return static_cast<short>(any_cast<uint32>(m_value));
                case valueType_uint16:      return static_cast<short>(any_cast<uint16>(m_value));
                case valueType_float:       return static_cast<short>(any_cast<float>(m_value));
                case valueType_double:      return static_cast<short>(any_cast<double>(m_value));
                case valueType_uint8:       return static_cast<short>(any_cast<uint8>(m_value));
                case valueType_bool:        return static_cast<short>(any_cast<bool>(m_value));
                case valueType_string:      return static_cast<short>(std::stoi(any_cast<std::string>(m_value)));

                default:
                    throw Error_BadDataType();
            }
        }
        catch(...)
        {
            throw Error_BadDataType();
        }
    }

    //    Gets the data point value as a signed int
    int Value::as_int32() const
    {
        try
        {
            switch(m_storedAs)
            {
                case valueType_int32:       return any_cast<int>(m_value);
                case valueType_int16:       return static_cast<int>(any_cast<short>(m_value));
                case valueType_uint32:      return static_cast<int>(any_cast<uint32>(m_value));
                case valueType_uint16:      return static_cast<int>(any_cast<uint16>(m_value));
                case valueType_float:       return static_cast<int>(any_cast<float>(m_value));
                case valueType_double:      return static_cast<int>(any_cast<double>(m_value));
                case valueType_uint8:       return static_cast<int>(any_cast<uint8>(m_value));
                case valueType_bool:        return static_cast<int>(any_cast<bool>(m_value));
                case valueType_string:      return static_cast<int>(std::stoi(any_cast<std::string>(m_value)));

                default:
                    throw Error_BadDataType();
            }
        }
        catch(...)
        {
            throw Error_BadDataType();
        }
    }

    bool Value::as_bool() const
    {
        try
        {
            switch(m_storedAs)
            {
                case valueType_bool:
                    return any_cast<bool>(m_value);

                case valueType_int16:
                case valueType_uint32:
                case valueType_uint16:
                case valueType_uint8:
                case valueType_int32:
                    return as_uint32() != 0;

                case valueType_float:
                case valueType_double:
                    return as_double() != 0.0;

                case valueType_string:
                default:
                    return as_uint32() != 0;
            }
        }
        catch(...)
        {
            throw Error_BadDataType();
        }
    }

    ChannelMask Value::as_ChannelMask() const
    {
        if(m_storedAs == valueType_ChannelMask)
        {
            ChannelMask result = any_cast<ChannelMask>(m_value);
            return result;
        }

        throw Error_BadDataType();
    }

    std::string Value::as_string() const
    {
        //if the data is stored as a string
        if(m_storedAs == valueType_string)
        {
            try
            {
                return any_cast<std::string>(m_value);
            }
            catch(std::bad_cast&)
            {
                throw Error_BadDataType();
            }
        }

        //build the string depending on how the value is stored
        switch(m_storedAs)
        {
        case valueType_uint8:       return Utils::toStr(static_cast<uint16>(as_uint8()));
        case valueType_uint16:      return Utils::toStr(as_uint16());
        case valueType_uint32:      return Utils::toStr(as_uint32());
        case valueType_int16:       return Utils::toStr(as_int16());
        case valueType_int32:       return Utils::toStr(as_int32());
        case valueType_float:       return Utils::toStr(as_float());
        case valueType_double:      return Utils::toStr(as_double());
        case valueType_bool:        return Utils::toStr(as_bool());

        default:
            throw Error_BadDataType();
        }
    }
}