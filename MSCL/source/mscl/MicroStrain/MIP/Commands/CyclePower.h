/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"

namespace mscl
{

#ifndef SWIG

    //Class: CyclePower
    //  Contains the logic for the MIP "Device Reset" command.
    class CyclePower
    {
    public:
        //Constants: Packet Bytes
        //    CMD_ID        - CMD_RESET    - The <MipTypes::Command> for this command
        static const MipTypes::Command CMD_ID = MipTypes::CMD_RESET;

    private:
        CyclePower();                                      //default constructor disabled
        CyclePower(const CyclePower&);            //copy constructor disabled
        CyclePower& operator=(const CyclePower&); //assignment operator disabled

    public:
        //Function: buildCommand
        //    Builds the command packet.
        //
        //Returns:
        //    A <ByteStream> containing the CyclePower command packet.
        static ByteStream buildCommand();

        //Class: Response
        //    Handles the response to the CyclePower command.
        class Response : public GenericMipCommand::Response
        {
        public:
            //Constructor: Response
            //    Creates the CyclePower::Response object.
            //    
            //Parameters:
            //    collector - The ResponseCollector to register the response with.
            Response(std::weak_ptr<ResponseCollector> collector);
        };
    };

#endif

}