/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Wireless/WirelessNode.h"
#include "mscl/MicroStrain/Wireless/BaseStation.h"
#include "mscl/Utils.h"
#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"
#include "mscl/MicroStrain/Wireless/Configuration/WirelessNodeConfig.h"
#include "mscl/MicroStrain/Wireless/Configuration/EepromLocation.h"
#include "mscl/MicroStrain/Wireless/Features/ChannelGroup.h"

#include <boost/test/unit_test.hpp>
#include "mock_BaseStation.h"
#include "mock_WirelessNode.h"
using namespace mscl;


BOOST_AUTO_TEST_SUITE(ChannelGroup_Test)

NodeInfo createInfo(WirelessModels::NodeModel node)
{
    return NodeInfo(Version(9, 9), node, 0, WirelessTypes::region_usa);
}

BOOST_AUTO_TEST_CASE(ChannelGroup_channelGroups)
{
    std::shared_ptr<NodeFeatures> sglink = NodeFeatures::create(createInfo(WirelessModels::node_sgLink));
    mscl::ChannelGroups groups = sglink->channelGroups();

    BOOST_CHECK_EQUAL(groups.size(), 4);
    BOOST_CHECK_EQUAL(groups.at(0).channels().toMask(), 1);    //differential channels
    auto diffSettings = groups.at(0).settings();
    BOOST_CHECK_EQUAL(diffSettings.size(), 4);
    BOOST_CHECK_EQUAL(diffSettings.at(0), WirelessTypes::chSetting_hardwareGain);
    BOOST_CHECK_EQUAL(diffSettings.at(1), WirelessTypes::chSetting_hardwareOffset);
    BOOST_CHECK_EQUAL(diffSettings.at(2), WirelessTypes::chSetting_autoBalance);
    BOOST_CHECK_EQUAL(diffSettings.at(3), WirelessTypes::chSetting_shuntCal);

    BOOST_CHECK_EQUAL(groups.at(1).channels().toMask(), 1);    //cal coefficient ch1
    auto ch1Settings = groups.at(1).settings();
    BOOST_CHECK_EQUAL(ch1Settings.at(0), WirelessTypes::chSetting_linearEquation);
    BOOST_CHECK_EQUAL(ch1Settings.at(1), WirelessTypes::chSetting_unit);
    BOOST_CHECK_EQUAL(ch1Settings.at(2), WirelessTypes::chSetting_equationType);

    BOOST_CHECK_EQUAL(groups.at(2).channels().toMask(), 4);    //cal coefficient ch3
    auto ch3Settings = groups.at(2).settings();
    BOOST_CHECK_EQUAL(ch3Settings.at(0), WirelessTypes::chSetting_linearEquation);
    BOOST_CHECK_EQUAL(ch3Settings.at(1), WirelessTypes::chSetting_unit);
    BOOST_CHECK_EQUAL(ch3Settings.at(2), WirelessTypes::chSetting_equationType);

    BOOST_CHECK_EQUAL(groups.at(3).channels().toMask(), 8);    //cal coefficient ch4
    auto ch4Settings = groups.at(3).settings();
    BOOST_CHECK_EQUAL(ch4Settings.at(0), WirelessTypes::chSetting_linearEquation);
    BOOST_CHECK_EQUAL(ch4Settings.at(1), WirelessTypes::chSetting_unit);
    BOOST_CHECK_EQUAL(ch4Settings.at(2), WirelessTypes::chSetting_equationType);
}

BOOST_AUTO_TEST_CASE(ChannelGroup_getGaugeFactor)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    NodeInfo info(Version(10, 0), WirelessModels::node_shmLink2, 0, WirelessTypes::region_usa);

    //make the features() function return the NodeFeatures we want
    std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
    expectNodeFeatures(features, impl, WirelessModels::node_shmLink2);

    expectRead(impl, NodeEepromMap::GAUGE_FACTOR_1, Value::FLOAT(1.2345f));
    expectRead(impl, NodeEepromMap::GAUGE_FACTOR_2, Value::FLOAT(713.45101f));
    expectRead(impl, NodeEepromMap::GAUGE_FACTOR_3, Value::FLOAT(0.000152f));

    BOOST_CHECK_THROW(node.getGaugeFactor(ChannelMask(8)), Error_NotSupported);    //ch4 not supported
    BOOST_CHECK_CLOSE(node.getGaugeFactor(ChannelMask(1)), 1.2345, 0.001);        //ch1
    BOOST_CHECK_CLOSE(node.getGaugeFactor(ChannelMask(2)), 713.45101, 0.001);    //ch2
    BOOST_CHECK_CLOSE(node.getGaugeFactor(ChannelMask(4)), 0.000152, 0.001);    //ch3
}

