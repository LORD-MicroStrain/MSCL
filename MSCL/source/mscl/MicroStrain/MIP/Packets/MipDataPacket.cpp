/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "MipDataPacket.h"

#include "mscl/Utils.h"
#include "MipFieldParser.h"
#include "mscl/MicroStrain/DataBuffer.h"

namespace mscl
{                    
    MipDataPacket::MipDataPacket():
        m_collectedTime(0),
        m_deviceTime(0),
        m_hasDeviceTime(false),
        m_deviceTimeValid(false),
        m_deviceTimeFlags(0)
    {
    }

    MipDataPacket::MipDataPacket(const MipPacket& packet):
        m_collectedTime(Timestamp::timeNow()),
        m_deviceTime(0),
        m_hasDeviceTime(false),
        m_deviceTimeValid(false),
        m_deviceTimeFlags(0)
    {
        //construct the data packet from the MipPacket passed in
        m_descriptorSet     = packet.descriptorSet();
        m_payload           = Payload(packet.payload());

        //parse the data fields in the packet
        parseDataFields();
    }

    void MipDataPacket::parseDataFields()
    {
        uint8 fieldDescriptor;
        uint16 fieldType;
        uint32 fieldLen;

        //create a DataBuffer to make parsing easier
        DataBuffer payloadData(m_payload.data());

        while(payloadData.moreToRead())
        {
            try
            {
                Bytes fieldBytes;

                //read the field length byte
                fieldLen = payloadData.read_uint8();

                //read the field descriptor byte
                fieldDescriptor = payloadData.read_uint8();

                //read all the bytes for the current field (up to the field length)
                for(uint32 itr = 0; itr < fieldLen - 2; itr++)
                {
                    //add the field bytes to a container
                    fieldBytes.push_back(payloadData.read_uint8());
                }

                fieldType = Utils::make_uint16(m_descriptorSet, fieldDescriptor);

                //add the field to the m_dataFields vector
                MipDataField tempField(fieldType, fieldBytes);
                m_dataFields.push_back(tempField);

                //parse the data points that are in the existing field that we just created
                parsePointsInField(tempField);
            }
            catch(...)
            {
                //possible corrupted packet, just break out and skip trying to parse anything else
                break;
            }
        }
    }

    void MipDataPacket::parsePointsInField(const MipDataField& field)
    {
        bool isTimestamp = false;
        bool isData = true;

        MipTypes::ChannelField id = MipTypes::getChannelField_baseDataClass(static_cast<MipTypes::ChannelField>(field.fieldId()));

        switch(id)
        {
            //fields that should only be used as timestamp, and not stored as data
            case MipTypes::CH_FIELD_DISP_DISPLACEMENT_TS:
                isTimestamp = true;
                isData = false;
                break;

            //fields that will get passed along as data points as well
            case MipTypes::CH_FIELD_SENSOR_GPS_CORRELATION_TIMESTAMP:
            case MipTypes::CH_FIELD_GNSS_GPS_TIME:
            case MipTypes::CH_FIELD_ESTFILTER_GPS_TIMESTAMP:
            case MipTypes::CH_FIELD_SENSOR_SHARED_GPS_TIMESTAMP:
                isTimestamp = true;
                isData = true;
                break;

            default:
                break;
        }

        // don't re-process if a different timestamp already found
        if(isTimestamp && !m_hasDeviceTime)
        {
            m_hasDeviceTime = true;
            parseTimeStamp(field);
        }

        size_t currentPointsCount = m_points.size();
        if(isData)
        {
            MipFieldParser::parseField(field, m_points);
        }

        if (MipTypes::isSharedChannelField(id))
        {
            for (size_t i = currentPointsCount; i < m_points.size(); i++)
            {
                MipDataPoint& point = m_points[i];
                m_sharedFields.addDataReference(point.field(), point.qualifier(), point);
            }
        }
    }

    bool MipDataPacket::timestampWithinRange(const Timestamp& timestamp) const
    {
        //timestamp is out of range if it is over an hour in the future
        static const uint64 NANOS_IN_1_HOUR = 3600000000000;

        //not valid if time is more than 1 hour in the past or future
        return ((timestamp - collectedTimestamp()).getNanoseconds() < NANOS_IN_1_HOUR);
    }

