/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/ResponsePattern.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "MipCmdResponse.h"

namespace mscl
{
    //Title: GenericMipCommand

    //Class: GenericMipCmdResponse
    //    Represents the response to a GenericMipCommand.
    //
    //See Also:
    //    <MipCmdResponse>
    class GenericMipCmdResponse : public MipCmdResponse
    {
    public:
        //Constructor: GenericMipCmdResponse
        //    Creates a GenericMipCmdResponse with default values.
        GenericMipCmdResponse();

    private:
        //Constructor: GenericMipCmdResponse
        //    Creates a GenericMipCmdResponse with the given parameters.
        //
        //Parameters:
        //    state - The state of the response.
        //    success - Whether or not the command was a success.
        //    errorCode - The MIP Ack/Nack error code received.
        //    cmdName - The name of the command.
        //    data - The <ByteStream> that holds the result data from the response (if any).
        GenericMipCmdResponse(ResponsePattern::State state, bool success, MipPacket::MipAckNack errorCode, std::string cmdName, ByteStream data);

#ifndef SWIG
    public:
        //Function: ResponseSuccess
        //    Creates a GenericMipCmdResponse with a successful response.
        //
        //Parameters:
        //    cmdName - The name of the command.
        //    data - The <ByteStream that holds the data from the response (if any).
        //
        //Returns:
        //    A <GenericMipCmdResponse> representing a success response from the command.
        static GenericMipCmdResponse ResponseSuccess(const std::string& cmdName, ByteStream data = ByteStream());

        //Function: ResponseFail
        //    Creates a GenericMipCmdResponse with a fail response.
        //
        //Parameters:
        //    errorState - The state that caused the ResponseFail.
        //    errorCode - The MIP Ack/Nack error code to set with the ResponseFail.
        //    cmdName - The name of the command.
        //
        //Returns:
        //    A <GenericMipCmdResponse> representing a failed response from the command.
        static GenericMipCmdResponse ResponseFail(ResponsePattern::State errorState, MipPacket::MipAckNack errorCode, const std::string& cmdName);
#endif

    private:
        //Variable: m_data
        //    The <ByteStream that holds the data received from the response, if any.
        ByteStream m_data;

    public:
        //Function: data
        //    Gets the data that was received from the response, if any.
        //
        //Returns:
        //    A <ByteStream> that contains the data received from the response, if any.
        ByteStream data() const;
    };



    //Class: GenericMipCommand
    //    Represents a base class for MIP commands
    class GenericMipCommand
    {
    protected:
        static const uint8 FIELD_ACK_NACK_BYTE = 0xF1;

    protected:
        GenericMipCommand() {}  //disabled default constructor

    private:
        GenericMipCommand(const GenericMipCommand&);                //disabled copy constructor
        GenericMipCommand& operator=(const GenericMipCommand&);    //disabled assignment operator

    public:
        virtual ~GenericMipCommand(){};

    public:
        //Function: buildCommand
        //    Builds the command for a MIP command, and returns a ByteStream containing the bytes to send
        //
        //Parameters:
        //    descSetByte - The descriptor set byte for the command
        //    cmdByte - The command (field) byte for the command
        //    fieldData - A vector of bytes that make up the field data to be sent in the command (defaults to empty)
        //
        //Returns:
        //    A <ByteStream> containing the MIP command packet built from the given bytes
        static ByteStream buildCommand(uint8 descSetByte, uint8 cmdByte, const Bytes& fieldData = Bytes());

        //Function: buildCommand
        //    Builds the command for a MIP command, and returns a ByteStream containing the bytes to send
        //
        //Parameters:
        //    commandId - The <MipTypes::Command> for the command
        //    fieldData - A vector of bytes that make up the field data to be sent in the command (defaults to empty)
        //
        //Returns:
        //    A <ByteStream> containing the MIP command packet built from the given bytes
        static ByteStream buildCommand(MipTypes::Command commandId, const Bytes& fieldData = Bytes());

        //Function: buildCommand
        //    Builds the command for a derived MIP command, and returns a ByteStream containing the bytes to send
        //
        //Parameters:
        //    fieldData - A vector of bytes that make up the field data to be sent in the command (defaults to empty)
        //
        //Returns:
        //    A <ByteStream> containing the MIP command packet built from the given bytes
        ByteStream buildCommand(const Bytes& fieldData = Bytes());

