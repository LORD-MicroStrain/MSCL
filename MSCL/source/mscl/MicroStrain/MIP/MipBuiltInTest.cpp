/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/MIP/MipBuiltInTest.h"

namespace mscl
{
    ContinuousBIT::ContinuousBIT(const Bytes bytes) :
    m_data(bytes)
    {}

    MipDataPoints ContinuousBIT::getMipDataPoints(const MipModels::NodeModel model, const Bytes data)
    {
        switch (model)
        {
        case MipModels::node_3dm_cv7_ahrs:
        case MipModels::node_3dm_cv7_ar:
        case MipModels::node_3dm_cv7_ins:
        case MipModels::node_3dm_cv7_gnss_ins:
        {
            const CV7ContinuousBIT bit(data);
            return bit.as_MipDataPoints();
        }
        case MipModels::node_3dm_gq7:
        {
            const GQ7ContinuousBIT bit(data);
            return bit.as_MipDataPoints();
        }
        default:
            return{};
        }
    }

    const Bytes& ContinuousBIT::data() const
    {
        return m_data;
    }

    uint8 ContinuousBIT_System_General::flags() const
    {
        return static_cast<uint8>(value());
    }

    bool ContinuousBIT_System_General::systemClockFailure() const
    {
        return get(SYSTEM_CLOCK_FAILURE) > 0;
    }

    bool ContinuousBIT_System_General::powerFault() const
    {
        return get(POWER_FAULT) > 0;
    }

    bool ContinuousBIT_System_General::firmwareFault() const
    {
        return get(FIRMWARE_FAULT) > 0;
    }

    bool ContinuousBIT_System_General::timingOverload() const
    {
        return get(TIMING_OVERLOAD) > 0;
    }

    bool ContinuousBIT_System_General::bufferOverrun() const
    {
        return get(BUFFER_OVERRUN) > 0;
    }

    uint16 ContinuousBIT_System_Process::flags() const
    {
        return static_cast<uint16>(value());
    }

    uint32 ContinuousBIT_System::flags() const
    {
        return static_cast<uint32>(value());
    }

    uint8 ContinuousBIT_IMU_General::flags() const
    {
        return static_cast<uint8>(value());
    }

    bool ContinuousBIT_IMU_General::clockFault() const
    {
        return get(CLOCK_FAULT) > 0;
    }

    bool ContinuousBIT_IMU_General::communicationFault() const
    {
        return get(COMMUNICATION_FAULT) > 0;
    }

    bool ContinuousBIT_IMU_General::timingOverrun() const
    {
        return get(TIMING_OVERRUN) > 0;
    }

    bool ContinuousBIT_IMU_General::calibrationErrorAccel() const
    {
        return get(CALIBRATION_ERROR_ACCEL) > 0;
    }

    bool ContinuousBIT_IMU_General::calibrationErrorGyro() const
    {
        return get(CALIBRATION_ERROR_GYRO) > 0;
    }

    bool ContinuousBIT_IMU_General::calibrationErrorMag() const
    {
        return get(CALIBRATION_ERROR_MAG) > 0;
    }

    uint16 ContinuousBIT_IMU_Sensors::flags() const
    {
        return static_cast<uint16>(value());
    }

    bool ContinuousBIT_IMU_Sensors::accelGeneralFault() const
    {
        return get(ACCEL_GENERAL_FAULT) > 0;
    }

    bool ContinuousBIT_IMU_Sensors::accelOverrange() const
    {
        return get(ACCEL_OVERRANGE) > 0;
    }

    bool ContinuousBIT_IMU_Sensors::accelSelfTestFail() const
    {
        return get(ACCEL_SELF_TEST_FAIL) > 0;
    }

    bool ContinuousBIT_IMU_Sensors::gyroGeneralFault() const
    {
        return get(GYRO_GENERAL_FAULT) > 0;
    }

    bool ContinuousBIT_IMU_Sensors::gyroOverrange() const
    {
        return get(GYRO_OVERRANGE) > 0;
    }

    bool ContinuousBIT_IMU_Sensors::gyroSelfTestFail() const
    {
        return get(GYRO_SELF_TEST_FAIL) > 0;
    }

    bool ContinuousBIT_IMU_Sensors::magGeneralFault() const
    {
        return get(MAG_GENERAL_FAULT) > 0;
    }

    bool ContinuousBIT_IMU_Sensors::magOverrange() const
    {
        return get(MAG_OVERRANGE) > 0;
    }

    bool ContinuousBIT_IMU_Sensors::magSelfTestFail() const
    {
        return get(MAG_SELF_TEST_FAIL) > 0;
    }

    bool ContinuousBIT_IMU_Sensors::pressureGeneralFault() const
    {
        return get(PRESSURE_GENERAL_FAULT) > 0;
    }

