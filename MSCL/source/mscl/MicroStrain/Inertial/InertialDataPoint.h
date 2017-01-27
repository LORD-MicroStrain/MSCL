/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/MicroStrain/DataPoint.h"
#include "InertialTypes.h"

namespace mscl
{
    //API Class: InertialDataPoint
    //    Represents a single Inertial Data Point (Extends from <DataPoint>)
    //
    //See Also:
    //    <DataPoint>, <Value>
    class InertialDataPoint : public DataPoint
    {
#ifndef SWIG
    public:
        //Constructor: InertialDataPoint
        //    Creates an InertialDataPoint object with default, unknown, values
        InertialDataPoint();

        //Constructor: InertialDataPoint
        //    Creates an InertialDataPoint object
        //
        //Parameters:
        //    field - The <InertialTypes::ChannelField> for the data point.
        //    qualifier - The <InertialTypes::ChannelQualifier> for the data point.
        //    storedAsType - The <ValueType> that represents how the internal data point value is stored.
        //    value - The value to store.
        //    valid - Whether the data point is flagged as valid (true) or invalid (false).
        InertialDataPoint(InertialTypes::ChannelField field, InertialTypes::ChannelQualifier qualifier, ValueType storedAsType, anyType value, bool valid);

    private:
        //Variable: m_field;
        //    The <InertialTypes::ChannelField> of the data point.
        InertialTypes::ChannelField m_field;

        //Variable: m_qualifier
        //    The <InertialTypes::ChannelQualifier> of the data point.
        InertialTypes::ChannelQualifier m_qualifier;

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
        //    The <InertialTypes::ChannelField> for this data point.
        InertialTypes::ChannelField field() const;

        //API Function: qualifier
        //    Gets the Channel Qualifier that describes the specific channel for the data point.
        //    This, combined with the <InertialTypes::ChannelField>, is a fully unique identifier for the channel.
        //
        //Returns:
        //    The <InertialTypes::ChannelQualifier> for this data point.
        InertialTypes::ChannelQualifier qualifier() const;

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

        //API Function: str
        //    Gets the string representation of the type of this data point
        //
        //Returns:
        //    The string representation of the type of this data point
        std::string str() const;
    };

    //API Typedef: InertialDataPoints
    //    Typedef for a vector of <InertialDataPoint> objects
    typedef std::vector<InertialDataPoint> InertialDataPoints;

    //API Class: InertialDataEnums
    //    Contains enums representing the possible values for certain Inertial Data Points
    struct InertialDataEnums
    {
    public:
        //============================================================================================================
        //API Enums: GpsFixType
        //    The GPS Fix Types with the GPS Fix Information field
        //
        //    FIXTYPE_3D            - 0x00    - 3D Fix
        //    FIXTYPE_2D            - 0x01    - 2D Fix
        //    FIXTYPE_TIMEONLY    - 0x02    - Time Only
        //    FIXTYPE_NONE        - 0x03    - None
        //    FIXTYPE_INVALID        - 0x04    - Invalid
        //============================================================================================================
        enum GpsFixType
        {
            FIXTYPE_3D            = 0x00,
            FIXTYPE_2D            = 0x01,
            FIXTYPE_TIMEONLY    = 0x02,
            FIXTYPE_NONE        = 0x03,
            FIXTYPE_INVALID        = 0x04
        };

        //============================================================================================================
        //API Enums: HwStatus_SensorState
        //    The Sensor States with the GPS Hardware Status field
        //
        //    SENSORSTATE_OFF            - 0x00    - Sensor Off
        //    SENSORSTATE_ON            - 0x01    - Sensor On
        //    SENSORSTATE_UNKNOWN        - 0x02    - Sensor State Unknown
        //============================================================================================================
        enum HwStatus_SensorState
        {
            SENSORSTATE_OFF        = 0x00,
            SENSORSTATE_ON        = 0x01,
            SENSORSTATE_UNKNOWN    = 0x02
        };

        //============================================================================================================
        //API Enums: HwStatus_AntennaState
        //    The Antenna States with the GPS Hardware Status field
        //
        //    ANTENNASTATE_INIT        - 0x01    - Antenna Init
        //    ANTENNASTATE_SHORT        - 0x02    - Antenna Short
        //    ANTENNASTATE_OPEN        - 0x03    - Antenna Open
        //    ANTENNASTATE_GOOD        - 0x04    - Antenna Good
        //    ANTENNASTATE_UNKNOWN    - 0x05    - Antenna State Unknown
        //============================================================================================================
        enum HwStatus_AntennaState
        {
            ANTENNASTATE_INIT        = 0x01,
            ANTENNASTATE_SHORT        = 0x02,
            ANTENNASTATE_OPEN        = 0x03,
            ANTENNASTATE_GOOD        = 0x04,
            ANTENNASTATE_UNKNOWN    = 0x05
        };

        //============================================================================================================
        //API Enums: HwStatus_AntennaPower
        //    The Antenna Powers with the GPS Hardware Status field
        //
        //    ANTENNAPOWER_OFF        - 0x00    - Antenna Off
        //    ANTENNAPOWER_ON            - 0x01    - Antenna On
        //    ANTENNAPOWER_UNKNOWN    - 0x02    - Antenna Power Unknown
        //============================================================================================================
        enum HwStatus_AntennaPower
        {
            ANTENNAPOWER_OFF        = 0x00,
            ANTENNAPOWER_ON            = 0x01,
            ANTENNAPOWER_UNKNOWN    = 0x02
        };

