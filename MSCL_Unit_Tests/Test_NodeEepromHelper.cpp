/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Wireless/WirelessNode.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromHelper.h"
#include "mscl/MicroStrain/Wireless/Features/NodeInfo.h"
#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"
#include "mscl/MicroStrain/Wireless/Configuration/WirelessNodeConfig.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"

#include <boost/test/unit_test.hpp>
#include "mock_WirelessNode.h"
using namespace mscl;


BOOST_AUTO_TEST_SUITE(NodeEepromHelper_Test)


BOOST_AUTO_TEST_CASE(NodeEepromHelper_writeChannelMask)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    ChannelMask chMask;
    chMask.enable(1, true);
    chMask.enable(3, true);
    chMask.enable(4, true);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);

    MOCK_EXPECT(impl->writeEeprom).with(NodeEepromMap::ACTIVE_CHANNEL_MASK, mock::any);//13);

    NodeEepromHelper eeprom = node.eepromHelper();
    BOOST_CHECK_NO_THROW(eeprom.write_channelMask(chMask));
}

BOOST_AUTO_TEST_CASE(NodeEepromHelper_readChannelMask)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    ChannelMask chMask;
    chMask.enable(1, true);
    chMask.enable(3, true);
    chMask.enable(4, true);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);

    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::ACTIVE_CHANNEL_MASK).returns(Value(valueType_uint16, static_cast<uint16>(13)));

    ChannelMask result = node.eepromHelper().read_channelMask();

    BOOST_CHECK_EQUAL(result.toMask(), chMask.toMask());
}

BOOST_AUTO_TEST_CASE(NodeEepromHelper_writeNumSweeps)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    NodeInfo info(Version(9, 9), WirelessModels::node_gLink_2g, 200000, WirelessTypes::region_usa);

    //make the features() function return the NodeFeatures we want
    std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
    MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));
    

    MOCK_EXPECT(impl->writeEeprom).with(NodeEepromMap::NUM_SWEEPS, Value(valueType_uint16, static_cast<uint16>(979)));

    uint32 sweeps = features->normalizeNumSweeps(97845);

    BOOST_CHECK_NO_THROW(node.eepromHelper().write_numSweeps(sweeps));
}

BOOST_AUTO_TEST_CASE(NodeEepromHelper_readNumSweeps)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);
    
    uint16 val = 979;

    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::NUM_SWEEPS).returns(Value(valueType_uint16, val));

    BOOST_CHECK_EQUAL(node.eepromHelper().read_numSweeps(), 97900);
}

BOOST_AUTO_TEST_CASE(NodeEepromHelper_writeUnlimitedDuration)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);
    
    uint16 val = 1;
    MOCK_EXPECT(impl->writeEeprom).with(NodeEepromMap::UNLIMITED_SAMPLING, Value(valueType_uint16, val));

    BOOST_CHECK_NO_THROW(node.eepromHelper().write_unlimitedDuration(true, WirelessTypes::samplingMode_sync));
}

BOOST_AUTO_TEST_CASE(NodeEepromHelper_writeUnlimitedDuration_datalogging)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);
    
    uint16 val = 0;
    MOCK_EXPECT(impl->writeEeprom).with(NodeEepromMap::UNLIMITED_DATALOG, Value(valueType_uint16, val));

    BOOST_CHECK_NO_THROW(node.eepromHelper().write_unlimitedDuration(false, WirelessTypes::samplingMode_armedDatalog));
}

BOOST_AUTO_TEST_CASE(NodeEepromHelper_readUnlimitedDuration)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);
    
    uint16 val = 1;
    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::UNLIMITED_SAMPLING).returns(Value::UINT16(val));

    BOOST_CHECK_EQUAL(node.eepromHelper().read_unlimitedDuration(WirelessTypes::samplingMode_sync), true);
}

BOOST_AUTO_TEST_CASE(NodeEepromHelper_readUnlimitedDuration_datalogging)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);
    
    uint16 val = 0;
    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::UNLIMITED_DATALOG).returns(Value::UINT16(val));

    BOOST_CHECK_EQUAL(node.eepromHelper().read_unlimitedDuration(WirelessTypes::samplingMode_armedDatalog), false);
}

BOOST_AUTO_TEST_CASE(NodeEepromHelper_writeSampleRate)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);
    
    uint16 rate1 = 104, rate2 = 75;
    expectWrite(impl, NodeEepromMap::SAMPLE_RATE, Value::UINT16(rate1));
    expectWrite(impl, NodeEepromMap::DATALOG_SAMPLE_RATE, Value::UINT16(rate2));

    NodeEepromHelper eeprom(node.eepromHelper());
    BOOST_CHECK_NO_THROW(eeprom.write_sampleRate(WirelessTypes::sampleRate_512Hz, WirelessTypes::samplingMode_sync));
    BOOST_CHECK_NO_THROW(eeprom.write_sampleRate(WirelessTypes::sampleRate_50kHz, WirelessTypes::samplingMode_armedDatalog));
}

BOOST_AUTO_TEST_CASE(NodeEepromHelper_readSampleRate)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);
    
    uint16 rate1 = 123, rate2 = 114;
    expectRead(impl, NodeEepromMap::SAMPLE_RATE, Value::UINT16(rate1));
    expectRead(impl, NodeEepromMap::DATALOG_SAMPLE_RATE, Value::UINT16(rate2));

    NodeEepromHelper eeprom(node.eepromHelper());

    BOOST_CHECK_EQUAL(eeprom.read_sampleRate(WirelessTypes::samplingMode_sync), WirelessTypes::sampleRate_60Min);
    BOOST_CHECK_EQUAL(eeprom.read_sampleRate(WirelessTypes::samplingMode_armedDatalog), WirelessTypes::sampleRate_2Sec);
}

