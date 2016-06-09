/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Wireless/Commands/LongPing.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/MicroStrain/ResponseCollector.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

WirelessPacket buildLongPingResponse(int nodeAddress)
{
    Bytes payload;
    payload.push_back(0x00);
    payload.push_back(0x00);

    //build the correct packet response first
    WirelessPacket packet;
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0x07));
    packet.type(static_cast<WirelessPacket::PacketType>(0x02));
    packet.nodeAddress(nodeAddress);
    packet.payload(payload);

    return packet;
}

BOOST_AUTO_TEST_SUITE(LongPing_Test)

BOOST_AUTO_TEST_CASE(PingResponse_Constructor)
{
    PingResponse r;

    int unknownRssi = WirelessTypes::UNKNOWN_RSSI;
    
    //check that the default constructor initialized correctly (throws exceptions for all values)
    BOOST_CHECK_EQUAL(r.success(), false);
    BOOST_CHECK_EQUAL(r.nodeRssi(), unknownRssi);
    BOOST_CHECK_EQUAL(r.baseRssi(), unknownRssi);
}

BOOST_AUTO_TEST_CASE(LongPing_BuildCommand)
{
    //create a LongPing command
    ByteStream b = LongPing::buildCommand(4794);

    //Check all the bytes in the ByteStream
    BOOST_CHECK_EQUAL(b.read_uint8(0), 0xAA);
    BOOST_CHECK_EQUAL(b.read_uint8(1), 0x05);
    BOOST_CHECK_EQUAL(b.read_uint8(2), 0x00);
    BOOST_CHECK_EQUAL(b.read_uint8(3), 0x12);
    BOOST_CHECK_EQUAL(b.read_uint8(4), 0xBA);
    BOOST_CHECK_EQUAL(b.read_uint8(5), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(6), 0x00);
    BOOST_CHECK_EQUAL(b.read_uint8(7), 0x02);
    BOOST_CHECK_EQUAL(b.read_uint8(8), 0x00);
    BOOST_CHECK_EQUAL(b.read_uint8(9), 0xD5);
}

BOOST_AUTO_TEST_CASE(LongPing_GetResponseResult)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    LongPing::Response response(123, rc);

    PingResponse r = response.result();

    int unknownRssi = WirelessTypes::UNKNOWN_RSSI;

    //check that the the response result is what it should be
    BOOST_CHECK_EQUAL(r.success(), false);
    BOOST_CHECK_EQUAL(r.nodeRssi(), unknownRssi);
    BOOST_CHECK_EQUAL(r.baseRssi(), unknownRssi);
}

BOOST_AUTO_TEST_CASE(LongPing_Match_Fail_DSF)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    LongPing::Response response(123, rc);

    //build the correct packet response first
    WirelessPacket packet = buildLongPingResponse(123);

    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0x00));    //wrong DSF

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(packet), false);
}

BOOST_AUTO_TEST_CASE(LongPing_Match_Fail_Type)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    LongPing::Response response(123, rc);

    //build the correct packet response first
    WirelessPacket packet = buildLongPingResponse(123);

    packet.type(static_cast<WirelessPacket::PacketType>(0x00));    //wrong packet type

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(packet), false);
}

BOOST_AUTO_TEST_CASE(LongPing_Match_Fail_Address)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    LongPing::Response response(123, rc);

    //build the correct packet response first
    WirelessPacket packet = buildLongPingResponse(123);

    packet.nodeAddress(456);    //wrong node address

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(packet), false);
}

BOOST_AUTO_TEST_CASE(LongPing_Match_Fail_PayloadLen)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    LongPing::Response response(123, rc);

    Bytes payload;
    payload.push_back(0x00);

    //build the correct packet response first
    WirelessPacket packet = buildLongPingResponse(123);

    packet.payload(payload);    //invalid payload length

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(packet), false);
}

BOOST_AUTO_TEST_CASE(LongPing_Match_Fail_Payload)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    LongPing::Response response(123, rc);

    Bytes payload;
    payload.push_back(0x00);
    payload.push_back(0x01);

    //build the correct packet response first
    WirelessPacket packet = buildLongPingResponse(123);

    packet.payload(payload);    //invalid payload bytes

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(packet), false);
}

BOOST_AUTO_TEST_CASE(LongPing_Match_Success)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    LongPing::Response response(123, rc);

    //build the correct packet response first
    WirelessPacket packet = buildLongPingResponse(123);

    //check that the match succeeds
    BOOST_CHECK_EQUAL(response.match(packet), true);

    BOOST_CHECK_EQUAL(response.result().success(), true);
}


BOOST_AUTO_TEST_SUITE_END()