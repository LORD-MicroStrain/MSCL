/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "MipCmdResponse.h"
#include "mscl/Exceptions.h"

namespace mscl
{
    MipCmdResponse::MipCmdResponse() :
        m_responseState(ResponsePattern::STATE_WAITING),
        m_success(false),
        m_ackNack(MipPacket::MIP_ACK_NACK_ERROR_NONE),
        m_commandName("MIP")
    {
    }

    MipCmdResponse::MipCmdResponse(ResponsePattern::State state, bool success, MipPacket::MipAckNack errorCode, std::string cmdName):
        m_responseState(state),
        m_success(success),
        m_ackNack(errorCode),
        m_commandName(cmdName)
    {
    }

    void MipCmdResponse::throwIfFailed()
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
                throw Error_MipCmdFailed(m_ackNack, "The " + m_commandName + " command has failed. (Error Code: " + Utils::toStr(m_ackNack) + ")");
                break;

            //if the state is Success or anything else
            case ResponsePattern::STATE_SUCCESS:
            default:
                //do nothing
                break;
        }
    }

    bool MipCmdResponse::success() const
    {
        return m_success;
    }

    MipPacket::MipAckNack MipCmdResponse::errorCode() const
    {
        return m_ackNack;
    }
}
