/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "GenericInertialCommand.h"

namespace mscl
{

#ifndef SWIG

	//Class: Ping
	//	Contains the logic for the Inertial Ping command.
	class Ping
	{
	public:
		//Constants: Packet Bytes
		//	CMD_ID			- CMD_PING	- The <InertialTypes::Command> for this command
		static const InertialTypes::Command CMD_ID = InertialTypes::CMD_PING;

	private:
		Ping();				//default constructor disabled

	public:
		//Function: buildCommand
		//	Builds the command packet
		//
		//Returns:
		//	A <ByteStream> containing the Inertial Ping command packet
		static ByteStream buildCommand();

		//Class: Response
		//	Handles the response to the Ping command.
		class Response : public GenericInertialCommand::Response
		{
		protected:
			virtual InertialTypes::Command commandId() const override { return CMD_ID; }

		public:
			//Constructor: Response
			//	Creates a Ping Response object
			//
			//Parameters:
			//	collector - The <ResponseCollector> used to register and unregister the response
			Response(std::weak_ptr<ResponseCollector> collector);
		};
	};

#endif

}