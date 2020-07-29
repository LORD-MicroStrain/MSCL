/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/Communication/SerialConnection.h"
#include "mscl/MicroStrain/Inertial/InertialNode.h"
#include "mscl/MicroStrain/Displacement/DisplacementModels.h"
#include "mscl/MicroStrain/MIP/MipNodeFeatures.h"
#include "mscl/MicroStrain/MIP/Packets/MipDataPacket.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/ChecksumBuilder.h"
#include "mscl/Utils.h"

#include <boost/test/unit_test.hpp>
#include "mock_InertialNode.h"
#include "mock_Connection.h"

#include <string>

using namespace mscl;

void expectNodeInfo_InertialNode(std::shared_ptr<mock_InertialNodeImpl> node, const std::string& modelNumber="6251-12345")
{
    //========================================================================================
    //BUILD THE RESPONSE TO THE getDeviceInfo COMMAND
    MipDeviceInfo info;
    info.fwVersion = Version(1, 1, 17);
    info.modelName = "ABCDABCDABCDABCD";
    info.modelNumber = modelNumber;
    info.serialNumber = "ABCDABCDABCDABCD";
    info.lotNumber = "ABCDABCDABCDABCD";
    info.deviceOptions = "ABCDABCDABCDABCD";

    //make the getDeviceInfo command return the response we created
    MOCK_EXPECT(node->getDeviceInfo).returns(info);    
    //========================================================================================

    //========================================================================================
    //BUILD THE RESPONSE TO THE getDescriptorSets COMMAND
    std::vector<uint16> fields;
    fields.push_back(MipTypes::CMD_GET_SENSOR_RATE_BASE);
    fields.push_back(MipTypes::CMD_GET_EF_RATE_BASE);
    fields.push_back(MipTypes::CMD_GET_GNSS_RATE_BASE);
    
    //make the getDescriptorSets command return the response we created
    MOCK_EXPECT(node->getDescriptorSets).returns(fields);
    //========================================================================================
}

BOOST_AUTO_TEST_SUITE(InertialNode_Test)

BOOST_AUTO_TEST_CASE(InertialNode_getDataPackets_noData)
{
    std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
    Connection conn(connImpl);

    //create the InertialNode object
    InertialNode node(conn);

    //check that there is no data to get
    BOOST_CHECK_EQUAL(node.totalPackets(), 0);
    BOOST_CHECK_EQUAL(node.getDataPackets().size(), 0);
}

BOOST_AUTO_TEST_CASE(InertialNode_getDataPackets_success)
{
    std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
    Connection conn(connImpl);

    //create the InertialNode object
    InertialNode node(conn);

    ByteStream bytes;

    //add bytes to the ByteStream
    bytes.append_uint16(0x7565);        //start of packet bytes
    bytes.append_uint16(0x800E);        //descriptor set / payload len
    bytes.append_uint16(0x0E01);        //field length / field descriptor
    bytes.append_uint32(0x3F9DF3B6);    //Accel 1 float
    bytes.append_uint32(0x00000000);    //Accel 2 float
    bytes.append_uint32(0x00000000);    //Accel 3 float
    bytes.append_uint16(bytes.calculateFletcherChecksum(0, 17));

    //add bytes to the ByteStream
    bytes.append_uint16(0x7565);        //start of packet bytes
    bytes.append_uint16(0x800E);        //descriptor set / payload len
    bytes.append_uint16(0x0E01);        //field length / field descriptor
    bytes.append_uint32(0x00000000);    //Accel 1 float
    bytes.append_uint32(0x00000000);    //Accel 2 float
    bytes.append_uint32(0x3F9DF3B6);    //Accel 3 float
    bytes.append_uint16(bytes.calculateFletcherChecksum(20, 37));

    connImpl->setResponseBytes(bytes);

    //force parsing of the bytes we just set
    connImpl->parseNextResponse();

    BOOST_CHECK_EQUAL(node.totalPackets(), 2);
    BOOST_CHECK_EQUAL(node.getDataPackets().at(0).descriptorSet(), 0x80);
}

