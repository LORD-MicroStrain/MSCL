/*****************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the included
LICENSE.txt file for a copy of the full GNU General Public License.
*****************************************************************************/
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

	//make the features() function return the NodeFeatures we want
	NodeInfo info(Version(9, 9), WirelessModels::node_gLink_2g, 200000, WirelessTypes::region_usa);
	std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
	MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

	WirelessNodeConfig c;
	c.inactivityTimeout(4500);

	//expect the single eeprom write
	expectWrite(impl, NodeEepromMap::INACTIVE_TIMEOUT, Value::UINT16(4500));
	expectResetRadio(impl);

	BOOST_CHECK_NO_THROW(node.applyConfig(c));
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_setMultipleValues)
{
	//Tests setting multiple values in the config and writing them to a Node

	std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
	BaseStation b = makeBaseStationWithMockImpl();
	WirelessNode node(100, b);
	node.setImpl(impl);

	//make the features() function return the NodeFeatures we want
	NodeInfo info(Version(9, 9), WirelessModels::node_gLink_2g, 200000, WirelessTypes::region_usa);
	std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
	MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

	WirelessNodeConfig c;
	c.inactivityTimeout(200);
	c.transmitPower(WirelessTypes::power_16dBm);

	//expect the eeprom writes
	expectWrite(impl, NodeEepromMap::INACTIVE_TIMEOUT, Value::UINT16(200));
	expectWrite(impl, NodeEepromMap::TX_POWER_LEVEL, Value::UINT16(WirelessTypes::power_16dBm));
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

	//make the features() function return the NodeFeatures we want
	NodeInfo info(Version(9, 9), WirelessModels::node_tcLink_1ch, 200000, WirelessTypes::region_usa);	//note TC-Link
	std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
	MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

	WirelessNodeConfig c;
	c.samplingMode(WirelessTypes::samplingMode_syncBurst);	//note Burst mode

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
	NodeInfo info(Version(9, 9), WirelessModels::node_tcLink_1ch, 200000, WirelessTypes::region_usa);	//note TC-Link
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
	NodeInfo info(Version(9, 9), WirelessModels::node_gLink_10g, 200000, WirelessTypes::region_usa);
	std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
	MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

	WirelessNodeConfig c;
	c.numSweeps(302);	//not a normalized sweeps value

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
	NodeInfo info(Version(9, 9), WirelessModels::node_tcLink_3ch, 200000, WirelessTypes::region_usa);	//note TC-Link
	std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
	MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

	WirelessNodeConfig c;
	c.dataFormat(WirelessTypes::dataFormat_2byte_uint);	//not a supported data format

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
	NodeInfo info(Version(9, 9), WirelessModels::node_gLink_10g, 200000, WirelessTypes::region_usa);
	std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
	MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

	WirelessNodeConfig c;
	TimeSpan ts = TimeSpan::Seconds(40198);
	c.timeBetweenBursts(ts);	//not a normalized time between bursts value

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
	NodeInfo info(Version(9, 9), WirelessModels::node_tcLink_1ch, 200000, WirelessTypes::region_usa);	//tc-link doesn't support burst
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
	NodeInfo info(Version(9, 9), WirelessModels::node_tcLink_1ch, 200000, WirelessTypes::region_usa);	//note TC-Link
	std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
	MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

	WirelessNodeConfig c;
	ChannelMask chs;
	chs.enable(1, true);
	chs.enable(2, true);
	c.activeChannels(chs);
	c.dataFormat(WirelessTypes::dataFormat_2byte_uint);	//not a supported data format

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
	expectRead(impl, NodeEepromMap::DATA_FORMAT, Value::UINT16(WirelessTypes::dataFormat_4byte_float));
	expectRead(impl, NodeEepromMap::TIME_BETW_SESSIONS, Value::UINT16(4000));

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
	NodeInfo info(Version(9, 9), WirelessModels::node_vLink, 200000, WirelessTypes::region_usa);	//note V-Link
	std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
	MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

	expectRead(impl, NodeEepromMap::SAMPLING_MODE, Value::UINT16(WirelessTypes::samplingMode_syncBurst));
	expectRead(impl, NodeEepromMap::SAMPLE_RATE, Value::UINT16(WirelessTypes::sampleRate_10kHz));
	expectRead(impl, NodeEepromMap::NUM_SWEEPS, Value::UINT16(40));
	expectRead(impl, NodeEepromMap::DATA_FORMAT, Value::UINT16(WirelessTypes::dataFormat_4byte_float));
	expectRead(impl, NodeEepromMap::TIME_BETW_SESSIONS, Value::UINT16(4000));
	expectRead(impl, NodeEepromMap::UNLIMITED_SAMPLING, Value::UINT16(0));

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
	expectRead(impl, NodeEepromMap::DATA_FORMAT, Value::UINT16(WirelessTypes::dataFormat_4byte_float));
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
	expectRead(impl, NodeEepromMap::DATA_FORMAT, Value::UINT16(WirelessTypes::dataFormat_4byte_float));
	expectRead(impl, NodeEepromMap::TIME_BETW_SESSIONS, Value::UINT16(4000));
	expectRead(impl, NodeEepromMap::UNLIMITED_SAMPLING, Value::UINT16(1));	//unlimited duration flag is true

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
	expectRead(impl, NodeEepromMap::DATA_FORMAT, Value::UINT16(WirelessTypes::dataFormat_4byte_float));
	expectRead(impl, NodeEepromMap::TIME_BETW_SESSIONS, Value::UINT16(4000));
	expectRead(impl, NodeEepromMap::UNLIMITED_SAMPLING, Value::UINT16(1));

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
	expectResetRadio(impl);
	c.checkRadioInterval(27);
	BOOST_CHECK_NO_THROW(node.applyConfig(c));
}

