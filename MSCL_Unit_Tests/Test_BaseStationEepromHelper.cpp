/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include <boost/test/unit_test.hpp>
#include "mscl/MicroStrain/Wireless/Configuration/BaseStationEepromHelper.h"
#include "mscl/MicroStrain/Wireless/Configuration/BaseStationEepromMap.h"
#include "mscl/MicroStrain/Wireless/BaseStation.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"
#include "mock_BaseStation.h"
using namespace mscl;


BOOST_AUTO_TEST_SUITE(BaseStationEepromHelper_Test)

BOOST_AUTO_TEST_CASE(BaseStationEepromHelper_readTransmitPower)
{
    std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl());
    BaseStation base(impl);

    //make the features() function return the BaseStationFeatures we want
    /*WirelessProtocol p = *(WirelessProtocol::getProtocol(Version(1, 7)).get());
    WirelessProtocol p2 = *(WirelessProtocol::getProtocol(Version(3, 0)).get());
    BaseStationInfo info(Version(9, 9), WirelessModels::base_wsdaBase_104_usb, WirelessTypes::region_usa, p, p2);

    std::unique_ptr<BaseStationFeatures> features = BaseStationFeatures::create(info);

    MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));*/

    std::unique_ptr<BaseStationFeatures> features;
    expectBaseFeatures(features, impl);

    expectRead(impl, BaseStationEepromMap::TX_POWER_LEVEL, Value(valueType_int16, (int16)WirelessTypes::power_10dBm));

    BaseStationEepromHelper c(base.eepromHelper());

    BOOST_CHECK_EQUAL(c.read_transmitPower(), WirelessTypes::power_10dBm);
}

BOOST_AUTO_TEST_CASE(BaseStationEepromHelper_readTransmitPower_legacy)
{
    std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl());
    BaseStation base(impl);

    //make the features() function return the BaseStationFeatures we want
    std::unique_ptr<BaseStationFeatures> features;
    //3.2 fw doesn't support the new transmit power values
    Version asppVer_lxrs(1, 0);
    Version asppVer_lxrsPlus(3, 0);
    BaseStationInfo info(Version(3, 2), WirelessModels::base_wsdaBase_104_usb, WirelessTypes::region_usa, asppVer_lxrs, asppVer_lxrsPlus);
    features = BaseStationFeatures::create(info);
    MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

    expectRead(impl, BaseStationEepromMap::TX_POWER_LEVEL, Value(valueType_int16, (int16)WirelessTypes::legacyPower_0dBm));

    BaseStationEepromHelper c(base.eepromHelper());

    BOOST_CHECK_EQUAL(c.read_transmitPower(), WirelessTypes::power_0dBm);
}

BOOST_AUTO_TEST_CASE(BaseStationEepromHelper_writeTransmitPower)
{
    std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl());
    BaseStation base(impl);

    //make the features() function return the BaseStationFeatures we want
    std::unique_ptr<BaseStationFeatures> features;
    expectBaseFeatures(features, impl);

    expectWrite(impl, BaseStationEepromMap::TX_POWER_LEVEL, Value(valueType_int16, (int16)WirelessTypes::power_16dBm));

    BOOST_CHECK_NO_THROW(base.eepromHelper().write_transmitPower(WirelessTypes::power_16dBm));
}

BOOST_AUTO_TEST_CASE(BaseStationEepromHelper_writeTransmitPower_legacy)
{
    std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl());
    BaseStation base(impl);

    //make the features() function return the BaseStationFeatures we want
    std::unique_ptr<BaseStationFeatures> features;
    //3.2 fw doesn't support the new transmit power values
    Version asppVer_lxrs(1, 0);
    Version asppVer_lxrsPlus(3, 0);
    BaseStationInfo info(Version(3, 2), WirelessModels::base_wsdaBase_104_usb, WirelessTypes::region_usa, asppVer_lxrs, asppVer_lxrsPlus);
    features = BaseStationFeatures::create(info);
    MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));

    expectWrite(impl, BaseStationEepromMap::TX_POWER_LEVEL, Value(valueType_int16, (int16)WirelessTypes::legacyPower_10dBm));

    BOOST_CHECK_NO_THROW(base.eepromHelper().write_transmitPower(WirelessTypes::power_10dBm));
}

BOOST_AUTO_TEST_CASE(BaseStationEepromHelper_readButton)
{
    std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl());
    BaseStation base(impl);

    //make the features() function return the BaseStationFeatures we want
    std::unique_ptr<BaseStationFeatures> features;
    expectBaseFeatures(features, impl, WirelessModels::base_wsdaBase_101_analog);

    expectRead(impl, BaseStationEepromMap::BUTTON1_SHORT_FUNC, Value::UINT16(BaseStationButton::btn_enableBeacon));
    expectRead(impl, BaseStationEepromMap::BUTTON1_SHORT_NODE, Value::UINT16(78));

    BaseStationEepromHelper c(base.eepromHelper());

    BaseStationButton result = c.read_button(1, BaseStationButton::action_shortPress);
    BOOST_CHECK_EQUAL(result.command(), BaseStationButton::btn_enableBeacon);
    BOOST_CHECK_EQUAL(result.nodeAddress(), 78);
}

BOOST_AUTO_TEST_CASE(BaseStationEepromHelper_writeButton)
{
    std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl());
    BaseStation base(impl);

    //make the features() function return the BaseStationFeatures we want
    std::unique_ptr<BaseStationFeatures> features;
    expectBaseFeatures(features, impl, WirelessModels::base_wsdaBase_101_analog);

    expectWrite(impl, BaseStationEepromMap::BUTTON2_LONG_FUNC, Value::UINT16(BaseStationButton::btn_nodeArmedDatalogging));
    expectWrite(impl, BaseStationEepromMap::BUTTON2_LONG_NODE, Value::UINT16(31568));

    BaseStationButton btn(BaseStationButton::btn_nodeArmedDatalogging, 31568);
    BOOST_CHECK_NO_THROW(base.eepromHelper().write_button(2, BaseStationButton::action_longPress, btn));
}

BOOST_AUTO_TEST_SUITE_END()