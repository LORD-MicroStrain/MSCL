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
#include "mscl/MicroStrain/Wireless/WirelessNode.h"
#include "mscl/MicroStrain/Wireless/BaseStation.h"
#include "mscl/MicroStrain/Wireless/Commands/LongPing.h"
#include "mscl/MicroStrain/ResponsePattern.h"
#include "mscl/Communication/SerialConnection.h"
#include "mscl/Communication/Connection.h"
#include "mscl/Utils.h"
#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"
#include "mscl/MicroStrain/Wireless/Commands/SetToIdleStatus.h"
#include "mscl/MicroStrain/Wireless/Commands/SetToIdle.h"
#include "mscl/MicroStrain/Wireless/Configuration/WirelessNodeConfig.h"

#include <boost/test/unit_test.hpp>
#include "mock_BaseStation.h"
#include "mock_WirelessNode.h"
using namespace mscl;


BOOST_AUTO_TEST_SUITE(WirelessNode_Test)

BOOST_AUTO_TEST_CASE(WirelessNode_Ping_success)
{
	std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl);
	BaseStation base(impl);
	WirelessNode node(123, base);

	PingResponse r = PingResponse::ResponseSuccess(-20, -30);
	
	//make the BaseStation's node_ping() function return our PingResponse object we created
	MOCK_EXPECT(impl->node_ping).once().returns(r);
	
	PingResponse result = node.ping();

	//check that node.ping() return everything successfully
	BOOST_CHECK_EQUAL(result.baseRssi(), -30);
	BOOST_CHECK_EQUAL(result.nodeRssi(), -20);
	BOOST_CHECK_EQUAL(result.success(), true);
}

BOOST_AUTO_TEST_CASE(WirelessNode_setToIdle_success)
{
	std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl);
	BaseStation base(impl);
	WirelessNode node(123, base);

	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	std::shared_ptr<SetToIdle::Response> response(new SetToIdle::Response(123, rc, base));

	SetToIdleStatus status(response);

	MOCK_EXPECT(impl->node_setToIdle).once().returns(status);

	SetToIdleStatus result = node.setToIdle();

	//a successful stop node response, without the initial 0xAA in the response
	Bytes bytes;
	bytes.push_back(0x90);
	bytes.push_back(0x01);

	DataBuffer buffer(bytes);

	//check that match returns true
	BOOST_CHECK_EQUAL(response->match(buffer), true);
	BOOST_CHECK_EQUAL(result.complete(), true);
	BOOST_CHECK_EQUAL(result.result(), SetToIdleStatus::setToIdleResult_success);
}

BOOST_AUTO_TEST_CASE(WirelessNode_stop_destroyBaseBeforeStopNodeStatus)
{
	std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl);
	BaseStation* base = new BaseStation(impl);
	WirelessNode* node = new WirelessNode(123, *base);

	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	std::shared_ptr<SetToIdle::Response> response(new SetToIdle::Response(123, rc, *base));

	SetToIdleStatus status(response);

	MOCK_EXPECT(impl->node_setToIdle).once().returns(status);

	SetToIdleStatus result = node->setToIdle();

	delete base;
	delete node;

	BOOST_CHECK_EQUAL(result.complete(), false);
	BOOST_CHECK_EQUAL(result.result(), SetToIdleStatus::setToIdleResult_notCompleted);

	MOCK_EXPECT(impl->ping).returns(true);
	BOOST_CHECK_THROW(result.cancel(), Error_Communication);

	try
	{
		result.cancel();
	}
	catch(Error_Communication& ex)
	{
		BOOST_CHECK_EQUAL(ex.what(), "Failed to cancel the Set to Idle operation.");
	}

	//a canceled stop node response, without the initial 0xAA in the response
	Bytes bytes;
	bytes.push_back(0x21);
	bytes.push_back(0x01);

	DataBuffer buffer(bytes);

	//check that match returns true
	BOOST_CHECK_EQUAL(response->match(buffer), true);
}

BOOST_AUTO_TEST_CASE(WirelessNode_readEepromuint16_pageDownload)
{
	std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl);
	BaseStation base(impl);
	WirelessNode node(123, base);

	ByteStream data;
	data.append_uint16(0);	//eeprom 0
	data.append_uint16(0);	//eeprom 2
	data.append_uint16(0);	//eeprom 4
	data.append_uint16(19);	//eeprom 6
	data.append_uint16(45);	//eeprom 8
	data.append_uint16(1);	//eeprom 10

	//force the page download to take our bytestream
	MOCK_EXPECT(impl->node_pageDownload).with(mock::any, mock::any, mock::any, mock::assign(data)).returns(true);

	uint16 result = node.readEeprom(6);

	//check the eeprom result is what we want
	BOOST_CHECK_EQUAL(result, 19);

	result = node.readEeprom(10);	//this shouldnt have to read again, as the original page downloaded should cache it

	//check the eeprom result is again what we want
	BOOST_CHECK_EQUAL(result, 1);
}

