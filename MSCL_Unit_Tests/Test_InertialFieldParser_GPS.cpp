/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Inertial/Packets/InertialFieldParser.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialDataPacket.h"
#include "mscl/MicroStrain/Inertial/InertialDataPoint.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialFieldParser_GPS.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(InertialFieldParser_GPS_Test)

BOOST_AUTO_TEST_CASE(InertialFieldParser_LLHPosition_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_double(1.2);        //latitude
    bytes.append_double(3.4);        //longitude
    bytes.append_double(5.67);        //height above ellipsoid
    bytes.append_double(7.89);        //height above MSL
    bytes.append_float(1.23f);        //horizontal accuracy
    bytes.append_float(2.34f);        //vertical accuracy
    bytes.append_uint16(29);        //valid flags (0001 1101)

    //Create the Data Field
    InertialDataField field(InertialTypes::CH_FIELD_GPS_LLH_POSITION, bytes.data());

    InertialDataPoints data;

    InertialFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 6);

    //Latitude
    BOOST_CHECK_EQUAL(data.at(0).field(), InertialTypes::CH_FIELD_GPS_LLH_POSITION);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), InertialTypes::CH_LATITUDE);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_double);
    BOOST_CHECK_EQUAL(data.at(0).valid(), true);
    BOOST_CHECK_CLOSE(data.at(0).as_double(), 1.2, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    //Longitude
    BOOST_CHECK_EQUAL(data.at(1).field(), InertialTypes::CH_FIELD_GPS_LLH_POSITION);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), InertialTypes::CH_LONGITUDE);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_double);
    BOOST_CHECK_EQUAL(data.at(1).valid(), true);
    BOOST_CHECK_CLOSE(data.at(1).as_double(), 3.4, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    //Height Above Ellipsoid
    BOOST_CHECK_EQUAL(data.at(2).field(), InertialTypes::CH_FIELD_GPS_LLH_POSITION);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), InertialTypes::CH_HEIGHT_ABOVE_ELLIPSOID);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_double);
    BOOST_CHECK_EQUAL(data.at(2).valid(), false);
    BOOST_CHECK_CLOSE(data.at(2).as_double(), 5.67, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());

    //Height Above MSL
    BOOST_CHECK_EQUAL(data.at(3).field(), InertialTypes::CH_FIELD_GPS_LLH_POSITION);
    BOOST_CHECK_EQUAL(data.at(3).qualifier(), InertialTypes::CH_HEIGHT_ABOVE_MSL);
    BOOST_CHECK_EQUAL(data.at(3).storedAs(), valueType_double);
    BOOST_CHECK_EQUAL(data.at(3).valid(), true);
    BOOST_CHECK_CLOSE(data.at(3).as_double(), 7.89, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(3).channelName());

    //Horizontal Accuracy
    BOOST_CHECK_EQUAL(data.at(4).field(), InertialTypes::CH_FIELD_GPS_LLH_POSITION);
    BOOST_CHECK_EQUAL(data.at(4).qualifier(), InertialTypes::CH_HORIZONTAL_ACCURACY);
    BOOST_CHECK_EQUAL(data.at(4).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(4).valid(), true);
    BOOST_CHECK_CLOSE(data.at(4).as_double(), 1.23, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(4).channelName());

    //Vertical Accuracy
    BOOST_CHECK_EQUAL(data.at(5).field(), InertialTypes::CH_FIELD_GPS_LLH_POSITION);
    BOOST_CHECK_EQUAL(data.at(5).qualifier(), InertialTypes::CH_VERTICAL_ACCURACY);
    BOOST_CHECK_EQUAL(data.at(5).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(5).valid(), true);
    BOOST_CHECK_CLOSE(data.at(5).as_double(), 2.34, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(5).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_ECEFPosition_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_double(1.2);        //x position
    bytes.append_double(3.4);        //y position
    bytes.append_double(5.67);        //z position
    bytes.append_float(7.89f);        //position accuracy
    bytes.append_uint16(2);            //valid flags (0000 0010)

    //Create the Data Field
    InertialDataField field(InertialTypes::CH_FIELD_GPS_ECEF_POSITION, bytes.data());

    InertialDataPoints data;

    InertialFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 4);

    //x position
    BOOST_CHECK_EQUAL(data.at(0).field(), InertialTypes::CH_FIELD_GPS_ECEF_POSITION);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), InertialTypes::CH_X);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_double);
    BOOST_CHECK_EQUAL(data.at(0).valid(), false);
    BOOST_CHECK_CLOSE(data.at(0).as_double(), 1.2, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    //y position
    BOOST_CHECK_EQUAL(data.at(1).field(), InertialTypes::CH_FIELD_GPS_ECEF_POSITION);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), InertialTypes::CH_Y);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_double);
    BOOST_CHECK_EQUAL(data.at(1).valid(), false);
    BOOST_CHECK_CLOSE(data.at(1).as_double(), 3.4, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    //z position
    BOOST_CHECK_EQUAL(data.at(2).field(), InertialTypes::CH_FIELD_GPS_ECEF_POSITION);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), InertialTypes::CH_Z);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_double);
    BOOST_CHECK_EQUAL(data.at(2).valid(), false);
    BOOST_CHECK_CLOSE(data.at(2).as_double(), 5.67, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());

    //position accuracy
    BOOST_CHECK_EQUAL(data.at(3).field(), InertialTypes::CH_FIELD_GPS_ECEF_POSITION);
    BOOST_CHECK_EQUAL(data.at(3).qualifier(), InertialTypes::CH_POSITION_ACCURACY);
    BOOST_CHECK_EQUAL(data.at(3).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(3).valid(), true);
    BOOST_CHECK_CLOSE(data.at(3).as_double(), 7.89, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(3).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_NEDVelocity_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.1f);    //north
    bytes.append_float(2.2f);    //east
    bytes.append_float(3.3f);    //down
    bytes.append_float(4.4f);    //speed
    bytes.append_float(5.5f);    //ground speed
    bytes.append_float(6.6f);    //heading
    bytes.append_float(7.7f);    //speed accuracy
    bytes.append_float(8.8f);    //heading accuracy
    bytes.append_uint16(41);    //valid flags (0010 1001)

    //Create the Data Field
    InertialDataField field(InertialTypes::CH_FIELD_GPS_NED_VELOCITY, bytes.data());

    InertialDataPoints data;

    InertialFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 8);

    //north
    BOOST_CHECK_EQUAL(data.at(0).field(), InertialTypes::CH_FIELD_GPS_NED_VELOCITY);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), InertialTypes::CH_NORTH);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), true);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 1.1, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    //east
    BOOST_CHECK_EQUAL(data.at(1).field(), InertialTypes::CH_FIELD_GPS_NED_VELOCITY);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), InertialTypes::CH_EAST);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(1).valid(), true);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 2.2, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    //down
    BOOST_CHECK_EQUAL(data.at(2).field(), InertialTypes::CH_FIELD_GPS_NED_VELOCITY);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), InertialTypes::CH_DOWN);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(2).valid(), true);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 3.3, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());

    //speed
    BOOST_CHECK_EQUAL(data.at(3).field(), InertialTypes::CH_FIELD_GPS_NED_VELOCITY);
    BOOST_CHECK_EQUAL(data.at(3).qualifier(), InertialTypes::CH_SPEED);
    BOOST_CHECK_EQUAL(data.at(3).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(3).valid(), false);
    BOOST_CHECK_CLOSE(data.at(3).as_float(), 4.4, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(3).channelName());

    //ground speed
    BOOST_CHECK_EQUAL(data.at(4).field(), InertialTypes::CH_FIELD_GPS_NED_VELOCITY);
    BOOST_CHECK_EQUAL(data.at(4).qualifier(), InertialTypes::CH_GROUND_SPEED);
    BOOST_CHECK_EQUAL(data.at(4).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(4).valid(), false);
    BOOST_CHECK_CLOSE(data.at(4).as_float(), 5.5, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(4).channelName());

    //heading
    BOOST_CHECK_EQUAL(data.at(5).field(), InertialTypes::CH_FIELD_GPS_NED_VELOCITY);
    BOOST_CHECK_EQUAL(data.at(5).qualifier(), InertialTypes::CH_HEADING);
    BOOST_CHECK_EQUAL(data.at(5).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(5).valid(), true);
    BOOST_CHECK_CLOSE(data.at(5).as_float(), 6.6, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(5).channelName());

    //speed accuracy
    BOOST_CHECK_EQUAL(data.at(6).field(), InertialTypes::CH_FIELD_GPS_NED_VELOCITY);
    BOOST_CHECK_EQUAL(data.at(6).qualifier(), InertialTypes::CH_SPEED_ACCURACY);
    BOOST_CHECK_EQUAL(data.at(6).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(6).valid(), false);
    BOOST_CHECK_CLOSE(data.at(6).as_float(), 7.7, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(6).channelName());

    //heading accuracy
    BOOST_CHECK_EQUAL(data.at(7).field(), InertialTypes::CH_FIELD_GPS_NED_VELOCITY);
    BOOST_CHECK_EQUAL(data.at(7).qualifier(), InertialTypes::CH_HEADING_ACCURACY);
    BOOST_CHECK_EQUAL(data.at(7).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(7).valid(), true);
    BOOST_CHECK_CLOSE(data.at(7).as_float(), 8.8, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(7).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_ECEFVelocity_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.1f);    //x
    bytes.append_float(2.2f);    //y
    bytes.append_float(3.3f);    //z
    bytes.append_float(4.4f);    //velocity accuracy
    bytes.append_uint16(1);        //valid flags (0000 0001)

    //Create the Data Field
    InertialDataField field(InertialTypes::CH_FIELD_GPS_ECEF_VELOCITY, bytes.data());

    InertialDataPoints data;

    InertialFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 4);

    //X
    BOOST_CHECK_EQUAL(data.at(0).field(), InertialTypes::CH_FIELD_GPS_ECEF_VELOCITY);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), InertialTypes::CH_X);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), true);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 1.1, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    //Y
    BOOST_CHECK_EQUAL(data.at(1).field(), InertialTypes::CH_FIELD_GPS_ECEF_VELOCITY);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), InertialTypes::CH_Y);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(1).valid(), true);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 2.2, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    //Z
    BOOST_CHECK_EQUAL(data.at(2).field(), InertialTypes::CH_FIELD_GPS_ECEF_VELOCITY);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), InertialTypes::CH_Z);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(2).valid(), true);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 3.3, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());

    //ACCURACY
    BOOST_CHECK_EQUAL(data.at(3).field(), InertialTypes::CH_FIELD_GPS_ECEF_VELOCITY);
    BOOST_CHECK_EQUAL(data.at(3).qualifier(), InertialTypes::CH_VELOCITY_ACCURACY);
    BOOST_CHECK_EQUAL(data.at(3).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(3).valid(), false);
    BOOST_CHECK_CLOSE(data.at(3).as_float(), 4.4, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(3).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_DOP_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(1.1f);    //geometric
    bytes.append_float(2.2f);    //position
    bytes.append_float(3.3f);    //horizontal
    bytes.append_float(4.4f);    //vertical
    bytes.append_float(5.5f);    //time
    bytes.append_float(6.6f);    //northing
    bytes.append_float(7.7f);    //easting
    bytes.append_uint16(112);    //valid flags (0111 0000)

    //Create the Data Field
    InertialDataField field(InertialTypes::CH_FIELD_GPS_DOP, bytes.data());

    InertialDataPoints data;

    InertialFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 7);

    //GEOMETRIC
    BOOST_CHECK_EQUAL(data.at(0).field(), InertialTypes::CH_FIELD_GPS_DOP);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), InertialTypes::CH_GEOMETRIC_DOP);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), false);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 1.1, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    //position
    BOOST_CHECK_EQUAL(data.at(1).field(), InertialTypes::CH_FIELD_GPS_DOP);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), InertialTypes::CH_POSITION_DOP);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(1).valid(), false);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 2.2, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    //horizontal
    BOOST_CHECK_EQUAL(data.at(2).field(), InertialTypes::CH_FIELD_GPS_DOP);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), InertialTypes::CH_HORIZONTAL_DOP);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(2).valid(), false);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 3.3, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());

    //vertical
    BOOST_CHECK_EQUAL(data.at(3).field(), InertialTypes::CH_FIELD_GPS_DOP);
    BOOST_CHECK_EQUAL(data.at(3).qualifier(), InertialTypes::CH_VERTICAL_DOP);
    BOOST_CHECK_EQUAL(data.at(3).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(3).valid(), false);
    BOOST_CHECK_CLOSE(data.at(3).as_float(), 4.4, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(3).channelName());

    //time
    BOOST_CHECK_EQUAL(data.at(4).field(), InertialTypes::CH_FIELD_GPS_DOP);
    BOOST_CHECK_EQUAL(data.at(4).qualifier(), InertialTypes::CH_TIME_DOP);
    BOOST_CHECK_EQUAL(data.at(4).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(4).valid(), true);
    BOOST_CHECK_CLOSE(data.at(4).as_float(), 5.5, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(4).channelName());

    //northing
    BOOST_CHECK_EQUAL(data.at(5).field(), InertialTypes::CH_FIELD_GPS_DOP);
    BOOST_CHECK_EQUAL(data.at(5).qualifier(), InertialTypes::CH_NORTHING_DOP);
    BOOST_CHECK_EQUAL(data.at(5).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(5).valid(), true);
    BOOST_CHECK_CLOSE(data.at(5).as_float(), 6.6, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(5).channelName());

    //easting
    BOOST_CHECK_EQUAL(data.at(6).field(), InertialTypes::CH_FIELD_GPS_DOP);
    BOOST_CHECK_EQUAL(data.at(6).qualifier(), InertialTypes::CH_EASTING_DOP);
    BOOST_CHECK_EQUAL(data.at(6).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(6).valid(), true);
    BOOST_CHECK_CLOSE(data.at(6).as_float(), 7.7, 0.0001);
    BOOST_CHECK_NO_THROW(data.at(6).channelName());

}