    bool ContinuousBIT_IMU_Sensors::pressureOverrange() const
    {
        return get(PRESSURE_OVERRANGE) > 0;
    }

    bool ContinuousBIT_IMU_Sensors::pressureSelfTestFail() const
    {
        return get(PRESSURE_SELF_TEST_FAIL) > 0;
    }

    uint32 ContinuousBIT_IMU::flags() const
    {
        return static_cast<uint32>(value());
    }

    uint8 ContinuousBIT_Filter_General::flags() const
    {
        return static_cast<uint8>(value());
    }

    bool ContinuousBIT_Filter_General::timingOverrun() const
    {
        return get(TIMING_OVERRUN) > 0;
    }

    bool ContinuousBIT_Filter_General::timingUnderrun() const
    {
        return get(TIMING_UNDERRUN) > 0;
    }

    uint32 ContinuousBIT_Filter::flags() const
    {
        return static_cast<uint32>(value());
    }


    /**************
    ****  CV7  ****
    **************/

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

    CV7ContinuousBIT_System::CV7ContinuousBIT_System(const uint32 bits) : ContinuousBIT_System(bits),
        m_general(CV7ContinuousBIT_System_General(static_cast<uint8>(get(GENERAL_FLAGS)))),
        m_process(CV7ContinuousBIT_System_Process(static_cast<uint8>(get(PROCESS_FLAGS))))
    {}

    CV7ContinuousBIT_System_General CV7ContinuousBIT_System::general() const
    {
        return m_general;
    }

    CV7ContinuousBIT_System_Process CV7ContinuousBIT_System::process() const
    {
        return m_process;
    }

    CV7ContinuousBIT_IMU::CV7ContinuousBIT_IMU(const uint32 bits) : ContinuousBIT_IMU(bits),
        m_general(CV7ContinuousBIT_IMU_General(static_cast<uint8>(get(GENERAL_FLAGS)))),
        m_sensors(CV7ContinuousBIT_IMU_Sensors(static_cast<uint16>(get(SENSORS_FLAGS))))
    {}

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

    bool CV7ContinuousBIT_Filter_General::fault() const
    {
        return get(FAULT) > 0;
    }

    CV7ContinuousBIT_Filter::CV7ContinuousBIT_Filter(const uint32 bits) : ContinuousBIT_Filter(bits),
        m_general(CV7ContinuousBIT_Filter_General(static_cast<uint8>(get(GENERAL_FLAGS))))
    {}

    CV7ContinuousBIT_Filter_General CV7ContinuousBIT_Filter::general() const
    {
        return m_general;
    }

    CV7ContinuousBIT::CV7ContinuousBIT(const Bytes bytes) : ContinuousBIT(bytes)
    {
        m_data = bytes;

        DataBuffer buffer(m_data);
        m_system = CV7ContinuousBIT_System(buffer.read_uint32());
        m_imu    = CV7ContinuousBIT_IMU(buffer.read_uint32());
        m_filter = CV7ContinuousBIT_Filter(buffer.read_uint32());
    }


    /**************************
    ****  CV7 System Bits  ****
    **************************/

    CV7ContinuousBIT_System CV7ContinuousBIT::system() const
    {
        return m_system;
    }

    bool CV7ContinuousBIT::systemClockFailure() const
    {
        return m_system.general().systemClockFailure();
    }

    bool CV7ContinuousBIT::powerFault() const
    {
        return m_system.general().powerFault();
    }

    bool CV7ContinuousBIT::firmwareFault() const
    {
        return m_system.general().firmwareFault();
    }

    bool CV7ContinuousBIT::timingOverload() const
    {
        return m_system.general().timingOverload();
    }

    bool CV7ContinuousBIT::bufferOverrun() const
    {
        return m_system.general().bufferOverrun();
    }

    bool CV7ContinuousBIT::imuProcessFault() const
    {
        return m_system.process().imuProcessFault();
    }

    bool CV7ContinuousBIT::imuRateMismatch() const
    {
        return m_system.process().imuRateMismatch();
    }

    bool CV7ContinuousBIT::imuDroppedData() const
    {
        return m_system.process().imuDroppedData();
    }

    bool CV7ContinuousBIT::imuStuck() const
    {
        return m_system.process().imuStuck();
    }

    bool CV7ContinuousBIT::filterProcessFault() const
    {
        return m_system.process().filterProcessFault();
    }

    bool CV7ContinuousBIT::filterDroppedData() const
    {
        return m_system.process().filterDroppedData();
    }

    bool CV7ContinuousBIT::filterRateMismatch() const
    {
        return m_system.process().filterRateMismatch();
    }

    bool CV7ContinuousBIT::filterStuck() const
    {
        return m_system.process().filterStuck();
    }


