/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "GenericInertialCommand.h"
#include "mscl/Version.h"
#include "mscl/MicroStrain/Inertial/Commands/InertialCmdResponse.h"

#include <string>

namespace mscl
{
	//Title: GetDeviceInfo

	//Struct: InertialDeviceInfo
	//	Contains information retrieved from an Inertial GetDeviceInfo command.
	struct InertialDeviceInfo
	{
	public:
		//Variable: m_fwVersion
		//	The firmware <Version>.
		Version fwVersion;

		//Variable: m_modelName
		//	The model name.
		std::string modelName;

		//Variable: m_modelNumber
		//	The model number.
		std::string modelNumber;

		//Variable: m_serialNumber
		//	The serial number.
		std::string serialNumber;

		//Variable: m_lotNumber
		//	The lot number.
		std::string lotNumber;

		//Variable: m_deviceOptions
		//	The device options.
		std::string deviceOptions;
	};

	//Class: GetDeviceInfo
	//	Contains the logic for the Inertial GetDeviceInfo command
	class GetDeviceInfo
	{
	public:
		//Constants: Packet Bytes
		//	CMD_ID				- CMD_GET_DEVICE_INFO	- The <InertialTypes::Command> for this command
		//  FIELD_DATA_BYTE		- 0x81					- The Data Field Descriptor byte
		static const InertialTypes::Command CMD_ID = InertialTypes::CMD_GET_DEVICE_INFO;
		static const uint8 FIELD_DATA_BYTE = 0x81;

	private:
		GetDeviceInfo();								//default constructor disabled

	public:
		//Function: buildCommand
		//	Builds the command packet
		//
		//Returns:
		//	A <ByteStream> containing the Inertial GetDeviceInfo command packet
		static ByteStream buildCommand();

		//Class: Response
		//	Handles the response to the GetDeviceInfo command
		class Response : public GenericInertialCommand::Response
		{
		protected:
			virtual InertialTypes::Command commandId() const override { return CMD_ID; }
			virtual uint8 fieldDataByte() const override { return FIELD_DATA_BYTE; }

		public:
			//Constructor: Response
			//	Creates a GetDeviceInfo Response object
			//
			//Parameters:
			//	collector - The <ResponseCollector> used to register and unregister the response
			Response(std::weak_ptr<ResponseCollector> collector);

		public:
			//Function: match_data
			//	Attempts to match an <InertialDataField> to the expected data field response.
			//
			//Returns:
			//	true if the field matches the expected data, false if it does not.
			virtual bool match_data(const InertialDataField& field) override;

			//Function: parseData
			//	Parses a successfully matched response for the GetDeviceInfo command.
			//
			//Parameters:
			//	response - The <GenericInertialCommandResponse> that matches the data field for this response.
			//
			//Returns:
			//	The GetDeviceInfoResponse parsed from the response.
			InertialDeviceInfo parseData(const GenericInertialCommandResponse& response) const;
		};
	};
}