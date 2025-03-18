/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Inertial/Commands/EstFilter_Commands.h"
#include "mscl/MicroStrain/Inertial/Commands/GNSS_Commands.h"
#include "mscl/MicroStrain/Inertial/Commands/Sensor_Commands.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/ResponseCollector.h"

using namespace mscl;

DISABLE_WARNING_BOOST_START
#include <boost/test/unit_test.hpp>
DISABLE_WARNING_BOOST_END

BOOST_AUTO_TEST_SUITE(GetDataRateBase_Test)


//Sensor TESTS
BOOST_AUTO_TEST_SUITE(GetDataRateBase_Test_Sensor)

BOOST_AUTO_TEST_CASE(GetDataRateBase_BuildCommand_Sensor)
{
    //create the command
    ByteStream b = GetSensorDataRateBase::buildCommand();

    BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
    BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
    BOOST_CHECK_EQUAL(b.read_uint8(2), 0x0C);
    BOOST_CHECK_EQUAL(b.read_uint8(3), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(4), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(5), 0x06);
    BOOST_CHECK_EQUAL(b.read_uint8(6), 0xF0);
    BOOST_CHECK_EQUAL(b.read_uint8(7), 0xF7);
}

BOOST_AUTO_TEST_CASE(GetDataRateBase_Sensor_Match_Fail_DescSet)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetSensorDataRateBase::Response response(rc);

    Bytes fieldData1;
    fieldData1.push_back(0x06);
    fieldData1.push_back(0x00);
    MipDataField field1(0x02F1, fieldData1); //invalid descriptor set

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field1), false);
}

BOOST_AUTO_TEST_CASE(GetDataRateBase_Sensor_Match_Fail_FieldDataLen)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetSensorDataRateBase::Response response(rc);

    Bytes fieldData;
    fieldData.push_back(0x06);
    MipDataField field(0x02F1, fieldData); //bad field data length

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field), false);
}

BOOST_AUTO_TEST_CASE(GetDataRateBase_Sensor_Match_Fail_FieldDesc)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetSensorDataRateBase::Response response(rc);

    Bytes fieldData;
    fieldData.push_back(0x06);
    fieldData.push_back(0x00);
    MipDataField field(0x0CF2, fieldData); //invalid field descriptor

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field), false);
}

BOOST_AUTO_TEST_CASE(GetDataRateBase_Sensor_Match_Fail_CommandEcho)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetSensorDataRateBase::Response response(rc);

    Bytes fieldData;
    fieldData.push_back(0x01);    //bad command echo
    fieldData.push_back(0x00);
    MipDataField field(0x0CF1, fieldData);

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field), false);
}

BOOST_AUTO_TEST_CASE(GetDataRateBase_Sensor_Match_FailWithErrorCode)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetSensorDataRateBase::Response response(rc);

    Bytes fieldData;
    fieldData.push_back(0x06);
    fieldData.push_back(MipPacket::MIP_ACK_NACK_ERROR_UNKNOWN_COMMAND);
    MipDataField field(0x0CF1, fieldData); //good field, but with error code

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field), true);
    BOOST_CHECK_EQUAL(response.result().success(), false);
    BOOST_CHECK_EQUAL(response.result().errorCode(), mscl::MipPacket::MIP_ACK_NACK_ERROR_UNKNOWN_COMMAND);
}

BOOST_AUTO_TEST_CASE(GetDataRateBase_Sensor_Match_Success_NotFullyMatched)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetSensorDataRateBase::Response response(rc);

    Bytes fieldData1;
    fieldData1.push_back(0x06);
    fieldData1.push_back(0x00);
    MipDataField field1(0x0CF1, fieldData1); //good field

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field1), true);
    BOOST_CHECK_EQUAL(response.fullyMatched(), false);    //not yet fully matched
    BOOST_CHECK_EQUAL(response.result().success(), false);    //only got the ACK/NACK, so not fully complete
}