    /***********************
    ****  CV7 IMU Bits  ****
    ***********************/

    CV7ContinuousBIT_IMU CV7ContinuousBIT::imu() const
    {
        return m_imu;
    }

    bool CV7ContinuousBIT::imuClockFault() const
    {
        return m_imu.general().clockFault();
    }

    bool CV7ContinuousBIT::imuCommunicationFault() const
    {
        return m_imu.general().communicationFault();
    }

    bool CV7ContinuousBIT::imuTimingOverrun() const
    {
        return m_imu.general().timingOverrun();
    }

    bool CV7ContinuousBIT::imuCalibrationErrorAccel() const
    {
        return m_imu.general().calibrationErrorAccel();
    }

    bool CV7ContinuousBIT::imuCalibrationErrorGyro() const
    {
        return m_imu.general().calibrationErrorGyro();
    }

    bool CV7ContinuousBIT::imuCalibrationErrorMag() const
    {
        return m_imu.general().calibrationErrorMag();
    }

    bool CV7ContinuousBIT::accelGeneralFault() const
    {
        return m_imu.sensors().accelGeneralFault();
    }

    bool CV7ContinuousBIT::accelOverrange() const
    {
        return m_imu.sensors().accelOverrange();
    }

    bool CV7ContinuousBIT::accelSelfTestFail() const
    {
        return m_imu.sensors().accelSelfTestFail();
    }

    bool CV7ContinuousBIT::gyroGeneralFault() const
    {
        return m_imu.sensors().gyroGeneralFault();
    }

    bool CV7ContinuousBIT::gyroOverrange() const
    {
        return m_imu.sensors().gyroOverrange();
    }

    bool CV7ContinuousBIT::gyroSelfTestFail() const
    {
        return m_imu.sensors().gyroSelfTestFail();
    }

    bool CV7ContinuousBIT::magGeneralFault() const
    {
        return m_imu.sensors().magGeneralFault();
    }

    bool CV7ContinuousBIT::magOverrange() const
    {
        return m_imu.sensors().magOverrange();
    }

    bool CV7ContinuousBIT::magSelfTestFail() const
    {
        return m_imu.sensors().magSelfTestFail();
    }

    bool CV7ContinuousBIT::pressureGeneralFault() const
    {
        return m_imu.sensors().pressureGeneralFault();
    }

    bool CV7ContinuousBIT::pressureOverrange() const
    {
        return m_imu.sensors().pressureOverrange();
    }

    bool CV7ContinuousBIT::pressureSelfTestFail() const
    {
        return m_imu.sensors().pressureSelfTestFail();
    }

    bool CV7ContinuousBIT::factoryBitsInvalid() const
    {
        return m_imu.factoryBitsInvalid();
    }


    /**************************
    ****  CV7 Filter Bits  ****
    **************************/

    CV7ContinuousBIT_Filter CV7ContinuousBIT::filter() const
    {
        return m_filter;
    }

    bool CV7ContinuousBIT::filterFault() const
    {
        return m_filter.general().fault();
    }

    bool CV7ContinuousBIT::filterTimingOverrun() const
    {
        return m_filter.general().timingOverrun();
    }

    bool CV7ContinuousBIT::filterTimingUnderrun() const
    {
        return m_filter.general().timingUnderrun();
    }

    MipDataPoints CV7ContinuousBIT::as_MipDataPoints() const
    {
        return{
            MipDataPoint(
                MipTypes::CH_FIELD_SYSTEM_BUILT_IN_TEST,
                MipTypes::CH_BIT_SYSTEM_GENERAL,
                valueType_uint8,
                system().general().flags()),
            MipDataPoint(
                MipTypes::CH_FIELD_SYSTEM_BUILT_IN_TEST,
                MipTypes::CH_BIT_SYSTEM_PROCESS,
                valueType_uint16,
                system().process().flags()),

            // IMU sections
            MipDataPoint(
                MipTypes::CH_FIELD_SYSTEM_BUILT_IN_TEST,
                MipTypes::CH_BIT_IMU_GENERAL,
                valueType_uint8,
                imu().general().flags()),
            MipDataPoint(
                MipTypes::CH_FIELD_SYSTEM_BUILT_IN_TEST,
                MipTypes::CH_BIT_IMU_SENSORS,
                valueType_uint16,
                imu().sensors().flags()),
            MipDataPoint(
                MipTypes::CH_FIELD_SYSTEM_BUILT_IN_TEST,
                MipTypes::CH_BIT_IMU_FACTORY_BITS,
                valueType_bool,
                imu().factoryBitsInvalid()),

            // Est Filter sections
            MipDataPoint(
                MipTypes::CH_FIELD_SYSTEM_BUILT_IN_TEST,
                MipTypes::CH_BIT_FILTER_GENERAL,
                valueType_uint8,
                filter().general().flags())
        };
    }


