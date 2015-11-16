/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacketUtils.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/DataBuffer.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacketCollector.h"
#include "mscl/MicroStrain/Wireless/WirelessParser.h"
#include "mscl/MicroStrain/ResponseCollector.h"

#include <boost/test/unit_test.hpp>
#include <turtle/mock.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(WirelessPacketUtils_Test)

BOOST_AUTO_TEST_CASE(WirelessPacketUtils_IntegrityCheckFalse)
{
    //create a packet with an unknown packet type
    WirelessPacket packet;
    packet.type(WirelessPacket::packetType_unknown);

    //verify that the integrity check is false
    BOOST_CHECK_EQUAL(WirelessPacketUtils::packetIntegrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(WirelessPacketUtils_IntegrityCheckTrue_LDC)
{
    WirelessPacket packet;

    DataBuffer b(1024);
    BufferWriter bw = b.getBufferWriter();

    //a valid ASPP packet that has an LDC packet type
    bw.buffer()[0]    = 0xAA;
    bw.buffer()[1]    = 0x07;
    bw.buffer()[2]    = 0x04;        //LDC Packet Type
    bw.buffer()[3]    = 0x00;
    bw.buffer()[4]    = 0x01;
    bw.buffer()[5]    = 0x08;        //payload length
    bw.buffer()[6]    = 0x02;        //first byte in payload of 0x02 signifies sync sampling packet type
    bw.buffer()[7]    = 0x01;        //channel mask
    bw.buffer()[8]    = 0x00;
    bw.buffer()[9]  = 0x03;        //data type
    bw.buffer()[10] = 0x00;
    bw.buffer()[11] = 0x00;
    bw.buffer()[12] = 0x00;
    bw.buffer()[13] = 0x00;
    bw.buffer()[14]    = 0x00;
    bw.buffer()[15] = 0x00;
    bw.buffer()[16] = 0x00;
    bw.buffer()[17] = 0x1A;
    bw.commit(18);

    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    WirelessPacketCollector packetCollector;
    WirelessParser parser(packetCollector, rc);

    //build the packet by calling parseAsPacket
    BOOST_CHECK_EQUAL(parser.parseAsPacket(b, packet, WirelessTypes::freq_11), WirelessParser::parsePacketResult_completePacket);

    BOOST_CHECK_EQUAL(WirelessPacketUtils::packetIntegrityCheck(packet), true);
}

BOOST_AUTO_TEST_CASE(WirelessPacketUtils_IntegrityCheckTrue_BufferedLdc)
{
    WirelessPacket packet;

    DataBuffer b(1024);
    BufferWriter bw = b.getBufferWriter();

    bw.buffer()[0]    = 0xAA;
    bw.buffer()[1]    = 0x07;
    bw.buffer()[2]    = 0x0D;        //Buffered LDC Packet Type
    bw.buffer()[3]    = 0x00;
    bw.buffer()[4]    = 0x01;
    bw.buffer()[5]    = 0x08;        //payload length
    bw.buffer()[6]    = 0x02;        //app id
    bw.buffer()[7]    = 0x01;        //channel mask
    bw.buffer()[8]    = 0x70;
    bw.buffer()[9]  = 0x03;        //data type
    bw.buffer()[10] = 0x00;
    bw.buffer()[11] = 0x00;
    bw.buffer()[12] = 0x00;
    bw.buffer()[13] = 0x00;
    bw.buffer()[14] = 0x00;
    bw.buffer()[15] = 0x00;
    bw.buffer()[16] = 0x00;
    bw.buffer()[17] = 0x93;
    bw.commit(18);

    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    WirelessPacketCollector packetCollector;
    WirelessParser parser(packetCollector, rc);

    //build the packet by calling parseAsPacket
    BOOST_CHECK_EQUAL(parser.parseAsPacket(b, packet, WirelessTypes::freq_15), WirelessParser::parsePacketResult_completePacket);

    BOOST_CHECK_EQUAL(WirelessPacketUtils::packetIntegrityCheck(packet), true);
}

BOOST_AUTO_TEST_CASE(WirelessPacketUtils_IntegrityCheckTrue_Ldc16ch)
{
    WirelessPacket packet;

    DataBuffer b(1024);
    BufferWriter bw = b.getBufferWriter();

    //a valid ASPP packet that has an LDC packet type
    bw.buffer()[0]    = 0xAA;
    bw.buffer()[1]    = 0x07;
    bw.buffer()[2]    = WirelessPacket::packetType_LDC_16ch;
    bw.buffer()[3]    = 0x00;
    bw.buffer()[4]    = 0x01;
    bw.buffer()[5]    = 0x08;        //payload length
    bw.buffer()[6]    = 0x00;        //channel mask
    bw.buffer()[7]    = 0x01;        //channel mask
    bw.buffer()[8]    = 0x70;        //sample rate
    bw.buffer()[9]  = 0x23;        //app id / data type
    bw.buffer()[10] = 0x00;
    bw.buffer()[11] = 0x00;
    bw.buffer()[12] = 0x00;
    bw.buffer()[13] = 0x00;
    bw.buffer()[14]    = 0x00;
    bw.buffer()[15] = 0x00;
    bw.buffer()[16] = 0x00;
    bw.buffer()[17] = 0xB8;
    bw.commit(18);

    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    WirelessPacketCollector packetCollector;
    WirelessParser parser(packetCollector, rc);

    //build the packet by calling parseAsPacket
    BOOST_CHECK_EQUAL(parser.parseAsPacket(b, packet, WirelessTypes::freq_15), WirelessParser::parsePacketResult_completePacket);

    BOOST_CHECK_EQUAL(WirelessPacketUtils::packetIntegrityCheck(packet), true);
}

BOOST_AUTO_TEST_CASE(WirelessPacketUtils_IntegrityCheckTrue_SyncSampling16ch_noChannelsInPayload)
{
    WirelessPacket packet;

    DataBuffer b(1024);
    BufferWriter bw = b.getBufferWriter();

    bw.buffer()[0] = 0xAA;
    bw.buffer()[1] = 0x07;
    bw.buffer()[2] = 0x1A;        //Sync Sampling 16ch Packet Type
    bw.buffer()[3] = 0x00;
    bw.buffer()[4] = 0x01;
    bw.buffer()[5] = 0x0E;        //payload length
    bw.buffer()[6] = 0x00;        //channel mask
    bw.buffer()[7] = 0x01;        //channel mask
    bw.buffer()[8] = 0x70;        //sample rate
    bw.buffer()[9] = 0x23;        //app id / data type
    bw.buffer()[10] = 0x00;
    bw.buffer()[11] = 0x00;
    bw.buffer()[12] = 0x00;
    bw.buffer()[13] = 0x00;
    bw.buffer()[14] = 0x00;
    bw.buffer()[15] = 0x00;
    bw.buffer()[16] = 0x00;
    bw.buffer()[17] = 0x00;
    bw.buffer()[18] = 0x00;
    bw.buffer()[19] = 0x00;
    bw.buffer()[20] = 0x00;
    bw.buffer()[21] = 0x00;
    bw.buffer()[22] = 0x00;
    bw.buffer()[23] = 0xC4;
    bw.commit(24);

    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    WirelessPacketCollector packetCollector;
    WirelessParser parser(packetCollector, rc);

    BOOST_CHECK_EQUAL(WirelessPacketUtils::packetIntegrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(WirelessPacketUtils_IntegrityCheckTrue_SyncSampling16ch)
{
    WirelessPacket packet;

    DataBuffer b(1024);
    BufferWriter bw = b.getBufferWriter();

    bw.buffer()[0]    = 0xAA;
    bw.buffer()[1]    = 0x07;
    bw.buffer()[2]    = 0x1A;        //Sync Sampling 16ch Packet Type
    bw.buffer()[3]    = 0x00;
    bw.buffer()[4]    = 0x01;
    bw.buffer()[5]    = 0x10;        //payload length
    bw.buffer()[6]    = 0x00;        //channel mask
    bw.buffer()[7]    = 0x01;        //channel mask
    bw.buffer()[8]    = 0x70;        //sample rate
    bw.buffer()[9]  = 0x23;        //app id / data type
    bw.buffer()[10] = 0x00;
    bw.buffer()[11] = 0x00;
    bw.buffer()[12] = 0x00;
    bw.buffer()[13] = 0x00;
    bw.buffer()[14] = 0x00;
    bw.buffer()[15] = 0x00;
    bw.buffer()[16] = 0x00;
    bw.buffer()[17] = 0x00;
    bw.buffer()[18] = 0x00;
    bw.buffer()[19] = 0x00;
    bw.buffer()[20] = 0x00;
    bw.buffer()[21] = 0x00;
    bw.buffer()[22] = 0x00;
    bw.buffer()[23] = 0x00;
    bw.buffer()[24] = 0x00;
    bw.buffer()[25] = 0xC6;
    bw.commit(26);

    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    WirelessPacketCollector packetCollector;
    WirelessParser parser(packetCollector, rc);

    //build the packet by calling parseAsPacket
    BOOST_CHECK_EQUAL(parser.parseAsPacket(b, packet, WirelessTypes::freq_15), WirelessParser::parsePacketResult_completePacket);

    BOOST_CHECK_EQUAL(WirelessPacketUtils::packetIntegrityCheck(packet), true);
}

BOOST_AUTO_TEST_CASE(WirelessPacketUtils_IntegrityCheckTrue_BufferedLdc16ch)
{
    WirelessPacket packet;

    DataBuffer b(1024);
    BufferWriter bw = b.getBufferWriter();

    bw.buffer()[0]    = 0xAA;
    bw.buffer()[1]    = 0x07;
    bw.buffer()[2]    = 0x1D;        //Buffered LDC 16ch Packet Type
    bw.buffer()[3]    = 0x00;
    bw.buffer()[4]    = 0x01;
    bw.buffer()[5]    = 0x08;        //payload length
    bw.buffer()[6]    = 0x00;        //channel mask
    bw.buffer()[7]    = 0x01;        //channel mask
    bw.buffer()[8]    = 0x70;        //sample rate
    bw.buffer()[9]  = 0x23;        //app id / data type
    bw.buffer()[10] = 0x00;
    bw.buffer()[11] = 0x00;
    bw.buffer()[12] = 0x00;
    bw.buffer()[13] = 0x00;
    bw.buffer()[14] = 0x00;
    bw.buffer()[15] = 0x00;
    bw.buffer()[16] = 0x00;
    bw.buffer()[17] = 0xC1;
    bw.commit(18);

    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    WirelessPacketCollector packetCollector;
    WirelessParser parser(packetCollector, rc);

    //build the packet by calling parseAsPacket
    BOOST_CHECK_EQUAL(parser.parseAsPacket(b, packet, WirelessTypes::freq_15), WirelessParser::parsePacketResult_completePacket);

    BOOST_CHECK_EQUAL(WirelessPacketUtils::packetIntegrityCheck(packet), true);
}

BOOST_AUTO_TEST_CASE(WirelessPacketUtils_IntegrityCheckTrue_AsyncDigital)
{
    WirelessPacket packet;

    DataBuffer b(1024);
    BufferWriter bw = b.getBufferWriter();

    bw.buffer()[0]    = 0xAA;
    bw.buffer()[1]    = 0x07;
    bw.buffer()[2]    = 0x0E;        //Async Digital Packet
    bw.buffer()[3]    = 0x00;
    bw.buffer()[4]    = 0x01;
    bw.buffer()[5]    = 0x10;        //payload length
    bw.buffer()[6]    = 0x00;        //channel mask
    bw.buffer()[7]    = 0x01;        //channel mask
    bw.buffer()[8]    = 0x00;
    bw.buffer()[9]    = 0x00;
    bw.buffer()[10]    = 0x00;
    bw.buffer()[11]    = 0x00;
    bw.buffer()[12]    = 0x00;
    bw.buffer()[13]    = 0x00;
    bw.buffer()[14]    = 0x00;
    bw.buffer()[15]    = 0x00;
    bw.buffer()[16]    = 0x00;
    bw.buffer()[17]    = 0x00;
    bw.buffer()[18] = 0x00;
    bw.buffer()[19] = 0x00;
    bw.buffer()[20] = 0x00;
    bw.buffer()[21] = 0x01;
    bw.buffer()[22] = 0x00;
    bw.buffer()[23] = 0x00;
    bw.buffer()[24] = 0x00;
    bw.buffer()[25] = 0x28;
    bw.commit(26);

    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    WirelessPacketCollector packetCollector;
    WirelessParser parser(packetCollector, rc);

    //build the packet by calling parseAsPacket
    BOOST_CHECK_EQUAL(parser.parseAsPacket(b, packet, WirelessTypes::freq_15), WirelessParser::parsePacketResult_completePacket);

    BOOST_CHECK_EQUAL(WirelessPacketUtils::packetIntegrityCheck(packet), true);
}

BOOST_AUTO_TEST_CASE(WirelessPacketUtils_IntegrityCheckTrue_AsyncDigitalAnalog)
{
    WirelessPacket packet;

    DataBuffer b(1024);
    BufferWriter bw = b.getBufferWriter();

    bw.buffer()[0]    = 0xAA;
    bw.buffer()[1]    = 0x07;
    bw.buffer()[2]    = 0x0F;        //Async Digital/Analog Packet
    bw.buffer()[3]    = 0x00;
    bw.buffer()[4]    = 0x01;
    bw.buffer()[5]    = 0x13;        //payload length
    bw.buffer()[6]    = 0x00;        //channel mask
    bw.buffer()[7]    = 0x01;        //channel mask
    bw.buffer()[8]    = 0x03;        //data type
    bw.buffer()[9]    = 0x00;
    bw.buffer()[10]    = 0x00;
    bw.buffer()[11]    = 0x00;
    bw.buffer()[12]    = 0x00;
    bw.buffer()[13]    = 0x00;
    bw.buffer()[14]    = 0x00;
    bw.buffer()[15]    = 0x00;
    bw.buffer()[16]    = 0x00;
    bw.buffer()[17]    = 0x00;
    bw.buffer()[18] = 0x00;
    bw.buffer()[19] = 0x00;
    bw.buffer()[20] = 0x00;
    bw.buffer()[21] = 0x00;
    bw.buffer()[22] = 0x01;
    bw.buffer()[23] = 0x00;
    bw.buffer()[24] = 0x00;
    bw.buffer()[25] = 0x00;
    bw.buffer()[26] = 0x00;
    bw.buffer()[27] = 0x00;
    bw.buffer()[28] = 0x2F;
    bw.commit(29);

    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    WirelessPacketCollector packetCollector;
    WirelessParser parser(packetCollector, rc);

    //build the packet by calling parseAsPacket
    BOOST_CHECK_EQUAL(parser.parseAsPacket(b, packet, WirelessTypes::freq_15), WirelessParser::parsePacketResult_completePacket);

    BOOST_CHECK_EQUAL(WirelessPacketUtils::packetIntegrityCheck(packet), true);
}

BOOST_AUTO_TEST_CASE(WirelessPacketUtils_CorrectPacketType_TCLink)
{
    WirelessPacket packet;

    DataBuffer b(1024);

    BufferWriter bw = b.getBufferWriter();

    //a valid ASPP packet that has a TC-LinkLDC type, but actually is a sync sampling packet 
    bw.buffer()[0]    = 0xAA;
    bw.buffer()[1]    = 0x07;
    bw.buffer()[2]    = 0x09;        //TC-LinkLDC type
    bw.buffer()[3]    = 0x00;
    bw.buffer()[4]    = 0x01;
    bw.buffer()[5]    = 0x10;        //payload length
    bw.buffer()[6]    = 0x02;        //first byte in payload of 0x02 signifies sync sampling packet type
    bw.buffer()[7]    = 0x01;        //channel mask
    bw.buffer()[8]    = 0x00;
    bw.buffer()[9]  = 0x03;        //data type
    bw.buffer()[10] = 0x00;
    bw.buffer()[11] = 0x00;
    bw.buffer()[12] = 0x00;
    bw.buffer()[13] = 0x00;
    bw.buffer()[14] = 0x00;
    bw.buffer()[15] = 0x00;
    bw.buffer()[16] = 0x00;
    bw.buffer()[17] = 0x00;
    bw.buffer()[18] = 0x00;
    bw.buffer()[19] = 0x00;
    bw.buffer()[20] = 0x00;
    bw.buffer()[21] = 0x00;
    bw.buffer()[22]    = 0x00;
    bw.buffer()[23] = 0x00;
    bw.buffer()[24] = 0x00;
    bw.buffer()[25] = 0x27;
    bw.commit(26);

    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    WirelessPacketCollector packetCollector;
    WirelessParser parser(packetCollector, rc);

    //build the packet by calling parseAsPacket
    BOOST_CHECK_EQUAL(parser.parseAsPacket(b, packet, WirelessTypes::freq_15), WirelessParser::parsePacketResult_completePacket);

    //check that the packet's type has been changed to a sync sampling type
    BOOST_CHECK_EQUAL(packet.type(), WirelessPacket::packetType_SyncSampling);
}

BOOST_AUTO_TEST_CASE(WirelessPacketUtils_CorrectPacketType_SHMLink)
{
    WirelessPacket packet;
    packet.type(WirelessPacket::packetType_LDC);

    Bytes b;
    b.push_back(WirelessPacket::packetType_SHM);

    packet.payload(b);

    WirelessPacketUtils::correctPacketType(packet);

    //check that the packet's type has been changed to a SHM
    BOOST_CHECK_EQUAL(packet.type(), WirelessPacket::packetType_SHM);
}

BOOST_AUTO_TEST_SUITE_END()