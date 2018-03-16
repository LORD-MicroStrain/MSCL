/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include <boost/utility/binary.hpp>

#include "mscl/MicroStrain/MIP/Packets/MipFieldParser.h"
#include "mscl/MicroStrain/MIP/Packets/MipDataPacket.h"

namespace mscl
{
    //Title: InertialFieldParser_GNSS

    class MipDataField;

    //Class: FieldParser_LLHPosition
    //    The field parser for LLH Position data
    class FieldParser_LLHPosition : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    LAT_LONG_FLAG          - b00000001 - The flag position for checking the latitude and longitude flag
        //    ELLIPSOID_FLAG         - b00000010 - The flag position for checking the height above ellipsoid flag
        //    MSL_HEIGHT_FLAG        - b00000001 - The flag position for checking the height above msl flag
        //    HORIZ_ACCUR_FLAG       - b00000001 - The flag position for checking the horizontal accuracy flag
        //    VERT_ACCUR_FLAG        - b00000001 - The flag position for checking the vertical accuracy flag
        static const uint16 LAT_LONG_FLAG          = BOOST_BINARY(00000001);
        static const uint16 ELLIPSOID_FLAG         = BOOST_BINARY(00000010);
        static const uint16 MSL_HEIGHT_FLAG        = BOOST_BINARY(00000100);
        static const uint16 HORIZ_ACCUR_FLAG       = BOOST_BINARY(00001000);
        static const uint16 VERT_ACCUR_FLAG        = BOOST_BINARY(00010000);

    private:
        FieldParser_LLHPosition(){};        //default constructor disabled

    public:
        //Function: parse
        //    Parses an <MipDataField> for <MipDataPoints> and stores them in the valid or invalid result vectors
        //
        //Parameters:
        //    field - The <MipDataField> to parse for data points
        //    result - The <MipDataPoints> vector to store the data points in
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;

        //Function: registerParser
        //    The static function that registers this parser with the list of parsers (called immediately)
        //
        //Returns:
        //    true, just for assigning the REGISTERED constant to true
        static bool registerParser();

    public:
        //Constant: FIELD_TYPE
        //    The 2-byte field type (Descriptor ID + Field ID) for this parser
        static const MipTypes::ChannelField FIELD_TYPE;

