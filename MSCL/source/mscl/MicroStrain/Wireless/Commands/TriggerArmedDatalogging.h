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

#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/ResponsePattern.h"

namespace mscl
{

#ifndef SWIG

	//Class: TriggerArmedDatalogging
	//	Contains logic for the Trigger Armed Datalogging Node command.
	class TriggerArmedDatalogging
	{
	private:
		TriggerArmedDatalogging();											//disabled default constructor
		TriggerArmedDatalogging(const TriggerArmedDatalogging&);			//disabled copy constructor
		TriggerArmedDatalogging& operator=(const TriggerArmedDatalogging&);	//disabled assignment operator

	public:
		//=====================================================================================================
		//Constants: Packet Information
		//	COMMAND_ID	- 0x000E		- The Command ID for the TriggerArmedDatalogging command
		//=====================================================================================================
		static const uint16 COMMAND_ID = 0x000E;

		//Function: buildCommand
		//	Builds the TriggerArmedDatalogging command packet.
		//
		//Parameters:
		//	nodeAddress - The address of the Node to build the command for.
		//
		//Returns:
		//	A <ByteStream> containing the command packet.
		static ByteStream buildCommand(NodeAddress nodeAddress);
	};

#endif

}