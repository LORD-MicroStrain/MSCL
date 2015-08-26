/*****************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the included
LICENSE.txt file for a copy of the full GNU General Public License.
*****************************************************************************/
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
				throw Error_Timeout();
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