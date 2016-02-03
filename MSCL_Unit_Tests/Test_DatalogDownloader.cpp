/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Wireless/DatalogDownloader.h"

#include <boost/test/unit_test.hpp>
#include "mock_BaseStation.h"
#include "mock_WirelessNode.h"
using namespace mscl;

BOOST_AUTO_TEST_SUITE(DatalogDownloader_Test)

BOOST_AUTO_TEST_CASE(DatalogDownloader_complete_noData)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(1, b);
    node.setImpl(impl);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);

    uint16 page = 0, offset = 0;
    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::CURRENT_LOG_PAGE).returns(Value::UINT16(page));//log page
    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::CURRENT_PAGE_OFFSET).returns(Value::UINT16(offset));//page offset

    DatalogDownloader dl(node);

    BOOST_CHECK_EQUAL(dl.complete(), true);
    BOOST_CHECK_THROW(dl.getNextData(), Error_NoData);
}

BOOST_AUTO_TEST_CASE(DatalogDownloader_getNextData_v1_0)
{
    std::shared_ptr<mock_baseStationImpl> baseImpl(new mock_baseStationImpl);
    BaseStation b(baseImpl);

    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(b));
    WirelessNode node(1, b);
    node.setImpl(impl);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);

    uint16 page = 0, offset = 44;
    MOCK_EXPECT(impl->firmwareVersion).returns(Version(8, 0));
    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::CURRENT_LOG_PAGE).returns(Value::UINT16(page));//log page
    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::CURRENT_PAGE_OFFSET).returns(Value::UINT16(offset));//page offset

    DatalogDownloader dl(node);

    BOOST_CHECK_EQUAL(dl.complete(), false);

    ByteStream data;
    data.append_uint16(0xFFFF);
    data.append_uint8(0xFD);    //header id
    data.append_uint8(0x00);    //trigger id
    data.append_uint8(0x01);    //header version major
    data.append_uint8(0x00);    //header version minor
    data.append_uint16(0x0A);    //# of bytes before channel data
    data.append_uint16(500);    //samples per data set 
    data.append_uint16(0x01);    //session index
    data.append_uint16(0x01);    //channel mask
    data.append_uint16(WirelessTypes::sampleRate_32Hz);    //sample rate
    data.append_uint16(0x00);    //# of user bytes
    data.append_uint16(0x0A);    //# of bytes per channel
    data.append_uint8(0x04);    //equation id
    data.append_uint8(0x06);    //unit id
    data.append_float(2.5f);    //slope
    data.append_float(0.1234f);    //offset
    data.append_uint16(0x08);    //# of bytes before end of header
    data.append_uint32(0);        //timestamp (seconds)
    data.append_uint32(0);        //timestamp (nanoseconds)

    data.append_uint16(583);    //data
    data.append_uint16(9212);    //data

    //force the page download to take our bytestream
    MOCK_EXPECT(baseImpl->node_pageDownload).once().with(mock::any, mock::any, mock::any, mock::assign(data)).returns(true);

    LoggedDataSweep sweep = dl.getNextData();

    BOOST_CHECK(dl.sampleRate() == SampleRate::Hertz(32));
    BOOST_CHECK_EQUAL(dl.sessionIndex(), 1);
    BOOST_CHECK_EQUAL(dl.startOfSession(), true);
    BOOST_CHECK_EQUAL(dl.totalSweeps(), 500);
    BOOST_CHECK_EQUAL(dl.triggerType(), WirelessTypes::trigger_userInit);
    BOOST_CHECK_EQUAL(dl.userString(), "");

    BOOST_CHECK_EQUAL(sweep.timestamp().nanoseconds(), 0);
    BOOST_CHECK_EQUAL(sweep.tick(), 0);
    BOOST_CHECK_EQUAL(sweep.data().size(), 1);
    BOOST_CHECK_EQUAL(sweep.data().at(0).storedAs(), valueType_uint16);
    BOOST_CHECK_EQUAL(sweep.data().at(0).as_int16(), 583);

    sweep = dl.getNextData();

    BOOST_CHECK_EQUAL(dl.startOfSession(), false);
    BOOST_CHECK_EQUAL(sweep.timestamp().nanoseconds(), 31250000);
    BOOST_CHECK_EQUAL(sweep.tick(), 1);
    BOOST_CHECK_EQUAL(sweep.data().size(), 1);
    BOOST_CHECK_EQUAL(sweep.data().at(0).storedAs(), valueType_uint16);
    BOOST_CHECK_EQUAL(sweep.data().at(0).as_int16(), 9212);

    BOOST_CHECK_EQUAL(dl.complete(), true);
    BOOST_CHECK_THROW(dl.getNextData(), Error_NoData);
}

