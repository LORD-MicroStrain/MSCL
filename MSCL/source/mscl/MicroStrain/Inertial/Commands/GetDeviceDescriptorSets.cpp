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
#include "GetDeviceDescriptorSets.h"
#include "Inertial_Commands.h"
#include "mscl/Utils.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketBuilder.h"

namespace mscl
{

	ByteStream GetDeviceDescriptorSets::buildCommand()
	{
		static const uint8 DescSet = 0x01;
		static const uint8 FieldDesc = 0x04;

		//create the field to add to the packet
		InertialDataField field(Utils::make_uint16(DescSet, FieldDesc));

		//create a packet builder with with field
		InertialPacketBuilder builder(DescSet, field);

		//build the packet and return the ByteStream result
		return builder.buildPacket();
	}


	GetDeviceDescriptorSets::Response::Response(std::weak_ptr<ResponseCollector> collector):
		GenericInertialCommand::Response(collector, true, true, "Get Device Descriptor Sets")
	{}

	bool GetDeviceDescriptorSets::Response::match_data(const InertialDataField& field)
	{
		InertialPacket::Payload fieldData(field.fieldData());

		//verify the field is the minimum size
		if(fieldData.size() < 2)
		{
			return false;
		}

		//call match from the super class as well
		return GenericInertialCommand::Response::match_data(field);
	}

	std::vector<uint16> GetDeviceDescriptorSets::Response::parseData(const GenericInertialCommandResponse& response) const
	{
		std::vector<uint16> result;
		Inertial_Commands::parseData_GetDeviceDescriptorSets(response, result);
		return result;
	}
}