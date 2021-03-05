/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "MipPacket.h"
#include "mscl/Timestamp.h"
#include "mscl/Types.h"
#include "mscl/MicroStrain/MIP/MipDataPoint.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "MipPacket.h"

#include <memory>
#include <vector>

namespace mscl
{
    class MipFieldParser;
    

    //API Class: MipDataPacket
    //    A Mip Data Packet that contains both valid and invalid data from a MIP Device.
    class MipDataPacket : public MipPacket
    {
        friend class MipPacketCollector;    //allow MipPacketColletor to adjust the timestamp of the packet

    public:
        //Constructor: MipDataPacket
        //    Creates a default constructed MipDataPacket
        MipDataPacket();

        //Constructor: MipDataPacket
        //    Creates a MipDataPacket object
        //
        //Parameters:
        //    packet - The <MipPacket> that was found to be a MipDataPacket
        explicit MipDataPacket(const MipPacket& packet);

    private:
        //Variable: m_dataFields
        //    The <MipDataFields> that are contained within this packet
        MipDataFields m_dataFields;

        //Variable: m_points
        //    The <MipDataPoints> within this packet
        MipDataPoints m_points;

        //Variable: m_collectedTime
        //    The <Timestamp> of when this packet was received
        Timestamp m_collectedTime;

        //Variable: m_deviceTime
        //  The timestamp that was provided by the Node in the data packet
        Timestamp m_deviceTime;

        //Variable: m_hasDeviceTime
        //  Whether the device timestamp was included in the data packet.
        bool m_hasDeviceTime;

        //Variable: m_deviceTimeValid
        //  Whether the device timestamp is valid or not (based on flags and/or it being a reasonable timestamp)
        bool m_deviceTimeValid;

        //Variable: m_deviceTimeFlags
        //  The flags value that the device timestamp was transmitted with.
        uint16 m_deviceTimeFlags;

    private:
        //Function: parseDataFields
        //    Parses the passed in MipPacket for all the field information and adds a data field to the <MipDataFields> container
        //    Also parses out all the <MipDataPoints> in the fields that were created and adds them to m_points
        void parseDataFields();

        //Function: parsePointsInField
        //    Parses an <MipDataField> for MipDataPoints and puts them into m_points
        //
        //Parameters:
        //    field - The <MipDataField> to parse for data points
        void parsePointsInField(const MipDataField& field);

        //Function: parseTimestamp
        //  Parses a MIP timestamp field, and sets the device time member variables.
        //
        //Parameters:
        //    field - The <MipDataField> to parse the time from
        void parseTimeStamp(const MipDataField& field);

        //Function: timestampWithinRange
        //  Checks if the given timestamp is within range of the <collectedTimestamp>.
        //
        //Parameters:
        //  timestamp - The <Timestamp> to validate.
        //
        //Returns:
        //  true if the given timestamp is within 1 hour of the <collectedTimestamp>, false otherwise.
        bool timestampWithinRange(const Timestamp& timestamp) const;

    public:
        //API Function: data
        //    Gets all the <MipDataPoints> that are contained within this packet.
        //
        //Returns:
        //    The <MipDataPoints> that are contained within this packet.
        const MipDataPoints& data() const;

        //API Function: collectedTimestamp
        //  Gets the <Timestamp> representing when the packet was collected by MSCL.
        //
        //Returns:
        //  A <Timestamp> representing when the packet was received by MSCL.
        const Timestamp& collectedTimestamp() const;

        //API Function: deviceTimestamp
        //  Gets the <Timestamp> which was transmitted in the Mip Data Packet as a channel field.
        //  Note: This will return a Timestamp of 0 if <deviceTimeValid> returns false.
        //
        //Returns:
        //  A <Timestamp> that was included in the data packet itself as a field.
        const Timestamp& deviceTimestamp() const;

        //API Function: hasDeviceTime
        //  Whether the data packet had a Timestamp field included in it.
        //
        //Returns:
        //  true if the data packet included a Timestamp field, false if it did not.
        bool hasDeviceTime() const;

        //API Function: deviceTimeValid
        //  Whether the Timestamp field sent from the device is valid or not.
        //
        //Returns:
        //  true if the Timestamp is valid, false if not.
        bool deviceTimeValid() const;

        //API Function: deviceTimeFlags
        //  Gets the timestamp flags that were transmitted in the Mip Data Packet.
        //  Note: This will return 0 if <deviceTimeValid> returns false.
        //
        //Returns:
        //  The uint16 flags that were sent with the device timestamp.
        uint16 deviceTimeFlags() const;
    };

    //API Typedef: MipDataPackets
    //    Typedef for a vector of <MipDataPacket> objects.
    typedef std::vector<MipDataPacket> MipDataPackets;
}