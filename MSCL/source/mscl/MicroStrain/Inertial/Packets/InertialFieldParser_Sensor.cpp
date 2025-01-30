/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "InertialFieldParser_Sensor.h"

#include <boost/date_time/posix_time/ptime.hpp>

#include "mscl/MicroStrain/MIP/Packets/MipDataPacket.h"
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
    const MipTypes::ChannelField FieldParser_RawAccelVector::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_RAW_ACCEL_VEC;
    const bool FieldParser_RawAccelVector::REGISTERED = FieldParser_RawAccelVector::registerParser();    //register the parser immediately

    void FieldParser_RawAccelVector::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z)));
    }

    bool FieldParser_RawAccelVector::registerParser()
    {
        static FieldParser_RawAccelVector p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_RawGyroVector
    const MipTypes::ChannelField FieldParser_RawGyroVector::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_RAW_GYRO_VEC;
    const bool FieldParser_RawGyroVector::REGISTERED = FieldParser_RawGyroVector::registerParser();    //register the parser immediately

    void FieldParser_RawGyroVector::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z)));
    }

    bool FieldParser_RawGyroVector::registerParser()
    {
        static FieldParser_RawGyroVector p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_RawMagVector
    const MipTypes::ChannelField FieldParser_RawMagVector::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_RAW_MAG_VEC;
    const bool FieldParser_RawMagVector::REGISTERED = FieldParser_RawMagVector::registerParser();    //register the parser immediately

    void FieldParser_RawMagVector::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z)));
    }

    bool FieldParser_RawMagVector::registerParser()
    {
        static FieldParser_RawMagVector p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_ScaledAccelVector
    const MipTypes::ChannelField FieldParser_ScaledAccelVector::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_SCALED_ACCEL_VEC;
    const bool FieldParser_ScaledAccelVector::REGISTERED = FieldParser_ScaledAccelVector::registerParser();    //register the parser immediately

    void FieldParser_ScaledAccelVector::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z)));
    }

    bool FieldParser_ScaledAccelVector::registerParser()
    {
        static FieldParser_ScaledAccelVector p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_ScaledGyroVector
    const MipTypes::ChannelField FieldParser_ScaledGyroVector::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_SCALED_GYRO_VEC;
    const bool FieldParser_ScaledGyroVector::REGISTERED = FieldParser_ScaledGyroVector::registerParser();    //register the parser immediately

    void FieldParser_ScaledGyroVector::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z)));
    }

    bool FieldParser_ScaledGyroVector::registerParser()
    {
        static FieldParser_ScaledGyroVector p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_ScaledMagVector
    const MipTypes::ChannelField FieldParser_ScaledMagVector::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_SCALED_MAG_VEC;
    const bool FieldParser_ScaledMagVector::REGISTERED = FieldParser_ScaledMagVector::registerParser();    //register the parser immediately

    void FieldParser_ScaledMagVector::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z)));
    }

    bool FieldParser_ScaledMagVector::registerParser()
    {
        static FieldParser_ScaledMagVector p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_DeltaThetaVector
    const MipTypes::ChannelField FieldParser_DeltaThetaVector::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_DELTA_THETA_VEC;
    const bool FieldParser_DeltaThetaVector::REGISTERED = FieldParser_DeltaThetaVector::registerParser();    //register the parser immediately

    void FieldParser_DeltaThetaVector::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z)));
    }

    bool FieldParser_DeltaThetaVector::registerParser()
    {
        static FieldParser_DeltaThetaVector p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_DeltaVelocityVector
    const MipTypes::ChannelField FieldParser_DeltaVelocityVector::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_DELTA_VELOCITY_VEC;
    const bool FieldParser_DeltaVelocityVector::REGISTERED = FieldParser_DeltaVelocityVector::registerParser();    //register the parser immediately

    void FieldParser_DeltaVelocityVector::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z)));
    }

    bool FieldParser_DeltaVelocityVector::registerParser()
    {
        static FieldParser_DeltaVelocityVector p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_OrientationMatrix
    const MipTypes::ChannelField FieldParser_OrientationMatrix::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_ORIENTATION_MATRIX;
    const bool FieldParser_OrientationMatrix::REGISTERED = FieldParser_OrientationMatrix::registerParser();    //register the parser immediately

    void FieldParser_OrientationMatrix::parse(const MipDataField& field, MipDataPoints& result) const
    {
        //create a Matrix to store as the data point
        Matrix data(3, 3, valueType_float, field.fieldData());

        //create a Matrix object with the Orientation Matrix data and create a MipDataPoint from it
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_MATRIX, valueType_Matrix, anyType(data)));
    }

    bool FieldParser_OrientationMatrix::registerParser()
    {
        static FieldParser_OrientationMatrix p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_Quaternion
    const MipTypes::ChannelField FieldParser_Quaternion::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_ORIENTATION_QUATERNION;
    const bool FieldParser_Quaternion::REGISTERED = FieldParser_Quaternion::registerParser();    //register the parser immediately

    void FieldParser_Quaternion::parse(const MipDataField& field, MipDataPoints& result) const
    {
        //create a Vector to store as the data point
        Vector data(valueType_float, field.fieldData());

        //create a data point and add it to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_QUATERNION, valueType_Vector, anyType(data)));
    }

    bool FieldParser_Quaternion::registerParser()
    {
        static FieldParser_Quaternion p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_OrientationUpdateMatrix
    const MipTypes::ChannelField FieldParser_OrientationUpdateMatrix::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_ORIENTATION_UPDATE_MATRIX;
    const bool FieldParser_OrientationUpdateMatrix::REGISTERED = FieldParser_OrientationUpdateMatrix::registerParser();    //register the parser immediately

    void FieldParser_OrientationUpdateMatrix::parse(const MipDataField& field, MipDataPoints& result) const
    {
        //create a Matrix to store as the data point
        Matrix data(3, 3, valueType_float, field.fieldData());

        //create a Matrix object with the Orientation Matrix data and create a MipDataPoint from it
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_MATRIX, valueType_Matrix, anyType(data)));
    }

    bool FieldParser_OrientationUpdateMatrix::registerParser()
    {
        static FieldParser_OrientationUpdateMatrix p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_EulerAngles
    const MipTypes::ChannelField FieldParser_EulerAngles::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_EULER_ANGLES;
    const bool FieldParser_EulerAngles::REGISTERED = FieldParser_EulerAngles::registerParser();    //register the parser immediately

    void FieldParser_EulerAngles::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float roll = bytes.read_float();
        float pitch = bytes.read_float();
        float yaw = bytes.read_float();

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_ROLL, valueType_float, anyType(roll)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_PITCH, valueType_float, anyType(pitch)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_YAW, valueType_float, anyType(yaw)));
    }

    bool FieldParser_EulerAngles::registerParser()
    {
        static FieldParser_EulerAngles p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_InternalTimestamp
    const MipTypes::ChannelField FieldParser_InternalTimestamp::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_INTERNAL_TIMESTAMP;
    const bool FieldParser_InternalTimestamp::REGISTERED = FieldParser_InternalTimestamp::registerParser();    //register the parser immediately

    void FieldParser_InternalTimestamp::parse(const MipDataField& field, MipDataPoints& result) const
    {
        //get the timestamp value as a uint32 (tick)
        uint32 time = field.fieldData().read_uint32(0);

        //create a data point and add it to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_TICK, valueType_uint32, anyType(time)));
    }

    bool FieldParser_InternalTimestamp::registerParser()
    {
        static FieldParser_InternalTimestamp p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_BeaconedTimestamp
    const MipTypes::ChannelField FieldParser_BeaconedTimestamp::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_BEACONED_TIMESTAMP;
    const bool FieldParser_BeaconedTimestamp::REGISTERED = FieldParser_BeaconedTimestamp::registerParser();    //register the parser immediately

    void FieldParser_BeaconedTimestamp::parse(const MipDataField& field, MipDataPoints& result) const
    {
        //Constant: GPS_TO_UNIX_EPOCH_DIFF
        //    The number of nanoseconds between the unix Epoch and the gps Epoch
        static const uint64 GPS_TO_UNIX_EPOCH_DIFF = 315964800000000000;

        DataBuffer bytes(field.fieldData());

        //get the timestamp status flags as a uint8
        uint8 timestampStatus = bytes.read_uint8();

        //get the timestamp's seconds and nanoseconds from the field bytes
        uint64 tsSeconds = bytes.read_uint32();
        uint64 tsSubSec = bytes.read_uint32();

        //get the full nanosecond-resolution timestamp, which is in GPS time
        uint64 tsNanoseconds = (tsSeconds * TimeSpan::NANOSECONDS_PER_SECOND) + tsSubSec;

        //create a Timestamp, converting to UTC time
        Timestamp timestamp(tsNanoseconds + GPS_TO_UNIX_EPOCH_DIFF);

        //get whether points are valid or invalid from the flags
        bool valid = pointIsValid(timestampStatus, TIMESTAMP_FLAG);

        //create a data point and add it to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_TIMESTAMP, valueType_Timestamp, anyType(timestamp), valid));
    }

    bool FieldParser_BeaconedTimestamp::registerParser()
    {
        static FieldParser_BeaconedTimestamp p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_StabilizedMagVector
    const MipTypes::ChannelField FieldParser_StabilizedMagVector::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_STABILIZED_MAG_VEC;
    const bool FieldParser_StabilizedMagVector::REGISTERED = FieldParser_StabilizedMagVector::registerParser();    //register the parser immediately

    void FieldParser_StabilizedMagVector::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z)));
    }

    bool FieldParser_StabilizedMagVector::registerParser()
    {
        static FieldParser_StabilizedMagVector p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_StabilizedAccelVector
    const MipTypes::ChannelField FieldParser_StabilizedAccelVector::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_STABILIZED_ACCEL_VEC;
    const bool FieldParser_StabilizedAccelVector::REGISTERED = FieldParser_StabilizedAccelVector::registerParser();    //register the parser immediately

    void FieldParser_StabilizedAccelVector::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        float x = bytes.read_float();
        float y = bytes.read_float();
        float z = bytes.read_float();

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_X, valueType_float, anyType(x)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Y, valueType_float, anyType(y)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_Z, valueType_float, anyType(z)));
    }

    bool FieldParser_StabilizedAccelVector::registerParser()
    {
        static FieldParser_StabilizedAccelVector p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_GpsCorrelationTimestamp
    const MipTypes::ChannelField FieldParser_GpsCorrelationTimestamp::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_GPS_CORRELATION_TIMESTAMP;
    const bool FieldParser_GpsCorrelationTimestamp::REGISTERED = FieldParser_GpsCorrelationTimestamp::registerParser();    //register the parser immediately

    void FieldParser_GpsCorrelationTimestamp::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        double gpsTimeOfWeek = bytes.read_double();
        uint16 gpsWeekNumber = bytes.read_uint16();
        uint16 timestampFlags = bytes.read_uint16();

        bool tsValid = pointIsValid(timestampFlags, TS_FLAG);

        //add data points
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_TIME_OF_WEEK, valueType_double, anyType(gpsTimeOfWeek), tsValid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_WEEK_NUMBER, valueType_uint16, anyType(gpsWeekNumber), tsValid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_FLAGS, valueType_uint16, anyType(timestampFlags)));
    }

    bool FieldParser_GpsCorrelationTimestamp::registerParser()
    {
        static FieldParser_GpsCorrelationTimestamp p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_TemperatureStatistics
    const MipTypes::ChannelField FieldParser_TemperatureStatistics::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_TEMPERATURE_STATISTICS;
    const bool FieldParser_TemperatureStatistics::REGISTERED = FieldParser_TemperatureStatistics::registerParser();    //register the parser immediately

    void FieldParser_TemperatureStatistics::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        float minTemp = bytes.read_float();
        float maxTemp = bytes.read_float();
        float meanTemp = bytes.read_float();

        //add data points
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_MIN_TEMP, valueType_float, anyType(minTemp)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_MAX_TEMP, valueType_float, anyType(maxTemp)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_MEAN_TEMP, valueType_float, anyType(meanTemp)));
    }

    bool FieldParser_TemperatureStatistics::registerParser()
    {
        static FieldParser_TemperatureStatistics p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_ScaledAmbientPressure
    const MipTypes::ChannelField FieldParser_ScaledAmbientPressure::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_SCALED_AMBIENT_PRESSURE;
    const bool FieldParser_ScaledAmbientPressure::REGISTERED = FieldParser_ScaledAmbientPressure::registerParser();    //register the parser immediately

    void FieldParser_ScaledAmbientPressure::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        float ambientPressure = bytes.read_float();

        //add data points
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_PRESSURE, valueType_float, anyType(ambientPressure)));
    }

    bool FieldParser_ScaledAmbientPressure::registerParser()
    {
        //create a static parser object
        static FieldParser_ScaledAmbientPressure p;

        //register the parser
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_OverrangeStatus
    const MipTypes::ChannelField FieldParser_OverrangeStatus::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_OVERRANGE_STATUS;
    const bool FieldParser_OverrangeStatus::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_OverrangeStatus::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        const uint16 status = bytes.read_uint16();

        //add data points
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_STATUS, valueType_uint16, anyType(status)));
    }

    bool FieldParser_OverrangeStatus::registerParser()
    {
        //create a static parser object
        static FieldParser_OverrangeStatus p;

        //register the parser
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_RawAmbientPressure
    const MipTypes::ChannelField FieldParser_RawAmbientPressure::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_RAW_AMBIENT_PRESSURE;
    const bool FieldParser_RawAmbientPressure::REGISTERED = FieldParser_RawAmbientPressure::registerParser();    //register the parser immediately

    void FieldParser_RawAmbientPressure::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        float ambientPressure = bytes.read_float();

        //add data points
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_PRESSURE, valueType_float, anyType(ambientPressure)));
    }

    bool FieldParser_RawAmbientPressure::registerParser()
    {
        //create a static parser object
        static FieldParser_RawAmbientPressure p;

        //register the parser
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_OdometerData
    const MipTypes::ChannelField FieldParser_OdometerData::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_ODOMETER_DATA;
    const bool FieldParser_OdometerData::REGISTERED = FieldParser_OdometerData::registerParser();    //register the parser immediately

    void FieldParser_OdometerData::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        float speed = bytes.read_float();
        float unc = bytes.read_float();
        bool valid = bytes.read_uint16() > 0;

        //add data points
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_SPEED, valueType_float, anyType(speed), valid));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_SPEED_ACCURACY, valueType_float, anyType(unc), valid));
    }

    bool FieldParser_OdometerData::registerParser()
    {
        //create a static parser object
        static FieldParser_OdometerData p;

        //register the parser
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================
}