BOOST_AUTO_TEST_CASE(WirelessNode_getLinearEquation)
{
    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
    BaseStation b = makeBaseStationWithMockImpl();
    WirelessNode node(100, b);
    node.setImpl(impl);

    NodeInfo info(Version(9, 9), WirelessModels::node_gLink_2g, 0, WirelessTypes::region_usa);

    //make the features() function return the NodeFeatures we want
    std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
    expectNodeFeatures(features, impl, WirelessModels::node_gLink_2g);

    //reading channel 1
    expectRead(impl, NodeEepromMap::CH_ACTION_SLOPE_1, Value::FLOAT(12.789f));        //slope
    expectRead(impl, NodeEepromMap::CH_ACTION_OFFSET_1, Value::FLOAT(-48.001f));    //offset
    expectRead(impl, NodeEepromMap::CH_ACTION_SLOPE_3, Value::FLOAT(6.45f));        //slope
    expectRead(impl, NodeEepromMap::CH_ACTION_OFFSET_3, Value::FLOAT(-0.002f));        //offset
    expectRead(impl, NodeEepromMap::CH_ACTION_ID_1, Value::UINT16(static_cast<uint16>(0x0407)));    //equation and unit

    LinearEquation eq = node.getLinearEquation(ChannelMask(1));//ch1
    LinearEquation eq2 = node.getLinearEquation(ChannelMask(4));//ch3

    BOOST_CHECK_CLOSE(eq.slope(), 12.789, 0.1);
    BOOST_CHECK_CLOSE(eq.offset(), -48.001, 0.1);
    BOOST_CHECK_CLOSE(eq2.slope(), 6.45, 0.1);
    BOOST_CHECK_CLOSE(eq2.offset(), -0.002, 0.1);
    BOOST_CHECK_EQUAL(node.getUnit(ChannelMask(1)), WirelessTypes::unit_volts_millivolts);
    BOOST_CHECK_EQUAL(node.getEquationType(ChannelMask(1)), WirelessTypes::equation_standard);
}

BOOST_AUTO_TEST_CASE(ChannelGroup_getThermocoupleType)
{
    //tests get thermocouple fail (not supported)
    {
        std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
        BaseStation b = makeBaseStationWithMockImpl();
        WirelessNode node(100, b);
        node.setImpl(impl);

        NodeInfo info(Version(9, 9), WirelessModels::node_gLink_2g, 0, WirelessTypes::region_usa);

        //make the features() function return the NodeFeatures we want
        std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);
        expectNodeFeatures(features, impl, WirelessModels::node_gLink_2g);

        BOOST_CHECK_THROW(node.getThermocoupleType(ChannelMask(1)), Error_NotSupported);
    }

    //tests get thermocouple success
    {
        std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(100));
        BaseStation b = makeBaseStationWithMockImpl();
        WirelessNode node(100, b);
        node.setImpl(impl);

        std::unique_ptr<NodeFeatures> features;
        expectNodeFeatures(features, impl, WirelessModels::node_tcLink_3ch);

        expectRead(impl, NodeEepromMap::THERMOCPL_TYPE, Value::UINT16(WirelessTypes::tc_N));

        BOOST_CHECK_EQUAL(node.getThermocoupleType(ChannelMask(BOOST_BINARY(00000111))), WirelessTypes::tc_N);
        BOOST_CHECK_THROW(node.getThermocoupleType(ChannelMask(BOOST_BINARY(00000101))), Error_NotSupported);
        BOOST_CHECK_THROW(node.getThermocoupleType(ChannelMask(BOOST_BINARY(00000001))), Error_NotSupported);
    }
}

BOOST_AUTO_TEST_SUITE_END()