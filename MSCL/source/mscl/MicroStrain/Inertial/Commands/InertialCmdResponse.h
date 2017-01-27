/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/MicroStrain/ResponsePattern.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacket.h"

namespace mscl
{
    //API Class: InertialCmdResponse
    //    Represents the response to a generic InertialNode command
    class InertialCmdResponse
    {
    public:
        //Constructor: InertialCmdResponse
        //    Creates an InertialCmdResponse with default values
        InertialCmdResponse();

        virtual ~InertialCmdResponse(){};    //virtual destructor

    protected:
        //Constructor: InertialCmdResponse
        //    Creates an InertialCmdResponse with the given parameters
        //
        //Parameters:
        //    state - The state of the response
        //    success - Whether or not the response was a success
        //    errorCode - The MIP Ack/Nack error code received
        //    cmdName - The name of the command that this response corresponds to
        InertialCmdResponse(ResponsePattern::State state, bool success, InertialPacket::MipAckNack errorCode, std::string cmdName);

    protected:
        //Variable: m_responseState
        //    The state of the response, which determines which exceptions are thrown, if any
        ResponsePattern::State m_responseState;

        //Variable: m_success
        //    Whether or not the response was a success
        bool m_success;

        //Variable: m_ackNack
        //    The MIP ack/nack that was received with the packet
        InertialPacket::MipAckNack m_ackNack;

        //Variable: m_commandName
        //    The name of the command that this response corresponds to (to be used in error descriptions)
        std::string m_commandName;

    public:
        //Function: throwIfFailed
        //    Throws an exeption if the response was a failure.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        void throwIfFailed();

        //API Function: success
        //    Gets whether or not the command was a success. 
        //
        //Returns:
        //    true if the command was a success, false otherwise
        //
        //Exceptions:
        //    - <Error>: The function was called before there was a response to the command (uninitialized)
        virtual bool success() const;

        //API Function: errorCode
        //    Gets the MIP ack/nack error code that was returned
        //
        //Returns:
        //    The MIP ack/nack error code as a <InertialPacket::MipAckNack>
        virtual InertialPacket::MipAckNack errorCode() const;
    };


}