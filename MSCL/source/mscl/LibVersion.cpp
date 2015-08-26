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
#include "stdafx.h"
#include "LibVersion.h"
#include <set>
#include <sstream>

namespace mscl
{
	uint32 LibVersion::major()
	{
		return static_cast<uint32>(MSCL_MAJOR);
	}

	uint32 LibVersion::minor()
	{
		return static_cast<uint32>(MSCL_MINOR);
	}

	uint32 LibVersion::patch()
	{
		return static_cast<uint32>(MSCL_PATCH);
	}

	std::string LibVersion::asString()
	{
		static std::string version("");

		//if the static version hasn't been created yet
		if(version.empty())
		{
			//create a string from the major, minor, and patch
			std::ostringstream ss;
			ss << MSCL_MAJOR << "." << MSCL_MINOR << "." << MSCL_PATCH;
			version = ss.str();
		}

		return version;
	}
}