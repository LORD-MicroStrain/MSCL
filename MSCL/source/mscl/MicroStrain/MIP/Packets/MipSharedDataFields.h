/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/MIP/MipDataPoint.h"

namespace mscl
{
    //API Class: MipSharedDataFields
    //  Object to more easily access shared data field information within a MipDataPacket
    class MipSharedDataFields
    {
    public:
        //API Enum: EventSource
        //  The event source value is the event trigger ID (1-based index) that caused the data packet to be output.
        //  If the event source is not an event trigger ID it will be one of the following:
        //
        //      EVENT_SOURCE_NONE       - 0x00 - This packet was output due to normal data streaming, was not triggered by an event
        //      EVENT_SOURCE_UNKNOWN    - 0xFF - The Event Source field was not found in this packet
        enum EventSource
        {
            EVENT_SOURCE_NONE       = 0x00,
            EVENT_SOURCE_UNKNOWN    = 0xFF
        };

    private:
        friend class MipDataPacket; // allow MipDataPacket to add data references

        //Variable: m_sharedDataPoints
        //  Holds a map of shared data field MipDataPoints, added while parsing fields in the packet in MipDataPacket::parsePointsInField()
        std::map<MipTypes::ChannelField, std::map<MipTypes::ChannelQualifier, MipDataPoint>> m_sharedDataPoints;

        //Function: addPoint
        //  Adds a shared data point at the specified field and qualifier
        void addPoint(MipTypes::ChannelField field, MipTypes::ChannelQualifier qualifier, MipDataPoint& dataPoint);

        //Function: has
        //  Checks whether a data point has been added for the specified field and qualifier
        //  Note: returns true if qualifier is CH_UNKNOWN and there is only one data point for the specified field
        bool has(MipTypes::ChannelField field, MipTypes::ChannelQualifier qualifier = MipTypes::CH_UNKNOWN) const;

    public:
        //API Constructor: MipSharedDataFields
        //  Create an empty MipSharedDataFields object
        MipSharedDataFields() {};

        //API Function: hasEventSource
        //  Checks whether the packet contains the Event Source field
        //
        //Returns:
        //  bool - true if Event Source is present
        bool hasEventSource() const;

        //API Function: eventSource
        //  Gets the Event Source value for the packet
        //
        //Returns:
        //  uint8 - the event source trigger ID, 0x00 if not triggered by event, 0xFF if Event Source not present
        uint8 eventSource() const;

        //API Function: hasTicks
        //  Checks whether the packet contains the Ticks field
        //
        //Returns:
        //  bool - true if Ticks is present
        bool hasTicks() const;

        //API Function: ticks
        //  Gets the Ticks value for the packet
        //
        //Returns:
        //  uint32 - the ticks value
        uint32 ticks() const;

        //API Function: hasDeltaTicks
        //  Checks whether the packet contains the Delta Ticks field
        //
        //Returns:
        //  bool - true if Delta Ticks is present
        bool hasDeltaTicks() const;

        //API Function: deltaTicks
        //  Gets the Delta Ticks value for the packet
        //
        //Returns:
        //  uint32 - the delta ticks value
        uint32 deltaTicks() const;

        //API Function: hasGpsTimestamp
        //  Checks whether the packet contains the GPS Timestamp field
        //
        //Returns:
        //  bool - true if GPS Timestamp is present
        bool hasGpsTimestamp() const;

        //API Function: gpsTimestamp
        //  Gets the GPS Timestamp value for the packet.
        //  Note: On Gen 7 products and later this will generally be the same value as <MipDataPacket::deviceTimestamp()>
        //
        //Returns:
        //  <Timestamp> - the GPS timestamp value
        Timestamp gpsTimestamp() const;

        //API Function: gpsTimestampValid
        //  Checks whether the GPS Timestamp value for the packet is valid.
        //  Note: On Gen 7 products and later this will generally be the same value as <MipDataPacket::deviceTimestamp()>
        //
        //Returns:
        //  bool - true if valid
        bool gpsTimestampValid() const;

        //API Function: hasDeltaTime
        //  Checks whether the packet contains the Delta Time field
        //
        //Returns:
        //  bool - true if Delta Time is present
        bool hasDeltaTime() const;

        //API Function: deltaTime
        //  Gets the Delta Time value for the packet
        //
        //Returns:
        //  double - the delta time value
        double deltaTime() const;

        //API Function: hasReferenceTime
        //  Checks whether the packet contains the Reference Timestamp (nanoseconds since startup) field
        //
        //Returns:
        //  bool - true if Reference Time is present
        bool hasReferenceTime() const;

        //API Function: referenceTime
        //  Gets the Reference Timestamp (nanoseconds since startup) for the packet
        //
        //Returns:
        //  uint64 - the reference time value
        uint64 referenceTime() const;

        //API Function: hasDeltaReferenceTime
        //  Checks whether the packet contains the Delta Reference Timestamp (nanoseconds since last output) field
        //
        //Returns:
        //  bool - true if Delta Reference Time is present
        bool hasDeltaReferenceTime() const;

        //API Function: deltaReferenceTime
        //  Gets the Delta Reference Timestamp (nanoseconds since last output) for the packet
        //
        //Returns:
        //  uint64 - the delta reference time value
        uint64 deltaReferenceTime() const;
        
        //API Function: hasExternalTimestamp
        //  Checks whether the packet contains the External Timestamp field
        //
        //Returns:
        //  bool - true if External Timestamp is present
        bool hasExternalTimestamp() const;

        //API Function: externalTimestamp
        //  Gets the External Timestamp value for the packet.
        //
        //Returns:
        //  <Timestamp> - the External Timestamp value
        Timestamp externalTimestamp() const;

        //API Function: externalTimestampValid
        //  Checks whether the External Timestamp value for the packet is valid.
        //
        //Returns:
        //  bool - true if valid
        bool externalTimestampValid() const;

        //API Function: hasDeltaExternalTime
        //  Checks whether the packet contains the Delta External Time field
        //
        //Returns:
        //  bool - true if Delta External Time is present
        bool hasDeltaExternalTime() const;

        //API Function: deltaExternalTimestamp
        //  Gets the Delta External Time value for the packet.
        //
        //Returns:
        //  <uint64> - the Delta External Time value
        uint64 deltaExternalTime() const;

        //API Function: deltaExternalTimeValid
        //  Checks whether the Delta External Time value for the packet is valid.
        //
        //Returns:
        //  bool - true if valid
        bool deltaExternalTimeValid() const;

        //API Function: get
        //  Get the shared field <MipDataPoint> with the specified field and qualifier.
        //  If qualifier is <MipTypes::CH_UNKNOWN> and there is only one data point for the field, that field will be returned.
        //  Note: most users will not need to use this function
        //
        //Parameters:
        //  field - the <MipTypes::ChannelField> of the data point to get
        //  qualifier - the <MipTypes::ChannelQualifier> of the data point to get. Default: MipTypes::CH_UNKNOWN
        //
        //Returns:
        //  <MipDataPoint> reference to the shared data point found
        const MipDataPoint& get(MipTypes::ChannelField field, MipTypes::ChannelQualifier qualifier = MipTypes::CH_UNKNOWN) const;
    };
} // namespace mscl