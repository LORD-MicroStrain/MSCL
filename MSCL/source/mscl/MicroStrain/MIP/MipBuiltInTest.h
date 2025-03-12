/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Bitfield.h"
#include "mscl/MicroStrain/MIP/MipDataPoint.h"
#include "mscl/MicroStrain/MIP/MipModels.h"

namespace mscl
{
    //API Class: ContinuousBIT
    //  Abstract class for device-specific Built-In Test result parser classes
    class ContinuousBIT
    {
    public:
        //API Constructor: ContinuousBIT
        ContinuousBIT() = delete;

        //API Constructor: ContinuousBIT
        //  Copy constructor
        explicit ContinuousBIT(const ContinuousBIT&) = delete;

        //API Constructor: ContinuousBIT
        //  Move constructor
        explicit ContinuousBIT(const ContinuousBIT&&) = delete;

        //API Function: operator=
        //  Copy assignment operator
        ContinuousBIT& operator=(const ContinuousBIT&) const = delete;

        //API Function: operator=
        //  Move assignment operator
        ContinuousBIT& operator=(const ContinuousBIT&&) const = delete;

        //API Function: as_MipDataPoints
        //  Get the Built-In Test data formatted as <MipDataPoint> objects
        //
        //Returns:
        //  <MipDataPoints> - Data in DataPoint format
        virtual MipDataPoints as_MipDataPoints() const = 0;

        //API Function: getMipDataPoints
        //  Static function to parse the Built-In Test result data into <MipDataPoint> objects based on the specified device model
        //
        //Parameters:
        //  model - <MipModels::NodeModel> of the device the data was output from
        //  data  - <Bytes> Built-In Test result
        //
        //Returns:
        //  <MipDataPoints> - Data in DataPoint format
        static MipDataPoints getMipDataPoints(MipModels::NodeModel model, Bytes data);

        //API Function: data
        //  Gets the original <Bytes> source data (not parsed)
        //
        //Returns:
        //  <Bytes> - Raw source data
        const Bytes& data() const;


        /**********************
        ****  System Bits  ****
        **********************/

        //API Function: systemClockFailure
        //  Gets the value of the System Clock Failure bit (bit 0)
        //
        //Returns:
        //  bool - true: The system clock is not operating properly
        virtual bool systemClockFailure() const = 0;

        //API Function: powerFault
        //  Gets the value of the Power Fault bit (bit 1)
        //
        //Returns:
        //  bool - true: Power supply voltage is outside the recommended range, or an internal power fault exists
        virtual bool powerFault() const = 0;

        //API Function: firmwareFault
        //  Gets the value of the Firmware Fault bit (bit 4)
        //
        //Returns:
        //  bool - true: System firmware has detected an unexpected or abnormal condition
        virtual bool firmwareFault() const = 0;

        //API Function: timingOverload
        //  Gets the value of the Timing Overload bit (bit 5)
        //
        //Returns:
        //  bool - true: The system is unable to keep up with the processing demand
        virtual bool timingOverload() const = 0;

        //API Function: bufferOverrun
        //  Gets the value of the Buffer Overrun bit (bit 6)
        //
        //Returns:
        //  bool - true: A data buffer in the system has reached its capacity
        virtual bool bufferOverrun() const = 0;


        /*******************
        ****  IMU Bits  ****
        *******************/

        //API Function: imuClockFault
        //  Gets the value of the IMU Clock Fault bit (bit 32)
        //
        //Returns:
        //  bool - true: IMU is not running off the system clock
        virtual bool imuClockFault() const = 0;

        //API Function: imuCommunicationFault
        //  Gets the value of the IMU Communication Fault bit (bit 33)
        //
        //Returns:
        //  bool - true: No communication with IMU
        virtual bool imuCommunicationFault() const = 0;

        //API Function: imuTimingOverrun
        //  Gets the value of the IMU Timing Overrun bit (bit 34)
        //
        //Returns:
        //  bool - true: IMU processes are taking longer than their allotted time
        virtual bool imuTimingOverrun() const = 0;

        //API Function: imuCalibrationErrorAccel
        //  Gets the value of the IMU Calibration Error Accelerometer bit (bit 36)
        //
        //Returns:
        //  bool - true: A problem is detected with the accelerometer calibration
        virtual bool imuCalibrationErrorAccel() const = 0;

        //API Function: imuCalibrationErrorGyro
        //  Gets the value of the IMU Calibration Error Gyroscope bit (bit 37)
        //
        //Returns:
        //  bool - true: A problem is detected with the gyroscope calibration
        virtual bool imuCalibrationErrorGyro() const = 0;

        //API Function: imuCalibrationErrorMag
        //  Gets the value of the IMU Calibration Error Magnetometer bit (bit 38)
        //
        //Returns:
        //  bool - true: A problem is detected with the magnetometer calibration
        virtual bool imuCalibrationErrorMag() const = 0;

        //API Function: accelGeneralFault
        //  Gets the value of the Accelerometer General Fault bit (bit 40)
        //
        //Returns:
        //  bool - true: Accelerometer will not initialize
        virtual bool accelGeneralFault() const = 0;

        //API Function: accelOverrange
        //  Gets the value of the Accelerometer Overrange bit (bit 41)
        //
        //Returns:
        //  bool - true: One or more axes subjected to accelerations near or outside the selected range
        virtual bool accelOverrange() const = 0;

        //API Function: accelSelfTest
        //  Gets the value of the Accelerometer Self Test bit (bit 42)
        //
        //Returns:
        //  bool - true: The internal self-test of the accelerometer failed
        virtual bool accelSelfTestFail() const = 0;

        //API Function: gyroGeneralFault
        //  Gets the value of the Gyroscope General Fault bit (bit 44)
        //
        //Returns:
        //  bool - true: Gyroscope will not initialize
        virtual bool gyroGeneralFault() const = 0;

        //API Function: gyroOverrange
        //  Gets the value of the Gyroscope Overrange bit (bit 45)
        //
        //Returns:
        //  bool - true: One or more axes subjected to rotational rates near or outside the selected range
        virtual bool gyroOverrange() const = 0;

        //API Function: gyroSelfTest
        //  Gets the value of the Gyroscope Self Test bit (bit 46)
        //
        //Returns:
        //  bool - true: The internal self-test of the gyroscope failed
        virtual bool gyroSelfTestFail() const = 0;

        //API Function: magGeneralFault
        //  Gets the value of the Magnetometer General Fault bit (bit 48)
        //
        //Returns:
        //  bool - true: Magnetometer will not initialize
        virtual bool magGeneralFault() const = 0;

        //API Function: magOverrange
        //  Gets the value of the Magnetometer Overrange bit (bit 49)
        //
        //Returns:
        //  bool - true: One or more axes subjected to magnetic fields strengths near or outside the supported range
        virtual bool magOverrange() const = 0;

        //API Function: magSelfTest
        //  Gets the value of the Magnetometer Self Test bit (bit 50)
        //
        //Returns:
        //  bool - true: The internal self-test of the magnetometer failed
        virtual bool magSelfTestFail() const = 0;

        //API Function: pressureGeneralFault
        //  Gets the value of the Pressure General Fault bit (bit 52)
        //
        //Returns:
        //  bool - true: Pressure sensor won't initialize
        virtual bool pressureGeneralFault() const = 0;

        //API Function: pressureOverrange
        //  Gets the value of the Pressure Overrange bit (bit 53)
        //
        //Returns:
        //  bool - true: Pressure sensor subjected to pressures above or below the supported range
        virtual bool pressureOverrange() const = 0;

        //API Function: pressureSelfTest
        //  Gets the value of the Pressure Self Test bit (bit 54)
        //
        //Returns:
        //  bool - true: The internal self-test of the pressure sensor failed
        virtual bool pressureSelfTestFail() const = 0;


        /**********************
        ****  Filter Bits  ****
        **********************/

        //API Function: filterTimingOverrun
        //  Gets the value of the Filter Timing Overrun bit (bit 66)
        //
        //Returns:
        //  bool - true: Filter processes are taking longer than their allotted time
        virtual bool filterTimingOverrun() const = 0;

        //API Function: filterTimingUnderrun
        //  Gets the value of the Filter Timing Underrun bit (bit 67)
        //
        //Returns:
        //  bool - true: Filter processes are being skipped
        virtual bool filterTimingUnderrun() const = 0;

    protected:
        //Constructor: ContinuousBIT
        explicit ContinuousBIT(Bytes bytes);

        //Destructor: ContinuousBIT
        virtual ~ContinuousBIT() = default;

        //Variable: m_data
        //  The original <Bytes> source data
        Bytes m_data;
    };


    /************************************************
    ****              Continuous BIT             ****
    ****  Structures for parsing Continuous BIT  ****
    ************************************************/

    //API Struct: ContinuousBIT_System_General
    //  Continuous Built-In Test flags for general system information
    //
    //  Bits 0-7 of the original 128 bit Continuous Built-In Test flags
    struct ContinuousBIT_System_General : Bitfield
    {
        //API Constants: Bitmasks
        //  Bitmasks for general system flags
        //
        //  SYSTEM_CLOCK_FAILURE - 0x01 - The system clock is not operating properly
        //  POWER_FAULT          - 0x02 - Power supply voltage is outside the recommended range, or an internal power fault exists
        //  FIRMWARE_FAULT       - 0x10 - System firmware has detected an unexpected or abnormal condition
        //  TIMING_OVERLOAD      - 0x20 - The system is unable to keep up with the processing demand
        //  BUFFER_OVERRUN       - 0x40 - A data buffer in the system has reached its capacity
        static constexpr uint8 SYSTEM_CLOCK_FAILURE = 0x01; // The system clock is not operating properly
        static constexpr uint8 POWER_FAULT          = 0x02; // Power supply voltage is outside the recommended range, or an internal power fault exists
        static constexpr uint8 FIRMWARE_FAULT       = 0x10; // System firmware has detected an unexpected or abnormal condition
        static constexpr uint8 TIMING_OVERLOAD      = 0x20; // The system is unable to keep up with the processing demand
        static constexpr uint8 BUFFER_OVERRUN       = 0x40; // A data buffer in the system has reached its capacity

        //API Function: flags
        //  Gets the value of the general system flags (bits 0-7)
        //
        //Returns:
        //  uint8 - Value of the general system flags
        uint8 flags() const;

        //API Function: systemClockFailure
        //  Gets the value of the System Clock Failure bit (bit 0)
        //
        //Returns:
        //  bool - true: The system clock is not operating properly
        bool systemClockFailure() const;

        //API Function: powerFault
        //  Gets the value of the Power Fault bit (bit 1)
        //
        //Returns:
        //  bool - true: Power supply voltage is outside the recommended range, or an internal power fault exists
        bool powerFault() const;

        //API Function: firmwareFault
        //  Gets the value of the Firmware Fault bit (bit 4)
        //
        //Returns:
        //  bool - true: System firmware has detected an unexpected or abnormal condition
        bool firmwareFault() const;

        //API Function: timingOverload
        //  Gets the value of the Timing Overload bit (bit 5)
        //
        //Returns:
        //  bool - true: The system is unable to keep up with the processing demand
        bool timingOverload() const;

        //API Function: bufferOverrun
        //  Gets the value of the Buffer Overrun bit (bit 6)
        //
        //Returns:
        //  bool - true: A data buffer in the system has reached its capacity
        bool bufferOverrun() const;

    protected:
        //Constructor: ContinuousBIT_System_General
        ContinuousBIT_System_General() = default;

        //Constructor: ContinuousBIT_System_General
        //
        //Parameters:
        //  bits - Bits 0-7 of the original 128 bit Continuous Built-In Test flags
        explicit ContinuousBIT_System_General(const uint8 bits) : Bitfield(static_cast<uint64>(bits)) {}
    };

    //API Struct: ContinuousBIT_System_Process
    //  Continuous Built-In Test flags for system process information
    //
    //  Bits 16-31 of the original 128 bit Continuous Built-In Test flags
    struct ContinuousBIT_System_Process : Bitfield
    {
        //API Function: flags
        //  Gets the value of the process system flags (bits 16-31)
        //
        //Returns:
        //  uint16 - Value of the process system flags
        uint16 flags() const;

    protected:
        //Constructor: ContinuousBIT_System_Process
        ContinuousBIT_System_Process() = default;

        //Constructor: ContinuousBIT_System_Process
        //
        //Parameters:
        //  bits - Bits 16-31 of the original 128 bit Continuous Built-In Test flags
        explicit ContinuousBIT_System_Process(const uint16 bits) : Bitfield(static_cast<uint64>(bits)) {}
    };

    //API Struct: ContinuousBIT_System
    //  Continuous Built-In Test flags for system information
    //
    //  Bits 0-31 of the original 128 bit Continuous Built-In Test flags
    struct ContinuousBIT_System : Bitfield
    {
        //API Constant: RESPONSE_OFFSET
        //  The offset of the 0 position of the value represented by this object in the overall BIT response
        //  Value: 0 bits
        static constexpr uint8_t RESPONSE_OFFSET = 0;

