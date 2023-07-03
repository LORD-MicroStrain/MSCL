/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <map>
#include "mscl/Value.h"
#include "mscl/Version.h"
#include "mscl/Timestamp.h"

#include "mscl/MicroStrain/Bitfield.h"

#include "mscl/MicroStrain/Inertial/PositionVelocity.h"

namespace mscl
{

    //API Struct: MipTypes
    //    Contains enumeration/types for various MIP information
    struct MipTypes
    {
    public:
        //API Enums: DataClass
        //  The enums for all the different data classes of MIP data.
        //
        //  CLASS_AHRS_IMU      - 0x80 - The AHRS/IMU MIP data class
        //  CLASS_GNSS          - 0x81 - The GNSS MIP data class
        //  CLASS_ESTFILTER     - 0x82 - The Estimation Filter MIP data class
        //  CLASS_DISPLACEMENT  - 0x90 - The Displacement MIP data class
        //  CLASS_GNSS1         - 0x91 - The GNSS Receiver 1 MIP data class
        //  CLASS_GNSS2         - 0x92 - The GNSS Receiver 2 MIP data class
        //  CLASS_GNSS3         - 0x93 - The GNSS Receiver 3 MIP data class
        //  CLASS_RTK           - 0x93 - The RTK MIP data class
        //  CLASS_GNSS4         - 0x94 - The GNSS Receiver 4 MIP data class
        //  CLASS_GNSS5         - 0x95 - The GNSS Receiver 5 MIP data class
        //  CLASS_SYSTEM        - 0xA0 - The System MIP data class
        enum DataClass
        {
            CLASS_AHRS_IMU     = 0x80,
            CLASS_GNSS         = 0x81,
            CLASS_ESTFILTER    = 0x82,
            CLASS_DISPLACEMENT = 0x90,
            CLASS_GNSS1        = 0x91,
            CLASS_GNSS2        = 0x92,

            // GQ7 GNSS3 is RTK data set
            CLASS_GNSS3 = 0x93,
            CLASS_RTK   = 0x93,

            CLASS_GNSS4 = 0x94,
            CLASS_GNSS5 = 0x95,

            CLASS_SYSTEM = 0xA0 
        };

        //API Enums: FunctionSelector
        //    The enums for all the different types/categories of MIP commands and data.
        //
        //      USE_NEW_SETTINGS            - 0x01  set command, requiring data to set.
        //      READ_BACK_CURRENT_SETTINGS  - 0x02  retrieves current data from device.
        //      SAVE_CURRENT_SETTINGS       - 0x03  saves current data to use at startup.
        //      LOAD_STARTUP_SETTINGS       - 0x04  sets current settings to startup.
        //      RESET_TO_DEFAULT            - 0x05  resets current to factory default.
        //      USE_NEW_SETTINGS_NO_ACKNACK - 0x06  set command, requiring data to set - does not send ACK/NACK reply
        enum FunctionSelector
        {
            USE_NEW_SETTINGS            = 0x01,
            READ_BACK_CURRENT_SETTINGS  = 0x02,
            SAVE_CURRENT_SETTINGS       = 0x03,
            LOAD_STARTUP_SETTINGS       = 0x04,
            RESET_TO_DEFAULT            = 0x05,
            USE_NEW_SETTINGS_NO_ACKNACK = 0x06
        };

        //API Enums: EnableSetting
        //    The enums for enable or disable of data.
        //
        //      DISABLED    - 0x00
        //      ENABLED     - 0x01
        enum EnableSetting
        {
            DISABLED = 0,
            ENABLED  = 1
        };

        //API Enums: TimeFrame
        //    The enums to represent different time categories.
        //
        //      TIME_FRAME_WEEKS    - 0x00
        //      TIME_FRAME_SECONDS  - 0x01
        enum TimeFrame
        {
            TIME_FRAME_WEEKS   = 0,
            TIME_FRAME_SECONDS = 1
        };

        //API Enums: Command
        //    The enums for all of the different MIP commands.
        //
        //  CMD_PING                                    - 0x0101    - Ping
        //  CMD_SET_IDLE                                - 0x0102    - Set to Idle
        //  CMD_GET_DEVICE_INFO                         - 0x0103    - Get Device Information
        //  CMD_GET_DESCRIPTOR_SETS                     - 0x0104    - Get Device Descriptor Sets
        //  CMD_BUILT_IN_TEST                           - 0x0105    - Device Build-In Test
        //  CMD_RESUME                                  - 0x0106    - Resume
        //  CMD_GET_EXT_DESCRIPTOR_SETS                 - 0x0107    - Get Extended Device Descriptor Sets
        //  CMD_COMM_PORT_SPEED                         - 0x0109    - Comm Port Speed (Baud Rate)
        //  CMD_GPS_TIME_UPDATE                         - 0x0172    - GPS Time Update
        //  CMD_RESET                                   - 0x017E    - Device Reset
        //  CMD_POLL_SENSOR_DATA                        - 0x0C01    - Poll Sensor Data
        //  CMD_POLL_GNSS_DATA                          - 0x0C02    - Poll GNSS Data
        //  CMD_POLL_EF_DATA                            - 0x0C03    - Poll Estimation Filter Data
        //  CMD_GET_SENSOR_RATE_BASE                    - 0x0C06    - Get Sensor Data Rate Base
        //  CMD_GET_GNSS_RATE_BASE                      - 0x0C07    - Get GNSS Data Rate Base
        //  CMD_GET_EF_RATE_BASE                        - 0x0C0B    - Get Estimation Filter Data Rate Base
        //  CMD_SENSOR_MESSAGE_FORMAT                   - 0x0C08    - Sensor Data Message Format
        //  CMD_GNSS_MESSAGE_FORMAT                     - 0x0C09    - GNSS Message Format
        //  CMD_EF_MESSAGE_FORMAT                       - 0x0C0A    - Estimation Filter Message Format
        //  CMD_NMEA_MESSAGE_FORMAT                     - 0x0C0C    - NMEA Message Format
        //  CMD_POLL                                    - 0x0C0D    - Generic Poll Data
        //  CMD_GET_BASE_RATE                           - 0x0C0E    - Generic Get Data Base Rate
        //  CMD_MESSAGE_FORMAT                          - 0x0C0F    - Generic Message Format
        //  CMD_FACTORY_STREAMING                       - 0x0C10    - Configure Factory Streaming
        //  CMD_CONTINUOUS_DATA_STREAM                  - 0x0C11    - Enable/Disable Device Continuous Data Stream
        //  CMD_RAW_RTCM_2_3_MESSAGE                    - 0x0C20    - Raw RTCM 2.3 Message
        //  CMD_GNSS_CONSTELLATION_SETTINGS             - 0x0C21    - GNSS Constellation Settings
        //  CMD_GNSS_SBAS_SETTINGS                      - 0x0C22    - GNSS SBAS Settings
        //  CMD_GNSS_ASSIST_FIX_CONTROL                 - 0x0C23    - GNSS Assisted Fix Control
        //  CMD_GNSS_ASSIST_TIME_UPDATE                 - 0x0C24    - GNSS Assisted Time Update
        //  CMD_PPS_SOURCE                              - 0x0C28    - PPS Source
        //  CMD_EVENT_SUPPORT                           - 0x0C2A    - Event Support
        //  CMD_EVENT_CONTROL                           - 0x0C2B    - Event Control
        //  CMD_EVENT_TRIGGER_STATUS                    - 0x0C2C    - Event Trigger Status
        //  CMD_EVENT_ACTION_STATUS                     - 0x0C2D    - Event Action Status
        //  CMD_EVENT_TRIGGER_CONFIGURATION             - 0x0C2E    - Event Trigger Configuration
        //  CMD_EVENT_ACTION_CONFIGURATION              - 0x0C2F    - Event Action Configuration
        //  CMD_SAVE_STARTUP_SETTINGS                   - 0x0C30    - Device Startup Settings
        //  CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_EULER     - 0x0C31    - Sensor to Vehicle Frame Transformation Euler Angles
        //  CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_QUAT      - 0x0C32    - Sensor to Vehicle Frame Transformation Quaternion
        //  CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_DCM       - 0x0C33    - Sensor to Vehicle Frame Transformation Direction Cosine Matrix
        //  CMD_GPS_DYNAMICS_MODE                       - 0x0C34    - GPS Dynamics Mode
        //  CMD_SENSOR_SIG_COND_SETTINGS                - 0x0C35    - Sensor Signal Conditioning Settings
        //  CMD_SENSOR_TIMESTAMP                        - 0x0C36    - Sensor Timestamp
        //  CMD_ACCEL_BIAS                              - 0x0C37    - Accel Bias
        //  CMD_GYRO_BIAS                               - 0x0C38    - Gyro Bias
        //  CMD_CAP_GYRO_BIAS                           - 0x0C39    - Capture Gyro Bias
        //  CMD_MAG_HARD_IRON_OFFSET                    - 0x0C3A    - Magnetometer Hard Iron Offset
        //  CMD_MAG_SOFT_IRON_MATRIX                    - 0x0C3B    - Magnetometer Soft Iron Matrix
        //  CMD_CF_REALIGN_UP                           - 0x0C3C    - Complimentary Filter - Realign Up
        //  CMD_CF_REALIGN_NORTH                        - 0x0C3D    - Complimentary Filter - Realign North
        //  CMD_CONING_SCULLING                         - 0x0C3E    - Coning and Sculling Enable
        //  CMD_UART_BAUD_RATE                          - 0x0C40    - UART Baud Rate
        //  CMD_GPIO_CONFIGURATION                      - 0x0C41    - Configure GPIO Pins
        //  CMD_GPIO_STATE                              - 0x0C42    - Check GPIO Pin State
        //  CMD_ODOMETER_SETTINGS                       - 0x0C43    - Configure Odometer Settings
        //  CMD_LOWPASS_FILTER_SETTINGS                 - 0x0C50    - Legacy Low-Pass Filter Settings
        //  CMD_COMPLEMENTARY_FILTER_SETTINGS           - 0x0C51    - Complementary Filter Settings
        //  CMD_SENSOR_RANGE                            - 0x0C52    - Configure Sensor Range
        //  CMD_SUPPORTED_SENSOR_RANGES                 - 0x0C53    - Read Device-Supported Sensor Ranges
        //  CMD_LOWPASS_ANTIALIASING_FILTER             - 0x0C54    - Low-Pass Anti-Aliasing Filter Settings
        //  CMD_DATA_STREAM_FORMAT                      - 0x0C60    - Device Data Stream Format
        //  CMD_POWER_STATES                            - 0x0C61    - Device Power States
        //  CMD_GPS_STARTUP_SETTINGS                    - 0x0C62    - Save/Restore Advanced GPS Startup Settings
        //  CMD_DEVICE_STATUS                           - 0x0C64    - Device Status
        //  CMD_EF_RESET_FILTER                         - 0x0D01    - Estimation Filter - Reset Filter
        //  CMD_EF_INIT_ATTITUDE                        - 0x0D02    - Estimation Filter - Set Initial Attitude
        //  CMD_EF_INIT_HEADING                         - 0x0D03    - Estimation Filter - Set Initial Heading
        //  CMD_EF_INIT_ATTITUDE_FROM_AHRS              - 0x0D04    - Estimation Filter - Set Initial Attitude from AHRS
        //  CMD_EF_RUN_FILTER                           - 0x0D05    - Estimation Filter - Run Filter if configured to wait for run command
        //  CMD_EF_VEHIC_DYNAMICS_MODE                  - 0x0D10    - Estimation Filter - Vehicle Dynamics Mode
        //  CMD_EF_SENS_VEHIC_FRAME_ROTATION_EULER      - 0x0D11    - Estimation Filter - Sensor to Vehicle Frame Rotation Euler Angles
        //  CMD_EF_SENS_VEHIC_FRAME_OFFSET              - 0x0D12    - Estimation Filter - Sensor to Vehicle Frame Offset
        //  CMD_EF_ANTENNA_OFFSET                       - 0x0D13    - Estimation Filter - Antenna Offset
        //  CMD_EF_BIAS_EST_CTRL                        - 0x0D14    - Estimation Filter - Bias Estimation Control
        //  CMD_EF_GNSS_SRC_CTRL                        - 0x0D15    - Estimation Filter - GNSS Source Control
        //  CMD_EF_EXTERN_GNSS_UPDATE                   - 0x0D16    - Estimation Filter - External GNSS Update
        //  CMD_EF_EXTERN_HEADING_UPDATE                - 0x0D17    - Estimation Filter - External Heading Update
        //  CMD_EF_HEADING_UPDATE_CTRL                  - 0x0D18    - Estimation Filter - Heading Update Control
        //  CMD_EF_AUTO_INIT_CTRL                       - 0x0D19    - Estimation Filter - Auto-Initialization Control
        //  CMD_EF_ACCEL_WHT_NSE_STD_DEV                - 0x0D1A    - Estimation Filter - Accelerometer White Noise Standard Deviation
        //  CMD_EF_GYRO_WHT_NSE_STD_DEV                 - 0x0D1B    - Estimation Filter - Gyroscope White Noise Standard Deviation
        //  CMD_EF_ACCEL_BIAS_MODEL_PARAMS              - 0x0D1C    - Estimation Filter - Accelerometer Bias Model Parameters
        //  CMD_EF_GYRO_BIAS_MODEL_PARAMS               - 0x0D1D    - Estimation Filter - Gyroscope Bias Model Parameters
        //  CMD_EF_ZERO_VEL_UPDATE_CTRL                 - 0x0D1E    - Estimation Filter - Zero Velocity Update Control
        //  CMD_EF_EXT_HEADING_UPDATE_TS                - 0x0D1F    - Estimation Filter - External Heading Update with Timestamp
        //  CMD_EF_ZERO_ANG_RATE_UPDATE_CTRL            - 0x0D20    - Estimation Filter - Zero Angular Rate Update Control
        //  CMD_EF_TARE_ORIENT                          - 0x0D21    - Estimation Filter - Tare Orientation
        //  CMD_EF_CMDED_ZERO_VEL_UPDATE                - 0x0D22    - Estimation Filter - Commanded Zero Velocity Update
        //  CMD_EF_CMDED_ZERO_ANG_RATE_UPDATE           - 0x0D23    - Estimation Filter - Commanded Zero Angular Rate Update
        //  CMD_EF_SET_REF_POSITION                     - 0x0D26    - Estimation Filter - Set Reference Position
        //  CMD_EF_MAG_CAPTURE_AUTO_CAL                 - 0x0D27    - Estimation Filter - Magnetometer Capture Auto Calibration
        //  CMD_EF_GRAVITY_NOISE_STD_DEV                - 0x0D28    - Estimation Filter - Gravity Noise Standard Deviation
        //  CMD_EF_PRESS_ALT_NOISE_STD_DEV              - 0x0D29    - Estimation Filter - Pressure Altitude Noise Standard Deviation
        //  CMD_EF_GRAVITY_NOISE_MINIMUM                - 0x0D2A    - Estimation Filter - Get/Set Gravity Noise Minimum
        //  CMD_EF_HARD_IRON_OFFSET_PROCESS_NOISE       - 0x0D2B    - Estimation Filter - Hard Iron Offset Process Noise
        //  CMD_EF_SOFT_IRON_OFFSET_PROCESS_NOISE       - 0x0D2C    - Estimation Filter - Soft Iron Offset Process Noise
        //  CMD_EF_ENABLE_DISABLE_MEASUREMENTS          - 0x0D41    - Estimation Filter - Enable/Disable Measurements
        //  CMD_EF_MAG_NOISE_STD_DEV                    - 0x0D42    - Estimation Filter - Magnetometer Noise Standard Deviation
        //  CMD_EF_DECLINATION_SRC                      - 0x0D43    - Estimation Filter - Declination Source
        //  CMD_EF_GRAV_MAGNITUDE_ERR_ADAPT_MEASURE     - 0x0D44    - Estimation Filter - Gravity Magnitude Error Adaptive Measurement
        //  CMD_EF_MAG_MAGNITUDE_ERR_ADAPT_MEASURE      - 0x0D45    - Estimation Filter - Magnetometer Magnitude Error Adaptive Measurement
        //  CMD_EF_MAG_DIP_ANGLE_ERR_ADAPT_MEASURE      - 0x0D46    - Estimation Filter - Magnetometer Dip Angle Error Adaptive Measurement
        //  CMD_EF_ALTITUDE_AID_CTRL                    - 0x0D47    - Estimation Filter - Altitude Aiding Control
        //  CMD_EF_PITCH_ROLL_AID_CTRL                  - 0x0D4B    - Estimation Filter - Pitch-Roll Aiding Control
        //  CMD_EF_INCLINATION_SRC                      - 0x0D4C    - Estimation Filter - Inclination Source
        //  CMD_EF_FIELD_MAGNITUDE_SRC                  - 0x0D4D    - Estimation Filter - Magnetic Field Magnitude Source
        //  CMD_EF_SENS_VEHIC_FRAME_ROTATION_DCM        - 0x0D4E    - Estimation Filter - Sensor to Vehicle Frame Rotation Direction Cosine Matrix
        //  CMD_EF_SENS_VEHIC_FRAME_ROTATION_QUAT       - 0x0D4F    - Estimation Filter - Sensor to Vehicle Frame Rotation Quaternion
        //  CMD_EF_AIDING_MEASUREMENT_ENABLE            - 0x0D50    - Estimation Filter - Aiding Measurement Enabled
        //  CMD_EF_INITIALIZATION_CONFIG                - 0x0D52    - Estimation Filter - Initialization Configuration
        //  CMD_EF_ADAPTIVE_FILTER_OPTIONS              - 0x0D53    - Estimation Filter - Adaptive Filter Options
        //  CMD_EF_MULTI_ANTENNA_OFFSET                 - 0x0D54    - Estimation Filter - Multi Antenna Offset
        //  CMD_EF_RELATIVE_POSITION_REF                - 0x0D55    - Estimation Filter - Reference Location for Relative Position Outputs
        //  CMD_EF_LEVER_ARM_OFFSET_REF                 - 0x0D56    - Estimation Filter - Lever Arm Reference Offset
        //  CMD_EF_EXTERN_SPEED_UPDATE                  - 0x0D60    - Estimation Filter - External Speed Measurement Update (Input Speed Measurement)
        //  CMD_EF_SPEED_MEASUREMENT_OFFSET             - 0x0D61    - Estimation Filter - Speed Measurement Lever Arm Offset
        //  CMD_EF_VERTICAL_GYRO_CONSTRAINT             - 0x0D62    - Estimation Filter - Vertical Gyro Constraint Enable/Disable
        //  CMD_EF_WHEELED_VEHICLE_CONSTRAINT           - 0x0D63    - Estimation Filter - Wheeled Vehicle Constraint Enable/Disable
        //  CMD_EF_GNSS_ANTENNA_LEVER_ARM_CAL           - 0x0D64    - Estimation Filter - GNSS Antenna Lever Arm Calibration Control
        //  CMD_GNSS_RECEIVER_INFO                      - 0x0E01    - GNSS Receiver Info
        //  CMD_GNSS_SIGNAL_CONFIG                      - 0x0E02    - GNSS Signal Configuration
        //  CMD_GNSS_RTK_CONFIG                         - 0x0E10    - GNSS RTK Configuration
        //  CMD_COMMUNICATION_MODE                      - 0x7F10    - Communication Mode
        //  CMD_HARDWARE_CTRL                           - 0x7F11    - Hardware Control
        //  CMD_GET_ANALOG_DISPLACEMENT_CALS            - 0x1101    - Get Analog Output to Displacement Slope and Offset
        //  CMD_DISPLACEMENT_OUTPUT_RATE                - 0x1102    - Displacement Output Data Rate
        //  CMD_DISPLACEMENT_DEVICE_TIME                - 0x1104    - Displacement Device Time
        //  CMD_RTK_DEVICE_STATUS_FLAGS                 - 0x0F01    - Get RTK Device Status Flags
        //  CMD_RTK_ACTIVATION_CODE                     - 0x0F07    - Get RTK Activation Code
        //  CMD_AIDING_FRAME_CONFIG                     - 0x1301    - Configure Aiding Measurement Reference Frames
        //  CMD_AIDING_SENSOR_FRAME_MAP                 - 0x1302    - Map Reference Frames to Sensor Inputs
        //  CMD_AIDING_ECHO_CONTROL                     - 0x131F    - Enable/Disable Aiding Measurement Echo in Response
        //  CMD_AIDING_POS_LOCAL                        - 0x1320    - ECEF Position Input
        //  CMD_AIDING_POS_ECEF                         - 0x1321    - LLH Position Input
        //  CMD_AIDING_POS_LLH                          - 0x1322    - Local Position Input
        //  CMD_AIDING_HEIGHT_ABS                       - 0x1323    - Absolute Height Input
        //  CMD_AIDING_HEIGHT_REL                       - 0x1324    - Relative Height Input
        //  CMD_AIDING_VEL_ECEF                         - 0x1328    - ECEF Velocity Input
        //  CMD_AIDING_VEL_NED                          - 0x1329    - NED Velocity Input
        //  CMD_AIDING_VEL_ODOM                         - 0x132A    - Velocity Input (Relative to the Vehicle Frame)
        //  CMD_AIDING_WHEELSPEED                       - 0x132B    - Wheel Speed Input
        //  CMD_AIDING_HEADING_TRUE                     - 0x1331    - True Heading Input
        //  CMD_AIDING_DELTA_POSITION                   - 0x1338    - Delta Position Input
        //  CMD_AIDING_DELTA_ATTITUDE                   - 0x1339    - Delta Attitude Input
        //  CMD_AIDING_ANGULAR_RATE_LOCAL               - 0x133A    - Local Angular Rate Input
        enum Command
        {
            CMD_PING                                = 0x0101,
            CMD_SET_IDLE                            = 0x0102,
            CMD_GET_DEVICE_INFO                     = 0x0103,
            CMD_GET_DESCRIPTOR_SETS                 = 0x0104,
            CMD_BUILT_IN_TEST                       = 0x0105,
            CMD_RESUME                              = 0x0106,
            CMD_GET_EXT_DESCRIPTOR_SETS             = 0x0107,
            CMD_COMM_PORT_SPEED                     = 0x0109,
            CMD_GPS_TIME_UPDATE                     = 0x0172,
            CMD_RESET                               = 0x017E,
            CMD_POLL_SENSOR_DATA                    = 0x0C01,
            CMD_POLL_GNSS_DATA                      = 0x0C02,
            CMD_POLL_EF_DATA                        = 0x0C03,
            CMD_GET_SENSOR_RATE_BASE                = 0x0C06,
            CMD_GET_GNSS_RATE_BASE                  = 0x0C07,
            CMD_GET_EF_RATE_BASE                    = 0x0C0B,
            CMD_SENSOR_MESSAGE_FORMAT               = 0x0C08,
            CMD_GNSS_MESSAGE_FORMAT                 = 0x0C09,
            CMD_EF_MESSAGE_FORMAT                   = 0x0C0A,
            CMD_NMEA_MESSAGE_FORMAT                 = 0x0C0C,
            CMD_POLL                                = 0x0C0D,
            CMD_GET_BASE_RATE                       = 0x0C0E,
            CMD_MESSAGE_FORMAT                      = 0x0C0F,
            CMD_FACTORY_STREAMING                   = 0x0C10,
            CMD_CONTINUOUS_DATA_STREAM              = 0x0C11,
            CMD_RAW_RTCM_2_3_MESSAGE                = 0x0C20,
            CMD_GNSS_CONSTELLATION_SETTINGS         = 0x0C21,
            CMD_GNSS_SBAS_SETTINGS                  = 0x0C22,
            CMD_GNSS_ASSIST_FIX_CONTROL             = 0x0C23,
            CMD_GNSS_ASSIST_TIME_UPDATE             = 0x0C24,
            CMD_PPS_SOURCE                          = 0x0C28,
            CMD_EVENT_SUPPORT                       = 0x0C2A,
            CMD_EVENT_CONTROL                       = 0x0C2B,
            CMD_EVENT_TRIGGER_STATUS                = 0x0C2C,
            CMD_EVENT_ACTION_STATUS                 = 0x0C2D,
            CMD_EVENT_TRIGGER_CONFIGURATION         = 0x0C2E,
            CMD_EVENT_ACTION_CONFIGURATION          = 0x0C2F,
            CMD_SAVE_STARTUP_SETTINGS               = 0x0C30,
            CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_EULER = 0x0C31,
            CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_QUAT  = 0x0C32,
            CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_DCM   = 0x0C33,
            CMD_GPS_DYNAMICS_MODE                   = 0x0C34,
            CMD_SENSOR_SIG_COND_SETTINGS            = 0x0C35,
            CMD_SENSOR_TIMESTAMP                    = 0x0C36,
            CMD_ACCEL_BIAS                          = 0x0C37,
            CMD_GYRO_BIAS                           = 0x0C38,
            CMD_CAP_GYRO_BIAS                       = 0x0C39,
            CMD_MAG_HARD_IRON_OFFSET                = 0x0C3A,
            CMD_MAG_SOFT_IRON_MATRIX                = 0x0C3B,
            CMD_CF_REALIGN_UP                       = 0x0C3C,
            CMD_CF_REALIGN_NORTH                    = 0x0C3D,
            CMD_CONING_SCULLING                     = 0x0C3E,
            CMD_UART_BAUD_RATE                      = 0x0C40,
            CMD_GPIO_CONFIGURATION                  = 0x0C41,
            CMD_GPIO_STATE                          = 0x0C42,
            CMD_ODOMETER_SETTINGS                   = 0x0C43,
            CMD_LOWPASS_FILTER_SETTINGS             = 0x0C50,
            CMD_COMPLEMENTARY_FILTER_SETTINGS       = 0x0C51,
            CMD_SENSOR_RANGE                        = 0x0C52,
            CMD_SUPPORTED_SENSOR_RANGES             = 0x0C53,
            CMD_LOWPASS_ANTIALIASING_FILTER         = 0x0C54,
            CMD_DATA_STREAM_FORMAT                  = 0x0C60,
            CMD_POWER_STATES                        = 0x0C61,
            CMD_GPS_STARTUP_SETTINGS                = 0x0C62,
            CMD_DEVICE_STATUS                       = 0x0C64,
            CMD_EF_RESET_FILTER                     = 0x0D01,
            CMD_EF_INIT_ATTITUDE                    = 0x0D02,
            CMD_EF_INIT_HEADING                     = 0x0D03,
            CMD_EF_INIT_ATTITUDE_FROM_AHRS          = 0x0D04,
            CMD_EF_RUN_FILTER                       = 0x0D05,
            CMD_EF_VEHIC_DYNAMICS_MODE              = 0x0D10,
            CMD_EF_SENS_VEHIC_FRAME_ROTATION_EULER  = 0x0D11,
            CMD_EF_SENS_VEHIC_FRAME_OFFSET          = 0x0D12,
            CMD_EF_ANTENNA_OFFSET                   = 0x0D13,
            CMD_EF_BIAS_EST_CTRL                    = 0x0D14,
            CMD_EF_GNSS_SRC_CTRL                    = 0x0D15,
            CMD_EF_EXTERN_GNSS_UPDATE               = 0x0D16,
            CMD_EF_EXTERN_HEADING_UPDATE            = 0x0D17,
            CMD_EF_HEADING_UPDATE_CTRL              = 0x0D18,
            CMD_EF_AUTO_INIT_CTRL                   = 0x0D19,
            CMD_EF_ACCEL_WHT_NSE_STD_DEV            = 0x0D1A,
            CMD_EF_GYRO_WHT_NSE_STD_DEV             = 0x0D1B,
            CMD_EF_ACCEL_BIAS_MODEL_PARAMS          = 0x0D1C,
            CMD_EF_GYRO_BIAS_MODEL_PARAMS           = 0x0D1D,
            CMD_EF_ZERO_VEL_UPDATE_CTRL             = 0x0D1E,
            CMD_EF_EXT_HEADING_UPDATE_TS            = 0x0D1F,
            CMD_EF_ZERO_ANG_RATE_UPDATE_CTRL        = 0x0D20,
            CMD_EF_TARE_ORIENT                      = 0x0D21,
            CMD_EF_CMDED_ZERO_VEL_UPDATE            = 0x0D22,
            CMD_EF_CMDED_ZERO_ANG_RATE_UPDATE       = 0x0D23,
            CMD_EF_SET_REF_POSITION                 = 0x0D26,
            CMD_EF_MAG_CAPTURE_AUTO_CAL             = 0x0D27,
            CMD_EF_GRAVITY_NOISE_STD_DEV            = 0x0D28,
            CMD_EF_PRESS_ALT_NOISE_STD_DEV          = 0x0D29,
            CMD_EF_GRAVITY_NOISE_MINIMUM            = 0x0D2A,
            CMD_EF_HARD_IRON_OFFSET_PROCESS_NOISE   = 0x0D2B,
            CMD_EF_SOFT_IRON_OFFSET_PROCESS_NOISE   = 0x0D2C,
            CMD_EF_ENABLE_DISABLE_MEASUREMENTS      = 0x0D41,
            CMD_EF_MAG_NOISE_STD_DEV                = 0x0D42,
            CMD_EF_DECLINATION_SRC                  = 0x0D43,
            CMD_EF_GRAV_MAGNITUDE_ERR_ADAPT_MEASURE = 0x0D44,
            CMD_EF_MAG_MAGNITUDE_ERR_ADAPT_MEASURE  = 0x0D45,
            CMD_EF_MAG_DIP_ANGLE_ERR_ADAPT_MEASURE  = 0x0D46,
            CMD_EF_ALTITUDE_AID_CTRL                = 0x0D47,
            CMD_EF_PITCH_ROLL_AID_CTRL              = 0x0D4B,
            CMD_EF_INCLINATION_SRC                  = 0x0D4C,
            CMD_EF_FIELD_MAGNITUDE_SRC              = 0x0D4D,
            CMD_EF_SENS_VEHIC_FRAME_ROTATION_DCM    = 0x0D4E,
            CMD_EF_SENS_VEHIC_FRAME_ROTATION_QUAT   = 0x0D4F,
            CMD_EF_AIDING_MEASUREMENT_ENABLE        = 0x0D50,
            CMD_EF_INITIALIZATION_CONFIG            = 0x0D52,
            CMD_EF_ADAPTIVE_FILTER_OPTIONS          = 0x0D53,
            CMD_EF_MULTI_ANTENNA_OFFSET             = 0x0D54,
            CMD_EF_RELATIVE_POSITION_REF            = 0x0D55,
            CMD_EF_LEVER_ARM_OFFSET_REF             = 0x0D56,
            CMD_EF_EXTERN_SPEED_UPDATE              = 0x0D60,
            CMD_EF_SPEED_MEASUREMENT_OFFSET         = 0x0D61,
            CMD_EF_VERTICAL_GYRO_CONSTRAINT         = 0x0D62,
            CMD_EF_WHEELED_VEHICLE_CONSTRAINT       = 0x0D63,
            CMD_EF_GNSS_ANTENNA_LEVER_ARM_CAL       = 0x0D64,
            CMD_GNSS_RECEIVER_INFO                  = 0x0E01,
            CMD_GNSS_SIGNAL_CONFIG                  = 0x0E02,
            CMD_GNSS_RTK_CONFIG                     = 0x0E10,
            CMD_COMMUNICATION_MODE                  = 0x7F10,
            CMD_HARDWARE_CTRL                       = 0x7F11,
            CMD_GET_ANALOG_DISPLACEMENT_CALS        = 0x1101,
            CMD_DISPLACEMENT_OUTPUT_RATE            = 0x1102,
            CMD_DISPLACEMENT_DEVICE_TIME            = 0x1104,
            CMD_RTK_DEVICE_STATUS_FLAGS             = 0x0F01,
            CMD_RTK_ACTIVATION_CODE                 = 0x0F07,
            CMD_AIDING_FRAME_CONFIG                 = 0x1301,
            CMD_AIDING_SENSOR_FRAME_MAP             = 0x1302,
            CMD_AIDING_ECHO_CONTROL                 = 0x131F,
            CMD_AIDING_POS_LOCAL                    = 0x1320,
            CMD_AIDING_POS_ECEF                     = 0x1321,
            CMD_AIDING_POS_LLH                      = 0x1322,
            CMD_AIDING_HEIGHT_ABS                   = 0x1323,
            CMD_AIDING_HEIGHT_REL                   = 0x1324,
            CMD_AIDING_VEL_ECEF                     = 0x1328,
            CMD_AIDING_VEL_NED                      = 0x1329,
            CMD_AIDING_VEL_ODOM                     = 0x132A,
            CMD_AIDING_WHEELSPEED                   = 0x132B,
            CMD_AIDING_HEADING_TRUE                 = 0x1331,
            CMD_AIDING_DELTA_POSITION               = 0x1338,
            CMD_AIDING_DELTA_ATTITUDE               = 0x1339,
            CMD_AIDING_ANGULAR_RATE_LOCAL           = 0x133A,
        };

