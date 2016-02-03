/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "InertialCmdResponse.h"
#include "mscl/Exceptions.h"

namespace mscl
{
    InertialCmdResponse::InertialCmdResponse() :
        m_responseState(ResponsePattern::STATE_WAITING),
        m_success(false),
        m_ackNack(InertialPacket::MIP_ACK_NACK_ERROR_NONE),
        m_commandName("Inertial")
    {
    }

    InertialCmdResponse::InertialCmdResponse(ResponsePattern::State state, bool success, InertialPacket::MipAckNack errorCode, std::string cmdName):
        m_responseState(state),
        m_success(success),
        m_ackNack(errorCode),
        m_commandName(cmdName)
    {
    }

    void InertialCmdResponse::throwIfFailed()
    {
        //check the current response state
        switch(m_responseState)
        {
            //if the state is Timeout
            case ResponsePattern::STATE_FAIL_TIMEOUT:
                throw Error_Communication();
                break;

            //if the state is Fail
            case ResponsePattern::STATE_FAIL:
                throw Error_InertialCmdFailed(m_ackNack, "The " + m_commandName + " command has failed.");
                break;

            //if the state is Success or anything else
            case ResponsePattern::STATE_SUCCESS:
            default:
                //do nothing
                break;
        }
    }

    bool InertialCmdResponse::success() const
    {
        return m_success;
    }

    InertialPacket::MipAckNack InertialCmdResponse::errorCode() const
    {
        return m_ackNack;
    }
}