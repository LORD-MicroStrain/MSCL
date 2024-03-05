/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

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
    //                                                        FieldParser_EventSource
    const MipTypes::ChannelField FieldParser_EventSource::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_SHARED_EVENT_SOURCE;
    const bool FieldParser_EventSource::REGISTERED = FieldParser_EventSource::registerParser();    //register the parser immediately

    void FieldParser_EventSource::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        uint8 sourceTrigger = bytes.read_uint8();

        MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        //add all the data points we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_ID, valueType_uint8, anyType(sourceTrigger)));
    }

    bool FieldParser_EventSource::registerParser()
    {
        static FieldParser_EventSource p;
        return MipSharedFieldParser::registerSharedParser(FIELD_TYPE, &p);
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
    //                                                        FieldParser_GpsTimestamp
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

    //=====================================================================================================================================================
    //                                                        FieldParser_ReferenceTime
    const MipTypes::ChannelField FieldParser_ReferenceTime::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_SHARED_REFERENCE_TIMESTAMP;
    const bool FieldParser_ReferenceTime::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_ReferenceTime::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        const uint64 referenceTime = bytes.read_uint64();

        const MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        //add all the data points we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_NANOSECONDS, valueType_uint64, anyType(referenceTime)));
    }

    bool FieldParser_ReferenceTime::registerParser()
    {
        static FieldParser_ReferenceTime p;
        return registerSharedParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //=====================================================================================================================================================
    //                                                        FieldParser_DeltaReferenceTime
    const MipTypes::ChannelField FieldParser_DeltaReferenceTime::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_SHARED_DELTA_REFERENCE_TIME;
    const bool FieldParser_DeltaReferenceTime::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_DeltaReferenceTime::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        const uint64 deltaTime = bytes.read_uint64();

        const MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        //add all the data points we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_NANOSECONDS, valueType_uint64, anyType(deltaTime)));
    }

    bool FieldParser_DeltaReferenceTime::registerParser()
    {
        static FieldParser_DeltaReferenceTime p;
        return registerSharedParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //===================================================================================================================================================== //=====================================================================================================================================================
    //                                                        FieldParser_ExternalTimestamp
    const MipTypes::ChannelField FieldParser_ExternalTimestamp::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_SHARED_EXTERNAL_TIMESTAMP;
    const bool FieldParser_ExternalTimestamp::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_ExternalTimestamp::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        const Timestamp time(bytes.read_uint64(), Timestamp::Epoch::GPS);
        const bool valid = pointIsValid(bytes.read_uint16(), static_cast<uint16>(BOOST_BINARY(00000001)));

        const MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        //add all the data points we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_TIMESTAMP, valueType_Timestamp, anyType(time), valid));
    }

    bool FieldParser_ExternalTimestamp::registerParser()
    {
        static FieldParser_ExternalTimestamp p;
        return registerSharedParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

    //===================================================================================================================================================== //=====================================================================================================================================================
    //                                                        FieldParser_DeltaExternalTime
    const MipTypes::ChannelField FieldParser_DeltaExternalTime::FIELD_TYPE = MipTypes::CH_FIELD_SENSOR_SHARED_DELTA_EXTERNAL_TIME;
    const bool FieldParser_DeltaExternalTime::REGISTERED = registerParser();    //register the parser immediately

    void FieldParser_DeltaExternalTime::parse(const MipDataField& field, MipDataPoints& result) const
    {
        DataBuffer bytes(field.fieldData());

        //get the data
        const uint64 delta = bytes.read_uint64();
        const bool valid = pointIsValid(bytes.read_uint16(), static_cast<uint16>(BOOST_BINARY(00000001)));

        const MipTypes::ChannelField chField = static_cast<MipTypes::ChannelField>(field.fieldId());

        //add all the data points we just collected
        result.push_back(MipDataPoint(chField, MipTypes::CH_NANOSECONDS, valueType_uint64, anyType(delta), valid));
    }

    bool FieldParser_DeltaExternalTime::registerParser()
    {
        static FieldParser_DeltaExternalTime p;
        return registerSharedParser(FIELD_TYPE, &p);
    }
    //=====================================================================================================================================================

}
