/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeInfo.h"
#include "mscl/MicroStrain/Wireless/WirelessNode_Impl.h"

namespace mscl
{
    //Class: MockWirelessNode_Impl
    //  Contains the Mock implementation logic for a WirelessNode.
    class MockWirelessNode_Impl: public WirelessNode_Impl
    {
    public:
        MockWirelessNode_Impl() = delete;                                           //default constructor disabled
        MockWirelessNode_Impl(const MockWirelessNode_Impl&) = delete;               //copy constructor disabled
        MockWirelessNode_Impl& operator=(const MockWirelessNode_Impl&) = delete;    //assignment operator disabled

        //Constructor: WirelessNode_Impl
        //    Creates a WirelessNode_Impl object.
        //
        //Parameters:
        //    nodeAddress - the node address of the node
        //    basestation - the node's parent Base Station
        //    info - The <NodeInfo> of the Node
        MockWirelessNode_Impl(NodeAddress nodeAddress, const BaseStation& basestation, const NodeInfo& info);

        ~MockWirelessNode_Impl() override = default;

    private:
        //Variable: m_info
        //  The <NodeInfo> for the MockWirelessNode to use when needed.
        NodeInfo m_info;

    protected:
        NodeEeprom& eeprom() const override;

    public:
        virtual void importEepromCache(const WirelessTypes::EepromMap& eeproms) const;

        Value readEeprom(const EepromLocation& location) const override;

        const NodeFeatures& features() const override;

        const WirelessProtocol& protocol(WirelessTypes::CommProtocol commProtocol) const override;

        Version firmwareVersion() const override;

        WirelessModels::NodeModel model() const override;

        std::string serial() const override;

        WirelessTypes::MicroControllerType microcontroller() const override;

        RadioFeatures radioFeatures() const override;

        uint64 dataStorageSize() const override;

        WirelessTypes::RegionCode regionCode() const override;

        uint16 getNumDatalogSessions() override;

        float percentFull() override;

        PingResponse ping() override;

        bool sleep() override;

        void cyclePower() override;

        void resetRadio() override;

        SetToIdleStatus setToIdle() override;

        void erase() override;

        bool startNonSyncSampling() override;

        bool startSyncSampling() override;

        void clearHistogram() override;

        AutoBalanceResult autoBalance(const ChannelMask& mask, float targetPercent) override;

        AutoCalResult_shmLink autoCal_shmLink() override;

        AutoCalResult_shmLink201 autoCal_shmLink201() override;

        AutoShuntCalResult autoShuntCal(const ChannelMask& mask, const ShuntCalCmdInfo& commandInfo) override;

        void getDiagnosticInfo(ChannelData& result) override;

        bool testCommProtocol(WirelessTypes::CommProtocol commProtocol) override;
    };
} // namespace mscl
