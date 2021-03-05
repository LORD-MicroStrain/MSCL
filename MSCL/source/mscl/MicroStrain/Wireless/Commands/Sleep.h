/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/ByteStream.h"
#include "WirelessResponsePattern.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/Types.h"

namespace mscl
{

#ifndef SWIG

    //Class: Sleep
    //    Contains logic for the Sleep Node command
    class Sleep
    {
    public:
        Sleep() = delete;                           //default constructor disabled
        Sleep(const Sleep&) = delete;               //copy constructor disabled
        Sleep& operator=(const Sleep&) = delete;    //assignment operator disabled

    public:
        //Function: buildCommand
        //    Builds the Sleep command packet.
        //
        //Parameters:
        //    nodeAddress - The address of the Node to build the command for.
        //
        //Returns:
        //    A <ByteStream> containing the command packet.
        static ByteStream buildCommand(NodeAddress nodeAddress);
    };

#endif
}