        //API Constants: Bitmasks
        //  GENERAL_FLAGS - 0xFF000000 - Bitmask for general system flags (bits 0-7)
        //  PROCESS_FLAGS - 0x0000FFFF - Bitmask for system process flags (bits 16-31)
        static constexpr uint32 GENERAL_FLAGS = 0xFF000000; // Bitmask for general system flags (bits 0-7)
        static constexpr uint32 PROCESS_FLAGS = 0x0000FFFF; // Bitmask for system process flags (bits 16-31)

        //API Function: flags
        //  Gets the value of the system flags (bits 0-31)
        //
        //Returns:
        //  uint32 - Value of the system flags
        uint32 flags() const;

    protected:
        //Constructor: ContinuousBIT_System
        ContinuousBIT_System() = default;

        //Constructor: ContinuousBIT_System
        //
        //Parameters:
        //  bits - Value of bits 0-31 of the original 128 bit Continuous Built-In Test flags
        explicit ContinuousBIT_System(const uint32 bits) : Bitfield(static_cast<uint64>(bits)) {}
    };

    //API Struct: ContinuousBIT_IMU_General
    //  Continuous Built-In Test flags for general IMU information
    //
    //  Bits 32-39 of the original 128 bit Continuous Built-In Test flags
    struct ContinuousBIT_IMU_General : Bitfield
    {
        //API Constants: Bitmasks
        //  Bitmasks for general IMU flags
        //
        //Note:
        //  These masks are shifted 32 bits to the right from the original 128 bitmask to have a 0 index at bit 32
        //
        //  CLOCK_FAULT             - 0x01 - IMU is not running off the system clock
        //  COMMUNICATION_FAULT     - 0x02 - No communication with IMU
        //  TIMING_OVERRUN          - 0x04 - IMU processes are taking longer than their allotted time
        //  CALIBRATION_ERROR_ACCEL - 0x10 - A problem is detected with the accelerometer calibration
        //  CALIBRATION_ERROR_GYRO  - 0x20 - A problem is detected with the gyroscope calibration
        //  CALIBRATION_ERROR_MAG   - 0x40 - A problem is detected with the magnetometer calibration
        static constexpr uint8 CLOCK_FAULT             = 0x01; // IMU is not running off the system clock
        static constexpr uint8 COMMUNICATION_FAULT     = 0x02; // No communication with IMU
        static constexpr uint8 TIMING_OVERRUN          = 0x04; // IMU processes are taking longer than their allotted time

        static constexpr uint8 CALIBRATION_ERROR_ACCEL = 0x10; // A problem is detected with the accelerometer calibration
        static constexpr uint8 CALIBRATION_ERROR_GYRO  = 0x20; // A problem is detected with the gyroscope calibration
        static constexpr uint8 CALIBRATION_ERROR_MAG   = 0x40; // A problem is detected with the magnetometer calibration

        //API Function: flags
        //  Gets the value of the general IMU flags (bits 32-39)
        //
        //Returns:
        //  uint8 - Value of the general IMU flags
        uint8 flags() const;

        //API Function: clockFault
        //  Gets the value of the Clock Fault bit (bit 32)
        //
        //Returns:
        //  bool - true: IMU is not running off the system clock
        bool clockFault() const;

        //API Function: communicationFault
        //  Gets the value of the Communication Fault bit (bit 33)
        //
        //Returns:
        //  bool - true: No communication with IMU
        bool communicationFault() const;

        //API Function: timingOverrun
        //  Gets the value of the Timing Overrun bit (bit 34)
        //
        //Returns:
        //  bool - true: IMU processes are taking longer than their allotted time
        bool timingOverrun() const;

        //API Function: calibrationErrorAccel
        //  Gets the value of the Calibration Error Accelerometer bit (bit 36)
        //
        //Returns:
        //  bool - true: A problem is detected with the accelerometer calibration
        bool calibrationErrorAccel() const;

        //API Function: calibrationErrorGyro
        //  Gets the value of the Calibration Error Gyroscope bit (bit 37)
        //
        //Returns:
        //  bool - true: A problem is detected with the gyroscope calibration
        bool calibrationErrorGyro() const;

        //API Function: calibrationErrorMag
        //  Gets the value of the Calibration Error Magnetometer bit (bit 38)
        //
        //Returns:
        //  bool - true: A problem is detected with the magnetometer calibration
        bool calibrationErrorMag() const;

    protected:
        //Constructor: ContinuousBIT_IMU_General
        ContinuousBIT_IMU_General() = default;

        //Constructor: ContinuousBIT_IMU_General
        //
        //Parameters:
        //  bits - Bits 32-39 of the original 128 bit Continuous Built-In Test flags
        ContinuousBIT_IMU_General(const uint8 bits) : Bitfield(static_cast<uint64>(bits)) {}
    };

    //API Struct: ContinuousBIT_IMU_Sensors
    //  Continuous Built-In Test flags for IMU sensors information
    //
    //  Bits 40-55 of the original 128 bit Continuous Built-In Test flags
    struct ContinuousBIT_IMU_Sensors : Bitfield
    {
        //API Constants: Bitmasks
        //  Bitmasks for IMU sensors flags
        //
        //Note:
        //  These masks are shifted 40 bits to the right from the original 128 bitmask to have a 0 index at bit 40
        //
        //  ACCEL_GENERAL_FAULT     - 0x0100 - Accelerometer will not initialize
        //  ACCEL_OVERRANGE         - 0x0200 - One or more axes subjected to accelerations near or outside the selected range
        //  ACCEL_SELF_TEST_FAIL    - 0x0400 - The internal self-test of the accelerometer failed
        //  GYRO_GENERAL_FAULT      - 0x1000 - Gyroscope will not initialize
        //  GYRO_OVERRANGE          - 0x2000 - One or more axes subjected to rotational rates near or outside the selected range
        //  GYRO_SELF_TEST_FAIL     - 0x4000 - The internal self-test of the gyroscope failed
        //  MAG_GENERAL_FAULT       - 0x0001 - Magnetometer will not initialize
        //  MAG_OVERRANGE           - 0x0002 - One or more axes subjected to magnetic fields strengths near or outside the supported range
        //  MAG_SELF_TEST_FAIL      - 0x0004 - The internal self-test of the magnetometer failed
        //  PRESSURE_GENERAL_FAULT  - 0x0010 - Pressure sensor won't initialize
        //  PRESSURE_OVERRANGE      - 0x0020 - Pressure sensor subjected to pressures above or below the supported range
        //  PRESSURE_SELF_TEST_FAIL - 0x0040 - The internal self-test of the pressure sensor failed
        static constexpr uint16 ACCEL_GENERAL_FAULT     = 0x0100; // Accelerometer will not initialize
        static constexpr uint16 ACCEL_OVERRANGE         = 0x0200; // One or more axes subjected to accelerations near or outside the selected range
        static constexpr uint16 ACCEL_SELF_TEST_FAIL    = 0x0400; // The internal self-test of the accelerometer failed

        static constexpr uint16 GYRO_GENERAL_FAULT      = 0x1000; // Gyroscope will not initialize
        static constexpr uint16 GYRO_OVERRANGE          = 0x2000; // One or more axes subjected to rotational rates near or outside the selected range
        static constexpr uint16 GYRO_SELF_TEST_FAIL     = 0x4000; // The internal self-test of the gyroscope failed

        static constexpr uint16 MAG_GENERAL_FAULT       = 0x0001; // Magnetometer will not initialize
        static constexpr uint16 MAG_OVERRANGE           = 0x0002; // One or more axes subjected to magnetic fields strengths near or outside the supported range
        static constexpr uint16 MAG_SELF_TEST_FAIL      = 0x0004; // The internal self-test of the magnetometer failed

        static constexpr uint16 PRESSURE_GENERAL_FAULT  = 0x0010; // Pressure sensor won't initialize
        static constexpr uint16 PRESSURE_OVERRANGE      = 0x0020; // Pressure sensor subjected to pressures above or below the supported range
        static constexpr uint16 PRESSURE_SELF_TEST_FAIL = 0x0040; // The internal self-test of the pressure sensor failed

        //API Function: flags
        //  Gets the value of the the IMU sensors flags (bits 40-55)
        //
        //Returns:
        //  uint16 - Value of the IMU sensors flags
        uint16 flags() const;

        //API Function: accelGeneralFault
        //  Gets the value of the Accelerometer General Fault bit (bit 40)
        //
        //Returns:
        //  bool - true: Accelerometer will not initialize
        bool accelGeneralFault() const;

        //API Function: accelOverrange
        //  Gets the value of the Accelerometer Overrange bit (bit 41)
        //
        //Returns:
        //  bool - true: One or more axes subjected to accelerations near or outside the selected range
        bool accelOverrange() const;

        //API Function: accelSelfTest
        //  Gets the value of the Accelerometer Self Test bit (bit 42)
        //
        //Returns:
        //  bool - true: The internal self-test of the accelerometer failed
        bool accelSelfTestFail() const;

        //API Function: gyroGeneralFault
        //  Gets the value of the Gyroscope General Fault bit (bit 44)
        //
        //Returns:
        //  bool - true: Gyroscope will not initialize
        bool gyroGeneralFault() const;

        //API Function: gyroOverrange
        //  Gets the value of the Gyroscope Overrange bit (bit 45)
        //
        //Returns:
        //  bool - true: One or more axes subjected to rotational rates near or outside the selected range
        bool gyroOverrange() const;

        //API Function: gyroSelfTest
        //  Gets the value of the Gyroscope Self Test bit (bit 46)
        //
        //Returns:
        //  bool - true: The internal self-test of the gyroscope failed
        bool gyroSelfTestFail() const;

        //API Function: magGeneralFault
        //  Gets the value of the Magnetometer General Fault bit (bit 48)
        //
        //Returns:
        //  bool - true: Magnetometer will not initialize
        bool magGeneralFault() const;

        //API Function: magOverrange
        //  Gets the value of the Magnetometer Overrange bit (bit 49)
        //
        //Returns:
        //  bool - true: One or more axes subjected to magnetic fields strengths near or outside the supported range
        bool magOverrange() const;

        //API Function: magSelfTest
        //  Gets the value of the Magnetometer Self Test bit (bit 50)
        //
        //Returns:
        //  bool - true: The internal self-test of the magnetometer failed
        bool magSelfTestFail() const;

        //API Function: pressureGeneralFault
        //  Gets the value of the Pressure General Fault bit (bit 52)
        //
        //Returns:
        //  bool - true: Pressure sensor won't initialize
        bool pressureGeneralFault() const;

        //API Function: pressureOverrange
        //  Gets the value of the Pressure Overrange bit (bit 53)
        //
        //Returns:
        //  bool - true: Pressure sensor subjected to pressures above or below the supported range
        bool pressureOverrange() const;

        //API Function: pressureSelfTest
        //  Gets the value of the Pressure Self Test bit (bit 54)
        //
        //Returns:
        //  bool - true: The internal self-test of the pressure sensor failed
        bool pressureSelfTestFail() const;

    protected:
        //Constructor: ContinuousBIT_IMU_Sensors
        ContinuousBIT_IMU_Sensors() = default;

        //Constructor: ContinuousBIT_IMU_Sensors
        //
        //Parameters:
        //  bits - Bits 40-55 of the original 128 bit Continuous Built-In Test flags
        explicit ContinuousBIT_IMU_Sensors(const uint16 bits) : Bitfield(static_cast<uint64>(bits)) {}
    };

    //API Struct: ContinuousBIT_IMU
    //  Continuous Built-In Test flags for IMU information
    //
    //  Bits 32-63 of the original 128 bit Continuous Built-In Test flags
    struct ContinuousBIT_IMU : Bitfield
    {
        //API Constant: RESPONSE_OFFSET
        //  The offset of the 0 position of the value represented by this object in the overall BIT response
        //  Value: 32 bits
        static constexpr uint8_t RESPONSE_OFFSET = 32;

        //Constants: Bitmasks
        //  GENERAL_FLAGS - 0xFF000000 - Bitmask for the general IMU bit flags (bits 32-39)
        //  SENSORS_FLAGS - 0x00FFFF00 - Bitmask for the IMU sensors bit flags (40-55)
        //
        //Note:
        //  These masks are shifted 32 bits to the right from the original 128 bitmask to have a 0 index at bit 32
        static constexpr uint32 GENERAL_FLAGS = 0xFF000000; // Bitmask for the general IMU bit flags (bits 32-39)
        static constexpr uint32 SENSORS_FLAGS = 0x00FFFF00; // Bitmask for the IMU sensors bit flags (40-55)

        //API Function: flags
        //  Gets the value of the IMU flags (bits 32-63)
        //
        //Returns:
        //  uint32 - Value of the IMU flags
        uint32 flags() const;

    protected:
        //Constructor: ContinuousBIT_IMU
        ContinuousBIT_IMU() = default;

        //Constructor: ContinuousBIT_IMU
        //
        //Parameters:
        //  bits - Value of bits 32-63 of the original 128 bit Continuous Built-In Test flags
        explicit ContinuousBIT_IMU(const uint32 bits) : Bitfield(bits) {}
    };

