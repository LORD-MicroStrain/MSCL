/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include <boost/utility/binary.hpp>

#include "InertialFieldParser.h"
#include "InertialDataPacket.h"

namespace mscl
{
	//Title: InertialFieldParser_EstFilter

	class InertialDataField;

	//Class: FieldParser_FilterStatus
	//	The field parser for Filter Status data
	class FieldParser_FilterStatus : public InertialFieldParser
	{
	private:
		FieldParser_FilterStatus(){};		//default constructor disabled

	public:
		//Function: parse
		//	Parses an <InertialDataField> for <InertialDataPoints> and stores them in the valid or invalid result vectors
		//
		//Parameters:
		//	field - The <InertialDataField> to parse for data points
		//	result - The <InertialDataPoints> vector to store the data points in
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;

		//Function: registerParser
		//	The static function that registers this parser with the list of parsers (called immediately)
		//
		//Returns:
		//	true, just for assigning the REGISTERED constant to true
		static bool registerParser();

	public:
		//Constant: FIELD_TYPE
		//	The 2-byte field type (Descriptor ID + Field ID) for this parser
		static const InertialTypes::ChannelField FIELD_TYPE;

		//Constant: REGISTERED
		//	Whether this parser is registered. This will always be true. This is used to call registerParser() immediately
		static const bool REGISTERED;
	};

	//Class: FieldParser_NAV_GPS_Timestamp
	//	The field parser for NAV GPS Timestamp data
	//
	//See Also:
	//	<FieldParser_FilterStatus>
	class FieldParser_NAV_GPS_Timestamp : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	TIME_FLAG		- b00000001 - The flag position for checking the Valid Time flag
		static const uint16 TIME_FLAG		= BOOST_BINARY(00000001);

