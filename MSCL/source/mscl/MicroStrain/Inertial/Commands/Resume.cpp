/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "Resume.h"

namespace mscl
{
    ByteStream Resume::buildCommand()
    {
        //build and return the command bytes
        return GenericInertialCommand::buildCommand(CMD_ID);
    }

    Resume::Response::Response(std::weak_ptr<ResponseCollector> collector):
        GenericInertialCommand::Response(collector, true, false, "Resume")
    {
    }
}