BOOST_AUTO_TEST_CASE(WirelessNode_readEepromuint16_read)
{
	std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl);
	BaseStation base(impl);
	WirelessNode node(123, base);

	//force the page download to fail
	MOCK_EXPECT(impl->node_pageDownload).returns(false);

	uint16 eepromVal = 876;

	MOCK_EXPECT(impl->node_readEeprom).once().with(mock::any, mock::any, 108, mock::assign(1)).returns(true);

	//force the read eeprom to return our response
	MOCK_EXPECT(impl->node_readEeprom).once().with(mock::any, mock::any, mock::any, mock::assign(eepromVal)).returns(true);

	uint16 result = node.readEeprom(20);

	//check the eeprom result is what we want
	BOOST_CHECK_EQUAL(result, 876);

	result = node.readEeprom(20);

	//check the eeprom result is again what we want
	BOOST_CHECK_EQUAL(result, 876);
}

BOOST_AUTO_TEST_CASE(WirelessNode_writeEepromuint16)
{
	std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl);
	BaseStation base(impl);
	WirelessNode node(123, base);

	//force the page download to fail
	MOCK_EXPECT(impl->node_pageDownload).returns(false);
	MOCK_EXPECT(impl->node_readEeprom).once().with(mock::any, mock::any, 108, mock::assign(1)).returns(true);

	//force the read eeprom to return our response
	MOCK_EXPECT(impl->node_writeEeprom).once().returns(true);

	BOOST_CHECK_NO_THROW(node.writeEeprom(20, (uint16)5432));

	//check the eeprom result is what we wrote
	uint16 result = node.readEeprom(20);
	BOOST_CHECK_EQUAL(result, 5432);
	
	MOCK_RESET(impl->node_writeEeprom);
	//check that writing the same value to eeprom doesn't throw an exception (uses cache)
	BOOST_CHECK_NO_THROW(node.writeEeprom(20, (uint16)5432));
}

BOOST_AUTO_TEST_CASE(WirelessNode_info)
{
	std::shared_ptr<mock_WirelessNodeImpl_Basic> impl(new mock_WirelessNodeImpl_Basic());
	BaseStation b = makeBaseStationWithMockImpl();
	WirelessNode node(123, b);
	node.setImpl(impl);

	expectReadModel(impl, WirelessModels::node_gLink_2g);
	expectRead(impl, NodeEepromMap::FIRMWARE_VER, Value::UINT16(0x804));
	expectRead(impl, NodeEepromMap::SERIAL_ID, Value(valueType_uint32, (uint32)97854684));
	expectRead(impl, NodeEepromMap::MICROCONTROLLER, Value::UINT16(WirelessTypes::microcontroller_18F452));
	expectRead(impl, NodeEepromMap::RADIO_OPTIONS, Value::UINT16(0xFFFF));

	//get the node info
	BOOST_CHECK_EQUAL(node.firmwareVersion().str(), "8.4.0");
	BOOST_CHECK_EQUAL(node.model(), WirelessModels::node_gLink_2g);
	BOOST_CHECK_EQUAL(node.serial(), "6305-2000-97854684");
	BOOST_CHECK_EQUAL(node.microcontroller(), WirelessTypes::microcontroller_18F452);
	BOOST_CHECK_EQUAL(node.radioFeatures().extendedRange(), false);
}

BOOST_AUTO_TEST_CASE(WirelessNode_info_withSvn)
{
	std::shared_ptr<mock_WirelessNodeImpl_Basic> impl(new mock_WirelessNodeImpl_Basic());
	BaseStation b = makeBaseStationWithMockImpl();
	WirelessNode node(123, b);
	node.setImpl(impl);

	expectReadModel(impl, WirelessModels::node_gLink_2g);
	expectRead(impl, NodeEepromMap::FIRMWARE_VER, Value::UINT16(0x0B15));
	expectRead(impl, NodeEepromMap::FIRMWARE_VER2, Value::UINT16(0xE94B));
	expectRead(impl, NodeEepromMap::SERIAL_ID, Value(valueType_uint32, (uint32)97854684));
	expectRead(impl, NodeEepromMap::MICROCONTROLLER, Value::UINT16(WirelessTypes::microcontroller_18F452));
	expectRead(impl, NodeEepromMap::RADIO_OPTIONS, Value::UINT16(0xFFFF));

	//get the node info
	BOOST_CHECK_EQUAL(node.firmwareVersion().str(), "11.1435979.0");
	BOOST_CHECK_EQUAL(node.model(), WirelessModels::node_gLink_2g);
	BOOST_CHECK_EQUAL(node.serial(), "6305-2000-97854684");
	BOOST_CHECK_EQUAL(node.microcontroller(), WirelessTypes::microcontroller_18F452);
	BOOST_CHECK_EQUAL(node.radioFeatures().extendedRange(), false);
}

