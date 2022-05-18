/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

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
    MipDataPackets InertialNode::getDataPackets(uint32 timeout, uint32 maxPackets)
    {
        MipDataPackets packets;
        m_impl->getDataPackets(packets, timeout, maxPackets);
        return packets;
    }

    uint32 InertialNode::totalPackets()
    {
        return m_impl->totalPackets();
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

    void InertialNode::setFactoryStreamingChannels(InertialTypes::FactoryStreamingOption option)
    {
        m_impl->set(MipTypes::Command::CMD_FACTORY_STREAMING, {
            Value::UINT8(static_cast<uint8>(option)),
            Value::UINT8(0) });
    }

    uint8 InertialNode::getCommunicationMode()
    {
        return m_impl->getCommunicationMode();
    }

    void InertialNode::setCommunicationMode(uint8 communicationMode)
    {
        m_impl->setCommunicationMode(communicationMode);
    }

    bool InertialNode::isDataStreamEnabled(MipTypes::DataClass dataClass)
    {
        return m_impl->isDataStreamEnabled(dataClass);
    }

    void InertialNode::enableDataStream(MipTypes::DataClass dataClass, bool enable, bool resumeStreaming)
    {
        m_impl->enableDataStream(dataClass, enable);

        if (enable && resumeStreaming && !features().useLegacyIdsForEnableDataStream())
        {
            m_impl->resume();
    }
    }

    void InertialNode::resetFilter()
    {
        m_impl->resetFilter();
    }

    void InertialNode::runFilter()
    {
        m_impl->run(MipTypes::CMD_EF_RUN_FILTER);
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

    void InertialNode::enableVerticalGyroConstraint(bool enable)
    {
        m_impl->set(MipTypes::CMD_EF_VERTICAL_GYRO_CONSTRAINT,
        { Value::BOOL(enable) });
    }

    bool InertialNode::verticalGyroConstraintEnabled() const
    {
        return m_impl->get(MipTypes::CMD_EF_VERTICAL_GYRO_CONSTRAINT)[0].as_bool();
    }

    void InertialNode::enableWheeledVehicleConstraint(bool enable)
    {
        m_impl->set(MipTypes::CMD_EF_WHEELED_VEHICLE_CONSTRAINT,
        { Value::BOOL(enable) });
    }

    bool InertialNode::wheeledVehicleConstraintEnabled() const
    {
        return m_impl->get(MipTypes::CMD_EF_WHEELED_VEHICLE_CONSTRAINT)[0].as_bool();
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

    void InertialNode::tareOrientation(const TareAxisValues& axisValue)
    {
        m_impl->tareOrientation(axisValue);
    }

    void InertialNode::setAngularRateZUPT(const ZUPTSettingsData& ZUPTSettings)
    {
        m_impl->setAngularRateZUPT(ZUPTSettings);
    }

    void InertialNode::cmdedVelZUPT()
    {
        m_impl->cmdedVelZUPT();
    }

    void InertialNode::cmdedAngRateZUPT()
    {
        m_impl->cmdedAngRateZUPT();
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

    FilterInitializationValues InertialNode::getInitialFilterConfiguration()
    {
        return m_impl->getInitialFilterConfiguration();
    }

    void InertialNode::setInitialFilterConfiguration(FilterInitializationValues filterConfig)
    {
        m_impl->setInitialFilterConfiguration(filterConfig);
    }

    EulerAngles InertialNode::getSensorToVehicleRotation_eulerAngles()
    {
        return m_impl->getSensorToVehicleRotation();
    }

    void InertialNode::setSensorToVehicleRotation_eulerAngles(const EulerAngles& angles)
    {
        m_impl->setSensorToVehicleRotation(angles);
    }

    Matrix_3x3 InertialNode::getSensorToVehicleRotation_matrix()
    {
        return Matrix_3x3(m_impl->get(MipTypes::CMD_EF_SENS_VEHIC_FRAME_ROTATION_DCM));
    }

    void InertialNode::setSensorToVehicleRotation_matrix(const Matrix_3x3& dcm)
    {
        m_impl->set(MipTypes::CMD_EF_SENS_VEHIC_FRAME_ROTATION_DCM,
            dcm.asMipFieldValues());
    }

    Quaternion InertialNode::getSensorToVehicleRotation_quaternion()
    {
        return Quaternion(m_impl->get(MipTypes::CMD_EF_SENS_VEHIC_FRAME_ROTATION_QUAT));
    }

    void InertialNode::setSensorToVehicleRotation_quaternion(const Quaternion& rotation)
    {
        m_impl->set(MipTypes::CMD_EF_SENS_VEHIC_FRAME_ROTATION_QUAT,
            rotation.asMipFieldValues());
    }

    EulerAngles InertialNode::getSensorToVehicleTransform_eulerAngles()
    {
        MipFieldValues res = m_impl->get(MipTypes::CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_EULER);
        return EulerAngles(res[0].as_float(), res[1].as_float(), res[2].as_float());
    }

    void InertialNode::setSensorToVehicleTransform_eulerAngles(const EulerAngles& ea)
    {
        MipFieldValues params = {
            Value::FLOAT(ea.roll()),
            Value::FLOAT(ea.pitch()),
            Value::FLOAT(ea.yaw())
        };
        m_impl->set(MipTypes::CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_EULER, params);
    }

    Matrix_3x3 InertialNode::getSensorToVehicleTransform_matrix()
    {
        return Matrix_3x3(m_impl->get(MipTypes::CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_DCM));
    }

    void InertialNode::setSensorToVehicleTransform_matrix(const Matrix_3x3& dcm)
    {
        m_impl->set(MipTypes::CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_DCM,
            dcm.asMipFieldValues());
    }

    Quaternion InertialNode::getSensorToVehicleTransform_quaternion()
    {
        return Quaternion(m_impl->get(MipTypes::CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_QUAT));
    }

    void InertialNode::setSensorToVehicleTransform_quaternion(const Quaternion& transformation)
    {
        m_impl->set(MipTypes::CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_QUAT,
            transformation.asMipFieldValues());
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

    void InertialNode::saveMagnetometerCaptureAutoCalibration()
    {
        m_impl->saveMagnetometerCaptureAutoCalibration();
    }

    void InertialNode::findMagnetometerCaptureAutoCalibration()
    {
        m_impl->findMagnetometerCaptureAutoCalibration();
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

    void InertialNode::setGPSDynamicsMode(const InertialTypes::GPSDynamicsMode& data)
    {
        std::vector<uint8> collection;
        collection.push_back(static_cast<uint8>(data));
        m_impl->setUint8s(MipTypes::Command::CMD_GPS_DYNAMICS_MODE, collection);
    }

    InertialTypes::GPSDynamicsMode InertialNode::getGPSDynamicsMode() const
    {
        uint8 mode = m_impl->getUint8s(MipTypes::Command::CMD_GPS_DYNAMICS_MODE)[0];
        return static_cast<InertialTypes::GPSDynamicsMode>(mode);
    }

    void InertialNode::setDevicePowerState(const InertialTypes::DeviceSelector& device, const InertialTypes::PowerState& data)
    {
        std::vector<uint8> collection;
        collection.push_back(static_cast<uint8>(device));
        collection.push_back(static_cast<uint8>(data));
        m_impl->setUint8s(MipTypes::Command::CMD_POWER_STATES, collection);
    }

    InertialTypes::PowerState InertialNode::getDevicePowerState(const InertialTypes::DeviceSelector& device) const
    {
        std::vector<uint8> params;
        params.push_back(static_cast<uint8>(device));
        uint8 data = m_impl->getUint8s(MipTypes::Command::CMD_POWER_STATES, params)[1];
        return static_cast<InertialTypes::PowerState>(data);
    }

    void InertialNode::setDeviceStreamFormat(const InertialTypes::DeviceSelector& device, const InertialTypes::StreamFormat& data)
    {
        std::vector<uint8> collection;
        collection.push_back(static_cast<uint8>(device));
        collection.push_back(static_cast<uint8>(data));
        m_impl->setUint8s(MipTypes::Command::CMD_DATA_STREAM_FORMAT, collection);
    }

    InertialTypes::StreamFormat InertialNode::getDeviceStreamFormat(const InertialTypes::DeviceSelector& device) const
    {
        std::vector<uint8> params;
        params.push_back(static_cast<uint8>(device));
        uint8 data = m_impl->getUint8s(MipTypes::Command::CMD_DATA_STREAM_FORMAT, params)[1];
        return static_cast<InertialTypes::StreamFormat>(data);
    }

    void InertialNode::setSignalConditioningSettings(const SignalConditioningValues& data)
    {
        m_impl->setSignalConditioningSettings(data);
    }

    SignalConditioningValues InertialNode::getSignalConditioningSettings() const
    {
        return m_impl->getSignalConditioningSettings();
    }

    void InertialNode::setEnableDisableMeasurements(const EnableDisableMeasurements& data)
    {
        std::vector<uint16> collection;
        collection.push_back(data.measurementOptions);
        m_impl->setUint16s(MipTypes::Command::CMD_EF_ENABLE_DISABLE_MEASUREMENTS, collection);
    }

    EnableDisableMeasurements InertialNode::getEnableDisableMeasurements() const
    {
        EnableDisableMeasurements r;
        r.measurementOptions = m_impl->getUint16s(MipTypes::Command::CMD_EF_ENABLE_DISABLE_MEASUREMENTS)[0];
        return r;
    }

    void InertialNode::setGravityNoiseMinimum(const GeometricVector& data)
    {
        GeometricVectors collection;
        collection.push_back(data);
        m_impl->setGeometricVectors(MipTypes::Command::CMD_EF_GRAVITY_NOISE_MINIMUM, collection);
    }

    GeometricVector InertialNode::getGravityNoiseMinimum() const
    {
        return m_impl->getGeometricVectors(MipTypes::Command::CMD_EF_GRAVITY_NOISE_MINIMUM)[0];
    }

    void InertialNode::sendExternalHeadingUpdate(const HeadingData& headingData)
    {
        m_impl->sendExternalHeadingUpdate(headingData);
    }

    void InertialNode::sendExternalHeadingUpdate(const HeadingData& headingData, const TimeUpdate& timestamp)
    {
        m_impl->sendExternalHeadingUpdate(headingData, timestamp);
    }

    bool InertialNode::aidingMeasurementEnabled(InertialTypes::AidingMeasurementSource aidingSource) const
    {
        MipFieldValues data = m_impl->get(MipTypes::CMD_EF_AIDING_MEASUREMENT_ENABLE,
            { Value::UINT16(static_cast<uint16>(aidingSource)) });
        
        // command echoes aiding source and current enabled setting - only need to return enabled
        return data[1].as_bool();
    }

    void InertialNode::enableDisableAidingMeasurement(InertialTypes::AidingMeasurementSource aidingSource, bool enable)
    {
        m_impl->set(MipTypes::CMD_EF_AIDING_MEASUREMENT_ENABLE, {
            Value::UINT16(static_cast<uint16>(aidingSource)),
            Value::BOOL(enable) });
    }

    AutoAdaptiveFilterOptions InertialNode::getAdaptiveFilterOptions() const
    {
        MipFieldValues data = m_impl->get(MipTypes::CMD_EF_ADAPTIVE_FILTER_OPTIONS);
        return AutoAdaptiveFilterOptions(
            static_cast<InertialTypes::AutoAdaptiveFilteringLevel>(data[0].as_uint8()),
            data[1].as_uint16());
    }

    void InertialNode::setAdaptiveFilterOptions(AutoAdaptiveFilterOptions options)
    {
        m_impl->set(MipTypes::CMD_EF_ADAPTIVE_FILTER_OPTIONS, {
            Value::UINT8(static_cast<uint8>(options.level)),
            Value::UINT16(options.timeLimit) });
    }

    PositionOffset InertialNode::getMultiAntennaOffset(uint8 receiverId) const
    {
        MipFieldValues data = m_impl->get(MipTypes::CMD_EF_MULTI_ANTENNA_OFFSET, {
            Value::UINT8(receiverId) });

        // skip data[0]: echoed receiver ID
        return PositionOffset(
            data[1].as_float(),  // x
            data[2].as_float(),  // y
            data[3].as_float()); // z
    }

    void InertialNode::setMultiAntennaOffset(uint8 receiverId, PositionOffset offset)
    {
        m_impl->set(MipTypes::CMD_EF_MULTI_ANTENNA_OFFSET, {
            Value::UINT8(receiverId),
            Value::FLOAT(offset.x()),
            Value::FLOAT(offset.y()),
            Value::FLOAT(offset.z()) });
    }

    InertialTypes::PpsSource InertialNode::getPpsSource() const
    {
        MipFieldValues data = m_impl->get(MipTypes::CMD_PPS_SOURCE);
        return static_cast<InertialTypes::PpsSource>(data[0].as_uint8());
    }

    void InertialNode::setPpsSource(InertialTypes::PpsSource ppsSource)
    {
        m_impl->set(MipTypes::CMD_PPS_SOURCE, { Value::UINT8(static_cast<uint8>(ppsSource)) });
    }

    OdometerConfiguration InertialNode::getOdometerConfig() const
    {
        MipFieldValues data = m_impl->get(MipTypes::CMD_ODOMETER_SETTINGS);
        OdometerConfiguration config;
        config.mode(static_cast<OdometerConfiguration::Mode>(data[0].as_uint8()));
        config.scaling(data[1].as_float());
        config.uncertainty(data[2].as_float());
        return config;
    }

    void InertialNode::setOdometerConfig(OdometerConfiguration config)
    {
        m_impl->set(MipTypes::CMD_ODOMETER_SETTINGS, {
            Value::UINT8(static_cast<uint8>(config.mode())),
            Value::FLOAT(config.scaling()),
            Value::FLOAT(config.uncertainty())
        });
    }

    SensorRange InertialNode::getSensorRange(SensorRange::Type sensorRangeType) const
    {
        MipFieldValues ret = m_impl->get(MipTypes::Command::CMD_SENSOR_RANGE, {
            Value::UINT8(static_cast<uint8>(sensorRangeType)) });
        uint8 rangeIndex = ret[1].as_uint8();

        SensorRanges rangeOptions = features().supportedSensorRanges(sensorRangeType);

        for (SensorRange range : rangeOptions)
        {
            if (range.id() == rangeIndex)
            {
                return range;
            }
        }

        return SensorRange(sensorRangeType, rangeIndex);
    }

    void InertialNode::setSensorRange(SensorRange range)
    {
        m_impl->set(MipTypes::Command::CMD_SENSOR_RANGE, {
            Value::UINT8(static_cast<uint8>(range.type())), // sensor range type
            Value::UINT8(range.id()) }); // range index
    }

    void InertialNode::setSensorRange(SensorRange::Type type, uint8 rangeId)
    {
        m_impl->set(MipTypes::Command::CMD_SENSOR_RANGE, {
            Value::UINT8(static_cast<uint8>(type)), // sensor range type
            Value::UINT8(rangeId) }); // range index
    }

    GpioConfiguration InertialNode::getGpioConfig(uint8 pin) const
    {
        MipFieldValues data = m_impl->get(MipTypes::CMD_GPIO_CONFIGURATION, {
            Value::UINT8(pin) });
        GpioConfiguration config;
        config.pin = data[0].as_uint8();
        config.feature = static_cast<GpioConfiguration::Feature>(data[1].as_uint8());
        config.behavior = data[2].as_uint8();
        config.pinModeValue(data[3].as_uint8());
        return config;
    }

    void InertialNode::setGpioConfig(GpioConfiguration config)
    {
        m_impl->set(MipTypes::CMD_GPIO_CONFIGURATION, {
            Value::UINT8(static_cast<uint8>(config.pin)),
            Value::INT8(static_cast<uint8>(config.feature)),
            Value::INT8(static_cast<uint8>(config.behavior)),
            Value::INT8(static_cast<uint8>(config.pinModeValue()))
        });
    }

    EventActionConfiguration InertialNode::getEventActionConfig(uint8 instance)
    {
        const ByteStream response = m_impl->get_RawResponseData(MipTypes::CMD_EVENT_ACTION_CONFIGURATION, {
            Value::UINT8(instance)    
        });
        DataBuffer data(response);

        EventActionConfiguration config;
        config.instance = data.read_uint8();
        config.trigger = data.read_uint8();
        config.type = static_cast<EventActionConfiguration::Type>(data.read_uint8());

        switch(config.type)
        {
        case EventActionConfiguration::Type::NONE:
            break;
        case EventActionConfiguration::Type::GPIO:
            config.parameters.gpio.pin = data.read_uint8();
            config.parameters.gpio.mode = static_cast<EventActionGpioParameters::Mode>(data.read_uint8());
            break;
        case EventActionConfiguration::Type::MESSAGE:
            config.parameters.message.descriptorSet = static_cast<MipTypes::DataClass>(data.read_uint8());
            config.parameters.message.decimation = SampleRate::Decimation(data.read_uint16());
            config.parameters.message.numFields = data.read_uint8();
            for (uint8 i = 0; i < std::min({static_cast<size_t>(config.parameters.message.numFields), config.parameters.message.descriptors.size()}); i++)
                config.parameters.message.descriptors[i] = static_cast<MipTypes::ChannelField>(Utils::make_uint16(static_cast<uint8>(config.parameters.message.descriptorSet), data.read_uint8(), Utils::Endianness::bigEndian));
            break;
        default:
            break;
        }

        return config;
    }

    void InertialNode::setEventActionConfig(EventActionConfiguration config)
    {
        mscl::MipFieldValues mip_values = {
            Value::UINT8(static_cast<uint8>(config.instance)),
            Value::UINT8(static_cast<uint8>(config.trigger)),
            Value::UINT8(static_cast<uint8>(config.type))
        };

        switch(config.type)
        {
        case EventActionConfiguration::Type::NONE:
            break;
        case EventActionConfiguration::Type::GPIO:
        {
            mip_values.push_back(Value::UINT8(static_cast<uint8>(config.parameters.gpio.pin)));
            mip_values.push_back(Value::UINT8(static_cast<uint8>(config.parameters.gpio.mode)));
            break;
        }
        case EventActionConfiguration::Type::MESSAGE:
        {
            mip_values.push_back(Value::UINT8(static_cast<uint8>(config.parameters.message.descriptorSet)));
            mip_values.push_back(Value::UINT16(static_cast<uint16>(config.parameters.message.decimation.toDecimation(m_impl->getDataRateBase(config.parameters.message.descriptorSet)))));
            mip_values.push_back(Value::UINT8(static_cast<uint8>(config.parameters.message.numFields)));
            for (uint8 i = 0; i < std::min({static_cast<size_t>(config.parameters.message.numFields), config.parameters.message.descriptors.size()}); i++)
                mip_values.push_back(Value::UINT8(static_cast<uint8>(Utils::lsb(static_cast<uint16>(config.parameters.message.descriptors[i])))));
            break;
        }
        default:
            break;
        }
        m_impl->set(MipTypes::CMD_EVENT_ACTION_CONFIGURATION, mip_values);
    }

    bool InertialNode::getGpioState(uint8 pin) const
    {
        MipFieldValues data = m_impl->get(MipTypes::CMD_GPIO_STATE, {
            Value::UINT8(pin) });

        return data[1].as_bool();
    }

    void InertialNode::setGpioState(uint8 pin, bool state)
    {
        m_impl->set(MipTypes::CMD_GPIO_STATE, {
            Value::UINT8(pin),
            Value::BOOL(state)
            });
    }

    EventControlMode InertialNode::getEventTriggerMode(const uint8 instance) const
    {
        const MipFieldValues data = m_impl->get(MipTypes::CMD_EVENT_CONTROL, {
            Value::UINT8(instance) });

        return static_cast<EventControlMode>(data[1].as_uint8());
    }

    void InertialNode::setEventTriggerMode(const uint8 instance, const EventControlMode mode) const
    {
        m_impl->set(MipTypes::CMD_EVENT_CONTROL, {
            Value::UINT8(instance),
            Value::UINT8(static_cast<uint8>(mode))
        });
    }

    EventTriggerConfiguration InertialNode::getEventTriggerConfig(const uint8 instance) const
    {
        const ByteStream response = m_impl->get_RawResponseData(MipTypes::CMD_EVENT_TRIGGER_CONFIGURATION, {
                                                              Value::UINT8(instance) });
        DataBuffer data(response);

        EventTriggerConfiguration config;

        config.instance = data.read_uint8();
        config.trigger  = static_cast<EventTriggerConfiguration::Type>(data.read_uint8());

        switch (config.trigger)
        {
        case EventTriggerConfiguration::GPIO_TRIGGER:
            config.parameters.gpio.pin  = data.read_uint8();
            config.parameters.gpio.mode = static_cast<EventTriggerGpioParameter::Mode>(data.read_uint8());
            break;

        case EventTriggerConfiguration::THRESHOLD_TRIGGER:
        {
            const MipTypes::ChannelField field = static_cast<MipTypes::ChannelField>(data.read_uint16());
            config.parameters.threshold.channel(field, data.read_uint8());
            config.parameters.threshold.type          = static_cast<EventTriggerThresholdParameter::Type>(data.read_uint8());
            config.parameters.threshold.lowThreshold  = data.read_double();
            config.parameters.threshold.highThreshold = data.read_double();
            break;
        }

        case EventTriggerConfiguration::COMBINATION_TRIGGER:
            config.parameters.combination.logicTable = data.read_uint16();

            for (uint8& inputTrigger : config.parameters.combination.inputTriggers)
            {
                inputTrigger = data.read_uint8();
            }
            break;

        case EventTriggerConfiguration::NONE:
            break;
        }

        return config;
    }

    void InertialNode::setEventTriggerConfig(const EventTriggerConfiguration config) const
    {
        MipFieldValues values = {
            Value::UINT8(config.instance),
            Value::UINT8(static_cast<uint8>(config.trigger))
        };

        switch (config.trigger)
        {
        case EventTriggerConfiguration::GPIO_TRIGGER:
            values.push_back(Value::UINT8(config.parameters.gpio.pin));
            values.push_back(Value::UINT8(static_cast<uint8>(config.parameters.gpio.mode)));
            break;

        case EventTriggerConfiguration::THRESHOLD_TRIGGER:
        {
            const EventTriggerThresholdParameter threshold = config.parameters.threshold;
            values.push_back(Value::UINT16(static_cast<uint16>(threshold.channelField())));
            values.push_back(Value::UINT8(threshold.channelIndex()));
            values.push_back(Value::UINT8(static_cast<uint8>(threshold.type)));
            values.push_back(Value::DOUBLE(threshold.lowThreshold));
            values.push_back(Value::DOUBLE(threshold.highThreshold));
            break;
        }
        case EventTriggerConfiguration::COMBINATION_TRIGGER:
        {
            values.push_back(Value::UINT16(config.parameters.combination.logicTable));

            for (const uint8 inputTrigger : config.parameters.combination.inputTriggers)
            {
                values.push_back(Value::UINT8(inputTrigger));
            }
            break;
        }
        case EventTriggerConfiguration::NONE:
            break;
        }

        m_impl->set(MipTypes::CMD_EVENT_TRIGGER_CONFIGURATION, values);
    }

    AntennaLeverArmCalConfiguration InertialNode::getAntennaLeverArmCal() const
    {
        MipFieldValues data = m_impl->get(MipTypes::CMD_EF_GNSS_ANTENNA_LEVER_ARM_CAL);
        AntennaLeverArmCalConfiguration config;
        config.enabled = data[0].as_uint8() > 0;
        config.maxOffsetError = data[1].as_float();
        return config;
    }

    void InertialNode::setAntennaLeverArmCal(AntennaLeverArmCalConfiguration config)
    {
        m_impl->set(MipTypes::CMD_EF_GNSS_ANTENNA_LEVER_ARM_CAL, {
            Value::UINT8(config.enabled ? 1 : 0),
            Value::FLOAT(config.maxOffsetError)
        });
    }

    PositionReferenceConfiguration InertialNode::getRelativePositionReference() const
    {
        MipFieldValues data = m_impl->get(MipTypes::CMD_EF_RELATIVE_POSITION_REF);
        PositionReferenceConfiguration ref;
        ref.autoConfig = data[0].as_uint8() == 0; // saved to device as enum - auto: 0, manual: 1
        ref.position = Position(
            data[2].as_double(), data[3].as_double(), data[4].as_double(),
            static_cast<PositionVelocityReferenceFrame>(data[1].as_uint8()));

        return ref;
    }

    void InertialNode::setRelativePositionReference(PositionReferenceConfiguration ref)
    {
        m_impl->set(MipTypes::CMD_EF_RELATIVE_POSITION_REF, {
            Value::UINT8((ref.autoConfig ? 0x00 : 0x01)), // saved to device as enum - auto: 0, manual: 1
            Value::UINT8(static_cast<uint8>(ref.position.referenceFrame)),
            Value::DOUBLE(ref.position.x()),
            Value::DOUBLE(ref.position.y()),
            Value::DOUBLE(ref.position.z()),
        });
    }

    void InertialNode::sendExternalSpeedMeasurementUpdate(float tow, float speed, float unc)
    {
        m_impl->run(MipTypes::Command::CMD_EF_EXTERN_SPEED_UPDATE, {
            Value::UINT8(1), // reserved (source, currently should always be 1)
            Value::FLOAT(tow),
            Value::FLOAT(speed),
            Value::FLOAT(unc)
        });
    }

    PositionOffset InertialNode::getSpeedMeasurementOffset() const
    {
        MipFieldValues data = m_impl->get(MipTypes::CMD_EF_SPEED_MEASUREMENT_OFFSET, {
            Value::UINT8(1) // reserved, placeholder source value
        });

        // skip first element - reserved, placeholder source value
        return PositionOffset(data[1].as_float(), data[2].as_float(), data[3].as_float());
    }

    void InertialNode::setSpeedMeasurementOffset(PositionOffset offset)
    {
        m_impl->set(MipTypes::CMD_EF_SPEED_MEASUREMENT_OFFSET, {
            Value::UINT8(1), // reserved, placeholder source value
            Value::FLOAT(offset.x()),
            Value::FLOAT(offset.y()),
            Value::FLOAT(offset.z()),
        });
    }

    GnssSignalConfiguration InertialNode::getGnssSignalConfig() const
    {
        MipFieldValues data = m_impl->get(MipTypes::CMD_GNSS_SIGNAL_CONFIG);
        GnssSignalConfiguration config;
        config.gpsSignalValue(data[0].as_uint8());
        config.glonassSignalValue(data[1].as_uint8());
        config.galileoSignalValue(data[2].as_uint8());
        config.beidouSignalValue(data[3].as_uint8());
        return config;
    }

    void InertialNode::setGnssSignalConfig(GnssSignalConfiguration config)
    {
        m_impl->set(MipTypes::CMD_GNSS_SIGNAL_CONFIG, {
            Value::UINT8(config.gpsSignalValue()),
            Value::UINT8(config.glonassSignalValue()),
            Value::UINT8(config.galileoSignalValue()),
            Value::UINT8(config.beidouSignalValue()),
            Value::UINT32(0)
        });
    }

    bool InertialNode::rtkEnabled() const
    {
        MipFieldValues data = m_impl->get(MipTypes::CMD_GNSS_RTK_CONFIG);
        return data[0].as_uint8() > 0;
    }

    void InertialNode::enableRtk(bool enable)
    {
        m_impl->set(MipTypes::CMD_GNSS_RTK_CONFIG, {
            Value::UINT8(enable ? 1 : 0),
            Value::UINT8(0),
            Value::UINT8(0),
            Value::UINT8(0)
        });
    }

    EventTriggerStatus InertialNode::getEventTriggerStatus(const std::vector<uint8> instances) const
    {
        std::vector<Value> specifier = { Value::UINT8(static_cast<uint8>(instances.size())) };
        
        for (const uint8& instance : instances)
        {
            specifier.push_back(Value::UINT8(instance));
        }
        
        const MipFieldValues data = m_impl->get(MipTypes::CMD_EVENT_TRIGGER_STATUS, specifier);
        
        const uint8 count = data[0].as_uint8();
        
        EventTriggerStatus status;
        
        // Data values start at index 1 and have 2 data entries
        for (int index = 1; index < count * 2 + 1; index += 2)
        {
            const int instanceIndex = (index - 1) / 2;

            status.push_back({
                static_cast<EventTriggerConfiguration::Type>(data[index].as_uint8()), // type
                // If instances count is 0, user requested all triggers
                instances.empty() ?
                    static_cast<uint8>(instanceIndex + 1):
                    instances[instanceIndex],                                            // instanceId
                data[index + 1].as_uint8()                                               // status
            });
        }
        
        return status;
    }
}
