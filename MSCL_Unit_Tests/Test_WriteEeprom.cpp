/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Wireless/Commands/WriteEeprom.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/MicroStrain/ResponseCollector.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

WirelessPacket buildWriteEepromResponse(int nodeAddress)
{
    Bytes payload;
    payload.push_back(0x00);
    payload.push_back(0x04);

    //build the correct packet response first
    WirelessPacket packet;
    packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0x00));
    packet.type(static_cast<WirelessPacket::PacketType>(0x00));
    packet.nodeAddress(nodeAddress);
    packet.payload(payload);

    return packet;
}

BOOST_AUTO_TEST_SUITE(WriteEeprom_Test)

BOOST_AUTO_TEST_CASE(WriteEeprom_BuildCommand)
{
    //create the command
    ByteStream b = WriteEeprom::buildCommand(456, 956, 100);

    //Check all the bytes in the ByteStream
    BOOST_CHECK_EQUAL(b.read_uint8(0), 0xAA);
    BOOST_CHECK_EQUAL(b.read_uint8(1), 0x05);
    BOOST_CHECK_EQUAL(b.read_uint8(2), 0x00);
    BOOST_CHECK_EQUAL(b.read_uint8(3), 0x01);
    BOOST_CHECK_EQUAL(b.read_uint8(4), 0xC8);
    BOOST_CHECK_EQUAL(b.read_uint8(5), 0x06);
    BOOST_CHECK_EQUAL(b.read_uint8(6), 0x00);
    BOOST_CHECK_EQUAL(b.read_uint8(7), 0x04);
    BOOST_CHECK_EQUAL(b.read_uint8(8), 0x03);
    BOOST_CHECK_EQUAL(b.read_uint8(9), 0xBC);
    BOOST_CHECK_EQUAL(b.read_uint8(10), 0x00);
    BOOST_CHECK_EQUAL(b.read_uint8(11), 0x64);
    BOOST_CHECK_EQUAL(b.read_uint8(12), 0x01);
    BOOST_CHECK_EQUAL(b.read_uint8(13), 0xFB);
}

BOOST_AUTO_TEST_CASE(WriteEeprom_GetResponseResult)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    WriteEeprom::Response response(123, rc);

    //check that the the response result is what it should be
    BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_CASE(WriteEeprom_Match_Fail_DSF)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    WriteEeprom::Response response(123, rc);

    //build the correct packet response first
    WirelessPacket packet = buildWriteEepromResponse(123);

    packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0x08));    //wrong DSF

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(packet), false);
}

BOOST_AUTO_TEST_CASE(WriteEeprom_Match_Fail_Type)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    WriteEeprom::Response response(123, rc);

    //build the correct packet response first
    WirelessPacket packet = buildWriteEepromResponse(123);

    packet.type(static_cast<WirelessPacket::PacketType>(0x02));    //wrong packet type

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(packet), false);
}

BOOST_AUTO_TEST_CASE(WriteEeprom_Match_Fail_Address)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    WriteEeprom::Response response(123, rc);

    //build the correct packet response first
    WirelessPacket packet = buildWriteEepromResponse(123);

    packet.nodeAddress(1);

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(packet), false);
}

BOOST_AUTO_TEST_CASE(WriteEeprom_Match_Fail_PayloadLen)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    WriteEeprom::Response response(123, rc);

    Bytes payload;
    payload.push_back(0x00);
    payload.push_back(0x00);
    payload.push_back(0x00);

    //build the correct packet response first
    WirelessPacket packet = buildWriteEepromResponse(123);

    packet.payload(payload);//invalid payload length

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(packet), false);
}

BOOST_AUTO_TEST_CASE(WriteEeprom_Match_Fail_CommandId)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    WriteEeprom::Response response(123, rc);

    Bytes payload;
    payload.push_back(0x00);
    payload.push_back(0x03);    //invalid command ID

    //build the correct packet response first
    WirelessPacket packet = buildWriteEepromResponse(123);

    packet.payload(payload);//invalid payload length

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(packet), false);
}

BOOST_AUTO_TEST_CASE(WriteEeprom_Match_Success)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    WriteEeprom::Response response(123, rc);

    //build the correct packet response first
    WirelessPacket packet = buildWriteEepromResponse(123);

    //check that the match succeeds
    BOOST_CHECK_EQUAL(response.match(packet), true);

    BOOST_CHECK_EQUAL(response.success(), true);
}

BOOST_AUTO_TEST_SUITE_END()