BOOST_AUTO_TEST_CASE(InertialNode_Ping_Success)
{
    std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
    Connection conn(connImpl);

    //create the InertialNode object
    InertialNode node(conn);
    
    //add bytes to the ByteStream
    ByteStream bytes;
    bytes.append_uint16(0x7565);        //start of packet bytes
    bytes.append_uint16(0x0104);        //descriptor set / payload len
    bytes.append_uint16(0x04F1);        //field length / field descriptor
    bytes.append_uint16(0x0100);        //command echo / error code
    bytes.append_uint16(bytes.calculateFletcherChecksum(0, 7));
    connImpl->setResponseBytes(bytes);

    BOOST_CHECK_EQUAL(node.ping(), true);
}

BOOST_AUTO_TEST_CASE(InertialNode_Ping_FailErrorCode)
{
    std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
    Connection conn(connImpl);

    //create the InertialNode object
    InertialNode node(conn);

    ByteStream bytes;
    bytes.append_uint16(0x7565);        //start of packet bytes
    bytes.append_uint16(0x0104);        //descriptor set / payload len
    bytes.append_uint16(0x04F1);        //field length / field descriptor
    bytes.append_uint16(0x0103);        //command echo / error code
    bytes.append_uint16(bytes.calculateFletcherChecksum(0, 7));
    connImpl->setResponseBytes(bytes);

    BOOST_CHECK_EQUAL(node.ping(), false);
}

BOOST_AUTO_TEST_CASE(InertialNode_Ping_FailTimeout)
{
    std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
    Connection conn(connImpl);

    //create the InertialNode object
    InertialNode node(conn);

    node.timeout(1);

    BOOST_CHECK_EQUAL(node.ping(), false);
}

BOOST_AUTO_TEST_CASE(InertialNode_info)
{
    std::shared_ptr<mock_InertialNodeImpl> impl(new mock_InertialNodeImpl());
    InertialNode node(impl);

    //setup the node info mock expections
    expectNodeInfo_InertialNode(impl);

    //verify the result is good
    BOOST_CHECK_EQUAL(node.firmwareVersion().str(), "1.1.17");
    BOOST_CHECK_EQUAL(node.modelName(), "ABCDABCDABCDABCD");
    BOOST_CHECK_EQUAL(node.modelNumber(), "6251-12345");
    BOOST_CHECK_EQUAL(node.model(), InertialModels::node_3dm_gx5_45);
    BOOST_CHECK_EQUAL(node.serialNumber(), "ABCDABCDABCDABCD");
    BOOST_CHECK_EQUAL(node.lotNumber(), "ABCDABCDABCDABCD");
    BOOST_CHECK_EQUAL(node.deviceOptions(), "ABCDABCDABCDABCD");
}

BOOST_AUTO_TEST_CASE(InertialNode_getDataRateBase_Sensor)
{
    std::shared_ptr<mock_InertialNodeImpl> impl(new mock_InertialNodeImpl());
    InertialNode node(impl);

    ByteStream data;
    data.append_uint16(2000);

    expectNodeInfo_InertialNode(impl);

    //make the doCommand function return the response that we want
    MOCK_EXPECT(impl->doCommand).once().returns(GenericMipCmdResponse::ResponseSuccess("", data));

    //verify that getSensorDataRateBase() returns the correct value
    BOOST_CHECK_EQUAL(node.getDataRateBase(MipTypes::CLASS_AHRS_IMU), 2000);
}

BOOST_AUTO_TEST_CASE(InertialNode_getDataRateBase_Gps)
{
    std::shared_ptr<mock_InertialNodeImpl> impl(new mock_InertialNodeImpl());
    InertialNode node(impl);

    ByteStream data;
    data.append_uint16(100);

    expectNodeInfo_InertialNode(impl);

    //make the doCommand function return the response that we want
    MOCK_EXPECT(impl->doCommand).once().returns(GenericMipCmdResponse::ResponseSuccess("", data));

    //verify that getGpsDataRateBase() returns the correct value
    BOOST_CHECK_EQUAL(node.getDataRateBase(MipTypes::CLASS_GNSS), 100);
}

