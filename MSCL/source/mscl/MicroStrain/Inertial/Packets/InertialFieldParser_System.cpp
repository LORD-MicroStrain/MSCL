/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"

#include "InertialFieldParser_System.h"

namespace mscl
{
    //the classes in this file do not get referenced anywhere, therefore the
    //linker will not include this compilation unit when statically
    //linking to an executable. Defining this variable, and then using it
    //elsewhere, will force this file to be included
    bool _forceLibraryToIncludeCompilationUnit_System;

    //=====================================================================================================================================================
    //                                                        FieldParser_GpioState
    const MipTypes::ChannelField FieldParser_GpioState::FIELD_TYPE = MipTypes::CH_FIELD_SYSTEM_GPIO_STATE;
    const bool FieldParser_GpioState::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_GpioState::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the value
        const uint8 states = bytes.read_uint8();

        //create the data point and add it to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_STATUS, valueType_uint8, anyType(states)));
    }

    bool FieldParser_GpioState::registerParser()
    {
        static FieldParser_GpioState p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_TimeSyncStatus
    const MipTypes::ChannelField FieldParser_TimeSyncStatus::FIELD_TYPE = MipTypes::CH_FIELD_SYSTEM_TIME_SYNC_STATUS;
    const bool FieldParser_TimeSyncStatus::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_TimeSyncStatus::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the values
        const bool ppsValid = bytes.read_uint8() > 0;
        const uint8 lastPps = bytes.read_uint8();

        //create the data points and add them to the result container
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_PPS_VALID, valueType_bool, anyType(ppsValid)));
        result.push_back(MipDataPoint(FIELD_TYPE, MipTypes::CH_LAST_PPS, valueType_uint8, anyType(lastPps)));
    }

    bool FieldParser_TimeSyncStatus::registerParser()
    {
        static FieldParser_TimeSyncStatus p;
        return MipFieldParser::registerParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================
}
