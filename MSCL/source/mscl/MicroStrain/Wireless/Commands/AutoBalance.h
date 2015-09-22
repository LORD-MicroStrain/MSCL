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
#include "mscl/Types.h"

namespace mscl
{
	//Class: AutoBalance
	//	Contains logic for the Auto Balance Node command.
	class AutoBalance
	{
	private:
		AutoBalance();								//default constructor disabled
		AutoBalance(const AutoBalance&);			//copy constructor disabled
		AutoBalance& operator=(const AutoBalance&);	//assignment operator disabled

	public:
		//Function: buildCommand
		//	Builds the AutoBalance command packet.
		//
		//Parameters:
		//	nodeAddress - The address of the Node to build the command for.
		//	channelNumber - The channel number to balance (ch1 = 1, ch8 = 8).
		//	targetValue - The target sensor output value in bits.
		//
		//Returns:
		//	A <ByteStream> containing the command packet.
		static ByteStream buildCommand(NodeAddress nodeAddress, uint8 channelNumber, uint16 targetValue);
	};
}