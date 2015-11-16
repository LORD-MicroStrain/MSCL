/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
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