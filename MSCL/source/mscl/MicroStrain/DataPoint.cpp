/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "DataPoint.h"

#include <iomanip>
#include "mscl/Exceptions.h"
#include "mscl/Types.h"
#include "mscl/Utils.h"

namespace mscl
{
    DataPoint::DataPoint(ValueType type, const anyType& value):
        Value(type, value)
    {
    }


    const Vector DataPoint::as_Vector() const
    {
        try
        {
            Vector result = any_cast<Vector>(m_value);
            return result;
        }
        catch(std::bad_cast&)
        {
            throw Error_BadDataType();
        }
    }

    const Matrix DataPoint::as_Matrix() const
    {
        try
        {
            Matrix result = any_cast<Matrix>(m_value);
            return result;
        }
        catch(std::bad_cast&)
        {
            throw Error_BadDataType();
        }
    }

    const Timestamp DataPoint::as_Timestamp() const
    {
        try
        {
            Timestamp result = any_cast<Timestamp>(m_value);
            return result;
        }
        catch(std::bad_cast&)
        {
            throw Error_BadDataType();
        }
    }

    const Bytes DataPoint::as_Bytes() const
    {
        try
        {
            Bytes result = any_cast<Bytes>(m_value);
            return result;
        }
        catch(std::bad_cast&)
        {
            throw Error_BadDataType();
        }
    }

    const StructuralHealth DataPoint::as_StructuralHealth() const
    {
        try
        {
            StructuralHealth result = any_cast<StructuralHealth>(m_value);
            return result;
        }
        catch(std::bad_cast&)
        {
            throw Error_BadDataType();
        }
    }

    const RfSweep DataPoint::as_RfSweep() const
    {
        try
        {
            RfSweep result = any_cast<RfSweep>(m_value);
            return result;
        }
        catch(std::bad_cast&)
        {
            throw Error_BadDataType();
        }
    }

    std::string DataPoint::as_string() const
    {
        //build the string depending on how the value is stored
        switch(m_storedAs)
        {
        case valueType_Vector:
            return as_Vector().str();

        case valueType_Matrix:
            return as_Matrix().str();

        case valueType_Timestamp:
            return as_Timestamp().str();

        case valueType_Bytes:
        {
            std::stringstream result;
            result << std::hex << std::setfill('0');

            const Bytes data = as_Bytes();
            Bytes::const_iterator itr;

            //for every byte in Bytes
            for(itr = data.begin(); itr != data.end(); ++itr)
            {
                result << "0x" << std::setw(2) << static_cast<uint32>(*itr);

                //if this isn't the last byte
                if(itr != (data.end() - 1))
                {
                    //add a separator
                    result << " ";
                }
            }

            return result.str();
        }

        case valueType_string:
        case valueType_float:
        case valueType_double:
        case valueType_uint8:
        case valueType_uint16:
        case valueType_uint32:
        case valueType_int16:
        case valueType_int32:
        case valueType_bool:
            return Value::as_string();

        //types that can't be converted to a string
        default:
            throw Error_BadDataType();
        }
    }
}