BOOST_AUTO_TEST_CASE(DatalogDownloader_getNextData_v2_0)
{
    std::shared_ptr<mock_baseStationImpl> baseImpl(new mock_baseStationImpl);
    BaseStation b(baseImpl);

    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(b));
    WirelessNode node(1, b);
    node.setImpl(impl);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);

    uint16 page = 0, offset = 46;
    MOCK_EXPECT(impl->firmwareVersion).returns(Version(8, 0));
    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::CURRENT_LOG_PAGE).returns(Value::UINT16(page));//log page
    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::CURRENT_PAGE_OFFSET).returns(Value::UINT16(offset));//page offset

    DatalogDownloader dl(node);

    BOOST_CHECK_EQUAL(dl.complete(), false);

    ByteStream data;
    data.append_uint16(0xFFFF);
    data.append_uint8(0xFD);    //header id
    data.append_uint8(0x00);    //trigger id
    data.append_uint8(0x02);    //header version major
    data.append_uint8(0x00);    //header version minor
    data.append_uint16(0x0C);    //# of bytes before channel data
    data.append_uint16(500);    //samples per data set 
    data.append_uint16(0x01);    //session index
    data.append_uint16(0x01);    //channel mask
    data.append_uint16(WirelessTypes::sampleRate_32Hz);    //sample rate
    data.append_uint8(0x01);    //data type
    data.append_uint8(0x00);    //unused byte
    data.append_uint16(0x00);    //# of user bytes
    data.append_uint16(0x0A);    //# of bytes per channel
    data.append_uint8(0x04);    //equation id
    data.append_uint8(0x06);    //unit id
    data.append_float(2.5f);    //slope
    data.append_float(0.1234f);    //offset
    data.append_uint16(0x08);    //# of bytes before end of header
    data.append_uint32(0);        //timestamp (seconds)
    data.append_uint32(0);        //timestamp (nanoseconds)

    data.append_uint16(583);    //data
    data.append_uint16(9212);    //data

    //force the page download to take our bytestream
    MOCK_EXPECT(baseImpl->node_pageDownload).once().with(mock::any, mock::any, mock::any, mock::assign(data)).returns(true);

    LoggedDataSweep sweep = dl.getNextData();

    BOOST_CHECK(dl.sampleRate() == SampleRate::Hertz(32));
    BOOST_CHECK_EQUAL(dl.sessionIndex(), 1);
    BOOST_CHECK_EQUAL(dl.startOfSession(), true);
    BOOST_CHECK_EQUAL(dl.totalSweeps(), 500);
    BOOST_CHECK_EQUAL(dl.triggerType(), WirelessTypes::trigger_userInit);
    BOOST_CHECK_EQUAL(dl.userString(), "");

    BOOST_CHECK_EQUAL(sweep.timestamp().nanoseconds(), 0);
    BOOST_CHECK_EQUAL(sweep.tick(), 0);
    BOOST_CHECK_EQUAL(sweep.data().size(), 1);
    BOOST_CHECK_EQUAL(sweep.data().at(0).storedAs(), valueType_uint16);
    BOOST_CHECK_EQUAL(sweep.data().at(0).as_int16(), 583);

    sweep = dl.getNextData();

    BOOST_CHECK_EQUAL(dl.startOfSession(), false);
    BOOST_CHECK_EQUAL(sweep.timestamp().nanoseconds(), 31250000);
    BOOST_CHECK_EQUAL(sweep.tick(), 1);
    BOOST_CHECK_EQUAL(sweep.data().size(), 1);
    BOOST_CHECK_EQUAL(sweep.data().at(0).storedAs(), valueType_uint16);
    BOOST_CHECK_EQUAL(sweep.data().at(0).as_int16(), 9212);

    BOOST_CHECK_EQUAL(dl.complete(), true);
    BOOST_CHECK_THROW(dl.getNextData(), Error_NoData);
}

