/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "Version.h"

#include <iomanip>
#include <sstream>

namespace mscl
{

Version::Version():
    m_major(0),
    m_minor(0),
    m_patch(0)
{
}

Version::Version(uint32 major, uint32 minor, uint32 patch):
    m_major(major),
    m_minor(minor),
    m_patch(patch)
{
}

Version::Version(uint32 major, uint32 minor):
    m_major(major),
    m_minor(minor),
    m_patch(0)
{
}

Version::Version(const Version& other):
    m_major(other.m_major),
    m_minor(other.m_minor),
    m_patch(other.m_patch)
{
}

std::string Version::str() const
{
    //build the Version into a stringstream with the correct formatting
    std::stringstream s;
    s << m_major << "." << m_minor << "." << m_patch;

    //return the string result
    return s.str();
}

bool Version::fromString(const std::string& strVersion)
{
    size_t majorMinorDec = strVersion.find_first_of('.');
    size_t minorPatchDec = strVersion.find_last_of('.');
    size_t end = (strVersion.size() - 1);

    size_t minorCharsToRead = 0;

    //if there is no "patch" part in the string
    if(minorPatchDec == majorMinorDec)
    {
        //read from the major/minor decimal to the end
        minorCharsToRead = end - majorMinorDec;
    }
    else
    {
        //read from the major/minor period to the minor/patch decimal
        minorCharsToRead = minorPatchDec - majorMinorDec;
    }

    

    if(majorMinorDec > 0 && majorMinorDec < end)
    {
        //major version
        {
            std::stringstream s(strVersion.substr(0, majorMinorDec));
            s >> m_major;
        }

        //minor
        {
            std::stringstream s(strVersion.substr(majorMinorDec + 1, minorCharsToRead));
            s >> m_minor;
        }

        //patch
        if((minorPatchDec > 0) && (minorPatchDec < end) && (minorPatchDec > majorMinorDec))
        {
            std::stringstream s(strVersion.substr(minorPatchDec + 1));
            s >> m_patch;
        }

        return true;
    }

    return false;
}

uint32 Version::majorPart() const
{
    return m_major;
}

uint32 Version::minorPart() const
{
    return m_minor;
}

uint32 Version::patchPart() const
{
    return m_patch;
}

int Version::compare(const Version& cmp) const
{
    //get the difference between the major values of the Versions
    int difference = static_cast<int>(m_major) - static_cast<int>(cmp.m_major);

    //if there is no difference between the major versions
    if(difference == 0)
    {
        //get the difference between the minor values of the Versions
        difference = m_minor - cmp.m_minor;

        //if there is no difference between the minor versions
        if(difference == 0)
        {
            //get the difference between the patch values of the Versions
            difference = m_patch - cmp.m_patch;
        }
    }

    //return the difference 
    return difference;
}

}