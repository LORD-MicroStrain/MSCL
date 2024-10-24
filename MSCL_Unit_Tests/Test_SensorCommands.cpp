/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Inertial/Commands/Sensor_Commands.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/ResponseCollector.h"

#include <boost/test/unit_test.hpp>
using namespace mscl;

BOOST_AUTO_TEST_SUITE(SensorCommands_Test)

BOOST_AUTO_TEST_SUITE(SensorCommands_GetSensorDataRateBase)

BOOST_AUTO_TEST_CASE(GetSensorDataRateBase_buildCommand)
{
    ByteStream b = GetSensorDataRateBase::buildCommand();

    //Check all the bytes in the ByteStream
    BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
    BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
    BOOST_CHECK_EQUAL(b.read_uint8(2), 0x0C);
    BOOST_CHECK_EQUAL(b.read_uint8(3), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(4), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(5), 0x06);
    BOOST_CHECK_EQUAL(b.read_uint8(6), 0xF0);
    BOOST_CHECK_EQUAL(b.read_uint8(7), 0xF7);
}

BOOST_AUTO_TEST_CASE(GetSensorDataRateBase_parseData)
{
    ByteStream data;
    data.append_uint16(4000);

    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetSensorDataRateBase::Response response(rc);

    BOOST_CHECK_EQUAL(response.parseResponse(GenericMipCmdResponse::ResponseSuccess("", data)), 4000);
}

BOOST_AUTO_TEST_CASE(GetSensorDataRateBase_Match_Success)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetSensorDataRateBase::Response response(rc);

    Bytes ackData;
    ackData.push_back(0x06);
    ackData.push_back(0x00);
    MipDataField ackField(0x0CF1, ackData); //ack/nack field

    Bytes data;
    data.push_back(0x00);
    data.push_back(0x0A);
    MipDataField dataField(0x0C83, data); //data field

    //check that the match succeeds
    BOOST_CHECK_EQUAL(response.match(ackField), true);
    BOOST_CHECK_EQUAL(response.fullyMatched(), false);
    BOOST_CHECK_EQUAL(response.match(dataField), true);
    BOOST_CHECK_EQUAL(response.fullyMatched(), true);
    BOOST_CHECK_EQUAL(response.result().success(), true);
    BOOST_CHECK_EQUAL(response.result().errorCode(), mscl::MipPacket::MIP_ACK_NACK_ERROR_NONE);
}

BOOST_AUTO_TEST_SUITE_END()    //End GetSensorDataRateBase


BOOST_AUTO_TEST_SUITE(SensorCommands_SensorMessageFormat)

BOOST_AUTO_TEST_CASE(SensorMessageFormat_buildCommand_get)
{
    ByteStream b = SensorMessageFormat::buildCommand_get();

    //Check all the bytes in the ByteStream
    BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
    BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
    BOOST_CHECK_EQUAL(b.read_uint8(2), 0x0C);
    BOOST_CHECK_EQUAL(b.read_uint8(3), 0x04);
    BOOST_CHECK_EQUAL(b.read_uint8(4), 0x04);
    BOOST_CHECK_EQUAL(b.read_uint8(5), 0x08);
    BOOST_CHECK_EQUAL(b.read_uint8(6), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(7), 0x00);
    BOOST_CHECK_EQUAL(b.read_uint8(8), 0xF8);
    BOOST_CHECK_EQUAL(b.read_uint8(9), 0xF3);
}

BOOST_AUTO_TEST_CASE(SensorMessageFormat_buildCommand_set)
{
    SampleRate hz1 = SampleRate::Hertz(1);

    MipChannels chs;
    chs.push_back(MipChannel(MipTypes::CH_FIELD_SENSOR_SCALED_ACCEL_VEC, hz1));
    chs.push_back(MipChannel(MipTypes::CH_FIELD_SENSOR_SCALED_GYRO_VEC, hz1));

    ByteStream b = SensorMessageFormat::buildCommand_set(chs, 10);

    //Check all the bytes in the ByteStream
    BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
    BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
    BOOST_CHECK_EQUAL(b.read_uint8(2), 0x0C);
    BOOST_CHECK_EQUAL(b.read_uint8(3), 0x0A);
    BOOST_CHECK_EQUAL(b.read_uint8(4), 0x0A);
    BOOST_CHECK_EQUAL(b.read_uint8(5), 0x08);
    BOOST_CHECK_EQUAL(b.read_uint8(6), 0x01);
    BOOST_CHECK_EQUAL(b.read_uint8(7), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(8), 0x04);
    BOOST_CHECK_EQUAL(b.read_uint8(9), 0x00);
    BOOST_CHECK_EQUAL(b.read_uint8(10), 0x0A);
    BOOST_CHECK_EQUAL(b.read_uint8(11), 0x05);
    BOOST_CHECK_EQUAL(b.read_uint8(12), 0x00);
    BOOST_CHECK_EQUAL(b.read_uint8(13), 0x0A);
    BOOST_CHECK_EQUAL(b.read_uint8(14), 0x22);
    BOOST_CHECK_EQUAL(b.read_uint8(15), 0xA0);
}

BOOST_AUTO_TEST_CASE(SensorMessageFormat_parseData)
{
    ByteStream data;
    data.append_uint8(0x02);
    data.append_uint8(0x06);    //CH_AHRS_SCALED_MAG_VEC
    data.append_uint16(10);        //rate decimation
    data.append_uint8(0x09);    //CH_AHRS_ORIENTATION_MATRIX
    data.append_uint16(2);        //rate decimation

    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    SensorMessageFormat::Response response(rc, true);

    uint16 sampleRateBase = 50;

    MipChannels chs = response.parseResponse(GenericMipCmdResponse::ResponseSuccess("", data), sampleRateBase);

    BOOST_CHECK_EQUAL(chs.size(), 2);
    BOOST_CHECK_EQUAL(chs.at(0).channelField(), MipTypes::CH_FIELD_SENSOR_SCALED_MAG_VEC);
    BOOST_CHECK_EQUAL(chs.at(0).rateDecimation(sampleRateBase), 10);
    BOOST_CHECK_EQUAL(chs.at(0).sampleRate().samplesPerSecond(), SampleRate::Hertz(5).samplesPerSecond());
}

BOOST_AUTO_TEST_SUITE_END()    //End SensorMessageFormat


BOOST_AUTO_TEST_SUITE_END()
