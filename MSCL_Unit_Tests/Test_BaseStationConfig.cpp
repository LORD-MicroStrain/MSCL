/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Wireless/Configuration/BaseStationConfig.h"
#include "mscl/MicroStrain/Wireless/Configuration/BaseStationEepromMap.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"
#include "mscl/MicroStrain/Wireless/BaseStation.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>
#include "mock_BaseStation.h"
using namespace mscl;

BOOST_AUTO_TEST_SUITE(BaseStationConfig_Test)

BOOST_AUTO_TEST_CASE(BaseStationConfig_Constructor)
{
    //Tests that a blank BaseStationConfig throws exceptions when trying to access any options

    BaseStationConfig c;

    //verify that a blank config throws exceptions (noting has been set)
    BOOST_CHECK_THROW(c.transmitPower(), Error_NoData);
    BOOST_CHECK_THROW(c.buttonLongPress(1), Error_NoData);
}

BOOST_AUTO_TEST_CASE(BaseStationConfig_SetAndGet)
{
    //Tests that setting an option in the BaseStationConfig allows that option to then be retrieved

    BaseStationConfig c;

    BaseStationButton b1(BaseStationButton::btn_nodeArmedDatalogging, 154);

    //set and get boot mode
    c.transmitPower(WirelessTypes::power_10dBm);
    c.buttonLongPress(1, b1);
    BOOST_CHECK_EQUAL(c.transmitPower(), WirelessTypes::power_10dBm);
    
    BaseStationButton b1Copy = c.buttonLongPress(1);
    BOOST_CHECK_EQUAL(b1Copy.command(), b1.command());
    BOOST_CHECK_EQUAL(b1Copy.nodeAddress(), b1.nodeAddress());
}

BOOST_AUTO_TEST_CASE(BaseStationConfig_setSingleValue)
{
    //Tests setting a single value in the config and writing it to a BaseStation
    std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl());
    BaseStation b(impl);

    //make the features() function return the BaseStationFeatures we want
    std::unique_ptr<BaseStationFeatures> features;
    expectBaseFeatures(features, impl);

    BaseStationConfig c;
    c.transmitPower(WirelessTypes::power_10dBm);

    //expect the single eeprom write
    expectWrite(impl, BaseStationEepromMap::TX_POWER_LEVEL, Value(valueType_int16, (int16)WirelessTypes::power_10dBm));
    expectResetRadio(impl);

    BOOST_CHECK_NO_THROW(b.applyConfig(c));
}

BOOST_AUTO_TEST_CASE(BaseStationConfig_buttons)
{
    //Tests setting button configurations
    std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl());
    BaseStation b(impl);

    //make the features() function return the BaseStationFeatures we want
    std::unique_ptr<BaseStationFeatures> features;
    expectBaseFeatures(features, impl, WirelessModels::base_wsdaBase_101_analog);

    BaseStationButton button(BaseStationButton::btn_nodeSleep, 9354);

    BaseStationConfig c;
    c.buttonShortPress(1, button);
    button.command(BaseStationButton::btn_disableBeacon);
    c.buttonLongPress(2, button);

    //expect the eeprom writes
    expectWrite(impl, BaseStationEepromMap::BUTTON1_SHORT_FUNC, Value::UINT16(BaseStationButton::btn_nodeSleep));
    expectWrite(impl, BaseStationEepromMap::BUTTON1_SHORT_NODE, Value::UINT16(9354));
    expectWrite(impl, BaseStationEepromMap::BUTTON2_LONG_FUNC, Value::UINT16(BaseStationButton::btn_disableBeacon));
    expectWrite(impl, BaseStationEepromMap::BUTTON2_LONG_NODE, Value::UINT16(9354));
    expectResetRadio(impl);

    BOOST_CHECK_NO_THROW(b.applyConfig(c));
}

BOOST_AUTO_TEST_CASE(BaseStationConfig_buttons_failVerify)
{
    //Tests setting button configurations
    std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl());
    BaseStation b(impl);

    //make the features() function return the BaseStationFeatures we want
    std::unique_ptr<BaseStationFeatures> features;
    expectBaseFeatures(features, impl, WirelessModels::base_wsdaBase_104_usb);

    BaseStationButton button(BaseStationButton::btn_nodeSleep, 9354);

    BaseStationConfig c;
    c.buttonShortPress(1, button);
    button.command(BaseStationButton::btn_disableBeacon);
    c.buttonLongPress(2, button);

    BOOST_CHECK_THROW(b.applyConfig(c), Error_InvalidConfig);

    //check that verify fails with the correct issue
    ConfigIssues issues;
    BOOST_CHECK_EQUAL(b.verifyConfig(c, issues), false);
    BOOST_CHECK_EQUAL(issues.size(), 1);
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_BUTTON);
}

