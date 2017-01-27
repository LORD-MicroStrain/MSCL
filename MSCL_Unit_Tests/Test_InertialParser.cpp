/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Inertial/InertialParser.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacket.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialDataPacket.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketCollector.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/ChecksumBuilder.h"
#include "mscl/MicroStrain/DataBuffer.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(InertialParser_Test)

BOOST_AUTO_TEST_SUITE(InertialParser_parseAsPacket)

BOOST_AUTO_TEST_CASE(InertialParser_parseAsPacket_NotEnoughData)
{
    //not enough bytes to be any MIP packet
    ByteStream b;
    b.append_uint16(0x7565);

    DataBuffer buffer(b.data());

    std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
    InertialPacketCollector packetCollector;
    InertialParser parser(&packetCollector, responseCollector);
    InertialPacket packet;

    //check that the result is inertialParserResult_notEnoughData b/c there isn't enough data to be a MIP packet 
    BOOST_CHECK_EQUAL(parser.parseAsPacket(buffer, packet), inertialParserResult_notEnoughData);

    b.append_uint8(0x80);
    b.append_uint8(0xAB);    //payload length
    b.append_uint16(0x0102);
    b.append_uint16(0x0102);

    DataBuffer buffer2(b.data());

    //check that the result is inertialParserResult_notEnoughData b/c there isn't enough data in the payload
    BOOST_CHECK_EQUAL(parser.parseAsPacket(buffer2, packet), inertialParserResult_notEnoughData);
}

BOOST_AUTO_TEST_CASE(InertialParser_parseAsPacket_InvalidPacket)
{
    ByteStream b;
    b.append_uint16(0x0165);    //not a start of MIP packet
    b.append_uint16(0x0000);
    b.append_uint16(0x0000);
    b.append_uint16(0x0000);

    DataBuffer buffer(b.data());

    std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
    InertialPacketCollector packetCollector;
    InertialParser parser(&packetCollector, responseCollector);
    InertialPacket packet;

    //check that the result is inertialParserResult_invalidPacket b/c the first bytes aren't the start of a packet
    BOOST_CHECK_EQUAL(parser.parseAsPacket(buffer, packet), inertialParserResult_invalidPacket);
}

BOOST_AUTO_TEST_CASE(InertialParser_parseAsPacket_BadChecksum)
{
    ByteStream b;
    b.append_uint16(0x7565);
    b.append_uint8(0x80);
    b.append_uint8(0x0E);    //payload length
    b.append_uint8(0x0E);
    b.append_uint8(0x04);
    b.append_uint32(0x00000000);
    b.append_uint32(0x00000000);
    b.append_uint32(0x00000000);
    b.append_uint16(0x0000);    //bad checksum

    DataBuffer buffer(b.data());

    std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
    InertialPacketCollector packetCollector;
    InertialParser parser(&packetCollector, responseCollector);
    InertialPacket packet;

    //check that the result is inertialParserResult_badChecksum b/c the checksum is invalid
    BOOST_CHECK_EQUAL(parser.parseAsPacket(buffer, packet), inertialParserResult_badChecksum);
}

BOOST_AUTO_TEST_CASE(InertialParser_parseAsPacket_CompletePacket)
{
    ByteStream b;
    b.append_uint16(0x7565);
    b.append_uint8(0x80);
    b.append_uint8(0x0E);    //payload length
    b.append_uint8(0x0E);
    b.append_uint8(0x04);
    b.append_uint32(0x00000000);
    b.append_uint32(0x00000000);
    b.append_uint32(0x00000000);
    
    ChecksumBuilder check;
    check.appendByteStream(b);
    uint16 checksum = check.fletcherChecksum();
    b.append_uint16(checksum);//append valid checksum

    DataBuffer buffer(b.data());

    std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
    InertialPacketCollector packetCollector;
    InertialParser parser(&packetCollector, responseCollector);
    InertialPacket packet;

    //check that the result is inertialParserResult_completePacket b/c the packet is valid
    BOOST_CHECK_EQUAL(parser.parseAsPacket(buffer, packet), inertialParserResult_completePacket);
}

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE(InertialParser_ParseSuite)