BOOST_AUTO_TEST_CASE(WirelessNode_serial_legacy)
{
	std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
	BaseStation b = makeBaseStationWithMockImpl();
	WirelessNode node(123, b);
	node.setImpl(impl);

	expectRead(impl, NodeEepromMap::SERIAL_ID, Value(valueType_uint32, (uint32)0xFFFFFFFF));	//uninitialized serial id
	expectRead(impl, NodeEepromMap::LEGACY_SERIAL_ID, Value::UINT16(6785));
	expectReadModel(impl, WirelessModels::node_gLink_2g);

	BOOST_CHECK_EQUAL(node.serial(), "6305-2000-06785");
}

BOOST_AUTO_TEST_CASE(WirelessNode_model_legacy)
{
	std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
	BaseStation b = makeBaseStationWithMockImpl();
	WirelessNode node(123, b);
	node.setImpl(impl);

	expectRead(impl, NodeEepromMap::MODEL_NUMBER, Value::UINT16(0xAAAA));//uninitialized model #
	expectRead(impl, NodeEepromMap::LEGACY_MODEL_NUMBER, Value::UINT16(2417));

	BOOST_CHECK_EQUAL(node.model(), WirelessModels::node_sgLink);	//63083000
}

BOOST_AUTO_TEST_CASE(WirelessNode_nodeAddress)
{
	BaseStation b = makeBaseStationWithMockImpl();
	WirelessNode node(44651, b);

	BOOST_CHECK_EQUAL(node.nodeAddress(), 44651);
}

BOOST_AUTO_TEST_CASE(WirelessNode_cyclePower)
{
	std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl());
	BaseStation b = makeBaseStationWithMockImpl();
	WirelessNode node(123, b);
	node.setImpl(impl);

	expectCyclePower(impl);

	BOOST_CHECK_NO_THROW(node.cyclePower());
}

BOOST_AUTO_TEST_CASE(WirelessNode_frequency)
{
	std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl);
	BaseStation base(impl);

	//call the create function
	WirelessNode node(123, base);

	//force the page download to fail
	MOCK_EXPECT(impl->node_pageDownload).returns(false);
	MOCK_EXPECT(impl->node_readEeprom).once().with(mock::any, mock::any, 108, mock::assign(1)).returns(true);
	MOCK_EXPECT(impl->node_readEeprom).once().with(mock::any, mock::any, 90, mock::assign(16)).returns(true);

	BOOST_CHECK_EQUAL(node.frequency(), WirelessTypes::freq_16);

	MOCK_EXPECT(impl->node_writeEeprom).once().with(mock::any, 123, 90, mock::any).returns(true);	//change frequency write
	MOCK_EXPECT(impl->node_writeEeprom).once().with(mock::any, 123, 250, mock::any).returns(true);	//cycle power

	//call the changeFrequency function
	node.changeFrequency(WirelessTypes::freq_18);

	BOOST_CHECK_EQUAL(node.frequency(), WirelessTypes::freq_18);

	//try to change again, but fail
	MOCK_EXPECT(impl->node_writeEeprom).once().with(mock::any, 123, 90, mock::any).returns(false);	//change frequency write
	BOOST_CHECK_THROW(node.changeFrequency(WirelessTypes::freq_12), Error_NodeCommunication);
}

BOOST_AUTO_TEST_CASE(WirelessNode_get_and_setBaseStation)
{
	std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl);
	BaseStation base(impl);
	base.baseCommandsTimeout(30000);	//change the timeout to 30 seconds

	//call the create function
	WirelessNode node(123, base);

	BOOST_CHECK(node.getBaseStation().baseCommandsTimeout() == 30000);

	std::shared_ptr<mock_baseStationImpl> impl2(new mock_baseStationImpl);
	BaseStation base2(impl2);
	base2.baseCommandsTimeout(12000);	//change the timeout to 12 seconds

	//call the setBaseStation command
	node.setBaseStation(base2);

	BOOST_CHECK(node.getBaseStation().baseCommandsTimeout() == 12000);
}

