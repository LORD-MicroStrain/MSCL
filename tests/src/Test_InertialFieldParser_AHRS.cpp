/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Inertial/Packets/InertialFieldParser_Sensor.h"
#include "mscl/MicroStrain/MIP/MipDataPoint.h"
#include "mscl/MicroStrain/MIP/Packets/MipDataPacket.h"
#include "mscl/MicroStrain/MIP/Packets/MipFieldParser.h"

using namespace mscl;

DISABLE_WARNING_BOOST_START
#include <boost/test/unit_test.hpp>
DISABLE_WARNING_BOOST_END

BOOST_AUTO_TEST_SUITE(InertialFieldParser_Sensor_Test)

BOOST_AUTO_TEST_CASE(InertialFieldParser_RawAccelVector_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.234f);    //Accel 1 float
    bytes.append_float(0.0f);    //Accel 2 float
    bytes.append_float(0.0f);    //Accel 3 float

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_SENSOR_RAW_ACCEL_VEC, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);
    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_SENSOR_RAW_ACCEL_VEC);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_X);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 1.234, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_SENSOR_RAW_ACCEL_VEC);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_Y);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_SENSOR_RAW_ACCEL_VEC);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_Z);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_RawGyroVector_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(0.0f);    //Gyro 1 float
    bytes.append_float(1.234f);    //Gyro 2 float
    bytes.append_float(0.0f);    //Gyro 3 float

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_SENSOR_RAW_GYRO_VEC, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);
    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_SENSOR_RAW_GYRO_VEC);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_X);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_SENSOR_RAW_GYRO_VEC);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_Y);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 1.234, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_SENSOR_RAW_GYRO_VEC);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_Z);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_RawMagVector_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(0.0f);    //Mag 1 float
    bytes.append_float(0.0f);    //Mag 2 float
    bytes.append_float(2.345f);    //Mag 3 float

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_SENSOR_RAW_MAG_VEC, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);
    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_SENSOR_RAW_MAG_VEC);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_X);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_SENSOR_RAW_MAG_VEC);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_Y);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_SENSOR_RAW_MAG_VEC);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_Z);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 2.345, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_ScaledAccelVector_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(2.345f);    //X Accel float
    bytes.append_float(0.0f);    //Y Accel float
    bytes.append_float(0.0f);    //Z Accel float

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_SENSOR_SCALED_ACCEL_VEC, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);
    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_SENSOR_SCALED_ACCEL_VEC);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_X);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 2.345, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_SENSOR_SCALED_ACCEL_VEC);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_Y);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_SENSOR_SCALED_ACCEL_VEC);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_Z);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_ScaledGyroVector_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(2.345f);    //X Gyro float
    bytes.append_float(0.0f);    //Y Gyro float
    bytes.append_float(0.0f);    //Z Gyro float

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_SENSOR_SCALED_GYRO_VEC, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);
    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_SENSOR_SCALED_GYRO_VEC);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_X);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 2.345, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_SENSOR_SCALED_GYRO_VEC);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_Y);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_SENSOR_SCALED_GYRO_VEC);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_Z);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_ScaledMagVector_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(2.345f);    //X Mag float
    bytes.append_float(0.0f);    //Y Mag float
    bytes.append_float(0.0f);    //Z Mag float

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_SENSOR_SCALED_MAG_VEC, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);
    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_SENSOR_SCALED_MAG_VEC);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_X);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 2.345, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_SENSOR_SCALED_MAG_VEC);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_Y);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_SENSOR_SCALED_MAG_VEC);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_Z);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_DeltaThetaVector_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(2.345f);    //X Delta Theta float
    bytes.append_float(0.0f);    //Y Delta Theta float
    bytes.append_float(0.0f);    //Z Delta Theta float

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_SENSOR_DELTA_THETA_VEC, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);
    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_SENSOR_DELTA_THETA_VEC);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_X);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 2.345, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_SENSOR_DELTA_THETA_VEC);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_Y);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_SENSOR_DELTA_THETA_VEC);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_Z);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_DeltaVelocityVector_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(2.345f);    //X Delta Velocity float
    bytes.append_float(0.0f);    //Y Delta Velocity float
    bytes.append_float(0.0f);    //Z Delta Velocity float

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_SENSOR_DELTA_VELOCITY_VEC, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);
    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_SENSOR_DELTA_VELOCITY_VEC);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_X);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 2.345, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_SENSOR_DELTA_VELOCITY_VEC);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_Y);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_SENSOR_DELTA_VELOCITY_VEC);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_Z);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_OrientMatrix_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(0.0f);
    bytes.append_float(1.234f);
    bytes.append_float(2.345f);
    bytes.append_float(3.456f);
    bytes.append_float(0.0f);
    bytes.append_float(9123.2f);
    bytes.append_float(0.0f);
    bytes.append_float(0.0f);
    bytes.append_float(0.0f);

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_SENSOR_ORIENTATION_MATRIX, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 1);
    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_SENSOR_ORIENTATION_MATRIX);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_MATRIX);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_Matrix);
    BOOST_CHECK_CLOSE(data.at(0).as_Matrix().as_floatAt(0, 0), 0.0, 0.0001);
    BOOST_CHECK_CLOSE(data.at(0).as_Matrix().as_floatAt(0, 1), 1.234, 0.0001);
    BOOST_CHECK_CLOSE(data.at(0).as_Matrix().as_floatAt(0, 2), 2.345, 0.0001);
    BOOST_CHECK_CLOSE(data.at(0).as_Matrix().as_floatAt(1, 0), 3.456, 0.0001);
    BOOST_CHECK_CLOSE(data.at(0).as_Matrix().as_floatAt(1, 1), 0.0, 0.0001);
    BOOST_CHECK_CLOSE(data.at(0).as_Matrix().as_floatAt(1, 2), 9123.2, 0.0001);
    BOOST_CHECK_CLOSE(data.at(0).as_Matrix().as_floatAt(2, 0), 0.0, 0.0001);
    BOOST_CHECK_CLOSE(data.at(0).as_Matrix().as_floatAt(2, 1), 0.0, 0.0001);
    BOOST_CHECK_CLOSE(data.at(0).as_Matrix().as_floatAt(2, 2), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_Quaternion_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(2.345f);    //q0
    bytes.append_float(0.0f);    //q1
    bytes.append_float(0.0f);    //q2
    bytes.append_float(0.0f);    //q3

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_SENSOR_ORIENTATION_QUATERNION, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 1);
    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_SENSOR_ORIENTATION_QUATERNION);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_QUATERNION);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_Vector);
    BOOST_CHECK_CLOSE(data.at(0).as_Vector().as_floatAt(0), 2.345, 0.0001);
    BOOST_CHECK_EQUAL(data.at(0).as_Vector().as_floatAt(1), 0);
    BOOST_CHECK_EQUAL(data.at(0).as_Vector().as_floatAt(2), 0);
    BOOST_CHECK_EQUAL(data.at(0).as_Vector().as_floatAt(3), 0);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_OrientUpdateMatrix_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(0.0f);
    bytes.append_float(1.234f);
    bytes.append_float(2.345f);
    bytes.append_float(3.456f);
    bytes.append_float(0.0f);
    bytes.append_float(9123.2f);
    bytes.append_float(0.0f);
    bytes.append_float(0.0f);
    bytes.append_float(0.0f);

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_SENSOR_ORIENTATION_UPDATE_MATRIX, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 1);
    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_SENSOR_ORIENTATION_UPDATE_MATRIX);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_MATRIX);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_Matrix);
    BOOST_CHECK_CLOSE(data.at(0).as_Matrix().as_floatAt(0, 0), 0.0, 0.0001);
    BOOST_CHECK_CLOSE(data.at(0).as_Matrix().as_floatAt(0, 1), 1.234, 0.0001);
    BOOST_CHECK_CLOSE(data.at(0).as_Matrix().as_floatAt(0, 2), 2.345, 0.0001);
    BOOST_CHECK_CLOSE(data.at(0).as_Matrix().as_floatAt(1, 0), 3.456, 0.0001);
    BOOST_CHECK_CLOSE(data.at(0).as_Matrix().as_floatAt(1, 1), 0.0, 0.0001);
    BOOST_CHECK_CLOSE(data.at(0).as_Matrix().as_floatAt(1, 2), 9123.2, 0.0001);
    BOOST_CHECK_CLOSE(data.at(0).as_Matrix().as_floatAt(2, 0), 0.0, 0.0001);
    BOOST_CHECK_CLOSE(data.at(0).as_Matrix().as_floatAt(2, 1), 0.0, 0.0001);
    BOOST_CHECK_CLOSE(data.at(0).as_Matrix().as_floatAt(2, 2), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_EulerAngles_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(2.345f);    //roll
    bytes.append_float(0.0f);    //pitch
    bytes.append_float(0.0f);    //yaw

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_SENSOR_EULER_ANGLES, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);
    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_SENSOR_EULER_ANGLES);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_ROLL);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 2.345, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_SENSOR_EULER_ANGLES);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_PITCH);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_SENSOR_EULER_ANGLES);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_YAW);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_InternalTimestamp_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_uint32(1234567890);     //timestamp value (tick)

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_SENSOR_INTERNAL_TIMESTAMP, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 1);
    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_SENSOR_INTERNAL_TIMESTAMP);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_TICK);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_uint32);
    BOOST_CHECK_EQUAL(data.at(0).as_uint32(), 1234567890);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_BeaconedTimestamp_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_uint8(1);
    bytes.append_uint32(1046317456);    //timestamp seconds (gps time)
    bytes.append_uint32(12345);         //timestamp nanoseconds

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_SENSOR_BEACONED_TIMESTAMP, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 1);
    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_SENSOR_BEACONED_TIMESTAMP);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_TIMESTAMP);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_Timestamp);
    BOOST_CHECK_EQUAL(data.at(0).as_Timestamp().str(), "2013-03-03 03:44:16.000012345");
    BOOST_CHECK_NO_THROW(data.at(0).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_StabilizedMagVector_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(2.345f);    //X Stab Mag float
    bytes.append_float(0.0f);    //Y Stab Mag float
    bytes.append_float(0.0f);    //Z Stab Mag float

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_SENSOR_STABILIZED_MAG_VEC, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);
    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_SENSOR_STABILIZED_MAG_VEC);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_X);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 2.345, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_SENSOR_STABILIZED_MAG_VEC);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_Y);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_SENSOR_STABILIZED_MAG_VEC);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_Z);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_StabilizedAccelVector_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(2.345f);    //X Stab Accel float
    bytes.append_float(0.0f);    //Y Stab Accel float
    bytes.append_float(0.0f);    //Z Stab Accel float

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_SENSOR_STABILIZED_ACCEL_VEC, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);
    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_SENSOR_STABILIZED_ACCEL_VEC);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_X);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 2.345, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_SENSOR_STABILIZED_ACCEL_VEC);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_Y);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_SENSOR_STABILIZED_ACCEL_VEC);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_Z);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_GpsCorrelationTimestamp_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_double(1.2);        //gps time of week
    bytes.append_uint16(1200);        //gps week number
    bytes.append_uint16(1);            //timestamp flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_SENSOR_GPS_CORRELATION_TIMESTAMP, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);

    //GPS Time of Week
    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_SENSOR_GPS_CORRELATION_TIMESTAMP);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_TIME_OF_WEEK);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_double);
    BOOST_CHECK_CLOSE(data.at(0).as_double(), 1.2, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    //GPS Week Number
    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_SENSOR_GPS_CORRELATION_TIMESTAMP);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_WEEK_NUMBER);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_uint16);
    BOOST_CHECK_EQUAL(data.at(1).as_uint16(), 1200);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    //Timestamp Flags
    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_SENSOR_GPS_CORRELATION_TIMESTAMP);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_FLAGS);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_uint16);
    BOOST_CHECK_EQUAL(data.at(2).as_uint16(), 1);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_ScaledAmbientPressure_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.2f);        //ambient pressure

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_SENSOR_SCALED_AMBIENT_PRESSURE, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 1);

    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_SENSOR_SCALED_AMBIENT_PRESSURE);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_PRESSURE);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 1.2, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());
}

BOOST_AUTO_TEST_SUITE_END()
