/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "InertialTypes.h"
#include "mscl/Utils.h"

namespace mscl
{
    std::string InertialTypes::channelFieldToStr(ChannelField field)
    {
        switch(field)
        {
            case CH_FIELD_SENSOR_RAW_ACCEL_VEC:                        return "Raw Accelerometer Vector";
            case CH_FIELD_SENSOR_RAW_GYRO_VEC:                         return "Raw Gyro Vector";
            case CH_FIELD_SENSOR_RAW_MAG_VEC:                          return "Raw Magnetometer Vector";
            case CH_FIELD_SENSOR_SCALED_ACCEL_VEC:                     return "Scaled Accelerometer Vector";
            case CH_FIELD_SENSOR_SCALED_GYRO_VEC:                      return "Scaled Gyro Vector";
            case CH_FIELD_SENSOR_SCALED_MAG_VEC:                       return "Scaled Magnetometer Vector";
            case CH_FIELD_SENSOR_DELTA_THETA_VEC:                      return "Delta Theta Vector";
            case CH_FIELD_SENSOR_DELTA_VELOCITY_VEC:                   return "Delta Velocity Vector";
            case CH_FIELD_SENSOR_ORIENTATION_MATRIX:                   return "Orientation Matrix";
            case CH_FIELD_SENSOR_ORIENTATION_QUATERNION:               return "Quaternion";
            case CH_FIELD_SENSOR_ORIENTATION_UPDATE_MATRIX:            return "Orientation Update Matrix";
            case CH_FIELD_SENSOR_EULER_ANGLES:                         return "Euler Angles";
            case CH_FIELD_SENSOR_INTERNAL_TIMESTAMP:                   return "Internal Timestamp";
            case CH_FIELD_SENSOR_BEACONED_TIMESTAMP:                   return "Beaconed Timestamp";
            case CH_FIELD_SENSOR_STABILIZED_MAG_VEC:                   return "Stabilized Mag Vector (North)";
            case CH_FIELD_SENSOR_STABILIZED_ACCEL_VEC:                 return "Stabilized Accel Vector (Up)";
            case CH_FIELD_SENSOR_GPS_CORRELATION_TIMESTAMP:            return "GPS Correlation Timestamp";
            case CH_FIELD_SENSOR_SCALED_AMBIENT_PRESSURE:              return "Scaled Ambient Pressure";
            case CH_FIELD_GPS_LLH_POSITION:                            return "LLH Position";
            case CH_FIELD_GPS_ECEF_POSITION:                           return "ECEF Position";
            case CH_FIELD_GPS_NED_VELOCITY:                            return "NED Velocity";
            case CH_FIELD_GPS_ECEF_VELOCITY:                           return "ECEF Velocity";
            case CH_FIELD_GPS_DOP:                                     return "DOP Data";
            case CH_FIELD_GPS_UTC_TIME:                                return "UTC Time";
            case CH_FIELD_GPS_GPS_TIME:                                return "GPS Time";
            case CH_FIELD_GPS_CLOCK_INFO:                              return "Clock Information";
            case CH_FIELD_GPS_FIX_INFO:                                return "GPS Fix Information";
            case CH_FIELD_GPS_SPACE_VEHICLE_INFO:                      return "Space Vehicle Information";
            case CH_FIELD_GPS_HARDWARE_STATUS:                         return "Hardware Status";
            case CH_FIELD_GPS_DGPS_INFO:                               return "DGPS Information";
            case CH_FIELD_GPS_DGPS_CHANNEL_STATUS:                     return "DGPS Channel Status";
            case CH_FIELD_ESTFILTER_ESTIMATED_LLH_POS:                 return "Estimated LLH Position";
            case CH_FIELD_ESTFILTER_ESTIMATED_NED_VELOCITY:            return "Estimated NED Velocity";
            case CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_QUATERNION:       return "Estimated Orientation Quaternion";
            case CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_MATRIX:           return "Estimated Orientation Matrix";
            case CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_EULER:            return "Estimated Orientation, Euler Angles";
            case CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS:               return "Estimated Gyro Bias";
            case CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS:              return "Estimated Accel Bias";
            case CH_FIELD_ESTFILTER_ESTIMATED_LLH_UNCERT:              return "Estimated LLH Position Uncertainty";
            case CH_FIELD_ESTFILTER_ESTIMATED_NED_UNCERT:              return "Estimated NED Velocity Uncertainty";
            case CH_FIELD_ESTFILTER_ESTIMATED_ATT_UNCERT_EULER:        return "Estimated Attitude Uncertainty, Euler Angles";
            case CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS_UNCERT:        return "Estimated Gyro Bias Uncertainty";
            case CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS_UNCERT:       return "Estimated Accel Bias Uncertainty";
            case CH_FIELD_ESTFILTER_ESTIMATED_LINEAR_ACCEL:            return "Estimated Linear Acceleration";
            case CH_FIELD_ESTFILTER_ESTIMATED_ANGULAR_RATE:            return "Estimated Angular Rate";
            case CH_FIELD_ESTFILTER_WGS84_LOC_GRAV_MAGNITUDE:          return "WG284 Local Gravity Magnitude";
            case CH_FIELD_ESTFILTER_FILTER_STATUS:                     return "Filter Status";
            case CH_FIELD_ESTFILTER_GPS_TIMESTAMP:                     return "GPS Timestamp";
            case CH_FIELD_ESTFILTER_ESTIMATED_ATT_UNCERT_QUAT:         return "Estimated Attitude Uncertainty, Quaternion Elements";
            case CH_FIELD_ESTFILTER_ESTIMATED_GRAVITY_VECTOR:          return "Estimated Gravity Vector";
            case CH_FIELD_ESTFILTER_MAGNETIC_MODEL_SLN:                return "Magnetic Model Solution";
            case CH_FIELD_ESTFILTER_ESTIMATED_GYRO_SCALE_FACTOR:       return "Estimated Gyro Scale Factor";
            case CH_FIELD_ESTFILTER_ACCEL_SCALE_FACTOR:                return "Estimated Accel Scale Factor";
            case CH_FIELD_ESTFILTER_GYRO_SCALE_FACTOR_UNCERT:          return "Estimated Gyro Scale Factor Uncertainty";
            
            default:
                return Utils::toStr(field);
        }
    }

