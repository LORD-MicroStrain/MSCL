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
#include "mscl/Types.h"

namespace mscl
{

#ifndef SWIG

	//Class: StartNonSyncSampling
	//	Contains logic for the StartNonSyncSampling Node command
	class StartNonSyncSampling
	{
	private:
		StartNonSyncSampling();											//default constructor disabled
		StartNonSyncSampling(const StartNonSyncSampling&);				//copy constructor disabled
		StartNonSyncSampling& operator=(const StartNonSyncSampling&);	//assignment operator disabled

	public:
		//Function: buildCommand
		//	Builds the StartNonSyncSampling command packet
		//
		//Parameters:
		//	nodeAddress - the address of the Node to build the command for
		//
		//Returns:
		//	A <ByteStream> containing the command packet
		static ByteStream buildCommand(NodeAddress nodeAddress);
	};

#endif
}