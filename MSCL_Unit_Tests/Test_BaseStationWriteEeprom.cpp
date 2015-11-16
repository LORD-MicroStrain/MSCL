/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Wireless/Commands/BaseStation_WriteEeprom.h"
#include "mscl/MicroStrain/Wireless/Commands/BaseStation_WriteEeprom_v2.h"
#include "mscl/Utils.h"
#include "mscl/MicroStrain/ChecksumBuilder.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/DataBuffer.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

Bytes buildBaseWriteEepromResponseV1(uint16 valueWritten)
{
    ChecksumBuilder checksum;
    checksum.append_uint16(valueWritten);

    //build success response
    Bytes bytes;
    bytes.push_back(0x78);    
    bytes.push_back(Utils::msb(valueWritten));
    bytes.push_back(Utils::lsb(valueWritten));
    bytes.push_back(Utils::msb(checksum.simpleChecksum()));
    bytes.push_back(Utils::lsb(checksum.simpleChecksum()));

    return bytes;
}

WirelessPacket buildBaseWriteEepromResponseV2(uint16 eepromLocation, uint16 valueWritten)
{
    ByteStream bs;
    bs.append_uint16(0x0078);            //command id
    bs.append_uint16(eepromLocation);    //eeprom address
    bs.append_uint16(valueWritten);        //eeprom value

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(0x1234);
    packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0x07));
    packet.type(WirelessPacket::packetType_baseSuccessReply);
    packet.payload(bs.data());    //give the packet the payload bytes we created

    return packet;
}

WirelessPacket buildBaseWriteEepromFailureV2(uint16 eepromLocation, uint16 valueWritten)
{
    ByteStream bs;
    bs.append_uint16(0x0078);            //command id
    bs.append_uint16(eepromLocation);    //eeprom address
    bs.append_uint16(valueWritten);        //eeprom value
    bs.append_uint8(WirelessPacket::error_readOnly);    //error code

    //build a WirelessPacket
    WirelessPacket packet;
    packet.nodeAddress(0x1234);
    packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0x07));
    packet.type(WirelessPacket::packetType_baseErrorReply);
    packet.payload(bs.data());    //give the packet the payload bytes we created

    return packet;
}

BOOST_AUTO_TEST_SUITE(BaseStationWriteEeprom_Test)

BOOST_AUTO_TEST_CASE(BaseStationWriteEeprom_BuildCommand)
{
    //create a Write EEPROM command
    ByteStream b = BaseStation_WriteEeprom::buildCommand(112, 1234);

    //check all the bytes in the ByteStream
    BOOST_CHECK_EQUAL(b.read_uint8(0), 0x78);
    BOOST_CHECK_EQUAL(b.read_uint16(1), 112);
    BOOST_CHECK_EQUAL(b.read_uint16(3), 1234);    
    BOOST_CHECK_EQUAL(b.read_uint16(5), 326);//verify the checksum
}

BOOST_AUTO_TEST_CASE(BaseStationWriteEeprom_MatchSuccessResponse_Success)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    BaseStation_WriteEeprom::Response response(123, rc);

    DataBuffer buffer(buildBaseWriteEepromResponseV1(123));

    //check that match returns true
    BOOST_CHECK_EQUAL(response.match(buffer), true);

    //check that the result of the command is successful
    BOOST_CHECK_EQUAL(response.success(), true);
}

BOOST_AUTO_TEST_CASE(BaseStationWriteEeprom_v2_MatchSuccessResponse_Success)
{
    uint16 eepromAddress = 140;
    uint16 eepromVal = 12347;

    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    BaseStation_WriteEeprom_v2::Response response(eepromVal, eepromAddress, rc);

    WirelessPacket packet = buildBaseWriteEepromResponseV2(eepromAddress, eepromVal);

    //check that match returns true
    BOOST_CHECK_EQUAL(response.match(packet), true);

    //check that the result of the command is successful
    BOOST_CHECK_EQUAL(response.success(), true);
    BOOST_CHECK_EQUAL(response.errorCode(), 0);
}

