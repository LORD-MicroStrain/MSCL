/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

namespace mscl
{
    //API Class: LinearEquation
    //    Represents a linear equation (y = mx + b).
    class LinearEquation
    {
    public:
        //API Constructor: LinearEquation
        //    Creates a default constructed LinearEquation object.
        //    (slope = 1.0, offset = 0.0)
        LinearEquation();

        //API Constructor: LinearEquation
        //    Creates a LinearEquation object.
        //
        //Parameters:
        //    slope - The slope of the linear equation.
        //    offset - The offset of the linear equation
        LinearEquation(float slope, float offset);

    private:
        //Variable: m_slope
        //    The slope of the linear equation (m in y=mx+b).
        float m_slope;

        //Variable: m_offset
        //    The offset of the linear equation (b in y=mx+b).
        float m_offset;

    public:
        //API Function: slope
        //    Sets the of slope the linear equation.
        //
        //Parameters:
        //    slope - The slope to set.
        void slope(float slope);

        //API Function: slope
        //    Gets the slope of the linear equation.
        //
        //Returns:
        //    The slope of the linear equation.
        float slope() const;

        //API Function: offset
        //    Sets the offset of the linear equation.
        //
        //Parameters:
        //    offset - The offset to set.
        void offset(float offset);

        //API Function: offset
        //    Gets the offset of the linear equation.
        //
        //Returns:
        //    The offset of the linear equation.
        float offset() const;
    };
}