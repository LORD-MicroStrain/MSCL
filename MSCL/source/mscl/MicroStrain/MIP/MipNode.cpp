/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "MipNode.h"

#include "mscl/MicroStrain/MIP/MipNode_Impl.h"

namespace mscl
{
    MipNode::MipNode(Connection connection) :
        m_impl(std::make_shared<MipNode_Impl>(connection))
    {
    }

    MipNode::MipNode(std::shared_ptr<MipNode_Impl> impl) :
        m_impl(impl)
    {
    }

    GenericMipCmdResponse MipNode::doCommand(GenericMipCommand::Response& response, const ByteStream& command, bool verifySupported) const
    {
        return m_impl->doCommand(response, command, verifySupported);
    }

    Bytes MipNode::doCommand(uint8 descriptorSet, uint8 cmdDescriptor, const Bytes& fieldData, bool ackNackResponse, bool dataResponse, uint8 responseDataDescriptor) const
    {
        return m_impl->doCommand(descriptorSet, cmdDescriptor, fieldData, ackNackResponse, dataResponse, responseDataDescriptor);
    }

    MipCommandSet MipNode::getConfigCommandBytes()
    {
        return m_impl->getConfigCommandBytes();
    }

    void MipNode::sendCommandBytes(MipCommandSet& cmds)
    {
        m_impl->sendCommandBytes(cmds);
    }

    void MipNode::sendCommandBytes(MipCommandBytes& cmd)
    {
        m_impl->sendCommandBytes(cmd);
    }

    std::string MipNode::deviceName(const std::string& serial)
    {
        //replace any unsupported sensorcloud characters
        std::string sensorcloudFilteredName = "inertial-" + serial;
        Utils::filterSensorcloudName(sensorcloudFilteredName);

        return sensorcloudFilteredName;
    }

    Connection& MipNode::connection()
    {
        return m_impl->connection();
    }

    const MipNodeFeatures& MipNode::features() const
    {
        return m_impl->features();
    }

    const Timestamp& MipNode::lastCommunicationTime() const
    {
        return m_impl->lastCommunicationTime();
    }

    DeviceState MipNode::lastDeviceState() const
    {
        return m_impl->lastDeviceState();
    }

    Version MipNode::firmwareVersion() const
    {
        return m_impl->firmwareVersion();
    }

    MipModels::NodeModel MipNode::model() const
    {
        return MipModels::nodeFromModelString(modelNumber());
    }

    std::string MipNode::modelName() const
    {
        return m_impl->modelName();
    }

    std::string MipNode::modelNumber() const
    {
        return m_impl->modelNumber();
    }

    std::string MipNode::serialNumber() const
    {
        return m_impl->serialNumber();
    }

    std::string MipNode::lotNumber() const
    {
        return m_impl->lotNumber();
    }

    std::string MipNode::deviceOptions() const
    {
        return m_impl->deviceOptions();
    }

    void MipNode::timeout(uint64 timeout)
    {
        m_impl->timeout(timeout);
    }

    uint64 MipNode::timeout() const
    {
        return m_impl->timeout();
    }

    std::string MipNode::name()
    {
        return deviceName(serialNumber());
    }

    bool MipNode::ping()
    {
        return m_impl->ping();
    }

    void MipNode::setToIdle()
    {
        m_impl->setToIdle();
    }

    bool MipNode::cyclePower()
    {
        return m_impl->cyclePower();
    }

    void MipNode::resume()
    {
        m_impl->resume();
    }

    void MipNode::saveSettingsAsStartup(MipTypes::MipCommands cmdIds)
    {
        for (MipTypes::Command cmd : cmdIds)
        {
            m_impl->saveAsStartup(cmd);
        }
    }

    void MipNode::saveSettingsAsStartup()
    {
        m_impl->saveSettingsAsStartup();
    }
}