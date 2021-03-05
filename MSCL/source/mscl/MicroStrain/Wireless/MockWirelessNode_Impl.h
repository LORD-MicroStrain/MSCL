/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "WirelessNode_Impl.h"
#include "Features/NodeInfo.h"
#include "Features/NodeFeatures.h"

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

    public:
        //Constructor: WirelessNode_Impl
        //    Creates a WirelessNode_Impl object.
        //
        //Parameters:
        //    nodeAddress - the node address of the node
        //    basestation - the node's parent Base Station
        //    info - The <NodeInfo> of the Node
        MockWirelessNode_Impl(NodeAddress nodeAddress, const BaseStation& basestation, const NodeInfo& info);

        virtual ~MockWirelessNode_Impl() {}

    private:
        //Variable: m_info
        //  The <NodeInfo> for the MockWirelessNode to use when needed.
        NodeInfo m_info;

    protected:
        virtual NodeEeprom& eeprom() const;

    public:
        virtual void importEepromCache(const WirelessTypes::EepromMap& eeproms) const;

        virtual Value readEeprom(const EepromLocation& location) const;

        virtual const NodeFeatures& features() const override;

        virtual const WirelessProtocol& protocol(WirelessTypes::CommProtocol commProtocol) const override;

        virtual Version firmwareVersion() const override;

        virtual WirelessModels::NodeModel model() const override;

        virtual std::string serial() const override;

        virtual WirelessTypes::MicroControllerType microcontroller() const override;

        virtual RadioFeatures radioFeatures() const override;

        virtual uint64 dataStorageSize() const override;

        virtual WirelessTypes::RegionCode regionCode() const override;

        virtual uint16 getNumDatalogSessions() override;

        virtual float percentFull() override;

        virtual PingResponse ping() override;

        virtual bool sleep() override;

        virtual void cyclePower() override;

        virtual void resetRadio() override;

        virtual SetToIdleStatus setToIdle() override;

        virtual void erase() override;

        virtual bool startNonSyncSampling() override;

        virtual bool startSyncSampling() override;

        virtual void clearHistogram() override;

        virtual AutoBalanceResult autoBalance(const ChannelMask& mask, float targetPercent) override;

        virtual AutoCalResult_shmLink autoCal_shmLink() override;

        virtual AutoCalResult_shmLink201 autoCal_shmLink201() override;

        virtual AutoShuntCalResult autoShuntCal(const ChannelMask& mask, const ShuntCalCmdInfo& commandInfo) override;

        virtual void getDiagnosticInfo(ChannelData& result) override;

        virtual bool testCommProtocol(WirelessTypes::CommProtocol commProtocol) override;
    };
}