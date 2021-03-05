/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"

namespace mscl
{

#ifndef SWIG

    //Class: Resume
    //    Contains the logic for the Inertial "Resume" command.
    class Resume
    {
    public:
        //Constants: Packet Bytes
        //    CMD_ID        - CMD_RESUME    - The <MipTypes::Command> for this command
        static const MipTypes::Command CMD_ID = MipTypes::CMD_RESUME;

    private:
        Resume();                            //default constructor disabled
        Resume(const Resume&);                //copy constructor disabled
        Resume& operator=(const Resume&);    //assignment operator disabled

    public:
        //Function: buildCommand
        //    Builds the command packet.
        //
        //Returns:
        //    A <ByteStream> containing the Resume command packet.
        static ByteStream buildCommand();

        //Class: Response
        //    Handles the response to the Resume command.
        class Response : public GenericMipCommand::Response
        {
        public:
            //Constructor: Response
            //    Creates the Resume::Response object.
            //    
            //Parameters:
            //    collector - The ResponseCollector to register the response with.
            Response(std::weak_ptr<ResponseCollector> collector);
        };
    };

#endif

}