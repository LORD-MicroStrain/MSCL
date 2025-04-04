/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/MIP/Packets/MipDataPacket.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacket.h"
#include "mscl/Utils.h"

using namespace mscl;

DISABLE_WARNING_BOOST_START
#include <boost/test/unit_test.hpp>
DISABLE_WARNING_BOOST_END

BOOST_AUTO_TEST_SUITE(InertialDataPacket_Test)

BOOST_AUTO_TEST_CASE(InertialDataPacket_DefaultConstructor)
{
    MipDataPacket p;
    BOOST_CHECK_EQUAL(p.collectedTimestamp().nanoseconds(), 0);
}

BOOST_AUTO_TEST_CASE(InertialDataPacket_ParseValidData)
{
    //build the payload bytes
    Bytes b;
    b.push_back(0x0E);    //Field Length
    b.push_back(0x01);    //Data Descriptor
    b.push_back(0x00);    //Accel 1 float
    b.push_back(0x00);
    b.push_back(0x00);
    b.push_back(0x00);
    b.push_back(0x00);    //Accel 2 float
    b.push_back(0x00);
    b.push_back(0x00);
    b.push_back(0x00);
    b.push_back(0x00);    //Accel 3 float
    b.push_back(0x00);
    b.push_back(0x00);
    b.push_back(0x00);

    //create a MipPacket with legitimate data
    MipPacket p;
    p.descriptorSet(DescriptorSet::DESC_SET_DATA_SENSOR);
    p.payload(b);

    //create a MipDataPacket with the MipPacket, which should immediately parse the data for fields and data points
    MipDataPacket packet(p);

    //make sure it found valid data points
    BOOST_CHECK_EQUAL(packet.data().size(), 3);

    //make sure the data is stored correctly
    BOOST_CHECK_EQUAL(packet.data()[0].storedAs(), valueType_float);

    BOOST_CHECK_EQUAL(packet.data()[0].as_float(), 0.0);
    BOOST_CHECK_EQUAL(packet.data()[1].as_float(), 0.0);
    BOOST_CHECK_EQUAL(packet.data()[2].as_float(), 0.0);

    BOOST_CHECK_EQUAL(packet.data()[0].valid(), true);

    Utils::threadSleep(500);
    //check that the timestamp is OK (less than current time)
    BOOST_CHECK_LT(packet.collectedTimestamp().nanoseconds(), Timestamp::timeNow().nanoseconds());
}

BOOST_AUTO_TEST_CASE(InertialDataPacket_ParseValidData_multipleFields)
{
    //build the payload bytes
    ByteStream bytes;
    bytes.append_uint16(0x0E01);        //Field Len, Data Descriptor
    bytes.append_float(0.0f);            //Accel 1 float
    bytes.append_float(0.0f);            //Accel 2 float
    bytes.append_float(0.0f);            //Accel 3 float
    bytes.append_uint16(0x0E02);        //Field Len, Data Descriptor
    bytes.append_float(1.234f);            //Gyro 1 float
    bytes.append_float(0.0f);            //Gyro 2 float
    bytes.append_float(0.0f);            //Gyro 3 float

    //create a MipPacket with legitimate data
    MipPacket p;
    p.descriptorSet(DescriptorSet::DESC_SET_DATA_SENSOR);
    p.payload(bytes.data());

    //create a MipDataPacket with the MipPacket, which should immediately parse the data for fields and data points
    MipDataPacket packet(p);

    //make sure it found valid data points
    BOOST_CHECK_EQUAL(packet.data().size(), 6);

    //check the data is correct
    BOOST_CHECK_EQUAL(packet.data()[0].as_float(), 0.0);
    BOOST_CHECK_EQUAL(packet.data()[1].as_float(), 0.0);
    BOOST_CHECK_EQUAL(packet.data()[2].as_float(), 0.0);

    BOOST_CHECK_CLOSE(packet.data()[3].as_float(), 1.234, 0.0001);
    BOOST_CHECK_EQUAL(packet.data()[4].as_float(), 0.0);
    BOOST_CHECK_EQUAL(packet.data()[5].as_float(), 0.0);

    BOOST_CHECK_EQUAL(packet.data()[0].valid(), true);
    BOOST_CHECK_EQUAL(packet.data()[1].valid(), true);
}

// BOOST_AUTO_TEST_CASE(InertialDataPacket_ParseInvalidData)
// {
//     //TODO: parse packets with invalid data, make sure they show as invalid
// }

BOOST_AUTO_TEST_CASE(InertialDataPacket_CorruptedBytes)
{
    //build the payload bytes
    ByteStream bytes;
    bytes.append_uint16(0x0E01);        //Field Len, Data Descriptor
    bytes.append_float(1.234f);         //Accel 1 float
    bytes.append_float(0.0f);           //Accel 2 float
    bytes.append_float(0.0f);           //Accel 3 float
    bytes.append_uint16(0xFA02);        //Invalid Field Len, Data Descriptor
    bytes.append_float(4.567f);
    bytes.append_float(0.0f);
    bytes.append_float(0.0f);

    MipPacket p;
    p.descriptorSet(DescriptorSet::DESC_SET_DATA_SENSOR);
    p.payload(bytes.data());

    //create a MipDataPacket with the MipPacket, which should immediately parse the data for fields and data points
    MipDataPacket packet(p);    //make sure this doesn't throw an exception

    //make sure it found the first valid data points
    BOOST_CHECK_EQUAL(packet.data().size(), 3);

    //check the data is correct
    BOOST_CHECK_CLOSE(packet.data()[0].as_float(), 1.234, 0.0001);
    BOOST_CHECK_EQUAL(packet.data()[1].as_float(), 0.0);
    BOOST_CHECK_EQUAL(packet.data()[2].as_float(), 0.0);
}

BOOST_AUTO_TEST_SUITE_END()
