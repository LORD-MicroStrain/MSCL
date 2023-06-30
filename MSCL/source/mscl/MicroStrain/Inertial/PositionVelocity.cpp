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
}