BOOST_AUTO_TEST_CASE(InertialNode_getDataRateBase_EstFilter)
{
    std::shared_ptr<mock_InertialNodeImpl> impl(new mock_InertialNodeImpl());
    InertialNode node(impl);

    ByteStream data;
    data.append_uint16(4000);

    expectNodeInfo_InertialNode(impl);

    //make the doCommand function return the response that we want
    MOCK_EXPECT(impl->doCommand).once().returns(GenericMipCmdResponse::ResponseSuccess("", data));

    //verify that getEstFilterDataRateBase() returns the correct value
    BOOST_CHECK_EQUAL(node.getDataRateBase(MipTypes::CLASS_ESTFILTER), 4000);
}

BOOST_AUTO_TEST_CASE(InertialNode_getDataRateBase_notSupported_EstFilter)
{
    std::shared_ptr<mock_InertialNodeImpl> impl(new mock_InertialNodeImpl());
    InertialNode node(impl);

    expectNodeInfo_InertialNode(impl);

    //make the doCommand function throw an exception
    MOCK_EXPECT(impl->doCommand).once().throws(Error_NotSupported());

    //verify that getEstFilterDataRateBase() throws an exception
    BOOST_CHECK_THROW(node.getDataRateBase(MipTypes::CLASS_ESTFILTER), Error_NotSupported);
}

BOOST_AUTO_TEST_CASE(InertialNode_getDataRateBase_error_EstFilter)
{
    std::shared_ptr<mock_InertialNodeImpl> impl(new mock_InertialNodeImpl());
    InertialNode node(impl);

    expectNodeInfo_InertialNode(impl);

    //make the doCommand function throw an exception
    MOCK_EXPECT(impl->doCommand).once().throws(Error_MipCmdFailed());
    //MOCK_EXPECT(impl->doCommand).once().returns(GenericMipCmdResponse::ResponseFail(ResponsePattern::STATE_FAIL, MipPacket::MIP_ACK_NACK_ERROR_UNKNOWN_COMMAND, ""));

    //verify that getEstFilterDataRateBase() throws an exception
    BOOST_CHECK_THROW(node.getDataRateBase(MipTypes::CLASS_ESTFILTER), Error_MipCmdFailed);
}

BOOST_AUTO_TEST_CASE(InertialNode_getMessageFormat_Sensor)
{
    std::shared_ptr<mock_InertialNodeImpl> impl(new mock_InertialNodeImpl());
    InertialNode node(impl);

    ByteStream data;
    data.append_uint8(2);
    data.append_uint8(0x0C);    //CH_AHRS_EULER_ANGLES
    data.append_uint16(0x0002);    //rate decimation
    data.append_uint8(0x02);    //CH_AHRS_RAW_GYRO_VEC
    data.append_uint16(0x000A);    //rate decimation

    uint16 sampleRateBase = 1000;

    ByteStream dataRateBase;
    dataRateBase.append_uint16(sampleRateBase);

    expectNodeInfo_InertialNode(impl);

    //expect the getDataRateBase command
    MOCK_EXPECT(impl->doCommand).once().returns(GenericMipCmdResponse::ResponseSuccess("", dataRateBase));

    //expect the getMessageFormat command
    MOCK_EXPECT(impl->doCommand).once().returns(GenericMipCmdResponse::ResponseSuccess("", data));


    MipChannels chs = node.getActiveChannelFields(MipTypes::CLASS_AHRS_IMU);

    //verify that the command returned the correct value
    BOOST_CHECK_EQUAL(chs.size(), 2);
    BOOST_CHECK_EQUAL(chs.at(0).channelField(), MipTypes::CH_FIELD_SENSOR_EULER_ANGLES);
    BOOST_CHECK_EQUAL(chs.at(0).rateDecimation(sampleRateBase), 2);
    BOOST_CHECK_EQUAL(chs.at(0).sampleRate().samplesPerSecond(), SampleRate::Hertz(500).samplesPerSecond());
    BOOST_CHECK_EQUAL(chs.at(0).descriptorSet(), 0x80);
    BOOST_CHECK_EQUAL(chs.at(0).fieldDescriptor(), 0x0C);
    BOOST_CHECK_EQUAL(chs.at(1).channelField(), MipTypes::CH_FIELD_SENSOR_RAW_GYRO_VEC);
    BOOST_CHECK_EQUAL(chs.at(1).rateDecimation(sampleRateBase), 10);
    BOOST_CHECK_EQUAL(chs.at(1).sampleRate().samplesPerSecond(), SampleRate::Hertz(100).samplesPerSecond());
    BOOST_CHECK_EQUAL(chs.at(1).descriptorSet(), 0x80);
    BOOST_CHECK_EQUAL(chs.at(1).fieldDescriptor(), 0x02);
}

