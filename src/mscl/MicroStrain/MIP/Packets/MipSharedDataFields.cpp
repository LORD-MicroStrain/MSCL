/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/MIP/Packets/MipSharedDataFields.h"

namespace mscl
{
    void MipSharedDataFields::addPoint(MipTypes::ChannelField field, MipTypes::ChannelQualifier qualifier, MipDataPoint& dataPoint)
    {
        // convert to base data class for key for easier lookup
        MipTypes::ChannelField baseField = MipTypes::getChannelField_baseDataClass(field);
        std::map<MipTypes::ChannelQualifier, MipDataPoint> emptyMap = {};

        // create channel field entry if not exists, get itr to entry
        auto entryItr = m_sharedDataPoints.emplace(baseField, emptyMap).first;

        // add qualifier entry if not exists
        entryItr->second.emplace(qualifier, dataPoint);
    }

    const MipDataPoint& MipSharedDataFields::get(MipTypes::ChannelField field, MipTypes::ChannelQualifier qualifier) const
    {
        // don't bother trying to lookup field if not shared field
        if (!MipTypes::isSharedChannelField(field))
        {
            throw Error_NoData("Specified field is not a shared data field");
        }

        // convert to base data class for lookup
        MipTypes::ChannelField baseField = MipTypes::getChannelField_baseDataClass(field);
        auto entryItr = m_sharedDataPoints.find(baseField);
        if (entryItr == m_sharedDataPoints.end()
            || entryItr->second.size() <= 0)
        {
            throw Error_NoData("Could not find the specified shared data field");
        }

        // if qualifier is unspecified but there's only one data point for the field, return it
        if (entryItr->second.size() == 1 && qualifier == MipTypes::CH_UNKNOWN)
        {
            // entryItr->second: map<qualifier, MipDataPoint>
            //    .begin(): first entry in qualifier map
            //    ->second: MipDataPoint mapped to first qualifier
            return entryItr->second.begin()->second;
        }

        auto qualEntryItr = entryItr->second.find(qualifier);
        if (qualEntryItr == entryItr->second.end())
        {
            throw Error_NoData("Could not find the specified shared data qualifier");
        }

        return qualEntryItr->second;
    }

    bool MipSharedDataFields::has(MipTypes::ChannelField field, MipTypes::ChannelQualifier qualifier) const
    {
        try
        {
            get(field, qualifier);
            return true;
        }
        catch (const std::exception&)
        {
            return false;
        }
    }

    bool MipSharedDataFields::hasEventSource() const
    {
        return eventSource() != EVENT_SOURCE_UNKNOWN;
    }

    uint8 MipSharedDataFields::eventSource() const
    {
        try
        {
            return get(MipTypes::CH_FIELD_SENSOR_SHARED_EVENT_SOURCE).as_uint8();
        }
        catch (const std::exception&)
        {
            return static_cast<uint8>(EVENT_SOURCE_UNKNOWN);
        }
    }

    bool MipSharedDataFields::hasTicks() const
    {
        return has(MipTypes::CH_FIELD_SENSOR_SHARED_TICKS);
    }

    uint32 MipSharedDataFields::ticks() const
    {
        try
        {
            return get(MipTypes::CH_FIELD_SENSOR_SHARED_TICKS).as_uint32();
        }
        catch (const std::exception&)
        {
            return 0;
        }
    }

    bool MipSharedDataFields::hasDeltaTicks() const
    {
        return has(MipTypes::CH_FIELD_SENSOR_SHARED_DELTA_TICKS);
    }

    uint32 MipSharedDataFields::deltaTicks() const
    {
        try
        {
            return get(MipTypes::CH_FIELD_SENSOR_SHARED_DELTA_TICKS).as_uint32();
        }
        catch (const std::exception&)
        {
            return 0;
        }
    }

    bool MipSharedDataFields::hasGpsTimestamp() const
    {
        return has(MipTypes::CH_FIELD_SENSOR_SHARED_GPS_TIMESTAMP, MipTypes::CH_TIME_OF_WEEK)
            && has(MipTypes::CH_FIELD_SENSOR_SHARED_GPS_TIMESTAMP, MipTypes::CH_WEEK_NUMBER);
    }