    /**************
    ****  GQ7  ****
    **************/

    uint8 GQ7ContinuousBIT_System_Process::imuIpcFault() const
    {
        return static_cast<uint8>(get(
            IMU_CONTROL_LINE_FAULT |
            IMU_COMMAND_RESPONSE_FAULT |
            IMU_SPI_TRANSFER_FAULT |
            IMU_DATA_FRAME_FAULT
        ) >> 8);
    }

    bool GQ7ContinuousBIT_System_Process::imuControlLineFault() const
    {
        return get(IMU_CONTROL_LINE_FAULT) > 0;
    }

    bool GQ7ContinuousBIT_System_Process::imuCommandResponseFault() const
    {
        return get(IMU_COMMAND_RESPONSE_FAULT) > 0;
    }

    bool GQ7ContinuousBIT_System_Process::imuSpiTransferFault() const
    {
        return get(IMU_SPI_TRANSFER_FAULT) > 0;
    }

    bool GQ7ContinuousBIT_System_Process::imuDataFrameFault() const
    {
        return get(IMU_DATA_FRAME_FAULT) > 0;
    }

    uint8 GQ7ContinuousBIT_System_Process::filterIpcFault() const
    {
        return static_cast<uint8>(get(
            FILTER_CONTROL_LINE_FAULT |
            FILTER_COMMAND_RESPONSE_FAULT |
            FILTER_SPI_TRANSFER_FAULT |
            FILTER_DATA_FRAME_FAULT
        ) >> 12);
    }

    bool GQ7ContinuousBIT_System_Process::filterControlLineFault() const
    {
        return get(FILTER_CONTROL_LINE_FAULT) > 0;
    }

    bool GQ7ContinuousBIT_System_Process::filterCommandResponseFault() const
    {
        return get(FILTER_COMMAND_RESPONSE_FAULT) > 0;
    }

    bool GQ7ContinuousBIT_System_Process::filterSpiTransferFault() const
    {
        return get(FILTER_SPI_TRANSFER_FAULT) > 0;
    }

    bool GQ7ContinuousBIT_System_Process::filterDataFrameFault() const
    {
        return get(FILTER_DATA_FRAME_FAULT) > 0;
    }

    uint8 GQ7ContinuousBIT_System_Process::gnssIpcFault() const
    {
        return static_cast<uint8>(get(
            GNSS_CONTROL_LINE_FAULT |
            GNSS_COMMAND_RESPONSE_FAULT |
            GNSS_SPI_TRANSFER_FAULT |
            GNSS_DATA_FRAME_FAULT
        ));
    }

    bool GQ7ContinuousBIT_System_Process::gnssControlLineFault() const
    {
        return get(GNSS_CONTROL_LINE_FAULT) > 0;
    }

    bool GQ7ContinuousBIT_System_Process::gnssCommandResponseFault() const
    {
        return get(GNSS_COMMAND_RESPONSE_FAULT) > 0;
    }

    bool GQ7ContinuousBIT_System_Process::gnssSpiTransferFault() const
    {
        return get(GNSS_SPI_TRANSFER_FAULT) > 0;
    }

    bool GQ7ContinuousBIT_System_Process::gnssDataFrameFault() const
    {
        return get(GNSS_DATA_FRAME_FAULT) > 0;
    }

    GQ7ContinuousBIT_System::GQ7ContinuousBIT_System(const uint32 bits) : ContinuousBIT_System(bits),
        m_general(GQ7ContinuousBIT_System_General(static_cast<uint8>(get(GENERAL_FLAGS)))),
        m_process(GQ7ContinuousBIT_System_Process(static_cast<uint8>(get(PROCESS_FLAGS))))
    {}

    GQ7ContinuousBIT_System_General GQ7ContinuousBIT_System::general() const
    {
        return m_general;
    }

    GQ7ContinuousBIT_System_Process GQ7ContinuousBIT_System::process() const
    {
        return m_process;
    }

    GQ7ContinuousBIT_IMU::GQ7ContinuousBIT_IMU(const uint32 bits) : ContinuousBIT_IMU(bits),
        m_general(GQ7ContinuousBIT_IMU_General(static_cast<uint8>(get(GENERAL_FLAGS)))),
        m_sensors(GQ7ContinuousBIT_IMU_Sensors(static_cast<uint16>(get(SENSORS_FLAGS))))
    {}

    GQ7ContinuousBIT_IMU_General GQ7ContinuousBIT_IMU::general() const
    {
        return m_general;
    }

    GQ7ContinuousBIT_IMU_Sensors GQ7ContinuousBIT_IMU::sensors() const
    {
        return m_sensors;
    }

