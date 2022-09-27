/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "mscl/MicroStrain/MIP/MipBuiltInTest.h"

namespace mscl
{
    MipDataPoints ContinuousBIT::getMipDataPoints(MipModels::NodeModel model, Bytes data)
    {
        switch (model)
        {
        case(MipModels::node_3dm_cv7_ahrs):
        case(MipModels::node_3dm_cv7_ar):
        {
            CV7ContinuousBIT bit(data);
            return bit.as_MipDataPoints();
        }
        default:
            return{};
        }
    }

    uint8 CV7ContinuousBIT_System_General::flags() const
    {
        return static_cast<uint8>(value());
    }

    bool CV7ContinuousBIT_System_General::systemClockFailure() const
    {
        return get(SYSTEM_CLOCK_FAILURE) > 0;
    }

    bool CV7ContinuousBIT_System_General::powerFault() const
    {
        return get(POWER_FAULT) > 0;
    }

    bool CV7ContinuousBIT_System_General::firmwareFault() const
    {
        return get(FIRMWARE_FAULT) > 0;
    }

    bool CV7ContinuousBIT_System_General::timingOverload() const
    {
        return get(TIMING_OVERLOAD) > 0;
    }

    bool CV7ContinuousBIT_System_General::bufferOverrun() const
    {
        return get(BUFFER_OVERRUN) > 0;
    }

    uint8 CV7ContinuousBIT_System_Process::flags() const
    {
        return static_cast<uint8>(value());
    }

    bool CV7ContinuousBIT_System_Process::imuProcessFault() const
    {
        return get(IMU_PROCESS_FAULT) > 0;
    }

    bool CV7ContinuousBIT_System_Process::imuRateMismatch() const
    {
        return get(IMU_RATE_MISMATCH) > 0;
    }

    bool CV7ContinuousBIT_System_Process::imuDroppedData() const
    {
        return get(IMU_DROPPED_DATA) > 0;
    }

    bool CV7ContinuousBIT_System_Process::imuStuck() const
    {
        return get(IMU_STUCK) > 0;
    }

    bool CV7ContinuousBIT_System_Process::filterProcessFault() const
    {
        return get(FILTER_PROCESS_FAULT) > 0;
    }

    bool CV7ContinuousBIT_System_Process::filterDroppedData() const
    {
        return get(FILTER_DROPPED_DATA) > 0;
    }

    bool CV7ContinuousBIT_System_Process::filterRateMismatch() const
    {
        return get(FILTER_RATE_MISMATCH) > 0;
    }

    bool CV7ContinuousBIT_System_Process::filterStuck() const
    {
        return get(FILTER_STUCK) > 0;
    }

    CV7ContinuousBIT_System::CV7ContinuousBIT_System(const uint32 bits) : Bitfield(static_cast<uint64>(bits))
    {
        m_general = CV7ContinuousBIT_System_General(static_cast<uint8>(get(GENERAL_FLAGS)));
        m_process = CV7ContinuousBIT_System_Process(static_cast<uint8>(get(PROCESS_FLAGS)));
    }

    uint32 CV7ContinuousBIT_System::flags() const
    {
        return static_cast<uint32>(value());
    }

    CV7ContinuousBIT_System_General CV7ContinuousBIT_System::general() const
    {
        return m_general;
    }

    CV7ContinuousBIT_System_Process CV7ContinuousBIT_System::process() const
    {
        return m_process;
    }

    uint8 CV7ContinuousBIT_IMU_General::flags() const
    {
        return static_cast<uint8>(value());
    }

    bool CV7ContinuousBIT_IMU_General::clockFault() const
    {
        return get(CLOCK_FAULT) > 0;
    }

    bool CV7ContinuousBIT_IMU_General::communicationFault() const
    {
        return get(COMMUNICATION_FAULT) > 0;
    }

    bool CV7ContinuousBIT_IMU_General::timingOverrun() const
    {
        return get(TIMING_OVERRUN) > 0;
    }

    bool CV7ContinuousBIT_IMU_General::calibrationErrorAccel() const
    {
        return get(CALIBRATION_ERROR_ACCEL) > 0;
    }

    bool CV7ContinuousBIT_IMU_General::calibrationErrorGyro() const
    {
        return get(CALIBRATION_ERROR_GYRO) > 0;
    }

    bool CV7ContinuousBIT_IMU_General::calibrationErrorMag() const
    {
        return get(CALIBRATION_ERROR_MAG) > 0;
    }

    uint16 CV7ContinuousBIT_IMU_Sensors::flags() const
    {
        return static_cast<uint16>(value());
    }

    bool CV7ContinuousBIT_IMU_Sensors::accelGeneralFault() const
    {
        return get(ACCEL_GENERAL_FAULT) > 0;
    }

    bool CV7ContinuousBIT_IMU_Sensors::accelOverrange() const
    {
        return get(ACCEL_OVERRANGE) > 0;
    }

    bool CV7ContinuousBIT_IMU_Sensors::accelSelfTestFail() const
    {
        return get(ACCEL_SELF_TEST_FAIL) > 0;
    }

    bool CV7ContinuousBIT_IMU_Sensors::gyroGeneralFault() const
    {
        return get(GYRO_GENERAL_FAULT) > 0;
    }

    bool CV7ContinuousBIT_IMU_Sensors::gyroOverrange() const
    {
        return get(GYRO_OVERRANGE) > 0;
    }

    bool CV7ContinuousBIT_IMU_Sensors::gyroSelfTestFail() const
    {
        return get(GYRO_SELF_TEST_FAIL) > 0;
    }

