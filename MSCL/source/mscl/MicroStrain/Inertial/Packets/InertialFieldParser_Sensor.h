/*****************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the included
LICENSE.txt file for a copy of the full GNU General Public License.
*****************************************************************************/
#pragma once

#include <boost/utility/binary.hpp>

#include "InertialFieldParser.h"
#include "InertialDataPacket.h"

namespace mscl
{
	//Title: InertialFieldParser_Sensor

	class InertialDataField;

	//Class: FieldParser_RawAccelVector
	//	The Field Parser for raw accelerometer data
	class FieldParser_RawAccelVector : public InertialFieldParser
	{
	private:
		FieldParser_RawAccelVector(){};	//default constructor disabled

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

	//Class: FieldParser_RawGyroVector
	//	The field parser for raw gyro data
	//
	//See Also:
	//	<FieldParser_RawAccelVector>
	class FieldParser_RawGyroVector : public InertialFieldParser
	{
	private:
		FieldParser_RawGyroVector(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_RawMagVector
	//	The field parser for raw magnetometer data
	//
	//See Also:
	//	<FieldParser_RawAccelVector>
	class FieldParser_RawMagVector : public InertialFieldParser
	{
	private:
		FieldParser_RawMagVector(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_ScaledAccelVector
	//	The field parser for scaled accelerometer data
	//
	//See Also:
	//	<FieldParser_RawAccelVector>
	class FieldParser_ScaledAccelVector : public InertialFieldParser
	{
	private:
		FieldParser_ScaledAccelVector(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_ScaledGyroVector
	//	The field parser for scaled gyro data
	//
	//See Also:
	//	<FieldParser_RawAccelVector>
	class FieldParser_ScaledGyroVector : public InertialFieldParser
	{
	private:
		FieldParser_ScaledGyroVector(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_ScaledMagVector
	//	The field parser for scaled magnetometer data
	//
	//See Also:
	//	<FieldParser_RawAccelVector>
	class FieldParser_ScaledMagVector : public InertialFieldParser
	{
	private:
		FieldParser_ScaledMagVector(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_DeltaThetaVector
	//	The field parser for delta theta data
	//
	//See Also:
	//	<FieldParser_RawAccelVector>
	class FieldParser_DeltaThetaVector : public InertialFieldParser
	{
	private:
		FieldParser_DeltaThetaVector(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_DeltaVelocityVector
	//	The field parser for delta velocity data
	//
	//See Also:
	//	<FieldParser_RawAccelVector>
	class FieldParser_DeltaVelocityVector : public InertialFieldParser
	{
	private:
		FieldParser_DeltaVelocityVector(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_OrientationMatrix
	//	The field parser for orientation matrix data
	//
	//See Also:
	//	<FieldParser_RawAccelVector>
	class FieldParser_OrientationMatrix : public InertialFieldParser
	{
	private:
		FieldParser_OrientationMatrix(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_Quaternion
	//	The field parser for quaternion data
	//
	//See Also:
	//	<FieldParser_RawAccelVector>
	class FieldParser_Quaternion : public InertialFieldParser
	{
	private:
		FieldParser_Quaternion(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_OrientationUpdateMatrix
	//	The field parser for orientation matrix data
	//
	//See Also:
	//	<FieldParser_RawAccelVector>
	class FieldParser_OrientationUpdateMatrix : public InertialFieldParser
	{
	private:
		FieldParser_OrientationUpdateMatrix(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_EulerAngles
	//	The field parser for Euler Angles data
	//
	//See Also:
	//	<FieldParser_RawAccelVector>
	class FieldParser_EulerAngles : public InertialFieldParser
	{
	private:
		FieldParser_EulerAngles(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_InternalTimestamp
	//	The field parser for Internal Timestamp data
	//
	//See Also:
	//	<FieldParser_RawAccelVector>
	class FieldParser_InternalTimestamp : public InertialFieldParser
	{
	private:
		FieldParser_InternalTimestamp(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_BeaconedTimestamp
	//	The field parser for Beaconed Timestamp data
	//
	//See Also:
	//	<FieldParser_RawAccelVector>
	class FieldParser_BeaconedTimestamp : public InertialFieldParser
	{
	private:
		FieldParser_BeaconedTimestamp(){};		//default constructor disabled

		//Constants: Valid Flags
		//	TIMESTAMP_FLAG		- b0001 - The flag position for checking the Timestamp status
		static const uint8 TIMESTAMP_FLAG = BOOST_BINARY(0001);

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_StabilizedMagVector
	//	The field parser for Stabilized Mag Vector (North)
	//
	//See Also:
	//	<FieldParser_RawAccelVector>
	class FieldParser_StabilizedMagVector : public InertialFieldParser
	{
	private:
		FieldParser_StabilizedMagVector(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_StabilizedAccelVector
	//	The field parser for Stabilized Accel Vector (Up)
	//
	//See Also:
	//	<FieldParser_RawAccelVector>
	class FieldParser_StabilizedAccelVector : public InertialFieldParser
	{
	private:
		FieldParser_StabilizedAccelVector(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_GpsCorrelationTimestamp
	//	The field parser for GPS Correlation Timestamp
	//
	//See Also:
	//	<FieldParser_RawAccelVector>
	class FieldParser_GpsCorrelationTimestamp : public InertialFieldParser
	{
	private:
		//Constants: Valid Flags
		//	TS_FLAG	- b00000001	- The flag position for checking the Timestamp Valid flag
		static const uint16 TS_FLAG = BOOST_BINARY(00000100);

		FieldParser_GpsCorrelationTimestamp(){};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};

	//Class: FieldParser_ScaledAmbientPressure
	//	The field parser for Scaled Ambient Pressure.
	class FieldParser_ScaledAmbientPressure : public InertialFieldParser
	{
	private:
		FieldParser_ScaledAmbientPressure() {};		//default constructor disabled

	public:
		virtual void parse(const InertialDataField& field, InertialDataPoints& result) const override;
		static bool registerParser();

	public:
		static const InertialTypes::ChannelField FIELD_TYPE;
		static const bool REGISTERED;
	};
}