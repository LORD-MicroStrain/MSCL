/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Inertial/Packets/InertialFieldParser_EstFilter.h"

#include "mscl/MicroStrain/MIP/MipDataField.h"

namespace mscl
{
    //the classes in this file do not get referenced anywhere, therefore, the
    //linker will not include this compilation unit when statically
    //linking to an executable. Defining this variable, and then using it
    //elsewhere, will force this file to be included
    bool _forceLibraryToIncludeCompilationUnit_NAV;

    //=====================================================================================================================================================
    //                                                        FieldParser_FilterStatus
    const MipTypes::ChannelField FieldParser_FilterStatus::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_FILTER_STATUS;
    const bool FieldParser_FilterStatus::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_FilterStatus::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the filter state
        uint16 filterState = bytes.read_uint16();

        //get the dynamics mode
        uint16 dynamicsMode = bytes.read_uint16();

        //get the status flags
        uint16 statusFlags = bytes.read_uint16();

        //add all the data points we just collected
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_FILTER_STATE, valueType_uint16, anyType(filterState)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_DYNAMICS_MODE, valueType_uint16, anyType(dynamicsMode)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_FLAGS, valueType_uint16, anyType(statusFlags)));
    }

    bool FieldParser_FilterStatus::registerParser()
    {
        static FieldParser_FilterStatus p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_NAV_GPS_Timestamp
    const MipTypes::ChannelField FieldParser_NAV_GPS_Timestamp::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_GPS_TIMESTAMP;
    const bool FieldParser_NAV_GPS_Timestamp::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_NAV_GPS_Timestamp::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_TIME_OF_WEEK, valueType_double, anyType(timeOfWeek), timeValid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_WEEK_NUMBER, valueType_uint16, anyType(weekNumber), timeValid));
    }

    bool FieldParser_NAV_GPS_Timestamp::registerParser()
    {
        static FieldParser_NAV_GPS_Timestamp p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedLLHPosition
    const MipTypes::ChannelField FieldParser_EstimatedLLHPosition::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_LLH_POS;
    const bool FieldParser_EstimatedLLHPosition::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_EstimatedLLHPosition::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_LATITUDE, valueType_double, anyType(latitude), latLongValid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_LONGITUDE, valueType_double, anyType(longitude), latLongValid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_HEIGHT_ABOVE_ELLIPSOID, valueType_double, anyType(heightAboveEllipsoid), latLongValid));
    }

    bool FieldParser_EstimatedLLHPosition::registerParser()
    {
        static FieldParser_EstimatedLLHPosition p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedNEDVelocity
    const MipTypes::ChannelField FieldParser_EstimatedNEDVelocity::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_NED_VELOCITY;
    const bool FieldParser_EstimatedNEDVelocity::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_EstimatedNEDVelocity::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_NORTH, valueType_float, anyType(north), nedValid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_EAST, valueType_float, anyType(east), nedValid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_DOWN, valueType_float, anyType(down), nedValid));
    }

    bool FieldParser_EstimatedNEDVelocity::registerParser()
    {
        static FieldParser_EstimatedNEDVelocity p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedQuaternion
    const MipTypes::ChannelField FieldParser_EstimatedQuaternion::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_QUATERNION;
    const bool FieldParser_EstimatedQuaternion::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_EstimatedQuaternion::parse(const MipDataField& field, MipDataPoints& result) const
    {
        //create a Vector to store as the data point
        Vector data(valueType_float, field.fieldData());

        //read the flags value
        const uint16 FLAG_BYTE_POS = 16;
        uint16 flags = field.fieldData().read_uint16(FLAG_BYTE_POS);

        //get whether points are valid or invalid from the flags
        bool valid    = pointIsValid(flags, QUATERNION_FLAG);

        //create a data point and add it to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_QUATERNION, valueType_Vector, anyType(data), valid));
    }

    bool FieldParser_EstimatedQuaternion::registerParser()
    {
        static FieldParser_EstimatedQuaternion p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedMatrix
    const MipTypes::ChannelField FieldParser_EstimatedMatrix::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_MATRIX;
    const bool FieldParser_EstimatedMatrix::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_EstimatedMatrix::parse(const MipDataField& field, MipDataPoints& result) const
    {
        //create a Matrix to store as the data point
        Matrix data(3, 3, valueType_float, field.fieldData());

        //read the flags value
        const uint16 FLAG_BYTE_POS = 36;
        uint16 flags = field.fieldData().read_uint16(FLAG_BYTE_POS);

        //get whether points are valid or invalid from the flags
        bool valid    = pointIsValid(flags, MATRIX_FLAG);

        //create a Matrix object with the Orientation Matrix data and create a MipDataPoint from it
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_MATRIX, valueType_Matrix, anyType(data), valid));
    }

    bool FieldParser_EstimatedMatrix::registerParser()
    {
        static FieldParser_EstimatedMatrix p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedEulerAngles
    const MipTypes::ChannelField FieldParser_EstimatedEulerAngles::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_EULER;
    const bool FieldParser_EstimatedEulerAngles::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_EstimatedEulerAngles::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_ROLL, valueType_float, anyType(roll), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_PITCH, valueType_float, anyType(pitch), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_YAW, valueType_float, anyType(yaw), valid));
    }

    bool FieldParser_EstimatedEulerAngles::registerParser()
    {
        static FieldParser_EstimatedEulerAngles p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedGyroBias
    const MipTypes::ChannelField FieldParser_EstimatedGyroBias::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS;
    const bool FieldParser_EstimatedGyroBias::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_EstimatedGyroBias::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_EstimatedGyroBias::registerParser()
    {
        static FieldParser_EstimatedGyroBias p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedAccelBias
    const MipTypes::ChannelField FieldParser_EstimatedAccelBias::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS;
    const bool FieldParser_EstimatedAccelBias::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_EstimatedAccelBias::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_EstimatedAccelBias::registerParser()
    {
        static FieldParser_EstimatedAccelBias p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedLLHPosUncertainty
    const MipTypes::ChannelField FieldParser_EstimatedLLHPosUncertainty::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_LLH_UNCERT;
    const bool FieldParser_EstimatedLLHPosUncertainty::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_EstimatedLLHPosUncertainty::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_NORTH, valueType_float, anyType(north), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_EAST, valueType_float, anyType(east), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_DOWN, valueType_float, anyType(down), valid));
    }

    bool FieldParser_EstimatedLLHPosUncertainty::registerParser()
    {
        static FieldParser_EstimatedLLHPosUncertainty p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedNEDUncertainty
    const MipTypes::ChannelField FieldParser_EstimatedNEDUncertainty::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_NED_UNCERT;
    const bool FieldParser_EstimatedNEDUncertainty::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_EstimatedNEDUncertainty::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_NORTH, valueType_float, anyType(north), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_EAST, valueType_float, anyType(east), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_DOWN, valueType_float, anyType(down), valid));
    }

    bool FieldParser_EstimatedNEDUncertainty::registerParser()
    {
        static FieldParser_EstimatedNEDUncertainty p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedAttEulerUncertainty
    const MipTypes::ChannelField FieldParser_EstimatedAttEulerUncertainty::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ATT_UNCERT_EULER;
    const bool FieldParser_EstimatedAttEulerUncertainty::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_EstimatedAttEulerUncertainty::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_ROLL, valueType_float, anyType(roll), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_PITCH, valueType_float, anyType(pitch), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_YAW, valueType_float, anyType(yaw), valid));
    }

    bool FieldParser_EstimatedAttEulerUncertainty::registerParser()
    {
        static FieldParser_EstimatedAttEulerUncertainty p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedGyroBiasUncertainty
    const MipTypes::ChannelField FieldParser_EstimatedGyroBiasUncertainty::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS_UNCERT;
    const bool FieldParser_EstimatedGyroBiasUncertainty::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_EstimatedGyroBiasUncertainty::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_EstimatedGyroBiasUncertainty::registerParser()
    {
        static FieldParser_EstimatedGyroBiasUncertainty p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedAccelBiasUncertainty
    const MipTypes::ChannelField FieldParser_EstimatedAccelBiasUncertainty::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS_UNCERT;
    const bool FieldParser_EstimatedAccelBiasUncertainty::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_EstimatedAccelBiasUncertainty::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_EstimatedAccelBiasUncertainty::registerParser()
    {
        static FieldParser_EstimatedAccelBiasUncertainty p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedLinearAccel
    const MipTypes::ChannelField FieldParser_EstimatedLinearAccel::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_LINEAR_ACCEL;
    const bool FieldParser_EstimatedLinearAccel::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_EstimatedLinearAccel::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_EstimatedLinearAccel::registerParser()
    {
        static FieldParser_EstimatedLinearAccel p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedAngularRate
    const MipTypes::ChannelField FieldParser_EstimatedAngularRate::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ANGULAR_RATE;
    const bool FieldParser_EstimatedAngularRate::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_EstimatedAngularRate::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_EstimatedAngularRate::registerParser()
    {
        static FieldParser_EstimatedAngularRate p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_WGS84LocalGravMagnitude
    const MipTypes::ChannelField FieldParser_WGS84LocalGravMagnitude::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_WGS84_LOC_GRAV_MAGNITUDE;
    const bool FieldParser_WGS84LocalGravMagnitude::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_WGS84LocalGravMagnitude::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the gravity magnitude
        float gravityMagnitude = bytes.read_float();

        //get the flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool gravValid    = pointIsValid(flags, GRAV_FLAG);

        //create a data point and add it to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_MAGNITUDE, valueType_float, anyType(gravityMagnitude), gravValid));
    }

    bool FieldParser_WGS84LocalGravMagnitude::registerParser()
    {
        static FieldParser_WGS84LocalGravMagnitude p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedAttQuaternUncertainty
    const MipTypes::ChannelField FieldParser_EstimatedAttQuaternUncertainty::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ATT_UNCERT_QUAT;
    const bool FieldParser_EstimatedAttQuaternUncertainty::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_EstimatedAttQuaternUncertainty::parse(const MipDataField& field, MipDataPoints& result) const
    {
        //create a Vector to store as the data point
        Vector data(valueType_float, field.fieldData());

        //read the flags value
        const uint16 FLAG_BYTE_POS = 16;
        uint16 flags = field.fieldData().read_uint16(FLAG_BYTE_POS);

        //get whether points are valid or invalid from the flags
        bool valid    = pointIsValid(flags, UNCERT_FLAG);

        //create a data point and add it to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_QUATERNION, valueType_Vector, anyType(data), valid));
    }

    bool FieldParser_EstimatedAttQuaternUncertainty::registerParser()
    {
        static FieldParser_EstimatedAttQuaternUncertainty p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedGravityVector
    const MipTypes::ChannelField FieldParser_EstimatedGravityVector::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_GRAVITY_VECTOR;
    const bool FieldParser_EstimatedGravityVector::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_EstimatedGravityVector::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_EstimatedGravityVector::registerParser()
    {
        static FieldParser_EstimatedGravityVector p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_HeadingUpdateSource
    const MipTypes::ChannelField FieldParser_HeadingUpdateSource::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_HEADING_UPDATE_SOURCE;
    const bool FieldParser_HeadingUpdateSource::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_HeadingUpdateSource::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_HEADING, valueType_float, anyType(heading), headingValid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_HEADING_UNCERTAINTY, valueType_float, anyType(headingUncertainty), headingValid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_SOURCE, valueType_uint16, anyType(source), headingValid));
    }

    bool FieldParser_HeadingUpdateSource::registerParser()
    {
        static FieldParser_HeadingUpdateSource p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_MagneticModelSolution
    const MipTypes::ChannelField FieldParser_MagneticModelSolution::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_MAGNETIC_MODEL_SLN;
    const bool FieldParser_MagneticModelSolution::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_MagneticModelSolution::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_NORTH, valueType_float, anyType(north), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_EAST, valueType_float, anyType(east), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_DOWN, valueType_float, anyType(down), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_INCLINATION, valueType_float, anyType(inclination), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_DECLINATION, valueType_float, anyType(declination), valid));
    }

    bool FieldParser_MagneticModelSolution::registerParser()
    {
        static FieldParser_MagneticModelSolution p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedGyroScaleFactor
    const MipTypes::ChannelField FieldParser_EstimatedGyroScaleFactor::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_GYRO_SCALE_FACTOR;
    const bool FieldParser_EstimatedGyroScaleFactor::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_EstimatedGyroScaleFactor::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_EstimatedGyroScaleFactor::registerParser()
    {
        static FieldParser_EstimatedGyroScaleFactor p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedAccelScaleFactor
    const MipTypes::ChannelField FieldParser_EstimatedAccelScaleFactor::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_ACCEL_SCALE_FACTOR;
    const bool FieldParser_EstimatedAccelScaleFactor::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_EstimatedAccelScaleFactor::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_EstimatedAccelScaleFactor::registerParser()
    {
        static FieldParser_EstimatedAccelScaleFactor p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedGyroScaleFactorUncertainty
    const MipTypes::ChannelField FieldParser_EstimatedGyroScaleFactorUncertainty::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_GYRO_SCALE_FACTOR_UNCERT;
    const bool FieldParser_EstimatedGyroScaleFactorUncertainty::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_EstimatedGyroScaleFactorUncertainty::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_EstimatedGyroScaleFactorUncertainty::registerParser()
    {
        static FieldParser_EstimatedGyroScaleFactorUncertainty p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_EstimatedAccelScaleFactorUncertainty
    const MipTypes::ChannelField FieldParser_EstimatedAccelScaleFactorUncertainty::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_ACCEL_SCALE_FACTOR_UNCERT;
    const bool FieldParser_EstimatedAccelScaleFactorUncertainty::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_EstimatedAccelScaleFactorUncertainty::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_EstimatedAccelScaleFactorUncertainty::registerParser()
    {
        static FieldParser_EstimatedAccelScaleFactorUncertainty p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_MagBias
    const MipTypes::ChannelField FieldParser_MagBias::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_MAG_BIAS;
    const bool FieldParser_MagBias::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_MagBias::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, VALID_FLAG);

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_MagBias::registerParser()
    {
        static FieldParser_MagBias p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_CompensatedAccel
    const MipTypes::ChannelField FieldParser_CompensatedAccel::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_COMPENSATED_ACCEL;
    const bool FieldParser_CompensatedAccel::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_CompensatedAccel::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_CompensatedAccel::registerParser()
    {
        static FieldParser_CompensatedAccel p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_StdAtmModel
    const MipTypes::ChannelField FieldParser_StdAtmModel::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_STD_ATMOSPHERE_MODEL;
    const bool FieldParser_StdAtmModel::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_StdAtmModel::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_GEOMETRIC_ALTITUDE, valueType_float, anyType(geometricAlt), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_GEOPOTENTIAL_ALTITUDE, valueType_float, anyType(geopotentialAlt), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_TEMPERATURE, valueType_float, anyType(temperature), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_PRESSURE, valueType_float, anyType(pressure), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_DENSITY, valueType_float, anyType(density), valid));
    }

    bool FieldParser_StdAtmModel::registerParser()
    {
        static FieldParser_StdAtmModel p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_PressureAlt
    const MipTypes::ChannelField FieldParser_PressureAlt::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_PRESSURE_ALTITUDE;
    const bool FieldParser_PressureAlt::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_PressureAlt::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //read the data
        float pressureAlt = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, VALID_FLAG);

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_ALTITUDE, valueType_float, anyType(pressureAlt), valid));
    }

    bool FieldParser_PressureAlt::registerParser()
    {
        static FieldParser_PressureAlt p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_MagAutoHardIronOffset
    const MipTypes::ChannelField FieldParser_MagAutoHardIronOffset::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_MAG_AUTO_HARD_IRON_OFFSET;
    const bool FieldParser_MagAutoHardIronOffset::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_MagAutoHardIronOffset::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, VECTOR_FLAG);

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_MagAutoHardIronOffset::registerParser()
    {
        static FieldParser_MagAutoHardIronOffset p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_MagAutoSoftIronMatrix
    const MipTypes::ChannelField FieldParser_MagAutoSoftIronMatrix::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_MAG_AUTO_SOFT_IRON_MATRIX;
    const bool FieldParser_MagAutoSoftIronMatrix::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_MagAutoSoftIronMatrix::parse(const MipDataField& field, MipDataPoints& result) const
    {
        //create a Matrix to store as the data point
        Matrix data(3, 3, valueType_float, field.fieldData());

        //read the flags value
        const uint16 FLAG_BYTE_POS = 36;
        uint16 flags = field.fieldData().read_uint16(FLAG_BYTE_POS);

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, MATRIX_FLAG);

        //create a Matrix object with the Orientation Matrix data and create a MipDataPoint from it
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_MATRIX, valueType_Matrix, anyType(data), valid));
    }

    bool FieldParser_MagAutoSoftIronMatrix::registerParser()
    {
        static FieldParser_MagAutoSoftIronMatrix p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_MagAutoHardIronOffsetUncert
    const MipTypes::ChannelField FieldParser_MagAutoHardIronOffsetUncert::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_MAG_AUTO_HARD_IRON_OFFSET_UNCERT;
    const bool FieldParser_MagAutoHardIronOffsetUncert::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_MagAutoHardIronOffsetUncert::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, VECTOR_FLAG);

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_MagAutoHardIronOffsetUncert::registerParser()
    {
        static FieldParser_MagAutoHardIronOffsetUncert p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_MagBiasUncert
    const MipTypes::ChannelField FieldParser_MagBiasUncert::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_MAG_BIAS_UNCERT;
    const bool FieldParser_MagBiasUncert::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_MagBiasUncert::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, VALID_FLAG);

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_MagBiasUncert::registerParser()
    {
        static FieldParser_MagBiasUncert p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_MagAutoSoftIronMatrixUncert
    const MipTypes::ChannelField FieldParser_MagAutoSoftIronMatrixUncert::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_MAG_AUTO_SOFT_IRON_MATRIX_UNCERT;
    const bool FieldParser_MagAutoSoftIronMatrixUncert::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_MagAutoSoftIronMatrixUncert::parse(const MipDataField& field, MipDataPoints& result) const
    {
        //create a Matrix to store as the data point
        Matrix data(3, 3, valueType_float, field.fieldData());

        //read the flags value
        const uint16 FLAG_BYTE_POS = 36;
        uint16 flags = field.fieldData().read_uint16(FLAG_BYTE_POS);

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, MATRIX_FLAG);

        //create a Matrix object with the Orientation Matrix data and create a MipDataPoint from it
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_MATRIX, valueType_Matrix, anyType(data), valid));
    }

    bool FieldParser_MagAutoSoftIronMatrixUncert::registerParser()
    {
        static FieldParser_MagAutoSoftIronMatrixUncert p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_MagCovarianceMatrix
    const MipTypes::ChannelField FieldParser_MagCovarianceMatrix::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_MAG_COVARIANCE_MATRIX;
    const bool FieldParser_MagCovarianceMatrix::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_MagCovarianceMatrix::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());
        ByteStream mat;
        for (uint8 i = 0; i < 9; i++)
        {
            mat.append_float(bytes.read_float());
        }
        //create a Matrix to store as the data point
        Matrix data(3, 3, valueType_float, mat);

        //read the flags value
        bool valid = bytes.read_uint16() > 0;

        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_MATRIX, valueType_Matrix, anyType(data), valid));
    }

    bool FieldParser_MagCovarianceMatrix::registerParser()
    {
        static FieldParser_MagCovarianceMatrix p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_MagResidualVector
    const MipTypes::ChannelField FieldParser_MagResidualVector::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_MAG_RESIDUAL_VECTOR;
    const bool FieldParser_MagResidualVector::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_MagResidualVector::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //read the flags value
        bool valid = bytes.read_uint16() > 0;

        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_MagResidualVector::registerParser()
    {
        static FieldParser_MagResidualVector p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_GnssAntennaOffsetCorrection
    const MipTypes::ChannelField FieldParser_GnssAntennaOffsetCorrection::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION;
    const bool FieldParser_GnssAntennaOffsetCorrection::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_GnssAntennaOffsetCorrection::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_GnssAntennaOffsetCorrection::registerParser()
    {
        static FieldParser_GnssAntennaOffsetCorrection p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_GnssAntennaOffsetCorrectionUncert
    const MipTypes::ChannelField FieldParser_GnssAntennaOffsetCorrectionUncert::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION_UNCERT;
    const bool FieldParser_GnssAntennaOffsetCorrectionUncert::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_GnssAntennaOffsetCorrectionUncert::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_GnssAntennaOffsetCorrectionUncert::registerParser()
    {
        static FieldParser_GnssAntennaOffsetCorrectionUncert p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_GnssClockCorrection
    const MipTypes::ChannelField FieldParser_GnssClockCorrection::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_GNSS_CLOCK_CORRECTION;
    const bool FieldParser_GnssClockCorrection::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_GnssClockCorrection::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //read the data
        uint8 receiver = bytes.read_uint8();
        float bias = bytes.read_float();
        float biasDrift = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, VALID_FLAG);

        // additional identifiers
        MipChannelIdentifiers addlIds = {
            MipChannelIdentifier(MipChannelIdentifier::Type::GNSS_RECEIVER_ID, receiver)
        };

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_BIAS, addlIds, valueType_float, anyType(bias), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_DRIFT, addlIds, valueType_float, anyType(biasDrift), valid));
    }

    bool FieldParser_GnssClockCorrection::registerParser()
    {
        static FieldParser_GnssClockCorrection p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_GnssClockCorrectionUncert
    const MipTypes::ChannelField FieldParser_GnssClockCorrectionUncert::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_GNSS_CLOCK_CORRECTION_UNCERT;
    const bool FieldParser_GnssClockCorrectionUncert::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_GnssClockCorrectionUncert::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //read the data
        uint8 receiver = bytes.read_uint8();
        float bias = bytes.read_float();
        float biasDrift = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, VALID_FLAG);

        // additional identifiers
        MipChannelIdentifiers addlIds = {
            MipChannelIdentifier(MipChannelIdentifier::Type::GNSS_RECEIVER_ID, receiver)
        };

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_BIAS, addlIds, valueType_float, anyType(bias), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_DRIFT, addlIds, valueType_float, anyType(biasDrift), valid));
    }

    bool FieldParser_GnssClockCorrectionUncert::registerParser()
    {
        static FieldParser_GnssClockCorrectionUncert p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_GnssMultiAntennaOffsetCorrection
    const MipTypes::ChannelField FieldParser_GnssMultiAntennaOffsetCorrection::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_GNSS_MULTI_ANTENNA_CORRECTION;
    const bool FieldParser_GnssMultiAntennaOffsetCorrection::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_GnssMultiAntennaOffsetCorrection::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //read the data
        uint8 receiver = bytes.read_uint8();
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, VALID_FLAG);

        // additional identifiers
        MipChannelIdentifiers addlIds = {
            MipChannelIdentifier(MipChannelIdentifier::Type::GNSS_RECEIVER_ID, receiver)
        };

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, addlIds, valueType_float, anyType(x), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, addlIds, valueType_float, anyType(y), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, addlIds, valueType_float, anyType(z), valid));
    }

    bool FieldParser_GnssMultiAntennaOffsetCorrection::registerParser()
    {
        static FieldParser_GnssMultiAntennaOffsetCorrection p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_GnssMultiAntennaOffsetCorrectionUncert
    const MipTypes::ChannelField FieldParser_GnssMultiAntennaOffsetCorrectionUncert::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_GNSS_MULTI_ANTENNA_CORRECTION_UNCERT;
    const bool FieldParser_GnssMultiAntennaOffsetCorrectionUncert::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_GnssMultiAntennaOffsetCorrectionUncert::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //read the data
        uint8 receiver = bytes.read_uint8();
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, VALID_FLAG);

        // additional identifiers
        MipChannelIdentifiers addlIds = {
            MipChannelIdentifier(MipChannelIdentifier::Type::GNSS_RECEIVER_ID, receiver)
        };

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, addlIds, valueType_float, anyType(x), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, addlIds, valueType_float, anyType(y), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, addlIds, valueType_float, anyType(z), valid));
    }

    bool FieldParser_GnssMultiAntennaOffsetCorrectionUncert::registerParser()
    {
        static FieldParser_GnssMultiAntennaOffsetCorrectionUncert p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_EcefPositionUncert
    const MipTypes::ChannelField FieldParser_EcefPositionUncert::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_ECEF_POS_UNCERT;
    const bool FieldParser_EcefPositionUncert::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_EcefPositionUncert::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_EcefPositionUncert::registerParser()
    {
        static FieldParser_EcefPositionUncert p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_EcefVelocityUncert
    const MipTypes::ChannelField FieldParser_EcefVelocityUncert::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_ECEF_VEL_UNCERT;
    const bool FieldParser_EcefVelocityUncert::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_EcefVelocityUncert::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_EcefVelocityUncert::registerParser()
    {
        static FieldParser_EcefVelocityUncert p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_EcefPosition
    const MipTypes::ChannelField FieldParser_EcefPosition::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_ECEF_POS;
    const bool FieldParser_EcefPosition::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_EcefPosition::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //read the data
        double x = bytes.read_double();
        double y = bytes.read_double();
        double z = bytes.read_double();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, VALID_FLAG);

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_double, anyType(x), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_double, anyType(y), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_double, anyType(z), valid));
    }

    bool FieldParser_EcefPosition::registerParser()
    {
        static FieldParser_EcefPosition p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_EcefVelocity
    const MipTypes::ChannelField FieldParser_EcefVelocity::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_ECEF_VEL;
    const bool FieldParser_EcefVelocity::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_EcefVelocity::parse(const MipDataField& field, MipDataPoints& result) const
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
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z), valid));
    }

    bool FieldParser_EcefVelocity::registerParser()
    {
        static FieldParser_EcefVelocity p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_NedRelativePos
    const MipTypes::ChannelField FieldParser_NedRelativePos::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_NED_RELATIVE_POS;
    const bool FieldParser_NedRelativePos::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_NedRelativePos::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //read the data
        double x = bytes.read_double();
        double y = bytes.read_double();
        double z = bytes.read_double();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(flags, VALID_FLAG);

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_double, anyType(x), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_double, anyType(y), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_double, anyType(z), valid));
    }

    bool FieldParser_NedRelativePos::registerParser()
    {
        static FieldParser_NedRelativePos p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_FilterPosAidingStatus
    const MipTypes::ChannelField FieldParser_FilterPosAidingStatus::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_POSITION_AIDING_STATUS;
    const bool FieldParser_FilterPosAidingStatus::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_FilterPosAidingStatus::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //read the data
        uint8 recId = bytes.read_uint8();
        float tow = bytes.read_float();
        uint16 status = bytes.read_uint16();

        //additional identifiers
        MipChannelIdentifiers addlIds = {
            MipChannelIdentifier(MipChannelIdentifier::Type::GNSS_RECEIVER_ID, recId)
        };

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_TIME_OF_WEEK, addlIds, valueType_float, anyType(tow)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_STATUS, addlIds, valueType_uint16, anyType(status)));
    }

    bool FieldParser_FilterPosAidingStatus::registerParser()
    {
        static FieldParser_FilterPosAidingStatus p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_FilterAttAidingStatus
    const MipTypes::ChannelField FieldParser_FilterAttAidingStatus::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_ATTITUDE_AIDING_STATUS;
    const bool FieldParser_FilterAttAidingStatus::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_FilterAttAidingStatus::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //read the data
        float tow = bytes.read_float();
        uint16 status = bytes.read_uint16();

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_TIME_OF_WEEK, valueType_float, anyType(tow)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_STATUS, valueType_uint16, anyType(status)));
    }

    bool FieldParser_FilterAttAidingStatus::registerParser()
    {
        static FieldParser_FilterAttAidingStatus p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_FilterAidingSummary
    const MipTypes::ChannelField FieldParser_FilterAidingSummary::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_AIDING_MEASURE_SUMMARY;
    const bool FieldParser_FilterAidingSummary::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_FilterAidingSummary::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //read the data
        float tow = bytes.read_float();
        uint8 source = bytes.read_uint8();
        uint8 type = bytes.read_uint8();
        uint8 status = bytes.read_uint8();

        //additional identifiers
        MipChannelIdentifiers addlIds = {
          MipChannelIdentifier(MipChannelIdentifier::Type::AIDING_MEASUREMENT_TYPE, type, source)
        };

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_TIME_OF_WEEK, addlIds, valueType_float, anyType(tow)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_STATUS, addlIds, valueType_uint8, anyType(status)));
    }

    bool FieldParser_FilterAidingSummary::registerParser()
    {
        static FieldParser_FilterAidingSummary p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_OdometerScaleError
    const MipTypes::ChannelField FieldParser_OdometerScaleError::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_ODOMETER_SCALE_FACTOR_ERROR;
    const bool FieldParser_OdometerScaleError::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_OdometerScaleError::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //read the data
        float error = bytes.read_float();
        bool valid = bytes.read_uint16() > 0;

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_ERROR, valueType_float, anyType(error), valid));
    }

    bool FieldParser_OdometerScaleError::registerParser()
    {
        static FieldParser_OdometerScaleError p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_OdometerScaleErrorUncert
    const MipTypes::ChannelField FieldParser_OdometerScaleErrorUncert::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_ODOMETER_SCALE_FACTOR_ERROR_UNCERT;
    const bool FieldParser_OdometerScaleErrorUncert::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_OdometerScaleErrorUncert::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //read the data
        float unc = bytes.read_float();
        bool valid = bytes.read_uint16() > 0;

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_ERROR_UNC, valueType_float, anyType(unc), valid));
    }

    bool FieldParser_OdometerScaleErrorUncert::registerParser()
    {
        static FieldParser_OdometerScaleErrorUncert p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_DualAntennaStatus
    const MipTypes::ChannelField FieldParser_DualAntennaStatus::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_GNSS_DUAL_ANTENNA_STATUS;
    const bool FieldParser_DualAntennaStatus::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_DualAntennaStatus::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //read the data
        float tow = bytes.read_float();
        float heading = bytes.read_float();
        float headingUnc = bytes.read_float();
        uint8 fixType = bytes.read_uint8();
        uint16 status = bytes.read_uint16();
        bool valid = bytes.read_uint16() > 0;

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_TIME_OF_WEEK, valueType_float, anyType(tow), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_HEADING, valueType_float, anyType(heading), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_HEADING_UNCERTAINTY, valueType_float, anyType(headingUnc), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_FIX_TYPE, valueType_uint8, anyType(fixType), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_STATUS, valueType_uint16, anyType(status), valid));
    }

    bool FieldParser_DualAntennaStatus::registerParser()
    {
        static FieldParser_DualAntennaStatus p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_FrameConfigError
    const MipTypes::ChannelField FieldParser_FrameConfigError::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_FRAME_CONFIG_ERROR;
    const bool FieldParser_FrameConfigError::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_FrameConfigError::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //read the data
        uint8 frameId = bytes.read_uint8();

        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        Bytes remaining = bytes.bytesToRead();
        Vector quat(valueType_float, ByteStream(remaining));

        // additional identifiers
        MipChannelIdentifiers addlIds = {
            MipChannelIdentifier(MipChannelIdentifier::Type::AIDING_MEASUREMENT_FRAME_ID, frameId)
        };

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, addlIds, valueType_float, anyType(x)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, addlIds, valueType_float, anyType(y)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, addlIds, valueType_float, anyType(z)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_QUATERNION, addlIds, valueType_Vector, anyType(quat)));
    }

    bool FieldParser_FrameConfigError::registerParser()
    {
        static FieldParser_FrameConfigError p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_FrameConfigErrorUnc
    const MipTypes::ChannelField FieldParser_FrameConfigErrorUnc::FIELD_TYPE = MipTypes::CH_FIELD_ESTFILTER_FRAME_CONFIG_ERROR_UNCERT;
    const bool FieldParser_FrameConfigErrorUnc::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_FrameConfigErrorUnc::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //read the data
        uint8 frameId = bytes.read_uint8();

        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        float roll = bytes.read_float();
        float pitch = bytes.read_float();
        float yaw = bytes.read_float();

        Bytes remaining = bytes.bytesToRead();
        Vector quat(valueType_float, ByteStream(remaining));

        // additional identifiers
        MipChannelIdentifiers addlIds = {
            MipChannelIdentifier(MipChannelIdentifier::Type::AIDING_MEASUREMENT_FRAME_ID, frameId)
        };

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, addlIds, valueType_float, anyType(x)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, addlIds, valueType_float, anyType(y)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, addlIds, valueType_float, anyType(z)));

        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_ROLL, addlIds, valueType_float, anyType(roll)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_PITCH, addlIds, valueType_float, anyType(pitch)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_YAW, addlIds, valueType_float, anyType(yaw)));
    }

    bool FieldParser_FrameConfigErrorUnc::registerParser()
    {
        static FieldParser_FrameConfigErrorUnc p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================
} // namespace mscl