    std::string InertialTypes::channelQualifierToStr(ChannelQualifier qualifier)
    {
        switch(qualifier)
        {
            case CH_X:                         return "X";
            case CH_Y:                         return "Y";
            case CH_Z:                         return "Z";
            case CH_MATRIX:                    return "Matrix";
            case CH_QUATERNION:                return "Quaternion";
            case CH_ROLL:                      return "Roll";
            case CH_PITCH:                     return "Pitch";
            case CH_YAW:                       return "Yaw";
            case CH_TICK:                      return "Tick";
            case CH_TIMESTAMP:                 return "Timestamp";
            case CH_STATUS:                    return "Status";
            case CH_TIME_OF_WEEK:              return "Time of Week";
            case CH_WEEK_NUMBER:               return "Week Number";
            case CH_LATITUDE:                  return "Latitude";
            case CH_LONGITUDE:                 return "Longitude";
            case CH_HEIGHT_ABOVE_ELLIPSOID:    return "Height Above Ellipsoid";
            case CH_HEIGHT_ABOVE_MSL:          return "Height Above MSL";
            case CH_HORIZONTAL_ACCURACY:       return "Horizontal Accuracy";
            case CH_VERTICAL_ACCURACY:         return "Vertical Accuracy";
            case CH_POSITION_ACCURACY:         return "Position Accuracy";
            case CH_NORTH:                     return "North";
            case CH_EAST:                      return "East";
            case CH_DOWN:                      return "Down";
            case CH_SPEED:                     return "Speed";
            case CH_GROUND_SPEED:              return "Ground Speed";
            case CH_HEADING:                   return "Heading";
            case CH_SPEED_ACCURACY:            return "Speed Accuracy";
            case CH_HEADING_ACCURACY:          return "Heading Accuracy";
            case CH_VELOCITY_ACCURACY:         return "Velocity Accuracy";
            case CH_GEOMETRIC_DOP:             return "Geometric DOP";
            case CH_POSITION_DOP:              return "Position DOP";
            case CH_HORIZONTAL_DOP:            return "Horizontal DOP";
            case CH_VERTICAL_DOP:              return "Vertical DOP";
            case CH_TIME_DOP:                  return "Time DOP";
            case CH_NORTHING_DOP:              return "Northing DOP";
            case CH_EASTING_DOP:               return "Easting DOP";
            case CH_FLAGS:                     return "Flags";
            case CH_BIAS:                      return "Bias";
            case CH_DRIFT:                     return "Drift";
            case CH_ACCURACY_ESTIMATE:         return "Accuracy Estimate";
            case CH_FIX_TYPE:                  return "Fix Type";
            case CH_SV_COUNT:                  return "Space Vehicle Count";
            case CH_CHANNEL:                   return "Channel Number";
            case CH_ID:                        return "ID Number";
            case CH_CARRIER_TO_NOISE_RATIO:    return "Carrier to Noise Ratio";
            case CH_AZIMUTH:                   return "Azimuth";
            case CH_ELEVATION:                 return "Elevation";
            case CH_SENSOR_STATE:              return "Sensor State";
            case CH_ANTENNA_STATE:             return "Antenna State";
            case CH_ANTENNA_POWER:             return "Antenna Power";
            case CH_FILTER_STATE:              return "Filter State";
            case CH_DYNAMICS_MODE:             return "Dynamics Mode";
            case CH_MAGNITUDE:                 return "Magnitude";
            case CH_HEADING_UNCERTAINTY:       return "Heading Uncertainty";
            case CH_SOURCE:                    return "Source";
            case CH_INCLINATION:               return "Inclination";
            case CH_DECLINATION:               return "Declination";

            case CH_UNKNOWN:
            default:
                return "Unknown";
        }
    }

