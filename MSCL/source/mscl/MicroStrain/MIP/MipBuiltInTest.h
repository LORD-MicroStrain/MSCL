/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/MIP/MipModels.h"
#include "mscl/MicroStrain/MIP/MipDataPoint.h"
#include "mscl/MicroStrain/Bitfield.h"

namespace mscl
{
    //API Class: ContinuousBIT
    //  Virtual base class for device-specific Built-In Test result parser classes
    class ContinuousBIT
    {
    public:
        //API Function: as_MipDataPoints
        //  Get the Built-In Test data formatted as <MipDataPoint> objects
        //
        //Returns:
        //  <MipDataPoints> - data in DataPoint format
        virtual MipDataPoints as_MipDataPoints() const = 0;

        //API Function: getMipDataPoints
        //  Static function to parse the Built-In Test result data into <MipDataPoint> objects based on the specified device model
        //
        //Parameters:
        //  model - <MipModels::NodeModel> of the device the data was output from
        //  data - <Bytes> Built-In Test result
        //
        //Returns:
        //  <MipDataPoints> - data in DataPoint format
        static MipDataPoints getMipDataPoints(MipModels::NodeModel model, Bytes data);
    };

    /************************************************
    ****                   CV7                   ****
    ****     Structures for parsing CV7 BIT      ****
    ************************************************/
    //API Struct: CV7ContinuousBIT_System_General
    //  Continuous Built-In Test flags for general system information
    //
    //  Bits 0-7 of the original 128 bit Continuous Built-In Test flags
    struct CV7ContinuousBIT_System_General : Bitfield
    {
        //API Constructor: CV7ContinuousBIT_System_General
        CV7ContinuousBIT_System_General() {}

        //API Constructor: CV7ContinuousBIT_System_General
        //
        //Parameters:
        //  bits - Bits 0-7 of the original 128 bit Continuous Built-In Test flags
        CV7ContinuousBIT_System_General(const uint8 bits) : Bitfield(static_cast<uint64>(bits)) {}

        //API Constants: Bitmasks
        //  Bitmasks for general system flags
        //
        //  SYSTEM_CLOCK_FAILURE - 0x01 - The system clock is not operating properly
        //  POWER_FAULT          - 0x02 - Power supply voltage is outside of the recommended range, or an internal power fault exists
        //  FIRMWARE_FAULT       - 0x10 - System firmware has detected an unexpected or abnormal condition
        //  TIMING_OVERLOAD      - 0x20 - The system is unable to keep up with the processing demand
        //  BUFFER_OVERRUN       - 0x40 - A data buffer in the system has reached its capacity
        static constexpr uint8 SYSTEM_CLOCK_FAILURE = 0x01; // The system clock is not operating properly
        static constexpr uint8 POWER_FAULT          = 0x02; // Power supply voltage is outside of the recommended range, or an internal power fault exists
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
        //  Gets the value of the System Clock Failure bit
        //  
        //Returns:
        //  bool - true: The system clock is not operating properly
        bool systemClockFailure() const;

        //API Function: powerFault
        //  Gets the value of the Power Fault bit
        //  
        //Returns:
        //  bool - true: Power supply voltage is outside of the recommended range, or an internal power fault exists
        bool powerFault() const;

        //API Function: firmwareFault
        //  Gets the value of the Firmware Fault bit
        //  
        //Returns:
        //  bool - true: System firmware has detected an unexpected or abnormal condition
        bool firmwareFault() const;

        //API Function: timingOverload
        //  Gets the value of the Timing Overload bit
        //  
        //Returns:
        //  bool - true: The system is unable to keep up with the processing demand
        bool timingOverload() const;

        //API Function: bufferOverrun
        //  Gets the value of the Buffer Overrun bit
        //  
        //Returns:
        //  bool - true: A data buffer in the system has reached its capacity
        bool bufferOverrun() const;
    };

    //API Struct: CV7ContinuousBIT_System_Process
    //  Continuous Built-In Test flags for system process information
    //
    //  Bits 16-23 of the original 128 bit Continuous Built-In Test flags
    struct CV7ContinuousBIT_System_Process : Bitfield
    {
        //API Constructor: CV7ContinuousBIT_System_Process
        CV7ContinuousBIT_System_Process() {}

        //API Constructor: CV7ContinuousBIT_System_Process
        //
        //Parameters:
        //  bits - Bits 16-23 of the original 128 bit Continuous Built-In Test flags
        CV7ContinuousBIT_System_Process(const uint8 bits) : Bitfield(static_cast<uint64>(bits)) {}

