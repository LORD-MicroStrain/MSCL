/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Vector.h"

namespace mscl
{
    class Rotation;

    //API Class: EulerAngles
    //    Represents generic Euler Angles (roll, pitch, yaw).
    class EulerAngles : public Vector
    {
    public:
        EulerAngles();

        //API Constructor: EulerAngles
        //    Creates an EulerAngles object.
        EulerAngles(float roll, float pitch, float yaw);

        //API Constructor: EulerAngles
        //  Creates a EulerAngles object based on specified <MipFieldValues> data
        //
        //Parameters:
        //  <MipFieldValues> - format must be 3 floats
        EulerAngles(const MipFieldValues& data, uint8 offset = 0);

#ifndef SWIG
        operator Rotation() const;
#endif //SWIG
        
    public:
        //API Function: asMipFieldValues
        //  Gets the current quaternion values formatted as a <MipFieldValues> object
        MipFieldValues asMipFieldValues() const;

        void appendMipFieldValues(MipFieldValues& appendTo) const;

    public:
        //API Function: roll
        //    Gets the roll angle.
        //
        //Returns:
        //    The roll Euler Angle.
        float roll() const;

        //API Function: pitch
        //    Gets the pitch angle.
        //
        //Returns:
        //    The pitch Euler Angle.
        float pitch() const;

        //API Function: yaw
        //    Gets the yaw (heading) angle.
        //
        //Returns:
        //    The yaw (heading) Euler Angle.
        float yaw() const;

        //API Function: heading
        //    Gets the heading (yaw) angle.
        //
        //Returns:
        //    The heading (yaw) Euler Angle.
        float heading() const;
    };

    //API Class: Quaternion
    //    Represents generic Quaternion (x, y, z, w).
    class Quaternion : public Vector
    {
    public:
        Quaternion();

        //API Constructor: Quaternion
        //    Creates an Quaternion object.
        Quaternion(float x, float y, float z, float w);

        //API Constructor: Quaternion
        //  Creates a Quaternion object based on specified <MipFieldValues> data
        //
        //Parameters:
        //  <MipFieldValues> - format must be 4 floats
        Quaternion(const MipFieldValues& data, uint8 offset = 0);

#ifndef SWIG
        operator Rotation() const;
#endif //SWIG
        
    public:
        //API Function: asMipFieldValues
        //  Gets the current quaternion values formatted as a <MipFieldValues> object
        MipFieldValues asMipFieldValues() const;

        void appendMipFieldValues(MipFieldValues& appendTo) const;
        
        //API Function: normalize
        // normalize the quaternion value
        void normalize();

    public:
        //API Function: x
        //    Gets the x value.
        //
        //Returns:
        //    The x value.
        float x() const;

        //API Function: y
        //    Gets the y value.
        //
        //Returns:
        //    The y value.
        float y() const;

        //API Function: z
        //    Gets the z value.
        //
        //Returns:
        //    The z value.
        float z() const;

        //API Function: w
        //    Gets the w value.
        //
        //Returns:
        //    The w value.
        float w() const;

    private:
        void set(uint8 index, float val);
    };

    class Rotation : public Vector
    {
    public:
        enum Format
        {
            EULER_ANGLES = 1,
            QUATERNION = 2
        };

    public:

        Rotation() : Rotation(EulerAngles(0, 0, 0)) {}
        Rotation(const EulerAngles& angles);
        Rotation(const Quaternion& quat);

        //API Constructor: Rotation
        //  Creates a Rotation object based on specified <MipFieldValues> data
        //
        //Parameters:
        //  <MipFieldValues> - format must be a u8 format id and 3 or 4 floats
        Rotation(const MipFieldValues& data, uint8 offset = 0);

    public:
        static Rotation FromEulerAngles(const EulerAngles& angles) { return Rotation(angles); }
        static Rotation FromQuaternion(const Quaternion& quat) { return Rotation(quat); }

#ifndef SWIG
        operator EulerAngles() const;
        operator Quaternion() const;
#endif //SWIG

    public:
        EulerAngles asEulerAngles() const;
        Quaternion asQuaternion() const;

        //API Function: asMipFieldValues
        //  Gets the current quaternion values formatted as a <MipFieldValues> object
        MipFieldValues asMipFieldValues(bool includeFormat = true) const;

        void appendMipFieldValues(MipFieldValues& appendTo, bool includeFormat = true) const;

    private:
        Format m_format;
        
    public:
        Format format() const { return m_format; }
    };
}