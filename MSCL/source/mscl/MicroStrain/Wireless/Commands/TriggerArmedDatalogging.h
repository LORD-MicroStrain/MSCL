/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

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
