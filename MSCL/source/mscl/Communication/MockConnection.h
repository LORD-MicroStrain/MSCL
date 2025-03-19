/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/Communication/Connection_Impl.h"

namespace mscl
{
    //Class: MockConnection
    //    A <Connection_Impl_Base> derived class for creating a Mock connection.
    class MockConnection final : public Connection_Impl_Base
    {
        MockConnection(const MockConnection&) = delete;             //copy constructor disabled
        MockConnection& operator=(const MockConnection&) = delete;  //assignment operator disabled

    public:
        //Constructor: MockConnection
        //    Initializes the MockConnection object.
        MockConnection() {}

        //Destructor: ~MockConnection
        //    Destroys the MockConnection object
        ~MockConnection() override {}

    protected:
        void establishConnection() override { return; }

    public:
        std::string description() override { return "Mock Connection"; }

        Connection::ConnectionType type() override { return Connection::connectionType_serial; }

        void disconnect() override { return; }

        void reconnect() override { return; }

        void registerParser(std::function<void(DataBuffer&)> parseFunction) override { return; }

        void unregisterParser() override { return; }

        void throwIfError() override { return; }

        void write(const ByteStream& data) const override { return; }

        void write(const Bytes& bytes) const override { return; }

        void clearBuffer() override { return; }

        std::size_t byteReadPos() const override { return 0; }

        std::size_t byteAppendPos() const override { return 0; }

        void rawByteMode(bool enable) override { return; }

        bool rawByteMode() override { return false; }

        void getRawBytes(Bytes& bytes, uint32 timeout = 0, uint32 maxBytes = 0, uint32 minBytes = 0) override { return; }

        void getRawBytesWithPattern(Bytes& bytes, const uint8* pattern, size_t length, uint32 timeout = 0) override { return; }

        void debugMode(bool enable) override { return; }

        bool debugMode() override { return false; }

        void getDebugData(ConnectionDebugDataVec& data, uint32 timeout) override { return; }

        std::string port() const override { return ""; }
    };
} // namespace mscl
