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

	expectRead(impl, BaseStationEepromMap::TX_POWER_LEVEL, Value::UINT16(WirelessTypes::power_10dBm));

	BaseStationEepromHelper c(base.eepromHelper());

	BOOST_CHECK_EQUAL(c.read_transmitPower(), WirelessTypes::power_10dBm);
}

BOOST_AUTO_TEST_CASE(BaseStationEepromHelper_writeTransmitPower)
{
	std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl());
	BaseStation base(impl);

	expectWrite(impl, BaseStationEepromMap::TX_POWER_LEVEL, Value::UINT16(WirelessTypes::power_16dBm));

	BOOST_CHECK_NO_THROW(base.eepromHelper().write_transmitPower(WirelessTypes::power_16dBm));
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