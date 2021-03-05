/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/ResponsePattern.h"
#include "mscl/Types.h"

namespace mscl
{
    //Class: AutoBalance
    //    Contains logic for the Auto Balance Node command.
    class AutoBalance
    {
    private:
        AutoBalance();                                //default constructor disabled
        AutoBalance(const AutoBalance&);            //copy constructor disabled
        AutoBalance& operator=(const AutoBalance&);    //assignment operator disabled

    public:
        //Function: buildCommand
        //    Builds the AutoBalance command packet.
        //
        //Parameters:
        //    nodeAddress - The address of the Node to build the command for.
        //    channelNumber - The channel number to balance (ch1 = 1, ch8 = 8).
        //    targetValue - The target sensor output value in bits (0-4096).
        //
        //Returns:
        //    A <ByteStream> containing the command packet.
        static ByteStream buildCommand(NodeAddress nodeAddress, uint8 channelNumber, uint16 targetValue);
    };
}