/*
BOOST_AUTO_TEST_CASE(WirelessNode_getSampling)
{
	std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
	BaseStation b = makeBaseStationWithMockImpl();
	WirelessNode node(100, b);
	node.setImpl(impl);

	expectGenericNodeFeatures(impl);
	

	MOCK_EXPECT(impl->readEeprom_uint16).once().returns(WirelessTypes::samplingMode_armedDatalog);										//sampling mode
	MOCK_EXPECT(impl->readEeprom_uint16).once().returns(0x017);																			//active channels
	MOCK_EXPECT(impl->readEeprom_uint16).once().with(NodeEepromMap::DATALOG_SAMPLE_RATE.location()).returns(WirelessTypes::sampleRate_32Hz);	//sample rate
	MOCK_EXPECT(impl->readEeprom_uint16).once().returns(40);																			//num sweeps
	MOCK_EXPECT(impl->readEeprom_uint16).once().with(NodeEepromMap::UNLIMITED_DATALOG.location()).returns(0);							//unlimited duration
	MOCK_EXPECT(impl->readEeprom_uint16).once().returns(WirelessTypes::dataFormat_4byte_float);											//data format
	MOCK_EXPECT(impl->readEeprom_uint16).once().returns(WirelessTypes::collectionMethod_logOnly);										//collection mode
	MOCK_EXPECT(impl->readEeprom_uint16).once().returns(100);																			//time between bursts

	SamplingConfig sampling = node.getSamplingConfig();

	//verify that loading from the node sets all the correct values
	BOOST_CHECK_EQUAL(sampling.samplingMode(), WirelessTypes::samplingMode_armedDatalog);
	BOOST_CHECK_EQUAL(sampling.activeChannels().toMask(), 0x17);
	BOOST_CHECK_EQUAL(sampling.sampleRate(), WirelessTypes::sampleRate_32Hz);
	BOOST_CHECK_EQUAL(sampling.numSweeps(), 4000);
	BOOST_CHECK_EQUAL(sampling.unlimitedDuration(), false);
	BOOST_CHECK_EQUAL(sampling.dataFormat(), WirelessTypes::dataFormat_4byte_float);
	BOOST_CHECK_EQUAL(sampling.dataCollectionMethod(), WirelessTypes::collectionMethod_logOnly);
	BOOST_CHECK_EQUAL(sampling.timeBetweenBursts().getSeconds(), 100);
}

BOOST_AUTO_TEST_CASE(NodeConfig_setSampling)
{
	std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
	BaseStation b = makeBaseStationWithMockImpl();
	WirelessNode node(100, b);
	node.setImpl(impl);

	

	SamplingConfig sampling;
	sampling.samplingMode(WirelessTypes::samplingMode_nonSync);
	sampling.sampleRate(WirelessTypes::sampleRate_2Hz);

	NodeInfo info(Version(9, 9), WirelessModels::node_gLink_2g, 200000);

	//make the features() function return the NodeFeatures we want
	std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
	MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

	//we expect the following values to get written
	MOCK_EXPECT(impl->writeEeprom_uint16).once().with(NodeEepromMap::SAMPLING_MODE.location(), WirelessTypes::samplingMode_nonSync);		//sampling mode
	MOCK_EXPECT(impl->writeEeprom_uint16).once().with(NodeEepromMap::ACTIVE_CHANNEL_MASK.location(), 0x01);									//active channels
	MOCK_EXPECT(impl->writeEeprom_uint16).once().with(NodeEepromMap::SAMPLE_RATE.location(), WirelessTypes::sampleRate_2Hz);				//sample rate
	MOCK_EXPECT(impl->writeEeprom_uint16).once().with(NodeEepromMap::NUM_SWEEPS.location(), 10);											//num sweeps
	MOCK_EXPECT(impl->writeEeprom_uint16).once().with(NodeEepromMap::UNLIMITED_SAMPLING.location(), 1);										//unlimited duration
	MOCK_EXPECT(impl->writeEeprom_uint16).once().with(NodeEepromMap::DATA_FORMAT.location(), WirelessTypes::dataFormat_2byte_uint);			//data format
	MOCK_EXPECT(impl->writeEeprom_uint16).once().with(NodeEepromMap::COLLECTION_MODE.location(), WirelessTypes::collectionMethod_transmitOnly);	//collection mode

	BOOST_CHECK_NO_THROW(node.setSamplingConfig(sampling));
}
*/

