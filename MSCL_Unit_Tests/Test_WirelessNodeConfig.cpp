/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Wireless/Configuration/DataModeMask.h"
#include "mscl/MicroStrain/Wireless/Configuration/WirelessNodeConfig.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"
#include "mscl/MicroStrain/Wireless/WirelessNode.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>
#include "mock_WirelessNode.h"
using namespace mscl;

BOOST_AUTO_TEST_SUITE(WirelessNodeConfig_Test)

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_Constructor)
{
    //Tests that a blank WirelessNodeConfig throws exceptions when trying to access any options

    WirelessNodeConfig c;

    //verify that a blank config throws exceptions (nothing has been set)
    BOOST_CHECK_THROW(c.activeChannels(), Error_NoData);
    BOOST_CHECK_THROW(c.numSweeps(), Error_NoData);
    BOOST_CHECK_THROW(c.timeBetweenBursts(), Error_NoData);
    BOOST_CHECK_THROW(c.inactivityTimeout(), Error_NoData);
    BOOST_CHECK_THROW(c.unit(ChannelMask(1)), Error_NoData);
    BOOST_CHECK_THROW(c.unit(ChannelMask(5)), Error_NoData);
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_SetAndGet)
{
    //Tests that setting an option in the WirelessNodeConfig allows that option to then be retrieved

    WirelessNodeConfig c;

    //set and get boot mode
    c.defaultMode(WirelessTypes::defaultMode_sleep);
    BOOST_CHECK_EQUAL(c.defaultMode(), WirelessTypes::defaultMode_sleep);

    //set and get sample rate
    c.sampleRate(WirelessTypes::sampleRate_5Min);
    BOOST_CHECK_EQUAL(c.sampleRate(), WirelessTypes::sampleRate_5Min);

    //set and get unlimited duration
    c.unlimitedDuration(true);
    BOOST_CHECK_EQUAL(c.unlimitedDuration(), true);
    c.unlimitedDuration(false);
    BOOST_CHECK_EQUAL(c.unlimitedDuration(), false);

    //set and get linear equation
    LinearEquation eq(1.234f, 84531.0f);
    c.linearEquation(ChannelMask(1), eq);
    BOOST_CHECK_CLOSE(c.linearEquation(ChannelMask(1)).slope(), 1.234, 0.001);
    BOOST_CHECK_THROW(c.linearEquation(ChannelMask(3)), Error_NoData);
    c.linearEquation(ChannelMask(3), eq);
    BOOST_CHECK_CLOSE(c.linearEquation(ChannelMask(3)).slope(), 1.234, 0.001);
    BOOST_CHECK_CLOSE(c.linearEquation(ChannelMask(3)).offset(), 84531.0, 0.001);
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_setSingleValue)
{
    //Tests setting a single value in the config and writing it to a Node

    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    MOCK_EXPECT(impl->protocol).returns(*(WirelessProtocol::v1_5().get()));

    //make the features() function return the NodeFeatures we want
    NodeInfo info(Version(9, 9), WirelessModels::node_gLink_2g, WirelessTypes::region_usa);
    std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
    MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

    WirelessNodeConfig c;
    c.inactivityTimeout(4500);

    //expect the single eeprom write
    expectWrite(impl, NodeEepromMap::INACTIVE_TIMEOUT, Value::UINT16(4500));
    MOCK_EXPECT(impl->cyclePower);

    BOOST_CHECK_NO_THROW(node.applyConfig(c));
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_setMultipleValues)
{
    //Tests setting multiple values in the config and writing them to a Node

    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    MOCK_EXPECT(impl->protocol).returns(*(WirelessProtocol::v1_5().get()));

    //make the features() function return the NodeFeatures we want
    NodeInfo info(Version(99, 9), WirelessModels::node_gLink_2g, WirelessTypes::region_usa);
    std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
    MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

    WirelessNodeConfig c;
    c.inactivityTimeout(200);
    c.transmitPower(WirelessTypes::power_16dBm);

    //expect the eeprom writes
    expectRead(impl, NodeEepromMap::FIRMWARE_VER, Value(valueType_uint16, (uint16)10));
    expectRead(impl, NodeEepromMap::COMM_PROTOCOL, Value(valueType_uint16, (uint16)WirelessTypes::commProtocol_lxrs));
    expectWrite(impl, NodeEepromMap::INACTIVE_TIMEOUT, Value::UINT16(200));
    expectWrite(impl, NodeEepromMap::TX_POWER_LEVEL, Value(valueType_int16, (int16)WirelessTypes::power_16dBm));
    expectResetRadio(impl);

    BOOST_CHECK_NO_THROW(node.applyConfig(c));
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_failVerifyWhenApplying)
{
    //Tests attempting to write a config that fails to verify

    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    MOCK_EXPECT(impl->protocol).returns(*(WirelessProtocol::v1_5().get()));

    //make the features() function return the NodeFeatures we want
    NodeInfo info(Version(9, 9), WirelessModels::node_tcLink_1ch, WirelessTypes::region_usa);    //note TC-Link
    std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
    MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

    WirelessNodeConfig c;
    c.samplingMode(WirelessTypes::samplingMode_syncBurst);    //note Burst mode

    //TC-Link doesn't support burst mode
    BOOST_CHECK_THROW(node.applyConfig(c), Error_InvalidNodeConfig);
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_verifyFail_activeChannels)
{
    //Tests failing to verify active channels

    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    //make the features() function return the NodeFeatures we want
    NodeInfo info(Version(9, 9), WirelessModels::node_tcLink_1ch, WirelessTypes::region_usa);    //note TC-Link
    std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
    MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

    WirelessNodeConfig c;
    ChannelMask chs;
    chs.enable(1, true);
    chs.enable(2, true);
    c.activeChannels(chs);

    //check that verify fails with the correct issue
    ConfigIssues issues;
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_EQUAL(issues.size(), 1);
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_ACTIVE_CHANNELS);
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_verifyFail_numSweeps)
{
    //Tests failing to verify number of sweeps

    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    //make the features() function return the NodeFeatures we want
    NodeInfo info(Version(9, 9), WirelessModels::node_gLink_10g, WirelessTypes::region_usa);
    std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
    MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

    WirelessNodeConfig c;
    c.numSweeps(302);    //not a normalized sweeps value

    //check that verify fails with the correct issue
    ConfigIssues issues;
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_EQUAL(issues.size(), 1);
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_SWEEPS);
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_verifyFail_dataFormat)
{
    //Tests failing to verify data format

    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    //make the features() function return the NodeFeatures we want
    NodeInfo info(Version(9, 9), WirelessModels::node_tcLink_3ch, WirelessTypes::region_usa);    //note TC-Link
    std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
    MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

    WirelessNodeConfig c;
    c.dataFormat(WirelessTypes::dataFormat_raw_uint16);    //not a supported data format

    //check that verify fails with the correct issue
    ConfigIssues issues;
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_EQUAL(issues.size(), 1);
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_DATA_FORMAT);
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_verifyFail_timeBetweenBursts)
{
    //Tests failing to verify time between bursts

    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    //make the features() function return the NodeFeatures we want
    NodeInfo info(Version(9, 9), WirelessModels::node_gLink_10g, WirelessTypes::region_usa);
    std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
    MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

    WirelessNodeConfig c;
    TimeSpan ts = TimeSpan::Seconds(40198);
    c.timeBetweenBursts(ts);    //not a normalized time between bursts value

    //check that verify fails with the correct issue
    ConfigIssues issues;
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_EQUAL(issues.size(), 1);
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_TIME_BETWEEN_BURSTS);
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_verifyFail_timeBetweenBursts_notSupported)
{
    //Tests failing to verify time between bursts as it is not supported by the Node

    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    //make the features() function return the NodeFeatures we want
    NodeInfo info(Version(9, 9), WirelessModels::node_tcLink_1ch, WirelessTypes::region_usa);    //tc-link doesn't support burst
    std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
    MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

    WirelessNodeConfig c;
    TimeSpan ts = TimeSpan::Seconds(40198);
    ts = features->normalizeTimeBetweenBursts(ts);
    c.timeBetweenBursts(ts);

    //check that verify fails with the correct issue
    ConfigIssues issues;
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_EQUAL(issues.size(), 1);
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_TIME_BETWEEN_BURSTS);
    BOOST_CHECK_EQUAL(issues.at(0).description(), "Time Between Bursts is not supported by this Node.");
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_verifyFail_multi)
{
    //Tests failing to verify with multiple issues

    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    //make the features() function return the NodeFeatures we want
    NodeInfo info(Version(9, 9), WirelessModels::node_tcLink_1ch, WirelessTypes::region_usa);    //note TC-Link
    std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
    MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

    WirelessNodeConfig c;
    ChannelMask chs;
    chs.enable(1, true);
    chs.enable(2, true);
    c.activeChannels(chs);
    c.dataFormat(WirelessTypes::dataFormat_raw_uint16);    //not a supported data format

    //check that verify fails with the correct issue
    ConfigIssues issues;
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_EQUAL(issues.size(), 2);
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_ACTIVE_CHANNELS);
    BOOST_CHECK_EQUAL(issues.at(1).id(), ConfigIssue::CONFIG_DATA_FORMAT);
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_verifyConflictsFail_sampleRate_sampleMode)
{
    //Tests failing to verify with conflicting sample rate / sample mode

    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(123, b);
    node.setImpl(impl);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);

    expectRead(impl, NodeEepromMap::SAMPLING_MODE, Value::UINT16(WirelessTypes::samplingMode_syncBurst));
    expectRead(impl, NodeEepromMap::ACTIVE_CHANNEL_MASK, Value::UINT16(0x017));
    expectRead(impl, NodeEepromMap::NUM_SWEEPS, Value::UINT16(40));
    expectRead(impl, NodeEepromMap::DATA_FORMAT, Value::UINT16(WirelessTypes::dataFormat_cal_float));
    expectRead(impl, NodeEepromMap::TIME_BETW_SESSIONS, Value::UINT16(4000));
    expectRead(impl, NodeEepromMap::COLLECTION_MODE, Value::UINT16(WirelessTypes::collectionMethod_transmitOnly));
    expectRead(impl, NodeEepromMap::COMM_PROTOCOL, Value::UINT16(WirelessTypes::commProtocol_lxrs));
    expectRead(impl, NodeEepromMap::FIRMWARE_VER, Value::UINT16((uint16)5));

    WirelessNodeConfig c;
    c.sampleRate(WirelessTypes::sampleRate_1Hz);

    //check that verify fails with the correct issue
    ConfigIssues issues;
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_GE(issues.size(), static_cast<uint16>(2));
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_SAMPLE_RATE);
    BOOST_CHECK_EQUAL(issues.at(1).id(), ConfigIssue::CONFIG_SAMPLING_MODE);
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_verifyConflictsFail_sampleRate_channels)
{
    //Tests failing to verify with conflicting sample rate / sample mode

    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(123, b);
    node.setImpl(impl);

    //make the features() function return the NodeFeatures we want
    NodeInfo info(Version(9, 9), WirelessModels::node_vLink, WirelessTypes::region_usa);    //note V-Link
    std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
    MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

    expectRead(impl, NodeEepromMap::SAMPLING_MODE, Value::UINT16(WirelessTypes::samplingMode_syncBurst));
    expectRead(impl, NodeEepromMap::SAMPLE_RATE, Value::UINT16(WirelessTypes::sampleRate_10kHz));
    expectRead(impl, NodeEepromMap::NUM_SWEEPS, Value::UINT16(40));
    expectRead(impl, NodeEepromMap::DATA_FORMAT, Value::UINT16(WirelessTypes::dataFormat_cal_float));
    expectRead(impl, NodeEepromMap::TIME_BETW_SESSIONS, Value::UINT16(4000));
    expectRead(impl, NodeEepromMap::UNLIMITED_SAMPLING, Value::UINT16(0));
    expectRead(impl, NodeEepromMap::COLLECTION_MODE, Value::UINT16(WirelessTypes::collectionMethod_transmitOnly));
    expectRead(impl, NodeEepromMap::COMM_PROTOCOL, Value::UINT16(WirelessTypes::commProtocol_lxrs));
    expectRead(impl, NodeEepromMap::FIRMWARE_VER, Value::UINT16((uint16)5));

    WirelessNodeConfig c;
    ChannelMask chs;
    chs.fromMask(127);
    c.activeChannels(chs);

    //check that verify fails with the correct issue
    ConfigIssues issues;
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_GE(issues.size(), static_cast<uint16>(2));
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_ACTIVE_CHANNELS);
    BOOST_CHECK_EQUAL(issues.at(1).id(), ConfigIssue::CONFIG_SAMPLE_RATE);
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_verifyConflictsFail_sweeps)
{
    //Tests failing to verify with conflicting sweeps and other settings

    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(123, b);
    node.setImpl(impl);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);

    expectRead(impl, NodeEepromMap::SAMPLING_MODE, Value::UINT16(WirelessTypes::samplingMode_sync));
    expectRead(impl, NodeEepromMap::SAMPLE_RATE, Value::UINT16(WirelessTypes::sampleRate_1Hz));
    expectRead(impl, NodeEepromMap::ACTIVE_CHANNEL_MASK, Value::UINT16(0x017));
    expectRead(impl, NodeEepromMap::NUM_SWEEPS, Value::UINT16(40));
    expectRead(impl, NodeEepromMap::DATA_FORMAT, Value::UINT16(WirelessTypes::dataFormat_cal_float));
    expectRead(impl, NodeEepromMap::TIME_BETW_SESSIONS, Value::UINT16(4000));
    expectRead(impl, NodeEepromMap::UNLIMITED_SAMPLING, Value::UINT16(0));

    WirelessNodeConfig c;
    c.numSweeps(2000000000);

    //check that verify fails with the correct issue
    ConfigIssues issues;
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_GE(issues.size(), static_cast<uint16>(1));
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_SWEEPS);
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_verifyConflicts_successBcUnlimitedDuration)
{
    //Tests successfully verifying even though the sweeps value is out of range
    //because the unlimited duration flag is set, meaning sweeps should be ignored

    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(123, b);
    node.setImpl(impl);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);

    expectRead(impl, NodeEepromMap::SAMPLING_MODE, Value::UINT16(WirelessTypes::samplingMode_sync));
    expectRead(impl, NodeEepromMap::SAMPLE_RATE, Value::UINT16(WirelessTypes::sampleRate_1Hz));
    expectRead(impl, NodeEepromMap::ACTIVE_CHANNEL_MASK, Value::UINT16(0x017));
    expectRead(impl, NodeEepromMap::NUM_SWEEPS, Value::UINT16(40));
    expectRead(impl, NodeEepromMap::DATA_FORMAT, Value::UINT16(WirelessTypes::dataFormat_cal_float));
    expectRead(impl, NodeEepromMap::TIME_BETW_SESSIONS, Value::UINT16(4000));
    expectRead(impl, NodeEepromMap::UNLIMITED_SAMPLING, Value::UINT16(1));    //unlimited duration flag is true
    expectRead(impl, NodeEepromMap::FIRMWARE_VER, Value::UINT16((uint16)5));

    WirelessNodeConfig c;
    c.numSweeps(2000000000);

    //check that verify succeeds
    ConfigIssues issues;
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), true);
    BOOST_CHECK_GE(issues.size(), static_cast<uint16>(0));
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_verifyConflictsFail_sweepsWithUnlimitedDurPlusBurst)
{
    //Tests failing to verify with sweeps out of range, even though unlimited duration flag is set.
    //The sweeps should still be checked because the sampling mode is burst, which ignores unlimited duration.

    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(123, b);
    node.setImpl(impl);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);

    expectRead(impl, NodeEepromMap::SAMPLING_MODE, Value::UINT16(WirelessTypes::samplingMode_syncBurst));
    expectRead(impl, NodeEepromMap::SAMPLE_RATE, Value::UINT16(WirelessTypes::sampleRate_64Hz));
    expectRead(impl, NodeEepromMap::ACTIVE_CHANNEL_MASK, Value::UINT16(0x017));
    expectRead(impl, NodeEepromMap::NUM_SWEEPS, Value::UINT16(40));
    expectRead(impl, NodeEepromMap::DATA_FORMAT, Value::UINT16(WirelessTypes::dataFormat_cal_float));
    expectRead(impl, NodeEepromMap::TIME_BETW_SESSIONS, Value::UINT16(4000));
    expectRead(impl, NodeEepromMap::UNLIMITED_SAMPLING, Value::UINT16(1));
    expectRead(impl, NodeEepromMap::COMM_PROTOCOL, Value::UINT16(WirelessTypes::commProtocol_lxrs));
    expectRead(impl, NodeEepromMap::FIRMWARE_VER, Value::UINT16((uint16)5));

    WirelessNodeConfig c;
    c.numSweeps(2000000000);

    //check that verify fails with the correct issue
    ConfigIssues issues;
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_GE(issues.size(), static_cast<uint16>(1));
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_SWEEPS);
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_checkRadioInterval)
{
    WirelessNodeConfig c;

    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(123, b);
    node.setImpl(impl);

    MOCK_EXPECT(impl->protocol).returns(*(WirelessProtocol::v1_5().get()));

    //make the features() function return the NodeFeatures we want
    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl, WirelessModels::node_gLink_10g);

    //test failing due to out of bounds (max)
    c.checkRadioInterval(65);
    BOOST_CHECK_THROW(node.applyConfig(c), Error_InvalidNodeConfig);

    //test failing due to out of bounds (min)
    c.checkRadioInterval(0);
    BOOST_CHECK_THROW(node.applyConfig(c), Error_InvalidNodeConfig);

    expectWrite(impl, NodeEepromMap::SLEEP_INTERVAL, Value::UINT16(284));
    MOCK_EXPECT(impl->cyclePower);
    c.checkRadioInterval(27);
    BOOST_CHECK_NO_THROW(node.applyConfig(c));
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_lostBeaconTimeout)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(123, b);
    node.setImpl(impl);

    MOCK_EXPECT(impl->protocol).returns(*(WirelessProtocol::v1_5().get()));

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);

    WirelessNodeConfig c;

    //check the beacon timeout minimum failing
    c.lostBeaconTimeout(1);
    BOOST_CHECK_THROW(node.applyConfig(c), Error_InvalidNodeConfig);

    //check the beacon timeout success
    c.lostBeaconTimeout(45);
    expectWrite(impl, NodeEepromMap::LOST_BEACON_TIMEOUT, Value::UINT16(45));
    MOCK_EXPECT(impl->cyclePower);
    BOOST_CHECK_NO_THROW(node.applyConfig(c));

    //check the beacon timeout maximum failing
    c.lostBeaconTimeout(605);
    BOOST_CHECK_THROW(node.applyConfig(c), Error_InvalidNodeConfig);
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_bootMode)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(123, b);
    node.setImpl(impl);

    MOCK_EXPECT(impl->protocol).returns(*(WirelessProtocol::v1_5().get()));

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl, WirelessModels::node_iepeLink);

    WirelessNodeConfig c;

    //check the boot mode not supported on iepe link
    c.defaultMode(WirelessTypes::defaultMode_ldc);
    BOOST_CHECK_THROW(node.applyConfig(c), Error_InvalidNodeConfig);

    MOCK_RESET(impl->features);
    expectNodeFeatures(features, impl, WirelessModels::node_gLink_10g);

    expectWrite(impl, NodeEepromMap::DEFAULT_MODE, Value::UINT16(WirelessTypes::defaultMode_ldc));
    MOCK_EXPECT(impl->cyclePower);
    BOOST_CHECK_NO_THROW(node.applyConfig(c));
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_filterSettlingTime)
{
    //tests settling time failing due to conflict
    {
        std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
        BaseStation b = makeBaseStationWithMockImpl();
        WirelessNode node(123, b);
        node.setImpl(impl);

        MOCK_EXPECT(impl->protocol).returns(*(WirelessProtocol::v1_5().get()));

        std::unique_ptr<NodeFeatures> features;
        expectNodeFeatures(features, impl, WirelessModels::node_tcLink_6ch);

        WirelessNodeConfig c;
        c.filterSettlingTime(ChannelMask(BOOST_BINARY(00111111)), WirelessTypes::settling_60ms); //invalid settling time for sample rate
        c.activeChannels(ChannelMask(1));
        c.numSweeps(100);
        c.dataFormat(WirelessTypes::dataFormat_cal_float);
        c.unlimitedDuration(true);
        c.dataCollectionMethod(WirelessTypes::collectionMethod_transmitOnly);

        expectRead(impl, NodeEepromMap::SAMPLING_MODE, Value::UINT16(WirelessTypes::samplingMode_sync));
        expectRead(impl, NodeEepromMap::SAMPLE_RATE, Value::UINT16(WirelessTypes::sampleRate_4Hz));

        //check the settling time fails to apply
        BOOST_CHECK_THROW(node.applyConfig(c), Error_InvalidNodeConfig);

        //check that verify fails with the correct issue
        ConfigIssues issues;
        BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
        BOOST_CHECK_EQUAL(issues.size(), 2);
        BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_FILTER_SETTLING_TIME);
        BOOST_CHECK_EQUAL(issues.at(1).id(), ConfigIssue::CONFIG_SAMPLE_RATE);
    }
    
    //tests settling time failing due to not supported
    {
        std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
        BaseStation b = makeBaseStationWithMockImpl();
        WirelessNode node(123, b);
        node.setImpl(impl);

        MOCK_EXPECT(impl->protocol).returns(*(WirelessProtocol::v1_5().get()));

        std::unique_ptr<NodeFeatures> features;
        expectNodeFeatures(features, impl, WirelessModels::node_gLink_10g);

        WirelessNodeConfig c;
        c.filterSettlingTime(ChannelMask(BOOST_BINARY(00000001)), WirelessTypes::settling_60ms); //g-link doesn't support this

        //check the settling time fails to apply
        BOOST_CHECK_THROW(node.applyConfig(c), Error_InvalidNodeConfig);

        //check that verify fails with the correct issue
        ConfigIssues issues;
        BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
        BOOST_CHECK_EQUAL(issues.size(), 1);
        BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_FILTER_SETTLING_TIME);
    }

    //tests settling time success
    {
        std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
        BaseStation b = makeBaseStationWithMockImpl();
        WirelessNode node(123, b);
        node.setImpl(impl);

        MOCK_EXPECT(impl->protocol).returns(*(WirelessProtocol::v1_5().get()));

        std::unique_ptr<NodeFeatures> features;
        expectNodeFeatures(features, impl, WirelessModels::node_tcLink_6ch);

        WirelessNodeConfig c;
        c.filterSettlingTime(ChannelMask(BOOST_BINARY(00111111)), WirelessTypes::settling_16ms);

        expectRead(impl, NodeEepromMap::SAMPLING_MODE, Value::UINT16(WirelessTypes::samplingMode_sync));
        expectRead(impl, NodeEepromMap::SAMPLE_RATE, Value::UINT16(WirelessTypes::sampleRate_2Hz));
        expectRead(impl, NodeEepromMap::ACTIVE_CHANNEL_MASK, Value::UINT16(1));
        expectRead(impl, NodeEepromMap::NUM_SWEEPS, Value::UINT16(1));
        expectRead(impl, NodeEepromMap::DATA_FORMAT, Value::UINT16(WirelessTypes::dataFormat_cal_float));
        expectRead(impl, NodeEepromMap::UNLIMITED_SAMPLING, Value::UINT16(1));

        //expect the single eeprom write
        expectWrite(impl, NodeEepromMap::FILTER_1, Value::UINT16(3));
        MOCK_EXPECT(impl->cyclePower);

        //check the settling time succeeds to apply
        BOOST_CHECK_NO_THROW(node.applyConfig(c));

        //check that verify succeeds
        ConfigIssues issues;
        BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), true);
    }
    
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_thermocoupleType)
{
    //tests thermo type failing due to not supported
    {
        std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
        BaseStation b = makeBaseStationWithMockImpl();
        WirelessNode node(123, b);
        node.setImpl(impl);

        MOCK_EXPECT(impl->protocol).returns(*(WirelessProtocol::v1_5().get()));

        std::unique_ptr<NodeFeatures> features;
        expectNodeFeatures(features, impl, WirelessModels::node_gLink_10g);

        WirelessNodeConfig c;
        c.thermocoupleType(ChannelMask(BOOST_BINARY(00000001)), WirelessTypes::tc_J); //g-link doesn't support this

        //check the settling time fails to apply
        BOOST_CHECK_THROW(node.applyConfig(c), Error_InvalidNodeConfig);

        //check that verify fails with the correct issue
        ConfigIssues issues;
        BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
        BOOST_CHECK_EQUAL(issues.size(), 1);
        BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_THERMOCOUPLE_TYPE);
    }

    //tests settling time success
    {
        std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
        BaseStation b = makeBaseStationWithMockImpl();
        WirelessNode node(123, b);
        node.setImpl(impl);

        MOCK_EXPECT(impl->protocol).returns(*(WirelessProtocol::v1_5().get()));

        std::unique_ptr<NodeFeatures> features;
        expectNodeFeatures(features, impl, WirelessModels::node_tcLink_6ch);

        WirelessNodeConfig c;
        c.thermocoupleType(ChannelMask(BOOST_BINARY(00111111)), WirelessTypes::tc_J);

        //expect the single eeprom write
        expectWrite(impl, NodeEepromMap::THERMOCPL_TYPE, Value::UINT16(2));
        MOCK_EXPECT(impl->cyclePower);

        //check the settling time succeeds to apply
        BOOST_CHECK_NO_THROW(node.applyConfig(c));

        //check that verify succeeds
        ConfigIssues issues;
        BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), true);
    }

}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_linearEquation)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(123, b);
    node.setImpl(impl);

    MOCK_EXPECT(impl->protocol).returns(*(WirelessProtocol::v1_5().get()));

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl, WirelessModels::node_gLink_10g);

    LinearEquation eq(64.78f, 142.23f);

    WirelessNodeConfig c;
    c.linearEquation(ChannelMask(8), eq);

    //expect the single eeprom write
    expectWrite(impl, NodeEepromMap::CH_ACTION_SLOPE_4, Value::FLOAT(64.78f));
    expectWrite(impl, NodeEepromMap::CH_ACTION_OFFSET_4, Value::FLOAT(142.23f));
    MOCK_EXPECT(impl->cyclePower);

    BOOST_CHECK_NO_THROW(node.applyConfig(c));

    //check that verify succeeds
    ConfigIssues issues;
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), true);
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_verify_fatigueDistAngles)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(123, b);
    node.setImpl(impl);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl, WirelessModels::node_shmLink2_cust1);

    //test good angle settings
    FatigueOptions opts;
    opts.distributedAngleMode_lowerBound(5.0f);
    opts.distributedAngleMode_upperBound(320.4513f);
    opts.distributedAngleMode_numAngles(16);

    WirelessNodeConfig c;
    c.fatigueOptions(opts);

    expectRead(impl, NodeEepromMap::SAMPLING_MODE, Value::UINT16((uint16)WirelessTypes::samplingMode_sync));
    expectRead(impl, NodeEepromMap::DATA_FORMAT, Value::UINT16((uint16)WirelessTypes::dataFormat_cal_float));

    ConfigIssues issues;
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), true);

    //test good very large angle
    opts.distributedAngleMode_lowerBound(0.4f);
    opts.distributedAngleMode_upperBound(359.5f);
    c.fatigueOptions(opts);
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), true);

    //test bad wrap around angle (too close)
    opts.distributedAngleMode_lowerBound(359.5f);
    opts.distributedAngleMode_upperBound(.3f);
    c.fatigueOptions(opts);
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_FATIGUE_DIST_ANGLE);
    issues.clear();

    //test good wrap around angle
    opts.distributedAngleMode_lowerBound(350.234f);
    opts.distributedAngleMode_upperBound(31.0f);
    c.fatigueOptions(opts);
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), true);

    //test bad standard angles (too close)
    opts.distributedAngleMode_lowerBound(49.5f);
    opts.distributedAngleMode_upperBound(50.0f);
    c.fatigueOptions(opts);
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_FATIGUE_DIST_ANGLE);
    issues.clear();

    //test bad number of angles
    opts.distributedAngleMode_lowerBound(1.0f);
    opts.distributedAngleMode_upperBound(31.0f);
    opts.distributedAngleMode_numAngles(3);
    c.fatigueOptions(opts);
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_FATIGUE_DIST_NUM_ANGLES);
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_verify_eventTrigger)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(123, b);
    node.setImpl(impl);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl, WirelessModels::node_wirelessImpactSensor);

    EventTriggerOptions opts;
    opts.triggerMask(BitMask(0));

    WirelessNodeConfig c;
    c.sampleRate(WirelessTypes::WirelessSampleRate::sampleRate_256Hz);
    c.activeChannels(ChannelMask(1));
    c.numSweeps(1000);
    c.dataFormat(WirelessTypes::dataFormat_cal_float);
    c.unlimitedDuration(true);
    c.dataCollectionMethod(WirelessTypes::collectionMethod_logAndTransmit);
    c.dataMode(WirelessTypes::dataMode_raw);

    ConfigIssues issues;

    //test good sampling mode with triggers disabled
    c.eventTriggerOptions(opts);
    c.samplingMode(WirelessTypes::samplingMode_sync);
   
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), true);

    //test good sampling mode with triggers enabled
    opts.triggerMask(BitMask(2));
    c.eventTriggerOptions(opts);
    c.samplingMode(WirelessTypes::samplingMode_syncEvent);
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), true);

    //test sampling mode with bad collection method
    c.dataCollectionMethod(WirelessTypes::collectionMethod_transmitOnly);
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_DATA_COLLECTION_METHOD);
    c.dataCollectionMethod(WirelessTypes::collectionMethod_logAndTransmit);
    issues.clear();

    //test bad sampling mode with triggers enabled
    opts.triggerMask(BitMask(1));
    c.eventTriggerOptions(opts);
    c.samplingMode(WirelessTypes::samplingMode_sync);
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_EVENT_TRIGGER_MASK);
    issues.clear();

    //test bad sampling mode with triggers disabled
    opts.triggerMask(BitMask(0));
    c.eventTriggerOptions(opts);
    c.samplingMode(WirelessTypes::samplingMode_syncEvent);
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_EVENT_TRIGGER_MASK);
    issues.clear();
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_verify_dataMode)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(123, b);
    node.setImpl(impl);

    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::ASPP_VER_LXRS).returns(Value::UINT16(0x0105));

    NodeInfo info(Version(10, 0), WirelessModels::node_sgLink, WirelessTypes::region_usa);
    std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
    MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

    WirelessNodeConfig c;
    c.sampleRate(WirelessTypes::WirelessSampleRate::sampleRate_256Hz);
    c.activeChannels(ChannelMask(1));
    c.numSweeps(1000);
    c.dataFormat(WirelessTypes::dataFormat_cal_float);
    c.unlimitedDuration(true);
    c.dataCollectionMethod(WirelessTypes::collectionMethod_logAndTransmit);
    c.samplingMode(WirelessTypes::samplingMode_sync);
    ConfigIssues issues;

    //-------------------------------------
    //Test derived mode not supported
    c.dataMode(WirelessTypes::dataMode_derived);
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_DATA_MODE);
    issues.clear();
    //-------------------------------------

    //-------------------------------------
    //Test data mode ok
    c.dataMode(WirelessTypes::dataMode_raw);
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), true);
    //-------------------------------------
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_verify_derivedModeRate)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(123, b);
    node.setImpl(impl);

    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::ASPP_VER_LXRS).returns(Value::UINT16(0x0105));
    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::FLASH_ID).returns(Value::UINT16(0));

    NodeInfo info(Version(10, 34862), WirelessModels::node_gLink_200_8g, WirelessTypes::region_usa);
    std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
    MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

    WirelessNodeConfig c;
    c.sampleRate(WirelessTypes::WirelessSampleRate::sampleRate_256Hz);
    c.lowPassFilter(ChannelMask(7), WirelessTypes::filter_209hz);
    c.activeChannels(ChannelMask(1));
    c.numSweeps(1000);
    c.dataFormat(WirelessTypes::dataFormat_cal_float);
    c.unlimitedDuration(true);
    c.dataCollectionMethod(WirelessTypes::collectionMethod_logAndTransmit);
    c.samplingMode(WirelessTypes::samplingMode_sync);
    c.dataMode(WirelessTypes::dataMode_raw_derived);
    c.derivedChannelMask(WirelessTypes::derivedCategory_rms, ChannelMask(1));
    c.derivedChannelMask(WirelessTypes::derivedCategory_peakToPeak, ChannelMask(1));
    c.derivedChannelMask(WirelessTypes::derivedCategory_velocity, ChannelMask(1));
    c.derivedChannelMask(WirelessTypes::derivedCategory_crestFactor, ChannelMask(1));
    EventTriggerOptions opts;
    opts.triggerMask(BitMask(0));
    c.eventTriggerOptions(opts);

    ConfigIssues issues;

    //-------------------------------------
    //Test derived mode not supported
    c.derivedDataRate(WirelessTypes::sampleRate_256Hz);
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_DERIVED_DATA_RATE);
    issues.clear();
    //-------------------------------------

    //-------------------------------------
    //Test derived data rate is ok
    c.derivedDataRate(WirelessTypes::sampleRate_30Min);
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), true);
    //-------------------------------------
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_verify_derivedModeMask)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(123, b);
    node.setImpl(impl);

    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::ASPP_VER_LXRS).returns(Value::UINT16(0x0105));
    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::FLASH_ID).returns(Value::UINT16(0));

    NodeInfo info(Version(10, 34862), WirelessModels::node_gLink_200_8g, WirelessTypes::region_usa);
    std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
    MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

    WirelessNodeConfig c;
    c.sampleRate(WirelessTypes::WirelessSampleRate::sampleRate_256Hz);
    c.lowPassFilter(ChannelMask(7), WirelessTypes::filter_209hz);
    c.activeChannels(ChannelMask(1));
    c.numSweeps(1000);
    c.dataFormat(WirelessTypes::dataFormat_cal_float);
    c.unlimitedDuration(true);
    c.dataCollectionMethod(WirelessTypes::collectionMethod_logAndTransmit);
    c.samplingMode(WirelessTypes::samplingMode_sync);
    c.dataMode(WirelessTypes::dataMode_raw_derived);
    c.derivedDataRate(WirelessTypes::sampleRate_30Sec);
    c.derivedChannelMask(WirelessTypes::derivedCategory_rms, ChannelMask(0));               //invalid ch for G-Link-200
    c.derivedChannelMask(WirelessTypes::derivedCategory_peakToPeak, ChannelMask(0));
    c.derivedChannelMask(WirelessTypes::derivedCategory_velocity, ChannelMask(0));
    c.derivedChannelMask(WirelessTypes::derivedCategory_crestFactor, ChannelMask(0));
    EventTriggerOptions opts;
    opts.triggerMask(BitMask(0));
    c.eventTriggerOptions(opts);

    ConfigIssues issues;

    //-------------------------------------
    //Test invalid derived mask
    c.derivedChannelMask(WirelessTypes::derivedCategory_rms, ChannelMask(512));             //invalid ch for G-Link-200
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_DERIVED_MASK_RMS);
    issues.clear();
    //-------------------------------------

    //-------------------------------------
    //Test invalid derived mask
    c.derivedChannelMask(WirelessTypes::derivedCategory_rms, ChannelMask(0));
    c.derivedChannelMask(WirelessTypes::derivedCategory_peakToPeak, ChannelMask(512));      //invalid ch for G-Link-200
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_DERIVED_MASK_P2P);
    issues.clear();
    //-------------------------------------

    //-------------------------------------
    //Test invalid derived mask
    c.derivedChannelMask(WirelessTypes::derivedCategory_peakToPeak, ChannelMask(0));
    c.derivedChannelMask(WirelessTypes::derivedCategory_velocity, ChannelMask(512));             //invalid ch for G-Link-200
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_DERIVED_MASK_IPS);
    issues.clear();
    //-------------------------------------

    //-------------------------------------
    //Test invalid derived mask
    c.derivedChannelMask(WirelessTypes::derivedCategory_velocity, ChannelMask(0));
    c.derivedChannelMask(WirelessTypes::derivedCategory_crestFactor, ChannelMask(513));     //invalid ch for G-Link-200
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_DERIVED_MASK_CREST_FACTOR);
    issues.clear();
    //-------------------------------------

    //-------------------------------------
    //Test derived data rate is ok
    c.derivedChannelMask(WirelessTypes::derivedCategory_crestFactor, ChannelMask(1));
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), true);
    //-------------------------------------
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_verify_derivedModeMask_invalidChannels)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(123, b);
    node.setImpl(impl);

    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::ASPP_VER_LXRS).returns(Value::UINT16(0x0105));
    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::FLASH_ID).returns(Value::UINT16(0));

    NodeInfo info(Version(12, 41496), WirelessModels::node_gLink_200_8g, WirelessTypes::region_usa);    //fw supports tilt
    std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
    MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

    WirelessNodeConfig c;
    c.sampleRate(WirelessTypes::WirelessSampleRate::sampleRate_256Hz);
    c.lowPassFilter(ChannelMask(7), WirelessTypes::filter_209hz);
    c.activeChannels(ChannelMask(1));
    c.numSweeps(1000);
    c.dataFormat(WirelessTypes::dataFormat_cal_float);
    c.unlimitedDuration(true);
    c.dataCollectionMethod(WirelessTypes::collectionMethod_logAndTransmit);
    c.samplingMode(WirelessTypes::samplingMode_sync);
    c.dataMode(WirelessTypes::dataMode_raw_derived);
    c.derivedDataRate(WirelessTypes::sampleRate_30Sec);
    c.derivedChannelMask(WirelessTypes::derivedCategory_rms, ChannelMask(0));               //invalid ch for G-Link-200
    c.derivedChannelMask(WirelessTypes::derivedCategory_peakToPeak, ChannelMask(0));
    c.derivedChannelMask(WirelessTypes::derivedCategory_velocity, ChannelMask(0));
    c.derivedChannelMask(WirelessTypes::derivedCategory_crestFactor, ChannelMask(0));
    EventTriggerOptions opts;
    opts.triggerMask(BitMask(0));
    c.eventTriggerOptions(opts);

    ConfigIssues issues;

    //-------------------------------------
    //Test invalid derived mask
    c.derivedChannelMask(WirelessTypes::derivedCategory_rms, ChannelMask(16));             //ch5 (roll) doesn't support rms
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_DERIVED_MASK_RMS);
    issues.clear();
    //-------------------------------------

    //-------------------------------------
    //Test invalid derived mask
    c.derivedChannelMask(WirelessTypes::derivedCategory_rms, ChannelMask(1));
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), true);
    issues.clear();
    //-------------------------------------

}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_verify_channelMasks)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(123, b);
    node.setImpl(impl);

    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::ASPP_VER_LXRS).returns(Value::UINT16(0x0105));
    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::FLASH_ID).returns(Value::UINT16(0));

    NodeInfo info(Version(10, 34862), WirelessModels::node_gLink_200_8g, WirelessTypes::region_usa);
    std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
    MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

    WirelessNodeConfig c;
    c.sampleRate(WirelessTypes::WirelessSampleRate::sampleRate_256Hz);
    c.lowPassFilter(ChannelMask(7), WirelessTypes::filter_209hz);
    c.numSweeps(1000);
    c.dataFormat(WirelessTypes::dataFormat_cal_float);
    c.unlimitedDuration(true);
    c.dataCollectionMethod(WirelessTypes::collectionMethod_logAndTransmit);
    c.samplingMode(WirelessTypes::samplingMode_sync);
    c.dataMode(WirelessTypes::dataMode_raw_derived);
    c.derivedDataRate(WirelessTypes::sampleRate_30Sec);
    c.derivedChannelMask(WirelessTypes::derivedCategory_rms, ChannelMask(1));
    c.derivedChannelMask(WirelessTypes::derivedCategory_peakToPeak, ChannelMask(0));
    c.derivedChannelMask(WirelessTypes::derivedCategory_velocity, ChannelMask(0));
    c.derivedChannelMask(WirelessTypes::derivedCategory_crestFactor, ChannelMask(0));
    EventTriggerOptions opts;
    opts.triggerMask(BitMask(0));
    c.eventTriggerOptions(opts);

    ConfigIssues issues;

    //-------------------------------------
    //Test no raw channels
    c.activeChannels(ChannelMask(0));
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_ACTIVE_CHANNELS);
    issues.clear();
    //-------------------------------------

    //-------------------------------------
    //Test invalid derived mask
    c.activeChannels(ChannelMask(1));
    c.derivedChannelMask(WirelessTypes::derivedCategory_rms, ChannelMask(0));
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_DERIVED_MASK);
    issues.clear();
    //-------------------------------------

    //-------------------------------------
    //Test derived data rate is ok
    c.derivedChannelMask(WirelessTypes::derivedCategory_rms, ChannelMask(1));
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), true);
    //-------------------------------------
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_verify_derivedSampleRate)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(123, b);
    node.setImpl(impl);

    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::ASPP_VER_LXRS).returns(Value::UINT16(0x0105));
    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::FLASH_ID).returns(Value::UINT16(0));

    NodeInfo info(Version(10, 34862), WirelessModels::node_gLink_200_8g, WirelessTypes::region_usa);
    std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
    MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

    WirelessNodeConfig c;
    c.numSweeps(1000);
    c.activeChannels(ChannelMask(1));
    c.dataFormat(WirelessTypes::dataFormat_cal_float);
    c.unlimitedDuration(true);
    c.dataCollectionMethod(WirelessTypes::collectionMethod_logAndTransmit);
    c.samplingMode(WirelessTypes::samplingMode_sync);
    c.dataMode(WirelessTypes::dataMode_raw_derived);
    c.derivedChannelMask(WirelessTypes::derivedCategory_rms, ChannelMask(1));
    c.derivedChannelMask(WirelessTypes::derivedCategory_peakToPeak, ChannelMask(0));
    c.derivedChannelMask(WirelessTypes::derivedCategory_velocity, ChannelMask(0));
    c.derivedChannelMask(WirelessTypes::derivedCategory_crestFactor, ChannelMask(0));
    EventTriggerOptions opts;
    opts.triggerMask(BitMask(0));
    c.eventTriggerOptions(opts);

    ConfigIssues issues;

    //-------------------------------------
    //Test too fast (1)
    c.sampleRate(WirelessTypes::sampleRate_16Hz);
    c.derivedDataRate(WirelessTypes::sampleRate_1Hz);
    c.lowPassFilter(ChannelMask(7), WirelessTypes::filter_209hz);
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_SAMPLE_RATE);
    BOOST_CHECK_EQUAL(issues.at(1).id(), ConfigIssue::CONFIG_DERIVED_DATA_RATE);
    issues.clear();
    //-------------------------------------

    //-------------------------------------
    //Test too fast (2)
    c.sampleRate(WirelessTypes::sampleRate_1Hz);
    c.derivedDataRate(WirelessTypes::sampleRate_30Sec);
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), false);
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_SAMPLE_RATE);
    BOOST_CHECK_EQUAL(issues.at(1).id(), ConfigIssue::CONFIG_DERIVED_DATA_RATE);
    issues.clear();
    //-------------------------------------

    //-------------------------------------
    //Test ok rate (1)
    c.sampleRate(WirelessTypes::sampleRate_1Hz);
    c.derivedDataRate(WirelessTypes::sampleRate_1Min);
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), true);
    //-------------------------------------

    //-------------------------------------
    //Test ok rate (2)
    c.sampleRate(WirelessTypes::sampleRate_32Hz);
    c.derivedDataRate(WirelessTypes::sampleRate_1Hz);
    BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), true);
    //-------------------------------------
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_flashBandwidth)
{
    WirelessTypes::DataFormat dataFormat = WirelessTypes::dataFormat_raw_uint24;
    uint8 numChannels = 8;
    WirelessTypes::WirelessSampleRate sampleRate = WirelessTypes::sampleRate_4096Hz;
    WirelessTypes::WirelessSampleRate derivedRate = WirelessTypes::sampleRate_1Hz;
    uint32 derivedBytesPerSweep = 0;

    BOOST_CHECK_EQUAL(WirelessNodeConfig::flashBandwidth(sampleRate, dataFormat, numChannels, derivedBytesPerSweep, derivedRate), 98304);
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_flashBandwidth_burst)
{
    WirelessTypes::DataFormat dataFormat = WirelessTypes::dataFormat_raw_uint24;
    uint8 numChannels = 8;
    WirelessTypes::WirelessSampleRate sampleRate = WirelessTypes::sampleRate_4096Hz;
    uint32 numSweeps = 4096;
    TimeSpan timeBetweenBursts = TimeSpan::Seconds(2);
    uint32 derivedBytesPerSweep = 0;

    BOOST_CHECK_EQUAL(WirelessNodeConfig::flashBandwidth_burst(sampleRate, dataFormat, numChannels, derivedBytesPerSweep, numSweeps, timeBetweenBursts), 49152);
}

BOOST_AUTO_TEST_SUITE_END()