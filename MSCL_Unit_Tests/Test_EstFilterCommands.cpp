/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "mscl/MicroStrain/Inertial/Commands/EstFilter_Commands.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/Inertial/EulerAngles.h"
#include "mscl/MicroStrain/Inertial/PositionOffset.h"

#include <boost/test/unit_test.hpp>
using namespace mscl;

BOOST_AUTO_TEST_SUITE(EstFilterCommands_Test)

BOOST_AUTO_TEST_SUITE(EstFilterCommands_GetEstFilterDataRateBase)

BOOST_AUTO_TEST_CASE(GetEstFilterDataRateBase_buildCommand)
{
    ByteStream b = GetEstFilterDataRateBase::buildCommand();

    //Check all the bytes in the ByteStream
    BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
    BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
    BOOST_CHECK_EQUAL(b.read_uint8(2), 0x0C);
    BOOST_CHECK_EQUAL(b.read_uint8(3), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(4), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(5), 0x0B);
    BOOST_CHECK_EQUAL(b.read_uint8(6), 0xF5);
    BOOST_CHECK_EQUAL(b.read_uint8(7), 0xFC);
}

BOOST_AUTO_TEST_CASE(GetEstFilterDataRateBase_parseData)
{
    ByteStream data;
    data.append_uint16(500);

    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetEstFilterDataRateBase::Response response(rc);

    BOOST_CHECK_EQUAL(response.parseResponse(GenericMipCmdResponse::ResponseSuccess("", data)), 500);
}

BOOST_AUTO_TEST_CASE(GetEstFilterDataRateBase_Match_Success)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetEstFilterDataRateBase::Response response(rc);

    Bytes ackData;
    ackData.push_back(0x0B);
    ackData.push_back(0x00);
    MipDataField ackField(0x0CF1, ackData); //ack/nack field

    Bytes data;
    data.push_back(0x00);
    data.push_back(0x02);
    MipDataField dataField(0x0C8A, data); //data field

    //check that the match succeeds
    BOOST_CHECK_EQUAL(response.match(ackField), true);
    BOOST_CHECK_EQUAL(response.fullyMatched(), false);
    BOOST_CHECK_EQUAL(response.match(dataField), true);
    BOOST_CHECK_EQUAL(response.fullyMatched(), true);
    BOOST_CHECK_EQUAL(response.result().success(), true);
    BOOST_CHECK_EQUAL(response.result().errorCode(), mscl::MipPacket::MIP_ACK_NACK_ERROR_NONE);
}

BOOST_AUTO_TEST_SUITE_END()    //End GetEstFilterDataRateBase


BOOST_AUTO_TEST_SUITE(EstFilterCommands_EstFilterMessageFormat)

BOOST_AUTO_TEST_CASE(EstFilterMessageFormat_buildCommand_get)
{
    ByteStream b = EstFilterMessageFormat::buildCommand_get();

    //Check all the bytes in the ByteStream
    BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
    BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
    BOOST_CHECK_EQUAL(b.read_uint8(2), 0x0C);
    BOOST_CHECK_EQUAL(b.read_uint8(3), 0x04);
    BOOST_CHECK_EQUAL(b.read_uint8(4), 0x04);
    BOOST_CHECK_EQUAL(b.read_uint8(5), 0x0A);
    BOOST_CHECK_EQUAL(b.read_uint8(6), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(7), 0x00);
    BOOST_CHECK_EQUAL(b.read_uint8(8), 0xFA);
    BOOST_CHECK_EQUAL(b.read_uint8(9), 0xF9);
}

BOOST_AUTO_TEST_CASE(EstFilterMessageFormat_buildCommand_set)
{
    SampleRate hz1 = SampleRate::Hertz(1);

    MipChannels chs;
    chs.push_back(MipChannel(MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_LLH_POS, hz1));
    chs.push_back(MipChannel(MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_NED_VELOCITY, hz1));

    ByteStream b = EstFilterMessageFormat::buildCommand_set(chs, 1);

    //Check all the bytes in the ByteStream
    BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
    BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
    BOOST_CHECK_EQUAL(b.read_uint8(2), 0x0C);
    BOOST_CHECK_EQUAL(b.read_uint8(3), 0x0A);
    BOOST_CHECK_EQUAL(b.read_uint8(4), 0x0A);
    BOOST_CHECK_EQUAL(b.read_uint8(5), 0x0A);
    BOOST_CHECK_EQUAL(b.read_uint8(6), 0x01);
    BOOST_CHECK_EQUAL(b.read_uint8(7), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(8), 0x01);
    BOOST_CHECK_EQUAL(b.read_uint8(9), 0x00);
    BOOST_CHECK_EQUAL(b.read_uint8(10), 0x01);
    BOOST_CHECK_EQUAL(b.read_uint8(11), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(12), 0x00);
    BOOST_CHECK_EQUAL(b.read_uint8(13), 0x01);
    BOOST_CHECK_EQUAL(b.read_uint8(14), 0x0C);
    BOOST_CHECK_EQUAL(b.read_uint8(15), 0x6A);
}

