/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "Inertial_CyclePower.h"

namespace mscl
{
    ByteStream Inertial_CyclePower::buildCommand()
    {
        //build and return the command bytes
        return GenericInertialCommand::buildCommand(CMD_ID);
    }

    Inertial_CyclePower::Response::Response(std::weak_ptr<ResponseCollector> collector):
        GenericInertialCommand::Response(InertialTypes::CMD_RESET, collector, true, false, "CyclePower")
    {
    }
}