    bool GQ7ContinuousBIT_Filter_General::clockFault() const
    {
        return get(CLOCK_FAULT) > 0;
    }

    bool GQ7ContinuousBIT_Filter_General::hardwareFault() const
    {
        return get(HARDWARE_FAULT) > 0;
    }

    uint8 GQ7ContinuousBIT_Filter_General::communicationError() const
    {
        return static_cast<uint8>(get(
            COMMUNICATION_ERROR_IMU_SPI |
            COMMUNICATION_ERROR_GNSS_SPI |
            COMMUNICATION_ERROR_COMMS_SPI |
            COMMUNICATION_ERROR_COMMS_UART
        ) >> 4);
    }

    bool GQ7ContinuousBIT_Filter_General::communicationErrorImuSpi() const
    {
        return get(COMMUNICATION_ERROR_IMU_SPI) > 0;
    }

    bool GQ7ContinuousBIT_Filter_General::communicationErrorGnssSpi() const
    {
        return get(COMMUNICATION_ERROR_GNSS_SPI) > 0;
    }

    bool GQ7ContinuousBIT_Filter_General::communicationErrorCommsSpi() const
    {
        return get(COMMUNICATION_ERROR_COMMS_SPI) > 0;
    }

    bool GQ7ContinuousBIT_Filter_General::communicationErrorCommsUart() const
    {
        return get(COMMUNICATION_ERROR_COMMS_UART) > 0;
    }

    GQ7ContinuousBIT_Filter::GQ7ContinuousBIT_Filter(const uint32 bits) : ContinuousBIT_Filter(bits),
        m_general(GQ7ContinuousBIT_Filter_General(static_cast<uint8>(get(GENERAL_FLAGS))))
    {}

    GQ7ContinuousBIT_Filter_General GQ7ContinuousBIT_Filter::general() const
    {
        return m_general;
    }

    uint8 GQ7ContinuousBIT_GNSS_General::flags() const
    {
        return static_cast<uint8>(value());
    }

    bool GQ7ContinuousBIT_GNSS_General::clockFault() const
    {
        return get(CLOCK_FAULT) > 0;
    }

    bool GQ7ContinuousBIT_GNSS_General::hardwareFault() const
    {
        return get(HARDWARE_FAULT) > 0;
    }

    uint8 GQ7ContinuousBIT_GNSS_General::communicationError() const
    {
        return static_cast<uint8>(get(
            COMMUNICATION_ERROR_COMMS_SERIAL |
            COMMUNICATION_ERROR_COMMS_SPI |
            COMMUNICATION_ERROR_NAV_SPI
        ) >> 2);
    }

    bool GQ7ContinuousBIT_GNSS_General::communicationErrorCommsSerial() const
    {
        return get(COMMUNICATION_ERROR_COMMS_SERIAL) > 0;
    }

    bool GQ7ContinuousBIT_GNSS_General::communicationErrorCommsSpi() const
    {
        return get(COMMUNICATION_ERROR_COMMS_SPI) > 0;
    }

    bool GQ7ContinuousBIT_GNSS_General::communicationErrorNavSpi() const
    {
        return get(COMMUNICATION_ERROR_NAV_SPI) > 0;
    }

    bool GQ7ContinuousBIT_GNSS_General::gpsTimeFault() const
    {
        return get(GPS_TIME_FAULT) > 0;
    }

    bool GQ7ContinuousBIT_GNSS_General::timingOverrun() const
    {
        return get(TIMING_OVERRUN) > 0;
    }

    uint16 GQ7ContinuousBIT_GNSS_Receivers::flags() const
    {
        return static_cast<uint16>(value());
    }

    bool GQ7ContinuousBIT_GNSS_Receivers::powerFaultReceiver1() const
    {
        return get(POWER_FAULT_RECEIVER_1) > 0;
    }

    bool GQ7ContinuousBIT_GNSS_Receivers::faultReceiver1() const
    {
        return get(FAULT_RECEIVER_1) > 0;
    }

    bool GQ7ContinuousBIT_GNSS_Receivers::shortedAntenna1() const
    {
        return get(SHORTED_ANTENNA_1) > 0;
    }

    bool GQ7ContinuousBIT_GNSS_Receivers::openAntenna1() const
    {
        return get(OPEN_ANTENNA_1) > 0;
    }

    bool GQ7ContinuousBIT_GNSS_Receivers::solutionFaultReceiver1() const
    {
        return get(SOLUTION_FAULT_RECEIVER_1) > 0;
    }

    bool GQ7ContinuousBIT_GNSS_Receivers::powerFaultReceiver2() const
    {
        return get(POWER_FAULT_RECEIVER_2) > 0;
    }

