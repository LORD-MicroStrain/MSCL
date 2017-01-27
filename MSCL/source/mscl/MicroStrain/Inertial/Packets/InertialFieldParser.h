/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "InertialDataPacket.h"
#include "mscl/MicroStrain/Inertial/InertialTypes.h"
#include <vector>
#include <map>

namespace mscl
{
    //Title: InertialFieldParser

    class InertialDataField;
    class InertialFieldParser;

    //Typedef: ParserMap
    //    Typedef for a map of <InertialTypes::ChannelField> / <InertialFieldParser> pairs
    typedef std::map<InertialTypes::ChannelField, const InertialFieldParser*> ParserMap;

    //Class: InertialFieldParser
    //    Base Class parser for parsing Inertial Data Fields
    class InertialFieldParser
    {
    protected:
        InertialFieldParser(){};                //default constructor disabled
        virtual ~InertialFieldParser(){};

    private:
        InertialFieldParser(const InertialFieldParser&);                //copy constructor disabled
        InertialFieldParser& operator=(const InertialFieldParser&);        //assignment operator disabled

    public:
        //Function: parse
        //    Parses an <InertialDataField> for <InertialDataPoints> and stores them in the result vector
        //
        //Parameters:
        //    field - The <InertialDataField> to parse for data points
        //    result - The <InertialDataPoints> vector to store the data points in
        virtual void parse(const InertialDataField& field, InertialDataPoints& result) const = 0;

        //Function: parseField
        //    The static parse function to call that looks through the parser map and parses the field with the correct parser
        //
        //Parameters:
        //    field - The <InertialDataField> to parse for data points
        //    result - The <InertialDataPoints> vector to store the data points in
        static void parseField(const InertialDataField& field, InertialDataPoints& result);

    protected:
        //Function: getParserMap
        //    Gets the static parser map that contains all the registered parsing classes
        //
        //Returns:
        //    A <ParserMap> holding all the parse functions in a map
        static ParserMap& getParserMap();

        //Function: registerParser
        //    Registers an <InertialFieldParser> with a <InertialTypes::ChannelField>.
        //
        //Returns:
        //    true if the parser was registered successfully, false if it failed (already existed).
        static bool registerParser(InertialTypes::ChannelField field, const InertialFieldParser* parser);

        //Function: pointIsValid
        //    Checks if the flag position for an Inertial Data Point is valid given the full flags value
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