BOOST_AUTO_TEST_CASE(NodeConfig_getNumDatalogSessions)
{
	std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
	BaseStation b = makeBaseStationWithMockImpl();
	WirelessNode node(100, b);
	node.setImpl(impl);

	std::unique_ptr<NodeFeatures> features;
	expectNodeFeatures(features, impl);

	expectRead(impl, NodeEepromMap::DATA_SETS_STORED, Value::UINT16(12));

	BOOST_CHECK_EQUAL(node.getNumDatalogSessions(), 12);
}

BOOST_AUTO_TEST_CASE(NodeConfig_getBootMode)
{
	std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
	BaseStation b = makeBaseStationWithMockImpl();
	WirelessNode node(100, b);
	node.setImpl(impl);

	std::unique_ptr<NodeFeatures> features;
	expectNodeFeatures(features, impl);
	
	expectRead(impl, NodeEepromMap::DEFAULT_MODE, Value::UINT16(5));

	BOOST_CHECK_EQUAL(node.getDefaultMode(), WirelessTypes::defaultMode_sleep);
}

BOOST_AUTO_TEST_CASE(NodeConfig_setBootMode)
{
	std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
	BaseStation b = makeBaseStationWithMockImpl();
	WirelessNode node(100, b);
	node.setImpl(impl);

	std::unique_ptr<NodeFeatures> features;
	expectNodeFeatures(features, impl);
	
	expectWrite(impl, NodeEepromMap::DEFAULT_MODE, Value::UINT16(6));
	expectCyclePower(impl);

	WirelessNodeConfig c;
	c.defaultMode(WirelessTypes::defaultMode_sync);

	BOOST_CHECK_NO_THROW(node.applyConfig(c));//node.setBootMode(WirelessTypes::bootMode_sync));
}

BOOST_AUTO_TEST_CASE(NodeConfig_getInactivityTimeout)
{
	std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
	BaseStation b = makeBaseStationWithMockImpl();
	WirelessNode node(100, b);
	node.setImpl(impl);

	std::unique_ptr<NodeFeatures> features;
	expectNodeFeatures(features, impl);
	
	expectRead(impl, NodeEepromMap::INACTIVE_TIMEOUT, Value::UINT16(50));

	BOOST_CHECK_EQUAL(node.getInactivityTimeout(), 50);
}

BOOST_AUTO_TEST_CASE(NodeConfig_setInactivityTimeout)
{
	std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
	BaseStation b = makeBaseStationWithMockImpl();
	WirelessNode node(100, b);
	node.setImpl(impl);

	std::unique_ptr<NodeFeatures> features;
	expectNodeFeatures(features, impl);
	
	expectWrite(impl, NodeEepromMap::INACTIVE_TIMEOUT, Value::UINT16(5));	//min of 5
	expectCyclePower(impl);

	uint16 timeout = 2;
	Utils::checkBounds_min(timeout, features->minInactivityTimeout());

	WirelessNodeConfig c;
	c.inactivityTimeout(timeout);

	BOOST_CHECK_NO_THROW(node.applyConfig(c));

	expectWrite(impl, NodeEepromMap::INACTIVE_TIMEOUT, Value::UINT16(400));
	expectCyclePower(impl);

	c.inactivityTimeout(400);

	BOOST_CHECK_NO_THROW(node.applyConfig(c));
}

BOOST_AUTO_TEST_CASE(NodeConfig_getCheckRadioInterval)
{
	std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
	BaseStation b = makeBaseStationWithMockImpl();
	WirelessNode node(100, b);
	node.setImpl(impl);

	std::unique_ptr<NodeFeatures> features;
	expectNodeFeatures(features, impl);

	expectRead(impl, NodeEepromMap::SLEEP_INTERVAL, Value::UINT16(640));

	BOOST_CHECK_EQUAL(node.getCheckRadioInterval(), 12);
}

BOOST_AUTO_TEST_CASE(NodeConfig_getTransmitPower)
{
	std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
	BaseStation b = makeBaseStationWithMockImpl();
	WirelessNode node(100, b);
	node.setImpl(impl);

	std::unique_ptr<NodeFeatures> features;
	expectNodeFeatures(features, impl);
	
	expectRead(impl, NodeEepromMap::TX_POWER_LEVEL, Value::UINT16(25615));

	BOOST_CHECK_EQUAL(node.getTransmitPower(), WirelessTypes::power_10dBm);
}

BOOST_AUTO_TEST_CASE(NodeConfig_setTransmitPower)
{
	std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
	BaseStation b = makeBaseStationWithMockImpl();
	WirelessNode node(100, b);
	node.setImpl(impl);

	std::unique_ptr<NodeFeatures> features;
	expectNodeFeatures(features, impl);

	expectWrite(impl, NodeEepromMap::TX_POWER_LEVEL, Value(valueType_int16, (int16)25619));
	expectCyclePower(impl);

	WirelessNodeConfig c;
	c.transmitPower(WirelessTypes::power_16dBm);

	BOOST_CHECK_NO_THROW(node.applyConfig(c));
}