BOOST_AUTO_TEST_CASE(InertialNode_getMessageFormat_Gps)
{
    std::shared_ptr<mock_InertialNodeImpl> impl(new mock_InertialNodeImpl());
    InertialNode node(impl);

    ByteStream data;
    data.append_uint8(1);
    data.append_uint8(0x03);    //CH_GPS_LLH_POSITION
    data.append_uint16(2);        //rate decimation

    uint16 sampleRateBase = 4;

    ByteStream dataRateBase;
    dataRateBase.append_uint16(sampleRateBase);

    expectNodeInfo_InertialNode(impl);

    //expect the getDataRateBase command
    MOCK_EXPECT(impl->doCommand).once().returns(GenericMipCmdResponse::ResponseSuccess("", dataRateBase));

    //make the doCommand function return the response that we want
    MOCK_EXPECT(impl->doCommand).once().returns(GenericMipCmdResponse::ResponseSuccess("", data));

    MipChannels chs = node.getActiveChannelFields(MipTypes::CLASS_GNSS);

    //verify that the command returned the correct value
    BOOST_CHECK_EQUAL(chs.size(), 1);
    BOOST_CHECK_EQUAL(chs.at(0).channelField(), MipTypes::CH_FIELD_GNSS_LLH_POSITION);
    BOOST_CHECK_EQUAL(chs.at(0).rateDecimation(sampleRateBase), 2);
    BOOST_CHECK_EQUAL(chs.at(0).sampleRate().samplesPerSecond(), SampleRate::Hertz(2).samplesPerSecond());
    BOOST_CHECK_EQUAL(chs.at(0).descriptorSet(), 0x81);
    BOOST_CHECK_EQUAL(chs.at(0).fieldDescriptor(), 0x03);
}

BOOST_AUTO_TEST_CASE(InertialNode_getMessageFormat_EstFilter)
{
    std::shared_ptr<mock_InertialNodeImpl> impl(new mock_InertialNodeImpl());
    InertialNode node(impl);

    ByteStream data;
    data.append_uint8(1);
    data.append_uint8(0x15);    //CH_NAV_MAGNETIC_MODEL_SLN
    data.append_uint16(1000);    //rate decimation

    uint16 sampleRateBase = 1000;

    ByteStream dataRateBase;
    dataRateBase.append_uint16(sampleRateBase);

    expectNodeInfo_InertialNode(impl);

    //expect the getDataRateBase command
    MOCK_EXPECT(impl->doCommand).once().returns(GenericMipCmdResponse::ResponseSuccess("", dataRateBase));

    //make the doCommand function return the response that we want
    MOCK_EXPECT(impl->doCommand).once().returns(GenericMipCmdResponse::ResponseSuccess("", data));

    MipChannels chs = node.getActiveChannelFields(MipTypes::CLASS_ESTFILTER);

    //verify that the command returned the correct value
    BOOST_CHECK_EQUAL(chs.size(), 1);
    BOOST_CHECK_EQUAL(chs.at(0).channelField(), MipTypes::CH_FIELD_ESTFILTER_MAGNETIC_MODEL_SLN);
    BOOST_CHECK_EQUAL(chs.at(0).rateDecimation(sampleRateBase), 1000);
    BOOST_CHECK_EQUAL(chs.at(0).sampleRate().samplesPerSecond(), SampleRate::Hertz(1).samplesPerSecond());
    BOOST_CHECK_EQUAL(chs.at(0).descriptorSet(), 0x82);
    BOOST_CHECK_EQUAL(chs.at(0).fieldDescriptor(), 0x15);
}

