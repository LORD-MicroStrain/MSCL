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
#include "Inertial_Commands.h"

#include "mscl/Utils.h"

namespace mscl
{
	void Inertial_Commands::parseData_GetDeviceInfo(const GenericInertialCommandResponse& response, InertialDeviceInfo& result)
	{
		//all the positions of the info in the fieldData
		static const size_t FWVERS_POS = 0;
		static const size_t MODELNAME_POS = 2;
		static const size_t MODELNUM_POS = 18;
		static const size_t SERIALNUM_POS = 34;
		static const size_t LOTNUM_POS = 50;
		static const size_t DEVOPTS_POS = 66;

		ByteStream fieldData = response.data();

		//load the firmware version
		uint16 fw = fieldData.read_uint16(FWVERS_POS);

		//inertial firmware version is in the form: 3487 = 3.4.87
		uint16 major = (fw / 1000);
		uint16 minorAndPatch = (fw - (major * 1000));
		uint16 minor = (minorAndPatch / 100);
		uint16 patch = (minorAndPatch - (minor * 100));

		result.fwVersion = Version(major, minor, patch);

		//load the model name and trim any whitespace
		result.modelName = fieldData.read_string(MODELNAME_POS, 16);
		Utils::strTrimLeft(result.modelName);

		//load the model number and trim any whitespace
		result.modelNumber = fieldData.read_string(MODELNUM_POS, 16);
		Utils::strTrimLeft(result.modelNumber);

		//load the serial number and trim any whitespace
		result.serialNumber = fieldData.read_string(SERIALNUM_POS, 16);
		Utils::strTrimLeft(result.serialNumber);

		//load the load number and trim any whitespace
		result.lotNumber = fieldData.read_string(LOTNUM_POS, 16);
		Utils::strTrimLeft(result.lotNumber);

		//load the device options and trim any whitespace
		result.deviceOptions = fieldData.read_string(DEVOPTS_POS, 16);
		Utils::strTrimLeft(result.deviceOptions);
	}

	void Inertial_Commands::parseData_GetDeviceDescriptorSets(const GenericInertialCommandResponse& response, std::vector<uint16>& result)
	{
		InertialPacket::Payload fieldData(response.data());

		size_t fieldLength = fieldData.size();
		size_t itr = 0;

		//loop over all the bytes in the field data
		while(itr < fieldLength)
		{
			//read the descriptor and add it to the vector
			result.push_back(fieldData.read_uint16(itr));
			itr += 2;
		}
	}

	uint16 Inertial_Commands::parseData_DataRateBase(const GenericInertialCommandResponse& response)
	{
		//return the value from the response
		return response.data().read_uint16(0);
	}

	uint8 Inertial_Commands::parseData_CommunicationMode(const GenericInertialCommandResponse& response)
	{
		//cast to comm mode and return
		return response.data().read_uint8(0);
	}

	InertialChannels Inertial_Commands::parseData_MessageFormat(const GenericInertialCommandResponse& response, uint8 descSet, uint16 sampleRateBase)
	{
		InertialChannels result;

		//use a DataBuffer to make reading nicer
		DataBuffer db(response.data());

		//first byte is the total number of descriptors (channels) that are in the data
		uint8 numDescriptors = db.read_uint8();

		//loop through all the descriptors
		for(uint8 desc = 0; desc < numDescriptors; ++desc)
		{
			//field descriptor followed by the rate decimation
			uint8 fieldDesc = db.read_uint8();
			uint16 rateDecimation = db.read_uint16();

			//build the InertialChannelField
			InertialTypes::ChannelField channelId = static_cast<InertialTypes::ChannelField>(Utils::make_uint16(descSet, fieldDesc));

			//create an InertialChannel and add to the result
			result.push_back(InertialChannel(channelId, SampleRate::Hertz(sampleRateBase / rateDecimation)));
		}

		//return the InertialChannels result
		return result;
	}

	bool Inertial_Commands::parseData_ContinuousDataStream(const GenericInertialCommandResponse& response)
	{
		//return true if enabled, false if disabled
		return (response.data().read_uint8(1) == 1);	//Note: position 0 is the device selector, which can be ignored here.
	}
}