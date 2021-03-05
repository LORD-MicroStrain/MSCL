/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

namespace mscl
{
    //API Class: PositionOffset
    //    Represents a position offset (x, y, z).
    class PositionOffset
    {
    private:
        //Variable: m_x;
        //    The x value.
        float m_x;

        //Variable: m_y
        //    The y value.
        float m_y;

        //Variable: m_z
        //    The z value.
        float m_z;

    public:
        PositionOffset();

        //API Constructor: PositionOffset
        //    Creates a PositionOffset object.
        PositionOffset(float x, float y, float z);

        //API Function: x
        //    Gets the x position offset.
        //
        //Returns:
        //    The x position offset.
        float x() const;

        //API Function: y
        //    Gets the y position offset.
        //
        //Returns:
        //    The y position offset.
        float y() const;

        //API Function: z
        //    Gets the z position offset.
        //
        //Returns:
        //    The z position offset.
        float z() const;
    };
}