BOOST_AUTO_TEST_CASE(InertialNode_setMessageFormat_Sensor)
{
    std::shared_ptr<mock_InertialNodeImpl> impl(new mock_InertialNodeImpl());
    InertialNode node(impl);

    MipChannels chs;
    chs.push_back(MipChannel(MipTypes::CH_FIELD_SENSOR_EULER_ANGLES, SampleRate::Hertz(20)));
    chs.push_back(MipChannel(MipTypes::CH_FIELD_SENSOR_SCALED_MAG_VEC, SampleRate::Hertz(10)));

    ByteStream dataRateBase;
    dataRateBase.append_uint16(100);

    expectNodeInfo_InertialNode(impl);

    //expect the getDataRateBase command
    MOCK_EXPECT(impl->doCommand).once().returns(GenericMipCmdResponse::ResponseSuccess("", dataRateBase));

    MOCK_EXPECT(impl->doCommand).once().returns(GenericMipCmdResponse::ResponseSuccess(""));

    BOOST_CHECK_NO_THROW(node.setActiveChannelFields(MipTypes::CLASS_AHRS_IMU, chs));
}

BOOST_AUTO_TEST_CASE(InertialNode_setMessageFormat_InvalidChannels_Sensor)
{
    std::shared_ptr<mock_InertialNodeImpl> impl(new mock_InertialNodeImpl());
    InertialNode node(impl);

    MipChannels chs;
    chs.push_back(MipChannel(MipTypes::CH_FIELD_SENSOR_EULER_ANGLES, SampleRate::Hertz(10)));
    chs.push_back(MipChannel(MipTypes::CH_FIELD_GNSS_ECEF_VELOCITY, SampleRate::Hertz(20)));    //not a Sensor channel

    ByteStream dataRateBase;
    dataRateBase.append_uint16(100);

    expectNodeInfo_InertialNode(impl);

    //expect the getDataRateBase command
    MOCK_EXPECT(impl->doCommand).once().returns(GenericMipCmdResponse::ResponseSuccess("", dataRateBase));

    BOOST_CHECK_THROW(node.setActiveChannelFields(MipTypes::CLASS_AHRS_IMU, chs), Error);
}

BOOST_AUTO_TEST_CASE(InertialNode_setMessageFormat_Gps)
{
    std::shared_ptr<mock_InertialNodeImpl> impl(new mock_InertialNodeImpl());
    InertialNode node(impl);

    MipChannels chs;
    chs.push_back(MipChannel(MipTypes::CH_FIELD_GNSS_GPS_TIME, SampleRate::Hertz(10)));
    chs.push_back(MipChannel(MipTypes::CH_FIELD_GNSS_UTC_TIME, SampleRate::Hertz(20)));

    ByteStream dataRateBase;
    dataRateBase.append_uint16(100);

    expectNodeInfo_InertialNode(impl);

    //expect the getDataRateBase command
    MOCK_EXPECT(impl->doCommand).once().returns(GenericMipCmdResponse::ResponseSuccess("", dataRateBase));

    MOCK_EXPECT(impl->doCommand).once().returns(GenericMipCmdResponse::ResponseSuccess(""));

    BOOST_CHECK_NO_THROW(node.setActiveChannelFields(MipTypes::CLASS_GNSS, chs));
}

BOOST_AUTO_TEST_CASE(InertialNode_setMessageFormat_InvalidChannels_Gps)
{
    std::shared_ptr<mock_InertialNodeImpl> impl(new mock_InertialNodeImpl());
    InertialNode node(impl);

    MipChannels chs;
    chs.push_back(MipChannel(MipTypes::CH_FIELD_GNSS_GPS_TIME, SampleRate::Hertz(10)));
    chs.push_back(MipChannel(MipTypes::CH_FIELD_SENSOR_EULER_ANGLES, SampleRate::Hertz(20)));    //not a gps channel

    ByteStream dataRateBase;
    dataRateBase.append_uint16(100);

    expectNodeInfo_InertialNode(impl);

    //expect the getDataRateBase command
    MOCK_EXPECT(impl->doCommand).once().returns(GenericMipCmdResponse::ResponseSuccess("", dataRateBase));

    BOOST_CHECK_THROW(node.setActiveChannelFields(MipTypes::CLASS_GNSS, chs), Error);
}