BOOST_AUTO_TEST_CASE(InertialFieldParser_UTCTime_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_uint16(2013);    //year
    bytes.append_uint8(3);        //month
    bytes.append_uint8(18);        //day
    bytes.append_uint8(13);        //hour
    bytes.append_uint8(26);        //minute
    bytes.append_uint8(57);        //seconds
    bytes.append_uint32(123);    //milliseconds
    bytes.append_uint16(3);        //flags (0000 0011)

    //Create the Data Field
    InertialDataField field(InertialTypes::CH_FIELD_GPS_UTC_TIME, bytes.data());

    InertialDataPoints data;

    InertialFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 2);

    //timestamp
    BOOST_CHECK_EQUAL(data.at(0).field(), InertialTypes::CH_FIELD_GPS_UTC_TIME);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), InertialTypes::CH_TIMESTAMP);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_Timestamp);
    BOOST_CHECK_EQUAL(data.at(0).valid(), true);
    BOOST_CHECK_EQUAL(data.at(0).as_Timestamp().nanoseconds(), 1363613217123000000);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    //flags
    BOOST_CHECK_EQUAL(data.at(1).field(), InertialTypes::CH_FIELD_GPS_UTC_TIME);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), InertialTypes::CH_FLAGS);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_uint16);
    BOOST_CHECK_EQUAL(data.at(1).valid(), true);
    BOOST_CHECK_EQUAL(data.at(1).as_uint16(), 3);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_GPSTime_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_double(753.159);    //time of week
    bytes.append_uint16(129);        //week number
    bytes.append_uint16(1);            //flags (0000 0001)

    //Create the Data Field
    InertialDataField field(InertialTypes::CH_FIELD_GPS_GPS_TIME, bytes.data());

    InertialDataPoints data;

    InertialFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 2);

    //timestamp
    BOOST_CHECK_EQUAL(data.at(0).field(), InertialTypes::CH_FIELD_GPS_GPS_TIME);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), InertialTypes::CH_TIME_OF_WEEK);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_double);
    BOOST_CHECK_EQUAL(data.at(0).valid(), true);
    BOOST_CHECK_EQUAL(data.at(0).as_double(), 753.159);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    //week number
    BOOST_CHECK_EQUAL(data.at(1).field(), InertialTypes::CH_FIELD_GPS_GPS_TIME);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), InertialTypes::CH_WEEK_NUMBER);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_uint16);
    BOOST_CHECK_EQUAL(data.at(1).valid(), false);
    BOOST_CHECK_EQUAL(data.at(1).as_uint16(), 129);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_ClockInfo_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_double(1.234);        //clock bias
    bytes.append_double(2.345);        //clock drift
    bytes.append_double(3.456);        //accuracy estimate
    bytes.append_uint16(3);            //flags (0000 0011)

    //Create the Data Field
    InertialDataField field(InertialTypes::CH_FIELD_GPS_CLOCK_INFO, bytes.data());

    InertialDataPoints data;

    InertialFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);

    //clock bias
    BOOST_CHECK_EQUAL(data.at(0).field(), InertialTypes::CH_FIELD_GPS_CLOCK_INFO);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), InertialTypes::CH_BIAS);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_double);
    BOOST_CHECK_EQUAL(data.at(0).valid(), true);
    BOOST_CHECK_EQUAL(data.at(0).as_double(), 1.234);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    //clock drift
    BOOST_CHECK_EQUAL(data.at(1).field(), InertialTypes::CH_FIELD_GPS_CLOCK_INFO);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), InertialTypes::CH_DRIFT);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_double);
    BOOST_CHECK_EQUAL(data.at(1).valid(), true);
    BOOST_CHECK_EQUAL(data.at(1).as_double(), 2.345);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    //accuracy estimate
    BOOST_CHECK_EQUAL(data.at(2).field(), InertialTypes::CH_FIELD_GPS_CLOCK_INFO);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), InertialTypes::CH_ACCURACY_ESTIMATE);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_double);
    BOOST_CHECK_EQUAL(data.at(2).valid(), false);
    BOOST_CHECK_EQUAL(data.at(2).as_double(), 3.456);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_GPSFixInfo_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_uint8(2);        //fix type
    bytes.append_uint8(200);    //number of SVs used for solution
    bytes.append_uint16(1);        //fix flags
    bytes.append_uint16(7);        //flags (0000 0111)

    //Create the Data Field
    InertialDataField field(InertialTypes::CH_FIELD_GPS_FIX_INFO, bytes.data());

    InertialDataPoints data;

    InertialFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);

    //fix type
    BOOST_CHECK_EQUAL(data.at(0).field(), InertialTypes::CH_FIELD_GPS_FIX_INFO);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), InertialTypes::CH_FIX_TYPE);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_uint8);
    BOOST_CHECK_EQUAL(data.at(0).valid(), true);
    BOOST_CHECK_EQUAL(data.at(0).as_uint8(), InertialDataEnums::FIXTYPE_TIMEONLY);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    //number of SVs used for solution
    BOOST_CHECK_EQUAL(data.at(1).field(), InertialTypes::CH_FIELD_GPS_FIX_INFO);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), InertialTypes::CH_SV_COUNT);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_uint8);
    BOOST_CHECK_EQUAL(data.at(1).valid(), true);
    BOOST_CHECK_EQUAL(data.at(1).as_uint8(), 200);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    //fix flags
    BOOST_CHECK_EQUAL(data.at(2).field(), InertialTypes::CH_FIELD_GPS_FIX_INFO);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), InertialTypes::CH_FLAGS);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_uint16);
    BOOST_CHECK_EQUAL(data.at(2).valid(), true);
    BOOST_CHECK_EQUAL(data.at(2).as_double(), 1);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_SpaceVehicleInfo_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_uint8(1);        //channel
    bytes.append_uint8(2);        //vehicle id
    bytes.append_uint16(3);        //carrier to noise ratio
    bytes.append_int16(-123);    //azimuth
    bytes.append_int16(-32000);    //elevation
    bytes.append_uint16(2);        //space vehicle flags
    bytes.append_uint16(45);    //flags (0010 1101)

    //Create the Data Field
    InertialDataField field(InertialTypes::CH_FIELD_GPS_SPACE_VEHICLE_INFO, bytes.data());

    InertialDataPoints data;

    InertialFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 6);

    //channel
    BOOST_CHECK_EQUAL(data.at(0).field(), InertialTypes::CH_FIELD_GPS_SPACE_VEHICLE_INFO);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), InertialTypes::CH_CHANNEL);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_uint8);
    BOOST_CHECK_EQUAL(data.at(0).valid(), true);
    BOOST_CHECK_EQUAL(data.at(0).as_uint8(), 1);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    //space vehicle id
    BOOST_CHECK_EQUAL(data.at(1).field(), InertialTypes::CH_FIELD_GPS_SPACE_VEHICLE_INFO);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), InertialTypes::CH_ID);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_uint8);
    BOOST_CHECK_EQUAL(data.at(1).valid(), false);
    BOOST_CHECK_EQUAL(data.at(1).as_uint8(), 2);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    //carrier to noise ratio
    BOOST_CHECK_EQUAL(data.at(2).field(), InertialTypes::CH_FIELD_GPS_SPACE_VEHICLE_INFO);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), InertialTypes::CH_CARRIER_TO_NOISE_RATIO);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_uint16);
    BOOST_CHECK_EQUAL(data.at(2).valid(), true);
    BOOST_CHECK_EQUAL(data.at(2).as_uint16(), 3);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());

    //azimuth
    BOOST_CHECK_EQUAL(data.at(3).field(), InertialTypes::CH_FIELD_GPS_SPACE_VEHICLE_INFO);
    BOOST_CHECK_EQUAL(data.at(3).qualifier(), InertialTypes::CH_AZIMUTH);
    BOOST_CHECK_EQUAL(data.at(3).storedAs(), valueType_int16);
    BOOST_CHECK_EQUAL(data.at(3).valid(), true);
    BOOST_CHECK_EQUAL(data.at(3).as_int16(), -123);
    BOOST_CHECK_NO_THROW(data.at(3).channelName());

    //elevation
    BOOST_CHECK_EQUAL(data.at(4).field(), InertialTypes::CH_FIELD_GPS_SPACE_VEHICLE_INFO);
    BOOST_CHECK_EQUAL(data.at(4).qualifier(), InertialTypes::CH_ELEVATION);
    BOOST_CHECK_EQUAL(data.at(4).storedAs(), valueType_int16);
    BOOST_CHECK_EQUAL(data.at(4).valid(), false);
    BOOST_CHECK_EQUAL(data.at(4).as_int16(), -32000);
    BOOST_CHECK_NO_THROW(data.at(4).channelName());

    //space vehicle flags
    BOOST_CHECK_EQUAL(data.at(5).field(), InertialTypes::CH_FIELD_GPS_SPACE_VEHICLE_INFO);
    BOOST_CHECK_EQUAL(data.at(5).qualifier(), InertialTypes::CH_FLAGS);
    BOOST_CHECK_EQUAL(data.at(5).storedAs(), valueType_uint16);
    BOOST_CHECK_EQUAL(data.at(5).valid(), true);
    BOOST_CHECK_EQUAL(data.at(5).as_uint16(), 2);
    BOOST_CHECK_NO_THROW(data.at(5).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_HardwareStatus_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_uint8(0);        //sensor state
    bytes.append_uint8(1);        //antenna state
    bytes.append_uint8(2);        //antenna power
    bytes.append_uint16(7);        //flags (0000 0111)

    //Create the Data Field
    InertialDataField field(InertialTypes::CH_FIELD_GPS_HARDWARE_STATUS, bytes.data());

    InertialDataPoints data;

    InertialFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 3);

    //sensor state
    BOOST_CHECK_EQUAL(data.at(0).field(), InertialTypes::CH_FIELD_GPS_HARDWARE_STATUS);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), InertialTypes::CH_SENSOR_STATE);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_uint8);
    BOOST_CHECK_EQUAL(data.at(0).valid(), true);
    BOOST_CHECK_EQUAL(data.at(0).as_uint8(), InertialDataEnums::SENSORSTATE_OFF);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    //antenna state
    BOOST_CHECK_EQUAL(data.at(1).field(), InertialTypes::CH_FIELD_GPS_HARDWARE_STATUS);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), InertialTypes::CH_ANTENNA_STATE);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_uint8);
    BOOST_CHECK_EQUAL(data.at(1).valid(), true);
    BOOST_CHECK_EQUAL(data.at(1).as_uint8(), InertialDataEnums::ANTENNASTATE_INIT);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    //antenna power
    BOOST_CHECK_EQUAL(data.at(2).field(), InertialTypes::CH_FIELD_GPS_HARDWARE_STATUS);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), InertialTypes::CH_ANTENNA_POWER);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_uint8);
    BOOST_CHECK_EQUAL(data.at(2).valid(), true);
    BOOST_CHECK_EQUAL(data.at(2).as_uint8(), InertialDataEnums::ANTENNAPOWER_UNKNOWN);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_DgpsInfo_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_float(5.4f);    //newest age
    bytes.append_int16(1);        //base station id
    bytes.append_int16(2);        //base station status
    bytes.append_uint16(3);        //number of dgps channels
    bytes.append_uint16(7);        //flags (0000 0111)

    //Create the Data Field
    InertialDataField field(InertialTypes::CH_FIELD_GPS_DGPS_INFO, bytes.data());

    InertialDataPoints data;

    InertialFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 4);

    BOOST_CHECK_EQUAL(data.at(0).field(), InertialTypes::CH_FIELD_GPS_DGPS_INFO);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), InertialTypes::CH_AGE);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(0).valid(), true);
    BOOST_CHECK_CLOSE(data.at(0).as_float(), 5.4, 0.001);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), InertialTypes::CH_FIELD_GPS_DGPS_INFO);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), InertialTypes::CH_ID);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_int16);
    BOOST_CHECK_EQUAL(data.at(1).valid(), true);
    BOOST_CHECK_EQUAL(data.at(1).as_int16(), 1);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), InertialTypes::CH_FIELD_GPS_DGPS_INFO);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), InertialTypes::CH_STATUS);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_int16);
    BOOST_CHECK_EQUAL(data.at(2).valid(), true);
    BOOST_CHECK_EQUAL(data.at(2).as_int16(), 2);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());

    BOOST_CHECK_EQUAL(data.at(3).field(), InertialTypes::CH_FIELD_GPS_DGPS_INFO);
    BOOST_CHECK_EQUAL(data.at(3).qualifier(), InertialTypes::CH_NUM_CHANNELS);
    BOOST_CHECK_EQUAL(data.at(3).storedAs(), valueType_uint16);
    BOOST_CHECK_EQUAL(data.at(3).valid(), false);
    BOOST_CHECK_EQUAL(data.at(3).as_uint16(), 3);
    BOOST_CHECK_NO_THROW(data.at(3).channelName());
}

