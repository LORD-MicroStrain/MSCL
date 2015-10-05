/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "InertialFieldParser.h"

#include <vector>
#include "InertialDataPacket.h"
#include "InertialFieldParser_Sensor.h"


namespace mscl
{
	//forces the linker to include the InertialFieldParser_YYY files
	//by using a global variable defined in their files
	bool run_once_forceLibraryToIncludeCompilationUnit()
	{
		//add the following 2 lines for each parser's file
		extern bool _forceLibraryToIncludeCompilationUnit_AHRS;
		_forceLibraryToIncludeCompilationUnit_AHRS = true;

		extern bool _forceLibraryToIncludeCompilationUnit_GPS;
		_forceLibraryToIncludeCompilationUnit_GPS = true;

		extern bool _forceLibraryToIncludeCompilationUnit_NAV;
		_forceLibraryToIncludeCompilationUnit_NAV = true;
	
		return true;
	}

	ParserMap& InertialFieldParser::getParserMap()
	{
		//force the linker to include all the parser files
		static bool unused = run_once_forceLibraryToIncludeCompilationUnit();

		//create a static ParserMap (1st time only) and return it
		static ParserMap p;
		return p;
	}

	bool InertialFieldParser::registerParser(InertialTypes::ChannelField field, const InertialFieldParser* parser)
	{
		ParserMap& map = getParserMap();

		//verify it doesn't already exist in the map
		if(map.find(field) != map.end())
		{
			assert(false);	//this should never happen
			return false;
		}

		//store the parser in the map of parsers
		getParserMap()[field] = parser;

		return true;
	}

	void InertialFieldParser::parseField(const InertialDataField& field, InertialDataPoints& result)
	{
		//get the static parser map
		ParserMap& parsers = getParserMap();

		InertialTypes::ChannelField chField = static_cast<InertialTypes::ChannelField>(field.fieldId());

		//try to find a parser in our map that can parse this field type
		std::map<InertialTypes::ChannelField, const InertialFieldParser*>::const_iterator itr = parsers.find(chField);

		//if we can find a parser for this field type
		if(itr != parsers.end())
		{
			//parse the field for data
			itr->second->parse(field, result);
		}
		//if we failed to find a parser for this field type
		else
		{			
			//just add a data point of this whole field as bytes
			result.push_back(InertialDataPoint(chField, InertialTypes::CH_UNKNOWN, valueType_Bytes, anyType(field.fieldData().data()), true));
		}
	}

	bool InertialFieldParser::pointIsValid(uint16 allFlags, uint16 flagPos)
	{
		//check the flag position against the allFlags value
		return ((allFlags & flagPos) > 0);
	}
}