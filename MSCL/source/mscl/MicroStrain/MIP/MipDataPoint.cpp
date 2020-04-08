/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "MipDataPoint.h"

namespace mscl
{
    MipDataPoint::MipDataPoint() :
        DataPoint(valueType_float, anyType(0.0f)),
        m_field(static_cast<MipTypes::ChannelField>(0)),
        m_qualifier(MipTypes::CH_UNKNOWN),
        m_hasValidFlag(false),
        m_valid(false)
    {
    }

    MipDataPoint::MipDataPoint(MipTypes::ChannelField field, MipTypes::ChannelQualifier qualifier, ValueType storedAsType, anyType value):
        DataPoint(storedAsType, value),
        m_field(field),
        m_qualifier(qualifier),
        m_hasValidFlag(false),
        m_valid(true)
    {
    }

    MipDataPoint::MipDataPoint(MipTypes::ChannelField field, MipTypes::ChannelQualifier qualifier, ValueType storedAsType, anyType value, bool valid) :
        DataPoint(storedAsType, value),
        m_field(field),
        m_qualifier(qualifier),
        m_hasValidFlag(true),
        m_valid(valid)
    {
    }

    MipTypes::ChannelField MipDataPoint::field() const
    {
        return m_field;
    }

    MipTypes::ChannelQualifier MipDataPoint::qualifier() const
    {
        return m_qualifier;
    }

    bool MipDataPoint::hasValidFlag() const
    {
        return m_hasValidFlag;
    }

    bool MipDataPoint::valid() const
    {
        return m_valid;
    }

    std::string MipDataPoint::channelName() const
    {
        return MipTypes::channelName(m_field, m_qualifier);
    }
}