    //API Struct: ContinuousBIT_Filter_General
    //  Continuous Built-In Test flags for general filter information
    //
    //  Bits 64-71 of the original 128 bit Continuous Built-In Test flags
    struct ContinuousBIT_Filter_General : Bitfield
    {
        //API Constants: Bitmasks
        //  Bitmasks for general filter flags
        //
        //Note:
        //  These masks are shifted 64 bits to the right from the original 128 bitmask to have a 0 index at bit 64
        //
        //  TIMING_OVERRUN  - 0x04 - Filter processes are taking longer than their allotted time
        //  TIMING_UNDERRUN - 0x08 - Filter processes are being skipped
        static constexpr uint8 TIMING_OVERRUN  = 0x04; // Filter processes are taking longer than their allotted time
        static constexpr uint8 TIMING_UNDERRUN = 0x08; // Filter processes are being skipped

        //API Function: flags
        //  Gets the value of the general filter flags (bits 64-71)
        //
        //Returns:
        //  uint8 - Value of the general filter flags
        uint8 flags() const;

        //API Function: timingOverrun
        //  Gets the value of the Filter Timing Overrun bit (bit 66)
        //
        //Returns:
        //  bool - true: Filter processes are taking longer than their allotted time
        bool timingOverrun() const;

        //API Function: timingUnderrun
        //  Gets the value of the Filter Timing Underrun bit (bit 67)
        //
        //Returns:
        //  bool - true: Filter processes are being skipped
        bool timingUnderrun() const;

    protected:
        //Constructor: ContinuousBIT_Filter_General
        ContinuousBIT_Filter_General() = default;

        //Constructor: ContinuousBIT_Filter_General
        //
        //Parameters:
        //  bits - Bits 64-71 of the original 128 bit Continuous Built-In Test flags
        explicit ContinuousBIT_Filter_General(const uint8 bits) : Bitfield(static_cast<uint64>(bits)) {}
    };

    //API Struct: ContinuousBIT_Filter
    //  Continuous Built-In Test flags for filter information
    //
    //  Bits 64-95 of the original 128 bit Continuous Built-In Test flags
    struct ContinuousBIT_Filter : Bitfield
    {
        //API Constant: RESPONSE_OFFSET
        //  The offset of the 0 position of the value represented by this object in the overall BIT response
        //  Value: 64 bits
        static constexpr uint8_t RESPONSE_OFFSET = 64;

        //API Constant: GENERAL_FLAGS
        //  Bitmask for general filter flags (bits 64-71)
        //
        //  GENERAL_FLAGS - 0xFF000000 - Bitmask for general filter flags (bits 64-71)
        //
        //Note:
        //  This mask is shifted 64 bits to the right from the original 128 bitmask to have a 0 index at bit 64
        static constexpr uint32 GENERAL_FLAGS = 0xFF000000; // Bitmask for general filter flags (bits 64-71)

        //API Function: flags
        //  Gets the value of the filter flags (bits 64-95)
        //
        //Returns:
        //  uint32 - Value of the filter flags
        uint32 flags() const;

    protected:
        //Constructor: ContinuousBIT_Filter
        ContinuousBIT_Filter() = default;

        //Constructor: ContinuousBIT_Filter
        //
        //Parameters:
        //  bits - Value of bits 64-95 of the original 128 bit Continuous Built-In Test flags
        explicit ContinuousBIT_Filter(const uint32 bits) : Bitfield(bits) {}
    };


    /************************************************
    ****                   CV7                   ****
    ****     Structures for parsing CV7 BIT      ****
    ************************************************/

    //API Struct: CV7ContinuousBIT_System_General
    //  Continuous Built-In Test flags for general system information
    //
    //  Bits 0-7 of the original 128 bit Continuous Built-In Test flags
    struct CV7ContinuousBIT_System_General : ContinuousBIT_System_General
    {
        //API Constructor: CV7ContinuousBIT_System_General
        CV7ContinuousBIT_System_General() = default;

        //API Constructor: CV7ContinuousBIT_System_General
        //
        //Parameters:
        //  bits - Bits 0-7 of the original 128 bit Continuous Built-In Test flags
        explicit CV7ContinuousBIT_System_General(const uint8 bits) : ContinuousBIT_System_General(bits) {}
    };

    //API Struct: CV7ContinuousBIT_System_Process
    //  Continuous Built-In Test flags for system process information
    //
    //  Bits 16-31 of the original 128 bit Continuous Built-In Test flags
    struct CV7ContinuousBIT_System_Process : ContinuousBIT_System_Process
    {
        //API Constructor: CV7ContinuousBIT_System_Process
        CV7ContinuousBIT_System_Process() : ContinuousBIT_System_Process() {}

        //API Constructor: CV7ContinuousBIT_System_Process
        //
        //Parameters:
        //  bits - Bits 16-31 of the original 128 bit Continuous Built-In Test flags
        explicit CV7ContinuousBIT_System_Process(const uint16 bits) : ContinuousBIT_System_Process(bits) {}

        //API Constants: Bitmasks
        //  Bitmasks for system process information flags
        //
        //Note:
        //  These masks are shifted 16 bits to the right from the original 128 bitmask to have a 0 index at bit 16
        //
        //  IMU_PROCESS_FAULT    - 0x8000 - The IMU subsystem is unresponsive or not operating normally
        //  IMU_RATE_MISMATCH    - 0x4000 - Faster/slower than expected base rate
        //  IMU_DROPPED_DATA     - 0x2000 - At least 1 dropped frame / overrun
        //  IMU_STUCK            - 0x1000 - No IMU data received in 1 second
        //  FILTER_PROCESS_FAULT - 0x0800 - The Filter subsystem is unresponsive or not operating normally
        //  FILTER_DROPPED_DATA  - 0x0400 - Filter samples not equal to IMU samples
        //  FILTER_RATE_MISMATCH - 0x0200 - Filter major cycle rate mismatch
        //  FILTER_STUCK         - 0x0100 - No filter data received in 1 second
        static constexpr uint16 IMU_PROCESS_FAULT    = 0x8000; // The IMU subsystem is unresponsive or not operating normally
        static constexpr uint16 IMU_RATE_MISMATCH    = 0x4000; // Faster/slower than expected base rate
        static constexpr uint16 IMU_DROPPED_DATA     = 0x2000; // At least 1 dropped frame / overrun
        static constexpr uint16 IMU_STUCK            = 0x1000; // No IMU data received in 1 second

        static constexpr uint16 FILTER_PROCESS_FAULT = 0x0800; // The Filter subsystem is unresponsive or not operating normally
        static constexpr uint16 FILTER_DROPPED_DATA  = 0x0400; // Filter samples not equal to IMU samples
        static constexpr uint16 FILTER_RATE_MISMATCH = 0x0200; // Filter major cycle rate mismatch
        static constexpr uint16 FILTER_STUCK         = 0x0100; // No filter data received in 1 second

        //API Function: imuProcessFault
        //  Gets the value of the IMU Process Fault bit (bit 16)
        //
        //Returns:
        //  bool - true: The IMU subsystem is unresponsive or not operating normally
        bool imuProcessFault() const;

        //API Function: imuDataRateMismatch
        //  Gets the value of the IMU Data Rate Mismatch bit (bit 17)
        //
        //Returns:
        //  bool - true: Faster/slower than expected base rate
        bool imuRateMismatch() const;

        //API Function: imuDroppedData
        //  Gets the value of the IMU Overrun Dropped Data bit (bit 18)
        //
        //Returns:
        //  bool - true: At least 1 dropped frame / overrun
        bool imuDroppedData() const;

        //API Function: imuStuck
        //  Gets the value of the IMU Stuck bit (bit 19)
        //
        //Returns:
        //  bool - true: No IMU data received in 1 second
        bool imuStuck() const;

        //API Function: filterProcessFault
        //  Gets the value of the Filter Process Fault bit (bit 20)
        //
        //Returns:
        //  bool - true: The Filter subsystem is unresponsive or not operating normally
        bool filterProcessFault() const;

        //API Function: filterDroppedData
        //  Gets the value of the Filter Dropped Data bit (bit 21)
        //
        //Returns:
        //  bool - true: Filter samples not equal to IMU samples
        bool filterDroppedData() const;

        //API Function: filterRateMismatch
        //  Gets the value of the Filter Rate Mismatch bit (bit 22)
        //
        //Returns:
        //  bool - true: Filter major cycle rate mismatch
        bool filterRateMismatch() const;

        //API Function: filterStuck
        //  Gets the value of the Filter Stuck bit (bit 23)
        //
        //Returns:
        //  bool - true: No filter data received in 1 second
        bool filterStuck() const;
    };

    //API Struct: CV7ContinuousBIT_System
    //  Continuous Built-In Test flags for system information
    //
    //  Bits 0-31 of the original 128 bit Continuous Built-In Test flags
    struct CV7ContinuousBIT_System : ContinuousBIT_System
    {
        //API Constructor: CV7ContinuousBIT_System
        CV7ContinuousBIT_System() = default;

        //API Constructor: CV7ContinuousBIT_System
        //
        //Parameters:
        //  bits - Value of bits 0-31 of the original 128 bit Continuous Built-In Test flags
        explicit CV7ContinuousBIT_System(uint32 bits);

        //API Function: general
        //  Gets information for general system flags (bits 0-7)
        //
        //Returns:
        //  <CV7ContinuousBIT_System_General> - Information for general system flags
        CV7ContinuousBIT_System_General general() const;

        //API Function: process
        //  Gets information for system process flags (bits 16-31)
        //
        //Returns:
        //  <CV7ContinuousBIT_System_Process> - Information for system process flags
        CV7ContinuousBIT_System_Process process() const;

    private:
        //Variable: m_general
        //  <ContinuousBIT_System_General> information for general system flags (bits 0-7)
        CV7ContinuousBIT_System_General m_general;

        //Variable: m_process
        //  <ContinuousBIT_System_Process> information for system process flags (bits 16-31)
        CV7ContinuousBIT_System_Process m_process;
    };

    //API Struct: CV7ContinuousBIT_IMU_General
    //  Continuous Built-In Test flags for general IMU information
    //
    //  Bits 32-39 of the original 128 bit Continuous Built-In Test flags
    struct CV7ContinuousBIT_IMU_General : ContinuousBIT_IMU_General
    {
        //API Constructor: CV7ContinuousBIT_IMU_General
        CV7ContinuousBIT_IMU_General() = default;

        //API Constructor: CV7ContinuousBIT_IMU_General
        //
        //Parameters:
        //  bits - Bits 32-39 of the original 128 bit Continuous Built-In Test flags
        explicit CV7ContinuousBIT_IMU_General(const uint8 bits) : ContinuousBIT_IMU_General(bits) {}
    };

    //API Struct: CV7ContinuousBIT_IMU_Sensors
    //  Continuous Built-In Test flags for IMU sensors information
    //
    //  Bits 40-55 of the original 128 bit Continuous Built-In Test flags
    struct CV7ContinuousBIT_IMU_Sensors : ContinuousBIT_IMU_Sensors
    {
        //API Constructor: CV7ContinuousBIT_IMU_Sensors
        CV7ContinuousBIT_IMU_Sensors() = default;

        //API Constructor: CV7ContinuousBIT_IMU_Sensors
        //
        //Parameters:
        //  bits - Bits 40-55 of the original 128 bit Continuous Built-In Test flags
        explicit CV7ContinuousBIT_IMU_Sensors(const uint16 bits) : ContinuousBIT_IMU_Sensors(bits) {}
    };

    //API Struct: CV7ContinuousBIT_IMU
    //  Continuous Built-In Test flags for IMU information
    //
    //  Bits 32-63 of the original 128 bit Continuous Built-In Test flags
    struct CV7ContinuousBIT_IMU : ContinuousBIT_IMU
    {
        //API Constructor: CV7ContinuousBIT_IMU
        CV7ContinuousBIT_IMU() = default;

        //API Constructor: CV7ContinuousBIT_IMU
        //
        //Parameters:
        //  bits - Value of bits 32-63 of the original 128 bit Continuous Built-In Test flags
        explicit CV7ContinuousBIT_IMU(uint32 bits);

        //Constants: Bitmasks
        //  FACTORY_BITS_INVALID - 0x00000001 - Factory settings invalid. Device unusable (56)
        //
        //Note:
        //  These masks are shifted 32 bits to the right from the original 128 bitmask to have a 0 index at bit 32
        static constexpr uint32 FACTORY_BITS_INVALID = 0x00000001; // Factory settings invalid. Device unusable

        //API Function: general
        //  Gets information for general IMU flags (bits 32-39)
        //
        //Returns:
        //  <CV7ContinuousBIT_IMU_General> - Information for general IMU flags
        CV7ContinuousBIT_IMU_General general() const;

        //API Function: sensors
        //  Gets information for IMU sensors flags (bits 40-55)
        //
        //Returns:
        //  <CV7ContinuousBIT_IMU_Sensors> - Information for IMU sensors flags
        CV7ContinuousBIT_IMU_Sensors sensors() const;

