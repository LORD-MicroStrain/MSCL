/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/Version.h"

namespace mscl
{
    Version::Version() :
        m_major(0),
        m_minor(0),
        m_patch(0)
    {}

    Version::Version(uint32 major, uint32 minor, uint32 patch) :
        m_major(major),
        m_minor(minor),
        m_patch(patch)
    {}

    Version::Version(uint32 major, uint32 minor) :
        m_major(major),
        m_minor(minor),
        m_patch(0)
    {}

    Version::Version(const Version& other) :
        m_major(other.m_major),
        m_minor(other.m_minor),
        m_patch(other.m_patch)
    {}

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
        // Pattern to extract only numbers Major.Minor.Patch. Anything else before or after is ignored
        const std::regex pattern(R"((\d+)\.?(\d+)?\.?(\d+)?)");

        std::smatch match;

        // Pattern will always find a Major number if it exists
        if (std::regex_search(strVersion, match, pattern))
        {
            m_major = std::stoi(match[1]);

            // Minor is optionally found
            m_minor = match[2].matched ? std::stoi(match[2]) : 0;

            // Patch is optionally found
            m_patch = match[3].matched ? std::stoi(match[3]) : 0;

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
} // namespace mscl
