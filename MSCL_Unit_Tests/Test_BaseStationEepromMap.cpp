/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Configuration/BaseStationEepromMap.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(BaseStationEepromMap_Test)

BOOST_AUTO_TEST_CASE(BaseStationEepromMap_getEepromLocation)
{
    BOOST_CHECK_EQUAL(BaseStationEepromMap::FREQUENCY.location(), 90);
}

BOOST_AUTO_TEST_CASE(BaseStationEepromMap_analogEeproms)
{
    EepromLocation analog1 = BaseStationEepromMap::analogNodeAddressEeprom(1);
    EepromLocation analog2 = BaseStationEepromMap::analogNodeChannelEeprom(2);
    EepromLocation analog4 = BaseStationEepromMap::analogMinFloatEeprom(4);
    EepromLocation analog8 = BaseStationEepromMap::analogMaxFloatEeprom(8);

    BOOST_CHECK_EQUAL(analog1.id(), BaseStationEepromMap::ANALOG_1_NODE_ADDRESS.id());
    BOOST_CHECK_EQUAL(analog1.location(), BaseStationEepromMap::ANALOG_1_NODE_ADDRESS.location());
    BOOST_CHECK_EQUAL(analog1.valueType(), BaseStationEepromMap::ANALOG_1_NODE_ADDRESS.valueType());

    BOOST_CHECK_EQUAL(analog2.id(), BaseStationEepromMap::ANALOG_2_NODE_CHANNEL.id());
    BOOST_CHECK_EQUAL(analog2.location(), BaseStationEepromMap::ANALOG_2_NODE_CHANNEL.location());
    BOOST_CHECK_EQUAL(analog2.valueType(), BaseStationEepromMap::ANALOG_2_NODE_CHANNEL.valueType());

    BOOST_CHECK_EQUAL(analog4.id(), BaseStationEepromMap::ANALOG_4_FLOAT_MIN.id());
    BOOST_CHECK_EQUAL(analog4.location(), BaseStationEepromMap::ANALOG_4_FLOAT_MIN.location());
    BOOST_CHECK_EQUAL(analog4.valueType(), BaseStationEepromMap::ANALOG_4_FLOAT_MIN.valueType());

    BOOST_CHECK_EQUAL(analog8.id(), BaseStationEepromMap::ANALOG_8_FLOAT_MAX.id());
    BOOST_CHECK_EQUAL(analog8.location(), BaseStationEepromMap::ANALOG_8_FLOAT_MAX.location());
    BOOST_CHECK_EQUAL(analog8.valueType(), BaseStationEepromMap::ANALOG_8_FLOAT_MAX.valueType());
}

BOOST_AUTO_TEST_SUITE_END()
