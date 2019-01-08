#pragma once

#include "mscl/Types.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include <array>


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
        //API Enums: HwStatus_SensorState
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
        //API Enums: FilterStatus
        //    Binary flags that give information with the NAV Filter Status field. Each bit must be checked accordingly.
        //
        //    FILTERSTATUS_IMU_UNAVAILABLE                   - 0x0001    - Filter Running, IMU Unavailable
        //    FILTERSTATUS_GPS_UNAVAILABLE                   - 0x0002    - Filter Running, GPS Unavailable
        //    FILTERSTATUS_MATRIX_SINGULARITY_IN_CALC        - 0x0008    - Filter Running, Matrix Singularity in Calculation
        //    FILTERSTATUS_POS_COVARIANCE_HIGH_WARN          - 0x0010    - Filter Running, Position Covariance High Warning
        //    FILTERSTATUS_VEL_COVARIANCE_HIGH_WARN          - 0x0020    - Filter Running, Velocity Covariance High Warning
        //    FILTERSTATUS_ATT_COVARIANCE_HIGH_WARN          - 0x0040    - Filter Running, Attitude Covariance High Warning
        //    FILTERSTATUS_NAN_IN_SOLUTION                   - 0x0080    - Filter Running, NAN in Solution
        //    FILTERSTATUS_ATT_NOT_INIT                      - 0x1000    - Filter Initialization, Attitude not Initialized
        //    FILTERSTATUS_POS_VEL_NOT_INIT                  - 0x2000    - Filter Initialization, Position and Velocity not Initialized
        //============================================================================================================
        enum FilterStatus
        {
            FILTERSTATUS_IMU_UNAVAILABLE = 0x0001,
            FILTERSTATUS_GPS_UNAVAILABLE = 0x0002,
            FILTERSTATUS_MATRIX_SINGULARITY_IN_CALC = 0x0008,
            FILTERSTATUS_POS_COVARIANCE_HIGH_WARN = 0x0010,
            FILTERSTATUS_VEL_COVARIANCE_HIGH_WARN = 0x0020,
            FILTERSTATUS_ATT_COVARIANCE_HIGH_WARN = 0x0040,
            FILTERSTATUS_NAN_IN_SOLUTION = 0x0080,
            FILTERSTATUS_ATT_NOT_INIT = 0x1000,
            FILTERSTATUS_POS_VEL_NOT_INIT = 0x2000
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
        //    i00 i01 i02 i10 i11 i12 i20 i21 i22
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

                /////  ZUPTSettingsData  /////

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

/////  FixedReferencePositionData  /////

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

                /////  SBASSettings  /////

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
    static uint8 getDataDescriptorForCommand(mscl::MipTypes::ChannelField descriptor) { return static_cast<uint8>(descriptor); }

    static mscl::MipTypes::ChannelField getDataDescriptorFromUint8(uint8 descriptor) { return static_cast<mscl::MipTypes::ChannelField>(descriptor | 0x8000); }
};

typedef std::vector<AdvancedLowPassFilterData> AdvancedLowPassFilterConfig;

//API Struct: ComplementaryFilterData
//    Contains the data needed by the <InertialNode::setComplementaryFilterSettings> class.
struct ComplementaryFilterData
{
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

//API Struct: DeviceStatusData
//    Contains the data needed by the <InertialNode::getBasicDeviceStatus> method.
struct DeviceStatusData
{
public:
    DeviceStatusData() :
        systemState(0),
        systemTimerInMS (0),
        gnssPowerStateOn (true),
        numberof1PPSPulses (0),
        last1PPSInMS (0),
        imuStreamIsEnabled (true),
        gnssStreamIsEnabled (true),
        estimationFilterStreamIsEnabled (true),
        outgoingIMUDroppedPacketCount(0),
        outgoingGnssDroppedPacketCount(0),
        outgoingEstimationFilterDroppedPacketCount(0),
        numOfBytesWrittenToComPort(0),
        numOfBytesWrittenFromComPort(0),
        numOfOverrunsOnWriteToComPort(0),
        numOfIMUParsingErrors (0),
        totalIMUMessagesRead(0),
        lastIMUMessageReadInMS(0),
        numOfGnssParsingErrors(0),
        totalGnssMessagesRead(0),
        lastGnssMessageReadInMS(0)
    { }

    //API Variable: systemState
    uint16 systemState;

    //API Variable: systemTimerInMS
    uint32 systemTimerInMS;

    //API Variable: gnssPowerStateOn
    bool gnssPowerStateOn;

    //API Variable: numberof1PPSPulses
    uint32 numberof1PPSPulses;

    //API Variable: last1PPSInMS
    uint32 last1PPSInMS;

    //API Variable: imuStreamIsEnabled
    bool imuStreamIsEnabled;

    //API Variable: gnssStreamIsEnabled
    bool gnssStreamIsEnabled;

    //API Variable: estimationFilterStreamIsEnabled
    bool estimationFilterStreamIsEnabled;

    //API Variable: outgoingIMUDroppedPacketCount
    uint32 outgoingIMUDroppedPacketCount;

    //API Variable: outgoingGnssDroppedPacketCount
    uint32 outgoingGnssDroppedPacketCount;

    //API Variable: outgoingEstimationFilterDroppedPacketCount
    uint32 outgoingEstimationFilterDroppedPacketCount;

    //API Variable: numOfBytesWrittenToComPort
    uint32 numOfBytesWrittenToComPort;

    //API Variable: numOfBytesWrittenFromComPort
    uint32 numOfBytesWrittenFromComPort;

    //API Variable: numOfOverrunsOnWriteToComPort
    uint32 numOfOverrunsOnWriteToComPort;

    //API Variable: numOfIMUParsingErrors
    uint32 numOfIMUParsingErrors;

    //API Variable: totalIMUMessagesRead
    uint32 totalIMUMessagesRead;

    //API Variable: lastIMUMessageReadInMS
    uint32 lastIMUMessageReadInMS;

    //API Variable: numOfGnssParsingErrors
    uint32 numOfGnssParsingErrors;

    //API Variable: totalGnssMessagesRead
    uint32 totalGnssMessagesRead;

    //API Variable: lastGnssMessageReadInMS
    uint32 lastGnssMessageReadInMS;
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

    typedef std::vector<InertialTypes::AdaptiveMeasurementMode> AdaptiveMeasurementModes;
}