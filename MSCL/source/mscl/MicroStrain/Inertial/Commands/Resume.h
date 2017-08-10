/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "GenericInertialCommand.h"

namespace mscl
{

#ifndef SWIG

    //Class: Resume
    //    Contains the logic for the Inertial "Resume" command.
    class Resume
    {
    public:
        //Constants: Packet Bytes
        //    CMD_ID        - CMD_RESUME    - The <InertialTypes::Command> for this command
        static const InertialTypes::Command CMD_ID = InertialTypes::CMD_RESUME;

    private:
        Resume();                            //default constructor disabled
        Resume(const Resume&);                //copy constructor disabled
        Resume& operator=(const Resume&);    //assignment operator disabled

    public:
        //Function: buildCommand
        //    Builds the command packet.
        //
        //Returns:
        //    A <ByteStream> containing the Inertial Resume command packet.
        static ByteStream buildCommand();

        //Class: Response
        //    Handles the response to the Resume command.
        class Response : public GenericInertialCommand::Response
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