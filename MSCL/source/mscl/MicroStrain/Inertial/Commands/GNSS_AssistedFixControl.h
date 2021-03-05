/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"
#include "mscl/MicroStrain/ResponseCollector.h"

namespace mscl
{

#ifndef SWIG

    //Class: GNSS_AssistedFixControl
    //    Contains the logic for the Inertial GNSS Assist Fix Control command.
    class GNSS_AssistedFixControl : private GenericMipCommand
    {
    public:
        static const int NO_FLAGS_DEFINED = 0xFF;

    private:
        GNSS_AssistedFixControl() {};                //default constructor disabled
        
         //Constants: Packet Bytes
         //     FIELD_DATA_BYTE - Descriptor byte for the Field data.
        static const uint8 FIELD_DATA_BYTE = 0xA2;

    public:
        virtual ~GNSS_AssistedFixControl() {};

        //Function: buildCommand_get
        //    Builds the bytes for the "get" command.
        //
        //Returns:
        //    A <ByteStream> containing the GNSS_AssistedFixControl command packet
        static ByteStream buildCommand_get();

        //Function: buildCommand_set
        //    Builds the bytes for the "set" command. 
        //
        //Parameters:
        //    enableAssistedFix -  boolean value.  If true, enables assisted fix.
        //
        //Returns:
        //    A <ByteStream> containing the GNSS_AssistedFixControl command packet
        static ByteStream buildCommand_set(bool enableAssistedFix);

        //Class: Response
        //    Handles the response to the GNSS Assisted Fix Control command.
        class Response : public GenericMipCommand::Response
        {
        protected:
            //Function: fieldDataByte
            //    Gets the data field descriptor byte
            virtual uint8 fieldDataByte() const    override { return FIELD_DATA_BYTE; }

        public:
            //Constructor: Response
            //    Creates a GNSS Assisted Fix Control Response object
            //
            //Parameters:
            //    collector - The <ResponseCollector> used to register and unregister the response
            Response(std::weak_ptr<ResponseCollector> collector, bool ackNackExpected, bool dataResponseExpected);

            //Function: parseResponse
            //    Parses the response, getting the data rate base result
            //
            //Parameters:
            //    response - The <GenericMipCmdResponse> holding the response to parse
            //
            //Returns:
            //    The data rate base result
            bool parseResponse(const GenericMipCmdResponse& response) const;
        };
    };

#endif
}

