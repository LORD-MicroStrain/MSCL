/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"
#include "mscl/MicroStrain/Wireless/WirelessNode_Impl.h"

#include "mock_BaseStation.h"

using namespace mscl;

MOCK_BASE_CLASS(mock_WirelessNodeImpl, WirelessNode_Impl)
{
    mock_WirelessNodeImpl():
        WirelessNode_Impl(123, makeBaseStationWithMockImpl())
    {}

    mock_WirelessNodeImpl(BaseStation basestation):
        WirelessNode_Impl(123, basestation)
    {}

    mock_WirelessNodeImpl(uint16 address):
        WirelessNode_Impl(address, makeBaseStationWithMockImpl())
    {}

    mock_WirelessNodeImpl(BaseStation basestation, uint16 address) :
        WirelessNode_Impl(address, basestation)
    {}

    MOCK_METHOD(ping, 0);
    MOCK_METHOD(cyclePower, 0);
    MOCK_METHOD(resetRadio, 0);
    MOCK_METHOD_EXT(readEeprom, 1, Value(const EepromLocation&), readEeprom);
    MOCK_METHOD_EXT(writeEeprom, 2, void(const EepromLocation&, const Value&), writeEeprom);
    MOCK_METHOD_EXT(readEeprom, 1, uint16(uint16), readEeprom_uint16);
    MOCK_METHOD_EXT(writeEeprom, 2, void(uint16, uint16), writeEeprom_uint16);
    MOCK_METHOD(changeFrequency, 1);
    MOCK_METHOD(features, 0);
    MOCK_METHOD(firmwareVersion, 0);
    MOCK_METHOD(protocol, 1);
};

MOCK_BASE_CLASS(mock_WirelessNodeImpl_Basic, WirelessNode_Impl)
{
    mock_WirelessNodeImpl_Basic():
        WirelessNode_Impl(123, makeBaseStationWithMockImpl())
    {}

    mock_WirelessNodeImpl_Basic(BaseStation basestation):
        WirelessNode_Impl(123, basestation)
    {}

    mock_WirelessNodeImpl_Basic(uint16 address):
        WirelessNode_Impl(address, makeBaseStationWithMockImpl())
    {}

    mock_WirelessNodeImpl_Basic(BaseStation basestation, uint16 address):
        WirelessNode_Impl(address, basestation)
    {}

    MOCK_METHOD_EXT(readEeprom, 1, Value(const EepromLocation&), readEeprom);
    MOCK_METHOD_EXT(writeEeprom, 2, void(const EepromLocation&, const Value&), writeEeprom);
    MOCK_METHOD_EXT(readEeprom, 1, uint16(uint16), readEeprom_uint16);
    MOCK_METHOD_EXT(writeEeprom, 2, void(uint16, uint16), writeEeprom_uint16);
    MOCK_METHOD(features, 0);
};

static void expectRead(std::shared_ptr<mock_WirelessNodeImpl> impl, const EepromLocation& loc, const Value& returnVal)
{
    MOCK_EXPECT(impl->readEeprom).with(loc).returns(returnVal);
}

static void expectWrite(std::shared_ptr<mock_WirelessNodeImpl> impl, const EepromLocation& loc, const Value& val)
{
    MOCK_EXPECT(impl->writeEeprom).with(loc, val);
}

static void expectWriteOnce(std::shared_ptr<mock_WirelessNodeImpl> impl, const EepromLocation& loc, const Value& val)
{
    MOCK_EXPECT(impl->writeEeprom).once().with(loc, val);
}

static void expectReadModel(std::shared_ptr<mock_WirelessNodeImpl> impl, WirelessModels::NodeModel model)
{
    //split the model into its 2 pieces
    uint16 modelType = static_cast<uint16>(model / 10000);
    uint16 modelOption = model % 10000;

    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::MODEL_NUMBER).returns(Value(valueType_uint16, modelType));
    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::MODEL_OPTION).returns(Value(valueType_uint16, modelOption));
}

static void expectGoodPing(std::shared_ptr<mock_WirelessNodeImpl> impl)
{
    PingResponse r = PingResponse::ResponseSuccess(-50, -50);
    MOCK_EXPECT(impl->ping).returns(r);
}

static void expectNodeFeatures(std::unique_ptr<NodeFeatures>& features, std::shared_ptr<mock_WirelessNodeImpl> impl, WirelessModels::NodeModel model = WirelessModels::node_gLink_2g)
{
    NodeInfo info(Version(9, 9), model, WirelessTypes::region_usa);

    features = NodeFeatures::create(info);

    MOCK_EXPECT(impl->features).returns(std::ref(*features.get()));
}

static void expectNodeFeatures_fw10(std::unique_ptr<NodeFeatures>& features, std::shared_ptr<mock_WirelessNodeImpl> impl, WirelessModels::NodeModel model = WirelessModels::node_gLink_2g)
{
    NodeInfo info(Version(10, 0), model, WirelessTypes::region_usa);

    features = NodeFeatures::create(info);

    MOCK_EXPECT(impl->features).returns(std::ref(*features.get()));
}

static void expectResetRadio(std::shared_ptr<mock_WirelessNodeImpl> impl)
{
    expectWrite(impl, NodeEepromMap::CYCLE_POWER, Value::UINT16(2));
}

static void expectRead(std::shared_ptr<mock_WirelessNodeImpl_Basic> impl, const EepromLocation& loc, const Value& returnVal)
{
    MOCK_EXPECT(impl->readEeprom).with(loc).returns(returnVal);
}

static void expectWrite(std::shared_ptr<mock_WirelessNodeImpl_Basic> impl, const EepromLocation& loc, const Value& val)
{
    MOCK_EXPECT(impl->writeEeprom).with(loc, val);
}

static void expectReadModel(std::shared_ptr<mock_WirelessNodeImpl_Basic> impl, WirelessModels::NodeModel model)
{
    //split the model into its 2 pieces
    uint16 modelType = static_cast<uint16>(model / 10000);
    uint16 modelOption = model % 10000;

    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::MODEL_NUMBER).returns(Value(valueType_uint16, modelType));
    MOCK_EXPECT(impl->readEeprom).with(NodeEepromMap::MODEL_OPTION).returns(Value(valueType_uint16, modelOption));
} // namespace mscl
