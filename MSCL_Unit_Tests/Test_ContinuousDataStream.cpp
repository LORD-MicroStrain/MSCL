/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/Inertial/Commands/ContinuousDataStream.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>

using namespace std;
using namespace mscl;

BOOST_AUTO_TEST_SUITE(ContinuousDataStream_Test)

BOOST_AUTO_TEST_CASE(ContinuousDataStream_BuildCommand_Sensor)
{
    //create the "get" command
    ByteStream b = ContinuousDataStream::buildCommand_get(MipTypes::CLASS_GNSS);
    BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
    BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
    BOOST_CHECK_EQUAL(b.read_uint8(2), 0x0C);
    BOOST_CHECK_EQUAL(b.read_uint8(3), 0x05);
    BOOST_CHECK_EQUAL(b.read_uint8(4), 0x05);
    BOOST_CHECK_EQUAL(b.read_uint8(5), 0x11);
    BOOST_CHECK_EQUAL(b.read_uint8(6), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(7), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(8), 0x00);
    BOOST_CHECK_EQUAL(b.read_uint8(9), 0x05);
    BOOST_CHECK_EQUAL(b.read_uint8(10), 0x1e);

    //create the "set" command
    ByteStream b2 = ContinuousDataStream::buildCommand_set(MipTypes::CLASS_GNSS, true);
    BOOST_CHECK_EQUAL(b2.read_uint8(0), 0x75);
    BOOST_CHECK_EQUAL(b2.read_uint8(1), 0x65);
    BOOST_CHECK_EQUAL(b2.read_uint8(2), 0x0C);
    BOOST_CHECK_EQUAL(b2.read_uint8(3), 0x05);
    BOOST_CHECK_EQUAL(b2.read_uint8(4), 0x05);
    BOOST_CHECK_EQUAL(b2.read_uint8(5), 0x11);
    BOOST_CHECK_EQUAL(b2.read_uint8(6), 0x01);
    BOOST_CHECK_EQUAL(b2.read_uint8(7), 0x02);
    BOOST_CHECK_EQUAL(b2.read_uint8(8), 0x01);
    BOOST_CHECK_EQUAL(b2.read_uint8(9), 0x05);
    BOOST_CHECK_EQUAL(b2.read_uint8(10), 0x1c);
}

BOOST_AUTO_TEST_CASE(ContinuousDataStream_get_Match_Success)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    ContinuousDataStream::Response response(rc, true, MipTypes::CLASS_GNSS);

    Bytes dataField;
    dataField.push_back(0x02);
    dataField.push_back(0x01);
    
    Bytes ackField;
    ackField.push_back(0x11);
    ackField.push_back(0x00);
    MipDataField field1(0x0CF1, ackField); //good ack field

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field1), true);
    BOOST_CHECK_EQUAL(response.fullyMatched(), false);    //not yet fully matched

    MipDataField field2(0x0C85, dataField); //good data field

    //check that the match succeeds
    BOOST_CHECK_EQUAL(response.match(field2), true);
    BOOST_CHECK_EQUAL(response.fullyMatched(), true);    //we  fully matched because the device info is enough to match
    BOOST_CHECK_EQUAL(response.result().success(), true);
    BOOST_CHECK_EQUAL(response.result().errorCode(), mscl::MipPacket::MIP_ACK_NACK_ERROR_NONE);
    BOOST_CHECK_EQUAL(response.result().data().read_uint8(0), 2);
    BOOST_CHECK_EQUAL(response.result().data().read_uint8(1), 1);
}

BOOST_AUTO_TEST_CASE(ContinuousDataStream_set_Match_Success)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    ContinuousDataStream::Response response(rc, false, MipTypes::CLASS_GNSS);

    Bytes ackField;
    ackField.push_back(0x11);
    ackField.push_back(0x00);
    MipDataField field1(0x0CF1, ackField); //good ack field

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field1), true);
    BOOST_CHECK_EQUAL(response.fullyMatched(), true);    //fully matched
}

BOOST_AUTO_TEST_CASE(ContinuousDataStream_get_Match_Success_OnlyData)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    ContinuousDataStream::Response response(rc, true, MipTypes::CLASS_GNSS);

    Bytes fieldData1;
    fieldData1.push_back(0x02);
    fieldData1.push_back(0x01);
    MipDataField field1(0x0C85, fieldData1);

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field1), true);
}

BOOST_AUTO_TEST_CASE(ContinuousDataStream_get_Match_Fail_WrongDeviceSelector)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    ContinuousDataStream::Response response(rc, true, MipTypes::CLASS_GNSS);

    Bytes fieldData1;
    fieldData1.push_back(0x01);    //invalid device selector (device category)
    fieldData1.push_back(0x01);    
    MipDataField field1(0x0C85, fieldData1); 

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field1), false);
}

BOOST_AUTO_TEST_CASE(ContinuousDataStream_get_Match_Fail_SmallFieldData)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    ContinuousDataStream::Response response(rc, true, MipTypes::CLASS_GNSS);

    Bytes fieldData1;
    fieldData1.push_back(0x02);    //missing a byte
    MipDataField field1(0x0C85, fieldData1);

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(field1), false);
}

BOOST_AUTO_TEST_SUITE_END()