/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/MicroStrain/DataPoint.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"

namespace mscl
{
    //API Class: MipDataPoint
    //    Represents a single Inertial Data Point (Extends from <DataPoint>)
    //
    //See Also:
    //    <DataPoint>, <Value>
    class MipDataPoint : public DataPoint
    {
#ifndef SWIG
    public:
        //Constructor: MipDataPoint
        //    Creates a MipDataPoint object with default, unknown, values
        MipDataPoint();

        //Constructor: MipDataPoint
        //    Creates a MipDataPoint object
        //
        //Parameters:
        //    field - The <MipTypes::ChannelField> for the data point.
        //    qualifier - The <MipTypes::ChannelQualifier> for the data point.
        //    storedAsType - The <ValueType> that represents how the internal data point value is stored.
        //    value - The value to store.
        //    valid - Whether the data point is flagged as valid (true) or invalid (false).
        MipDataPoint(MipTypes::ChannelField field, MipTypes::ChannelQualifier qualifier, ValueType storedAsType, anyType value, bool valid);

    private:
        //Variable: m_field;
        //    The <MipTypes::ChannelField> of the data point.
        MipTypes::ChannelField m_field;

        //Variable: m_qualifier
        //    The <MipTypes::ChannelQualifier> of the data point.
        MipTypes::ChannelQualifier m_qualifier;

        //Variable: m_valid
        //    Whether the data point is valid(true) or invalid(false)
        bool m_valid;
#endif

    public:
        //API Function: field
        //    Gets the Channel Field that describes the full MIP "Field" that the data point came in.
        //    This is a combination of a MIP "Descriptor ID", and a MIP "Field ID".
        //
        //Returns:
        //    The <MipTypes::ChannelField> for this data point.
        MipTypes::ChannelField field() const;

        //API Function: qualifier
        //    Gets the Channel Qualifier that describes the specific channel for the data point.
        //    This, combined with the <MipTypes::ChannelField>, is a fully unique identifier for the channel.
        //
        //Returns:
        //    The <MipTypes::ChannelQualifier> for this data point.
        MipTypes::ChannelQualifier qualifier() const;

        //API Function: valid
        //    Gets whether the data point is flagged as valid(true) or invalid(false)
        //
        //Returns:
        //    true if the data point is valid, false if the data point is invalid
        bool valid() const;

        //API Function: channelName
        //    Gets the name of the channel. 
        //    This is the universal channel name that should be used for uploading to SensorCloud.
        //
        //Returns:
        //    The name of the channel.
        //
        //Exceptions:
        //    - <Error>: Unknown channel.
        std::string channelName() const;
    };

    //API Typedef: MipDataPoints
    //    Typedef for a vector of <MipDataPoint> objects
    typedef std::vector<MipDataPoint> MipDataPoints;
}