    void MipDataPacket::parseTimeStamp(const MipDataField& field)
    {
        DataBuffer bytes(field.fieldData());

        MipTypes::ChannelField id = MipTypes::getChannelField_baseDataClass(static_cast<MipTypes::ChannelField>(field.fieldId()));

        switch (id)
        {
            case MipTypes::CH_FIELD_DISP_DISPLACEMENT_TS:
            {
                m_deviceTimeFlags = bytes.read_uint8();
                m_deviceTimeValid = (m_deviceTimeFlags == 1);
                m_deviceTime.setTime(bytes.read_uint64());
                break;
            }

            case MipTypes::CH_FIELD_SENSOR_GPS_CORRELATION_TIMESTAMP:
            {
                double gpsTimeOfWeek = bytes.read_double();
                uint16 gpsWeekNumber = bytes.read_uint16();

                //convert to UTC time
                m_deviceTimeFlags = bytes.read_uint16();
                m_deviceTime.setTime(Timestamp::gpsTimeToUtcTime(gpsTimeOfWeek, gpsWeekNumber));

                //check the GPS time looks like a valid absolute timestamp
                //Note: unfortunately, the flags that come with this packet can't be used to identify this,
                //      so we are just checking for an old or future timestamp, since it starts at 0 when first powered on
                m_deviceTimeValid = timestampWithinRange(m_deviceTime);

                break;
            }

            case MipTypes::CH_FIELD_SENSOR_SHARED_GPS_TIMESTAMP:
            case MipTypes::CH_FIELD_GNSS_GPS_TIME:
            {
                double gpsTimeOfWeek = bytes.read_double();
                uint16 gpsWeekNumber = bytes.read_uint16();

                //convert to UTC time
                m_deviceTimeFlags = bytes.read_uint16();
                m_deviceTime.setTime(Timestamp::gpsTimeToUtcTime(gpsTimeOfWeek, gpsWeekNumber));

                //check the GPS time looks like a valid absolute timestamp
                //Note: we might be able to use the flags here, but we're doing this check for the other descriptor sets anyway
                m_deviceTimeValid = timestampWithinRange(m_deviceTime);

                break;
            }

            case MipTypes::CH_FIELD_ESTFILTER_GPS_TIMESTAMP:
            {
                double gpsTimeOfWeek = bytes.read_double();
                uint16 gpsWeekNumber = bytes.read_uint16();

                //convert to UTC time
                m_deviceTimeFlags = bytes.read_uint16();
                m_deviceTime.setTime(Timestamp::gpsTimeToUtcTime(gpsTimeOfWeek, gpsWeekNumber));

                //check the GPS time looks like a valid absolute timestamp
                //Note: unfortunately, the flags that come with this packet can't be used to identify this, as it seems
                //      they are invalid if the estimation filter isn't initialized, even if the time is initialized
                m_deviceTimeValid = timestampWithinRange(m_deviceTime);

                break;
            }

            default:
                assert(false);  //shouldn't get to this function without being able to parse the timestamp
                break;
        }

    }

    const MipDataPoints& MipDataPacket::data() const
    {
        return m_points;
    }

    const MipSharedDataFields& MipDataPacket::shared() const
    {
        return m_sharedFields;
    }

    const Timestamp& MipDataPacket::collectedTimestamp() const
    {
        return m_collectedTime;
    }

    const Timestamp& MipDataPacket::deviceTimestamp() const
    {
        return m_deviceTime;
    }

    bool MipDataPacket::deviceTimeValid() const
    {
        return m_deviceTimeValid;
    }

    bool MipDataPacket::hasDeviceTime() const
    {
        return m_hasDeviceTime;
    }

    uint16 MipDataPacket::deviceTimeFlags() const
    {
        return m_deviceTimeFlags;
    }

    void MipSharedDataFields::addDataReference(MipTypes::ChannelField field, MipTypes::ChannelQualifier qualifier, MipDataPoint& dataRef)
    {
        MipTypes::ChannelField baseField = MipTypes::getChannelField_baseDataClass(field);
        std::map<MipTypes::ChannelQualifier, MipDataPoint> emptyMap = {};
        auto entryItr = m_dataReferences.emplace(baseField, emptyMap).first;
        entryItr->second.emplace(qualifier, dataRef);
    }

    const MipDataPoint& MipSharedDataFields::get(MipTypes::ChannelField field, MipTypes::ChannelQualifier qualifier) const
    {
        if (!MipTypes::isSharedChannelField(field))
        {
            throw Error_NoData("Specified field is not a shared data field");
        }

        MipTypes::ChannelField baseField = MipTypes::getChannelField_baseDataClass(field);
        auto entryItr = m_dataReferences.find(baseField);
        if (entryItr == m_dataReferences.end()
            || entryItr->second.size() <= 0)
        {
            throw Error_NoData("Could not find the specified shared data field");
        }

        if (entryItr->second.size() == 1 && qualifier == MipTypes::CH_UNKNOWN)
        {
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
        catch (const std::exception&){/*ignore*/}

        return ts;
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
}