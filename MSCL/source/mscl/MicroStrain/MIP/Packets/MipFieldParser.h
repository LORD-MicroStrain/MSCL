/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "MipDataPacket.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include <vector>
#include <map>

namespace mscl
{
    //Title: MipFieldParser

    class MipDataField;
    class MipFieldParser;

    //Typedef: ParserMap
    //    Typedef for a map of <MipTypes::ChannelField> / <MipFieldParser> pairs
    typedef std::map<MipTypes::ChannelField, const MipFieldParser*> ParserMap;

    //Class: MipFieldParser
    //    Base Class parser for parsing Mip Data Fields
    class MipFieldParser
    {
    protected:
        MipFieldParser(){};                //default constructor disabled
        virtual ~MipFieldParser(){};

    private:
        MipFieldParser(const MipFieldParser&);                //copy constructor disabled
        MipFieldParser& operator=(const MipFieldParser&);        //assignment operator disabled

    public:
        //Function: parse
        //    Parses an <MipDataField> for <MipDataPoints> and stores them in the result vector
        //
        //Parameters:
        //    field - The <MipDataField> to parse for data points
        //    result - The <MipDataPoints> vector to store the data points in
        virtual void parse(const MipDataField& field, MipDataPoints& result) const = 0;

        //Function: parseField
        //    The static parse function to call that looks through the parser map and parses the field with the correct parser
        //
        //Parameters:
        //    field - The <MipDataField> to parse for data points
        //    result - The <MipDataPoints> vector to store the data points in
        static void parseField(const MipDataField& field, MipDataPoints& result);

    protected:
        //Function: getParserMap
        //    Gets the static parser map that contains all the registered parsing classes
        //
        //Returns:
        //    A <ParserMap> holding all the parse functions in a map
        static ParserMap& getParserMap();

        //Function: registerParser
        //    Registers an <MipFieldParser> with a <MipTypes::ChannelField>.
        //
        //Returns:
        //    true if the parser was registered successfully, false if it failed (already existed).
        static bool registerParser(MipTypes::ChannelField field, const MipFieldParser* parser);

        //Function: pointIsValid
        //    Checks if the flag position for a Mip Data Point is valid given the full flags value
        //
        //Parameters:
        //    allFlags - The full flags value representing all the valid and invalid flags
        //    flagPos - The binary position of the flag to check if it is valid (1) or invalid (0)
        //
        //Returns:
        //    true if the flag position is valid, false if the flag position is invalid
        static bool pointIsValid(uint16 allFlags, uint16 flagPos);
    };
}