/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Commands/StartSyncSampling.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/MicroStrain/ResponseCollector.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

WirelessPacket buildSyncSamplingResponse(uint16 nodeAddress)
{
    Bytes payload;
    payload.push_back(0x00);
    payload.push_back(0x3B);
    payload.push_back(0x00);

    //build the correct packet response first
    WirelessPacket packet;
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0x07));
    packet.type(static_cast<WirelessPacket::PacketType>(0x00));
    packet.nodeAddress(nodeAddress);
    packet.payload(payload);

    return packet;
}

BOOST_AUTO_TEST_SUITE(StartSyncSampling_Test)

BOOST_AUTO_TEST_CASE(StartSyncSampling_buildCommand)
{
    ByteStream result = StartSyncSampling::buildCommand(WirelessPacket::aspp_v1, 123);

    uint8 sop = WirelessPacket::ASPP_V1_SOP;

    BOOST_CHECK_EQUAL(result.read_uint8(0), sop);
    BOOST_CHECK_EQUAL(result.read_uint8(1), 0x05);
    BOOST_CHECK_EQUAL(result.read_uint8(2), 0x00);
    BOOST_CHECK_EQUAL(result.read_uint16(3), 123);
    BOOST_CHECK_EQUAL(result.read_uint8(5), 0x02);
    BOOST_CHECK_EQUAL(result.read_uint16(6), 0x003B);
    BOOST_CHECK_EQUAL(result.read_uint16(8), 0x00BD);
}

BOOST_AUTO_TEST_CASE(StartSyncSampling_Response_constructor)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    StartSyncSampling::Response response(123, rc);

    BOOST_CHECK_EQUAL(response.fullyMatched(), false);
    BOOST_CHECK_EQUAL(response.success(), false);
}

BOOST_AUTO_TEST_CASE(StartSyncSampling_Response_match_success)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    StartSyncSampling::Response response(123, rc);

    //build the packet response
    WirelessPacket packet = buildSyncSamplingResponse(123);

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(packet), true);
}

BOOST_AUTO_TEST_CASE(StartSyncSampling_Response_match_fail_dsf)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    StartSyncSampling::Response response(123, rc);

    //build the packet response
    WirelessPacket packet = buildSyncSamplingResponse(123);

    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0x08));    //wrong DSF

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(packet), false);
}

BOOST_AUTO_TEST_CASE(StartSyncSampling_Response_match_fail_packetType)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    StartSyncSampling::Response response(123, rc);

    //build the packet response
    WirelessPacket packet = buildSyncSamplingResponse(123);

    packet.type(static_cast<WirelessPacket::PacketType>(0x02));    //wrong packet type

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(packet), false);
}

BOOST_AUTO_TEST_CASE(StartSyncSampling_Response_match_fail_nodeAddress)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    StartSyncSampling::Response response(123, rc);

    //build the packet response
    WirelessPacket packet = buildSyncSamplingResponse(123);

    packet.nodeAddress(1234);    //wrong node address

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(packet), false);
}

BOOST_AUTO_TEST_CASE(StartSyncSampling_Response_match_fail_payloadLen)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    StartSyncSampling::Response response(123, rc);

    //build the packet response
    WirelessPacket packet = buildSyncSamplingResponse(123);

    Bytes payload;
    payload.push_back(0x00);

    packet.payload(payload);//invalid payload length

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(packet), false);
}

BOOST_AUTO_TEST_CASE(StartSyncSampling_Response_match_fail_cmdId)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    StartSyncSampling::Response response(123, rc);

    //build the packet response
    WirelessPacket packet = buildSyncSamplingResponse(123);

    Bytes payload;
    payload.push_back(0x01);
    payload.push_back(0x3B);
    payload.push_back(0x00);

    packet.payload(payload);//invalid payload length

    //check that the match fails
    BOOST_CHECK_EQUAL(response.match(packet), false);
}

BOOST_AUTO_TEST_SUITE_END()
