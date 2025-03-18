/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Vector.h"

namespace mscl
{
    Vector::Vector() :
        Matrix()
    {}

    Vector::Vector(ValueType storedAs, const ByteStream& data) :
        //size (columns) = (# of bytes in ByteStream / # of bytes in the values' type)
        Matrix(1, static_cast<uint16>(data.size() / Utils::valueTypeSize(storedAs)), storedAs, data)
    {}

    double Vector::as_doubleAt(uint16 index) const
    {
        //return the double at the requested position
        return Matrix::as_doubleAt(ROW_POS, index);
    }

    float Vector::as_floatAt(uint16 index) const
    {
        //return the float at the requested position
        return Matrix::as_floatAt(ROW_POS, index);
    }

    uint16 Vector::as_uint16At(uint16 index) const
    {
        //return the uint16 at the requested position
        return Matrix::as_uint16At(ROW_POS, index);
    }

    uint8 Vector::as_uint8At(uint16 index) const
    {
        //return the uint8 at the requested position
        return Matrix::as_uint8At(ROW_POS, index);
    }

    uint16 Vector::size() const
    {
        return columns();
    }
}
