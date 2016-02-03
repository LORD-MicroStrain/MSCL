/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "InertialDataField.h"
#include "mscl/Types.h"
#include "mscl/Utils.h"
#include "mscl/MicroStrain/ByteStream.h"

namespace mscl
{
    InertialDataField::InertialDataField() :
        m_fieldId(0)
    {
    }

    InertialDataField::InertialDataField(uint16 fieldId) :
        m_fieldId(fieldId)
    {
    }

    InertialDataField::InertialDataField(uint16 fieldId, Bytes fieldData):
        m_fieldId(fieldId),
        m_fieldData(fieldData)
    {
    }

    uint16 InertialDataField::fieldId() const
    {
        return m_fieldId;
    }

    uint8 InertialDataField::fieldDescriptor() const
    {
        return Utils::lsb(m_fieldId);
    }

    uint8 InertialDataField::descriptorSet() const
    {
        return Utils::msb(m_fieldId);
    }

    ByteStream InertialDataField::fieldData() const
    {
        return m_fieldData;
    }
}