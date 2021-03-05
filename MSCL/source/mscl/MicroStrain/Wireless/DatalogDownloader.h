/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include <memory>

#include "CalCoefficients.h"
#include "ChannelMask.h"
#include "LoggedDataSweep.h"
#include "WirelessNode.h"
#include "WirelessTypes.h"
#include "Packets/WirelessDataPacket.h"
#include "mscl/TimestampCounter.h"
#include "mscl/Version.h"
#include "mscl/MicroStrain/SampleRate.h"

namespace mscl
{
    class NodeMemory;

#ifndef SWIG

    struct DatalogSessionInfo
    {
        //Variable: sessionInfoUpdated
        //  Indicates whether the session info has been updated since the last time <getNextData> was called.
        bool sessionInfoUpdated;

        //Variable: calCoefficientsUpdated
        //  Indicates whether calibration coefficients have been updates since the last time <getNextData> was called.
        bool calCoefficientsUpdated;

        //Variable: startOfTrigger
        //    Whether the current data point is the start of a new trigger/session.
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

        //Variable: derivedRate
        //    The <SampleRate> of any derived data.
        SampleRate derivedRate;

        //Variable: timeBetweenSweeps
        //    The number of nanoseconds between each sweep, determined by the sample rate.
        uint64 timeBetweenSweeps;

        //Variable: derivedTimeBetweenSweeps
        //    The number of nanoseconds between each derived sweep, determined by the derived sample rate.
        uint64 derivedTimeBetweenSweeps;

        //Variable: dataType
        //    The <WirelessTypes::DataType> of the session.
        WirelessTypes::DataType dataType;

        //Variable: valueType
        //    The <ValueType> of the session.
        ValueType valueType;

        //Variable: userString
        //    The user entered string of the session (if any).
        std::string userString;

        TimestampCounter tsCounter;

        //Variable: timestamp
        //    The starting timestamp for the session, in nanoseconds.
        uint64 timestamp;

        //Variable: calCoefficients
        //    A map of <WirelessChannel::ChannelId> to <CalCoefficients>.
        ChannelCalMap calCoefficients;

        DatalogSessionInfo():
            sessionInfoUpdated(false),
            calCoefficientsUpdated(false),
            startOfTrigger(false),
            triggerType(WirelessTypes::trigger_userInit),
            numSweeps(0),
            sessionIndex(0),
            activeChannels(0),
            sampleRate(SampleRate::Hertz(0)),
            derivedRate(SampleRate::Hertz(0)),
            timeBetweenSweeps(0),
            derivedTimeBetweenSweeps(0),
            dataType(WirelessTypes::dataType_uint16),
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
        //    - <Error_NotSupported>: Logged data is not supported by the Node.
        //    - <Error_NodeCommunication>: Failed to read info from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        explicit DatalogDownloader(const WirelessNode& node);

        //API Constructor: DatalogDownloader
        //  Advanced Constructor for creating a DatalogDownloader object with known parameters (not compatible with datalog version 1).
        //  Note: In most cases, you should use the standard DatalogDownloader constructor instead of this one,
        //        which will automatically determine the start and end positions for you.
        //
        //Parameters:
        //  node - The <WirelessNode> to download the data from.
        //  startAddress - The flash address of the first log header.
        //  size - The max number of logged bytes.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Logged data is not supported by the Node.
        //    - <Error_NodeCommunication>: Failed to read info from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        DatalogDownloader(const WirelessNode& node, uint32 startAddress, uint32 size);

        ~DatalogDownloader();

        DatalogDownloader() = delete;                                       //disabled default constructor
        DatalogDownloader(const DatalogDownloader&) = delete;               //disabled copy constructor
        DatalogDownloader& operator=(const DatalogDownloader&) = delete;    //disabled assignment operator

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

        //Variable: m_sweepCount
        //    The 0-based count indicating which sweep we are currently on in the data.
        uint64 m_sweepCount;

        //Variable: m_nodeMemory
        //    The <NodeMemory> object to help with interacting with the Node's datalogging memory.
        std::unique_ptr<NodeMemory> m_nodeMemory;

        //Variable: m_sessionInfo
        //    The <DatalogSessionInfo> containing information about the current trigger session data.
        DatalogSessionInfo m_sessionInfo;

