/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "InertialFieldParser_Sensor.h"

#include <boost/date_time/posix_time/ptime.hpp>

#include "InertialDataPacket.h"
#include "mscl/MicroStrain/DataBuffer.h"
#include "mscl/MicroStrain/Vector.h"
#include "mscl/MicroStrain/Matrix.h"
#include "mscl/Timestamp.h"
#include "mscl/TimeSpan.h"
#include "mscl/Types.h"

namespace mscl
{
    //the classes in this file do not get referenced anywhere, therefore the 
    //linker will not include this compilation unit when statically 
    //linking to an executable. Defining this variable, and then using it
    //elsewhere, will force this file to be included
    bool _forceLibraryToIncludeCompilationUnit_AHRS;

    //=====================================================================================================================================================
    //                                                        FieldParser_RawAccelVector
    const InertialTypes::ChannelField FieldParser_RawAccelVector::FIELD_TYPE = InertialTypes::CH_FIELD_SENSOR_RAW_ACCEL_VEC;
    const bool FieldParser_RawAccelVector::REGISTERED = FieldParser_RawAccelVector::registerParser();    //register the parser immediately

    void FieldParser_RawAccelVector::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_X, valueType_float, anyType(x), true));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Y, valueType_float, anyType(y), true));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Z, valueType_float, anyType(z), true));
    }

    bool FieldParser_RawAccelVector::registerParser()
    {
        //create a static parser object
        static FieldParser_RawAccelVector p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_RawGyroVector
    const InertialTypes::ChannelField FieldParser_RawGyroVector::FIELD_TYPE = InertialTypes::CH_FIELD_SENSOR_RAW_GYRO_VEC;
    const bool FieldParser_RawGyroVector::REGISTERED = FieldParser_RawGyroVector::registerParser();    //register the parser immediately

    void FieldParser_RawGyroVector::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_X, valueType_float, anyType(x), true));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Y, valueType_float, anyType(y), true));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Z, valueType_float, anyType(z), true));
    }

    bool FieldParser_RawGyroVector::registerParser()
    {
        //create a static parser object
        static FieldParser_RawGyroVector p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_RawMagVector
    const InertialTypes::ChannelField FieldParser_RawMagVector::FIELD_TYPE = InertialTypes::CH_FIELD_SENSOR_RAW_MAG_VEC;
    const bool FieldParser_RawMagVector::REGISTERED = FieldParser_RawMagVector::registerParser();    //register the parser immediately

    void FieldParser_RawMagVector::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_X, valueType_float, anyType(x), true));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Y, valueType_float, anyType(y), true));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Z, valueType_float, anyType(z), true));
    }

    bool FieldParser_RawMagVector::registerParser()
    {
        //create a static parser object
        static FieldParser_RawMagVector p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_ScaledAccelVector
    const InertialTypes::ChannelField FieldParser_ScaledAccelVector::FIELD_TYPE = InertialTypes::CH_FIELD_SENSOR_SCALED_ACCEL_VEC;
    const bool FieldParser_ScaledAccelVector::REGISTERED = FieldParser_ScaledAccelVector::registerParser();    //register the parser immediately

    void FieldParser_ScaledAccelVector::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_X, valueType_float, anyType(x), true));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Y, valueType_float, anyType(y), true));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Z, valueType_float, anyType(z), true));
    }

    bool FieldParser_ScaledAccelVector::registerParser()
    {
        //create a static parser object
        static FieldParser_ScaledAccelVector p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_ScaledGyroVector
    const InertialTypes::ChannelField FieldParser_ScaledGyroVector::FIELD_TYPE = InertialTypes::CH_FIELD_SENSOR_SCALED_GYRO_VEC;
    const bool FieldParser_ScaledGyroVector::REGISTERED = FieldParser_ScaledGyroVector::registerParser();    //register the parser immediately

    void FieldParser_ScaledGyroVector::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_X, valueType_float, anyType(x), true));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Y, valueType_float, anyType(y), true));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Z, valueType_float, anyType(z), true));
    }

    bool FieldParser_ScaledGyroVector::registerParser()
    {
        //create a static parser object
        static FieldParser_ScaledGyroVector p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_ScaledMagVector
    const InertialTypes::ChannelField FieldParser_ScaledMagVector::FIELD_TYPE = InertialTypes::CH_FIELD_SENSOR_SCALED_MAG_VEC;
    const bool FieldParser_ScaledMagVector::REGISTERED = FieldParser_ScaledMagVector::registerParser();    //register the parser immediately

    void FieldParser_ScaledMagVector::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_X, valueType_float, anyType(x), true));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Y, valueType_float, anyType(y), true));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Z, valueType_float, anyType(z), true));
    }

    bool FieldParser_ScaledMagVector::registerParser()
    {
        //create a static parser object
        static FieldParser_ScaledMagVector p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_DeltaThetaVector
    const InertialTypes::ChannelField FieldParser_DeltaThetaVector::FIELD_TYPE = InertialTypes::CH_FIELD_SENSOR_DELTA_THETA_VEC;
    const bool FieldParser_DeltaThetaVector::REGISTERED = FieldParser_DeltaThetaVector::registerParser();    //register the parser immediately

    void FieldParser_DeltaThetaVector::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_X, valueType_float, anyType(x), true));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Y, valueType_float, anyType(y), true));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Z, valueType_float, anyType(z), true));
    }

    bool FieldParser_DeltaThetaVector::registerParser()
    {
        //create a static parser object
        static FieldParser_DeltaThetaVector p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_DeltaVelocityVector
    const InertialTypes::ChannelField FieldParser_DeltaVelocityVector::FIELD_TYPE = InertialTypes::CH_FIELD_SENSOR_DELTA_VELOCITY_VEC;
    const bool FieldParser_DeltaVelocityVector::REGISTERED = FieldParser_DeltaVelocityVector::registerParser();    //register the parser immediately

    void FieldParser_DeltaVelocityVector::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_X, valueType_float, anyType(x), true));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Y, valueType_float, anyType(y), true));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Z, valueType_float, anyType(z), true));
    }

    bool FieldParser_DeltaVelocityVector::registerParser()
    {
        //create a static parser object
        static FieldParser_DeltaVelocityVector p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_OrientationMatrix
    const InertialTypes::ChannelField FieldParser_OrientationMatrix::FIELD_TYPE = InertialTypes::CH_FIELD_SENSOR_ORIENTATION_MATRIX;
    const bool FieldParser_OrientationMatrix::REGISTERED = FieldParser_OrientationMatrix::registerParser();    //register the parser immediately

    void FieldParser_OrientationMatrix::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        //create a Matrix to store as the data point
        Matrix data(3, 3, valueType_float, field.fieldData());

        //create a Matrix object with the Orientation Matrix data and create an InertialDataPoint from it
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_MATRIX, valueType_Matrix, anyType(data), true));
    }

    bool FieldParser_OrientationMatrix::registerParser()
    {
        //create a static parser object
        static FieldParser_OrientationMatrix p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_Quaternion
    const InertialTypes::ChannelField FieldParser_Quaternion::FIELD_TYPE = InertialTypes::CH_FIELD_SENSOR_ORIENTATION_QUATERNION;
    const bool FieldParser_Quaternion::REGISTERED = FieldParser_Quaternion::registerParser();    //register the parser immediately

    void FieldParser_Quaternion::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        //create a Vector to store as the data point
        Vector data(valueType_float, field.fieldData());

        //create a data point and add it to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_QUATERNION, valueType_Vector, anyType(data), true));
    }

    bool FieldParser_Quaternion::registerParser()
    {
        //create a static parser object
        static FieldParser_Quaternion p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_OrientationUpdateMatrix
    const InertialTypes::ChannelField FieldParser_OrientationUpdateMatrix::FIELD_TYPE = InertialTypes::CH_FIELD_SENSOR_ORIENTATION_UPDATE_MATRIX;
    const bool FieldParser_OrientationUpdateMatrix::REGISTERED = FieldParser_OrientationUpdateMatrix::registerParser();    //register the parser immediately

    void FieldParser_OrientationUpdateMatrix::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        //create a Matrix to store as the data point
        Matrix data(3, 3, valueType_float, field.fieldData());

        //create a Matrix object with the Orientation Matrix data and create an InertialDataPoint from it
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_MATRIX, valueType_Matrix, anyType(data), true));
    }

    bool FieldParser_OrientationUpdateMatrix::registerParser()
    {
        //create a static parser object
        static FieldParser_OrientationUpdateMatrix p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_EulerAngles
    const InertialTypes::ChannelField FieldParser_EulerAngles::FIELD_TYPE = InertialTypes::CH_FIELD_SENSOR_EULER_ANGLES;
    const bool FieldParser_EulerAngles::REGISTERED = FieldParser_EulerAngles::registerParser();    //register the parser immediately

    void FieldParser_EulerAngles::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float roll = bytes.read_float();
        float pitch = bytes.read_float();
        float yaw = bytes.read_float();

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_ROLL, valueType_float, anyType(roll), true));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_PITCH, valueType_float, anyType(pitch), true));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_YAW, valueType_float, anyType(yaw), true));
    }

    bool FieldParser_EulerAngles::registerParser()
    {
        //create a static parser object
        static FieldParser_EulerAngles p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_InternalTimestamp
    const InertialTypes::ChannelField FieldParser_InternalTimestamp::FIELD_TYPE = InertialTypes::CH_FIELD_SENSOR_INTERNAL_TIMESTAMP;
    const bool FieldParser_InternalTimestamp::REGISTERED = FieldParser_InternalTimestamp::registerParser();    //register the parser immediately

    void FieldParser_InternalTimestamp::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        //get the timestamp value as a uint32 (tick)
        uint32 time = field.fieldData().read_uint32(0);

        //create a data point and add it to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_TICK, valueType_uint32, anyType(time), true));
    }

    bool FieldParser_InternalTimestamp::registerParser()
    {
        //create a static parser object
        static FieldParser_InternalTimestamp p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_BeaconedTimestamp
    const InertialTypes::ChannelField FieldParser_BeaconedTimestamp::FIELD_TYPE = InertialTypes::CH_FIELD_SENSOR_BEACONED_TIMESTAMP;
    const bool FieldParser_BeaconedTimestamp::REGISTERED = FieldParser_BeaconedTimestamp::registerParser();    //register the parser immediately

    void FieldParser_BeaconedTimestamp::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        namespace px = boost::posix_time;

        //Constant: unixEpoch
        //    The posixTime representing the unix epoch
        static const px::ptime unixEpoch = px::ptime(boost::gregorian::date(1970, 1, 1));

        //Constant: gpsEpoch
        //    The posixTime representing the gps epoch
        static const px::ptime gpsEpoch = px::ptime(boost::gregorian::date(1980, 1, 6));

        //Constant: gpsToUnixEpochDiff
        //    The number of nanoseconds between the unix Epoch and the gps Epoch
        static const uint64 gpsToUnixEpochDiff = (gpsEpoch - unixEpoch).total_nanoseconds();



        DataBuffer bytes(field.fieldData());

        //get the timestamp status flags as a uint8
        uint8 timestampStatus = bytes.read_uint8();

        //get the timestamp's seconds and nanoseconds from the field bytes
        uint64 tsSeconds = bytes.read_uint32();
        uint64 tsSubSec = bytes.read_uint32();

        //get the full nanosecond-resolution timestamp, which is in GPS time
        uint64 tsNanoseconds = (tsSeconds * TimeSpan::NANOSECONDS_PER_SECOND) + tsSubSec;

        //create a Timestamp, converting to UTC time
        Timestamp timestamp(tsNanoseconds + gpsToUnixEpochDiff);

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(timestampStatus, TIMESTAMP_FLAG);

        //create a data point and add it to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_TIMESTAMP, valueType_Timestamp, anyType(timestamp), valid));
    }

    bool FieldParser_BeaconedTimestamp::registerParser()
    {
        //create a static parser object
        static FieldParser_BeaconedTimestamp p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_StabilizedMagVector
    const InertialTypes::ChannelField FieldParser_StabilizedMagVector::FIELD_TYPE = InertialTypes::CH_FIELD_SENSOR_STABILIZED_MAG_VEC;
    const bool FieldParser_StabilizedMagVector::REGISTERED = FieldParser_StabilizedMagVector::registerParser();    //register the parser immediately

    void FieldParser_StabilizedMagVector::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_X, valueType_float, anyType(x), true));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Y, valueType_float, anyType(y), true));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Z, valueType_float, anyType(z), true));
    }

    bool FieldParser_StabilizedMagVector::registerParser()
    {
        //create a static parser object
        static FieldParser_StabilizedMagVector p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_StabilizedAccelVector
    const InertialTypes::ChannelField FieldParser_StabilizedAccelVector::FIELD_TYPE = InertialTypes::CH_FIELD_SENSOR_STABILIZED_ACCEL_VEC;
    const bool FieldParser_StabilizedAccelVector::REGISTERED = FieldParser_StabilizedAccelVector::registerParser();    //register the parser immediately

    void FieldParser_StabilizedAccelVector::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //create the data points and add them to the result container
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_X, valueType_float, anyType(x), true));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Y, valueType_float, anyType(y), true));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Z, valueType_float, anyType(z), true));
    }

    bool FieldParser_StabilizedAccelVector::registerParser()
    {
        //create a static parser object
        static FieldParser_StabilizedAccelVector p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_GpsCorrelationTimestamp
    const InertialTypes::ChannelField FieldParser_GpsCorrelationTimestamp::FIELD_TYPE = InertialTypes::CH_FIELD_SENSOR_GPS_CORRELATION_TIMESTAMP;
    const bool FieldParser_GpsCorrelationTimestamp::REGISTERED = FieldParser_GpsCorrelationTimestamp::registerParser();    //register the parser immediately

    void FieldParser_GpsCorrelationTimestamp::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        double gpsTimeOfWeek = bytes.read_double();
        uint16 gpsWeekNumber = bytes.read_uint16();
        uint16 timestampFlags = bytes.read_uint16();

        bool tsValid = pointIsValid(timestampFlags, TS_FLAG);

        //add data points 
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_TIME_OF_WEEK, valueType_double, anyType(gpsTimeOfWeek), tsValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_WEEK_NUMBER, valueType_uint16, anyType(gpsWeekNumber), tsValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_FLAGS, valueType_uint16, anyType(timestampFlags), true));
    }

    bool FieldParser_GpsCorrelationTimestamp::registerParser()
    {
        //create a static parser object
        static FieldParser_GpsCorrelationTimestamp p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_ScaledAmbientPressure
    const InertialTypes::ChannelField FieldParser_ScaledAmbientPressure::FIELD_TYPE = InertialTypes::CH_FIELD_SENSOR_SCALED_AMBIENT_PRESSURE;
    const bool FieldParser_ScaledAmbientPressure::REGISTERED = FieldParser_ScaledAmbientPressure::registerParser();    //register the parser immediately

    void FieldParser_ScaledAmbientPressure::parse(const InertialDataField& field, InertialDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        float ambientPressure = bytes.read_float();

        //add data points 
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_PRESSURE, valueType_float, anyType(ambientPressure), true));
    }

    bool FieldParser_ScaledAmbientPressure::registerParser()
    {
        //create a static parser object
        static FieldParser_ScaledAmbientPressure p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================
}