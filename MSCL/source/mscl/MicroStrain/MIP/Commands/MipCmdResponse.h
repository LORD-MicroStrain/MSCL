/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/MicroStrain/ResponsePattern.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacket.h"

namespace mscl
{
    //API Class: MipCmdResponse
    //    Represents the response to a generic InertialNode command
    class MipCmdResponse
    {
    public:
        //Constructor: MipCmdResponse
        //    Creates a MipCmdResponse with default values
        MipCmdResponse();

        virtual ~MipCmdResponse(){};    //virtual destructor

    protected:
        //Constructor: MipCmdResponse
        //    Creates a MipCmdResponse with the given parameters
        //
        //Parameters:
        //    state - The state of the response
        //    success - Whether or not the response was a success
        //    errorCode - The MIP Ack/Nack error code received
        //    cmdName - The name of the command that this response corresponds to
        MipCmdResponse(ResponsePattern::State state, bool success, MipPacket::MipAckNack errorCode, std::string cmdName);

    protected:
        //Variable: m_responseState
        //    The state of the response, which determines which exceptions are thrown, if any
        ResponsePattern::State m_responseState;

        //Variable: m_success
        //    Whether or not the response was a success
        bool m_success;

        //Variable: m_ackNack
        //    The MIP ack/nack that was received with the packet
        MipPacket::MipAckNack m_ackNack;

        //Variable: m_commandName
        //    The name of the command that this response corresponds to (to be used in error descriptions)
        std::string m_commandName;

    public:
        //Function: throwIfFailed
        //    Throws an exeption if the response was a failure.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
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
        //    The MIP ack/nack error code as a <MipPacket::MipAckNack>
        virtual MipPacket::MipAckNack errorCode() const;
    };


}