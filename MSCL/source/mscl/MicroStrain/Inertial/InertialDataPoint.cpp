/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "InertialDataPoint.h"

namespace mscl
{
	InertialDataPoint::InertialDataPoint() :
		DataPoint(valueType_float, anyType(0.0f)),
		m_field(static_cast<InertialTypes::ChannelField>(0)),
		m_qualifier(InertialTypes::CH_UNKNOWN),
		m_valid(false)
	{
	}

	InertialDataPoint::InertialDataPoint(InertialTypes::ChannelField field, InertialTypes::ChannelQualifier qualifier, ValueType storedAsType, anyType value, bool valid) :
		DataPoint(storedAsType, value),
			m_field(field),
			m_qualifier(qualifier),
			m_valid(valid)
	{
	}

	InertialTypes::ChannelField InertialDataPoint::field() const
	{
		return m_field;
	}

	InertialTypes::ChannelQualifier InertialDataPoint::qualifier() const
	{
		return m_qualifier;
	}

	bool InertialDataPoint::valid() const
	{
		return m_valid;
	}

	std::string InertialDataPoint::channelName() const
	{
		return InertialTypes::channelName(m_field, m_qualifier);
	}

	std::string InertialDataPoint::str() const
	{
		return InertialTypes::channelFieldToStr(m_field) + "-" + InertialTypes::channelQualifierToStr(m_qualifier);
	}
}