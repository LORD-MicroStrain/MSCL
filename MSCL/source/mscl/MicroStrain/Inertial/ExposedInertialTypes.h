#pragma once

#include "mscl/Types.h"
#include "mscl/MicroStrain/Matrix.h"
#include "mscl/MicroStrain/Bitfield.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/Inertial/EulerAngles.h"
#include <array>
#include <boost/optional.hpp>
#include "mscl/Exceptions.h"


namespace mscl
{
    struct InertialTypes
    {
        //API Enum: VehicleModeType
        //    The enum for the different data descriptors.
        //
        //  PORTABLE_VEHICLE = 0x01
        //  AUTOMOTIVE_VEHICLE = 0x02
        //  AIRBORNE_VEHICLE = 0x03
        //  AIRBORNE_HIGH_G_VEHICLE = 0x4
        enum VehicleModeType
        {
            PORTABLE_VEHICLE = 0x01,
            AUTOMOTIVE_VEHICLE = 0x02,
            AIRBORNE_VEHICLE = 0x03,
            AIRBORNE_HIGH_G_VEHICLE = 0x4
        };

        //API Enum: GPSDynamicsMode
        //    The enum for possible GPS dynamics modes.
        //
        //  GPS_PORTABLE = 0x00,
        //  GPS_STATIONARY = 0x02,
        //  GPS_PEDESTRIAN = 0x03,
        //  GPS_AUTOMOTIVE = 0x04,
        //  GPS_SEA = 0x05,
        //  GPS_AIRBORNE_1G = 0x06,
        //  GPS_AIRBORNE_2G = 0x07,
        //  GPS_AIRBORNE_4G = 0x08
        enum GPSDynamicsMode
        {
            GPS_PORTABLE = 0x00,
            GPS_STATIONARY = 0x02,
            GPS_PEDESTRIAN = 0x03,
            GPS_AUTOMOTIVE = 0x04,
            GPS_SEA = 0x05,
            GPS_AIRBORNE_1G = 0x06,
            GPS_AIRBORNE_2G = 0x07,
            GPS_AIRBORNE_4G = 0x08
        };

        //API Enum: AxisBitfieldValues
        //    The axis bitfield values for Tare Orientation.
        //
        //  RESET_ALL_AXIS = 0x00,
        //  TARE_ROLL_AXIS = 0x01,
        //  TARE_PITCH_AXIS = 0x02,
        //  TARE_YAW_AXIS = 0x04
        enum AxisBitfieldValues
        {
            RESET_ALL_AXIS = 0x00,
            TARE_ROLL_AXIS = 0x01,
            TARE_PITCH_AXIS = 0x02,
            TARE_YAW_AXIS = 0x04
        };

        //API Enum: GNSS_Source
        //    Dictates whether GNSS source is internal or external.
        //
        //  INTERNAL_GNSS = 0x01
        //  EXTERNAL_GNSS = 0x02
        enum GNSS_Source
        {
            INTERNAL_GNSS = 0x01,
            EXTERNAL_GNSS = 0x02
        };

        //============================================================================================================
        //API Enum: GnssFixFlags
        //    The GNSS Fix Flags in the GPS Fix Information field
        //
        //    FIX_SBAS_CORRECTIONS      - 0x0001    - SBAS Corrections Used
        //    FIX_DGNSS_CORRECTIONS     - 0x0002    - Differential (DGNSS) Corrections Used
        //============================================================================================================
        enum GnssFixFlags
        {
            FIX_SBAS_CORRECTIONS = 0x0001,
            FIX_DGNSS_CORRECTIONS = 0x0002
        };

        //============================================================================================================
        //API Enum: GnssFixType
        //    The GNSS Fix Types with the GPS Fix Information field
        //
        //    FIXTYPE_3D             - 0x00    - 3D Fix
        //    FIXTYPE_2D             - 0x01    - 2D Fix
        //    FIXTYPE_TIMEONLY       - 0x02    - Time Only
        //    FIXTYPE_NONE           - 0x03    - None
        //    FIXTYPE_INVALID        - 0x04    - Invalid
		//    FIXTYPE_RTK_FLOAT      - 0x05    - RTK Float
		//    FIXTYPE_RTK_FIXED      - 0x06    - RTK Fixed
		//
		//============================================================================================================
        enum GnssFixType
        {
            FIXTYPE_3D = 0x00,
            FIXTYPE_2D = 0x01,
            FIXTYPE_TIMEONLY = 0x02,
            FIXTYPE_NONE = 0x03,
            FIXTYPE_INVALID = 0x04,
			FIXTYPE_RTK_FLOAT = 0x05,
			FIXTYPE_RTK_FIXED = 0x06,
        };

        //============================================================================================================
        //API Enum: DualAntennaFixType
        //    The GNSS Dual Antenna Fix Types in the Estimation Filter GNSS Dual Antenna Status field
        //
        //    FIXTYPE_DUAL_ANTENNA_NONE       - 0x00    - None
        //    FIXTYPE_DUAL_ANTENNA_FLOAT      - 0x01    - Dual Antenna Float
        //    FIXTYPE_DUAL_ANTENNA_FIXED      - 0x02    - Dual Antenna Fixed
        //
        //============================================================================================================
        enum DualAntennaFixType
        {
            FIXTYPE_DUAL_ANTENNA_NONE = 0x00,
            FIXTYPE_DUAL_ANTENNA_FLOAT = 0x01,
            FIXTYPE_DUAL_ANTENNA_FIXED = 0x02,
        };

        //============================================================================================================
        //API Enum: DualAntennaStatusFlags
        //    The bitmask definition for GNSS Dual Antenna Status in the Estimation Filter GNSS Dual Antenna Status field
        //
        //    DATA_VALID_REC_1      - 0x01    - Receiver 1 Data Valid - 0000 0001
        //    DATA_VALID_REC_2      - 0x02    - Receiver 2 Data Valid - 0000 0010
        //    ANTENNA_OFFSETS_VALID - 0x04    - Antenna Offsets Valid - 0000 0100
        //
        //============================================================================================================
        enum DualAntennaStatusFlags
        {
            DATA_VALID_REC_1        = 0x01, // 0000 0001
            DATA_VALID_REC_2        = 0x02, // 0000 0010
            ANTENNA_OFFSETS_VALID   = 0x04  // 0000 0100
        };

        //============================================================================================================
        //API Enum: SpaceVehicleFlags
        //    The Space Vehicle Flags in the Space Vehicle Information field
        //
        //    SVFLAG_NAVIGATION     - 0x0001    - SV Used for Navigation
        //    SVFLAG_HEALTHY        - 0x0002    - SV Healthy
        //============================================================================================================
        enum SpaceVehicleFlags
        {
            SVFLAG_NAVIGATION = 0x0001,
            SVFLAG_HEALTHY = 0x0002
        };

        //============================================================================================================
        //API Enum: DeviceSelector
        //    The available device selectors.
        //
        //    DEVICE_AHRS           - 0x01
        //    DEVICE_GPS            - 0x02
        //============================================================================================================
        enum DeviceSelector
        {
            DEVICE_AHRS = 0x01,
            DEVICE_GPS = 0x02
        };

        //============================================================================================================
        //API Enum: PowerState
        //    The available device power states.
        //
        //    ON_FULL_PERFORMANCE     - 0x01
        //    ON_LOW_POWER            - 0x02
        //    SLEEP                   - 0x03
        //    OFF                     - 0x04
        //============================================================================================================
        enum PowerState
        {
            ON_FULL_PERFORMANCE = 0x01,
            ON_LOW_POWER = 0x02,
            SLEEP = 0x03,
            OFF = 0x04
        };

        //============================================================================================================
        //API Enum: StreamFormat
        //    The available device data stream formats.
        //
        //    STANDARD_MIP           - 0x01     - standard MIP (default)
        //    WRAPPED_RAW            - 0x02     - MIP wrapper around raw sensor data
        //============================================================================================================
        enum StreamFormat
        {
            STANDARD_MIP = 0x01,
            WRAPPED_RAW = 0x02
        };

        //============================================================================================================
        //API Enum: SensorState
        //    The Sensor States with the GPS Hardware Status field
        //
        //    SENSORSTATE_OFF            - 0x00    - Sensor Off
        //    SENSORSTATE_ON             - 0x01    - Sensor On
        //    SENSORSTATE_UNKNOWN        - 0x02    - Sensor State Unknown
        //============================================================================================================
        enum SensorState
        {
            SENSORSTATE_OFF = 0x00,
            SENSORSTATE_ON = 0x01,
            SENSORSTATE_UNKNOWN = 0x02
        };

        //============================================================================================================
        //API Enum: AntennaState
        //    The Antenna States with the GPS Hardware Status field
        //
        //    ANTENNASTATE_INIT         - 0x01    - Antenna Init
        //    ANTENNASTATE_SHORT        - 0x02    - Antenna Short
        //    ANTENNASTATE_OPEN         - 0x03    - Antenna Open
        //    ANTENNASTATE_GOOD         - 0x04    - Antenna Good
        //    ANTENNASTATE_UNKNOWN      - 0x05    - Antenna State Unknown
        //============================================================================================================
        enum AntennaState
        {
            ANTENNASTATE_INIT = 0x01,
            ANTENNASTATE_SHORT = 0x02,
            ANTENNASTATE_OPEN = 0x03,
            ANTENNASTATE_GOOD = 0x04,
            ANTENNASTATE_UNKNOWN = 0x05
        };

        //============================================================================================================
        //API Enum: AntennaPower
        //    The Antenna Powers with the GPS Hardware Status field
        //
        //    ANTENNAPOWER_OFF           - 0x00    - Antenna Off
        //    ANTENNAPOWER_ON            - 0x01    - Antenna On
        //    ANTENNAPOWER_UNKNOWN       - 0x02    - Antenna Power Unknown
        //============================================================================================================
        enum AntennaPower
        {
            ANTENNAPOWER_OFF = 0x00,
            ANTENNAPOWER_ON = 0x01,
            ANTENNAPOWER_UNKNOWN = 0x02
        };

        //============================================================================================================
        //API Enum: FilterState 
        //    The Filter States with the NAV Filter Status field
		//    Refer to device documentation for supported filter states.
        //
        //    FILTERSTATE_STARTUP                - 0x00    - Startup
        //    FILTERSTATE_INIT                   - 0x01    - Initialization (see status flags)
        //    FILTERSTATE_RUNNING_SLN_VALID      - 0x02    - Running, Solution Valid
        //    FILTERSTATE_RUNNING_SLN_ERROR      - 0x03    - Running, Solution Error (see status flags)
        //
		//    FILTERSTATE_VERT_GYRO              - 0x02    - Vertical gyro mode
		//    FILTERSTATE_AHRS                   - 0x03    - AHRS mode
		//    FILTERSTATE_FULL_NAV               - 0x04    - Full navigation mode
		//============================================================================================================
        enum FilterState
        {
            FILTERSTATE_STARTUP            = 0x00,
            FILTERSTATE_INIT               = 0x01,
            FILTERSTATE_RUNNING_SLN_VALID  = 0x02,
            FILTERSTATE_RUNNING_SLN_ERROR  = 0x03,

			FILTERSTATE_VERT_GYRO          = 0x02,
			FILTERSTATE_AHRS               = 0x03,
			FILTERSTATE_FULL_NAV           = 0x04
		};
        
