/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"

#include "PositionVelocity.h"

namespace mscl
{
    GeometricVector::GeometricVector(float x_init, float y_init, float z_init, PositionVelocityReferenceFrame ref) :
        vec_0(x_init),
        vec_1(y_init),
        vec_2(z_init),
        referenceFrame(ref)
    { }

    GeometricVector::GeometricVector() :
        vec_0(0),
        vec_1(0),
        vec_2(0),
        referenceFrame(PositionVelocityReferenceFrame::ECEF)
    { }

    GeometricVector::~GeometricVector()
    { }

    void GeometricVector::fromMipFieldValues(const MipFieldValues& data, uint8 offset, bool includesFrame)
    {
        uint8 index = offset;
        if (includesFrame)
        {
            referenceFrame = static_cast<PositionVelocityReferenceFrame>(data[index].as_uint8());
            index++;
        }

        vec_0 = data[index].as_float();
        vec_1 = data[++index].as_float();
        vec_2 = data[++index].as_float();
    }

    MipFieldValues GeometricVector::asMipFieldValues(bool includeFrame) const
    {
        MipFieldValues m;
        appendMipFieldValues(m, includeFrame);

        return m;
    }

    void GeometricVector::appendMipFieldValues(MipFieldValues& appendTo, bool includeFrame) const
    {
        if (includeFrame)
        {
            appendTo.push_back(Value::UINT8(static_cast<uint8>(referenceFrame)));
        }

        appendTo.push_back(Value::FLOAT(vec_0));
        appendTo.push_back(Value::FLOAT(vec_1));
        appendTo.push_back(Value::FLOAT(vec_2));
    }
}