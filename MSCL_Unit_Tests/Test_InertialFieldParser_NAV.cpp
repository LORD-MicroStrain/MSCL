/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/MIP/Packets/MipFieldParser.h"
#include "mscl/MicroStrain/MIP/Packets/MipDataPacket.h"
#include "mscl/MicroStrain/MIP/MipDataPoint.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialFieldParser_EstFilter.h"
#include "mscl/MicroStrain/Inertial/ExposedInertialTypes.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(InertialFieldParser_EstFilter_Test)

BOOST_AUTO_TEST_CASE(InertialFieldParser_FilterStatus_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_uint16(0x03);    //filter state
    bytes.append_uint16(0x02);    //dynamics mode
    bytes.append_uint16(0x03);    //status flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_FILTER_STATUS, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);

    //Filter State
    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_FILTER_STATUS);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_FILTER_STATE);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_uint16);
    BOOST_CHECK_EQUAL(data.at(0).valid(), true);
    BOOST_CHECK_EQUAL(data.at(0).as_uint16(), InertialTypes::FILTERSTATE_RUNNING_SLN_ERROR);
    BOOST_CHECK_EQUAL(data.at(0).channelName(), "estFilterState");

    //Dynamics Mode
    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_ESTFILTER_FILTER_STATUS);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_DYNAMICS_MODE);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_uint16);
    BOOST_CHECK_EQUAL(data.at(1).valid(), true);
    BOOST_CHECK_EQUAL(data.at(1).as_uint16(), InertialTypes::AUTOMOTIVE_VEHICLE);
    BOOST_CHECK_EQUAL(data.at(1).channelName(), "estFilterDynamicsMode");

    //flags
    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_ESTFILTER_FILTER_STATUS);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_FLAGS);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_uint16);
    BOOST_CHECK_EQUAL(data.at(2).valid(), true);
    BOOST_CHECK_EQUAL(data.at(2).as_uint16(), 0x03);
    BOOST_CHECK_EQUAL(data.at(2).channelName(), "estFilterStatusFlags");
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_GPSTimestamp_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_double(23.45);    //time of week
    bytes.append_uint16(10);    //week number
    bytes.append_uint16(1);        //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_GPS_TIMESTAMP, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 2);

    //Time of Week
    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_GPS_TIMESTAMP);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_TIME_OF_WEEK);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_double);
    BOOST_CHECK_EQUAL(data.at(0).valid(), true);
    BOOST_CHECK_EQUAL(data.at(0).as_double(), 23.45);
    BOOST_CHECK_EQUAL(data.at(0).channelName(), "estFilterGpsTimeTow");

    //Week Number
    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_ESTFILTER_GPS_TIMESTAMP);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_WEEK_NUMBER);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_uint16);
    BOOST_CHECK_EQUAL(data.at(1).valid(), true);
    BOOST_CHECK_EQUAL(data.at(1).as_uint16(), 10);
    BOOST_CHECK_EQUAL(data.at(1).channelName(), "estFilterGpsTimeWeekNum");
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_EstimatedLLHPosition_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_double(1.2);        //latitude
    bytes.append_double(3.4);        //longitude
    bytes.append_double(5.67);        //height above ellipsoid
    bytes.append_uint16(0);            //valid flags (0000 0000)

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_LLH_POS, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);

    //Latitude
    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_LLH_POS);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_LATITUDE);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_double);
    BOOST_CHECK_EQUAL(data.at(0).valid(), false);
    BOOST_CHECK_CLOSE(data.at(0).as_double(), 1.2, 0.0001);
    BOOST_CHECK_EQUAL(data.at(0).channelName(), "estLatitude");

    //Longitude
    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_LLH_POS);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_LONGITUDE);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_double);
    BOOST_CHECK_EQUAL(data.at(1).valid(), false);
    BOOST_CHECK_CLOSE(data.at(1).as_double(), 3.4, 0.0001);
    BOOST_CHECK_EQUAL(data.at(1).channelName(), "estLongitude");

    //Height Above Ellipsoid
    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_LLH_POS);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_HEIGHT_ABOVE_ELLIPSOID);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_double);
    BOOST_CHECK_EQUAL(data.at(2).valid(), false);
    BOOST_CHECK_CLOSE(data.at(2).as_double(), 5.67, 0.0001);
    BOOST_CHECK_EQUAL(data.at(2).channelName(), "estHeightAboveElipsoid");
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_EstimatedNEDVelocity_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.1f);    //north
    bytes.append_float(2.2f);    //east
    bytes.append_float(3.3f);    //down
    bytes.append_uint16(1);        //valid flags (0000 0001)

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_NED_VELOCITY, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);

    //north
    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_NED_VELOCITY);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_NORTH);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), true);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 1.1, 0.0001);
    BOOST_CHECK_EQUAL(data.at(0).channelName(), "estNorthVelocity");

    //east
    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_NED_VELOCITY);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_EAST);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(1).valid(), true);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 2.2, 0.0001);
    BOOST_CHECK_EQUAL(data.at(1).channelName(), "estEastVelocity");

    //down
    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_NED_VELOCITY);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_DOWN);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(2).valid(), true);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 3.3, 0.0001);
    BOOST_CHECK_EQUAL(data.at(2).channelName(), "estDownVelocity");
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_EstimatedQuaternion_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(2.345f);    //q0
    bytes.append_float(0.0f);    //q1
    bytes.append_float(0.0f);    //q2    
    bytes.append_float(0.0f);    //q3
    bytes.append_uint16(1);        //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_QUATERNION, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 1);
    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_QUATERNION);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_QUATERNION);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_Vector);
    BOOST_CHECK_EQUAL(data.at(0).valid(), true);
    BOOST_CHECK_CLOSE(data.at(0).as_Vector().as_floatAt(0), 2.345, 0.0001);
    BOOST_CHECK_EQUAL(data.at(0).as_Vector().as_floatAt(1), 0);
    BOOST_CHECK_EQUAL(data.at(0).as_Vector().as_floatAt(2), 0);
    BOOST_CHECK_EQUAL(data.at(0).as_Vector().as_floatAt(3), 0);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_EstimatedOrientMatrix_parse)
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
    bytes.append_uint16(0);        //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_MATRIX, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 1);
    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_MATRIX);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_MATRIX);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_Matrix);
    BOOST_CHECK_EQUAL(data.at(0).valid(), false);
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