	private:
		FieldParser_NAV_GPS_Timestamp(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_EstimatedLLHPosition
	//	The field parser for Estimated LLH Position data
	//
	//See Also:
	//	<FieldParser_FilterStatus>
	class FieldParser_EstimatedLLHPosition : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	LLH_FLAG		- b00000001 - The flag position for checking the LLH flag
		static const uint16 LLH_FLAG		= BOOST_BINARY(00000001);

	private:
		FieldParser_EstimatedLLHPosition(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_EstimatedNEDVelocity
	//	The field parser for Estimated NED Velocity data
	//
	//See Also:
	//	<FieldParser_FilterStatus>
	class FieldParser_EstimatedNEDVelocity : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	NED_FLAG		- b00000001 - The flag position for checking the NED Velocity flag
		static const uint16 NED_FLAG		= BOOST_BINARY(00000001);

	private:
		FieldParser_EstimatedNEDVelocity(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_EstimatedQuaternion
	//	The field parser for Estimated Orientation Quaternion data
	//
	//See Also:
	//	<FieldParser_FilterStatus>
	class FieldParser_EstimatedQuaternion : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	NED_FLAG		- b00000001 - The flag position for checking the Orientation Quaternion flag
		static const uint16 QUATERNION_FLAG		= BOOST_BINARY(00000001);

	private:
		FieldParser_EstimatedQuaternion(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_EstimatedMatrix
	//	The field parser for Estimated Orientation Matrix data
	//
	//See Also:
	//	<FieldParser_FilterStatus>
	class FieldParser_EstimatedMatrix : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	NED_FLAG		- b00000001 - The flag position for checking the Orientation Quaternion flag
		static const uint16 MATRIX_FLAG		= BOOST_BINARY(00000001);

	private:
		FieldParser_EstimatedMatrix(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_EstimatedEulerAngles
	//	The field parser for Estimated Orientation Euler Angles data
	//
	//See Also:
	//	<FieldParser_FilterStatus>
	class FieldParser_EstimatedEulerAngles : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	EULER_FLAG		- b00000001 - The flag position for checking the Orientation Quaternion flag
		static const uint16 EULER_FLAG		= BOOST_BINARY(00000001);

	private:
		FieldParser_EstimatedEulerAngles(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_EstimatedGyroBias
	//	The field parser for Estimated Gyro Bias data
	//
	//See Also:
	//	<FieldParser_FilterStatus>
	class FieldParser_EstimatedGyroBias : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	GYRO_FLAG		- b00000001 - The flag position for checking the Gyro Bias flag
		static const uint16 GYRO_FLAG		= BOOST_BINARY(00000001);

	private:
		FieldParser_EstimatedGyroBias(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_EstimatedAccelBias
	//	The field parser for Estimated Accel Bias data
	class FieldParser_EstimatedAccelBias : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	ACCEL_FLAG		- b00000001 - The flag position for checking the Accel Bias flag
		static const uint16 ACCEL_FLAG = BOOST_BINARY(00000001);

	private:
		FieldParser_EstimatedAccelBias() {};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_EstimatedLLHPosUncertainty
	//	The field parser for Estimated LLH Position Uncertainty data
	//
	//See Also:
	//	<FieldParser_FilterStatus>
	class FieldParser_EstimatedLLHPosUncertainty : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	UNCERTAINTY_FLAG		- b00000001 - The flag position for checking the Uncertainty flag
		static const uint16 UNCERTAINTY_FLAG		= BOOST_BINARY(00000001);

	private:
		FieldParser_EstimatedLLHPosUncertainty(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_EstimatedNEDUncertainty
	//	The field parser for Estimated NED Velocity Uncertainty data
	//
	//See Also:
	//	<FieldParser_FilterStatus>
	class FieldParser_EstimatedNEDUncertainty : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	UNCERTAINTY_FLAG		- b00000001 - The flag position for checking the Uncertainty flag
		static const uint16 UNCERTAINTY_FLAG		= BOOST_BINARY(00000001);

	private:
		FieldParser_EstimatedNEDUncertainty(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_EstimatedAttEulerUncertainty
	//	The field parser for Estimated Attitude Euler Angles Uncertainty data
	//
	//See Also:
	//	<FieldParser_FilterStatus>
	class FieldParser_EstimatedAttEulerUncertainty : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	UNCERTAINTY_FLAG		- b00000001 - The flag position for checking the Uncertainty flag
		static const uint16 UNCERTAINTY_FLAG		= BOOST_BINARY(00000001);

	private:
		FieldParser_EstimatedAttEulerUncertainty(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_EstimatedGyroBiasUncertainty
	//	The field parser for Estimated Gyro Bias Uncertainty data
	//
	//See Also:
	//	<FieldParser_FilterStatus>
	class FieldParser_EstimatedGyroBiasUncertainty : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	UNCERTAINTY_FLAG		- b00000001 - The flag position for checking the Uncertainty flag
		static const uint16 UNCERTAINTY_FLAG		= BOOST_BINARY(00000001);

	private:
		FieldParser_EstimatedGyroBiasUncertainty(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_EstimatedAccelBiasUncertainty
	//	The field parser for Estimated Accel Bias Uncertainty data
	class FieldParser_EstimatedAccelBiasUncertainty : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	UNCERTAINTY_FLAG		- b00000001 - The flag position for checking the Uncertainty flag
		static const uint16 UNCERTAINTY_FLAG = BOOST_BINARY(00000001);

	private:
		FieldParser_EstimatedAccelBiasUncertainty() {};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_EstimatedLinearAccel
	//	The field parser for Estimated Linear Acceleration data
	//
	//See Also:
	//	<FieldParser_FilterStatus>
	class FieldParser_EstimatedLinearAccel : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	ACCEL_FLAG		- b00000001 - The flag position for checking the Linear Acceleration flag
		static const uint16 ACCEL_FLAG		= BOOST_BINARY(00000001);

	private:
		FieldParser_EstimatedLinearAccel(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_EstimatedAngularRate
	//	The field parser for Estimated Angular Rate data
	//
	//See Also:
	//	<FieldParser_FilterStatus>
	class FieldParser_EstimatedAngularRate : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	RATE_FLAG		- b00000001 - The flag position for checking the Angular Rate flag
		static const uint16 RATE_FLAG		= BOOST_BINARY(00000001);

	private:
		FieldParser_EstimatedAngularRate(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_WGS84LocalGravMagnitude
	//	The field parser for WGS84 Local Gravity Magnitude data
	//
	//See Also:
	//	<FieldParser_FilterStatus>
	class FieldParser_WGS84LocalGravMagnitude : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	GRAV_FLAG		- b00000001 - The flag position for checking the Gravity Magnitude flag
		static const uint16 GRAV_FLAG		= BOOST_BINARY(00000001);

	private:
		FieldParser_WGS84LocalGravMagnitude(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_EstimatedAttQuaternUncertainty
	//	The field parser for Estimated Attitude Uncertainty, Quaternion Elements data
	//
	//See Also:
	//	<FieldParser_FilterStatus>
	class FieldParser_EstimatedAttQuaternUncertainty : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	UNCERT_FLAG		- b00000001 - The flag position for checking the Uncertainty flag
		static const uint16 UNCERT_FLAG		= BOOST_BINARY(00000001);

	private:
		FieldParser_EstimatedAttQuaternUncertainty(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_EstimatedGravityVector
	//	The field parser for Estimated Gravity Vector data
	//
	//See Also:
	//	<FieldParser_FilterStatus>
	class FieldParser_EstimatedGravityVector : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	GRAV_FLAG		- b00000001 - The flag position for checking the Gravity Vector flag
		static const uint16 GRAV_FLAG		= BOOST_BINARY(00000001);

	private:
		FieldParser_EstimatedGravityVector(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_HeadingUpdateSource
	//	The field parser for Heading Update Source State data
	//
	//See Also:
	//	<FieldParser_FilterStatus>
	class FieldParser_HeadingUpdateSource : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	HEADING_FLAG		- b00000001 - The flag position for checking the Heading Flag
		static const uint16 HEADING_FLAG		= BOOST_BINARY(00000001);

	private:
		FieldParser_HeadingUpdateSource(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_MagneticModelSolution
	//	The field parser for Magnetic Model Solution data
	//
	//See Also:
	//	<FieldParser_FilterStatus>
	class FieldParser_MagneticModelSolution : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	SLN_FLAG		- b00000001 - The flag position for checking the Magnetic Model Solution Flag
		static const uint16 SLN_FLAG		= BOOST_BINARY(00000001);

	private:
		FieldParser_MagneticModelSolution(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_EstimatedGyroScaleFactor
	//	The field parser for Estimated Gyro Scale Factor data
	class FieldParser_EstimatedGyroScaleFactor : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	VALID_FLAG		- b00000001 - The flag position for checking the Estimated Gyro Scale Factor flag
		static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

	private:
		FieldParser_EstimatedGyroScaleFactor() {};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_EstimatedAccelScaleFactor
	//	The field parser for Estimated Accel Scale Factor data
	class FieldParser_EstimatedAccelScaleFactor : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	VALID_FLAG		- b00000001 - The flag position for checking the Estimated Gyro Scale Factor flag
		static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

	private:
		FieldParser_EstimatedAccelScaleFactor() {};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_EstimatedGyroScaleFactorUncertainty
	//	The field parser for Estimated Gyro Scale Factor Uncertainty data
	class FieldParser_EstimatedGyroScaleFactorUncertainty : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	VALID_FLAG		- b00000001 - The flag position for checking the Estimated Gyro Scale Factor flag
		static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

	private:
		FieldParser_EstimatedGyroScaleFactorUncertainty() {};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_EstimatedAccelScaleFactorUncertainty
	//	The field parser for Estimated Accel Scale Factor Uncertainty data
	class FieldParser_EstimatedAccelScaleFactorUncertainty : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	VALID_FLAG		- b00000001 - The flag position for checking the Estimated Gyro Scale Factor flag
		static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

	private:
		FieldParser_EstimatedAccelScaleFactorUncertainty() {};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_CompensatedAccel
	//	The field parser for Compensated Acceleration data
	class FieldParser_CompensatedAccel : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	VALID_FLAG		- b00000001 - The flag position for checking the Estimated Gyro Scale Factor flag
		static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

	private:
		FieldParser_CompensatedAccel() {};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_StdAtmModel
	//	The field parser for Standard Atmosphere Model data
	class FieldParser_StdAtmModel : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	VALID_FLAG		- b00000001 - The flag position for checking the Estimated Gyro Scale Factor flag
		static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

	private:
		FieldParser_StdAtmModel() {};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_PressureAlt
	//	The field parser for Pressure Altitude data
	class FieldParser_PressureAlt : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	VALID_FLAG		- b00000001 - The flag position for checking the Estimated Gyro Scale Factor flag
		static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

	private:
		FieldParser_PressureAlt() {};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_GpsAntennaOffsetCorrection
	//	The field parser for GPS Antenna Offset Correction data
	class FieldParser_GpsAntennaOffsetCorrection : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	VALID_FLAG		- b00000001 - The flag position for checking the Estimated Gyro Scale Factor flag
		static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

	private:
		FieldParser_GpsAntennaOffsetCorrection() {};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_GpsAntennaOffsetCorrectionUncert
	//	The field parser for GPS Antenna Offset Correction Uncertainty data
	class FieldParser_GpsAntennaOffsetCorrectionUncert : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	VALID_FLAG		- b00000001 - The flag position for checking the Estimated Gyro Scale Factor flag
		static const uint16 VALID_FLAG = BOOST_BINARY(00000001);

	private:
		FieldParser_GpsAntennaOffsetCorrectionUncert() {};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};
}