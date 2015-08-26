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
//PUBLIC_HEADER
#pragma once

#include <map>
#include "mscl/Types.h"

namespace mscl
{
	//API Title: FatigueOptions

	//API Class: SnCurveSegment
	//	Represents a single segment of an SN-Curve.
	class SnCurveSegment
	{
	public:
		//API Default Constructor: SnCurveSegment
		//	Creates a default constructed SnCurveSegment.
		SnCurveSegment();
		
		//API Constructor: SnCurveSegment
		//	Creates an SnCurveSegment.
		//
		//Parameters:
		//	m - The m value of the segment.
		//	loga - The logA value of the segment.
		SnCurveSegment(float m, float loga);

	private:
		//Variable: m_m
		//	The m value of the segment.
		float m_m;

		//Variable: m_loga
		//	The logA value of the segment.
		float m_loga;

	public:
		//API Function: m
		//	Gets the m value of the segment.
		float m() const;

		//API Function: m
		//	Sets the m value of the segment.
		//
		//Parameters:
		//	val - The m value to set.
		void m(float val);

		//API Function: logA
		//	Gets the logA value of the segment.
		float logA() const;

		//API Function: logA
		//	Sets the logA value of the segment.
		//
		//Parameters:
		//	val - The logA value to set.
		void logA(float val);
	};

	//API Typedef: DamageAngles
	//	Typedef for a map of angle IDs (uint8) to damage angles (float).
	typedef std::map<uint8, float> DamageAngles;

	//API Typedef: SnCurveSegments
	//	Typedef for a map of segment IDs (uint8) to <SnCurveSegment> objects.
	typedef std::map<uint8, SnCurveSegment> SnCurveSegments;

	//API Class: FatigueOptions
	//	Contains all of the fatigue options that can be configured for a WirelessNode.
	class FatigueOptions
	{
	public:
		//API Default Constructor: FatigueOptions
		//	Creates a default constructed FatigueOptions object.
		FatigueOptions();

	private:
		//Variable: m_youngsModulus
		//	The Young's Modulus value.
		float m_youngsModulus;

		//Variable: m_poissonsRatio
		//	The Poisson's Ratio value.
		float m_poissonsRatio;

		//Variable: m_peakValleyThreshold
		//	The peak/valley threshold.
		uint16 m_peakValleyThreshold;

		//Variable: m_rawMode
		//	Whether raw data is enabled or disabled.
		bool m_rawMode;

		//Variable: m_damageAngles
		//	The <DamageAngles>.
		DamageAngles m_damageAngles;

		//Variable: m_snCurveSegments
		//	The <SnCurveSegments>.
		SnCurveSegments m_snCurveSegments;

	public:
		//API Function: youngsModulus
		//	Gets the Young's Modulus set in this options object.
		float youngsModulus() const;

		//API Function: youngsModulus
		//	Sets the Young's Modulus in this options object.
		//
		//Parameters:
		//	val - The Young's Modulus to set.
		void youngsModulus(float val);

		//API Function: poissonsRatio
		//	Gets the Poisson's Ration set in this options object.
		float poissonsRatio() const;

		//API Function: poissonsRatio
		//	Sets the Poisson's Ratio in this options object.
		//
		//Parameters:
		//	val - The Poisson's Ratio to set.
		void poissonsRatio(float val);

		//API Function: peakValleyThreshold
		//	Gets the Peak/Valley Threshold set in this options object.
		uint16 peakValleyThreshold() const;

		//API Function: peakValleyThreshold
		//	Sets the Peak/Valley Threshold in this options object.
		//
		//Parameters:
		//	val - The Peak/Valley Threshold to set.
		void peakValleyThreshold(uint16 val);

		//API Function: rawMode
		//	Gets the raw mode flag set in this options object.
		//	This determines whether raw data that builds the Histograms will be sent when sampling.
		bool rawMode() const;
		
		//API Function: rawMode
		//	Sets the raw mode flag in this options object.
		//
		//Parameters:
		//	enable - Whether to enable (true) or disable (false) raw mode.
		void rawMode(bool enable);

		//API Function: damageAngle
		//	Gets the damage angle set in this options object, for the given angle id (0-based).
		//
		//Parameters:
		//	angleId - The angle ID to get the damage angle for.
		//
		//Exceptions:
		//	<Error_NoData> - The given angle ID was not set in this object.
		float damageAngle(uint8 angleId) const;

		//API Function: damageAngles
		//	Gets the <DamageAngles> container set in this options object.
		const DamageAngles& damageAngles() const;

		//API Function: damageAngle
		//	Sets the damage angle in this options object, for the given angle id (0-based).
		//	The angle will be automatically converted to between 0 and 360 if it is out of range.
		//
		//Parameters:
		//	angleId - The angle ID to set the damage angle for.
		//	angle - The damage angle value to set.
		void damageAngle(uint8 angleId, float angle);

		//API Function: snCurveSegment
		//	Gets the <SnCurveSegment> set in this options object, for the given segment id (0-based).
		//
		//Parameters:
		//	segmentId - The segment ID to get the segment for.
		//
		//Exceptions:
		//	<Error_NoData> - The given segment ID was not set in this object.
		const SnCurveSegment& snCurveSegment(uint8 segmentId) const;

		//API Function: snCurveSegments
		//	Gets the <SnCurveSegments> container set in this options object.
		const SnCurveSegments& snCurveSegments() const;

		//API Function: snCurveSegment
		//	Sets the <SnCurveSegment> in this options object, for the given segment id (0-based).
		//
		//Parameters:
		//	segmentId - The segment ID to set the segment for.
		//	segment - The <SnCurveSegment> to set.
		void snCurveSegment(uint8 segmentId, const SnCurveSegment& segment);
	};
}