/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "MipTypes.h"
#include "mscl/Utils.h"

namespace mscl
{
    std::string MipTypes::channelName(ChannelField field, ChannelQualifier qualifier)
    {
        // handle "duplicate" GNSS data sets
        ChannelField keyField = field;
        std::string prepend = "";
        if (MipTypes::isGnssChannelField(field))
        {
            keyField = MipTypes::getChannelField_baseDataClass(field);
            prepend = MipTypes::getChannelNamePrependText(field);
        }

        //try to find the channel in the map
        auto result = CHANNEL_NAMES.find(ChannelId(keyField, qualifier));

        //if we failed to find the channel
        if(result == CHANNEL_NAMES.end())
        {
            assert(false);
            return "unknown_" + Utils::toStr(field) + "-" + Utils::toStr(qualifier);
        }

        //replace any unsupported sensorcloud characters
        std::string sensorcloudFilteredName = prepend + result->second;
        Utils::filterSensorcloudName(sensorcloudFilteredName);

        //found the channel, return the name
        return sensorcloudFilteredName;
    }

    MipTypes::DataClass MipTypes::channelFieldToDataClass(MipTypes::ChannelField channelField)
    {
        return static_cast<DataClass>(Utils::msb(static_cast<uint16>(channelField)));
    }

    size_t MipTypes::ChannelIdHash::operator()(const MipTypes::ChannelId& channelId) const
    {
        return channelId.first ^ channelId.second;
    }

