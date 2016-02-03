/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/ResponsePattern.h"

namespace mscl
{

#ifndef SWIG

    //Class: TriggerArmedDatalogging
    //    Contains logic for the Trigger Armed Datalogging Node command.
    class TriggerArmedDatalogging
    {
    private:
        TriggerArmedDatalogging();                                            //disabled default constructor
        TriggerArmedDatalogging(const TriggerArmedDatalogging&);            //disabled copy constructor
        TriggerArmedDatalogging& operator=(const TriggerArmedDatalogging&);    //disabled assignment operator

    public:
        //=====================================================================================================
        //Constants: Packet Information
        //    COMMAND_ID    - 0x000E        - The Command ID for the TriggerArmedDatalogging command
        //=====================================================================================================
        static const uint16 COMMAND_ID = 0x000E;

        //Function: buildCommand
        //    Builds the TriggerArmedDatalogging command packet.
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