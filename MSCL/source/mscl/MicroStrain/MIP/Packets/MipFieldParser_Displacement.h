/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include <boost/utility/binary.hpp>

#include "mscl/MicroStrain/MIP/Packets/MipFieldParser.h"
#include "mscl/MicroStrain/MIP/Packets/MipDataPacket.h"

namespace mscl
{
    //Title: MipFieldParser_Displacement

    class MipDataField;

    //Class: FieldParser_RawPosition
    //    The Field Parser for raw position (ADC counts) data
    class FieldParser_RawPosition: public MipFieldParser
    {
    private:
        FieldParser_RawPosition() {};    //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };

    //Class: FieldParser_Position
    //    The Field Parser for displacement position (mm) data
    class FieldParser_Position : public MipFieldParser
    {
    private:
        FieldParser_Position(){};    //default constructor disabled

    public:
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;
        static bool registerParser();

    public:
        static const MipTypes::ChannelField FIELD_TYPE;
        static const bool REGISTERED;
    };
}