BOOST_AUTO_TEST_CASE(GetDataRateBase_Sensor_Match_Success_OnlyData)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetSensorDataRateBase::Response response(rc);

    ByteStream bytes;
    bytes.append_uint16(1000);

    MipDataField field2(0x0C83, bytes.data()); //good device info field

    //check that the match succeeds
    BOOST_CHECK_EQUAL(response.match(field2), true);
    BOOST_CHECK_EQUAL(response.fullyMatched(), true);    //even though we didn't get an ACK/NACK, we still fully matched because the descriptors info is enough to match
    BOOST_CHECK_EQUAL(response.result().success(), true);
    BOOST_CHECK_EQUAL(response.result().errorCode(), mscl::MipPacket::MIP_ACK_NACK_ERROR_NONE);
    BOOST_CHECK_EQUAL(response.result().data().read_uint16(0), 1000);
}

BOOST_AUTO_TEST_CASE(GetDataRateBase_Sensor_Match_Success)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetSensorDataRateBase::Response response(rc);

    ByteStream bytes;
    bytes.append_uint16(4);

    Bytes fieldData1;
    fieldData1.push_back(0x06);
    fieldData1.push_back(0x00);
    MipDataField field1(0x0CF1, fieldData1); //good field

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field1), true);
    BOOST_CHECK_EQUAL(response.fullyMatched(), false);    //not yet fully matched

    MipDataField field2(0x0C83, bytes.data()); //good device info field

    //check that the match succeeds
    BOOST_CHECK_EQUAL(response.match(field2), true);
    BOOST_CHECK_EQUAL(response.fullyMatched(), true);    //we fully matched because the device info is enough to match
    BOOST_CHECK_EQUAL(response.result().success(), true);
    BOOST_CHECK_EQUAL(response.result().errorCode(), mscl::MipPacket::MIP_ACK_NACK_ERROR_NONE);
    BOOST_CHECK_EQUAL(response.result().data().read_uint16(0), 4);
}

BOOST_AUTO_TEST_SUITE_END()


//GPS TESTS
BOOST_AUTO_TEST_SUITE(GetDataRateBase_Test_GPS)

BOOST_AUTO_TEST_CASE(GetDataRateBase_BuildCommand_GPS)
{
    //create the GetDeviceInfo command
    ByteStream b = GetGnssDataRateBase::buildCommand();

    BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
    BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
    BOOST_CHECK_EQUAL(b.read_uint8(2), 0x0C);
    BOOST_CHECK_EQUAL(b.read_uint8(3), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(4), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(5), 0x07);
    BOOST_CHECK_EQUAL(b.read_uint8(6), 0xF1);
    BOOST_CHECK_EQUAL(b.read_uint8(7), 0xF8);
}

BOOST_AUTO_TEST_CASE(GetDataRateBase_GPS_Match_Fail_DescSet)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetGnssDataRateBase::Response response(rc);

    Bytes fieldData1;
    fieldData1.push_back(0x07);
    fieldData1.push_back(0x00);
    MipDataField field1(0x02F1, fieldData1); //invalid descriptor set

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field1), false);
}

BOOST_AUTO_TEST_CASE(GetDataRateBase_GPS_Match_Fail_FieldDataLen)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetGnssDataRateBase::Response response(rc);

    Bytes fieldData;
    fieldData.push_back(0x07);
    MipDataField field(0x0CF1, fieldData); //bad field data length

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field), false);
}

BOOST_AUTO_TEST_CASE(GetDataRateBase_GPS_Match_Fail_FieldDesc)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetGnssDataRateBase::Response response(rc);

    Bytes fieldData;
    fieldData.push_back(0x07);
    fieldData.push_back(0x00);
    MipDataField field(0x0CF2, fieldData); //invalid field descriptor

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field), false);
}

BOOST_AUTO_TEST_CASE(GetDataRateBase_GPS_Match_Fail_CommandEcho)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetGnssDataRateBase::Response response(rc);

    Bytes fieldData;
    fieldData.push_back(0x01);    //bad command echo
    fieldData.push_back(0x00);
    MipDataField field(0x0CF1, fieldData);

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field), false);
}

BOOST_AUTO_TEST_CASE(GetDataRateBase_GPS_Match_FailWithErrorCode)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetGnssDataRateBase::Response response(rc);

    Bytes fieldData;
    fieldData.push_back(0x07);
    fieldData.push_back(MipPacket::MIP_ACK_NACK_ERROR_UNKNOWN_COMMAND);
    MipDataField field(0x0CF1, fieldData); //good field, but with error code

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field), true);
    BOOST_CHECK_EQUAL(response.result().success(), false);
    BOOST_CHECK_EQUAL(response.result().errorCode(), mscl::MipPacket::MIP_ACK_NACK_ERROR_UNKNOWN_COMMAND);
}

