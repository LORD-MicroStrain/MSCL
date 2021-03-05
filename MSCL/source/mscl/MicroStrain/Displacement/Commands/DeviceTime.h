/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"
#include "mscl/MicroStrain/ResponseCollector.h"

namespace mscl
{
    //Class: DeviceTime
    //    Contains the logic for the DeviceTime command.
    class DeviceTime : private GenericMipCommand
    {
    private:
        DeviceTime() {};                //default constructor disabled
        
         //Constants: Packet Bytes
         // FIELD_DATA_BYTE - Descriptor byte for the Field data.
        static const uint8 FIELD_DATA_BYTE = 0x82;

    public:
        virtual ~DeviceTime() {};

        static ByteStream buildCommand_get(uint64 nanoseconds);

        class Response : public GenericMipCommand::Response
        {
        protected:
            virtual uint8 fieldDataByte() const override { return FIELD_DATA_BYTE; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector, bool dataResponseExpected);
        };
    };
}