        //====================================================================================================
        //API Enums: ChannelField
        //  The enums for all of the different MIP Channel Field IDs.
        //
        //  CH_FIELD_SENSOR_RAW_ACCEL_VEC                           - 0x8001    - Raw Accelerometer Vector
        //  CH_FIELD_SENSOR_RAW_GYRO_VEC                            - 0x8002    - Raw Gyro Vector
        //  CH_FIELD_SENSOR_RAW_MAG_VEC                             - 0x8003    - Raw Magnetometer Vector
        //  CH_FIELD_SENSOR_SCALED_ACCEL_VEC                        - 0x8004    - Scaled Accelerometer Vector
        //  CH_FIELD_SENSOR_SCALED_GYRO_VEC                         - 0x8005    - Scaled Gyro Vector
        //  CH_FIELD_SENSOR_SCALED_MAG_VEC                          - 0x8006    - Scaled Magnetometer Vector
        //  CH_FIELD_SENSOR_DELTA_THETA_VEC                         - 0x8007    - Delta Theta Vector
        //  CH_FIELD_SENSOR_DELTA_VELOCITY_VEC                      - 0x8008    - Delta Velocity Vector
        //  CH_FIELD_SENSOR_ORIENTATION_MATRIX                      - 0x8009    - Orientation Matrix
        //  CH_FIELD_SENSOR_ORIENTATION_QUATERNION                  - 0x800A    - Quaternion
        //  CH_FIELD_SENSOR_ORIENTATION_UPDATE_MATRIX               - 0x800B    - Orientation Update Matrix
        //  CH_FIELD_SENSOR_EULER_ANGLES                            - 0x800C    - Euler Angles
        //  CH_FIELD_SENSOR_INTERNAL_TIMESTAMP                      - 0x800E    - Internal Timestamp
        //  CH_FIELD_SENSOR_BEACONED_TIMESTAMP                      - 0x800F    - Beaconed Timestamp
        //  CH_FIELD_SENSOR_STABILIZED_MAG_VEC                      - 0x8010    - Stabilized Mag Vector (North)
        //  CH_FIELD_SENSOR_STABILIZED_ACCEL_VEC                    - 0x8011    - Stabilized Accel Vector (Up)
        //  CH_FIELD_SENSOR_GPS_CORRELATION_TIMESTAMP               - 0x8012    - GPS Correlation Timestamp
        //  CH_FIELD_SENSOR_TEMPERATURE_STATISTICS                  - 0x8014    - Temperature Statistics
        //  CH_FIELD_SENSOR_RAW_AMBIENT_PRESSURE                    - 0x8016    - Raw Ambient Pressure
        //  CH_FIELD_SENSOR_SCALED_AMBIENT_PRESSURE                 - 0x8017    - Scaled Ambient Pressure
        //  CH_FIELD_SENSOR_OVERRANGE_STATUS                        - 0x8018    - Overrange Status
        //  CH_FIELD_SENSOR_ODOMETER_DATA                           - 0x8040    - Odometer Data
        //  CH_FIELD_SENSOR_SHARED_EVENT_SOURCE                     - 0x80D0    - Event Source
        //  CH_FIELD_SENSOR_SHARED_TICKS                            - 0x80D1    - Ticks
        //  CH_FIELD_SENSOR_SHARED_DELTA_TICKS                      - 0x80D2    - Delta Ticks
        //  CH_FIELD_SENSOR_SHARED_GPS_TIMESTAMP                    - 0x80D3    - GPS Timestamp
        //  CH_FIELD_SENSOR_SHARED_DELTA_TIMESTAMP                  - 0x80D4    - Delta GPS Timestamp
        //  CH_FIELD_SENSOR_SHARED_REFERENCE_TIMESTAMP              - 0x80D5    - Internal Reference Timestamp
        //  CH_FIELD_SENSOR_SHARED_DELTA_REFERENCE_TIME             - 0x80D6    - Delta Internal Reference Time
        //  CH_FIELD_SENSOR_SHARED_EXTERNAL_TIMESTAMP               - 0x80D7    - External Timestamp
        //  CH_FIELD_SENSOR_SHARED_DELTA_EXTERNAL_TIME              - 0x80D8    - Delta External Time
        //  CH_FIELD_GNSS_LLH_POSITION                              - 0x8103    - LLH Position
        //  CH_FIELD_GNSS_ECEF_POSITION                             - 0x8104    - ECEF Position
        //  CH_FIELD_GNSS_NED_VELOCITY                              - 0x8105    - NED Velocity
        //  CH_FIELD_GNSS_ECEF_VELOCITY                             - 0x8106    - ECEF Velocity
        //  CH_FIELD_GNSS_DOP                                       - 0x8107    - DOP Data
        //  CH_FIELD_GNSS_UTC_TIME                                  - 0x8108    - UTC Time
        //  CH_FIELD_GNSS_GPS_TIME                                  - 0x8109    - GPS Time
        //  CH_FIELD_GNSS_CLOCK_INFO                                - 0x810A    - Clock Information
        //  CH_FIELD_GNSS_FIX_INFO                                  - 0x810B    - GNSS Fix Information
        //  CH_FIELD_GNSS_SPACE_VEHICLE_INFO                        - 0x810C    - Space Vehicle Information
        //  CH_FIELD_GNSS_HARDWARE_STATUS                           - 0x810D    - Hardware Status
        //  CH_FIELD_GNSS_DGNSS_INFO                                - 0x810E    - DGNSS Information
        //  CH_FIELD_GNSS_DGNSS_CHANNEL_STATUS                      - 0x810F    - Individual DGNSS Channel Status Entry
        //  CH_FIELD_GNSS_CLOCK_INFO_2                              - 0x8110    - GNSS Clock Info 2
        //  CH_FIELD_GNSS_GPS_LEAP_SECONDS                          - 0x8111    - GNSS GPS Leap Seconds
        //  CH_FIELD_GNSS_SBAS_INFO                                 - 0x8112    - GNSS SBAS Info
        //  CH_FIELD_GNSS_SBAS_CORRECTION                           - 0x8113    - GNSS SBAS Correction
        //  CH_FIELD_GNSS_RF_ERROR_DETECTION                        - 0x8114    - GNSS RF Error Detection
        //  CH_FIELD_GNSS_SATELLITE_STATUS                          - 0x8120    - GNSS Satellite Status
        //  CH_FIELD_GNSS_RAW_OBSERVATION                           - 0x8122    - GNSS Raw Observation data
        //  CH_FIELD_GNSS_STATION_INFO                              - 0x8130    - GNSS Base Station Info
        //  CH_FIELD_GNSS_RTK_CORRECTIONS_STATUS                    - 0x8131    - GNSS RTK Corrections Status
        //  CH_FIELD_GNSS_GPS_EPHEMERIS                             - 0x8161    - GNSS GPS Ephemeris
        //  CH_FIELD_GNSS_GLONASS_EPHEMERIS                         - 0x8162    - GNSS GLONASS Ephemeris
        //  CH_FIELD_GNSS_GALILEO_EPHEMERIS                         - 0x8163    - GNSS Galileo Ephemeris
        //  CH_FIELD_GNSS_GPS_IONOSPHERIC_CORRECTION                - 0x8171    - GPS Ionospheric Correction
        //  CH_FIELD_GNSS_GALILEO_IONOSPHERIC_CORRECTION            - 0x8173    - Galileo Ionospheric Correction
        //  CH_FIELD_GNSS_SHARED_EVENT_SOURCE                       - 0x81D0    - Event Source
        //  CH_FIELD_GNSS_SHARED_TICKS                              - 0x81D1    - Ticks
        //  CH_FIELD_GNSS_SHARED_DELTA_TICKS                        - 0x81D2    - Delta Ticks
        //  CH_FIELD_GNSS_SHARED_GPS_TIMESTAMP                      - 0x81D3    - GPS Timestamp
        //  CH_FIELD_GNSS_SHARED_DELTA_TIMESTAMP                    - 0x81D4    - Delta GPS Timestamp
        //  CH_FIELD_GNSS_SHARED_REFERENCE_TIMESTAMP                - 0x81D5    - Internal Reference Timestamp
        //  CH_FIELD_GNSS_SHARED_DELTA_REFERENCE_TIME               - 0x81D6    - Delta Internal Reference Time
        //  CH_FIELD_GNSS_SHARED_EXTERNAL_TIMESTAMP                 - 0x81D7    - External Timestamp
        //  CH_FIELD_GNSS_SHARED_DELTA_EXTERNAL_TIME                - 0x81D8    - Delta External Time
        //  CH_FIELD_ESTFILTER_ESTIMATED_LLH_POS                    - 0x8201    - Estimated LLH Position
        //  CH_FIELD_ESTFILTER_ESTIMATED_NED_VELOCITY               - 0x8202    - Estimated NED Velocity
        //  CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_QUATERNION          - 0x8203    - Estimated Orientation Quaternion
        //  CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_MATRIX              - 0x8204    - Estimated Orientation Matrix
        //  CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_EULER               - 0x8205    - Estimated Orientation, Euler Angles
        //  CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS                  - 0x8206    - Estimated Gyro Bias
        //  CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS                 - 0x8207    - Estimated Accel Bias
        //  CH_FIELD_ESTFILTER_ESTIMATED_LLH_UNCERT                 - 0x8208    - Estimated LLH Position Uncertainty
        //  CH_FIELD_ESTFILTER_ESTIMATED_NED_UNCERT                 - 0x8209    - Estimated NED Velocity Uncertainty
        //  CH_FIELD_ESTFILTER_ESTIMATED_ATT_UNCERT_EULER           - 0x820A    - Estimated Attitude Uncertainty, Euler Angles
        //  CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS_UNCERT           - 0x820B    - Estimated Gyro Bias Uncertainty
        //  CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS_UNCERT          - 0x820C    - Estimated Accel Bias Uncertainty
        //  CH_FIELD_ESTFILTER_ESTIMATED_LINEAR_ACCEL               - 0x820D    - Estimated Linear Acceleration
        //  CH_FIELD_ESTFILTER_ESTIMATED_ANGULAR_RATE               - 0x820E    - Estimated Angular Rate
        //  CH_FIELD_ESTFILTER_WGS84_LOC_GRAV_MAGNITUDE             - 0x820F    - WG284 Local Gravity Magnitude
        //  CH_FIELD_ESTFILTER_FILTER_STATUS                        - 0x8210    - Filter Status
        //  CH_FIELD_ESTFILTER_GPS_TIMESTAMP                        - 0x8211    - GPS Timestamp
        //  CH_FIELD_ESTFILTER_ESTIMATED_ATT_UNCERT_QUAT            - 0x8212    - Estimated Attitude Uncertainty, Quaternion Elements
        //  CH_FIELD_ESTFILTER_ESTIMATED_GRAVITY_VECTOR             - 0x8213    - Estimated Gravity Vector
        //  CH_FIELD_ESTFILTER_HEADING_UPDATE_SOURCE                - 0x8214    - Heading Update Source
        //  CH_FIELD_ESTFILTER_MAGNETIC_MODEL_SLN                   - 0x8215    - Magnetic Model Solution
        //  CH_FIELD_ESTFILTER_ESTIMATED_GYRO_SCALE_FACTOR          - 0x8216    - Gyro Scale Factor
        //  CH_FIELD_ESTFILTER_ACCEL_SCALE_FACTOR                   - 0x8217    - Accel Scale Factor
        //  CH_FIELD_ESTFILTER_GYRO_SCALE_FACTOR_UNCERT             - 0x8218    - Gyro Scale Factor Uncertainty
        //  CH_FIELD_ESTFILTER_ACCEL_SCALE_FACTOR_UNCERT            - 0x8219    - Accel Scale Factor Uncertainty
        //  CH_FIELD_ESTFILTER_MAG_BIAS                             - 0x821A    - Mag Bias
        //  CH_FIELD_ESTFILTER_MAG_BIAS_UNCERT                      - 0x821B    - Mag Bias Uncertainty
        //  CH_FIELD_ESTFILTER_COMPENSATED_ACCEL                    - 0x821C    - Compensated Accel
        //  CH_FIELD_ESTFILTER_STD_ATMOSPHERE_MODEL                 - 0x8220    - Standard Atmosphere Model
        //  CH_FIELD_ESTFILTER_PRESSURE_ALTITUDE                    - 0x8221    - Estimated Pressure Altitude
        //  CH_FIELD_ESTFILTER_MAG_AUTO_HARD_IRON_OFFSET            - 0x8225    - Mag Auto Hard Iron Offset
        //  CH_FIELD_ESTFILTER_MAG_AUTO_SOFT_IRON_MATRIX            - 0x8226    - Mag Auto Soft Iron Matrix
        //  CH_FIELD_ESTFILTER_MAG_AUTO_HARD_IRON_OFFSET_UNCERT     - 0x8228    - Mag Auto Hard Iron Offset Uncertainty
        //  CH_FIELD_ESTFILTER_MAG_AUTO_SOFT_IRON_MATRIX_UNCERT     - 0x8229    - Mag Auto Soft Iron Matrix Uncertainty
        //  CH_FIELD_ESTFILTER_MAG_COVARIANCE_MATRIX                - 0x822A    - Magnetometer Covariance Matrix
        //  CH_FIELD_ESTFILTER_MAG_RESIDUAL_VECTOR                  - 0x822C    - Magnetometer Residual Vector
        //  CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION              - 0x8230    - GNSS Antenna Offset Correction
        //  CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION_UNCERT       - 0x8231    - GNSS Antenna Offset Correction Uncertainty
        //  CH_FIELD_ESTFILTER_GNSS_CLOCK_CORRECTION                - 0x8232    - GNSS Clock Correction
        //  CH_FIELD_ESTFILTER_GNSS_CLOCK_CORRECTION_UNCERT         - 0x8233    - GNSS Clock Correction Uncertainty
        //  CH_FIELD_ESTFILTER_GNSS_MULTI_ANTENNA_CORRECTION        - 0x8234    - GNSS Multi-Antenna Offset Correction
        //  CH_FIELD_ESTFILTER_GNSS_MULTI_ANTENNA_CORRECTION_UNCERT - 0x8235    - GNSS Multi-Antenna Offset Correction Uncertainty
        //  CH_FIELD_ESTFILTER_ECEF_POS_UNCERT                      - 0x8236    - ECEF Position Uncertainty
        //  CH_FIELD_ESTFILTER_ECEF_VEL_UNCERT                      - 0x8237    - ECEF Velocity Uncertainty
        //  CH_FIELD_ESTFILTER_ECEF_POS                             - 0x8240    - ECEF Position
        //  CH_FIELD_ESTFILTER_ECEF_VEL                             - 0x8241    - ECEF Velocity
        //  CH_FIELD_ESTFILTER_NED_RELATIVE_POS                     - 0x8242    - NED Relative Position
        //  CH_FIELD_ESTFILTER_POSITION_AIDING_STATUS               - 0x8243    - GNSS Position Aiding Status
        //  CH_FIELD_ESTFILTER_ATTITUDE_AIDING_STATUS               - 0x8244    - GNSS Attitude Aiding Status
        //  CH_FIELD_ESTFILTER_AIDING_MEASURE_SUMMARY               - 0x8246    - Filter Aiding Measurement Summary
        //  CH_FIELD_ESTFILTER_ODOMETER_SCALE_FACTOR_ERROR          - 0x8247    - Odometer Scale Factor Error
        //  CH_FIELD_ESTFILTER_ODOMETER_SCALE_FACTOR_ERROR_UNCERT   - 0X8248    - Odometer Scale Factor Error Uncertainty
        //  CH_FIELD_ESTFILTER_GNSS_DUAL_ANTENNA_STATUS             - 0x8249    - GNSS Dual Antenna Status
        //  CH_FIELD_ESTFILTER_SHARED_EVENT_SOURCE                  - 0x82D0    - Event Source
        //  CH_FIELD_ESTFILTER_SHARED_TICKS                         - 0x82D1    - Ticks
        //  CH_FIELD_ESTFILTER_SHARED_DELTA_TICKS                   - 0x82D2    - Delta Ticks
        //  CH_FIELD_ESTFILTER_SHARED_GPS_TIMESTAMP                 - 0x82D3    - GPS Timestamp
        //  CH_FIELD_ESTFILTER_SHARED_DELTA_TIMESTAMP               - 0x82D4    - Delta GPS Timestamp
        //  CH_FIELD_ESTFILTER_SHARED_REFERENCE_TIMESTAMP           - 0x82D5    - Internal Reference Timestamp
        //  CH_FIELD_ESTFILTER_SHARED_DELTA_REFERENCE_TIME          - 0x82D6    - Delta Internal Reference Time
        //  CH_FIELD_ESTFILTER_SHARED_EXTERNAL_TIMESTAMP            - 0x82D7    - External Timestamp
        //  CH_FIELD_ESTFILTER_SHARED_DELTA_EXTERNAL_TIME           - 0x82D8    - Delta External Time
        //  CH_FIELD_DISP_POSITION                                  - 0x9001    - Position
        //  CH_FIELD_DISP_RAW_POSITION                              - 0x9002    - Raw Position
        //  CH_FIELD_DISP_DISPLACEMENT_TS                           - 0x9004    - Displacement Device Timestamp
        //  CH_FIELD_GNSS_1_LLH_POSITION                            - 0x9103    - GNSS 1 LLH Position
        //  CH_FIELD_GNSS_1_ECEF_POSITION                           - 0x9104    - GNSS 1 ECEF Position
        //  CH_FIELD_GNSS_1_NED_VELOCITY                            - 0x9105    - GNSS 1 NED Velocity
        //  CH_FIELD_GNSS_1_ECEF_VELOCITY                           - 0x9106    - GNSS 1 ECEF Velocity
        //  CH_FIELD_GNSS_1_DOP                                     - 0x9107    - GNSS 1 DOP Data
        //  CH_FIELD_GNSS_1_UTC_TIME                                - 0x9108    - GNSS 1 UTC Time
        //  CH_FIELD_GNSS_1_GPS_TIME                                - 0x9109    - GNSS 1 GPS Time
        //  CH_FIELD_GNSS_1_CLOCK_INFO                              - 0x910A    - GNSS 1 Clock Information
        //  CH_FIELD_GNSS_1_FIX_INFO                                - 0x910B    - GNSS 1 Fix Information
        //  CH_FIELD_GNSS_1_SPACE_VEHICLE_INFO                      - 0x910C    - GNSS 1 Space Vehicle Information
        //  CH_FIELD_GNSS_1_HARDWARE_STATUS                         - 0x910D    - GNSS 1 Hardware Status
        //  CH_FIELD_GNSS_1_DGNSS_INFO                              - 0x910E    - GNSS 1 DGNSS Information
        //  CH_FIELD_GNSS_1_DGNSS_CHANNEL_STATUS                    - 0x910F    - GNSS 1 Individual DGNSS Channel Status Entry
        //  CH_FIELD_GNSS_1_CLOCK_INFO_2                            - 0x9110    - GNSS 1 Clock Info 2
        //  CH_FIELD_GNSS_1_GPS_LEAP_SECONDS                        - 0x9111    - GNSS 1 GPS Leap Seconds
        //  CH_FIELD_GNSS_1_SBAS_INFO                               - 0x9112    - GNSS 1 SBAS Info
        //  CH_FIELD_GNSS_1_SBAS_CORRECTION                         - 0x9113    - GNSS 1 SBAS Correction
        //  CH_FIELD_GNSS_1_RF_ERROR_DETECTION                      - 0x9114    - GNSS 1 RF Error Detection
        //  CH_FIELD_GNSS_1_SATELLITE_STATUS                        - 0x9120    - GNSS 1 Satellite Status
        //  CH_FIELD_GNSS_1_RAW_OBSERVATION                         - 0x9122    - GNSS 1 Raw Observation data
        //  CH_FIELD_GNSS_1_STATION_INFO                            - 0x9130    - GNSS 1 Base Station Info
        //  CH_FIELD_GNSS_1_RTK_CORRECTIONS_STATUS                  - 0x9131    - GNSS 1 RTK Corrections Status
        //  CH_FIELD_GNSS_1_GPS_EPHEMERIS                           - 0x9161    - GNSS 1 GPS Ephemeris
        //  CH_FIELD_GNSS_1_GLONASS_EPHEMERIS                       - 0x9162    - GNSS 1 GLONASS Ephemeris
        //  CH_FIELD_GNSS_1_GALILEO_EPHEMERIS                       - 0x9163    - GNSS 1 Galileo Ephemeris
        //  CH_FIELD_GNSS_1_GPS_IONOSPHERIC_CORRECTION              - 0x9171    - GNSS 1 GPS Ionospheric Correction
        //  CH_FIELD_GNSS_1_GALILEO_IONOSPHERIC_CORRECTION          - 0x9173    - GNSS 1 Galileo Ionospheric Correction
        //  CH_FIELD_GNSS_1_SHARED_EVENT_SOURCE                     - 0x91D0    - Event Source
        //  CH_FIELD_GNSS_1_SHARED_TICKS                            - 0x91D1    - Ticks
        //  CH_FIELD_GNSS_1_SHARED_DELTA_TICKS                      - 0x91D2    - Delta Ticks
        //  CH_FIELD_GNSS_1_SHARED_GPS_TIMESTAMP                    - 0x91D3    - GPS Timestamp
        //  CH_FIELD_GNSS_1_SHARED_DELTA_TIMESTAMP                  - 0x91D4    - Delta GPS Timestamp
        //  CH_FIELD_GNSS_1_SHARED_REFERENCE_TIMESTAMP              - 0x91D5    - Internal Reference Timestamp
        //  CH_FIELD_GNSS_1_SHARED_DELTA_REFERENCE_TIME             - 0x91D6    - Delta Internal Reference Time
        //  CH_FIELD_GNSS_1_SHARED_EXTERNAL_TIMESTAMP               - 0x91D7    - External Timestamp
        //  CH_FIELD_GNSS_1_SHARED_DELTA_EXTERNAL_TIME              - 0x91D8    - Delta External Time
        //  CH_FIELD_GNSS_2_LLH_POSITION                            - 0x9203    - GNSS 2 LLH Position
        //  CH_FIELD_GNSS_2_ECEF_POSITION                           - 0x9204    - GNSS 2 ECEF Position
        //  CH_FIELD_GNSS_2_NED_VELOCITY                            - 0x9205    - GNSS 2 NED Velocity
        //  CH_FIELD_GNSS_2_ECEF_VELOCITY                           - 0x9206    - GNSS 2 ECEF Velocity
        //  CH_FIELD_GNSS_2_DOP                                     - 0x9207    - GNSS 2 DOP Data
        //  CH_FIELD_GNSS_2_UTC_TIME                                - 0x9208    - GNSS 2 UTC Time
        //  CH_FIELD_GNSS_2_GPS_TIME                                - 0x9209    - GNSS 2 GPS Time
        //  CH_FIELD_GNSS_2_CLOCK_INFO                              - 0x920A    - GNSS 2 Clock Information
        //  CH_FIELD_GNSS_2_FIX_INFO                                - 0x920B    - GNSS 2 Fix Information
        //  CH_FIELD_GNSS_2_SPACE_VEHICLE_INFO                      - 0x920C    - GNSS 2 Space Vehicle Information
        //  CH_FIELD_GNSS_2_HARDWARE_STATUS                         - 0x920D    - GNSS 2 Hardware Status
        //  CH_FIELD_GNSS_2_DGNSS_INFO                              - 0x920E    - GNSS 2 DGNSS Information
        //  CH_FIELD_GNSS_2_DGNSS_CHANNEL_STATUS                    - 0x920F    - GNSS 2 Individual DGNSS Channel Status Entry
        //  CH_FIELD_GNSS_2_CLOCK_INFO_2                            - 0x9210    - GNSS 2 Clock Info 2
        //  CH_FIELD_GNSS_2_GPS_LEAP_SECONDS                        - 0x9211    - GNSS 2 GPS Leap Seconds
        //  CH_FIELD_GNSS_2_SBAS_INFO                               - 0x9212    - GNSS 2 SBAS Info
        //  CH_FIELD_GNSS_2_SBAS_CORRECTION                         - 0x9213    - GNSS 2 SBAS Correction
        //  CH_FIELD_GNSS_2_RF_ERROR_DETECTION                      - 0x9214    - GNSS 2 RF Error Detection
        //  CH_FIELD_GNSS_2_SATELLITE_STATUS                        - 0x9220    - GNSS 2 Satellite Status
        //  CH_FIELD_GNSS_2_RAW_OBSERVATION                         - 0x9222    - GNSS 2 Raw Observation data
        //  CH_FIELD_GNSS_2_STATION_INFO                            - 0x9230    - GNSS 2 Base Station Info
        //  CH_FIELD_GNSS_2_RTK_CORRECTIONS_STATUS                  - 0x9231    - GNSS 2 RTK Corrections Status
        //  CH_FIELD_GNSS_2_GPS_EPHEMERIS                           - 0x9261    - GNSS 2 GPS Ephemeris
        //  CH_FIELD_GNSS_2_GLONASS_EPHEMERIS                       - 0x9262    - GNSS 2 GLONASS Ephemeris
        //  CH_FIELD_GNSS_2_GALILEO_EPHEMERIS                       - 0x9263    - GNSS 2 Galileo Ephemeris
        //  CH_FIELD_GNSS_2_GPS_IONOSPHERIC_CORRECTION              - 0x9271    - GNSS 2 GPS Ionospheric Correction
        //  CH_FIELD_GNSS_2_GALILEO_IONOSPHERIC_CORRECTION          - 0x9273    - GNSS 2 Galileo Ionospheric Correction
        //  CH_FIELD_GNSS_2_SHARED_EVENT_SOURCE                     - 0x92D0    - Event Source
        //  CH_FIELD_GNSS_2_SHARED_TICKS                            - 0x92D1    - Ticks
        //  CH_FIELD_GNSS_2_SHARED_DELTA_TICKS                      - 0x92D2    - Delta Ticks
        //  CH_FIELD_GNSS_2_SHARED_GPS_TIMESTAMP                    - 0x92D3    - GPS Timestamp
        //  CH_FIELD_GNSS_2_SHARED_DELTA_TIMESTAMP                  - 0x92D4    - Delta GPS Timestamp
        //  CH_FIELD_GNSS_2_SHARED_REFERENCE_TIMESTAMP              - 0x92D5    - Internal Reference Timestamp
        //  CH_FIELD_GNSS_2_SHARED_DELTA_REFERENCE_TIME             - 0x92D6    - Delta Internal Reference Time
        //  CH_FIELD_GNSS_2_SHARED_EXTERNAL_TIMESTAMP               - 0x92D7    - External Timestamp
        //  CH_FIELD_GNSS_2_SHARED_DELTA_EXTERNAL_TIME              - 0x92D8    - Delta External Time
        //  CH_FIELD_GNSS_3_LLH_POSITION                            - 0x9303    - GNSS 3 LLH Position
        //  CH_FIELD_GNSS_3_ECEF_POSITION                           - 0x9304    - GNSS 3 ECEF Position
        //  CH_FIELD_GNSS_3_NED_VELOCITY                            - 0x9305    - GNSS 3 NED Velocity
        //  CH_FIELD_GNSS_3_ECEF_VELOCITY                           - 0x9306    - GNSS 3 ECEF Velocity
        //  CH_FIELD_GNSS_3_DOP                                     - 0x9307    - GNSS 3 DOP Data
        //  CH_FIELD_GNSS_3_UTC_TIME                                - 0x9308    - GNSS 3 UTC Time
        //  CH_FIELD_GNSS_3_GPS_TIME                                - 0x9309    - GNSS 3 GPS Time
        //  CH_FIELD_GNSS_3_CLOCK_INFO                              - 0x930A    - GNSS 3 Clock Information
        //  CH_FIELD_GNSS_3_FIX_INFO                                - 0x930B    - GNSS 3 Fix Information
        //  CH_FIELD_GNSS_3_SPACE_VEHICLE_INFO                      - 0x930C    - GNSS 3 Space Vehicle Information
        //  CH_FIELD_GNSS_3_HARDWARE_STATUS                         - 0x930D    - GNSS 3 Hardware Status
        //  CH_FIELD_GNSS_3_DGNSS_INFO                              - 0x930E    - GNSS 3 DGNSS Information
        //  CH_FIELD_GNSS_3_DGNSS_CHANNEL_STATUS                    - 0x930F    - GNSS 3 Individual DGNSS Channel Status Entry
        //  CH_FIELD_GNSS_3_CLOCK_INFO_2                            - 0x9310    - GNSS 3 Clock Info 2
        //  CH_FIELD_GNSS_3_GPS_LEAP_SECONDS                        - 0x9311    - GNSS 3 GPS Leap Seconds
        //  CH_FIELD_GNSS_3_SBAS_INFO                               - 0x9312    - GNSS 3 SBAS Info
        //  CH_FIELD_GNSS_3_SBAS_CORRECTION                         - 0x9313    - GNSS 3 SBAS Correction
        //  CH_FIELD_GNSS_3_RF_ERROR_DETECTION                      - 0x9314    - GNSS 3 RF Error Detection
        //  CH_FIELD_GNSS_3_SATELLITE_STATUS                        - 0x9320    - GNSS 3 Satellite Status
        //  CH_FIELD_GNSS_3_RAW_OBSERVATION                         - 0x9322    - GNSS 3 Raw Observation data
        //  CH_FIELD_GNSS_3_STATION_INFO                            - 0x9330    - GNSS 3 Base Station Info
        //  CH_FIELD_GNSS_3_RTK_CORRECTIONS_STATUS                  - 0x9331    - GNSS 3 RTK Corrections Status
        //  CH_FIELD_GNSS_3_GPS_EPHEMERIS                           - 0x9361    - GNSS 3 GPS Ephemeris
        //  CH_FIELD_GNSS_3_GLONASS_EPHEMERIS                       - 0x9362    - GNSS 3 GLONASS Ephemeris
        //  CH_FIELD_GNSS_3_GALILEO_EPHEMERIS                       - 0x9363    - GNSS 3 Galileo Ephemeris
        //  CH_FIELD_GNSS_3_GPS_IONOSPHERIC_CORRECTION              - 0x9371    - GNSS 3 GPS Ionospheric Correction
        //  CH_FIELD_GNSS_3_GALILEO_IONOSPHERIC_CORRECTION          - 0x9373    - GNSS 3 Galileo Ionospheric Correction
        //  CH_FIELD_GNSS_3_SHARED_EVENT_SOURCE                     - 0x93D0    - Event Source
        //  CH_FIELD_GNSS_3_SHARED_TICKS                            - 0x93D1    - Ticks
        //  CH_FIELD_GNSS_3_SHARED_DELTA_TICKS                      - 0x93D2    - Delta Ticks
        //  CH_FIELD_GNSS_3_SHARED_GPS_TIMESTAMP                    - 0x93D3    - GPS Timestamp
        //  CH_FIELD_GNSS_3_SHARED_DELTA_TIMESTAMP                  - 0x93D4    - Delta GPS Timestamp
        //  CH_FIELD_GNSS_3_SHARED_REFERENCE_TIMESTAMP              - 0x93D5    - Internal Reference Timestamp
        //  CH_FIELD_GNSS_3_SHARED_DELTA_REFERENCE_TIME             - 0x93D6    - Delta Internal Reference Time
        //  CH_FIELD_GNSS_3_SHARED_EXTERNAL_TIMESTAMP               - 0x93D7    - External Timestamp
        //  CH_FIELD_GNSS_3_SHARED_DELTA_EXTERNAL_TIME              - 0x93D8    - Delta External Time
        //  CH_FIELD_GNSS_4_LLH_POSITION                            - 0x9403    - GNSS 4 LLH Position
        //  CH_FIELD_GNSS_4_ECEF_POSITION                           - 0x9404    - GNSS 4 ECEF Position
        //  CH_FIELD_GNSS_4_NED_VELOCITY                            - 0x9405    - GNSS 4 NED Velocity
        //  CH_FIELD_GNSS_4_ECEF_VELOCITY                           - 0x9406    - GNSS 4 ECEF Velocity
        //  CH_FIELD_GNSS_4_DOP                                     - 0x9407    - GNSS 4 DOP Data
        //  CH_FIELD_GNSS_4_UTC_TIME                                - 0x9408    - GNSS 4 UTC Time
        //  CH_FIELD_GNSS_4_GPS_TIME                                - 0x9409    - GNSS 4 GPS Time
        //  CH_FIELD_GNSS_4_CLOCK_INFO                              - 0x940A    - GNSS 4 Clock Information
        //  CH_FIELD_GNSS_4_FIX_INFO                                - 0x940B    - GNSS 4 Fix Information
        //  CH_FIELD_GNSS_4_SPACE_VEHICLE_INFO                      - 0x940C    - GNSS 4 Space Vehicle Information
        //  CH_FIELD_GNSS_4_HARDWARE_STATUS                         - 0x940D    - GNSS 4 Hardware Status
        //  CH_FIELD_GNSS_4_DGNSS_INFO                              - 0x940E    - GNSS 4 DGNSS Information
        //  CH_FIELD_GNSS_4_DGNSS_CHANNEL_STATUS                    - 0x940F    - GNSS 4 Individual DGNSS Channel Status Entry
        //  CH_FIELD_GNSS_4_CLOCK_INFO_2                            - 0x9410    - GNSS 4 Clock Info 2
        //  CH_FIELD_GNSS_4_GPS_LEAP_SECONDS                        - 0x9411    - GNSS 4 GPS Leap Seconds
        //  CH_FIELD_GNSS_4_SBAS_INFO                               - 0x9412    - GNSS 4 SBAS Info
        //  CH_FIELD_GNSS_4_SBAS_CORRECTION                         - 0x9413    - GNSS 4 SBAS Correction
        //  CH_FIELD_GNSS_4_RF_ERROR_DETECTION                      - 0x9414    - GNSS 4 RF Error Detection
        //  CH_FIELD_GNSS_4_SATELLITE_STATUS                        - 0x9420    - GNSS 4 Satellite Status
        //  CH_FIELD_GNSS_4_RAW_OBSERVATION                         - 0x9422    - GNSS 4 Raw Observation data
        //  CH_FIELD_GNSS_4_STATION_INFO                            - 0x9430    - GNSS 4 Base Station Info
        //  CH_FIELD_GNSS_4_RTK_CORRECTIONS_STATUS                  - 0x9431    - GNSS 4 RTK Corrections Status
        //  CH_FIELD_GNSS_4_GPS_EPHEMERIS                           - 0x9461    - GNSS 4 GPS Ephemeris
        //  CH_FIELD_GNSS_4_GLONASS_EPHEMERIS                       - 0x9462    - GNSS 4 GLONASS Ephemeris
        //  CH_FIELD_GNSS_4_GALILEO_EPHEMERIS                       - 0x9463    - GNSS 4 Galileo Ephemeris
        //  CH_FIELD_GNSS_4_GPS_IONOSPHERIC_CORRECTION              - 0x9471    - GNSS 4 GPS Ionospheric Correction
        //  CH_FIELD_GNSS_4_GALILEO_IONOSPHERIC_CORRECTION          - 0x9473    - GNSS 4 Galileo Ionospheric Correction
        //  CH_FIELD_GNSS_4_SHARED_EVENT_SOURCE                     - 0x94D0    - Event Source
        //  CH_FIELD_GNSS_4_SHARED_TICKS                            - 0x94D1    - Ticks
        //  CH_FIELD_GNSS_4_SHARED_DELTA_TICKS                      - 0x94D2    - Delta Ticks
        //  CH_FIELD_GNSS_4_SHARED_GPS_TIMESTAMP                    - 0x94D3    - GPS Timestamp
        //  CH_FIELD_GNSS_4_SHARED_DELTA_TIMESTAMP                  - 0x94D4    - Delta GPS Timestamp
        //  CH_FIELD_GNSS_4_SHARED_REFERENCE_TIMESTAMP              - 0x94D5    - Internal Reference Timestamp
        //  CH_FIELD_GNSS_4_SHARED_DELTA_REFERENCE_TIME             - 0x94D6    - Delta Internal Reference Time
        //  CH_FIELD_GNSS_4_SHARED_EXTERNAL_TIMESTAMP               - 0x94D7    - External Timestamp
        //  CH_FIELD_GNSS_4_SHARED_DELTA_EXTERNAL_TIME              - 0x94D8    - Delta External Time
        //  CH_FIELD_GNSS_5_LLH_POSITION                            - 0x9503    - GNSS 5 LLH Position
        //  CH_FIELD_GNSS_5_ECEF_POSITION                           - 0x9504    - GNSS 5 ECEF Position
        //  CH_FIELD_GNSS_5_NED_VELOCITY                            - 0x9505    - GNSS 5 NED Velocity
        //  CH_FIELD_GNSS_5_ECEF_VELOCITY                           - 0x9506    - GNSS 5 ECEF Velocity
        //  CH_FIELD_GNSS_5_DOP                                     - 0x9507    - GNSS 5 DOP Data
        //  CH_FIELD_GNSS_5_UTC_TIME                                - 0x9508    - GNSS 5 UTC Time
        //  CH_FIELD_GNSS_5_GPS_TIME                                - 0x9509    - GNSS 5 GPS Time
        //  CH_FIELD_GNSS_5_CLOCK_INFO                              - 0x950A    - GNSS 5 Clock Information
        //  CH_FIELD_GNSS_5_FIX_INFO                                - 0x950B    - GNSS 5 Fix Information
        //  CH_FIELD_GNSS_5_SPACE_VEHICLE_INFO                      - 0x950C    - GNSS 5 Space Vehicle Information
        //  CH_FIELD_GNSS_5_HARDWARE_STATUS                         - 0x950D    - GNSS 5 Hardware Status
        //  CH_FIELD_GNSS_5_DGNSS_INFO                              - 0x950E    - GNSS 5 DGNSS Information
        //  CH_FIELD_GNSS_5_DGNSS_CHANNEL_STATUS                    - 0x950F    - GNSS 5 Individual DGNSS Channel Status Entry
        //  CH_FIELD_GNSS_5_CLOCK_INFO_2                            - 0x9510    - GNSS 5 Clock Info 2
        //  CH_FIELD_GNSS_5_GPS_LEAP_SECONDS                        - 0x9511    - GNSS 5 GPS Leap Seconds
        //  CH_FIELD_GNSS_5_SBAS_INFO                               - 0x9512    - GNSS 5 SBAS Info
        //  CH_FIELD_GNSS_5_SBAS_CORRECTION                         - 0x9513    - GNSS 5 SBAS Correction
        //  CH_FIELD_GNSS_5_RF_ERROR_DETECTION                      - 0x9514    - GNSS 5 RF Error Detection
        //  CH_FIELD_GNSS_5_SATELLITE_STATUS                        - 0x9520    - GNSS 5 Satellite Status
        //  CH_FIELD_GNSS_5_RAW_OBSERVATION                         - 0x9522    - GNSS 5 Raw Observation data
        //  CH_FIELD_GNSS_5_STATION_INFO                            - 0x9530    - GNSS 5 Base Station Info
        //  CH_FIELD_GNSS_5_RTK_CORRECTIONS_STATUS                  - 0x9531    - GNSS 5 RTK Corrections Status
        //  CH_FIELD_GNSS_5_GPS_EPHEMERIS                           - 0x9561    - GNSS 5 GPS Ephemeris
        //  CH_FIELD_GNSS_5_GLONASS_EPHEMERIS                       - 0x9562    - GNSS 5 GLONASS Ephemeris
        //  CH_FIELD_GNSS_5_GALILEO_EPHEMERIS                       - 0x9563    - GNSS 5 Galileo Ephemeris
        //  CH_FIELD_GNSS_5_GPS_IONOSPHERIC_CORRECTION              - 0x9571    - GNSS 5 GPS Ionospheric Correction
        //  CH_FIELD_GNSS_5_GALILEO_IONOSPHERIC_CORRECTION          - 0x9573    - GNSS 5 Galileo Ionospheric Correction
        //  CH_FIELD_GNSS_5_SHARED_EVENT_SOURCE                     - 0x95D0    - Event Source
        //  CH_FIELD_GNSS_5_SHARED_TICKS                            - 0x95D1    - Ticks
        //  CH_FIELD_GNSS_5_SHARED_DELTA_TICKS                      - 0x95D2    - Delta Ticks
        //  CH_FIELD_GNSS_5_SHARED_GPS_TIMESTAMP                    - 0x95D3    - GPS Timestamp
        //  CH_FIELD_GNSS_5_SHARED_DELTA_TIMESTAMP                  - 0x95D4    - Delta GPS Timestamp
        //  CH_FIELD_GNSS_5_SHARED_REFERENCE_TIMESTAMP              - 0x95D5    - Internal Reference Timestamp
        //  CH_FIELD_GNSS_5_SHARED_DELTA_REFERENCE_TIME             - 0x95D6    - Delta Internal Reference Time
        //  CH_FIELD_GNSS_5_SHARED_EXTERNAL_TIMESTAMP               - 0x95D7    - External Timestamp
        //  CH_FIELD_GNSS_5_SHARED_DELTA_EXTERNAL_TIME              - 0x95D8    - Delta External Time
        //  CH_FIELD_SYSTEM_BUILT_IN_TEST                           - 0xA001    - Built-In Test (BIT)
        //  CH_FIELD_SYSTEM_TIME_SYNC_STATUS                        - 0xA002    - Time Sync Status
        //  CH_FIELD_SYSTEM_GPIO_STATE                              - 0xA003    - GPIO State
        //  CH_FIELD_SYSTEM_SHARED_EVENT_SOURCE                     - 0xA0D0    - Event Source
        //  CH_FIELD_SYSTEM_SHARED_TICKS                            - 0xA0D1    - Ticks
        //  CH_FIELD_SYSTEM_SHARED_DELTA_TICKS                      - 0xA0D2    - Delta Ticks
        //  CH_FIELD_SYSTEM_SHARED_GPS_TIMESTAMP                    - 0xA0D3    - GPS Timestamp
        //  CH_FIELD_SYSTEM_SHARED_DELTA_TIMESTAMP                  - 0xA0D4    - Delta GPS Timestamp
        //  CH_FIELD_SYSTEM_SHARED_REFERENCE_TIMESTAMP              - 0xA0D5    - Internal Reference Timestamp
        //  CH_FIELD_SYSTEM_SHARED_DELTA_REFERENCE_TIME             - 0xA0D6    - Delta Internal Reference Time
        //  CH_FIELD_SYSTEM_SHARED_EXTERNAL_TIMESTAMP               - 0xA0D7    - External Timestamp
        //  CH_FIELD_SYSTEM_SHARED_DELTA_EXTERNAL_TIME              - 0xA0D8    - Delta External Time
        //====================================================================================================
        enum ChannelField
        {
            CH_FIELD_SENSOR_RAW_ACCEL_VEC                           = 0x8001,
            CH_FIELD_SENSOR_RAW_GYRO_VEC                            = 0x8002,
            CH_FIELD_SENSOR_RAW_MAG_VEC                             = 0x8003,
            CH_FIELD_SENSOR_SCALED_ACCEL_VEC                        = 0x8004,
            CH_FIELD_SENSOR_SCALED_GYRO_VEC                         = 0x8005,
            CH_FIELD_SENSOR_SCALED_MAG_VEC                          = 0x8006,
            CH_FIELD_SENSOR_DELTA_THETA_VEC                         = 0x8007,
            CH_FIELD_SENSOR_DELTA_VELOCITY_VEC                      = 0x8008,
            CH_FIELD_SENSOR_ORIENTATION_MATRIX                      = 0x8009,
            CH_FIELD_SENSOR_ORIENTATION_QUATERNION                  = 0x800A,
            CH_FIELD_SENSOR_ORIENTATION_UPDATE_MATRIX               = 0x800B,
            CH_FIELD_SENSOR_EULER_ANGLES                            = 0x800C,
            CH_FIELD_SENSOR_INTERNAL_TIMESTAMP                      = 0x800E,
            CH_FIELD_SENSOR_BEACONED_TIMESTAMP                      = 0x800F,
            CH_FIELD_SENSOR_STABILIZED_MAG_VEC                      = 0x8010,
            CH_FIELD_SENSOR_STABILIZED_ACCEL_VEC                    = 0x8011,
            CH_FIELD_SENSOR_GPS_CORRELATION_TIMESTAMP               = 0x8012,
            CH_FIELD_SENSOR_TEMPERATURE_STATISTICS                  = 0x8014,
            CH_FIELD_SENSOR_RAW_AMBIENT_PRESSURE                    = 0x8016,
            CH_FIELD_SENSOR_SCALED_AMBIENT_PRESSURE                 = 0x8017,
            CH_FIELD_SENSOR_OVERRANGE_STATUS                        = 0x8018,
            CH_FIELD_SENSOR_ODOMETER_DATA                           = 0x8040,
            CH_FIELD_SENSOR_SHARED_EVENT_SOURCE                     = 0x80D0,
            CH_FIELD_SENSOR_SHARED_TICKS                            = 0x80D1,
            CH_FIELD_SENSOR_SHARED_DELTA_TICKS                      = 0x80D2,
            CH_FIELD_SENSOR_SHARED_GPS_TIMESTAMP                    = 0x80D3,
            CH_FIELD_SENSOR_SHARED_DELTA_TIMESTAMP                  = 0x80D4,
            CH_FIELD_SENSOR_SHARED_REFERENCE_TIMESTAMP              = 0x80D5,
            CH_FIELD_SENSOR_SHARED_DELTA_REFERENCE_TIME             = 0x80D6,
            CH_FIELD_SENSOR_SHARED_EXTERNAL_TIMESTAMP               = 0x80D7,
            CH_FIELD_SENSOR_SHARED_DELTA_EXTERNAL_TIME              = 0x80D8,
            CH_FIELD_GNSS_LLH_POSITION                              = 0x8103,
            CH_FIELD_GNSS_ECEF_POSITION                             = 0x8104,
            CH_FIELD_GNSS_NED_VELOCITY                              = 0x8105,
            CH_FIELD_GNSS_ECEF_VELOCITY                             = 0x8106,
            CH_FIELD_GNSS_DOP                                       = 0x8107,
            CH_FIELD_GNSS_UTC_TIME                                  = 0x8108,
            CH_FIELD_GNSS_GPS_TIME                                  = 0x8109,
            CH_FIELD_GNSS_CLOCK_INFO                                = 0x810A,
            CH_FIELD_GNSS_FIX_INFO                                  = 0x810B,
            CH_FIELD_GNSS_SPACE_VEHICLE_INFO                        = 0x810C,
            CH_FIELD_GNSS_HARDWARE_STATUS                           = 0x810D,
            CH_FIELD_GNSS_DGNSS_INFO                                = 0x810E,
            CH_FIELD_GNSS_DGNSS_CHANNEL_STATUS                      = 0x810F,
            CH_FIELD_GNSS_CLOCK_INFO_2                              = 0x8110,
            CH_FIELD_GNSS_GPS_LEAP_SECONDS                          = 0x8111,
            CH_FIELD_GNSS_SBAS_INFO                                 = 0x8112,
            CH_FIELD_GNSS_SBAS_CORRECTION                           = 0x8113,
            CH_FIELD_GNSS_RF_ERROR_DETECTION                        = 0x8114,
            CH_FIELD_GNSS_SATELLITE_STATUS                          = 0x8120,
            CH_FIELD_GNSS_RAW_OBSERVATION                           = 0x8122,
            CH_FIELD_GNSS_STATION_INFO                              = 0x8130,
            CH_FIELD_GNSS_RTK_CORRECTIONS_STATUS                    = 0x8131,
            CH_FIELD_GNSS_GPS_EPHEMERIS                             = 0x8161,
            CH_FIELD_GNSS_GLONASS_EPHEMERIS                         = 0x8162,
            CH_FIELD_GNSS_GALILEO_EPHEMERIS                         = 0x8163,
            CH_FIELD_GNSS_GPS_IONOSPHERIC_CORRECTION                = 0x8171,
            CH_FIELD_GNSS_GALILEO_IONOSPHERIC_CORRECTION            = 0x8173,
            CH_FIELD_GNSS_SHARED_EVENT_SOURCE                       = 0x81D0,
            CH_FIELD_GNSS_SHARED_TICKS                              = 0x81D1,
            CH_FIELD_GNSS_SHARED_DELTA_TICKS                        = 0x81D2,
            CH_FIELD_GNSS_SHARED_GPS_TIMESTAMP                      = 0x81D3,
            CH_FIELD_GNSS_SHARED_DELTA_TIMESTAMP                    = 0x81D4,
            CH_FIELD_GNSS_SHARED_REFERENCE_TIMESTAMP                = 0x81D5,
            CH_FIELD_GNSS_SHARED_DELTA_REFERENCE_TIME               = 0x81D6,
            CH_FIELD_GNSS_SHARED_EXTERNAL_TIMESTAMP                 = 0x81D7,
            CH_FIELD_GNSS_SHARED_DELTA_EXTERNAL_TIME                = 0x81D8,
            CH_FIELD_ESTFILTER_ESTIMATED_LLH_POS                    = 0x8201,    //TODO: rename? (no estimated?, look at gx4?)
            CH_FIELD_ESTFILTER_ESTIMATED_NED_VELOCITY               = 0x8202,
            CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_QUATERNION          = 0x8203,
            CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_MATRIX              = 0x8204,
            CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_EULER               = 0x8205,
            CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS                  = 0x8206,
            CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS                 = 0x8207,
            CH_FIELD_ESTFILTER_ESTIMATED_LLH_UNCERT                 = 0x8208,
            CH_FIELD_ESTFILTER_ESTIMATED_NED_UNCERT                 = 0x8209,
            CH_FIELD_ESTFILTER_ESTIMATED_ATT_UNCERT_EULER           = 0x820A,
            CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS_UNCERT           = 0x820B,
            CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS_UNCERT          = 0x820C,
            CH_FIELD_ESTFILTER_ESTIMATED_LINEAR_ACCEL               = 0x820D,
            CH_FIELD_ESTFILTER_ESTIMATED_ANGULAR_RATE               = 0x820E,
            CH_FIELD_ESTFILTER_WGS84_LOC_GRAV_MAGNITUDE             = 0x820F,
            CH_FIELD_ESTFILTER_FILTER_STATUS                        = 0x8210,
            CH_FIELD_ESTFILTER_GPS_TIMESTAMP                        = 0x8211,
            CH_FIELD_ESTFILTER_ESTIMATED_ATT_UNCERT_QUAT            = 0x8212,
            CH_FIELD_ESTFILTER_ESTIMATED_GRAVITY_VECTOR             = 0x8213,
            CH_FIELD_ESTFILTER_HEADING_UPDATE_SOURCE                = 0x8214,
            CH_FIELD_ESTFILTER_MAGNETIC_MODEL_SLN                   = 0x8215,
            CH_FIELD_ESTFILTER_ESTIMATED_GYRO_SCALE_FACTOR          = 0x8216,
            CH_FIELD_ESTFILTER_ACCEL_SCALE_FACTOR                   = 0x8217,
            CH_FIELD_ESTFILTER_GYRO_SCALE_FACTOR_UNCERT             = 0x8218,
            CH_FIELD_ESTFILTER_ACCEL_SCALE_FACTOR_UNCERT            = 0x8219,
            CH_FIELD_ESTFILTER_MAG_BIAS                             = 0x821A,
            CH_FIELD_ESTFILTER_MAG_BIAS_UNCERT                      = 0x821B,
            CH_FIELD_ESTFILTER_COMPENSATED_ACCEL                    = 0x821C,
            CH_FIELD_ESTFILTER_STD_ATMOSPHERE_MODEL                 = 0x8220,
            CH_FIELD_ESTFILTER_PRESSURE_ALTITUDE                    = 0x8221,
            CH_FIELD_ESTFILTER_MAG_AUTO_HARD_IRON_OFFSET            = 0x8225,
            CH_FIELD_ESTFILTER_MAG_AUTO_SOFT_IRON_MATRIX            = 0x8226,
            CH_FIELD_ESTFILTER_MAG_AUTO_HARD_IRON_OFFSET_UNCERT     = 0x8228,
            CH_FIELD_ESTFILTER_MAG_AUTO_SOFT_IRON_MATRIX_UNCERT     = 0x8229,
            CH_FIELD_ESTFILTER_MAG_COVARIANCE_MATRIX                = 0x822A,
            CH_FIELD_ESTFILTER_MAG_RESIDUAL_VECTOR                  = 0x822C,
            CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION              = 0x8230,
            CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION_UNCERT       = 0x8231,
            CH_FIELD_ESTFILTER_GNSS_CLOCK_CORRECTION                = 0x8232,
            CH_FIELD_ESTFILTER_GNSS_CLOCK_CORRECTION_UNCERT         = 0x8233,
            CH_FIELD_ESTFILTER_GNSS_MULTI_ANTENNA_CORRECTION        = 0x8234,
            CH_FIELD_ESTFILTER_GNSS_MULTI_ANTENNA_CORRECTION_UNCERT = 0x8235,
            CH_FIELD_ESTFILTER_ECEF_POS_UNCERT                      = 0x8236,
            CH_FIELD_ESTFILTER_ECEF_VEL_UNCERT                      = 0x8237,
            CH_FIELD_ESTFILTER_ECEF_POS                             = 0x8240,
            CH_FIELD_ESTFILTER_ECEF_VEL                             = 0x8241,
            CH_FIELD_ESTFILTER_NED_RELATIVE_POS                     = 0x8242,
            CH_FIELD_ESTFILTER_POSITION_AIDING_STATUS               = 0x8243,
            CH_FIELD_ESTFILTER_ATTITUDE_AIDING_STATUS               = 0x8244,
            CH_FIELD_ESTFILTER_AIDING_MEASURE_SUMMARY               = 0x8246,
            CH_FIELD_ESTFILTER_ODOMETER_SCALE_FACTOR_ERROR          = 0x8247,
            CH_FIELD_ESTFILTER_ODOMETER_SCALE_FACTOR_ERROR_UNCERT   = 0X8248,
            CH_FIELD_ESTFILTER_GNSS_DUAL_ANTENNA_STATUS             = 0x8249,
            CH_FIELD_ESTFILTER_SHARED_EVENT_SOURCE                  = 0x82D0,
            CH_FIELD_ESTFILTER_SHARED_TICKS                         = 0x82D1,
            CH_FIELD_ESTFILTER_SHARED_DELTA_TICKS                   = 0x82D2,
            CH_FIELD_ESTFILTER_SHARED_GPS_TIMESTAMP                 = 0x82D3,
            CH_FIELD_ESTFILTER_SHARED_DELTA_TIMESTAMP               = 0x82D4,
            CH_FIELD_ESTFILTER_SHARED_REFERENCE_TIMESTAMP           = 0x82D5,
            CH_FIELD_ESTFILTER_SHARED_DELTA_REFERENCE_TIME          = 0x82D6,
            CH_FIELD_ESTFILTER_SHARED_EXTERNAL_TIMESTAMP            = 0x82D7,
            CH_FIELD_ESTFILTER_SHARED_DELTA_EXTERNAL_TIME           = 0x82D8,
            CH_FIELD_DISP_DISPLACEMENT_RAW                          = 0x9001,
            CH_FIELD_DISP_DISPLACEMENT_MM                           = 0x9002,
            CH_FIELD_DISP_DISPLACEMENT_TS                           = 0x9004,
            CH_FIELD_GNSS_1_LLH_POSITION                            = 0x9103,
            CH_FIELD_GNSS_1_ECEF_POSITION                           = 0x9104,
            CH_FIELD_GNSS_1_NED_VELOCITY                            = 0x9105,
            CH_FIELD_GNSS_1_ECEF_VELOCITY                           = 0x9106,
            CH_FIELD_GNSS_1_DOP                                     = 0x9107,
            CH_FIELD_GNSS_1_UTC_TIME                                = 0x9108,
            CH_FIELD_GNSS_1_GPS_TIME                                = 0x9109,
            CH_FIELD_GNSS_1_CLOCK_INFO                              = 0x910A,
            CH_FIELD_GNSS_1_FIX_INFO                                = 0x910B,
            CH_FIELD_GNSS_1_SPACE_VEHICLE_INFO                      = 0x910C,
            CH_FIELD_GNSS_1_HARDWARE_STATUS                         = 0x910D,
            CH_FIELD_GNSS_1_DGNSS_INFO                              = 0x910E,
            CH_FIELD_GNSS_1_DGNSS_CHANNEL_STATUS                    = 0x910F,
            CH_FIELD_GNSS_1_CLOCK_INFO_2                            = 0x9110,
            CH_FIELD_GNSS_1_GPS_LEAP_SECONDS                        = 0x9111,
            CH_FIELD_GNSS_1_SBAS_INFO                               = 0x9112,
            CH_FIELD_GNSS_1_SBAS_CORRECTION                         = 0x9113,
            CH_FIELD_GNSS_1_RF_ERROR_DETECTION                      = 0x9114,
            CH_FIELD_GNSS_1_SATELLITE_STATUS                        = 0x9120,
            CH_FIELD_GNSS_1_RAW_OBSERVATION                         = 0x9122,
            CH_FIELD_GNSS_1_STATION_INFO                            = 0x9130,
            CH_FIELD_GNSS_1_RTK_CORRECTIONS_STATUS                  = 0x9131,
            CH_FIELD_GNSS_1_GPS_EPHEMERIS                           = 0x9161,
            CH_FIELD_GNSS_1_GLONASS_EPHEMERIS                       = 0x9162,
            CH_FIELD_GNSS_1_GALILEO_EPHEMERIS                       = 0x9163,
            CH_FIELD_GNSS_1_GPS_IONOSPHERIC_CORRECTION              = 0x9171,
            CH_FIELD_GNSS_1_GALILEO_IONOSPHERIC_CORRECTION          = 0x9173,
            CH_FIELD_GNSS_1_SHARED_EVENT_SOURCE                     = 0x91D0,
            CH_FIELD_GNSS_1_SHARED_TICKS                            = 0x91D1,
            CH_FIELD_GNSS_1_SHARED_DELTA_TICKS                      = 0x91D2,
            CH_FIELD_GNSS_1_SHARED_GPS_TIMESTAMP                    = 0x91D3,
            CH_FIELD_GNSS_1_SHARED_DELTA_TIMESTAMP                  = 0x91D4,
            CH_FIELD_GNSS_1_SHARED_REFERENCE_TIMESTAMP              = 0x91D5,
            CH_FIELD_GNSS_1_SHARED_DELTA_REFERENCE_TIME             = 0x91D6,
            CH_FIELD_GNSS_1_SHARED_EXTERNAL_TIMESTAMP               = 0x91D7,
            CH_FIELD_GNSS_1_SHARED_DELTA_EXTERNAL_TIME              = 0x91D8,
            CH_FIELD_GNSS_2_LLH_POSITION                            = 0x9203,
            CH_FIELD_GNSS_2_ECEF_POSITION                           = 0x9204,
            CH_FIELD_GNSS_2_NED_VELOCITY                            = 0x9205,
            CH_FIELD_GNSS_2_ECEF_VELOCITY                           = 0x9206,
            CH_FIELD_GNSS_2_DOP                                     = 0x9207,
            CH_FIELD_GNSS_2_UTC_TIME                                = 0x9208,
            CH_FIELD_GNSS_2_GPS_TIME                                = 0x9209,
            CH_FIELD_GNSS_2_CLOCK_INFO                              = 0x920A,
            CH_FIELD_GNSS_2_FIX_INFO                                = 0x920B,
            CH_FIELD_GNSS_2_SPACE_VEHICLE_INFO                      = 0x920C,
            CH_FIELD_GNSS_2_HARDWARE_STATUS                         = 0x920D,
            CH_FIELD_GNSS_2_DGNSS_INFO                              = 0x920E,
            CH_FIELD_GNSS_2_DGNSS_CHANNEL_STATUS                    = 0x920F,
            CH_FIELD_GNSS_2_CLOCK_INFO_2                            = 0x9210,
            CH_FIELD_GNSS_2_GPS_LEAP_SECONDS                        = 0x9211,
            CH_FIELD_GNSS_2_SBAS_INFO                               = 0x9212,
            CH_FIELD_GNSS_2_SBAS_CORRECTION                         = 0x9213,
            CH_FIELD_GNSS_2_RF_ERROR_DETECTION                      = 0x9214,
            CH_FIELD_GNSS_2_SATELLITE_STATUS                        = 0x9220,
            CH_FIELD_GNSS_2_RAW_OBSERVATION                         = 0x9222,
            CH_FIELD_GNSS_2_STATION_INFO                            = 0x9230,
            CH_FIELD_GNSS_2_RTK_CORRECTIONS_STATUS                  = 0x9231,
            CH_FIELD_GNSS_2_GPS_EPHEMERIS                           = 0x9261,
            CH_FIELD_GNSS_2_GLONASS_EPHEMERIS                       = 0x9262,
            CH_FIELD_GNSS_2_GALILEO_EPHEMERIS                       = 0x9263,
            CH_FIELD_GNSS_2_GPS_IONOSPHERIC_CORRECTION              = 0x9271,
            CH_FIELD_GNSS_2_GALILEO_IONOSPHERIC_CORRECTION          = 0x9273,
            CH_FIELD_GNSS_2_SHARED_EVENT_SOURCE                     = 0x92D0,
            CH_FIELD_GNSS_2_SHARED_TICKS                            = 0x92D1,
            CH_FIELD_GNSS_2_SHARED_DELTA_TICKS                      = 0x92D2,
            CH_FIELD_GNSS_2_SHARED_GPS_TIMESTAMP                    = 0x92D3,
            CH_FIELD_GNSS_2_SHARED_DELTA_TIMESTAMP                  = 0x92D4,
            CH_FIELD_GNSS_2_SHARED_REFERENCE_TIMESTAMP              = 0x92D5,
            CH_FIELD_GNSS_2_SHARED_DELTA_REFERENCE_TIME             = 0x92D6,
            CH_FIELD_GNSS_2_SHARED_EXTERNAL_TIMESTAMP               = 0x92D7,
            CH_FIELD_GNSS_2_SHARED_DELTA_EXTERNAL_TIME              = 0x92D8,
            CH_FIELD_GNSS_3_LLH_POSITION                            = 0x9303,
            CH_FIELD_GNSS_3_ECEF_POSITION                           = 0x9304,
            CH_FIELD_GNSS_3_NED_VELOCITY                            = 0x9305,
            CH_FIELD_GNSS_3_ECEF_VELOCITY                           = 0x9306,
            CH_FIELD_GNSS_3_DOP                                     = 0x9307,
            CH_FIELD_GNSS_3_UTC_TIME                                = 0x9308,
            CH_FIELD_GNSS_3_GPS_TIME                                = 0x9309,
            CH_FIELD_GNSS_3_CLOCK_INFO                              = 0x930A,
            CH_FIELD_GNSS_3_FIX_INFO                                = 0x930B,
            CH_FIELD_GNSS_3_SPACE_VEHICLE_INFO                      = 0x930C,
            CH_FIELD_GNSS_3_HARDWARE_STATUS                         = 0x930D,
            CH_FIELD_GNSS_3_DGNSS_INFO                              = 0x930E,
            CH_FIELD_GNSS_3_DGNSS_CHANNEL_STATUS                    = 0x930F,
            CH_FIELD_GNSS_3_CLOCK_INFO_2                            = 0x9310,
            CH_FIELD_GNSS_3_GPS_LEAP_SECONDS                        = 0x9311,
            CH_FIELD_GNSS_3_SBAS_INFO                               = 0x9312,
            CH_FIELD_GNSS_3_SBAS_CORRECTION                         = 0x9313,
            CH_FIELD_GNSS_3_RF_ERROR_DETECTION                      = 0x9314,
            CH_FIELD_GNSS_3_SATELLITE_STATUS                        = 0x9320,
            CH_FIELD_GNSS_3_RAW_OBSERVATION                         = 0x9322,
            CH_FIELD_GNSS_3_STATION_INFO                            = 0x9330,
            CH_FIELD_GNSS_3_RTK_CORRECTIONS_STATUS                  = 0x9331,
            CH_FIELD_GNSS_3_GPS_EPHEMERIS                           = 0x9361,
            CH_FIELD_GNSS_3_GLONASS_EPHEMERIS                       = 0x9362,
            CH_FIELD_GNSS_3_GALILEO_EPHEMERIS                       = 0x9363,
            CH_FIELD_GNSS_3_GPS_IONOSPHERIC_CORRECTION              = 0x9371,
            CH_FIELD_GNSS_3_GALILEO_IONOSPHERIC_CORRECTION          = 0x9373,
            CH_FIELD_GNSS_3_SHARED_EVENT_SOURCE                     = 0x93D0,
            CH_FIELD_GNSS_3_SHARED_TICKS                            = 0x93D1,
            CH_FIELD_GNSS_3_SHARED_DELTA_TICKS                      = 0x93D2,
            CH_FIELD_GNSS_3_SHARED_GPS_TIMESTAMP                    = 0x93D3,
            CH_FIELD_GNSS_3_SHARED_DELTA_TIMESTAMP                  = 0x93D4,
            CH_FIELD_GNSS_3_SHARED_REFERENCE_TIMESTAMP              = 0x93D5,
            CH_FIELD_GNSS_3_SHARED_DELTA_REFERENCE_TIME             = 0x93D6,
            CH_FIELD_GNSS_3_SHARED_EXTERNAL_TIMESTAMP               = 0x93D7,
            CH_FIELD_GNSS_3_SHARED_DELTA_EXTERNAL_TIME              = 0x93D8,
            CH_FIELD_GNSS_4_LLH_POSITION                            = 0x9403,
            CH_FIELD_GNSS_4_ECEF_POSITION                           = 0x9404,
            CH_FIELD_GNSS_4_NED_VELOCITY                            = 0x9405,
            CH_FIELD_GNSS_4_ECEF_VELOCITY                           = 0x9406,
            CH_FIELD_GNSS_4_DOP                                     = 0x9407,
            CH_FIELD_GNSS_4_UTC_TIME                                = 0x9408,
            CH_FIELD_GNSS_4_GPS_TIME                                = 0x9409,
            CH_FIELD_GNSS_4_CLOCK_INFO                              = 0x940A,
            CH_FIELD_GNSS_4_FIX_INFO                                = 0x940B,
            CH_FIELD_GNSS_4_SPACE_VEHICLE_INFO                      = 0x940C,
            CH_FIELD_GNSS_4_HARDWARE_STATUS                         = 0x940D,
            CH_FIELD_GNSS_4_DGNSS_INFO                              = 0x940E,
            CH_FIELD_GNSS_4_DGNSS_CHANNEL_STATUS                    = 0x940F,
            CH_FIELD_GNSS_4_CLOCK_INFO_2                            = 0x9410,
            CH_FIELD_GNSS_4_GPS_LEAP_SECONDS                        = 0x9411,
            CH_FIELD_GNSS_4_SBAS_INFO                               = 0x9412,
            CH_FIELD_GNSS_4_SBAS_CORRECTION                         = 0x9413,
            CH_FIELD_GNSS_4_RF_ERROR_DETECTION                      = 0x9414,
            CH_FIELD_GNSS_4_SATELLITE_STATUS                        = 0x9420,
            CH_FIELD_GNSS_4_RAW_OBSERVATION                         = 0x9422,
            CH_FIELD_GNSS_4_STATION_INFO                            = 0x9430,
            CH_FIELD_GNSS_4_RTK_CORRECTIONS_STATUS                  = 0x9431,
            CH_FIELD_GNSS_4_GPS_EPHEMERIS                           = 0x9461,
            CH_FIELD_GNSS_4_GLONASS_EPHEMERIS                       = 0x9462,
            CH_FIELD_GNSS_4_GALILEO_EPHEMERIS                       = 0x9463,
            CH_FIELD_GNSS_4_GPS_IONOSPHERIC_CORRECTION              = 0x9471,
            CH_FIELD_GNSS_4_GALILEO_IONOSPHERIC_CORRECTION          = 0x9473,
            CH_FIELD_GNSS_4_SHARED_EVENT_SOURCE                     = 0x94D0,
            CH_FIELD_GNSS_4_SHARED_TICKS                            = 0x94D1,
            CH_FIELD_GNSS_4_SHARED_DELTA_TICKS                      = 0x94D2,
            CH_FIELD_GNSS_4_SHARED_GPS_TIMESTAMP                    = 0x94D3,
            CH_FIELD_GNSS_4_SHARED_DELTA_TIMESTAMP                  = 0x94D4,
            CH_FIELD_GNSS_4_SHARED_REFERENCE_TIMESTAMP              = 0x94D5,
            CH_FIELD_GNSS_4_SHARED_DELTA_REFERENCE_TIME             = 0x94D6,
            CH_FIELD_GNSS_4_SHARED_EXTERNAL_TIMESTAMP               = 0x94D7,
            CH_FIELD_GNSS_4_SHARED_DELTA_EXTERNAL_TIME              = 0x94D8,
            CH_FIELD_GNSS_5_LLH_POSITION                            = 0x9503,
            CH_FIELD_GNSS_5_ECEF_POSITION                           = 0x9504,
            CH_FIELD_GNSS_5_NED_VELOCITY                            = 0x9505,
            CH_FIELD_GNSS_5_ECEF_VELOCITY                           = 0x9506,
            CH_FIELD_GNSS_5_DOP                                     = 0x9507,
            CH_FIELD_GNSS_5_UTC_TIME                                = 0x9508,
            CH_FIELD_GNSS_5_GPS_TIME                                = 0x9509,
            CH_FIELD_GNSS_5_CLOCK_INFO                              = 0x950A,
            CH_FIELD_GNSS_5_FIX_INFO                                = 0x950B,
            CH_FIELD_GNSS_5_SPACE_VEHICLE_INFO                      = 0x950C,
            CH_FIELD_GNSS_5_HARDWARE_STATUS                         = 0x950D,
            CH_FIELD_GNSS_5_DGNSS_INFO                              = 0x950E,
            CH_FIELD_GNSS_5_DGNSS_CHANNEL_STATUS                    = 0x950F,
            CH_FIELD_GNSS_5_CLOCK_INFO_2                            = 0x9510,
            CH_FIELD_GNSS_5_GPS_LEAP_SECONDS                        = 0x9511,
            CH_FIELD_GNSS_5_SBAS_INFO                               = 0x9512,
            CH_FIELD_GNSS_5_SBAS_CORRECTION                         = 0x9513,
            CH_FIELD_GNSS_5_RF_ERROR_DETECTION                      = 0x9514,
            CH_FIELD_GNSS_5_SATELLITE_STATUS                        = 0x9520,
            CH_FIELD_GNSS_5_RAW_OBSERVATION                         = 0x9522,
            CH_FIELD_GNSS_5_STATION_INFO                            = 0x9530,
            CH_FIELD_GNSS_5_RTK_CORRECTIONS_STATUS                  = 0x9531,
            CH_FIELD_GNSS_5_GPS_EPHEMERIS                           = 0x9561,
            CH_FIELD_GNSS_5_GLONASS_EPHEMERIS                       = 0x9562,
            CH_FIELD_GNSS_5_GALILEO_EPHEMERIS                       = 0x9563,
            CH_FIELD_GNSS_5_GPS_IONOSPHERIC_CORRECTION              = 0x9571,
            CH_FIELD_GNSS_5_GALILEO_IONOSPHERIC_CORRECTION          = 0x9573,
            CH_FIELD_GNSS_5_SHARED_EVENT_SOURCE                     = 0x95D0,
            CH_FIELD_GNSS_5_SHARED_TICKS                            = 0x95D1,
            CH_FIELD_GNSS_5_SHARED_DELTA_TICKS                      = 0x95D2,
            CH_FIELD_GNSS_5_SHARED_GPS_TIMESTAMP                    = 0x95D3,
            CH_FIELD_GNSS_5_SHARED_DELTA_TIMESTAMP                  = 0x95D4,
            CH_FIELD_GNSS_5_SHARED_REFERENCE_TIMESTAMP              = 0x95D5,
            CH_FIELD_GNSS_5_SHARED_DELTA_REFERENCE_TIME             = 0x95D6,
            CH_FIELD_GNSS_5_SHARED_EXTERNAL_TIMESTAMP               = 0x95D7,
            CH_FIELD_GNSS_5_SHARED_DELTA_EXTERNAL_TIME              = 0x95D8,
            CH_FIELD_SYSTEM_BUILT_IN_TEST                           = 0xA001,
            CH_FIELD_SYSTEM_TIME_SYNC_STATUS                        = 0xA002,
            CH_FIELD_SYSTEM_GPIO_STATE                              = 0xA003,
            CH_FIELD_SYSTEM_SHARED_EVENT_SOURCE                     = 0xA0D0,
            CH_FIELD_SYSTEM_SHARED_TICKS                            = 0xA0D1,
            CH_FIELD_SYSTEM_SHARED_DELTA_TICKS                      = 0xA0D2,
            CH_FIELD_SYSTEM_SHARED_GPS_TIMESTAMP                    = 0xA0D3,
            CH_FIELD_SYSTEM_SHARED_DELTA_TIMESTAMP                  = 0xA0D4,
            CH_FIELD_SYSTEM_SHARED_REFERENCE_TIMESTAMP              = 0xA0D5,
            CH_FIELD_SYSTEM_SHARED_DELTA_REFERENCE_TIME             = 0xA0D6,
            CH_FIELD_SYSTEM_SHARED_EXTERNAL_TIMESTAMP               = 0xA0D7,
            CH_FIELD_SYSTEM_SHARED_DELTA_EXTERNAL_TIME              = 0xA0D8,
        };