BOOST_AUTO_TEST_CASE(InertialFieldParser_DgpsChannelStatus_parse)
{
    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_uint8(1);        //space vehicle id
    bytes.append_float(1.23f);    //age
    bytes.append_float(7.125f);    //pseudorange correction
    bytes.append_float(457.01f);//pseudorange rate correction
    bytes.append_uint16(15);    //flags (0000 1111)

    //Create the Data Field
    InertialDataField field(InertialTypes::CH_FIELD_GPS_DGPS_CHANNEL_STATUS, bytes.data());

    InertialDataPoints data;

    InertialFieldParser::parseField(field, data);

    //verify the field was parsed correctly
    BOOST_CHECK_EQUAL(data.size(), 4);

    BOOST_CHECK_EQUAL(data.at(0).field(), InertialTypes::CH_FIELD_GPS_DGPS_CHANNEL_STATUS);
    BOOST_CHECK_EQUAL(data.at(0).qualifier(), InertialTypes::CH_ID);
    BOOST_CHECK_EQUAL(data.at(0).storedAs(), valueType_uint8);
    BOOST_CHECK_EQUAL(data.at(0).valid(), true);
    BOOST_CHECK_EQUAL(data.at(0).as_uint8(), 1);
    BOOST_CHECK_NO_THROW(data.at(0).channelName());

    BOOST_CHECK_EQUAL(data.at(1).field(), InertialTypes::CH_FIELD_GPS_DGPS_CHANNEL_STATUS);
    BOOST_CHECK_EQUAL(data.at(1).qualifier(), InertialTypes::CH_AGE);
    BOOST_CHECK_EQUAL(data.at(1).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(1).valid(), true);
    BOOST_CHECK_CLOSE(data.at(1).as_float(), 1.23, 0.001);
    BOOST_CHECK_NO_THROW(data.at(1).channelName());

    BOOST_CHECK_EQUAL(data.at(2).field(), InertialTypes::CH_FIELD_GPS_DGPS_CHANNEL_STATUS);
    BOOST_CHECK_EQUAL(data.at(2).qualifier(), InertialTypes::CH_CORRECTION);
    BOOST_CHECK_EQUAL(data.at(2).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(2).valid(), true);
    BOOST_CHECK_CLOSE(data.at(2).as_float(), 7.125, 0.001);
    BOOST_CHECK_NO_THROW(data.at(2).channelName());

    BOOST_CHECK_EQUAL(data.at(3).field(), InertialTypes::CH_FIELD_GPS_DGPS_CHANNEL_STATUS);
    BOOST_CHECK_EQUAL(data.at(3).qualifier(), InertialTypes::CH_RATE_CORRECTION);
    BOOST_CHECK_EQUAL(data.at(3).storedAs(), valueType_float);
    BOOST_CHECK_EQUAL(data.at(3).valid(), true);
    BOOST_CHECK_CLOSE(data.at(3).as_float(), 457.01, 0.001);
    BOOST_CHECK_NO_THROW(data.at(3).channelName());
}

BOOST_AUTO_TEST_SUITE_END()