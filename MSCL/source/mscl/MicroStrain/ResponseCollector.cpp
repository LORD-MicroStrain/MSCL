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
#include "ResponseCollector.h"
#include "ResponsePattern.h"
#include "DataBuffer.h"

#include "Wireless/Packets/WirelessPacket.h"
#include "Inertial/InertialDataField.h"

namespace mscl
{
	void ResponseCollector::registerResponse(ResponsePattern* response)
	{
		//get a lock on the response mutex
		mutex_lock_guard lock(m_responseMutex);

		//add the ResponsePattern to the vector of expected responses
		m_expectedResponses.push_back(response);
	}

	void ResponseCollector::unregisterResponse(ResponsePattern* response)
	{
		//get a lock on the response mutex
		mutex_lock_guard lock(m_responseMutex);

		//find the ResponsePattern in the vector of expected responses
		auto pos = std::find(m_expectedResponses.begin(), m_expectedResponses.end(), response);

		//if we didn't find the ResponsePattern in the vector of responses
		if(pos == m_expectedResponses.end())
		{
			return;
		}

		//remove the response from the vector 
		m_expectedResponses.erase(pos);
	}

	bool ResponseCollector::waitingForResponse()
	{
		//get a lock on the response mutex
		mutex_lock_guard lock(m_responseMutex);

		return !m_expectedResponses.empty();
	}

	bool ResponseCollector::matchExpected(DataBuffer& data)
	{
		//make a save point so we can revert if need be
		ReadBufferSavePoint savepoint(&data);

		size_t startBytesRemaining = 0;

		//get a lock on the response mutex
		mutex_lock_guard lock(m_responseMutex);

		//need to loop over all of the bytes to check for responses
		while(data.moreToRead())
		{
			//log the bytes remaining in the data before we attempt to match
			startBytesRemaining = data.bytesRemaining();

			//look through all the expected responses
			for(auto itr = m_expectedResponses.begin(); itr < m_expectedResponses.end(); itr++)
			{
				//if we found a match
				if((*itr)->match(data))
				{
					//match functions move the data pointer on success (even if not fully matched)
					//need to make sure we don't roll back to our previous savepoint.
					savepoint.commit();

					if((*itr)->fullyMatched())
					{
						//unregister the response
						m_expectedResponses.erase(itr);

						return true;
					}
				}

				//if any match function moved the data pointer, we don't want to move it back here
				if(startBytesRemaining != data.bytesRemaining())
				{
					savepoint.commit();
				}
			}

			//if we can move to the next byte and the byte position hasn't been moved elsewhere (internally by a match function).
			if(data.moreToRead() && startBytesRemaining == data.bytesRemaining())
			{
				//move to the next byte and check for the response again
				data.read_uint8();
			}
		}

		return false;
	}

	bool ResponseCollector::matchExpected(const WirelessPacket& packet)
	{
		//get a lock on the response mutex
		mutex_lock_guard lock(m_responseMutex);

		//look through all the expected responses
		for(auto itr = m_expectedResponses.begin(); itr < m_expectedResponses.end(); itr++)
		{
			//if we found a match
			if((*itr)->match(packet))
			{
				if((*itr)->fullyMatched())
				{
					//unregister the response
					m_expectedResponses.erase(itr);

					return true;
				}
			}
		}

		return false;
	}

	bool ResponseCollector::matchExpected(InertialDataField& field)
	{
		//get a lock on the response mutex
		mutex_lock_guard lock(m_responseMutex);

		//look through all the expected responses
		for(auto itr = m_expectedResponses.begin(); itr < m_expectedResponses.end(); itr++)
		{
			//if we found a match
			if((*itr)->match(field))
			{
				if( (*itr)->fullyMatched() )
				{
					//unregister the response
					m_expectedResponses.erase(itr);

					return true;
				}
			}
		}

		return false;
	}
}