/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "Mip_SetToIdle.h"

namespace mscl
{
    ByteStream Mip_SetToIdle::buildCommand()
    {
        //build and return the command bytes
        return GenericMipCommand::buildCommand(CMD_ID);
    }

    Mip_SetToIdle::Response::Response(std::weak_ptr<ResponseCollector> collector):
        GenericMipCommand::Response(MipTypes::CMD_SET_IDLE, collector, true, false, "Set to Idle")
    {
    }
}