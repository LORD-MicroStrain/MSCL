/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "InertialFieldParser_Shared.h"
#include "mscl/MicroStrain/MIP/Packets/MipDataPacket.h"
#include "mscl/MicroStrain/DataBuffer.h"

namespace mscl
{
    //the classes in this file do not get referenced anywhere, therefore the 
    //linker will not include this compilation unit when statically 
    //linking to an executable. Defining this variable, and then using it
    //elsewhere, will force this file to be included
    bool _forceLibraryToIncludeCompilationUnit_Shared;

    //=====================================================================================================================================================
    //                                                        MipSharedFieldParser
    bool MipSharedFieldParser::registerSharedParser(MipTypes::ChannelField chField, const MipFieldParser* parser)
    {
        bool registered = true;
        MipTypes::MipChannelFields fields = MipTypes::getChannelFields_allDataClasses(chField);
        for (MipTypes::ChannelField field : fields)
        {
            // any failures should return false
            registered = registered && MipFieldParser::registerParser(field, parser);
        }

        return registered;
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_Ticks
    const MipTypes::ChannelField FieldParser_Ticks::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_SHARED_TICKS;
    const bool FieldParser_Ticks::REGISTERED = FieldParser_Ticks::registerParser();    //register the parser immediately

    void FieldParser_Ticks::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        uint32 ticks = bytes.read_uint32();

        MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        //add all the data points we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_TICK, valueType_uint32, anyType(ticks)));
    }

    bool FieldParser_Ticks::registerParser()
    {
        static FieldParser_Ticks p;
        return MipSharedFieldParser::registerSharedParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_DeltaTicks
    const MipTypes::ChannelField FieldParser_DeltaTicks::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_SHARED_DELTA_TICKS;
    const bool FieldParser_DeltaTicks::REGISTERED = FieldParser_DeltaTicks::registerParser();    //register the parser immediately

    void FieldParser_DeltaTicks::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        uint32 deltaTicks = bytes.read_uint32();

        MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        //add all the data points we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_DELTA_TICK, valueType_uint32, anyType(deltaTicks)));
    }

    bool FieldParser_DeltaTicks::registerParser()
    {
        static FieldParser_DeltaTicks p;
        return MipSharedFieldParser::registerSharedParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_DeltaTicks
    const MipTypes::ChannelField FieldParser_GpsTimestamp::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_SHARED_GPS_TIMESTAMP;
    const bool FieldParser_GpsTimestamp::REGISTERED = FieldParser_GpsTimestamp::registerParser();    //register the parser immediately

    void FieldParser_GpsTimestamp::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        double tow = bytes.read_double();
        uint16 weekNumber = bytes.read_uint16();

        uint16 flags = bytes.read_uint16();

        //get whether points are valid or invalid from the flags
        bool towValid = pointIsValid(flags, TOW_VALID);
        bool weekNumValid = pointIsValid(flags, WEEK_NUM_VALID);
        
        MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        //add all the data points we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_TIME_OF_WEEK, valueType_double, anyType(tow), towValid));
        result.push_back(MipDataPoint(chField, MipTypes::CH_WEEK_NUMBER, valueType_uint16, anyType(weekNumber), weekNumValid));
    }

    bool FieldParser_GpsTimestamp::registerParser()
    {
        static FieldParser_GpsTimestamp p;
        return MipSharedFieldParser::registerSharedParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_DeltaTime
    const MipTypes::ChannelField FieldParser_DeltaTime::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_SHARED_DELTA_TIMESTAMP;
    const bool FieldParser_DeltaTime::REGISTERED = FieldParser_DeltaTime::registerParser();    //register the parser immediately

    void FieldParser_DeltaTime::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        double deltaTime = bytes.read_double();

        MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        //add all the data points we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_DELTA_TIME, valueType_double, anyType(deltaTime)));
    }

    bool FieldParser_DeltaTime::registerParser()
    {
        static FieldParser_DeltaTime p;
        return MipSharedFieldParser::registerSharedParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================
}