        //Constant: REGISTERED
        //    Whether this parser is registered. This will always be true. This is used to call registerParser() immediately
        static const bool REGISTERED;
    };

    //Class: FieldParser_ECEFPosition
    //    The field parser for ECEF Position data
    class FieldParser_ECEFPosition : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    ECEF_POS_FLAG         - b00000001 - The flag position for checking the ECEF Position flag
        //    ELLIPSOID_FLAG        - b00000010 - The flag position for checking the position accuracy flag
        static const uint16 ECEF_POS_FLAG        = BOOST_BINARY(00000001);
        static const uint16 POS_ACCURACY_FLAG    = BOOST_BINARY(00000010);

    private:
        FieldParser_ECEFPosition(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_NEDVelocity
    //    The field parser for NED Velocity data
    class FieldParser_NEDVelocity : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    NED_VELOCITY_FLAG     - b00000001 - The flag position for checking the NED Velocity flag
        //    SPEED_FLAG            - b00000010 - The flag position for checking the Speed flag
        //    GROUND_SPEED_FLAG     - b00000100 - The flag position for checking the Ground Speed flag
        //    HEADING_FLAG          - b00001000 - The flag position for checking the Heading flag
        //    SPEED_ACCUR_FLAG      - b00010000 - The flag position for checking the Speed Accuracy flag
        //    HEADING_ACCUR_FLAG    - b00100000 - The flag position for checking the Heading Accuracy flag
        static const uint16 NED_VELOCITY_FLAG     = BOOST_BINARY(00000001);
        static const uint16 SPEED_FLAG            = BOOST_BINARY(00000010);
        static const uint16 GROUND_SPEED_FLAG     = BOOST_BINARY(00000100);
        static const uint16 HEADING_FLAG          = BOOST_BINARY(00001000);
        static const uint16 SPEED_ACCUR_FLAG      = BOOST_BINARY(00010000);
        static const uint16 HEADING_ACCUR_FLAG    = BOOST_BINARY(00100000);

    private:
        FieldParser_NEDVelocity(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_ECEFVelocity
    //    The field parser for ECEF Velocity data
    class FieldParser_ECEFVelocity : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    ECEF_VELOCITY_FLAG     - b00000001    - The flag position for checking the ECEF Velocity flag
        //    VELOCITY_ACCUR_FLAG    - b00000010 - The flag position for checking the Velocity Accuracy flag
        static const uint16 ECEF_VELOCITY_FLAG     = BOOST_BINARY(00000001);
        static const uint16 VELOCITY_ACCUR_FLAG    = BOOST_BINARY(00000010);

    private:
        FieldParser_ECEFVelocity(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_DOP
    //    The field parser for DOP data
    class FieldParser_DOP : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    GDOP_FLAG    - b00000001 - The flag position for checking the Geometric DOP flag
        //    PDOP_FLAG    - b00000010 - The flag position for checking the Position DOP flag
        //    HDOP_FLAG    - b00000100 - The flag position for checking the Horizontal DOP flag
        //    VDOP_FLAG    - b00001000 - The flag position for checking the Vertical DOP flag
        //    TDOP_FLAG    - b00010000 - The flag position for checking the Time DOP flag
        //    NDOP_FLAG    - b00100000 - The flag position for checking the Northing DOP flag
        //    EDOP_FLAG    - b01000000 - The flag position for checking the Easting DOP flag
        static const uint16 GDOP_FLAG    = BOOST_BINARY(00000001);
        static const uint16 PDOP_FLAG    = BOOST_BINARY(00000010);
        static const uint16 HDOP_FLAG    = BOOST_BINARY(00000100);
        static const uint16 VDOP_FLAG    = BOOST_BINARY(00001000);
        static const uint16 TDOP_FLAG    = BOOST_BINARY(00010000);
        static const uint16 NDOP_FLAG    = BOOST_BINARY(00100000);
        static const uint16 EDOP_FLAG    = BOOST_BINARY(01000000);

    private:
        FieldParser_DOP(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_UTCTime
    //    The field parser for UTC Time data
    class FieldParser_UTCTime : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    GPS_TIME_DATE_VALID      - b00000001 - The flag position for checking the GPS Time and Date flag
        //    UTC_TIME_OFFSET_VALID    - b00000010 - The flag position for checking the UTC Time (leap seconds) flag
        static const uint16 GPS_TIME_DATE_VALID      = BOOST_BINARY(00000001);
        static const uint16 UTC_TIME_OFFSET_VALID    = BOOST_BINARY(00000010);

    private:
        FieldParser_UTCTime(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_GPSTime
    //    The field parser for GPS Time data
    class FieldParser_GPSTime : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    TOW_VALID        - b00000001 - The flag position for checking the GPS Time of Week flag
        //    WEEK_NUM_VALID   - b00000010 - The flag position for checking the GPS Week Number flag
        static const uint16 TOW_VALID         = BOOST_BINARY(00000001);
        static const uint16 WEEK_NUM_VALID    = BOOST_BINARY(00000010);

    private:
        FieldParser_GPSTime(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_ClockInfo
    //    The field parser for Clock Info data
    class FieldParser_ClockInfo : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    BIAS_VALID         - b00000001 - The flag position for checking the Clock Bias flag
        //    DRIFT_VALID        - b00000010 - The flag position for checking the Drift flag
        //    ACCUR_VALID        - b00000100 - The flag position for checking the Accuracy Estimate flag
        static const uint16 BIAS_VALID         = BOOST_BINARY(00000001);
        static const uint16 DRIFT_VALID        = BOOST_BINARY(00000010);
        static const uint16 ACCUR_VALID        = BOOST_BINARY(00000100);

    private:
        FieldParser_ClockInfo(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_GPSFixInfo
    //    The field parser for GPS Fix Information data
    class FieldParser_GPSFixInfo : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    FIX_TYPE_VALID         - b00000001 - The flag position for checking the Fix Type flag
        //    NUM_SVS_VALID          - b00000010 - The flag position for checking the Number of SVs flag
        //    FIX_FLAGS_VALID        - b00000100 - The flag position for checking the Fix Flags flag
        static const uint16 FIX_TYPE_VALID         = BOOST_BINARY(00000001);
        static const uint16 NUM_SVS_VALID          = BOOST_BINARY(00000010);
        static const uint16 FIX_FLAGS_VALID        = BOOST_BINARY(00000100);

    private:
        FieldParser_GPSFixInfo(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_SpaceVehicleInfo
    //    The field parser for Space Vehicle Information data
    class FieldParser_SpaceVehicleInfo : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    CHANNEL_VALID          - b00000001 - The flag position for checking the Channel flag
        //    SV_ID_VALID            - b00000010 - The flag position for checking the Space Vehicle ID flag
        //    RATIO_VALID            - b00000100 - The flag position for checking the Carrier to Noise Ratio flag
        //    AZIMUTH_VALID          - b00001000 - The flag position for checking the Azimuth flag
        //    ELEVATION_VALID        - b00010000 - The flag position for checking the Elevation flag
        //    SV_FLAGS_VALID         - b00100000 - The flag position for checking the Space Vehicle Flags flag
        static const uint16 CHANNEL_VALID          = BOOST_BINARY(00000001);
        static const uint16 SV_ID_VALID            = BOOST_BINARY(00000010);
        static const uint16 RATIO_VALID            = BOOST_BINARY(00000100);
        static const uint16 AZIMUTH_VALID          = BOOST_BINARY(00001000);
        static const uint16 ELEVATION_VALID        = BOOST_BINARY(00010000);
        static const uint16 SV_FLAGS_VALID         = BOOST_BINARY(00100000);

    private:
        FieldParser_SpaceVehicleInfo(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_HardwareStatus
    //    The field parser for Hardware Status Information data
    class FieldParser_HardwareStatus : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    SENSOR_STATE_VALID         - b00000001 - The flag position for checking the Sensor State flag
        //    ANTENNA_STATE_VALID        - b00000010 - The flag position for checking the Antenna State flag
        //    ANTENNA_POWER_VALID        - b00000100 - The flag position for checking the Antenna Power flag
        static const uint16 SENSOR_STATE_VALID         = BOOST_BINARY(00000001);
        static const uint16 ANTENNA_STATE_VALID        = BOOST_BINARY(00000010);
        static const uint16 ANTENNA_POWER_VALID        = BOOST_BINARY(00000100);

    private:
        FieldParser_HardwareStatus(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_DGNSSInfo
    //    The field parser for DGNSS Information data
    class FieldParser_DGNSSInfo: public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    LATEST_AGE_VALID          - b00000001 - The flag position for checking the Latest Age flag
        //    BASE_ID_VALID             - b00000010 - The flag position for checking the Base Station ID flag
        //    BASE_STATUS_VALID         - b00000100 - The flag position for checking the Base Station Status flag
        //    NUM_CHANNELS_VALID        - b00001000 - The flag position for checking the Number of DGPS Channels flag
        static const uint16 LATEST_AGE_VALID      = BOOST_BINARY(00000001);
        static const uint16 BASE_ID_VALID         = BOOST_BINARY(00000010);
        static const uint16 BASE_STATUS_VALID     = BOOST_BINARY(00000100);
        static const uint16 NUM_CHANNELS_VALID    = BOOST_BINARY(00001000);

    private:
        FieldParser_DGNSSInfo() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_DGNSSChannelStatus
    //    The field parser for DGNSS Channel Status data
    class FieldParser_DGNSSChannelStatus: public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    SV_ID_VALID                - b00000001 - The flag position for checking the Space Vehicle ID flag
        //    AGE_VALID                  - b00000010 - The flag position for checking the Age flag
        //    CORRECTION_VALID           - b00000100 - The flag position for checking the Pseudorange Correction flag
        //    RATE_CORRECTION_VALID      - b00001000 - The flag position for checking the Pseudorange Rate Correction flag
        static const uint16 SV_ID_VALID                = BOOST_BINARY(00000001);
        static const uint16 AGE_VALID                  = BOOST_BINARY(00000010);
        static const uint16 CORRECTION_VALID           = BOOST_BINARY(00000100);
        static const uint16 RATE_CORRECTION_VALID      = BOOST_BINARY(00001000);

    private:
        FieldParser_DGNSSChannelStatus() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };
}