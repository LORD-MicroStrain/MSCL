/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"

#include "InertialFieldParser_GNSS.h"
#include "mscl/MicroStrain/MIP/Packets/MipDataPacket.h"
#include "mscl/MicroStrain/DataBuffer.h"

namespace mscl
{
    //the classes in this file do not get referenced anywhere, therefore the
    //linker will not include this compilation unit when statically
    //linking to an executable. Defining this variable, and then using it
    //elsewhere, will force this file to be included
    bool _forceLibraryToIncludeCompilationUnit_GNSS;

    //=====================================================================================================================================================
    //                                                        MipGnssFieldParser
    bool MipGnssFieldParser::registerGnssParser(MipTypes::ChannelField chField, const MipFieldParser* parser)
    {
        bool registered = true;
        MipTypes::MipChannelFields fields = MipTypes::getChannelFields_allDataClasses(chField);
        for (MipTypes::ChannelField field : fields)
        {
            // any failures should return false
            registered = registered && MipFieldParser::registerParser(field, parser);
        }

        return registered;
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_LLHPosition
    const MipTypes::ChannelField FieldParser_LLHPosition::FIELD_TYPE = MipTypes::CH_FIELD_GNSS_LLH_POSITION;
    const bool FieldParser_LLHPosition::REGISTERED = FieldParser_LLHPosition::registerParser();    //register the parser immediately

    void FieldParser_LLHPosition::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        double latitude = bytes.read_double();
        double longitude = bytes.read_double();
        double heightAboveEllipsoid = bytes.read_double();
        double heightAboveMSL = bytes.read_double();
        float horizAccuracy = bytes.read_float();
        float vertAccuracy = bytes.read_float();

        //get the flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool latLongValid    = pointIsValid(flags, LAT_LONG_FLAG);
        bool ellipsoidValid = pointIsValid(flags, ELLIPSOID_FLAG);
        bool mslValid        = pointIsValid(flags, MSL_HEIGHT_FLAG);
        bool horizValid        = pointIsValid(flags, HORIZ_ACCUR_FLAG);
        bool vertValid        = pointIsValid(flags, VERT_ACCUR_FLAG);

        MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        //add all the data points we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_LATITUDE, valueType_double, anyType(latitude), latLongValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_LONGITUDE, valueType_double, anyType(longitude), latLongValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_HEIGHT_ABOVE_ELLIPSOID, valueType_double, anyType(heightAboveEllipsoid), ellipsoidValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_HEIGHT_ABOVE_MSL, valueType_double, anyType(heightAboveMSL), mslValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_HORIZONTAL_ACCURACY, valueType_float, anyType(horizAccuracy), horizValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_VERTICAL_ACCURACY, valueType_float, anyType(vertAccuracy), vertValid));
    }

    bool FieldParser_LLHPosition::registerParser()
    {
        static FieldParser_LLHPosition p;
        return MipGnssFieldParser::registerGnssParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_ECEFPosition
    const MipTypes::ChannelField FieldParser_ECEFPosition::FIELD_TYPE = MipTypes::CH_FIELD_GNSS_ECEF_POSITION;
    const bool FieldParser_ECEFPosition::REGISTERED = FieldParser_ECEFPosition::registerParser();    //register the parser immediately

    void FieldParser_ECEFPosition::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        double xPos = bytes.read_double();
        double yPos = bytes.read_double();
        double zPos = bytes.read_double();
        float posAccuracy = bytes.read_float();

        //get the flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool ecefPosValid    = pointIsValid(flags, ECEF_POS_FLAG);
        bool posAccurValid    = pointIsValid(flags, POS_ACCURACY_FLAG);

        MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        //add all the data points we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_X, valueType_double, anyType(xPos), ecefPosValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_Y, valueType_double, anyType(yPos), ecefPosValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_Z, valueType_double, anyType(zPos), ecefPosValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_POSITION_ACCURACY, valueType_float, anyType(posAccuracy), posAccurValid));
    }

    bool FieldParser_ECEFPosition::registerParser()
    {
        static FieldParser_ECEFPosition p;
        return MipGnssFieldParser::registerGnssParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_NEDVelocity
    const MipTypes::ChannelField FieldParser_NEDVelocity::FIELD_TYPE = MipTypes::CH_FIELD_GNSS_NED_VELOCITY;
    const bool FieldParser_NEDVelocity::REGISTERED = FieldParser_NEDVelocity::registerParser();    //register the parser immediately

    void FieldParser_NEDVelocity::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        float north = bytes.read_float();
        float east = bytes.read_float();
        float down = bytes.read_float();
        float speed = bytes.read_float();
        float groundSpeed = bytes.read_float();
        float heading = bytes.read_float();
        float speedAccuracy = bytes.read_float();
        float headingAccuracy = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool nedVelocityValid    = pointIsValid(flags, NED_VELOCITY_FLAG);
        bool speedValid            = pointIsValid(flags, SPEED_FLAG);
        bool groundSpeedValid    = pointIsValid(flags, GROUND_SPEED_FLAG);
        bool headingValid        = pointIsValid(flags, HEADING_FLAG);
        bool speedAccurValid    = pointIsValid(flags, SPEED_ACCUR_FLAG);
        bool headingAccurValid    = pointIsValid(flags, HEADING_ACCUR_FLAG);

        MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        //add all the data points we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_NORTH, valueType_float, anyType(north), nedVelocityValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_EAST, valueType_float, anyType(east), nedVelocityValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_DOWN, valueType_float, anyType(down), nedVelocityValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_SPEED, valueType_float, anyType(speed), speedValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_GROUND_SPEED, valueType_float, anyType(groundSpeed), groundSpeedValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_HEADING, valueType_float, anyType(heading), headingValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_SPEED_ACCURACY, valueType_float, anyType(speedAccuracy), speedAccurValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_HEADING_ACCURACY, valueType_float, anyType(headingAccuracy), headingAccurValid));
    }

