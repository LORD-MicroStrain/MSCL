/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
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