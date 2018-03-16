/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(NodeEepromMap_Test)

BOOST_AUTO_TEST_CASE(NodeEepromMap_canUseCache)
{
    BOOST_CHECK_EQUAL(NodeEepromMap::canUseCache_read(NodeEepromMap::RESET_COUNTER.location()), false);
    BOOST_CHECK_EQUAL(NodeEepromMap::canUseCache_read(NodeEepromMap::CURRENT_PAGE_OFFSET.location()), false);
    BOOST_CHECK_EQUAL(NodeEepromMap::canUseCache_read(NodeEepromMap::FILTER_1.location()), true);
    BOOST_CHECK_EQUAL(NodeEepromMap::canUseCache_write(NodeEepromMap::CYCLE_POWER.location()), false);
    BOOST_CHECK_EQUAL(NodeEepromMap::canUseCache_write(NodeEepromMap::CH_ACTION_ID_3.location()), true);
}

BOOST_AUTO_TEST_CASE(NodeEepromMap_getEepromLocation)
{
    BOOST_CHECK_EQUAL(NodeEepromMap::DEFAULT_MODE.location(), 18);
}

BOOST_AUTO_TEST_CASE(NodeEepromMap_getOffsetEeprom)
{
    EepromLocation offset1 = NodeEepromMap::getOffsetEeprom(NodeEepromMap::CH_ACTION_SLOPE_1);
    EepromLocation offset3 = NodeEepromMap::getOffsetEeprom(NodeEepromMap::CH_ACTION_SLOPE_3);
    EepromLocation offset4 = NodeEepromMap::getOffsetEeprom(NodeEepromMap::CH_ACTION_SLOPE_4);
    EepromLocation offset7 = NodeEepromMap::getOffsetEeprom(NodeEepromMap::CH_ACTION_SLOPE_7);

    BOOST_CHECK_EQUAL(offset1.id(), NodeEepromMap::CH_ACTION_OFFSET_1.id());
    BOOST_CHECK_EQUAL(offset1.location(), NodeEepromMap::CH_ACTION_OFFSET_1.location());
    BOOST_CHECK_EQUAL(offset1.valueType(), NodeEepromMap::CH_ACTION_OFFSET_1.valueType());

    BOOST_CHECK_EQUAL(offset3.id(), NodeEepromMap::CH_ACTION_OFFSET_3.id());
    BOOST_CHECK_EQUAL(offset3.location(), NodeEepromMap::CH_ACTION_OFFSET_3.location());
    BOOST_CHECK_EQUAL(offset3.valueType(), NodeEepromMap::CH_ACTION_OFFSET_3.valueType());

    BOOST_CHECK_EQUAL(offset4.id(), NodeEepromMap::CH_ACTION_OFFSET_4.id());
    BOOST_CHECK_EQUAL(offset4.location(), NodeEepromMap::CH_ACTION_OFFSET_4.location());
    BOOST_CHECK_EQUAL(offset4.valueType(), NodeEepromMap::CH_ACTION_OFFSET_4.valueType());

    BOOST_CHECK_EQUAL(offset7.id(), NodeEepromMap::CH_ACTION_OFFSET_7.id());
    BOOST_CHECK_EQUAL(offset7.location(), NodeEepromMap::CH_ACTION_OFFSET_7.location());
    BOOST_CHECK_EQUAL(offset7.valueType(), NodeEepromMap::CH_ACTION_OFFSET_7.valueType());
}

