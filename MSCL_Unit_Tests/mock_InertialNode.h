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

#include "mscl/MicroStrain/Inertial/InertialNode_Impl.h"

#include <memory>
#include <turtle/mock.hpp>
#include "mock_Connection.h"
using namespace mscl;


MOCK_BASE_CLASS(mock_InertialNodeImpl, InertialNode_Impl)
{	
	mock_InertialNodeImpl():
		InertialNode_Impl(makeConnectionWithMockImpl())
	{
	}

	MOCK_METHOD_EXT(getDeviceInfo, 0, mscl::InertialDeviceInfo(), getDeviceInfo);
	MOCK_METHOD_EXT(getDescriptorSets, 0, std::vector<uint16>(), getDescriptorSets);
	MOCK_METHOD_EXT(doInertialCmd, 4, mscl::GenericInertialCommandResponse(mscl::GenericInertialCommand::Response&, const mscl::ByteStream&, mscl::InertialTypes::Command, bool), doInertialCmd);
};