    std::string InertialTypes::channelName(ChannelField field, ChannelQualifier qualifier)
    {
        //try to find the channel in the map
        auto result = CHANNEL_NAMES.find(ChannelId(field, qualifier));

        //if we failed to find the channel
        if(result == CHANNEL_NAMES.end())
        {
            assert(false);
            return "unknown_" + Utils::toStr(field) + "-" + Utils::toStr(qualifier);
        }

        //replace any unsupported sensorcloud characters
        std::string sensorcloudFilteredName = result->second;
        Utils::filterSensorcloudName(sensorcloudFilteredName);

        //found the channel, return the name
        return sensorcloudFilteredName;
    }

    InertialTypes::InertialCategory InertialTypes::channelFieldToCategory(InertialTypes::ChannelField channelField)
    {
        return static_cast<InertialCategory>(Utils::msb(static_cast<uint16>(channelField)));
    }

    size_t InertialTypes::ChannelIdHash::operator()(const InertialTypes::ChannelId& channelId) const
    {
        return channelId.first ^ channelId.second;
    }

    const std::unordered_map<InertialTypes::ChannelId, std::string, InertialTypes::ChannelIdHash> InertialTypes::CHANNEL_NAMES(
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

        {ChannelId(CH_FIELD_GPS_LLH_POSITION, CH_LATITUDE), "latitude"},
        {ChannelId(CH_FIELD_GPS_LLH_POSITION, CH_LONGITUDE), "longitude"},
        {ChannelId(CH_FIELD_GPS_LLH_POSITION, CH_HEIGHT_ABOVE_ELLIPSOID), "heightAboveElipsoid"},
        {ChannelId(CH_FIELD_GPS_LLH_POSITION, CH_HEIGHT_ABOVE_MSL), "heightAboveMSL"},
        {ChannelId(CH_FIELD_GPS_LLH_POSITION, CH_HORIZONTAL_ACCURACY), "horizontalAccuracy"},
        {ChannelId(CH_FIELD_GPS_LLH_POSITION, CH_VERTICAL_ACCURACY), "verticalAccuracy"},

        {ChannelId(CH_FIELD_GPS_ECEF_POSITION, CH_X), "ecefPosX"},
        {ChannelId(CH_FIELD_GPS_ECEF_POSITION, CH_Y), "ecefPosY"},
        {ChannelId(CH_FIELD_GPS_ECEF_POSITION, CH_Z), "ecefPosZ"},
        {ChannelId(CH_FIELD_GPS_ECEF_POSITION, CH_POSITION_ACCURACY), "ecefPosAccuracy"},

        {ChannelId(CH_FIELD_GPS_NED_VELOCITY, CH_NORTH), "northVelocity"},
        {ChannelId(CH_FIELD_GPS_NED_VELOCITY, CH_EAST), "eastVelocity"},
        {ChannelId(CH_FIELD_GPS_NED_VELOCITY, CH_DOWN), "downVelocity"},
        {ChannelId(CH_FIELD_GPS_NED_VELOCITY, CH_SPEED), "speed"},
        {ChannelId(CH_FIELD_GPS_NED_VELOCITY, CH_GROUND_SPEED), "groundSpeed"},
        {ChannelId(CH_FIELD_GPS_NED_VELOCITY, CH_HEADING), "heading"},
        {ChannelId(CH_FIELD_GPS_NED_VELOCITY, CH_SPEED_ACCURACY), "speedAccuracy"},
        {ChannelId(CH_FIELD_GPS_NED_VELOCITY, CH_HEADING_ACCURACY), "headingAccuracy"},

        {ChannelId(CH_FIELD_GPS_ECEF_VELOCITY, CH_X), "ecefVelX"},
        {ChannelId(CH_FIELD_GPS_ECEF_VELOCITY, CH_Y), "ecefVelY"},
        {ChannelId(CH_FIELD_GPS_ECEF_VELOCITY, CH_Z), "ecefVelZ"},
        {ChannelId(CH_FIELD_GPS_ECEF_VELOCITY, CH_VELOCITY_ACCURACY), "ecefVelAccuracy"},

        {ChannelId(CH_FIELD_GPS_DOP, CH_GEOMETRIC_DOP), "geometricDOP"},
        {ChannelId(CH_FIELD_GPS_DOP, CH_POSITION_DOP), "positionDOP"},
        {ChannelId(CH_FIELD_GPS_DOP, CH_HORIZONTAL_DOP), "horizontalDOP"},
        {ChannelId(CH_FIELD_GPS_DOP, CH_VERTICAL_DOP), "verticalDOP"},
        {ChannelId(CH_FIELD_GPS_DOP, CH_TIME_DOP), "timeDOP"},
        {ChannelId(CH_FIELD_GPS_DOP, CH_NORTHING_DOP), "northingDOP"},
        {ChannelId(CH_FIELD_GPS_DOP, CH_EASTING_DOP), "eastingDOP"},

        {ChannelId(CH_FIELD_GPS_UTC_TIME, CH_TIMESTAMP), "utcTimestamp"},
        {ChannelId(CH_FIELD_GPS_UTC_TIME, CH_FLAGS), "utcTimestampFlags"},

        {ChannelId(CH_FIELD_GPS_GPS_TIME, CH_TIME_OF_WEEK), "gpsTimeTow"},
        {ChannelId(CH_FIELD_GPS_GPS_TIME, CH_WEEK_NUMBER), "gpsTimeWeekNum"},

        {ChannelId(CH_FIELD_GPS_CLOCK_INFO, CH_BIAS), "gpsClockBias"},
        {ChannelId(CH_FIELD_GPS_CLOCK_INFO, CH_DRIFT), "gpsClockDrift"},
        {ChannelId(CH_FIELD_GPS_CLOCK_INFO, CH_ACCURACY_ESTIMATE), "gpsClockAccuracy"},

        {ChannelId(CH_FIELD_GPS_FIX_INFO, CH_FIX_TYPE), "gpsFixType"},
        {ChannelId(CH_FIELD_GPS_FIX_INFO, CH_SV_COUNT), "gpsFixSvCount"},
        {ChannelId(CH_FIELD_GPS_FIX_INFO, CH_FLAGS), "gpsFixFlags"},

        {ChannelId(CH_FIELD_GPS_SPACE_VEHICLE_INFO, CH_CHANNEL), "spaceVehicleChannel"},
        {ChannelId(CH_FIELD_GPS_SPACE_VEHICLE_INFO, CH_ID), "spaceVehicleId"},
        {ChannelId(CH_FIELD_GPS_SPACE_VEHICLE_INFO, CH_CARRIER_TO_NOISE_RATIO), "spaceVehicleCarrierToNoiseRatio"},
        {ChannelId(CH_FIELD_GPS_SPACE_VEHICLE_INFO, CH_AZIMUTH), "spaceVehicleAzimuth"},
        {ChannelId(CH_FIELD_GPS_SPACE_VEHICLE_INFO, CH_ELEVATION), "spaceVehicleElevation"},
        {ChannelId(CH_FIELD_GPS_SPACE_VEHICLE_INFO, CH_FLAGS), "spaceVehicleFlags"},

        {ChannelId(CH_FIELD_GPS_HARDWARE_STATUS, CH_SENSOR_STATE), "sensorState"},
        {ChannelId(CH_FIELD_GPS_HARDWARE_STATUS, CH_ANTENNA_STATE), "antennaState"},
        {ChannelId(CH_FIELD_GPS_HARDWARE_STATUS, CH_ANTENNA_POWER), "antennaPower"},

        {ChannelId(CH_FIELD_GPS_DGPS_INFO, CH_AGE), "dgpsNewestAge"},
        {ChannelId(CH_FIELD_GPS_DGPS_INFO, CH_ID), "dgpsBaseStationId"},
        {ChannelId(CH_FIELD_GPS_DGPS_INFO, CH_STATUS), "dgpsBaseStationStatus"},
        {ChannelId(CH_FIELD_GPS_DGPS_INFO, CH_NUM_CHANNELS), "dgpsNumChannels"},

        {ChannelId(CH_FIELD_GPS_DGPS_CHANNEL_STATUS, CH_ID), "dgpsSpaceVehicleId"},
        {ChannelId(CH_FIELD_GPS_DGPS_CHANNEL_STATUS, CH_AGE), "dgpsAge"},
        {ChannelId(CH_FIELD_GPS_DGPS_CHANNEL_STATUS, CH_CORRECTION), "dgpsPseudorangeCorrection"},
        {ChannelId(CH_FIELD_GPS_DGPS_CHANNEL_STATUS, CH_RATE_CORRECTION), "dgpsPseudorangeRateCorrection"},

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

        {ChannelId(CH_FIELD_ESTFILTER_GPS_ANTENNA_CORRECTION, CH_X), "estGpsAntennaOffsetCorrectX"},
        {ChannelId(CH_FIELD_ESTFILTER_GPS_ANTENNA_CORRECTION, CH_Y), "estGpsAntennaOffsetCorrectY"},
        {ChannelId(CH_FIELD_ESTFILTER_GPS_ANTENNA_CORRECTION, CH_Z), "estGpsAntennaOffsetCorrectZ"},

        {ChannelId(CH_FIELD_ESTFILTER_GPS_ANTENNA_CORRECTION_UNCERT, CH_X), "estGpsAntennaOffsetCorrectXUncert"},
        {ChannelId(CH_FIELD_ESTFILTER_GPS_ANTENNA_CORRECTION_UNCERT, CH_Y), "estGpsAntennaOffsetCorrectYUncert"},
        {ChannelId(CH_FIELD_ESTFILTER_GPS_ANTENNA_CORRECTION_UNCERT, CH_Z), "estGpsAntennaOffsetCorrectZUncert"},
    });
}