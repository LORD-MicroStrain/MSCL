/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/MIP/Packets/MipFieldParser.h"

namespace mscl
{
    //Title: MipFieldParser_Displacement

    class MipDataField;

    //Class: FieldParser_RawPosition
    //    The Field Parser for raw position (ADC counts) data
    class FieldParser_RawPosition : public MipFieldParser
    {
        FieldParser_RawPosition() = default;    //default constructor disabled

    public:
        void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_Position
    //    The Field Parser for displacement position (mm) data
    class FieldParser_Position : public MipFieldParser
    {
        FieldParser_Position() {}    //default constructor disabled

    public:
        void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };
}
