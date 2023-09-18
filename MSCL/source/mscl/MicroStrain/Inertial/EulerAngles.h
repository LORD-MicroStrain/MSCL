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
        //API Constructor: EulerAngles
        //    Creates an EulerAngles object.
        EulerAngles();

        //API Constructor: EulerAngles
        //    Creates an EulerAngles object with the specified roll, pitch, and yaw/heading.
        EulerAngles(float roll, float pitch, float yaw);

        //API Constructor: EulerAngles
        //  Creates a EulerAngles object based on specified <MipFieldValues> data
        //
        //Parameters:
        //  <MipFieldValues> - format must be 3 floats
        //  offset - default: 0 - uint8 index offset to start reading from
        EulerAngles(const MipFieldValues& data, uint8 offset = 0);

#ifndef SWIG
        //API Function: operator Rotation() (cast)
        //    Creates a <Rotation> object with this object's roll, pitch, and yaw values
        operator Rotation() const;
#endif //SWIG
        
    public:
        //API Function: asMipFieldValues
        //  Gets the current euler angles values formatted as a <MipFieldValues> object.
        //
        //Returns:
        //  <MipFieldValues> - collection of values that represents this object.
        MipFieldValues asMipFieldValues() const;

        //API Function: appendMipFieldValues
        //  Adds the properly formatted <MipFieldValues> that represent this object to the specified collection.
        //
        //Parameters:
        //  appendTo - (reference) the <MipFieldValues> collection to append to
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
        //  offset - default: 0 - uint8 index offset to start reading from
        Quaternion(const MipFieldValues& data, uint8 offset = 0);

#ifndef SWIG
        //API Function: operator Rotation() (cast)
        //    Creates a <Rotation> object with this object's x, y, z, w values
        operator Rotation() const;
#endif //SWIG
        
    public:
        //API Function: asMipFieldValues
        //  Gets the current quaternion values formatted as a <MipFieldValues> object
        //
        //Returns:
        //  <MipFieldValues> - collection of values that represents this object.
        MipFieldValues asMipFieldValues() const;

        //API Function: appendMipFieldValues
        //  Adds the properly formatted <MipFieldValues> that represent this object to the specified collection.
        //
        //Parameters:
        //  appendTo - (reference) the <MipFieldValues> collection to append to
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

    //API Class: Rotation
    //  Structure that can represent either a <Quaternion> or <EulerAngles> object.
    class Rotation : public Vector
    {
    public:
        //API Enum: Format
        //  Possible formats for the Rotation object.
        //
        //  EULER_ANGLES    - 1 - EulerAngles format
        //  QUATERINION     - 2 - Quaternion format
        enum Format
        {
            EULER_ANGLES = 1,
            QUATERNION = 2
        };

    public:

        //API Constructor: Rotation
        //  Constructs a Rotation object with default values.
        Rotation() : Rotation(EulerAngles(0, 0, 0)) {}

        //API Constructor: Rotation
        //  Constructs a Rotation object based on the specified <EulerAngles>.
        //
        //Parameters:
        //  angles - <EulerAngles> object to populate rotation values from
        Rotation(const EulerAngles& angles);

        //API Constructor: Rotation
        //  Constructs a Rotation object based on the specified <Quaternion>.
        //
        //Parameters:
        //  quat - <Quaternion> object to populate rotation values from
        Rotation(const Quaternion& quat);

        //API Constructor: Rotation
        //  Creates a Rotation object based on specified <MipFieldValues> data
        //
        //Parameters:
        //  <MipFieldValues> - format must be a u8 format id and 3 or 4 floats
        //  offset - default: 0 - uint8 index offset to start reading from
        Rotation(const MipFieldValues& data, uint8 offset = 0);

    public:
        //API Function: FromEulerAngles (static)
        //  Constructs a Rotation object based on the specified <EulerAngles>.
        //
        //Parameters:
        //  angles - <EulerAngles> object to populate rotation values from
        static Rotation FromEulerAngles(const EulerAngles& angles) { return Rotation(angles); }

        //API Function: FromQuaternion (static)
        //  Constructs a Rotation object based on the specified <Quaternion>.
        //
        //Parameters:
        //  quat - <Quaternion> object to populate rotation values from
        static Rotation FromQuaternion(const Quaternion& quat) { return Rotation(quat); }

#ifndef SWIG
        //API Function: operator EulerAngles() (cast)
        //  Creates an <EulerAngles> object with this object's rotation values.
        //  <Error_BadDataType> exception will be thrown if this Rotation object does not represent an EulerAngles rotation.
        operator EulerAngles() const;

        //API Function: operator Quaternion() (cast)
        //  Creates an <Quaternion> object with this object's rotation values.
        //  <Error_BadDataType> exception will be thrown if this Rotation object does not represent an Quaternion rotation.
        operator Quaternion() const;
#endif //SWIG

    public:
        //API Function: asEulerAngles
        //  Creates an <EulerAngles> object with this object's rotation values.
        //  <Error_BadDataType> exception will be thrown if this Rotation object does not represent an EulerAngles rotation.
        EulerAngles asEulerAngles() const;

        //API Function: asQuaternion
        //  Creates an <Quaternion> object with this object's rotation values.
        //  <Error_BadDataType> exception will be thrown if this Rotation object does not represent an Quaternion rotation.
        Quaternion asQuaternion() const;

        //API Function: asMipFieldValues
        //  Gets the current quaternion values formatted as a <MipFieldValues> object
        //
        //Parameters:
        //  includeFormat - bool - default: true - indicate whether the uint8 format identifier should be included in the MipFieldValues
        //
        //Returns:
        //  <MipFieldValues> - collection of values that represents this object.
        MipFieldValues asMipFieldValues(bool includeFormat = true) const;

        //API Function: appendMipFieldValues
        //  Adds the properly formatted <MipFieldValues> that represent this object to the specified collection.
        //
        //Parameters:
        //  appendTo - (reference) the <MipFieldValues> collection to append to
        //  includeFormat - bool - default: true - indicate whether the uint8 format identifier should be included in the MipFieldValues
        void appendMipFieldValues(MipFieldValues& appendTo, bool includeFormat = true) const;

    private:
        //Variable: m_format
        //  The <Format> this Rotation object represents
        Format m_format;
        
    public:
        //API Function: format
        //  Gets the <Format> of this Rotation object.
        Format format() const { return m_format; }
    };
}