    bool GQ7ContinuousBIT_GNSS_Receivers::faultReceiver2() const
    {
        return get(FAULT_RECEIVER_2) > 0;
    }

    bool GQ7ContinuousBIT_GNSS_Receivers::shortedAntenna2() const
    {
        return get(SHORTED_ANTENNA_2) > 0;
    }

    bool GQ7ContinuousBIT_GNSS_Receivers::openAntenna2() const
    {
        return get(OPEN_ANTENNA_2) > 0;
    }

    bool GQ7ContinuousBIT_GNSS_Receivers::solutionFaultReceiver2() const
    {
        return get(SOLUTION_FAULT_RECEIVER_2) > 0;
    }

    bool GQ7ContinuousBIT_GNSS_Receivers::rtcmCommunicationFault() const
    {
        return get(RTCM_COMMUNICATION_FAULT) > 0;
    }

    bool GQ7ContinuousBIT_GNSS_Receivers::rtkDongleFault() const
    {
        return get(RTK_DONGLE_FAULT) > 0;
    }

    GQ7ContinuousBIT_GNSS::GQ7ContinuousBIT_GNSS(const uint32 bits) : Bitfield(bits),
        m_general(GQ7ContinuousBIT_GNSS_General(static_cast<uint8>(get(GENERAL_FLAGS)))),
        m_receivers(GQ7ContinuousBIT_GNSS_Receivers(static_cast<uint16>(get(RECEIVERS_FLAGS))))
    {}

    uint32 GQ7ContinuousBIT_GNSS::flags() const
    {
        return static_cast<uint32>(value());
    }

    GQ7ContinuousBIT_GNSS_General GQ7ContinuousBIT_GNSS::general() const
    {
        return m_general;
    }

    GQ7ContinuousBIT_GNSS_Receivers GQ7ContinuousBIT_GNSS::receivers() const
    {
        return m_receivers;
    }

    GQ7ContinuousBIT::GQ7ContinuousBIT(const Bytes bytes) : ContinuousBIT(bytes)
    {
        DataBuffer buffer(m_data);
        m_system = GQ7ContinuousBIT_System(buffer.read_uint32());
        m_imu    = GQ7ContinuousBIT_IMU(buffer.read_uint32());
        m_filter = GQ7ContinuousBIT_Filter(buffer.read_uint32());
        m_gnss   = GQ7ContinuousBIT_GNSS(buffer.read_uint32());
    }


    /**************************
    ****  GQ7 System Bits  ****
    **************************/

    GQ7ContinuousBIT_System GQ7ContinuousBIT::system() const
    {
        return m_system;
    }

    bool GQ7ContinuousBIT::systemClockFailure() const
    {
        return m_system.general().systemClockFailure();
    }

    bool GQ7ContinuousBIT::powerFault() const
    {
        return m_system.general().powerFault();
    }

    bool GQ7ContinuousBIT::firmwareFault() const
    {
        return m_system.general().firmwareFault();
    }

    bool GQ7ContinuousBIT::timingOverload() const
    {
        return m_system.general().timingOverload();
    }

    bool GQ7ContinuousBIT::bufferOverrun() const
    {
        return m_system.general().bufferOverrun();
    }

    uint8 GQ7ContinuousBIT::imuIpcFault() const
    {
        return m_system.process().imuIpcFault();
    }

    bool GQ7ContinuousBIT::imuControlLineFault() const
    {
        return m_system.process().imuControlLineFault();
    }

    bool GQ7ContinuousBIT::imuCommandResponseFault() const
    {
        return m_system.process().imuCommandResponseFault();
    }

    bool GQ7ContinuousBIT::imuSpiTransferFault() const
    {
        return m_system.process().imuSpiTransferFault();
    }

    bool GQ7ContinuousBIT::imuDataFrameFault() const
    {
        return m_system.process().imuDataFrameFault();
    }

    uint8 GQ7ContinuousBIT::filterIpcFault() const
    {
        return m_system.process().filterIpcFault();
    }

    bool GQ7ContinuousBIT::filterControlLineFault() const
    {
        return m_system.process().filterControlLineFault();
    }

    bool GQ7ContinuousBIT::filterCommandResponseFault() const
    {
        return m_system.process().filterCommandResponseFault();
    }

    bool GQ7ContinuousBIT::filterSpiTransferFault() const
    {
        return m_system.process().filterSpiTransferFault();
    }

    bool GQ7ContinuousBIT::filterDataFrameFault() const
    {
        return m_system.process().filterDataFrameFault();
    }

    uint8 GQ7ContinuousBIT::gnssIpcFault() const
    {
        return m_system.process().gnssIpcFault();
    }

    bool GQ7ContinuousBIT::gnssControlLineFault() const
    {
        return m_system.process().gnssControlLineFault();
    }

