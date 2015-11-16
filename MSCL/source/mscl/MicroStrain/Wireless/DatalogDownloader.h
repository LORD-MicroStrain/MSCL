/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
//PUBLIC_HEADER
#pragma once

#include <memory>

#include "WirelessNode.h"
#include "ChannelMask.h"
#include "LoggedDataSweep.h"
#include "WirelessTypes.h"
#include "mscl/Version.h"
#include "mscl/MicroStrain/SampleRate.h"

namespace mscl
{
    class NodeMemory;

#ifndef SWIG
    struct DatalogSessionInfo
    {
        //Variable: startOfTrigger
        //    Whether the current data point is the start of a new trigger.
        //    This will be true for a single data point, in which case all
        //    of this DatalogSessionInfo will have been updated with new information.
        //    When moved to the next datapoint, startOfTrigger will be reset to false.
        bool startOfTrigger;

        //Variable: triggerType
        //    The <WirelessTypes::TriggerType> of the session.
        WirelessTypes::TriggerType triggerType;

        //Variable: numSweeps
        //    The total number of sweeps that are in the session.
        uint32 numSweeps;
        
        //Variable: sessionIndex
        //    The datalogging session index. This starts at 1 for the first session,
        //    and gets incremented for each additional session.
        uint16 sessionIndex;

        //Variable: activeChannels
        //    The <ChannelMask> for the session.
        ChannelMask activeChannels;

        //Variable: sampleRate
        //    The <SampleRate> for the session.
        SampleRate sampleRate;

        //Variable: timeBetweenSweeps
        //    The number of nanoseconds between each sweep, determined by the sample rate.
        uint64 timeBetweenSweeps;

        //Variable: dataType
        //    The <WirelessTypes::DataType> of the session.
        WirelessTypes::DataType dataType;

        //Variable: valueType
        //    The <ValueType> of the session.
        ValueType valueType;

        //Variable: userString
        //    The user entered string of the session (if any).
        std::string userString;

        //Variable: timestamp
        //    The starting timestamp for the session, in nanoseconds.
        uint64 timestamp;
        
        //TODO: add support for ChannelActions

        DatalogSessionInfo():
            startOfTrigger(false),
            triggerType(WirelessTypes::trigger_userInit),
            numSweeps(0),
            sessionIndex(0),
            activeChannels(0),
            sampleRate(SampleRate::Hertz(0)),
            timeBetweenSweeps(0),
            dataType(WirelessTypes::dataType_2byteUInt_16bitRes),
            valueType(valueType_uint16),
            userString(""),
            timestamp(0)
        {
        }
    };
#endif

    //API Class: DatalogDownloader
    //    Used to download logged data from a WirelessNode.
    class DatalogDownloader
    {
    public:
        //API Constructor: DatalogDownloader
        //    Creates a DatalogDownloader object. Datalogging information will immediately be read from the Node.
        //
        //Parameters:
        //    node - The <WirelessNode> to download the data from.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to read info from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        explicit DatalogDownloader(const WirelessNode& node);

        ~DatalogDownloader();

    private:
        DatalogDownloader();                                    //disabled default constructor
        DatalogDownloader(const DatalogDownloader&);            //disabled copy constructor
        DatalogDownloader& operator=(const DatalogDownloader&);    //disabled assignment operator

    private:
        //Constants: Datalogging Header Versions
        //    HEADER_VERSION_1_0 - Version 1.0
        //    HEADER_VERSION_2_0 - Version 2.0
        //    HEADER_VERSION_2_1 - Version 2.1
        static const Version HEADER_VERSION_1_0;
        static const Version HEADER_VERSION_2_0;
        static const Version HEADER_VERSION_2_1;

        //Variable: m_node
        //    The <WirelessNode> to download the data from.
        WirelessNode m_node;

        //Variable: m_foundFirstTrigger
        //    Whether or not the first trigger has been found.
        bool m_foundFirstTrigger;

        //Variable: m_outOfMemory
        //    Whether or not we requested data that is out of bounds of the memory.
        bool m_outOfMemory;

        //Variable: m_currentByte
        //    The current byte position into the Node's memory.
        uint64 m_currentByte;

        //Variable: m_sweepCount
        //    The 0-based count indicating which sweep we are currently on in the data.
        uint64 m_sweepCount;

        //Variable: m_logPage
        //    The last log page that contains datalogging data.
        uint16 m_logPage;

        //Variable: m_pageOffset
        //    The byte offset into the last log page containing datalogging data.
        uint16 m_pageOffset;

        //Variable: m_nodeMemory
        //    The <NodeMemory> object to help with interacting with the Node's datalogging memory.
        std::unique_ptr<NodeMemory> m_nodeMemory;

        //Variable: m_sessionInfo
        //    The <DatalogSessionInfo> containing information about the current trigger session data.
        DatalogSessionInfo m_sessionInfo;