        //API Constant: MIN_SHARED_FIELD_DESCRIPTOR
        //  The minimum descriptor that marks the start of available shared data field descriptors. If a field descriptor is above 0xD0 it is shared.
        static const uint8 MIN_SHARED_FIELD_DESCRIPTOR = 0xD0;

        //====================================================================================================
        //API Enums: ChannelQualifier
        //    The enums for different MIP Channel Qualifiers.
        //    This combined with the <ChannelField> produces a unique identifier for each individual channel that is collected.
        //
        //    CH_UNKNOWN                    - 0   - Unknown Channel
        //    CH_X                          - 1   - X
        //    CH_Y                          - 2   - Y
        //    CH_Z                          - 3   - Z
        //    CH_MATRIX                     - 4   - Matrix
        //    CH_QUATERNION                 - 5   - Quaternion
        //    CH_ROLL                       - 6   - Roll
        //    CH_PITCH                      - 7   - Pitch
        //    CH_YAW                        - 8   - Yaw
        //    CH_TICK                       - 9   - Tick
        //    CH_TIMESTAMP                  - 10  - Timestamp
        //    CH_STATUS                     - 11  - Status
        //    CH_TIME_OF_WEEK               - 12  - Time of Week
        //    CH_WEEK_NUMBER                - 13  - Week Number
        //    CH_LATITUDE                   - 14  - Latitude
        //    CH_LONGITUDE                  - 15  - Longitude
        //    CH_HEIGHT_ABOVE_ELLIPSOID     - 16  - Height Above Ellipsoid
        //    CH_HEIGHT_ABOVE_MSL           - 17  - Height Above MSL
        //    CH_HEIGHT                     - 81  - Height (Other reference point)
        //    CH_HORIZONTAL_ACCURACY        - 18  - Horizontal Accuracy
        //    CH_VERTICAL_ACCURACY          - 19  - Vertical Accuracy
        //    CH_POSITION_ACCURACY          - 20  - Position Accuracy
        //    CH_NORTH                      - 21  - North
        //    CH_EAST                       - 22  - East
        //    CH_DOWN                       - 23  - Down
        //    CH_SPEED                      - 24  - Speed
        //    CH_GROUND_SPEED               - 25  - Ground Speed
        //    CH_HEADING                    - 26  - Heading
        //    CH_SPEED_ACCURACY             - 27  - Speed Accuracy
        //    CH_HEADING_ACCURACY           - 28  - Heading Accuracy
        //    CH_VELOCITY_ACCURACY          - 29  - Velocity Accuracy
        //    CH_GEOMETRIC_DOP              - 30  - Geometric DOP
        //    CH_POSITION_DOP               - 31  - Position DOP
        //    CH_HORIZONTAL_DOP             - 32  - Horizontal DOP
        //    CH_VERTICAL_DOP               - 33  - Vertical DOP
        //    CH_TIME_DOP                   - 34  - Time DOP
        //    CH_NORTHING_DOP               - 35  - Northing DOP
        //    CH_EASTING_DOP                - 36  - Easting DOP
        //    CH_FLAGS                      - 37  - Flags
        //    CH_BIAS                       - 38  - Bias
        //    CH_DRIFT                      - 39  - Drift
        //    CH_ACCURACY_ESTIMATE          - 40  - Accuracy Estimate
        //    CH_FIX_TYPE                   - 41  - Fix Type
        //    CH_SV_COUNT                   - 42  - Number of Space Vehicles used for solution
        //    CH_CHANNEL                    - 43  - Channel Number
        //    CH_ID                         - 44  - ID Number
        //    CH_CARRIER_TO_NOISE_RATIO     - 45  - Carrier to Noise Ratio
        //    CH_AZIMUTH                    - 46  - Azimuth
        //    CH_ELEVATION                  - 47  - Elevation
        //    CH_SENSOR_STATE               - 48  - Sensor State
        //    CH_ANTENNA_STATE              - 49  - Antenna State
        //    CH_ANTENNA_POWER              - 50  - Antenna Power
        //    CH_FILTER_STATE               - 51  - Filter State
        //    CH_DYNAMICS_MODE              - 52  - Dynamics Mode
        //    CH_MAGNITUDE                  - 53  - Magnitude
        //    CH_HEADING_UNCERTAINTY        - 54  - Heading Uncertainty
        //    CH_SOURCE                     - 55  - Source
        //    CH_INCLINATION                - 56  - Inclination
        //    CH_DECLINATION                - 57  - Declination
        //    CH_PRESSURE                   - 58  - Pressure
        //    CH_AGE                        - 59  - Age
        //    CH_NUM_CHANNELS               - 60  - Number of Channels
        //    CH_CORRECTION                 - 61  - Correction
        //    CH_RATE_CORRECTION            - 62  - Rate Correction
        //    CH_GEOMETRIC_ALTITUDE         - 63  - Geometric Altitude
        //    CH_GEOPOTENTIAL_ALTITUDE      - 64  - Geopotential Altitude
        //    CH_TEMPERATURE                - 65  - Temperature
        //    CH_DENSITY                    - 66  - Density
        //    CH_ALTITUDE                   - 67  - Altitude
        //    CH_DISPLACEMENT               - 68  - Displacement
        //    CH_MAX_TEMP                   - 69  - Max Temp
        //    CH_MIN_TEMP                   - 70  - Min Temp
        //    CH_MEAN_TEMP                  - 71  - Mean Temp
        //    CH_BIAS_ACCURACY_ESTIMATE     - 72  - Bias Accuracy Estimate
        //    CH_DRIFT_ACCURACY_ESTIMATE    - 73  - Drift Accuracy Estimate
        //    CH_SECONDS                    - 74  - Seconds
        //    CH_NUM_PACKETS                - 76  - Num Packets
        //    CH_GPS_CORRECTION_LATENCY     - 77  - GPS Correction Latency
        //    CH_GLONASS_CORRECTION_LATENCY - 78  - Glonass Correction Latency
        //    CH_GALILEO_CORRECTION_LATENCY - 79  - Galileo Correction Latency
        //    CH_BEIDOU_CORRECTION_LATENCY  - 80  - Beidou Correction Latency
        //    CH_HEALTH                     - 82  - Satellite Health
        //    CH_INDEX                      - 83  - Index
        //    CH_COUNT                      - 84  - Count
        //    CH_SIGNAL_STRENGTH            - 85  - Signal Strength
        //    CH_SIGNAL_QUALITY             - 86  - Signal Quality
        //    CH_RANGE                      - 87  - Range
        //    CH_RANGE_UNC                  - 88  - Range Uncertainty
        //    CH_ALPHA                      - 90  - Alpha
        //    CH_BETA                       - 91  - Beta
        //    CH_DISTURBANCE_FLAGS          - 92  - Disturbance Flags
        //    CH_CARRIER_PHASE              - 93  - Carrier Phase
        //    CH_CARRIER_PHASE_UNC          - 94  - Carrier Phase Uncertainty
        //    CH_DOPPLER                    - 95  - Doppler
        //    CH_DOPPLER_UNC                - 96  - Doppler Uncertainty
        //    CH_DELTA_TIME                 - 97  - Delta Time
        //    CH_DELTA_TICK                 - 98  - Delta Tick
        //    CH_ERROR                      - 99  - Measurement Error
        //    CH_ERROR_UNC                  - 100 - Measurement Error Uncertainty
        //    CH_W                          - 101 - W
        //    CH_M0                         - 102 - Matrix M0
        //    CH_M1                         - 103 - Matrix M1
        //    CH_M2                         - 104 - Matrix M2
        //    CH_M3                         - 105 - Matrix M3
        //    CH_M4                         - 106 - Matrix M4
        //    CH_M5                         - 107 - Matrix M5
        //    CH_M6                         - 108 - Matrix M6
        //    CH_M7                         - 109 - Matrix M7
        //    CH_M8                         - 110 - Matrix M8
        //    CH_NANOSECONDS                - 111 - Nanoseconds
        //    CH_VALID_FLAGS                - 112 - Valid Flags
        //    CH_PPS_VALID                  - 113 - PPS Valid
        //    CH_LAST_PPS                   - 114 - Last PPS Received
        //    CH_UDREI                      - 115 - User Differential Range Error Index
        //    CH_PSEUDORANGE_CORRECTION     - 116 - Pseudorange Correction
        //    CH_IONOSPHERIC_CORRECTION     - 117 - Ionospheric Correction
        //    CH_JAMMING_STATE              - 118 - Jamming State
        //    CH_SPOOFING_STATE             - 119 - Spoofing State
        //    CH_SYSTEM_ID                  - 120 - System ID (GNSS, SBAS, etc.)
        //    CH_SATELLITE_ID               - 121 - Satellite ID (GNSS, SBAS, etc.)
        //
        //    CH_BIT_SYSTEM_GENERAL         - 248 - Built In Test System General
        //    CH_BIT_SYSTEM_PROCESS         - 249 - Built In Test System Process
        //    CH_BIT_IMU_GENERAL            - 250 - Built In Test IMU General
        //    CH_BIT_IMU_SENSORS            - 251 - Built In Test IMU Sensors
        //    CH_BIT_IMU_FACTORY_BITS       - 252 - Built in Test IMU Factory Bits Valid
        //    CH_BIT_FILTER_GENERAL         - 253 - Built In Test Est Filter General
        //    CH_BIT_GNSS_GENERAL           - 254 - Built In Test GNSS General
        //    CH_BIT_GNSS_RECEIVERS         - 255 - Built In Test GNSS Receivers
        //====================================================================================================
        enum ChannelQualifier
        {
            CH_UNKNOWN                      = 0,
            CH_X                            = 1,
            CH_Y                            = 2,
            CH_Z                            = 3,
            CH_MATRIX                       = 4,
            CH_QUATERNION                   = 5,
            CH_ROLL                         = 6,
            CH_PITCH                        = 7,
            CH_YAW                          = 8,
            CH_TICK                         = 9,
            CH_TIMESTAMP                    = 10,
            CH_STATUS                       = 11,
            CH_TIME_OF_WEEK                 = 12,
            CH_WEEK_NUMBER                  = 13,
            CH_LATITUDE                     = 14,
            CH_LONGITUDE                    = 15,
            CH_HEIGHT_ABOVE_ELLIPSOID       = 16,
            CH_HEIGHT_ABOVE_MSL             = 17,
            CH_HORIZONTAL_ACCURACY          = 18,
            CH_VERTICAL_ACCURACY            = 19,
            CH_POSITION_ACCURACY            = 20,
            CH_NORTH                        = 21,
            CH_EAST                         = 22,
            CH_DOWN                         = 23,
            CH_SPEED                        = 24,
            CH_GROUND_SPEED                 = 25,
            CH_HEADING                      = 26,
            CH_SPEED_ACCURACY               = 27,
            CH_HEADING_ACCURACY             = 28,
            CH_VELOCITY_ACCURACY            = 29,
            CH_GEOMETRIC_DOP                = 30,
            CH_POSITION_DOP                 = 31,
            CH_HORIZONTAL_DOP               = 32,
            CH_VERTICAL_DOP                 = 33,
            CH_TIME_DOP                     = 34,
            CH_NORTHING_DOP                 = 35,
            CH_EASTING_DOP                  = 36,
            CH_FLAGS                        = 37,
            CH_BIAS                         = 38,
            CH_DRIFT                        = 39,
            CH_ACCURACY_ESTIMATE            = 40,
            CH_FIX_TYPE                     = 41,
            CH_SV_COUNT                     = 42,
            CH_CHANNEL                      = 43,
            CH_ID                           = 44,
            CH_CARRIER_TO_NOISE_RATIO       = 45,
            CH_AZIMUTH                      = 46,
            CH_ELEVATION                    = 47,
            CH_SENSOR_STATE                 = 48,
            CH_ANTENNA_STATE                = 49,
            CH_ANTENNA_POWER                = 50,
            CH_FILTER_STATE                 = 51,
            CH_DYNAMICS_MODE                = 52,
            CH_MAGNITUDE                    = 53,
            CH_HEADING_UNCERTAINTY          = 54,
            CH_SOURCE                       = 55,
            CH_INCLINATION                  = 56,
            CH_DECLINATION                  = 57,
            CH_PRESSURE                     = 58,
            CH_AGE                          = 59,
            CH_NUM_CHANNELS                 = 60,
            CH_CORRECTION                   = 61,
            CH_RATE_CORRECTION              = 62,
            CH_GEOMETRIC_ALTITUDE           = 63,
            CH_GEOPOTENTIAL_ALTITUDE        = 64,
            CH_TEMPERATURE                  = 65,
            CH_DENSITY                      = 66,
            CH_ALTITUDE                     = 67,
            CH_DISPLACEMENT                 = 68,
            CH_MAX_TEMP                     = 69,
            CH_MIN_TEMP                     = 70,
            CH_MEAN_TEMP                    = 71,
            CH_BIAS_ACCURACY_ESTIMATE       = 72,
            CH_DRIFT_ACCURACY_ESTIMATE      = 73,
            CH_SECONDS                      = 74,
            CH_NUM_PACKETS                  = 76,
            CH_GPS_CORRECTION_LATENCY       = 77,
            CH_GLONASS_CORRECTION_LATENCY   = 78,
            CH_GALILEO_CORRECTION_LATENCY   = 79,
            CH_BEIDOU_CORRECTION_LATENCY    = 80,
            CH_HEIGHT                       = 81,
            CH_HEALTH                       = 82,
            CH_INDEX                        = 83,
            CH_COUNT                        = 84,
            CH_SIGNAL_STRENGTH              = 85,
            CH_SIGNAL_QUALITY               = 86,
            CH_RANGE                        = 87,
            CH_RANGE_UNC                    = 88,
            CH_ALPHA                        = 90,
            CH_BETA                         = 91,
            CH_DISTURBANCE_FLAGS            = 92,
            CH_CARRIER_PHASE                = 93,
            CH_CARRIER_PHASE_UNC            = 94,
            CH_DOPPLER                      = 95,
            CH_DOPPLER_UNC                  = 96,
            CH_DELTA_TIME                   = 97,
            CH_DELTA_TICK                   = 98,
            CH_ERROR                        = 99,
            CH_ERROR_UNC                    = 100,
            CH_W                            = 101,
            CH_M0                           = 102,
            CH_M1                           = 103,
            CH_M2                           = 104,
            CH_M3                           = 105,
            CH_M4                           = 106,
            CH_M5                           = 107,
            CH_M6                           = 108,
            CH_M7                           = 109,
            CH_M8                           = 110,
            CH_NANOSECONDS                  = 111,
            CH_VALID_FLAGS                  = 112,
            CH_PPS_VALID                    = 113,
            CH_LAST_PPS                     = 114,
            CH_UDREI                        = 115,
            CH_PSEUDORANGE_CORRECTION       = 116,
            CH_IONOSPHERIC_CORRECTION       = 117,
            CH_JAMMING_STATE                = 118,
            CH_SPOOFING_STATE               = 119,
            CH_SYSTEM_ID                    = 120,
            CH_SATELLITE_ID                 = 121,