        //API Function: factoryBitsInvalid
        //  Gets the value of the Factory Bits Invalid bit (bit 56)
        //
        //Returns:
        //  bool - true: Factory settings invalid. Device unusable
        bool factoryBitsInvalid() const;

    private:
        //Variable: m_general
        //  <CV7ContinuousBIT_IMU_General> information for general IMU flags (bits 32-39)
        CV7ContinuousBIT_IMU_General m_general;

        //Variable: m_sensors;
        //  <CV7ContinuousBIT_IMU_Sensors> information for IMU sensors flags (bits 40-55)
        CV7ContinuousBIT_IMU_Sensors m_sensors;
    };

    //API Struct: CV7ContinuousBIT_Filter_General
    //  Continuous Built-In Test flags for general filter information
    //
    //  Bits 64-71 of the original 128 bit Continuous Built-In Test flags
    struct CV7ContinuousBIT_Filter_General : ContinuousBIT_Filter_General
    {
        //API Constructor: CV7ContinuousBIT_Filter_General
        CV7ContinuousBIT_Filter_General() = default;

        //API Constructor: CV7ContinuousBIT_Filter_General
        //
        //Parameters:
        //  bits - Bits 64-71 of the original 128 bit Continuous Built-In Test flags
        explicit CV7ContinuousBIT_Filter_General(const uint8 bits) : ContinuousBIT_Filter_General(bits) {}

        //API Constants: Bitmasks
        //  Bitmasks for general filter flags
        //
        //Note:
        //  These masks are shifted 64 bits to the right from the original 128 bitmask to have a 0 index at bit 64
        //
        //  FAULT - 0x01 - Filter processes will not initialize
        static constexpr uint8 FAULT = 0x01; // Filter processes will not initialize

        //API Function: fault
        //  Gets the value of the Filter Fault bit (bit 64)
        //
        //Returns:
        //  bool - true: Filter processes will not initialize
        bool fault() const;
    };

    //API Struct: CV7ContinuousBIT_Filter
    //  Continuous Built-In Test flags for filter information
    //
    //  Bits 64-95 of the original 128 bit Continuous Built-In Test flags
    struct CV7ContinuousBIT_Filter : ContinuousBIT_Filter
    {
        //API Constructor: CV7ContinuousBIT_Filter
        CV7ContinuousBIT_Filter() = default;

        //API Constructor: CV7ContinuousBIT_Filter
        //
        //Parameters:
        //  bits - Value of bits 64-95 of the original 128 bit Continuous Built-In Test flags
        explicit CV7ContinuousBIT_Filter(uint32 bits);

        //API Function: general
        //  Gets information for general filter flags (bits 64-71)
        //
        //Returns:
        //  <CV7ContinuousBIT_Filter_General> - Information for general filter flags
        CV7ContinuousBIT_Filter_General general() const;

    private:
        //Variable: m_general
        //  <CV7ContinuousBIT_Filter_General> information for general filter flags (bits 64-71)
        CV7ContinuousBIT_Filter_General m_general;
    };

    //API Class: CV7ContinuousBIT
    //  Continuous Built-In Test flag data
    //
    //  See the CV7 <Built-in Test: https://s3.amazonaws.com/files.microstrain.com/CV7+Online/user_manual_content/additional_features/Built-in%20Test.htm>
    //  documentation for more information
    class CV7ContinuousBIT : public ContinuousBIT
    {
    public:
        //API Constructor: CV7ContinuousBIT
        CV7ContinuousBIT() = delete;

        //API Constructor: CV7ContinuousBIT
        //
        //Parameters:
        //  bytes - Flag values from Continuous Built-In Test
        explicit CV7ContinuousBIT(Bytes bytes);


        /**********************
        ****  System Bits  ****
        **********************/

        //API Function: system
        //  Gets information for system flags (bits 0-31)
        //
        //Returns:
        //  <CV7ContinuousBIT_System> - Information for system flags
        CV7ContinuousBIT_System system() const;

        //API Function: systemClockFailure
        //  Gets the value of the System Clock Failure bit (bit 0)
        //
        //Returns:
        //  bool - true: The system clock is not operating properly
        bool systemClockFailure() const override;

        //API Function: powerFault
        //  Gets the value of the Power Fault bit (bit 1)
        //
        //Returns:
        //  bool - true: Power supply voltage is outside the recommended range, or an internal power fault exists
        bool powerFault() const override;

        //API Function: firmwareFault
        //  Gets the value of the Firmware Fault bit (bit 4)
        //
        //Returns:
        //  bool - true: System firmware has detected an unexpected or abnormal condition
        bool firmwareFault() const override;

        //API Function: timingOverload
        //  Gets the value of the Timing Overload bit (bit 5)
        //
        //Returns:
        //  bool - true: The system is unable to keep up with the processing demand
        bool timingOverload() const override;

        //API Function: bufferOverrun
        //  Gets the value of the Buffer Overrun bit (bit 6)
        //
        //Returns:
        //  bool - true: A data buffer in the system has reached its capacity
        bool bufferOverrun() const override;

        //API Function: imuProcessFault
        //  Gets the value of the IMU Process Fault bit (bit 16)
        //
        //Returns:
        //  bool - true: The IMU subsystem is unresponsive or not operating normally
        bool imuProcessFault() const;

        //API Function: imuDataRateMismatch
        //  Gets the value of the IMU Data Rate Mismatch bit (bit 17)
        //
        //Returns:
        //  bool - true: Faster/slower than expected base rate
        bool imuRateMismatch() const;

        //API Function: imuDroppedData
        //  Gets the value of the IMU Overrun Dropped Data bit (bit 18)
        //
        //Returns:
        //  bool - true: At least 1 dropped frame / overrun
        bool imuDroppedData() const;

        //API Function: imuStuck
        //  Gets the value of the IMU Stuck bit (bit 19)
        //
        //Returns:
        //  bool - true: No IMU data received in 1 second
        bool imuStuck() const;

        //API Function: filterProcessFault
        //  Gets the value of the Filter Process Fault bit (bit 20)
        //
        //Returns:
        //  bool - true: The Filter subsystem is unresponsive or not operating normally
        bool filterProcessFault() const;

        //API Function: filterDroppedData
        //  Gets the value of the Filter Dropped Data bit (bit 21)
        //
        //Returns:
        //  bool - true: Filter samples not equal to IMU samples
        bool filterDroppedData() const;

        //API Function: filterRateMismatch
        //  Gets the value of the Filter Rate Mismatch bit (bit 22)
        //
        //Returns:
        //  bool - true: Filter major cycle rate mismatch
        bool filterRateMismatch() const;

        //API Function: filterStuck
        //  Gets the value of the Filter Stuck bit (bit 23)
        //
        //Returns:
        //  bool - true: No filter data received in 1 second
        bool filterStuck() const;


        /*******************
        ****  IMU Bits  ****
        *******************/

        //API Function: imu
        //  Gets information for IMU flags (bits 32-63)
        //
        //Returns:
        //  <CV7ContinuousBIT_IMU> - Information for IMU flags
        CV7ContinuousBIT_IMU imu() const;

        //API Function: imuClockFault
        //  Gets the value of the IMU Clock Fault bit (bit 32)
        //
        //Returns:
        //  bool - true: IMU is not running off the system clock
        bool imuClockFault() const override;

        //API Function: imuCommunicationFault
        //  Gets the value of the IMU Communication Fault bit (bit 33)
        //
        //Returns:
        //  bool - true: No communication with IMU
        bool imuCommunicationFault() const override;

        //API Function: imuTimingOverrun
        //  Gets the value of the IMU Timing Overrun bit (bit 34)
        //
        //Returns:
        //  bool - true: IMU processes are taking longer than their allotted time
        bool imuTimingOverrun() const override;

        //API Function: imuCalibrationErrorAccel
        //  Gets the value of the IMU Calibration Error Accelerometer bit (bit 36)
        //
        //Returns:
        //  bool - true: A problem is detected with the accelerometer calibration
        bool imuCalibrationErrorAccel() const override;

        //API Function: imuCalibrationErrorGyro
        //  Gets the value of the IMU Calibration Error Gyroscope bit (bit 37)
        //
        //Returns:
        //  bool - true: A problem is detected with the gyroscope calibration
        bool imuCalibrationErrorGyro() const override;

        //API Function: imuCalibrationErrorMag
        //  Gets the value of the IMU Calibration Error Magnetometer bit (bit 38)
        //
        //Returns:
        //  bool - true: A problem is detected with the magnetometer calibration
        bool imuCalibrationErrorMag() const override;

        //API Function: accelGeneralFault
        //  Gets the value of the Accelerometer General Fault bit (bit 40)
        //
        //Returns:
        //  bool - true: Accelerometer will not initialize
        bool accelGeneralFault() const override;

        //API Function: accelOverrange
        //  Gets the value of the Accelerometer Overrange bit (bit 41)
        //
        //Returns:
        //  bool - true: One or more axes subjected to accelerations near or outside the selected range
        bool accelOverrange() const override;

        //API Function: accelSelfTest
        //  Gets the value of the Accelerometer Self Test bit (bit 42)
        //
        //Returns:
        //  bool - true: The internal self-test of the accelerometer failed
        bool accelSelfTestFail() const override;

        //API Function: gyroGeneralFault
        //  Gets the value of the Gyroscope General Fault bit (bit 44)
        //
        //Returns:
        //  bool - true: Gyroscope will not initialize
        bool gyroGeneralFault() const override;

        //API Function: gyroOverrange
        //  Gets the value of the Gyroscope Overrange bit (bit 45)
        //
        //Returns:
        //  bool - true: One or more axes subjected to rotational rates near or outside the selected range
        bool gyroOverrange() const override;

        //API Function: gyroSelfTest
        //  Gets the value of the Gyroscope Self Test bit (bit 46)
        //
        //Returns:
        //  bool - true: The internal self-test of the gyroscope failed
        bool gyroSelfTestFail() const override;

        //API Function: magGeneralFault
        //  Gets the value of the Magnetometer General Fault bit (bit 48)
        //
        //Returns:
        //  bool - true: Magnetometer will not initialize
        bool magGeneralFault() const override;

        //API Function: magOverrange
        //  Gets the value of the Magnetometer Overrange bit (bit 49)
        //
        //Returns:
        //  bool - true: One or more axes subjected to magnetic fields strengths near or outside the supported range
        bool magOverrange() const override;

        //API Function: magSelfTest
        //  Gets the value of the Magnetometer Self Test bit (bit 50)
        //
        //Returns:
        //  bool - true: The internal self-test of the magnetometer failed
        bool magSelfTestFail() const override;

        //API Function: pressureGeneralFault
        //  Gets the value of the Pressure General Fault bit (bit 52)
        //
        //Returns:
        //  bool - true: Pressure sensor won't initialize
        bool pressureGeneralFault() const override;

        //API Function: pressureOverrange
        //  Gets the value of the Pressure Overrange bit (bit 53)
        //
        //Returns:
        //  bool - true: Pressure sensor subjected to pressures above or below the supported range
        bool pressureOverrange() const override;

        //API Function: pressureSelfTest
        //  Gets the value of the Pressure Self Test bit (bit 54)
        //
        //Returns:
        //  bool - true: The internal self-test of the pressure sensor failed
        bool pressureSelfTestFail() const override;

        //API Function: factoryBitsInvalid
        //  Gets the value of the Factory Bits Invalid bit (bit 56)
        //
        //Returns:
        //  bool - true: Factory settings invalid. Device unusable
        bool factoryBitsInvalid() const;


        /**********************
        ****  Filter Bits  ****
        **********************/

        //API Function: filter
        //  Gets information for filter flags (bits 64-95)
        //
        //Returns:
        //  <CV7ContinuousBIT_Filter> - Information for filter flags
        CV7ContinuousBIT_Filter filter() const;

        //API Function: filterFault
        //  Gets the value of the Filter Fault bit (bit 64)
        //
        //Returns:
        //  bool - true: Filter processes will not initialize
        bool filterFault() const;

        //API Function: filterTimingOverrun
        //  Gets the value of the Filter Timing Overrun bit (bit 66)
        //
        //Returns:
        //  bool - true: Filter processes are taking longer than their allotted time
        bool filterTimingOverrun() const override;

        //API Function: filterTimingUnderrun
        //  Gets the value of the Filter Timing Underrun bit (bit 67)
        //
        //Returns:
        //  bool - true: Filter processes are being skipped
        bool filterTimingUnderrun() const override;

        //API Function: as_MipDataPoints
        //  Gets the data formatted as <MipDataPoint> objects.
        //
        //Returns:
        //  <MipDataPoints> - data in DataPoint format
        MipDataPoints as_MipDataPoints() const override;

    private:
        //Variable: m_system
        //  <CV7ContinuousBIT_System> information for system flags (bits 0-31)
        CV7ContinuousBIT_System m_system;

        //Variable: m_imu
        //  <CV7ContinuousBIT_IMU> information for IMU flags (bits 32-63)
        CV7ContinuousBIT_IMU m_imu;

