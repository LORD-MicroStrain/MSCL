/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Displacement/DisplacementNode.h"

#include "mscl/MicroStrain/MIP/MipNode_Impl.h"

namespace mscl
{
    DisplacementNode::DisplacementNode(Connection connection) :
        m_impl(std::make_shared<MipNode_Impl>(connection))
    {}

    DisplacementNode::DisplacementNode(std::shared_ptr<MipNode_Impl> impl) :
        m_impl(impl)
    {}

    const MipNodeFeatures& DisplacementNode::features()
    {
        return m_impl->features();
    }

    MipDataPackets DisplacementNode::getDataPackets(uint32 timeout, uint32 maxPackets)
    {
        MipDataPackets packets;
        m_impl->getDataPackets(packets, timeout, maxPackets);
        return packets;
    }

    GenericMipCmdResponse DisplacementNode::doCommand(GenericMipCommand::Response& response, const ByteStream& command, bool verifySupported) const
    {
        return m_impl->doCommand(response, command, verifySupported);
    }

    Bytes DisplacementNode::doCommand(uint8 descriptorSet, uint8 cmdDescriptor, const Bytes& fieldData, bool ackNackResponse, bool dataResponse, uint8 responseDataDescriptor) const
    {
        return m_impl->doCommand(descriptorSet, cmdDescriptor, fieldData, ackNackResponse, dataResponse, responseDataDescriptor);
    }

    std::string DisplacementNode::deviceName(const std::string& serial)
    {
        //replace any unsupported sensorcloud characters
        std::string sensorcloudFilteredName = serial;
        Utils::filterSensorcloudName(sensorcloudFilteredName);

        return sensorcloudFilteredName;
    }

    Connection& DisplacementNode::connection()
    {
        return m_impl->connection();
    }

    const Timestamp& DisplacementNode::lastCommunicationTime() const
    {
        return m_impl->lastCommunicationTime();
    }

    DeviceState DisplacementNode::lastDeviceState() const
    {
        return m_impl->lastDeviceState();
    }

    Version DisplacementNode::firmwareVersion() const
    {
        return m_impl->firmwareVersion();
    }

    DisplacementModels::NodeModel DisplacementNode::model() const
    {
        return DisplacementModels::nodeFromModelString(modelNumber());
    }

    std::string DisplacementNode::modelName() const
    {
        return m_impl->modelName();
    }

    std::string DisplacementNode::modelNumber() const
    {
        return m_impl->modelNumber();
    }

    std::string DisplacementNode::serialNumber() const
    {
        return m_impl->serialNumber();
    }

    std::string DisplacementNode::lotNumber() const
    {
        return m_impl->lotNumber();
    }

    std::string DisplacementNode::deviceOptions() const
    {
        return m_impl->deviceOptions();
    }

    uint32 DisplacementNode::totalPackets()
    {
        return m_impl->totalPackets();
    }

    void DisplacementNode::timeout(uint64 timeout)
    {
        m_impl->timeout(timeout);
    }

    uint64 DisplacementNode::timeout() const
    {
        return m_impl->timeout();
    }

    std::string DisplacementNode::name()
    {
        return deviceName(serialNumber());
    }

    bool DisplacementNode::ping()
    {
        return m_impl->ping();
    }

    void DisplacementNode::setToIdle()
    {
        m_impl->setToIdle();
    }

    bool DisplacementNode::cyclePower()
    {
        return m_impl->cyclePower();
    }

    void DisplacementNode::resume()
    {
        m_impl->resume();
    }

    SampleRate DisplacementNode::getDisplacementOutputDataRate() const
    {
        return m_impl->getDisplacementOutputDataRate();
    }

    LinearEquation DisplacementNode::getAnalogToDisplacementCal() const
    {
        return m_impl->getAnalogToDisplacementCal();
    }

    void DisplacementNode::setDeviceTime()
    {
        return m_impl->setDeviceTime();
    }

    void DisplacementNode::setDeviceTime(uint64 nanoseconds)
    {
        return m_impl->setDeviceTime(nanoseconds);
    }
} // namespace mscl
