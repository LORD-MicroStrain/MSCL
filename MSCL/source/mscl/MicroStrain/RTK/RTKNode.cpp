/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "RTKNode.h"

#include "mscl/Types.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"
#include "mscl/MicroStrain/MIP/MipNodeFeatures.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacket.h"
#include "mscl/MicroStrain/MIP/MipNode_Impl.h"

#include <algorithm>


namespace mscl
{
    RTKNode::RTKNode(Connection connection): 
        m_impl(std::make_shared<MipNode_Impl>(connection))
    {
    }

    RTKNode::RTKNode(std::shared_ptr<MipNode_Impl> impl) :
        m_impl(impl)
    {
    }

    const MipNodeFeatures& RTKNode::features()
    {
        return m_impl->features();
    }

    MipDataPackets RTKNode::getDataPackets(uint32 timeout, uint32 maxPackets)
    { 
        MipDataPackets packets;
        m_impl->getDataPackets(packets, timeout, maxPackets);
        return packets;
    }

    GenericMipCmdResponse RTKNode::doCommand(GenericMipCommand::Response& response, const ByteStream& command, bool verifySupported) const
    {
        return m_impl->doCommand(response, command, verifySupported);
    }

    Bytes RTKNode::doCommand(uint8 descriptorSet, uint8 cmdDescriptor, const Bytes& fieldData, bool ackNackResponse, bool dataResponse, uint8 responseDataDescriptor) const
    {
        return m_impl->doCommand(descriptorSet, cmdDescriptor, fieldData, ackNackResponse, dataResponse, responseDataDescriptor);
    }

    std::string RTKNode::deviceName(const std::string& serial)
    {
        //replace any unsupported sensorcloud characters
        std::string sensorcloudFilteredName = serial;
        Utils::filterSensorcloudName(sensorcloudFilteredName);

        return sensorcloudFilteredName;
    }

    Connection& RTKNode::connection()
    {
        return m_impl->connection();
    }

    const Timestamp& RTKNode::lastCommunicationTime() const
    {
        return m_impl->lastCommunicationTime();
    }

    DeviceState RTKNode::lastDeviceState() const
    {
        return m_impl->lastDeviceState();
    }

    Version RTKNode::firmwareVersion() const
    {
        return m_impl->firmwareVersion();
    }

    RTKModels::NodeModel RTKNode::model() const
    {
        return RTKModels::nodeFromModelString(modelNumber());
    }

    std::string RTKNode::modelName() const
    {
        return m_impl->modelName();
    }

    std::string RTKNode::modelNumber() const
    {
        return m_impl->modelNumber();
    }

    std::string RTKNode::serialNumber() const
    {
        return m_impl->serialNumber();
    }

    std::string RTKNode::lotNumber() const
    {
        return m_impl->lotNumber();
    }

    std::string RTKNode::deviceOptions() const
    {
        return m_impl->deviceOptions();
    }

    uint32 RTKNode::totalPackets()                                                            
    { 
        return m_impl->totalPackets(); 
    }

    void RTKNode::timeout(uint64 timeout)                                        
    { 
        m_impl->timeout(timeout); 
    }

    uint64 RTKNode::timeout() const
    {
        return m_impl->timeout();
    }

    std::string RTKNode::name()
    {
        return deviceName(serialNumber());
    }

    bool RTKNode::ping()
    { 
        return m_impl->ping(); 
    }

    void RTKNode::setToIdle()
    {
        m_impl->setToIdle();
    }

    bool RTKNode::cyclePower()
    {
        return m_impl->cyclePower();
    }

    void RTKNode::resume()
    {
        m_impl->resume();
    }

    RTKDeviceStatusFlags RTKNode::getDeviceStatusFlags() const
    {
        return m_impl->getDeviceStatusFlags();
    }
}
