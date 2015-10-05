/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "FatigueOptions.h"
#include <math.h>

namespace mscl
{
	SnCurveSegment::SnCurveSegment():
		m_m(1.0),
		m_loga(0.0)
	{
	}

	SnCurveSegment::SnCurveSegment(float m, float loga):
		m_m(m),
		m_loga(loga)
	{
	}

	float SnCurveSegment::m() const
	{
		return m_m;
	}

	void SnCurveSegment::m(float val)
	{
		m_m = val;
	}

	float SnCurveSegment::logA() const
	{
		return m_loga;
	}

	void SnCurveSegment::logA(float val)
	{
		m_loga = val;
	}


	FatigueOptions::FatigueOptions():
		m_youngsModulus(0.2025f),
		m_poissonsRatio(0.3f),
		m_peakValleyThreshold(0),
		m_rawMode(false)
	{
	}

	float FatigueOptions::youngsModulus() const
	{
		return m_youngsModulus;
	}

	void FatigueOptions::youngsModulus(float val)
	{
		m_youngsModulus = val;
	}

	float FatigueOptions::poissonsRatio() const
	{
		return m_poissonsRatio;
	}

	void FatigueOptions::poissonsRatio(float val)
	{
		m_poissonsRatio = val;
	}

	uint16 FatigueOptions::peakValleyThreshold() const
	{
		return m_peakValleyThreshold;
	}

	void FatigueOptions::peakValleyThreshold(uint16 val)
	{
		m_peakValleyThreshold = val;
	}

	bool FatigueOptions::rawMode() const
	{
		return m_rawMode;
	}

	void FatigueOptions::rawMode(bool enable)
	{
		m_rawMode = enable;
	}

	float FatigueOptions::damageAngle(uint8 angleId) const
	{
		try
		{
			return m_damageAngles.at(angleId);
		}
		catch(std::out_of_range&)
		{
			throw Error_NoData("No damage angle exists for the given angleId.");
		}
	}

	const DamageAngles& FatigueOptions::damageAngles() const
	{
		return m_damageAngles;
	}

	void FatigueOptions::damageAngle(uint8 angleId, float angle)
	{
		//convert the angle to within 0 - 360
		float angleToSet = fmod(angle, 360.0f);
		if(angleToSet < 0.0f)
		{
			angleToSet += 360.0f;
		}

		m_damageAngles[angleId] = angleToSet;
	}

	const SnCurveSegment& FatigueOptions::snCurveSegment(uint8 segmentId) const
	{
		try
		{
			return m_snCurveSegments.at(segmentId);
		}
		catch(std::out_of_range&)
		{
			throw Error_NoData("No SnCurveSegment exists for the given segmentId.");
		}
	}

	const SnCurveSegments& FatigueOptions::snCurveSegments() const
	{
		return m_snCurveSegments;
	}

	void FatigueOptions::snCurveSegment(uint8 segmentId, const SnCurveSegment& segment)
	{
		m_snCurveSegments[segmentId] = segment;
	}
}