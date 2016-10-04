/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "InertialFieldParser_EstFilter.h"
#include "InertialDataPacket.h"
#include "mscl/MicroStrain/DataBuffer.h"

namespace mscl
{
    //the classes in this file do not get referenced anywhere, therefore the 
    //linker will not include this compilation unit when statically 
    //linking to an executable. Defining this variable, and then using it
    //elsewhere, will force this file to be included
    bool _forceLibraryToIncludeCompilationUnit_NAV;

    //=====================================================================================================================================================
    //                                                        FieldParser_FilterStatus
    const InertialTypes::ChannelField FieldParser_FilterStatus::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_FILTER_STATUS;
    const bool FieldParser_FilterStatus::REGISTERED = FieldParser_FilterStatus::registerParser();    //register the parser immediately

    void FieldParser_FilterStatus::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the filter state
        uint16 filterState = bytes.read_uint16();

        //get the dynamics mode
        uint16 dynamicsMode = bytes.read_uint16();

        //get the status flags
        uint16 statusFlags = bytes.read_uint16();

        //add all the data points we just collected
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_FILTER_STATE, valueType_uint16, anyType(filterState), true));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_DYNAMICS_MODE, valueType_uint16, anyType(dynamicsMode), true));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_FLAGS, valueType_uint16, anyType(statusFlags), true));
    }

    bool FieldParser_FilterStatus::registerParser()
    {
        //create a static parser object
        static FieldParser_FilterStatus p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_NAV_GPS_Timestamp
    const InertialTypes::ChannelField FieldParser_NAV_GPS_Timestamp::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_GPS_TIMESTAMP;
    const bool FieldParser_NAV_GPS_Timestamp::REGISTERED = FieldParser_NAV_GPS_Timestamp::registerParser();    //register the parser immediately

    void FieldParser_NAV_GPS_Timestamp::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the time of week
        double timeOfWeek = bytes.read_double();

        //get the week number
        uint16 weekNumber = bytes.read_uint16();

        //get the flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool timeValid    = pointIsValid(flags, TIME_FLAG);

        //add all the data points we just collected
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_TIME_OF_WEEK, valueType_double, anyType(timeOfWeek), timeValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_WEEK_NUMBER, valueType_uint16, anyType(weekNumber), timeValid));
    }

    bool FieldParser_NAV_GPS_Timestamp::registerParser()
    {
        //create a static parser object
        static FieldParser_NAV_GPS_Timestamp p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedLLHPosition
    const InertialTypes::ChannelField FieldParser_EstimatedLLHPosition::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_LLH_POS;
    const bool FieldParser_EstimatedLLHPosition::REGISTERED = FieldParser_EstimatedLLHPosition::registerParser();    //register the parser immediately

    void FieldParser_EstimatedLLHPosition::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the latitude
        double latitude = bytes.read_double();

        //get the longitude
        double longitude = bytes.read_double();

        //get the Height above Ellipsoid
        double heightAboveEllipsoid = bytes.read_double();

        //get the flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool latLongValid    = pointIsValid(flags, LLH_FLAG);

        //add all the data points we just collected
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_LATITUDE, valueType_double, anyType(latitude), latLongValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_LONGITUDE, valueType_double, anyType(longitude), latLongValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_HEIGHT_ABOVE_ELLIPSOID, valueType_double, anyType(heightAboveEllipsoid), latLongValid));
    }

    bool FieldParser_EstimatedLLHPosition::registerParser()
    {
        //create a static parser object
        static FieldParser_EstimatedLLHPosition p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedNEDVelocity
    const InertialTypes::ChannelField FieldParser_EstimatedNEDVelocity::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_NED_VELOCITY;
    const bool FieldParser_EstimatedNEDVelocity::REGISTERED = FieldParser_EstimatedNEDVelocity::registerParser();    //register the parser immediately

    void FieldParser_EstimatedNEDVelocity::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the north value
        float north = bytes.read_float();

        //get the east value
        float east = bytes.read_float();

        //get the down value
        float down = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool nedValid    = pointIsValid(flags, NED_FLAG);

        //add all the data points we just collected
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_NORTH, valueType_float, anyType(north), nedValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_EAST, valueType_float, anyType(east), nedValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_DOWN, valueType_float, anyType(down), nedValid));
    }

    bool FieldParser_EstimatedNEDVelocity::registerParser()
    {
        //create a static parser object
        static FieldParser_EstimatedNEDVelocity p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedQuaternion
    const InertialTypes::ChannelField FieldParser_EstimatedQuaternion::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_QUATERNION;
    const bool FieldParser_EstimatedQuaternion::REGISTERED = FieldParser_EstimatedQuaternion::registerParser();    //register the parser immediately

    void FieldParser_EstimatedQuaternion::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        //create a Vector to store as the data point
        Vector data(valueType_float, field.fieldData());

        //read the flags value
        const uint16 FLAG_BYTE_POS = 16;
        uint16 flags = field.fieldData().read_uint16(FLAG_BYTE_POS);

        //get whether points are valid or invalid from the flags
        bool valid    = pointIsValid(flags, QUATERNION_FLAG);

        //create a data point and add it to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_QUATERNION, valueType_Vector, anyType(data), valid));
    }

    bool FieldParser_EstimatedQuaternion::registerParser()
    {
        //create a static parser object
        static FieldParser_EstimatedQuaternion p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedMatrix
    const InertialTypes::ChannelField FieldParser_EstimatedMatrix::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_MATRIX;
    const bool FieldParser_EstimatedMatrix::REGISTERED = FieldParser_EstimatedMatrix::registerParser();    //register the parser immediately

    void FieldParser_EstimatedMatrix::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        //create a Matrix to store as the data point
        Matrix data(3, 3, valueType_float, field.fieldData());

        //read the flags value
        const uint16 FLAG_BYTE_POS = 36;
        uint16 flags = field.fieldData().read_uint16(FLAG_BYTE_POS);

        //get whether points are valid or invalid from the flags
        bool valid    = pointIsValid(flags, MATRIX_FLAG);

        //create a Matrix object with the Orientation Matrix data and create an InertialDataPoint from it
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_MATRIX, valueType_Matrix, anyType(data), valid));
    }

    bool FieldParser_EstimatedMatrix::registerParser()
    {
        //create a static parser object
        static FieldParser_EstimatedMatrix p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedEulerAngles
    const InertialTypes::ChannelField FieldParser_EstimatedEulerAngles::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_EULER;
    const bool FieldParser_EstimatedEulerAngles::REGISTERED = FieldParser_EstimatedEulerAngles::registerParser();    //register the parser immediately

    void FieldParser_EstimatedEulerAngles::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data values
        float roll = bytes.read_float();
        float pitch = bytes.read_float();
        float yaw = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid    = pointIsValid(flags, EULER_FLAG);

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_ROLL, valueType_float, anyType(roll), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_PITCH, valueType_float, anyType(pitch), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_YAW, valueType_float, anyType(yaw), valid));
    }

    bool FieldParser_EstimatedEulerAngles::registerParser()
    {
        //create a static parser object
        static FieldParser_EstimatedEulerAngles p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedGyroBias
    const InertialTypes::ChannelField FieldParser_EstimatedGyroBias::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS;
    const bool FieldParser_EstimatedGyroBias::REGISTERED = FieldParser_EstimatedGyroBias::registerParser();    //register the parser immediately

    void FieldParser_EstimatedGyroBias::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, GYRO_FLAG);

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_EstimatedGyroBias::registerParser()
    {
        //create a static parser object
        static FieldParser_EstimatedGyroBias p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================


    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedAccelBias
    const InertialTypes::ChannelField FieldParser_EstimatedAccelBias::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS;
    const bool FieldParser_EstimatedAccelBias::REGISTERED = FieldParser_EstimatedAccelBias::registerParser();    //register the parser immediately

    void FieldParser_EstimatedAccelBias::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //read the data values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, ACCEL_FLAG);

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_EstimatedAccelBias::registerParser()
    {
        //create a static parser object
        static FieldParser_EstimatedAccelBias p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================


    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedLLHPosUncertainty
    const InertialTypes::ChannelField FieldParser_EstimatedLLHPosUncertainty::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_LLH_UNCERT;
    const bool FieldParser_EstimatedLLHPosUncertainty::REGISTERED = FieldParser_EstimatedLLHPosUncertainty::registerParser();    //register the parser immediately

    void FieldParser_EstimatedLLHPosUncertainty::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float north = bytes.read_float();
        float east = bytes.read_float();
        float down = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, UNCERTAINTY_FLAG);

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_NORTH, valueType_float, anyType(north), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_EAST, valueType_float, anyType(east), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_DOWN, valueType_float, anyType(down), valid));
    }

    bool FieldParser_EstimatedLLHPosUncertainty::registerParser()
    {
        //create a static parser object
        static FieldParser_EstimatedLLHPosUncertainty p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedNEDUncertainty
    const InertialTypes::ChannelField FieldParser_EstimatedNEDUncertainty::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_NED_UNCERT;
    const bool FieldParser_EstimatedNEDUncertainty::REGISTERED = FieldParser_EstimatedNEDUncertainty::registerParser();    //register the parser immediately

    void FieldParser_EstimatedNEDUncertainty::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float north = bytes.read_float();
        float east = bytes.read_float();
        float down = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, UNCERTAINTY_FLAG);

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_NORTH, valueType_float, anyType(north), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_EAST, valueType_float, anyType(east), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_DOWN, valueType_float, anyType(down), valid));
    }

    bool FieldParser_EstimatedNEDUncertainty::registerParser()
    {
        //create a static parser object
        static FieldParser_EstimatedNEDUncertainty p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedAttEulerUncertainty
    const InertialTypes::ChannelField FieldParser_EstimatedAttEulerUncertainty::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_ATT_UNCERT_EULER;
    const bool FieldParser_EstimatedAttEulerUncertainty::REGISTERED = FieldParser_EstimatedAttEulerUncertainty::registerParser();    //register the parser immediately

    void FieldParser_EstimatedAttEulerUncertainty::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float roll = bytes.read_float();
        float pitch = bytes.read_float();
        float yaw = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, UNCERTAINTY_FLAG);

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_ROLL, valueType_float, anyType(roll), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_PITCH, valueType_float, anyType(pitch), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_YAW, valueType_float, anyType(yaw), valid));
    }

    bool FieldParser_EstimatedAttEulerUncertainty::registerParser()
    {
        //create a static parser object
        static FieldParser_EstimatedAttEulerUncertainty p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedGyroBiasUncertainty
    const InertialTypes::ChannelField FieldParser_EstimatedGyroBiasUncertainty::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS_UNCERT;
    const bool FieldParser_EstimatedGyroBiasUncertainty::REGISTERED = FieldParser_EstimatedGyroBiasUncertainty::registerParser();    //register the parser immediately

    void FieldParser_EstimatedGyroBiasUncertainty::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, UNCERTAINTY_FLAG);

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_EstimatedGyroBiasUncertainty::registerParser()
    {
        //create a static parser object
        static FieldParser_EstimatedGyroBiasUncertainty p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================


    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedAccelBiasUncertainty
    const InertialTypes::ChannelField FieldParser_EstimatedAccelBiasUncertainty::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS_UNCERT;
    const bool FieldParser_EstimatedAccelBiasUncertainty::REGISTERED = FieldParser_EstimatedAccelBiasUncertainty::registerParser();    //register the parser immediately

    void FieldParser_EstimatedAccelBiasUncertainty::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, UNCERTAINTY_FLAG);

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_EstimatedAccelBiasUncertainty::registerParser()
    {
        //create a static parser object
        static FieldParser_EstimatedAccelBiasUncertainty p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================


    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedLinearAccel
    const InertialTypes::ChannelField FieldParser_EstimatedLinearAccel::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_LINEAR_ACCEL;
    const bool FieldParser_EstimatedLinearAccel::REGISTERED = FieldParser_EstimatedLinearAccel::registerParser();    //register the parser immediately

    void FieldParser_EstimatedLinearAccel::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, ACCEL_FLAG);

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_EstimatedLinearAccel::registerParser()
    {
        //create a static parser object
        static FieldParser_EstimatedLinearAccel p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedAngularRate
    const InertialTypes::ChannelField FieldParser_EstimatedAngularRate::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_ANGULAR_RATE;
    const bool FieldParser_EstimatedAngularRate::REGISTERED = FieldParser_EstimatedAngularRate::registerParser();    //register the parser immediately

    void FieldParser_EstimatedAngularRate::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, RATE_FLAG);

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_EstimatedAngularRate::registerParser()
    {
        //create a static parser object
        static FieldParser_EstimatedAngularRate p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_WGS84LocalGravMagnitude
    const InertialTypes::ChannelField FieldParser_WGS84LocalGravMagnitude::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_WGS84_LOC_GRAV_MAGNITUDE;
    const bool FieldParser_WGS84LocalGravMagnitude::REGISTERED = FieldParser_WGS84LocalGravMagnitude::registerParser();    //register the parser immediately

    void FieldParser_WGS84LocalGravMagnitude::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the gravity magnitude
        float gravityMagnitude = bytes.read_float();

        //get the flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool gravValid    = pointIsValid(flags, GRAV_FLAG);

        //create a data point and add it to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_MAGNITUDE, valueType_float, anyType(gravityMagnitude), gravValid));
    }

    bool FieldParser_WGS84LocalGravMagnitude::registerParser()
    {
        //create a static parser object
        static FieldParser_WGS84LocalGravMagnitude p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedAttQuaternUncertainty
    const InertialTypes::ChannelField FieldParser_EstimatedAttQuaternUncertainty::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_ATT_UNCERT_QUAT;
    const bool FieldParser_EstimatedAttQuaternUncertainty::REGISTERED = FieldParser_EstimatedAttQuaternUncertainty::registerParser();    //register the parser immediately

    void FieldParser_EstimatedAttQuaternUncertainty::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        //create a Vector to store as the data point
        Vector data(valueType_float, field.fieldData());

        //read the flags value
        const uint16 FLAG_BYTE_POS = 16;
        uint16 flags = field.fieldData().read_uint16(FLAG_BYTE_POS);

        //get whether points are valid or invalid from the flags
        bool valid    = pointIsValid(flags, UNCERT_FLAG);

        //create a data point and add it to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_QUATERNION, valueType_Vector, anyType(data), valid));
    }

    bool FieldParser_EstimatedAttQuaternUncertainty::registerParser()
    {
        //create a static parser object
        static FieldParser_EstimatedAttQuaternUncertainty p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedGravityVector
    const InertialTypes::ChannelField FieldParser_EstimatedGravityVector::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_GRAVITY_VECTOR;
    const bool FieldParser_EstimatedGravityVector::REGISTERED = FieldParser_EstimatedGravityVector::registerParser();    //register the parser immediately

    void FieldParser_EstimatedGravityVector::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, GRAV_FLAG);

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_EstimatedGravityVector::registerParser()
    {
        //create a static parser object
        static FieldParser_EstimatedGravityVector p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_HeadingUpdateSource
    const InertialTypes::ChannelField FieldParser_HeadingUpdateSource::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_HEADING_UPDATE_SOURCE;
    const bool FieldParser_HeadingUpdateSource::REGISTERED = FieldParser_HeadingUpdateSource::registerParser();    //register the parser immediately

    void FieldParser_HeadingUpdateSource::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the heading
        float heading = bytes.read_float();

        //get the uncertainty
        float headingUncertainty = bytes.read_float();

        //get the source
        uint16 source = bytes.read_uint16();

        //get the flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool headingValid    = pointIsValid(flags, HEADING_FLAG);

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_HEADING, valueType_float, anyType(heading), headingValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_HEADING_UNCERTAINTY, valueType_float, anyType(headingUncertainty), headingValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_SOURCE, valueType_uint16, anyType(source), headingValid));
    }

    bool FieldParser_HeadingUpdateSource::registerParser()
    {
        //create a static parser object
        static FieldParser_HeadingUpdateSource p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_MagneticModelSolution
    const InertialTypes::ChannelField FieldParser_MagneticModelSolution::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_MAGNETIC_MODEL_SLN;
    const bool FieldParser_MagneticModelSolution::REGISTERED = FieldParser_MagneticModelSolution::registerParser();    //register the parser immediately

    void FieldParser_MagneticModelSolution::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //read the data
        float north = bytes.read_float();
        float east = bytes.read_float();
        float down = bytes.read_float();
        float inclination = bytes.read_float();
        float declination = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid    = pointIsValid(flags, SLN_FLAG);

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_NORTH, valueType_float, anyType(north), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_EAST, valueType_float, anyType(east), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_DOWN, valueType_float, anyType(down), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_INCLINATION, valueType_float, anyType(inclination), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_DECLINATION, valueType_float, anyType(declination), valid));
    }

    bool FieldParser_MagneticModelSolution::registerParser()
    {
        //create a static parser object
        static FieldParser_MagneticModelSolution p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================


    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedGyroScaleFactor
    const InertialTypes::ChannelField FieldParser_EstimatedGyroScaleFactor::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_GYRO_SCALE_FACTOR;
    const bool FieldParser_EstimatedGyroScaleFactor::REGISTERED = FieldParser_EstimatedGyroScaleFactor::registerParser();    //register the parser immediately

    void FieldParser_EstimatedGyroScaleFactor::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //read the data
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, VALID_FLAG);

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_EstimatedGyroScaleFactor::registerParser()
    {
        //create a static parser object
        static FieldParser_EstimatedGyroScaleFactor p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedAccelScaleFactor
    const InertialTypes::ChannelField FieldParser_EstimatedAccelScaleFactor::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_ACCEL_SCALE_FACTOR;
    const bool FieldParser_EstimatedAccelScaleFactor::REGISTERED = FieldParser_EstimatedAccelScaleFactor::registerParser();    //register the parser immediately

    void FieldParser_EstimatedAccelScaleFactor::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //read the data
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, VALID_FLAG);

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_EstimatedAccelScaleFactor::registerParser()
    {
        //create a static parser object
        static FieldParser_EstimatedAccelScaleFactor p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedGyroScaleFactorUncertainty
    const InertialTypes::ChannelField FieldParser_EstimatedGyroScaleFactorUncertainty::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_GYRO_SCALE_FACTOR_UNCERT;
    const bool FieldParser_EstimatedGyroScaleFactorUncertainty::REGISTERED = FieldParser_EstimatedGyroScaleFactorUncertainty::registerParser();    //register the parser immediately

    void FieldParser_EstimatedGyroScaleFactorUncertainty::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //read the data
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, VALID_FLAG);

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_EstimatedGyroScaleFactorUncertainty::registerParser()
    {
        //create a static parser object
        static FieldParser_EstimatedGyroScaleFactorUncertainty p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedAccelScaleFactorUncertainty
    const InertialTypes::ChannelField FieldParser_EstimatedAccelScaleFactorUncertainty::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_ACCEL_SCALE_FACTOR_UNCERT;
    const bool FieldParser_EstimatedAccelScaleFactorUncertainty::REGISTERED = FieldParser_EstimatedAccelScaleFactorUncertainty::registerParser();    //register the parser immediately

    void FieldParser_EstimatedAccelScaleFactorUncertainty::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //read the data
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, VALID_FLAG);

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_EstimatedAccelScaleFactorUncertainty::registerParser()
    {
        //create a static parser object
        static FieldParser_EstimatedAccelScaleFactorUncertainty p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================


    //=====================================================================================================================================================
    //                                                        FieldParser_CompensatedAccel
    const InertialTypes::ChannelField FieldParser_CompensatedAccel::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_COMPENSATED_ACCEL;
    const bool FieldParser_CompensatedAccel::REGISTERED = FieldParser_CompensatedAccel::registerParser();    //register the parser immediately

    void FieldParser_CompensatedAccel::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //read the data
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, VALID_FLAG);

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_CompensatedAccel::registerParser()
    {
        //create a static parser object
        static FieldParser_CompensatedAccel p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================


    //=====================================================================================================================================================
    //                                                        FieldParser_StdAtmModel
    const InertialTypes::ChannelField FieldParser_StdAtmModel::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_STD_ATMOSPHERE_MODEL;
    const bool FieldParser_StdAtmModel::REGISTERED = FieldParser_StdAtmModel::registerParser();    //register the parser immediately

    void FieldParser_StdAtmModel::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //read the data
        float geometricAlt = bytes.read_float();
        float geopotentialAlt = bytes.read_float();
        float temperature = bytes.read_float();
        float pressure = bytes.read_float();
        float density = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, VALID_FLAG);

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_GEOMETRIC_ALTITUDE, valueType_float, anyType(geometricAlt), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_GEOPOTENTIAL_ALTITUDE, valueType_float, anyType(geopotentialAlt), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_TEMPERATURE, valueType_float, anyType(temperature), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_PRESSURE, valueType_float, anyType(pressure), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_DENSITY, valueType_float, anyType(density), valid));
    }

    bool FieldParser_StdAtmModel::registerParser()
    {
        //create a static parser object
        static FieldParser_StdAtmModel p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_PressureAlt
    const InertialTypes::ChannelField FieldParser_PressureAlt::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_PRESSURE_ALTITUDE;
    const bool FieldParser_PressureAlt::REGISTERED = FieldParser_PressureAlt::registerParser();    //register the parser immediately

    void FieldParser_PressureAlt::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //read the data
        float pressureAlt = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, VALID_FLAG);

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_ALTITUDE, valueType_float, anyType(pressureAlt), valid));
    }

    bool FieldParser_PressureAlt::registerParser()
    {
        //create a static parser object
        static FieldParser_PressureAlt p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================


    //=====================================================================================================================================================
    //                                                        FieldParser_GpsAntennaOffsetCorrection
    const InertialTypes::ChannelField FieldParser_GpsAntennaOffsetCorrection::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_GPS_ANTENNA_CORRECTION;
    const bool FieldParser_GpsAntennaOffsetCorrection::REGISTERED = FieldParser_GpsAntennaOffsetCorrection::registerParser();    //register the parser immediately

    void FieldParser_GpsAntennaOffsetCorrection::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //read the data
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, VALID_FLAG);

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_GpsAntennaOffsetCorrection::registerParser()
    {
        //create a static parser object
        static FieldParser_GpsAntennaOffsetCorrection p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_GpsAntennaOffsetCorrectionUncert
    const InertialTypes::ChannelField FieldParser_GpsAntennaOffsetCorrectionUncert::FIELD_TYPE = InertialTypes::CH_FIELD_ESTFILTER_GPS_ANTENNA_CORRECTION_UNCERT;
    const bool FieldParser_GpsAntennaOffsetCorrectionUncert::REGISTERED = FieldParser_GpsAntennaOffsetCorrectionUncert::registerParser();    //register the parser immediately

    void FieldParser_GpsAntennaOffsetCorrectionUncert::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //read the data
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, VALID_FLAG);

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_GpsAntennaOffsetCorrectionUncert::registerParser()
    {
        //create a static parser object
        static FieldParser_GpsAntennaOffsetCorrectionUncert p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================
}