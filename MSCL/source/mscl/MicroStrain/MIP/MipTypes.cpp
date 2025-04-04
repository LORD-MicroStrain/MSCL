/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/MIP/MipTypes.h"

namespace mscl
{
    std::string MipTypes::channelName(ChannelField field, ChannelQualifier qualifier)
    {
        // handle "duplicate" GNSS data sets
        // handle shared data fields
        ChannelField keyField = field;
        std::string prepend = "";
        std::string append = "";

        if (isGnssChannelField(field)
            || isSharedChannelField(field))
        {
            keyField = getChannelField_baseDataClass(field);
            prepend = getChannelNamePrependText(field);

            // only get append string if field not already differentiated by class by prepend string
            if (prepend == "")
            {
                append = getChannelNameAppendText(field);
            }
        }

        //try to find the channel in the map
        auto result = CHANNEL_NAMES.find(ChannelId(keyField, qualifier));

        //if we failed to find the channel
        if(result == CHANNEL_NAMES.end())
        {
            return "unknown_" + Utils::toStr(field) + "-" + Utils::toStr(qualifier);
        }

        //replace any unsupported sensorcloud characters
        std::string sensorcloudFilteredName = prepend + result->second + append;
        Utils::filterSensorcloudName(sensorcloudFilteredName);

        //found the channel, return the name
        return sensorcloudFilteredName;
    }

    MipTypes::DataClass MipTypes::channelFieldToDataClass(ChannelField channelField)
    {
        return static_cast<DataClass>(Utils::msb(static_cast<uint16>(channelField)));
    }

    size_t MipTypes::ChannelIdHash::operator()(const ChannelId& channelId) const
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

        { ChannelId(CH_FIELD_SENSOR_OVERRANGE_STATUS, CH_STATUS), "overrangeStatus" },

        {ChannelId(CH_FIELD_SENSOR_ODOMETER_DATA, CH_SPEED), "odometer_speed"},
        {ChannelId(CH_FIELD_SENSOR_ODOMETER_DATA, CH_SPEED_ACCURACY), "odometer_uncert"},

        {ChannelId(CH_FIELD_SENSOR_RAW_AMBIENT_PRESSURE, CH_PRESSURE), "rawAmbientPressure"},

        {ChannelId(CH_FIELD_SENSOR_TEMPERATURE_STATISTICS, CH_MIN_TEMP), "tempStats_min"},
        {ChannelId(CH_FIELD_SENSOR_TEMPERATURE_STATISTICS, CH_MAX_TEMP), "tempStats_max"},
        {ChannelId(CH_FIELD_SENSOR_TEMPERATURE_STATISTICS, CH_MEAN_TEMP), "tempStats_mean"},

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

        {ChannelId(CH_FIELD_GNSS_SPACE_VEHICLE_INFO, CH_CHANNEL), "svi_trackingChannel" },
        {ChannelId(CH_FIELD_GNSS_SPACE_VEHICLE_INFO, CH_CARRIER_TO_NOISE_RATIO), "svi_carrierToNoiseRatio"},
        {ChannelId(CH_FIELD_GNSS_SPACE_VEHICLE_INFO, CH_AZIMUTH), "svi_azimuth"},
        {ChannelId(CH_FIELD_GNSS_SPACE_VEHICLE_INFO, CH_ELEVATION), "svi_elevation"},
        {ChannelId(CH_FIELD_GNSS_SPACE_VEHICLE_INFO, CH_FLAGS), "svi_flags"},

        {ChannelId(CH_FIELD_GNSS_HARDWARE_STATUS, CH_SENSOR_STATE), "sensorState"},
        {ChannelId(CH_FIELD_GNSS_HARDWARE_STATUS, CH_ANTENNA_STATE), "antennaState"},
        {ChannelId(CH_FIELD_GNSS_HARDWARE_STATUS, CH_ANTENNA_POWER), "antennaPower"},

        {ChannelId(CH_FIELD_GNSS_DGNSS_INFO, CH_AGE), "dgnss_newestAge"},
        {ChannelId(CH_FIELD_GNSS_DGNSS_INFO, CH_STATUS), "dgnss_baseStationStatus"},
        {ChannelId(CH_FIELD_GNSS_DGNSS_INFO, CH_NUM_CHANNELS), "dgnss_numChannels"},

        {ChannelId(CH_FIELD_GNSS_DGNSS_CHANNEL_STATUS, CH_AGE), "dgnss_age"},
        {ChannelId(CH_FIELD_GNSS_DGNSS_CHANNEL_STATUS, CH_CORRECTION), "dgnss_pseudorangeCorr"},
        {ChannelId(CH_FIELD_GNSS_DGNSS_CHANNEL_STATUS, CH_RATE_CORRECTION), "dgnss_pseudorangeRateCorr"},

        { ChannelId(CH_FIELD_GNSS_CLOCK_INFO_2, CH_BIAS), "gpsClockBias" },
        { ChannelId(CH_FIELD_GNSS_CLOCK_INFO_2, CH_DRIFT), "gpsClockDrift" },
        { ChannelId(CH_FIELD_GNSS_CLOCK_INFO_2, CH_BIAS_ACCURACY_ESTIMATE), "gpsClockBiasAccuracy" },
        { ChannelId(CH_FIELD_GNSS_CLOCK_INFO_2, CH_DRIFT_ACCURACY_ESTIMATE), "gpsClockDriftAccuracy" },

        { ChannelId(CH_FIELD_GNSS_GPS_LEAP_SECONDS, CH_SECONDS), "gpsLeapSeconds" },

        { ChannelId(CH_FIELD_GNSS_SBAS_INFO, CH_TIME_OF_WEEK), "sbasInfo_tow" },
        { ChannelId(CH_FIELD_GNSS_SBAS_INFO, CH_WEEK_NUMBER), "sbasInfo_weekNumber" },
        { ChannelId(CH_FIELD_GNSS_SBAS_INFO, CH_SYSTEM_ID), "sbasInfo_system" },
        { ChannelId(CH_FIELD_GNSS_SBAS_INFO, CH_SATELLITE_ID), "sbasInfo_satellite" },
        { ChannelId(CH_FIELD_GNSS_SBAS_INFO, CH_COUNT), "sbasInfo_count" },
        { ChannelId(CH_FIELD_GNSS_SBAS_INFO, CH_STATUS), "sbasInfo_status" },

        { ChannelId(CH_FIELD_GNSS_SBAS_CORRECTION, CH_INDEX), "sbasCorr_index" },
        { ChannelId(CH_FIELD_GNSS_SBAS_CORRECTION, CH_COUNT), "sbasCorr_count" },
        { ChannelId(CH_FIELD_GNSS_SBAS_CORRECTION, CH_TIME_OF_WEEK), "sbasCorr_tow" },
        { ChannelId(CH_FIELD_GNSS_SBAS_CORRECTION, CH_WEEK_NUMBER), "sbasCorr_weekNumber" },
        { ChannelId(CH_FIELD_GNSS_SBAS_CORRECTION, CH_UDREI), "sbasCorr_udrei" },
        { ChannelId(CH_FIELD_GNSS_SBAS_CORRECTION, CH_PSEUDORANGE_CORRECTION), "sbasCorr_pseudorange" },
        { ChannelId(CH_FIELD_GNSS_SBAS_CORRECTION, CH_IONOSPHERIC_CORRECTION), "sbasCorr_ionospheric" },

        { ChannelId(CH_FIELD_GNSS_SATELLITE_STATUS, CH_INDEX), "satStatus_index" },
        { ChannelId(CH_FIELD_GNSS_SATELLITE_STATUS, CH_COUNT), "satStatus_count" },
        { ChannelId(CH_FIELD_GNSS_SATELLITE_STATUS, CH_TIME_OF_WEEK), "satStatus_tow" },
        { ChannelId(CH_FIELD_GNSS_SATELLITE_STATUS, CH_WEEK_NUMBER), "satStatus_weekNumber" },
        { ChannelId(CH_FIELD_GNSS_SATELLITE_STATUS, CH_ELEVATION), "satStatus_elevation" },
        { ChannelId(CH_FIELD_GNSS_SATELLITE_STATUS, CH_AZIMUTH), "satStatus_azimuth" },
        { ChannelId(CH_FIELD_GNSS_SATELLITE_STATUS, CH_HEALTH), "satStatus_satelliteHealth" },

