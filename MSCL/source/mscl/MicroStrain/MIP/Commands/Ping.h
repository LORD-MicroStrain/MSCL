/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"

namespace mscl
{

#ifndef SWIG

    //Class: Ping
    //    Contains the logic for the Inertial Ping command.
    class Ping
    {
    public:
        //Constants: Packet Bytes
        //    CMD_ID            - CMD_PING    - The <MipTypes::Command> for this command
        static const MipTypes::Command CMD_ID = MipTypes::CMD_PING;

    private:
        Ping();                //default constructor disabled

    public:
        //Function: buildCommand
        //    Builds the command packet
        //
        //Returns:
        //    A <ByteStream> containing the Ping command packet
        static ByteStream buildCommand();

        //Class: Response
        //    Handles the response to the Ping command.
        class Response : public GenericMipCommand::Response
        {
        public:
            //Constructor: Response
            //    Creates a Ping Response object
            //
            //Parameters:
            //    collector - The <ResponseCollector> used to register and unregister the response
            Response(std::weak_ptr<ResponseCollector> collector);
        };
    };

#endif

}