        //API Constants: Bitmasks
        //  Bitmasks for system process information flags
        //
        //Note:
        //  These masks are shifted 16 bits to the right from the original 128 bitmask to have a 0 index at bit 16
        //
        //  IMU_PROCESS_FAULT        - 0x01 - The IMU subsystem is unresponsive or not operating normally
        //  IMU_RATE_MISMATCH        - 0x02 - Faster/slower than expected base rate
        //  IMU_DROPPED_DATA         - 0x04 - At least 1 dropped frame / overrun
        //  IMU_STUCK                - 0x08 - No IMU data received in 1 second
        //  FILTER_PROCESS_FAULT     - 0x10 - The Filter subsystem is unresponsive or not operating normally
        //  FILTER_DROPPED_DATA      - 0x20 - Filter samples not equal to IMU samples
        //  FILTER_RATE_MISMATCH     - 0x40 - Filter major cycle rate mismatch
        //  FILTER_STUCK             - 0x80 - No filter data received in 1 second
        static constexpr uint8 IMU_PROCESS_FAULT    = 0x01; // The IMU subsystem is unresponsive or not operating normally
        static constexpr uint8 IMU_RATE_MISMATCH    = 0x02; // Faster/slower than expected base rate
        static constexpr uint8 IMU_DROPPED_DATA     = 0x04; // At least 1 dropped frame / overrun
        static constexpr uint8 IMU_STUCK            = 0x08; // No IMU data received in 1 second

        static constexpr uint8 FILTER_PROCESS_FAULT = 0x10; // The Filter subsystem is unresponsive or not operating normally
        static constexpr uint8 FILTER_DROPPED_DATA  = 0x20; // Filter samples not equal to IMU samples
        static constexpr uint8 FILTER_RATE_MISMATCH = 0x40; // Filter major cycle rate mismatch
        static constexpr uint8 FILTER_STUCK         = 0x80; // No filter data received in 1 second

        //API Function: flags
        //  Gets the value of the process system flags (bits 16-23)
        //
        //Returns:
        //  uint8 - Value of the process system flags
        uint8 flags() const;

        //API Function: imuProcessFault
        //  Gets the value of the Imu Process Fault bit
        //  
        //Returns:
        //  bool - true: The IMU subsystem is unresponsive or not operating normally
        bool imuProcessFault() const;

        //API Function: imuDataRateMismatch
        //  Gets the value of the Imu Data Rate Mismatch bit
        //  
        //Returns:
        //  bool - true: Faster/slower than expected base rate
        bool imuRateMismatch() const;

        //API Function: imuDroppedData
        //  Gets the value of the Imu Overrun Dropped Data bit
        //  
        //Returns:
        //  bool - true: At least 1 dropped frame / overrun
        bool imuDroppedData() const;

        //API Function: imuStuck
        //  Gets the value of the Imu Stuck bit
        //  
        //Returns:
        //  bool - true: No IMU data received in 1 second
        bool imuStuck() const;

        //API Function: filterProcessFault
        //  Gets the value of the Filter Process Fault bit
        //  
        //Returns:
        //  bool - true: The Filter subsystem is unresponsive or not operating normally
        bool filterProcessFault() const;

        //API Function: filterDroppedData
        //  Gets the value of the Filter Dropped Data bit
        //  
        //Returns:
        //  bool - true: Filter samples not equal to IMU samples
        bool filterDroppedData() const;

        //API Function: filterRateMismatch
        //  Gets the value of the Filter Rate Mismatch bit
        //  
        //Returns:
        //  bool - true: Filter major cycle rate mismatch
        bool filterRateMismatch() const;

        //API Function: filterStuck
        //  Gets the value of the Filter Stuck bit
        //  
        //Returns:
        //  bool - true: No filter data received in 1 second
        bool filterStuck() const;
    };

    //API Struct: CV7ContinuousBIT_System
    //  Continuous Built-In Test flags for system information
    //
    //  Bits 0-31 of the original 128 bit Continuous Built-In Test flags
    struct CV7ContinuousBIT_System : Bitfield
    {
        //API Constructor: CV7ContinuousBIT_System
        CV7ContinuousBIT_System() {}

        //API Constructor: CV7ContinuousBIT_System
        //
        //Parameters:
        //  bits - Value of bits 0-31 of the original 128 bit Continuous Built-In Test flags
        CV7ContinuousBIT_System(uint32 bits);

        //API Constant: RESPONSE_OFFSET
        //  The offset of the 0 position of the value represented by this object in the overall BIT response
        //  Value: 0 bits
        static constexpr uint8_t RESPONSE_OFFSET = 0;

