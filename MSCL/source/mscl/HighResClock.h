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

#include "Types.h"

namespace mscl
{

//Class: HighResClock
//	Helper class used to obtain the current system time from as high-resolution of a clock as possible.
class HighResClock
{
private:
	//Variable: m_startHighResNanos
	//	The nanoseconds since epoch for the high-resolution clock.
	uint64 m_startHighResNanos;

	//Variable: m_startSysTimeNanos
	//	The nanoseconds since epoch for the system clock.
	uint64 m_startSysTimeNanos;

public:
	//Default Constructor: HighResClock
	//	Creates a HighResClock object, which sets the start clock times.
	HighResClock();

	//Function: getCurrentSystemTime
	//	Gets the number of nanoseconds since Unix Epoch, using a high-resolution clock.
	uint64 getCurrentSystemTime() const;
};

}