BOOST_AUTO_TEST_CASE(InertialNode_setMessageFormat_EstFilter)
{
    std::shared_ptr<mock_InertialNodeImpl> impl(new mock_InertialNodeImpl());
    InertialNode node(impl);

    MipChannels chs;
    chs.push_back(MipChannel(MipTypes::CH_FIELD_ESTFILTER_FILTER_STATUS, SampleRate::Hertz(10)));

    ByteStream dataRateBase;
    dataRateBase.append_uint16(100);

    expectNodeInfo_InertialNode(impl);

    //expect the getDataRateBase command
    MOCK_EXPECT(impl->doCommand).once().returns(GenericMipCmdResponse::ResponseSuccess("", dataRateBase));

    MOCK_EXPECT(impl->doCommand).once().returns(GenericMipCmdResponse::ResponseSuccess(""));

    BOOST_CHECK_NO_THROW(node.setActiveChannelFields(MipTypes::CLASS_ESTFILTER, chs));
}

BOOST_AUTO_TEST_CASE(InertialNode_setMessageFormat_InvalidChannels_EstFilter)
{
    std::shared_ptr<mock_InertialNodeImpl> impl(new mock_InertialNodeImpl());
    InertialNode node(impl);

    MipChannels chs;
    chs.push_back(MipChannel(MipTypes::CH_FIELD_SENSOR_DELTA_THETA_VEC, SampleRate::Hertz(10)));    //not an est filter channel

    ByteStream dataRateBase;
    dataRateBase.append_uint16(100);

    expectNodeInfo_InertialNode(impl);

    //expect the getDataRateBase command
    MOCK_EXPECT(impl->doCommand).once().returns(GenericMipCmdResponse::ResponseSuccess("", dataRateBase));

    BOOST_CHECK_THROW(node.setActiveChannelFields(MipTypes::CLASS_ESTFILTER, chs), Error);
}

BOOST_AUTO_TEST_CASE(InertialNode_supportedSampleRates_1000)
{
    std::shared_ptr<mock_InertialNodeImpl> impl(new mock_InertialNodeImpl());
    InertialNode node(impl);

    ByteStream dataRateBase;
    dataRateBase.append_uint16(1000);

    //setup the node info mock expections
    expectNodeInfo_InertialNode(impl);

    //expect the getDataRateBase command
    MOCK_EXPECT(impl->doCommand).once().returns(GenericMipCmdResponse::ResponseSuccess("", dataRateBase));

    SampleRates rates_1000 = node.features().supportedSampleRates(MipTypes::CLASS_ESTFILTER);

    BOOST_CHECK_EQUAL(rates_1000.size(), 16);
    BOOST_CHECK(rates_1000.at(0) == SampleRate::Hertz(1));
    BOOST_CHECK(rates_1000.at(1) == SampleRate::Hertz(2));
    BOOST_CHECK(rates_1000.at(2) == SampleRate::Hertz(4));
    BOOST_CHECK(rates_1000.at(3) == SampleRate::Hertz(5));
    BOOST_CHECK(rates_1000.at(4) == SampleRate::Hertz(8));
    BOOST_CHECK(rates_1000.at(5) == SampleRate::Hertz(10));
    BOOST_CHECK(rates_1000.at(6) == SampleRate::Hertz(20));
    BOOST_CHECK(rates_1000.at(7) == SampleRate::Hertz(25));
    BOOST_CHECK(rates_1000.at(8) == SampleRate::Hertz(40));
    BOOST_CHECK(rates_1000.at(9) == SampleRate::Hertz(50));
    BOOST_CHECK(rates_1000.at(10) == SampleRate::Hertz(100));
    BOOST_CHECK(rates_1000.at(11) == SampleRate::Hertz(125));
    BOOST_CHECK(rates_1000.at(12) == SampleRate::Hertz(200));
    BOOST_CHECK(rates_1000.at(13) == SampleRate::Hertz(250));
    BOOST_CHECK(rates_1000.at(14) == SampleRate::Hertz(500));
    BOOST_CHECK(rates_1000.at(15) == SampleRate::Hertz(1000));
}

