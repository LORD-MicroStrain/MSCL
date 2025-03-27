/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Inertial/PositionVelocity.h"

namespace mscl
{
    Vec3f::Vec3f(float x, float y, float z) :
        vec_0(x),
        vec_1(y),
        vec_2(z)
    {}

    void Vec3f::fromMipFieldValues(const MipFieldValues& data, uint8 offset)
    {
        uint8 index = offset;

        vec_0 = data[index].as_float();
        vec_1 = data[++index].as_float();
        vec_2 = data[++index].as_float();
    }

    MipFieldValues Vec3f::asMipFieldValues() const
    {
        MipFieldValues m;
        appendMipFieldValues(m);

        return m;
    }

    void Vec3f::appendMipFieldValues(MipFieldValues& appendTo) const
    {
        appendTo.push_back(Value::FLOAT(vec_0));
        appendTo.push_back(Value::FLOAT(vec_1));
        appendTo.push_back(Value::FLOAT(vec_2));
    }

    GeometricVector::GeometricVector(float x_init, float y_init, float z_init, PositionVelocityReferenceFrame ref) :
        Vec3f(x_init, y_init, z_init),
        referenceFrame(ref)
    {}

    GeometricVector::GeometricVector() :
        Vec3f(),
        referenceFrame(ECEF)
    {}

    GeometricVector::~GeometricVector()
    {}

    void GeometricVector::fromMipFieldValues_includesFrame(const MipFieldValues& data, uint8 offset)
    {
        uint8 index = offset;
        referenceFrame = static_cast<PositionVelocityReferenceFrame>(data[index].as_uint8());
        index++;

        fromMipFieldValues(data, index);
    }

    MipFieldValues GeometricVector::asMipFieldValues_includeFrame() const
    {
        MipFieldValues m;
        appendMipFieldValues_includeFrame(m);

        return m;
    }

    void GeometricVector::appendMipFieldValues_includeFrame(MipFieldValues& appendTo) const
    {
        appendTo.push_back(Value::UINT8(static_cast<uint8>(referenceFrame)));
        appendMipFieldValues(appendTo);
    }
} // namespace mscl