        //Variable: m_filter
        //  <CV7ContinuousBIT_Filter> information for filter flags (bits 64-95)
        CV7ContinuousBIT_Filter m_filter;
    };


    /************************************************
    ****                   GQ7                   ****
    ****     Structures for parsing GQ7 BIT      ****
    ************************************************/

    //API Struct: GQ7ContinuousBIT_System_General
    //  Continuous Built-In Test flags for general system information
    //
    //  Bits 0-7 of the original 128 bit Continuous Built-In Test flags
    struct GQ7ContinuousBIT_System_General : ContinuousBIT_System_General
    {
        //API Constructor: GQ7ContinuousBIT_System_General
        GQ7ContinuousBIT_System_General() = default;

        //API Constructor: GQ7ContinuousBIT_System_General
        //
        //Parameters:
        //  bits - Bits 0-7 of the original 128 bit Continuous Built-In Test flags
        explicit GQ7ContinuousBIT_System_General(const uint8 bits) : ContinuousBIT_System_General(bits) {}
    };

    //API Struct: GQ7ContinuousBIT_System_Process
    //  Continuous Built-In Test flags for system process information
    //
    //  Bits 16-31 of the original 128 bit Continuous Built-In Test flags
    struct GQ7ContinuousBIT_System_Process : ContinuousBIT_System_Process
    {
        //API Constructor: GQ7ContinuousBIT_System_Process
        GQ7ContinuousBIT_System_Process() : ContinuousBIT_System_Process() {}

        //API Constructor: GQ7ContinuousBIT_System_Process
        //
        //Parameters:
        //  bits - Bits 16-31 of the original 128 bit Continuous Built-In Test flags
        explicit GQ7ContinuousBIT_System_Process(const uint16 bits) : ContinuousBIT_System_Process(bits) {}

        //API Constants: Bitmasks
        //  Bitmasks for system process information flags
        //
        //Note:
        //  These masks are shifted 16 bits to the right from the original 128 bitmask to have a 0 index at bit 16
        //
        //  IMU_CONTROL_LINE_FAULT        - 0x0100 - The IMU control line is not behaving as expected
        //  IMU_COMMAND_RESPONSE_FAULT    - 0x0200 - The IMU is not responsive to commands
        //  IMU_SPI_TRANSFER_FAULT        - 0x0400 - Misaligned/failed IMU SPI transfers
        //  IMU_DATA_FRAME_FAULT          - 0x0800 - Missing IMU data frame(s)
        //  FILTER_CONTROL_LINE_FAULT     - 0x1000 - The filter control line is not behaving as expected
        //  FILTER_COMMAND_RESPONSE_FAULT - 0x2000 - The filter is not responsive to commands
        //  FILTER_SPI_TRANSFER_FAULT     - 0x4000 - Misaligned/failed filter SPI transfers
        //  FILTER_DATA_FRAME_FAULT       - 0x8000 - Missing filter data frame(s)
        //  GNSS_CONTROL_LINE_FAULT       - 0x0001 - The GNSS control line is not behaving as expected
        //  GNSS_COMMAND_RESPONSE_FAULT   - 0x0002 - The GNSS is not responsive to commands
        //  GNSS_SPI_TRANSFER_FAULT       - 0x0004 - Misaligned/failed GNSS SPI transfers
        //  GNSS_DATA_FRAME_FAULT         - 0x0008 - Missing GNSS data frame(s)
        static constexpr uint16 IMU_CONTROL_LINE_FAULT        = 0x0100; // The IMU control line is not behaving as expected
        static constexpr uint16 IMU_COMMAND_RESPONSE_FAULT    = 0x0200; // The IMU is not responsive to commands
        static constexpr uint16 IMU_SPI_TRANSFER_FAULT        = 0x0400; // Misaligned/failed IMU SPI transfers
        static constexpr uint16 IMU_DATA_FRAME_FAULT          = 0x0800; // Missing IMU data frame(s)

        static constexpr uint16 FILTER_CONTROL_LINE_FAULT     = 0x1000; // The filter control line is not behaving as expected
        static constexpr uint16 FILTER_COMMAND_RESPONSE_FAULT = 0x2000; // The filter is not responsive to commands
        static constexpr uint16 FILTER_SPI_TRANSFER_FAULT     = 0x4000; // Misaligned/failed filter SPI transfers
        static constexpr uint16 FILTER_DATA_FRAME_FAULT       = 0x8000; // Missing filter data frame(s)

        static constexpr uint16 GNSS_CONTROL_LINE_FAULT       = 0x0001; // The GNSS control line is not behaving as expected
        static constexpr uint16 GNSS_COMMAND_RESPONSE_FAULT   = 0x0002; // The GNSS is not responsive to commands
        static constexpr uint16 GNSS_SPI_TRANSFER_FAULT       = 0x0004; // Misaligned/failed GNSS SPI transfers
        static constexpr uint16 GNSS_DATA_FRAME_FAULT         = 0x0008; // Missing GNSS data frame(s)

        //API Function: imuIpcFault
        //  Gets the value of the IMU IPC fault flags (bits 16-19)
        //
        //Note:
        //  Bits 0-3 of this value correspond to bits 16-19
        //
        //Returns:
        //  uint8 - Value of the IMU IPC fault flags
        uint8 imuIpcFault() const;

        //API Function: imuControlLineFault
        //  Gets the value of the IMU Control Line Fault bit (bit 16)
        //
        //Returns:
        //  bool - true: The IMU control line is not behaving as expected
        bool imuControlLineFault() const;

        //API Function: imuCommandResponseFault
        //  Gets the value of the IMU Command Response Fault bit (bit 17)
        //
        //Returns:
        //  bool - true: The IMU is not responsive to commands
        bool imuCommandResponseFault() const;

        //API Function: imuSpiTransferFault
        //  Gets the value of the IMU SPI Transfer Fault bit (bit 18)
        //
        //Returns:
        //  bool - true: Misaligned/failed IMU SPI transfers
        bool imuSpiTransferFault() const;

        //API Function: imuDataFrameFault
        //  Gets the value of the IMU Data Frame Fault bit (bit 19)
        //
        //Returns:
        //  bool - true: Missing IMU data frame(s)
        bool imuDataFrameFault() const;

        //API Function: filterIpcFault
        //  Gets the value of the Filter IPC fault flags (bits 20-23)
        //
        //Note:
        //  Bits 0-3 of this value correspond to bits 20-23
        //
        //Returns:
        //  uint8 - Value of the filter IPC fault flags
        uint8 filterIpcFault() const;

        //API Function: filterControlLineFault
        //  Gets the value of the Filter Control Line Fault bit (bit 20)
        //
        //Returns:
        //  bool - true: The filter control line is not behaving as expected
        bool filterControlLineFault() const;

        //API Function: filterCommandResponseFault
        //  Gets the value of the Filter Command Response Fault bit (bit 21)
        //
        //Returns:
        //  bool - true: The filter is not responsive to commands
        bool filterCommandResponseFault() const;

        //API Function: filterSpiTransferFault
        //  Gets the value of the Filter SPI Transfer Fault bit (bit 22)
        //
        //Returns:
        //  bool - true: Misaligned/failed filter SPI transfers
        bool filterSpiTransferFault() const;

        //API Function: filterDataFrameFault
        //  Gets the value of the Filter Data Frame Fault bit (bit 23)
        //
        //Returns:
        //  bool - true: Missing filter data frame(s)
        bool filterDataFrameFault() const;

        //API Function: gnssIpcFault
        //  Gets the value of the GNSS IPC fault flags (bits 24-27)
        //
        //Note:
        //  Bits 0-3 of this value correspond to bits 24-27
        //
        //Returns:
        //  uint8 - Value of the GNSS IPC fault flags
        uint8 gnssIpcFault() const;

        //API Function: gnssControlLineFault
        //  Gets the value of the GNSS Control Line Fault bit (bit 24)
        //
        //Returns:
        //  bool - true: The GNSS control line is not behaving as expected
        bool gnssControlLineFault() const;

        //API Function: gnssCommandResponseFault
        //  Gets the value of the GNSS Command Response Fault bit (bit 25)
        //
        //Returns:
        //  bool - true: The GNSS is not responsive to commands
        bool gnssCommandResponseFault() const;

        //API Function: gnssSpiTransferFault
        //  Gets the value of the GNSS SPI Transfer Fault bit (bit 26)
        //
        //Returns:
        //  bool - true: Misaligned/failed GNSS SPI transfers
        bool gnssSpiTransferFault() const;

        //API Function: gnssDataFrameFault
        //  Gets the value of the GNSS Data Frame Fault bit (bit 27)
        //
        //Returns:
        //  bool - true: Missing GNSS data frame(s)
        bool gnssDataFrameFault() const;
    };

    //API Struct: GQ7ContinuousBIT_System
    //  Continuous Built-In Test flags for system information
    //
    //  Bits 0-31 of the original 128 bit Continuous Built-In Test flags
    struct GQ7ContinuousBIT_System : ContinuousBIT_System
    {
        //API Constructor: GQ7ContinuousBIT_System
        GQ7ContinuousBIT_System() = default;

        //API Constructor: GQ7ContinuousBIT_System
        //
        //Parameters:
        //  bits - Value of bits 0-31 of the original 128 bit Continuous Built-In Test flags
        explicit GQ7ContinuousBIT_System(uint32 bits);

        //API Function: general
        //  Gets information for general system flags (bits 0-7)
        //
        //Returns:
        //  <GQ7ContinuousBIT_System_General> - Information for general system flags
        GQ7ContinuousBIT_System_General general() const;

        //API Function: process
        //  Gets information for system process flags (bits 16-31)
        //
        //Returns:
        //  <GQ7ContinuousBIT_System_Process> - Information for system process flags
        GQ7ContinuousBIT_System_Process process() const;

    private:
        //Variable: m_general
        //  <ContinuousBIT_System_General> information for general system flags (bits 0-7)
        GQ7ContinuousBIT_System_General m_general;

        //Variable: m_process
        //  <ContinuousBIT_System_Process> information for system process flags (bits 16-31)
        GQ7ContinuousBIT_System_Process m_process;
    };

    //API Struct: GQ7ContinuousBIT_IMU_General
    //  Continuous Built-In Test flags for general IMU information
    //
    //  Bits 32-39 of the original 128 bit Continuous Built-In Test flags
    struct GQ7ContinuousBIT_IMU_General : ContinuousBIT_IMU_General
    {
        //API Constructor: GQ7ContinuousBIT_IMU_General
        GQ7ContinuousBIT_IMU_General() = default;

        //API Constructor: GQ7ContinuousBIT_IMU_General
        //
        //Parameters:
        //  bits - Bits 32-39 of the original 128 bit Continuous Built-In Test flags
        explicit GQ7ContinuousBIT_IMU_General(const uint8 bits) : ContinuousBIT_IMU_General(bits) {}
    };

    //API Struct: GQ7ContinuousBIT_IMU_Sensors
    //  Continuous Built-In Test flags for IMU sensors information
    //
    //  Bits 40-55 of the original 128 bit Continuous Built-In Test flags
    struct GQ7ContinuousBIT_IMU_Sensors : ContinuousBIT_IMU_Sensors
    {
        //API Constructor: GQ7ContinuousBIT_IMU_Sensors
        GQ7ContinuousBIT_IMU_Sensors() = default;

        //API Constructor: GQ7ContinuousBIT_IMU_Sensors
        //
        //Parameters:
        //  bits - Bits 40-55 of the original 128 bit Continuous Built-In Test flags
        explicit GQ7ContinuousBIT_IMU_Sensors(const uint16 bits) : ContinuousBIT_IMU_Sensors(bits) {}
    };

    //API Struct: GQ7ContinuousBIT_IMU
    //  Continuous Built-In Test flags for IMU information
    //
    //  Bits 32-63 of the original 128 bit Continuous Built-In Test flags
    struct GQ7ContinuousBIT_IMU : ContinuousBIT_IMU
    {
        //API Constructor: GQ7ContinuousBIT_IMU
        GQ7ContinuousBIT_IMU() = default;

        //API Constructor: GQ7ContinuousBIT_IMU
        //
        //Parameters:
        //  bits - Value of bits 32-63 of the original 128 bit Continuous Built-In Test flags
        explicit GQ7ContinuousBIT_IMU(uint32 bits);

        //API Function: general
        //  Gets information for general IMU flags (bits 32-39)
        //
        //Returns:
        //  <GQ7ContinuousBIT_IMU_General> - Information for general IMU flags
        GQ7ContinuousBIT_IMU_General general() const;

        //API Function: sensors
        //  Gets information for IMU sensors flags (bits 40-55)
        //
        //Returns:
        //  <GQ7ContinuousBIT_IMU_Sensors> - Information for IMU sensors flags
        GQ7ContinuousBIT_IMU_Sensors sensors() const;

    private:
        //Variable: m_general
        //  <GQ7ContinuousBIT_IMU_General> information for general IMU flags (bits 32-39)
        GQ7ContinuousBIT_IMU_General m_general;

