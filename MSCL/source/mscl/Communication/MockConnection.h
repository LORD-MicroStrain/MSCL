/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "Connection_Impl.h"

namespace mscl
{
    //Class: MockConnection
    //    A <Connection_Impl_Base> derived class for creating a Mock connection.
    class MockConnection final : public Connection_Impl_Base
    {
    private:
        MockConnection(const MockConnection&) = delete;             //copy constructor disabled
        MockConnection& operator=(const MockConnection&) = delete;  //assignment operator disabled

    public:
        //Constructor: MockConnection
        //    Initializes the MockConnection object.
        MockConnection() {}

        //Destructor: ~MockConnection
        //    Destroys the MockConnection object
        virtual ~MockConnection() {}

    protected:
        virtual void establishConnection() override { return; }

    public:
        virtual std::string description() override { return "Mock Connection"; }

        virtual Connection::ConnectionType type() override { return Connection::connectionType_serial; };

        virtual void disconnect() override { return; }

        virtual void reconnect() override { return; }

        virtual void registerParser(std::function<void(DataBuffer&)> parseFunction) override { return; }

        virtual void unregisterParser() override { return; }

        virtual void throwIfError() override { return; }

        virtual void write(const ByteStream& data) const override { return; }

        virtual void write(const Bytes& bytes) const override { return; }

        virtual void clearBuffer() override { return; }

        virtual std::size_t byteReadPos() const override { return 0; }

        virtual std::size_t byteAppendPos() const override { return 0; }

        virtual void rawByteMode(bool enable) override { return; }

        virtual bool rawByteMode() override { return false; }

        virtual void getRawBytes(Bytes& bytes, uint32 timeout = 0, uint32 maxBytes = 0, uint32 minBytes = 0) override { return; }

        virtual void getRawBytesWithPattern(Bytes& bytes, const uint8* pattern, size_t length, uint32 timeout = 0) override { return; }

        virtual void debugMode(bool enable) override { return; }

        virtual bool debugMode() override { return false; }

        virtual void getDebugData(ConnectionDebugDataVec& data, uint32 timeout) override { return; }
    };

}