            // Keep BIT channels at end of list
            CH_BIT_SYSTEM_GENERAL           = 248,
            CH_BIT_SYSTEM_PROCESS           = 249,
            CH_BIT_IMU_GENERAL              = 250,
            CH_BIT_IMU_SENSORS              = 251,
            CH_BIT_IMU_FACTORY_BITS         = 252,
            CH_BIT_FILTER_GENERAL           = 253,
            CH_BIT_GNSS_GENERAL             = 254,
            CH_BIT_GNSS_RECEIVERS           = 255
        };
        
        //API Typedef: MipChannelFields
        //    A vector of <ChannelField> enums.
        typedef std::vector<ChannelField> MipChannelFields;

        //API Typedef: MipCommands
        //    A vector of <Command> enums.
        typedef std::vector<Command> MipCommands;

        //API Typedef: MipDataClasses
        //    A vector of <DataClass> enums.
        typedef std::vector<DataClass> MipDataClasses;

        //API Typedef: ChannelIndex
        //    A <ChannelQualifier>, int pair indicating the index value of the qualifier in a channel field.
        typedef std::pair<ChannelQualifier, uint8> ChannelIndex;

        //API Typedef: ChannelIndices
        //    A list of <ChannelIndex> values
        typedef std::vector<ChannelIndex> ChannelIndices;

