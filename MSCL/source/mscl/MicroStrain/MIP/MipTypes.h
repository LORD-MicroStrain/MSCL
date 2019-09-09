/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "mscl/Types.h"

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
    enum DataClass
    {
        CLASS_AHRS_IMU      = 0x80,
        CLASS_GNSS          = 0x81,
        CLASS_ESTFILTER     = 0x82,
        CLASS_DISPLACEMENT  = 0x90
    };

    //Enums: FunctionSelector
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
        USE_NEW_SETTINGS = 0x01,
        READ_BACK_CURRENT_SETTINGS = 0x02,
        SAVE_CURRENT_SETTINGS = 0x03,
        LOAD_STARTUP_SETTINGS = 0x04,
        RESET_TO_DEFAULT = 0x05,
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
        ENABLED = 1
    };

    //API Enums: TimeFrame
    //    The enums to represent different time categories.
    //
    //      TIME_FRAME_WEEKS    - 0x00
    //      TIME_FRAME_SECONDS  - 0x01
    enum TimeFrame 
    {
        TIME_FRAME_WEEKS = 0,
        TIME_FRAME_SECONDS = 1
    };

    //Enums: Command
    //    The enums for all of the different MIP commands.
    //
    //  CMD_PING                                    - 0x0101    - Ping
    //  CMD_SET_IDLE                                - 0x0102    - Set to Idle
    //  CMD_GET_DEVICE_INFO                         - 0x0103    - Get Device Information
    //  CMD_GET_DESCRIPTOR_SETS                     - 0x0104    - Get Device Descriptor Sets
    //  CMD_BUILT_IN_TEST                           - 0x0105    - Device Build-In Test
    //  CMD_RESUME                                  - 0x0106    - Resume
    //  CMD_GET_EXT_DESCRIPTOR_SETS                 - 0x0107    - Get Extedned Device Descriptor Sets
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
    //  CMD_CONTINUOUS_DATA_STREAM                  - 0x0C11    - Enable/Disable Device Continuous Data Stream
    //  CMD_RAW_RTCM_2_3_MESSAGE                    - 0x0C20    - Raw RTCM 2.3 Message
    //  CMD_GNSS_CONSTELLATION_SETTINGS             - 0x0C21    - GNSS Constellation Settings
    //  CMD_GNSS_SBAS_SETTINGS                      - 0x0C22    - GNSS SBAS Settings
    //  CMD_GNSS_ASSIST_FIX_CONTROL                 - 0x0C23    - GNSS Assisted Fix Control
    //  CMD_GNSS_ASSIST_TIME_UPDATE                 - 0x0C24    - GNSS Assisted Time Update
    //  CMD_SAVE_STARTUP_SETTINGS                   - 0x0C30    - Device Startup Settings
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
    //  CMD_LOWPASS_FILTER_SETTINGS                 - 0x0C50    - Advanced Low-Pass Filter Settings
    //  CMD_COMPLEMENTARY_FILTER_SETTINGS           - 0x0C51    - Complementary Filter Settings
    //  CMD_DATA_STREAM_FORMAT                      - 0x0C60    - Device Data Stream Format
    //  CMD_POWER_STATES                            - 0x0C61    - Device Power States
    //  CMD_GPS_STARTUP_SETTINGS                    - 0x0C62    - Save/Restore Advanced GPS Startup Settings
    //  CMD_DEVICE_STATUS                           - 0x0C64    - Device Status
    //  CMD_EF_RESET_FILTER                         - 0x0D01    - Estimation Filter - Reset Filter
    //  CMD_EF_INIT_ATTITUDE                        - 0x0D02    - Estimation Filter - Set Initial Attitude
    //  CMD_EF_INIT_HEADING                         - 0x0D03    - Estimation Filter - Set Initial Heading
    //  CMD_EF_INIT_ATTITUDE_FROM_AHRS              - 0x0D04    - Estimation Filter - Set Initial Attitude from AHRS
    //  CMD_EF_VEHIC_DYNAMICS_MODE                  - 0x0D10    - Estimation Filter - Vehicle Dynamics Mode
    //  CMD_EF_SENS_VEHIC_FRAME_TRANS               - 0x0D11    - Estimation Filter - Sensor to Vehicle Frame Transformation
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
    //  CMD_COMMUNICATION_MODE                      - 0x7F10    - Communication Mode
    //  CMD_HARDWARE_CTRL                           - 0x7F11    - Hardware Control
    //  CMD_GET_ANALOG_DISPLACEMENT_CALS            - 0x1101    - Get Analog Output to Displacement Slope and Offset
    //  CMD_DISPLACEMENT_OUTPUT_RATE                - 0x1102    - Displacement Output Data Rate
    //  CMD_DISPLACEMENT_DEVICE_TIME                - 0x1104    - Displacement Device Time
    enum Command
    {
        CMD_PING                                    = 0x0101,
        CMD_SET_IDLE                                = 0x0102,
        CMD_GET_DEVICE_INFO                         = 0x0103,
        CMD_GET_DESCRIPTOR_SETS                     = 0x0104,
        CMD_BUILT_IN_TEST                           = 0x0105,
        CMD_RESUME                                  = 0x0106,
        CMD_GET_EXT_DESCRIPTOR_SETS                 = 0x0107,
        CMD_GPS_TIME_UPDATE                         = 0x0172,
        CMD_RESET                                   = 0x017E,
        CMD_POLL_SENSOR_DATA                        = 0x0C01,
        CMD_POLL_GNSS_DATA                          = 0x0C02,
        CMD_POLL_EF_DATA                            = 0x0C03,
        CMD_GET_SENSOR_RATE_BASE                    = 0x0C06,
        CMD_GET_GNSS_RATE_BASE                      = 0x0C07,
        CMD_GET_EF_RATE_BASE                        = 0x0C0B,
        CMD_SENSOR_MESSAGE_FORMAT                   = 0x0C08,
        CMD_GNSS_MESSAGE_FORMAT                     = 0x0C09,
        CMD_EF_MESSAGE_FORMAT                       = 0x0C0A,
        CMD_CONTINUOUS_DATA_STREAM                  = 0x0C11,
        CMD_RAW_RTCM_2_3_MESSAGE                    = 0x0C20,
        CMD_GNSS_CONSTELLATION_SETTINGS             = 0x0C21,
        CMD_GNSS_SBAS_SETTINGS                      = 0x0C22,
        CMD_GNSS_ASSIST_FIX_CONTROL                 = 0x0C23,
        CMD_GNSS_ASSIST_TIME_UPDATE                 = 0x0C24,
        CMD_SAVE_STARTUP_SETTINGS                   = 0x0C30,
        CMD_GPS_DYNAMICS_MODE                       = 0x0C34,
        CMD_SENSOR_SIG_COND_SETTINGS                = 0x0C35,
        CMD_SENSOR_TIMESTAMP                        = 0x0C36,
        CMD_ACCEL_BIAS                              = 0x0C37,
        CMD_GYRO_BIAS                               = 0x0C38,
        CMD_CAP_GYRO_BIAS                           = 0x0C39,
        CMD_MAG_HARD_IRON_OFFSET                    = 0x0C3A,
        CMD_MAG_SOFT_IRON_MATRIX                    = 0x0C3B,
        CMD_CF_REALIGN_UP                           = 0x0C3C,
        CMD_CF_REALIGN_NORTH                        = 0x0C3D,
        CMD_CONING_SCULLING                         = 0x0C3E,
        CMD_UART_BAUD_RATE                          = 0x0C40,
        CMD_LOWPASS_FILTER_SETTINGS                 = 0x0C50,
        CMD_COMPLEMENTARY_FILTER_SETTINGS           = 0x0C51,
        CMD_DATA_STREAM_FORMAT                      = 0x0C60,
        CMD_POWER_STATES                            = 0x0C61,
        CMD_GPS_STARTUP_SETTINGS                    = 0x0C62,
        CMD_DEVICE_STATUS                           = 0x0C64,
        CMD_EF_RESET_FILTER                         = 0x0D01,
        CMD_EF_INIT_ATTITUDE                        = 0x0D02,
        CMD_EF_INIT_HEADING                         = 0x0D03,
        CMD_EF_INIT_ATTITUDE_FROM_AHRS              = 0x0D04,
        CMD_EF_VEHIC_DYNAMICS_MODE                  = 0x0D10,
        CMD_EF_SENS_VEHIC_FRAME_TRANS               = 0x0D11,
        CMD_EF_SENS_VEHIC_FRAME_OFFSET              = 0x0D12,
        CMD_EF_ANTENNA_OFFSET                       = 0x0D13,
        CMD_EF_BIAS_EST_CTRL                        = 0x0D14,
        CMD_EF_GNSS_SRC_CTRL                        = 0x0D15,
        CMD_EF_EXTERN_GNSS_UPDATE                   = 0x0D16,
        CMD_EF_EXTERN_HEADING_UPDATE                = 0x0D17,
        CMD_EF_HEADING_UPDATE_CTRL                  = 0x0D18,
        CMD_EF_AUTO_INIT_CTRL                       = 0x0D19,
        CMD_EF_ACCEL_WHT_NSE_STD_DEV                = 0x0D1A,
        CMD_EF_GYRO_WHT_NSE_STD_DEV                 = 0x0D1B,
        CMD_EF_ACCEL_BIAS_MODEL_PARAMS              = 0x0D1C,
        CMD_EF_GYRO_BIAS_MODEL_PARAMS               = 0x0D1D,
        CMD_EF_ZERO_VEL_UPDATE_CTRL                 = 0x0D1E,
        CMD_EF_EXT_HEADING_UPDATE_TS                = 0x0D1F,
        CMD_EF_ZERO_ANG_RATE_UPDATE_CTRL            = 0x0D20,
        CMD_EF_TARE_ORIENT                          = 0x0D21,
        CMD_EF_CMDED_ZERO_VEL_UPDATE                = 0x0D22,
        CMD_EF_CMDED_ZERO_ANG_RATE_UPDATE           = 0x0D23,
        CMD_EF_SET_REF_POSITION                     = 0x0D26,
        CMD_EF_MAG_CAPTURE_AUTO_CAL                 = 0x0D27,
        CMD_EF_GRAVITY_NOISE_STD_DEV                = 0x0D28,
        CMD_EF_PRESS_ALT_NOISE_STD_DEV              = 0x0D29,
        CMD_EF_GRAVITY_NOISE_MINIMUM                = 0x0D2A,
        CMD_EF_HARD_IRON_OFFSET_PROCESS_NOISE       = 0x0D2B,
        CMD_EF_SOFT_IRON_OFFSET_PROCESS_NOISE       = 0x0D2C,
        CMD_EF_ENABLE_DISABLE_MEASUREMENTS          = 0x0D41,
        CMD_EF_MAG_NOISE_STD_DEV                    = 0x0D42,
        CMD_EF_DECLINATION_SRC                      = 0x0D43,
        CMD_EF_GRAV_MAGNITUDE_ERR_ADAPT_MEASURE     = 0x0D44,
        CMD_EF_MAG_MAGNITUDE_ERR_ADAPT_MEASURE      = 0x0D45,
        CMD_EF_MAG_DIP_ANGLE_ERR_ADAPT_MEASURE      = 0x0D46,
        CMD_EF_ALTITUDE_AID_CTRL                    = 0x0D47,
        CMD_EF_PITCH_ROLL_AID_CTRL                  = 0x0D4B,
        CMD_EF_INCLINATION_SRC                      = 0x0D4C,
        CMD_EF_FIELD_MAGNITUDE_SRC                  = 0x0D4D,
        CMD_COMMUNICATION_MODE                      = 0x7F10,
        CMD_HARDWARE_CTRL                           = 0x7F11,
        CMD_GET_ANALOG_DISPLACEMENT_CALS            = 0x1101,
        CMD_DISPLACEMENT_OUTPUT_RATE                = 0x1102,
        CMD_DISPLACEMENT_DEVICE_TIME                = 0x1104
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
    //  CH_FIELD_SENSOR_STABILIZED_ACCEL_VEC                    - 0x8011    - Stabliized Accel Vector (Up)
    //  CH_FIELD_SENSOR_GPS_CORRELATION_TIMESTAMP               - 0x8012    - GPS Correlation Timestamp
    //  CH_FIELD_SENSOR_SCALED_AMBIENT_PRESSURE                 - 0x8017    - Scaled Ambient Pressure
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
    //  CH_FIELD_ESTFILTER_COMPENSATED_ACCEL                    - 0x821C    - Compensated Accel
    //  CH_FIELD_ESTFILTER_STD_ATMOSPHERE_MODEL                 - 0x8220    - Standard Atmosphere Model
    //  CH_FIELD_ESTFILTER_PRESSURE_ALTITUDE                    - 0x8221    - Estimated Pressure Altitude
    //  CH_FIELD_ESTFILTER_MAG_AUTO_HARD_IRON_OFFSET            - 0x8225    - Mag Auto Hard Iron Offset
    //  CH_FIELD_ESTFILTER_MAG_AUTO_SOFT_IRON_MATRIX            - 0x8226    - Mag Auto Soft Iron Matrix
    //  CH_FIELD_ESTFILTER_MAG_AUTO_HARD_IRON_OFFSET_UNCERT     - 0x8228    - Mag Auto Hard Iron Offset Uncertainty
    //  CH_FIELD_ESTFILTER_MAG_AUTO_SOFT_IRON_MATRIX_UNCERT     - 0x8229    - Mag Auto Soft Iron Matrix Uncertainty
    //  CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION              - 0x8230    - GNSS Antenna Offset Correction
    //  CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION_UNCERT       - 0x8231    - GNSS Antenna Offset Correction Uncertainty
    //  CH_FIELD_DISP_POSITION                                  - 0x9001    - Position
    //  CH_FIELD_DISP_RAW_POSITION                              - 0x9002    - Raw Position
    //  CH_FIELD_DISP_DISPLACEMENT_TS                           - 0x9004    - Displacement Device Timestamp
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
        CH_FIELD_SENSOR_SCALED_AMBIENT_PRESSURE                 = 0x8017,
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
        CH_FIELD_ESTFILTER_COMPENSATED_ACCEL                    = 0x821C,
        CH_FIELD_ESTFILTER_STD_ATMOSPHERE_MODEL                 = 0x8220,
        CH_FIELD_ESTFILTER_PRESSURE_ALTITUDE                    = 0x8221,
        CH_FIELD_ESTFILTER_MAG_AUTO_HARD_IRON_OFFSET            = 0x8225,
        CH_FIELD_ESTFILTER_MAG_AUTO_SOFT_IRON_MATRIX            = 0x8226,
        CH_FIELD_ESTFILTER_MAG_AUTO_HARD_IRON_OFFSET_UNCERT     = 0x8228,
        CH_FIELD_ESTFILTER_MAG_AUTO_SOFT_IRON_MATRIX_UNCERT     = 0x8229,
        CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION              = 0x8230,
        CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION_UNCERT       = 0x8231,
        CH_FIELD_DISP_DISPLACEMENT_RAW                          = 0x9001,
        CH_FIELD_DISP_DISPLACEMENT_MM                           = 0x9002,
        CH_FIELD_DISP_DISPLACEMENT_TS                           = 0x9004
    };

    //====================================================================================================
    //API Enums: ChannelQualifier
    //    The enums for different MIP Channel Qualifiers.
    //    This combined with the <ChannelField> produces a unique identifier for each individual channel that is collected.
    //
    //    CH_UNKNOWN                    - 0 - Unknown Channel
    //    CH_X                          - 1 - X
    //    CH_Y                          - 2 - Y
    //    CH_Z                          - 3 - Z
    //    CH_MATRIX                     - 4 - Matrix
    //    CH_QUATERNION                 - 5 - Quaternion
    //    CH_ROLL                       - 6 - Roll
    //    CH_PITCH                      - 7 - Pitch
    //    CH_YAW                        - 8 - Yaw
    //    CH_TICK                       - 9 - Tick
    //    CH_TIMESTAMP                  - 10 - Timestamp
    //    CH_STATUS                     - 11 - Status
    //    CH_TIME_OF_WEEK               - 12 - Time of Week
    //    CH_WEEK_NUMBER                - 13 - Week Number
    //    CH_LATITUDE                   - 14 - Latitude
    //    CH_LONGITUDE                  - 15 - Longitude
    //    CH_HEIGHT_ABOVE_ELLIPSOID     - 16 - Height Above Ellipsoid
    //    CH_HEIGHT_ABOVE_MSL           - 17 - Height Above MSL
    //    CH_HORIZONTAL_ACCURACY        - 18 - Horizontal Accuracy
    //    CH_VERTICAL_ACCURACY          - 19 - Vertical Accuracy
    //    CH_POSITION_ACCURACY          - 20 - Position Accuracy
    //    CH_NORTH                      - 21 - North
    //    CH_EAST                       - 22 - East
    //    CH_DOWN                       - 23 - Down
    //    CH_SPEED                      - 24 - Speed
    //    CH_GROUND_SPEED               - 25 - Ground Speed
    //    CH_HEADING                    - 26 - Heading
    //    CH_SPEED_ACCURACY             - 27 - Speed Accuracy
    //    CH_HEADING_ACCURACY           - 28 - Heading Accuracy
    //    CH_VELOCITY_ACCURACY          - 29 - Velocity Accuracy
    //    CH_GEOMETRIC_DOP              - 30 - Geometric DOP
    //    CH_POSITION_DOP               - 31 - Position DOP
    //    CH_HORIZONTAL_DOP             - 32 - Horizontal DOP
    //    CH_VERTICAL_DOP               - 33 - Vertical DOP
    //    CH_TIME_DOP                   - 34 - Time DOP
    //    CH_NORTHING_DOP               - 35 - Northing DOP
    //    CH_EASTING_DOP                - 36 - Easting DOP
    //    CH_FLAGS                      - 37 - Flags
    //    CH_BIAS                       - 38 - Bias
    //    CH_DRIFT                      - 39 - Drift
    //    CH_ACCURACY_ESTIMATE          - 40 - Accuracy Estimate
    //    CH_FIX_TYPE                   - 41 - Fix Type
    //    CH_SV_COUNT                   - 42 - Number of Space Vehicles used for solution
    //    CH_CHANNEL                    - 43 - Channel Number
    //    CH_ID                         - 44 - ID Number
    //    CH_CARRIER_TO_NOISE_RATIO     - 45 - Carrier to Noise Ratio
    //    CH_AZIMUTH                    - 46 - Azimuth
    //    CH_ELEVATION                  - 47 - Elevation
    //    CH_SENSOR_STATE               - 48 - Sensor State
    //    CH_ANTENNA_STATE              - 49 - Antenna State
    //    CH_ANTENNA_POWER              - 50 - Antenna Power
    //    CH_FILTER_STATE               - 51 - Filter State
    //    CH_DYNAMICS_MODE              - 52 - Dynamics Mode
    //    CH_MAGNITUDE                  - 53 - Magnitude
    //    CH_HEADING_UNCERTAINTY        - 54 - Heading Uncertainty
    //    CH_SOURCE                     - 55 - Source
    //    CH_INCLINATION                - 56 - Inclination
    //    CH_DECLINATION                - 57 - Declination
    //    CH_PRESSURE                   - 58 - Pressure
    //    CH_AGE                        - 59 - Age
    //    CH_NUM_CHANNELS               - 60 - Number of Channels
    //    CH_CORRECTION                 - 61 - Correction
    //    CH_RATE_CORRECTION            - 62 - Rate Correction
    //    CH_GEOMETRIC_ALTITUDE         - 63 - Geometric Altitude
    //    CH_GEOPOTENTIAL_ALTITUDE      - 64 - Geopotential Altitude
    //    CH_TEMPERATURE                - 65 - Temperature
    //    CH_DENSITY                    - 66 - Density
    //    CH_ALTITUDE                   - 67 - Altitude
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
        CH_DISPLACEMENT                 = 68
    };

    //API Typedefs:
    //  MipChannelFields    - A vector of <ChannelField> enums.
    //  MipCommands         - A vector of <Command> enums.
    typedef std::vector<ChannelField> MipChannelFields;
    typedef std::vector<Command> MipCommands;

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

private:
    //Const: CHANNEL_NAMES
    //    An unordered_map mapping each <ChannelId> to its respective name (universal SensorCloud name).
    static const std::unordered_map<ChannelId, std::string, ChannelIdHash> CHANNEL_NAMES;

};

//API Struct: MipCommandBytes
//    Contains an <Command> id and a <BytesCollection> vector to store the actual bytes to send to the device for that command.
struct MipCommandBytes
{
    MipTypes::Command id;
    BytesCollection commands;
    bool responseSuccess; // true by default - set to false on NACK

    MipCommandBytes() :
        responseSuccess(false) {}

    MipCommandBytes(MipTypes::Command _id) :
        id(_id),
        responseSuccess(false) {}

    MipCommandBytes(MipTypes::Command _id, Bytes _cmd) :
        id(_id),
        commands({ _cmd }),
        responseSuccess(false) {}

    MipCommandBytes(MipTypes::Command _id, BytesCollection _cmds) :
        id(_id),
        commands(_cmds),
        responseSuccess(false) {}

    void add(Bytes cmd) { commands.push_back(cmd); }
};

//API Typedef: MipCommandSet
//      A vector of <MipCommandBytes>
typedef std::vector<MipCommandBytes> MipCommandSet;

}