    bool GQ7ContinuousBIT::gnssCommandResponseFault() const
    {
        return m_system.process().gnssCommandResponseFault();
    }

    bool GQ7ContinuousBIT::gnssSpiTransferFault() const
    {
        return m_system.process().gnssSpiTransferFault();
    }

    bool GQ7ContinuousBIT::gnssDataFrameFault() const
    {
        return m_system.process().gnssDataFrameFault();
    }


    /*******************
    ****  IMU Bits  ****
    *******************/

    GQ7ContinuousBIT_IMU GQ7ContinuousBIT::imu() const
    {
        return m_imu;
    }

    bool GQ7ContinuousBIT::imuClockFault() const
    {
        return m_imu.general().clockFault();
    }

    bool GQ7ContinuousBIT::imuCommunicationFault() const
    {
        return m_imu.general().communicationFault();
    }

    bool GQ7ContinuousBIT::imuTimingOverrun() const
    {
        return m_imu.general().timingOverrun();
    }

    bool GQ7ContinuousBIT::imuCalibrationErrorAccel() const
    {
        return m_imu.general().calibrationErrorAccel();
    }

    bool GQ7ContinuousBIT::imuCalibrationErrorGyro() const
    {
        return m_imu.general().calibrationErrorGyro();
    }

    bool GQ7ContinuousBIT::imuCalibrationErrorMag() const
    {
        return m_imu.general().calibrationErrorMag();
    }

    bool GQ7ContinuousBIT::accelGeneralFault() const
    {
        return m_imu.sensors().accelGeneralFault();
    }

    bool GQ7ContinuousBIT::accelOverrange() const
    {
        return m_imu.sensors().accelOverrange();
    }

    bool GQ7ContinuousBIT::accelSelfTestFail() const
    {
        return m_imu.sensors().accelSelfTestFail();
    }

    bool GQ7ContinuousBIT::gyroGeneralFault() const
    {
        return m_imu.sensors().gyroGeneralFault();
    }

    bool GQ7ContinuousBIT::gyroOverrange() const
    {
        return m_imu.sensors().gyroOverrange();
    }

    bool GQ7ContinuousBIT::gyroSelfTestFail() const
    {
        return m_imu.sensors().gyroSelfTestFail();
    }

    bool GQ7ContinuousBIT::magGeneralFault() const
    {
        return m_imu.sensors().magGeneralFault();
    }

    bool GQ7ContinuousBIT::magOverrange() const
    {
        return m_imu.sensors().magOverrange();
    }

    bool GQ7ContinuousBIT::magSelfTestFail() const
    {
        return m_imu.sensors().magSelfTestFail();
    }

    bool GQ7ContinuousBIT::pressureGeneralFault() const
    {
        return m_imu.sensors().pressureGeneralFault();
    }

    bool GQ7ContinuousBIT::pressureOverrange() const
    {
        return m_imu.sensors().pressureOverrange();
    }

    bool GQ7ContinuousBIT::pressureSelfTestFail() const
    {
        return m_imu.sensors().pressureSelfTestFail();
    }


    /**************************
    ****  GQ7 Filter Bits  ****
    **************************/

    GQ7ContinuousBIT_Filter GQ7ContinuousBIT::filter() const
    {
        return m_filter;
    }

    bool GQ7ContinuousBIT::filterClockFault() const
    {
        return m_filter.general().clockFault();
    }

    bool GQ7ContinuousBIT::filterHardwareFault() const
    {
        return m_filter.general().hardwareFault();
    }

    bool GQ7ContinuousBIT::filterTimingOverrun() const
    {
        return m_filter.general().timingOverrun();
    }

    bool GQ7ContinuousBIT::filterTimingUnderrun() const
    {
        return m_filter.general().timingUnderrun();
    }

    uint8 GQ7ContinuousBIT::filterCommunicationError() const
    {
        return m_filter.general().communicationError();
    }

    bool GQ7ContinuousBIT::filterCommunicationErrorImuSpi() const
    {
        return m_filter.general().communicationErrorImuSpi();
    }

    bool GQ7ContinuousBIT::filterCommunicationErrorGnssSpi() const
    {
        return m_filter.general().communicationErrorGnssSpi();
    }

    bool GQ7ContinuousBIT::filterCommunicationErrorCommsSpi() const
    {
        return m_filter.general().communicationErrorCommsSpi();
    }

    bool GQ7ContinuousBIT::filterCommunicationErrorCommsUart() const
    {
        return m_filter.general().communicationErrorCommsUart();
    }


    /************************
    ****  GQ7 GNSS Bits  ****
    ************************/

    GQ7ContinuousBIT_GNSS GQ7ContinuousBIT::gnss() const
    {
        return m_gnss;
    }

