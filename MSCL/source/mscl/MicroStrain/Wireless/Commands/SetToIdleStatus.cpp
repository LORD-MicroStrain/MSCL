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
#include "SetToIdleStatus.h"
#include "SetToIdle.h"

namespace mscl
{
	SetToIdleStatus::SetToIdleStatus(std::shared_ptr<SetToIdle::Response> response) :
		m_response(response),
		m_complete(false)
	{
	}

	SetToIdleStatus::SetToIdleResult SetToIdleStatus::result()
	{
		return m_response->result();
	}

	bool SetToIdleStatus::complete(uint64 timeout) //timeout = 10
	{
		//if it hasn't already been known that it completed
		if(!m_complete)
		{
			//perform a wait on the response object for the specified timeout
			m_complete = m_response->wait(timeout);
		}
		
		//return the result
		return m_complete;
	}

	void SetToIdleStatus::cancel()
	{
		m_response->cancel();
	}
}