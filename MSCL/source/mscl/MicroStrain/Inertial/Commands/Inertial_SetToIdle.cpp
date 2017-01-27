/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "Inertial_SetToIdle.h"

namespace mscl
{
    ByteStream Inertial_SetToIdle::buildCommand()
    {
        //build and return the command bytes
        return GenericInertialCommand::buildCommand(CMD_ID);
    }

    Inertial_SetToIdle::Response::Response(std::weak_ptr<ResponseCollector> collector):
        GenericInertialCommand::Response(collector, true, false, "Set to Idle")
    {
    }
}