    Timestamp MipSharedDataFields::gpsTimestamp() const
    {
        Timestamp ts(0);

        try
        {
            double tow = get(MipTypes::CH_FIELD_SENSOR_SHARED_GPS_TIMESTAMP, MipTypes::CH_TIME_OF_WEEK).as_double();
            uint16 weekNumber = get(MipTypes::CH_FIELD_SENSOR_SHARED_GPS_TIMESTAMP, MipTypes::CH_WEEK_NUMBER).as_uint16();
            ts.setTime(Timestamp::gpsTimeToUtcTime(tow, weekNumber));
        }
        catch (const std::exception&) {/*ignore*/ }

        return ts;
    }

    bool MipSharedDataFields::gpsTimestampValid() const
    {
        bool valid = false;

        try
        {
            bool tow = get(MipTypes::CH_FIELD_SENSOR_SHARED_GPS_TIMESTAMP, MipTypes::CH_TIME_OF_WEEK).valid();
            bool weekNumber = get(MipTypes::CH_FIELD_SENSOR_SHARED_GPS_TIMESTAMP, MipTypes::CH_WEEK_NUMBER).valid();
            valid = tow && weekNumber;
        }
        catch (const std::exception&) {/*ignore*/ }

        return valid;
    }

    bool MipSharedDataFields::hasDeltaTime() const
    {
        return has(MipTypes::CH_FIELD_SENSOR_SHARED_DELTA_TIMESTAMP);
    }

    double MipSharedDataFields::deltaTime() const
    {
        try
        {
            return get(MipTypes::CH_FIELD_SENSOR_SHARED_DELTA_TIMESTAMP).as_double();
        }
        catch (const std::exception&)
        {
            return 0;
        }
    }

    bool MipSharedDataFields::hasReferenceTime() const
    {
        return has(MipTypes::CH_FIELD_SENSOR_SHARED_REFERENCE_TIMESTAMP);
    }

    uint64 MipSharedDataFields::referenceTime() const
    {
        try
        {
            return get(MipTypes::CH_FIELD_SENSOR_SHARED_REFERENCE_TIMESTAMP).as_uint64();
        }
        catch (const std::exception&)
        {
            return 0;
        }
    }

    bool MipSharedDataFields::hasDeltaReferenceTime() const
    {
        return has(MipTypes::CH_FIELD_SENSOR_SHARED_DELTA_REFERENCE_TIME);
    }

    uint64 MipSharedDataFields::deltaReferenceTime() const
    {
        try
        {
            return get(MipTypes::CH_FIELD_SENSOR_SHARED_DELTA_REFERENCE_TIME).as_uint64();
        }
        catch (const std::exception&)
        {
            return 0;
        }
    }

    bool MipSharedDataFields::hasExternalTimestamp() const
    {
        return has(MipTypes::CH_FIELD_SENSOR_SHARED_EXTERNAL_TIMESTAMP);
    }

    Timestamp MipSharedDataFields::externalTimestamp() const
    {
        try
        {
            return get(MipTypes::CH_FIELD_SENSOR_SHARED_EXTERNAL_TIMESTAMP).as_Timestamp();
        }
        catch (const std::exception&)
        {
            return Timestamp(0);
        }
    }

    bool MipSharedDataFields::externalTimestampValid() const
    {
        try
        {
            return get(MipTypes::CH_FIELD_SENSOR_SHARED_EXTERNAL_TIMESTAMP).valid();
        }
        catch (const std::exception&)
        {
            return false;
        }
    }

    bool MipSharedDataFields::hasDeltaExternalTime() const
    {
        return has(MipTypes::CH_FIELD_SENSOR_SHARED_DELTA_EXTERNAL_TIME);
    }

    uint64 MipSharedDataFields::deltaExternalTime() const
    {
        try
        {
            return get(MipTypes::CH_FIELD_SENSOR_SHARED_DELTA_EXTERNAL_TIME).as_uint64();
        }
        catch (const std::exception&)
        {
            return 0;
        }
    }

    bool MipSharedDataFields::deltaExternalTimeValid() const
    {
        try
        {
            return get(MipTypes::CH_FIELD_SENSOR_SHARED_DELTA_EXTERNAL_TIME).valid();
        }
        catch (const std::exception&)
        {
            return false;
        }
    }
} // namespace mscl
