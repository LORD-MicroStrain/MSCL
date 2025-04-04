/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/MIP/MipDataField.h"

namespace mscl
{
    MipDataField::MipDataField() :
        m_fieldId(0)
    {}

    MipDataField::MipDataField(uint16 fieldId) :
        m_fieldId(fieldId)
    {}

    MipDataField::MipDataField(uint16 fieldId, Bytes fieldData) :
        m_fieldId(fieldId),
        m_fieldData(fieldData)
    {}

    uint16 MipDataField::fieldId() const
    {
        return m_fieldId;
    }

    uint8 MipDataField::fieldDescriptor() const
    {
        return Utils::lsb(m_fieldId);
    }

    uint8 MipDataField::descriptorSet() const
    {
        return Utils::msb(m_fieldId);
    }

    ByteStream MipDataField::fieldData() const
    {
        return m_fieldData;
    }
} // namespace mscl