    bool FieldParser_NEDVelocity::registerParser()
    {
        static FieldParser_NEDVelocity p;
        return MipGnssFieldParser::registerGnssParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_ECEFVelocity
    const MipTypes::ChannelField FieldParser_ECEFVelocity::FIELD_TYPE = MipTypes::CH_FIELD_GNSS_ECEF_VELOCITY;
    const bool FieldParser_ECEFVelocity::REGISTERED = FieldParser_ECEFVelocity::registerParser();    //register the parser immediately

    void FieldParser_ECEFVelocity::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        float xVelocity = bytes.read_float();
        float yVelocity = bytes.read_float();
        float zVelocity = bytes.read_float();
        float velocityAccuracy = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool ecefVelocityValid    = pointIsValid(flags, ECEF_VELOCITY_FLAG);
        bool accuracyValid        = pointIsValid(flags, VELOCITY_ACCUR_FLAG);

        MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        //add all the data points we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_X, valueType_float, anyType(xVelocity), ecefVelocityValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_Y, valueType_float, anyType(yVelocity), ecefVelocityValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_Z, valueType_float, anyType(zVelocity), ecefVelocityValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_VELOCITY_ACCURACY, valueType_float, anyType(velocityAccuracy), accuracyValid));
    }

    bool FieldParser_ECEFVelocity::registerParser()
    {
        static FieldParser_ECEFVelocity p;
        return MipGnssFieldParser::registerGnssParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_DOP
    const MipTypes::ChannelField FieldParser_DOP::FIELD_TYPE = MipTypes::CH_FIELD_GNSS_DOP;
    const bool FieldParser_DOP::REGISTERED = FieldParser_DOP::registerParser();    //register the parser immediately

    void FieldParser_DOP::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        float geometric = bytes.read_float();
        float position = bytes.read_float();
        float horizontal = bytes.read_float();
        float vertical = bytes.read_float();
        float time = bytes.read_float();
        float northing = bytes.read_float();
        float easting = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool gValid    = pointIsValid(flags, GDOP_FLAG);
        bool pValid    = pointIsValid(flags, PDOP_FLAG);
        bool hValid    = pointIsValid(flags, HDOP_FLAG);
        bool vValid    = pointIsValid(flags, VDOP_FLAG);
        bool tValid    = pointIsValid(flags, TDOP_FLAG);
        bool nValid    = pointIsValid(flags, NDOP_FLAG);
        bool eValid    = pointIsValid(flags, EDOP_FLAG);

        MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        //add all the data points we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_GEOMETRIC_DOP, valueType_float, anyType(geometric), gValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_POSITION_DOP, valueType_float, anyType(position), pValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_HORIZONTAL_DOP, valueType_float, anyType(horizontal), hValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_VERTICAL_DOP, valueType_float, anyType(vertical), vValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_TIME_DOP, valueType_float, anyType(time), tValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_NORTHING_DOP, valueType_float, anyType(northing), nValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_EASTING_DOP, valueType_float, anyType(easting), eValid));
    }

    bool FieldParser_DOP::registerParser()
    {
        static FieldParser_DOP p;
        return MipGnssFieldParser::registerGnssParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_UTCTime
    const MipTypes::ChannelField FieldParser_UTCTime::FIELD_TYPE = MipTypes::CH_FIELD_GNSS_UTC_TIME;
    const bool FieldParser_UTCTime::REGISTERED = FieldParser_UTCTime::registerParser();    //register the parser immediately

    void FieldParser_UTCTime::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        uint16 year = bytes.read_uint16();
        uint16 month = bytes.read_uint8();
        uint16 day = bytes.read_uint8();
        uint16 hour = bytes.read_uint8();
        uint16 minute = bytes.read_uint8();
        uint16 second = bytes.read_uint8();
        uint32 millisecond = bytes.read_uint32();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool gpsTimeValid    = pointIsValid(flags, GPS_TIME_DATE_VALID);
        bool utcTimeValid    = pointIsValid(flags, UTC_TIME_OFFSET_VALID);

        //full timestamp is only considered valid if all the flags are valid
        bool fullTimestampValid = (gpsTimeValid && utcTimeValid);

        //create a Timestamp from the values
        Timestamp time(year, month, day, hour, minute, second, millisecond);

        MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        //add all the data points we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_TIMESTAMP, valueType_Timestamp, anyType(time), fullTimestampValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_FLAGS, valueType_uint16, anyType(flags)));
    }

    bool FieldParser_UTCTime::registerParser()
    {
        static FieldParser_UTCTime p;
        return MipGnssFieldParser::registerGnssParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_GPSTime
    const MipTypes::ChannelField FieldParser_GPSTime::FIELD_TYPE = MipTypes::CH_FIELD_GNSS_GPS_TIME;
    const bool FieldParser_GPSTime::REGISTERED = FieldParser_GPSTime::registerParser();    //register the parser immediately

    void FieldParser_GPSTime::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        double gpsTimeOfWeek = bytes.read_double();
        uint16 gpsWeekNumber = bytes.read_uint16();

        //get the flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool towValid    = pointIsValid(flags, TOW_VALID);
        bool weekValid    = pointIsValid(flags, WEEK_NUM_VALID);

        MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        //add data points for the values we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_TIME_OF_WEEK, valueType_double, anyType(gpsTimeOfWeek), towValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_WEEK_NUMBER, valueType_uint16, anyType(gpsWeekNumber), weekValid));
    }

