/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

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

        //Variable: m_utcTime
        //  The UTC timestamp provided by the Node in the data packet
        Timestamp m_utcTime;

        //Variable: m_utcTimeValid
        //  Whether the utc timestamp is valid or not
        bool m_utcTimeValid;

        //Variable: m_utcTimeFlags
        //  The flag that was transmitted with 
        uint16 m_utcTimeFlags;

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

        static bool isFieldTimestamp(const MipDataField& field);

        void parseTimeStamp(const MipDataField& field);

    public:
        //API Function: data
        //    Gets all the <MipDataPoints> that are contained within this packet
        //
        //Returns:
        //    The <MipDataPoints> that are contained within this packet
        const MipDataPoints& data() const;

        //API Function: collectedTimestamp
        //  Gets the <Timestamp> representing when the packet was collected by MSCL.
        //
        //Returns:
        //  A <Timestamp> representing when the packet was received by MSCL
        const Timestamp& collectedTimestamp() const;

        //API Function: utcTimestamp
        //  Gets the UTC <Timestamp> which was transmitted in the Mip Data Packet as a channel field.
        //  Note: This will return a Timestamp of 0 if <utcTimeValid> returns false.
        //
        //Returns:
        //  A <Timestamp> representing when the packet was received by MSCL
        const Timestamp& utcTimestamp() const;

        //API Function: utcTimeValid
        //  Whether the UTC Timestamp returned from the device is valid or not.
        //
        //Returns:
        //  true if the UTC Timestamp is valid, false if not.
        bool utcTimeValid() const;

        //API Function: utcTimeFlags
        //  Gets the UTC timestamp flags that were transmitted in the Mip Data Packet.
        //  Note: This will return 0 if <utcTimeValid> returns false.
        //
        //Returns:
        //  A uint16 representing the UTC timestamp flags.
        uint16 utcTimeFlags() const;
    };

    //API Typedef: MipDataPackets
    //    Typedef for a vector of <MipDataPacket> objects.
    typedef std::vector<MipDataPacket> MipDataPackets;
}