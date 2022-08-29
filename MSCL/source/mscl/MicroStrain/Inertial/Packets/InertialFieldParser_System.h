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

    //Class: FieldParser_BuiltInTest
    //    The Field Parser for continuous built-in test (BIT) results
    class FieldParser_BuiltInTest : public MipFieldParser
    {
        FieldParser_BuiltInTest() {}    //default constructor disabled

    public:
        //Function: parse
        //    Parses a <MipDataField> for <MipDataPoints> and stores them in the valid or invalid result vectors
        //
        //Parameters:
        //    field - The <MipDataField> to parse for data points
        //    result - The <MipDataPoints> vector to store the data points in
        void parse(const MipDataField& field, MipDataPoints& result) const override;

        //Function: registerParser
        //    The static function that registers this parser with the list of parsers (called immediately)
        //
        //Returns:
        //    True, just for assigning the REGISTERED constant to true
        static bool registerParser();

        //Constant: FIELD_TYPE
        //    The 2-byte field type (Descriptor ID + Field ID) for this parser
        static const MipTypes::ChannelField FIELD_TYPE;

        //Constant: REGISTERED
        //    Whether this parser is registered. This will always be true. This is used to call registerParser() immediately
        static const bool REGISTERED;
    };

    //Class: FieldParser_TimeSyncStatus
    //    The Field Parser for time sync status (PPS) data
    class FieldParser_TimeSyncStatus : public MipFieldParser
    {
        FieldParser_TimeSyncStatus() {}    //default constructor disabled
    
    public:
        //Function: parse
        //    Parses a <MipDataField> for <MipDataPoints> and stores them in the valid or invalid result vectors
        //
        //Parameters:
        //    field - The <MipDataField> to parse for data points
        //    result - The <MipDataPoints> vector to store the data points in
        void parse(const MipDataField& field, MipDataPoints& result) const override;

        //Function: registerParser
        //    The static function that registers this parser with the list of parsers (called immediately)
        //
        //Returns:
        //    True, just for assigning the REGISTERED constant to true
        static bool registerParser();

        //Constant: FIELD_TYPE
        //    The 2-byte field type (Descriptor ID + Field ID) for this parser
        static const MipTypes::ChannelField FIELD_TYPE;

        //Constant: REGISTERED
        //    Whether this parser is registered. This will always be true. This is used to call registerParser() immediately
        static const bool REGISTERED;
    };

    //Class: FieldParser_GpioState
    //    The Field Parser for all GPIO pin state data
    class FieldParser_GpioState : public MipFieldParser
    {
        FieldParser_GpioState() {}    //default constructor disabled

    public:
        //Function: parse
        //    Parses a <MipDataField> for <MipDataPoints> and stores them in the valid or invalid result vectors
        //
        //Parameters:
        //    field - The <MipDataField> to parse for data points
        //    result - The <MipDataPoints> vector to store the data points in
        void parse(const MipDataField& field, MipDataPoints& result) const override;

        //Function: registerParser
        //    The static function that registers this parser with the list of parsers (called immediately)
        //
        //Returns:
        //    True, just for assigning the REGISTERED constant to true
        static bool registerParser();

        //Constant: FIELD_TYPE
        //    The 2-byte field type (Descriptor ID + Field ID) for this parser
        static const MipTypes::ChannelField FIELD_TYPE;

        //Constant: REGISTERED
        //    Whether this parser is registered. This will always be true. This is used to call registerParser() immediately
        static const bool REGISTERED;
    };
}