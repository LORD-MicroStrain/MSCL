/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
//PUBLIC_HEADER
#pragma once

#include <string>
#include "Types.h"

#ifndef SWIG
//update with each release
#define MSCL_MAJOR 1
#define MSCL_MINOR 20
#define MSCL_PATCH 1
#endif

namespace mscl
{
	//API Class: LibVersion
	//	Contains functions to obtain information on the current version of the MSCL Library
	class LibVersion
	{
	public:
		//API Function: major
		//	Gets the major version of MSCL.
		//
		//Returns:
		//	The major version of MSCL.
		static uint32 major();

		//API Function: minor
		//	Gets the minor version of MSCL.
		//
		//Returns:
		//	The minor version of MSCL.
		static uint32 minor();

		//API Function: patch
		//	Gets the patch version of MSCL.
		//
		//Returns:
		//	The patch version of MSCL.
		static uint32 patch();

		//API Function: asString
		//	Gets the MSCL version as a string.
		//
		//Returns:
		//	The MSCL version as a string.
		static std::string asString();
	};
}