        //============================================================================================================
        //API Enum: FilterStatus_Running
        //    Binary flags that give information with the NAV Filter Status field when filter is initialized and running. Each bit must be checked accordingly.
		//    Refer to device documentation for supported filter status flags.
		//
        // FILTERSTATUS_IMU_UNAVAILABLE                         - 0x0001    - Filter Running, IMU Unavailable
        // FILTERSTATUS_GPS_UNAVAILABLE                         - 0x0002    - Filter Running, GPS Unavailable
        // FILTERSTATUS_MATRIX_SINGULARITY_IN_CALC              - 0x0008    - Filter Running, Matrix Singularity in Calculation
        // FILTERSTATUS_POS_COVARIANCE_HIGH_WARN                - 0x0010    - Filter Running, Position Covariance High Warning
        // FILTERSTATUS_VEL_COVARIANCE_HIGH_WARN                - 0x0020    - Filter Running, Velocity Covariance High Warning
        // FILTERSTATUS_ATT_COVARIANCE_HIGH_WARN                - 0x0040    - Filter Running, Attitude Covariance High Warning
        // FILTERSTATUS_NAN_IN_SOLUTION                         - 0x0080    - Filter Running, NAN in Solution
        // FILTERSTATUS_GYRO_BIAS_EST_HIGH_WARN                 - 0x0100    - Filter Running, Gyro Bias Estimate High Warning
        // FILTERSTATUS_ACCEL_BIAS_EST_HIGH_WARN                - 0x0200    - Filter Running, Accel Bias Estimate High Warning
        // FILTERSTATUS_GYRO_SCALE_FACTOR_EST_HIGH_WARN         - 0x0400    - Filter Running, Gyro Scale Factor Estimate High Warning
        // FILTERSTATUS_ACCEL_SCALE_FACTOR_EST_HIGH_WARN        - 0x0800    - Filter Running, Accel Scale Factor Estimate High Warning
        // FILTERSTATUS_MAG_BIAS_EST_HIGH_WARN                  - 0x1000    - Filter Running, Magnetometer Bias Estimate High Warning
        // FILTERSTATUS_ANTENNA_OFFSET_CORRECTION_EST_HIGH_WARN - 0x2000    - Filter Running, GNSS Antenna Offset Correction Estimate High Warning
        // FILTERSTATUS_HARD_IRON_OFFSET_EST_HIGH_WARN          - 0x4000    - Filter Running, Hard Iron Offset Estimate High Warning
        // FILTERSTATUS_SOFT_IRON_CORRECTION_EST_HIGH_WARN      - 0x8000    - Filter Running, Soft Iron Correction Estimate High Warning
        //
		// FILTERSTATUS_CONDITION                               - 0x0003    - Filter Running, Filter Condition Indicator (mask for bits 1 and 2)
		// FILTERSTATUS_ROLL_PITCH_WARNING                      - 0x0004    - Filter Running, Roll/Pitch angle warning
		// FILTERSTATUS_HEADING_WARNING                         - 0x0008    - Filter Running, Heading angle warning
		// FILTERSTATUS_POSITION_WARNING                        - 0x0010    - Filter Running, Position warning
		// FILTERSTATUS_VELOCITY_WARNING                        - 0x0020    - Filter Running, Velocity warning
		// FILTERSTATUS_IMU_BIAS_WARNING                        - 0x0040    - Filter Running, IMU bias warning
		// FILTERSTATUS_GNSS_CLK_WARNING                        - 0x0080    - Filter Running, GNSS clock warning
		// FILTERSTATUS_ANT_LEVER_ARM_WARNING                   - 0x0100    - Filter Running, Antenna lever arm warning
		// FILTERSTATUS_MOUNTING_TRANSFORM_WARNING              - 0x0200    - Filter Running, Mounting transformation warning
		//============================================================================================================
        enum FilterStatus_Running
        {
            FILTERSTATUS_IMU_UNAVAILABLE = 0x0001,
            FILTERSTATUS_GPS_UNAVAILABLE = 0x0002,
            FILTERSTATUS_MATRIX_SINGULARITY_IN_CALC = 0x0008,
            FILTERSTATUS_POS_COVARIANCE_HIGH_WARN = 0x0010,
            FILTERSTATUS_VEL_COVARIANCE_HIGH_WARN = 0x0020,
            FILTERSTATUS_ATT_COVARIANCE_HIGH_WARN = 0x0040,
            FILTERSTATUS_NAN_IN_SOLUTION = 0x0080,
            FILTERSTATUS_GYRO_BIAS_EST_HIGH_WARN = 0x0100,
            FILTERSTATUS_ACCEL_BIAS_EST_HIGH_WARN = 0x0200,
            FILTERSTATUS_GYRO_SCALE_FACTOR_EST_HIGH_WARN = 0x0400,
            FILTERSTATUS_ACCEL_SCALE_FACTOR_EST_HIGH_WARN = 0x0800,
            FILTERSTATUS_MAG_BIAS_EST_HIGH_WARN = 0x1000,
            FILTERSTATUS_ANTENNA_OFFSET_CORRECTION_EST_HIGH_WARN = 0x2000,
            FILTERSTATUS_HARD_IRON_OFFSET_EST_HIGH_WARN = 0x4000,
            FILTERSTATUS_SOFT_IRON_CORRECTION_EST_HIGH_WARN = 0x8000,

            FILTERSTATUS_CONDITION = 0x0003,
			FILTERSTATUS_ROLL_PITCH_WARNING = 0x0004,
			FILTERSTATUS_HEADING_WARNING = 0x0008,
			FILTERSTATUS_POSITION_WARNING = 0x0010,
			FILTERSTATUS_VELOCITY_WARNING = 0x0020,
			FILTERSTATUS_IMU_BIAS_WARNING = 0x0040,
			FILTERSTATUS_GNSS_CLK_WARNING = 0x0080,
			FILTERSTATUS_ANT_LEVER_ARM_WARNING = 0x0100,
			FILTERSTATUS_MOUNTING_TRANSFORM_WARNING = 0x0200,
		};


        //============================================================================================================
        //API Enum: FilterStatus_Initialization
        //    Binary flags that give information with the NAV Filter Status field when filter is not initialized. Each bit must be checked accordingly.
        //
        //    FILTERSTATUS_ATT_NOT_INIT                      - 0x1000    - Filter Initialization, Attitude not Initialized
        //    FILTERSTATUS_POS_VEL_NOT_INIT                  - 0x2000    - Filter Initialization, Position and Velocity not Initialized
        //============================================================================================================
        enum FilterStatus_Initialization
        {
            FILTERSTATUS_ATT_NOT_INIT = 0x1000,
            FILTERSTATUS_POS_VEL_NOT_INIT = 0x2000
        };

        //============================================================================================================
        //API Enum: FilterCondition
        //    Enum of possible filter conditions. On supported devices the filter condition is included in the Filter Status Flags value.
        //
        //    STABLE                      - 0x01    - Filter stable
        //    CONVERGING                  - 0x02    - Filter converging
        //    UNSTABLE                    - 0x03    - Filter unstable
        //============================================================================================================
        enum FilterCondition
        {
            STABLE      = 0x01,
            CONVERGING  = 0x02,
            UNSTABLE    = 0x03
        };

        //============================================================================================================
        //API Enum: DgnssBaseStatus
        //    The Base Station Status in the DGNSS Information field. Note: 'UDRE' is User Differential Range Error.
        //
        // DGNSSBASE_UDRE_SCALE_FACTOR_1_00                         - 0     - UDRE Scale Factor = 1.0
        // DGNSSBASE_UDRE_SCALE_FACTOR_0_75                         - 1     - UDRE Scale Factor = 0.75
        // DGNSSBASE_UDRE_SCALE_FACTOR_0_50                         - 2     - UDRE Scale Factor = 0.5
        // DGNSSBASE_UDRE_SCALE_FACTOR_0_30                         - 3     - UDRE Scale Factor = 0.3
        // DGNSSBASE_UDRE_SCALE_FACTOR_0_20                         - 4     - UDRE Scale Factor = 0.2
        // DGNSSBASE_UDRE_SCALE_FACTOR_0_10                         - 5     - UDRE Scale Factor = 0.1
        // DGNSSBASE_REFERENCE_STATION_TRANSMISSION_NOT_MONITORED   - 6     - Reference Station Transmission Not Monitored
        // DGNSSBASE_REFERENCE_STATION_NOT_WORKING                  - 7     - Reference Station Not Working
        //============================================================================================================
        enum DgnssBaseStatus
        {
            DGNSSBASE_UDRE_SCALE_FACTOR_1_00 = 0,
            DGNSSBASE_UDRE_SCALE_FACTOR_0_75 = 1,
            DGNSSBASE_UDRE_SCALE_FACTOR_0_50 = 2,
            DGNSSBASE_UDRE_SCALE_FACTOR_0_30 = 3,
            DGNSSBASE_UDRE_SCALE_FACTOR_0_20 = 4,
            DGNSSBASE_UDRE_SCALE_FACTOR_0_10 = 5,
            DGNSSBASE_REFERENCE_STATION_TRANSMISSION_NOT_MONITORED = 6,
            DGNSSBASE_REFERENCE_STATION_NOT_WORKING = 7
        };

        //============================================================================================================
        //API Enum: HeadingSource
        //    The Heading Sources with the Heading Update Source State field
        //
        //    HEADINGSOURCE_NONE                                 - 0x0000    - No source, heading updates disabled
        //    HEADINGSOURCE_INTERNAL_MAGNETOMETER                - 0x0001    - Internal Magnetometer
        //    HEADINGSOURCE_INTERNAL_GPS_VELOCITY_VECTOR         - 0x0002    - Internal GPS Velocity Vector
        //    HEADINGSOURCE_EXTERNAL_HEADING_UPDATE_CMD          - 0x0004    - External Heading Update Command
        //    HEADINGSOURCE_GNSS_DUAL_ANTENNA                    - 0x0008    - GNSS Dual Antenna
        //============================================================================================================
        enum HeadingSource
        {
            HEADINGSOURCE_NONE = 0x0000,
            HEADINGSOURCE_INTERNAL_MAGNETOMETER = 0x0001,
            HEADINGSOURCE_INTERNAL_GPS_VELOCITY_VECTOR = 0x0002,
            HEADINGSOURCE_EXTERNAL_HEADING_UPDATE_CMD = 0x0004,
            HEADINGSOURCE_GNSS_DUAL_ANTENNA = 0x0008
        };

        //API Enum: HeadingUpdateEnableOption
        //    The enum to represent the different available options and combinations for the Heading Update Control command (0x0D, 0x18)
        //
        //      ENABLE_NONE                        - 0x00
        //      ENABLE_INTERNAL_MAGNETOMETER       - 0x01
        //      ENABLE_INTERNAL_GNSS               - 0x02
        //      ENABLE_EXTERNAL_MESSAGES           - 0x03
        //      ENABLE_MAGNETOMETER_AND_GNSS       - 0X04
        //      ENABLE_GNSS_AND_EXTERNAL           - 0X05
        //      ENABLE_MAGNETOMETER_AND_EXTERNAL   - 0X06
        //      ENABLE_ALL                         - 0x07
        enum HeadingUpdateEnableOption
        {
            ENABLE_NONE = 0x00,
            ENABLE_INTERNAL_MAGNETOMETER = 0x01,
            ENABLE_INTERNAL_GNSS = 0x02,
            ENABLE_EXTERNAL_MESSAGES = 0x03,
            ENABLE_MAGNETOMETER_AND_GNSS = 0x04,
            ENABLE_GNSS_AND_EXTERNAL = 0x05,
            ENABLE_MAGNETOMETER_AND_EXTERNAL = 0x06,
            ENABLE_ALL = 0x07
        };

        //API Enum: EstimationControlOption
        //    The enum to represent the different available options and combinations for the Estimation Control command (0x0D, 0x14)
        //
        //      ENABLE_GYRO_BIAS_ESTIMATION             - 0x0001
        //      ENABLE_ACCEL_BIAS_ESTIMATION            - 0x0002
        //      ENABLE_GYRO_SCALE_FACTOR_ESTIMATION     - 0x0004
        //      ENABLE_ACCEL_SCALE_FACTOR_ESTIMATION    - 0X0008
        //      ENABLE_GNSS_ANTENNA_OFFSET_ESTIMATION   - 0X0010
        //      ENABLE_HARD_IRON_AUTO_CALIBRATION       - 0X0020
        //      ENABLE_SOFT_IRON_AUTO_CALIBRATION       - 0x0040
        enum EstimationControlOption
        {
            ENABLE_GYRO_BIAS_ESTIMATION = 0x0001,
            ENABLE_ACCEL_BIAS_ESTIMATION = 0x0002,
            ENABLE_GYRO_SCALE_FACTOR_ESTIMATION = 0x0004,
            ENABLE_ACCEL_SCALE_FACTOR_ESTIMATION = 0X0008,
            ENABLE_GNSS_ANTENNA_OFFSET_ESTIMATION = 0X0010,
            ENABLE_HARD_IRON_AUTO_CALIBRATION = 0X0020,
            ENABLE_SOFT_IRON_AUTO_CALIBRATION = 0x0040
        };

        //API Enum: EstimationControlOption
        //    The enum to represent the source options for Declination (0x0D, 0x43), Inclination (0x0D, 0x4C), and Magnitude Source (0x0D, 0x4D)
        //
        //      NONE                        - 0x0001
        //      WORLD_MAGNETIC_MODEL        - 0x0002
        //      MANUAL                      - 0x0004
        enum GeographicSourceOption
        {
            NONE = 0x01,
            WORLD_MAGNETIC_MODEL = 0x02,
            MANUAL = 0x03
		};

        //API Enum: AdaptiveMeasurementMode
        //    The enum to represent the different available options and combinations for the Adaptive Measurement commands (0x0D, 0x44-0x46)
        //
        //      ADAPTIVE_MEASUREMENT_DISABLE        - 0x00
        //      ADAPTIVE_MEASUREMENT_ENABLE_FIXED   - 0x01
        //      ADAPTIVE_MEASUREMENT_ENABLE_AUTO    - 0x02
        enum AdaptiveMeasurementMode
        {
            ADAPTIVE_MEASUREMENT_DISABLE = 0x00,
            ADAPTIVE_MEASUREMENT_ENABLE_FIXED = 0x01,
            ADAPTIVE_MEASUREMENT_ENABLE_AUTO = 0x02
        };

        //API Enum: AidingMeasurementSource
        //    The enum to represent the different available aiding measurement sources
        //
        //      GNSS_POS_VEL_AIDING     - 0x0000
        //      GNSS_HEADING_AIDING     - 0x0001
        //      ALTIMETER_AIDING        - 0x0002
        //      ODOMETER_AIDING         - 0x0003
        //      MAGNETOMETER_AIDING     - 0x0004
        //      EXTERNAL_HEADING_AIDING - 0x0005
        enum AidingMeasurementSource
        {
            GNSS_POS_VEL_AIDING = 0x0000,
            GNSS_HEADING_AIDING = 0x0001,
            ALTIMETER_AIDING = 0x0002,
            ODOMETER_AIDING = 0x0003,
            MAGNETOMETER_AIDING = 0x0004,
            EXTERNAL_HEADING_AIDING = 0x0005
        };