BOOST_AUTO_TEST_CASE(NodeEepromMap_getEventTriggerEeproms_uint16Legacy)
{
    EepromLocation ch = NodeEepromMap::EVENT_SRC_1;
    EepromLocation type = NodeEepromMap::EVENT_OPER_1;
    EepromLocation val = NodeEepromMap::EVENT_VAL1_1;

    //Trigger 3
    NodeEepromMap::getEventTriggerEeproms(2, false, ch, type, val);
    BOOST_CHECK_EQUAL(ch.id(), NodeEepromMap::EVENT_SRC_3.id());
    BOOST_CHECK_EQUAL(ch.location(), NodeEepromMap::EVENT_SRC_3.location());
    BOOST_CHECK_EQUAL(ch.valueType(), NodeEepromMap::EVENT_SRC_3.valueType());
    BOOST_CHECK_EQUAL(type.id(), NodeEepromMap::EVENT_OPER_3.id());
    BOOST_CHECK_EQUAL(type.location(), NodeEepromMap::EVENT_OPER_3.location());
    BOOST_CHECK_EQUAL(type.valueType(), NodeEepromMap::EVENT_OPER_3.valueType());
    BOOST_CHECK_EQUAL(val.id(), NodeEepromMap::EVENT_VAL1_3.id());
    BOOST_CHECK_EQUAL(val.location(), NodeEepromMap::EVENT_VAL1_3.location());
    BOOST_CHECK_EQUAL(val.valueType(), NodeEepromMap::EVENT_VAL1_3.valueType());

    //Trigger 1
    NodeEepromMap::getEventTriggerEeproms(0, false, ch, type, val);
    BOOST_CHECK_EQUAL(ch.id(), NodeEepromMap::EVENT_SRC_1.id());
    BOOST_CHECK_EQUAL(ch.location(), NodeEepromMap::EVENT_SRC_1.location());
    BOOST_CHECK_EQUAL(ch.valueType(), NodeEepromMap::EVENT_SRC_1.valueType());
    BOOST_CHECK_EQUAL(type.id(), NodeEepromMap::EVENT_OPER_1.id());
    BOOST_CHECK_EQUAL(type.location(), NodeEepromMap::EVENT_OPER_1.location());
    BOOST_CHECK_EQUAL(type.valueType(), NodeEepromMap::EVENT_OPER_1.valueType());
    BOOST_CHECK_EQUAL(val.id(), NodeEepromMap::EVENT_VAL1_1.id());
    BOOST_CHECK_EQUAL(val.location(), NodeEepromMap::EVENT_VAL1_1.location());
    BOOST_CHECK_EQUAL(val.valueType(), NodeEepromMap::EVENT_VAL1_1.valueType());

    //Trigger 7
    NodeEepromMap::getEventTriggerEeproms(6, false, ch, type, val);
    BOOST_CHECK_EQUAL(ch.id(), NodeEepromMap::EVENT_SRC_7.id());
    BOOST_CHECK_EQUAL(ch.location(), NodeEepromMap::EVENT_SRC_7.location());
    BOOST_CHECK_EQUAL(ch.valueType(), NodeEepromMap::EVENT_SRC_7.valueType());
    BOOST_CHECK_EQUAL(type.id(), NodeEepromMap::EVENT_OPER_7.id());
    BOOST_CHECK_EQUAL(type.location(), NodeEepromMap::EVENT_OPER_7.location());
    BOOST_CHECK_EQUAL(type.valueType(), NodeEepromMap::EVENT_OPER_7.valueType());
    BOOST_CHECK_EQUAL(val.id(), NodeEepromMap::EVENT_VAL1_7.id());
    BOOST_CHECK_EQUAL(val.location(), NodeEepromMap::EVENT_VAL1_7.location());
    BOOST_CHECK_EQUAL(val.valueType(), NodeEepromMap::EVENT_VAL1_7.valueType());

    //Trigger 8
    NodeEepromMap::getEventTriggerEeproms(7, false, ch, type, val);
    BOOST_CHECK_EQUAL(ch.id(), NodeEepromMap::EVENT_SRC_8.id());
    BOOST_CHECK_EQUAL(ch.location(), NodeEepromMap::EVENT_SRC_8.location());
    BOOST_CHECK_EQUAL(ch.valueType(), NodeEepromMap::EVENT_SRC_8.valueType());
    BOOST_CHECK_EQUAL(type.id(), NodeEepromMap::EVENT_OPER_8.id());
    BOOST_CHECK_EQUAL(type.location(), NodeEepromMap::EVENT_OPER_8.location());
    BOOST_CHECK_EQUAL(type.valueType(), NodeEepromMap::EVENT_OPER_8.valueType());
    BOOST_CHECK_EQUAL(val.id(), NodeEepromMap::EVENT_VAL1_8.id());
    BOOST_CHECK_EQUAL(val.location(), NodeEepromMap::EVENT_VAL1_8.location());
    BOOST_CHECK_EQUAL(val.valueType(), NodeEepromMap::EVENT_VAL1_8.valueType());
}