        //============================================================================================================
        //API Enums: FilterStatus_FilterState 
        //    The Filter States with the NAV Filter Status field
        //
        //    FILTERSTATE_STARTUP                - 0x00    - Startup
        //    FILTERSTATE_INIT                - 0x01    - Initialization (see status flags)
        //    FILTERSTATE_RUNNING_SLN_VALID    - 0x02    - Running, Solution Valid
        //    FILTERSTATE_RUNNING_SLN_ERROR    - 0x03    - Running, Solution Error (see status flags)
        //============================================================================================================
        enum FilterStatus_FilterState
        {
            FILTERSTATE_STARTUP                = 0x00,
            FILTERSTATE_INIT                = 0x01,
            FILTERSTATE_RUNNING_SLN_VALID    = 0x02,
            FILTERSTATE_RUNNING_SLN_ERROR    = 0x03
        };

        //============================================================================================================
        //API Enums: FilterStatus_DynamicsMode
        //    The Dynamics Modes with the NAV Filter Status field
        //
        //    DYNAMICSMODE_PORTABLE        - 0x01    - Portable
        //    DYNAMICSMODE_AUTOMOTIVE        - 0x02    - Automotive
        //    DYNAMICSMODE_AIRBORNE        - 0x03    - Airborne
        //============================================================================================================
        enum FilterStatus_DynamicsMode
        {
            DYNAMICSMODE_PORTABLE        = 0x01,
            DYNAMICSMODE_AUTOMOTIVE        = 0x02,
            DYNAMICSMODE_AIRBORNE        = 0x03
        };

        //============================================================================================================
        //API Enums: FilterStatus_StatusFlags
        //    Binary flags that give information with the NAV Filter Status field. Each bit must be checked accordingly.
        //
        //    FILTERSTATUS_IMU_UNAVAILABLE                - 0x0001    - Filter Running, IMU Unavailable
        //    FILTERSTATUS_GPS_UNAVAILABLE                - 0x0002    - Filter Running, GPS Unavailable
        //    FILTERSTATUS_MATRIX_SINGULARITY_IN_CALC        - 0x0008    - Filter Running, Matrix Singularity in Calculation
        //    FILTERSTATUS_POS_COVARIANCE_HIGH_WARN        - 0x0010    - Filter Running, Position Covariance High Warning
        //    FILTERSTATUS_VEL_COVARIANCE_HIGH_WARN        - 0x0020    - Filter Running, Velocity Covariance High Warning
        //    FILTERSTATUS_ATT_COVARIANCE_HIGH_WARN        - 0x0040    - Filter Running, Attitude Covariance High Warning
        //    FILTERSTATUS_NAN_IN_SOLUTION                - 0x0080    - Filter Running, NAN in Solution
        //    FILTERSTATUS_ATT_NOT_INIT                    - 0x1000    - Filter Initialization, Attitude not Initialized
        //    FILTERSTATUS_POS_VEL_NOT_INIT                - 0x2000    - Filter Initialization, Position and Velocity not Initialized
        //============================================================================================================
        enum FilterStatus_StatusFlags
        {
            FILTERSTATUS_IMU_UNAVAILABLE                = 0x0001,
            FILTERSTATUS_GPS_UNAVAILABLE                = 0x0002,
            FILTERSTATUS_MATRIX_SINGULARITY_IN_CALC        = 0x0008,
            FILTERSTATUS_POS_COVARIANCE_HIGH_WARN        = 0x0010,
            FILTERSTATUS_VEL_COVARIANCE_HIGH_WARN        = 0x0020,
            FILTERSTATUS_ATT_COVARIANCE_HIGH_WARN        = 0x0040,
            FILTERSTATUS_NAN_IN_SOLUTION                = 0x0080,
            FILTERSTATUS_ATT_NOT_INIT                    = 0x1000,
            FILTERSTATUS_POS_VEL_NOT_INIT                = 0x2000
        };

        //============================================================================================================
        //API Enums: HeadingSource
        //    The Heading Sources with the Heading Update Source State field
        //
        //    HEADINGSOURCE_NONE                                - 0x0000    - No source, heading updates disabled
        //    HEADINGSOURCE_INTERNAL_MAGNETOMETER                - 0x0001    - Internal Magnetometer
        //    HEADINGSOURCE_INTERNAL_GPS_VELOCITY_VECTOR        - 0x0002    - Internal GPS Velocity Vector
        //    HEADINGSOURCE_EXTERNAL_HEADING_UPDATE_CMD        - 0x0004    - External Heading Update Command
        //============================================================================================================
        enum HeadingSource
        {
            HEADINGSOURCE_NONE                            = 0x0000,
            HEADINGSOURCE_INTERNAL_MAGNETOMETER            = 0x0001,
            HEADINGSOURCE_INTERNAL_GPS_VELOCITY_VECTOR    = 0x0002,
            HEADINGSOURCE_EXTERNAL_HEADING_UPDATE_CMD    = 0x0004
        };
    };
}