BOOST_AUTO_TEST_CASE(NodeEepromHelper_writeDataFormat)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);
    
    expectWrite(impl, NodeEepromMap::DATA_FORMAT, Value::UINT16(static_cast<uint16>(2)));

    BOOST_CHECK_NO_THROW(node.eepromHelper().write_dataFormat(WirelessTypes::dataFormat_cal_float));
}

BOOST_AUTO_TEST_CASE(NodeEepromHelper_readDataFormat)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);
    
    uint16 val = 1;
    expectRead(impl, NodeEepromMap::DATA_FORMAT, Value::UINT16(val));

    BOOST_CHECK_EQUAL(node.eepromHelper().read_dataFormat(), WirelessTypes::dataFormat_raw_uint16);
}

BOOST_AUTO_TEST_CASE(NodeEepromHelper_writeCollectionMode)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);
    
    uint16 val = 2;
    expectWrite(impl, NodeEepromMap::COLLECTION_MODE, Value::UINT16(val));

    BOOST_CHECK_NO_THROW(node.eepromHelper().write_collectionMode(WirelessTypes::collectionMethod_transmitOnly));
}

BOOST_AUTO_TEST_CASE(NodeEepromHelper_readCollectionMode)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);
    
    uint16 val = 3;
    expectRead(impl, NodeEepromMap::COLLECTION_MODE, Value::UINT16(val));

    BOOST_CHECK_EQUAL(node.eepromHelper().read_collectionMode(), WirelessTypes::collectionMethod_logAndTransmit);
}

BOOST_AUTO_TEST_CASE(NodeEepromHelper_convertFromDataloggingRate)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);
    
    uint16 val = 2;
    expectRead(impl, NodeEepromMap::DATALOG_SAMPLE_RATE, Value::UINT16(val));

    //test that the datalogging sample rate was converted to a real value
    BOOST_CHECK_EQUAL(node.eepromHelper().read_sampleRate(WirelessTypes::samplingMode_armedDatalog), WirelessTypes::sampleRate_1024Hz);
}

BOOST_AUTO_TEST_CASE(NodeEepromHelper_convertToDataloggingRate)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);
    
    uint16 val = 3;
    expectWrite(impl, NodeEepromMap::DATALOG_SAMPLE_RATE, Value::UINT16(val));

    BOOST_CHECK_NO_THROW(node.eepromHelper().write_sampleRate(WirelessTypes::sampleRate_512Hz, WirelessTypes::samplingMode_armedDatalog));
}

BOOST_AUTO_TEST_CASE(NodeEepromHelper_getChannelCalCoefficients)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);
    
    //reading channel 1
    expectRead(impl, NodeEepromMap::CH_ACTION_SLOPE_1, Value::FLOAT(12.789f));                        //slope
    expectRead(impl, NodeEepromMap::CH_ACTION_OFFSET_1, Value::FLOAT(-48.001f));                    //offset
    expectRead(impl, NodeEepromMap::CH_ACTION_ID_1, Value::UINT16(static_cast<uint16>(0x0407)));    //equation and unit

    NodeEepromHelper c(node.eepromHelper());

    LinearEquation eq;
    c.read_channelLinearEquation(ChannelMask(1), eq);

    BOOST_CHECK_CLOSE(eq.slope(), 12.789, 0.1);
    BOOST_CHECK_CLOSE(eq.offset(), -48.001, 0.1);
    BOOST_CHECK_EQUAL(c.read_channelUnit(ChannelMask(1)), WirelessTypes::unit_volts_millivolts);
    BOOST_CHECK_EQUAL(c.read_channelEquation(ChannelMask(1)), WirelessTypes::equation_standard);
}

BOOST_AUTO_TEST_CASE(NodeEepromHelper_setChannelCalCoefficients)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);
    

    //we expect the following values to get written
    expectWrite(impl, NodeEepromMap::CH_ACTION_SLOPE_3, Value::FLOAT(2.345f));        //slope
    expectWrite(impl, NodeEepromMap::CH_ACTION_OFFSET_3, Value::FLOAT(0.0005f));    //offset
    expectWrite(impl, NodeEepromMap::CH_ACTION_ID_3, Value::UINT16(static_cast<uint16>(0x0401)));    //unit and equation
    expectRead(impl, NodeEepromMap::CH_ACTION_ID_3, Value::UINT16(static_cast<uint16>(0x0401)));

    NodeEepromHelper c = (node.eepromHelper());

    LinearEquation eq(2.345f, 0.0005f);

    BOOST_CHECK_NO_THROW(c.write_channelLinearEquation(ChannelMask(4), eq));
    BOOST_CHECK_NO_THROW(c.write_channelUnit(ChannelMask(4), WirelessTypes::unit_other_bits));
    BOOST_CHECK_NO_THROW(c.write_channelEquation(ChannelMask(4), WirelessTypes::equation_standard));
}

BOOST_AUTO_TEST_CASE(NodeEepromHelper_getNumDatalogSessions)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);
    

    NodeEepromHelper c(node.eepromHelper());

    expectRead(impl, NodeEepromMap::DATA_SETS_STORED, Value::UINT16(static_cast<uint16>(12)));

    BOOST_CHECK_EQUAL(c.read_numDatalogSessions(), 12);
}

BOOST_AUTO_TEST_SUITE_END()