        //API Enum: ConstellationId
        //  The enum to represent the different available constellation IDs for GNSS constellation settings
        //
        //      GPS       - 0x00
        //      SBAS      - 0x01
        //      GALILEO   - 0x02
        //      BEIDOU    - 0x03
        //      QZSS      - 0x05
        //      GLONASS   - 0x06
        enum ConstellationId
        {
            GPS = 0x00,
            SBAS = 0x01,
            GALILEO = 0x02,
            BEIDOU = 0x03,
            QZSS = 0x05,
            GLONASS = 0x06
        };

        //API Enum: AutoAdaptiveFilteringLevel
        //  The enum to represent the auto-adaptive filtering operating levels
        //
        //      FILTERING_OFF           - 0x00
        //      FILTERING_CONSERVATIVE  - 0x01
        //      FILTERING_MODERATE      - 0x02
        //      FILTERING_AGGRESIVE     - 0x03
        enum AutoAdaptiveFilteringLevel
        {
            FILTERING_OFF           = 0x00,
            FILTERING_CONSERVATIVE  = 0x01,
            FILTERING_MODERATE      = 0x02,
            FILTERING_AGGRESIVE     = 0x03
        };

        //API Enum: FactoryStreamingOption
        //  The enum to represent the factory streaming action options
        //
        //      FACTORY_STREAMING_OVERWRITE - 0x00
        //      FACTORY_STREAMING_ADDITIVE  - 0x02
        enum FactoryStreamingOption
        {
            FACTORY_STREAMING_OVERWRITE = 0x00,
            FACTORY_STREAMING_ADDITIVE  = 0x02
        };

        //API Enum: PpsSource
        //  The enum to represent the PPS source options
        //
        //      PPS_DISABLED    - 0x00
        //      PPS_RECEIVER_1  - 0x01
        //      PPS_RECEIVER_2  - 0x02
        //      PPS_GPIO        - 0x03
        //      PPS_GENERATED   - 0x04
        enum PpsSource
        {
            PPS_DISABLED    = 0x00,
            PPS_RECEIVER_1  = 0x01,
            PPS_RECEIVER_2  = 0x02,
            PPS_GPIO        = 0x03,
            PPS_GENERATED   = 0x04
        };

        //API Enum: GnssAidingStatus
        //  Bitmask for the GNSS Position and Attitude Aiding Status field values
        //  Note: GNSS constellation entries are defined by the corresponding constellation enum in <GnssSignalConfiguration>
        //    GNSS_AIDING_TIGHT_COUPLING  - 0x0001  - 0000 0000 0000 0001
        //    GNSS_AIDING_DIFFERENTIAL    - 0x0002  - 0000 0000 0000 0010
        //    GNSS_AIDING_INTEGER_FIX     - 0x0004  - 0000 0000 0000 0100
        //    GNSS_AIDING_GPS             - 0x0018  - 0000 0000 0001 1000
        //    GNSS_AIDING_GLONASS         - 0x0060  - 0000 0000 0110 0000
        //    GNSS_AIDING_GALILEO         - 0x0180  - 0000 0001 1000 0000
        //    GNSS_AIDING_BEIDOU          - 0x0600  - 0000 0110 0000 0000
        enum GnssAidingStatus
        {
            GNSS_AIDING_TIGHT_COUPLING = 0x0001, // 0000 0000 0000 0001
            GNSS_AIDING_DIFFERENTIAL = 0x0002, // 0000 0000 0000 0010
            GNSS_AIDING_INTEGER_FIX = 0x0004, // 0000 0000 0000 0100
            GNSS_AIDING_GPS = 0x0018, // 0000 0000 0001 1000
            GNSS_AIDING_GLONASS = 0x0060, // 0000 0000 0110 0000
            GNSS_AIDING_GALILEO = 0x0180, // 0000 0001 1000 0000
            GNSS_AIDING_BEIDOU = 0x0600, // 0000 0110 0000 0000
        };

        //API Enum: AidingMeasurementStatus
        //  Bit definitions for the Aiding Measurement Summary Status field values
        //    AIDING_MEASUREMENT_ENABLED                - 0x0001  - 0000 0000 0000 0001
        //    AIDING_MEASUREMENT_USED                   - 0x0002  - 0000 0000 0000 0010
        //    AIDING_MEASUREMENT_WARNING_RESIDUAL_HIGH  - 0x0004  - 0000 0000 0000 0100
        //    AIDING_MEASUREMENT_WARNING_SAMPLE_TIME    - 0x0008  - 0000 0000 0000 1000
        //    AIDING_MEASUREMENT_CONFIG_ERROR           - 0x0010  - 0000 0000 0001 0000
        //    AIDING_MEASUREMENT_MAX_COUNT_EXCEEDED     - 0x0020  - 0000 0000 0010 0000
        enum AidingMeasurementStatus
        {
            AIDING_MEASUREMENT_ENABLED                = 0x0001, // 0000 0000 0000 0001
            AIDING_MEASUREMENT_USED                   = 0x0002, // 0000 0000 0000 0010
            AIDING_MEASUREMENT_WARNING_RESIDUAL_HIGH  = 0x0004, // 0000 0000 0000 0100
            AIDING_MEASUREMENT_WARNING_SAMPLE_TIME    = 0x0008, // 0000 0000 0000 1000
            AIDING_MEASUREMENT_CONFIG_ERROR           = 0x0010, // 0000 0000 0001 0000
            AIDING_MEASUREMENT_MAX_COUNT_EXCEEDED     = 0x0020, // 0000 0000 0010 0000
        };

        //API Enum: RtkCorrectionsStatus
        //  Bit definitions for the RTK Corrections Epoch Status field value
        //      RTK_CORRECTION_ANTENNA_POS_RECEIVED     - 0x0001  - 0000 0000 0000 0001
        //      RTK_CORRECTION_ANTENNA_DESC_RECEIVED    - 0x0002  - 0000 0000 0000 0010
        //      RTK_CORRECTION_GPS_RECEIVED             - 0x0004  - 0000 0000 0000 0100
        //      RTK_CORRECTION_GLONASS_RECEIVED         - 0x0008  - 0000 0000 0000 1000
        //      RTK_CORRECTION_GALILEO_RECEIVED         - 0x0010  - 0000 0000 0001 0000
        //      RTK_CORRECTION_BEIDOU_RECEIVED          - 0x0020  - 0000 0000 0010 0000
        //      RTK_CORRECTION_USING_GPS_MSM            - 0x0040  - 0000 0000 0100 0000
        //      RTK_CORRECTION_USING_GLONASS_MSM        - 0x0080  - 0000 0000 1000 0000
        enum RtkCorrectionsStatus
        {
            RTK_CORRECTION_ANTENNA_POS_RECEIVED     = 0x0001, // 0000 0000 0000 0001
            RTK_CORRECTION_ANTENNA_DESC_RECEIVED    = 0x0002, // 0000 0000 0000 0010
            RTK_CORRECTION_GPS_RECEIVED             = 0x0004, // 0000 0000 0000 0100
            RTK_CORRECTION_GLONASS_RECEIVED         = 0x0008, // 0000 0000 0000 1000
            RTK_CORRECTION_GALILEO_RECEIVED         = 0x0010, // 0000 0000 0001 0000
            RTK_CORRECTION_BEIDOU_RECEIVED          = 0x0020, // 0000 0000 0010 0000
            RTK_CORRECTION_USING_GPS_MSM            = 0x0040, // 0000 0000 0100 0000
            RTK_CORRECTION_USING_GLONASS_MSM        = 0x0080, // 0000 0000 1000 0000
        };

        //API Enum: GnssSignalQuality
        //  Value definitions for the GNSS Raw Observation Signal Quality field value
        //      SIGNAL_QUALITY_NONE         - 0x00 - None
        //      SIGNAL_QUALITY_SEARCHING    - 0x01 - Searching
        //      SIGNAL_QUALITY_ACQUIRED     - 0x02 - Acquired
        //      SIGNAL_QUALITY_UNUSABLE     - 0x03 - Unusable
        //      SIGNAL_QUALITY_TIME_LOCKED  - 0x04 - Time Locked
        //      SIGNAL_QUALITY_FULLY_LOCKED - 0x05 - Fully Locked
        enum GnssSignalQuality
        {
            SIGNAL_QUALITY_NONE         = 0x00,
            SIGNAL_QUALITY_SEARCHING    = 0x01,
            SIGNAL_QUALITY_ACQUIRED     = 0x02,
            SIGNAL_QUALITY_UNUSABLE     = 0x03,
            SIGNAL_QUALITY_TIME_LOCKED  = 0x04,
            SIGNAL_QUALITY_FULLY_LOCKED = 0x05,
        };
    };

    //API Typedef: SatellitePRNs
    //  A vector of <uint16> PRN#s for satellites.
    typedef std::vector<uint16> SatellitePRNs;

    //API Typedef: RTCMMessage
    //  A string composing the RTCM message.
    typedef std::string RTCMMessage;

    //API Typedef: VehicleModeTypes
    //  A vector of <VehicleModeType> enum values
    typedef std::vector<InertialTypes::VehicleModeType> VehicleModeTypes;

    //API Typedef: AdaptiveFilterLevels
    // A vector of <AutoAdaptiveFilteringLevel> enum values
    typedef std::vector<InertialTypes::AutoAdaptiveFilteringLevel> AdaptiveFilterLevels;

    //API Typedef: PpsSourceOptions
    //  A vector of <InertialTypes::PpsSource> values
    typedef std::vector<InertialTypes::PpsSource> PpsSourceOptions;

    ///////////////  Matrix_3x3  ///////////////

    //API Class: Matrix_3x3
    //    Defines a 3 by 3 matrix.
    class Matrix_3x3
    {
    public:
        //API Constructor: Matrix_3x3
        //    Creates a Matrix object.
        //
        //Parameters:
        //    a float for each matrix index (0, 0) - (2, 2)
        Matrix_3x3(float i00, float i01, float i02, float i10, float i11, float i12, float i20, float i21, float i22);

        //API Constructor: Matrix_3x3
        //      Creates a Matrix object based on a <MipFieldValues> object
        //      Note: MipFieldValues format must be 9 floats
        Matrix_3x3(MipFieldValues data);

        //API Constructor: Matrix_3x3
        //    Creates a zero-filled Matrix object.
        Matrix_3x3() {}

        //API Destructor: ~Matrix_3x3
        //    Destroys a Matrix_3x3 object.
        ~Matrix_3x3();

        //API Function: set
        //  Sets matrix index to passed in float value.
        //
        //Parameters:
        //  col - the column to set.
        //  row - the row to set.
        //  value - the value to set (row,col) to.
        void set(uint8 row, uint8 col, float value);

        //Function: operator()
        //  Gets value at matrix index (row, col).
        //
        //Parameters:
        //  row - the row to set.
        //  col - the column to set.
#ifndef SWIG
        float operator() (uint8 row, uint8 col) const;
#endif

        //API Function: at
        //  Gets value at matrix index (row, col).
        //
        //Parameters:
        //  row - the row to set.
        //  col - the column to set.
        float at(uint8 row, uint8 col) const;

        std::string str() const;

        //API Function: asMipFieldValues
        //  Gets the current matrix values formatted as a <MipFieldValues> object
        MipFieldValues asMipFieldValues() const;

    private:
        //Variable: m_array
        //  A 3 by 3 array.
        std::array< std::array<float, 3>, 3 > m_array;
    };

    //API Typedef: Matrix_3x3s
    //  A vector of <Matrix_3x3> objects
    typedef std::vector<Matrix_3x3> Matrix_3x3s;

    //API Class: Quaternion
    //  A four-element implementation of <Matrix>
    class Quaternion : public Matrix
    {
    public:
        //API Constructor: Quaternion
        //  Creates a zero-filled Quaternion object
        Quaternion();

        //API Constructor: Quaternion
        //  Creates a Quaternion object with the specified elements
        //
        //Parameters:
        //  four floats representing the quaternion elements
        Quaternion(float q0, float q1, float q2, float q3);

        //API Constructor: Quaternion
        //  Creates a Quaternion object based on specified <MipFieldValues> data
        //
        //Parameters:
        //  <MipFieldValues> - format must be 4 floats
        Quaternion(MipFieldValues data);

        //API Function: at
        // get the float element at the specified index
        float at(uint8 index) const;

        //API Function: set
        // set the float element at the specified index
        void set(uint8 index, float val);

        //API Function: normalize
        // normalize the quaternion value
        void normalize();

        //API Function: asMipFieldValues
        //  Gets the current quaternion values formatted as a <MipFieldValues> object
        MipFieldValues asMipFieldValues() const;
    };

    //API Enum: PositionVelocityReferenceFrame
    //    Enum representing position and velocity reference frame options.
    //
    //  ECEF    - 0x01  -   Earth-Centered, Earth-Fixed
    //  LLH_NED - 0x02  -   Position: Lat/Long/Height, Velocity: North/East/Down
    enum PositionVelocityReferenceFrame
    {
        ECEF    = 0x01,
        LLH_NED = 0x02
    };

