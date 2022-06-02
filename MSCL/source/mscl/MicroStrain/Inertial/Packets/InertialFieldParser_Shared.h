/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#pragma once

#include <boost/utility/binary.hpp>

#include "mscl/MicroStrain/MIP/Packets/MipFieldParser.h"
#include "mscl/MicroStrain/MIP/Packets/MipDataPacket.h"

namespace mscl
{
    //Title: InertialFieldParser_Shared

    class MipDataField;

    //Class: MipSharedFieldParser
    //    The base class for all Shared field parsers - handles registering the parser for the same field across all Shared data sets
    class MipSharedFieldParser : public MipFieldParser
    {
    protected:
        MipSharedFieldParser() {};                //default constructor disabled
        virtual ~MipSharedFieldParser() {};

    private:
        MipSharedFieldParser(const MipSharedFieldParser&);                //copy constructor disabled

    protected:
        static bool registerSharedParser(MipTypes::ChannelField chField, const MipFieldParser* parser);
    };

    //Class: FieldParser_EventSource
    //    The field parser for Event Source
    class FieldParser_EventSource : public MipSharedFieldParser
    {
    private:
        FieldParser_EventSource() {};        //default constructor disabled

    public:
        //Function: parse
        //    Parses an <MipDataField> for <MipDataPoints> and stores them in the valid or invalid result vectors
        //
        //Parameters:
        //    field - The <MipDataField> to parse for data points
        //    result - The <MipDataPoints> vector to store the data points in
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;

        //Function: registerParser
        //    The static function that registers this parser with the list of parsers (called immediately)
        //
        //Returns:
        //    true, just for assigning the REGISTERED constant to true
        static bool registerParser();

    public:
        //Constant: FIELD_TYPE
        //    The 2-byte field type (Descriptor ID + Field ID) for this parser
        static const MipTypes::ChannelField FIELD_TYPE;

        //Constant: REGISTERED
        //    Whether this parser is registered. This will always be true. This is used to call registerParser() immediately
        static const bool REGISTERED;
    };

    //Class: FieldParser_Ticks
    //    The field parser for Ticks
    class FieldParser_Ticks : public MipSharedFieldParser
    {
    private:
        FieldParser_Ticks() {};        //default constructor disabled

    public:
        //Function: parse
        //    Parses an <MipDataField> for <MipDataPoints> and stores them in the valid or invalid result vectors
        //
        //Parameters:
        //    field - The <MipDataField> to parse for data points
        //    result - The <MipDataPoints> vector to store the data points in
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;

        //Function: registerParser
        //    The static function that registers this parser with the list of parsers (called immediately)
        //
        //Returns:
        //    true, just for assigning the REGISTERED constant to true
        static bool registerParser();

    public:
        //Constant: FIELD_TYPE
        //    The 2-byte field type (Descriptor ID + Field ID) for this parser
        static const MipTypes::ChannelField FIELD_TYPE;

        //Constant: REGISTERED
        //    Whether this parser is registered. This will always be true. This is used to call registerParser() immediately
        static const bool REGISTERED;
    };

    //Class: FieldParser_DeltaTicks
    //    The field parser for Delta Ticks
    class FieldParser_DeltaTicks : public MipSharedFieldParser
    {
    private:
        FieldParser_DeltaTicks() {};        //default constructor disabled

    public:
        //Function: parse
        //    Parses an <MipDataField> for <MipDataPoints> and stores them in the valid or invalid result vectors
        //
        //Parameters:
        //    field - The <MipDataField> to parse for data points
        //    result - The <MipDataPoints> vector to store the data points in
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;

        //Function: registerParser
        //    The static function that registers this parser with the list of parsers (called immediately)
        //
        //Returns:
        //    true, just for assigning the REGISTERED constant to true
        static bool registerParser();

    public:
        //Constant: FIELD_TYPE
        //    The 2-byte field type (Descriptor ID + Field ID) for this parser
        static const MipTypes::ChannelField FIELD_TYPE;

        //Constant: REGISTERED
        //    Whether this parser is registered. This will always be true. This is used to call registerParser() immediately
        static const bool REGISTERED;
    };

    //Class: FieldParser_GpsTimestamp
    //    The field parser for GPS Timestamp
    class FieldParser_GpsTimestamp : public MipSharedFieldParser
    {
    private:
        //Constants: Valid Flags
        //    TOW_VALID        - b00000001 - The flag position for checking the GPS Time of Week flag
        //    WEEK_NUM_VALID   - b00000010 - The flag position for checking the GPS Week Number flag
        static const uint16 TOW_VALID = BOOST_BINARY(00000001);
        static const uint16 WEEK_NUM_VALID = BOOST_BINARY(00000010);
    
    private:
        FieldParser_GpsTimestamp() {};        //default constructor disabled

    public:
        //Function: parse
        //    Parses an <MipDataField> for <MipDataPoints> and stores them in the valid or invalid result vectors
        //
        //Parameters:
        //    field - The <MipDataField> to parse for data points
        //    result - The <MipDataPoints> vector to store the data points in
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;

        //Function: registerParser
        //    The static function that registers this parser with the list of parsers (called immediately)
        //
        //Returns:
        //    true, just for assigning the REGISTERED constant to true
        static bool registerParser();

    public:
        //Constant: FIELD_TYPE
        //    The 2-byte field type (Descriptor ID + Field ID) for this parser
        static const MipTypes::ChannelField FIELD_TYPE;

        //Constant: REGISTERED
        //    Whether this parser is registered. This will always be true. This is used to call registerParser() immediately
        static const bool REGISTERED;
    };