        { ChannelId(CH_FIELD_GNSS_RF_ERROR_DETECTION, CH_JAMMING_STATE), "rfError_jammingState" },
        { ChannelId(CH_FIELD_GNSS_RF_ERROR_DETECTION, CH_SPOOFING_STATE), "rfError_spoofingState" },

        { ChannelId(CH_FIELD_GNSS_RAW_OBSERVATION, CH_INDEX), "rawObs_index" },
        { ChannelId(CH_FIELD_GNSS_RAW_OBSERVATION, CH_COUNT), "rawObs_count" },
        { ChannelId(CH_FIELD_GNSS_RAW_OBSERVATION, CH_TIME_OF_WEEK), "rawObs_tow" },
        { ChannelId(CH_FIELD_GNSS_RAW_OBSERVATION, CH_WEEK_NUMBER), "rawObs_weekNumber" },
        { ChannelId(CH_FIELD_GNSS_RAW_OBSERVATION, CH_SIGNAL_STRENGTH), "rawObs_sigStrength" },
        { ChannelId(CH_FIELD_GNSS_RAW_OBSERVATION, CH_SIGNAL_QUALITY), "rawObs_sigQuality" },
        { ChannelId(CH_FIELD_GNSS_RAW_OBSERVATION, CH_DELTA_TIME), "rawObs_lockTime" },
        { ChannelId(CH_FIELD_GNSS_RAW_OBSERVATION, CH_RANGE), "rawObs_pseudorange" },
        { ChannelId(CH_FIELD_GNSS_RAW_OBSERVATION, CH_RANGE_UNC), "rawObs_pseudorange_unc" },
        { ChannelId(CH_FIELD_GNSS_RAW_OBSERVATION, CH_CARRIER_PHASE), "rawObs_carrierPhase" },
        { ChannelId(CH_FIELD_GNSS_RAW_OBSERVATION, CH_CARRIER_PHASE_UNC), "rawObs_carrierPhase_unc" },
        { ChannelId(CH_FIELD_GNSS_RAW_OBSERVATION, CH_DOPPLER), "rawObs_doppler" },
        { ChannelId(CH_FIELD_GNSS_RAW_OBSERVATION, CH_DOPPLER_UNC), "rawObs_doppler_unc" },

        { ChannelId(CH_FIELD_GNSS_STATION_INFO, CH_TIME_OF_WEEK), "gnssBaseInfo_tow" },
        { ChannelId(CH_FIELD_GNSS_STATION_INFO, CH_WEEK_NUMBER), "gnssBaseInfo_weekNumber" },
        { ChannelId(CH_FIELD_GNSS_STATION_INFO, CH_X), "gnssBaseInfo_pos_x" },
        { ChannelId(CH_FIELD_GNSS_STATION_INFO, CH_Y), "gnssBaseInfo_pos_y" },
        { ChannelId(CH_FIELD_GNSS_STATION_INFO, CH_Z), "gnssBaseInfo_pos_z" },
        { ChannelId(CH_FIELD_GNSS_STATION_INFO, CH_HEIGHT), "gnssBaseInfo_pos_height" },
        { ChannelId(CH_FIELD_GNSS_STATION_INFO, CH_STATUS), "gnssBaseInfo_status" },

        { ChannelId(CH_FIELD_GNSS_RTK_CORRECTIONS_STATUS, CH_TIME_OF_WEEK), "rtkCorrStatus_tow" },
        { ChannelId(CH_FIELD_GNSS_RTK_CORRECTIONS_STATUS, CH_WEEK_NUMBER), "rtkCorrStatus_weekNumber" },
        { ChannelId(CH_FIELD_GNSS_RTK_CORRECTIONS_STATUS, CH_STATUS), "rtkCorrStatus_status" },
        { ChannelId(CH_FIELD_GNSS_RTK_CORRECTIONS_STATUS, CH_FLAGS), "rtkCorrStatus_rtkStatusFlags" },
        { ChannelId(CH_FIELD_GNSS_RTK_CORRECTIONS_STATUS, CH_GPS_CORRECTION_LATENCY), "rtkCorrStatus_gpsCorrLatency" },
        { ChannelId(CH_FIELD_GNSS_RTK_CORRECTIONS_STATUS, CH_GLONASS_CORRECTION_LATENCY), "rtkCorrStatus_glonassCorrLatency" },
        { ChannelId(CH_FIELD_GNSS_RTK_CORRECTIONS_STATUS, CH_GALILEO_CORRECTION_LATENCY), "rtkCorrStatus_galileoCorrLatency" },
        { ChannelId(CH_FIELD_GNSS_RTK_CORRECTIONS_STATUS, CH_BEIDOU_CORRECTION_LATENCY), "rtkCorrStatus_beidouCorrLatency" },

        { ChannelId(CH_FIELD_GNSS_GPS_IONOSPHERIC_CORRECTION, CH_TIME_OF_WEEK), "gpsCorrTimeOfWeek" },
        { ChannelId(CH_FIELD_GNSS_GPS_IONOSPHERIC_CORRECTION, CH_WEEK_NUMBER), "gpsCorrWeekNumber" },
        { ChannelId(CH_FIELD_GNSS_GPS_IONOSPHERIC_CORRECTION, CH_ALPHA), "gpsCorrAlpha" },
        { ChannelId(CH_FIELD_GNSS_GPS_IONOSPHERIC_CORRECTION, CH_BETA), "gpsCorrBeta" },

        { ChannelId(CH_FIELD_GNSS_GALILEO_IONOSPHERIC_CORRECTION, CH_TIME_OF_WEEK), "galileoCorrTimeOfWeek" },
        { ChannelId(CH_FIELD_GNSS_GALILEO_IONOSPHERIC_CORRECTION, CH_WEEK_NUMBER), "galileoCorrWeekNumber" },
        { ChannelId(CH_FIELD_GNSS_GALILEO_IONOSPHERIC_CORRECTION, CH_ALPHA), "galileoCorrAlpha" },
        { ChannelId(CH_FIELD_GNSS_GALILEO_IONOSPHERIC_CORRECTION, CH_DISTURBANCE_FLAGS), "galileoCorrDisturbanceFlags" },

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

        {ChannelId(CH_FIELD_ESTFILTER_MAG_COVARIANCE_MATRIX, CH_MATRIX), "estMagCovarianceMatrix"},

        {ChannelId(CH_FIELD_ESTFILTER_MAG_RESIDUAL_VECTOR, CH_X), "estMagResidualVector_x"},
        {ChannelId(CH_FIELD_ESTFILTER_MAG_RESIDUAL_VECTOR, CH_Y), "estMagResidualVector_y"},
        {ChannelId(CH_FIELD_ESTFILTER_MAG_RESIDUAL_VECTOR, CH_Z), "estMagResidualVector_z"},

        {ChannelId(CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION, CH_X), "estGnssAntennaOffsetCorrectX"},
        {ChannelId(CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION, CH_Y), "estGnssAntennaOffsetCorrectY"},
        {ChannelId(CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION, CH_Z), "estGnssAntennaOffsetCorrectZ"},

        {ChannelId(CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION_UNCERT, CH_X), "estGnssAntennaOffsetCorrectXUncert"},
        {ChannelId(CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION_UNCERT, CH_Y), "estGnssAntennaOffsetCorrectYUncert"},
        {ChannelId(CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION_UNCERT, CH_Z), "estGnssAntennaOffsetCorrectZUncert"},

        { ChannelId(CH_FIELD_ESTFILTER_GNSS_CLOCK_CORRECTION, CH_BIAS), "gnssClockCorr_bias" },
        { ChannelId(CH_FIELD_ESTFILTER_GNSS_CLOCK_CORRECTION, CH_DRIFT), "gnssClockCorr_biasDrift" },

        { ChannelId(CH_FIELD_ESTFILTER_GNSS_CLOCK_CORRECTION_UNCERT, CH_BIAS), "gnssClockCorr_uncert_bias" },
        { ChannelId(CH_FIELD_ESTFILTER_GNSS_CLOCK_CORRECTION_UNCERT, CH_DRIFT), "gnssClockCorr_uncert_biasDrift" },

        { ChannelId(CH_FIELD_ESTFILTER_GNSS_MULTI_ANTENNA_CORRECTION, CH_X), "estGnssAntennaOffsetCorrect_x" },
        { ChannelId(CH_FIELD_ESTFILTER_GNSS_MULTI_ANTENNA_CORRECTION, CH_Y), "estGnssAntennaOffsetCorrect_y" },
        { ChannelId(CH_FIELD_ESTFILTER_GNSS_MULTI_ANTENNA_CORRECTION, CH_Z), "estGnssAntennaOffsetCorrect_z" },