    bool CV7ContinuousBIT_IMU_Sensors::magGeneralFault() const
    {
        return get(MAG_GENERAL_FAULT) > 0;
    }

    bool CV7ContinuousBIT_IMU_Sensors::magOverrange() const
    {
        return get(MAG_OVERRANGE) > 0;
    }

    bool CV7ContinuousBIT_IMU_Sensors::magSelfTestFail() const
    {
        return get(MAG_SELF_TEST_FAIL) > 0;
    }

    bool CV7ContinuousBIT_IMU_Sensors::pressureGeneralFault() const
    {
        return get(PRESSURE_GENERAL_FAULT) > 0;
    }

    bool CV7ContinuousBIT_IMU_Sensors::pressureOverrange() const
    {
        return get(PRESSURE_OVERRANGE) > 0;
    }

    bool CV7ContinuousBIT_IMU_Sensors::pressureSelfTestFail() const
    {
        return get(PRESSURE_SELF_TEST_FAIL) > 0;
    }

    CV7ContinuousBIT_IMU::CV7ContinuousBIT_IMU(const uint32 bits) : Bitfield(static_cast<uint64>(bits))
    {
        m_general = CV7ContinuousBIT_IMU_General(static_cast<uint8>(get(GENERAL_FLAGS)));
        m_sensors = CV7ContinuousBIT_IMU_Sensors(static_cast<uint16>(get(SENSORS_FLAGS)));
    }

    uint32 CV7ContinuousBIT_IMU::flags() const
    {
        return static_cast<uint32>(value());
    }

    CV7ContinuousBIT_IMU_General CV7ContinuousBIT_IMU::general() const
    {
        return m_general;
    }

    CV7ContinuousBIT_IMU_Sensors CV7ContinuousBIT_IMU::sensors() const
    {
        return m_sensors;
    }

    bool CV7ContinuousBIT_IMU::factoryBitsInvalid() const
    {
        return get(FACTORY_BITS_INVALID) > 0;
    }

    uint8 CV7ContinuousBIT_Filter_General::flags() const
    {
        return static_cast<uint8>(value());
    }

    bool CV7ContinuousBIT_Filter_General::fault() const
    {
        return get(FAULT) > 0;
    }

    bool CV7ContinuousBIT_Filter_General::timingOverrun() const
    {
        return get(TIMING_OVERRUN) > 0;
    }

    bool CV7ContinuousBIT_Filter_General::timingUnderrun() const
    {
        return get(TIMING_UNDERRUN) > 0;
    }

    CV7ContinuousBIT_Filter::CV7ContinuousBIT_Filter(const uint32 bits) : Bitfield(static_cast<uint64>(bits))
    {
        m_general = CV7ContinuousBIT_Filter_General(static_cast<uint8>(get(GENERAL_FLAGS)));
    }

    uint32 CV7ContinuousBIT_Filter::flags() const
    {
        return static_cast<uint32>(value());
    }

    CV7ContinuousBIT_Filter_General CV7ContinuousBIT_Filter::general() const
    {
        return m_general;
    }

    CV7ContinuousBIT::CV7ContinuousBIT(const Bytes bytes) :
        m_data(bytes)
    {
        DataBuffer buffer(m_data);
        m_system = CV7ContinuousBIT_System(buffer.read_uint32());
        m_imu = CV7ContinuousBIT_IMU(buffer.read_uint32());
        m_filter = CV7ContinuousBIT_Filter(buffer.read_uint32());
    }

    CV7ContinuousBIT_System CV7ContinuousBIT::system() const
    {
        return m_system;
    }

    CV7ContinuousBIT_IMU CV7ContinuousBIT::imu() const
    {
        return m_imu;
    }

    CV7ContinuousBIT_Filter CV7ContinuousBIT::filter() const
    {
        return m_filter;
    }

    const Bytes& CV7ContinuousBIT::data() const
    {
        return m_data;
    }

    MipDataPoints CV7ContinuousBIT::as_MipDataPoints() const
    {
        return{
            mscl::MipDataPoint(
                MipTypes::CH_FIELD_SYSTEM_BUILT_IN_TEST,
                MipTypes::CH_BIT_SYSTEM_GENERAL,
                mscl::ValueType::valueType_uint8,
                system().general().flags()),
            mscl::MipDataPoint(
                MipTypes::CH_FIELD_SYSTEM_BUILT_IN_TEST,
                MipTypes::CH_BIT_SYSTEM_PROCESS,
                mscl::ValueType::valueType_uint8,
                system().process().flags()),

            // IMU sections
            mscl::MipDataPoint(
                MipTypes::CH_FIELD_SYSTEM_BUILT_IN_TEST,
                MipTypes::CH_BIT_IMU_GENERAL,
                mscl::ValueType::valueType_uint8,
                imu().general().flags()),
            mscl::MipDataPoint(
                MipTypes::CH_FIELD_SYSTEM_BUILT_IN_TEST,
                MipTypes::CH_BIT_IMU_SENSORS,
                mscl::ValueType::valueType_uint16,
                imu().sensors().flags()),
            mscl::MipDataPoint(
                MipTypes::CH_FIELD_SYSTEM_BUILT_IN_TEST,
                MipTypes::CH_BIT_IMU_FACTORY_BITS,
                mscl::ValueType::valueType_bool,
                imu().factoryBitsInvalid()),

            // Est Filter sections
            mscl::MipDataPoint(
                MipTypes::CH_FIELD_SYSTEM_BUILT_IN_TEST,
                MipTypes::CH_BIT_FILTER_GENERAL,
                mscl::ValueType::valueType_uint8,
                filter().general().flags())
        };
    }
}  // namespace mscl