BOOST_AUTO_TEST_CASE(NodeConfig_getLostBeconTimeout)
{
	std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
	BaseStation b = makeBaseStationWithMockImpl();
	WirelessNode node(100, b);
	node.setImpl(impl);

	std::unique_ptr<NodeFeatures> features;
	expectNodeFeatures(features, impl);

	//tests timeout within range
	{
		expectRead(impl, NodeEepromMap::LOST_BEACON_TIMEOUT, Value::UINT16(26));

		BOOST_CHECK_EQUAL(node.getLostBeaconTimeout(), 26);
	}

	MOCK_RESET(impl->readEeprom);

	//tests timeout disabled
	{
		//a value of 0 should be disabled and able to be returned
		expectRead(impl, NodeEepromMap::LOST_BEACON_TIMEOUT, Value::UINT16(0));
		BOOST_CHECK_EQUAL(node.getLostBeaconTimeout(), 0);

		MOCK_RESET(impl->readEeprom);

		//a value greater than max sets it to disabled (equal to 0)
		expectRead(impl, NodeEepromMap::LOST_BEACON_TIMEOUT, Value::UINT16(743));
		BOOST_CHECK_EQUAL(node.getLostBeaconTimeout(), 0);
	}

	MOCK_RESET(impl->readEeprom);

	//tests timeout below min
	{
		//a value of 1 gets put within range on the node
		expectRead(impl, NodeEepromMap::LOST_BEACON_TIMEOUT, Value::UINT16(1));
		BOOST_CHECK_EQUAL(node.getLostBeaconTimeout(), 2);
	}
}

BOOST_AUTO_TEST_CASE(WirelessNode_getFatigueOptions_legacy)
{
	std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
	BaseStation b = makeBaseStationWithMockImpl();
	WirelessNode node(100, b);
	node.setImpl(impl);

	NodeInfo info(Version(9, 9), WirelessModels::node_shmLink, 0, WirelessTypes::region_usa);

	//make the features() function return the NodeFeatures we want
	std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
	expectNodeFeatures(features, impl, WirelessModels::node_shmLink);

	expectRead(impl, NodeEepromMap::PEAK_VALLEY_THRES, Value::UINT16(82));			//peak/valley
	expectRead(impl, NodeEepromMap::LEGACY_DAMAGE_ANGLE_1, Value::UINT16(45));		//angle 1
	expectRead(impl, NodeEepromMap::LEGACY_DAMAGE_ANGLE_2, Value::UINT16(51));		//angle 2
	expectRead(impl, NodeEepromMap::LEGACY_DAMAGE_ANGLE_3, Value::UINT16(39));		//angle 3
	expectRead(impl, NodeEepromMap::SNCURVE_LOGA_1, Value::FLOAT(1.234f));			//sn curve segment 1 - loga
	expectRead(impl, NodeEepromMap::SNCURVE_M_1, Value::FLOAT(5.6f));				//sn curve segment 1 - m
	expectRead(impl, NodeEepromMap::SNCURVE_LOGA_2, Value::FLOAT(0.875f));			//sn curve segment 2 - loga
	expectRead(impl, NodeEepromMap::SNCURVE_M_2, Value::FLOAT(0.9f));				//sn curve segment 2 - m

	auto fatigue = node.getFatigueOptions();

	BOOST_CHECK_EQUAL(fatigue.peakValleyThreshold(), 82);
	BOOST_CHECK_EQUAL(fatigue.damageAngles().size(), 3);
	BOOST_CHECK_CLOSE(fatigue.damageAngle(0), 45.0, 0.1);
	BOOST_CHECK_CLOSE(fatigue.damageAngle(1), 51.0, 0.1);
	BOOST_CHECK_CLOSE(fatigue.damageAngle(2), 39.0, 0.1);
	BOOST_CHECK_CLOSE(fatigue.poissonsRatio(), 0.3, 0.1);		//default value
	BOOST_CHECK_CLOSE(fatigue.youngsModulus(), 0.2025, 0.1);	//default value
	BOOST_CHECK_EQUAL(fatigue.snCurveSegments().size(), 2);
	BOOST_CHECK_CLOSE(fatigue.snCurveSegment(0).logA(), 1.234, 0.1);
	BOOST_CHECK_CLOSE(fatigue.snCurveSegment(0).m(), 5.6, 0.1);
	BOOST_CHECK_CLOSE(fatigue.snCurveSegment(1).logA(), 0.875, 0.1);
	BOOST_CHECK_CLOSE(fatigue.snCurveSegment(1).m(), 0.9, 0.1);

	fatigue.damageAngle(0, 370.0f);
	BOOST_CHECK_CLOSE(fatigue.damageAngle(0), 10.0, 0.1);

	fatigue.damageAngle(1, 1475.743f);
	BOOST_CHECK_CLOSE(fatigue.damageAngle(1), 35.743, 0.1);

	fatigue.damageAngle(2, -10.4f);
	BOOST_CHECK_CLOSE(fatigue.damageAngle(2), 349.6, 0.1);
}