BOOST_AUTO_TEST_CASE(BaseStationWriteEeprom_MatchSuccessResponse_IncorrectEepromValue)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    BaseStation_WriteEeprom::Response response(123, rc);

    DataBuffer buffer(buildBaseWriteEepromResponseV1(456));//build with incorrect eeprom value

    //check that match returns false
    BOOST_CHECK_EQUAL(response.match(buffer), false);
}

BOOST_AUTO_TEST_CASE(BaseStationWriteEeprom_MatchSuccessResponse_FailNumBytes)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    BaseStation_WriteEeprom::Response response(123, rc);

    Bytes b;
    b.push_back(0x04);

    DataBuffer buffer(b);

    //check that match returns false
    BOOST_CHECK_EQUAL(response.match(buffer), false);

    //check that the result of the command is failure
    BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_CASE(BaseStationWriteEeprom_MatchSuccessResponse_FailByteMatch)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    BaseStation_WriteEeprom::Response response(23, rc);

    Bytes b = buildBaseWriteEepromResponseV1(23);
    b[0] = 0x01;    //incorrect command byte

    DataBuffer buffer(b);

    //check that match returns false
    BOOST_CHECK_EQUAL(response.match(buffer), false);

    //check that the result of the command is failure
    BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_CASE(BaseStationWriteEeprom_MatchSuccessResponse_FailChecksum)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    BaseStation_WriteEeprom::Response response(0, rc);

    Bytes b = buildBaseWriteEepromResponseV1(0);
    b[3] = 0x99;    //incorrect checksum

    DataBuffer buffer(b);

    //check that match returns false
    BOOST_CHECK_EQUAL(response.match(buffer), false);

    //check that the result of the command is failure
    BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_CASE(BaseStationWriteEeprom_MatchFailResponse_Success)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    BaseStation_WriteEeprom::Response response(0, rc);

    Bytes b;
    b.push_back(0x21);

    DataBuffer buffer(b);

    //check that match returns true
    BOOST_CHECK_EQUAL(response.match(buffer), true);

    //check that the result of the command is failure
    BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_CASE(BaseStationWriteEeprom_v2_MatchFailResponse_Success)
{
    uint16 eepromAddress = 140;

    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    BaseStation_WriteEeprom_v2::Response response(123, eepromAddress, rc);

    WirelessPacket packet = buildBaseWriteEepromFailureV2(eepromAddress, 123);

    //check that match returns true
    BOOST_CHECK_EQUAL(response.match(packet), true);

    //check that the result of the command is successful
    BOOST_CHECK_EQUAL(response.success(), false);
    BOOST_CHECK_EQUAL(response.errorCode(), WirelessPacket::error_readOnly);
}

BOOST_AUTO_TEST_CASE(BaseStationWriteEeprom_MatchFailResponse_FailNumBytes)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    BaseStation_WriteEeprom::Response response(0, rc);

    Bytes b;//no bytes

    DataBuffer buffer(b);

    //check that match returns false
    BOOST_CHECK_EQUAL(response.match(buffer), false);

    //check that the result of the command is failure
    BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_CASE(BaseStationWriteEeprom_MatchFailResponse_InvalidByte)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    BaseStation_WriteEeprom::Response response(0, rc);

    Bytes b;
    b.push_back(0x22);

    DataBuffer buffer(b);

    //check that match returns false
    BOOST_CHECK_EQUAL(response.match(buffer), false);

    //check that the result of the command is failure
    BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_CASE(BaseStationWriteEeprom_Wait_Timeout)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    //create the response for the BaseStation_ReadEeprom command
    BaseStation_WriteEeprom::Response response(0, rc);

    //wait for a quick timeout (no data has been sent/received)
    response.wait(1);

    //check that the result of the command is failure
    BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_SUITE_END()