BOOST_AUTO_TEST_CASE(InertialParser_parse_validDataPacket_AfterBadBytes)
{
    ByteStream b;
    b.append_uint16(0x0104);
    b.append_uint16(0x7565);
    b.append_uint8(0x80);
    b.append_uint8(0x0E);    //payload length
    b.append_uint8(0x0E);
    b.append_uint8(0x04);
    b.append_uint32(0x00000000);
    b.append_uint32(0x00000000);
    b.append_uint32(0x00000000);
    b.append_uint16(b.calculateFletcherChecksum(2, 19));

    DataBuffer buffer(b.data());

    std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
    InertialPacketCollector packetCollector;
    InertialParser parser(&packetCollector, responseCollector);
    InertialPacket packet;

    InertialDataPackets dataPackets;

    packetCollector.getDataPackets(dataPackets);

    BOOST_CHECK_EQUAL(dataPackets.size(), 0);

    //call the parse() function, sending the DataBuffer we created
    parser.parse(buffer);

    //calling getNextDataPacket now should return a legitimate InertialDataPacket
    packetCollector.getDataPackets(dataPackets, 0);

    BOOST_CHECK_EQUAL(dataPackets.at(0).isDataPacket(), true);
    BOOST_CHECK_EQUAL(dataPackets.at(0).descriptorSet(), DescriptorSet::DESC_SET_DATA_SENSOR);
}

BOOST_AUTO_TEST_CASE(InertialParser_parse_validDataPacket)
{
    ByteStream b;
    b.append_uint16(0x7565);
    b.append_uint8(0x80);
    b.append_uint8(0x0E);    //payload length
    b.append_uint8(0x0E);
    b.append_uint8(0x04);
    b.append_uint32(0x00000000);
    b.append_uint32(0x00000000);
    b.append_uint32(0x00000000);
    
    ChecksumBuilder check;
    check.appendByteStream(b);
    uint16 checksum = check.fletcherChecksum();
    b.append_uint16(checksum);//append valid checksum

    DataBuffer buffer(b.data());

    std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
    InertialPacketCollector packetCollector;
    InertialParser parser(&packetCollector, responseCollector);
    InertialPacket packet;

    InertialDataPackets dataPackets;

    packetCollector.getDataPackets(dataPackets);

    BOOST_CHECK_EQUAL(dataPackets.size(), 0);

    //call the parse() function, sending the DataBuffer we created
    parser.parse(buffer);

    //calling getNextDataPacket now should return a legitimate InertialDataPacket
    packetCollector.getDataPackets(dataPackets);

    BOOST_CHECK_EQUAL(dataPackets.at(0).isDataPacket(), true);
    BOOST_CHECK_EQUAL(dataPackets.at(0).descriptorSet(), DescriptorSet::DESC_SET_DATA_SENSOR);
}

BOOST_AUTO_TEST_CASE(InertialParser_parse_responsePacket_notExpected)
{
    ByteStream b;
    b.append_uint16(0x7565);
    b.append_uint8(0x01);
    b.append_uint8(0x04);    //payload length
    b.append_uint8(0x04);
    b.append_uint8(0xF1);
    b.append_uint8(0x01);
    b.append_uint8(0x00);
    
    ChecksumBuilder check;
    check.appendByteStream(b);
    uint16 checksum = check.fletcherChecksum();
    b.append_uint16(checksum);//append valid checksum

    DataBuffer buffer(b.data());

    std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
    InertialPacketCollector packetCollector;
    InertialParser parser(&packetCollector, responseCollector);
    InertialPacket packet;

    InertialDataPackets dataPackets;

    packetCollector.getDataPackets(dataPackets);

    BOOST_CHECK_EQUAL(dataPackets.size(), 0);

    //call the parse() function, sending the DataBuffer we created
    parser.parse(buffer);

    packetCollector.getDataPackets(dataPackets);

    BOOST_CHECK_EQUAL(dataPackets.size(), 0);
}

