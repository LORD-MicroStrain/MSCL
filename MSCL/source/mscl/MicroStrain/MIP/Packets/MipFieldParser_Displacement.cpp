/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "MipFieldParser_Displacement.h"

#include <boost/date_time/posix_time/ptime.hpp>

#include "mscl/MicroStrain/MIP/Packets/MipDataPacket.h"
#include "mscl/MicroStrain/DataBuffer.h"
#include "mscl/Types.h"

namespace mscl
{
    //the classes in this file do not get referenced anywhere, therefore the 
    //linker will not include this compilation unit when statically 
    //linking to an executable. Defining this variable, and then using it
    //elsewhere, will force this file to be included
    bool _forceLibraryToIncludeCompilationUnit_Displacement;

    //=====================================================================================================================================================
    //                                                        FieldParser_RawPosition
    const MipTypes::ChannelField FieldParser_RawPosition::FIELD_TYPE = MipTypes::CH_FIELD_DISP_DISPLACEMENT_RAW;
    const bool FieldParser_RawPosition::REGISTERED = FieldParser_RawPosition::registerParser();    //register the parser immediately

    void FieldParser_RawPosition::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        uint32 adcCount = bytes.read_uint32();

        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_DISPLACEMENT, valueType_uint32, anyType(adcCount)));
    }

    bool FieldParser_RawPosition::registerParser()
    {
        static FieldParser_RawPosition p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_Position
    const MipTypes::ChannelField FieldParser_Position::FIELD_TYPE = MipTypes::CH_FIELD_DISP_DISPLACEMENT_MM;
    const bool FieldParser_Position::REGISTERED = FieldParser_Position::registerParser();    //register the parser immediately

    void FieldParser_Position::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        float position = bytes.read_float();

        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_DISPLACEMENT, valueType_float, anyType(position)));
    }

    bool FieldParser_Position::registerParser()
    {
        static FieldParser_Position p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================
}