        //Variable: m_sensors;
        //  <GQ7ContinuousBIT_IMU_Sensors> information for IMU sensors flags (bits 40-55)
        GQ7ContinuousBIT_IMU_Sensors m_sensors;
    };

    //API Struct: GQ7ContinuousBIT_Filter_General
    //  Continuous Built-In Test flags for general filter information
    //
    //  Bits 64-71 of the original 128 bit Continuous Built-In Test flags
    struct GQ7ContinuousBIT_Filter_General : ContinuousBIT_Filter_General
    {
        //API Constructor: GQ7ContinuousBIT_Filter_General
        GQ7ContinuousBIT_Filter_General() = default;

        //API Constructor: GQ7ContinuousBIT_Filter_General
        //
        //Parameters:
        //  bits - Bits 64-71 of the original 128 bit Continuous Built-In Test flags
        explicit GQ7ContinuousBIT_Filter_General(const uint8 bits) : ContinuousBIT_Filter_General(bits) {}

        //API Constants: Bitmasks
        //  Bitmasks for general filter flags
        //
        //Note:
        //  These masks are shifted 64 bits to the right from the original 128 bitmask to have a 0 index at bit 64
        //
        //  CLOCK_FAULT                    - 0x01 - The filter subsystem is not running off the system clock
        //  HARDWARE_FAULT                 - 0x02 - Filter hardware initialization error
        //  IMU_SPI_COMMUNICATION_ERROR    - 0x10 - No communication on the IMU SPI port
        //  GNSS_SPI_COMMUNICATION_ERROR   - 0x20 - No communication on the GNSS SPI port
        //  COMMS_SPI_COMMUNICATION_ERROR  - 0x40 - No communication on the COMMS SPI port
        //  COMMS_UART_COMMUNICATION_ERROR - 0x80 - No communication on the COMMS UART port
        static constexpr uint8 CLOCK_FAULT                    = 0x01; // The filter subsystem is not running off the system clock
        static constexpr uint8 HARDWARE_FAULT                 = 0x02; // Filter hardware initialization error

        static constexpr uint8 COMMUNICATION_ERROR_IMU_SPI    = 0x10; // No communication on the IMU SPI port
        static constexpr uint8 COMMUNICATION_ERROR_GNSS_SPI   = 0x20; // No communication on the GNSS SPI port
        static constexpr uint8 COMMUNICATION_ERROR_COMMS_SPI  = 0x40; // No communication on the COMMS SPI port
        static constexpr uint8 COMMUNICATION_ERROR_COMMS_UART = 0x80; // No communication on the COMMS UART port

        //API Function: clockFault
        //  Gets the value of the Filter Clock Fault bit (bit 64)
        //
        //Returns:
        //  bool - true: The filter subsystem is not running off the system clock
        bool clockFault() const;

        //API Function: hardwareFault
        //  Gets the value of the Filter Hardware Fault bit (bit 65)
        //
        //Returns:
        //  bool - true: Filter hardware initialization error
        bool hardwareFault() const;

        //API Function: communicationError
        //  Gets the value of the Filter Communication Error flags (bits 68-71)
        //
        //Note:
        //  Bits 0-3 of this value correspond to bits 68-71
        //
        //Returns:
        //  uint8 - Value of the Filter Communication Error flags
        uint8 communicationError() const;

        //API Function: communicationErrorImuSpi
        //  Gets the value of the Filter Communication Error IMU SPI bit (bit 68)
        //
        //Returns:
        //  bool - true: No filter communication on the IMU SPI port
        bool communicationErrorImuSpi() const;

        //API Function: communicationErrorGnssSpi
        //  Gets the value of the Filter Communication Error GNSS SPI bit (bit 69)
        //
        //Returns:
        //  bool - true: No filter communication on the GNSS SPI port
        bool communicationErrorGnssSpi() const;

        //API Function: communicationErrorCommsSpi
        //  Gets the value of the Filter Communication Error COMMS SPI bit (bit 70)
        //
        //Returns:
        //  bool - true: No filter communication on the COMMS SPI port
        bool communicationErrorCommsSpi() const;

        //API Function: communicationErrorCommsUart
        //  Gets the value of the Filter Communication Error COMMS UART bit (bit 71)
        //
        //Returns:
        //  bool - true: No filter communication on the COMMS UART port
        bool communicationErrorCommsUart() const;
    };

    //API Struct: GQ7ContinuousBIT_Filter
    //  Continuous Built-In Test flags for filter information
    //
    //  Bits 64-95 of the original 128 bit Continuous Built-In Test flags
    struct GQ7ContinuousBIT_Filter : ContinuousBIT_Filter
    {
        //API Constructor: GQ7ContinuousBIT_Filter
        GQ7ContinuousBIT_Filter() = default;

        //API Constructor: GQ7ContinuousBIT_Filter
        //
        //Parameters:
        //  bits - Value of bits 64-95 of the original 128 bit Continuous Built-In Test flags
        explicit GQ7ContinuousBIT_Filter(uint32 bits);

        //API Function: general
        //  Gets information for general filter flags (bits 64-71)
        //
        //Returns:
        //  <GQ7ContinuousBIT_Filter_General> - Information for general filter flags
        GQ7ContinuousBIT_Filter_General general() const;

    private:
        //Variable: m_general
        //  <GQ7ContinuousBIT_Filter_General> information for general filter flags (bits 64-71)
        GQ7ContinuousBIT_Filter_General m_general;
    };

    //API Struct: GQ7ContinuousBIT_GNSS_General
    //  Continuous Built-In Test flags for general GNSS information
    //
    //  Bits 96-103 of the original 128 bit Continuous Built-In Test flags
    struct GQ7ContinuousBIT_GNSS_General : Bitfield
    {
        //API Constructor: GQ7ContinuousBIT_GNSS_General
        GQ7ContinuousBIT_GNSS_General() = default;

        //API Constructor: GQ7ContinuousBIT_GNSS_General
        //
        //Parameters:
        //  bits - Bits 96-103 of the original 128 bit Continuous Built-In Test flags
        explicit GQ7ContinuousBIT_GNSS_General(const uint8 bits) : Bitfield(static_cast<uint64>(bits)) {}

        //API Constants: Bitmasks
        //  Bitmasks for general GNSS flags
        //
        //Note:
        //  These masks are shifted 96 bits to the right from the original 128 bitmask to have a 0 index at bit 96
        //
        //  CLOCK_FAULT                      - 0x01 - The GNSS subsystem is not running off the system clock
        //  HARDWARE_FAULT                   - 0x02 - GNSS hardware initialization error
        //  COMMUNICATION_ERROR_COMMS_SERIAL - 0x04 - No communication on the COMMS Serial port
        //  COMMUNICATION_ERROR_COMMS_SPI    - 0x08 - No communication on the COMMS SPI port
        //  COMMUNICATION_ERROR_NAV_SPI      - 0x10 - No communication on the NAV SPI port
        //  GPS_TIME_FAULT                   - 0x20 - System GPS time is invalid
        //  TIMING_OVERRUN                   - 0x40 - GNSS processes are taking longer than their allotted time
        static constexpr uint8 CLOCK_FAULT                      = 0x01; // The GNSS subsystem is not running off the system clock
        static constexpr uint8 HARDWARE_FAULT                   = 0x02; // GNSS hardware initialization error

        static constexpr uint8 COMMUNICATION_ERROR_COMMS_SERIAL = 0x04; // No communication on the COMMS Serial port
        static constexpr uint8 COMMUNICATION_ERROR_COMMS_SPI    = 0x08; // No communication on the COMMS SPI port
        static constexpr uint8 COMMUNICATION_ERROR_NAV_SPI      = 0x10; // No communication on the NAV SPI port

        static constexpr uint8 GPS_TIME_FAULT                   = 0x20; // System GPS time is invalid
        static constexpr uint8 TIMING_OVERRUN                   = 0x40; // GNSS processes are taking longer than their allotted time

        //API Function: flags
        //  Gets the value of the general GNSS flags (bits 96-103)
        //
        //Returns:
        //  uint8 - Value of the general GNSS flags
        uint8 flags() const;

        //API Function: clockFault
        //  Gets the value of the GNSS Clock Fault bit (bit 96)
        //
        //Returns:
        //  bool - true: The GNSS subsystem is not running off the system clock
        bool clockFault() const;

        //API Function: hardwareFault
        //  Gets the value of the GNSS Hardware Fault bit (bit 97)
        //
        //Returns:
        //  bool - true: GNSS hardware initialization error
        bool hardwareFault() const;

        //API Function: communicationError
        //  Gets the value of the GNSS Communication Error flags (bits 98-100)
        //
        //Note:
        //  Bits 0-2 of this value correspond to bits 98-100
        //
        //Returns:
        //  uint8 - Value of the GNSS Communication Error flags
        uint8 communicationError() const;

        //API Function: communicationErrorCommsSerial
        //  Gets the value of the GNSS Communication Error COMMS Serial bit (bit 98)
        //
        //Returns:
        //  bool - true: No GNSS communication on the COMMS Serial port
        bool communicationErrorCommsSerial() const;

        //API Function: communicationErrorCommsSpi
        //  Gets the value of the GNSS Communication Error COMMS SPI bit (bit 99)
        //
        //Returns:
        //  bool - true: No GNSS communication on the COMMS SPI port
        bool communicationErrorCommsSpi() const;

        //API Function: communicationErrorNavSpi
        //  Gets the value of the GNSS Communication Error NAV SPI bit (bit 100)
        //
        //Returns:
        //  bool - true: No GNSS communication on the NAV SPI port
        bool communicationErrorNavSpi() const;

        //API Function: gpsTimeFault
        //  Gets the value of the GPS Time Fault bit (bit 101)
        //
        //Returns:
        //  bool - true: System GPS time is invalid
        bool gpsTimeFault() const;

        //API Function: timingOverrun
        //  Gets the value of the GNSS Timing Overrun bit (bit 102)
        //
        //Returns:
        //  bool - true: GNSS processes are taking longer than their allotted time
        bool timingOverrun() const;
    };

    //API Struct: GQ7ContinuousBIT_GNSS_Receivers
    //  Continuous Built-In Test flags for GNSS receivers information
    //
    //  Bits 104-119 of the original 128 bit Continuous Built-In Test flags
    struct GQ7ContinuousBIT_GNSS_Receivers : Bitfield
    {
        //API Constructor: GQ7ContinuousBIT_GNSS_Receivers
        GQ7ContinuousBIT_GNSS_Receivers() = default;

        //API Constructor: GQ7ContinuousBIT_GNSS_Receivers
        //
        //Parameters:
        //  bits - Bits 104-119 of the original 128 bit Continuous Built-In Test flags
        explicit GQ7ContinuousBIT_GNSS_Receivers(const uint16 bits) : Bitfield(static_cast<uint64>(bits)) {}

        //API Constants: Bitmasks
        //  Bitmasks for GNSS receivers flags
        //
        //Note:
        //  These masks are shifted 104 bits to the right from the original 128 bitmask to have a 0 index at bit 104
        //
        //  POWER_FAULT_RECEIVER_1    - 0x0100 - Receiver 1 internal power fault
        //  FAULT_RECEIVER_1          - 0x0200 - Receiver 1 is inoperable
        //  SHORTED_ANTENNA_1         - 0x0400 - Antenna 1 is shorted to ground
        //  OPEN_ANTENNA_1            - 0x0800 - Antenna 1 is open-circuit (or DC block is installed)
        //  SOLUTION_FAULT_RECEIVER_1 - 0x1000 - Receiver 1 solution is invalid
        //  POWER_FAULT_RECEIVER_2    - 0x2000 - Receiver 2 internal power fault
        //  FAULT_RECEIVER_2          - 0x4000 - Receiver 2 is inoperable
        //  SHORTED_ANTENNA_2         - 0x8000 - Antenna 2 is shorted to ground
        //  OPEN_ANTENNA_2            - 0x0001 - Antenna 2 is open-circuit (or DC block is installed)
        //  SOLUTION_FAULT_RECEIVER_2 - 0x0002 - Receiver 2 solution is invalid
        //  RTCM_COMMUNICATION_FAULT  - 0x0004 - RTCM data was being received previously, but it not currently being received
        //  RTK_DONGLE_FAULT          - 0x0008 - A problem has been detected with the RTK dongle. Query directly for more detail
        static constexpr uint16 POWER_FAULT_RECEIVER_1    = 0x0100; // Receiver 1 internal power fault
        static constexpr uint16 FAULT_RECEIVER_1          = 0x0200; // Receiver 1 is inoperable
        static constexpr uint16 SHORTED_ANTENNA_1         = 0x0400; // Antenna 1 is shorted to ground
        static constexpr uint16 OPEN_ANTENNA_1            = 0x0800; // Antenna 1 is open-circuit (or DC block is installed)
        static constexpr uint16 SOLUTION_FAULT_RECEIVER_1 = 0x1000; // Receiver 1 solution is invalid

