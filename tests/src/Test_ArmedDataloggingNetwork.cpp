/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/ArmedDataloggingNetwork.h"
#include "mscl/MicroStrain/Wireless/WirelessNode.h"
#include "mscl/MicroStrain/Wireless/WirelessNode_Impl.h"

#include "mock_WirelessNode.h"

using namespace mscl;

BOOST_AUTO_TEST_SUITE(ArmedDataloggingNetwork_Test)

BOOST_AUTO_TEST_CASE(ArmedDataloggingNetwork_addNode_success)
{
    std::shared_ptr<mock_baseStationImpl> baseImpl(new mock_baseStationImpl());
    BaseStation b(baseImpl);

    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(b));
    WirelessNode node(1, b);
    node.setImpl(impl);

    std::shared_ptr<mock_WirelessNodeImpl> impl2(new mock_WirelessNodeImpl(b));
    WirelessNode node2(2, b);
    node2.setImpl(impl2);

    ArmedDataloggingNetwork nwk(b);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);
    expectNodeFeatures(features, impl2);

    uint16 mode = WirelessTypes::samplingMode_armedDatalog;

    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::SAMPLING_MODE).returns(Value::UINT16(mode));    //sampling mode
    MOCK_EXPECT(impl2->readEeprom).with(NodeEepromMap::SAMPLING_MODE).returns(Value::UINT16(mode));    //sampling mode

    BOOST_CHECK_NO_THROW(nwk.addNode(node, "Hello World!"));
    BOOST_CHECK_NO_THROW(nwk.addNode(node2, "This is a test"));
}

BOOST_AUTO_TEST_CASE(ArmedDataloggingNetwork_addNode_fail_differentBase)
{
    std::shared_ptr<mock_baseStationImpl> baseImpl1(new mock_baseStationImpl());
    BaseStation b(baseImpl1);

    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(b));
    WirelessNode node(1, b);
    node.setImpl(impl);

    std::shared_ptr<BaseStation_Impl> baseImpl2(new mock_baseStationImpl());
    BaseStation b2(baseImpl2);

    std::shared_ptr<mock_WirelessNodeImpl> impl2(new mock_WirelessNodeImpl(b2, 2));
    WirelessNode node2(2, b2);
    node2.setImpl(impl2);

    ArmedDataloggingNetwork nwk(b);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);

    uint16 mode = WirelessTypes::samplingMode_armedDatalog;
    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::SAMPLING_MODE).returns(Value::UINT16(mode));    //sampling mode

    BOOST_CHECK_NO_THROW(nwk.addNode(node, "Hello World!"));
    BOOST_CHECK_THROW(nwk.addNode(node2, "Test"), Error);
}

BOOST_AUTO_TEST_CASE(ArmedDataloggingNetwork_addNode_fail_invalidConfig)
{
    std::shared_ptr<mock_baseStationImpl> baseImpl1(new mock_baseStationImpl());
    BaseStation b(baseImpl1);

    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(b));
    WirelessNode node(1, b);
    node.setImpl(impl);

    ArmedDataloggingNetwork nwk(b);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);
    uint16 mode = WirelessTypes::samplingMode_nonSync;
    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::SAMPLING_MODE).returns(Value::UINT16(mode));    //invalid sampling mode

    BOOST_CHECK_THROW(nwk.addNode(node, "Hello World!"), Error_InvalidNodeConfig);
}

