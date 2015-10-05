/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "Vector.h"
#include "Matrix.h"
#include "mscl/Utils.h"

namespace mscl
{
	Vector::Vector():
		m_size(0),
		m_valuesType(valueType_float)
	{
	}

	Vector::Vector(ValueType storedAs, const ByteStream& data):
		m_size(static_cast<uint16>(data.size() / Utils::valueTypeSize(storedAs))),	//size = (# of bytes in ByteStream / # of bytes in the values' type)
		m_valuesType(storedAs),
		m_data(m_size, 1, storedAs, data)
	{
	}

	float Vector::as_floatAt(uint16 index) const
	{
		//return the float at the requested position
		return m_data.as_floatAt(index, COLUMN_POS);
	}

	uint16 Vector::as_uint16At(uint16 index) const
	{
		//return the uint16 at the requested position
		return m_data.as_uint16At(index, COLUMN_POS);
	}

	uint8 Vector::as_uint8At(uint16 index) const
	{
		//return the uint8 at the requested position
		return m_data.as_uint8At(index, COLUMN_POS);
	}

	ValueType Vector::valuesType() const
	{
		return m_valuesType;
	}

	uint16 Vector::size() const
	{
		return m_size;
	}

	std::string Vector::str() const
	{
		std::stringstream result;

		result << "[";
		//for every value in the Vector
		for (uint16 itr = 0; itr < m_size; itr++)
		{
			//get the value of the value depending on how it is stored
			switch(m_valuesType)
			{
			case valueType_uint16:
				result << as_uint16At(itr);
				break;

			case valueType_float:
				result << as_floatAt(itr);
				break;

			//all other values not supported as a Vector type as of now
			default:
				break;
			}

			//if this isn't the last value in the Vector
			if(itr < (m_size - 1))
			{
				//add a separator
				result << ",";
			}
		}
		result << "]";

		return result.str();
	}
}