    bool FieldParser_GPSTime::registerParser()
    {
        static FieldParser_GPSTime p;
        return MipGnssFieldParser::registerGnssParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_ClockInfo
    const MipTypes::ChannelField FieldParser_ClockInfo::FIELD_TYPE = MipTypes::CH_FIELD_GNSS_CLOCK_INFO;
    const bool FieldParser_ClockInfo::REGISTERED = FieldParser_ClockInfo::registerParser();    //register the parser immediately

    void FieldParser_ClockInfo::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        double clockBias = bytes.read_double();
        double clockDrift = bytes.read_double();
        double accuracy = bytes.read_double();

        //get the flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool biasValid    = pointIsValid(flags, BIAS_VALID);
        bool driftValid    = pointIsValid(flags, DRIFT_VALID);
        bool accurValid = pointIsValid(flags, ACCUR_VALID);

        MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        //add data points for the values we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_BIAS, valueType_double, anyType(clockBias), biasValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_DRIFT, valueType_double, anyType(clockDrift), driftValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_ACCURACY_ESTIMATE, valueType_double, anyType(accuracy), accurValid));
    }

    bool FieldParser_ClockInfo::registerParser()
    {
        static FieldParser_ClockInfo p;
        return MipGnssFieldParser::registerGnssParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_GPSFixInfo
    const MipTypes::ChannelField FieldParser_GPSFixInfo::FIELD_TYPE = MipTypes::CH_FIELD_GNSS_FIX_INFO;
    const bool FieldParser_GPSFixInfo::REGISTERED = FieldParser_GPSFixInfo::registerParser();    //register the parser immediately

    void FieldParser_GPSFixInfo::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        uint8 fixType = bytes.read_uint8();
        uint8 numSvs = bytes.read_uint8();
        uint16 fixFlags = bytes.read_uint16();

        //get the flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool fixTypeValid    = pointIsValid(flags, FIX_TYPE_VALID);
        bool numSvsValid    = pointIsValid(flags, NUM_SVS_VALID);
        bool fixFlagsValid    = pointIsValid(flags, FIX_FLAGS_VALID);

        MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        //add data points for the values we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_FIX_TYPE, valueType_uint8, anyType(fixType), fixTypeValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_SV_COUNT, valueType_uint8, anyType(numSvs), numSvsValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_FLAGS, valueType_uint16, anyType(fixFlags), fixFlagsValid));
    }

    bool FieldParser_GPSFixInfo::registerParser()
    {
        static FieldParser_GPSFixInfo p;
        return MipGnssFieldParser::registerGnssParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_SpaceVehicleInfo
    const MipTypes::ChannelField FieldParser_SpaceVehicleInfo::FIELD_TYPE = MipTypes::CH_FIELD_GNSS_SPACE_VEHICLE_INFO;
    const bool FieldParser_SpaceVehicleInfo::REGISTERED = FieldParser_SpaceVehicleInfo::registerParser();    //register the parser immediately

    void FieldParser_SpaceVehicleInfo::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        uint8 channel = bytes.read_uint8();
        uint8 vehicleId = bytes.read_uint8();
        uint16 ratio = bytes.read_uint16();
        int16 azimuth = bytes.read_int16();
        int16 elevation = bytes.read_int16();
        uint16 svFlags = bytes.read_uint16();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool channelValid    = pointIsValid(flags, CHANNEL_VALID);
        bool ratioValid        = pointIsValid(flags, RATIO_VALID);
        bool azimuthValid    = pointIsValid(flags, AZIMUTH_VALID);
        bool elevationValid    = pointIsValid(flags, ELEVATION_VALID);
        bool svFlagsValid    = pointIsValid(flags, SV_FLAGS_VALID);

        MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());
        MipChannelIdentifiers addlIds = {
            MipChannelIdentifier(MipChannelIdentifier::Type::GNSS_SATELLITE_ID, vehicleId)
        };