BOOST_AUTO_TEST_CASE(EstFilterMessageFormat_parseData)
{
    ByteStream data;
    data.append_uint8(0x01);
    data.append_uint8(0x06);    //CH_NAV_ESTIMATED_GYRO_BIAS
    data.append_uint16(2);        //rate decimation

    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    EstFilterMessageFormat::Response response(rc, true);

    uint16 sampleRateBase = 100;

    MipChannels chs = response.parseResponse(GenericMipCmdResponse::ResponseSuccess("", data), sampleRateBase);

    BOOST_CHECK_EQUAL(chs.size(), 1);
    BOOST_CHECK_EQUAL(chs.at(0).channelField(), MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS);
    BOOST_CHECK_EQUAL(chs.at(0).rateDecimation(sampleRateBase), 2);
    BOOST_CHECK_EQUAL(chs.at(0).sampleRate().samplesPerSecond(), SampleRate::Hertz(50).samplesPerSecond());

}

BOOST_AUTO_TEST_SUITE_END()    //End EstFilterMessageFormat

BOOST_AUTO_TEST_SUITE(EstFilterCommands_SensorToVehicFrameTrans)

BOOST_AUTO_TEST_CASE(SensorToVehicFrameTrans_buildCommand_get)
{
    ByteStream b = SensorToVehicFrameTrans::buildCommand_get();

    //Check all the bytes in the ByteStream
    BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
    BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
    BOOST_CHECK_EQUAL(b.read_uint8(2), 0x0D);
    BOOST_CHECK_EQUAL(b.read_uint8(3), 0x03);    //payload len
    BOOST_CHECK_EQUAL(b.read_uint8(4), 0x03);    //field len
    BOOST_CHECK_EQUAL(b.read_uint8(5), 0x11);    //field desc
    BOOST_CHECK_EQUAL(b.read_uint8(6), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(7), 0x00);
    BOOST_CHECK_EQUAL(b.read_uint8(8), 0x0B);
}

BOOST_AUTO_TEST_CASE(SensorToVehicFrameTrans_buildCommand_set)
{
    mscl::EulerAngles angles(1.5f, 10.123f, 0.018945f);

    ByteStream b = SensorToVehicFrameTrans::buildCommand_set(angles);

    //Check all the bytes in the ByteStream
    BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
    BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
    BOOST_CHECK_EQUAL(b.read_uint8(2), 0x0D);
    BOOST_CHECK_EQUAL(b.read_uint8(3), 0x0F);    //payload len
    BOOST_CHECK_EQUAL(b.read_uint8(4), 0x0F);    //field len
    BOOST_CHECK_EQUAL(b.read_uint8(5), 0x11);    //field desc
    BOOST_CHECK_EQUAL(b.read_uint8(6), 0x01);
    BOOST_CHECK_EQUAL(b.read_uint8(7), 0x3F);
    BOOST_CHECK_EQUAL(b.read_uint8(8), 0xC0);
    BOOST_CHECK_EQUAL(b.read_uint8(9), 0x00);
    BOOST_CHECK_EQUAL(b.read_uint8(10), 0x00);
    BOOST_CHECK_EQUAL(b.read_uint8(11), 0x41);
    BOOST_CHECK_EQUAL(b.read_uint8(12), 0x21);
    BOOST_CHECK_EQUAL(b.read_uint8(13), 0xF7);
    BOOST_CHECK_EQUAL(b.read_uint8(14), 0xCF);
    BOOST_CHECK_EQUAL(b.read_uint8(15), 0x3C);
    BOOST_CHECK_EQUAL(b.read_uint8(16), 0x9B);
    BOOST_CHECK_EQUAL(b.read_uint8(17), 0x32);
    BOOST_CHECK_EQUAL(b.read_uint8(18), 0x8B);
    BOOST_CHECK_EQUAL(b.read_uint8(19), 0xD2);
    BOOST_CHECK_EQUAL(b.read_uint8(20), 0x1A);
}