BOOST_AUTO_TEST_CASE(InertialNode_supportedSampleRates_4)
{
    std::shared_ptr<mock_InertialNodeImpl> impl(new mock_InertialNodeImpl());
    InertialNode node(impl);

    ByteStream dataRateBase;
    dataRateBase.append_uint16(4);

    //setup the node info mock expectations
    expectNodeInfo_InertialNode(impl);

    //expect the getDataRateBase command
    MOCK_EXPECT(impl->doCommand).once().returns(GenericMipCmdResponse::ResponseSuccess("", dataRateBase));

    SampleRates rates_4 = node.features().supportedSampleRates(MipTypes::CLASS_ESTFILTER);

    BOOST_CHECK_EQUAL(rates_4.size(), 3);
    BOOST_CHECK(rates_4.at(0) == SampleRate::Hertz(1));
    BOOST_CHECK(rates_4.at(1) == SampleRate::Hertz(2));
    BOOST_CHECK(rates_4.at(2) == SampleRate::Hertz(4));
}

BOOST_AUTO_TEST_CASE(InertialNode_enableDataStream_success)
{
    std::shared_ptr<mock_InertialNodeImpl> impl(new mock_InertialNodeImpl());
    InertialNode node(impl);

    ByteStream data;

    //setup the node info mock expectations
    expectNodeInfo_InertialNode(impl);

    //expect a success response
    MOCK_EXPECT(impl->doCommand).once().returns(GenericMipCmdResponse::ResponseSuccess("", data));

    BOOST_CHECK_NO_THROW(node.enableDataStream(MipTypes::CLASS_GNSS));
}

BOOST_AUTO_TEST_CASE(InertialNode_enableDataStream_fail)
{
    std::shared_ptr<mock_InertialNodeImpl> impl(new mock_InertialNodeImpl());
    InertialNode node(impl);

    ByteStream data;

    //setup the node info mock expectations
    expectNodeInfo_InertialNode(impl);

    //expect a fail response
    MOCK_EXPECT(impl->doCommand).once().throws(Error_MipCmdFailed());

    BOOST_CHECK_THROW(node.enableDataStream(MipTypes::CLASS_GNSS), Error_MipCmdFailed);
}

BOOST_AUTO_TEST_CASE(InertialNode_setToIdle_success)
{
    std::shared_ptr<mock_InertialNodeImpl> impl(new mock_InertialNodeImpl());
    InertialNode node(impl);

    ByteStream data;

    //expect a success response
    MOCK_EXPECT(impl->doCommand).once().returns(GenericMipCmdResponse::ResponseSuccess("", data));

    BOOST_CHECK_NO_THROW(node.setToIdle());
}

BOOST_AUTO_TEST_CASE(InertialNode_setToIdle_fail)
{
    std::shared_ptr<mock_InertialNodeImpl> impl(new mock_InertialNodeImpl());
    InertialNode node(impl);

    ByteStream data;

    //expect a fail response
    MOCK_EXPECT(impl->doCommand).once().throws(Error_MipCmdFailed());

    BOOST_CHECK_THROW(node.setToIdle(), Error_MipCmdFailed);
}

BOOST_AUTO_TEST_CASE(InertialNode_deviceName)
{
    std::string serial = "6225.01466";

    BOOST_CHECK_EQUAL(InertialNode::deviceName(serial), "inertial-6225.01466");
}


//TODO: move this to displacement test area
BOOST_AUTO_TEST_CASE(DisplacementNode_nodeFromModelString)
{
    BOOST_CHECK_EQUAL(DisplacementModels::nodeFromModelString("6130-2000"), DisplacementModels::node_digitalDemod);
}


BOOST_AUTO_TEST_SUITE_END()