        //API Typedef: ChannelFieldQualifiers
        //    A map of <ChannelField> values and their associated <ChannelIndices>
        typedef std::map<ChannelField, ChannelIndices> ChannelFieldQualifiers;

#ifndef SWIG
        //Typedef: ChannelId
        //    A typedef for a <ChannelField>, <ChannelQualifier> pair.
        typedef std::pair<ChannelField, ChannelQualifier> ChannelId;

        //Function: channelFieldToDataClass
        //    Gets the <DataClass> for a <MipTypes::ChannelField>.
        //
        //Parameters:
        //    channelId - The <MipTypes::ChannelField> to get the category for.
        //
        //Returns:
        //    The <DataClass> for the given channel ID.
        static DataClass channelFieldToDataClass(MipTypes::ChannelField channelField);

        struct ChannelIdHash
        {
            size_t operator()(const MipTypes::ChannelId& channelId) const;
        };
#endif

        //API Function: channelName
        //    Gets the name of the specified <ChannelId>.
        //    This is the universal channel name that should be used for uploading to SensorCloud.
        //
        //Parameters:
        //    field - The <ChannelField> of the channel.
        //    qualifier - The <ChannelQualifier> of the channel.
        //
        //Returns:
        //    The universal name of the channel.
        //
        //Exceptions:
        //    - <Error>: Unknown channel.
        static std::string channelName(ChannelField field, ChannelQualifier qualifier);

