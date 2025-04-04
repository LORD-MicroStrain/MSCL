/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"
#include "mscl/MicroStrain/SampleRate.h"

namespace mscl
{
    //Class: DisplacementOutputDataRate
    //    Contains the logic for the DisplacementOutputDataRate command.
    class DisplacementOutputDataRate : GenericMipCommand
    {
        DisplacementOutputDataRate() {}                //default constructor disabled

         //Constants: Packet Bytes
         // FIELD_DATA_BYTE - Descriptor byte for the Field data.
        static const uint8 FIELD_DATA_BYTE = 0x82;

    public:
        ~DisplacementOutputDataRate() override = default;

        static ByteStream buildCommand_get();

        class Response : public GenericMipCommand::Response
        {
        protected:
            uint8 fieldDataByte() const override { return FIELD_DATA_BYTE; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector, bool dataResponseExpected);

            SampleRate parseResponse(const GenericMipCmdResponse& response) const;
        };
    };
} // namespace mscl