BOOST_AUTO_TEST_CASE(InertialFieldParser_EstimatedEulerAngles_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(2.345f);    //roll
    bytes.append_float(0.0f);    //pitch
    bytes.append_float(0.0f);    //yaw
    bytes.append_uint16(1);        //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_EULER, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);

    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_EULER);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_ROLL);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), true);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 2.345, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_EULER);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_PITCH);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(1).valid(), true);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_EULER);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_YAW);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(2).valid(), true);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_EstimatedGyroBias_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(2.345f);    //x
    bytes.append_float(0.0f);    //y
    bytes.append_float(0.0f);    //z
    bytes.append_uint16(1);        //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);

    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_X);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), true);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 2.345, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_Y);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(1).valid(), true);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_Z);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(2).valid(), true);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_EstimatedAccelBias_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(2.345f);    //x
    bytes.append_float(0.0f);    //y
    bytes.append_float(0.0f);    //z
    bytes.append_uint16(1);        //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);

    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_X);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), true);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 2.345, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_Y);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(1).valid(), true);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_Z);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(2).valid(), true);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 0.0, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_EstimatedLLHUncertainty_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.234f);    //north
    bytes.append_float(4.567f);    //east
    bytes.append_float(9.988f);    //down
    bytes.append_uint16(0);        //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_LLH_UNCERT, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);

    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_LLH_UNCERT);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_NORTH);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), false);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 1.234, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_LLH_UNCERT);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_EAST);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(1).valid(), false);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 4.567, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_LLH_UNCERT);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_DOWN);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(2).valid(), false);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 9.988, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_EstimatedNEDUncertainty_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.234f);    //north
    bytes.append_float(4.567f);    //east
    bytes.append_float(9.988f);    //down
    bytes.append_uint16(1);        //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_NED_UNCERT, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);

    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_NED_UNCERT);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_NORTH);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), true);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 1.234, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_NED_UNCERT);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_EAST);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(1).valid(), true);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 4.567, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_NED_UNCERT);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_DOWN);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(2).valid(), true);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 9.988, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_EstimatedAttEulerUncertainty_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.234f);    //roll
    bytes.append_float(4.567f);    //pitch
    bytes.append_float(9.988f);    //yaw
    bytes.append_uint16(1);        //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ATT_UNCERT_EULER, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);

    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ATT_UNCERT_EULER);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_ROLL);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), true);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 1.234, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ATT_UNCERT_EULER);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_PITCH);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(1).valid(), true);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 4.567, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ATT_UNCERT_EULER);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_YAW);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(2).valid(), true);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 9.988, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_EstimatedGyroBiasUncertainty_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.234f);    //x
    bytes.append_float(4.567f);    //y
    bytes.append_float(9.988f);    //z
    bytes.append_uint16(0);        //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS_UNCERT, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);

    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS_UNCERT);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_X);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), false);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 1.234, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS_UNCERT);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_Y);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(1).valid(), false);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 4.567, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS_UNCERT);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_Z);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(2).valid(), false);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 9.988, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_EstimatedAccelBiasUncertainty_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.234f);    //x
    bytes.append_float(4.567f);    //y
    bytes.append_float(9.988f);    //z
    bytes.append_uint16(0);        //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS_UNCERT, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);

    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS_UNCERT);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_X);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), false);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 1.234, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS_UNCERT);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_Y);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(1).valid(), false);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 4.567, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS_UNCERT);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_Z);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(2).valid(), false);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 9.988, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_EstimatedLinearAccel_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.234f);    //x
    bytes.append_float(4.567f);    //y
    bytes.append_float(9.988f);    //z
    bytes.append_uint16(0);        //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_LINEAR_ACCEL, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);

    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_LINEAR_ACCEL);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_X);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), false);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 1.234, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_LINEAR_ACCEL);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_Y);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(1).valid(), false);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 4.567, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_LINEAR_ACCEL);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_Z);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(2).valid(), false);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 9.988, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_EstimatedAngularRate_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.234f);    //x
    bytes.append_float(4.567f);    //y
    bytes.append_float(9.988f);    //z
    bytes.append_uint16(0);        //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ANGULAR_RATE, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);

    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ANGULAR_RATE);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_X);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), false);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 1.234, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ANGULAR_RATE);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_Y);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(1).valid(), false);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 4.567, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ANGULAR_RATE);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_Z);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(2).valid(), false);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 9.988, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_WGS84LocalGravMagnitude_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(456.123f);    //gravity magnitude
    bytes.append_uint16(1);        //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_WGS84_LOC_GRAV_MAGNITUDE, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 1);
    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_WGS84_LOC_GRAV_MAGNITUDE);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_MAGNITUDE);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), true);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 456.123, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_EstimatedAttQuaternUncertainty_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.234f);    //q0
    bytes.append_float(4.567f);    //q1
    bytes.append_float(9.988f);    //q2
    bytes.append_float(0.001f);    //q3
    bytes.append_uint16(1);        //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ATT_UNCERT_QUAT, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 1);
    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ATT_UNCERT_QUAT);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_QUATERNION);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_Vector);
    BOOST_CHECK_EQUAL(data.at(0).valid(), true);
    BOOST_CHECK_CLOSE(data.at(0).as_Vector().as_floatAt(0), 1.234, 0.0001);
    BOOST_CHECK_CLOSE(data.at(0).as_Vector().as_floatAt(1), 4.567, 0.0001);
    BOOST_CHECK_CLOSE(data.at(0).as_Vector().as_floatAt(2), 9.988, 0.0001);
    BOOST_CHECK_CLOSE(data.at(0).as_Vector().as_floatAt(3), 0.001, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_EstimatedGravityVector_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.234f);    //x
    bytes.append_float(4.567f);    //y
    bytes.append_float(9.988f);    //z
    bytes.append_uint16(0);        //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_GRAVITY_VECTOR, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);

    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_GRAVITY_VECTOR);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_X);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), false);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 1.234, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_GRAVITY_VECTOR);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_Y);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(1).valid(), false);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 4.567, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_GRAVITY_VECTOR);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_Z);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(2).valid(), false);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 9.988, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_HeadingUpdateSource_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.234f);    //heading
    bytes.append_float(4.567f);    //uncertaininty
    bytes.append_uint16(10);    //source
    bytes.append_uint16(0);        //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_HEADING_UPDATE_SOURCE, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);

    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_HEADING_UPDATE_SOURCE);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_HEADING);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), false);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 1.234, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_ESTFILTER_HEADING_UPDATE_SOURCE);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_HEADING_UNCERTAINTY);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(1).valid(), false);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 4.567, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_ESTFILTER_HEADING_UPDATE_SOURCE);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_SOURCE);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_uint16);
    BOOST_CHECK_EQUAL(data.at(2).valid(), false);
    BOOST_CHECK_EQUAL(data.at(2).as_uint16(), 10);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_MagneticModelSln_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.234f);    //intensity, north
    bytes.append_float(2.345f);    //intensity, east
    bytes.append_float(3.456f);    //intensity, down
    bytes.append_float(4.567f);    //inclination
    bytes.append_float(9.456f);    //declination
    bytes.append_uint16(1);        //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_MAGNETIC_MODEL_SLN, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    BOOST_CHECK_EQUAL(data.size(), 5);
    
    //intensity vector
    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_MAGNETIC_MODEL_SLN);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_NORTH);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), true);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 1.234, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_ESTFILTER_MAGNETIC_MODEL_SLN);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_EAST);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(1).valid(), true);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 2.345, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_ESTFILTER_MAGNETIC_MODEL_SLN);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_DOWN);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(2).valid(), true);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 3.456, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());

    //inclination
    BOOST_CHECK_EQUAL(data.at(3).field(), MipTypes::CH_FIELD_ESTFILTER_MAGNETIC_MODEL_SLN);
    BOOST_CHECK_EQUAL(data.at(3).qualifier(), MipTypes::CH_INCLINATION);
    BOOST_CHECK_EQUAL(data.at(3).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(3).valid(), true);
    BOOST_CHECK_CLOSE(data.at(3).as_float(), 4.567, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(3).channelName());

    //declination
    BOOST_CHECK_EQUAL(data.at(4).field(), MipTypes::CH_FIELD_ESTFILTER_MAGNETIC_MODEL_SLN);
    BOOST_CHECK_EQUAL(data.at(4).qualifier(), MipTypes::CH_DECLINATION);
    BOOST_CHECK_EQUAL(data.at(4).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(4).valid(), true);
    BOOST_CHECK_CLOSE(data.at(4).as_float(), 9.456, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(4).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_EstimatedGyroScaleFactor_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.978f);    //x
    bytes.append_float(4.789f);    //y
    bytes.append_float(16.001f);//z
    bytes.append_uint16(0);        //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_GYRO_SCALE_FACTOR, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);

    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_GYRO_SCALE_FACTOR);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_X);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), false);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 1.978, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_GYRO_SCALE_FACTOR);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_Y);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(1).valid(), false);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 4.789, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_GYRO_SCALE_FACTOR);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_Z);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(2).valid(), false);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 16.001, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_EstimatedAccelScaleFactor_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.978f);    //x
    bytes.append_float(4.789f);    //y
    bytes.append_float(16.001f);//z
    bytes.append_uint16(1);        //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_ACCEL_SCALE_FACTOR, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);

    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_ACCEL_SCALE_FACTOR);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_X);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), true);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 1.978, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_ESTFILTER_ACCEL_SCALE_FACTOR);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_Y);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(1).valid(), true);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 4.789, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_ESTFILTER_ACCEL_SCALE_FACTOR);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_Z);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(2).valid(), true);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 16.001, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_EstimatedGyroScaleFactorUncert_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.978f);    //x
    bytes.append_float(4.789f);    //y
    bytes.append_float(16.001f);//z
    bytes.append_uint16(0);        //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_GYRO_SCALE_FACTOR_UNCERT, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);

    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_GYRO_SCALE_FACTOR_UNCERT);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_X);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), false);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 1.978, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_ESTFILTER_GYRO_SCALE_FACTOR_UNCERT);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_Y);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(1).valid(), false);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 4.789, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_ESTFILTER_GYRO_SCALE_FACTOR_UNCERT);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_Z);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(2).valid(), false);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 16.001, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_EstimatedAccelScaleFactorUncert_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.978f);    //x
    bytes.append_float(4.789f);    //y
    bytes.append_float(16.001f);//z
    bytes.append_uint16(0);        //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_ACCEL_SCALE_FACTOR_UNCERT, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);

    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_ACCEL_SCALE_FACTOR_UNCERT);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_X);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), false);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 1.978, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_ESTFILTER_ACCEL_SCALE_FACTOR_UNCERT);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_Y);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(1).valid(), false);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 4.789, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_ESTFILTER_ACCEL_SCALE_FACTOR_UNCERT);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_Z);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(2).valid(), false);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 16.001, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_CompensatedAccel_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.978f);    //x
    bytes.append_float(4.789f);    //y
    bytes.append_float(16.001f);//z
    bytes.append_uint16(0);        //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_COMPENSATED_ACCEL, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);

    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_COMPENSATED_ACCEL);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_X);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), false);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 1.978, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_ESTFILTER_COMPENSATED_ACCEL);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_Y);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(1).valid(), false);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 4.789, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_ESTFILTER_COMPENSATED_ACCEL);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_Z);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(2).valid(), false);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 16.001, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_StdAtmModel_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.978f);    //geometric altitude
    bytes.append_float(4.789f);    //geopotential altitude
    bytes.append_float(16.001f);//temperature
    bytes.append_float(16.001f);//pressure
    bytes.append_float(16.001f);//density
    bytes.append_uint16(0);        //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_STD_ATMOSPHERE_MODEL, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 5);

    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_STD_ATMOSPHERE_MODEL);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_GEOMETRIC_ALTITUDE);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), false);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 1.978, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_ESTFILTER_STD_ATMOSPHERE_MODEL);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_GEOPOTENTIAL_ALTITUDE);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(1).valid(), false);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 4.789, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_ESTFILTER_STD_ATMOSPHERE_MODEL);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_TEMPERATURE);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(2).valid(), false);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 16.001, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());

    BOOST_CHECK_EQUAL(data.at(3).field(), MipTypes::CH_FIELD_ESTFILTER_STD_ATMOSPHERE_MODEL);
    BOOST_CHECK_EQUAL(data.at(3).qualifier(), MipTypes::CH_PRESSURE);
    BOOST_CHECK_EQUAL(data.at(3).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(3).valid(), false);
    BOOST_CHECK_CLOSE(data.at(3).as_float(), 16.001, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(3).channelName());

    BOOST_CHECK_EQUAL(data.at(4).field(), MipTypes::CH_FIELD_ESTFILTER_STD_ATMOSPHERE_MODEL);
    BOOST_CHECK_EQUAL(data.at(4).qualifier(), MipTypes::CH_DENSITY);
    BOOST_CHECK_EQUAL(data.at(4).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(4).valid(), false);
    BOOST_CHECK_CLOSE(data.at(4).as_float(), 16.001, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(4).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_PressureAltitude_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(0.4672f);    //geometric altitude
    bytes.append_uint16(0);            //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_PRESSURE_ALTITUDE, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 1);

    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_PRESSURE_ALTITUDE);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_ALTITUDE);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), false);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 0.4672, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_GpsAntennaOffsetCorrection_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.978f);    //x
    bytes.append_float(4.789f);    //y
    bytes.append_float(16.001f);//z
    bytes.append_uint16(0);        //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);

    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_X);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), false);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 1.978, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_Y);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(1).valid(), false);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 4.789, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_Z);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(2).valid(), false);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 16.001, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_GpsAntennaOffsetCorrectionUncert_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.978f);    //x
    bytes.append_float(4.789f);    //y
    bytes.append_float(16.001f);//z
    bytes.append_uint16(0);        //flags

    //Create the Data Field
    MipDataField field(MipTypes::CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION_UNCERT, bytes.data());

    MipDataPoints data;

    MipFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);

    BOOST_CHECK_EQUAL(data.at(0).field(), MipTypes::CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION_UNCERT);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), MipTypes::CH_X);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), false);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 1.978, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), MipTypes::CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION_UNCERT);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), MipTypes::CH_Y);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(1).valid(), false);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 4.789, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), MipTypes::CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION_UNCERT);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), MipTypes::CH_Z);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(2).valid(), false);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 16.001, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_SUITE_END()