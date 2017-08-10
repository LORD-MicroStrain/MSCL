/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "GenericInertialCommand.h"

namespace mscl
{

#ifndef SWIG

    //Class: Inertial_CyclePower
    //  Contains the logic for the Inertial "Device Reset" command.
    class Inertial_CyclePower
    {
    public:
        //Constants: Packet Bytes
        //    CMD_ID        - CMD_RESET    - The <InertialTypes::Command> for this command
        static const InertialTypes::Command CMD_ID = InertialTypes::CMD_RESET;

    private:
        Inertial_CyclePower();                                      //default constructor disabled
        Inertial_CyclePower(const Inertial_CyclePower&);            //copy constructor disabled
        Inertial_CyclePower& operator=(const Inertial_CyclePower&); //assignment operator disabled

    public:
        //Function: buildCommand
        //    Builds the command packet.
        //
        //Returns:
        //    A <ByteStream> containing the Inertial_CyclePower command packet.
        static ByteStream buildCommand();

        //Class: Response
        //    Handles the response to the Inertial_CyclePower command.
        class Response : public GenericInertialCommand::Response
        {
        public:
            //Constructor: Response
            //    Creates the Inertial_CyclePower::Response object.
            //    
            //Parameters:
            //    collector - The ResponseCollector to register the response with.
            Response(std::weak_ptr<ResponseCollector> collector);
        };
    };

#endif

}