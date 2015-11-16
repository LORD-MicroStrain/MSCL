/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "InertialFieldParser_GPS.h"
#include "InertialDataPacket.h"
#include "mscl/MicroStrain/DataBuffer.h"

namespace mscl
{
    //the classes in this file do not get referenced anywhere, therefore the 
    //linker will not include this compilation unit when statically 
    //linking to an executable. Defining this variable, and then using it
    //elsewhere, will force this file to be included
    bool _forceLibraryToIncludeCompilationUnit_GPS;

    //=====================================================================================================================================================
    //                                                        FieldParser_LLHPosition
    const InertialTypes::ChannelField FieldParser_LLHPosition::FIELD_TYPE = InertialTypes::CH_FIELD_GPS_LLH_POSITION;
    const bool FieldParser_LLHPosition::REGISTERED = FieldParser_LLHPosition::registerParser();    //register the parser immediately

    void FieldParser_LLHPosition::parse(const InertialDataField& field, InertialDataPoints& result) const
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

        //add all the data points we just collected
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_LATITUDE, valueType_double, anyType(latitude), latLongValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_LONGITUDE, valueType_double, anyType(longitude), latLongValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_HEIGHT_ABOVE_ELLIPSOID, valueType_double, anyType(heightAboveEllipsoid), ellipsoidValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_HEIGHT_ABOVE_MSL, valueType_double, anyType(heightAboveMSL), mslValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_HORIZONTAL_ACCURACY, valueType_float, anyType(horizAccuracy), horizValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_VERTICAL_ACCURACY, valueType_float, anyType(vertAccuracy), vertValid));
    }

    bool FieldParser_LLHPosition::registerParser()
    {
        //create a static parser object
        static FieldParser_LLHPosition p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_ECEFPosition
    const InertialTypes::ChannelField FieldParser_ECEFPosition::FIELD_TYPE = InertialTypes::CH_FIELD_GPS_ECEF_POSITION;
    const bool FieldParser_ECEFPosition::REGISTERED = FieldParser_ECEFPosition::registerParser();    //register the parser immediately

    void FieldParser_ECEFPosition::parse(const InertialDataField& field, InertialDataPoints& result) const
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

        //add all the data points we just collected
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_X, valueType_double, anyType(xPos), ecefPosValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Y, valueType_double, anyType(yPos), ecefPosValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Z, valueType_double, anyType(zPos), ecefPosValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_POSITION_ACCURACY, valueType_float, anyType(posAccuracy), posAccurValid));
    }

    bool FieldParser_ECEFPosition::registerParser()
    {
        //create a static parser object
        static FieldParser_ECEFPosition p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_NEDVelocity
    const InertialTypes::ChannelField FieldParser_NEDVelocity::FIELD_TYPE = InertialTypes::CH_FIELD_GPS_NED_VELOCITY;
    const bool FieldParser_NEDVelocity::REGISTERED = FieldParser_NEDVelocity::registerParser();    //register the parser immediately

    void FieldParser_NEDVelocity::parse(const InertialDataField& field, InertialDataPoints& result) const
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

        //add all the data points we just collected
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_NORTH, valueType_float, anyType(north), nedVelocityValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_EAST, valueType_float, anyType(east), nedVelocityValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_DOWN, valueType_float, anyType(down), nedVelocityValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_SPEED, valueType_float, anyType(speed), speedValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_GROUND_SPEED, valueType_float, anyType(groundSpeed), groundSpeedValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_HEADING, valueType_float, anyType(heading), headingValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_SPEED_ACCURACY, valueType_float, anyType(speedAccuracy), speedAccurValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_HEADING_ACCURACY, valueType_float, anyType(headingAccuracy), headingAccurValid));
    }

    bool FieldParser_NEDVelocity::registerParser()
    {
        //create a static parser object
        static FieldParser_NEDVelocity p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_ECEFVelocity
    const InertialTypes::ChannelField FieldParser_ECEFVelocity::FIELD_TYPE = InertialTypes::CH_FIELD_GPS_ECEF_VELOCITY;
    const bool FieldParser_ECEFVelocity::REGISTERED = FieldParser_ECEFVelocity::registerParser();    //register the parser immediately

    void FieldParser_ECEFVelocity::parse(const InertialDataField& field, InertialDataPoints& result) const
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

        //add all the data points we just collected
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_X, valueType_float, anyType(xVelocity), ecefVelocityValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Y, valueType_float, anyType(yVelocity), ecefVelocityValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_Z, valueType_float, anyType(zVelocity), ecefVelocityValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_VELOCITY_ACCURACY, valueType_float, anyType(velocityAccuracy), accuracyValid));
    }

    bool FieldParser_ECEFVelocity::registerParser()
    {
        //create a static parser object
        static FieldParser_ECEFVelocity p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_DOP
    const InertialTypes::ChannelField FieldParser_DOP::FIELD_TYPE = InertialTypes::CH_FIELD_GPS_DOP;
    const bool FieldParser_DOP::REGISTERED = FieldParser_DOP::registerParser();    //register the parser immediately

    void FieldParser_DOP::parse(const InertialDataField& field, InertialDataPoints& result) const
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

        //add all the data points we just collected
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_GEOMETRIC_DOP, valueType_float, anyType(geometric), gValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_POSITION_DOP, valueType_float, anyType(position), pValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_HORIZONTAL_DOP, valueType_float, anyType(horizontal), hValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_VERTICAL_DOP, valueType_float, anyType(vertical), vValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_TIME_DOP, valueType_float, anyType(time), tValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_NORTHING_DOP, valueType_float, anyType(northing), nValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_EASTING_DOP, valueType_float, anyType(easting), eValid));
    }

    bool FieldParser_DOP::registerParser()
    {
        //create a static parser object
        static FieldParser_DOP p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_UTCTime
    const InertialTypes::ChannelField FieldParser_UTCTime::FIELD_TYPE = InertialTypes::CH_FIELD_GPS_UTC_TIME;
    const bool FieldParser_UTCTime::REGISTERED = FieldParser_UTCTime::registerParser();    //register the parser immediately

    void FieldParser_UTCTime::parse(const InertialDataField& field, InertialDataPoints& result) const
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

        //add all the data points we just collected
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_TIMESTAMP, valueType_Timestamp, anyType(time), fullTimestampValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_FLAGS, valueType_uint16, anyType(flags), true));
    }

    bool FieldParser_UTCTime::registerParser()
    {
        //create a static parser object
        static FieldParser_UTCTime p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_GPSTime
    const InertialTypes::ChannelField FieldParser_GPSTime::FIELD_TYPE = InertialTypes::CH_FIELD_GPS_GPS_TIME;
    const bool FieldParser_GPSTime::REGISTERED = FieldParser_GPSTime::registerParser();    //register the parser immediately

    void FieldParser_GPSTime::parse(const InertialDataField& field, InertialDataPoints& result) const
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

        //add data points for the values we just collected
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_TIME_OF_WEEK, valueType_double, anyType(gpsTimeOfWeek), towValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_WEEK_NUMBER, valueType_uint16, anyType(gpsWeekNumber), weekValid));
    }

    bool FieldParser_GPSTime::registerParser()
    {
        //create a static parser object
        static FieldParser_GPSTime p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_ClockInfo
    const InertialTypes::ChannelField FieldParser_ClockInfo::FIELD_TYPE = InertialTypes::CH_FIELD_GPS_CLOCK_INFO;
    const bool FieldParser_ClockInfo::REGISTERED = FieldParser_ClockInfo::registerParser();    //register the parser immediately

    void FieldParser_ClockInfo::parse(const InertialDataField& field, InertialDataPoints& result) const
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

        //add data points for the values we just collected
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_BIAS, valueType_double, anyType(clockBias), biasValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_DRIFT, valueType_double, anyType(clockDrift), driftValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_ACCURACY_ESTIMATE, valueType_double, anyType(accuracy), accurValid));
    }

    bool FieldParser_ClockInfo::registerParser()
    {
        //create a static parser object
        static FieldParser_ClockInfo p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_GPSFixInfo
    const InertialTypes::ChannelField FieldParser_GPSFixInfo::FIELD_TYPE = InertialTypes::CH_FIELD_GPS_FIX_INFO;
    const bool FieldParser_GPSFixInfo::REGISTERED = FieldParser_GPSFixInfo::registerParser();    //register the parser immediately

    void FieldParser_GPSFixInfo::parse(const InertialDataField& field, InertialDataPoints& result) const
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

        //add data points for the values we just collected
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_FIX_TYPE, valueType_uint8, anyType(fixType), fixTypeValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_SV_COUNT, valueType_uint8, anyType(numSvs), numSvsValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_FLAGS, valueType_uint16, anyType(fixFlags), fixFlagsValid));
    }

    bool FieldParser_GPSFixInfo::registerParser()
    {
        //create a static parser object
        static FieldParser_GPSFixInfo p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_SpaceVehicleInfo
    const InertialTypes::ChannelField FieldParser_SpaceVehicleInfo::FIELD_TYPE = InertialTypes::CH_FIELD_GPS_SPACE_VEHICLE_INFO;
    const bool FieldParser_SpaceVehicleInfo::REGISTERED = FieldParser_SpaceVehicleInfo::registerParser();    //register the parser immediately

    void FieldParser_SpaceVehicleInfo::parse(const InertialDataField& field, InertialDataPoints& result) const
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
        bool svIdValid        = pointIsValid(flags, SV_ID_VALID);
        bool ratioValid        = pointIsValid(flags, RATIO_VALID);
        bool azimuthValid    = pointIsValid(flags, AZIMUTH_VALID);
        bool elevationValid    = pointIsValid(flags, ELEVATION_VALID);
        bool svFlagsValid    = pointIsValid(flags, SV_FLAGS_VALID);

        //add data points for the values we just collected
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_CHANNEL, valueType_uint8, anyType(channel), channelValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_ID, valueType_uint8, anyType(vehicleId), svIdValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_CARRIER_TO_NOISE_RATIO, valueType_uint16, anyType(ratio), ratioValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_AZIMUTH, valueType_int16, anyType(azimuth), azimuthValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_ELEVATION, valueType_int16, anyType(elevation), elevationValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_FLAGS, valueType_uint16, anyType(svFlags), svFlagsValid));
    }

    bool FieldParser_SpaceVehicleInfo::registerParser()
    {
        //create a static parser object
        static FieldParser_SpaceVehicleInfo p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================



    //=====================================================================================================================================================
    //                                                        FieldParser_HardwareStatus
    const InertialTypes::ChannelField FieldParser_HardwareStatus::FIELD_TYPE = InertialTypes::CH_FIELD_GPS_HARDWARE_STATUS;
    const bool FieldParser_HardwareStatus::REGISTERED = FieldParser_HardwareStatus::registerParser();    //register the parser immediately

    void FieldParser_HardwareStatus::parse(const InertialDataField& field, InertialDataPoints& result) const
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

        //add data points for the values we just collected
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_SENSOR_STATE, valueType_uint8, anyType(sensorState), sensorStateValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_ANTENNA_STATE, valueType_uint8, anyType(antennaState), antennaStateValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_ANTENNA_POWER, valueType_uint8, anyType(antennaPower), antennaPowerValid));
    }

    bool FieldParser_HardwareStatus::registerParser()
    {
        //create a static parser object
        static FieldParser_HardwareStatus p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================


    //=====================================================================================================================================================
    //                                                        FieldParser_DGPSInfo
    const InertialTypes::ChannelField FieldParser_DGPSInfo::FIELD_TYPE = InertialTypes::CH_FIELD_GPS_DGPS_INFO;
    const bool FieldParser_DGPSInfo::REGISTERED = FieldParser_DGPSInfo::registerParser();    //register the parser immediately

    void FieldParser_DGPSInfo::parse(const InertialDataField& field, InertialDataPoints& result) const
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
        bool ageValid = pointIsValid(flags, LATEST_AGE_VALID);
        bool baseIdValid = pointIsValid(flags, BASE_ID_VALID);
        bool baseStatusValid = pointIsValid(flags, BASE_STATUS_VALID);
        bool numChsValid = pointIsValid(flags, NUM_CHANNELS_VALID);

        //add data points for the values we just collected
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_AGE, valueType_float, anyType(newestAge), ageValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_ID, valueType_int16, anyType(baseId), baseIdValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_STATUS, valueType_int16, anyType(baseStatus), baseStatusValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_NUM_CHANNELS, valueType_uint16, anyType(numChs), numChsValid));
    }

    bool FieldParser_DGPSInfo::registerParser()
    {
        //create a static parser object
        static FieldParser_DGPSInfo p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================


    //=====================================================================================================================================================
    //                                                        FieldParser_DGPSChannelStatus
    const InertialTypes::ChannelField FieldParser_DGPSChannelStatus::FIELD_TYPE = InertialTypes::CH_FIELD_GPS_DGPS_CHANNEL_STATUS;
    const bool FieldParser_DGPSChannelStatus::REGISTERED = FieldParser_DGPSChannelStatus::registerParser();    //register the parser immediately

    void FieldParser_DGPSChannelStatus::parse(const InertialDataField& field, InertialDataPoints& result) const
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
        bool ageValid = pointIsValid(flags, AGE_VALID);
        bool correctionValid = pointIsValid(flags, CORRECTION_VALID);
        bool rateCorrectionValid = pointIsValid(flags, RATE_CORRECTION_VALID);

        //add data points for the values we just collected
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_ID, valueType_uint8, anyType(spaceVehicleId), svIdValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_AGE, valueType_float, anyType(age), ageValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_CORRECTION, valueType_float, anyType(correction), correctionValid));
        result.push_back(InertialDataPoint(FIELD_TYPE, InertialTypes::CH_RATE_CORRECTION, valueType_float, anyType(rateCorrection), rateCorrectionValid));
    }

    bool FieldParser_DGPSChannelStatus::registerParser()
    {
        //create a static parser object
        static FieldParser_DGPSChannelStatus p;

        //register the parser
        return InertialFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================
}