BOOST_AUTO_TEST_CASE(SensorToVehicFrameTrans_parseData)
{
    ByteStream data;
    data.append_float(-2.3f);
    data.append_float(0.34234f);
    data.append_float(0.00019f);

    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    SensorToVehicFrameTrans::Response response(rc, true);

    mscl::EulerAngles angles = response.parseResponse(GenericMipCmdResponse::ResponseSuccess("", data));

    BOOST_CHECK_CLOSE(angles.roll(), -2.3, 0.001);
    BOOST_CHECK_CLOSE(angles.pitch(), 0.34234, 0.001);
    BOOST_CHECK_CLOSE(angles.yaw(), 0.00019, 0.001);
}

BOOST_AUTO_TEST_SUITE_END()    //End EstFilterCommands_SensorToVehicFrameTrans


BOOST_AUTO_TEST_SUITE(EstFilterCommands_SensorToVehicFrameOffset)

BOOST_AUTO_TEST_CASE(SensorToVehicFrameOffset_buildCommand_get)
{
    ByteStream b = SensorToVehicFrameOffset::buildCommand_get();

    //Check all the bytes in the ByteStream
    BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
    BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
    BOOST_CHECK_EQUAL(b.read_uint8(2), 0x0D);
    BOOST_CHECK_EQUAL(b.read_uint8(3), 0x03);    //payload len
    BOOST_CHECK_EQUAL(b.read_uint8(4), 0x03);    //field len
    BOOST_CHECK_EQUAL(b.read_uint8(5), 0x12);    //field desc
    BOOST_CHECK_EQUAL(b.read_uint8(6), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(7), 0x01);
    BOOST_CHECK_EQUAL(b.read_uint8(8), 0x0D);
}

BOOST_AUTO_TEST_CASE(SensorToVehicFrameOffset_buildCommand_set)
{
    mscl::PositionOffset offset(1.5f, -1.123f, 0.018945f);

    ByteStream b = SensorToVehicFrameOffset::buildCommand_set(offset);

    //Check all the bytes in the ByteStream
    BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
    BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
    BOOST_CHECK_EQUAL(b.read_uint8(2), 0x0D);
    BOOST_CHECK_EQUAL(b.read_uint8(3), 0x0F);    //payload len
    BOOST_CHECK_EQUAL(b.read_uint8(4), 0x0F);    //field len
    BOOST_CHECK_EQUAL(b.read_uint8(5), 0x12);    //field desc
    BOOST_CHECK_EQUAL(b.read_uint8(6), 0x01);
    BOOST_CHECK_EQUAL(b.read_uint8(7), 0x3F);
    BOOST_CHECK_EQUAL(b.read_uint8(8), 0xC0);
    BOOST_CHECK_EQUAL(b.read_uint8(9), 0x00);
    BOOST_CHECK_EQUAL(b.read_uint8(10), 0x00);
    BOOST_CHECK_EQUAL(b.read_uint8(11), 0xBF);
    BOOST_CHECK_EQUAL(b.read_uint8(12), 0x8F);
    BOOST_CHECK_EQUAL(b.read_uint8(13), 0xBE);
    BOOST_CHECK_EQUAL(b.read_uint8(14), 0x77);
    BOOST_CHECK_EQUAL(b.read_uint8(15), 0x3C);
    BOOST_CHECK_EQUAL(b.read_uint8(16), 0x9B);
    BOOST_CHECK_EQUAL(b.read_uint8(17), 0x32);
    BOOST_CHECK_EQUAL(b.read_uint8(18), 0x8B);
    BOOST_CHECK_EQUAL(b.read_uint8(19), 0x2E);
    BOOST_CHECK_EQUAL(b.read_uint8(20), 0x0C);
}

BOOST_AUTO_TEST_CASE(SensorToVehicFrameOffset_parseData)
{
    ByteStream data;
    data.append_float(-5.3f);
    data.append_float(0.3234f);
    data.append_float(0.70019f);

    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    SensorToVehicFrameOffset::Response response(rc, true);

    mscl::PositionOffset offset = response.parseResponse(GenericMipCmdResponse::ResponseSuccess("", data));

    BOOST_CHECK_CLOSE(offset.x(), -5.3, 0.001);
    BOOST_CHECK_CLOSE(offset.y(), 0.3234, 0.001);
    BOOST_CHECK_CLOSE(offset.z(), 0.70019, 0.001);
}

BOOST_AUTO_TEST_SUITE_END()    //End EstFilterCommands_SensorToVehicFrameTrans


BOOST_AUTO_TEST_SUITE_END()