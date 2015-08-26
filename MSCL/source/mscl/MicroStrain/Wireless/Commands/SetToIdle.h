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
#pragma once

#include "mscl/MicroStrain/ResponsePattern.h"
#include "mscl/MicroStrain/Wireless/BaseStation.h"
#include "SetToIdleStatus.h"

namespace mscl
{
	//Title: SetToIdle

#ifndef SWIG
	//Class: SetToIdle
	//	Contains logic for the Set to Idle command.
	namespace SetToIdle
	{
		//Function: buildCommand
		//	Builds the SetToIdle command packet.
		//
		//Parameters:
		//	nodeAddress - the address of the Node to build the command for.
		//
		//Returns:
		//	A <ByteStream> containing the SetToIdle command packet
		ByteStream buildCommand(NodeAddress nodeAddress);


		//Class: Response
		//	Handles the response to the SetToIdle command
		class Response : public ResponsePattern
		{
		public:
			//Constructor: Response
			//	Creates a SetToIdle Response object
			//
			//Parameters:
			//	nodeAddress - the node address to check for.
			//	collector - The <ResponseCollector> used to register and unregister the response.
			//	baseStation - The <BaseStation> that will send the command (used for canceling this command).
			Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector, const BaseStation& baseStation);

			//Destructor: Response
			//	Destroys the SetToIdle Response object. This also cancels the SetToIdle operation on the BaseStation, if not already complete or canceled.
			~Response();

		private:
			//Variable: m_nodeAddress
			//	The node address to look for in the response.
			uint16 m_nodeAddress;

			//Variable: m_result
			//	The <SetToIdleResult> detailing the result of the Set to Idle command.
			SetToIdleStatus::SetToIdleResult m_result;

			//Variable: m_baseStation
			//	The <BaseStation> that will send the command (used for canceling this command).
			BaseStation m_baseStation;

			//Variable: m_setToIdleMutex
			//	The mutex used for thread safety.
			std::mutex m_setToIdleMutex;

		public:
			//Function: match
			//	Checks if the bytes passed in match the response pattern from their current read position.
			//
			//Parameters:
			//	data - The <DataBuffer> containing the bytes in which to try to find the pattern.
			//
			//Returns:
			//	true if the response pattern was found, false otherwise.
			virtual bool match(DataBuffer& data) override;

			//Function: cancel
			//	Attempts to cancel the Stop Node operation.
			void cancel();

			//Function: result
			//	Gets the <SetToIdleResult> of the Stop Node command.
			//
			//Returns:
			//	The <SetToIdleResult> containing the result of the Stop Node command.
			SetToIdleStatus::SetToIdleResult result();
		};
	};
#endif
}