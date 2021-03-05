/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/ByteStream.h"
#include "WirelessResponsePattern.h"
#include "mscl/Types.h"

namespace mscl
{

#ifndef SWIG

    //Class: Erase
    //    Contains logic for the Erase Node command
    class Erase
    {
    private:
        Erase();                        //default constructor disabled
        Erase(const Erase&);            //copy constructor disabled
        Erase& operator=(const Erase&);    //assignment operator disabled

    public:
        //Function: buildCommand
        //    Builds the Erase command packet.
        //
        //Parameters:
        //    nodeAddress - The address of the Node to build the command for.
        //
        //Returns:
        //    A <ByteStream> containing the command packet.
        static ByteStream buildCommand(NodeAddress nodeAddress);

        //Class: Response
        //    Handles the response to the Erase node command
        class Response : public WirelessResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates a Erase Response object
            //
            //Parameters:
            //    collector - The <ResponseCollector> used to register and unregister the response
            explicit Response(std::weak_ptr<ResponseCollector> collector);

        public:
            //Function: match
            //    Checks if the bytes passed in match the response pattern from their current read position
            //
            //Parameters:
            //    data - The <DataBuffer> containing the bytes in which to try to find the pattern
            //
            //Returns:
            //    true if the response pattern was found, false otherwise
            virtual bool match(DataBuffer& data) override;
        };
    };

#endif
}