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
#pragma once

#include <memory>
#include "mscl/Communication/Connection.h"
#include "mscl/Communication/Connection_Impl.h"
#include "mscl/MicroStrain/DataBuffer.h"

#include <turtle/mock.hpp>
using namespace mscl;

static ByteStream loadBaseInfoResponse()
{
	ByteStream loadBaseInfoResponse;
	loadBaseInfoResponse.append_uint8(0x73);	//command id
	loadBaseInfoResponse.append_uint16(13);		//frequency
	loadBaseInfoResponse.append_uint16(loadBaseInfoResponse.calculateSimpleChecksum(1, 2));	//checksum
	return loadBaseInfoResponse;
}

//creating a mockConnection class to give to our mockBaseStation
class mockConnectionImpl : public Connection_Impl_Base
{
public:
	mockConnectionImpl():
		responseItr(0),
		delay(0),
		useDelay(false)
	{
	}

private:
	std::function<void(DataBuffer&)> parseFunc;
	std::vector<DataBuffer> writeResponses;
	size_t responseItr;
	uint16_t delay;	//in ms
	bool useDelay;

private:
	virtual void registerParser(std::function<void(DataBuffer&)> parseFunction)
	{
		parseFunc = parseFunction;
	}

	virtual void unregisterParser(){}
	virtual void throwIfError(){}
	virtual std::string description(){return "";}

	virtual void write(const ByteStream& data)
	{
		parseNextResponse();
	}

	virtual void write(const Bytes& bytes)
	{
		parseNextResponse();
	}

	virtual void clearBuffer() {}

	virtual void disconnect() {}
	virtual void reconnect() {}
	virtual void establishConnection() {}

	virtual void rawByteMode(bool enable){}
	virtual void getRawBytes(Bytes& bytes, uint32 timeout = 0, uint32 maxBytes = 0) {};

public:
	void setResponseBytes(ByteStream response)
	{
		writeResponses.clear();
		writeResponses.push_back(DataBuffer(response));
	}

	void setResponseBytes(std::vector<ByteStream> responses)
	{
		writeResponses.clear();
		for(size_t itr = 0; itr < responses.size(); ++itr)
		{
			writeResponses.push_back(DataBuffer(responses.at(itr)));
		}
	}

	void setResponseBytesWithDelay(std::vector<ByteStream> responses, uint16_t msDelay)
	{
		delay = msDelay;
		useDelay = true;

		setResponseBytes(responses);
	}

	void parseNextResponse()
	{
		if((responseItr + 1) <= writeResponses.size())
		{
			//send the data that we want to be the response
			parseFunc(writeResponses.at(responseItr));

			responseItr++;
		}

		//if we are at the end of the responses vector
		if(responseItr == writeResponses.size())
		{
			//empty out the responses and start back at 0
			responseItr = 0;
			writeResponses.clear();
		}
		else
		{
			//if we are using the delay
			if(useDelay)
			{
				//sleep and then call this function again to parse the next response
				std::this_thread::sleep_for(std::chrono::milliseconds(delay));
				parseNextResponse();
			}
		}
	}
};

static Connection makeConnectionWithMockImpl()
{
	static std::shared_ptr<Connection_Impl_Base> impl(new mockConnectionImpl);
	return Connection(impl);
}