BOOST_AUTO_TEST_CASE(NodeEepromMap_getEventTriggerEeproms_float)
{
    EepromLocation ch = NodeEepromMap::EVENT_SRC_1;
    EepromLocation type = NodeEepromMap::EVENT_OPER_1;
    EepromLocation val = NodeEepromMap::EVENT_VAL1_1;

    //Trigger 3
    NodeEepromMap::getEventTriggerEeproms(2, true, ch, type, val);
    BOOST_CHECK_EQUAL(ch.id(), NodeEepromMap::EVENT_SRC_3.id());
    BOOST_CHECK_EQUAL(ch.location(), NodeEepromMap::EVENT_SRC_3.location());
    BOOST_CHECK_EQUAL(ch.valueType(), NodeEepromMap::EVENT_SRC_3.valueType());
    BOOST_CHECK_EQUAL(type.id(), NodeEepromMap::EVENT_OPER_3.id());
    BOOST_CHECK_EQUAL(type.location(), NodeEepromMap::EVENT_OPER_3.location());
    BOOST_CHECK_EQUAL(type.valueType(), NodeEepromMap::EVENT_OPER_3.valueType());
    BOOST_CHECK_EQUAL(val.id(), NodeEepromMap::EVENT_VAL1_3.id());
    BOOST_CHECK_EQUAL(val.location(), NodeEepromMap::EVENT_VAL1_3.location());
    BOOST_CHECK_EQUAL(val.valueType(), valueType_float);

    //Trigger 1
    NodeEepromMap::getEventTriggerEeproms(0, true, ch, type, val);
    BOOST_CHECK_EQUAL(ch.id(), NodeEepromMap::EVENT_SRC_1.id());
    BOOST_CHECK_EQUAL(ch.location(), NodeEepromMap::EVENT_SRC_1.location());
    BOOST_CHECK_EQUAL(ch.valueType(), NodeEepromMap::EVENT_SRC_1.valueType());
    BOOST_CHECK_EQUAL(type.id(), NodeEepromMap::EVENT_OPER_1.id());
    BOOST_CHECK_EQUAL(type.location(), NodeEepromMap::EVENT_OPER_1.location());
    BOOST_CHECK_EQUAL(type.valueType(), NodeEepromMap::EVENT_OPER_1.valueType());
    BOOST_CHECK_EQUAL(val.id(), NodeEepromMap::EVENT_VAL1_1.id());
    BOOST_CHECK_EQUAL(val.location(), NodeEepromMap::EVENT_VAL1_1.location());
    BOOST_CHECK_EQUAL(val.valueType(), valueType_float);

    //Trigger 7
    NodeEepromMap::getEventTriggerEeproms(6, true, ch, type, val);
    BOOST_CHECK_EQUAL(ch.id(), NodeEepromMap::EVENT_SRC_7.id());
    BOOST_CHECK_EQUAL(ch.location(), NodeEepromMap::EVENT_SRC_7.location());
    BOOST_CHECK_EQUAL(ch.valueType(), NodeEepromMap::EVENT_SRC_7.valueType());
    BOOST_CHECK_EQUAL(type.id(), NodeEepromMap::EVENT_OPER_7.id());
    BOOST_CHECK_EQUAL(type.location(), NodeEepromMap::EVENT_OPER_7.location());
    BOOST_CHECK_EQUAL(type.valueType(), NodeEepromMap::EVENT_OPER_7.valueType());
    BOOST_CHECK_EQUAL(val.id(), NodeEepromMap::EVENT_VAL1_7.id());
    BOOST_CHECK_EQUAL(val.location(), NodeEepromMap::EVENT_VAL1_7.location());
    BOOST_CHECK_EQUAL(val.valueType(), valueType_float);

    //Trigger 8
    NodeEepromMap::getEventTriggerEeproms(7, true, ch, type, val);
    BOOST_CHECK_EQUAL(ch.id(), NodeEepromMap::EVENT_SRC_8.id());
    BOOST_CHECK_EQUAL(ch.location(), NodeEepromMap::EVENT_SRC_8.location());
    BOOST_CHECK_EQUAL(ch.valueType(), NodeEepromMap::EVENT_SRC_8.valueType());
    BOOST_CHECK_EQUAL(type.id(), NodeEepromMap::EVENT_OPER_8.id());
    BOOST_CHECK_EQUAL(type.location(), NodeEepromMap::EVENT_OPER_8.location());
    BOOST_CHECK_EQUAL(type.valueType(), NodeEepromMap::EVENT_OPER_8.valueType());
    BOOST_CHECK_EQUAL(val.id(), NodeEepromMap::EVENT_VAL1_8.id());
    BOOST_CHECK_EQUAL(val.location(), NodeEepromMap::EVENT_VAL1_8.location());
    BOOST_CHECK_EQUAL(val.valueType(), valueType_float);
}

BOOST_AUTO_TEST_SUITE_END()