        //API Constants: Bitmasks
        //  GENERAL_FLAGS - 0xFF000000 - Bitmask for general system flags (bits 0-7)
        //  PROCESS_FLAGS - 0x0000FF00 - Bitmask for system process flags (bits 16-23)
        static constexpr uint32 GENERAL_FLAGS   = 0xFF000000; // Bitmask for general system flags (bits 0-7)
        static constexpr uint32 PROCESS_FLAGS   = 0x0000FF00; // Bitmask for system process flags (bits 16-23)

        //API Function: flags
        //  Gets the value of the system flags (bits 0-31)
        //
        //Returns:
        //  uint32 - Value of the system flags
        uint32 flags() const;

        //API Function: general
        //  Gets information for general system flags (bits 0-7)
        //
        //Returns:
        //  <CV7ContinuousBIT_System_General> - Information for general system flags
        CV7ContinuousBIT_System_General general() const;

        //API Function: process
        //  Gets information for system process flags (bits 16-23)
        //
        //Returns:
        //  <CV7ContinuousBIT_System_Process> - Information for system process flags
        CV7ContinuousBIT_System_Process process() const;

    private:
        //Variable: m_general
        //  <CV7ContinuousBIT_System_General> information for general system flags (bits 0-7)
        CV7ContinuousBIT_System_General m_general;

        //Variable: m_process
        //  <CV7ContinuousBIT_System_Process> information for system process flags (bits 16-23)
        CV7ContinuousBIT_System_Process m_process;
    };

    //API Struct: CV7ContinuousBIT_IMU_General
    //  Continuous Built-In Test flags for general IMU information
    //
    //  Bits 32-39 of the original 128 bit Continuous Built-In Test flags
    struct CV7ContinuousBIT_IMU_General : Bitfield
    {
        //API Constructor: CV7ContinuousBIT_IMU_General
        CV7ContinuousBIT_IMU_General() {}

        //API Constructor: CV7ContinuousBIT_IMU_General
        //
        //Parameters:
        //  bits - Bits 32-39 of the original 128 bit Continuous Built-In Test flags
        CV7ContinuousBIT_IMU_General(const uint8 bits) : Bitfield(static_cast<uint64>(bits)) {}

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
        static constexpr uint8 CLOCK_FAULT              = 0x01; // IMU is not running off the system clock
        static constexpr uint8 COMMUNICATION_FAULT      = 0x02; // No communication with IMU
        static constexpr uint8 TIMING_OVERRUN           = 0x04; // IMU processes are taking longer than their allotted time

        static constexpr uint8 CALIBRATION_ERROR_ACCEL  = 0x10; // A problem is detected with the accelerometer calibration
        static constexpr uint8 CALIBRATION_ERROR_GYRO   = 0x20; // A problem is detected with the gyroscope calibration
        static constexpr uint8 CALIBRATION_ERROR_MAG    = 0x40; // A problem is detected with the magnetometer calibration

        //API Function: flags
        //  Gets the value of the general IMU flags (bits 32-39)
        //
        //Returns:
        //  uint8 - Value of the general IMU flags
        uint8 flags() const;

        //API Function: clockFault
        //  Gets the value of the Clock Fault bit
        //  
        //Returns:
        //  bool - true: IMU is not running off the system clock
        bool clockFault() const;

        //API Function: communicationFault
        //  Gets the value of the Communication Fault bit
        //  
        //Returns:
        //  bool - true: No communication with IMU
        bool communicationFault() const;

        //API Function: timingOverrun
        //  Gets the value of the Timing Overrun bit
        //  
        //Returns:
        //  bool - true: IMU processes are taking longer than their allotted time
        bool timingOverrun() const;

        //API Function: calibrationErrorAccel
        //  Gets the value of the Calibration Error Accelerometer bit
        //  
        //Returns:
        //  bool - true: A problem is detected with the accelerometer calibration
        bool calibrationErrorAccel() const;

        //API Function: calibrationErrorGyro
        //  Gets the value of the Calibration Error Gyroscope bit
        //  
        //Returns:
        //  bool - true: A problem is detected with the gyroscope calibration
        bool calibrationErrorGyro() const;

        //API Function: calibrationErrorMag
        //  Gets the value of the Calibration Error Magnetometer bit
        //  
        //Returns:
        //  bool - true: A problem is detected with the magnetometer calibration
        bool calibrationErrorMag() const;
    };

    //API Struct: CV7ContinuousBIT_IMU_Sensors
    //  Continuous Built-In Test flags for IMU sensors information
    //
    //  Bits 40-55 of the original 128 bit Continuous Built-In Test flags
    struct CV7ContinuousBIT_IMU_Sensors : Bitfield
    {
        //API Constructor: CV7ContinuousBIT_IMU_Sensors
        CV7ContinuousBIT_IMU_Sensors() {}

