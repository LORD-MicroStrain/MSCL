/*****************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the included
LICENSE.txt file for a copy of the full GNU General Public License.
*****************************************************************************/
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