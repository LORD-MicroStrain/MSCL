/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "MockWirelessNode_Impl.h"
#include "Configuration/MockNodeEeprom.h"
#include "Features/NodeFeatures.h"

namespace mscl
{
    MockWirelessNode_Impl::MockWirelessNode_Impl(NodeAddress nodeAddress, const BaseStation& basestation, const NodeInfo& info):
        WirelessNode_Impl(nodeAddress, basestation),
        m_info(info)
    {
    }

    NodeEeprom& MockWirelessNode_Impl::eeprom() const
    {
        rec_mutex_lock_guard lock(m_protocolMutex);

        //if the eeprom variable hasn't been set yet
        if(m_eeprom == NULL)
        {
            //create the Mock eeprom variable
            m_eeprom.reset(new MockNodeEeprom(this, m_baseStation, m_eepromSettings));
        }

        return *(m_eeprom.get());
    }

    void MockWirelessNode_Impl::importEepromCache(const WirelessTypes::EepromMap& eeproms) const
    {
        eeprom().importCache(eeproms);
    }

    Value MockWirelessNode_Impl::readEeprom(const EepromLocation& location) const
    {
        try
        {
            return eeprom().readEeprom(location);
        }
        catch(mscl::Error_NodeCommunication& e)
        {
            throw mscl::Error_NodeCommunication(e.nodeAddress(), "Attempted to read the " + location.description() + " from Node " + Utils::toStr(e.nodeAddress()) + " but it is not in the Mock Node's Cache.");
        }
        catch(mscl::Error_NotSupported&)
        {
            throw mscl::Error_NotSupported("Node " + Utils::toStr(nodeAddress()) + " does not support reading the " + location.description());
        }
    }

    const NodeFeatures& MockWirelessNode_Impl::features() const
    {
        //if the features variable hasn't been set yet
        if(m_features == NULL)
        {
            //set the features variable by creating a new NodeFeatures pointer
            m_features = NodeFeatures::create(m_info);
        }

        return *(m_features.get());
    }

    const WirelessProtocol& MockWirelessNode_Impl::protocol(WirelessTypes::CommProtocol commProtocol) const
    {
        rec_mutex_lock_guard lock(m_protocolMutex);

        //WirelessProtocol shouldn't matter for MockWirelessNode
        return *WirelessProtocol::getProtocol(Version(1, 7));
    }

    Version MockWirelessNode_Impl::firmwareVersion() const
    {
        //use cached info for Mock object
        return m_info.firmwareVersion();
    }

    WirelessModels::NodeModel MockWirelessNode_Impl::model() const
    {
        //use cached info for Mock object
        return m_info.model();
    }

    std::string MockWirelessNode_Impl::serial() const
    {
        return "mock-node-" + Utils::toStr(m_address);
    }

    WirelessTypes::MicroControllerType MockWirelessNode_Impl::microcontroller() const
    {
        return WirelessTypes::microcontroller_18F452;
    }

    RadioFeatures MockWirelessNode_Impl::radioFeatures() const
    {
        return RadioFeatures(1);
    }

    uint64 MockWirelessNode_Impl::dataStorageSize() const
    {
        return 0;
    }

    WirelessTypes::RegionCode MockWirelessNode_Impl::regionCode() const
    {
        //use cached info for Mock object
        return m_info.regionCode();
    }

    uint16 MockWirelessNode_Impl::getNumDatalogSessions()
    {
        return 0;
    }

    float MockWirelessNode_Impl::percentFull()
    {
        return 0.0f;
    }

    PingResponse MockWirelessNode_Impl::ping()
    {
        return PingResponse::ResponseSuccess(0, 0);
    }

    bool MockWirelessNode_Impl::sleep()
    {
        throw Error_NotSupported("Sleep is not supported with MockWirelessNode.");
    }

    void MockWirelessNode_Impl::cyclePower()
    {
        return;
    }

    void MockWirelessNode_Impl::resetRadio()
    {
        return;
    }

    SetToIdleStatus MockWirelessNode_Impl::setToIdle()
    {
        throw Error_NotSupported("Set To Idle is not supported with MockWirelessNode.");
    }

    void MockWirelessNode_Impl::erase()
    {
        throw Error_NotSupported("Erase is not supported with MockWirelessNode.");
    }

    bool MockWirelessNode_Impl::startNonSyncSampling()
    {
        throw Error_NotSupported("Start Non-Sync Sampling is not supported with MockWirelessNode.");
    }

    bool MockWirelessNode_Impl::startSyncSampling()
    {
        throw Error_NotSupported("Start Sync Sampling is not supported with MockWirelessNode.");
    }

    void MockWirelessNode_Impl::clearHistogram()
    {
        throw Error_NotSupported("Clear Histogram is not supported with MockWirelessNode.");
    }

    AutoBalanceResult MockWirelessNode_Impl::autoBalance(const ChannelMask& mask, float targetPercent)
    {
        throw Error_NotSupported("AutoBalance is not supported with MockWirelessNode.");
    }

    AutoCalResult_shmLink MockWirelessNode_Impl::autoCal_shmLink()
    {
        throw Error_NotSupported("AutoCal is not supported with MockWirelessNode.");
    }

    AutoCalResult_shmLink201 MockWirelessNode_Impl::autoCal_shmLink201()
    {
        throw Error_NotSupported("AutoCal is not supported with MockWirelessNode.");
    }

    AutoShuntCalResult MockWirelessNode_Impl::autoShuntCal(const ChannelMask& mask, const ShuntCalCmdInfo& commandInfo)
    {
        throw Error_NotSupported("Auto Shunt Cal is not supported with MockWirelessNode.");
    }

    void MockWirelessNode_Impl::getDiagnosticInfo(ChannelData& result)
    {
        throw Error_NotSupported("Get Diagnostic Info is not supported with MockWirelessNode.");
    }

    bool MockWirelessNode_Impl::testCommProtocol(WirelessTypes::CommProtocol commProtocol)
    {
        return true;
    }
}