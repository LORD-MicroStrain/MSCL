/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/DataBuffer.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/ResponsePattern.h"
#include "mscl/MicroStrain/Wireless/Commands/LongPing.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

using namespace mscl;

DISABLE_WARNING_BOOST_START
#include <boost/test/unit_test.hpp>
DISABLE_WARNING_BOOST_END

BOOST_AUTO_TEST_SUITE(ResponseCollector_Test)

BOOST_AUTO_TEST_CASE(ResponsePattern_Match)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    //the ResponsePattern class just always returns false for match functions
    ResponsePattern p(rc);
    DataBuffer d(1);
    BOOST_CHECK_EQUAL(p.match(d), false);

    WirelessPacket packet;
    BOOST_CHECK_EQUAL(p.match(packet), false);

    MipDataField field;
    BOOST_CHECK_EQUAL(p.match(field), false);
}

BOOST_AUTO_TEST_CASE(ResponseCollector_MatchExpected_Bytes_Fail)
{
    std::shared_ptr<ResponseCollector> collector(new ResponseCollector);

    //create the response for the LongPing command with the node address
    LongPing::Response response(123, collector);

    //create a DataBuffer of Bytes
    Bytes b;
    b.push_back(0x01);
    b.push_back(0x02);
    b.push_back(0x03);
    DataBuffer data(b);

    //check that matchExpected() returns false
    BOOST_CHECK_EQUAL(collector->matchExpected(data), false);

    //check that we are still waiting for a response
    BOOST_CHECK_EQUAL(collector->waitingForResponse(), true);
}

BOOST_AUTO_TEST_CASE(WirelessPacketCollector_MatchExpected_Packet_Success)
{
    std::shared_ptr<ResponseCollector> collector(new ResponseCollector);

    //create the response for the LongPing command with the node address
    LongPing::Response response(123, collector);

    //create a DataBuffer of Bytes
    Bytes b;
    b.push_back(0x00);
    b.push_back(0x00);

    WirelessPacket packet;
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0x07));
    packet.type(static_cast<WirelessPacket::PacketType>(0x02));
    packet.nodeAddress(123);
    packet.payload(b);

    //check that matchExpected() returns true
    BOOST_CHECK_EQUAL(collector->matchExpected(packet, 0), true);

    collector->unregisterResponse(&response);

    //check that we are no longer waiting for a response
    BOOST_CHECK_EQUAL(collector->waitingForResponse(), false);
}

BOOST_AUTO_TEST_CASE(WirelessPacketCollector_MatchExpected_Packet_False)
{
    std::shared_ptr<ResponseCollector> collector(new ResponseCollector);

    //create the response for the LongPing command with the node address
    LongPing::Response response(123, collector);

    //create a DataBuffer of Bytes
    Bytes b;
    b.push_back(0x00);
    b.push_back(0x00);

    WirelessPacket packet;
    packet.deliveryStopFlags(DeliveryStopFlags::fromInvertedByte(0x07));
    packet.type(static_cast<WirelessPacket::PacketType>(0x02));
    packet.nodeAddress(456);
    packet.payload(b);

    //check that matchExpected() returns false
    BOOST_CHECK_EQUAL(collector->matchExpected(packet, 0), false);
}

BOOST_AUTO_TEST_CASE(WirelessPacketCollector_MatchExpected_InertialDataField_Fail)
{
    ResponseCollector collector;

    MipDataField f;

    //check that matchExpected() returns false
    BOOST_CHECK_EQUAL(collector.matchExpected(f), false);
}

BOOST_AUTO_TEST_SUITE_END()