        { ChannelId(CH_FIELD_ESTFILTER_GNSS_MULTI_ANTENNA_CORRECTION_UNCERT, CH_X), "estGnssAntennaOffsetCorrect_uncert_x" },
        { ChannelId(CH_FIELD_ESTFILTER_GNSS_MULTI_ANTENNA_CORRECTION_UNCERT, CH_Y), "estGnssAntennaOffsetCorrect_uncert_y" },
        { ChannelId(CH_FIELD_ESTFILTER_GNSS_MULTI_ANTENNA_CORRECTION_UNCERT, CH_Z), "estGnssAntennaOffsetCorrect_uncert_z" },

        { ChannelId(CH_FIELD_ESTFILTER_ECEF_POS_UNCERT, CH_X), "estEcefPos_uncert_x" },
        { ChannelId(CH_FIELD_ESTFILTER_ECEF_POS_UNCERT, CH_Y), "estEcefPos_uncert_y" },
        { ChannelId(CH_FIELD_ESTFILTER_ECEF_POS_UNCERT, CH_Z), "estEcefPos_uncert_z" },

        { ChannelId(CH_FIELD_ESTFILTER_ECEF_VEL_UNCERT, CH_X), "estEcefVel_uncert_x" },
        { ChannelId(CH_FIELD_ESTFILTER_ECEF_VEL_UNCERT, CH_Y), "estEcefVel_uncert_y" },
        { ChannelId(CH_FIELD_ESTFILTER_ECEF_VEL_UNCERT, CH_Z), "estEcefVel_uncert_z" },

        { ChannelId(CH_FIELD_ESTFILTER_ECEF_POS, CH_X), "estEcefPos_x" },
        { ChannelId(CH_FIELD_ESTFILTER_ECEF_POS, CH_Y), "estEcefPos_y" },
        { ChannelId(CH_FIELD_ESTFILTER_ECEF_POS, CH_Z), "estEcefPos_z" },

        { ChannelId(CH_FIELD_ESTFILTER_ECEF_VEL, CH_X), "estEcefVel_x" },
        { ChannelId(CH_FIELD_ESTFILTER_ECEF_VEL, CH_Y), "estEcefVel_y" },
        { ChannelId(CH_FIELD_ESTFILTER_ECEF_VEL, CH_Z), "estEcefVel_z" },

        { ChannelId(CH_FIELD_ESTFILTER_NED_RELATIVE_POS, CH_X), "estNedRelPos_x" },
        { ChannelId(CH_FIELD_ESTFILTER_NED_RELATIVE_POS, CH_Y), "estNedRelPos_y" },
        { ChannelId(CH_FIELD_ESTFILTER_NED_RELATIVE_POS, CH_Z), "estNedRelPos_z" },

        { ChannelId(CH_FIELD_ESTFILTER_POSITION_AIDING_STATUS, CH_TIME_OF_WEEK), "gnssAiding_pos_tow" },
        { ChannelId(CH_FIELD_ESTFILTER_POSITION_AIDING_STATUS, CH_STATUS), "gnssAiding_pos_status" },

        { ChannelId(CH_FIELD_ESTFILTER_ATTITUDE_AIDING_STATUS, CH_TIME_OF_WEEK), "gnssAiding_att_tow" },
        { ChannelId(CH_FIELD_ESTFILTER_ATTITUDE_AIDING_STATUS, CH_STATUS), "gnssAiding_att_status" },

        { ChannelId(CH_FIELD_ESTFILTER_AIDING_MEASURE_SUMMARY, CH_TIME_OF_WEEK), "aidingSummary_tow" },
        { ChannelId(CH_FIELD_ESTFILTER_AIDING_MEASURE_SUMMARY, CH_STATUS), "aidingSummary_status" },

        { ChannelId(CH_FIELD_ESTFILTER_ODOMETER_SCALE_FACTOR_ERROR, CH_ERROR), "odometer_scaleFactorError" },
        { ChannelId(CH_FIELD_ESTFILTER_ODOMETER_SCALE_FACTOR_ERROR_UNCERT, CH_ERROR_UNC), "odometer_scaleFactorError_unc" },

        { ChannelId(CH_FIELD_ESTFILTER_GNSS_DUAL_ANTENNA_STATUS, CH_TIME_OF_WEEK), "estDualAntennaStatus_tow" },
        { ChannelId(CH_FIELD_ESTFILTER_GNSS_DUAL_ANTENNA_STATUS, CH_HEADING), "estDualAntennaStatus_heading" },
        { ChannelId(CH_FIELD_ESTFILTER_GNSS_DUAL_ANTENNA_STATUS, CH_HEADING_UNCERTAINTY), "estDualAntennaStatus_uncert_heading" },
        { ChannelId(CH_FIELD_ESTFILTER_GNSS_DUAL_ANTENNA_STATUS, CH_FIX_TYPE), "estDualAntennaStatus_fixType" },
        { ChannelId(CH_FIELD_ESTFILTER_GNSS_DUAL_ANTENNA_STATUS, CH_STATUS), "estDualAntennaStatus_status" },

        { ChannelId(CH_FIELD_ESTFILTER_FRAME_CONFIG_ERROR, CH_X), "aidingFrameConfigError_translation_x" },
        { ChannelId(CH_FIELD_ESTFILTER_FRAME_CONFIG_ERROR, CH_Y), "aidingFrameConfigError_translation_y" },
        { ChannelId(CH_FIELD_ESTFILTER_FRAME_CONFIG_ERROR, CH_Z), "aidingFrameConfigError_translation_z" },
        { ChannelId(CH_FIELD_ESTFILTER_FRAME_CONFIG_ERROR, CH_QUATERNION), "aidingFrameConfigError_rotation" },

        { ChannelId(CH_FIELD_ESTFILTER_FRAME_CONFIG_ERROR_UNCERT, CH_X), "aidingFrameConfigError_translation_uncert_x" },
        { ChannelId(CH_FIELD_ESTFILTER_FRAME_CONFIG_ERROR_UNCERT, CH_Y), "aidingFrameConfigError_translation_uncert_y" },
        { ChannelId(CH_FIELD_ESTFILTER_FRAME_CONFIG_ERROR_UNCERT, CH_Z), "aidingFrameConfigError_translation_uncert_z" },
        { ChannelId(CH_FIELD_ESTFILTER_FRAME_CONFIG_ERROR_UNCERT, CH_ROLL), "aidingFrameConfigError_rotation_uncert_roll" },
        { ChannelId(CH_FIELD_ESTFILTER_FRAME_CONFIG_ERROR_UNCERT, CH_PITCH), "aidingFrameConfigError_rotation_uncert_pitch" },
        { ChannelId(CH_FIELD_ESTFILTER_FRAME_CONFIG_ERROR_UNCERT, CH_YAW), "aidingFrameConfigError_rotation_uncert_yaw" },

        { ChannelId(CH_FIELD_DISP_DISPLACEMENT_RAW, CH_DISPLACEMENT), "rawDisplacement" },
        { ChannelId(CH_FIELD_DISP_DISPLACEMENT_MM, CH_DISPLACEMENT), "displacementMillimeters" },

        // System Data
        { ChannelId(CH_FIELD_SYSTEM_BUILT_IN_TEST, CH_STATUS              ), "builtInTest"                    },
        { ChannelId(CH_FIELD_SYSTEM_BUILT_IN_TEST, CH_BIT_SYSTEM_GENERAL  ), "builtInTest_system_bitGeneral"  },
        { ChannelId(CH_FIELD_SYSTEM_BUILT_IN_TEST, CH_BIT_SYSTEM_PROCESS  ), "builtInTest_system_bitProcess"  },
        { ChannelId(CH_FIELD_SYSTEM_BUILT_IN_TEST, CH_BIT_IMU_GENERAL     ), "builtInTest_imu_bitGeneral"     },
        { ChannelId(CH_FIELD_SYSTEM_BUILT_IN_TEST, CH_BIT_IMU_SENSORS     ), "builtInTest_imu_bitSensors"     },
        { ChannelId(CH_FIELD_SYSTEM_BUILT_IN_TEST, CH_BIT_IMU_FACTORY_BITS), "builtInTest_imu_bitFactoryBits" },
        { ChannelId(CH_FIELD_SYSTEM_BUILT_IN_TEST, CH_BIT_FILTER_GENERAL  ), "builtInTest_filter_bitGeneral"  },
        { ChannelId(CH_FIELD_SYSTEM_BUILT_IN_TEST, CH_BIT_GNSS_GENERAL    ), "builtInTest_gnss_bitGeneral"    },
        { ChannelId(CH_FIELD_SYSTEM_BUILT_IN_TEST, CH_BIT_GNSS_RECEIVERS  ), "builtInTest_gnss_bitReceivers"  },