    ///////////////  GeometricVector  ///////////////

    //API Class: GeometricVector
    //    Defines a 3 dimensional, spatial vector.
    class GeometricVector
    {
    public:
        //API Function: VectorECEF
        //    Initializes and returns a new vector with the reference frame set to Earth-Centered, Earth-Fixed
        //
        //Parameters:
        //    x_init - initial x coordinate
        //    y_init - initial y coordinate
        //    z_init - initial z coordinate
        static GeometricVector VectorECEF(float x_init, float y_init, float z_init) { return GeometricVector(x_init, y_init, z_init); }

        //API Function: VectorNED
        //    Initializes and returns a new vector with the reference frame set to North-East-Down
        //
        //Parameters:
        //    north - initial x coordinate
        //    east - initial y coordinate
        //    down - initial z coordinate
        static GeometricVector VectorNED(float north, float east, float down) { return GeometricVector(north, east, down, PositionVelocityReferenceFrame::LLH_NED); }

        //API Constructor: GeometricVector
        //    Creates a GeometricVector object.
        //
        //Parameters:
        //    x_init - initial x coordinate
        //    y_init - initial y coordinate
        //    z_init - initial z coordinate
        //    ref - reference frame (default: ECEF)
        GeometricVector(float x_init, float y_init, float z_init, PositionVelocityReferenceFrame ref = PositionVelocityReferenceFrame::ECEF);

        //API Constructor: GeometricVector
        //    Creates a zero-filled GeometricVector object.
        //    Default reference frame: ECEF
        GeometricVector();

        //API Destructor: ~GeometricVector
        //    Destroys a TimeUpdate object.
        ~GeometricVector();

        //API Variable: referenceFrame
        //    The <PositionVelocityReferenceFrame> of this vector.
        //    Default: ECEF
        PositionVelocityReferenceFrame referenceFrame;
        
        //API Function: x
        // Only valid if referenceFrame is ECEF
        float x() const { return vec_0; }
        void x(float x) { vec_0 = x; };

        //API Function: y
        // Only valid if referenceFrame is ECEF
        float y() const { return vec_1; }
        void y(float y) { vec_1 = y; };

        //API Function: z
        // Only valid if referenceFrame is ECEF
        float z() const { return vec_2; }
        void z(float z) { vec_2 = z; };

        //API Function: north
        // Only valid if referenceFrame is LLH_NED
        float north() const { return vec_0; }
        void north(float north) { vec_0 = north; }

        //API Function: east
        // Only valid if referenceFrame is LLH_NED
        float east() const { return vec_1; }
        void east(float east) { vec_1 = east; }

        //API Function: down
        // Only valid if referenceFrame is LLH_NED
        float down() const { return vec_2; }
        void down(float down) { vec_2 = down; }

    private:
        //API Variable: vec_0, _1, _2
        //  The vector values.
        float vec_0, vec_1, vec_2;
    };

    //API Typedef: GeometricVectors
    //  A vector of <GeometricVector> objects
    typedef std::vector<GeometricVector> GeometricVectors;

    ///////////////  Position  ///////////////

    //API Struct: Position
    //    Defines a geographic position.
    class Position
    {
    public:
        //API Constructor: PositionLLH
        //    Creates a Position object with the reference frame set to LLH
        //
        //Parameters:
        //    lat_init - initial latitude
        //    long_init - initial longitude
        //    alt_init - initial altitude
        static Position PositionLLH(double lat_init, double long_init, double alt_init) { return Position(lat_init, long_init, alt_init, PositionVelocityReferenceFrame::LLH_NED); }
        
        //API Constructor: Position
        //    Creates a Position object with the reference frame set to ECEF
        //
        //Parameters:
        //    x_init - initial x
        //    y_init - initial y
        //    z_init - initial z
        static Position PositionECEF(double x_init, double y_init, double z_init) { return Position(x_init, y_init, z_init, PositionVelocityReferenceFrame::ECEF); }

        //API Constructor: Position
        //    Creates a Position object.
        //
        //Parameters:
        //    lat_init - initial latitude
        //    long_init - initial longitude
        //    alt_init - initial altitude
        //    ref - reference frame (default: LLH)
        Position(double lat_init, double long_init, double alt_init, PositionVelocityReferenceFrame ref = PositionVelocityReferenceFrame::LLH_NED) :
            position_0(lat_init),
            position_1(long_init),
            position_2(alt_init),
            referenceFrame(ref) {}

        //API Constructor: Position
        //    Creates a zero-filled Position object.
        //    Default reference frame: LLH
        Position() :
            position_0(0),
            position_1(0),
            position_2(0),
            referenceFrame(PositionVelocityReferenceFrame::LLH_NED) {}

        //API Destructor: ~Position
        //    Destroys a TimeUpdate object.
        ~Position() {}

        //API Variable: referenceFrame
        //    The <PositionVelocityReferenceFrame> of this position.
        //    Default: LLH
        PositionVelocityReferenceFrame referenceFrame;

        //API Function: latitude
        // Only valid if referenceFrame is LLH_NED
        double latitude() const { return position_0; }
        void latitude(double latitude) { position_0 = latitude; }

        //API Function: longitude
        // Only valid if referenceFrame is LLH_NED
        double longitude() const { return position_1; }
        void longitude(double longitude) { position_1 = longitude; }

        //API Function: altitude
        // Only valid if referenceFrame is LLH_NED
        double altitude() const { return position_2; }
        void altitude(double altitude) { position_2 = altitude; }

        //API Function: x
        // Only valid if referenceFrame is ECEF
        double x() const { return position_0; }
        void x(double x) { position_0 = x; }

        //API Function: y
        // Only valid if referenceFrame is ECEF
        double y() const { return position_1; }
        void y(double y) { position_1 = y; }

        //API Function: z
        // Only valid if referenceFrame is ECEF
        double z() const { return position_2; }
        void z(double z) { position_2 = z; }

    private:
        //API Variable: position_0, _1, _2
        // The position values
        double position_0, position_1, position_2;
    };

    ///////////////  TimeUpdate  ///////////////

    //API Class: TimeUpdate
    //    Contains time data for the GNSS_AssistTimeUpdate class.
    class TimeUpdate
    {
    public:
        //API Constructor: TimeUpdate
        //    Creates a TimeUpdate object.
        //
        //Parameters:
        //    timeOfWeek    - time into a given week in seconds.
        //    weekNumber    - the week number.
        //    timeAccuracy  - accuracy in seconds.
        TimeUpdate(double timeOfWeek, uint16 weekNumber, float timeAccuracy = 0);

        //API Destructor: ~TimeUpdate
        //    Destroys a TimeUpdate object.
        ~TimeUpdate();

        //API Function: timeOfWeek
        //  time into a given week in seconds.
        double timeOfWeek() const { return m_timeOfWeek; }

        //API Function: weekNumber
        //  the week number.
        uint16 weekNumber() const { return m_weekNumber; }

        //API Function: timeAccuracy
        //  accuracy in seconds.
        float timeAccuracy() const { return m_timeAccuracy; }

    private:
        //Constant: timeOfWeek
        //  time into a given week in seconds.
        const double m_timeOfWeek;

        //Constant: weekNumber
        //  the week number.
        const uint16 m_weekNumber;

        //Constant: timeAccuracy
        //  accuracy in seconds.
        const float m_timeAccuracy;
    };

    //API Struct: ZUPTSettingsData
    //    Contains the data for the AngularRateZUPTControl and VelocityZUPTControl classes.
    struct ZUPTSettingsData
    {
        //API Constructor: ZUPTSettingsData
        //    Creates a ZUPTSettingsData object.
        //
        //Parameters:
        //    enable - whether the control is enabled
        //    threshold - the threshold to trigger the control
        ZUPTSettingsData(bool enable, float threshold) :
        enabled(enable),
        threshold(threshold)
    { }

        //API Variable: enabled
        bool enabled;

        //API Variable: threshold
        float threshold;
    };

    //API Struct: FixedReferencePositionData
    //    Contains the data for Set Reference Position command.
    struct FixedReferencePositionData
    {
        //API Constructor: FixedReferencePositionData
        //    Creates a FixedReferencePositionData object.
        //
        //Parameters:
        //    pEnable - indicates whether a fixed reference position should be used
        //    pReference - the reference position
        FixedReferencePositionData(bool pEnable, Position pReference) :
            enable(pEnable),
            referencePosition(pReference) { }

        //API Constructor: FixedReferencePositionData
        //    Creates a FixedReferencePositionData object.
        FixedReferencePositionData() :
            enable(false),
            referencePosition(Position()) { }

        //API Variable: enable
        bool enable;

        //API Variable: referencePosition
        Position referencePosition;
    };

    //API Struct: SBASSettingsData
    //    Contains the data for the SBASSettings class.
    struct SBASSettingsData
    {
        //API Variable: enableSBAS
        bool enableSBAS;

        //API Variable: enableRanging
        bool enableRanging;

        //API Variable: enableCorrectionData
        bool enableCorrectionData;

        //API Variable: applyIntegrityInfo
        bool applyIntegrityInfo;

        //API Variable: SatellitePRNs 
        //  The <SatellitePRNs> for all included satellites.
        SatellitePRNs satellitePRNs;

        //API Constructor: SBASSettingsData
        //    Creates a SBASSettingsData object with default values.
        SBASSettingsData():
            enableSBAS(false),
            enableRanging(false),
            enableCorrectionData(false),
            applyIntegrityInfo(false)
        {}
    };

    //API Struct: Constellation
    //    Contains the satellite constellation data used in the <ConstellationSettingsData> class.
    struct Constellation
    {
        //API Variable: constellationID
        InertialTypes::ConstellationId constellationID;

        //API Variable: enabled
        bool enabled;

        //API Variable: reservedChannelCount
        //  The number of reserved channels.  (Must be <= 32)
        uint8 reservedChannelCount;

        //API Variable: maxChannels
        //  The maximum number of tracking channels.
        uint8 maxChannels;

        //API Variable: enableL1SAIF
        //  enables L1AIF for constellation QZSS
        bool enableL1SAIF;
    };

    //API Typedef: Constellations
    //  A vector of <Constellation> objects
    typedef std::vector<Constellation> Constellations;

    //API Struct: ConstellationSettingsData
    //    Contains the data for the <InertialNode::setConstellationSettings> API call.
    struct ConstellationSettingsData
    {
        //API Variable: maxChannelsAvailable
        uint16 maxChannelsAvailable;  // Ignored on send.  Only relevant on reply.

        //API Variable: maxChannelsToUse
        uint16 maxChannelsToUse;

        //API Variable: constellations
        Constellations constellations;
    };

    //API Struct: AdvancedLowPassFilterData
    //    Contains the data for the <InertialNode::setAdvancedLowPassFilterSettings> API call.
    struct AdvancedLowPassFilterData
    {
        //API Enum: ManualFilterBandwidthConfig
        //    The enum for the different data descriptors.
        //
        //  SET_TO_HALF_REPORTING_RATE = 0X00
        //  USER_SPECIFIED_CUTOFF_FREQ = 0x01
        enum ManualFilterBandwidthConfig
        {
            SET_TO_HALF_REPORTING_RATE = 0x00,
            USER_SPECIFIED_CUTOFF_FREQ = 0x01
        };

        // API Constructor: AdvancedLowPassFilterData
        AdvancedLowPassFilterData() :
            dataDescriptor(mscl::MipTypes::ChannelField::CH_FIELD_SENSOR_SCALED_ACCEL_VEC),
            manualFilterBandwidthConfig(SET_TO_HALF_REPORTING_RATE),
            applyLowPassFilter(true),
            cutoffFrequency(0)
        { }

        // API Constructor: AdvancedLowPassFilterData
        AdvancedLowPassFilterData(mscl::MipTypes::ChannelField descriptor) :
            dataDescriptor(descriptor),
            manualFilterBandwidthConfig(SET_TO_HALF_REPORTING_RATE),
            applyLowPassFilter(true),
            cutoffFrequency(0)
        { }

        //API Variable: dataDescriptor
        //    the data descriptor these settings apply to
        //
        //  Valid values:
        //  CH_FIELD_SENSOR_SCALED_ACCEL_VEC = 0x8004
        //  CH_FIELD_SENSOR_SCALED_GYRO_VEC = 0x8005
        //  CH_FIELD_SENSOR_SCALED_MAG_VEC = 0x8006
        //  CH_FIELD_SENSOR_SCALED_AMBIENT_PRESSURE = 0x8017
        mscl::MipTypes::ChannelField dataDescriptor;

        //API Variable: manualFilterBandwidthConfig
        //  The <ManualFilterBandwidthConfig> to use.
        ManualFilterBandwidthConfig manualFilterBandwidthConfig;

        //API Variable: applyLowPassFilter
        //    applies low-pass filter if set to true.
        bool applyLowPassFilter;

        //API Variable: cutoffFrequency
        //    Sets the cutoff frequency, only if manualFilterBandwidthConfig == USER_SPECIFIED_CUTOFF_FREQ
        uint16 cutoffFrequency;

