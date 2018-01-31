/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "InertialNode.h"

#include "mscl/Types.h"
#include "mscl/Communication/SerialConnection.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"
#include "mscl/MicroStrain/MIP/MipNodeFeatures.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacket.h"
#include "mscl/MicroStrain/MIP/MipNode_Impl.h"

#include <algorithm>


namespace mscl
{
    InertialNode::InertialNode(Connection connection): 
        m_impl(std::make_shared<MipNode_Impl>(connection))
    {
    }

    InertialNode::InertialNode(std::shared_ptr<MipNode_Impl> impl) :
        m_impl(impl)
    {
    }

    const MipNodeFeatures& InertialNode::features()
    {
        return m_impl->features();
    }

    MipDataPackets InertialNode::getDataPackets(uint32 timeout, uint32 maxPackets)
    { 
        MipDataPackets packets;
        m_impl->getDataPackets(packets, timeout, maxPackets);
        return packets;
    }

    GenericMipCmdResponse InertialNode::doCommand(GenericMipCommand::Response& response, const ByteStream& command, bool verifySupported) const
    {
        return m_impl->doCommand(response, command, verifySupported);
    }

    std::string InertialNode::deviceName(const std::string& serial)
    {
        //replace any unsupported sensorcloud characters
        std::string sensorcloudFilteredName = "inertial-" + serial;
        Utils::filterSensorcloudName(sensorcloudFilteredName);

        return sensorcloudFilteredName;
    }

    Connection& InertialNode::connection()
    {
        return m_impl->connection();
    }

    const Timestamp& InertialNode::lastCommunicationTime() const
    {
        return m_impl->lastCommunicationTime();
    }

    Version InertialNode::firmwareVersion() const
    {
        return m_impl->firmwareVersion();
    }

    InertialModels::NodeModel InertialNode::model() const
    {
        return InertialModels::nodeFromModelString(modelNumber());
    }

    std::string InertialNode::modelName() const
    {
        return m_impl->modelName();
    }

    std::string InertialNode::modelNumber() const
    {
        return m_impl->modelNumber();
    }

    std::string InertialNode::serialNumber() const
    {
        return m_impl->serialNumber();
    }

    std::string InertialNode::lotNumber() const
    {
        return m_impl->lotNumber();
    }

    std::string InertialNode::deviceOptions() const
    {
        return m_impl->deviceOptions();
    }

    uint32 InertialNode::totalPackets()                                                            
    { 
        return m_impl->totalPackets(); 
    }

    void InertialNode::timeout(uint64 timeout)                                        
    { 
        m_impl->timeout(timeout); 
    }

    uint64 InertialNode::timeout() const
    {
        return m_impl->timeout();
    }

    std::string InertialNode::name()
    {
        return deviceName(serialNumber());
    }

    bool InertialNode::ping()                                                        
    { 
        return m_impl->ping(); 
    }

    void InertialNode::setToIdle()
    {
        m_impl->setToIdle();
    }

    bool InertialNode::cyclePower()
    {
        return m_impl->cyclePower();
    }

	void InertialNode::resume()
	{
		m_impl->resume();
	}

	void InertialNode::saveSettingsAsStartup()
    {
        return m_impl->saveSettingsAsStartup();
    }

    void InertialNode::loadStartupSettings()
    {
        return m_impl->loadStartupSettings();
    }

    void InertialNode::loadFactoryDefaultSettings()
    {
        return m_impl->loadFactoryDefaultSettings();
    }

    uint16 InertialNode::getDataRateBase(MipTypes::DataClass category)
    { 
        return m_impl->getDataRateBase(category);
    }

    MipChannels InertialNode::getActiveChannelFields(MipTypes::DataClass category)
    { 
        return m_impl->getMessageFormat(category);
    }

    void InertialNode::setActiveChannelFields(MipTypes::DataClass category, const MipChannels& channels)
    { 
        m_impl->setMessageFormat(category, channels);
    }

    void InertialNode::saveActiveChannelFields(MipTypes::DataClass category)
    {
        m_impl->saveMessageFormat(category);
    }

    uint8 InertialNode::getCommunicationMode()                                                    
    { 
        return m_impl->getCommunicationMode(); 
    }