BOOST_AUTO_TEST_CASE(GetDataRateBase_GPS_Match_Success_NotFullyMatched)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetGnssDataRateBase::Response response(rc);

    Bytes fieldData1;
    fieldData1.push_back(0x07);
    fieldData1.push_back(0x00);
    MipDataField field1(0x0CF1, fieldData1); //good field

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field1), true);
    BOOST_CHECK_EQUAL(response.fullyMatched(), false);    //not yet fully matched
    BOOST_CHECK_EQUAL(response.result().success(), false);    //only got the ACK/NACK, so not fully complete
}

BOOST_AUTO_TEST_CASE(GetDataRateBase_GPS_Match_Success_OnlyData)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetGnssDataRateBase::Response response(rc);

    ByteStream bytes;
    bytes.append_uint16(2000);

    MipDataField field2(0x0C84, bytes.data()); //good device info field

    //check that the match succeeds
    BOOST_CHECK_EQUAL(response.match(field2), true);
    BOOST_CHECK_EQUAL(response.fullyMatched(), true);    //even though we didn't get an ACK/NACK, we still fully matched because the descriptors info is enough to match
    BOOST_CHECK_EQUAL(response.result().success(), true);
    BOOST_CHECK_EQUAL(response.result().errorCode(), mscl::MipPacket::MIP_ACK_NACK_ERROR_NONE);
    BOOST_CHECK_EQUAL(response.result().data().read_uint16(0), 2000);
}

BOOST_AUTO_TEST_CASE(GetDataRateBase_GPS_Match_Success)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetGnssDataRateBase::Response response(rc);

    ByteStream bytes;
    bytes.append_uint16(40);

    Bytes fieldData1;
    fieldData1.push_back(0x07);
    fieldData1.push_back(0x00);
    MipDataField field1(0x0CF1, fieldData1); //good field

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field1), true);
    BOOST_CHECK_EQUAL(response.fullyMatched(), false);    //not yet fully matched

    MipDataField field2(0x0C84, bytes.data()); //good device info field

    //check that the match succeeds
    BOOST_CHECK_EQUAL(response.match(field2), true);
    BOOST_CHECK_EQUAL(response.fullyMatched(), true);    //we fully matched because the device info is enough to match
    BOOST_CHECK_EQUAL(response.result().success(), true);
    BOOST_CHECK_EQUAL(response.result().errorCode(), mscl::MipPacket::MIP_ACK_NACK_ERROR_NONE);
    BOOST_CHECK_EQUAL(response.result().data().read_uint16(0), 40);
}


BOOST_AUTO_TEST_SUITE_END()


//EstFilter TESTS
BOOST_AUTO_TEST_SUITE(GetDataRateBase_Test_EstFilter)

BOOST_AUTO_TEST_CASE(GetDataRateBase_BuildCommand_EstFilter)
{
    //create the GetDeviceInfo command
    ByteStream b = GetEstFilterDataRateBase::buildCommand();

    BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
    BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
    BOOST_CHECK_EQUAL(b.read_uint8(2), 0x0C);
    BOOST_CHECK_EQUAL(b.read_uint8(3), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(4), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(5), 0x0B);
    BOOST_CHECK_EQUAL(b.read_uint8(6), 0xF5);
    BOOST_CHECK_EQUAL(b.read_uint8(7), 0xFC);
}

BOOST_AUTO_TEST_CASE(GetDataRateBase_EstFilter_Match_Fail_DescSet)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetEstFilterDataRateBase::Response response(rc);

    Bytes fieldData1;
    fieldData1.push_back(0x0B);
    fieldData1.push_back(0x00);
    MipDataField field1(0x03F1, fieldData1); //invalid descriptor set

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field1), false);
}

BOOST_AUTO_TEST_CASE(GetDataRateBase_EstFilter_Match_Fail_FieldDataLen)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetEstFilterDataRateBase::Response response(rc);

    Bytes fieldData;
    fieldData.push_back(0x0B);
    MipDataField field(0x0CF1, fieldData); //bad field data length

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field), false);
}

