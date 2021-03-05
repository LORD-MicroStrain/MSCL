/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include <boost/utility/binary.hpp>

#include "mscl/MicroStrain/MIP/Packets/MipFieldParser.h"
#include "mscl/MicroStrain/MIP/Packets/MipDataPacket.h"

namespace mscl
{
    //Title: InertialFieldParser_Sensor

    class MipDataField;

    //Class: FieldParser_RawAccelVector
    //    The Field Parser for raw accelerometer data
    class FieldParser_RawAccelVector : public MipFieldParser
    {
    private:
        FieldParser_RawAccelVector(){};    //default constructor disabled

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

    //Class: FieldParser_RawGyroVector
    //    The field parser for raw gyro data
    class FieldParser_RawGyroVector : public MipFieldParser
    {
    private:
        FieldParser_RawGyroVector(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_RawMagVector
    //    The field parser for raw magnetometer data
    class FieldParser_RawMagVector : public MipFieldParser
    {
    private:
        FieldParser_RawMagVector(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_ScaledAccelVector
    //    The field parser for scaled accelerometer data
    class FieldParser_ScaledAccelVector : public MipFieldParser
    {
    private:
        FieldParser_ScaledAccelVector(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_ScaledGyroVector
    //    The field parser for scaled gyro data
    class FieldParser_ScaledGyroVector : public MipFieldParser
    {
    private:
        FieldParser_ScaledGyroVector(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_ScaledMagVector
    //    The field parser for scaled magnetometer data
    class FieldParser_ScaledMagVector : public MipFieldParser
    {
    private:
        FieldParser_ScaledMagVector(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_DeltaThetaVector
    //    The field parser for delta theta data
    class FieldParser_DeltaThetaVector : public MipFieldParser
    {
    private:
        FieldParser_DeltaThetaVector(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_DeltaVelocityVector
    //    The field parser for delta velocity data
    class FieldParser_DeltaVelocityVector : public MipFieldParser
    {
    private:
        FieldParser_DeltaVelocityVector(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_OrientationMatrix
    //    The field parser for orientation matrix data
    class FieldParser_OrientationMatrix : public MipFieldParser
    {
    private:
        FieldParser_OrientationMatrix(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_Quaternion
    //    The field parser for quaternion data
    class FieldParser_Quaternion : public MipFieldParser
    {
    private:
        FieldParser_Quaternion(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_OrientationUpdateMatrix
    //    The field parser for orientation matrix data
    class FieldParser_OrientationUpdateMatrix : public MipFieldParser
    {
    private:
        FieldParser_OrientationUpdateMatrix(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_EulerAngles
    //    The field parser for Euler Angles data
    class FieldParser_EulerAngles : public MipFieldParser
    {
    private:
        FieldParser_EulerAngles(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_InternalTimestamp
    //    The field parser for Internal Timestamp data
    class FieldParser_InternalTimestamp : public MipFieldParser
    {
    private:
        FieldParser_InternalTimestamp(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_BeaconedTimestamp
    //    The field parser for Beaconed Timestamp data
    class FieldParser_BeaconedTimestamp : public MipFieldParser
    {
    private:
        FieldParser_BeaconedTimestamp(){};        //default constructor disabled

        //Constants: Valid Flags
        //    TIMESTAMP_FLAG        - b0001 - The flag position for checking the Timestamp status
        static const uint8 TIMESTAMP_FLAG = BOOST_BINARY(0001);

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_StabilizedMagVector
    //    The field parser for Stabilized Mag Vector (North)
    class FieldParser_StabilizedMagVector : public MipFieldParser
    {
    private:
        FieldParser_StabilizedMagVector(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_StabilizedAccelVector
    //    The field parser for Stabilized Accel Vector (Up)
    class FieldParser_StabilizedAccelVector : public MipFieldParser
    {
    private:
        FieldParser_StabilizedAccelVector(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_GpsCorrelationTimestamp
    //    The field parser for GPS Correlation Timestamp
    class FieldParser_GpsCorrelationTimestamp : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    TS_FLAG    - b00000001    - The flag position for checking the Timestamp Valid flag
        static const uint16 TS_FLAG = BOOST_BINARY(00000100);

        FieldParser_GpsCorrelationTimestamp(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_GpsCorrelationTimestamp
    //    The field parser for GPS Correlation Timestamp
    class FieldParser_TemperatureStatistics : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    TS_FLAG    - b00000001    - The flag position for checking the Timestamp Valid flag

        FieldParser_TemperatureStatistics() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_ScaledAmbientPressure
    //    The field parser for Scaled Ambient Pressure.
    class FieldParser_ScaledAmbientPressure : public MipFieldParser
    {
    private:
        FieldParser_ScaledAmbientPressure() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_RawAmbientPressure
    //    The field parser for Raw Ambient Pressure.
    class FieldParser_RawAmbientPressure : public MipFieldParser
    {
    private:
        FieldParser_RawAmbientPressure() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_OdometerData
    //    The field parser for the Odometer Data field.
    class FieldParser_OdometerData : public MipFieldParser
    {
    private:
        FieldParser_OdometerData() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };
}