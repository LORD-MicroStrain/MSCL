/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

namespace mscl
{
    //API Class: EulerAngles
    //    Represents generic Euler Angles (roll, pitch, yaw).
    class EulerAngles
    {
    private:
        //Variable: m_roll;
        //    The roll value.
        float m_roll;

        //Variable: m_pitch
        //    The pitch value.
        float m_pitch;

        //Variable: m_yaw
        //    The yaw value.
        float m_yaw;

    public:
        EulerAngles();

        //API Constructor: EulerAngles
        //    Creates an EulerAngles object.
        EulerAngles(float roll, float pitch, float yaw);

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
}