BOOST_AUTO_TEST_CASE(WirelessNodeConfig_lostBeaconTimeout)
{
	std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
	BaseStation b = makeBaseStationWithMockImpl();
	WirelessNode node(123, b);
	node.setImpl(impl);

	std::unique_ptr<NodeFeatures> features;
	expectNodeFeatures(features, impl);

	WirelessNodeConfig c;

	//check the beacon timeout minimum failing
	c.lostBeaconTimeout(1);
	BOOST_CHECK_THROW(node.applyConfig(c), Error_InvalidNodeConfig);

	//check the beacon timeout success
	c.lostBeaconTimeout(45);
	expectWrite(impl, NodeEepromMap::LOST_BEACON_TIMEOUT, Value::UINT16(45));
	expectResetRadio(impl);
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

	std::unique_ptr<NodeFeatures> features;
	expectNodeFeatures(features, impl, WirelessModels::node_iepeLink);

	WirelessNodeConfig c;

	//check the boot mode not supported on iepe link
	c.defaultMode(WirelessTypes::defaultMode_ldc);
	BOOST_CHECK_THROW(node.applyConfig(c), Error_InvalidNodeConfig);

	MOCK_RESET(impl->features);
	expectNodeFeatures(features, impl, WirelessModels::node_gLink_10g);

	expectWrite(impl, NodeEepromMap::DEFAULT_MODE, Value::UINT16(WirelessTypes::defaultMode_ldc));
	expectResetRadio(impl);
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

		std::unique_ptr<NodeFeatures> features;
		expectNodeFeatures(features, impl, WirelessModels::node_tcLink_6ch);

		WirelessNodeConfig c;
		c.filterSettlingTime(ChannelMask(BOOST_BINARY(00111111)), WirelessTypes::settling_60ms); //invalid settling time for sample rate
		c.activeChannels(ChannelMask(1));
		c.numSweeps(100);
		c.dataFormat(WirelessTypes::dataFormat_4byte_float);
		c.unlimitedDuration(true);

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

		std::unique_ptr<NodeFeatures> features;
		expectNodeFeatures(features, impl, WirelessModels::node_tcLink_6ch);

		WirelessNodeConfig c;
		c.filterSettlingTime(ChannelMask(BOOST_BINARY(00111111)), WirelessTypes::settling_16ms);

		expectRead(impl, NodeEepromMap::SAMPLING_MODE, Value::UINT16(WirelessTypes::samplingMode_sync));
		expectRead(impl, NodeEepromMap::SAMPLE_RATE, Value::UINT16(WirelessTypes::sampleRate_2Hz));
		expectRead(impl, NodeEepromMap::ACTIVE_CHANNEL_MASK, Value::UINT16(1));
		expectRead(impl, NodeEepromMap::NUM_SWEEPS, Value::UINT16(1));
		expectRead(impl, NodeEepromMap::DATA_FORMAT, Value::UINT16(WirelessTypes::dataFormat_4byte_float));
		expectRead(impl, NodeEepromMap::UNLIMITED_SAMPLING, Value::UINT16(1));

		//expect the single eeprom write
		expectWrite(impl, NodeEepromMap::FILTER_1, Value::UINT16(3));
		expectResetRadio(impl);

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

		std::unique_ptr<NodeFeatures> features;
		expectNodeFeatures(features, impl, WirelessModels::node_tcLink_6ch);

		WirelessNodeConfig c;
		c.thermocoupleType(ChannelMask(BOOST_BINARY(00111111)), WirelessTypes::tc_J);

		//expect the single eeprom write
		expectWrite(impl, NodeEepromMap::THERMOCPL_TYPE, Value::UINT16(2));
		expectResetRadio(impl);

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

	std::unique_ptr<NodeFeatures> features;
	expectNodeFeatures(features, impl, WirelessModels::node_gLink_10g);

	LinearEquation eq(64.78f, 142.23f);

	WirelessNodeConfig c;
	c.linearEquation(ChannelMask(8), eq);

	//expect the single eeprom write
	expectWrite(impl, NodeEepromMap::CH_ACTION_SLOPE_4, Value::FLOAT(64.78f));
	expectWrite(impl, NodeEepromMap::CH_ACTION_OFFSET_4, Value::FLOAT(142.23f));
	expectResetRadio(impl);

	BOOST_CHECK_NO_THROW(node.applyConfig(c));

	//check that verify succeeds
	ConfigIssues issues;
	BOOST_CHECK_EQUAL(node.verifyConfig(c, issues), true);
}

BOOST_AUTO_TEST_SUITE_END()