        static constexpr uint16 POWER_FAULT_RECEIVER_2    = 0x2000; // Receiver 2 internal power fault
        static constexpr uint16 FAULT_RECEIVER_2          = 0x4000; // Receiver 2 is inoperable
        static constexpr uint16 SHORTED_ANTENNA_2         = 0x8000; // Antenna 2 is shorted to ground
        static constexpr uint16 OPEN_ANTENNA_2            = 0x0001; // Antenna 2 is open-circuit (or DC block is installed)
        static constexpr uint16 SOLUTION_FAULT_RECEIVER_2 = 0x0002; // Receiver 2 solution is invalid

        static constexpr uint16 RTCM_COMMUNICATION_FAULT  = 0x0004; // RTCM data was being received previously, but it not currently being received
        static constexpr uint16 RTK_DONGLE_FAULT          = 0x0008; // A problem has been detected with the RTK dongle. Query directly for more detail

        //API Function: flags
        //  Gets the value of the GNSS receivers flags (bits 104-119)
        //
        //Returns:
        //  uint16 - Value of the GNSS receivers flags
        uint16 flags() const;

        //API Function: powerFaultReceiver1
        //  Gets the value of the GNSS Receiver 1 Power Fault bit (bit 104)
        //
        //Returns:
        //  bool - true: GNSS receiver 1 internal power fault
        bool powerFaultReceiver1() const;

        //API Function: faultReceiver1
        //  Gets the value of the GNSS Receiver 1 Fault bit (bit 105)
        //
        //Returns:
        //  bool - true: GNSS receiver 1 is inoperable
        bool faultReceiver1() const;

        //API Function: shortedAntenna1
        //  Gets the value of the GNSS Antenna 1 Shorted bit (bit 106)
        //
        //Returns:
        //  bool - true: GNSS antenna 1 is shorted to ground
        bool shortedAntenna1() const;

        //API Function: openAntenna1
        //  Gets the value of the GNSS Antenna 1 Open bit (bit 107)
        //
        //Returns:
        //  bool - true: GNSS antenna 1 is open-circuit (or DC block is installed)
        bool openAntenna1() const;

        //API Function: solutionFaultReceiver1
        //  Gets the value of the GNSS Receiver 1 Solution Fault bit (bit 108)
        //
        //Returns:
        //  bool - true: GNSS receiver 1 solution is invalid
        bool solutionFaultReceiver1() const;

        //API Function: powerFaultReceiver2
        //  Gets the value of the GNSS Receiver 2 Power Fault bit (bit 109)
        //
        //Returns:
        //  bool - true: GNSS receiver 2 internal power fault
        bool powerFaultReceiver2() const;

        //API Function: faultReceiver2
        //  Gets the value of the GNSS Receiver 2 Fault bit (bit 110)
        //
        //Returns:
        //  bool - true: GNSS receiver 2 is inoperable
        bool faultReceiver2() const;

        //API Function: shortedAntenna2
        //  Gets the value of the GNSS Antenna 2 Shorted bit (bit 111)
        //
        //Returns:
        //  bool - true: GNSS antenna 2 is shorted to ground
        bool shortedAntenna2() const;

        //API Function: openAntenna2
        //  Gets the value of the GNSS Antenna 2 Open bit (bit 112)
        //
        //Returns:
        //  bool - true: GNSS antenna 2 is open-circuit (or DC block is installed)
        bool openAntenna2() const;

        //API Function: solutionFaultReceiver2
        //  Gets the value of the GNSS Receiver 2 Solution Fault bit (bit 113)
        //
        //Returns:
        //  bool - true: GNSS receiver 2 solution is invalid
        bool solutionFaultReceiver2() const;

        //API Function: rtcmCommunicationFault
        //  Gets the value of the RTCM Communication Fault bit (bit 114)
        //
        //Returns:
        //  bool - true: RTCM data was being received previously, but it not currently being received
        bool rtcmCommunicationFault() const;

        //API Function: rtkDongleFault
        //  Gets the value of the RTK Dongle Fault bit (bit 115)
        //
        //Returns:
        //  bool - true: A problem has been detected with the RTK dongle. Query directly for more detail
        bool rtkDongleFault() const;
    };

    //API Struct: GQ7ContinuousBIT_GNSS
    //  Continuous Built-In Test flags for GNSS information
    //
    //  Bits 96-127 of the original 128 bit Continuous Built-In Test flags
    struct GQ7ContinuousBIT_GNSS : Bitfield
    {
        //API Constructor: GQ7ContinuousBIT_GNSS
        GQ7ContinuousBIT_GNSS() = default;

        //API Constructor: GQ7ContinuousBIT_GNSS
        //
        //Parameters:
        //  bits - Value of bits 96-127 of the original 128 bit Continuous Built-In Test flags
        explicit GQ7ContinuousBIT_GNSS(uint32 bits);

        //API Constant: RESPONSE_OFFSET
        //  The offset of the 0 position of the value represented by this object in the overall BIT response
        //  Value: 96 bits
        static constexpr uint8_t RESPONSE_OFFSET = 96;

        //API Constants: Bitmasks
        //  GENERAL_FLAGS   - 0xFF000000 - Bitmask for general GNSS flags (bits 96-103)
        //  RECEIVERS_FLAGS - 0x00FFFF00 - Bitmask for GNSS receivers flags (bits 104-119)
        static constexpr uint32 GENERAL_FLAGS   = 0xFF000000; // Bitmask for general GNSS flags (bits 96-103)
        static constexpr uint32 RECEIVERS_FLAGS = 0x00FFFF00; // Bitmask for GNSS receivers flags (bits 104-119)

        //API Function: flags
        //  Gets the value of the GNSS flags (bits 96-127)
        //
        //Returns:
        //  uint32 - Value of the GNSS flags
        uint32 flags() const;

        //API Function: general
        //  Gets information for general GNSS flags (bits 96-103)
        //
        //Returns:
        //  <GQ7ContinuousBIT_GNSS_General> - Information for general GNSS flags
        GQ7ContinuousBIT_GNSS_General general() const;

        //API Function: receivers
        //  Gets information for GNSS receivers flags (bits 104-119)
        //
        //Returns:
        //  <GQ7ContinuousBIT_GNSS_Receivers> - Information for GNSS receivers flags
        GQ7ContinuousBIT_GNSS_Receivers receivers() const;

    private:
        //Variable: m_general
        //  <GQ7ContinuousBIT_GNSS_General> information for general GNSS flags (bits 96-103)
        GQ7ContinuousBIT_GNSS_General m_general;

        //Variable: m_receivers;
        //  <GQ7ContinuousBIT_GNSS_Receivers> information for GNSS receivers flags (bits 104-119)
        GQ7ContinuousBIT_GNSS_Receivers m_receivers;
    };

    //API Class: GQ7ContinuousBIT
    //  Continuous Built-In Test flag data
    //
    //  See the GQ7 <Built-in Test: https://s3.amazonaws.com/files.microstrain.com/GQ7+User+Manual/user_manual_content/additional_features/Built-in%20Test.htm>
    //  documentation for more information
    class GQ7ContinuousBIT : public ContinuousBIT
    {
    public:
        //API Constructor: GQ7ContinuousBIT
        GQ7ContinuousBIT() = delete;

        //API Constructor: GQ7ContinuousBIT
        //
        //Parameters:
        //  bytes - Flag values from Continuous Built-In Test
        explicit GQ7ContinuousBIT(Bytes bytes);


        /**********************
        ****  System Bits  ****
        **********************/

        //API Function: system
        //  Gets information for system flags (bits 0-31)
        //
        //Returns:
        //  <GQ7ContinuousBIT_System> - Information for system flags
        GQ7ContinuousBIT_System system() const;

        //API Function: systemClockFailure
        //  Gets the value of the System Clock Failure bit (bit 0)
        //
        //Returns:
        //  bool - true: The system clock is not operating properly
        bool systemClockFailure() const override;

        //API Function: powerFault
        //  Gets the value of the Power Fault bit (bit 1)
        //
        //Returns:
        //  bool - true: Power supply voltage is outside the recommended range, or an internal power fault exists
        bool powerFault() const override;

        //API Function: firmwareFault
        //  Gets the value of the Firmware Fault bit (bit 4)
        //
        //Returns:
        //  bool - true: System firmware has detected an unexpected or abnormal condition
        bool firmwareFault() const override;

        //API Function: timingOverload
        //  Gets the value of the Timing Overload bit (bit 5)
        //
        //Returns:
        //  bool - true: The system is unable to keep up with the processing demand
        bool timingOverload() const override;

        //API Function: bufferOverrun
        //  Gets the value of the Buffer Overrun bit (bit 6)
        //
        //Returns:
        //  bool - true: A data buffer in the system has reached its capacity
        bool bufferOverrun() const override;

        //API Function: imuIpcFault
        //  Gets the value of the IMU IPC fault flags (bits 16-19)
        //
        //Note:
        //  Bits 0-3 of this value correspond to bits 16-19
        //
        //Returns:
        //  uint8 - Value of the IMU IPC fault flags
        uint8 imuIpcFault() const;

        //API Function: imuControlLineFault
        //  Gets the value of the IMU Control Line Fault bit (bit 16)
        //
        //Returns:
        //  bool - true: The IMU control line is not behaving as expected
        bool imuControlLineFault() const;

        //API Function: imuCommandResponseFault
        //  Gets the value of the IMU Command Response Fault bit (bit 17)
        //
        //Returns:
        //  bool - true: The IMU is not responsive to commands
        bool imuCommandResponseFault() const;

        //API Function: imuSpiTransferFault
        //  Gets the value of the IMU SPI Transfer Fault bit (bit 18)
        //
        //Returns:
        //  bool - true: Misaligned/failed IMU SPI transfers
        bool imuSpiTransferFault() const;

        //API Function: imuDataFrameFault
        //  Gets the value of the IMU Data Frame Fault bit (bit 19)
        //
        //Returns:
        //  bool - true: Missing IMU data frame(s)
        bool imuDataFrameFault() const;

        //API Function: filterIpcFault
        //  Gets the value of the Filter IPC fault flags (bits 20-23)
        //
        //Note:
        //  Bits 0-3 of this value correspond to bits 20-23
        //
        //Returns:
        //  uint8 - Value of the filter IPC fault flags
        uint8 filterIpcFault() const;

        //API Function: filterControlLineFault
        //  Gets the value of the Filter Control Line Fault bit (bit 20)
        //
        //Returns:
        //  bool - true: The filter control line is not behaving as expected
        bool filterControlLineFault() const;

        //API Function: filterCommandResponseFault
        //  Gets the value of the Filter Command Response Fault bit (bit 21)
        //
        //Returns:
        //  bool - true: The filter is not responsive to commands
        bool filterCommandResponseFault() const;

        //API Function: filterSpiTransferFault
        //  Gets the value of the Filter SPI Transfer Fault bit (bit 22)
        //
        //Returns:
        //  bool - true: Misaligned/failed filter SPI transfers
        bool filterSpiTransferFault() const;

        //API Function: filterDataFrameFault
        //  Gets the value of the Filter Data Frame Fault bit (bit 23)
        //
        //Returns:
        //  bool - true: Missing filter data frame(s)
        bool filterDataFrameFault() const;

        //API Function: gnssIpcFault
        //  Gets the value of the GNSS IPC fault flags (bits 24-27)
        //
        //Note:
        //  Bits 0-3 of this value correspond to bits 24-27
        //
        //Returns:
        //  uint8 - Value of the GNSS IPC fault flags
        uint8 gnssIpcFault() const;

        //API Function: gnssControlLineFault
        //  Gets the value of the GNSS Control Line Fault bit (bit 24)
        //
        //Returns:
        //  bool - true: The GNSS control line is not behaving as expected
        bool gnssControlLineFault() const;

        //API Function: gnssCommandResponseFault
        //  Gets the value of the GNSS Command Response Fault bit (bit 25)
        //
        //Returns:
        //  bool - true: The GNSS is not responsive to commands
        bool gnssCommandResponseFault() const;

        //API Function: gnssSpiTransferFault
        //  Gets the value of the GNSS SPI Transfer Fault bit (bit 26)
        //
        //Returns:
        //  bool - true: Misaligned/failed GNSS SPI transfers
        bool gnssSpiTransferFault() const;

        //API Function: gnssDataFrameFault
        //  Gets the value of the GNSS Data Frame Fault bit (bit 27)
        //
        //Returns:
        //  bool - true: Missing GNSS data frame(s)
        bool gnssDataFrameFault() const;


        /*******************
        ****  IMU Bits  ****
        *******************/

        //API Function: imu
        //  Gets information for IMU flags (bits 32-63)
        //
        //Returns:
        //  <GQ7ContinuousBIT_IMU> - Information for IMU flags
        GQ7ContinuousBIT_IMU imu() const;

        //API Function: imuClockFault
        //  Gets the value of the IMU Clock Fault bit (bit 32)
        //
        //Returns:
        //  bool - true: IMU is not running off the system clock
        bool imuClockFault() const override;

        //API Function: imuCommunicationFault
        //  Gets the value of the IMU Communication Fault bit (bit 33)
        //
        //Returns:
        //  bool - true: No communication with IMU
        bool imuCommunicationFault() const override;

