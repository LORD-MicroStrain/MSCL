/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/Types.h"

namespace mscl
{

#ifndef SWIG

    //Class: Sleep
    //    Contains logic for the Sleep Node command
    class Sleep
    {
    private:
        Sleep();                        //default constructor disabled
        Sleep(const Sleep&);            //copy constructor disabled
        Sleep& operator=(const Sleep&);    //assignment operator disabled

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