    void InertialNode::setCommunicationMode(uint8 communicationMode)                            
    { 
        m_impl->setCommunicationMode(communicationMode); 
    }

    void InertialNode::enableDataStream(MipTypes::DataClass category, bool enable)
    {
        m_impl->enableDataStream(category, enable);
    }

    void InertialNode::resetFilter()
    {
        m_impl->resetFilter();
    }

    bool InertialNode::getAutoInitialization()
    {
        return m_impl->getAutoInitialization();
    }

    void InertialNode::setAutoInitialization(bool enable)
    {
        m_impl->setAutoInitialization(enable);
    }

    void InertialNode::setInitialAttitude(const EulerAngles& attitude)
    {
        m_impl->setInitialAttitude(attitude);
    }

    void InertialNode::setInitialHeading(float heading)
    {
        m_impl->setInitialHeading(heading);
    }

    EulerAngles InertialNode::getSensorToVehicleTransformation()
    {
        return m_impl->getSensorToVehicleTransformation();
    }

    void InertialNode::setSensorToVehicleTransformation(const EulerAngles& angles)
    {
        m_impl->setSensorToVehicleTransformation(angles);
    }

    PositionOffset InertialNode::getSensorToVehicleOffset()
    {
        return m_impl->getSensorToVehicleOffset();
    }

    void InertialNode::setSensorToVehicleOffset(const PositionOffset& offset)
    {
        m_impl->setSensorToVehicleOffset(offset);
    }

    PositionOffset InertialNode::getAntennaOffset()
    {
        return m_impl->getAntennaOffset();
    }

    void InertialNode::setAntennaOffset(const PositionOffset& offset)
    {
        m_impl->setAntennaOffset(offset);
    }

    bool InertialNode::getGNSSAssistedFixControl()
    {
        return m_impl->getGNSSAssistedFixControl();
    }

    void InertialNode::setGNSSAssistedFixControl(bool enableAssistedFix)
    {
        m_impl->setGNSSAssistedFixControl(enableAssistedFix);
    }

    TimeUpdate InertialNode::getGNSSAssistTimeUpdate()
    {
        return m_impl->getGNSSAssistTimeUpdate();
    }

    void InertialNode::setGNSSAssistTimeUpdate(const TimeUpdate& timeUpdate)
    {
        m_impl->setGNSSAssistTimeUpdate(timeUpdate);
    }

    mscl::uint32 InertialNode::getGPSTimeUpdate(MipTypes::TimeFrame timeFrame)
    {
        switch (timeFrame)
        {
        case MipTypes::TIME_FRAME_WEEKS:
            return m_impl->getGPSTimeUpdateWeeks();
        case MipTypes::TIME_FRAME_SECONDS:
            return m_impl->getGPSTimeUpdateSeconds();
        default:
            throw Error_MipCmdFailed("InertialNode::getGPSTimeUpdate  Unknown timeframe");
        }
    }

    void InertialNode::setGPSTimeUpdate(MipTypes::TimeFrame timeFrame, mscl::uint32 time)
    {
        m_impl->setGPSTimeUpdate(timeFrame, time);
    }

    void InertialNode::setConstellationSettings(const ConstellationSettingsData& dataToUse)
    {
        m_impl->setConstellationSettings(dataToUse);
    }

    ConstellationSettingsData InertialNode::getConstellationSettings()
    {
        return m_impl->getConstellationSettings();
    }

    void InertialNode::setSBASSettings(const SBASSettingsData& dataToUse)
    {
        m_impl->setSBASSettings(dataToUse);
    }

    SBASSettingsData InertialNode::getSBASSettings()
    {
        return m_impl->getSBASSettings();
    }

    void InertialNode::setAccelerometerBias(const GeometricVector& biasVector)
    {
        m_impl->setAccelerometerBias(biasVector);
    }

    GeometricVector InertialNode::getAccelerometerBias()
    {
        return m_impl->getAccelerometerBias();
    }

    void InertialNode::setGyroBias(const GeometricVector& biasVector)
    {
        m_impl->setGyroBias(biasVector);
    }

    GeometricVector InertialNode::getGyroBias()
    {
        return m_impl->getGyroBias();
    }

    GeometricVector InertialNode::captureGyroBias(const uint16& samplingTime)
    {
        return m_impl->captureGyroBias(samplingTime);
    }