    public:
        //API Function: getDataDescriptorForCommand
        //    Formats the given <MipTypes::ChannelField> data descriptor to be written to a <ByteStream> command.
        //
        //Parameters:
        //    descriptor - the <MipTypes::ChannelField> to format
        //
        //Returns:
        //    uint8 - the provided descriptor cast to uint8
        static uint8 getDataDescriptorForCommand(mscl::MipTypes::ChannelField descriptor) { return static_cast<uint8>(descriptor); }

        //API Function: getDataDescriptorFromUint8
        //    Gets the <MipTypes::ChannelField> data descriptor represented by the given <uint8> descriptor.
        //
        //Parameters:
        //    descriptor - the <uint8> data descriptor
        //
        //Returns:
        //    <MipTypes::ChannelField> - the provided descriptor cast to <MipTypes::ChannelField>
        static mscl::MipTypes::ChannelField getDataDescriptorFromUint8(uint8 descriptor) { return static_cast<mscl::MipTypes::ChannelField>(descriptor | 0x8000); }
    };

    //API Typedef: AdvancedLowPassFilterConfig
    //  A vector of <AdvancedLowPassFilterData> objects
    typedef std::vector<AdvancedLowPassFilterData> AdvancedLowPassFilterConfig;

    //API Struct: ComplementaryFilterData
    //    Contains the data needed by the <InertialNode::setComplementaryFilterSettings> class.
    struct ComplementaryFilterData
    {
        // API Constructor: ComplementaryFilterData
        //    Creates a ComplementaryFilterData object with default values.
        ComplementaryFilterData() :
            upCompensationEnabled(false),
            upCompensationTimeInSeconds(10),
            northCompensationEnabled(false),
            northCompensationTimeInSeconds(10)
        { }

        //API Variable: upCompensationEnabled
        //    determines whether or not the up compensation is enabled.
        bool upCompensationEnabled;

        //API Variable: upCompensationTimeInSeconds
        //    Sets the compensation time (in seconds) for the up compensation.
        float upCompensationTimeInSeconds;

        //API Variable: northCompensationEnabled
        //    determines whether or not the north compensation is enabled.
        bool northCompensationEnabled;

        //API Variable: northCompensationTimeInSeconds
        //    Sets the compensation time (in seconds) for the north compensation.
        float northCompensationTimeInSeconds;
    };

    //API Struct: PpsPulseInfo
    //    Contains the 1PPS Pulse info for <DeviceStatusData>.
    struct PpsPulseInfo
    {
    public:
        // API Constructor: PpsPulseInfo
        //    Creates a PpsPulseInfo object with default values.
        PpsPulseInfo():
            count(0),
            lastTimeinMS(0)
        {
        };

        //API Variable: count
        //  The number of 1PPS pulses
        uint32 count;

        //API Variable: lastTimeinMS
        //  Time of the last 1PPS pulse in MS (references System Timer)
        uint32 lastTimeinMS;
    };

    //API Struct: StreamInfo
    //    Contains stream info for <DeviceStatusData>.
    struct StreamInfo
    {
    public:
        // API Constructor: StreamInfo
        //    Creates a StreamInfo object with default values.
        StreamInfo():
            enabled(false),
            outgoingPacketsDropped(0)
        {
        };

        //API Variable: enabled
        bool enabled;

        //API Variable: outgoingPacketsDropped
        uint32 outgoingPacketsDropped;
    };

    //API Struct: DeviceMessageInfo
    struct DeviceMessageInfo
    {
    public:
        // API Constructor: DeviceMessageInfo
        //    Creates a DeviceMessageInfo object with default values.
        DeviceMessageInfo():
            messageParsingErrors(0),
            messagesRead(0),
            lastMessageReadinMS(0)
        {
        };

        //API Variable: messageParsingErrors
        uint32 messageParsingErrors;

        //API Variable: messagesRead
        uint32 messagesRead;

        //API Variable: lastMessageReadinMS
        //  Time of last message read for the stream in MS (references System Timer)
        uint32 lastMessageReadinMS;
    };

    //API Struct: PortInfo
    //    Contains USB or COM port info for <DeviceStatusData>.
    struct PortInfo
    {
    public:
        // API Constructor: PortInfo
        //    Creates a PortInfo object with default values.
        PortInfo():
            bytesWritten(0),
            bytesRead(0),
            overrunsOnWrite(0),
            overrunsOnRead(0)
        {
        };

        //API Variable: bytesWritten
        uint32 bytesWritten;

        //API Variable: bytesRead
        uint32 bytesRead;

        //API Variable: overrunsOnWrite
        uint32 overrunsOnWrite;

        //API Variable: overrunsOnRead
        uint32 overrunsOnRead;
    };

    //API Struct: TemperatureInfo
    //    Contains internal temperature info for <DeviceStatusData>.
    struct TemperatureInfo
    {
    public:
        // API Constructor: TemperatureInfo
        //    Creates a TemperatureInfo object with default values.
        TemperatureInfo():
            onBoardTemp(0),
            lastReadInMS(0),
            error(0)
        {
        };

        //API Variable: onBoardTemp
        float onBoardTemp;

        //API Variable: lastReadInMS
        //  Time of last temperature sensor reading in MS (references System Timer)
        uint32 lastReadInMS;

        //API Variable: error
        uint8 error;
    };


    //API Enum: DeviceStatusValues
    //    Keys corresponding to the device status values returned by <DeviceStatusData::asMap>, <DeviceStatusData::asValueMap>.
    //
    //  ModelNumber                                 modelNumber
    //  StatusStructure                             statusStructure
    //  SystemState                                 systemState()
    //  gnss1PpsPulseInfo_Count                     gnss1PpsPulseInfo().count
    //  gnss1PpsPulseInfo_LastTimeinMS              gnss1PpsPulseInfo().lastTimeinMS
    //  GnssPowerStateOn                            gnssPowerStateOn()
    //  ImuStreamInfo_Enabled                       imuStreamInfo().enabled
    //  ImuStreamInfo_PacketsDropped                imuStreamInfo().outgoingPacketsDropped
    //  GnssStreamInfo_Enabled                      gnssStreamInfo().enabled
    //  GnssStreamInfo_PacketsDropped               gnssStreamInfo().outgoingPacketsDropped
    //  EstimationFilterStreamInfo_Enabled          estimationFilterStreamInfo().enabled
    //  EstimationFilterStreamInfo_PacketsDropped   estimationFilterStreamInfo().outgoingPacketsDropped
    //  ComPortInfo_BytesRead                       comPortInfo().bytesRead
    //  ComPortInfo_BytesWritten                    comPortInfo().bytesWritten
    //  ComPortInfo_OverrunsOnRead                  comPortInfo().overrunsOnRead
    //  ComPortInfo_OverrunsOnWrite                 comPortInfo().overrunsOnWrite
    //  ImuMessageInfo_LastMessageReadinMS          imuMessageInfo().lastMessageReadinMS
    //  ImuMessageInfo_MessageParsingErrors         imuMessageInfo().messageParsingErrors
    //  ImuMessageInfo_MessagesRead                 imuMessageInfo().messagesRead
    //  GnssMessageInfo_LastMessageReadinMS         gnssMessageInfo().lastMessageReadinMS
    //  GnssMessageInfo_MessageParsingErrors        gnssMessageInfo().messageParsingErrors
    //  GnssMessageInfo_MessagesRead                gnssMessageInfo().messagesRead
    //  TemperatureInfo_Error                       temperatureInfo().error
    //  TemperatureInfo_LastReadInMS                temperatureInfo().lastReadInMS
    //  TemperatureInfo_OnBoardTemp                 temperatureInfo().onBoardTemp
    //  PowerState                                  powerState()
    //  GyroRange                                   gyroRange()
    //  AccelRange                                  accelRange()
    //  HasMagnetometer                             hasMagnetometer()
    //  HasPressure                                 hasPressure()
    enum DeviceStatusValues
    {
        ModelNumber,
        StatusStructure_Value,
        SystemState_Value,
        gnss1PpsPulseInfo_Count,
        gnss1PpsPulseInfo_LastTimeinMS,
        GnssPowerStateOn,
        ImuStreamInfo_Enabled,
        ImuStreamInfo_PacketsDropped,
        GnssStreamInfo_Enabled,
        GnssStreamInfo_PacketsDropped,
        EstimationFilterStreamInfo_Enabled,
        EstimationFilterStreamInfo_PacketsDropped,
        ComPortInfo_BytesRead,
        ComPortInfo_BytesWritten,
        ComPortInfo_OverrunsOnRead,
        ComPortInfo_OverrunsOnWrite,
        ImuMessageInfo_LastMessageReadinMS,
        ImuMessageInfo_MessageParsingErrors,
        ImuMessageInfo_MessagesRead,
        GnssMessageInfo_LastMessageReadinMS,
        GnssMessageInfo_MessageParsingErrors,
        GnssMessageInfo_MessagesRead,
        TemperatureInfo_Error,
        TemperatureInfo_LastReadInMS,
        TemperatureInfo_OnBoardTemp,
        PowerState,
        GyroRange,
        AccelRange,
        HasMagnetometer,
        HasPressure
    };

    //API Typedef: DeviceStatusMap
    //  A map of <DeviceStatusValues>, string entries.
    typedef std::map<DeviceStatusValues, std::string> DeviceStatusMap;

    //API Typedef: DeviceStatusValueMap
    //  A map of <DeviceStatusValues>, <Value> entries.
    typedef std::map<DeviceStatusValues, Value> DeviceStatusValueMap;

    //API Class: DeviceStatusData
    //    Contains the data needed by the <InertialNode::getBasicDeviceStatus> method.
    class DeviceStatusData
    {
    public:
        //API Enum: StatusSelector
        //    Represents the two different types of statuses returned by DeviceStatus.
        //
        //      BASIC_STATUS_STRUCTURE       - 0x01 - used to receive a limited device status.
        //      DIAGNOSTIC_STATUS_STRUCTURE  - 0x02 - used to receive a complete device status.
        enum StatusSelector
        {
            BASIC_STATUS_STRUCTURE = 0x01,
            DIAGNOSTIC_STATUS_STRUCTURE = 0x02
        };

        //API Enum: SystemState
        //    Enum of available system states.
        //
        //    SYSTEM_INITIALIZATION = 0x0001
        //    SYSTEM_STARTUP = 0x0002
        //    SYSTEM_RUNNING = 0x0003
        enum SystemState
        {
            SYSTEM_INITIALIZATION = 0x0001,
            SYSTEM_STARTUP = 0x0002,
            SYSTEM_RUNNING = 0x0003
        };

        // API Constructor: DeviceStatusData
        //    Creates a DeviceStatusData object with default values.
        DeviceStatusData() {};

        //API Variable: model
        uint16 modelNumber;

        //API Variable: statusStructure
        StatusSelector statusStructure;

        //API Variable: systemTimerInMS
        uint32 systemTimerInMS;

        //API Function: systemState
        //  get or set m_systemState
        SystemState systemState();
        void systemState(SystemState val);

        //API Function: gnssPowerStateOn
        //  get or set m_gnssPowerStateOn
        bool gnssPowerStateOn() const;
        void gnssPowerStateOn(bool val);

        //API Function: gnss1PpsPulseInfo
        //  get or set m_gnss1PpsPulseInfo
        PpsPulseInfo gnss1PpsPulseInfo();
        void gnss1PpsPulseInfo(PpsPulseInfo val);

        //API Function: imuStreamInfo
        //  get or set m_imuStreamInfo
        StreamInfo imuStreamInfo();
        void imuStreamInfo(StreamInfo val);

        //API Function: gnssStreamInfo
        //  get or set m_gnssStreamInfo
        StreamInfo gnssStreamInfo();
        void gnssStreamInfo(StreamInfo val);

        //API Function: estimationFilterStreamInfo
        //  get or set m_estimationFilterStreamInfo
        StreamInfo estimationFilterStreamInfo();
        void estimationFilterStreamInfo(StreamInfo val);

        //API Function: imuMessageInfo
        //  get or set m_imuMessageInfo
        DeviceMessageInfo imuMessageInfo();
        void imuMessageInfo(DeviceMessageInfo val);

        //API Function: gnssMessageInfo
        //  get or set m_gnssMessageInfo
        DeviceMessageInfo gnssMessageInfo();
        void gnssMessageInfo(DeviceMessageInfo val);

        //API Function: comPortInfo
        //  get or set m_comPortInfo
        PortInfo comPortInfo();
        void comPortInfo(PortInfo val);

        //API Function: usbPortInfo
        //  get or set m_usbPortInfo
        PortInfo usbPortInfo();
        void usbPortInfo(PortInfo val);

        //API Function: hasMagnetometer
        //  get or set m_hasMagnetometer
        bool hasMagnetometer() const;
        void hasMagnetometer(bool val);

        //API Function: magnetometerInitializationFailed
        //  get or set m_magnetometerInitializationFailed
        bool magnetometerInitializationFailed() const;
        void magnetometerInitializationFailed(bool val);

        //API Function: hasPressure
        //  get or set m_hasPressure
        bool hasPressure() const;
        void hasPressure(bool val);

        //API Function: pressureInitializationFailed
        //  get or set m_pressureInitializationFailed
        bool pressureInitializationFailed() const;
        void pressureInitializationFailed(bool val);

