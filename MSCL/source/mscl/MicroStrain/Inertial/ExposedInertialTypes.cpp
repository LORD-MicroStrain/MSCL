#include "stdafx.h"
#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"
#include "ExposedInertialTypes.h"

namespace mscl
{
    //////////  Matrix  //////////

    Matrix_3x3::Matrix_3x3(float i00, float i01, float i02, float i10, float i11, float i12, float i20, float i21, float i22)
    {
        // Not sure why I need firstArray.  Just putting this list in the initialization below doesn't compile.
        std::array<float, 3> firstRow{ i00, i01, i02 };
        m_array = { firstRow,{ i10, i11, i12 },{ i20, i21, i22 } };
    }

    Matrix_3x3::~Matrix_3x3()
    { }

    void Matrix_3x3::set(uint8 row, uint8 col, float value)
    {
        m_array[row][col] = value;
    }


    float Matrix_3x3::operator() (uint8 row, uint8 col) const
    {
        return m_array.at(row).at(col);
    }

    float Matrix_3x3::at(uint8 row, uint8 col) const
    {
        return (*this)(row, col);
    }

    //////////  GeometricVector  //////////

    GeometricVector::GeometricVector(float x_init, float y_init, float z_init) :
        x(x_init),
        y(y_init),
        z(z_init)
    { }

    GeometricVector::GeometricVector() :
        x(0),
        y(0),
        z(0)
    { }

    GeometricVector::~GeometricVector()
    { }



    //////////  TimeUpdate  //////////

    TimeUpdate::TimeUpdate(double timeOfWeek, uint16 weekNumber, float timeAccuracy):
        m_timeOfWeek(timeOfWeek),
        m_weekNumber(weekNumber),
        m_timeAccuracy(timeAccuracy)
    {
    }

    TimeUpdate::~TimeUpdate()
    {
    }



    //////////  HeadingUpdateOptions  //////////


    InertialTypes::HeadingUpdateEnableOption HeadingUpdateOptions::AsOptionId() const
    {
        if (useInternalMagnetometer)
        {
            if (useInternalGNSSVelocityVector)
            {
                if (useExternalHeadingMessages)
                    return InertialTypes::HeadingUpdateEnableOption::ENABLE_ALL;
                else
                    return InertialTypes::HeadingUpdateEnableOption::ENABLE_MAGNETOMETER_AND_GNSS;
            }
            else
            {
                if (useExternalHeadingMessages)
                    return InertialTypes::HeadingUpdateEnableOption::ENABLE_MAGNETOMETER_AND_EXTERNAL;
                else
                    return InertialTypes::HeadingUpdateEnableOption::ENABLE_INTERNAL_MAGNETOMETER;
            }
        }
        else
        {
            if (useInternalGNSSVelocityVector)
            {
                if (useExternalHeadingMessages)
                    return InertialTypes::HeadingUpdateEnableOption::ENABLE_GNSS_AND_EXTERNAL;
                else
                    return InertialTypes::HeadingUpdateEnableOption::ENABLE_INTERNAL_GNSS;
            }
            else
            {
                if (useExternalHeadingMessages)
                    return InertialTypes::HeadingUpdateEnableOption::ENABLE_EXTERNAL_MESSAGES;
                else
                    return InertialTypes::HeadingUpdateEnableOption::ENABLE_NONE;
            }
        }
    }

    //  This constructor converts a uint8 to a HeadingUpdateOptions object according to the Communications Protocol.
    HeadingUpdateOptions::HeadingUpdateOptions(const InertialTypes::HeadingUpdateEnableOption& headingUpdateOption)
    {
        switch (headingUpdateOption)
        {
        case InertialTypes::HeadingUpdateEnableOption::ENABLE_NONE:
            useInternalMagnetometer = false;
            useInternalGNSSVelocityVector = false;
            useExternalHeadingMessages = false;
            break;
        case InertialTypes::HeadingUpdateEnableOption::ENABLE_INTERNAL_MAGNETOMETER:
            useInternalMagnetometer = true;
            useInternalGNSSVelocityVector = false;
            useExternalHeadingMessages = false;
            break;
        case InertialTypes::HeadingUpdateEnableOption::ENABLE_INTERNAL_GNSS:
            useInternalMagnetometer = false;
            useInternalGNSSVelocityVector = true;
            useExternalHeadingMessages = false;
            break;
        case InertialTypes::HeadingUpdateEnableOption::ENABLE_EXTERNAL_MESSAGES:
            useInternalMagnetometer = false;
            useInternalGNSSVelocityVector = false;
            useExternalHeadingMessages = true;
            break;
        case InertialTypes::HeadingUpdateEnableOption::ENABLE_MAGNETOMETER_AND_GNSS:
            useInternalMagnetometer = true;
            useInternalGNSSVelocityVector = true;
            useExternalHeadingMessages = false;
            break;
        case InertialTypes::HeadingUpdateEnableOption::ENABLE_GNSS_AND_EXTERNAL:
            useInternalMagnetometer = false;
            useInternalGNSSVelocityVector = true;
            useExternalHeadingMessages = true;
            break;
        case InertialTypes::HeadingUpdateEnableOption::ENABLE_MAGNETOMETER_AND_EXTERNAL:
            useInternalMagnetometer = true;
            useInternalGNSSVelocityVector = false;
            useExternalHeadingMessages = true;
            break;
        case InertialTypes::HeadingUpdateEnableOption::ENABLE_ALL:
            useInternalMagnetometer = true;
            useInternalGNSSVelocityVector = true;
            useExternalHeadingMessages = true;
            break;
        default:
            throw Error_MipCmdFailed("An invalid option value was passed in to HeadingUpdateOptions.");
        }
    }