BOOST_AUTO_TEST_CASE(BaseStationConfig_buttons_failVerifyButtonNumber)
{
    //Tests setting button configurations
    std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl());
    BaseStation b(impl);

    //make the features() function return the BaseStationFeatures we want
    std::unique_ptr<BaseStationFeatures> features;
    expectBaseFeatures(features, impl, WirelessModels::base_wsdaBase_101_analog);

    BaseStationButton button(BaseStationButton::btn_nodeSleep, 9354);

    BaseStationConfig c;
    c.buttonLongPress(6, button);
    c.buttonShortPress(4, button);

    //check that verify fails with the correct issue
    ConfigIssues issues;
    BOOST_CHECK_EQUAL(b.verifyConfig(c, issues), false);
    BOOST_CHECK_EQUAL(issues.size(), 2);
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_BUTTON);
    BOOST_CHECK_EQUAL(issues.at(0).description(), "Button 6 is not supported by this BaseStation.");
    BOOST_CHECK_EQUAL(issues.at(1).id(), ConfigIssue::CONFIG_BUTTON);
    BOOST_CHECK_EQUAL(issues.at(1).description(), "Button 4 is not supported by this BaseStation.");
}

BOOST_AUTO_TEST_CASE(BaseStationConfig_analogPairing)
{
    //Tests setting button analog pairing options
    std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl());
    BaseStation b(impl);

    //make the features() function return the BaseStationFeatures we want
    std::unique_ptr<BaseStationFeatures> features;
    expectBaseFeatures(features, impl, WirelessModels::base_wsdaBase_101_analog);

    BaseStationConfig c;
    c.analogPairingEnable(true);
    c.analogExceedanceEnable(false);
    c.analogTimeoutTime(60);
    c.analogTimeoutVoltage(45.942f);

    //expect the eeprom writes

    expectWrite(impl, BaseStationEepromMap::ANALOG_PAIRING_ENABLE, Value::UINT16(1));
    expectWrite(impl, BaseStationEepromMap::ANALOG_EXCEED_ENABLE, Value::UINT16(0));
    expectWrite(impl, BaseStationEepromMap::ANALOG_TIMEOUT_TIME, Value::UINT16(60));
    expectWrite(impl, BaseStationEepromMap::ANALOG_TIMEOUT_VOLTAGE, Value::FLOAT(45.942f));
    expectResetRadio(impl);

    BOOST_CHECK_NO_THROW(b.applyConfig(c));
}

BOOST_AUTO_TEST_CASE(BaseStationConfig_analogPairing_fail)
{
    //Tests setting button analog pairing options
    std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl());
    BaseStation b(impl);

    //make the features() function return the BaseStationFeatures we want
    std::unique_ptr<BaseStationFeatures> features;
    expectBaseFeatures(features, impl, WirelessModels::base_wsdaBase_104_usb);

    BaseStationConfig c;
    c.analogPairingEnable(false);
    c.analogExceedanceEnable(false);

    BOOST_CHECK_THROW(b.applyConfig(c), Error_InvalidConfig);

    //check that verify fails with the correct issue
    ConfigIssues issues;
    BOOST_CHECK_EQUAL(b.verifyConfig(c, issues), false);
    BOOST_CHECK_EQUAL(issues.size(), 1);
    BOOST_CHECK_EQUAL(issues.at(0).id(), ConfigIssue::CONFIG_ANALOG_PAIR);
}

BOOST_AUTO_TEST_CASE(BaseStationConfig_legacyTransmitPower)
{
    //Tests setting a single value in the config and writing it to a BaseStation
    std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl());
    BaseStation b(impl);

    std::unique_ptr<BaseStationFeatures> features;
    
    //3.2 fw doesn't support the new transmit power values
    BaseStationInfo info(Version(3, 2), WirelessModels::base_wsdaBase_104_usb, WirelessTypes::region_usa);
    features = BaseStationFeatures::create(info);
    MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

    BaseStationConfig c;
    c.transmitPower(WirelessTypes::power_10dBm);

    //expect the single eeprom write
    expectWrite(impl, BaseStationEepromMap::TX_POWER_LEVEL, Value(valueType_int16, (int16)WirelessTypes::legacyPower_10dBm));
    expectRead(impl, BaseStationEepromMap::ASPP_VER, Value::UINT16((0)));
    expectRead(impl, BaseStationEepromMap::FIRMWARE_VER, Value::UINT16((uint16)(3)));
    expectRead(impl, BaseStationEepromMap::FIRMWARE_VER2, Value::UINT16((uint16)(2)));
    expectCyclePower(impl);

    BOOST_CHECK_NO_THROW(b.applyConfig(c));
}

BOOST_AUTO_TEST_SUITE_END()