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
        void establishConnection() override {}

    public:
        std::string description() override { return "Mock Connection"; }

        Connection::ConnectionType type() override { return Connection::connectionType_serial; }

        void disconnect() override {}

        void reconnect() override {}

        void registerParser(std::function<void(DataBuffer&)> parseFunction) override {  (void)parseFunction; }

        void unregisterParser() override {}

        void throwIfError() override {}

        void write(const ByteStream& data) const override { (void)data; }

        void write(const Bytes& bytes) const override { (void)bytes; }

        void clearBuffer() override {}

        std::size_t byteReadPos() const override { return 0; }

        std::size_t byteAppendPos() const override { return 0; }

        void rawByteMode(bool enable) override { (void)enable; }

        bool rawByteMode() override { return false; }

        void getRawBytes(Bytes& bytes, uint32 timeout = 0, uint32 maxBytes = 0, uint32 minBytes = 0) override
        {
            (void)bytes;
            (void)timeout;
            (void)maxBytes;
            (void)minBytes;
        }

        void getRawBytesWithPattern(Bytes& bytes, const uint8* pattern, size_t length, uint32 timeout = 0) override
        {
            (void)bytes;
            (void)pattern;
            (void)length;
            (void)timeout;
        }

        void debugMode(bool enable) override { (void)enable; }

        bool debugMode() override { return false; }

        void getDebugData(ConnectionDebugDataVec& data, uint32 timeout) override { (void)data; (void)timeout; }

        std::string port() const override { return ""; }
    };
} // namespace mscl