    //////////  EstimationControlOptions  //////////


    uint16 EstimationControlOptions::AsUint16() const {
        uint16 intValue = 0;

        if (enableGyroBiasEstimation) {
            intValue = intValue | InertialTypes::EstimationControlOption::ENABLE_GYRO_BIAS_ESTIMATION;
        }

        if (enableAccelBiasEstimation) {
            intValue = intValue | InertialTypes::EstimationControlOption::ENABLE_ACCEL_BIAS_ESTIMATION;
        }

        if (enableGyroScaleFactorEstimation) {
            intValue = intValue | InertialTypes::EstimationControlOption::ENABLE_GYRO_SCALE_FACTOR_ESTIMATION;
        }

        if (enableAccelScaleFactorEstimation) {
            intValue = intValue | InertialTypes::EstimationControlOption::ENABLE_ACCEL_SCALE_FACTOR_ESTIMATION;
        }

        if (enableGNSSAntennaOffsetEstimation) {
            intValue = intValue | InertialTypes::EstimationControlOption::ENABLE_GNSS_ANTENNA_OFFSET_ESTIMATION;
        }

        if (enableHardIronAutoCalibration) {
            intValue = intValue | InertialTypes::EstimationControlOption::ENABLE_HARD_IRON_AUTO_CALIBRATION;
        }

        if (enableSoftIronAutoCalibration) {
            intValue = intValue | InertialTypes::EstimationControlOption::ENABLE_SOFT_IRON_AUTO_CALIBRATION;
        }

        return intValue;
    }

    //  This constructor converts a uint16 to a EstimationControlOptions object according to the Communications Protocol.
    EstimationControlOptions::EstimationControlOptions(const mscl::uint16& estimationControlData) {
        enableGyroBiasEstimation = (estimationControlData & InertialTypes::EstimationControlOption::ENABLE_GYRO_BIAS_ESTIMATION) != 0;
        enableAccelBiasEstimation = (estimationControlData & InertialTypes::EstimationControlOption::ENABLE_ACCEL_BIAS_ESTIMATION) != 0;
        enableGyroScaleFactorEstimation = (estimationControlData & InertialTypes::EstimationControlOption::ENABLE_GYRO_SCALE_FACTOR_ESTIMATION) != 0;
        enableAccelScaleFactorEstimation = (estimationControlData & InertialTypes::EstimationControlOption::ENABLE_ACCEL_SCALE_FACTOR_ESTIMATION) != 0;
        enableGNSSAntennaOffsetEstimation = (estimationControlData & InertialTypes::EstimationControlOption::ENABLE_GNSS_ANTENNA_OFFSET_ESTIMATION) != 0;
        enableHardIronAutoCalibration = (estimationControlData & InertialTypes::EstimationControlOption::ENABLE_HARD_IRON_AUTO_CALIBRATION) != 0;
        enableSoftIronAutoCalibration = (estimationControlData & InertialTypes::EstimationControlOption::ENABLE_SOFT_IRON_AUTO_CALIBRATION) != 0;
    }

    DeviceStatusData::SystemState DeviceStatusData::systemState()
    {
        checkValue(m_systemState, "systemState");
        return *m_systemState;
    }

    void DeviceStatusData::systemState(SystemState val)
    {
        m_systemState = val;
    }

    bool DeviceStatusData::gnssPowerStateOn() const
    {
        checkValue(m_gnssPowerStateOn, "gnssPowerStateOn");
        return *m_gnssPowerStateOn;
    }

    void DeviceStatusData::gnssPowerStateOn(bool val)
    {
        m_gnssPowerStateOn = val;
    }

    PpsPulseInfo DeviceStatusData::gnss1PpsPulseInfo()
    {
        checkValue(m_gnss1PpsPulseInfo, "gnss1PpsPulseInfo");
        return *m_gnss1PpsPulseInfo;
    }

    void DeviceStatusData::gnss1PpsPulseInfo(PpsPulseInfo val)
    {
        m_gnss1PpsPulseInfo = val;
    }

    StreamInfo DeviceStatusData::imuStreamInfo()
    {
        checkValue(m_imuStreamInfo, "imuStreamInfo");
        return *m_imuStreamInfo;
    }

    void DeviceStatusData::imuStreamInfo(StreamInfo val)
    {
        m_imuStreamInfo = val;
    }

    StreamInfo DeviceStatusData::gnssStreamInfo()
    {
        checkValue(m_gnssStreamInfo, "gnssStreamInfo");
        return *m_gnssStreamInfo;
    }

