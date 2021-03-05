/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

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
        MipDataPoint(MipTypes::ChannelField field, MipTypes::ChannelQualifier qualifier, ValueType storedAsType, anyType value);

        //Constructor: MipDataPoint
        //    Creates a MipDataPoint object with additional identifier values that describe the point
        //
        //Parameters:
        //    field - The <MipTypes::ChannelField> for the data point.
        //    qualifier - The <MipTypes::ChannelQualifier> for the data point.
        //    addlIds - The <MipChannelIdentifiers> to further identify the data point.
        //    storedAsType - The <ValueType> that represents how the internal data point value is stored.
        //    value - The value to store.
        MipDataPoint(MipTypes::ChannelField field, MipTypes::ChannelQualifier qualifier, MipChannelIdentifiers addlIds, ValueType storedAsType, anyType value);

        //Constructor: MipDataPoint
        //    Creates a MipDataPoint object with a valid flag that describes the point
        //
        //Parameters:
        //    field - The <MipTypes::ChannelField> for the data point.
        //    qualifier - The <MipTypes::ChannelQualifier> for the data point.
        //    storedAsType - The <ValueType> that represents how the internal data point value is stored.
        //    value - The value to store.
        //    valid - Whether the data point is flagged as valid (true) or invalid (false).
        MipDataPoint(MipTypes::ChannelField field, MipTypes::ChannelQualifier qualifier, ValueType storedAsType, anyType value, bool valid);

        //Constructor: MipDataPoint
        //    Creates a MipDataPoint object with additional identifier values and a valid flag that describes the point
        //
        //Parameters:
        //    field - The <MipTypes::ChannelField> for the data point.
        //    qualifier - The <MipTypes::ChannelQualifier> for the data point.
        //    addlIds - The <MipChannelIdentifiers> to further identify the data point.
        //    storedAsType - The <ValueType> that represents how the internal data point value is stored.
        //    value - The value to store.
        //    valid - Whether the data point is flagged as valid (true) or invalid (false).
        MipDataPoint(MipTypes::ChannelField field, MipTypes::ChannelQualifier qualifier, MipChannelIdentifiers addlIds, ValueType storedAsType, anyType value, bool valid);

    private:
        //Variable: m_field;
        //    The <MipTypes::ChannelField> of the data point.
        MipTypes::ChannelField m_field;

        //Variable: m_qualifier
        //    The <MipTypes::ChannelQualifier> of the data point.
        MipTypes::ChannelQualifier m_qualifier;

        //Variable: m_addlIdentifiers
        //  A <MipChannelIdentifiers> list of additional identifiers for this data point ie GNSS constellation and satellite ID
        MipChannelIdentifiers m_addlIdentifiers;

        //Variable: m_hasValidFlag
        //  Whether the data point was transmitted with a valid flag.
        //  If the point wasn't transmitted with a flag, m_valid will be set to true.
        bool m_hasValidFlag;

        //Variable: m_valid
        //    Whether the data point is valid(true) or invalid(false).
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

        //API Function: hasAddlIdentifiers
        //  Indicates whether or not this data point has additional data identifiers.
        //
        //Returns:
        //  true if additional <MipChannelIdentifiers> have been assigned to this data point. 
        bool hasAddlIdentifiers() const;

        //API Function: addlIdentifiers
        //  Get the additional identifier values assigned to this data point.
        //
        //Returns:
        //  <MipChannelIdentifiers> - the additional identifiers for this data point.
        MipChannelIdentifiers addlIdentifiers() const;

        //API Function: hasValidFlag
        //  Gets whether the data point had a valid flag transmitted in the data packet.
        //  Note: if hasValidFlag returns false, <valid> will always return true.
        //
        //Returns:
        //  true if the data point had a valid flag associated with it, false otherwise.
        bool hasValidFlag() const;

        //API Function: valid
        //  Gets whether the data point is valid(true) or invalid(false).
        //  Note: if a data point was not transmitted with a flag representing its validity,
        //        this will still return true. To determine if the data point had a flag in the
        //        data packet, use <hasValidFlag>.
        //
        //Returns:
        //  true if the data point is valid, false if the data point is invalid
        bool valid() const;

        //API Function: channelName
        //    Gets the name of the channel. 
        //    This is the universal channel name that should be used for uploading to SensorCloud.
        //
        //Parameters:
        //    includeAddlIds - default: true - when true, includes the additional identifiers in the channel name string if present.
        //    consolidatedFormat - default: false - consolidate additional identifiers into interpreted strings when relevant. Ex: when false: "aidingMeasurement_5", when true: "magnetometer"
        //
        //Returns:
        //    The name of the channel.
        //
        //Exceptions:
        //    - <Error>: Unknown channel.
        std::string channelName(bool includeAddlIds = true, bool consolidatedFormat = false) const;
    };

    //API Typedef: MipDataPoints
    //    Typedef for a vector of <MipDataPoint> objects
    typedef std::vector<MipDataPoint> MipDataPoints;
}