        { ChannelId(CH_FIELD_SYSTEM_TIME_SYNC_STATUS, CH_PPS_VALID), "timeSync_ppsValid" },
        { ChannelId(CH_FIELD_SYSTEM_TIME_SYNC_STATUS, CH_LAST_PPS), "timeSync_lastPps" },

        { ChannelId(CH_FIELD_SYSTEM_GPIO_STATE, CH_STATUS), "gpioState" },

        // Shared Inertial Channels
        { ChannelId(CH_FIELD_SENSOR_SHARED_EVENT_SOURCE, CH_ID), "eventInfo_triggerId" },

        { ChannelId(CH_FIELD_SENSOR_SHARED_TICKS, CH_TICK), "timeInfo_ticks" },

        { ChannelId(CH_FIELD_SENSOR_SHARED_DELTA_TICKS, CH_DELTA_TICK), "timeInfo_deltaTicks" },

        { ChannelId(CH_FIELD_SENSOR_SHARED_GPS_TIMESTAMP, CH_TIME_OF_WEEK), "timeInfo_tow" },
        { ChannelId(CH_FIELD_SENSOR_SHARED_GPS_TIMESTAMP, CH_WEEK_NUMBER), "timeInfo_weekNumber" },

        { ChannelId(CH_FIELD_SENSOR_SHARED_DELTA_TIMESTAMP, CH_DELTA_TIME), "timeInfo_deltaTime" },

        { ChannelId(CH_FIELD_SENSOR_SHARED_REFERENCE_TIMESTAMP, CH_NANOSECONDS), "timeInfo_referenceTime" },

        { ChannelId(CH_FIELD_SENSOR_SHARED_DELTA_REFERENCE_TIME, CH_NANOSECONDS), "timeInfo_deltaReferenceTime" },

        { ChannelId(CH_FIELD_SENSOR_SHARED_EXTERNAL_TIMESTAMP, CH_TIMESTAMP), "timeInfo_externalTimestamp" },