    private:
        //Function: read_uint8
        //    Reads a 1-byte unsigned integer from the Node's memory.
        //
        //Parameters:
        //    position - The 0-based position to read from. This value will be incremented by 1 if successful.
        //
        //Returns:
        //    The 1-byte uint8 at the requested position in the Node's memory.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to download data from the Node.
        //    - <Error_NoData>: The requested bytePosition is outside the range of the datalogged data.
        //    - <Error_Connection>: A connection error has occurred.
        uint8 read_uint8(uint64& position);

        //Function: read_uint16
        //    Reads a 2-byte unsigned integer from the Node's memory.
        //
        //Parameters:
        //    position - The 0-based position to read from. This value will be incremented by 2 if successful.
        //
        //Returns:
        //    The uint16 at the requested position in the Node's memory.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to download data from the Node.
        //    - <Error_NoData>: The requested bytePosition is outside the range of the datalogged data.
        //    - <Error_Connection>: A connection error has occurred.
        uint16 read_uint16(uint64& position);

        //Function: read_uint32
        //    Reads a 4-byte unsigned integer from the Node's memory.
        //
        //Parameters:
        //    position - The 0-based position to read from. This value will be incremented by 4 if successful.
        //
        //Returns:
        //    The uint32 at the requested position in the Node's memory.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to download data from the Node.
        //    - <Error_NoData>: The requested bytePosition is outside the range of the datalogged data.
        //    - <Error_Connection>: A connection error has occurred.
        uint32 read_uint32(uint64& position);

        //Function: read_float
        //    Reads a 4-byte float from the Node's memory.
        //
        //Parameters:
        //    position - The 0-based position to read from.  This value will be incremented by 4 if successful.
        //
        //Returns:
        //    The float at the requested position in the Node's memory.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to download data from the Node.
        //    - <Error_NoData>: The requested bytePosition is outside the range of the datalogged data.
        //    - <Error_Connection>: A connection error has occurred.
        float read_float(uint64& position);

        //Function: read_string
        //    Reads a string of the specified length from the Node's memory.
        //
        //Parameters:
        //    position - The 0-based position to start reading from. This value will be incremented by the length read if successful.
        //    length - The size (number of characters) to read for.
        //
        //Returns:
        //    The string at the requested position in the Node's memory, of the requested length.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to download data from the Node.
        //    - <Error_NoData>: The requested bytePosition is outside the range of the datalogged data.
        //    - <Error_Connection>: A connection error has occurred.
        std::string read_string(uint64& position, uint64 length);

        //Function: isStartOfTrigger
        //    Checks whether the given position is a start of a new trigger session.
        //
        //Parameters:
        //    position - The 0-based position to read from to check for a start of trigger.
        //
        //Returns:
        //    true if a start of trigger was found, false otherwise.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to download data from the Node.
        //    - <Error_Connection>: A connection error has occurred.
        bool isStartOfTrigger(uint64 position);

        //Function: parseTriggerHeader
        //    Parses a trigger header from the current byte position. The current datalogging session info in this class is updated.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to download data from the Node.
        //    - <Error_Connection>: A connection error has occurred.
        void parseTriggerHeader();

    public:
        //API Function: complete
        //    Checks if all of the data has been downloaded (no more data available).
        //
        //Returns:
        //    true if all the data has been downloaded, false if there is still more data to download.
        bool complete();

        //API Function: getNextData
        //    Gets the next <LoggedDataSweep> that is logged to the Node.
        //
        //Returns:
        //    A <LoggedDataSweep> containing the next data sweep that was logged to the Node.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to download data from the Node.
        //    - <Error_NoData>: The requested bytePosition is outside the range of the datalogged data.
        //    - <Error_Connection>: A connection error has occurred.
        LoggedDataSweep getNextData();

        //API Function: startOfSession
        //    Gets whether a new datalogging session has been found (after calling <getNextData>).
        //    This will be true for a single <LoggedDataSweep>, signifying that all of the DatalogDownloader's 
        //    info has been updated with new information (sample rate, session index, etc.) about this sweep.
        //
        //Returns:
        //    true if a new datalogging session has been found, false otherwise.
        bool startOfSession();

        //API Function: triggerType
        //    Gets the <WirelessTypes::TriggerType> of the current datalogging session.
        //
        //Returns:
        //    The <WirelessTypes::TriggerType> of the current datalogging session.
        WirelessTypes::TriggerType triggerType();

        //API Function: totalSweeps
        //    Gets the total number of sweeps that are in the current datalogging session.
        //
        //Returns:
        //    The total number of sweeps that are in the current datalogging session.
        uint32 totalSweeps();

        //API Function: sessionIndex
        //    Gets the index of the current datalogging session. 
        //    This starts at 1 for the first session, and is incremented for each additional session.
        //
        //Returns:
        //    The index of the current datalogging session. 
        uint16 sessionIndex();

        //API Function: sampleRate
        //    Gets the <SampleRate> of the current datalogging session.
        //
        //Returns:
        //    The <SampleRate> of the current datalogging session.
        const SampleRate& sampleRate();

        //API Function: userString
        //    Gets the user entered string of the current datalogging session (if any).
        //
        //Returns:
        //    The user entered string of the current datalogging session, or an empty string if none was provided.
        const std::string& userString();
    };
}