    void InertialNode::setMagnetometerSoftIronMatrix(const Matrix_3x3& matrix)
    {
        m_impl->setMagnetometerSoftIronMatrix(matrix);
    }

    Matrix_3x3 InertialNode::getMagnetometerSoftIronMatrix()
    {
        return m_impl->getMagnetometerSoftIronMatrix();
    }

    void InertialNode::setMagnetometerHardIronOffset(const GeometricVector& offsetVector)
    {
        m_impl->setMagnetometerHardIronOffset(offsetVector);
    }

    GeometricVector InertialNode::getMagnetometerHardIronOffset()
    {
        return m_impl->getMagnetometerHardIronOffset();
    }

    void InertialNode::setConingAndScullingEnable(bool enable)
    {
        m_impl->setConingAndScullingEnable(enable);
    }

    bool InertialNode::getConingAndScullingEnable()
    {
        return m_impl->getConingAndScullingEnable();
    }

    void InertialNode::setUARTBaudRate(uint32 baudRate)
    {
        m_impl->setUARTBaudRate(baudRate);
    }

    uint32 InertialNode::getUARTBaudRate()
    {
        return m_impl->getUARTBaudRate();
    }

    void InertialNode::setAdvancedLowPassFilterSettings(const AdvancedLowPassFilterData& data)
    {
        m_impl->setAdvancedLowPassFilterSettings(data);
    }

    AdvancedLowPassFilterData InertialNode::getAdvancedLowPassFilterSettings(const AdvancedLowPassFilterData& data)
    {
        return m_impl->getAdvancedLowPassFilterSettings(data);
    }

    void InertialNode::setComplementaryFilterSettings(const ComplementaryFilterData& data)
    {
        m_impl->setComplementaryFilterSettings(data);
    }
    
    ComplementaryFilterData InertialNode::getComplementaryFilterSettings()
    {
        return m_impl->getComplementaryFilterSettings();
    }

    DeviceStatusData InertialNode::getBasicDeviceStatus()
    {
        return m_impl->getBasicDeviceStatus();
    }

    DeviceStatusData InertialNode::getDiagnosticDeviceStatus()
    {
        return m_impl->getDiagnosticDeviceStatus();
    }

    void InertialNode::sendRawRTCM_2_3Message(const RTCMMessage& theMessage)
    {
        m_impl->sendRawRTCM_2_3Message(theMessage);
    }

    void InertialNode::setVehicleDynamicsMode(const InertialTypes::VehicleModeType& mode)
    {
        m_impl->setVehicleDynamicsMode(mode);
    }

    InertialTypes::VehicleModeType InertialNode::getVehicleDynamicsMode()
    {
        return m_impl->getVehicleDynamicsMode();
    }

    void InertialNode::setEstimationControlFlags(const uint16& flags)
    {
        m_impl->setEstimationControlFlags(flags);
    }

    uint16 InertialNode::getEstimationControlFlags()
    {
        return m_impl->getEstimationControlFlags();
    }

    void InertialNode::setGNSS_SourceControl(const InertialTypes::GNSS_Source& gnssSource)
    {
        m_impl->setGNSS_SourceControl(gnssSource);
    }

    InertialTypes::GNSS_Source InertialNode::getGNSS_SourceControl()
    {
        return m_impl->getGNSS_SourceControl();
    }

    void InertialNode::sendExternalGNSSUpdate(const ExternalGNSSUpdateData& gnssUpdateData)
    {
        m_impl->sendExternalGNSSUpdate(gnssUpdateData);
    }

    void InertialNode::setHeadingUpdateControl(const HeadingUpdateOptions& headingUpdateOptions)
    {
        m_impl->setHeadingUpdateControl(headingUpdateOptions);
    }

    HeadingUpdateOptions InertialNode::getHeadingUpdateControl()
    {
        return m_impl->getHeadingUpdateControl();
    }

    void InertialNode::sendExternalHeadingUpdate(const HeadingData& headingData)
    {
        m_impl->sendExternalHeadingUpdate(headingData);
    }

    void InertialNode::sendExternalHeadingUpdate(const HeadingData& headingData, const TimeUpdate& timestamp)
    {
        m_impl->sendExternalHeadingUpdate(headingData, timestamp);
    }
}