BOOST_AUTO_TEST_CASE(DatalogDownloader_getNextData_v2_1)
{
    std::shared_ptr<mock_baseStationImpl> baseImpl(new mock_baseStationImpl);
    BaseStation b(baseImpl);

    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(b));
    WirelessNode node(1, b);
    node.setImpl(impl);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);

    uint16 page = 0, offset = 46;
    MOCK_EXPECT(impl->firmwareVersion).returns(Version(8, 0));
    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::CURRENT_LOG_PAGE).returns(Value::UINT16(page));//log page
    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::CURRENT_PAGE_OFFSET).returns(Value::UINT16(offset));//page offset

    DatalogDownloader dl(node);

    BOOST_CHECK_EQUAL(dl.complete(), false);

    ByteStream data;
    data.append_uint16(0xFFFF);
    data.append_uint8(0xFD);    //header id
    data.append_uint8(0x00);    //trigger id
    data.append_uint8(0x02);    //header version major
    data.append_uint8(0x01);    //header version minor
    data.append_uint16(0x0C);    //# of bytes before channel data
    data.append_uint16(500);    //samples per data set 
    data.append_uint16(0x01);    //session index
    data.append_uint16(0x01);    //channel mask
    data.append_uint16(WirelessTypes::sampleRate_32Hz);    //sample rate
    data.append_uint8(0x01);    //data type
    data.append_uint8(0x00);    //unused byte
    data.append_uint16(0x00);    //# of user bytes
    data.append_uint16(0x0A);    //# of bytes per channel
    data.append_uint8(0x04);    //equation id
    data.append_uint8(0x06);    //unit id
    data.append_float(2.5f);    //slope
    data.append_float(0.1234f);    //offset
    data.append_uint16(0x08);    //# of bytes before end of header
    data.append_uint32(0);        //timestamp (seconds)
    data.append_uint32(0);        //timestamp (nanoseconds)

    data.append_uint16(583);    //data
    data.append_uint16(9212);    //data

    //force the page download to take our bytestream
    MOCK_EXPECT(baseImpl->node_pageDownload).once().with(mock::any, mock::any, mock::any, mock::assign(data)).returns(true);

    LoggedDataSweep sweep = dl.getNextData();

    BOOST_CHECK(dl.sampleRate() == SampleRate::Hertz(32));
    BOOST_CHECK_EQUAL(dl.sessionIndex(), 1);
    BOOST_CHECK_EQUAL(dl.startOfSession(), true);
    BOOST_CHECK_EQUAL(dl.totalSweeps(), 50000);
    BOOST_CHECK_EQUAL(dl.triggerType(), WirelessTypes::trigger_userInit);
    BOOST_CHECK_EQUAL(dl.userString(), "");

    BOOST_CHECK_EQUAL(sweep.timestamp().nanoseconds(), 0);
    BOOST_CHECK_EQUAL(sweep.tick(), 0);
    BOOST_CHECK_EQUAL(sweep.data().size(), 1);
    BOOST_CHECK_EQUAL(sweep.data().at(0).storedAs(), valueType_uint16);
    BOOST_CHECK_EQUAL(sweep.data().at(0).as_int16(), 583);

    sweep = dl.getNextData();

    BOOST_CHECK_EQUAL(dl.startOfSession(), false);
    BOOST_CHECK_EQUAL(sweep.timestamp().nanoseconds(), 31250000);
    BOOST_CHECK_EQUAL(sweep.tick(), 1);
    BOOST_CHECK_EQUAL(sweep.data().size(), 1);
    BOOST_CHECK_EQUAL(sweep.data().at(0).storedAs(), valueType_uint16);
    BOOST_CHECK_EQUAL(sweep.data().at(0).as_int16(), 9212);

    BOOST_CHECK_EQUAL(dl.complete(), true);
    BOOST_CHECK_THROW(dl.getNextData(), Error_NoData);
}

BOOST_AUTO_TEST_SUITE_END()