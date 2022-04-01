/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"
#include "ExposedInertialTypes.h"
#include <boost/math/constants/constants.hpp>

namespace mscl
{
    //////////  Matrix  //////////

    Matrix_3x3::Matrix_3x3(float i00, float i01, float i02, float i10, float i11, float i12, float i20, float i21, float i22)
    {
        // Not sure why I need firstArray.  Just putting this list in the initialization below doesn't compile.
        std::array<float, 3> firstRow{ i00, i01, i02 };
        m_array = { firstRow,{ i10, i11, i12 },{ i20, i21, i22 } };
    }

    Matrix_3x3::Matrix_3x3(MipFieldValues data)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                int index = (i * 3) + j;
                m_array[i][j] = data[index].as_float();
            }
        }
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

    std::string Matrix_3x3::str() const
    {
        std::stringstream result;
        result << "[";

        //for every value in the Matrix
        for (uint16 row = 0; row < 3; row++)
        {
            result << "[";
            for (uint16 col = 0; col < 3; col++)
            {
                result << m_array[row][col];

                //if this isn't the last column in the row
                if (col != 2)
                {
                    //add a separator
                    result << ",";
                }
            }
            result << "]";

            //if this isn't the last row
            if (row != 2)
            {
                //add a separator
                result << ",";
            }
        }

        result << "]";

        return result.str();
    }

    MipFieldValues Matrix_3x3::asMipFieldValues() const
    {
        MipFieldValues m;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                m.push_back(Value::FLOAT(m_array[i][j]));
            }
        }

        return m;
    }

    //////////  Quaternion  //////////
    Quaternion::Quaternion() :
        Matrix(1, 4, ValueType::valueType_float, ByteStream())
    {
        m_data.append_float(0);
        m_data.append_float(0);
        m_data.append_float(0);
        m_data.append_float(0);
    }

    Quaternion::Quaternion(float q0, float q1, float q2, float q3) :
        Matrix(1, 4, ValueType::valueType_float, ByteStream())
    {
        m_data.append_float(q0);
        m_data.append_float(q1);
        m_data.append_float(q2);
        m_data.append_float(q3);
    }

    Quaternion::Quaternion(MipFieldValues data) :
        Matrix(1, 4, ValueType::valueType_float, ByteStream())
    {
        for (int i = 0; i < 4; i++)
        {
            m_data.append_float(data[i].as_float());
        }
    }

    float Quaternion::at(uint8 index) const
    {
        return as_floatAt(0, index);
    }

    void Quaternion::set(uint8 index, float val)
    {
        uint32 pos = getBytePos(0, index);
        ByteStream valB;
        valB.append_float(val);

        for (uint32 i = 0; i < 4; i++)
        {
            uint32 replaceIndex = pos + i;
            m_data.data()[replaceIndex] = valB[i];
        }
    }

    void Quaternion::normalize()
    {
        float magnitude = 0.0f;
        for (uint8 i = 0; i < 4; i++)
        {
            float val = at(i);
            magnitude += val * val;
        }

        magnitude = sqrt(magnitude);

        if (magnitude == 0)
        {
            return;
        }

        ByteStream b;
        for (uint8 i = 0; i < 4; i++)
        {
            float val = at(i);
            b.append_float(val / magnitude);
        }

        m_data = b;
    }

    MipFieldValues Quaternion::asMipFieldValues() const
    {
        MipFieldValues m;
        for (uint8 i = 0; i < 4; i++)
        {
            m.push_back(Value::FLOAT(at(i)));
        }

        return m;
    }

    //////////  GeometricVector  //////////

    GeometricVector::GeometricVector(float x_init, float y_init, float z_init, PositionVelocityReferenceFrame ref) :
        vec_0(x_init),
        vec_1(y_init),
        vec_2(z_init),
        referenceFrame(ref)
    { }

    GeometricVector::GeometricVector() :
        vec_0(0),
        vec_1(0),
        vec_2(0),
        referenceFrame(PositionVelocityReferenceFrame::ECEF)
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

    mscl::DeviceStatusMap DeviceStatusData::asMap() const
    {
        mscl::DeviceStatusMap statusMap;
        mscl::DeviceStatusValueMap m = asValueMap();

        for (auto kv : m)
        {
            statusMap[kv.first] = kv.second.as_string();
        }

        return statusMap;
    }

    mscl::DeviceStatusValueMap DeviceStatusData::asValueMap() const
    {
        mscl::DeviceStatusValueMap statusMap;
        statusMap[ModelNumber] = mscl::Value::UINT16(modelNumber);
        statusMap[StatusStructure_Value] = mscl::Value::UINT8(static_cast<uint8>(statusStructure));

        if (isSet(m_systemState)) 
        {
            statusMap[SystemState_Value] = mscl::Value::UINT16(static_cast<uint16>(m_systemState.get()));
        }

        if (isSet(m_gnss1PpsPulseInfo))
        {
            statusMap[gnss1PpsPulseInfo_Count] = mscl::Value::UINT32(m_gnss1PpsPulseInfo.get().count);
            statusMap[gnss1PpsPulseInfo_LastTimeinMS] = mscl::Value::UINT32(m_gnss1PpsPulseInfo.get().lastTimeinMS);
        }

        if (isSet(m_gnssPowerStateOn)) {
            statusMap[GnssPowerStateOn] = mscl::Value::BOOL(m_gnssPowerStateOn.get());
        }

        if (isSet(m_imuStreamInfo))
        {
            statusMap[ImuStreamInfo_Enabled] = mscl::Value::BOOL(m_imuStreamInfo.get().enabled);
            statusMap[ImuStreamInfo_PacketsDropped] = mscl::Value::UINT32(m_imuStreamInfo.get().outgoingPacketsDropped);
        }

        if (isSet(m_gnssStreamInfo))
        {
            statusMap[GnssStreamInfo_Enabled] = mscl::Value::BOOL(m_gnssStreamInfo.get().enabled);
            statusMap[GnssStreamInfo_PacketsDropped] = mscl::Value::UINT32(m_gnssStreamInfo.get().outgoingPacketsDropped);
        }

        if (isSet(m_estimationFilterStreamInfo))
        {
            statusMap[EstimationFilterStreamInfo_Enabled] = mscl::Value::BOOL(m_estimationFilterStreamInfo.get().enabled);
            statusMap[EstimationFilterStreamInfo_PacketsDropped] = mscl::Value::UINT32(m_estimationFilterStreamInfo.get().outgoingPacketsDropped);
        }

        if (isSet(m_comPortInfo))
        {
            statusMap[ComPortInfo_BytesRead] = mscl::Value::UINT32(m_comPortInfo.get().bytesRead);
            statusMap[ComPortInfo_BytesWritten] = mscl::Value::UINT32(m_comPortInfo.get().bytesWritten);
            statusMap[ComPortInfo_OverrunsOnRead] = mscl::Value::UINT32(m_comPortInfo.get().overrunsOnRead);
            statusMap[ComPortInfo_OverrunsOnWrite] = mscl::Value::UINT32(m_comPortInfo.get().overrunsOnWrite); // supported to features
        }

        if (isSet(m_imuMessageInfo))
        {
            statusMap[ImuMessageInfo_LastMessageReadinMS] = mscl::Value::UINT32(m_imuMessageInfo.get().lastMessageReadinMS);
            statusMap[ImuMessageInfo_MessageParsingErrors] = mscl::Value::UINT32(m_imuMessageInfo.get().messageParsingErrors);
            statusMap[ImuMessageInfo_MessagesRead] = mscl::Value::UINT32(m_imuMessageInfo.get().messagesRead);
        }

        if (isSet(m_gnssMessageInfo))
        {
            statusMap[GnssMessageInfo_LastMessageReadinMS] = mscl::Value::UINT32(m_gnssMessageInfo.get().lastMessageReadinMS);
            statusMap[GnssMessageInfo_MessageParsingErrors] = mscl::Value::UINT32(m_gnssMessageInfo.get().messageParsingErrors);
            statusMap[GnssMessageInfo_MessagesRead] = mscl::Value::UINT32(m_gnssMessageInfo.get().messagesRead);
        }

        if (isSet(m_temperatureInfo))
        {
            statusMap[TemperatureInfo_Error] = mscl::Value::UINT8(m_temperatureInfo.get().error);
            statusMap[TemperatureInfo_LastReadInMS] = mscl::Value::UINT32(m_temperatureInfo.get().lastReadInMS);
            statusMap[TemperatureInfo_OnBoardTemp] = mscl::Value::FLOAT(m_temperatureInfo.get().onBoardTemp);
        }

        if (isSet(m_powerState))
        {
            statusMap[PowerState] = mscl::Value::UINT8(static_cast<uint8>(m_powerState.get()));
        }

        if (isSet(m_gyroRange))
        {
            statusMap[GyroRange] = mscl::Value::UINT16(m_gyroRange.get());
        }

        if (isSet(m_accelRange))
        {
            statusMap[AccelRange] = mscl::Value::UINT16(m_accelRange.get());
        }

        if (isSet(m_hasMagnetometer))
        {
            statusMap[HasMagnetometer] = mscl::Value::BOOL(m_hasMagnetometer.get());
        }

        if (isSet(m_hasPressure))
        {
            statusMap[HasPressure] = mscl::Value::BOOL(m_hasPressure.get());
        }

        return statusMap;
    }

    RTKDeviceStatusFlags::RTKDeviceStatusFlags(const RTKDeviceStatusFlags_v1 rtk_v1) :
        Bitfield(rtk_v1.value())
    {}

    RTKDeviceStatusFlags::operator RTKDeviceStatusFlags_v1() const
    {
        return RTKDeviceStatusFlags_v1(static_cast<uint32>(value()));
    }

    uint8 RTKDeviceStatusFlags::version() const
    {
        return static_cast<uint8>(get(VERSION));
    }

    RTKDeviceStatusFlags::ModemState RTKDeviceStatusFlags::modemState() const
    {
        return static_cast<ModemState>(get(MODEM_STATE));
    }

    void RTKDeviceStatusFlags::modemState(const ModemState state)
    {
        set(MODEM_STATE, state);
    }

    RTKDeviceStatusFlags::ConnectionType RTKDeviceStatusFlags::connectionType() const
    {
        return static_cast<ConnectionType>(get(CONNECTION_TYPE));
    }

    void RTKDeviceStatusFlags::connectionType(const ConnectionType state)
    {
        set(CONNECTION_TYPE, state);
    }

    int8 RTKDeviceStatusFlags::rssi() const
    {
        return -1 * static_cast<int8>(get(RSSI));
    }

    void RTKDeviceStatusFlags::rssi(const uint8 value)
    {
        set(RSSI, value);
    }

    uint8 RTKDeviceStatusFlags::signalQuality() const
    {
        return static_cast<uint8>(get(SIGNAL_QUALITY));
    }

    void RTKDeviceStatusFlags::signalQuality(const uint8 quality)
    {
        set(SIGNAL_QUALITY, quality);
    }

    uint8 RTKDeviceStatusFlags::towerChangeIndicator() const
    {
        return static_cast<uint8>(get(TOWER_CHANGE_INDICATOR));
    }

    void RTKDeviceStatusFlags::towerChangeIndicator(const uint8 value)
    {
        set(TOWER_CHANGE_INDICATOR, value);
    }

    uint8 RTKDeviceStatusFlags::nmeaTimeout() const
    {
        return static_cast<uint8>(get(NMEA_TIMEOUT));
    }

    void RTKDeviceStatusFlags::nmeaTimeout(const uint8 timeout)
    {
        set(NMEA_TIMEOUT, timeout);
    }

    uint8 RTKDeviceStatusFlags::serverTimeout() const
    {
        return static_cast<uint8>(get(SERVER_TIMEOUT));
    }

    void RTKDeviceStatusFlags::serverTimeout(const uint8 timeout)
    {
        set(SERVER_TIMEOUT, timeout);
    }

    uint8 RTKDeviceStatusFlags::rtcmTimeout() const
    {
        return static_cast<uint8>(get(RTCM_TIMEOUT));
    }

    void RTKDeviceStatusFlags::rtcmTimeout(const uint8 timeout)
    {
        set(RTCM_TIMEOUT, timeout);
    }

    uint8 RTKDeviceStatusFlags::deviceOutOfRange() const
    {
        return static_cast<uint8>(get(DEVICE_OUT_OF_RANGE));
    }

    void RTKDeviceStatusFlags::deviceOutOfRange(const uint8 outOfRange)
    {
        set(DEVICE_OUT_OF_RANGE, outOfRange);
    }

    uint8 RTKDeviceStatusFlags::correctionsUnavailable() const
    {
        return static_cast<uint8>(get(CORRECTIONS_UNAVAILABLE));
    }

    void RTKDeviceStatusFlags::correctionsUnavailable(const uint8 unavailable)
    {
        set(CORRECTIONS_UNAVAILABLE, unavailable);
    }

    RTKDeviceStatusFlags_v1::operator RTKDeviceStatusFlags() const
    {
        return RTKDeviceStatusFlags(static_cast<uint32>(value()));
    }

    uint8 RTKDeviceStatusFlags_v1::version() const
    {
        return static_cast<uint8>(get(VERSION));
    }

    RTKDeviceStatusFlags_v1::ControllerState RTKDeviceStatusFlags_v1::controllerState() const
    {
        return static_cast<ControllerState>(get(CONTROLLER_STATE));
    }

    void RTKDeviceStatusFlags_v1::controllerState(RTKDeviceStatusFlags_v1::ControllerState state)
    {
        set(CONTROLLER_STATE, state);
    }

    RTKDeviceStatusFlags_v1::PlatformState RTKDeviceStatusFlags_v1::platformState() const
    {
        return static_cast<PlatformState>(get(PLATFORM_STATE));
    }

    void RTKDeviceStatusFlags_v1::platformState(RTKDeviceStatusFlags_v1::PlatformState state)
    {
        set(PLATFORM_STATE, state);
    }

    RTKDeviceStatusFlags_v1::ControllerStatusCode RTKDeviceStatusFlags_v1::controllerStatusCode() const
    {
        return static_cast<ControllerStatusCode>(get(CONTROLLER_STATUS_CODE));
    }

    void RTKDeviceStatusFlags_v1::controllerStatusCode(RTKDeviceStatusFlags_v1::ControllerStatusCode status)
    {
        set(CONTROLLER_STATUS_CODE, status);
    }

    RTKDeviceStatusFlags_v1::PlatformStatusCode RTKDeviceStatusFlags_v1::platformStatusCode() const
    {
        return static_cast<PlatformStatusCode>(get(PLATFORM_STATUS_CODE));
    }

    void RTKDeviceStatusFlags_v1::platformStatusCode(RTKDeviceStatusFlags_v1::PlatformStatusCode status)
    {
        set(PLATFORM_STATUS_CODE, status);
    }

    RTKDeviceStatusFlags_v1::ResetReason RTKDeviceStatusFlags_v1::resetReason() const
    {
        return static_cast<ResetReason>(get(RESET_REASON));
    }

    void RTKDeviceStatusFlags_v1::resetReason(RTKDeviceStatusFlags_v1::ResetReason reason)
    {
        set(RESET_REASON, static_cast<uint32>(reason));
    }

    uint8 RTKDeviceStatusFlags_v1::signalQuality() const
    {
        return static_cast<uint8>(get(SIGNAL_QUALITY));
    }

    void RTKDeviceStatusFlags_v1::signalQuality(uint8 quality)
    {
        set(SIGNAL_QUALITY, quality);
    }

    GnssSignalConfiguration::GnssSignalConfiguration()
    {
        m_gpsSignals = Bitfield(0);
        m_glonassSignals = Bitfield(0);
        m_galileoSignals = Bitfield(0);
        m_beidouSignals = Bitfield(0);
    }

    void GnssSignalConfiguration::enableGpsSignal(GnssSignalConfiguration::GpsSignal signal, bool enable)
    {
        m_gpsSignals.set(signal, (enable ? 1 : 0));
    }

    bool GnssSignalConfiguration::gpsSignalEnabled(GnssSignalConfiguration::GpsSignal signal)
    {
        return m_gpsSignals.get(signal) > 0;
    }

    void GnssSignalConfiguration::enableGlonassSignal(GnssSignalConfiguration::GlonassSignal signal, bool enable)
    {
        m_glonassSignals.set(signal, (enable ? 1 : 0));
    }

    bool GnssSignalConfiguration::glonassSignalEnabled(GnssSignalConfiguration::GlonassSignal signal)
    {
        return m_glonassSignals.get(signal) > 0;
    }

    void GnssSignalConfiguration::enableGalileoSignal(GnssSignalConfiguration::GalileoSignal signal, bool enable)
    {
        m_galileoSignals.set(signal, (enable ? 1 : 0));
    }

    bool GnssSignalConfiguration::galileoSignalEnabled(GnssSignalConfiguration::GalileoSignal signal)
    {
        return m_galileoSignals.get(signal) > 0;
    }

    void GnssSignalConfiguration::enableBeiDouSignal(GnssSignalConfiguration::BeiDouSignal signal, bool enable)
    {
        m_beidouSignals.set(signal, (enable ? 1 : 0));
    }

    bool GnssSignalConfiguration::beidouSignalEnabled(GnssSignalConfiguration::BeiDouSignal signal)
    {
        return m_beidouSignals.get(signal) > 0;
    }

    OdometerConfiguration::Mode OdometerConfiguration::mode() const
    {
        return m_mode;
    }

    void OdometerConfiguration::mode(OdometerConfiguration::Mode m)
    {
        m_mode = m;
    }

    float OdometerConfiguration::scaling() const
    {
        return m_scaling;
    }

    void OdometerConfiguration::scaling(float scale)
    {
        if (scale == INFINITY)
        {
            m_scaling = 0;
            return;
        }

        m_scaling = scale;
    }

    void OdometerConfiguration::scaling(float resolution, float radius)
    {
        if (resolution == 0 || radius == 0)
        {
            m_scaling = 0;
        }

        float mPerRev = radius * 2 * boost::math::constants::pi<float>();
        m_scaling = resolution / mPerRev;
    }

    float OdometerConfiguration::uncertainty() const
    {
        return m_unc;
    }

    void OdometerConfiguration::uncertainty(float unc)
    {
        if (unc == INFINITY)
        {
            m_unc = 0.01f;
            return;
        }

        m_unc = unc;
    }
}  // namespace mscl