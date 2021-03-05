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
    //Title: InertialFieldParser_EstFilter

    class MipDataField;

    //Class: FieldParser_FilterStatus
    //    The field parser for Filter Status data
    class FieldParser_FilterStatus : public MipFieldParser
    {
    private:
        FieldParser_FilterStatus(){};        //default constructor disabled

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

    //Class: FieldParser_NAV_GPS_Timestamp
    //    The field parser for NAV GPS Timestamp data
    class FieldParser_NAV_GPS_Timestamp : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    TIME_FLAG        - b00000001 - The flag position for checking the Valid Time flag
        static const uint16 TIME_FLAG        = BOOST_BINARY(00000001);

    private:
        FieldParser_NAV_GPS_Timestamp(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_EstimatedLLHPosition
    //    The field parser for Estimated LLH Position data
    class FieldParser_EstimatedLLHPosition : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    LLH_FLAG        - b00000001 - The flag position for checking the LLH flag
        static const uint16 LLH_FLAG        = BOOST_BINARY(00000001);

    private:
        FieldParser_EstimatedLLHPosition(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_EstimatedNEDVelocity
    //    The field parser for Estimated NED Velocity data
    class FieldParser_EstimatedNEDVelocity : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    NED_FLAG        - b00000001 - The flag position for checking the NED Velocity flag
        static const uint16 NED_FLAG        = BOOST_BINARY(00000001);

    private:
        FieldParser_EstimatedNEDVelocity(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_EstimatedQuaternion
    //    The field parser for Estimated Orientation Quaternion data
    class FieldParser_EstimatedQuaternion : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    NED_FLAG        - b00000001 - The flag position for checking the Orientation Quaternion flag
        static const uint16 QUATERNION_FLAG        = BOOST_BINARY(00000001);

    private:
        FieldParser_EstimatedQuaternion(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_EstimatedMatrix
    //    The field parser for Estimated Orientation Matrix data
    class FieldParser_EstimatedMatrix : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    NED_FLAG        - b00000001 - The flag position for checking the Orientation Quaternion flag
        static const uint16 MATRIX_FLAG        = BOOST_BINARY(00000001);

    private:
        FieldParser_EstimatedMatrix(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_EstimatedEulerAngles
    //    The field parser for Estimated Orientation Euler Angles data
    class FieldParser_EstimatedEulerAngles : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    EULER_FLAG        - b00000001 - The flag position for checking the Orientation Quaternion flag
        static const uint16 EULER_FLAG        = BOOST_BINARY(00000001);

    private:
        FieldParser_EstimatedEulerAngles(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_EstimatedGyroBias
    //    The field parser for Estimated Gyro Bias data
    class FieldParser_EstimatedGyroBias : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    GYRO_FLAG        - b00000001 - The flag position for checking the Gyro Bias flag
        static const uint16 GYRO_FLAG        = BOOST_BINARY(00000001);

    private:
        FieldParser_EstimatedGyroBias(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_EstimatedAccelBias
    //    The field parser for Estimated Accel Bias data
    class FieldParser_EstimatedAccelBias : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    ACCEL_FLAG        - b00000001 - The flag position for checking the Accel Bias flag
        static const uint16 ACCEL_FLAG = BOOST_BINARY(00000001);

    private:
        FieldParser_EstimatedAccelBias() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_EstimatedLLHPosUncertainty
    //    The field parser for Estimated LLH Position Uncertainty data
    class FieldParser_EstimatedLLHPosUncertainty : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    UNCERTAINTY_FLAG        - b00000001 - The flag position for checking the Uncertainty flag
        static const uint16 UNCERTAINTY_FLAG        = BOOST_BINARY(00000001);

    private:
        FieldParser_EstimatedLLHPosUncertainty(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_EstimatedNEDUncertainty
    //    The field parser for Estimated NED Velocity Uncertainty data
    class FieldParser_EstimatedNEDUncertainty : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    UNCERTAINTY_FLAG        - b00000001 - The flag position for checking the Uncertainty flag
        static const uint16 UNCERTAINTY_FLAG        = BOOST_BINARY(00000001);

    private:
        FieldParser_EstimatedNEDUncertainty(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_EstimatedAttEulerUncertainty
    //    The field parser for Estimated Attitude Euler Angles Uncertainty data
    class FieldParser_EstimatedAttEulerUncertainty : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    UNCERTAINTY_FLAG        - b00000001 - The flag position for checking the Uncertainty flag
        static const uint16 UNCERTAINTY_FLAG        = BOOST_BINARY(00000001);

    private:
        FieldParser_EstimatedAttEulerUncertainty(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_EstimatedGyroBiasUncertainty
    //    The field parser for Estimated Gyro Bias Uncertainty data
    class FieldParser_EstimatedGyroBiasUncertainty : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    UNCERTAINTY_FLAG        - b00000001 - The flag position for checking the Uncertainty flag
        static const uint16 UNCERTAINTY_FLAG        = BOOST_BINARY(00000001);

    private:
        FieldParser_EstimatedGyroBiasUncertainty(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_EstimatedAccelBiasUncertainty
    //    The field parser for Estimated Accel Bias Uncertainty data
    class FieldParser_EstimatedAccelBiasUncertainty : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    UNCERTAINTY_FLAG        - b00000001 - The flag position for checking the Uncertainty flag
        static const uint16 UNCERTAINTY_FLAG = BOOST_BINARY(00000001);

    private:
        FieldParser_EstimatedAccelBiasUncertainty() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_EstimatedLinearAccel
    //    The field parser for Estimated Linear Acceleration data
    class FieldParser_EstimatedLinearAccel : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    ACCEL_FLAG        - b00000001 - The flag position for checking the Linear Acceleration flag
        static const uint16 ACCEL_FLAG        = BOOST_BINARY(00000001);

    private:
        FieldParser_EstimatedLinearAccel(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_EstimatedAngularRate
    //    The field parser for Estimated Angular Rate data
    class FieldParser_EstimatedAngularRate : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    RATE_FLAG        - b00000001 - The flag position for checking the Angular Rate flag
        static const uint16 RATE_FLAG        = BOOST_BINARY(00000001);

    private:
        FieldParser_EstimatedAngularRate(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_WGS84LocalGravMagnitude
    //    The field parser for WGS84 Local Gravity Magnitude data
    class FieldParser_WGS84LocalGravMagnitude : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    GRAV_FLAG        - b00000001 - The flag position for checking the Gravity Magnitude flag
        static const uint16 GRAV_FLAG        = BOOST_BINARY(00000001);

    private:
        FieldParser_WGS84LocalGravMagnitude(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_EstimatedAttQuaternUncertainty
    //    The field parser for Estimated Attitude Uncertainty, Quaternion Elements data
    class FieldParser_EstimatedAttQuaternUncertainty : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    UNCERT_FLAG        - b00000001 - The flag position for checking the Uncertainty flag
        static const uint16 UNCERT_FLAG        = BOOST_BINARY(00000001);

    private:
        FieldParser_EstimatedAttQuaternUncertainty(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_EstimatedGravityVector
    //    The field parser for Estimated Gravity Vector data
    class FieldParser_EstimatedGravityVector : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    GRAV_FLAG        - b00000001 - The flag position for checking the Gravity Vector flag
        static const uint16 GRAV_FLAG        = BOOST_BINARY(00000001);

    private:
        FieldParser_EstimatedGravityVector(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_HeadingUpdateSource
    //    The field parser for Heading Update Source State data
    class FieldParser_HeadingUpdateSource : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    HEADING_FLAG        - b00000001 - The flag position for checking the Heading Flag
        static const uint16 HEADING_FLAG        = BOOST_BINARY(00000001);

    private:
        FieldParser_HeadingUpdateSource(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_MagneticModelSolution
    //    The field parser for Magnetic Model Solution data
    class FieldParser_MagneticModelSolution : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    SLN_FLAG        - b00000001 - The flag position for checking the Magnetic Model Solution Flag
        static const uint16 SLN_FLAG        = BOOST_BINARY(00000001);

    private:
        FieldParser_MagneticModelSolution(){};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_EstimatedGyroScaleFactor
    //    The field parser for Estimated Gyro Scale Factor data
    class FieldParser_EstimatedGyroScaleFactor : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    VALID_FLAG        - b00000001 - The flag position for checking the Estimated Gyro Scale Factor flag
        static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

    private:
        FieldParser_EstimatedGyroScaleFactor() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_EstimatedAccelScaleFactor
    //    The field parser for Estimated Accel Scale Factor data
    class FieldParser_EstimatedAccelScaleFactor : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    VALID_FLAG        - b00000001 - The flag position for checking the Estimated Gyro Scale Factor flag
        static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

    private:
        FieldParser_EstimatedAccelScaleFactor() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_EstimatedGyroScaleFactorUncertainty
    //    The field parser for Estimated Gyro Scale Factor Uncertainty data
    class FieldParser_EstimatedGyroScaleFactorUncertainty : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    VALID_FLAG        - b00000001 - The flag position for checking the Estimated Gyro Scale Factor flag
        static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

    private:
        FieldParser_EstimatedGyroScaleFactorUncertainty() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_EstimatedAccelScaleFactorUncertainty
    //    The field parser for Estimated Accel Scale Factor Uncertainty data
    class FieldParser_EstimatedAccelScaleFactorUncertainty : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    VALID_FLAG        - b00000001 - The flag position for checking the Estimated Gyro Scale Factor flag
        static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

    private:
        FieldParser_EstimatedAccelScaleFactorUncertainty() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_CompensatedAccel
    //    The field parser for Compensated Acceleration data
    class FieldParser_CompensatedAccel : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    VALID_FLAG        - b00000001 - The flag position for checking the Estimated Gyro Scale Factor flag
        static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

    private:
        FieldParser_CompensatedAccel() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_StdAtmModel
    //    The field parser for Standard Atmosphere Model data
    class FieldParser_StdAtmModel : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    VALID_FLAG        - b00000001 - The flag position for checking the Estimated Gyro Scale Factor flag
        static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

    private:
        FieldParser_StdAtmModel() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_PressureAlt
    //    The field parser for Pressure Altitude data
    class FieldParser_PressureAlt : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    VALID_FLAG        - b00000001 - The flag position for checking the Estimated Gyro Scale Factor flag
        static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

    private:
        FieldParser_PressureAlt() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_MagAutoHardIronOffset
    //    The field parser for Estimated Mag Auto Hard Iron Offset data
    class FieldParser_MagAutoHardIronOffset: public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    VECTOR_FLAG        - b00000001 - The flag position for checking the Vector flag
        static const uint16 VECTOR_FLAG = BOOST_BINARY(00000001);

    private:
        FieldParser_MagAutoHardIronOffset() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_MagBias
    //    The field parser for Estimated Mag Auto Hard Iron Offset data
    class FieldParser_MagBias : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    VALID_FLAG        - b00000001 - The flag position for checking the Mag Bias flag
        static const uint16 VALID_FLAG = BOOST_BINARY(00000001);
        
        FieldParser_MagBias() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_MagAutoSoftIronMatrix
    //    The field parser for Estimated Mag Auto Soft Iron Matrix data
    class FieldParser_MagAutoSoftIronMatrix: public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    MATRIX_FLAG        - b00000001 - The flag position for checking the Matrix flag
        static const uint16 MATRIX_FLAG = BOOST_BINARY(00000001);

    private:
        FieldParser_MagAutoSoftIronMatrix() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_MagAutoHardIronOffsetUncert
    //    The field parser for Estimated Mag Auto Hard Iron Offset Uncertainty data
    class FieldParser_MagAutoHardIronOffsetUncert: public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    VECTOR_FLAG        - b00000001 - The flag position for checking the Vector flag
        static const uint16 VECTOR_FLAG = BOOST_BINARY(00000001);

    private:
        FieldParser_MagAutoHardIronOffsetUncert() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_MagBiasUncert
    //    The field parser for Estimated Mag Bias Uncertainty data
    class FieldParser_MagBiasUncert : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    VALID_FLAG        - b00000001 - The flag position for checking the Mag Bias Uncertainty flag
        static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

        FieldParser_MagBiasUncert() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_MagAutoSoftIronMatrixUncert
    //    The field parser for Estimated Mag Auto Soft Iron Matrix Uncertainty data
    class FieldParser_MagAutoSoftIronMatrixUncert: public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    MATRIX_FLAG        - b00000001 - The flag position for checking the Matrix flag
        static const uint16 MATRIX_FLAG = BOOST_BINARY(00000001);

    private:
        FieldParser_MagAutoSoftIronMatrixUncert() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_MagCovarianceMatrix
    //    The field parser for the Estimated Magnetometer Covariance Matrix field
    class FieldParser_MagCovarianceMatrix : public MipFieldParser
    {
    private:
        FieldParser_MagCovarianceMatrix() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_MagResidualVector
    //    The field parser for the Magnetometer Residual Vector field
    class FieldParser_MagResidualVector : public MipFieldParser
    {
    private:
        FieldParser_MagResidualVector() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_GnssAntennaOffsetCorrection
    //    The field parser for GNSS Antenna Offset Correction data
    class FieldParser_GnssAntennaOffsetCorrection: public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    VALID_FLAG        - b00000001 - The flag position for checking the Estimated Gyro Scale Factor flag
        static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

    private:
        FieldParser_GnssAntennaOffsetCorrection() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_GnssAntennaOffsetCorrectionUncert
    //    The field parser for GNSS Antenna Offset Correction Uncertainty data
    class FieldParser_GnssAntennaOffsetCorrectionUncert: public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    VALID_FLAG        - b00000001 - The flag position for checking the Estimated Gyro Scale Factor flag
        static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

    private:
        FieldParser_GnssAntennaOffsetCorrectionUncert() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_GnssClockCorrection
    //    The field parser for GNSS Clock Correction data
    class FieldParser_GnssClockCorrection : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    VALID_FLAG        - b00000001 - The flag position for checking the Estimated Gyro Scale Factor flag
        static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

    private:
        FieldParser_GnssClockCorrection() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_GnssClockCorrectionUncert
    //    The field parser for GNSS Clock Correction Uncertainty data
    class FieldParser_GnssClockCorrectionUncert : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    VALID_FLAG        - b00000001 - The flag position for checking the Estimated Gyro Scale Factor flag
        static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

    private:
        FieldParser_GnssClockCorrectionUncert() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_GnssMultiAntennaOffsetCorrection
    //    The field parser for GNSS Multi-Antenna Offset Correction data
    class FieldParser_GnssMultiAntennaOffsetCorrection : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    VALID_FLAG        - b00000001 - The flag position for checking the Estimated Gyro Scale Factor flag
        static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

    private:
        FieldParser_GnssMultiAntennaOffsetCorrection() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_GnssMultiAntennaOffsetCorrectionUncert
    //    The field parser for GNSS Multi-Antenna Offset Correction Uncertainty data
    class FieldParser_GnssMultiAntennaOffsetCorrectionUncert : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    VALID_FLAG        - b00000001 - The flag position for checking the Estimated Gyro Scale Factor flag
        static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

    private:
        FieldParser_GnssMultiAntennaOffsetCorrectionUncert() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_EcefPositionUncert
    //    The field parser for ECEF Position Uncertainty data
    class FieldParser_EcefPositionUncert : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    VALID_FLAG        - b00000001 - The flag position for checking the field data valid flag
        static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

    private:
        FieldParser_EcefPositionUncert() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_EcefVelocityUncert
    //    The field parser for ECEF Velocity Uncertainty data
    class FieldParser_EcefVelocityUncert : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    VALID_FLAG        - b00000001 - The flag position for checking the field data valid flag
        static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

    private:
        FieldParser_EcefVelocityUncert() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_EcefPosition
    //    The field parser for ECEF Position data
    class FieldParser_EcefPosition : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    VALID_FLAG        - b00000001 - The flag position for checking the field data valid flag
        static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

    private:
        FieldParser_EcefPosition() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_EcefVelocity
    //    The field parser for ECEF Velocity data
    class FieldParser_EcefVelocity : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    VALID_FLAG        - b00000001 - The flag position for checking the field data valid flag
        static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

    private:
        FieldParser_EcefVelocity() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_NedRelativePos
    //    The field parser for NED Relative Position data
    class FieldParser_NedRelativePos : public MipFieldParser
    {
    private:
        //Constants: Valid Flags
        //    VALID_FLAG        - b00000001 - The flag position for checking the field data valid flag
        static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

    private:
        FieldParser_NedRelativePos() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_FilterPosAidingStatus
    //    The field parser for the filter GNSS Position Aiding status
    class FieldParser_FilterPosAidingStatus : public MipFieldParser
    {
    private:
        FieldParser_FilterPosAidingStatus() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_FilterAttAidingStatus
    //    The field parser for the filter GNSS Attitude Aiding status
    class FieldParser_FilterAttAidingStatus : public MipFieldParser
    {
    private:
        FieldParser_FilterAttAidingStatus() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_FilterAidingSummary
    //    The field parser for the filter Aiding Measurement Summary
    class FieldParser_FilterAidingSummary : public MipFieldParser
    {
    private:
        FieldParser_FilterAidingSummary() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_OdometerScaleError
    //    The field parser for the filter Odometer Scale Factor Error
    class FieldParser_OdometerScaleError : public MipFieldParser
    {
    private:
        FieldParser_OdometerScaleError() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_OdometerScaleErrorUncert
    //    The field parser for the filter Odometer Scale Factor Error Uncertainty
    class FieldParser_OdometerScaleErrorUncert : public MipFieldParser
    {
    private:
        FieldParser_OdometerScaleErrorUncert() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_DualAntennaStatus
    //    The field parser for the filter GNSS Dual Antenna Status data
    class FieldParser_DualAntennaStatus : public MipFieldParser
    {
    private:
        FieldParser_DualAntennaStatus() {};        //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };
}