        //API Constructor: CV7ContinuousBIT_IMU_Sensors
        //
        //Parameters:
        //  bits - Bits 40-55 of the original 128 bit Continuous Built-In Test flags
        CV7ContinuousBIT_IMU_Sensors(const uint16 bits) : Bitfield(static_cast<uint64>(bits)) {}

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
        //  Gets the value of the Accelerometer General Fault bit
        //  
        //Returns:
        //  bool - true: Accelerometer will not initialize
        bool accelGeneralFault() const;

        //API Function: accelOverrange
        //  Gets the value of the Accelerometer Overrange bit
        //  
        //Returns:
        //  bool - true: One or more axes subjected to accelerations near or outside the selected range
        bool accelOverrange() const;

        //API Function: accelSelfTest
        //  Gets the value of the Accelerometer Self Test bit
        //  
        //Returns:
        //  bool - true: The internal self-test of the accelerometer failed
        bool accelSelfTestFail() const;

        //API Function: gyroGeneralFault
        //  Gets the value of the Gyroscope General Fault bit
        //  
        //Returns:
        //  bool - true: Gyroscope will not initialize
        bool gyroGeneralFault() const;

        //API Function: gyroOverrange
        //  Gets the value of the Gyroscope Overrange bit
        //  
        //Returns:
        //  bool - true: One or more axes subjected to rotational rates near or outside the selected range
        bool gyroOverrange() const;

        //API Function: gyroSelfTest
        //  Gets the value of the Gyroscope Self Test bit
        //  
        //Returns:
        //  bool - true: The internal self-test of the gyroscope failed
        bool gyroSelfTestFail() const;

        //API Function: magGeneralFault
        //  Gets the value of the Magnetometer General Fault bit
        //  
        //Returns:
        //  bool - true: Magnetometer will not initialize
        bool magGeneralFault() const;

        //API Function: magOverrange
        //  Gets the value of the Magnetometer Overrange bit
        //  
        //Returns:
        //  bool - true: One or more axes subjected to magnetic fields strengths near or outside the supported range
        bool magOverrange() const;

        //API Function: magSelfTest
        //  Gets the value of the Magnetometer Self Test bit
        //  
        //Returns:
        //  bool - true: The internal self-test of the magnetometer failed
        bool magSelfTestFail() const;

        //API Function: pressureGeneralFault
        //  Gets the value of the Pressure General Fault bit
        //  
        //Returns:
        //  bool - true: Pressure sensor won't initialize
        bool pressureGeneralFault() const;

        //API Function: pressureOverrange
        //  Gets the value of the Pressure Overrange bit
        //  
        //Returns:
        //  bool - true: Pressure sensor subjected to pressures above or below the supported range
        bool pressureOverrange() const;

        //API Function: pressureSelfTest
        //  Gets the value of the Pressure Self Test bit
        //  
        //Returns:
        //  bool - true: The internal self-test of the pressure sensor failed
        bool pressureSelfTestFail() const;
    };

    //API Struct: CV7ContinuousBIT_IMU
    //  Continuous Built-In Test flags for IMU information
    //
    //  Bits 32-63 of the original 128 bit Continuous Built-In Test flags
    struct CV7ContinuousBIT_IMU : Bitfield
    {
        //API Constructor: CV7ContinuousBIT_IMU
        CV7ContinuousBIT_IMU() {}

        //API Constructor: CV7ContinuousBIT_IMU
        //
        //Parameters:
        //  bits - Value of bits 32-63 of the original 128 bit Continuous Built-In Test flags
        CV7ContinuousBIT_IMU(uint32 bits);

        //API Constant: RESPONSE_OFFSET
        //  The offset of the 0 position of the value represented by this object in the overall BIT response
        //  Value: 32 bits
        static constexpr uint8_t RESPONSE_OFFSET = 32;

        //Constants: Bitmasks
        //  GENERAL_FLAGS           - 0xFF000000 - Bitmask for the general IMU bit flags (bits 32-39)
        //  SENSORS_FLAGS           - 0x00FFFF00 - Bitmask for the IMU sensors bit flags (40-55)
        //  FACTORY_BITS_INVALID    - 0x00000001 - Factory settings invalid. Device unusable (56)
        //
        //Note:
        //  These masks are shifted 32 bits to the right from the original 128 bitmask to have a 0 index at bit 32
        static constexpr uint32 GENERAL_FLAGS           = 0xFF000000; // Bitmask for the general IMU bit flags (bits 32-39)
        static constexpr uint32 SENSORS_FLAGS           = 0x00FFFF00; // Bitmask for the IMU sensors bit flags (40-55)
        static constexpr uint32 FACTORY_BITS_INVALID    = 0x00000001; // Factory settings invalid. Device unusable

