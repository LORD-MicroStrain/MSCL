/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Wireless/Commands/ReadEeprom.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

WirelessPacket buildReadEepromResponse(int nodeAddress)
{
    Bytes payload;
    payload.push_back(0x00);
    payload.push_back(0x00);

    //build the correct packet response first
    WirelessPacket packet;
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0x00));
    packet.type(static_cast<WirelessPacket::PacketType>(0x00));
    packet.nodeAddress(nodeAddress);
    packet.payload(payload);

    return packet;
}

BOOST_AUTO_TEST_SUITE(ReadEeprom_Test)

BOOST_AUTO_TEST_CASE(ReadEeprom_BuildCommand)
{
    //create the command
    ByteStream b = ReadEeprom::buildCommand(456, 956);

    //Check all the bytes in the ByteStream
    BOOST_CHECK_EQUAL(b.read_uint8(0), 0xAA);
    BOOST_CHECK_EQUAL(b.read_uint8(1), 0x05);
    BOOST_CHECK_EQUAL(b.read_uint8(2), 0x00);
    BOOST_CHECK_EQUAL(b.read_uint8(3), 0x01);
    BOOST_CHECK_EQUAL(b.read_uint8(4), 0xC8);
    BOOST_CHECK_EQUAL(b.read_uint8(5), 0x04);
    BOOST_CHECK_EQUAL(b.read_uint8(6), 0x00);
    BOOST_CHECK_EQUAL(b.read_uint8(7), 0x03);
    BOOST_CHECK_EQUAL(b.read_uint8(8), 0x03);
    BOOST_CHECK_EQUAL(b.read_uint8(9), 0xBC);
    BOOST_CHECK_EQUAL(b.read_uint8(10), 0x01);
    BOOST_CHECK_EQUAL(b.read_uint8(11), 0x94);
}

BOOST_AUTO_TEST_CASE(ReadEeprom_GetResponseResult)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    ReadEeprom::Response response(123, rc);

    //check that the the response result is what it should be
    BOOST_CHECK_EQUAL(response.success(), false);
    BOOST_CHECK_THROW(response.eepromValue(), Error);
}

BOOST_AUTO_TEST_CASE(ReadEeprom_Match_Fail_DSF)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    ReadEeprom::Response response(123, rc);

    //build the correct packet response first
    WirelessPacket packet = buildReadEepromResponse(123);

    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0x07));    //wrong DSF

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(packet), false);
}

BOOST_AUTO_TEST_CASE(ReadEeprom_Match_Fail_Type)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    ReadEeprom::Response response(123, rc);

    //build the correct packet response first
    WirelessPacket packet = buildReadEepromResponse(123);

    packet.type(static_cast<WirelessPacket::PacketType>(0x01));    //wrong packet type

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(packet), false);
}

BOOST_AUTO_TEST_CASE(ReadEeprom_Match_Fail_Address)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    ReadEeprom::Response response(123, rc);

    //build the correct packet response first
    WirelessPacket packet = buildReadEepromResponse(123);

    packet.nodeAddress(1);

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(packet), false);
}

BOOST_AUTO_TEST_CASE(ReadEeprom_Match_Fail_PayloadLen)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    ReadEeprom::Response response(123, rc);

    Bytes payload;
    payload.push_back(0x00);

    //build the correct packet response first
    WirelessPacket packet = buildReadEepromResponse(123);

    packet.payload(payload);//invalid payload length

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(packet), false);
}

BOOST_AUTO_TEST_CASE(ReadEeprom_Match_Success)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    ReadEeprom::Response response(123, rc);

    //build the correct packet response first
    WirelessPacket packet = buildReadEepromResponse(123);

    //check that the match succeeds
    BOOST_CHECK_EQUAL(response.match(packet), true);

    BOOST_CHECK_EQUAL(response.success(), true);
}

BOOST_AUTO_TEST_SUITE_END()