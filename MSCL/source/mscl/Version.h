/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include <string>
#include "Types.h"

namespace mscl
{

//API Class: Version
//    Class that represents, and provides helper functions for, a Version number
class Version
{
public:
    //API Default Constructor: Version
    //    Creates a Version object with 0.0 as a version
    Version();

    //API Constructor: Version
    //    Create a Version object from major, minor, patch.
    //
    //Parameters:
    //    major - The major part of the version (ie. 1 in 1.23.97).
    //    minor - The minor part of the version (ie. 23 in 1.23.97).
    //    patch - The patch part of the version (ie. 97 in 1.23.97).
    Version(uint32 major, uint32 minor, uint32 patch);

    //API Constructor: Version
    //    Create a Version object from major and minor.
    //
    //Parameters:
    //    major - The major part of the version (ie. 1 in 1.23.97).
    //    minor - The minor part of the version (ie. 23 in 1.23.97).
    Version(uint32 major, uint32 minor);

    //API Constructor: Version
    //    The copy constructor for a Version object.
    //
    //Parameters:
    //    other - The Version to be copied.
    Version(const Version& other);

private:
    //Variable: m_major
    //    The major part of the Version.
    uint32 m_major;

    //Variable: m_minor
    //    The minor part of the Version.
    uint32 m_minor;

    //Variable: m_patch
    //    The patch part of the Version.
    uint32 m_patch;

public:
    //========================================================================
    //API Operators
    //    ==    - checks if two versions are equal to one another
    //    !=    - checks if two versions are not equal to one another
    //    <    - checks if a version is less than another
    //    <=    - checks if a version is less than or equal to another
    //    >    - checks if a version is greater than another
    //    >=    - checks if a version is greater than or equal to another
    //========================================================================
    bool operator==(const Version& cmp) const {return compare(cmp) == 0;}
    bool operator!=(const Version& cmp) const {return compare(cmp) != 0;}
    bool operator< (const Version& cmp) const {return compare(cmp) <  0;}
    bool operator<=(const Version& cmp) const {return compare(cmp) <= 0;}
    bool operator> (const Version& cmp) const {return compare(cmp) >  0;}
    bool operator>=(const Version& cmp) const {return compare(cmp) >= 0;}

    //API Function: str
    //    Gets a string representation of the Version.
    //
    //Returns:
    //    A string representing the Version.
    std::string str() const;

    //API Function: fromString
    //    Builds the Version object from the given string.
    //    If successful, the Version object will be updated to the given string.
    //
    //Parameters:
    //    strVersion - The string representation of a version (ie. "1.23")
    //
    //Returns:
    //    true if the string was parsed successfully and the Version was updated, false if the string failed to parse
    bool fromString(const std::string& strVersion);

    //API Function: majorPart
    //    Gets the major part of the Version
    //
    //Returns:
    //    The major part of the Version (ie. 1 in 1.23.97)
    uint32 majorPart() const;

    //API Function: minorPart
    //    Gets the minor part of the Version
    //
    //Returns:
    //    The minor part of the Version (ie. 23 in 1.23.97)
    uint32 minorPart() const;

    //API Function: patchPart
    //    Gets the patch part of the Version
    //
    //Returns:
    //    The patch part of the Version (ie. 97 in 1.23.97)
    uint32 patchPart() const;

private:
    //Function: compare
    //    Compares the current Version to the given Version parameter
    //
    //Parameters:
    //    cmp - The Version to compare to the current Version
    //
    //Returns:
    //    0 if the 2 versions are equal, a negative number if the current Version is less than the parameter Version, a positive number if the current Version is greater than the parameter Version.
    int compare(const Version& cmp) const;
};

}