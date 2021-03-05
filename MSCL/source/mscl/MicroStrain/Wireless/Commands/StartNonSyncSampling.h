/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/Types.h"

namespace mscl
{

#ifndef SWIG

    //Class: StartNonSyncSampling
    //    Contains logic for the StartNonSyncSampling Node command
    class StartNonSyncSampling
    {
    private:
        StartNonSyncSampling();                                            //default constructor disabled
        StartNonSyncSampling(const StartNonSyncSampling&);                //copy constructor disabled
        StartNonSyncSampling& operator=(const StartNonSyncSampling&);    //assignment operator disabled

    public:
        //Function: buildCommand
        //    Builds the StartNonSyncSampling command packet
        //
        //Parameters:
        //    nodeAddress - the address of the Node to build the command for
        //
        //Returns:
        //    A <ByteStream> containing the command packet
        static ByteStream buildCommand(NodeAddress nodeAddress);
    };

#endif
}