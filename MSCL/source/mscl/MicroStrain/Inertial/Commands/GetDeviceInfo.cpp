/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "GetDeviceInfo.h"
#include "Inertial_Commands.h"
#include "mscl/Utils.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketBuilder.h"

namespace mscl
{
	ByteStream GetDeviceInfo::buildCommand()
	{
		static const uint8 DESC_SET = 0x01;
		static const uint8 FIELD_DESC = 0x03;

		//create the field to add to the packet
		InertialDataField field(Utils::make_uint16(DESC_SET, FIELD_DESC));

		//create a packet builder with with field
		InertialPacketBuilder builder(DESC_SET, field);

		//build the packet and return the ByteStream result
		return builder.buildPacket();
	}


	GetDeviceInfo::Response::Response(std::weak_ptr<ResponseCollector> collector):
		GenericInertialCommand::Response(collector, true, true, "Get Device Info")
	{
	}

	bool GetDeviceInfo::Response::match_data(const InertialDataField& field)
	{
		static const uint8 FIELD_DATA_LEN = 82;

		//verify the field data size is correct
		if(field.fieldData().size() != FIELD_DATA_LEN)
		{
			return false;
		}

		//call match from the super class as well
		return GenericInertialCommand::Response::match_data(field);
	}

	InertialDeviceInfo GetDeviceInfo::Response::parseData(const GenericInertialCommandResponse& response) const
	{
		InertialDeviceInfo result;
		Inertial_Commands::parseData_GetDeviceInfo(response, result);
		return result;
	}
}