BOOST_AUTO_TEST_CASE(WirelessNode_getFatigueOptions)
{
	std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
	BaseStation b = makeBaseStationWithMockImpl();
	WirelessNode node(100, b);
	node.setImpl(impl);

	NodeInfo info(Version(10, 9), WirelessModels::node_shmLink2, 0, WirelessTypes::region_usa);

	//make the features() function return the NodeFeatures we want
	std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
	expectNodeFeatures(features, impl, WirelessModels::node_shmLink2);

	expectRead(impl, NodeEepromMap::PEAK_VALLEY_THRES, Value::UINT16(64318));		//peak/valley
	expectRead(impl, NodeEepromMap::YOUNGS_MODULUS, Value::FLOAT(123.5f));			//youngs modulus
	expectRead(impl, NodeEepromMap::POISSONS_RATIO, Value::FLOAT(943.12f));			//poissons ratio
	expectRead(impl, NodeEepromMap::HISTOGRAM_RAW_FLAG, Value::UINT16(1));			//youngs modulus
	expectRead(impl, NodeEepromMap::DAMAGE_ANGLE_1, Value::UINT16(45));				//angle 1
	expectRead(impl, NodeEepromMap::DAMAGE_ANGLE_2, Value::UINT16(51));				//angle 2
	expectRead(impl, NodeEepromMap::DAMAGE_ANGLE_3, Value::UINT16(39));				//angle 3
	expectRead(impl, NodeEepromMap::SNCURVE_LOGA_1, Value::FLOAT(1.234f));			//sn curve segment 1 - loga
	expectRead(impl, NodeEepromMap::SNCURVE_M_1, Value::FLOAT(5.6f));				//sn curve segment 1 - m
	expectRead(impl, NodeEepromMap::SNCURVE_LOGA_2, Value::FLOAT(0.875f));			//sn curve segment 2 - loga
	expectRead(impl, NodeEepromMap::SNCURVE_M_2, Value::FLOAT(0.9f));				//sn curve segment 2 - m
	expectRead(impl, NodeEepromMap::SNCURVE_LOGA_3, Value::FLOAT(0.7f));			//sn curve segment 3 - loga
	expectRead(impl, NodeEepromMap::SNCURVE_M_3, Value::FLOAT(0.002f));				//sn curve segment 3 - m
	expectRead(impl, NodeEepromMap::FATIGUE_MODE, Value::UINT16(1));				//fatigue mode
	expectRead(impl, NodeEepromMap::DIST_ANGLE_NUM_ANGLES, Value::UINT16(6));		//dist angle mode num angles
	expectRead(impl, NodeEepromMap::DIST_ANGLE_LOWER_BOUND, Value::FLOAT(2.456f));	//dist angle mode lower bound
	expectRead(impl, NodeEepromMap::DIST_ANGLE_UPPER_BOUND, Value::FLOAT(10.412f));	//dist angle mode upper bound
	expectRead(impl, NodeEepromMap::HISTOGRAM_ENABLE, Value::UINT16(1));			//histogram enable

	auto fatigue = node.getFatigueOptions();

	BOOST_CHECK_EQUAL(fatigue.peakValleyThreshold(), 64318);
	BOOST_CHECK_EQUAL(fatigue.damageAngles().size(), 3);
	BOOST_CHECK_CLOSE(fatigue.damageAngle(0), 45.0, 0.1);
	BOOST_CHECK_CLOSE(fatigue.damageAngle(1), 51.0, 0.1);
	BOOST_CHECK_CLOSE(fatigue.damageAngle(2), 39.0, 0.1);
	BOOST_CHECK_CLOSE(fatigue.poissonsRatio(), 943.12, 0.1);
	BOOST_CHECK_CLOSE(fatigue.youngsModulus(), 123.5, 0.1);
	BOOST_CHECK_EQUAL(fatigue.snCurveSegments().size(), 3);
	BOOST_CHECK_CLOSE(fatigue.snCurveSegment(0).logA(), 1.234, 0.1);
	BOOST_CHECK_CLOSE(fatigue.snCurveSegment(0).m(), 5.6, 0.1);
	BOOST_CHECK_CLOSE(fatigue.snCurveSegment(1).logA(), 0.875, 0.1);
	BOOST_CHECK_CLOSE(fatigue.snCurveSegment(1).m(), 0.9, 0.1);
	BOOST_CHECK_CLOSE(fatigue.snCurveSegment(2).logA(), 0.7, 0.1);
	BOOST_CHECK_CLOSE(fatigue.snCurveSegment(2).m(), 0.002, 0.1);
	BOOST_CHECK_EQUAL(fatigue.fatigueMode(), WirelessTypes::fatigueMode_distributedAngle);
	BOOST_CHECK_EQUAL(fatigue.distributedAngleMode_numAngles(), 6);
	BOOST_CHECK_CLOSE(fatigue.distributedAngleMode_lowerBound(), 2.456, 0.1);
	BOOST_CHECK_CLOSE(fatigue.distributedAngleMode_upperBound(), 10.412, 0.1);
	BOOST_CHECK_EQUAL(fatigue.histogramEnable(), true);
}

