/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "Sensor_Commands.h"

#include "mscl/Exceptions.h"
#include "mscl/Utils.h"
#include "Inertial_Commands.h"

namespace mscl
{
	//==========================================================================================
	//GET SENSOR DATA RATE BASE
	ByteStream GetSensorDataRateBase::buildCommand()
	{
		//return the result of the Generic buildCommand function
		return GenericInertialCommand::buildCommand(CMD_ID);
	}

	GetSensorDataRateBase::Response::Response(std::weak_ptr<ResponseCollector> collector):
		GenericInertialCommand::Response(collector, true, true, "Get Sensor Data Rate Base")
	{}

	uint16 GetSensorDataRateBase::Response::parseData(const GenericInertialCommandResponse& response) const
	{
		return Inertial_Commands::parseData_DataRateBase(response);
	}
	//==========================================================================================

	//==========================================================================================
	//SENSOR MESSAGE FORMAT
	ByteStream SensorMessageFormat::buildCommand_get()
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

	ByteStream SensorMessageFormat::buildCommand_set(const InertialChannels& channels, uint16 sampleRateBase)
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
			if(ch.descriptorSet() != DescriptorSet::DESC_SET_DATA_SENSOR)
			{
				throw Error("InertialChannel (" + Utils::toStr(ch.channelField()) +") is not in the Sensor descriptor set");
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

	SensorMessageFormat::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse):
		GenericInertialCommand::Response(collector, true, dataResponse, "Sensor Message Format")
	{}

	InertialChannels SensorMessageFormat::Response::parseData(const GenericInertialCommandResponse& response, uint16 sampleRateBase) const
	{
		return Inertial_Commands::parseData_MessageFormat(response, fieldDataByte(), sampleRateBase);
	}
	//==========================================================================================

}