        //Function: fieldId
        //    Gets the <MipTypes::Command>
        virtual MipTypes::Command commandId() const = 0;

        //Class: Response
        //    Handles the response to the MIP command
        class Response : public ResponsePattern
        {
            friend class MipNode_Impl;

        protected:
            //Variable: m_ackNackResponse
            //    Whether or not an ack/nack response field is expected
            bool m_ackNackResponse;

            //Variable: m_dataResponse
            //    Whether or not a data response field is expected
            bool m_dataResponse;

            //Variable: m_command
            //    The command enumeration
            const MipTypes::Command m_command;

            //Variable: m_commandName
            //    The name of the command
            std::string m_commandName;

            //Variable: m_fieldDataByte
            //    The field data byte.
            uint8 m_fieldDataByte;

            //Variable: m_result
            //    The <GenericMipCmdResponse> that holds the result of the GenericMipCommand
            GenericMipCmdResponse m_result;

        protected:
            //Function: commandId
            //    Gets the <MipTypes::Command> for the MIP command
            virtual MipTypes::Command commandId() const { return m_command; }

            //Function: fieldDataByte
            //    Gets the data field byte that should be received with the data field (if any)
            virtual uint8 fieldDataByte() const;

            //Function: descSetByte
            //    Gets the descriptor set byte for the MIP command
            uint8 descSetByte() const;

            //Function: cmdByte
            //    Gets the command byte for the MIP command
            uint8 cmdByte() const;

            //Function: fieldAckNackByte
            //    Gets the ack/nack byte that should be received with the ack/nack field
            uint8 fieldAckNackByte() const;

        public:
            //Default Constructor: Response
            //    Creates a default constructor Response.
            //    Note: You will need to use the <setResponseCollector> function before being used.
            //
            //Parameters:
            //    ackNackResponse - Whether or not an ack/nack response field is expected
            //    dataResponse - Whether or not a data response field is expected
            //    cmdName - The name of the command (to be used in exceptions that may be thrown)
            Response(const MipTypes::Command&, bool ackNackResponse, bool dataResponse, std::string cmdName);

            //Constructor: Response
            //    Creates a Response object
            //
            //Parameters:
            //    collector - The <ResponseCollector> used to register and unregister the response
            //    ackNackResponse - Whether or not an ack/nack response field is expected
            //    dataResponse - Whether or not a data response field is expected
            //    cmdName - The name of the command (to be used in exceptions that may be thrown)
            Response(const MipTypes::Command&, std::weak_ptr<ResponseCollector> collector, bool ackNackResponse,
                     bool dataResponse, const std::string& cmdName, uint8 fieldDataByte = 0);

            virtual ~Response(){};

        public:
            //Function: match
            //    Checks if the <MipDataField> passed in matches the expected response pattern's bytes
            //
            //Parameters:
            //    field - The <MipDataField> in which to try to find the pattern
            //
            //Returns:
            //    true if the packet matches a response pattern, false otherwise
            virtual bool match(const MipDataField& field) override;

            //Function: match_ackNack
            //    Checks if the <MipDataField> matches the ACK/NACK field for this command (if one is even expected)
            //
            //Parameters:
            //    field - The <MipDataField> in which to try to find the pattern
            //
            //Returns:
            //    true if the packet matches the expected response pattern, false otherwise
            bool match_ackNack(const MipDataField& field);

            //Function: match_data
            //    Checks if the <MipDataField> matches the data field for this command (if one is even expected)
            //
            //Parameters:
            //    field - The <MipDataField> in which to try to find the pattern
            //
            //Returns:
            //    true if the packet matches the expected response pattern, false otherwise
            virtual bool match_data(const MipDataField& field);

            //Function: wait
            //    Waits for a certain amount of time for the response pattern to be matched
            //
            //Parameters:
            //    timeout - The maximum time (in milliseconds) to wait until the command times out and returns, if not found first
            //
            //Returns:
            //    true if the response pattern was matched, false otherwise
            bool wait(uint64 timeout);

            //Function: result
            //    Gets the <GenericMipCmdResponse> that holds the result of the response
            //
            //Returns:
            //    A <GenericMipCmdResponse> that holds the result of the response
            GenericMipCmdResponse result();
        };
    };
}