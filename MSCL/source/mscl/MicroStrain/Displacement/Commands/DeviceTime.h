/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"

namespace mscl
{
    //Class: DeviceTime
    //    Contains the logic for the DeviceTime command.
    class DeviceTime : GenericMipCommand
    {
        DeviceTime() {}                //default constructor disabled

         //Constants: Packet Bytes
         // FIELD_DATA_BYTE - Descriptor byte for the Field data.
        static const uint8 FIELD_DATA_BYTE = 0x82;

    public:
        ~DeviceTime() override = default;

        static ByteStream buildCommand_get(uint64 nanoseconds);

        class Response : public GenericMipCommand::Response
        {
        protected:
            uint8 fieldDataByte() const override { return FIELD_DATA_BYTE; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector, bool dataResponseExpected);
        };
    };
} // namespace mscl
