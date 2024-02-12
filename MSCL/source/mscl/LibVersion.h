/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#pragma once

#include "Version.h"

#ifndef SWIG
//update with each release
#define MSCL_MAJOR 65
#define MSCL_MINOR 0
#define MSCL_PATCH 0
#endif

namespace mscl
{
    //API Variable: MSCL_VERSION
    //  Gets the <Version> of MSCL.
    static const Version MSCL_VERSION = Version(MSCL_MAJOR, MSCL_MINOR, MSCL_PATCH);
}