#pragma once

#include "mscl/Types.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
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
        //API Enums: GnssFixFlags
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
        //API Enums: GnssFixType
        //    The GNSS Fix Types with the GPS Fix Information field
        //
        //    FIXTYPE_3D             - 0x00    - 3D Fix
        //    FIXTYPE_2D             - 0x01    - 2D Fix
        //    FIXTYPE_TIMEONLY       - 0x02    - Time Only
        //    FIXTYPE_NONE           - 0x03    - None
        //    FIXTYPE_INVALID        - 0x04    - Invalid
        //============================================================================================================
        enum GnssFixType
        {
            FIXTYPE_3D = 0x00,
            FIXTYPE_2D = 0x01,
            FIXTYPE_TIMEONLY = 0x02,
            FIXTYPE_NONE = 0x03,
            FIXTYPE_INVALID = 0x04
        };

        //============================================================================================================
        //API Enums: SpaceVehicleFlags
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
        //API Enums: DeviceSelector
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
        //API Enums: PowerState
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
        //API Enums: StreamFormat
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
        //API Enums: SensorState
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
        //API Enums: AntennaState
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
        //API Enums: AntennaPower
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
        //API Enums: FilterState 
        //    The Filter States with the NAV Filter Status field
        //
        //    FILTERSTATE_STARTUP                - 0x00    - Startup
        //    FILTERSTATE_INIT                   - 0x01    - Initialization (see status flags)
        //    FILTERSTATE_RUNNING_SLN_VALID      - 0x02    - Running, Solution Valid
        //    FILTERSTATE_RUNNING_SLN_ERROR      - 0x03    - Running, Solution Error (see status flags)
        //============================================================================================================
        enum FilterState
        {
            FILTERSTATE_STARTUP = 0x00,
            FILTERSTATE_INIT = 0x01,
            FILTERSTATE_RUNNING_SLN_VALID = 0x02,
            FILTERSTATE_RUNNING_SLN_ERROR = 0x03
        };

        //============================================================================================================
        //API Enums: FilterStatus_Running
        //    Binary flags that give information with the NAV Filter Status field when filter is initialized and running. Each bit must be checked accordingly.
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
            FILTERSTATUS_SOFT_IRON_CORRECTION_EST_HIGH_WARN = 0x8000
        };

        //============================================================================================================
        //API Enums: FilterStatus_Initialization
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
        //API Enums: DgnssBaseStatus
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
        //API Enums: HeadingSource
        //    The Heading Sources with the Heading Update Source State field
        //
        //    HEADINGSOURCE_NONE                                 - 0x0000    - No source, heading updates disabled
        //    HEADINGSOURCE_INTERNAL_MAGNETOMETER                - 0x0001    - Internal Magnetometer
        //    HEADINGSOURCE_INTERNAL_GPS_VELOCITY_VECTOR         - 0x0002    - Internal GPS Velocity Vector
        //    HEADINGSOURCE_EXTERNAL_HEADING_UPDATE_CMD          - 0x0004    - External Heading Update Command
        //============================================================================================================
        enum HeadingSource
        {
            HEADINGSOURCE_NONE = 0x0000,
            HEADINGSOURCE_INTERNAL_MAGNETOMETER = 0x0001,
            HEADINGSOURCE_INTERNAL_GPS_VELOCITY_VECTOR = 0x0002,
            HEADINGSOURCE_EXTERNAL_HEADING_UPDATE_CMD = 0x0004
        };

        //API Enums: HeadingUpdateEnableOption
        //    The enums to represent the different available options and combinations for the Heading Update Control command (0x0D, 0x18)
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

        //API Enums: EstimationControlOption
        //    The enums to represent the different available options and combinations for the Estimation Control command (0x0D, 0x14)
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

        //API Enums: EstimationControlOption
        //    The enums to represent the source options for Declination (0x0D, 0x43), Inclination (0x0D, 0x4C), and Magnitude Source (0x0D, 0x4D)
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

        //API Enums: AdaptiveMeasurementMode
        //    The enums to represent the different available options and combinations for the Adaptive Measurement commands (0x0D, 0x44-0x46)
        enum AdaptiveMeasurementMode
        {
            ADAPTIVE_MEASUREMENT_DISABLE = 0x00,
            ADAPTIVE_MEASUREMENT_ENABLE_FIXED = 0x01,
            ADAPTIVE_MEASUREMENT_ENABLE_AUTO = 0x02
        };

        //API Enums: ConstellationId
        //  The enums to represent the different available constellation IDs for GNSS constellation settings
        enum ConstellationId
        {
            GPS = 0x00,
            SBAS = 0x01,
            GALILEO = 0x02,
            BEIDOU = 0x03,
            QZSS = 0x05,
            GLONASS = 0x06
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
        //    Creates a zero-filled Matrix object.
        Matrix_3x3() {}

        //API Destructor: ~Matrix_3x3
        //    Destroys a Matrix_3x3 object.
        ~Matrix_3x3();

        //Function: set
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

        //Function: at
        //  Gets value at matrix index (row, col).
        //
        //Parameters:
        //  row - the row to set.
        //  col - the column to set.
        float at(uint8 row, uint8 col) const;

    private:
        //Variable: m_array
        //  A 3 by 3 array.
        std::array< std::array<float, 3>, 3 > m_array;
    };

    //API Typedef: Matrix_3x3s
    //  A vector of <Matrix_3x3> objects
    typedef std::vector<Matrix_3x3> Matrix_3x3s;

    ///////////////  GeometricVector  ///////////////

    //API Struct: GeometricVector
    //    Defines a 3 dimensional, spatial vector.
    struct GeometricVector
    {
    public:
        //API Constructor: GeometricVector
        //    Creates a GeometricVector object.
        //
        //Parameters:
        //    x_init - initial x coordinate
        //    y_init - initial y coordinate
        //    z_init - initial z coordinate
        GeometricVector(float x_init, float y_init, float z_init);

        //API Constructor: GeometricVector
        //    Creates a zero-filled GeometricVector object.
        GeometricVector();

        //API Destructor: ~GeometricVector
        //    Destroys a TimeUpdate object.
        ~GeometricVector();

        //API Variable: x
        //  the vector's x coordinate.
        float x;

        //API Variable: y
        //  the vector's y coordinate.
        float y;

        //API Variable: z
        //  the vector's z coordinate.
        float z;
    };

    //API Typedef: GeometricVectors
    //  A vector of <GeometricVector> objects
    typedef std::vector<GeometricVector> GeometricVectors;

    ///////////////  Position  ///////////////

    //API Struct: Position
    //    Defines a latitude, longitude, and altitude.
    struct Position
    {
    public:
        //API Constructor: Position
        //    Creates a Position object.
        //
        //Parameters:
        //    lat_init - initial latitude
        //    long_init - initial longitude
        //    alt_init - initial altitude
        Position(double lat_init, double long_init, double alt_init):
            latitude(lat_init),
            longitude(long_init),
            altitude(alt_init) {}

        //API Constructor: Position
        //    Creates a zero-filled Position object.
        Position() :
            latitude(0),
            longitude(0),
            altitude(0) {}

        //API Destructor: ~Position
        //    Destroys a TimeUpdate object.
        ~Position() {}

        //API Variable: latitude
        double latitude;

        //API Variable: longitude
        double longitude;

        //API Variable: altitude
        double altitude;
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

    //API Class: DeviceStatusData
    //    Contains the data needed by the <InertialNode::getBasicDeviceStatus> method.
    class DeviceStatusData
    {
    public:
        //API Enum: StatusSelector
        //    Represents the two different types of statuses returned by DeviceStatus.
        //
        //      BASIC_STATUS_STRUCTURE       - 0x01  used to receive a limited device status.
        //      DIAGNOSTIC_STATUS_STRUCTURE  - 0x02  used to receive a complete device status.
        enum StatusSelector
        {
            BASIC_STATUS_STRUCTURE = 0x01,
            DIAGNOSTIC_STATUS_STRUCTURE = 0x02,
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
        //Function: operator <InertialTypes::HeadingUpdateEnableOption>
        //  Converts this class to a <InertialTypes::HeadingUpdateEnableOption>.
        InertialTypes::HeadingUpdateEnableOption AsOptionId() const;

        //Constructor: HeadingUpdateOptions
        HeadingUpdateOptions() :
            useInternalMagnetometer(false),
            useInternalGNSSVelocityVector(false),
            useExternalHeadingMessages(false)
        { }

        //Constructor: HeadingUpdateOptions
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

    //API Typedef: HeadingUpdateOptionsList
    //  A vector of <HeadingUpdateOptions> objects
    typedef std::vector<HeadingUpdateOptions> HeadingUpdateOptionsList;

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
}