    bool GQ7ContinuousBIT::gnssClockFault() const
    {
        return m_gnss.general().clockFault();
    }

    bool GQ7ContinuousBIT::gnssHardwareFault() const
    {
        return m_gnss.general().hardwareFault();
    }

    uint8 GQ7ContinuousBIT::gnssCommunicationError() const
    {
        return m_gnss.general().communicationError();
    }

    bool GQ7ContinuousBIT::gnssCommunicationErrorCommsSerial() const
    {
        return m_gnss.general().communicationErrorCommsSerial();
    }

    bool GQ7ContinuousBIT::gnssCommunicationErrorCommsSpi() const
    {
        return m_gnss.general().communicationErrorCommsSpi();
    }

    bool GQ7ContinuousBIT::gnssCommunicationErrorNavSpi() const
    {
        return m_gnss.general().communicationErrorNavSpi();
    }

    bool GQ7ContinuousBIT::gpsTimeFault() const
    {
        return m_gnss.general().gpsTimeFault();
    }

    bool GQ7ContinuousBIT::gnssTimingOverrun() const
    {
        return m_gnss.general().timingOverrun();
    }

    bool GQ7ContinuousBIT::gnssPowerFaultReceiver1() const
    {
        return m_gnss.receivers().powerFaultReceiver1();
    }

    bool GQ7ContinuousBIT::gnssFaultReceiver1() const
    {
        return m_gnss.receivers().faultReceiver1();
    }

    bool GQ7ContinuousBIT::gnssShortedAntenna1() const
    {
        return m_gnss.receivers().shortedAntenna1();
    }

    bool GQ7ContinuousBIT::gnssOpenAntenna1() const
    {
        return m_gnss.receivers().openAntenna1();
    }

    bool GQ7ContinuousBIT::gnssSolutionFaultReceiver1() const
    {
        return m_gnss.receivers().solutionFaultReceiver1();
    }

    bool GQ7ContinuousBIT::gnssPowerFaultReceiver2() const
    {
        return m_gnss.receivers().powerFaultReceiver2();
    }

    bool GQ7ContinuousBIT::gnssFaultReceiver2() const
    {
        return m_gnss.receivers().faultReceiver2();
    }

    bool GQ7ContinuousBIT::gnssShortedAntenna2() const
    {
        return m_gnss.receivers().shortedAntenna2();
    }

    bool GQ7ContinuousBIT::gnssOpenAntenna2() const
    {
        return m_gnss.receivers().openAntenna2();
    }

    bool GQ7ContinuousBIT::gnssSolutionFaultReceiver2() const
    {
        return m_gnss.receivers().solutionFaultReceiver2();
    }

    bool GQ7ContinuousBIT::rtcmCommunicationFault() const
    {
        return m_gnss.receivers().rtcmCommunicationFault();
    }

    bool GQ7ContinuousBIT::rtkDongleFault() const
    {
        return m_gnss.receivers().rtkDongleFault();
    }

    MipDataPoints GQ7ContinuousBIT::as_MipDataPoints() const
    {
        return{
            MipDataPoint(
                MipTypes::CH_FIELD_SYSTEM_BUILT_IN_TEST,
                MipTypes::CH_BIT_SYSTEM_GENERAL,
                valueType_uint8,
                system().general().flags()),
            MipDataPoint(
                MipTypes::CH_FIELD_SYSTEM_BUILT_IN_TEST,
                MipTypes::CH_BIT_SYSTEM_PROCESS,
                valueType_uint16,
                system().process().flags()),

            // IMU sections
            MipDataPoint(
                MipTypes::CH_FIELD_SYSTEM_BUILT_IN_TEST,
                MipTypes::CH_BIT_IMU_GENERAL,
                valueType_uint8,
                imu().general().flags()),
            MipDataPoint(
                MipTypes::CH_FIELD_SYSTEM_BUILT_IN_TEST,
                MipTypes::CH_BIT_IMU_SENSORS,
                valueType_uint16,
                imu().sensors().flags()),

            // Est Filter sections
            MipDataPoint(
                MipTypes::CH_FIELD_SYSTEM_BUILT_IN_TEST,
                MipTypes::CH_BIT_FILTER_GENERAL,
                valueType_uint8,
                filter().general().flags()),

            // GNSS sections
            MipDataPoint(
                MipTypes::CH_FIELD_SYSTEM_BUILT_IN_TEST,
                MipTypes::CH_BIT_GNSS_GENERAL,
                valueType_uint8,
                gnss().general().flags()),
            MipDataPoint(
                MipTypes::CH_FIELD_SYSTEM_BUILT_IN_TEST,
                MipTypes::CH_BIT_GNSS_RECEIVERS,
                valueType_uint16,
                gnss().receivers().flags())
        };
    }
}  // namespace mscl