        //API Function: flags
        //  Gets the value of the IMU flags (bits 32-63)
        //
        //Returns:
        //  uint32 - Value of the IMU flags
        uint32 flags() const;

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
        //  Gets the value of the Factory Bits Invalid bit
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
    struct CV7ContinuousBIT_Filter_General : Bitfield
    {
        //API Constructor: CV7ContinuousBIT_Filter_General
        CV7ContinuousBIT_Filter_General() {}

        //API Constructor: CV7ContinuousBIT_Filter_General
        //
        //Parameters:
        //  bits - Bits 64-71 of the original 128 bit Continuous Built-In Test flags
        CV7ContinuousBIT_Filter_General(const uint8 bits) : Bitfield(static_cast<uint64>(bits)) {}

        //API Constants: Bitmasks
        //  Bitmasks for general filter flags
        //
        //Note:
        //  These masks are shifted 64 bits to the right from the original 128 bitmask to have a 0 index at bit 64
        //
        //  FAULT           - 0x01 - Filter processes will not initialize
        //  TIMING_OVERRUN  - 0x04 - Filter processes are taking longer than their allotted time
        //  TIMING_UNDERRUN - 0x08 - Filter processes are being skipped
        static constexpr uint8 FAULT            = 0x01; // Filter processes will not initialize
        static constexpr uint8 TIMING_OVERRUN   = 0x04; // Filter processes are taking longer than their allotted time
        static constexpr uint8 TIMING_UNDERRUN  = 0x08; // Filter processes are being skipped

        //API Function: flags
        //  Gets the value of the general filter flags (bits 64-71)
        //
        //Returns:
        //  uint8 - Value of the general filter flags
        uint8 flags() const;

        //API Function: fault
        //  Gets the value of the Filter Fault bit
        //  
        //Returns:
        //  bool - true: Filter processes will not initialize
        bool fault() const;

        //API Function: timingOverrun
        //  Gets the value of the Filter Timing Overrun bit
        //  
        //Returns:
        //  bool - true: Filter processes are taking longer than their allotted time
        bool timingOverrun() const;

        //API Function: timingUnderrun
        //  Gets the value of the Filter Timing Underrun bit
        //  
        //Returns:
        //  bool - true: Filter processes are being skipped
        bool timingUnderrun() const;
    };

    //API Struct: CV7ContinuousBIT_Filter
    //  Continuous Built-In Test flags for filter information
    //
    //  Bits 64-95 of the original 128 bit Continuous Built-In Test flags
    struct CV7ContinuousBIT_Filter : Bitfield
    {
        //API Constructor: CV7ContinuousBIT_Filter
        CV7ContinuousBIT_Filter() {}

        //API Constructor: CV7ContinuousBIT_Filter
        //
        //Parameters:
        //  bits - Value of bits 64-95 of the original 128 bit Continuous Built-In Test flags
        CV7ContinuousBIT_Filter(uint32 bits);

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
        CV7ContinuousBIT() {}

        //API Constructor: CV7ContinuousBIT
        //
        //Parameters:
        //  bytes - Flag values from Continuous Built-In Test
        CV7ContinuousBIT(Bytes bytes);

        //API Function: system
        //  Gets information for system flags (bits 0-31)
        //
        //Returns:
        //  <CV7ContinuousBIT_System> - Information for system flags
        CV7ContinuousBIT_System system() const;

        //API Function: imu
        //  Gets information for IMU flags (bits 32-63)
        //
        //Returns:
        //  <CV7ContinuousBIT_IMU> - Information for IMU flags
        CV7ContinuousBIT_IMU imu() const;

        //API Function: filter
        //  Gets information for filter flags (bits 64-95)
        //
        //Returns:
        //  <CV7ContinuousBIT_Filter> - Information for filter flags
        CV7ContinuousBIT_Filter filter() const;

        //API Function: data
        //  Gets the original <Bytes> source data (not parsed)
        //
        //Returns:
        //  <Bytes> - raw source data
        const Bytes& data() const;

        //API Function: as_MipDataPoints
        //  Gets the data formatted as <MipDataPoint> objects.
        //
        //Returns:
        //  <MipDataPoints> - data in DataPoint format
        MipDataPoints as_MipDataPoints() const override;

    private:
        //Variable: m_data
        //  The original <Bytes> source data
        Bytes m_data;

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
} // namespace mscl