BOOST_AUTO_TEST_CASE(InertialParser_parse_badChecksum)
{
    ByteStream b;
    b.append_uint16(0x7565);
    b.append_uint8(0x80);
    b.append_uint8(0x0E);    //payload length
    b.append_uint8(0x0E);
    b.append_uint8(0x04);
    b.append_uint32(0x00000000);
    b.append_uint32(0x00000000);
    b.append_uint32(0x00000000);
    b.append_uint16(0x0102);    //bad checksum

    DataBuffer buffer(b.data());

    std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
    InertialPacketCollector packetCollector;
    InertialParser parser(&packetCollector, responseCollector);
    InertialPacket packet;

    InertialDataPackets dataPackets;

    packetCollector.getDataPackets(dataPackets);

    BOOST_CHECK_EQUAL(dataPackets.size(), 0);

    //call the parse() function, sending the DataBuffer we created
    parser.parse(buffer);

    packetCollector.getDataPackets(dataPackets);

    BOOST_CHECK_EQUAL(dataPackets.size(), 0);
}

BOOST_AUTO_TEST_CASE(InertialParser_parse_notEnoughData)
{
    ByteStream b;
    b.append_uint16(0x7565);
    b.append_uint8(0x80);
    b.append_uint8(0x0E);    //payload length
    b.append_uint8(0x0E);
    b.append_uint8(0x04);
    b.append_uint32(0x00000000);
    b.append_uint32(0x00000000);
    b.append_uint32(0x00000000);

    ChecksumBuilder check;
    check.appendByteStream(b);
    uint16 checksum = check.fletcherChecksum();
    b.append_uint16(checksum);//append the valid checksum 

    //add another part of a valid packet, but missing the checksum
    b.append_uint16(0x7565);
    b.append_uint8(0x80);
    b.append_uint8(0x0E);    //payload length
    b.append_uint8(0x0E);
    b.append_uint8(0x04);
    b.append_uint32(0x00000000);
    b.append_uint32(0x00000000);
    b.append_uint32(0x00000000);

    DataBuffer buffer(b.data());

    std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
    InertialPacketCollector packetCollector;
    InertialParser parser(&packetCollector, responseCollector);
    InertialPacket packet;

    InertialDataPackets dataPackets;

    packetCollector.getDataPackets(dataPackets);

    BOOST_CHECK_EQUAL(dataPackets.size(), 0);

    //call the parse() function, sending the DataBuffer we created
    parser.parse(buffer);

    packetCollector.getDataPackets(dataPackets);

    BOOST_CHECK_EQUAL(dataPackets.size(), 1);
    dataPackets.clear();

    packetCollector.getDataPackets(dataPackets);

    BOOST_CHECK_EQUAL(dataPackets.size(), 0);
}

BOOST_AUTO_TEST_CASE(InertialParser_parse_validDataPacket_AfterNotEnoughData)
{
    ByteStream b;
    b.append_uint16(0x7565);    //make it look like a valid packet by putting random SOP bytes here
    b.append_uint16(0x7565);
    b.append_uint8(0x80);
    b.append_uint8(0x0E);    //payload length
    b.append_uint8(0x0E);
    b.append_uint8(0x04);
    b.append_uint32(0x00000000);
    b.append_uint32(0x00000000);
    b.append_uint32(0x00000000);
    b.append_uint16(b.calculateFletcherChecksum(2, 19));

    DataBuffer buffer(b.data());

    std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
    InertialPacketCollector packetCollector;
    InertialParser parser(&packetCollector, responseCollector);
    InertialPacket packet;

    InertialDataPackets dataPackets;

    packetCollector.getDataPackets(dataPackets);

    BOOST_CHECK_EQUAL(dataPackets.size(), 0);

    //call the parse() function, sending the DataBuffer we created
    parser.parse(buffer);

    packetCollector.getDataPackets(dataPackets);

    BOOST_CHECK_EQUAL(dataPackets.size(), 1);

    BOOST_CHECK_EQUAL(dataPackets.at(0).isDataPacket(), true);
    BOOST_CHECK_EQUAL(dataPackets.at(0).descriptorSet(), DescriptorSet::DESC_SET_DATA_SENSOR);
}

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE_END()