BOOST_AUTO_TEST_CASE(ArmedDataloggingNetwork_removeNode)
{
    std::shared_ptr<mock_baseStationImpl> baseImpl1(new mock_baseStationImpl());
    BaseStation b(baseImpl1);

    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(b));
    WirelessNode node(1, b);
    node.setImpl(impl);

    std::shared_ptr<mock_WirelessNodeImpl> impl2(new mock_WirelessNodeImpl(b));
    WirelessNode node2(2, b);
    node2.setImpl(impl2);

    ArmedDataloggingNetwork nwk(b);

    BOOST_CHECK_NO_THROW(nwk.removeNode(123));    //node not in list, silent fail

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);
    expectNodeFeatures(features, impl2);

    uint16 mode = WirelessTypes::samplingMode_armedDatalog;
    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::SAMPLING_MODE).returns(Value::UINT16(mode));    //sampling mode
    MOCK_EXPECT(impl2->readEeprom).with(NodeEepromMap::SAMPLING_MODE).returns(Value::UINT16(mode));    //sampling mode

    BOOST_CHECK_NO_THROW(nwk.addNode(node, "Hello World!"));
    BOOST_CHECK_NO_THROW(nwk.addNode(node2, "This is a test"));

    BOOST_CHECK_NO_THROW(nwk.removeNode(1));
    BOOST_CHECK_NO_THROW(nwk.removeNode(2));
}

BOOST_AUTO_TEST_CASE(ArmedDataloggingNetwork_startSampling_success)
{
    std::shared_ptr<mock_baseStationImpl> baseImpl(new mock_baseStationImpl());
    BaseStation b(baseImpl);

    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(b, 1));
    WirelessNode node(1, b);
    node.setImpl(impl);

    std::shared_ptr<mock_WirelessNodeImpl> impl2(new mock_WirelessNodeImpl(b, 2));
    WirelessNode node2(2, b);
    node2.setImpl(impl2);

    ArmedDataloggingNetwork nwk(b);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);
    expectNodeFeatures(features, impl2);

    uint16 mode = WirelessTypes::samplingMode_armedDatalog;
    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::SAMPLING_MODE).returns(Value::UINT16(mode));    //sampling mode
    MOCK_EXPECT(impl2->readEeprom).with(NodeEepromMap::SAMPLING_MODE).returns(Value::UINT16(mode));    //sampling mode

    BOOST_CHECK_NO_THROW(nwk.addNode(node, "Hello World!"));
    BOOST_CHECK_NO_THROW(nwk.addNode(node2));

    MOCK_EXPECT(baseImpl->node_armForDatalogging).with(1, "Hello World!").returns(true);
    MOCK_EXPECT(baseImpl->node_armForDatalogging).with(2, "").returns(true);

    MOCK_EXPECT(baseImpl->node_triggerArmedDatalogging).with(65535);

    BOOST_CHECK_NO_THROW(nwk.startSampling());
}

BOOST_AUTO_TEST_CASE(ArmedDataloggingNetwork_startSampling_failArm)
{
    std::shared_ptr<mock_baseStationImpl> baseImpl(new mock_baseStationImpl());
    BaseStation b(baseImpl);

    std::shared_ptr<mock_WirelessNodeImpl> impl(new mock_WirelessNodeImpl(b, 1));
    WirelessNode node(1, b);
    node.setImpl(impl);

    std::shared_ptr<mock_WirelessNodeImpl> impl2(new mock_WirelessNodeImpl(b, 2));
    WirelessNode node2(2, b);
    node2.setImpl(impl2);

    ArmedDataloggingNetwork nwk(b);

    std::unique_ptr<NodeFeatures> features;
    expectNodeFeatures(features, impl);
    expectNodeFeatures(features, impl2);

    uint16 mode = WirelessTypes::samplingMode_armedDatalog;
    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::SAMPLING_MODE).returns(Value::UINT16(mode));    //sampling mode
    MOCK_EXPECT(impl2->readEeprom).with(NodeEepromMap::SAMPLING_MODE).returns(Value::UINT16(mode));    //sampling mode

    BOOST_CHECK_NO_THROW(nwk.addNode(node, "Hello World!"));
    BOOST_CHECK_NO_THROW(nwk.addNode(node2));

    MOCK_EXPECT(baseImpl->node_armForDatalogging).returns(false);

    BOOST_CHECK_THROW(nwk.startSampling(), Error_NodeCommunication);
}

BOOST_AUTO_TEST_SUITE_END()