        //API Function: getChannelFields_allDataClasses
        //  Get a list of <ChannelField>s representing the same descriptor/channel field across all GNSS data classes
        //
        //Parameters:
        //  chField - the <ChannelField> value to convert
        //
        //Returns:
        //  <MipChannelFields> - list of channel fields representing the same descriptor in each of the GNSS data classes (including the original value)
        static MipChannelFields getChannelFields_allDataClasses(ChannelField chField);

        //API Function: getChannelField_baseDataClass
        //  Gets the <ChannelField> representing the provided channel field's equivalent in the original GNSS data class (0x81)
        //
        //Parameters:
        //  chField - the <ChannelField> value to convert
        //
        //Returns:
        //  <ChannelField> - the provided channel field's equivalent in the original GNSS data class (0x81)
        static ChannelField getChannelField_baseDataClass(ChannelField chField);

        //API Function: getChannelField_toDataClass
        //  Gets the <ChannelField> representing the provided channel field's equivalent in the specified <DataClass>
        //
        //Parameters:
        //  chField - the <ChannelField> value to convert
        //  dataClass - the <DataClass> to convert the channel field to
        //
        //Returns:
        //  <ChannelField> - the provided channel field's equivalent in the specified data class
        static ChannelField getChannelField_toDataClass(ChannelField chField, DataClass dataClass);

        //API Function: getChannelNamePrependText
        //  Gets the text to prepend the channel name to distinguish between different GNSS data classes
        //
        //Parameters:
        //  chField - the <ChannelField> to get the channel name of
        //
        //Returns:
        //  string - text to prepend the channel name
        static std::string getChannelNamePrependText(ChannelField chField);