        //API Function: gnssReceiverInitializationFailed
        //  get or set m_gnssReceiverInitializationFailed
        bool gnssReceiverInitializationFailed() const;
        void gnssReceiverInitializationFailed(bool val);

        //API Function: coldStartOnPowerOn
        //  get or set m_coldStartOnPowerOn
        bool coldStartOnPowerOn() const;
        void coldStartOnPowerOn(bool val);

        //API Function: temperatureInfo
        //  get or set m_temperatureInfo
        TemperatureInfo temperatureInfo();
        void temperatureInfo(TemperatureInfo val);

        //API Function: powerState
        //  get or set m_powerState
        InertialTypes::PowerState powerState() const;
        void powerState(InertialTypes::PowerState val);

        //API Function: gyroRange
        //  get or set m_gyroRange
        uint16 gyroRange() const;
        void gyroRange(uint16 val);

        //API Function: accelRange
        //  get or set m_accelRange
        uint16 accelRange() const;
        void accelRange(uint16 val);

        //API Function: asMap
        //  get the device status as a map
        mscl::DeviceStatusMap asMap() const;

        //API Function: asValueMap
        //  get the device status as value map
        mscl::DeviceStatusValueMap asValueMap() const;


    private: // optional variables are private with public getters & setters

        //Function: checkValue
        //    Throws an exception if an optional value isn't set.
        //
        //Parameters:
        //    opt - The boost::optional value to check if it is set.
        //    valueName - The name of the value being checked. This will be included in the exception description if not set.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        template<typename T>
        void checkValue(const boost::optional<T>& opt, const std::string& valueName) const { if (!isSet(opt)) { throw Error_NoData("The " + valueName + " option has not been set"); } }

        //Function: isSet
        //    Checks whether the optional value is set.
        //
        //Parameters:
        //    opt - The boost::optional value to check if it is set.
        //
        //Returns:
        //    true if the value is set, false if it is not set.
        template<typename T>
        bool isSet(const boost::optional<T>& opt) const { return static_cast<bool>(opt); }

        //Variable: m_systemState
        boost::optional<SystemState> m_systemState;

        //Variable: m_gnssPowerStateOn
        boost::optional<bool> m_gnssPowerStateOn;

        //Variable: m_gnss1PpsPulseInfo
        boost::optional<PpsPulseInfo> m_gnss1PpsPulseInfo;

        //Variable: m_imuStreamInfo
        boost::optional<StreamInfo> m_imuStreamInfo;

        //Variable: m_gnssStreamInfo
        boost::optional<StreamInfo> m_gnssStreamInfo;

        //Variable: m_estimationFilterStreamInfo
        boost::optional<StreamInfo> m_estimationFilterStreamInfo;

        //Variable: m_imuMessageInfo
        boost::optional<DeviceMessageInfo> m_imuMessageInfo;

        //Variable: m_gnssMessageInfo
        boost::optional<DeviceMessageInfo> m_gnssMessageInfo;

        //Variable: m_comPortInfo
        boost::optional<PortInfo> m_comPortInfo;

        //Variable: m_usbPortInfo
        boost::optional<PortInfo> m_usbPortInfo;

        //Variable: m_hasMagnetometer
        boost::optional<bool> m_hasMagnetometer;

        //Variable: m_magnetometerInitializationFailed
        boost::optional<bool> m_magnetometerInitializationFailed;

        //Variable: m_hasPressure
        boost::optional<bool> m_hasPressure;

        //Variable: m_pressureInitializationFailed
        boost::optional<bool> m_pressureInitializationFailed;

        //Variable: m_gnssReceiverInitializationFailed
        boost::optional<bool> m_gnssReceiverInitializationFailed;

        //Variable: m_coldStartOnPowerOn
        boost::optional<bool> m_coldStartOnPowerOn;

        //Variable: m_temperatureInfo
        boost::optional<TemperatureInfo> m_temperatureInfo;

        //Variable: m_powerState
        boost::optional<InertialTypes::PowerState> m_powerState;

        //Variable: m_gyroRange
        //  Gyroscope range in degrees/second
        boost::optional<uint16> m_gyroRange;

        //Variable: m_accelRange
        //  Accelerometer range in gauss
        boost::optional<uint16> m_accelRange;
    };

    

    //API Typedef: StatusSelectors
    //  A vector of <StatusSelector> objects
    typedef std::vector<DeviceStatusData::StatusSelector> StatusSelectors;


    //API Struct: ExternalGNSSUpdateData
    //    Contains the data needed by the <InertialNode::sendExternalGNSSUpdate> method.
    struct ExternalGNSSUpdateData
    {
    public:

        //API Variable: gpsTimeOfWeek
        double gpsTimeOfWeek;

        //API Variable: gpsWeekNumber
        uint16 gpsWeekNumber;

        //API Variable: lattitude
        double lattitude;

        //API Variable: longitude
        double longitude;

        //API Variable: altitudeAboveWGS84Ellipsoid
        double altitudeAboveWGS84Ellipsoid;

        //API Variable: northVelocity
        float northVelocity;

        //API Variable: eastVelocity
        float eastVelocity;

        //API Variable: downVelocity
        float downVelocity;

        //API Variable: northPositionUncertainty
        float northPositionUncertainty;

        //API Variable: eastPositionUncertainty
        float eastPositionUncertainty;

        //API Variable: downPositionUncertainty
        float downPositionUncertainty;

        //API Variable: northVelocityUncertainty
        float northVelocityUncertainty;

        //API Variable: eastVelocityUncertainty
        float eastVelocityUncertainty;

        //API Variable: downVelocityUncertainty
        float downVelocityUncertainty;
    };

    //API Struct: HeadingUpdateOptions
    //    Contains the possible sources of aiding heading updates to the Kalman filter.
    //    Some, all, or none of the options can be set as heading aids.
    struct HeadingUpdateOptions
    {
    public:
        //API Function: operator <InertialTypes::HeadingUpdateEnableOption>
        //  Converts this class to a <InertialTypes::HeadingUpdateEnableOption>.
        InertialTypes::HeadingUpdateEnableOption AsOptionId() const;

        //API Constructor: HeadingUpdateOptions
        HeadingUpdateOptions() :
            useInternalMagnetometer(false),
            useInternalGNSSVelocityVector(false),
            useExternalHeadingMessages(false)
        { }

        //API Constructor: HeadingUpdateOptions
        //  Updates this class from a <InertialTypes::HeadingUpdateEnableOption> according to the Communications Protocol.
        //
        //Parameters:
        //  headingUpdateOption - The heading update used to fill in this object.
        HeadingUpdateOptions(const InertialTypes::HeadingUpdateEnableOption& headingUpdateOption);

        //API Variable: useInternalMagnetometer
        bool useInternalMagnetometer;

        //API Variable: useInternalGNSSVelocityVector
        bool useInternalGNSSVelocityVector;

        //API Variable: useExternalHeadingMessages
        bool useExternalHeadingMessages;
    };

    //API Typedef: HeadingUpdateOptionsList
    //  A vector of <HeadingUpdateOptions> objects
    typedef std::vector<HeadingUpdateOptions> HeadingUpdateOptionsList;

    //API Enum: FilterInitialValuesSource
    //    Options defining which initial filter values are user-specified or automatically determined on initialization.
    //
    //  Automatic               - 0x00  - Automatic position, velocity, and attitude
    //  UserSpecified_Heading   - 0x01  - Automatic position and velocity, automatic pitch and roll, and user-specified heading
    //  UserSpecified_Attitude  - 0x02  - Automatic position and velocity, fully user-specified attitude
    //  UserSpecified_All       - 0x03  - User-specified position, velocity, and attitude
    enum FilterInitialValuesSource
    {
        Automatic = 0,
        UserSpecified_Heading = 1,
        UserSpecified_Attitude = 2,
        UserSpecified_All = 3
    };

    //API Enum: HeadingAlignmentOption
    //    Method options for automatically determining initial filter heading
    //
    //  GNSS_DualAntenna    - 0x01  - Dual-antenna GNSS alignment
    //  GNSS_Kinematic      - 0x02  - GNSS kinematic alignment (GNSS velocity determines initial heading)
    //  Magnetometer        - 0x04  - Magnetometer heading alignment
    enum HeadingAlignmentOption
    {
        GNSS_DualAntenna = 0x01,
        GNSS_Kinematic = 0x02,
        Magnetometer = 0x04
    };

    //API Struct: HeadingAlignmentMethod
    //  Struct to create and interact with a HeadingAlignmentOption bitfield
    struct HeadingAlignmentMethod
    {
        //API Constructor: HeadingAlignmentMethod
        //  Default constructor, value = 0
        HeadingAlignmentMethod() {}

        //API Constructor: HeadingAlignmentMethod
        //  Construct HeadingAlignmentMethod object with specified initial value.
        //
        //Parameters:
        //  val - uint8 intial value
        HeadingAlignmentMethod(uint8 val) :
            value(val)
        {}
        
        //API Variable: value
        //  The HeadingAlignmentMethod bitfield value
        uint8 value;

        //API Function: select
        //  Add a <HeadingAlignmentOption> to the bitfield.
        //
        //Parameters:
        //  option - <HeadingAlignmentOption> to enable
        void select(HeadingAlignmentOption option)
        {
            value = value | static_cast<uint8>(option);
        }

        //API Function: deselect
        //  Remove a <HeadingAlignmentOption> from the bitfield.
        //
        //Parameters:
        //  option - <HeadingAlignmentOption> to disable
        void deselect(HeadingAlignmentOption option)
        {
            uint8 r = value & static_cast<uint8>(option); // remove any bits from option that are not already selected
            value = value ^ r;
        }

        //API Function: deselect
        //  Checks whether the specified <HeadingAlignmentOption> is included in the bitfield.
        //
        //Parameters:
        //  option - <HeadingAlignmentOption> to check
        //
        //Returns:
        //  bool - true: specified <HeadingAlignmentOption> included in bitfield, false: option not included
        bool selected(HeadingAlignmentOption  option)
        {
            return (value & static_cast<uint8>(option)) > 0;
        }
    };

    //API Struct: FilterInitializationValues
    //  Struct to hold values for the Filter Initialization Config command.
    struct FilterInitializationValues
    {
        //API Constructor: FilterInitializationValues
        //    Creates a FilterInitializationValues object with default values.
        //
        //Default values:
        //  initialValuesSource - <FilterInitialValuesSource>::Automatic
        //  autoHeadingAlignmentMethod - <HeadingAlignmentMethod>::GNSS_Kinematic
        //  referenceFrame - <PositionVelocityReferenceFrame>::ECEF
        FilterInitializationValues() :
            initialValuesSource(FilterInitialValuesSource::Automatic),
            autoHeadingAlignmentMethod(HeadingAlignmentOption::GNSS_Kinematic),
            referenceFrame(PositionVelocityReferenceFrame::ECEF) {}

		//API Variable: autoInitialize
		bool autoInitialize;

        //API Variable: initialValuesSource
        FilterInitialValuesSource initialValuesSource;

        //API Variable: autoHeadingAlignmentMethod
        HeadingAlignmentMethod autoHeadingAlignmentMethod;

        //API Variable: initialAttitude
        //  Note: Only heading value will be used if initialValueSource indicates pitch/roll will be determined automatically.
        EulerAngles initialAttitude;

        //API Variable: initialPosition
        Position initialPosition;

        //API Variable: initialVelocity
        GeometricVector initialVelocity;

        //API Variable: referenceFrame
        PositionVelocityReferenceFrame referenceFrame;
        
        //API Function: manualHeading
        //    Checks the value of initialValuesSource to determine if the initial heading needs to be set manually.
        bool manualHeading()
        {
            return initialValuesSource == FilterInitialValuesSource::UserSpecified_Heading
                || initialValuesSource == FilterInitialValuesSource::UserSpecified_Attitude
                || initialValuesSource == FilterInitialValuesSource::UserSpecified_All;
        };

        //API Function: manualAttitude
        //    Checks the value of initialValuesSource to determine if the initial heading, pitch, and roll need to be set manually.
        bool manualAttitude()
        {
            return initialValuesSource == FilterInitialValuesSource::UserSpecified_Attitude
                || initialValuesSource == FilterInitialValuesSource::UserSpecified_All;
        };

        //API Function: manualPositionVelocity
        //    Checks the value of initialValuesSource to determine if the initial position and velocity need to be set manually.
        bool manualPositionVelocity() { return initialValuesSource == FilterInitialValuesSource::UserSpecified_All; }
    };

    //API Struct: TareAxisValues
    //    Contains the possible axis bitfield values.
    struct TareAxisValues
    {
    public:
        //Function: operator <InertialTypes::HeadingUpdateEnableOption>
        //  Converts this class to a uint8.
        uint8 asUint8() const;

        //Constructor: HeadingUpdateOptions
        TareAxisValues(bool tareRollAxis, bool tarePitchAxis, bool tareYawAxis) :
            tareRollAxis(tareRollAxis),
            tarePitchAxis(tarePitchAxis),
            tareYawAxis(tareYawAxis)
        { };

        //API Variable: tareRollAxis
        bool tareRollAxis;

        //API Variable: tarePitchAxis
        bool tarePitchAxis;

