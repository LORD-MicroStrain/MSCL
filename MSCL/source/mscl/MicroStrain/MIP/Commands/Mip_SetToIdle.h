/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"

namespace mscl
{

#ifndef SWIG

    //Class: Mip_SetToIdle
    //    Contains the logic for the MIP "Set to Idle" command.
    class Mip_SetToIdle
    {
    public:
        //Constants: Packet Bytes
        //    CMD_ID        - CMD_SET_IDLE    - The <MipTypes::Command> for this command
        static const MipTypes::Command CMD_ID = MipTypes::CMD_SET_IDLE;

    private:
        Mip_SetToIdle();                                        //default constructor disabled
        Mip_SetToIdle(const Mip_SetToIdle&);                //copy constructor disabled
        Mip_SetToIdle& operator=(const Mip_SetToIdle&);    //assignment operator disabled

    public:
        //Function: buildCommand
        //    Builds the command packet.
        //
        //Returns:
        //    A <ByteStream> containing the SetToIdle command packet.
        static ByteStream buildCommand();

        //Class: Response
        //    Handles the response to the SetToIdle command.
        class Response : public GenericMipCommand::Response
        {
        public:
            //Constructor: Response
            //    Creates the SetToIdle::Response object.
            //    
            //Parameters:
            //    collector - The ResponseCollector to register the response with.
            Response(std::weak_ptr<ResponseCollector> collector);
        };
    };

#endif

}