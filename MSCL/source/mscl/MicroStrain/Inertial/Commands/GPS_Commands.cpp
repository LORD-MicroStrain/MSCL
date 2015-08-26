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
#include "GPS_Commands.h"

#include "Inertial_Commands.h"
#include "mscl/Exceptions.h"
#include "mscl/Utils.h"

namespace mscl
{
	ByteStream GetGpsDataRateBase::buildCommand()
	{
		//return the result of the Generic buildCommand function
		return GenericInertialCommand::buildCommand(CMD_ID);
	}

	GetGpsDataRateBase::Response::Response(std::weak_ptr<ResponseCollector> collector):
		GenericInertialCommand::Response(collector, true, true, "Get GPS Data Rate Base")
	{}

	uint16 GetGpsDataRateBase::Response::parseData(const GenericInertialCommandResponse& response) const
	{
		return Inertial_Commands::parseData_DataRateBase(response);
	}

	//==========================================================================================
	//GPS MESSAGE FORMAT
	ByteStream GpsMessageFormat::buildCommand_get()
	{
		//container to hold the command's field data
		ByteStream fieldData;

		//add the command selector byte
		fieldData.append_uint8(static_cast<uint8>(Inertial_Commands::cmd_getCurrent));

		//"get" has no channels, so add 0 
		fieldData.append_uint8(0);

		//build and return the command bytes
		return GenericInertialCommand::buildCommand(CMD_ID, fieldData.data());
	}

	ByteStream GpsMessageFormat::buildCommand_set(const InertialChannels& channels, uint16 sampleRateBase)
	{
		//container to hold the command's field data
		ByteStream fieldData;

		//add the command selector byte
		fieldData.append_uint8(static_cast<uint8>(Inertial_Commands::cmd_setCurrent));

		//add the number of channels
		fieldData.append_uint8(static_cast<uint8>(channels.size()));

		//loop through each channel in the vector of channels
		for(InertialChannel ch : channels)
		{
			//if we find a channel not in the Sensor descriptor set
			if(ch.descriptorSet() != DescriptorSet::DESC_SET_DATA_GPS)
			{
				throw Error("InertialChannel (" + Utils::toStr(ch.channelField()) +") is not in the GPS descriptor set");
			}

			//validate the sample rate for the channel
			ch.validateSampleRate(sampleRateBase);

			//add the field descriptor and rate decimation
			fieldData.append_uint8(ch.fieldDescriptor());
			fieldData.append_uint16(ch.rateDecimation(sampleRateBase));
		}

		//build and return the command bytes
		return GenericInertialCommand::buildCommand(CMD_ID, fieldData.data());
	}

	GpsMessageFormat::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse):
		GenericInertialCommand::Response(collector, true, dataResponse, "GPS Message Format")
	{}

	InertialChannels GpsMessageFormat::Response::parseData(const GenericInertialCommandResponse& response, uint16 sampleRateBase) const
	{
		return Inertial_Commands::parseData_MessageFormat(response, fieldDataByte(), sampleRateBase);
	}
	//==========================================================================================
}