    //Class: FieldParser_DeltaTime
    //    The field parser for Delta Time
    class FieldParser_DeltaTime : public MipSharedFieldParser
    {
    private:
        FieldParser_DeltaTime() {};        //default constructor disabled

    public:
        //Function: parse
        //    Parses an <MipDataField> for <MipDataPoints> and stores them in the valid or invalid result vectors
        //
        //Parameters:
        //    field - The <MipDataField> to parse for data points
        //    result - The <MipDataPoints> vector to store the data points in
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;

        //Function: registerParser
        //    The static function that registers this parser with the list of parsers (called immediately)
        //
        //Returns:
        //    true, just for assigning the REGISTERED constant to true
        static bool registerParser();

    public:
        //Constant: FIELD_TYPE
        //    The 2-byte field type (Descriptor ID + Field ID) for this parser
        static const MipTypes::ChannelField FIELD_TYPE;

        //Constant: REGISTERED
        //    Whether this parser is registered. This will always be true. This is used to call registerParser() immediately
        static const bool REGISTERED;
    };

    //Class: FieldParser_ReferenceTime
    //    The field parser for internal Reference Time (0xFF,0xD5)
    class FieldParser_ReferenceTime : public MipSharedFieldParser
    {
        FieldParser_ReferenceTime() {}    //default constructor disabled

    public:
        //Function: parse
        //    Parses an <MipDataField> for <MipDataPoints> and stores them in the valid or invalid result vectors
        //
        //Parameters:
        //    field - The <MipDataField> to parse for data points
        //    result - The <MipDataPoints> vector to store the data points in
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;

        //Function: registerParser
        //    The static function that registers this parser with the list of parsers (called immediately)
        //
        //Returns:
        //    True, just for assigning <REGISTERED> to true
        static bool registerParser();

        //Constant: FIELD_TYPE
        //    The <MipTypes::ChannelField> for this parser
        static const MipTypes::ChannelField FIELD_TYPE;

        //Constant: REGISTERED
        //    Whether this parser is registered. This will always be true.
        //
        //Note:
        //    This is used to call <registerParser> immediately
        static const bool REGISTERED;
    };

    //Class: FieldParser_DeltaReferenceTime
    //    The field parser for internal Delta Reference Time (0xFF,0xD6)
    class FieldParser_DeltaReferenceTime : public MipSharedFieldParser
    {
        FieldParser_DeltaReferenceTime() {}    //default constructor disabled

    public:
        //Function: parse
        //    Parses an <MipDataField> for <MipDataPoints> and stores them in the valid or invalid result vectors
        //
        //Parameters:
        //    field - The <MipDataField> to parse for data points
        //    result - The <MipDataPoints> vector to store the data points in
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;

        //Function: registerParser
        //    The static function that registers this parser with the list of parsers (called immediately)
        //
        //Returns:
        //    True, just for assigning <REGISTERED> to true
        static bool registerParser();

        //Constant: FIELD_TYPE
        //    The <MipTypes::ChannelField> for this parser
        static const MipTypes::ChannelField FIELD_TYPE;

        //Constant: REGISTERED
        //    Whether this parser is registered. This will always be true.
        //
        //Note:
        //    This is used to call <registerParser> immediately
        static const bool REGISTERED;
    };
    
    //Class: FieldParser_ExternalTimestamp
    //    The field parser for External Timestamp (0xFF,0xD7)
    class FieldParser_ExternalTimestamp : public MipSharedFieldParser
    {
        FieldParser_ExternalTimestamp() {}    //default constructor disabled

    public:
        //Function: parse
        //    Parses an <MipDataField> for <MipDataPoints> and stores them in the valid or invalid result vectors
        //
        //Parameters:
        //    field - The <MipDataField> to parse for data points
        //    result - The <MipDataPoints> vector to store the data points in
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;

        //Function: registerParser
        //    The static function that registers this parser with the list of parsers (called immediately)
        //
        //Returns:
        //    True, just for assigning <REGISTERED> to true
        static bool registerParser();

        //Constant: FIELD_TYPE
        //    The <MipTypes::ChannelField> for this parser
        static const MipTypes::ChannelField FIELD_TYPE;

        //Constant: REGISTERED
        //    Whether this parser is registered. This will always be true.
        //
        //Note:
        //    This is used to call <registerParser> immediately
        static const bool REGISTERED;
    };

    //Class: FieldParser_DeltaExternalTime
    //    The field parser for Delta External Time (0xFF,0xD8)
    class FieldParser_DeltaExternalTime : public MipSharedFieldParser
    {
        FieldParser_DeltaExternalTime() {}    //default constructor disabled

    public:
        //Function: parse
        //    Parses an <MipDataField> for <MipDataPoints> and stores them in the valid or invalid result vectors
        //
        //Parameters:
        //    field - The <MipDataField> to parse for data points
        //    result - The <MipDataPoints> vector to store the data points in
        virtual void parse(const MipDataField& field, MipDataPoints& result) const override;

        //Function: registerParser
        //    The static function that registers this parser with the list of parsers (called immediately)
        //
        //Returns:
        //    True, just for assigning <REGISTERED> to true
        static bool registerParser();

        //Constant: FIELD_TYPE
        //    The <MipTypes::ChannelField> for this parser
        static const MipTypes::ChannelField FIELD_TYPE;

        //Constant: REGISTERED
        //    Whether this parser is registered. This will always be true.
        //
        //Note:
        //    This is used to call <registerParser> immediately
        static const bool REGISTERED;
    };
}