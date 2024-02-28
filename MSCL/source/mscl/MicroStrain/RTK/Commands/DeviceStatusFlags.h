/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"
#include "mscl/MicroStrain/Inertial/ExposedInertialTypes.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/SampleRate.h"


namespace mscl
{
    //Class: DeviceStatusFlags
    //    Contains the logic for the DeviceStatusFlags command.
    class DeviceStatusFlags : private GenericMipCommand
    {
    private:
        DeviceStatusFlags() {};                //default constructor disabled

         //Constants: Packet Bytes
         // FIELD_DATA_BYTE - Descriptor byte for the Field data.
        static const uint8 FIELD_DATA_BYTE = 0x81;

    public:
        virtual ~DeviceStatusFlags() {};

        static ByteStream buildCommand_get();

        class Response : public GenericMipCommand::Response
        {
        protected:
            virtual uint8 fieldDataByte() const override { return FIELD_DATA_BYTE; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector);

            RTKDeviceStatusFlags parseResponse(const GenericMipCmdResponse& response) const;
        };
    };
}
