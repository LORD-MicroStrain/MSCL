/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/ResponsePattern.h"

namespace mscl
{
#ifndef SWIG

    //Class: BaseStation_Ping
    //    Contains logic for the base station Ping command
    class BaseStation_Ping
    {
    private:
        BaseStation_Ping();                                        //default constructor disabled
        BaseStation_Ping(const BaseStation_Ping&);                //copy constuctor disabled
        BaseStation_Ping& operator=(const BaseStation_Ping&);    //assignement operator disabled

    public:
        //Function: buildCommand
        //    Builds the Ping command packet
        //
        //Returns:
        //    A <ByteStream> containing the base station Ping command
        static ByteStream buildCommand();

        //Class: Response
        //    Handles the response to the base station Ping command
        class Response : public ResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates a Ping Response object
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