/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/ResponsePattern.h"

namespace mscl
{
    class WirelessPacket;

#ifndef SWIG

    //Class: ShortPing
    //    Contains logic for the ShortPing node command
    class ShortPing
    {
    private:
        ShortPing();                                //default constructor disabled
        ShortPing(const ShortPing&);                //copy constructor disabled
        ShortPing& operator=(const ShortPing&);        //assignement operator disabled

    public:
        //Function: buildCommand
        //    Builds the ShortPing command packet
        //
        //Returns:
        //    A <ByteStream> containing the ShortPing command packet
        static ByteStream buildCommand(NodeAddress nodeAddress);

        //Class: Response
        //    Handles the response to the ShortPing node command
        class Response : public ResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates a ShortPing Response object
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