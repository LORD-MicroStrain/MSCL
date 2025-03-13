/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

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
    loadBaseInfoResponse.append_uint8(0x73);    //command id
    loadBaseInfoResponse.append_uint16(13);        //frequency
    loadBaseInfoResponse.append_uint16(loadBaseInfoResponse.calculateSimpleChecksum(1, 2));    //checksum
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
    mutable std::function<void(DataBuffer&)> parseFunc;
    mutable std::vector<DataBuffer> writeResponses;
    mutable size_t responseItr;
    uint16_t delay;    //in ms
    bool useDelay;

private:
    virtual void registerParser(std::function<void(DataBuffer&)> parseFunction)
    {
        parseFunc = parseFunction;
    }

    virtual void unregisterParser(){}
    virtual void throwIfError(){}
    virtual std::string description(){return "";}
    virtual Connection::ConnectionType type() { return Connection::connectionType_serial; }

    virtual void write(const ByteStream& data) const
    {
        parseNextResponse();
    }

    virtual void write(const Bytes& bytes) const
    {
        parseNextResponse();
    }

    virtual void clearBuffer() {}

    virtual void disconnect() {}
    virtual void reconnect() {}
    virtual void establishConnection() {}

    virtual std::size_t byteReadPos() const
    {
      return 0;
    }

    virtual std::size_t byteAppendPos() const
    {
      return 0;
    }

    virtual void rawByteMode(bool enable){}
    virtual bool rawByteMode() { return false; }
    virtual void getRawBytes(Bytes& bytes, uint32 timeout = 0, uint32 maxBytes = 0, uint32 minBytes = 0) {};
    virtual void getRawBytesWithPattern(Bytes& bytes, const uint8* pattern, size_t length, uint32 timeout = 0) {};
    virtual void debugMode(bool enable) {};
    virtual bool debugMode() { return false; };
    virtual void getDebugData(ConnectionDebugDataVec& data, uint32 timeout) {};

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

    void parseNextResponse() const
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

    std::string port() const override { return ""; }
};

static Connection makeConnectionWithMockImpl()
{
    static std::shared_ptr<Connection_Impl_Base> impl(new mockConnectionImpl);
    return Connection(impl);
}