        //API Variable: tareYawAxis
        bool tareYawAxis;
    };

    //API Struct: Geographic Source Options
    //    Holds the Geographic Source Option and the fixed value if manual is selected.
    //    Determines the sources for Declination, Inclination, and Magnitude.
    struct GeographicSourceOptions
    {
    public:
        //Constructor: GeographicSourceOptions
        GeographicSourceOptions() :
            source(InertialTypes::GeographicSourceOption::NONE),
            manual(0.0)
        { }

        //Constructor: GeographicSourceOptions
        //  constructs this class from a GeographicSourceOption and a float.
        //
        //Parameters:
        //  sourceValue - The geographic source option to use.
        //  fixedValue - The fixed value entered by the user to be used if the source is fixed.
        GeographicSourceOptions(const InertialTypes::GeographicSourceOption& sourceValue, const float fixedValue) :
            source(sourceValue),
            manual(fixedValue)
        {}

        //API Variable: source
        InertialTypes::GeographicSourceOption source;

        //API Variable: manual
        float manual;
    };

    //API Struct: EstimationControlOptions
    //    Controls which parameters are estimated by the Kalman Filter.
    //    Some, all, or none of the options can be set as estimation controls.
    struct EstimationControlOptions
    {
    public:
        //Function: operator <mscl::uint16>
        //  Converts this class to a <mscl::uint16>.
        uint16 AsUint16() const;

        //Constructor: EstimationControlOptions
        EstimationControlOptions() :
            enableGyroBiasEstimation(false),
            enableAccelBiasEstimation(false),
            enableGyroScaleFactorEstimation(false),
            enableAccelScaleFactorEstimation(false),
            enableGNSSAntennaOffsetEstimation(false),
            enableHardIronAutoCalibration(false),
            enableSoftIronAutoCalibration(false)
        { }

        //Constructor: EstimationControlOptions
        //  constructs this class from a <mscl::uint16> estimation control according to the Communications Protocol.
        //
        //Parameters:
        //  estimationControlData - The estimation control data used to fill in this object.
        EstimationControlOptions(const mscl::uint16& estimationControlData);

        //API Variable: enableGyroBiasEstimation
        bool enableGyroBiasEstimation;

        //API Variable: enableAccelBiasEstimation
        bool enableAccelBiasEstimation;

        //API Variable: enableGyroScaleFactorEstimation
        bool enableGyroScaleFactorEstimation;

        //API Variable: enableAccelScaleFactorEstimation
        bool enableAccelScaleFactorEstimation;

        //API Variable: enableGNSSAntennaOffsetEstimation
        bool enableGNSSAntennaOffsetEstimation;

        //API Variable: enableHardIronAutoCalibration
        bool enableHardIronAutoCalibration;

        //API Variable: enableSoftIronAutoCalibration
        bool enableSoftIronAutoCalibration;
    };

    //API Struct: HeadingData
    struct HeadingData
    {
    public:
        HeadingData () : 
            heading (TRUE_HEADING),
            headingAngle(0),
            headingAngleUncertainty(0)
        { }

        //API Enum: HeadingType
        //    Dictates whether heading is relative to true north or magnetic north.
        enum HeadingType
        {
            TRUE_HEADING = 0x01,
            MAGNETIC_HEADING = 0x02
        } heading;

        //API Variable: headingAngle
        float headingAngle;

        //API Variable: headingAngleUncertainty
        float headingAngleUncertainty;
    };

    //API Struct: AdaptiveMeasurementData
    struct AdaptiveMeasurementData
    {
    public:
        //API Constructor: AdaptiveMeasurementData
        //    Initialize an AdaptiveMeasurementData object with default values
        AdaptiveMeasurementData() :
            mode(InertialTypes::AdaptiveMeasurementMode::ADAPTIVE_MEASUREMENT_DISABLE),
            lowPassFilterCutoff(0),
            lowLimit(0),
            highLimit(0),
            lowLimitUncertainty(0),
            highLimitUncertainty(0),
            minUncertainty(0)
        {}

        //API Variable: mode
        InertialTypes::AdaptiveMeasurementMode mode;
        
        //API Variable: lowPassFilterCutoff
        float lowPassFilterCutoff;

        //API Variable: lowLimit
        float lowLimit;

        //API Variable: highLimit
        float highLimit;

        //API Variable: lowLimitUncertainty
        float lowLimitUncertainty;

        //API Variable: highLimitUncertainty
        float highLimitUncertainty;

        //API Variable: minUncertainty
        float minUncertainty;
    };

    //API Struct: AutoAdaptiveFilterOptions
    struct AutoAdaptiveFilterOptions
    {
    public:
        //API Constructor: AutoAdaptiveFilterOptions
        //  Initializes a AutoAdaptiveFilterOptions object with default values
        AutoAdaptiveFilterOptions() :
            level(InertialTypes::FILTERING_MODERATE),
            timeLimit(0)
        {};

        //API Constructor: AutoAdaptiveFilterOptions
        //  Initializes a AutoAdaptiveFilterOptions object with specified values
        AutoAdaptiveFilterOptions(InertialTypes::AutoAdaptiveFilteringLevel lvl, uint16 limit) :
            level(lvl),
            timeLimit(limit)
        {};

        //API Variable: level
        //  The auto-adaptive filter operating level
        InertialTypes::AutoAdaptiveFilteringLevel level;

        //API Variable: timeLimit
        //  The maximum duration of measurement rejection before entering recovery mode (ms)
        uint16 timeLimit;
    };

    //API Typedef: AdaptiveMeasurementModes
    //  A vector of <AdaptiveMeasurementMode> enum values
    typedef std::vector<InertialTypes::AdaptiveMeasurementMode> AdaptiveMeasurementModes;

    //API Struct: SignalConditioningValues
    struct SignalConditioningValues
    {
    public:
        //API Enum: DataConditioningFlags
        //    Indicates the bit value used to enable/disable data conditioning features
        enum DataConditioningFlags
        {
            ENABLE_ORIENTATION_CALC = 0x0001,
            ENABLE_CONING_SCULLING = 0x0002,
            ENABLE_FINITE_SIZE_CORRECTION = 0x0040,
            DISABLE_MAGNETOMETER = 0x0100,
            DISABLE_NORTH_COMP = 0x0400,
            DISABLE_UP_COMP = 0x0800,
            ENABLE_QUATERNION_CALC = 0x10000
        };

        //API Enum: MagPowerBandwidthSettings
        //    Indicates the magnetometer bandwidth and power consumption settings
        //
        //    HIGH = 0 - High bandwidth, highest power consumption
        //    LOW = 1 - Bandwidth coupled to Data Rate, low power consumption (default)
        enum MagPowerBandwidthSettings
        {
            HIGH = 0,
            LOW = 1
        };

        //API Variable: dataConditioningFlags
        uint16 dataConditioningFlags;

        //API Variable: orientationCalcDecimation
        uint16 orientationCalcDecimation;

        //API Variable: accelGyroFilterWidth
        uint8 accelGyroFilterWidth;

        //API Variable: magFilterWidth
        uint8 magFilterWidth;

        //API Variable: upCompensation
        uint16 upCompensation;

        //API Variable: northCompensation
        uint16 northCompensation;

        //API Variable: magBandwidthPower
        MagPowerBandwidthSettings magBandwidthPower;

        //Constructor: SignalConditioningValues
        SignalConditioningValues() {};

        //API Function: conditioningOptionOn
        //    Checks whether the specified conditioning option bit is 1.
        bool conditioningOptionOn(DataConditioningFlags option) { return (dataConditioningFlags & static_cast<uint16>(option)) > 0; };
        bool conditioningOptionOn(uint16 options) { return (dataConditioningFlags & options) > 0; };

        //API Function: setConditioningOptionOn
        //    Sets the specified conditioning option bit to 1.
        void setConditioningOptionOn(DataConditioningFlags option) { dataConditioningFlags = dataConditioningFlags | static_cast<uint16>(option); };
        void setConditioningOptionOn(uint16 options) { dataConditioningFlags = dataConditioningFlags | options; };

        //API Function: setConditioningOptionOff
        //    Sets the specified conditioning option bit to 0.
        void setConditioningOptionOff(DataConditioningFlags option) { dataConditioningFlags = dataConditioningFlags & ~static_cast<uint16>(option); };
        void setConditioningOptionOff(uint16 options) { dataConditioningFlags = dataConditioningFlags & ~options; };
    };

    //API Struct: EnableDisableMeasurements
    struct EnableDisableMeasurements
    {
    public:
        //API Enum: MeasurementOptions
        //    Indicates the bit value used to enable/disable available measurement options
        enum MeasurementOptions
        {
            ACCELEROMETER_MEASUREMENTS = 0x00000001,
            MAGNETOMETER_MEASUREMENTS = 0x00000002
        };

        //Constructor: EnableDisableMeasurements
        EnableDisableMeasurements() {};

        //Constructor: EnableDisableMeasurements
        EnableDisableMeasurements(uint16 option) :
            measurementOptions(option) {};

        //API Variable: measurementOptions
        uint16 measurementOptions;

        //API Function: optionEnabled
        //    Checks whether the specified option is enabled.
        bool optionEnabled(MeasurementOptions option) { return (measurementOptions & static_cast<uint16>(option)) > 0; };
        bool optionEnabled(uint16 options) { return (measurementOptions & options) > 0; };
        
        //API Function: enableOption
        //    Enables the specified option.
        void enableOption(MeasurementOptions option) { measurementOptions = measurementOptions | static_cast<uint16>(option); }
        void enableOption(uint16 options) { measurementOptions = measurementOptions | options; }

        //API Function: disableOption
        //    Disables the specified option.
        void disableOption(MeasurementOptions option) { measurementOptions = measurementOptions & ~static_cast<uint16>(option); }
        void disableOption(uint16 options) { measurementOptions = measurementOptions & ~options; }
    };

    //API Struct: RTKDeviceStatusFlags
    class RTKDeviceStatusFlags : public Bitfield
    {
    public:
        //API Constants:
        //  Bitmasks indicating the bits that define each value
        //      CONTROLLER_STATE            - 0x00000007 - Controller State         (00000000000000000000000000000111)
        //      PLATFORM_STATE              - 0x000000F8 - Platform State           (00000000000000000000000011111000)
        //      CONTROLLER_STATUS_CODE      - 0x00000700 - Controller Status Code   (00000000000000000000011100000000)
        //      PLATFORM_STATUS_CODE        - 0x00003800 - Platform Status Code     (00000000000000000011100000000000)
        //      RESET_REASON                - 0x0000C000 - Reset Reason             (00000000000000001100000000000000)
        //      SIGNAL_QUALITY              - 0x000F0000 - Signal Quality           (00000000000011110000000000000000)
        static const uint32 CONTROLLER_STATE            = 0x00000007; // 00000000000000000000000000000111
        static const uint32 PLATFORM_STATE              = 0x000000F8; // 00000000000000000000000011111000
        static const uint32 CONTROLLER_STATUS_CODE      = 0x00000700; // 00000000000000000000011100000000
        static const uint32 PLATFORM_STATUS_CODE        = 0x00003800; // 00000000000000000011100000000000
        static const uint32 RESET_REASON                = 0x0000C000; // 00000000000000001100000000000000
        static const uint32 SIGNAL_QUALITY              = 0x000F0000; // 00000000000011110000000000000000

        //API Enum: ControllerState
        //  Controller state values
        //      IDLE            - 0x00 - Idle
        //      ACTIVE          - 0x04 - Active
        enum ControllerState
        {
            IDLE            = 0x00,
            ACTIVE          = 0x04,
        };

        //API Enum: PlatformState
        //  Platform state values
        //      MODEM_OFF                       - 0x00 - Modem Off
        //      MODEM_POWERING_ON               - 0x01 - Modem Powering On
        //      MODEM_CONFIGURE                 - 0x02 - Configuring Modem
        //      MODEM_POWERING_DOWN             - 0x03 - Modem Powering Down
        //      MODEM_READY                     - 0x04 - Modem Ready
        //      MODEM_CONNECTING                - 0x05 - Modem Connecting to Network
        //      MODEM_DISCONNECTING             - 0x06 - Modem Disconnecting from Network
        //      MODEM_CONNECTED                 - 0x07 - Modem Connected
        //      SERVICE_CONNECTING              - 0x08 - Connecting to RTK Service
        //      SERVICE_CONNECTION_FAILED       - 0x09 - Connection to RTK Service Failed
        //      SERVICE_CONNECTION_CANCELED     - 0x0A - Connection to RTK Service Canceled
        //      SERVICE_DISCONNECTING           - 0x0B - Disconnecting from RTK Service
        //      SERVICE_CONNECTED               - 0x0C - Connected to RTK Service
        //      PLATFORM_ERROR                  - 0x0D - Platform Error
        //      RESET_MODEM                     - 0x0E - Reset Modem
        enum PlatformState
        {
            MODEM_OFF                       = 0x00,
            MODEM_POWERING_ON               = 0x01,
            MODEM_CONFIGURE                 = 0x02,
            MODEM_POWERING_DOWN             = 0x03,
            MODEM_READY                     = 0x04,
            MODEM_CONNECTING                = 0x05,
            MODEM_DISCONNECTING             = 0x06,
            MODEM_CONNECTED                 = 0x07,
            SERVICE_CONNECTING              = 0x08,
            SERVICE_CONNECTION_FAILED       = 0x09,
            SERVICE_CONNECTION_CANCELED     = 0x0A,
            SERVICE_DISCONNECTING           = 0x0B,
            SERVICE_CONNECTED               = 0x0C,
            PLATFORM_ERROR                  = 0x0D,
            RESET_MODEM                     = 0x0E
        };