        //add data points for the values we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_CHANNEL, addlIds, valueType_uint8, channel, channelValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_CARRIER_TO_NOISE_RATIO, addlIds, valueType_uint16, anyType(ratio), ratioValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_AZIMUTH, addlIds, valueType_int16, anyType(azimuth), azimuthValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_ELEVATION, addlIds, valueType_int16, anyType(elevation), elevationValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_FLAGS, addlIds, valueType_uint16, anyType(svFlags), svFlagsValid));
    }

    bool FieldParser_SpaceVehicleInfo::registerParser()
    {
        static FieldParser_SpaceVehicleInfo p;
        return MipGnssFieldParser::registerGnssParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_HardwareStatus
    const MipTypes::ChannelField FieldParser_HardwareStatus::FIELD_TYPE = MipTypes::CH_FIELD_GNSS_HARDWARE_STATUS;
    const bool FieldParser_HardwareStatus::REGISTERED = FieldParser_HardwareStatus::registerParser();    //register the parser immediately

    void FieldParser_HardwareStatus::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        uint8 sensorState = bytes.read_uint8();
        uint8 antennaState = bytes.read_uint8();
        uint8 antennaPower = bytes.read_uint8();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool sensorStateValid = pointIsValid(flags, SENSOR_STATE_VALID);
        bool antennaStateValid = pointIsValid(flags, ANTENNA_STATE_VALID);
        bool antennaPowerValid = pointIsValid(flags, ANTENNA_POWER_VALID);

        MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        //add data points for the values we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_SENSOR_STATE, valueType_uint8, anyType(sensorState), sensorStateValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_ANTENNA_STATE, valueType_uint8, anyType(antennaState), antennaStateValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_ANTENNA_POWER, valueType_uint8, anyType(antennaPower), antennaPowerValid));
    }

    bool FieldParser_HardwareStatus::registerParser()
    {
        static FieldParser_HardwareStatus p;
        return MipGnssFieldParser::registerGnssParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_DGNSSInfo
    const MipTypes::ChannelField FieldParser_DGNSSInfo::FIELD_TYPE = MipTypes::CH_FIELD_GNSS_DGNSS_INFO;
    const bool FieldParser_DGNSSInfo::REGISTERED = FieldParser_DGNSSInfo::registerParser();    //register the parser immediately

    void FieldParser_DGNSSInfo::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        float newestAge = bytes.read_float();
        int16 baseId = bytes.read_int16();
        int16 baseStatus = bytes.read_int16();
        uint16 numChs = bytes.read_uint16();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool baseIdValid = pointIsValid(flags, BASE_ID_VALID);
        bool ageValid = pointIsValid(flags, LATEST_AGE_VALID) & baseIdValid;
        bool baseStatusValid = pointIsValid(flags, BASE_STATUS_VALID) & baseIdValid;
        bool numChsValid = pointIsValid(flags, NUM_CHANNELS_VALID) & baseIdValid;

        MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());
        MipChannelIdentifiers addlIds = {
            MipChannelIdentifier(MipChannelIdentifier::Type::GNSS_BASE_STATION_ID, baseId)
        };

        //add data points for the values we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_AGE, addlIds, valueType_float, anyType(newestAge), ageValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_STATUS, addlIds, valueType_int16, anyType(baseStatus), baseStatusValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_NUM_CHANNELS, addlIds, valueType_uint16, anyType(numChs), numChsValid));
    }

    bool FieldParser_DGNSSInfo::registerParser()
    {
        static FieldParser_DGNSSInfo p;
        return MipGnssFieldParser::registerGnssParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================


    //=====================================================================================================================================================
    //                                                        FieldParser_DGNSSChannelStatus
    const MipTypes::ChannelField FieldParser_DGNSSChannelStatus::FIELD_TYPE = MipTypes::CH_FIELD_GNSS_DGNSS_CHANNEL_STATUS;
    const bool FieldParser_DGNSSChannelStatus::REGISTERED = FieldParser_DGNSSChannelStatus::registerParser();    //register the parser immediately

    void FieldParser_DGNSSChannelStatus::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        uint8 spaceVehicleId = bytes.read_uint8();
        float age = bytes.read_float();
        float correction = bytes.read_float();
        float rateCorrection = bytes.read_float();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool svIdValid = pointIsValid(flags, SV_ID_VALID);
        bool ageValid = pointIsValid(flags, AGE_VALID) & svIdValid;
        bool correctionValid = pointIsValid(flags, CORRECTION_VALID) & svIdValid;
        bool rateCorrectionValid = pointIsValid(flags, RATE_CORRECTION_VALID) & svIdValid;

        MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());
        MipChannelIdentifiers addlIds = {
            MipChannelIdentifier(MipChannelIdentifier::Type::GNSS_SATELLITE_ID, spaceVehicleId)
        };

        //add data points for the values we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_AGE, addlIds, valueType_float, anyType(age), ageValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_CORRECTION, addlIds, valueType_float, anyType(correction), correctionValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_RATE_CORRECTION, addlIds, valueType_float, anyType(rateCorrection), rateCorrectionValid));
    }

    bool FieldParser_DGNSSChannelStatus::registerParser()
    {
        static FieldParser_DGNSSChannelStatus p;
        return MipGnssFieldParser::registerGnssParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================


    //=====================================================================================================================================================
    //                                                        FieldParser_ClockInfo2
    const MipTypes::ChannelField FieldParser_ClockInfo2::FIELD_TYPE = MipTypes::CH_FIELD_GNSS_CLOCK_INFO_2;
    const bool FieldParser_ClockInfo2::REGISTERED = FieldParser_ClockInfo2::registerParser();    //register the parser immediately

    void FieldParser_ClockInfo2::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        double clockBias = bytes.read_double();
        double clockDrift = bytes.read_double();
        double biasAccuracy = bytes.read_double();
        double driftAccuracy = bytes.read_double();

        //get the flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool biasValid = pointIsValid(flags, BIAS_VALID);
        bool driftValid = pointIsValid(flags, DRIFT_VALID);
        bool biasAccurValid = pointIsValid(flags, BIAS_ACCUR_VALID);
        bool driftAccurValid = pointIsValid(flags, DRIFT_ACCUR_VALID);

        MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        //add data points for the values we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_BIAS, valueType_double, anyType(clockBias), biasValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_DRIFT, valueType_double, anyType(clockDrift), driftValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_BIAS_ACCURACY_ESTIMATE, valueType_double, anyType(biasAccuracy), biasAccurValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_DRIFT_ACCURACY_ESTIMATE, valueType_double, anyType(driftAccuracy), driftAccurValid));
    }

    bool FieldParser_ClockInfo2::registerParser()
    {
        static FieldParser_ClockInfo2 p;
        return MipGnssFieldParser::registerGnssParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================


    //=====================================================================================================================================================
    //                                                        FieldParser_GPSLeapSeconds
    const MipTypes::ChannelField FieldParser_GPSLeapSeconds::FIELD_TYPE = MipTypes::CH_FIELD_GNSS_GPS_LEAP_SECONDS;
    const bool FieldParser_GPSLeapSeconds::REGISTERED = FieldParser_GPSLeapSeconds::registerParser();    //register the parser immediately

    void FieldParser_GPSLeapSeconds::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        uint8 seconds = bytes.read_uint8();

        //get the valid flags
        uint16 flags = bytes.read_uint16();


        //get whether points are valid or invalid from the flags
        bool secondsValid = pointIsValid(flags, SECONDS_VALID);

        MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        //add data points for the values we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_SECONDS, valueType_uint8, anyType(seconds), secondsValid));
    }

    bool FieldParser_GPSLeapSeconds::registerParser()
    {
        static FieldParser_GPSLeapSeconds p;
        return MipGnssFieldParser::registerGnssParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_GnssSBASInfo
    const MipTypes::ChannelField FieldParser_GnssSBASInfo::FIELD_TYPE = MipTypes::CH_FIELD_GNSS_SBAS_INFO;
    const bool FieldParser_GnssSBASInfo::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_GnssSBASInfo::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        // get the data
        const double tow         = bytes.read_double();
        const uint16 weekNum     = bytes.read_uint16();
        const uint8  sbasId      = bytes.read_uint8();
        const uint8  satelliteId = bytes.read_uint8();
        const uint8  count       = bytes.read_uint8();
        const uint8  status      = bytes.read_uint8();

        // get the valid flags
        const uint16 flags = bytes.read_uint16();

        // get whether points are valid or invalid from the flags
        const bool towValid        = pointIsValid(flags, TOW_VALID);
        const bool weekNumValid    = pointIsValid(flags, WEEK_NUMBER_VALID);
        const bool systemValid     = pointIsValid(flags, SYSTEM_VALID);
        const bool satelliteValid  = pointIsValid(flags, SATELLITE_VALID);
        const bool countValid      = pointIsValid(flags, COUNT_VALID);
        const bool sbasStatusValid = pointIsValid(flags, SBAS_STATUS_VALID);

        // identifiers
        const MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        // add data points for the values collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_TIME_OF_WEEK, valueType_double, anyType(tow),     towValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_WEEK_NUMBER,  valueType_uint16, anyType(weekNum), weekNumValid));

        result.push_back(MipDataPoint(chField, MipTypes::CH_SYSTEM_ID, valueType_uint8, anyType(sbasId), systemValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_SATELLITE_ID, valueType_uint8, anyType(satelliteId), satelliteValid));

        result.push_back(MipDataPoint(chField, MipTypes::CH_COUNT,  valueType_uint8, anyType(count),  countValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_STATUS, valueType_uint8, anyType(status), sbasStatusValid));
    }

    bool FieldParser_GnssSBASInfo::registerParser()
    {
        static FieldParser_GnssSBASInfo p;
        return registerGnssParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_GnssSBASCorrection
    const MipTypes::ChannelField FieldParser_GnssSBASCorrection::FIELD_TYPE = MipTypes::CH_FIELD_GNSS_SBAS_CORRECTION;
    const bool FieldParser_GnssSBASCorrection::REGISTERED = registerParser();    //register the parser immediately
    void FieldParser_GnssSBASCorrection::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        // get the data
        const uint8  index       = bytes.read_uint8();
        const uint8  count       = bytes.read_uint8();
        const double tow         = bytes.read_double();
        const uint16 weekNum     = bytes.read_uint16();
        const uint8  gnssId      = bytes.read_uint8();
        const uint8  satelliteId = bytes.read_uint8();
        const uint8  udrei       = bytes.read_uint8();
        const float  pseudorange = bytes.read_float();
        const float  ionospheric = bytes.read_float();

        // get the valid flags
        const uint16 flags = bytes.read_uint16();

        // get whether points are valid or invalid from the flags
        const bool udreiValid = pointIsValid(flags, UDREI_VALID);
        const bool pseudorangeValid = pointIsValid(flags, PSEUDORANGE_CORRECTION_VALID);
        const bool ionosphericValid = pointIsValid(flags, IONOSPHERIC_CORRECTION_VALID);

        // identifiers
        const auto chField = static_cast<MipTypes::ChannelField>(field.fieldId());
        const MipChannelIdentifiers addlIds = {
            MipChannelIdentifier(MipChannelIdentifier::Type::GNSS_CONSTELLATION, gnssId),
            MipChannelIdentifier(MipChannelIdentifier::Type::GNSS_SATELLITE_ID,  satelliteId)
        };

        // add data points for the values collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_INDEX, addlIds, valueType_uint8, anyType(index)));
        result.push_back(MipDataPoint(chField, MipTypes::CH_COUNT, addlIds, valueType_uint8, anyType(count)));
        result.push_back(MipDataPoint(chField, MipTypes::CH_TIME_OF_WEEK, addlIds, valueType_double, anyType(tow)));
        result.push_back(MipDataPoint(chField, MipTypes::CH_WEEK_NUMBER, addlIds, valueType_uint16, anyType(weekNum)));
        result.push_back(MipDataPoint(chField, MipTypes::CH_UDREI, addlIds, valueType_uint8, anyType(udrei), udreiValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_PSEUDORANGE_CORRECTION, addlIds, valueType_float, anyType(pseudorange), pseudorangeValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_IONOSPHERIC_CORRECTION, addlIds, valueType_float, anyType(ionospheric), ionosphericValid));
    }

    bool FieldParser_GnssSBASCorrection::registerParser()
    {
        static FieldParser_GnssSBASCorrection p;
        return registerGnssParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_GnssRFErrorDetection
    const MipTypes::ChannelField FieldParser_GnssRFErrorDetection::FIELD_TYPE = MipTypes::CH_FIELD_GNSS_RF_ERROR_DETECTION;
    const bool FieldParser_GnssRFErrorDetection::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_GnssRFErrorDetection::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        // get the data
        const uint8  rfBand        = bytes.read_uint8();
        const uint8  jammingState  = bytes.read_uint8();
        const uint8  spoofingState = bytes.read_uint8();

        // skip 4 reserved bytes
        bytes.read_uint32();

        // get the valid flags
        const uint16 flags = bytes.read_uint16();

        // get whether points are valid or invalid from the flags
        const bool rfBandValid   = pointIsValid(flags, RF_BAND_VALID);
        const bool jammingValid  = pointIsValid(flags, JAMMING_VALID);
        const bool spoofingValid = pointIsValid(flags, SPOOFING_VALID);

        // identifiers
        const auto chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        MipChannelIdentifiers addlIds = {
            MipChannelIdentifier(MipChannelIdentifier::Type::GNSS_RF_BAND, rfBand)
        };

        // add data points for the values collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_JAMMING_STATE,  addlIds, valueType_uint8, anyType(jammingState),  jammingValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_SPOOFING_STATE, addlIds, valueType_uint8, anyType(spoofingState), spoofingValid));
    }

    bool FieldParser_GnssRFErrorDetection::registerParser()
    {
        static FieldParser_GnssRFErrorDetection p;
        return registerGnssParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_GnssSatelliteStatus
    const MipTypes::ChannelField FieldParser_GnssSatelliteStatus::FIELD_TYPE = MipTypes::CH_FIELD_GNSS_SATELLITE_STATUS;
    const bool FieldParser_GnssSatelliteStatus::REGISTERED = FieldParser_GnssSatelliteStatus::registerParser();    //register the parser immediately

    void FieldParser_GnssSatelliteStatus::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        uint8 index = bytes.read_uint8();
        uint8 count = bytes.read_uint8();

        double tow = bytes.read_double();
        uint16 weekNum = bytes.read_uint16();

        uint8 gnssId = bytes.read_uint8();
        uint8 satelliteId = bytes.read_uint8();

        float elevation = bytes.read_float();
        float azimuth = bytes.read_float();
        bool health = bytes.read_uint8() > 0;

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool towValid = pointIsValid(flags, TOW_VALID);
        bool weekNumValid = pointIsValid(flags, WEEK_NUMBER_VALID);
        bool elevationValid = pointIsValid(flags, ELEVATION_VALID);
        bool azimuthValid = pointIsValid(flags, AZIMUTH_VALID);
        bool healthValid = pointIsValid(flags, HEALTH_VALID);

        // identifiers
        MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        MipChannelIdentifiers addlIds = {
            MipChannelIdentifier(MipChannelIdentifier::Type::GNSS_CONSTELLATION, gnssId),
            MipChannelIdentifier(MipChannelIdentifier::Type::GNSS_SATELLITE_ID, satelliteId)
        };

        //add data points for the values we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_INDEX, addlIds, valueType_uint8, anyType(index)));
        result.push_back(MipDataPoint(chField, MipTypes::CH_COUNT, addlIds, valueType_uint8, anyType(count)));

        result.push_back(MipDataPoint(chField, MipTypes::CH_TIME_OF_WEEK, addlIds, valueType_double, anyType(tow), towValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_WEEK_NUMBER, addlIds, valueType_uint16, anyType(weekNum), weekNumValid));

        result.push_back(MipDataPoint(chField, MipTypes::CH_ELEVATION, addlIds, valueType_float, anyType(elevation), elevationValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_AZIMUTH, addlIds, valueType_float, anyType(azimuth), azimuthValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_HEALTH, addlIds, valueType_bool, anyType(health), healthValid));
    }

    bool FieldParser_GnssSatelliteStatus::registerParser()
    {
        static FieldParser_GnssSatelliteStatus p;
        return MipGnssFieldParser::registerGnssParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_GnssRawObservation
    const MipTypes::ChannelField FieldParser_GnssRawObservation::FIELD_TYPE = MipTypes::CH_FIELD_GNSS_RAW_OBSERVATION;
    const bool FieldParser_GnssRawObservation::REGISTERED = FieldParser_GnssRawObservation::registerParser();    //register the parser immediately

    void FieldParser_GnssRawObservation::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        uint8 index = bytes.read_uint8();
        uint8 count = bytes.read_uint8();

        double tow = bytes.read_double();
        uint16 weekNum = bytes.read_uint16();

        uint16 recId = bytes.read_uint16();

        // tracking channel will currently always be 0 - read over the bytes, but don't bother storing it
        bytes.read_uint8();

        uint8 gnssId = bytes.read_uint8();
        uint8 satelliteId = bytes.read_uint8();
        uint8 signalId = bytes.read_uint8();

        float signalStrenth = bytes.read_float();
        uint8 signalQuality = bytes.read_uint8();

        double pseudorange = bytes.read_double();
        double carrierPhase = bytes.read_double();
        float doppler = bytes.read_float();

        float rangeUnc = bytes.read_float();
        float phaseUnc = bytes.read_float();
        float dopplerUnc = bytes.read_float();

        float lockTime = bytes.read_float();


        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool towValid = pointIsValid(flags, TOW_VALID);
        bool weekNumValid = pointIsValid(flags, WEEK_NUMBER_VALID);

        //bool chIdValid = pointIsValid(flags, CHANNEL_VALID);
        bool signalStrenthValid = pointIsValid(flags, SIGNAL_STRENGTH_VALID);
        bool qualityValid = pointIsValid(flags, QUALITY_VALID);
        bool psuedorangeValid = pointIsValid(flags, PSEUDORANGE_VALID);
        bool carrierPhaseValid = pointIsValid(flags, CARRIER_PHASE_VALID);
        bool dopplerValid = pointIsValid(flags, DOPPLER_VALID);
        bool rangeUncValid = pointIsValid(flags, RANGE_UNC_VALID);
        bool carrierPhaseUncValid = pointIsValid(flags, CARRIER_PHASE_UNC_VALID);
        bool dopplerUncValid = pointIsValid(flags, DOPPLER_UNC_VALID);
        bool lockTimeValid = pointIsValid(flags, LOCK_TIME_VALID);

        // identifiers
        MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        MipChannelIdentifiers addlIds = {
            MipChannelIdentifier(MipChannelIdentifier::Type::GNSS_RECEIVER_ID, recId),
            MipChannelIdentifier(MipChannelIdentifier::Type::GNSS_CONSTELLATION, gnssId),
            MipChannelIdentifier(MipChannelIdentifier::Type::GNSS_SATELLITE_ID, satelliteId),
            MipChannelIdentifier(MipChannelIdentifier::Type::GNSS_SIGNAL_ID, signalId)
        };

        //add data points for the values we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_INDEX, addlIds, valueType_uint8, anyType(index)));
        result.push_back(MipDataPoint(chField, MipTypes::CH_COUNT, addlIds, valueType_uint8, anyType(count)));

        // don't include tracking channel for now - currently never populate, will always be 0
        //result.push_back(MipDataPoint(chField, MipTypes::CH_CHANNEL, addlIds, valueType_uint8, chId, chIdValid));

        result.push_back(MipDataPoint(chField, MipTypes::CH_TIME_OF_WEEK, addlIds, valueType_double, anyType(tow), towValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_WEEK_NUMBER, addlIds, valueType_uint16, anyType(weekNum), weekNumValid));

        result.push_back(MipDataPoint(chField, MipTypes::CH_SIGNAL_STRENGTH, addlIds, valueType_float, anyType(signalStrenth), signalStrenthValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_SIGNAL_QUALITY, addlIds, valueType_uint8, anyType(signalQuality), qualityValid));

        result.push_back(MipDataPoint(chField, MipTypes::CH_RANGE, addlIds, valueType_double, anyType(pseudorange), psuedorangeValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_CARRIER_PHASE, addlIds, valueType_double, anyType(carrierPhase), carrierPhaseValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_DOPPLER, addlIds, valueType_float, anyType(doppler), dopplerValid));

        result.push_back(MipDataPoint(chField, MipTypes::CH_RANGE_UNC, addlIds, valueType_float, anyType(rangeUnc), rangeUncValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_CARRIER_PHASE_UNC, addlIds, valueType_float, anyType(phaseUnc), carrierPhaseUncValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_DOPPLER_UNC, addlIds, valueType_float, anyType(dopplerUnc), dopplerUncValid));

        result.push_back(MipDataPoint(chField, MipTypes::CH_DELTA_TIME, addlIds, valueType_float, anyType(lockTime), lockTimeValid));
    }

    bool FieldParser_GnssRawObservation::registerParser()
    {
        static FieldParser_GnssRawObservation p;
        return MipGnssFieldParser::registerGnssParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_GnssStationInfo
    const MipTypes::ChannelField FieldParser_GnssStationInfo::FIELD_TYPE = MipTypes::CH_FIELD_GNSS_STATION_INFO;
    const bool FieldParser_GnssStationInfo::REGISTERED = FieldParser_GnssStationInfo::registerParser();    //register the parser immediately

    void FieldParser_GnssStationInfo::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        double tow = bytes.read_double();
        uint16 weekNum = bytes.read_uint16();

        double posX = bytes.read_double();
        double posY = bytes.read_double();
        double posZ = bytes.read_double();

        float height = bytes.read_float();

        uint16 stationId = bytes.read_uint16();
        uint16 indicators = bytes.read_uint16();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool towValid = pointIsValid(flags, TOW_VALID);
        bool weekNumValid = pointIsValid(flags, WEEK_NUMBER_VALID);
        bool ecefPosValid = pointIsValid(flags, ECEF_POS_VALID);
        bool heightValid = pointIsValid(flags, HEIGHT_VALID);
        bool indicatorsValid = pointIsValid(flags, INDICATORS_VALID);

        // identifiers
        MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        MipChannelIdentifiers addlIds = {
            MipChannelIdentifier(MipChannelIdentifier::Type::GNSS_BASE_STATION_ID, stationId)
        };

        //add data points for the values we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_TIME_OF_WEEK, addlIds, valueType_double, anyType(tow), towValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_WEEK_NUMBER, addlIds, valueType_uint16, anyType(weekNum), weekNumValid));

        result.push_back(MipDataPoint(chField, MipTypes::CH_X, addlIds, valueType_double, anyType(posX), ecefPosValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_Y, addlIds, valueType_double, anyType(posY), ecefPosValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_Z, addlIds, valueType_double, anyType(posZ), ecefPosValid));

        result.push_back(MipDataPoint(chField, MipTypes::CH_HEIGHT, addlIds, valueType_float, anyType(height), heightValid));

        result.push_back(MipDataPoint(chField, MipTypes::CH_STATUS, addlIds, valueType_uint16, anyType(indicators), indicatorsValid));
    }

    bool FieldParser_GnssStationInfo::registerParser()
    {
        static FieldParser_GnssStationInfo p;
        return MipGnssFieldParser::registerGnssParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_RTKCorrectionsStatus
    const MipTypes::ChannelField FieldParser_RTKCorrectionsStatus::FIELD_TYPE = MipTypes::CH_FIELD_GNSS_RTK_CORRECTIONS_STATUS;
    const bool FieldParser_RTKCorrectionsStatus::REGISTERED = FieldParser_RTKCorrectionsStatus::registerParser();    //register the parser immediately

    void FieldParser_RTKCorrectionsStatus::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        double tow = bytes.read_double();
        uint16 weekNum = bytes.read_uint16();
        uint16 epochStatus = bytes.read_uint16();
        uint32 rtkStatus = bytes.read_uint32();
        float gpsCorrectionLatency = bytes.read_float();
        float glonassCorrectionLatency = bytes.read_float();
        float galileoCorrectionLatency = bytes.read_float();
        float beidouCorrectionLatency = bytes.read_float();
        bytes.read_uint32();
        bytes.read_uint32();
        bytes.read_uint32();
        bytes.read_uint32();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool towValid = pointIsValid(flags, TOW_VALID);
        bool weekNumValid = pointIsValid(flags, WEEK_NUMBER_VALID);
        bool epochStatusValid = pointIsValid(flags, EPOCH_STATUS_VALID);
        bool rtkStatusValid = pointIsValid(flags, RTK_STATUS_VALID);
        bool gpsValid = pointIsValid(flags, GPS_LATENCY_VALID);
        bool glonassValid = pointIsValid(flags, GLONASS_LATENCY_VALID);
        bool galileoValid = pointIsValid(flags, GALILEO_LATENCY_VALID);
        bool beidouValid = pointIsValid(flags, BEIDOU_LATENCY_VALID);

        MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        //add data points for the values we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_TIME_OF_WEEK, valueType_double, anyType(tow), towValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_WEEK_NUMBER, valueType_uint16, anyType(weekNum), weekNumValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_STATUS, valueType_uint16, anyType(epochStatus), epochStatusValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_FLAGS, valueType_uint32, anyType(rtkStatus), rtkStatusValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_GPS_CORRECTION_LATENCY, valueType_float, anyType(gpsCorrectionLatency), gpsValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_GLONASS_CORRECTION_LATENCY, valueType_float, anyType(glonassCorrectionLatency), glonassValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_GALILEO_CORRECTION_LATENCY, valueType_float, anyType(galileoCorrectionLatency), galileoValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_BEIDOU_CORRECTION_LATENCY, valueType_float, anyType(beidouCorrectionLatency), beidouValid));
    }

    bool FieldParser_RTKCorrectionsStatus::registerParser()
    {
        static FieldParser_RTKCorrectionsStatus p;
        return MipGnssFieldParser::registerGnssParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_GPSIonosphericCorrection
    const MipTypes::ChannelField FieldParser_GPSIonosphericCorrection::FIELD_TYPE = MipTypes::CH_FIELD_GNSS_GPS_IONOSPHERIC_CORRECTION;
    const bool FieldParser_GPSIonosphericCorrection::REGISTERED = FieldParser_GPSIonosphericCorrection::registerParser();    //register the parser immediately

    void FieldParser_GPSIonosphericCorrection::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        double timeOfWeek = bytes.read_double();
        uint16 weekNumber = bytes.read_uint16();

        ByteStream alphaData;
        for (int i = 0; i < 4; i++)
        {
            alphaData.append_double(bytes.read_double());
        }
        Vector alpha(valueType_double, alphaData);

        ByteStream betaData;
        for (int i = 0; i < 4; i++)
        {
            betaData.append_double(bytes.read_double());
        }
        Vector beta(valueType_double, betaData);

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool timeOfWeekValid = pointIsValid(flags, TIME_OF_WEEK_VALID);
        bool weekNumberValid = pointIsValid(flags, WEEK_NUMBER_VALID);
        bool alphaValid = pointIsValid(flags, ALPHA_VALID);
        bool betaValid = pointIsValid(flags, BETA_VALID);

        MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        //add data points for the values we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_TIME_OF_WEEK, valueType_double, anyType(timeOfWeek), timeOfWeekValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_WEEK_NUMBER, valueType_uint16, anyType(weekNumber), weekNumberValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_ALPHA, valueType_Vector, anyType(alpha), alphaValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_BETA, valueType_Vector, anyType(beta), betaValid));
    }

    bool FieldParser_GPSIonosphericCorrection::registerParser()
    {
        static FieldParser_GPSIonosphericCorrection p;
        return MipGnssFieldParser::registerGnssParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================


    //=====================================================================================================================================================
    //                                                        FieldParser_IonosphericCorrection
    const MipTypes::ChannelField FieldParser_IonosphericCorrection::FIELD_TYPE = MipTypes::CH_FIELD_GNSS_GALILEO_IONOSPHERIC_CORRECTION;
    const bool FieldParser_IonosphericCorrection::REGISTERED = FieldParser_IonosphericCorrection::registerParser();    //register the parser immediately

    void FieldParser_IonosphericCorrection::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        double timeOfWeek = bytes.read_double();
        uint16 weekNumber = bytes.read_uint16();

        ByteStream alphaData;
        for (int i = 0; i < 3; i++)
        {
            alphaData.append_double(bytes.read_double());
        }
        Vector alpha(valueType_double, alphaData);
        uint8 disturbanceFlags = bytes.read_uint8();

        //get the valid flags
        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool timeOfWeekValid = pointIsValid(flags, TIME_OF_WEEK_VALID);
        bool weekNumberValid = pointIsValid(flags, WEEK_NUMBER_VALID);
        bool alphaValid = pointIsValid(flags, ALPHA_VALID);
        bool disturbanceFlagsValid = pointIsValid(flags, DISTURBANCE_FLAGS_VALID);

        MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        //add data points for the values we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_TIME_OF_WEEK, valueType_double , anyType(timeOfWeek), timeOfWeekValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_WEEK_NUMBER, valueType_uint16, anyType(weekNumber), weekNumberValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_ALPHA, valueType_Vector, anyType(alpha), alphaValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_DISTURBANCE_FLAGS, valueType_uint8, anyType(disturbanceFlags), disturbanceFlagsValid));
    }

    bool FieldParser_IonosphericCorrection::registerParser()
    {
        static FieldParser_IonosphericCorrection p;
        return MipGnssFieldParser::registerGnssParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================
}