        //API Function: getChannelNameAppendText
        //  Gets the text to append to the channel name to distinguish between different shared data fields
        //
        //Parameters:
        //  chField - the <ChannelField> to get the channel name of
        //
        //Returns:
        //  string - text to append to the channel name
        static std::string getChannelNameAppendText(ChannelField chField);

        //API Function: isGnssChannelField
        //  Checks whether the provided <ChannelField> is within a GNSS data set.
        //
        //Parameters:
        //  chField - the <ChannelField> value to check
        //
        //Returns:
        //  bool - true if chField is GNSS data, false if it is not
        static bool isGnssChannelField(ChannelField chField);

        //API Function: isSharedChannelField
        //  Checks whether the provided <ChannelField> is a shared field amongst all inertial data sets.
        //
        //Parameters:
        //  chField - the <ChannelField> value to check
        //
        //Returns:
        //  bool - true if chField is a shared data field, false if it is not
        static bool isSharedChannelField(ChannelField chField);

        //API Function: channelFieldQualifiers
        //    Gets a map of <ChannelField> values with all associated <ChannelQualifier> values and their index within the field.
        //
        //Parameters:
        //    fields - <MipChannelFields> to include if found.
        //
        //Returns:
        //    A map of <ChannelField> and their respective <ChannelIndex> values.
        static ChannelFieldQualifiers channelFieldQualifiers(const MipChannelFields& fields);

        //API Function: channelFieldQualifier
        //    Gets the <ChannelQualifier> of the <ChannelField> for the specified index.
        //
        //Parameters:
        //    field - target <ChannelField>.
        //    index - 1-based index within the field to lookup
        //
        //Returns:
        //    A <ChannelQualifier> that corresponds to the index or <CH_UNKNOWN> if not found.
        static ChannelQualifier channelFieldQualifier(ChannelField field, uint8 index);

        //API Function: channelFieldQualifierIndex
        //    Gets the index of the <ChannelQualifier> in the <ChannelField>.
        //
        //Parameters:
        //    field - target <ChannelField>.
        //    qualifier - <ChannelQualifier> within the field to lookup the index of
        //
        //Returns:
        //    The 1-based index of the specified <ChannelQualifier> in the <ChannelField>, or 0 if the <ChannelQualifier> isn't in the <ChannelField>.
        static uint8 channelFieldQualifierIndex(ChannelField field, ChannelQualifier qualifier);

    private:
        //Function: findChannelIndex
        //  Lookup channel index for given ChannelField based on either qualifier or index
        //  If qualifier known, pass in index 0
        //  If index known, pass in qualifier UNKNOWN
        static ChannelIndex findChannelIndex(ChannelField field, ChannelQualifier qualifier, uint8 index);

    private:
        //Const: CHANNEL_NAMES
        //    An unordered_map mapping each <ChannelId> to its respective name (universal SensorCloud name).
        static const std::unordered_map<ChannelId, std::string, ChannelIdHash> CHANNEL_NAMES;

        //Const: CHANNEL_INDICES
        //    A map mapping each <ChannelField>'s <ChannelQualifier> to its respective index.
        static const ChannelFieldQualifiers CHANNEL_INDICES;

        //Function: GNSS_DATA_CLASSES
        //  vector of <DataClass> values containing all GNSS data class descriptors that have the same field descriptors.
        //  was a const but ran into static initialization order issues with registering GNSS field parsers.
        static std::vector<DataClass> GNSS_DATA_CLASSES();

        //Function: INERTIAL_DATA_CLASSES
        //  vector of <DataClass> values containing all inertial data class descriptors that have the same field descriptors.
        //  was a const but ran into static initialization order issues with registering shared field parsers.
        static std::vector<DataClass> INERTIAL_DATA_CLASSES();
    };

    //API Class: MipChannelIdentifier
    //  A single additional identifier for a MipDataPoint. Contains a uint value with an identifier type specifier.
    class MipChannelIdentifier
    {
    public:
        //API Enum: Type
        //  Identifier type options, indicates what the <MipChannelIdentifier::id> value represents.
        //
        //      GNSS_RECEIVER_ID        - GNSS Receiver ID
        //      GNSS_BASE_STATION_ID    - Differential GNSS Base Station ID
        //      GNSS_CONSTELLATION      - GNSS Constellation ID
        //      GNSS_SATELLITE_ID       - GNSS Satellite ID
        //      GNSS_SIGNAL_ID          - GNSS Signal ID
        //      AIDING_MEASUREMENT_TYPE - Filter Aiding Measurement Type
        //      GNSS_RF_BAND            - GNSS RF Band
        enum Type
        {
            // when adding to this list, be sure to add name string to TYPE_NAMES map
            // Type option order will determine the order they are added to the full channel identifier string
            GNSS_RECEIVER_ID,
            GNSS_BASE_STATION_ID,
            GNSS_CONSTELLATION,
            GNSS_SATELLITE_ID,
            GNSS_SIGNAL_ID,
            AIDING_MEASUREMENT_TYPE,
            GNSS_RF_BAND
        };

        //API Enum: AidingMeasurementTypes
        //  ID definitions when Type is <MipChannelIdentifier::AIDING_MEASUREMENT_TYPE>
        //
        //      GNSS         - 0x01 - GNSS
        //      DUAL_ANTENNA - 0x02 - Dual Antenna
        //      HEADING      - 0x03 - Heading
        //      PRESSURE     - 0x04 - Pressure
        //      MAGNETOMETER - 0x05 - Magnetometer
        //      SPEED        - 0x06 - Speed
        enum AidingMeasurementTypes
        {
            GNSS         = 0x01,
            DUAL_ANTENNA = 0x02,
            HEADING      = 0x03,
            PRESSURE     = 0x04,
            MAGNETOMETER = 0x05,
            SPEED        = 0x06
        };

        //API Enum: GnssConstellationIds
        //  ID definitions when Type is <MipChannelIdentifier::GNSS_CONSTELLATION>
        //
        //      UNKNOWN_CONSTELLATION - 0 - Unknown
        //      GPS                   - 1 - GPS
        //      GLONASS               - 2 - GLONASS
        //      GALILEO               - 3 - Galileo
        //      BEIDOU                - 4 - BeiDou
        enum GnssConstellationIds
        {
            UNKNOWN_CONSTELLATION = 0,
            GPS                   = 1,
            GLONASS               = 2,
            GALILEO               = 3,
            BEIDOU                = 4
        };

        //API Enum: GnssSignalIds
        //  ID definitions when Type is <MipChannelIdentifier::GNSS_SIGNAL_ID>
        //
        //      UNKNOWN        - 0
        //      GPS_L1CA       - 1
        //      GPS_L1P        - 2
        //      GPS_L1Z        - 3
        //      GPS_L2CA       - 4
        //      GPS_L2P        - 5
        //      GPS_L2Z        - 6
        //      GPS_L2CL       - 7
        //      GPS_L2CM       - 8
        //      GPS_L2CML      - 9
        //      GPS_L5I        - 10
        //      GPS_L5Q        - 11
        //      GPS_L5IQ       - 12
        //      GPS_L1CD       - 13
        //      GPS_L1CP       - 14
        //      GPS_L1CDP      - 15
        //      GLONASS_G1CA   - 32
        //      GLONASS_G1P    - 33
        //      GLONASS_G2C    - 34
        //      GLONASS_G2P    - 35
        //      GALILEO_E1C    - 64
        //      GALILEO_E1A    - 65
        //      GALILEO_E1B    - 66
        //      GALILEO_E1BC   - 67
        //      GALILEO_E1ABC  - 68
        //      GALILEO_E6C    - 69
        //      GALILEO_E6A    - 70
        //      GALILEO_E6B    - 71
        //      GALILEO_E6BC   - 72
        //      GALILEO_E6ABC  - 73
        //      GALILEO_E5BI   - 74
        //      GALILEO_E5BQ   - 75
        //      GALILEO_E5BIQ  - 76
        //      GALILEO_E5ABI  - 77
        //      GALILEO_E5ABQ  - 78
        //      GALILEO_E5ABIQ - 79
        //      GALILEO_E5AI   - 80
        //      GALILEO_E5AQ   - 81
        //      GALILEO_E5AIQ  - 82
        //      SBAS_L1CA      - 96
        //      SBAS_L5I       - 97
        //      SBAS_L5Q       - 98
        //      SBAS_L5IQ      - 99
        //      QZSS_L1CA      - 128
        //      QZSS_LEXS      - 129
        //      QZSS_LEXL      - 130
        //      QZSS_LEXSL     - 131
        //      QZSS_L2CM      - 132
        //      QZSS_L2CL      - 133
        //      QZSS_L2CML     - 134
        //      QZSS_L5I       - 135
        //      QZSS_L5Q       - 136
        //      QZSS_L5IQ      - 137
        //      QZSS_L1CD      - 138
        //      QZSS_L1CP      - 139
        //      QZSS_L1CDP     - 140
        //      BEIDOU_B1I     - 160
        //      BEIDOU_B1Q     - 161
        //      BEIDOU_B1IQ    - 162
        //      BEIDOU_B3I     - 163
        //      BEIDOU_B3Q     - 164
        //      BEIDOU_B3IQ    - 165
        //      BEIDOU_B2I     - 166
        //      BEIDOU_B2Q     - 167
        //      BEIDOU_B2IQ    - 168
        enum GnssSignalIds
        {
            UNKNOWN_SIGNAL = 0,
            GPS_L1CA       = 1,
            GPS_L1P        = 2,
            GPS_L1Z        = 3,
            GPS_L2CA       = 4,
            GPS_L2P        = 5,
            GPS_L2Z        = 6,
            GPS_L2CL       = 7,
            GPS_L2CM       = 8,
            GPS_L2CML      = 9,
            GPS_L5I        = 10,
            GPS_L5Q        = 11,
            GPS_L5IQ       = 12,
            GPS_L1CD       = 13,
            GPS_L1CP       = 14,
            GPS_L1CDP      = 15,
            GLONASS_G1CA   = 32,
            GLONASS_G1P    = 33,
            GLONASS_G2C    = 34,
            GLONASS_G2P    = 35,
            GALILEO_E1C    = 64,
            GALILEO_E1A    = 65,
            GALILEO_E1B    = 66,
            GALILEO_E1BC   = 67,
            GALILEO_E1ABC  = 68,
            GALILEO_E6C    = 69,
            GALILEO_E6A    = 70,
            GALILEO_E6B    = 71,
            GALILEO_E6BC   = 72,
            GALILEO_E6ABC  = 73,
            GALILEO_E5BI   = 74,
            GALILEO_E5BQ   = 75,
            GALILEO_E5BIQ  = 76,
            GALILEO_E5ABI  = 77,
            GALILEO_E5ABQ  = 78,
            GALILEO_E5ABIQ = 79,
            GALILEO_E5AI   = 80,
            GALILEO_E5AQ   = 81,
            GALILEO_E5AIQ  = 82,
            SBAS_L1CA      = 96,
            SBAS_L5I       = 97,
            SBAS_L5Q       = 98,
            SBAS_L5IQ      = 99,
            QZSS_L1CA      = 128,
            QZSS_LEXS      = 129,
            QZSS_LEXL      = 130,
            QZSS_LEXSL     = 131,
            QZSS_L2CM      = 132,
            QZSS_L2CL      = 133,
            QZSS_L2CML     = 134,
            QZSS_L5I       = 135,
            QZSS_L5Q       = 136,
            QZSS_L5IQ      = 137,
            QZSS_L1CD      = 138,
            QZSS_L1CP      = 139,
            QZSS_L1CDP     = 140,
            BEIDOU_B1I     = 160,
            BEIDOU_B1Q     = 161,
            BEIDOU_B1IQ    = 162,
            BEIDOU_B3I     = 163,
            BEIDOU_B3Q     = 164,
            BEIDOU_B3IQ    = 165,
            BEIDOU_B2I     = 166,
            BEIDOU_B2Q     = 167,
            BEIDOU_B2IQ    = 168,
        };

        //API Enum: GnssRfBands
        //  ID definitions when Type is <MipChannelIdentifier::GNSS_RF_BAND>
        //
        //      UNKNOWN_RF_BAND - 0 - Unknown
        //      RF_BAND_L1      - 1 - L1
        //      RF_BAND_L2      - 2 - L2
        //      RF_BAND_L5      - 5 - L5
        enum GnssRfBands
        {
            UNKNOWN_RF_BAND = 0,
            RF_BAND_L1      = 1,
            RF_BAND_L2      = 2,
            RF_BAND_L5      = 5
        };

#ifndef SWIG
        // Linux environments fail to automatically hash Type
        struct TypeHash
        {
            size_t operator()(const MipChannelIdentifier::Type& type) const;
        };

        //Typedef: TypeId
        //    A typedef for a <MipChannelIdentifier::Type>, uint32 pair.
        typedef std::pair<Type, uint32> TypeId;
        struct TypeIdHash
        {
            size_t operator()(const MipChannelIdentifier::TypeId& id) const;
        };

        typedef std::tuple<Type, uint32, uint32> SpecifierId;
        struct SpecifierIdHash
        {
            size_t operator()(const MipChannelIdentifier::SpecifierId& id) const;
        };
#endif

    public:
        //API Constructor: MipChannelIdentifier
        //  Default constructor
        MipChannelIdentifier() {}

        //API Constructor: MipChannelIdentifier
        //  Construct MipChannelIdentifier object with specified <MipChannelIdentifier::Type> and ID values.
        //
        //Parameters:
        //  identifierType - specifies the type of identifier this represents
        //  id - the identifier value
        MipChannelIdentifier(Type identifierType, uint32 id) :
            m_type(identifierType),
            m_id(id) {}

        //API Constructor: MipChannelIdentifier
        //  Construct MipChannelIdentifier object with specified <MipChannelIdentifier::Type> and ID values.
        //
        //Parameters:
        //  identifierType - specifies the type of identifier this represents
        //  id - the identifier value
        //  specifier - the optional additional specifier
        MipChannelIdentifier(Type identifierType, uint32 id, uint32 specifier) :
            m_type(identifierType),
            m_id(id),
            m_specifier(specifier) {}

        ~MipChannelIdentifier() {}

    public:
        //API Function: identifierType
        //  Returns the <MipChannelIdentifier::Type> specifier of this identifier.
        Type identifierType() const { return m_type; }

        //API Function: id
        //  Returns the identifier value.
        uint32 id() const { return m_id; }

        //API Function: hasSpecifier
        //  Indicates whether this identifier has an optional additional specifier.
        bool hasSpecifier() const;

        //API Function: specifier
        //  Returns the optional additional specifier value.
        //
        //Note:
        //  This is only valid and applicable if hasSpecifier returns true. Value may be non-zero regardless.
        uint32 specifier() const { return m_specifier; }

        //API Function: name
        //  Returns the string representation of this identifier based on type and value.
        //
        //Parameters:
        //  standardizedFormat - specify whether the format should be left consistent for all identifier types or consolidated where relevant
        //
        //Example:
        //  <GNSS_CONSTELLATION, 2>: true = "gnssConstellation_2", false = "glonass"
        std::string name(bool standardizedFormat = true) const;

    private:
        //Variable: m_type
        //  The <MipChannelIdentifier::Type> indicator of this identifier.
        Type m_type;

        //Variable: m_id
        //  The value of this identifier.
        uint32 m_id;

        //Variable: m_specifier
        //  An option additional specifier for this identifier.
        uint32 m_specifier;

        //API Function: hasSpecifier
        //  Indicates whether this identifier has an optional additional specifier.
        //Parameters:
        //  specifierName - string reference that is set to the specifier name if found
        bool hasSpecifier(std::string& specifierName) const;

        //Const: TYPE_NAMES
        //  A map of <MipChannelIdentifier::Type> values and their string labels.
        static const std::unordered_map<Type, std::string, TypeHash> TYPE_NAMES;

        //Const: TRANSLATED_TYPE_NAMES
        //  A map of <MipChannelIdentifier::TypeId> values and their string labels.
        static const std::unordered_map<TypeId, std::string, TypeIdHash> TRANSLATED_TYPE_NAMES;

        //Const: SPECIFIER_NAMES
        //  A map of <MipChannelIdentifier::SpecifierId> values and their string labels.
        static const std::unordered_map<SpecifierId, std::string, SpecifierIdHash> SPECIFIER_NAMES;
    };

    //API Typedef: MipChannelIdentifiers
    //  A vector of <MipChannelIdentifier> values, used to assign additional identifiers to a <MipDataPoint>
    typedef std::vector<MipChannelIdentifier> MipChannelIdentifiers;

    //API Struct: MipCommandBytes
    //    Contains an <Command> id and a <BytesCollection> vector to store the actual bytes to send to the device for that command.
    struct MipCommandBytes
    {
        //API Variable: id
        // <MipTypes::Command> this object represents
        MipTypes::Command id;

        //API Variable: commands
        // <BytesCollection> of raw command bytes
        BytesCollection commands;

        //API Variable: buildCmdFailed
        // bool - indicates building command bytes was attempted but failed
        // false by default - set to true on failure
        bool buildCmdFailed;

        //API Variable: sendCmdFailed
        // bool - indicates sending the command bytes was attempted but failed
        // false by default - set to true on failure
        bool sendCmdFailed;

        //API Constructor: MipCommandBytes
        // Default constructor for MipCommandBytes object
        MipCommandBytes() :
            buildCmdFailed(false),
            sendCmdFailed(false) {}

        //API Constructor: MipCommandBytes
        // Constructor for MipCommandBytes object
        //
        //Parameters:
        //  id - <MipTypes::Command> this object represents
        MipCommandBytes(MipTypes::Command _id) :
            id(_id),
            buildCmdFailed(false),
            sendCmdFailed(false) {}

        //API Constructor: MipCommandBytes
        // Constructor for MipCommandBytes object
        //
        //Parameters:
        //  id - <MipTypes::Command> this object represents
        //  cmd - raw command <Bytes> to add to the commands <BytesCollection>
        MipCommandBytes(MipTypes::Command _id, Bytes _cmd) :
            id(_id),
            commands({ _cmd }),
            buildCmdFailed(false),
            sendCmdFailed(false) {}

        //API Constructor: MipCommandBytes
        // Constructor for MipCommandBytes object
        //
        //Parameters:
        //  id - <MipTypes::Command> this object represents
        //  cmds - collection of raw command <Bytes> to add to the commands <BytesCollection>
        MipCommandBytes(MipTypes::Command _id, BytesCollection _cmds) :
            id(_id),
            commands(_cmds),
            buildCmdFailed(false),
            sendCmdFailed(false) {}

        //API Function: add
        // Add raw command <Bytes> to commands <BytesCollection>
        //
        //Parameters:
        //  cmd - command <Bytes> to add
        void add(Bytes cmd) { commands.push_back(cmd); }

        //API Function: valid
        // Indicates whether this object contains any relevant information, specifically whether it contains any command <Bytes> or has been marked for failure.
        //
        //Returns:
        //  bool - true if commands size is at least one OR send command failed OR build command failed
        bool valid() { return commands.size() > 0 || sendCmdFailed || buildCmdFailed; }
    };

    //API Typedef: MipCommandSet
    //      A vector of <MipCommandBytes>
    typedef std::vector<MipCommandBytes> MipCommandSet;

    //API Typedef: MipFieldFormat
    //      A <ValueType> vector
    typedef std::vector<ValueType> MipFieldFormat;

    //API Typedef: MipFieldValues
    //      A <Value> vector
    typedef std::vector<Value> MipFieldValues;

    //API Typedef: MipCommandParameters
    //      A list of <MipCommandParameterList> command/parameter definitions
    typedef std::vector<std::pair<MipTypes::Command, MipFieldValues>> MipCommandParameters;

    //API Typedef: MipFunctionSelectors
    //      A <MipTypes::FunctionSelector> vector
    typedef std::vector<MipTypes::FunctionSelector> MipFunctionSelectors;

    //API Typedef: MipResponseMatchValues
    //      A map of locations and values to match in a MIP response to determine success
    typedef std::map<size_t, Value> MipResponseMatchValues;

    //API Class: AidingMeasurementInput
    //  Base class for commanded aiding measurement types for command set 0x13 Aiding Measurement inputs
    class AidingMeasurementInput
    {
    public:
        //API Enum: ResponseMode
        //  Response mode options for Aiding Measurement inputs (command set 0x13).
        //
        //  ACK_NACK      - 0x01 - The device will send and ACK/NACK response only
        //  ECHO_INPUT    - 0x02 - The device will echo the input parameter data back in a response field (recommended for support). An ACK/NACK will also be sent.
        enum ResponseMode
        {
            ACK_NACK    = 0x01,
            ECHO_INPUT  = 0x02 // also includes ACK/NACK
        };

    protected:
        //Variable: m_timestamp
        //  The <Timestamp> of this measurement.
        Timestamp m_timestamp;

        //Variable: m_sensorId
        //  The ID of the source sensor for this measurement.
        uint8 m_sensorId;

        //Variable: m_validFlags
        //  The <Bitfield> valid flags of this measurement.
        Bitfield m_validFlags;