        //Variable: m_dataDownloadVersion
        //  The version of the datalog download procedure to use.
        uint8 m_datalogDownloadVersion;

        //Variable: m_isMathData
        //  Whether the data to parse next is math data (true) or standard channel data (false).
        bool m_isMathData;

        //Variable: m_mathMetaData
        //  A vector of the <WirelessDataPacket::AlgorithmMetaData> for the current data section (gets updated each math block header).
        std::vector<WirelessDataPacket::AlgorithmMetaData> m_mathMetaDeta;

    private:
        //Function: parseTriggerHeader_v1
        //    Parses a (v1) trigger header from the current byte position. The current datalogging session info in this class is updated.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to download data from the Node.
        //    - <Error_Connection>: A connection error has occurred.
        void parseTriggerHeader_v1();

        //Function: parseTriggerHeader_v2
        //    Parses a (v2) trigger header from the current byte position. The current datalogging session info in this class is updated.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to download data from the Node.
        //    - <Error_Connection>: A connection error has occurred.
        void parseTriggerHeader_v2();

        void parseRawCalData();

        void parseDerivedMetaData(uint8 numActiveAlgorithms);

        //Function: parseNextSweep
        //  Parses the next Raw Data Sweep from the current byte position.
        LoggedDataSweep parseNextSweep();

        //Function: parseNextMathSweep
        //  Parses the next Math/Derived Data Sweep from the current byte position.
        LoggedDataSweep parseNextMathSweep();

    public:
        //API Function: complete
        //  Checks if all of the data has been downloaded (no more data available).
        //  Note: This may be updated each time <getNextData> is called.
        //
        //Returns:
        //  true if all the data has been downloaded, false if there is still more data to download.
        bool complete();

        //API Function: percentComplete
        //  Gets the percent completion of the download.
        //  Note: This will be updated each time <getNextData> is called.
        //
        //Returns:
        //  The percent completion of the download (0 - 100).
        float percentComplete() const;

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

        //API Function: metaDataUpdated
        //  Gets whether the any of the meta data (sample rate, cal coefficients, etc) has been updated since the last call to <getNextData>.
        //  This will be true for a single <LoggedDataSweep> (after calling <getNextData>), signifying that you should interrogate
        //  all of the meta data on this DatalogDownloader object again to get updated information which may have changed.
        //
        //Returns:
        //  true if the meta data has been updated, false otherwise.
        bool metaDataUpdated() const;

        //API Function: calCoefficientsUpdated
        //  Gets whether the calibration coefficients information has been updated since the last call to <getNextData>.
        //  This will be true for a single <LoggedDataSweep> (after calling <getNextData>).
        bool calCoefficientsUpdated() const;

        //API Function: startOfSession
        //  Gets whether a new datalogging session has been found (after calling <getNextData>). This will be true for a single <LoggedDataSweep>.
        //  Note: May be changed whenever <metaDataUpdated> returns true.
        //
        //Returns:
        //  true if a new datalogging session has been found, false otherwise.
        bool startOfSession() const;

        //API Function: sessionIndex
        //  Gets the index of the current datalogging session.
        //  Note: May be changed whenever <startOfSession> returns true.
        //
        //Returns:
        //  The index of the current datalogging session.
        uint16 sessionIndex() const;

        //API Function: sampleRate
        //  Gets the <SampleRate> of the current datalogging session.
        //  Note: May be changed whenever <metaDataUpdated> returns true.
        //
        //Returns:
        //  The <SampleRate> of the current datalogging session.
        const SampleRate& sampleRate() const;

        //API Function: userString
        //  Gets the user entered string of the current datalogging session (if any).
        //  Note: A user string can only be provided with Armed Datalogging, which is a legacy sampling mode not supported on new products.
        //  Note: May be changed whenever <metaDataUpdated> returns true.
        //
        //Returns:
        //    The user entered string of the current datalogging session, or an empty string if none was provided.
        const std::string& userString() const;

        //API Function: calCoefficients
        //  Gets the <ChannelCalMap> of the current datalogging session.
        //  Note: May be changed whenever <metaDataUpdated> returns true.
        //
        //Returns:
        //  The <ChannelCalMap> of <WirelessChannel::ChannelId>s to <CalCoefficients>. 
        const ChannelCalMap& calCoefficients() const;
    };
}
