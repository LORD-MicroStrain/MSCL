/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "GenericInertialCommand.h"
#include "mscl/MicroStrain/Inertial/InertialTypes.h"

namespace mscl
{
	//Class: ContinuousDataStream
	//	Contains the logic for the "Continuous Data Stream" command.
	class ContinuousDataStream
	{
	public:
		//Constants: Packet Bytes
		//	CMD_ID				- CMD_CONTINUOUS_DATA_STREAM	- The <InertialTypes::Command> for this command
		//  FIELD_DATA_BYTE		- 0x85							- The Data Field Descriptor byte
		static const InertialTypes::Command CMD_ID	= InertialTypes::CMD_CONTINUOUS_DATA_STREAM;
		static const uint8 FIELD_DATA_BYTE			= 0x85;

	private:
		ContinuousDataStream();	//disabled default constructor

		//Function: getDeviceSelector
		//	Converts an <InertialTypes::InertialCategory> to the device selector for this command.
		//
		//Parameters:
		//	type - The <InertialTypes::InertialCategory> to get the device selector for.
		//
		//Returns:
		//	The device selector for the given <InertialTypes::InertialCategory>.
		static uint8 getDeviceSelector(InertialTypes::InertialCategory type);

	public:
		//Function: buildCommand_get
		//	Builds the bytes for the "get" command.
		//
		//Parameters:
		//	type - The <InertialTypes::InertialCategory> to get the current state for.
		//
		//Returns:
		//	A <ByteStream> that holds the bytes that make up the command.
		static ByteStream buildCommand_get(InertialTypes::InertialCategory type);

		//Function: buildCommand_set
		//	Builds the bytes for the "set" command. 
		//
		//Parameters:
		//	type - The <InertialTypes::InertialCategory> to set the state for.
		//	enable - Whether to enable (true) or disable (false) continuous data streaming.
		//
		//Returns:
		//	A <ByteStream> that holds the bytes that make up the command.
		static ByteStream buildCommand_set(InertialTypes::InertialCategory type, bool enable);

		//Class: Response
		//	Handles the response to the ContinuousDataStream command.
		class Response : public GenericInertialCommand::Response
		{
		protected:
			virtual InertialTypes::Command commandId() const { return CMD_ID; }
			virtual uint8 fieldDataByte() const			{ return FIELD_DATA_BYTE; }

		private:
			//Variable: m_deviceSelector
			//	The device selector to look for in the response.
			uint8 m_deviceSelector;

		public:
			//Constructor: Response
			//	Creates the ContinuousDataStream::Response object.
			//	
			//Parameters:
			//	collector - The ResponseCollector to register the response with.
			//	dataResponse - Whether the command is expecting a data field response
			//	type - The <InertialTypes::InertialCategory> to use for the command/response.
			Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse, InertialTypes::InertialCategory type);

			//Function: match_data
			//	Attempts to match an <InertialDataField> to the expected data field response.
			//
			//Returns:
			//	true if the field matches the expected data, false if it does not.
			virtual bool match_data(const InertialDataField& field) override;

			//Function: parseData
			//	Parses a successfully matched response for the ContinuousDataStream command.
			//
			//Parameters:
			//	response - The <GenericInertialCommandResponse> that matches the data field for this response.
			//
			//Returns:
			//	true if the data stream is enabled, false if it is disabled.
			bool parseData(const GenericInertialCommandResponse& response) const;
		};
	};
}