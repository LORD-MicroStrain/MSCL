/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "Version.h"

#ifndef SWIG
//update with each release
#define MSCL_MAJOR 48
#define MSCL_MINOR 2
#define MSCL_PATCH 3
#endif

namespace mscl
{
    //API Variable: MSCL_VERSION
    //  Gets the <Version> of MSCL.
    static const Version MSCL_VERSION = Version(MSCL_MAJOR, MSCL_MINOR, MSCL_PATCH);
}