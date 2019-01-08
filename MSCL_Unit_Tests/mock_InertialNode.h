/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/MIP/MipNode_Impl.h"

#include <memory>
#include <turtle/mock.hpp>
#include "mock_Connection.h"
using namespace mscl;


MOCK_BASE_CLASS(mock_InertialNodeImpl, MipNode_Impl)
{    
    mock_InertialNodeImpl():
        MipNode_Impl(makeConnectionWithMockImpl())
    {
    }

    MOCK_METHOD_EXT(getDeviceInfo, 0, mscl::MipDeviceInfo(), getDeviceInfo);
    MOCK_METHOD_EXT(getDescriptorSets, 0, std::vector<uint16>(), getDescriptorSets);
    MOCK_METHOD_EXT(doCommand, 3, mscl::GenericMipCmdResponse(mscl::GenericMipCommand::Response&, const mscl::ByteStream&, bool), doCommand);
};