    const std::unordered_map<MipTypes::ChannelId, std::string, MipTypes::ChannelIdHash> MipTypes::CHANNEL_NAMES(
    {
        {ChannelId(CH_FIELD_SENSOR_RAW_ACCEL_VEC, CH_X), "rawAccelX"},
        {ChannelId(CH_FIELD_SENSOR_RAW_ACCEL_VEC, CH_Y), "rawAccelY"},
        {ChannelId(CH_FIELD_SENSOR_RAW_ACCEL_VEC, CH_Z), "rawAccelZ"},

        {ChannelId(CH_FIELD_SENSOR_RAW_GYRO_VEC, CH_X), "rawGyroX"},
        {ChannelId(CH_FIELD_SENSOR_RAW_GYRO_VEC, CH_Y), "rawGyroY"},
        {ChannelId(CH_FIELD_SENSOR_RAW_GYRO_VEC, CH_Z), "rawGyroZ"},

        {ChannelId(CH_FIELD_SENSOR_RAW_MAG_VEC, CH_X), "rawMagX"},
        {ChannelId(CH_FIELD_SENSOR_RAW_MAG_VEC, CH_Y), "rawMagY"},
        {ChannelId(CH_FIELD_SENSOR_RAW_MAG_VEC, CH_Z), "rawMagZ"},

        {ChannelId(CH_FIELD_SENSOR_SCALED_ACCEL_VEC, CH_X), "scaledAccelX"},
        {ChannelId(CH_FIELD_SENSOR_SCALED_ACCEL_VEC, CH_Y), "scaledAccelY"},
        {ChannelId(CH_FIELD_SENSOR_SCALED_ACCEL_VEC, CH_Z), "scaledAccelZ"},

        {ChannelId(CH_FIELD_SENSOR_SCALED_GYRO_VEC, CH_X), "scaledGyroX"},
        {ChannelId(CH_FIELD_SENSOR_SCALED_GYRO_VEC, CH_Y), "scaledGyroY"},
        {ChannelId(CH_FIELD_SENSOR_SCALED_GYRO_VEC, CH_Z), "scaledGyroZ"},

        {ChannelId(CH_FIELD_SENSOR_SCALED_MAG_VEC, CH_X), "scaledMagX"},
        {ChannelId(CH_FIELD_SENSOR_SCALED_MAG_VEC, CH_Y), "scaledMagY"},
        {ChannelId(CH_FIELD_SENSOR_SCALED_MAG_VEC, CH_Z), "scaledMagZ"},

        {ChannelId(CH_FIELD_SENSOR_DELTA_THETA_VEC, CH_X), "deltaThetaX"},
        {ChannelId(CH_FIELD_SENSOR_DELTA_THETA_VEC, CH_Y), "deltaThetaY"},
        {ChannelId(CH_FIELD_SENSOR_DELTA_THETA_VEC, CH_Z), "deltaThetaZ"},

        {ChannelId(CH_FIELD_SENSOR_DELTA_VELOCITY_VEC, CH_X), "deltaVelX"},
        {ChannelId(CH_FIELD_SENSOR_DELTA_VELOCITY_VEC, CH_Y), "deltaVelY"},
        {ChannelId(CH_FIELD_SENSOR_DELTA_VELOCITY_VEC, CH_Z), "deltaVelZ"},

        {ChannelId(CH_FIELD_SENSOR_ORIENTATION_MATRIX, CH_MATRIX), "orientMatrix"},

        {ChannelId(CH_FIELD_SENSOR_ORIENTATION_QUATERNION, CH_QUATERNION), "orientQuaternion"},

        {ChannelId(CH_FIELD_SENSOR_ORIENTATION_UPDATE_MATRIX, CH_MATRIX), "orientUpdateMatrix"},

        {ChannelId(CH_FIELD_SENSOR_EULER_ANGLES, CH_ROLL), "roll"},
        {ChannelId(CH_FIELD_SENSOR_EULER_ANGLES, CH_PITCH), "pitch"},
        {ChannelId(CH_FIELD_SENSOR_EULER_ANGLES, CH_YAW), "yaw"},

        {ChannelId(CH_FIELD_SENSOR_INTERNAL_TIMESTAMP, CH_TICK), "internalTimestamp"},

        {ChannelId(CH_FIELD_SENSOR_BEACONED_TIMESTAMP, CH_TIMESTAMP), "beaconedTimestamp"},

        {ChannelId(CH_FIELD_SENSOR_STABILIZED_MAG_VEC, CH_X), "stabilizedMagX"},
        {ChannelId(CH_FIELD_SENSOR_STABILIZED_MAG_VEC, CH_Y), "stabilizedMagY"},
        {ChannelId(CH_FIELD_SENSOR_STABILIZED_MAG_VEC, CH_Z), "stabilizedMagZ"},

        {ChannelId(CH_FIELD_SENSOR_STABILIZED_ACCEL_VEC, CH_X), "stabilizedAccelX"},
        {ChannelId(CH_FIELD_SENSOR_STABILIZED_ACCEL_VEC, CH_Y), "stabilizedAccelY"},
        {ChannelId(CH_FIELD_SENSOR_STABILIZED_ACCEL_VEC, CH_Z), "stabilizedAccelZ"},

        {ChannelId(CH_FIELD_SENSOR_GPS_CORRELATION_TIMESTAMP, CH_TIME_OF_WEEK), "gpsCorrelTimestampTow"},
        {ChannelId(CH_FIELD_SENSOR_GPS_CORRELATION_TIMESTAMP, CH_WEEK_NUMBER), "gpsCorrelTimestampWeekNum"},
        {ChannelId(CH_FIELD_SENSOR_GPS_CORRELATION_TIMESTAMP, CH_FLAGS), "gpsCorrelTimestampFlags"},

        {ChannelId(CH_FIELD_SENSOR_SCALED_AMBIENT_PRESSURE, CH_PRESSURE), "scaledAmbientPressure"},

        {ChannelId(CH_FIELD_SENSOR_RAW_AMBIENT_PRESSURE, CH_PRESSURE), "rawAmbientPressure"},

        {ChannelId(CH_FIELD_SENSOR_TEMPERATURE_STATISTICS, CH_MIN_TEMP), "minTemp"},
        {ChannelId(CH_FIELD_SENSOR_TEMPERATURE_STATISTICS, CH_MAX_TEMP), "maxTemp"},
        {ChannelId(CH_FIELD_SENSOR_TEMPERATURE_STATISTICS, CH_MEAN_TEMP), "meanTemp"},

        {ChannelId(CH_FIELD_GNSS_LLH_POSITION, CH_LATITUDE), "latitude"},
        {ChannelId(CH_FIELD_GNSS_LLH_POSITION, CH_LONGITUDE), "longitude"},
        {ChannelId(CH_FIELD_GNSS_LLH_POSITION, CH_HEIGHT_ABOVE_ELLIPSOID), "heightAboveElipsoid"},
        {ChannelId(CH_FIELD_GNSS_LLH_POSITION, CH_HEIGHT_ABOVE_MSL), "heightAboveMSL"},
        {ChannelId(CH_FIELD_GNSS_LLH_POSITION, CH_HORIZONTAL_ACCURACY), "horizontalAccuracy"},
        {ChannelId(CH_FIELD_GNSS_LLH_POSITION, CH_VERTICAL_ACCURACY), "verticalAccuracy"},

        {ChannelId(CH_FIELD_GNSS_ECEF_POSITION, CH_X), "ecefPosX"},
        {ChannelId(CH_FIELD_GNSS_ECEF_POSITION, CH_Y), "ecefPosY"},
        {ChannelId(CH_FIELD_GNSS_ECEF_POSITION, CH_Z), "ecefPosZ"},
        {ChannelId(CH_FIELD_GNSS_ECEF_POSITION, CH_POSITION_ACCURACY), "ecefPosAccuracy"},

        {ChannelId(CH_FIELD_GNSS_NED_VELOCITY, CH_NORTH), "northVelocity"},
        {ChannelId(CH_FIELD_GNSS_NED_VELOCITY, CH_EAST), "eastVelocity"},
        {ChannelId(CH_FIELD_GNSS_NED_VELOCITY, CH_DOWN), "downVelocity"},
        {ChannelId(CH_FIELD_GNSS_NED_VELOCITY, CH_SPEED), "speed"},
        {ChannelId(CH_FIELD_GNSS_NED_VELOCITY, CH_GROUND_SPEED), "groundSpeed"},
        {ChannelId(CH_FIELD_GNSS_NED_VELOCITY, CH_HEADING), "heading"},
        {ChannelId(CH_FIELD_GNSS_NED_VELOCITY, CH_SPEED_ACCURACY), "speedAccuracy"},
        {ChannelId(CH_FIELD_GNSS_NED_VELOCITY, CH_HEADING_ACCURACY), "headingAccuracy"},

        {ChannelId(CH_FIELD_GNSS_ECEF_VELOCITY, CH_X), "ecefVelX"},
        {ChannelId(CH_FIELD_GNSS_ECEF_VELOCITY, CH_Y), "ecefVelY"},
        {ChannelId(CH_FIELD_GNSS_ECEF_VELOCITY, CH_Z), "ecefVelZ"},
        {ChannelId(CH_FIELD_GNSS_ECEF_VELOCITY, CH_VELOCITY_ACCURACY), "ecefVelAccuracy"},

        {ChannelId(CH_FIELD_GNSS_DOP, CH_GEOMETRIC_DOP), "geometricDOP"},
        {ChannelId(CH_FIELD_GNSS_DOP, CH_POSITION_DOP), "positionDOP"},
        {ChannelId(CH_FIELD_GNSS_DOP, CH_HORIZONTAL_DOP), "horizontalDOP"},
        {ChannelId(CH_FIELD_GNSS_DOP, CH_VERTICAL_DOP), "verticalDOP"},
        {ChannelId(CH_FIELD_GNSS_DOP, CH_TIME_DOP), "timeDOP"},
        {ChannelId(CH_FIELD_GNSS_DOP, CH_NORTHING_DOP), "northingDOP"},
        {ChannelId(CH_FIELD_GNSS_DOP, CH_EASTING_DOP), "eastingDOP"},

        {ChannelId(CH_FIELD_GNSS_UTC_TIME, CH_TIMESTAMP), "utcTimestamp"},
        {ChannelId(CH_FIELD_GNSS_UTC_TIME, CH_FLAGS), "utcTimestampFlags"},

        {ChannelId(CH_FIELD_GNSS_GPS_TIME, CH_TIME_OF_WEEK), "gpsTimeTow"},
        {ChannelId(CH_FIELD_GNSS_GPS_TIME, CH_WEEK_NUMBER), "gpsTimeWeekNum"},

        {ChannelId(CH_FIELD_GNSS_CLOCK_INFO, CH_BIAS), "gpsClockBias"},
        {ChannelId(CH_FIELD_GNSS_CLOCK_INFO, CH_DRIFT), "gpsClockDrift"},
        {ChannelId(CH_FIELD_GNSS_CLOCK_INFO, CH_ACCURACY_ESTIMATE), "gpsClockAccuracy"},

        {ChannelId(CH_FIELD_GNSS_FIX_INFO, CH_FIX_TYPE), "gnssFixType"},
        {ChannelId(CH_FIELD_GNSS_FIX_INFO, CH_SV_COUNT), "gnssFixSvCount"},
        {ChannelId(CH_FIELD_GNSS_FIX_INFO, CH_FLAGS), "gnssFixFlags"},

        {ChannelId(CH_FIELD_GNSS_SPACE_VEHICLE_INFO, CH_CHANNEL), "spaceVehicleChannel"},
        {ChannelId(CH_FIELD_GNSS_SPACE_VEHICLE_INFO, CH_ID), "spaceVehicleId"},
        {ChannelId(CH_FIELD_GNSS_SPACE_VEHICLE_INFO, CH_CARRIER_TO_NOISE_RATIO), "spaceVehicleCarrierToNoiseRatio"},
        {ChannelId(CH_FIELD_GNSS_SPACE_VEHICLE_INFO, CH_AZIMUTH), "spaceVehicleAzimuth"},
        {ChannelId(CH_FIELD_GNSS_SPACE_VEHICLE_INFO, CH_ELEVATION), "spaceVehicleElevation"},
        {ChannelId(CH_FIELD_GNSS_SPACE_VEHICLE_INFO, CH_FLAGS), "spaceVehicleFlags"},

        {ChannelId(CH_FIELD_GNSS_HARDWARE_STATUS, CH_SENSOR_STATE), "sensorState"},
        {ChannelId(CH_FIELD_GNSS_HARDWARE_STATUS, CH_ANTENNA_STATE), "antennaState"},
        {ChannelId(CH_FIELD_GNSS_HARDWARE_STATUS, CH_ANTENNA_POWER), "antennaPower"},

        {ChannelId(CH_FIELD_GNSS_DGNSS_INFO, CH_AGE), "dgnssNewestAge"},
        {ChannelId(CH_FIELD_GNSS_DGNSS_INFO, CH_ID), "dgnssBaseStationId"},
        {ChannelId(CH_FIELD_GNSS_DGNSS_INFO, CH_STATUS), "dgnssBaseStationStatus"},
        {ChannelId(CH_FIELD_GNSS_DGNSS_INFO, CH_NUM_CHANNELS), "dgnssNumChannels"},

        {ChannelId(CH_FIELD_GNSS_DGNSS_CHANNEL_STATUS, CH_ID), "dgnssSpaceVehicleId"},
        {ChannelId(CH_FIELD_GNSS_DGNSS_CHANNEL_STATUS, CH_AGE), "dgnssAge"},
        {ChannelId(CH_FIELD_GNSS_DGNSS_CHANNEL_STATUS, CH_CORRECTION), "dgnssPseudorangeCorrection"},
        {ChannelId(CH_FIELD_GNSS_DGNSS_CHANNEL_STATUS, CH_RATE_CORRECTION), "dgnssPseudorangeRateCorrection"},

        { ChannelId(CH_FIELD_GNSS_CLOCK_INFO_2, CH_BIAS), "gpsClockBias" },
        { ChannelId(CH_FIELD_GNSS_CLOCK_INFO_2, CH_DRIFT), "gpsClockDrift" },
        { ChannelId(CH_FIELD_GNSS_CLOCK_INFO_2, CH_BIAS_ACCURACY_ESTIMATE), "gpsClockBiasAccuracy" },
        { ChannelId(CH_FIELD_GNSS_CLOCK_INFO_2, CH_DRIFT_ACCURACY_ESTIMATE), "gpsClockDriftAccuracy" },

        { ChannelId(CH_FIELD_GNSS_GPS_LEAP_SECONDS, CH_SECONDS), "gpsLeapSeconds" },

        { ChannelId(CH_FIELD_GNSS_RTK_CORRECTIONS_STATUS, CH_DATA_RECEIVED_EPOCH), "dataReceivedEpoch" },
        { ChannelId(CH_FIELD_GNSS_RTK_CORRECTIONS_STATUS, CH_NUM_PACKETS), "numPackets" },
        { ChannelId(CH_FIELD_GNSS_RTK_CORRECTIONS_STATUS, CH_STATUS), "rtkStatusFlags" },
        { ChannelId(CH_FIELD_GNSS_RTK_CORRECTIONS_STATUS, CH_GPS_CORRECTION_LATENCY), "gpsCorrectionLatency" },
        { ChannelId(CH_FIELD_GNSS_RTK_CORRECTIONS_STATUS, CH_GLONASS_CORRECTION_LATENCY), "glonassCorrectionLatency" },
        { ChannelId(CH_FIELD_GNSS_RTK_CORRECTIONS_STATUS, CH_GALILEO_CORRECTION_LATENCY), "galileoCorrectionLatency" },
        { ChannelId(CH_FIELD_GNSS_RTK_CORRECTIONS_STATUS, CH_BEIDOU_CORRECTION_LATENCY), "beidouCorrectionLatency" },

        { ChannelId(CH_FIELD_GNSS_GPS_IONOSPHERIC_CORRECTION, CH_TIME_OF_WEEK), "gpsCorrectionTimeOfWeek" },
        { ChannelId(CH_FIELD_GNSS_GPS_IONOSPHERIC_CORRECTION, CH_WEEK_NUMBER), "gpsCorrectionWeekNumber" },
        { ChannelId(CH_FIELD_GNSS_GPS_IONOSPHERIC_CORRECTION, CH_ALPHA), "gpsCorrectionAlpha" },
        { ChannelId(CH_FIELD_GNSS_GPS_IONOSPHERIC_CORRECTION, CH_BETA), "gpsCorrectionBeta" },

        { ChannelId(CH_FIELD_GNSS_IONOSPHERIC_CORRECTION, CH_TIME_OF_WEEK), "gnssCorrectionTimeOfWeek" },
        { ChannelId(CH_FIELD_GNSS_IONOSPHERIC_CORRECTION, CH_WEEK_NUMBER), "gnssCorrectionWeekNumber" },
        { ChannelId(CH_FIELD_GNSS_IONOSPHERIC_CORRECTION, CH_ALPHA), "gnssCorrectionAlpha" },
        { ChannelId(CH_FIELD_GNSS_IONOSPHERIC_CORRECTION, CH_DISTURBANCE_FLAGS), "gnssCorrectionDisturbanceFlags" },


        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_LLH_POS, CH_LATITUDE), "estLatitude"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_LLH_POS, CH_LONGITUDE), "estLongitude"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_LLH_POS, CH_HEIGHT_ABOVE_ELLIPSOID), "estHeightAboveElipsoid"},

        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_NED_VELOCITY, CH_NORTH), "estNorthVelocity"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_NED_VELOCITY, CH_EAST), "estEastVelocity"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_NED_VELOCITY, CH_DOWN), "estDownVelocity"},

        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_QUATERNION, CH_QUATERNION), "estOrientQuaternion"},

        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_MATRIX, CH_MATRIX), "estOrientMatrix"},

        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_EULER, CH_ROLL), "estRoll"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_EULER, CH_PITCH), "estPitch"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_EULER, CH_YAW), "estYaw"},

        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS, CH_X), "estGyroBiasX"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS, CH_Y), "estGyroBiasY"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS, CH_Z), "estGyroBiasZ"},

        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS, CH_X), "estAccelBiasX"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS, CH_Y), "estAccelBiasY"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS, CH_Z), "estAccelBiasZ"},

        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_LLH_UNCERT, CH_NORTH), "estNorthPositionUncert"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_LLH_UNCERT, CH_EAST), "estEastPositionUncert"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_LLH_UNCERT, CH_DOWN), "estDownPositionUncert"},

        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_NED_UNCERT, CH_NORTH), "estNorthVelocityUncert"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_NED_UNCERT, CH_EAST), "estEastVelocityUncert"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_NED_UNCERT, CH_DOWN), "estDownVelocityUncert"},

        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_ATT_UNCERT_EULER, CH_ROLL), "estRollUncert"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_ATT_UNCERT_EULER, CH_PITCH), "estPitchUncert"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_ATT_UNCERT_EULER, CH_YAW), "estYawUncert"},

        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS_UNCERT, CH_X), "estGyroBiasXUncert"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS_UNCERT, CH_Y), "estGyroBiasYUncert"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS_UNCERT, CH_Z), "estGyroBiasZUncert"},

        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS_UNCERT, CH_X), "estAccelBiasXUncert"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS_UNCERT, CH_Y), "estAccelBiasYUncert"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS_UNCERT, CH_Z), "estAccelBiasZUncert"},

        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_LINEAR_ACCEL, CH_X), "estLinearAccelX"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_LINEAR_ACCEL, CH_Y), "estLinearAccelY"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_LINEAR_ACCEL, CH_Z), "estLinearAccelZ"},

        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_ANGULAR_RATE, CH_X), "estAngularRateX"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_ANGULAR_RATE, CH_Y), "estAngularRateY"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_ANGULAR_RATE, CH_Z), "estAngularRateZ"},

        {ChannelId(CH_FIELD_ESTFILTER_WGS84_LOC_GRAV_MAGNITUDE, CH_MAGNITUDE), "estWGS84LocalGravMagnitude"},

        {ChannelId(CH_FIELD_ESTFILTER_FILTER_STATUS, CH_FILTER_STATE), "estFilterState"},
        {ChannelId(CH_FIELD_ESTFILTER_FILTER_STATUS, CH_DYNAMICS_MODE), "estFilterDynamicsMode"},
        {ChannelId(CH_FIELD_ESTFILTER_FILTER_STATUS, CH_FLAGS), "estFilterStatusFlags"},

        {ChannelId(CH_FIELD_ESTFILTER_GPS_TIMESTAMP, CH_TIME_OF_WEEK), "estFilterGpsTimeTow"},
        {ChannelId(CH_FIELD_ESTFILTER_GPS_TIMESTAMP, CH_WEEK_NUMBER), "estFilterGpsTimeWeekNum"},

        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_ATT_UNCERT_QUAT, CH_QUATERNION), "estAttitudeUncertQuaternion"},

        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_GRAVITY_VECTOR, CH_X), "estGravityVectorX"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_GRAVITY_VECTOR, CH_Y), "estGravityVectorY"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_GRAVITY_VECTOR, CH_Z), "estGravityVectorZ"},
        
        {ChannelId(CH_FIELD_ESTFILTER_HEADING_UPDATE_SOURCE, CH_HEADING), "estHeading"},
        {ChannelId(CH_FIELD_ESTFILTER_HEADING_UPDATE_SOURCE, CH_HEADING_UNCERTAINTY), "estHeadingUncert"},
        {ChannelId(CH_FIELD_ESTFILTER_HEADING_UPDATE_SOURCE, CH_SOURCE), "estHeadingSource"},

        {ChannelId(CH_FIELD_ESTFILTER_MAGNETIC_MODEL_SLN, CH_NORTH), "estMagneticModelSlnNorth"},
        {ChannelId(CH_FIELD_ESTFILTER_MAGNETIC_MODEL_SLN, CH_EAST), "estMagneticModelSlnEast"},
        {ChannelId(CH_FIELD_ESTFILTER_MAGNETIC_MODEL_SLN, CH_DOWN), "estMagneticModelSlnDown"},
        {ChannelId(CH_FIELD_ESTFILTER_MAGNETIC_MODEL_SLN, CH_INCLINATION), "estMagneticModelSlnInclination"},
        {ChannelId(CH_FIELD_ESTFILTER_MAGNETIC_MODEL_SLN, CH_DECLINATION), "estMagneticModelSlnDeclination"},

        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_GYRO_SCALE_FACTOR, CH_X), "estGyroScaleFactorX"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_GYRO_SCALE_FACTOR, CH_Y), "estGyroScaleFactorY"},
        {ChannelId(CH_FIELD_ESTFILTER_ESTIMATED_GYRO_SCALE_FACTOR, CH_Z), "estGyroScaleFactorZ"},

        {ChannelId(CH_FIELD_ESTFILTER_ACCEL_SCALE_FACTOR, CH_X), "estAccelScaleFactorX"},
        {ChannelId(CH_FIELD_ESTFILTER_ACCEL_SCALE_FACTOR, CH_Y), "estAccelScaleFactorY"},
        {ChannelId(CH_FIELD_ESTFILTER_ACCEL_SCALE_FACTOR, CH_Z), "estAccelScaleFactorZ"},

        {ChannelId(CH_FIELD_ESTFILTER_GYRO_SCALE_FACTOR_UNCERT, CH_X), "estGyroScaleFactorXUncert"},
        {ChannelId(CH_FIELD_ESTFILTER_GYRO_SCALE_FACTOR_UNCERT, CH_Y), "estGyroScaleFactorYUncert"},
        {ChannelId(CH_FIELD_ESTFILTER_GYRO_SCALE_FACTOR_UNCERT, CH_Z), "estGyroScaleFactorZUncert"},

        {ChannelId(CH_FIELD_ESTFILTER_ACCEL_SCALE_FACTOR_UNCERT, CH_X), "estAccelScaleFactorXUncert"},
        {ChannelId(CH_FIELD_ESTFILTER_ACCEL_SCALE_FACTOR_UNCERT, CH_Y), "estAccelScaleFactorYUncert"},
        {ChannelId(CH_FIELD_ESTFILTER_ACCEL_SCALE_FACTOR_UNCERT, CH_Z), "estAccelScaleFactorZUncert"},

        {ChannelId(CH_FIELD_ESTFILTER_COMPENSATED_ACCEL, CH_X), "estCompensatedAccelX"},
        {ChannelId(CH_FIELD_ESTFILTER_COMPENSATED_ACCEL, CH_Y), "estCompensatedAccelY"},
        {ChannelId(CH_FIELD_ESTFILTER_COMPENSATED_ACCEL, CH_Z), "estCompensatedAccelZ"},

        {ChannelId(CH_FIELD_ESTFILTER_STD_ATMOSPHERE_MODEL, CH_GEOMETRIC_ALTITUDE), "estStdAtmModelGeometricAlt"},
        {ChannelId(CH_FIELD_ESTFILTER_STD_ATMOSPHERE_MODEL, CH_GEOPOTENTIAL_ALTITUDE), "estStdAtmModelGeopotentialAlt"},
        {ChannelId(CH_FIELD_ESTFILTER_STD_ATMOSPHERE_MODEL, CH_TEMPERATURE), "estStdAtmModelTemperature"},
        {ChannelId(CH_FIELD_ESTFILTER_STD_ATMOSPHERE_MODEL, CH_PRESSURE), "estStdAtmModelPressure"},
        {ChannelId(CH_FIELD_ESTFILTER_STD_ATMOSPHERE_MODEL, CH_DENSITY), "estStdAtmModelDensity"},

        {ChannelId(CH_FIELD_ESTFILTER_PRESSURE_ALTITUDE, CH_ALTITUDE), "estPressureAlt"},

        {ChannelId(CH_FIELD_ESTFILTER_MAG_BIAS, CH_X), "estMagBiasX"},
        {ChannelId(CH_FIELD_ESTFILTER_MAG_BIAS, CH_Y), "estMagBiasY"},
        {ChannelId(CH_FIELD_ESTFILTER_MAG_BIAS, CH_Z), "estMagBiasZ"},

        {ChannelId(CH_FIELD_ESTFILTER_MAG_AUTO_HARD_IRON_OFFSET, CH_X), "estMagAutoHardIronOffsetX"},
        {ChannelId(CH_FIELD_ESTFILTER_MAG_AUTO_HARD_IRON_OFFSET, CH_Y), "estMagAutoHardIronOffsetY"},
        {ChannelId(CH_FIELD_ESTFILTER_MAG_AUTO_HARD_IRON_OFFSET, CH_Z), "estMagAutoHardIronOffsetZ"},

        {ChannelId(CH_FIELD_ESTFILTER_MAG_AUTO_SOFT_IRON_MATRIX, CH_MATRIX), "estMagAutoSoftIronMatrix"},

        {ChannelId(CH_FIELD_ESTFILTER_MAG_AUTO_HARD_IRON_OFFSET_UNCERT, CH_X), "estMagAutoHardIronOffsetXUncert"},
        {ChannelId(CH_FIELD_ESTFILTER_MAG_AUTO_HARD_IRON_OFFSET_UNCERT, CH_Y), "estMagAutoHardIronOffsetYUncert"},
        {ChannelId(CH_FIELD_ESTFILTER_MAG_AUTO_HARD_IRON_OFFSET_UNCERT, CH_Z), "estMagAutoHardIronOffsetZUncert"},

        {ChannelId(CH_FIELD_ESTFILTER_MAG_BIAS_UNCERT, CH_X), "estMagBiasOffsetXUncert"},
        {ChannelId(CH_FIELD_ESTFILTER_MAG_BIAS_UNCERT, CH_Y), "estMagBiasOffsetYUncert"},
        {ChannelId(CH_FIELD_ESTFILTER_MAG_BIAS_UNCERT, CH_Z), "estMagBiasOffsetZUncert"},

        {ChannelId(CH_FIELD_ESTFILTER_MAG_AUTO_SOFT_IRON_MATRIX_UNCERT, CH_MATRIX), "estMagAutoSoftIronMatrixUncert"},

        {ChannelId(CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION, CH_X), "estGnssAntennaOffsetCorrectX"},
        {ChannelId(CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION, CH_Y), "estGnssAntennaOffsetCorrectY"},
        {ChannelId(CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION, CH_Z), "estGnssAntennaOffsetCorrectZ"},

        {ChannelId(CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION_UNCERT, CH_X), "estGnssAntennaOffsetCorrectXUncert"},
        {ChannelId(CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION_UNCERT, CH_Y), "estGnssAntennaOffsetCorrectYUncert"},
        {ChannelId(CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION_UNCERT, CH_Z), "estGnssAntennaOffsetCorrectZUncert"},

        {ChannelId(CH_FIELD_DISP_DISPLACEMENT_RAW, CH_DISPLACEMENT), "rawDisplacement"},
        {ChannelId(CH_FIELD_DISP_DISPLACEMENT_MM, CH_DISPLACEMENT), "displacementMillimeters"},
    });

    std::vector<MipTypes::DataClass> MipTypes::GNSS_DATA_CLASSES()
    {
        return {
            DataClass::CLASS_GNSS,
            DataClass::CLASS_GNSS1,
            DataClass::CLASS_GNSS2,
            DataClass::CLASS_GNSS3,
            DataClass::CLASS_GNSS4,
            DataClass::CLASS_GNSS5
        };
    }

    MipTypes::MipChannelFields MipTypes::getChannelFields_allDataClasses(MipTypes::ChannelField chField)
    {
        MipChannelFields fields;
        if (!MipTypes::isGnssChannelField(chField))
        {
            fields.push_back(chField);
            return fields;
        }

        for (DataClass descSet : GNSS_DATA_CLASSES())
        {
            fields.push_back(MipTypes::getChannelField_toDataClass(chField, descSet));
        }

        return fields;
    }

    MipTypes::ChannelField MipTypes::getChannelField_baseDataClass(MipTypes::ChannelField chField)
    {
        if (!MipTypes::isGnssChannelField(chField))
        {
            return chField;
        }

        return MipTypes::getChannelField_toDataClass(chField, DataClass::CLASS_GNSS);
    }

    MipTypes::ChannelField MipTypes::getChannelField_toDataClass(MipTypes::ChannelField chField, MipTypes::DataClass dataClass)
    {
        uint8 fieldDesc = Utils::lsb(static_cast<uint16>(chField));
        uint16 newChField = Utils::make_uint16(static_cast<uint8>(dataClass), fieldDesc);
        return ChannelField(newChField);
    }

    std::string MipTypes::getChannelNamePrependText(MipTypes::ChannelField chField)
    {
        switch (MipTypes::channelFieldToDataClass(chField))
        {
        case DataClass::CLASS_GNSS1:
            return "gnss1_";
        case DataClass::CLASS_GNSS2:
            return "gnss2_";
        case DataClass::CLASS_GNSS3:
            return "gnss3_";
        case DataClass::CLASS_GNSS4:
            return "gnss4_";
        case DataClass::CLASS_GNSS5:
            return "gnss5_";

        case DataClass::CLASS_GNSS:
        default:
            return "";
        }
    }

    bool MipTypes::isGnssChannelField(MipTypes::ChannelField chField)
    {
        std::vector<DataClass> classes = GNSS_DATA_CLASSES();
        return std::find(classes.begin(), classes.end(), MipTypes::channelFieldToDataClass(chField))
            != classes.end();
    }
}