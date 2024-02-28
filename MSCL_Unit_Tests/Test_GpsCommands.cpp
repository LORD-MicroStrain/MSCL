/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Inertial/Commands/GNSS_Commands.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/ResponseCollector.h"

#include <boost/test/unit_test.hpp>
using namespace mscl;

BOOST_AUTO_TEST_SUITE(GpsCommands_Test)

BOOST_AUTO_TEST_SUITE(GpsCommands_GetGpsDataRateBase)

BOOST_AUTO_TEST_CASE(GetGpsDataRateBase_buildCommand)
{
    ByteStream b = GetGnssDataRateBase::buildCommand();

    //Check all the bytes in the ByteStream
    BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
    BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
    BOOST_CHECK_EQUAL(b.read_uint8(2), 0x0C);
    BOOST_CHECK_EQUAL(b.read_uint8(3), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(4), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(5), 0x07);
    BOOST_CHECK_EQUAL(b.read_uint8(6), 0xF1);
    BOOST_CHECK_EQUAL(b.read_uint8(7), 0xF8);
}

BOOST_AUTO_TEST_CASE(GetGpsDataRateBase_parseData)
{
    ByteStream data;
    data.append_uint16(1000);

    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetGnssDataRateBase::Response response(rc);

    BOOST_CHECK_EQUAL(response.parseResponse(GenericMipCmdResponse::ResponseSuccess("", data)), 1000);
}

BOOST_AUTO_TEST_CASE(GetGpsDataRateBase_Match_Success)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetGnssDataRateBase::Response response(rc);

    Bytes ackData;
    ackData.push_back(0x07);
    ackData.push_back(0x00);
    MipDataField ackField(0x0CF1, ackData); //ack/nack field

    Bytes data;
    data.push_back(0x00);
    data.push_back(0x04);
    MipDataField dataField(0x0C84, data); //data field

    //check that the match succeeds
    BOOST_CHECK_EQUAL(response.match(ackField), true);
    BOOST_CHECK_EQUAL(response.fullyMatched(), false);
    BOOST_CHECK_EQUAL(response.match(dataField), true);
    BOOST_CHECK_EQUAL(response.fullyMatched(), true);
    BOOST_CHECK_EQUAL(response.result().success(), true);
    BOOST_CHECK_EQUAL(response.result().errorCode(), mscl::MipPacket::MIP_ACK_NACK_ERROR_NONE);
}

BOOST_AUTO_TEST_SUITE_END()    //End GetGpsDataRateBase


BOOST_AUTO_TEST_SUITE(GpsCommands_GpsMessageFormat)

BOOST_AUTO_TEST_CASE(GpsMessageFormat_buildCommand_get)
{
    ByteStream b = GnssMessageFormat::buildCommand_get();

    //Check all the bytes in the ByteStream
    BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
    BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
    BOOST_CHECK_EQUAL(b.read_uint8(2), 0x0C);
    BOOST_CHECK_EQUAL(b.read_uint8(3), 0x04);
    BOOST_CHECK_EQUAL(b.read_uint8(4), 0x04);
    BOOST_CHECK_EQUAL(b.read_uint8(5), 0x09);
    BOOST_CHECK_EQUAL(b.read_uint8(6), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(7), 0x00);
    BOOST_CHECK_EQUAL(b.read_uint8(8), 0xF9);
    BOOST_CHECK_EQUAL(b.read_uint8(9), 0xF6);
}

BOOST_AUTO_TEST_CASE(GpsMessageFormat_buildCommand_set)
{
    MipChannels chs;
    chs.push_back(MipChannel(MipTypes::CH_FIELD_GNSS_LLH_POSITION, SampleRate::Hertz(2)));
    chs.push_back(MipChannel(MipTypes::CH_FIELD_GNSS_NED_VELOCITY, SampleRate::Hertz(4)));

    ByteStream b = GnssMessageFormat::buildCommand_set(chs, 4);

    //Check all the bytes in the ByteStream
    BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
    BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
    BOOST_CHECK_EQUAL(b.read_uint8(2), 0x0C);
    BOOST_CHECK_EQUAL(b.read_uint8(3), 0x0A);
    BOOST_CHECK_EQUAL(b.read_uint8(4), 0x0A);
    BOOST_CHECK_EQUAL(b.read_uint8(5), 0x09);
    BOOST_CHECK_EQUAL(b.read_uint8(6), 0x01);
    BOOST_CHECK_EQUAL(b.read_uint8(7), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(8), 0x03);
    BOOST_CHECK_EQUAL(b.read_uint8(9), 0x00);
    BOOST_CHECK_EQUAL(b.read_uint8(10), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(11), 0x05);
    BOOST_CHECK_EQUAL(b.read_uint8(12), 0x00);
    BOOST_CHECK_EQUAL(b.read_uint8(13), 0x01);
    BOOST_CHECK_EQUAL(b.read_uint8(14), 0x11);
    BOOST_CHECK_EQUAL(b.read_uint8(15), 0x7A);
}

BOOST_AUTO_TEST_CASE(GpsMessageFormat_parseData)
{
    ByteStream data;
    data.append_uint8(0x01);
    data.append_uint8(0x08);    //CH_GPS_UTC_TIME
    data.append_uint16(4);        //rate decimation

    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GnssMessageFormat::Response response(rc, true);

    uint16 sampleRateBase = 1000;

    MipChannels chs = response.parseResponse(GenericMipCmdResponse::ResponseSuccess("", data), sampleRateBase);

    BOOST_CHECK_EQUAL(chs.size(), 1);
    BOOST_CHECK_EQUAL(chs.at(0).channelField(), MipTypes::CH_FIELD_GNSS_UTC_TIME);
    BOOST_CHECK_EQUAL(chs.at(0).rateDecimation(sampleRateBase), 4);
    BOOST_CHECK_EQUAL(chs.at(0).sampleRate().samplesPerSecond(), SampleRate::Hertz(250).samplesPerSecond());
}

BOOST_AUTO_TEST_SUITE_END()    //End GpsMessageFormat


BOOST_AUTO_TEST_SUITE_END()