BOOST_AUTO_TEST_CASE(GetDataRateBase_EstFilter_Match_Fail_FieldDesc)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetEstFilterDataRateBase::Response response(rc);

    Bytes fieldData;
    fieldData.push_back(0x0B);
    fieldData.push_back(0x00);
    MipDataField field(0x0CF2, fieldData); //invalid field descriptor

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field), false);
}

BOOST_AUTO_TEST_CASE(GetDataRateBase_EstFilter_Match_Fail_CommandEcho)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetEstFilterDataRateBase::Response response(rc);

    Bytes fieldData;
    fieldData.push_back(0x01);    //bad command echo
    fieldData.push_back(0x00);
    MipDataField field(0x0CF1, fieldData);

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field), false);
}

BOOST_AUTO_TEST_CASE(GetDataRateBase_EstFilter_Match_FailWithErrorCode)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetEstFilterDataRateBase::Response response(rc);

    Bytes fieldData;
    fieldData.push_back(0x0B);
    fieldData.push_back(MipPacket::MIP_ACK_NACK_ERROR_UNKNOWN_COMMAND);
    MipDataField field(0x0CF1, fieldData); //good field, but with error code

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field), true);
    BOOST_CHECK_EQUAL(response.result().success(), false);
    BOOST_CHECK_EQUAL(response.result().errorCode(), mscl::MipPacket::MIP_ACK_NACK_ERROR_UNKNOWN_COMMAND);
}

BOOST_AUTO_TEST_CASE(GetDataRateBase_EstFilter_Match_Fail_DataMatchFieldDesc)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetEstFilterDataRateBase::Response response(rc);

    ByteStream bytes;
    bytes.append_uint16(2000);

    MipDataField field2(0x0C00, bytes.data()); //bad field descriptor

    //check that the match succeeds
    BOOST_CHECK_EQUAL(response.match(field2), false);
}

BOOST_AUTO_TEST_CASE(GetDataRateBase_EstFilter_Match_Success_NotFullyMatched)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetEstFilterDataRateBase::Response response(rc);

    Bytes fieldData1;
    fieldData1.push_back(0x0B);
    fieldData1.push_back(0x00);
    MipDataField field1(0x0CF1, fieldData1); //good field

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field1), true);
    BOOST_CHECK_EQUAL(response.fullyMatched(), false);    //not yet fully matched
    BOOST_CHECK_EQUAL(response.result().success(), false);    //only got the ACK/NACK, so not fully complete
}

BOOST_AUTO_TEST_CASE(GetDataRateBase_EstFilter_Match_Success_OnlyData)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetEstFilterDataRateBase::Response response(rc);

    ByteStream bytes;
    bytes.append_uint16(2000);

    MipDataField field2(0x0C8A, bytes.data()); //good device info field

    //check that the match succeeds
    BOOST_CHECK_EQUAL(response.match(field2), true);
    BOOST_CHECK_EQUAL(response.fullyMatched(), true);    //even though we didn't get an ACK/NACK, we still fully matched because the descriptors info is enough to match
    BOOST_CHECK_EQUAL(response.result().success(), true);
    BOOST_CHECK_EQUAL(response.result().errorCode(), mscl::MipPacket::MIP_ACK_NACK_ERROR_NONE);
    BOOST_CHECK_EQUAL(response.result().data().read_uint16(0), 2000);
}

BOOST_AUTO_TEST_CASE(GetDataRateBase_EstFilter_Match_Success)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    GetEstFilterDataRateBase::Response response(rc);

    ByteStream bytes;
    bytes.append_uint16(40);

    Bytes fieldData1;
    fieldData1.push_back(0x0B);
    fieldData1.push_back(0x00);
    MipDataField field1(0x0CF1, fieldData1); //good field

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field1), true);
    BOOST_CHECK_EQUAL(response.fullyMatched(), false);    //not yet fully matched

    MipDataField field2(0x0C8A, bytes.data()); //good device info field

    //check that the match succeeds
    BOOST_CHECK_EQUAL(response.match(field2), true);
    BOOST_CHECK_EQUAL(response.fullyMatched(), true);    //we fully matched because the device info is enough to match
    BOOST_CHECK_EQUAL(response.result().success(), true);
    BOOST_CHECK_EQUAL(response.result().errorCode(), mscl::MipPacket::MIP_ACK_NACK_ERROR_NONE);
    BOOST_CHECK_EQUAL(response.result().data().read_uint16(0), 40);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
