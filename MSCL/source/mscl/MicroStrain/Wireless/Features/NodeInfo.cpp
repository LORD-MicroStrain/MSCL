/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "NodeInfo.h"
#include "mscl/MicroStrain/Wireless/WirelessNode_Impl.h"

namespace mscl
{
    //read the required information from the node and store in the NodeInfo
    NodeInfo::NodeInfo(const WirelessNode_Impl* node):
        m_node(node),
        m_firmwareVersion(std::bind(&WirelessNode_Impl::firmwareVersion, m_node)),
        m_model(std::bind(&WirelessNode_Impl::model, m_node)),
        m_dataStorageSize(std::bind(&WirelessNode_Impl::dataStorageSize, m_node)),
        m_regionCode(std::bind(&WirelessNode_Impl::regionCode, m_node))
    {
    }

    NodeInfo::NodeInfo(const Version& fw, WirelessModels::NodeModel model, uint64 storageSize, WirelessTypes::RegionCode region):
        m_node(nullptr),
        m_firmwareVersion(fw),
        m_model(model),
        m_dataStorageSize(storageSize),
        m_regionCode(region)
    {
    }

    Version NodeInfo::firmwareVersion() const
    {
        return *m_firmwareVersion;
    }

    WirelessModels::NodeModel NodeInfo::model() const
    {
        return *m_model;
    }

    uint64 NodeInfo::dataStorageSize() const
    {
        return *m_dataStorageSize;
    }

    WirelessTypes::RegionCode NodeInfo::regionCode() const
    {
        return *m_regionCode;
    }
}