    protected:
        //Constructor: AidingMeasurementInput
        //  Constructs an AidingMeasurementInput object with default values
        AidingMeasurementInput() :
            m_timestamp(0),
            m_sensorId(0),
            m_validFlags(0)
        {}

        //Constructor: AidingMeasurementInput
        //  Constructs and AidingMeasurementInput object from the provided <MipFieldValues> read from the device.
        AidingMeasurementInput(const MipFieldValues& values);

        //Destructor: AidingMeasurementInput
        ~AidingMeasurementInput() {}

    public:
        //Function: toMipFieldValues
        //  Converts this object to a <MipFieldValues> parameter list.
        //
        //Returns:
        //  <MipFieldValues> parameter list
        MipFieldValues toMipFieldValues() const;

    protected:
        //Function: parseMipFieldValues
        //  Populates this object from a MipFieldValues parameter list.
        //
        //Parameters:
        //  values - <MipFieldValues> parameter list
        virtual void parseMipFieldValues(const MipFieldValues& values);

        //Function appendMipFieldValues
        //  [Virtual] Append class-specific aiding measurement values to the parameter list.
        //  Called from toMipFieldValues.
        //
        //Parameters:
        //  values - <MipFieldValues> parameter list
        virtual void appendMipFieldValues(MipFieldValues& values) const = 0;

    public:
        //API Function: timestamp
        //  Get the timestamp of this measurement.
        //
        //Returns:
        //  <Timestamp>
        Timestamp timestamp() const { return m_timestamp; }

        //API Function: timestamp
        //  Set the timestamp of this measurement.
        //
        //Parameters:
        //  ts - <Timestamp>
        void timestamp(Timestamp ts) { m_timestamp = ts; }

        //API Function: timebase
        //  Get the timebase/epoch for the timestamp of this measurement.
        //  Note: read from the <Timestamp> object. timestamp().storedEpoch() returns the same result.
        //
        //Returns:
        //  <Timestamp::Epoch> - timebase/epoch of the timestamp
        Timestamp::Epoch timebase() const { return m_timestamp.storedEpoch(); }

        //API Function: sensorId
        //  Get the data source sensor ID of this measurement.
        //
        //Returns:
        //  uint8 - sensor ID
        uint8 sensorId() const { return m_sensorId; }

        //API Function: sensorId
        //  Set the data source sensor ID of this measurement.
        //
        //Parameters:
        //  id - uint8 sensor ID
        void sensorId(uint8 id) { m_sensorId = id; }

        //API Function: validFlags
        //  Get the valid flags of this measurement.
        //
        //Returns:
        //  <Bitfield> - valid flags
        Bitfield validFlags() const { return m_validFlags; }

        //API Function: validFlags
        //  Set the valid flags for this measurement.
        //
        //Parameters:
        //  flags - <Bitfield> valid flags
        void validFlags(Bitfield flags) { m_validFlags = flags; }
    };

    //API Class: AidingMeasurementPosition
    //  A class that represents position aiding measurement inputs. Extends <AidingMeasurementInput>.
    class AidingMeasurementPosition : public AidingMeasurementInput
    {
    public:
        //API Enum: ValidFlags
        //  Bitmask for each position value in the valid flags.
        //
        //  X           - 0x01
        //  Y           - 0x02
        //  Z           - 0x04
        //  LATITUDE    - 0x01
        //  LONGITUDE   - 0x02
        //  HEIGHT      - 0x04
        //  ALTITUDE    - 0x04
        enum ValidFlags
        {
            X = 1,
            LATITUDE = 1,

            Y = 2,
            LONGITUDE = 2,

            Z = 4,
            HEIGHT = 4,
            ALTITUDE = 4
        };
        
    protected:
        //Variable: m_position
        //  Position measurement value.
        //  Also indicates reference frame.
        Position m_position;

        //Variable: m_unc
        //  Uncertainties of the position measurements.
        GeometricUncertainty m_unc;

    public:
        //API Constructor: AidingMeasurementPosition
        //  Constructs an AidingMeasurementPosition object with default values.
        AidingMeasurementPosition() : AidingMeasurementInput() {}

        //API Constructor: AidingMeasurementPosition
        //  Constructs an AidingMeasurementPosition object with the specified reference frame from the <MipFieldValues> parameter list returned from the device.
        //
        //Parameters:
        //  referenceFrame - the <PositionVelocityReferenceFrame> of this measurement
        //  values - the <MipFieldValues> parameter list to build this object from
        AidingMeasurementPosition(PositionVelocityReferenceFrame referenceFrame, const MipFieldValues& values);

        ~AidingMeasurementPosition() {}

    protected:
        //Function: parseMipFieldValues
        //  Populates measurement values based on the <MipFieldValues> parameter list.
        //
        //Parameters:
        //  values - <MipFieldValues> parameter list
        virtual void parseMipFieldValues(const MipFieldValues& values) override;

        //Function: appendMipFieldValues
        //  Appends the position measurement info to the provided <MipFieldValues> parameter list.
        //
        //Parameters:
        //  values - the <MipFieldValues> parameter list to append to
        virtual void appendMipFieldValues(MipFieldValues& values) const override;

    public:
        //API Function: position
        //  Get the <Position> measurement.
        //
        //Returns:
        //  <Position> - position data of this object
        Position position() const { return m_position; }

        //API Function: position
        //  Set the <Position> measurement.
        void position(Position pos) { m_position = pos; }

        //API Function: uncertainty
        //  Get the measurment uncertainty
        //
        //Returns:
        //  <GeometricUncertainty> - the uncertainty of the position measurement
        GeometricUncertainty uncertainty() const { return m_unc; }

        //API Function: uncertainty
        //  Sets the measurement uncertainty.
        //
        //Parameters:
        //  uncertainty - the <GeometricUncertainty> of the measurement
        void uncertainty(GeometricUncertainty uncertainty) { m_unc = uncertainty; }

        //API Function: referenceFrame
        //  Get the <PositionVelocityReferenceFrame> of this position measurement.
        //
        //Returns:
        //  <PositionVelocityReferenceFrame> - reference frame ID of the measurement
        PositionVelocityReferenceFrame referenceFrame() const { return m_position.referenceFrame; }
        
        //API Function: referenceFrame
        //  Set the <PositionVelocityReferenceFrame> of this measurement.
        //
        //Parameters:
        //  frame - the <PositionVelocityReferenceFrame> to set
        void referenceFrame(PositionVelocityReferenceFrame frame) { m_position.referenceFrame = m_unc.referenceFrame = frame; }

        //API Function: valid
        //  Checks whether the specified value is valid.
        //
        //Parameters:
        //  <ValidFlags> value bitmask
        //
        //Returns:
        //  bool - true if valid
        bool valid(ValidFlags val) const { return m_validFlags.checkBit(static_cast<uint8>(val)); }
        
        //API Function: valid
        //  Sets the validity of the specified value.
        //
        //Parameters:
        //  val - <ValidFlags> value bitmask
        //  valid - bool indicating whether the value is valid
        void valid(ValidFlags val, bool valid) { m_validFlags.set(val, valid ? 1 : 0); }
    };

    //API Class: AidingMeasurementVelocity
    //  A class that represents velocity aiding measurement inputs. Extends <AidingMeasurementInput>.
    class AidingMeasurementVelocity : public AidingMeasurementInput
    {
    public:
        //API Enum: ValidFlags
        //  Bitmask for each velocity value in the valid flags.
        //
        //  X           - 0x01
        //  Y           - 0x02
        //  Z           - 0x04
        //  NORTH       - 0x01
        //  EAST        - 0x02
        //  DOWN        - 0x04
        enum ValidFlags
        {
            X = 1,
            NORTH = 1,

            Y = 2,
            EAST = 2,

            Z = 4,
            DOWN = 4
        };

    protected:
        //Variable: m_velocity
        //  The <Velocity> measurement
        Velocity m_velocity;

        //Variable: m_unc
        //  The uncertainty of the velocity measurement
        GeometricUncertainty m_unc;

    public:
        //API Constructor: AidingMeasurementVelocity
        //  Constructs an AidingMeasurementVelocity object with default values
        AidingMeasurementVelocity() : AidingMeasurementInput() {}

        //API Constructor: AidingMeasurementVelocity
        //  Constructs an AidingMeasurementVelocity object with the specified reference frame from the <MipFieldValues> parameter list returned from the device.
        //
        //Parameters:
        //  referenceFrame - the <PositionVelocityReferenceFrame> of this measurement
        //  values - the <MipFieldValues> parameter list to build this object from
        AidingMeasurementVelocity(PositionVelocityReferenceFrame referenceFrame, const MipFieldValues& values);

        ~AidingMeasurementVelocity() {}

    protected:
        //Function: parseMipFieldValues
        //  Populates measurement values based on the <MipFieldValues> parameter list.
        //
        //Parameters:
        //  values - <MipFieldValues> parameter list
        virtual void parseMipFieldValues(const MipFieldValues& values) override;

        //Function: appendMipFieldValues
        //  Appends the velocity measurement info to the provided <MipFieldValues> parameter list.
        //
        //Parameters:
        //  values - the <MipFieldValues> parameter list to append to
        virtual void appendMipFieldValues(MipFieldValues& values) const override;

    public:
        //API Function: velocity
        //  Gets the <Velocity> measurement values.
        //
        //Returns:
        //  <Velocity> - measurement values
        Velocity velocity() const { return m_velocity; }

        //API Function: velocity
        //  Sets the <Velocity> measurement values.
        //
        //Parameters:
        //  vel - the <Velocity> values to set
        void velocity(Velocity vel) { m_velocity = vel; }

        //API Function: uncertainty
        //  Get the measurment uncertainty
        //
        //Returns:
        //  <GeometricUncertainty> - the uncertainty of the velocity measurement
        GeometricUncertainty uncertainty() const { return m_unc; }

        //API Function: uncertainty
        //  Sets the measurement uncertainty.
        //
        //Parameters:
        //  uncertainty - the <GeometricUncertainty> of the measurement
        void uncertainty(GeometricUncertainty uncertainty) { m_unc = uncertainty; }

        //API Function: referenceFrame
        //  Get the <PositionVelocityReferenceFrame> of this velocity measurement.
        //
        //Returns:
        //  <PositionVelocityReferenceFrame> - reference frame ID of the measurement
        PositionVelocityReferenceFrame referenceFrame() const { return m_velocity.referenceFrame; }

        //API Function: referenceFrame
        //  Set the <PositionVelocityReferenceFrame> of this measurement.
        //
        //Parameters:
        //  frame - the <PositionVelocityReferenceFrame> to set
        void referenceFrame(PositionVelocityReferenceFrame frame) { m_velocity.referenceFrame = m_unc.referenceFrame = frame; }

        //API Function: valid
        //  Checks whether the specified value is valid.
        //
        //Parameters:
        //  <ValidFlags> value bitmask
        //
        //Returns:
        //  bool - true if valid
        bool valid(ValidFlags val) const { return m_validFlags.checkBit(static_cast<uint8>(val)); }

        //API Function: valid
        //  Sets the validity of the specified value.
        //
        //Parameters:
        //  val - <ValidFlags> value bitmask
        //  valid - bool indicating whether the value is valid
        void valid(ValidFlags val, bool valid) { m_validFlags.set(val, valid ? 1 : 0); }
    };

    //API Class: AidingMeasurementHeading
    //  A class that represents heading aiding measurement inputs. Extends <AidingMeasurementInput>.
    class AidingMeasurementHeading : public AidingMeasurementInput
    {
    protected:
        //Variable: m_heading
        //  The heading measurement
        float m_heading;

        //Variable: m_unc
        //  The heading uncertainty
        float m_unc;

    public:
        //API Constructor: AidingMeasurementHeading
        //  Constructs an AidingMeasurementHeading object with default values.
        AidingMeasurementHeading() : AidingMeasurementInput() {}

        //API Constructor: AidingMeasurmentHeading
        //  Constructs an AidingMeasurementHeading object from the provided <MipFieldValues> parameter list.
        //
        //Parameters:
        //  values - <MipFieldValues> parameter list
        AidingMeasurementHeading(const MipFieldValues& values);

        ~AidingMeasurementHeading() {}

    protected:
        //Function: parseMipFieldValues
        //  Populates measurement values based on the <MipFieldValues> parameter list.
        //
        //Parameters:
        //  values - <MipFieldValues> parameter list
        virtual void parseMipFieldValues(const MipFieldValues& values) override;

        //Function: appendMipFieldValues
        //  Appends the heading measurement info to the provided <MipFieldValues> parameter list.
        //
        //Parameters:
        //  values - the <MipFieldValues> parameter list to append to
        virtual void appendMipFieldValues(MipFieldValues& values) const override;

    public:
        //API Function: heading
        //  Get the heading measurement value.
        //
        //Returns:
        //  float - the heading measurement value
        float heading() const { return m_heading; }

        //API Function: heading
        //  Sets the heading measurement value.
        //
        //Parameters:
        //  heading - float heading measurement
        void heading(float heading) { m_heading = heading; }

        //API Function: uncertainty
        //  Get the heading measurement uncertainty.
        //
        //Returns:
        //  float - heading measurement uncertainty
        float uncertainty() const { return m_unc; }

        //API Function: uncertainty
        //  Set the heading measurement uncertainty.
        //
        //Parameters:
        //  uncertainty - float measurement uncertainty
        void uncertainty(float uncertainty) { m_unc = uncertainty; }

        //API Function: valid
        //  Check whether the heading measurement is valid
        //
        //Returns:
        //  bool - true if valid
        bool valid() const { return m_validFlags.value() > 0; }

        //API Function: valid
        //  Set the validity of the heading measurement.
        //
        //Parameters:
        //  valid - bool, true if valid
        void valid(bool valid) { m_validFlags.value(valid ? 1 : 0); }
    };

    //API Struct: GnssReceiverInfo
    //  Maps GNSS Receiver ID to the <MipTypes::DataClass> it outputs to
    struct GnssReceiverInfo
    {
        //API Constant: INFO_NOT_FOUND
        //  String value assigned when the target value was unable to be found in the full description field.
        //
        //  INFO_NOT_FOUND - "Not Found"
        static const std::string INFO_NOT_FOUND;

        //API Constructor: GnssReceiverInfo
        //  Constructs GnssReceiverInfo object with default values
        GnssReceiverInfo();

        //API Constructor: GnssReceiverInfo
        //  Constructs GnssReceiverInfo object with specified values
        GnssReceiverInfo(uint8 recId, MipTypes::DataClass target, std::string desc);

        //API Variable: id
        //  Receiver ID
        uint8 id;

        //API Variable: targetDataClass
        //  MIP data class associated with this receiver
        MipTypes::DataClass targetDataClass;

        //API Variable: description
        //  ASCII description of receiver
        std::string description;

        //API Variable: module
        //  ASCII name of the receiver module
        std::string module;

        //API Variable: fwId
        //  ASCII name of the receiver firmware identifier
        std::string fwId;

        //API Variable: fwVersion
        //  Firmware version of the receiver module
        Version fwVersion;
    };

    //API Typedef: GnssReceivers
    //  A vector of <GnssReceiverInfo>
    typedef std::vector<GnssReceiverInfo> GnssReceivers;

    //API Struct: DeviceCommPort
    //  Stores info related to device comm ports (id, type)
    struct DeviceCommPort
    {
        //API Enum: Type
        //  Available comm port type definitions
        //      PRIMARY - 0
        //      AUX     - 1
        enum Type
        {
            PRIMARY = 0,
            AUX     = 1
        };

        //API Constructor: DeviceCommPort
        //  Constructs DeviceCommPort object with default values
        DeviceCommPort() {};

        //API Constructor: DeviceCommPort
        //  Constructs DeviceCommPort object with specified values
        DeviceCommPort(Type portType, uint8 portId) :
            type(portType),
            id(portId)
        {};

        //API Variable: type
        // Port type (primary, aux, etc.)
        Type type;

        //API Variable: id
        // Port ID
        uint8 id;
    };

    typedef std::vector<DeviceCommPort> CommPortInfo;

    //API Struct: EventTypeInfo
    //  Information about event trigger or action types
    struct EventTypeInfo
    {
        //API Constructor: EventTypeInfo
        //  Default constructor
        EventTypeInfo() : type(0), maxInstances(0) {}

        //API Constructor: EventTypeInfo
        EventTypeInfo(const uint8 type, const uint8 maxInstances) :
            type(type),
            maxInstances(maxInstances)
        { }

        //API Variable: type
        //  The event type based on <EventSupportInfo::Query>
        //
        //  - <EventSupportInfo::Query::TRIGGERS> = <EventTriggerConfiguration::Type>
        //  - <EventSupportInfo::Query::ACTIONS>  = <EventActionConfiguration::Type>
        uint8 type;

        //API Variable: maxInstances
        //  Maximum supported instances for the type
        uint8 maxInstances;
    };

    //API Typedef: EventTypes
    //  A vector of <EventTypeInfo>
    typedef std::vector<EventTypeInfo> EventTypes;

    //API Struct: EventSupportInfo
    struct EventSupportInfo
    {
        //API Enum: Query
        //  What type of information to retrieve
        //
        //  TRIGGERS  - 0x01 - Query the supported trigger types and max count for each
        //  ACTIONS   - 0x02 - Query the supported action types and max count for each
        enum Query
        {
            TRIGGERS = 0x01, // Query the supported trigger types and max count for each
            ACTIONS  = 0x02  // Query the supported action types and max count for each
        };

        //API Variable: query
        //  Type of information 
        Query query;

        //API Variable: maxInstances
        //  Maximum number of supported triggers/actions
        uint8 maxInstances;

        //API Variable: entries
        //  Event info
        EventTypes entries;
    };

    // API Class: SensorRange
    // An object representing a configurable sensor range option
    class SensorRange
    {
    public:
        //API Enum: Type
        //  Sensor and unit identifiers for configurable Sensor Range command (0x0C,0x52)
        //      ALL          - 0x00 - All (save as startup, load startup, reset to default only)
        //      ACCEL_MS2    - 0x01 - Accelerometer in m/s^2
        //      GYRO_DPS     - 0x02 - Gyroscope in degrees per second
        //      MAG_MG       - 0x03 - Magnetometer in mG
        //      PRESSURE_HPA - 0x04 - Pressure in hPa
        enum Type
        {
            ALL = 0x00,
            ACCEL_G = 0x01,
            GYRO_DPS = 0x02,
            MAG_GAUSS = 0x03,
            PRESSURE_HPA = 0x04
        };

    private:
        //API Variable: type
        // The SensorRange::Type of this range
        Type m_type;

        //API Variable: range
        // This will only be set and valid if read from <SupportedSensorRanges> object
        // Default: -1 (invalid)
        float m_range = -1.0f;

        //API Variable: id
        // The index ID of this range according to device manual
        uint8 m_id;

    private:
        friend class MipNode_Impl;
        friend class InertialNode;

        //Private Constructor: SensorRange
        // Construct a SensorRange object with specified range
        // This object should not be constructed directly by users
        //
        //Parameters:
        //  type - SensorRange::Type of this range
        //  range - Range value
        SensorRange(Type rangeType, uint8 index, float rangeValue = -1.0f) :
            m_type(rangeType),
            m_range(rangeValue),
            m_id(index)
        {};

    public:
        // needed for SWIG - should not be used
        SensorRange() {};

        //API Function: type
        // The SensorRange::Type of this range
        Type type() const { return m_type; };

        //API Function: range
        // This will only be set and valid if read from <SupportedSensorRanges> object
        float range() const { return m_range; };

        //API Function: id
        // The index ID of this range according to device manual
        uint8 id() const { return m_id; };
    };

    //API Typedef: SensorRanges
    //  A vector of <SensorRange> values
    typedef std::vector<SensorRange> SensorRanges;

    //API Typedef: SensorRangeOptions
    //  A collection of <SensorRange::Type> values mapped to associated <SensorRange> objects
    typedef std::map<SensorRange::Type, SensorRanges> SensorRangeOptions;

    //API Class: SupportedSensorRanges
    // Structure to hold all info for looking up supported sensor ranges for a device
    class SupportedSensorRanges
    {
    private:
        // only MipNode_Impl can populate supported options
        friend class MipNode_Impl;
        SensorRangeOptions m_options;

    public:
        SupportedSensorRanges() {};

        //API Function: options
        // Get the supported sensor range options
        //
        // Returns:
        //  <SensorRangeOptions> - the supported options
        const SensorRangeOptions options() const { return m_options; };

        //API Function: lookupRecommended
        // Lookup the supported option of the specified type that is closest to but also incorporates the specified range.
        // Ex:
        //  specified range: Accel_G, 5
        //  supported accel ranges: 4G, 8G, 16G
        //  returns: 8G because it is the closest supported option where 5G will not overrun the range
        //
        // Parameters:
        //  type - <SensorRange::Type> type of range to lookup
        //  range - Float range value to find
        //
        // Returns:
        //  <SensorRange> - The closest supported range to the specified value
        SensorRange lookupRecommended(SensorRange::Type type, float range) const;
    };
}