        //API Enum: ControllerStatusCode
        //  Controller status code values
        //      CONTROLLER_OK   - 0x00 - Controller OK
        //      WAITING_NMEA    - 0x01 - Awaiting NMEA
        //      RTK_TIMEOUT     - 0x02 - RTK Timed Out
        //      RTK_UNAVAILABLE - 0x03 - RTK Unavailable
        //      CONFIG_INVALID  - 0x07 - Invalid Configuration
        enum ControllerStatusCode
        {
            CONTROLLER_OK   = 0x00,
            WAITING_NMEA    = 0x01,
            RTK_TIMEOUT     = 0x02,
            RTK_UNAVAILABLE = 0x03,
            CONFIG_INVALID  = 0x07
        };

        //API Enum: PlatformStatusCode
        //  Platform status code values
        //      PLATFORM_OK             - 0x00 - Platform OK
        //      RTK_CONNECTION_DROPPED  - 0x04 - RTK Service Connection Broken
        //      CELL_CONNECTION_DROPPED - 0x06 - Cell Connection Dropped
        //      MODEM_ERROR             - 0x07 - Modem Error
        enum PlatformStatusCode
        {
            PLATFORM_OK             = 0x00,
            RTK_CONNECTION_DROPPED  = 0x04,
            CELL_CONNECTION_DROPPED = 0x06,
            MODEM_ERROR             = 0x07
        };
        
        //API Enum: ResetReason
        //  Possible RTK reset reason values
        //      POWER_ON                - 0x00 - Reset due to Power-on
        //      UNKNOWN                 - 0x01 - Hardware reset
        //      SOFT_RESET              - 0x02 - Soft reset
        //      HARDWARE_ERROR_RESET    - 0x03 - Watchdog reset
        enum ResetReason
        {
            POWER_ON                = 0x00,
            UNKNOWN                 = 0x01,
            SOFT_RESET              = 0x02,
            HARDWARE_ERROR_RESET    = 0x03
        };

    public:
        //Constructor: RTKDeviceStatusFlags
        RTKDeviceStatusFlags() {};

        //Constructor: RTKDeviceStatusFlags
        RTKDeviceStatusFlags(uint32 flags) :
            Bitfield(static_cast<uint64>(flags))
        {};

    public:
        //API Function: controllerState
        ControllerState controllerState() const;
        void controllerState(ControllerState state);

        //API Function: platformState
        PlatformState platformState() const;
        void platformState(PlatformState state);

        //API Function: controllerStatusCode
        ControllerStatusCode controllerStatusCode() const;
        void controllerStatusCode(ControllerStatusCode status);

        //API Function: platformStatusCode
        PlatformStatusCode platformStatusCode() const;
        void platformStatusCode(PlatformStatusCode status);

        //API Function: resetReason
        ResetReason resetReason() const;
        void resetReason(ResetReason reason);

        //API Function: signalQuality
        uint8 signalQuality() const;
        void signalQuality(uint8 quality);
    };

    //API Class: GnssSignalConfiguration
    class GnssSignalConfiguration
    {
    public:
        //API Enum: GpsSignal
        //  Available GPS signals.
        //      L1CA    - 0x01 - L1CA:  00000001
        //      L2C     - 0x02 - L2C:   00000010
        enum GpsSignal
        {
            L1CA = 0x01,
            L2C  = 0x02
        };

        //API Enum: GlonassSignal
        //  Available GLONASS signals.
        //      L1OF    - 0x01 - L1OF:  00000001
        //      L2OF    - 0x02 - L2OF:  00000010
        enum GlonassSignal
        {
            L1OF = 0x01,
            L2OF = 0x02
        };

        //API Enum: GalileoSignal
        //  Available Galileo signals.
        //      E1  - 0x01 - E1:   00000001
        //      E5B - 0x02 - E5B:  00000010
        enum GalileoSignal
        {
            E1  = 0x01,
            E5B = 0x02
        };

        //API Enum: BeiDouSignal
        //  Available BeiDou signals.
        //      B1  - 0x01 - B1:    00000001
        //      B2  - 0x02 - B2:    00000010
        enum BeiDouSignal
        {
            B1 = 0x01,
            B2 = 0x02
        };

    public:
        //API Constructor: GnssSignalConfiguration
        GnssSignalConfiguration();

    private:
        Bitfield m_gpsSignals;
        Bitfield m_glonassSignals;
        Bitfield m_galileoSignals;
        Bitfield m_beidouSignals;

    public:
        //API Function: enableGpsSignal
        //  Enable or disable specified GPS signal
        void enableGpsSignal(GpsSignal signal, bool enable = true);

        //API Function: gpsSignalEnabled
        //  Check whether the specified GPS signal is enabled
        bool gpsSignalEnabled(GpsSignal signal);

        //API Function: gpsSignalValue
        //  Gets or sets the underlying value for the GPS signal bitfield
        void gpsSignalValue(uint8 val) { m_gpsSignals.value(val); };
        uint8 gpsSignalValue() { return static_cast<uint8>(m_gpsSignals.value()); };

        //API Function: enableGlonassSignal
        //  Enable or disable specified GLONASS signal
        void enableGlonassSignal(GlonassSignal signal, bool enable = true);

        //API Function: glonassSignalEnabled
        //  Check whether the specified GLONASS signal is enabled
        bool glonassSignalEnabled(GlonassSignal signal);

        //API Function: glonassSignalValue
        //  Gets or sets the underlying value for the GLONASS signal bitfield
        void glonassSignalValue(uint8 val) { m_glonassSignals.value(val); };
        uint8 glonassSignalValue() { return static_cast<uint8>(m_glonassSignals.value()); };

        //API Function: enableGalileoSignal
        //  Enable or disable specified Galileo signal
        void enableGalileoSignal(GalileoSignal signal, bool enable = true);

        //API Function: galileoSignalEnabled
        //  Check whether the specified Galileo signal is enabled
        bool galileoSignalEnabled(GalileoSignal signal);

        //API Function: galileoSignalValue
        //  Gets or sets the underlying value for the Galileo signal bitfield
        void galileoSignalValue(uint8 val) { m_galileoSignals.value(val); };
        uint8 galileoSignalValue() { return static_cast<uint8>(m_galileoSignals.value()); };

        //API Function: enableBeiDouSignal
        //  Enable or disable specified BeiDou signal
        void enableBeiDouSignal(BeiDouSignal signal, bool enable = true);

        //API Function: beidouSignalEnabled
        //  Check whether the specified BeiDou signal is enabled
        bool beidouSignalEnabled(BeiDouSignal signal);

        //API Function: beidouSignalValue
        //  Gets or sets the underlying value for the BeiDou signal bitfield
        void beidouSignalValue(uint8 val) { m_beidouSignals.value(val); };
        uint8 beidouSignalValue() { return static_cast<uint8>(m_beidouSignals.value()); };
    };

    //API Struct: PositionReferenceConfiguration
    struct PositionReferenceConfiguration
    {
        //API Variable: autoConfig
        //  Indicates whether the position reference is automatically determined (position value ignored if true).
        bool autoConfig = false;

        //API Variable: position
        //  The reference position value.
        Position position;
    };

    //API Struct: AntennaLeverArmCalConfiguration
    struct AntennaLeverArmCalConfiguration
    {
        //API Variable: enabled
        //  Enable or disable lever arm error tracking
        bool enabled;

        //API Variable: maxOffsetError
        //  Maximum offset error magnitude
        float maxOffsetError;
    };

    //API Class: OdometerConfiguration
    class OdometerConfiguration
    {
    public:
        //API Enum: Mode
        //  Odometer mode options
        //      DISABLED    - 0x00 - Encoder is disabled
        //      SINGLE      - 0x01 - Single pulse input; one direction only
        //      QUADRATURE  - 0x02 - Quadrature encoder mode
        enum Mode
        {
            DISABLED    = 0x00,
            SINGLE      = 0x01,
            QUADRATURE  = 0x02
        };

    public:
        OdometerConfiguration() {};

        //API Function: mode
        //  Get/Set the mode
        Mode mode() const;
        void mode(Mode m);

        //API Function: uncertainty
        //  Get/Set the uncertainty (m/m)
        float uncertainty() const;
        void uncertainty(float unc);

        //API Function: scaling
        //  Get/Set the scaling value directly (pulses per meter)
        float scaling() const;
        void scaling(float scale);

        //API Function: scaling
        //  Set the scaling by specifying the encoder resolution and the wheel radius.
        //  Scaling = encoder resultion / (2pi * radius)
        //
        //Parameters:
        //  resolution - encoder resolution (pulses per revolution)
        //  radius - wheel radius (meters)
        //
        //Note: 0 is an invalid value for both radius and resolution and will resulting in scaling = 0
        void scaling(float resolution, float radius);

    private:
        //API Variable: m_mode
        Mode m_mode;

        //API Variable: m_scaling
        float m_scaling;

        //API Variable: m_unc
        float m_unc;
    };

    //API Struct: GpioConfiguration
    struct GpioConfiguration
    {
        //API Enum: Feature
        //  GPIO Feature options
        //      UNUSED_FEATURE    - 0x00 - Pin is unused
        //      GPIO_FEATURE      - 0x01 - Encoder is disabled
        //      PPS_FEATURE       - 0x02 - Single pulse input; one direction only
        //      ENCODER_FEATURE   - 0x03 - Quadrature encoder mode
        enum Feature
        {
            UNUSED_FEATURE = 0x00,
            GPIO_FEATURE = 0x01,
            PPS_FEATURE = 0x02,
            ENCODER_FEATURE = 0x03
        };

        //API Enum: GpioBehavior
        //  GPIO Pin behavior
        //      UNUSED_BEHAVIOR              - 0x00 - Unused
        //      GPIO_INPUT_BEHAVIOR          - 0x01 - Input
        //      GPIO_OUTPUT_LOW_BEHAVIOR     - 0x02 - Output on low
        //      GPIO_OUTPUT_HIGH_BEHAVIOR    - 0x03 - Output on high
        enum GpioBehavior
        {
            UNUSED_BEHAVIOR = 0x00,
            GPIO_INPUT_BEHAVIOR = 0x01,
            GPIO_OUTPUT_LOW_BEHAVIOR = 0x02,
            GPIO_OUTPUT_HIGH_BEHAVIOR = 0x03
        };

        //API Enum: PpsBehavior
        //  PPS Pin behavior
        //      UNUSED      - 0x00 - Pin is unused
        //      PPS_INPUT   - 0x01 - Input
        //      PPS_OUTPUT  - 0x02 - Single pulse input; one direction only
        enum PpsBehavior
        {
            PPS_UNUSED = 0x00,
            PPS_INPUT = 0x01,
            PPS_OUTPUT = 0x02
        };

        //API Enum: EncoderBehavior
        //  Encoder Pin behavior
        //      UNUSED      - 0x00 - Pin is unused
        //      ENCODER_A   - 0x01 - Encoder is disabled
        //      ENCODER_B   - 0x02 - Single pulse input; one direction only
        enum EncoderBehavior
        {
            ENCODER_UNUSED = 0x00,
            ENCODER_A = 0x01,
            ENCODER_B = 0x02
        };

        //API Enum: PinModes
        //  PinModes for the pinMode Bitfield
        //      OPEN_DRAIN  - 0x01
        //      PULLDOWN    - 0x02
        //      PULLUP      - 0x04
        enum PinModes
        {
            OPEN_DRAIN = 0x01,
            PULLDOWN = 0x02,
            PULLUP = 0x04
        };

        Bitfield pinMode;

        uint8 pin;

        Feature feature;

        uint8 behavior;

        //API Function: pinModeValue
        //  Gets or sets the underlying value for the pin mode bitfield
        void pinModeValue(uint8 val) { pinMode.value(val); };
        uint8 pinModeValue() { return static_cast<uint8>(pinMode.value()); };
    };

    //API Typedef: PinModes
    //  A vector of <GpioConfiguration::PinModes> representing masked pin modes
    typedef std::vector<GpioConfiguration::PinModes> GpioPinModeOptions;

    //API Typedef: BehaviorModes
    //  A map of uint behavior ID, <GpioPinModeOptions> pairs
    typedef std::map<uint8, GpioPinModeOptions> GpioBehaviorModes;

    //API Typedef: FeatureBehaviors
    //  A map of <GpioConfiguration::Feature>, <GpioBehaviorModes> pairs
    typedef std::map<GpioConfiguration::Feature, GpioBehaviorModes> GpioFeatureBehaviors;

    //API Typedef: GpioPinOptions
    // A map of uint GPIO pin ID, <GpioFeatureBehaviors> pairs
    typedef std::map<uint8, GpioFeatureBehaviors> GpioPinOptions;
}