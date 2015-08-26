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
#include "Ping.h"

#include "mscl/Utils.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacket.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketBuilder.h"

namespace mscl
{
	ByteStream Ping::buildCommand()
	{
		static const uint8 DESC_SET = 0x01;
		static const uint8 FIELD_DESC = 0x01;

		//create the field to add to the packet
		InertialDataField field(Utils::make_uint16(DESC_SET, FIELD_DESC));

		//create a packet builder with with field
		InertialPacketBuilder builder(DESC_SET, field);

		//build the packet and return the ByteStream result
		return builder.buildPacket();
	}

	Ping::Response::Response(std::weak_ptr<ResponseCollector> collector):
		GenericInertialCommand::Response(collector, true, false, "Ping")
	{
	}
}