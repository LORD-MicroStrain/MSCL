/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"

#include "EulerAngles.h"

namespace mscl
{
    EulerAngles::EulerAngles():
        EulerAngles(0.0f, 0.0f, 0.0f)
    {
    }

    EulerAngles::EulerAngles(float roll, float pitch, float yaw) :
        Vector(ValueType::valueType_float, ByteStream())
    {
        m_numColumns = 3;
        m_data.append_float(roll);
        m_data.append_float(pitch);
        m_data.append_float(yaw);
    }

    EulerAngles::EulerAngles(const MipFieldValues& data, uint8 offset) :
        Vector(ValueType::valueType_float, ByteStream())
    {
        m_numColumns = 3;
        for (int i = offset; i < m_numColumns; i++)
        {
            m_data.append_float(data[i].as_float());
        }
    }

#ifndef SWIG
    EulerAngles::operator Rotation() const
    {
        return Rotation::FromEulerAngles(*this);
    }
#endif

    MipFieldValues EulerAngles::asMipFieldValues() const
    {
        MipFieldValues m;
        appendMipFieldValues(m);

        return m;
    }

    void EulerAngles::appendMipFieldValues(MipFieldValues& appendTo) const
    {
        for (uint8 i = 0; i < 3; i++)
        {
            appendTo.push_back(Value::FLOAT(as_floatAt(i)));
        }
    }

    float EulerAngles::roll() const
    {
        return as_floatAt(0);
    }

    float EulerAngles::pitch() const
    {
        return as_floatAt(1);
    }

    float EulerAngles::yaw() const
    {
        return as_floatAt(2);
    }

    float EulerAngles::heading() const
    {
        return as_floatAt(2);
    }

    Quaternion::Quaternion() :
        Quaternion(0.0f, 0.0f, 0.0f, 0.0f)
    {
    }

    Quaternion::Quaternion(float x, float y, float z, float w) :
        Vector(ValueType::valueType_float, ByteStream())
    {
        m_numColumns = 4;
        m_data.append_float(x);
        m_data.append_float(y);
        m_data.append_float(z);
        m_data.append_float(w);
    }

    Quaternion::Quaternion(const MipFieldValues& data, uint8 offset) :
        Vector(ValueType::valueType_float, ByteStream())
    {
        m_numColumns = 4;
        for (int i = offset; i < m_numColumns; i++)
        {
            m_data.append_float(data[i].as_float());
        }
    }

#ifndef SWIG
    Quaternion::operator Rotation() const
    {
        return Rotation::FromQuaternion(*this);
    }
#endif

    MipFieldValues Quaternion::asMipFieldValues() const
    {
        MipFieldValues m;
        appendMipFieldValues(m);

        return m;
    }

    void Quaternion::appendMipFieldValues(MipFieldValues& appendTo) const
    {
        for (uint8 i = 0; i < 4; i++)
        {
            appendTo.push_back(Value::FLOAT(as_floatAt(i)));
        }
    }

    void Quaternion::normalize()
    {
        float magnitude = 0.0f;
        for (uint8 i = 0; i < 4; i++)
        {
            float val = as_floatAt(i);
            magnitude += val * val;
        }

        magnitude = sqrt(magnitude);

        if (magnitude == 0)
        {
            return;
        }

        ByteStream b;
        for (uint8 i = 0; i < 4; i++)
        {
            float val = as_floatAt(i);
            b.append_float(val / magnitude);
        }

        m_data = b;
    }

    float Quaternion::x() const
    {
        return as_floatAt(0);
    }

    float Quaternion::y() const
    {
        return as_floatAt(1);
    }

    float Quaternion::z() const
    {
        return as_floatAt(2);
    }

    float Quaternion::w() const
    {
        return as_floatAt(3);
    }

    void Quaternion::set(uint8 index, float val)
    {
        uint32 pos = getBytePos(0, index);
        ByteStream valB;
        valB.append_float(val);

        for (uint32 i = 0; i < 4; i++)
        {
            uint32 replaceIndex = pos + i;
            m_data.data()[replaceIndex] = valB[i];
        }
    }

    Rotation::Rotation(const EulerAngles& angles) :
        Vector(ValueType::valueType_float, ByteStream()),
        m_format(Rotation::Format::EULER_ANGLES)
    {
        m_numColumns = 4;
        m_data.append_float(angles.roll());
        m_data.append_float(angles.pitch());
        m_data.append_float(angles.yaw());
        m_data.append_float(0.0f);
    }

    Rotation::Rotation(const Quaternion& quat) :
        Vector(ValueType::valueType_float, ByteStream()),
        m_format(Rotation::Format::QUATERNION)
    {
        m_numColumns = 4;
        m_data.append_float(quat.x());
        m_data.append_float(quat.y());
        m_data.append_float(quat.z());
        m_data.append_float(quat.w());
    }

    Rotation::Rotation(const MipFieldValues& data, uint8 offset) :
        Vector(ValueType::valueType_float, ByteStream())
    {
        m_format = static_cast<Format>(data[offset].as_uint8());

        m_numColumns = 4;
        for (int i = offset + 1; i < m_numColumns; i++)
        {
            m_data.append_float(data[i].as_float());
        }
    }

#ifndef SWIG
    Rotation::operator mscl::EulerAngles() const
    {
        return asEulerAngles();
    }

    Rotation::operator mscl::Quaternion() const
    {
        return asQuaternion();
    }
#endif

    EulerAngles Rotation::asEulerAngles() const
    {
        return EulerAngles(as_floatAt(0), as_floatAt(1), as_floatAt(2));
    }

    Quaternion Rotation::asQuaternion() const
    {
        return Quaternion(as_floatAt(0), as_floatAt(1), as_floatAt(2), as_floatAt(3));
    }

    MipFieldValues Rotation::asMipFieldValues(bool includeFormat) const
    {
        MipFieldValues m;
        appendMipFieldValues(m, includeFormat);

        return m;
    }

    void Rotation::appendMipFieldValues(MipFieldValues& appendTo, bool includeFormat) const
    {
        if (includeFormat)
        {
            appendTo.push_back(Value::UINT8(static_cast<uint8>(m_format)));
        }

        for (uint8 i = 0; i < 4; i++)
        {
            appendTo.push_back(Value::FLOAT(as_floatAt(i)));
        }
    }
}