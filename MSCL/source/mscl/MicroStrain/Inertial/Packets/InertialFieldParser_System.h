/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/MIP/Packets/MipFieldParser.h"

namespace mscl
{
    //Title: InertialFieldParser_System

    class MipDataField;

    //Class: MipSystemFieldParser
    //    The base class for all System field parsers
    //    Handles registering the parser for the same field across all System data sets
    class MipSystemFieldParser : public MipFieldParser
    {
    protected:
        // Default constructor disabled
        MipSystemFieldParser() {}
        virtual ~MipSystemFieldParser() {}

    private:
        // Copy constructor disabled
        MipSystemFieldParser(const MipSystemFieldParser&);

    protected:
        static bool registerSystemParser(MipTypes::ChannelField chField, const MipFieldParser* parser);
    };
}