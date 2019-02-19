/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

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

    const MipNodeFeatures& InertialNode::features() const
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

    DeviceState InertialNode::lastDeviceState() const
    {
        return m_impl->lastDeviceState();
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

    void InertialNode::pollData(MipTypes::DataClass dataClass, const MipTypes::MipChannelFields& fields /*= MipTypes::MipChannelFields()*/)
    {
        m_impl->pollData(dataClass, fields);
    }

    uint16 InertialNode::getDataRateBase(MipTypes::DataClass dataClass)
    { 
        return m_impl->getDataRateBase(dataClass);
    }

    MipChannels InertialNode::getActiveChannelFields(MipTypes::DataClass dataClass)
    { 
        return m_impl->getMessageFormat(dataClass);
    }

    void InertialNode::setActiveChannelFields(MipTypes::DataClass dataClass, const MipChannels& channels)
    { 
        m_impl->setMessageFormat(dataClass, channels);
    }

    void InertialNode::saveActiveChannelFields(MipTypes::DataClass dataClass)
    {
        m_impl->saveMessageFormat(dataClass);
    }

    uint8 InertialNode::getCommunicationMode()                                                    
    { 
        return m_impl->getCommunicationMode(); 
    }

    void InertialNode::setCommunicationMode(uint8 communicationMode)                            
    { 
        m_impl->setCommunicationMode(communicationMode); 
    }

    void InertialNode::enableDataStream(MipTypes::DataClass dataClass, bool enable)
    {
        m_impl->enableDataStream(dataClass, enable);
    }

    void InertialNode::resetFilter()
    {
        m_impl->resetFilter();
    }

    bool InertialNode::getAltitudeAid()
    {
        return m_impl->getAltitudeAid();
    }

    void InertialNode::setAltitudeAid(bool enable)
    {
        m_impl->setAltitudeAid(enable);
    }

    bool InertialNode::getPitchRollAid()
    {
        return m_impl->getPitchRollAid();
    }

    void InertialNode::setPitchRollAid(bool enable)
    {
        m_impl->setPitchRollAid(enable);
    }

    ZUPTSettingsData InertialNode::getVelocityZUPT()
    {
        return m_impl->getVelocityZUPT();
    }

    void InertialNode::setVelocityZUPT(const ZUPTSettingsData& ZUPTSettings)
    {
        m_impl->setVelocityZUPT(ZUPTSettings);
    }

    ZUPTSettingsData InertialNode::getAngularRateZUPT()
    {
        return m_impl->getAngularRateZUPT();
    }

    void InertialNode::setAngularRateZUPT(const ZUPTSettingsData& ZUPTSettings)
    {
        m_impl->setAngularRateZUPT(ZUPTSettings);
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

    void InertialNode::setAdvancedLowPassFilterSettings(const AdvancedLowPassFilterConfig& data)
    {
        for (size_t i = 0; i < data.size(); i++)
        {
            m_impl->setAdvancedLowPassFilterSettings(data[i]);
        }
    }

    AdvancedLowPassFilterConfig InertialNode::getAdvancedLowPassFilterSettings(const MipTypes::MipChannelFields& dataDescriptors)
    {
        AdvancedLowPassFilterConfig data;
        for (size_t i = 0; i < dataDescriptors.size(); i++)
        {
            data.push_back(m_impl->getAdvancedLowPassFilterSettings(dataDescriptors[i]));
        }

        return data;
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

    void InertialNode::setEstimationControlFlags(const EstimationControlOptions& flags)
    {
        m_impl->setEstimationControlFlags(flags);
    }

    EstimationControlOptions InertialNode::getEstimationControlFlags()
    {
        return m_impl->getEstimationControlFlags();
    }

    void InertialNode::setInclinationSource(const GeographicSourceOptions& options)
    {
        m_impl->setInclinationSource(options);
    }

    GeographicSourceOptions InertialNode::getInclinationSource()
    {
        return m_impl->getInclinationSource();
    }

    void InertialNode::setDeclinationSource(const GeographicSourceOptions& options)
    {
        m_impl->setDeclinationSource(options);
    }

    GeographicSourceOptions InertialNode::getDeclinationSource()
    {
        return m_impl->getDeclinationSource();
    }

    void InertialNode::setMagneticFieldMagnitudeSource(const GeographicSourceOptions& options)
    {
        m_impl->setMagneticFieldMagnitudeSource(options);
    }

    GeographicSourceOptions InertialNode::getMagneticFieldMagnitudeSource()
    {
        return m_impl->getMagneticFieldMagnitudeSource();
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

    void InertialNode::setGravityErrorAdaptiveMeasurement(const AdaptiveMeasurementData& data)
    {
        m_impl->setAdaptiveMeasurement(MipTypes::Command::CMD_EF_GRAV_MAGNITUDE_ERR_ADAPT_MEASURE, data);
    }

    AdaptiveMeasurementData InertialNode::getGravityErrorAdaptiveMeasurement()
    {
        return m_impl->getAdaptiveMeasurement(MipTypes::Command::CMD_EF_GRAV_MAGNITUDE_ERR_ADAPT_MEASURE);
    }

    void InertialNode::setMagnetometerErrorAdaptiveMeasurement(const AdaptiveMeasurementData& data)
    {
        m_impl->setAdaptiveMeasurement(MipTypes::Command::CMD_EF_MAG_MAGNITUDE_ERR_ADAPT_MEASURE, data);
    }

    AdaptiveMeasurementData InertialNode::getMagnetometerErrorAdaptiveMeasurement()
    {
        return m_impl->getAdaptiveMeasurement(MipTypes::Command::CMD_EF_MAG_MAGNITUDE_ERR_ADAPT_MEASURE);
    }

    void InertialNode::setMagDipAngleErrorAdaptiveMeasurement(const AdaptiveMeasurementData& data)
    {
        m_impl->setAdaptiveMeasurement(MipTypes::Command::CMD_EF_MAG_DIP_ANGLE_ERR_ADAPT_MEASURE, data);
    }

    AdaptiveMeasurementData InertialNode::getMagDipAngleErrorAdaptiveMeasurement()
    {
        return m_impl->getAdaptiveMeasurement(MipTypes::Command::CMD_EF_MAG_DIP_ANGLE_ERR_ADAPT_MEASURE);
    }

    void InertialNode::setMagNoiseStandardDeviation(const GeometricVector& data)
    {
        GeometricVectors collection;
        collection.push_back(data);
        m_impl->setGeometricVectors(MipTypes::Command::CMD_EF_MAG_NOISE_STD_DEV, collection);
    }

    GeometricVector InertialNode::getMagNoiseStandardDeviation()
    {
        return m_impl->getGeometricVectors(MipTypes::Command::CMD_EF_MAG_NOISE_STD_DEV)[0];
    }

    void InertialNode::setGravNoiseStandardDeviation(const GeometricVector& data)
    {
        GeometricVectors collection;
        collection.push_back(data);
        m_impl->setGeometricVectors(MipTypes::Command::CMD_EF_GRAVITY_NOISE_STD_DEV, collection);
    }

    GeometricVector InertialNode::getGravNoiseStandardDeviation()
    {
        return m_impl->getGeometricVectors(MipTypes::Command::CMD_EF_GRAVITY_NOISE_STD_DEV)[0];
    }

    void InertialNode::setAccelNoiseStandardDeviation(const GeometricVector& data)
    {
        GeometricVectors collection;
        collection.push_back(data);
        m_impl->setGeometricVectors(MipTypes::Command::CMD_EF_ACCEL_WHT_NSE_STD_DEV, collection);
    }

    GeometricVector InertialNode::getAccelNoiseStandardDeviation()
    {
        return m_impl->getGeometricVectors(MipTypes::Command::CMD_EF_ACCEL_WHT_NSE_STD_DEV)[0];
    }

    void InertialNode::setGyroNoiseStandardDeviation(const GeometricVector& data)
    {
        GeometricVectors collection;
        collection.push_back(data);
        m_impl->setGeometricVectors(MipTypes::Command::CMD_EF_GYRO_WHT_NSE_STD_DEV, collection);
    }

    GeometricVector InertialNode::getGyroNoiseStandardDeviation()
    {
        return m_impl->getGeometricVectors(MipTypes::Command::CMD_EF_GYRO_WHT_NSE_STD_DEV)[0];
    }

    void InertialNode::setPressureAltNoiseStandardDeviation(const float& data)
    {
        std::vector<float> collection;
        collection.push_back(data);
        m_impl->setFloats(MipTypes::Command::CMD_EF_PRESS_ALT_NOISE_STD_DEV, collection);
    }

    float InertialNode::getPressureAltNoiseStandardDeviation()
    {
        return m_impl->getFloats(MipTypes::Command::CMD_EF_PRESS_ALT_NOISE_STD_DEV)[0];
    }

    void InertialNode::setHardIronOffsetProcessNoise(const GeometricVector& data)
    {
        GeometricVectors collection;
        collection.push_back(data);
        m_impl->setGeometricVectors(MipTypes::Command::CMD_EF_HARD_IRON_OFFSET_PROCESS_NOISE, collection);
    }

    GeometricVector InertialNode::getHardIronOffsetProcessNoise()
    {
        return m_impl->getGeometricVectors(MipTypes::Command::CMD_EF_HARD_IRON_OFFSET_PROCESS_NOISE)[0];
    }

    void InertialNode::setAccelBiasModelParams(const GeometricVectors& data)
    {
        m_impl->setGeometricVectors(MipTypes::Command::CMD_EF_ACCEL_BIAS_MODEL_PARAMS, data);
    }

    GeometricVectors InertialNode::getAccelBiasModelParams()
    {
        return m_impl->getGeometricVectors(MipTypes::Command::CMD_EF_ACCEL_BIAS_MODEL_PARAMS);
    }

    void InertialNode::setGyroBiasModelParams(const GeometricVectors& data)
    {
        m_impl->setGeometricVectors(MipTypes::Command::CMD_EF_GYRO_BIAS_MODEL_PARAMS, data);
    }

    GeometricVectors InertialNode::getGyroBiasModelParams()
    {
        return m_impl->getGeometricVectors(MipTypes::Command::CMD_EF_GYRO_BIAS_MODEL_PARAMS);
    }

    void InertialNode::setSoftIronMatrixProcessNoise(const Matrix_3x3& data)
    {
        Matrix_3x3s collection;
        collection.push_back(data);
        m_impl->setMatrix3x3s(MipTypes::Command::CMD_EF_SOFT_IRON_OFFSET_PROCESS_NOISE, collection);
    }

    Matrix_3x3 InertialNode::getSoftIronMatrixProcessNoise()
    {
        return m_impl->getMatrix3x3s(MipTypes::Command::CMD_EF_SOFT_IRON_OFFSET_PROCESS_NOISE)[0];
    }

    void InertialNode::setFixedReferencePosition(const FixedReferencePositionData& data)
    {
        m_impl->setFixedReferencePosition(data);
    }

    FixedReferencePositionData InertialNode::getFixedReferencePosition()
    {
        return m_impl->getFixedReferencePosition();
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