        //API Function: imuTimingOverrun
        //  Gets the value of the IMU Timing Overrun bit (bit 34)
        //
        //Returns:
        //  bool - true: IMU processes are taking longer than their allotted time
        bool imuTimingOverrun() const override;

        //API Function: imuCalibrationErrorAccel
        //  Gets the value of the IMU Calibration Error Accelerometer bit (bit 36)
        //
        //Returns:
        //  bool - true: A problem is detected with the accelerometer calibration
        bool imuCalibrationErrorAccel() const override;

        //API Function: imuCalibrationErrorGyro
        //  Gets the value of the IMU Calibration Error Gyroscope bit (bit 37)
        //
        //Returns:
        //  bool - true: A problem is detected with the gyroscope calibration
        bool imuCalibrationErrorGyro() const override;

        //API Function: imuCalibrationErrorMag
        //  Gets the value of the IMU Calibration Error Magnetometer bit (bit 38)
        //
        //Returns:
        //  bool - true: A problem is detected with the magnetometer calibration
        bool imuCalibrationErrorMag() const override;

        //API Function: accelGeneralFault
        //  Gets the value of the Accelerometer General Fault bit (bit 40)
        //
        //Returns:
        //  bool - true: Accelerometer will not initialize
        bool accelGeneralFault() const override;

        //API Function: accelOverrange
        //  Gets the value of the Accelerometer Overrange bit (bit 41)
        //
        //Returns:
        //  bool - true: One or more axes subjected to accelerations near or outside the selected range
        bool accelOverrange() const override;

        //API Function: accelSelfTest
        //  Gets the value of the Accelerometer Self Test bit (bit 42)
        //
        //Returns:
        //  bool - true: The internal self-test of the accelerometer failed
        bool accelSelfTestFail() const override;

        //API Function: gyroGeneralFault
        //  Gets the value of the Gyroscope General Fault bit (bit 44)
        //
        //Returns:
        //  bool - true: Gyroscope will not initialize
        bool gyroGeneralFault() const override;

        //API Function: gyroOverrange
        //  Gets the value of the Gyroscope Overrange bit (bit 45)
        //
        //Returns:
        //  bool - true: One or more axes subjected to rotational rates near or outside the selected range
        bool gyroOverrange() const override;

        //API Function: gyroSelfTest
        //  Gets the value of the Gyroscope Self Test bit (bit 46)
        //
        //Returns:
        //  bool - true: The internal self-test of the gyroscope failed
        bool gyroSelfTestFail() const override;

        //API Function: magGeneralFault
        //  Gets the value of the Magnetometer General Fault bit (bit 48)
        //
        //Returns:
        //  bool - true: Magnetometer will not initialize
        bool magGeneralFault() const override;

        //API Function: magOverrange
        //  Gets the value of the Magnetometer Overrange bit (bit 49)
        //
        //Returns:
        //  bool - true: One or more axes subjected to magnetic fields strengths near or outside the supported range
        bool magOverrange() const override;

        //API Function: magSelfTest
        //  Gets the value of the Magnetometer Self Test bit (bit 50)
        //
        //Returns:
        //  bool - true: The internal self-test of the magnetometer failed
        bool magSelfTestFail() const override;

        //API Function: pressureGeneralFault
        //  Gets the value of the Pressure General Fault bit (bit 52)
        //
        //Returns:
        //  bool - true: Pressure sensor won't initialize
        bool pressureGeneralFault() const override;

        //API Function: pressureOverrange
        //  Gets the value of the Pressure Overrange bit (bit 53)
        //
        //Returns:
        //  bool - true: Pressure sensor subjected to pressures above or below the supported range
        bool pressureOverrange() const override;

        //API Function: pressureSelfTest
        //  Gets the value of the Pressure Self Test bit (bit 54)
        //
        //Returns:
        //  bool - true: The internal self-test of the pressure sensor failed
        bool pressureSelfTestFail() const override;


        /**********************
        ****  Filter Bits  ****
        **********************/

        //API Function: filter
        //  Gets information for filter flags (bits 64-95)
        //
        //Returns:
        //  <GQ7ContinuousBIT_Filter> - Information for filter flags
        GQ7ContinuousBIT_Filter filter() const;

        //API Function: filterClockFault
        //  Gets the value of the Filter Clock Fault bit (bit 64)
        //
        //Returns:
        //  bool - true: The filter subsystem is not running off the system clock
        bool filterClockFault() const;

        //API Function: filterHardwareFault
        //  Gets the value of the Filter Hardware Fault bit (bit 65)
        //
        //Returns:
        //  bool - true: Filter hardware initialization error
        bool filterHardwareFault() const;

        //API Function: filterTimingOverrun
        //  Gets the value of the Filter Timing Overrun bit (bit 66)
        //
        //Returns:
        //  bool - true: Filter processes are taking longer than their allotted time
        bool filterTimingOverrun() const override;

        //API Function: filterTimingUnderrun
        //  Gets the value of the Filter Timing Underrun bit (bit 67)
        //
        //Returns:
        //  bool - true: Filter processes are being skipped
        bool filterTimingUnderrun() const override;

        //API Function: filterCommunicationError
        //  Gets the value of the Filter Communication Error flags (bits 68-71)
        //
        //Note:
        //  Bits 0-3 of this value correspond to bits 68-71
        //
        //Returns:
        //  uint8 - Value of the Filter Communication Error flags
        uint8 filterCommunicationError() const;

        //API Function: filterCommunicationErrorImuSpi
        //  Gets the value of the Filter Communication Error IMU SPI bit (bit 68)
        //
        //Returns:
        //  bool - true: No filter communication on the IMU SPI port
        bool filterCommunicationErrorImuSpi() const;

        //API Function: filterCommunicationErrorGnssSpi
        //  Gets the value of the Filter Communication Error GNSS SPI bit (bit 69)
        //
        //Returns:
        //  bool - true: No filter communication on the GNSS SPI port
        bool filterCommunicationErrorGnssSpi() const;

        //API Function: communicationErrorCommsSpi
        //  Gets the value of the Filter Communication Error COMMS SPI bit (bit 70)
        //
        //Returns:
        //  bool - true: No filter communication on the COMMS SPI port
        bool filterCommunicationErrorCommsSpi() const;

        //API Function: filterCommunicationErrorCommsUart
        //  Gets the value of the Filter Communication Error COMMS UART bit (bit 71)
        //
        //Returns:
        //  bool - true: No filter communication on the COMMS UART port
        bool filterCommunicationErrorCommsUart() const;


        /********************
        ****  GNSS Bits  ****
        ********************/

        //API Function: gnss
        //  Gets information for GNSS flags (bits 96-127)
        //
        //Returns:
        //  <GQ7ContinuousBIT_GNSS> - Information for GNSS flags
        GQ7ContinuousBIT_GNSS gnss() const;

        //API Function: gnssClockFault
        //  Gets the value of the GNSS Clock Fault bit (bit 96)
        //
        //Returns:
        //  bool - true: The GNSS subsystem is not running off the system clock
        bool gnssClockFault() const;

        //API Function: gnssHardwareFault
        //  Gets the value of the GNSS Hardware Fault bit (bit 97)
        //
        //Returns:
        //  bool - true: GNSS hardware initialization error
        bool gnssHardwareFault() const;

        //API Function: gnssCommunicationError
        //  Gets the value of the GNSS Communication Error flags (bits 98-100)
        //
        //Note:
        //  Bits 0-2 of this value correspond to bits 98-100
        //
        //Returns:
        //  uint8 - Value of the GNSS Communication Error flags
        uint8 gnssCommunicationError() const;

        //API Function: gnssCommunicationErrorCommsSerial
        //  Gets the value of the GNSS Communication Error COMMS Serial bit (bit 98)
        //
        //Returns:
        //  bool - true: No GNSS communication on the COMMS Serial port
        bool gnssCommunicationErrorCommsSerial() const;

        //API Function: gnssCommunicationErrorCommsSpi
        //  Gets the value of the GNSS Communication Error COMMS SPI bit (bit 99)
        //
        //Returns:
        //  bool - true: No GNSS communication on the COMMS SPI port
        bool gnssCommunicationErrorCommsSpi() const;

        //API Function: gnssCommunicationErrorNavSpi
        //  Gets the value of the GNSS Communication Error NAV SPI bit (bit 100)
        //
        //Returns:
        //  bool - true: No GNSS communication on the NAV SPI port
        bool gnssCommunicationErrorNavSpi() const;

        //API Function: gpsTimeFault
        //  Gets the value of the GPS Time Fault bit (bit 101)
        //
        //Returns:
        //  bool - true: System GPS time is invalid
        bool gpsTimeFault() const;

        //API Function: gnssTimingOverrun
        //  Gets the value of the GNSS Timing Overrun bit (bit 102)
        //
        //Returns:
        //  bool - true: GNSS processes are taking longer than their allotted time
        bool gnssTimingOverrun() const;

        //API Function: gnssPowerFaultReceiver1
        //  Gets the value of the GNSS Receiver 1 Power Fault bit (bit 104)
        //
        //Returns:
        //  bool - true: GNSS receiver 1 internal power fault
        bool gnssPowerFaultReceiver1() const;

        //API Function: gnssFaultReceiver1
        //  Gets the value of the GNSS Receiver 1 Fault bit (bit 105)
        //
        //Returns:
        //  bool - true: GNSS receiver 1 is inoperable
        bool gnssFaultReceiver1() const;

        //API Function: gnssShortedAntenna1
        //  Gets the value of the GNSS Antenna 1 Shorted bit (bit 106)
        //
        //Returns:
        //  bool - true: GNSS antenna 1 is shorted to ground
        bool gnssShortedAntenna1() const;

        //API Function: gnssOpenAntenna1
        //  Gets the value of the GNSS Antenna 1 Open bit (bit 107)
        //
        //Returns:
        //  bool - true: GNSS antenna 1 is open-circuit (or DC block is installed)
        bool gnssOpenAntenna1() const;

        //API Function: gnssSolutionFaultReceiver1
        //  Gets the value of the GNSS Receiver 1 Solution Fault bit (bit 108)
        //
        //Returns:
        //  bool - true: GNSS receiver 1 solution is invalid
        bool gnssSolutionFaultReceiver1() const;

        //API Function: gnssPowerFaultReceiver2
        //  Gets the value of the GNSS Receiver 2 Power Fault bit (bit 109)
        //
        //Returns:
        //  bool - true: GNSS receiver 2 internal power fault
        bool gnssPowerFaultReceiver2() const;

        //API Function: gnssFaultReceiver2
        //  Gets the value of the GNSS Receiver 2 Fault bit (bit 110)
        //
        //Returns:
        //  bool - true: GNSS receiver 2 is inoperable
        bool gnssFaultReceiver2() const;

        //API Function: gnssShortedAntenna2
        //  Gets the value of the GNSS Antenna 2 Shorted bit (bit 111)
        //
        //Returns:
        //  bool - true: GNSS antenna 2 is shorted to ground
        bool gnssShortedAntenna2() const;

        //API Function: gnssOpenAntenna2
        //  Gets the value of the GNSS Antenna 2 Open bit (bit 112)
        //
        //Returns:
        //  bool - true: GNSS antenna 2 is open-circuit (or DC block is installed)
        bool gnssOpenAntenna2() const;

        //API Function: gnssSolutionFaultReceiver2
        //  Gets the value of the GNSS Receiver 2 Solution Fault bit (bit 113)
        //
        //Returns:
        //  bool - true: GNSS receiver 2 solution is invalid
        bool gnssSolutionFaultReceiver2() const;

        //API Function: rtcmCommunicationFault
        //  Gets the value of the RTCM Communication Fault bit (bit 114)
        //
        //Returns:
        //  bool - true: RTCM data was being received previously, but it not currently being received
        bool rtcmCommunicationFault() const;

        //API Function: rtkDongleFault
        //  Gets the value of the RTK Dongle Fault bit (bit 115)
        //
        //Returns:
        //  bool - true: A problem has been detected with the RTK dongle. Query directly for more detail
        bool rtkDongleFault() const;

        //API Function: as_MipDataPoints
        //  Gets the data formatted as <MipDataPoint> objects.
        //
        //Returns:
        //  <MipDataPoints> - data in DataPoint format
        MipDataPoints as_MipDataPoints() const override;

    private:
        //Variable: m_system
        //  <GQ7ContinuousBIT_System> information for system flags (bits 0-31)
        GQ7ContinuousBIT_System m_system;

        //Variable: m_imu
        //  <GQ7ContinuousBIT_IMU> information for IMU flags (bits 32-63)
        GQ7ContinuousBIT_IMU m_imu;

        //Variable: m_filter
        //  <GQ7ContinuousBIT_Filter> information for filter flags (bits 64-95)
        GQ7ContinuousBIT_Filter m_filter;

        //Variable: m_gnss
        //  <GQ7ContinuousBIT_GNSS> information for GNSS flags (bits 96-127)
        GQ7ContinuousBIT_GNSS m_gnss;
    };
} // namespace mscl
