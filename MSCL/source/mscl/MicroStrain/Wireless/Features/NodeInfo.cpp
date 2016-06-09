/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "NodeInfo.h"
#include "mscl/MicroStrain/Wireless/WirelessNode_Impl.h"

namespace mscl
{
    //read the required information from the node and store in the NodeInfo
    NodeInfo::NodeInfo(const WirelessNode_Impl* node):
        m_node(node)
        /*m_firmwareVersion(node.firmwareVersion()),
        m_model(node.model()),
        m_dataStorageSize(node.dataStorageSize()),
        m_regionCode(node.regionCode())*/
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
        if(!static_cast<bool>(m_firmwareVersion))
        {
            m_firmwareVersion = m_node->firmwareVersion();
        }
        
        return *m_firmwareVersion;
    }

    WirelessModels::NodeModel NodeInfo::model() const
    {
        if(!static_cast<bool>(m_model))
        {
            m_model = m_node->model();
        }

        return *m_model;
    }

    uint64 NodeInfo::dataStorageSize() const
    {
        if(!static_cast<bool>(m_dataStorageSize))
        {
            m_dataStorageSize = m_node->dataStorageSize();

        }

        return *m_dataStorageSize;
    }

    WirelessTypes::RegionCode NodeInfo::regionCode() const
    {
        if(!static_cast<bool>(m_regionCode))
        {
            m_regionCode = m_node->regionCode();

        }

        return *m_regionCode;
    }
}