BOOST_AUTO_TEST_CASE(WirelessNode_getHistogramOptions_legacy)
{
	std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
	BaseStation b = makeBaseStationWithMockImpl();
	WirelessNode node(100, b);
	node.setImpl(impl);

	NodeInfo info(Version(9, 9), WirelessModels::node_shmLink, 0, WirelessTypes::region_usa);

	//make the features() function return the NodeFeatures we want
	std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
	expectNodeFeatures(features, impl, WirelessModels::node_shmLink);

	expectRead(impl, NodeEepromMap::BIN_START, Value::UINT16(10));		//bin start
	expectRead(impl, NodeEepromMap::BIN_SIZE, Value::UINT16(5));		//bin size

	auto hist = node.getHistogramOptions();

	BOOST_CHECK_EQUAL(hist.binsStart(), 10);
	BOOST_CHECK_EQUAL(hist.binsSize(), 5);
	BOOST_CHECK_EQUAL(hist.transmitRate(), WirelessTypes::sampleRate_30Sec);	//default value
}

BOOST_AUTO_TEST_CASE(WirelessNode_getHistogramOptions)
{
	std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
	BaseStation b = makeBaseStationWithMockImpl();
	WirelessNode node(100, b);
	node.setImpl(impl);

	NodeInfo info(Version(9, 9), WirelessModels::node_shmLink2, 0, WirelessTypes::region_usa);

	//make the features() function return the NodeFeatures we want
	std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
	expectNodeFeatures(features, impl, WirelessModels::node_shmLink2);

	expectRead(impl, NodeEepromMap::HISTOGRAM_SAMPLE_RATE, Value::UINT16(118));		//histogram rate
	expectRead(impl, NodeEepromMap::BIN_START, Value::UINT16(12));		//bin start
	expectRead(impl, NodeEepromMap::BIN_SIZE, Value::UINT16(7));		//bin size

	auto hist = node.getHistogramOptions();

	BOOST_CHECK_EQUAL(hist.binsStart(), 12);
	BOOST_CHECK_EQUAL(hist.binsSize(), 7);
	BOOST_CHECK_EQUAL(hist.transmitRate(), WirelessTypes::sampleRate_1Min);	//default value
}

BOOST_AUTO_TEST_CASE(WirelessNode_clearHistogram)
{
	std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
	BaseStation b = makeBaseStationWithMockImpl();
	WirelessNode node(100, b);
	node.setImpl(impl);

	NodeInfo info(Version(9, 9), WirelessModels::node_shmLink2, 0, WirelessTypes::region_usa);

	//make the features() function return the NodeFeatures we want
	std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
	expectNodeFeatures(features, impl, WirelessModels::node_shmLink2);

	expectCyclePower(impl);
	expectWrite(impl, NodeEepromMap::RESET_BINS, Value::UINT16(1));

	BOOST_CHECK_NO_THROW(node.clearHistogram());
}

BOOST_AUTO_TEST_CASE(WirelessNode_erase)
{
	std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl);
	BaseStation base(impl);
	WirelessNode node(123, base);

	MOCK_EXPECT(impl->node_erase).once().returns(true);

	BOOST_CHECK_NO_THROW(node.erase());

	MOCK_EXPECT(impl->node_erase).once().returns(false);

	BOOST_CHECK_THROW(node.erase(), Error_NodeCommunication);
}

BOOST_AUTO_TEST_SUITE_END()