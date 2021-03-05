/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/Inertial/ExposedInertialTypes.h"

namespace mscl
{

#ifndef SWIG

    //Class: GNSS_AssistTimeUpdate
    //    Contains the logic for the Inertial GNSS Assist TimeUpdate command.
    //    It is important to note that this command will get a Nack back every time after the first from power up.
    class GNSS_AssistTimeUpdate : private GenericMipCommand
    {
    protected:
        //Function: CommandId
        //Returns:
        //    MipTypes::Command - the command ID.
        virtual MipTypes::Command commandId() const override { return MipTypes::CMD_GNSS_ASSIST_TIME_UPDATE; }

    public:
        GNSS_AssistTimeUpdate();

        //Constants: Packet Bytes
        //     FIELD_DATA_BYTE - Descriptor byte for the Field data.
        static const uint8 FIELD_DATA_BYTE = 0xA3;

    public:
        virtual ~GNSS_AssistTimeUpdate() {};

        //Function: buildCommand_get
        //    Builds the bytes for the "get" command.
        //Returns:
        //    A <ByteStream> containing the GNSS_AssistTimeUpdate command packet
        ByteStream buildCommand_get();

        //Function: buildCommand_set
        //    Builds the bytes for the "set" command. 
        //
        //Parameters:
        //    FieldData -  The data to set.
        //Returns:
        //    A <ByteStream> containing the GNSS_AssistTimeUpdate command packet
        ByteStream buildCommand_set(const TimeUpdate&);

        //Class: Response
        //    Handles the response to the GNSS_AssistTimeUpdate command.
        class Response : public GenericMipCommand::Response
        {
            //Function: fieldDataByte
            //    Gets the data field descriptor byte
            virtual uint8 fieldDataByte() const    override { return FIELD_DATA_BYTE; }

        public:
            //Constructor: Response
            //    Creates a GNSS_AssistTimeUpdate Response object
            //
            //Parameters:
            //    collector - The <ResponseCollector> used to register and unregister the response
            Response(std::weak_ptr<ResponseCollector> collector, bool ackNackExpected, bool dataResponseExpected);

            //Function: parseResponse
            //    Parses the response, getting the assist time result
            //
            //Parameters:
            //    response - The <GenericMipCmdResponse> holding the response to parse
            //
            //Returns:
            //    The data rate base result
            TimeUpdate parseResponse(const GenericMipCmdResponse& response) const;
        };
    };

#endif
}
