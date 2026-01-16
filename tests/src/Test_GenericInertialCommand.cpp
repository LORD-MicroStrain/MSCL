/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/ResponseCollector.h"

using namespace mscl;

DISABLE_WARNING_BOOST_START
#include <boost/test/unit_test.hpp>
DISABLE_WARNING_BOOST_END

BOOST_AUTO_TEST_SUITE(GenericInertialCommand_Test)

BOOST_AUTO_TEST_CASE(GenericInertialCommandResponse_ResponseSuccess)
{
    //check a success response with no data
    GenericMipCmdResponse res = GenericMipCmdResponse::ResponseSuccess("Hello World");
    BOOST_CHECK_EQUAL(res.errorCode(), MipPacket::MIP_ACK_NACK_ERROR_NONE);
    BOOST_CHECK_EQUAL(res.success(), true);
    BOOST_CHECK_EQUAL(res.data().size(), 0);

    //check a success response with data
    ByteStream bytes;
    bytes.append_uint16(0x1234);
    GenericMipCmdResponse res2 = GenericMipCmdResponse::ResponseSuccess("Hello World", bytes);
    BOOST_CHECK_EQUAL(res2.errorCode(), MipPacket::MIP_ACK_NACK_ERROR_NONE);
    BOOST_CHECK_EQUAL(res2.success(), true);
    BOOST_CHECK_EQUAL(res2.data().size(), 2);
}

BOOST_AUTO_TEST_CASE(GenericInertialCommandResponse_ResponseFail)
{
    //check a fail response
    GenericMipCmdResponse res = GenericMipCmdResponse::ResponseFail(ResponsePattern::STATE_FAIL, MipPacket::MIP_ACK_NACK_ERROR_UNKNOWN_COMMAND, "");
    BOOST_CHECK_EQUAL(res.errorCode(), MipPacket::MIP_ACK_NACK_ERROR_UNKNOWN_COMMAND);
    BOOST_CHECK_EQUAL(res.success(), false);
}

BOOST_AUTO_TEST_CASE(GenericInertialCommand_buildCommand_withBytes)
{
    ByteStream cmdNoData = GenericMipCommand::buildCommand(0x0C, 0x06);

    //Check all the bytes in the ByteStream
    BOOST_CHECK_EQUAL(cmdNoData.read_uint8(0), 0x75);
    BOOST_CHECK_EQUAL(cmdNoData.read_uint8(1), 0x65);
    BOOST_CHECK_EQUAL(cmdNoData.read_uint8(2), 0x0C);
    BOOST_CHECK_EQUAL(cmdNoData.read_uint8(3), 0x02);
    BOOST_CHECK_EQUAL(cmdNoData.read_uint8(4), 0x02);
    BOOST_CHECK_EQUAL(cmdNoData.read_uint8(5), 0x06);
    BOOST_CHECK_EQUAL(cmdNoData.read_uint8(6), 0xF0);
    BOOST_CHECK_EQUAL(cmdNoData.read_uint8(7), 0xF7);

    Bytes data;
    data.push_back(0x02);
    data.push_back(0x00);
    ByteStream cmd = GenericMipCommand::buildCommand(0x0C, 0x08, data);

    //Check all the bytes in the ByteStream
    BOOST_CHECK_EQUAL(cmd.read_uint8(0), 0x75);
    BOOST_CHECK_EQUAL(cmd.read_uint8(1), 0x65);
    BOOST_CHECK_EQUAL(cmd.read_uint8(2), 0x0C);
    BOOST_CHECK_EQUAL(cmd.read_uint8(3), 0x04);
    BOOST_CHECK_EQUAL(cmd.read_uint8(4), 0x04);
    BOOST_CHECK_EQUAL(cmd.read_uint8(5), 0x08);
    BOOST_CHECK_EQUAL(cmd.read_uint8(6), 0x02);
    BOOST_CHECK_EQUAL(cmd.read_uint8(7), 0x00);
    BOOST_CHECK_EQUAL(cmd.read_uint8(8), 0xF8);
    BOOST_CHECK_EQUAL(cmd.read_uint8(9), 0xF3);
}

BOOST_AUTO_TEST_SUITE_END()