        { ChannelId(CH_FIELD_SENSOR_SHARED_DELTA_EXTERNAL_TIME, CH_NANOSECONDS), "timeInfo_deltaExternalTime" },
    });

    const MipTypes::ChannelFieldQualifiers MipTypes::CHANNEL_INDICES(
    {
        // 0x80: Sensor Data

        // (0x80, 0x04)
        { CH_FIELD_SENSOR_SCALED_ACCEL_VEC, {
            ChannelIndex(CH_X, 1),
            ChannelIndex(CH_Y, 2),
            ChannelIndex(CH_Z, 3)
        } },
        // (0x80, 0x05)
        { CH_FIELD_SENSOR_SCALED_GYRO_VEC, {
            ChannelIndex(CH_X, 1),
            ChannelIndex(CH_Y, 2),
            ChannelIndex(CH_Z, 3)
        } },
        // (0x80, 0x06)
        { CH_FIELD_SENSOR_SCALED_MAG_VEC, {
            ChannelIndex(CH_X, 1),
            ChannelIndex(CH_Y, 2),
            ChannelIndex(CH_Z, 3)
        } },
        // (0x80, 0x09)
        { CH_FIELD_SENSOR_ORIENTATION_MATRIX, {
            ChannelIndex(CH_M0, 1),
            ChannelIndex(CH_M1, 2),
            ChannelIndex(CH_M2, 3),
            ChannelIndex(CH_M3, 4),
            ChannelIndex(CH_M4, 5),
            ChannelIndex(CH_M5, 6),
            ChannelIndex(CH_M6, 7),
            ChannelIndex(CH_M7, 8),
            ChannelIndex(CH_M8, 9),
        } },
        // (0x80, 0x0A)
        { CH_FIELD_SENSOR_ORIENTATION_QUATERNION,{
            ChannelIndex(CH_W, 1),
            ChannelIndex(CH_X, 2),
            ChannelIndex(CH_Y, 3),
            ChannelIndex(CH_Z, 4)
        } },
        // (0x80, 0x0C)
        { CH_FIELD_SENSOR_EULER_ANGLES,{
            ChannelIndex(CH_ROLL,  1),
            ChannelIndex(CH_PITCH, 2),
            ChannelIndex(CH_YAW,   3)
        } },
        // (0x80, 0x17)
        { CH_FIELD_SENSOR_SCALED_AMBIENT_PRESSURE,{
            ChannelIndex(CH_PRESSURE, 1)
        } },
        // (0x80, 0xD3)
        { CH_FIELD_SENSOR_SHARED_GPS_TIMESTAMP,{
            ChannelIndex(CH_TIME_OF_WEEK, 1),
            ChannelIndex(CH_WEEK_NUMBER,  2),
            ChannelIndex(CH_VALID_FLAGS,  3)
        } },
        // (0x80, 0xD5)
        { CH_FIELD_SENSOR_SHARED_REFERENCE_TIMESTAMP,{
            ChannelIndex(CH_NANOSECONDS, 1)
        } },
        // (0x80, 0xD7)
        { CH_FIELD_SENSOR_SHARED_EXTERNAL_TIMESTAMP,{
            ChannelIndex(CH_TIMESTAMP, 1),
            ChannelIndex(CH_VALID_FLAGS, 2)
        } },

        // 0x82 Filter Data

        // (0x82, 0x03)
        { CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_QUATERNION,{
            ChannelIndex(CH_W,           1),
            ChannelIndex(CH_X,           2),
            ChannelIndex(CH_Y,           3),
            ChannelIndex(CH_Z,           4),
            ChannelIndex(CH_VALID_FLAGS, 5)
        } },
        // (0x82, 0x05)
        { CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_EULER,{
            ChannelIndex(CH_ROLL,        1),
            ChannelIndex(CH_PITCH,       2),
            ChannelIndex(CH_YAW,         3),
            ChannelIndex(CH_VALID_FLAGS, 4)
        } },
        // (0x82, 0x06)
        { CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS,{
            ChannelIndex(CH_X,           1),
            ChannelIndex(CH_Y,           2),
            ChannelIndex(CH_Z,           3),
            ChannelIndex(CH_VALID_FLAGS, 4)
        } },
        // (0x82, 0x07)
        { CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS,{
            ChannelIndex(CH_X,           1),
            ChannelIndex(CH_Y,           2),
            ChannelIndex(CH_Z,           3),
            ChannelIndex(CH_VALID_FLAGS, 4)
        } },
        // (0x82, 0x0A)
        { CH_FIELD_ESTFILTER_ESTIMATED_ATT_UNCERT_EULER,{
            ChannelIndex(CH_ROLL,        1),
            ChannelIndex(CH_PITCH,       2),
            ChannelIndex(CH_YAW,         3),
            ChannelIndex(CH_VALID_FLAGS, 4)
        } },
        // (0x82, 0x0B)
        { CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS_UNCERT,{
            ChannelIndex(CH_X,           1),
            ChannelIndex(CH_Y,           2),
            ChannelIndex(CH_Z,           3),
            ChannelIndex(CH_VALID_FLAGS, 4)
        } },
        // (0x82, 0x0C)
        { CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS_UNCERT,{
            ChannelIndex(CH_X,           1),
            ChannelIndex(CH_Y,           2),
            ChannelIndex(CH_Z,           3),
            ChannelIndex(CH_VALID_FLAGS, 4)
        } },
        // (0x82, 0x0D)
        { CH_FIELD_ESTFILTER_ESTIMATED_LINEAR_ACCEL,{
            ChannelIndex(CH_X,           1),
            ChannelIndex(CH_Y,           2),
            ChannelIndex(CH_Z,           3),
            ChannelIndex(CH_VALID_FLAGS, 4)
        } },
        // (0x82, 0x0E)
        { CH_FIELD_ESTFILTER_ESTIMATED_ANGULAR_RATE,{
            ChannelIndex(CH_X,           1),
            ChannelIndex(CH_Y,           2),
            ChannelIndex(CH_Z,           3),
            ChannelIndex(CH_VALID_FLAGS, 4)
        } },
        // (0x82, 0x10)
        { CH_FIELD_ESTFILTER_FILTER_STATUS,{
            ChannelIndex(CH_FILTER_STATE,  1),
            ChannelIndex(CH_DYNAMICS_MODE, 2),
            ChannelIndex(CH_FLAGS,         3)
        } },
        // (0x82, 0x12)
        { CH_FIELD_ESTFILTER_ESTIMATED_ATT_UNCERT_QUAT,{
            ChannelIndex(CH_W,           1),
            ChannelIndex(CH_X,           2),
            ChannelIndex(CH_Y,           3),
            ChannelIndex(CH_Z,           4),
            ChannelIndex(CH_VALID_FLAGS, 5)
        } },
        // (0x82, 0x13)
        { CH_FIELD_ESTFILTER_ESTIMATED_GRAVITY_VECTOR,{
            ChannelIndex(CH_X,           1),
            ChannelIndex(CH_Y,           2),
            ChannelIndex(CH_Z,           3),
            ChannelIndex(CH_VALID_FLAGS, 4)
        } },
        // (0x82, 0x1C)
        { CH_FIELD_ESTFILTER_COMPENSATED_ACCEL,{
            ChannelIndex(CH_X,           1),
            ChannelIndex(CH_Y,           2),
            ChannelIndex(CH_Z,           3),
            ChannelIndex(CH_VALID_FLAGS, 4)
        } },
        // (0x82, 0x21)
        { CH_FIELD_ESTFILTER_PRESSURE_ALTITUDE,{
            ChannelIndex(CH_ALTITUDE,    1),
            ChannelIndex(CH_VALID_FLAGS, 2)
        } },
        // (0x82, 0xD3)
        { CH_FIELD_ESTFILTER_SHARED_GPS_TIMESTAMP,{
            ChannelIndex(CH_TIME_OF_WEEK, 1),
            ChannelIndex(CH_WEEK_NUMBER,  2),
            ChannelIndex(CH_VALID_FLAGS,  3)
        } },
        // (0x82, 0xD5)
        { CH_FIELD_ESTFILTER_SHARED_REFERENCE_TIMESTAMP,{
            ChannelIndex(CH_NANOSECONDS, 1)
        } },
        // (0x82, 0xD7)
        { CH_FIELD_ESTFILTER_SHARED_EXTERNAL_TIMESTAMP,{
            ChannelIndex(CH_TIMESTAMP, 1),
            ChannelIndex(CH_VALID_FLAGS, 2)
        } },

        // 0xA0 System Data

        // (0xA0, 0x01)
        /*{ CH_FIELD_SYSTEM_BUILT_IN_TEST,{
            // TODO: Figure out channel qualifiers
            ChannelIndex(CH_, 1),
            ChannelIndex(CH_, 2),
            ChannelIndex(CH_, 3),
            ChannelIndex(CH_, 4),
            ChannelIndex(CH_, 5),
            ChannelIndex(CH_, 6),
            ChannelIndex(CH_, 7),
            ChannelIndex(CH_, 8),
            ChannelIndex(CH_, 9),
            ChannelIndex(CH_, 10),
            ChannelIndex(CH_, 11),
            ChannelIndex(CH_, 12),
            ChannelIndex(CH_, 13),
            ChannelIndex(CH_, 14),
            ChannelIndex(CH_, 15),
            ChannelIndex(CH_, 16)
        } },*/
        // (0xA0, 0x02)
        { CH_FIELD_SYSTEM_TIME_SYNC_STATUS,{
            ChannelIndex(CH_PPS_VALID, 1),
            ChannelIndex(CH_LAST_PPS,  2)
        } },
        // (0xA0, 0x03)
        { CH_FIELD_SYSTEM_GPIO_STATE,{
            ChannelIndex(CH_STATUS, 1)
        } },
        // (0xA0, 0xD3)
        { CH_FIELD_SYSTEM_SHARED_GPS_TIMESTAMP,{
            ChannelIndex(CH_TIME_OF_WEEK, 1),
            ChannelIndex(CH_WEEK_NUMBER,  2),
            ChannelIndex(CH_VALID_FLAGS,  3)
        } },
        // (0xA0, 0xD5)
        { CH_FIELD_SYSTEM_SHARED_REFERENCE_TIMESTAMP,{
            ChannelIndex(CH_NANOSECONDS, 1)
        } },
        // (0xA0, 0xD7)
        { CH_FIELD_SYSTEM_SHARED_EXTERNAL_TIMESTAMP,{
            ChannelIndex(CH_TIMESTAMP, 1),
            ChannelIndex(CH_VALID_FLAGS, 2)
        } }
    });

    std::vector<MipTypes::DataClass> MipTypes::GNSS_DATA_CLASSES()
    {
        return {
            CLASS_GNSS,
            CLASS_GNSS1,
            CLASS_GNSS2,
            CLASS_GNSS3,
            CLASS_GNSS4,
            CLASS_GNSS5
        };
    }

    std::vector<MipTypes::DataClass> MipTypes::INERTIAL_DATA_CLASSES()
    {
        return{
            CLASS_AHRS_IMU,
            CLASS_ESTFILTER,
            CLASS_GNSS,
            CLASS_GNSS1,
            CLASS_GNSS2,
            CLASS_GNSS3,
            CLASS_GNSS4,
            CLASS_GNSS5,
            CLASS_SYSTEM
        };
    }

    MipTypes::MipChannelFields MipTypes::getChannelFields_allDataClasses(ChannelField chField)
    {
        MipChannelFields fields;
        if (isSharedChannelField(chField))
        {
            for (DataClass descSet : INERTIAL_DATA_CLASSES())
            {
                fields.push_back(getChannelField_toDataClass(chField, descSet));
            }
        }
        else if (isGnssChannelField(chField)) // if shared field, already have all GNSS entries
        {
            for (DataClass descSet : GNSS_DATA_CLASSES())
            {
                fields.push_back(getChannelField_toDataClass(chField, descSet));
            }
        }
        else
        {
            fields.push_back(chField);
        }

        return fields;
    }

    MipTypes::ChannelField MipTypes::getChannelField_baseDataClass(ChannelField chField)
    {
        if (isSharedChannelField(chField))
        {
            return getChannelField_toDataClass(chField, CLASS_AHRS_IMU);
        }

        if (isGnssChannelField(chField))
        {
            return getChannelField_toDataClass(chField, CLASS_GNSS);
        }

        return chField;
    }

    MipTypes::ChannelField MipTypes::getChannelField_toDataClass(ChannelField chField, DataClass dataClass)
    {
        uint8 fieldDesc = Utils::lsb(static_cast<uint16>(chField));
        uint16 newChField = Utils::make_uint16(static_cast<uint8>(dataClass), fieldDesc);
        return ChannelField(newChField);
    }

    std::string MipTypes::getChannelNamePrependText(ChannelField chField)
    {
        switch (channelFieldToDataClass(chField))
        {
        case CLASS_GNSS1:
            return "gnss1_";
        case CLASS_GNSS2:
            return "gnss2_";
        case CLASS_GNSS3:
            return "gnss3_";
        case CLASS_GNSS4:
            return "gnss4_";
        case CLASS_GNSS5:
            return "gnss5_";

        case CLASS_GNSS:
        default:
            return "";
        }
    }

    std::string MipTypes::getChannelNameAppendText(ChannelField chField)
    {
        if (!isSharedChannelField(chField))
        {
            return "";
        }

        switch (channelFieldToDataClass(chField))
        {
        case CLASS_AHRS_IMU:
            return "_ahrsImu";
        case CLASS_ESTFILTER:
            return "_estFilter";
        case CLASS_GNSS:
            return "_gnss";

        case CLASS_GNSS1:
            return "_gnss1";
        case CLASS_GNSS2:
            return "_gnss2";
        case CLASS_GNSS3:
            return "_gnss3";
        case CLASS_GNSS4:
            return "_gnss4";
        case CLASS_GNSS5:
            return "_gnss5";

        case CLASS_SYSTEM:
            return "_system";

        default:
            return "";
        }
    }

    bool MipTypes::isGnssChannelField(ChannelField chField)
    {
        std::vector<DataClass> classes = GNSS_DATA_CLASSES();
        return std::find(classes.begin(), classes.end(), channelFieldToDataClass(chField))
            != classes.end();
    }

    bool MipTypes::isSharedChannelField(ChannelField chField)
    {
        uint8 fieldDescriptor = Utils::lsb(static_cast<uint16>(chField));
        return fieldDescriptor >= MIN_SHARED_FIELD_DESCRIPTOR;
    }

    MipTypes::ChannelFieldQualifiers MipTypes::channelFieldQualifiers(const MipChannelFields& fields)
    {
        ChannelFieldQualifiers fieldQualifiers{};

        for (const ChannelField& field : fields)
        {
            auto found = CHANNEL_INDICES.find(field);

            if (found != CHANNEL_INDICES.end())
            {
                fieldQualifiers.emplace(found->first, found->second);
            }
        }

        return fieldQualifiers;
    }

    MipTypes::ChannelQualifier MipTypes::channelFieldQualifier(const ChannelField field, const uint8 index)
    {
        return findChannelIndex(field, CH_UNKNOWN, index).first;
    }

    uint8 MipTypes::channelFieldQualifierIndex(const ChannelField channelField, const ChannelQualifier channelQualifier)
    {
        return findChannelIndex(channelField, channelQualifier, 0).second;
    }

    MipTypes::ChannelIndex MipTypes::findChannelIndex(ChannelField field, ChannelQualifier qualifier, uint8 index)
    {
        // Find the channel field if it exists
        const auto channelFieldEntry = CHANNEL_INDICES.find(field);

        // Channel field doesn't exist so the channel is unknown
        if (channelFieldEntry == CHANNEL_INDICES.end())
        {
            return{ CH_UNKNOWN, 0 };
        }

        const auto channelQualifiers = channelFieldEntry->second;
        auto qualifierEntry = channelQualifiers.end();

        if (index != 0)
        {
            // Find the channel qualifier with the specified index
            qualifierEntry = std::find_if(channelQualifiers.begin(), channelQualifiers.end(),
                [&](const ChannelIndex& qualifierIndexPair)
            {
                return qualifierIndexPair.second == index;
            }
            );
        }

        if (qualifier != CH_UNKNOWN)
        {
            // Find the channel qualifier with the specified index
            qualifierEntry = std::find_if(channelQualifiers.begin(), channelQualifiers.end(),
                [&](const ChannelIndex& qualifierIndexPair)
            {
                return qualifierIndexPair.first == qualifier;
            }
            );
        }

        // Found the qualifier
        if (qualifierEntry != channelQualifiers.end())
        {
            return *qualifierEntry;
        }

        return{ CH_UNKNOWN, 0 };
    }

    size_t MipChannelIdentifier::TypeHash::operator()(const Type& type) const
    {
        return static_cast<size_t>(type);
    }

    size_t MipChannelIdentifier::TypeIdHash::operator()(const TypeId& id) const
    {
        return id.first ^ id.second;
    }

    size_t MipChannelIdentifier::SpecifierIdHash::operator()(const SpecifierId& id) const
    {
        return std::get<0>(id) ^ std::get<1>(id) ^ std::get<2>(id);
    }

    const std::unordered_map<MipChannelIdentifier::Type, std::string, MipChannelIdentifier::TypeHash> MipChannelIdentifier::TYPE_NAMES(
    {
        { GNSS_RECEIVER_ID,             "rec" },
        { GNSS_BASE_STATION_ID,         "gnssBase" },
        { GNSS_CONSTELLATION,           "gnssId" },
        { GNSS_SATELLITE_ID,            "sat" },
        { GNSS_SIGNAL_ID,               "sig" },
        { AIDING_MEASUREMENT_TYPE,      "aidType" },
        { GNSS_RF_BAND,                 "rfBand" },
        { AIDING_MEASUREMENT_FRAME_ID,  "aidFrameId"}
    });

    const std::unordered_map<MipChannelIdentifier::TypeId, std::string, MipChannelIdentifier::TypeIdHash> MipChannelIdentifier::TRANSLATED_TYPE_NAMES(
    {
        { TypeId(AIDING_MEASUREMENT_TYPE, GNSS),         "gnss" },
        { TypeId(AIDING_MEASUREMENT_TYPE, DUAL_ANTENNA), "dualAnt" },
        { TypeId(AIDING_MEASUREMENT_TYPE, HEADING),      "heading" },
        { TypeId(AIDING_MEASUREMENT_TYPE, PRESSURE),     "pressure" },
        { TypeId(AIDING_MEASUREMENT_TYPE, MAGNETOMETER), "mag" },
        { TypeId(AIDING_MEASUREMENT_TYPE, SPEED),        "speed" },

        { TypeId(AIDING_MEASUREMENT_TYPE, AIDING_POS_ECEF              ), "aidingPosEcef" },
        { TypeId(AIDING_MEASUREMENT_TYPE, AIDING_POS_LLH               ), "aidingPosLlh" },
        { TypeId(AIDING_MEASUREMENT_TYPE, AIDING_HEIGHT_ABOVE_ELLIPSOID), "aidingHeightAboveEllipsoid" },
        { TypeId(AIDING_MEASUREMENT_TYPE, AIDING_VEL_ECEF              ), "aidingVelEcef" },
        { TypeId(AIDING_MEASUREMENT_TYPE, AIDING_VEL_NED               ), "aidingVelNed" },
        { TypeId(AIDING_MEASUREMENT_TYPE, AIDING_VEL_BODY_FRAME        ), "aidingVelBodyFrame" },
        { TypeId(AIDING_MEASUREMENT_TYPE, AIDING_HEADING_TRUE          ), "aidingHeadingTrue" },
        { TypeId(AIDING_MEASUREMENT_TYPE, AIDING_MAGNETIC_FIELD        ), "aidingMagField" },
        { TypeId(AIDING_MEASUREMENT_TYPE, AIDING_PRESSURE              ), "aidingPressure" },

        { TypeId(GNSS_CONSTELLATION, GPS),     "gps" },
        { TypeId(GNSS_CONSTELLATION, GLONASS), "glonass" },
        { TypeId(GNSS_CONSTELLATION, GALILEO), "galileo" },
        { TypeId(GNSS_CONSTELLATION, BEIDOU),  "beidou" },

        { TypeId(GNSS_SIGNAL_ID, GPS_L1CA),  "sig-L1CA" },
        { TypeId(GNSS_SIGNAL_ID, GPS_L1P),   "sig-L1P" },
        { TypeId(GNSS_SIGNAL_ID, GPS_L1Z),   "sig-L1Z" },
        { TypeId(GNSS_SIGNAL_ID, GPS_L2CA),  "sig-L2CA" },
        { TypeId(GNSS_SIGNAL_ID, GPS_L2P),   "sig-L2P" },
        { TypeId(GNSS_SIGNAL_ID, GPS_L2Z),   "sig-L2Z" },
        { TypeId(GNSS_SIGNAL_ID, GPS_L2CL),  "sig-L2CL" },
        { TypeId(GNSS_SIGNAL_ID, GPS_L2CM),  "sig-L2CM" },
        { TypeId(GNSS_SIGNAL_ID, GPS_L2CML), "sig-L2CML" },
        { TypeId(GNSS_SIGNAL_ID, GPS_L5I),   "sig-L5I" },
        { TypeId(GNSS_SIGNAL_ID, GPS_L5Q),   "sig-L5Q" },
        { TypeId(GNSS_SIGNAL_ID, GPS_L5IQ),  "sig-L5IQ" },
        { TypeId(GNSS_SIGNAL_ID, GPS_L1CD),  "sig-L1CD" },
        { TypeId(GNSS_SIGNAL_ID, GPS_L1CP),  "sig-L1CP" },
        { TypeId(GNSS_SIGNAL_ID, GPS_L1CDP), "sig-L1CDP" },

        { TypeId(GNSS_SIGNAL_ID, GLONASS_G1CA), "sig-G1CA" },
        { TypeId(GNSS_SIGNAL_ID, GLONASS_G1P),  "sig-G1P" },
        { TypeId(GNSS_SIGNAL_ID, GLONASS_G2C),  "sig-G2C" },
        { TypeId(GNSS_SIGNAL_ID, GLONASS_G2P),  "sig-G2P" },

        { TypeId(GNSS_SIGNAL_ID, GALILEO_E1C),    "sig-E1C" },
        { TypeId(GNSS_SIGNAL_ID, GALILEO_E1A),    "sig-E1A" },
        { TypeId(GNSS_SIGNAL_ID, GALILEO_E1B),    "sig-E1B" },
        { TypeId(GNSS_SIGNAL_ID, GALILEO_E1BC),   "sig-E1BC" },
        { TypeId(GNSS_SIGNAL_ID, GALILEO_E1ABC),  "sig-E1ABC" },
        { TypeId(GNSS_SIGNAL_ID, GALILEO_E6C),    "sig-E6C" },
        { TypeId(GNSS_SIGNAL_ID, GALILEO_E6A),    "sig-E6A" },
        { TypeId(GNSS_SIGNAL_ID, GALILEO_E6B),    "sig-E6B" },
        { TypeId(GNSS_SIGNAL_ID, GALILEO_E6BC),   "sig-E6BC" },
        { TypeId(GNSS_SIGNAL_ID, GALILEO_E6ABC),  "sig-E6ABC" },
        { TypeId(GNSS_SIGNAL_ID, GALILEO_E5BI),   "sig-E5BI" },
        { TypeId(GNSS_SIGNAL_ID, GALILEO_E5BQ),   "sig-E5BQ" },
        { TypeId(GNSS_SIGNAL_ID, GALILEO_E5BIQ),  "sig-E5BIQ" },
        { TypeId(GNSS_SIGNAL_ID, GALILEO_E5ABI),  "sig-E5ABI" },
        { TypeId(GNSS_SIGNAL_ID, GALILEO_E5ABQ),  "sig-E5ABQ" },
        { TypeId(GNSS_SIGNAL_ID, GALILEO_E5ABIQ), "sig-E5ABIQ" },
        { TypeId(GNSS_SIGNAL_ID, GALILEO_E5AI),   "sig-E5AI" },
        { TypeId(GNSS_SIGNAL_ID, GALILEO_E5AQ),   "sig-E5AQ" },
        { TypeId(GNSS_SIGNAL_ID, GALILEO_E5AIQ),  "sig-E5AIQ" },

        { TypeId(GNSS_SIGNAL_ID, SBAS_L1CA), "sig-L1CA" },
        { TypeId(GNSS_SIGNAL_ID, SBAS_L5I),  "sig-L5I" },
        { TypeId(GNSS_SIGNAL_ID, SBAS_L5Q),  "sig-L5Q" },
        { TypeId(GNSS_SIGNAL_ID, SBAS_L5IQ), "sig-L5IQ" },

        { TypeId(GNSS_SIGNAL_ID, QZSS_L1CA),  "sig-L1CA" },
        { TypeId(GNSS_SIGNAL_ID, QZSS_LEXS),  "sig-LEXS" },
        { TypeId(GNSS_SIGNAL_ID, QZSS_LEXL),  "sig-LEXL" },
        { TypeId(GNSS_SIGNAL_ID, QZSS_LEXSL), "sig-LEXSL" },
        { TypeId(GNSS_SIGNAL_ID, QZSS_L2CM),  "sig-L2CM" },
        { TypeId(GNSS_SIGNAL_ID, QZSS_L2CL),  "sig-L2CL" },
        { TypeId(GNSS_SIGNAL_ID, QZSS_L2CML), "sig-L2CML" },
        { TypeId(GNSS_SIGNAL_ID, QZSS_L5I),   "sig-L5I" },
        { TypeId(GNSS_SIGNAL_ID, QZSS_L5Q),   "sig-L5Q" },
        { TypeId(GNSS_SIGNAL_ID, QZSS_L5IQ),  "sig-L5IQ" },
        { TypeId(GNSS_SIGNAL_ID, QZSS_L1CD),  "sig-L1CD" },
        { TypeId(GNSS_SIGNAL_ID, QZSS_L1CP),  "sig-L1CP" },
        { TypeId(GNSS_SIGNAL_ID, QZSS_L1CDP), "sig-L1CDP" },

        { TypeId(GNSS_SIGNAL_ID, BEIDOU_B1I),  "sig-B1I" },
        { TypeId(GNSS_SIGNAL_ID, BEIDOU_B1Q),  "sig-B1Q" },
        { TypeId(GNSS_SIGNAL_ID, BEIDOU_B1IQ), "sig-B1IQ" },
        { TypeId(GNSS_SIGNAL_ID, BEIDOU_B3I),  "sig-B3I" },
        { TypeId(GNSS_SIGNAL_ID, BEIDOU_B3Q),  "sig-B3Q" },
        { TypeId(GNSS_SIGNAL_ID, BEIDOU_B3IQ), "sig-B3IQ" },
        { TypeId(GNSS_SIGNAL_ID, BEIDOU_B2I),  "sig-B2I" },
        { TypeId(GNSS_SIGNAL_ID, BEIDOU_B2Q),  "sig-B2Q" },
        { TypeId(GNSS_SIGNAL_ID, BEIDOU_B2IQ), "sig-B2IQ" },

        { TypeId(GNSS_RF_BAND, RF_BAND_L1), "rf-L1" },
        { TypeId(GNSS_RF_BAND, RF_BAND_L2), "rf-L2" },
        { TypeId(GNSS_RF_BAND, RF_BAND_L5), "rf-L5" },
    });

    const std::unordered_map<MipChannelIdentifier::SpecifierId, std::string, MipChannelIdentifier::SpecifierIdHash> MipChannelIdentifier::SPECIFIER_NAMES(
    {
        { SpecifierId(AIDING_MEASUREMENT_TYPE, GNSS, 1), "rec" },
        { SpecifierId(AIDING_MEASUREMENT_TYPE, GNSS, 2), "rec" }
    });

    bool MipChannelIdentifier::hasSpecifier() const
    {
        std::string throwaway;
        return hasSpecifier(throwaway);
    }

    bool MipChannelIdentifier::hasSpecifier(std::string& specifierName) const
    {
        //try to find the type in the map
        auto entry = SPECIFIER_NAMES.find(SpecifierId(m_type, m_id, m_specifier));

        //if we failed to find the channel
        if (entry == SPECIFIER_NAMES.end())
        {
            specifierName = "";
            return false;
        }

        specifierName = entry->second;
        return true;
    }

    std::string MipChannelIdentifier::name(bool standardizedFormat) const
    {
        //try to find the type in the map
        auto typeName = TYPE_NAMES.find(m_type);

        //if we failed to find the channel
        if (typeName == TYPE_NAMES.end())
        {
            return "unknownId_" + Utils::toStr(m_id);
        }

        std::string sensorcloudFilteredName = typeName->second + "_" + Utils::toStr(m_id);

        // add switch here to consolidate Type, ID pair where relevant
        // Ex: <GNSS_CONSTELLATION, 2> can just be "glonass" instead of "gnssConstellation_2"
        // Only apply this if standardizedFormat parameter is false
        if (!standardizedFormat)
        {
            auto translated = TRANSLATED_TYPE_NAMES.find(TypeId(m_type, m_id));
            if (translated != TRANSLATED_TYPE_NAMES.end())
            {
                sensorcloudFilteredName = translated->second;
            }
        }

        std::string specifierName;
        if (hasSpecifier(specifierName))
        {
            sensorcloudFilteredName += "_" + specifierName + "_" + Utils::toStr(m_specifier);
        }

        Utils::filterSensorcloudName(sensorcloudFilteredName);

        //found the channel, return the name
        return sensorcloudFilteredName;
    }

    AidingMeasurementInput::AidingMeasurementInput(const MipFieldValues& values)
    {
        parseMipFieldValues(values);
    }

    MipFieldValues AidingMeasurementInput::toMipFieldValues() const
    {
        MipFieldValues values;

        values.push_back(Value::UINT8(static_cast<uint8>(m_timestamp.storedEpoch())));
        values.push_back(Value::UINT8(0x01)); // reserved
        values.push_back(Value::UINT64(m_timestamp.nanoseconds()));

        values.push_back(Value::UINT8(m_frameId));

        appendMipFieldValues(values);

        values.push_back(Value::UINT16(static_cast<uint16>(m_validFlags.value())));

        return values;
    }

    void AidingMeasurementInput::parseMipFieldValues(const MipFieldValues& values)
    {
        m_timestamp = Timestamp(values[2].as_uint64(), static_cast<Timestamp::Epoch>(values[0].as_uint8()));
        m_frameId = values[3].as_uint8();

        m_validFlags = Bitfield(values[values.size() - 1].as_uint16());
    }

    AidingMeasurementPosition::AidingMeasurementPosition(PositionVelocityReferenceFrame referenceFrame, const MipFieldValues& values) :
        AidingMeasurementInput()
    {
        m_position.referenceFrame = referenceFrame;
        parseMipFieldValues(values);
    }

    void AidingMeasurementPosition::parseMipFieldValues(const MipFieldValues& values)
    {
        // parse out base values (timestamp, sensor id, valid flags)
        AidingMeasurementInput::parseMipFieldValues(values);

        m_position = Position(
            values[4].as_double(),
            values[5].as_double(),
            values[6].as_double(),
            m_position.referenceFrame
        );

        m_unc = GeometricUncertainty(
            values[7].as_float(),
            values[8].as_float(),
            values[9].as_float(),
            m_position.referenceFrame
        );
    }

    void AidingMeasurementPosition::appendMipFieldValues(MipFieldValues& values) const
    {
        values.push_back(Value::DOUBLE(m_position.x()));
        values.push_back(Value::DOUBLE(m_position.y()));
        values.push_back(Value::DOUBLE(m_position.z()));

        values.push_back(Value::FLOAT(m_unc.x()));
        values.push_back(Value::FLOAT(m_unc.y()));
        values.push_back(Value::FLOAT(m_unc.z()));
    }

    AidingMeasurementHeight::AidingMeasurementHeight(const MipFieldValues& values) :
        AidingMeasurementInput(),
        m_reference(HEIGHT_ABOVE_ELLIPSOID)
    {
        parseMipFieldValues(values);
    }

    void AidingMeasurementHeight::parseMipFieldValues(const MipFieldValues& values)
    {
        // parse out base values (timestamp, sensor id, valid flags)
        AidingMeasurementInput::parseMipFieldValues(values);

        m_height = values[4].as_float();
        m_unc = values[5].as_float();
    }

    void AidingMeasurementHeight::appendMipFieldValues(MipFieldValues& values) const
    {
        values.push_back(Value::FLOAT(m_height));
        values.push_back(Value::FLOAT(m_unc));
    }

    AidingMeasurementVelocity::AidingMeasurementVelocity(PositionVelocityReferenceFrame referenceFrame, const MipFieldValues& values) :
        AidingMeasurementInput()
    {
        m_velocity.referenceFrame = referenceFrame;
        parseMipFieldValues(values);
    }

    void AidingMeasurementVelocity::parseMipFieldValues(const MipFieldValues& values)
    {
        // parse out base values (timestamp, sensor id, valid flags)
        AidingMeasurementInput::parseMipFieldValues(values);

        m_velocity = Velocity(
            values[4].as_float(),
            values[5].as_float(),
            values[6].as_float(),
            m_velocity.referenceFrame
        );

        m_unc = GeometricUncertainty(
            values[7].as_float(),
            values[8].as_float(),
            values[9].as_float(),
            m_velocity.referenceFrame
        );
    }

    void AidingMeasurementVelocity::appendMipFieldValues(MipFieldValues& values) const
    {
        values.push_back(Value::FLOAT(m_velocity.x()));
        values.push_back(Value::FLOAT(m_velocity.y()));
        values.push_back(Value::FLOAT(m_velocity.z()));

        values.push_back(Value::FLOAT(m_unc.x()));
        values.push_back(Value::FLOAT(m_unc.y()));
        values.push_back(Value::FLOAT(m_unc.z()));
    }

    AidingMeasurementHeading::AidingMeasurementHeading(const MipFieldValues& values) :
        AidingMeasurementInput()
    {
        parseMipFieldValues(values);
    }

    AidingMeasurementMagneticField::AidingMeasurementMagneticField(const MipFieldValues& values) :
        AidingMeasurementInput()
    {
        parseMipFieldValues(values);
    }

    void AidingMeasurementMagneticField::parseMipFieldValues(const MipFieldValues& values)
    {
        // parse out base values (timestamp, sensor id, valid flags)
        AidingMeasurementInput::parseMipFieldValues(values);

        m_magField.fromMipFieldValues(values, 4);
        m_unc.fromMipFieldValues(values, 7);
    }

    void AidingMeasurementMagneticField::appendMipFieldValues(MipFieldValues& values) const
    {
        m_magField.appendMipFieldValues(values);
        m_unc.appendMipFieldValues(values);
    }

    void AidingMeasurementHeading::parseMipFieldValues(const MipFieldValues& values)
    {
        // parse out base values (timestamp, sensor id, valid flags)
        AidingMeasurementInput::parseMipFieldValues(values);

        m_heading = values[4].as_float();
        m_unc = values[5].as_float();
    }

    void AidingMeasurementHeading::appendMipFieldValues(MipFieldValues& values) const
    {
        values.push_back(Value::FLOAT(m_heading));
        values.push_back(Value::FLOAT(m_unc));
    }

    AidingMeasurementPressure::AidingMeasurementPressure(const MipFieldValues& values) :
        AidingMeasurementInput()
    {
        parseMipFieldValues(values);
    }

    void AidingMeasurementPressure::parseMipFieldValues(const MipFieldValues& values)
    {
        // parse out base values (timestamp, sensor id, valid flags)
        AidingMeasurementInput::parseMipFieldValues(values);

        m_pressure = values[4].as_float();
        m_unc = values[5].as_float();
    }

    void AidingMeasurementPressure::appendMipFieldValues(MipFieldValues& values) const
    {
        values.push_back(Value::FLOAT(m_pressure));
        values.push_back(Value::FLOAT(m_unc));
    }

    const std::string GnssReceiverInfo::INFO_NOT_FOUND = "Not Found";

    GnssReceiverInfo::GnssReceiverInfo() :
        id(0),
        targetDataClass(MipTypes::DataClass(0)),
        description(INFO_NOT_FOUND),
        module(INFO_NOT_FOUND),
        fwId(INFO_NOT_FOUND),
        fwVersion(Version(0, 0))
    {}

    GnssReceiverInfo::GnssReceiverInfo(const uint8 recId, const MipTypes::DataClass target, std::string desc) :
        id(recId),
        targetDataClass(target),
        description(std::move(desc)),
        module(INFO_NOT_FOUND),
        fwId(INFO_NOT_FOUND),
        fwVersion(Version(0, 0))
    {
        // Tokenize by comma
        const std::vector<std::string> segments = Utils::tokenize(description);

        // Module info exists
        if (!segments.empty())
        {
            module = segments[0];
            Utils::strTrim(module);
            module = module.empty() ? INFO_NOT_FOUND : module;
        }

        // Firmware info exists
        if (segments.size() > 1)
        {
            std::string fwTrim = segments[1];
            Utils::strTrim(fwTrim);

            // Pull fw version number from second element
            if (fwVersion.fromString(fwTrim))
            {
                // If version number found, parse out just identifier section by whitespace
                const std::vector<std::string> firmwareInfo = Utils::tokenize(fwTrim, " ", false);

                // Firmware ID found
                if (firmwareInfo.size() > 1)
                {
                    fwId = firmwareInfo[0];
                }
            }
            // No version number found, set whole element to fw identifier
            else
            {
                fwId = fwTrim;
            }

            fwId = fwId.empty() ? INFO_NOT_FOUND : fwId;
        }
    }

    SensorRange SupportedSensorRanges::lookupRecommended(SensorRange::Type type, float range) const
    {
        SensorRanges typeOptions;
        try
        {
            typeOptions = m_options.at(type);
            if (typeOptions.size() <= 0)
            {
                throw Error_NotSupported("The specified Sensor Range type is not supported");
            }
        }
        catch (const std::out_of_range&)
        {
            throw Error_NotSupported("The specified Sensor Range type is not supported");
        }

        // remove 5% for threshold comparison to account for rounding error
        // ex: supported range value is 2.6666, user specifies 2.67 - should still return 2.6666 range
        float rangeWithWiggleRoom = range * 0.95f;

        SensorRange closest = typeOptions[0];
        for (SensorRange option : typeOptions)
        {
            // if current entry lower than indicated target range, ignore
            // don't want to recommend a range that will likely be overrun
            if (option.range() < rangeWithWiggleRoom)
            {
                if (option.range() > closest.range())
                {
                    closest = option;
                }
                continue;
            }

            // if the difference between current entry and the specified range is less
            // than the difference of the previous closest
            // or previous closest is lower than the specified range
            // set new closest
            float closestDiff = abs(range - closest.range());
            float diff = abs(range - option.range());
            if (closestDiff > diff
                || closest.range() < rangeWithWiggleRoom)
            {
                closest = option;
                closestDiff = diff;
            }
        }

        return closest;
    }
} // namespace mscl