    void DeviceStatusData::gnssStreamInfo(StreamInfo val)
    {
        m_gnssStreamInfo = val;
    }

    StreamInfo DeviceStatusData::estimationFilterStreamInfo()
    {
        checkValue(m_estimationFilterStreamInfo, "estimationFilterStreamInfo");
        return *m_estimationFilterStreamInfo;
    }

    void DeviceStatusData::estimationFilterStreamInfo(StreamInfo val)
    {
        m_estimationFilterStreamInfo = val;
    }

    DeviceMessageInfo DeviceStatusData::imuMessageInfo()
    {
        checkValue(m_imuMessageInfo, "imuMessageInfo");
        return *m_imuMessageInfo;
    }

    void DeviceStatusData::imuMessageInfo(DeviceMessageInfo val)
    {
        m_imuMessageInfo = val;
    }

    DeviceMessageInfo DeviceStatusData::gnssMessageInfo()
    {
        checkValue(m_gnssMessageInfo, "gnssMessageInfo");
        return *m_gnssMessageInfo;
    }

    void DeviceStatusData::gnssMessageInfo(DeviceMessageInfo val)
    {
        m_gnssMessageInfo = val;
    }

    PortInfo DeviceStatusData::comPortInfo()
    {
        checkValue(m_comPortInfo, "comPortInfo");
        return *m_comPortInfo;
    }

    void DeviceStatusData::comPortInfo(PortInfo val)
    {
        m_comPortInfo = val;
    }

    PortInfo DeviceStatusData::usbPortInfo()
    {
        checkValue(m_usbPortInfo, "usbPortInfo");
        return *m_usbPortInfo;
    }

    void DeviceStatusData::usbPortInfo(PortInfo val)
    {
        m_usbPortInfo = val;
    }

    bool DeviceStatusData::hasMagnetometer() const
    {
        checkValue(m_hasMagnetometer, "hasMagnetometer");
        return *m_hasMagnetometer;
    }

    void DeviceStatusData::hasMagnetometer(bool val)
    {
        m_hasMagnetometer = val;
    }

    bool DeviceStatusData::magnetometerInitializationFailed() const
    {
        checkValue(m_magnetometerInitializationFailed, "magnetometerInitializationFailed");
        return *m_magnetometerInitializationFailed;
    }

    void DeviceStatusData::magnetometerInitializationFailed(bool val)
    {
        m_magnetometerInitializationFailed = val;
    }

    bool DeviceStatusData::hasPressure() const
    {
        checkValue(m_hasPressure, "hasPressure");
        return *m_hasPressure;
    }

    void DeviceStatusData::hasPressure(bool val)
    {
        m_hasPressure = val;
    }

    bool DeviceStatusData::pressureInitializationFailed() const
    {
        checkValue(m_pressureInitializationFailed, "pressureInitializationFailed");
        return *m_pressureInitializationFailed;
    }

    void DeviceStatusData::pressureInitializationFailed(bool val)
    {
        m_pressureInitializationFailed = val;
    }

    bool DeviceStatusData::gnssReceiverInitializationFailed() const
    {
        checkValue(m_gnssReceiverInitializationFailed, "gnssReceiverInitializationFailed");
        return *m_gnssReceiverInitializationFailed;
    }

    void DeviceStatusData::gnssReceiverInitializationFailed(bool val)
    {
        m_gnssReceiverInitializationFailed = val;
    }

    bool DeviceStatusData::coldStartOnPowerOn() const
    {
        checkValue(m_coldStartOnPowerOn, "coldStartOnPowerOn");
        return *m_coldStartOnPowerOn;
    }

    void DeviceStatusData::coldStartOnPowerOn(bool val)
    {
        m_coldStartOnPowerOn = val;
    }

    TemperatureInfo DeviceStatusData::temperatureInfo()
    {
        checkValue(m_temperatureInfo, "temperatureInfo");
        return *m_temperatureInfo;
    }

    void DeviceStatusData::temperatureInfo(TemperatureInfo val)
    {
        m_temperatureInfo = val;
    }

    InertialTypes::PowerState DeviceStatusData::powerState() const
    {
        checkValue(m_powerState, "powerState");
        return *m_powerState;
    }

    void DeviceStatusData::powerState(InertialTypes::PowerState val)
    {
        m_powerState = val;
    }

    uint16 DeviceStatusData::gyroRange() const
    {
        checkValue(m_gyroRange, "gyroRange");
        return *m_gyroRange;
    }

    void DeviceStatusData::gyroRange(uint16 val)
    {
        m_gyroRange = val;
    }

    uint16 DeviceStatusData::accelRange() const
    {
        checkValue(m_accelRange, "accelRange");
        return *m_accelRange;
    }

    void DeviceStatusData::accelRange(uint16 val)
    {
        m_accelRange = val;
    }

    uint8 TareAxisValues::asUint8() const
    {
        return tarePitchAxis * InertialTypes::TARE_PITCH_AXIS
            | tareRollAxis * InertialTypes::TARE_ROLL_AXIS
            | tareYawAxis * InertialTypes::TARE_YAW_AXIS;
    }

}  // namespace mscl