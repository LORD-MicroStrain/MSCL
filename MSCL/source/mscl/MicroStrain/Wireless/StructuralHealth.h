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

#include "mscl/Histogram.h"
#include "mscl/MicroStrain/SampleRate.h"

namespace mscl
{
	//API Class: StructuralHealth
	//	Holds Structural Health Monitor channel information.
	class StructuralHealth
	{
	public:
		//API Constructor: StructuralHealth
		//	Creates a StructuralHealth object.
		//
		//Parameters:
		//	angle - The actual angle that is being measured.
		//	uptime - The uptime counter of how long the device has been running.
		//	damage - The percent of damage that has occurred. (0% = no damage, 100% = dead)
		//	processingRate - The processing rate used in calculating the Histogram.
		//	histogram - The <Histogram> that was calculated for the given angle.
		StructuralHealth(float angle, uint32 uptime, float damage, const SampleRate& processingRate, const Histogram& histogram);

	private:
		//Variable: m_angle
		//	The actual angle that is being measured.
		float m_angle;

		//Variable: m_uptime
		//	The uptime counter of how long the device has been running.
		uint32 m_uptime;

		//Variable: m_damage
		//	The percent of damage that has occurred. (0% = no damage, 100% = dead)
		float m_damage;

		//Variable: m_processingRate
		//	The processing rate that the sensors were sampled at to calculate the histogram.
		SampleRate m_processingRate;

		//Variable: m_histogram
		//	The <Histogram> that was calculated for the given angle.
		Histogram m_histogram;

	public:
		//API Function: angle
		//	Gets the actual angle that is being measured.
		//
		//Returns:
		//	The actual angle that is being measured.
		float angle() const;

		//API Function: uptime
		//	Gets the uptime counter of how long the device has been running.
		//
		//Returns:
		//	The uptime counter of how long the device has been running.
		uint32 uptime() const;

		//API Function: damage
		//	Gets the percent of damage that has occurred. (0% = no damage, 100% = dead)
		//
		//Returns:
		//	The percent of damage that has occured. (0% = no damage, 100% = dead)
		float damage() const;

		//API Function: processingRate
		//	Gets the processing rate that the sensors were sampled at to calculate the histogram.
		//
		//Returns:
		//	The processing rate as a <SampleRate>.
		const SampleRate& processingRate() const;

		//API Function: histogram
		//	Gets the <Histogram> that was calculated for the given angle.
		//
		//Returns:
		//	The <Histogram> that was calculated for the given angle.
		const Histogram& histogram() const;
	};
}