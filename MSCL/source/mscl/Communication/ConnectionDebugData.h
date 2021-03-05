/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/Types.h"
#include "mscl/Timestamp.h"

#include <vector>

namespace mscl
{
    //API Class: ConnectionDebugData
    //  Holds data used when the Connection debug mode is enabled.
    class ConnectionDebugData
    {
    public:
        //API Constructor: ConnectionDebugData
        //  Creates an empty ConnectionDebugData object.
        ConnectionDebugData();

        //Constructor: ConnectionDebugData
        //  Creates a ConnectionDebugData object.
        //
        //Parameters:
        //  fromRead - Whether the debug data is from a read operation (true) or a write operation (false).
        //  data - The <Bytes> that were read from or written to the connection.
        ConnectionDebugData(bool fromRead, const Bytes& data);

    private:
        //Variable: m_fromRead
        //  Whether the debug data is from a read operation (true) or a write operation (false).
        bool m_fromRead;

        //Variable: m_loggedTime
        //  The <Timestamp> of when the debug data was collected.
        Timestamp m_loggedTime;

        //Variable: m_data
        //  The <Bytes> that were read from or written to the connection.
        Bytes m_data;

    public:
        //API Function: fromRead
        //  Gets whether the debug data is from a read operation or a write operation.
        //
        //Returns:
        //  true if the debug data is from a read operation, false if it is from a write operation.
        bool fromRead() const;

        //API Function: timestamp
        //  Gets the <Timestamp> of when the debug data was collected.
        //
        //Returns:
        //  A <Timestamp> representing when the debug data was collected.
        const Timestamp& timestamp() const;

        //API Function: data
        //  Gets the <Bytes> that were read from or written to the connection.
        const Bytes& data() const;
    };

    //API Typedef: ConnectionDebugDataVec
    //  typedef for a vector of <ConnectionDebugData> objects.
    typedef std::vector<ConnectionDebugData> ConnectionDebugDataVec;
}