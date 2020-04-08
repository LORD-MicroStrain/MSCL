/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "DatalogDownloader.h"

#include "Configuration/NodeEepromHelper.h"
#include "Commands/DatalogSessionInfoResult.h"
#include "Features/NodeFeatures.h"
#include "Packets/WirelessDataPacket.h"
#include "NodeMemory_v1.h"
#include "NodeMemory_v2.h"
#include "WirelessDataPoint.h"
#include "mscl/Utils.h"

namespace mscl
{
    const Version DatalogDownloader::HEADER_VERSION_1_0(1, 0);
    const Version DatalogDownloader::HEADER_VERSION_2_0(2, 0);
    const Version DatalogDownloader::HEADER_VERSION_2_1(2, 1);

    DatalogDownloader::DatalogDownloader(const WirelessNode& node):
        m_node(node),
        m_foundFirstTrigger(false),
        m_outOfMemory(false),
        m_sweepCount(0),
        m_isMathData(false)
    {
        //verify the node supports logged data
        if(!node.features().supportsLoggedData())
        {
            throw Error_NotSupported("Logging is not supported by this Node.");
        }

        m_datalogDownloadVersion = m_node.features().datalogDownloadVersion();

        if(m_datalogDownloadVersion == 1)
        {
            //get the datalogging information from the Node
            uint16 logPage = m_node.eepromHelper().read_logPage();
            uint16 pageOffset = m_node.eepromHelper().read_logPageOffset();

            //create the NodeMemory object (v1)
            m_nodeMemory.reset(new NodeMemory_v1(m_node, logPage, pageOffset));
        }
        else
        {
            BaseStation& base = m_node.getBaseStation();

            //get the datalogging session info
            DatalogSessionInfoResult dlInfo;
            if(!base.node_getDatalogSessionInfo(node.protocol(base.communicationProtocol()), node.nodeAddress(), dlInfo))
            {
                throw Error_NodeCommunication(m_node.nodeAddress(), "Failed to get the Datalog Session Info");
            }

            //get the FlashInfo
            FlashInfo flashInfo = m_node.eepromHelper().read_flashInfo();

            //create the Node Memory object (v2)
            m_nodeMemory.reset(new NodeMemory_v2(m_node, flashInfo, dlInfo.startAddress, dlInfo.maxLoggedBytes));
        }
    }

    DatalogDownloader::DatalogDownloader(const WirelessNode& node, uint32 startAddress, uint32 size):
        m_node(node),
        m_foundFirstTrigger(false),
        m_outOfMemory(false),
        m_sweepCount(0),
        m_isMathData(false)
    {
        //verify the node supports logged data
        if(!node.features().supportsLoggedData())
        {
            throw Error_NotSupported("Logging is not supported by this Node.");
        }

        m_datalogDownloadVersion = m_node.features().datalogDownloadVersion();

        if(m_datalogDownloadVersion == 1)
        {
            //get the datalogging information from the Node
            uint16 logPage = m_node.eepromHelper().read_logPage();
            uint16 pageOffset = m_node.eepromHelper().read_logPageOffset();

            //create the NodeMemory object (v1)
            m_nodeMemory.reset(new NodeMemory_v1(m_node, logPage, pageOffset));
        }
        else
        {
            //get the FlashInfo
            FlashInfo flashInfo = m_node.eepromHelper().read_flashInfo();

            //create the Node Memory object (v2)
            m_nodeMemory.reset(new NodeMemory_v2(m_node, flashInfo, startAddress, size));
        }
    }

    DatalogDownloader::~DatalogDownloader()
    {
        m_nodeMemory.reset(nullptr);
    }

    void DatalogDownloader::parseTriggerHeader_v1()
    {
        //TODO: What if an exception is thrown in here??

        //reset the sweep count
        m_sweepCount = 0;

        //move passed the start of header bytes
        m_nodeMemory->skipBytes(3);

        //read the trigger type
        m_sessionInfo.triggerType = static_cast<WirelessTypes::TriggerType>(m_nodeMemory->read_uint8());

        //read the header version
        uint8 versionMajor = m_nodeMemory->read_uint8();
        uint8 versionMinor = m_nodeMemory->read_uint8();
        Version headerVersion(versionMajor, versionMinor);

        //read the number of bytes before the channel data
        uint16 bytesBeforeData = m_nodeMemory->read_uint16();
        uint32 byteCounter = m_nodeMemory->readIndex();    //used to calculate if we need to later consume (throw out) bytes that we don't know how to parse

        //read the number of sweeps
        m_sessionInfo.numSweeps = m_nodeMemory->read_uint16();

        //Header Version 2.1+
        if(headerVersion >= HEADER_VERSION_2_1)
        {
            //the number of sweeps in the header should be multiplied by 100
            m_sessionInfo.numSweeps *= 100;
        }

        //read the session index
        m_sessionInfo.sessionIndex = m_nodeMemory->read_uint16();

        //read the active channel mask
        m_sessionInfo.activeChannels = ChannelMask(m_nodeMemory->read_uint16());

        //read the sample rate
        uint16 sampleRateVal = m_nodeMemory->read_uint16();

        //if it is an armed datalogging rate, we need to convert it to a WirelessSampleRate
        //Note: if not a datalogging rate, this will just cast it to a WirelessSampleRate without conversion.
        WirelessTypes::WirelessSampleRate rate = WirelessTypes::dataloggingRateToSampleRate(sampleRateVal);
        m_sessionInfo.sampleRate = SampleRate::FromWirelessEepromValue(rate);
        m_sessionInfo.timeBetweenSweeps = m_sessionInfo.sampleRate.samplePeriod().getNanoseconds();

        if(headerVersion >= HEADER_VERSION_2_0)
        {
            //read the data type
            m_sessionInfo.dataType = static_cast<WirelessTypes::DataType>(m_nodeMemory->read_uint8());

            m_nodeMemory->skipBytes(1);    //unused byte
        }
        else
        {
            //no data type in the header, always uint16
            m_sessionInfo.dataType = WirelessTypes::dataType_uint16_12bitRes;
        }

        m_sessionInfo.valueType = WirelessTypes::dataTypeToValueType(m_sessionInfo.dataType);

        //read the number of user entered bytes
        uint16 numUserBytes = m_nodeMemory->read_uint16();

        //read the user entered string
        m_sessionInfo.userString = m_nodeMemory->read_string(numUserBytes);

        //if the user string is an odd number of bytes
        if(m_sessionInfo.userString.length() % 2 != 0)
        {
            //the data has 1 extra byte (always even), need to throw it out
            m_nodeMemory->skipBytes(1);

            if(headerVersion <= HEADER_VERSION_2_1)
            {
                //there is a bug in header version 2.1 and below where the
                //extra user byte isn't added to the bytesBeforeData count
                bytesBeforeData += 1;
            }
        }

        //====================================================
        //MOVE PASSED ANY EXTRA BYTES
        m_nodeMemory->skipBytes(bytesBeforeData - (m_nodeMemory->readIndex() - byteCounter));
        //====================================================

        //read the number of bytes per channel
        uint16 bytesPerChannel = m_nodeMemory->read_uint16();

        //loop through all of the active channels to get channel action information
        uint8 channelItr = 0;
        uint8 lastChannel = m_sessionInfo.activeChannels.lastChEnabled();

        WirelessChannel::ChannelId chId;
        WirelessTypes::CalCoef_EquationType equation;
        WirelessTypes::CalCoef_Unit unit;
        float slope;
        float offset;

        ChannelCalMap oldCals = m_sessionInfo.calCoefficients;

        //clear the calCoefficients map so we get rid of any we might not have anymore (channels that have been removed?)
        m_sessionInfo.calCoefficients.clear();

        for(channelItr = 1; channelItr <= lastChannel; ++channelItr)
        {
            //only contains channel action info if the channel is in the data
            if(m_sessionInfo.activeChannels.enabled(channelItr))
            {
                byteCounter = m_nodeMemory->readIndex();

                chId = static_cast<WirelessChannel::ChannelId>(channelItr);

                //read the channel action equation
                equation = static_cast<WirelessTypes::CalCoef_EquationType>(m_nodeMemory->read_uint8());

                //read the channel action unit
                unit = static_cast<WirelessTypes::CalCoef_Unit>(m_nodeMemory->read_uint8());

                //check for uninitialized value
                if(unit == 0xAA || unit == 0xFF)
                {
                    unit = WirelessTypes::unit_none;
                }

                //read the channel action slope
                slope = m_nodeMemory->read_float(Utils::littleEndian);

                //read the channel action offset
                offset = m_nodeMemory->read_float(Utils::littleEndian);

                CalCoefficients cals = CalCoefficients(equation, unit, LinearEquation(slope, offset));

                //if we already have calibration coefficients for this channel in the map
                auto calItr = oldCals.find(chId);
                if(calItr != oldCals.end())
                {
                    //if we are changing at least 1 calibration coefficient
                    if(calItr->second != cals)
                    {
                        m_sessionInfo.calCoefficientsUpdated = true;
                    }
                }

                //add the cal coefficients to the session info
                m_sessionInfo.calCoefficients[chId] = cals;

                //====================================================
                //MOVE PASSED ANY EXTRA BYTES
                m_nodeMemory->skipBytes(bytesPerChannel - (m_nodeMemory->readIndex() - byteCounter));
                //====================================================
            }
        }

        //if we've added or removed any cal coefficients
        if(m_sessionInfo.calCoefficients.size() != oldCals.size())
        {
            m_sessionInfo.calCoefficientsUpdated = true;
        }

        //read the number of bytes before the end of the header
        uint16 bytesBeforeEnd = m_nodeMemory->read_uint16();
        Utils::checkBounds_min(bytesBeforeEnd, static_cast<uint16>(8));  //seems to be a bug where this number is less than what is actually there (8 is normal)
        byteCounter = m_nodeMemory->readIndex();

        //read the timestamp bytes
        uint32 timestampSeconds = m_nodeMemory->read_uint32();
        uint32 timestampNanos = m_nodeMemory->read_uint32();

        //build the full nanosecond resolution timestamp
        m_sessionInfo.tsCounter.reset(sampleRate(), ((static_cast<uint64>(timestampSeconds) * TimeSpan::NANOSECONDS_PER_SECOND) + timestampNanos));

        //====================================================
        //MOVE PASSED ANY EXTRA BYTES
        m_nodeMemory->skipBytes(bytesBeforeEnd - (m_nodeMemory->readIndex() - byteCounter));
        //====================================================

        //set the startOfTrigger flag to true
        m_sessionInfo.startOfTrigger = true;

        m_sessionInfo.sessionInfoUpdated = true;
    }

    void DatalogDownloader::parseTriggerHeader_v2()
    {
        //TODO: What if an exception is thrown in here??

        m_sessionInfo.calCoefficientsUpdated = false;
        m_sessionInfo.sessionInfoUpdated = false;
        m_sessionInfo.startOfTrigger = false;

        uint8 headerId = m_nodeMemory->read_uint8();

        if(headerId == NodeMemory_v2::REFRESH_HEADER_ID)
        {
            //nothing changed, just getting more sweeps of data
            m_nodeMemory->skipBytes(1); //skip sweep count
        }
        else if(headerId == NodeMemory_v2::SESSION_CHANGE_HEADER_ID)
        {
            //reset the sweep count
            m_sweepCount = 0;

            m_nodeMemory->skipBytes(1); //skip sweep count

            //read the timestamp
            m_sessionInfo.tsCounter.reset(m_nodeMemory->read_uint64(Utils::littleEndian));

            //read the session index
            uint16 newSessionIndex = m_nodeMemory->read_uint16(Utils::littleEndian);

            //only update sessionInfoUpdated flag if index has changed
            if(m_sessionInfo.sessionIndex != newSessionIndex)
            {
                m_sessionInfo.sessionIndex = newSessionIndex;
                m_sessionInfo.startOfTrigger = true;
                m_sessionInfo.sessionInfoUpdated = true;
            }
        }
        else if(headerId == NodeMemory_v2::SESSION_CHANGE_HEADER_ID_V2)
        {
            //reset the sweep count
            m_sweepCount = 0;

            m_nodeMemory->skipBytes(1); //skip sweep count

            NodeMemory_v2::SweepType sweepType = static_cast<NodeMemory_v2::SweepType>(m_nodeMemory->read_uint8());
            if(sweepType == NodeMemory_v2::sweepType_raw)
            {
                //if we are switching from math to raw sweeps
                if(m_isMathData)
                {
                    //set the sessionInfoUpdated flag to true
                    m_sessionInfo.sessionInfoUpdated = true;
                }

                m_isMathData = false;
            }
            else if(sweepType == NodeMemory_v2::sweepType_derived)
            {
                //if we are switching from raw to math sweeps
                if(!m_isMathData)
                {
                    //set the sessionInfoUpdated flag to true
                    m_sessionInfo.sessionInfoUpdated = true;
                }

                m_isMathData = true;
            }

            //update the timestampCounter with the new timestamp, and adjust sample rate if sweep type has changed
            m_sessionInfo.tsCounter.reset(sampleRate(), m_nodeMemory->read_uint64(Utils::littleEndian));

            //read the session index
            uint16 newSessionIndex = m_nodeMemory->read_uint16(Utils::littleEndian);

            //only update sessionInfoUpdated flag if index has changed
            if(m_sessionInfo.sessionIndex != newSessionIndex)
            {
                m_sessionInfo.sessionIndex = newSessionIndex;
                m_sessionInfo.startOfTrigger = true;
                m_sessionInfo.sessionInfoUpdated = true;
            }
        }
        else if(headerId == NodeMemory_v2::BLOCK_HEADER_ID)
        {
            //reset the sweep count
            m_sweepCount = 0;

            m_sessionInfo.sessionInfoUpdated = true;

            uint8 version = m_nodeMemory->read_uint8();

            if(version == 0)
            {
                m_isMathData = false;

                m_nodeMemory->skipBytes(4); //skip header size, sweep count, and block index

                uint16 newSessionIndex = m_nodeMemory->read_uint16(Utils::littleEndian);

                if(!m_foundFirstTrigger || m_sessionInfo.sessionIndex != newSessionIndex)
                {
                    m_sessionInfo.sessionIndex = newSessionIndex;
                    m_sessionInfo.startOfTrigger = true;
                }

                uint64 newTimestamp = m_nodeMemory->read_uint64(Utils::littleEndian);

                //read the sample rate
                WirelessTypes::WirelessSampleRate rate = static_cast<WirelessTypes::WirelessSampleRate>(m_nodeMemory->read_uint8());

                m_sessionInfo.sampleRate = SampleRate::FromWirelessEepromValue(rate);
                m_sessionInfo.timeBetweenSweeps = m_sessionInfo.sampleRate.samplePeriod().getNanoseconds();

                //update the timestampCounter with the new timestamp, and adjust sample rate if sweep type has changed
                m_sessionInfo.tsCounter.reset(sampleRate(), newTimestamp);

                //read the active channel mask
                m_sessionInfo.activeChannels = ChannelMask(m_nodeMemory->read_uint16(Utils::littleEndian));

                //read the data type
                m_sessionInfo.dataType = static_cast<WirelessTypes::DataType>(m_nodeMemory->read_uint8());
                m_sessionInfo.valueType = WirelessTypes::dataTypeToValueType(m_sessionInfo.dataType);

                //parse the raw calibration data
                parseRawCalData();
            }
            else if(version == 1)
            {
                m_nodeMemory->skipBytes(2); //skip header size and sweep count

                NodeMemory_v2::SweepType sweepType = static_cast<NodeMemory_v2::SweepType>(m_nodeMemory->read_uint8());
                if(sweepType == NodeMemory_v2::sweepType_raw)
                {
                    m_isMathData = false;
                }
                else if(sweepType == NodeMemory_v2::sweepType_derived)
                {
                    m_isMathData = true;
                }

                m_nodeMemory->skipBytes(2); //skip block index

                uint16 newSessionIndex = m_nodeMemory->read_uint16(Utils::littleEndian);

                //only update sessionInfoUpdated flag if index has changed
                if(!m_foundFirstTrigger || m_sessionInfo.sessionIndex != newSessionIndex)
                {
                    m_sessionInfo.sessionIndex = newSessionIndex;
                    m_sessionInfo.startOfTrigger = true;
                }

                uint64 newTimestamp = m_nodeMemory->read_uint64(Utils::littleEndian);

                //read the raw sample rate
                WirelessTypes::WirelessSampleRate rawRate = static_cast<WirelessTypes::WirelessSampleRate>(m_nodeMemory->read_uint8());

                m_sessionInfo.sampleRate = SampleRate::FromWirelessEepromValue(rawRate);
                m_sessionInfo.timeBetweenSweeps = m_sessionInfo.sampleRate.samplePeriod().getNanoseconds();

                //read the active channel mask
                m_sessionInfo.activeChannels = ChannelMask(m_nodeMemory->read_uint16(Utils::littleEndian));

                //read the data type
                m_sessionInfo.dataType = static_cast<WirelessTypes::DataType>(m_nodeMemory->read_uint8());
                m_sessionInfo.valueType = WirelessTypes::dataTypeToValueType(m_sessionInfo.dataType);

                uint8 numActiveAlgorithms = m_nodeMemory->read_uint8();

                uint32 calculationRate = m_nodeMemory->read_uint32(Utils::littleEndian);

                //the upper bit determines hz (1) vs seconds (0)
                bool isHertz = Utils::bitIsSet(calculationRate, 31);
                if(isHertz)
                {
                    //turn off the bit to get the real value
                    Utils::setBit(calculationRate, 31, false);
                    m_sessionInfo.derivedRate = SampleRate::Hertz(calculationRate);
                }
                else
                {
                    m_sessionInfo.derivedRate = SampleRate::Seconds(calculationRate);
                }

                m_sessionInfo.derivedTimeBetweenSweeps = m_sessionInfo.derivedRate.samplePeriod().getNanoseconds();

                //update the timestampCounter with the new timestamp, and adjust sample rate if sweep type has changed
                m_sessionInfo.tsCounter.reset(sampleRate(), newTimestamp);

                //parse the raw calibration data
                parseRawCalData();

                //parse the derived meta data
                parseDerivedMetaData(numActiveAlgorithms);
            }
        }
        else
        {
            //shouldn't be parsing invalid headers at this point
            assert(false);
        }
    }

    void DatalogDownloader::parseRawCalData()
    {
        //loop through all of the active channels to get channel action information
        uint8 channelItr = 0;
        uint8 lastChannel = m_sessionInfo.activeChannels.lastChEnabled();

        WirelessChannel::ChannelId chId;
        WirelessTypes::CalCoef_EquationType equation;
        WirelessTypes::CalCoef_Unit unit;
        float slope;
        float offset;

        ChannelCalMap oldCals = m_sessionInfo.calCoefficients;

        //clear the calCoefficients map so we get rid of any we might not have anymore (channels that have been removed?)
        m_sessionInfo.calCoefficients.clear();

        for(channelItr = 1; channelItr <= lastChannel; ++channelItr)
        {
            //only contains channel action info if the channel is in the data
            if(m_sessionInfo.activeChannels.enabled(channelItr))
            {
                chId = static_cast<WirelessChannel::ChannelId>(channelItr);

                //read the channel action equation
                equation = static_cast<WirelessTypes::CalCoef_EquationType>(m_nodeMemory->read_uint8());

                //read the channel action unit
                unit = static_cast<WirelessTypes::CalCoef_Unit>(m_nodeMemory->read_uint8());

                //check for uninitialized value
                if(unit == 0xAA || unit == 0xFF)
                {
                    unit = WirelessTypes::unit_none;
                }

                //read the channel action slope
                slope = m_nodeMemory->read_float(Utils::littleEndian);

                //read the channel action offset
                offset = m_nodeMemory->read_float(Utils::littleEndian);

                CalCoefficients cals = CalCoefficients(equation, unit, LinearEquation(slope, offset));

                //if we already have calibration coefficients for this channel in the map
                auto calItr = oldCals.find(chId);
                if(calItr != oldCals.end())
                {
                    //if we are changing at least 1 calibration coefficient
                    if(calItr->second != cals)
                    {
                        m_sessionInfo.calCoefficientsUpdated = true;
                    }
                }

                //add the cal coefficients to the session info
                m_sessionInfo.calCoefficients[chId] = cals;
            }
        }

        //if we've added or removed any cal coefficients
        if(m_sessionInfo.calCoefficients.size() != oldCals.size())
        {
            m_sessionInfo.calCoefficientsUpdated = true;
        }
    }

    void DatalogDownloader::parseDerivedMetaData(uint8 numActiveAlgorithms)
    {
        m_mathMetaDeta.clear();
        
        WirelessTypes::DerivedDataPacketAlgorithmId id;
        uint16 channelMask = 0;
        uint8 algItr = 0;

        //read and store all the math meta data
        for(algItr = 0; algItr < numActiveAlgorithms; ++algItr)
        {
            id = static_cast<WirelessTypes::DerivedDataPacketAlgorithmId>(m_nodeMemory->read_uint8());
            channelMask = m_nodeMemory->read_uint16(Utils::littleEndian);

            m_mathMetaDeta.emplace_back(id, ChannelMask(channelMask));
        }
    }

    bool DatalogDownloader::complete()
    {
        //if the m_outOfMemory flag was set indicating that we are out of memory
        if(m_outOfMemory)
        {
            return true;
        }

        //check if there are no bytes remaining in the Node's datalogging memory
        if(m_nodeMemory->bytesRemaining() == 0)
        {
            m_outOfMemory = true;
            return true;
        }

        //we still have bytes remaining
        return false;
    }

    float DatalogDownloader::percentComplete() const
    {
        return m_nodeMemory->percentComplete();
    }

    LoggedDataSweep DatalogDownloader::parseNextSweep()
    {
        ChannelData chData;

        uint8 lastActiveCh = m_sessionInfo.activeChannels.lastChEnabled();

        Utils::Endianness dataEndian = Utils::bigEndian;
        if(m_datalogDownloadVersion == 2)
        {
            dataEndian = Utils::littleEndian;
        }

        //calibrations are applied if floating point data
        bool calsApplied = WirelessTypes::isCalApplied(m_sessionInfo.dataType);

        //loop through all the channels
        for(uint8 chItr = 1; chItr <= lastActiveCh; ++chItr)
        {
            //if the current channel is enabled
            if(m_sessionInfo.activeChannels.enabled(chItr))
            {
                anyType dataPoint;

                switch(m_sessionInfo.dataType)
                {
                    //4 byte float
                    case WirelessTypes::dataType_float32:
                    case WirelessTypes::dataType_float32_noCals:
                        dataPoint = m_nodeMemory->read_float(dataEndian);
                        break;

                    //uint32
                    case WirelessTypes::dataType_uint32:
                        dataPoint = m_nodeMemory->read_uint32(dataEndian);
                        break;

                    //uint24 (get as a uint32)
                    case WirelessTypes::dataType_uint24:
                        case WirelessTypes::dataType_uint24_18bitRes:
                        dataPoint = m_nodeMemory->read_uint24(dataEndian);
                        break;

                    //uint16 (from a 18-bit device, shift bits)
                    case WirelessTypes::dataType_uint16_18bitTrunc:
                    {
                        uint32 val = m_nodeMemory->read_uint16(dataEndian);
                        dataPoint = (val << 2);
                        break;
                    }

                    //uint16 value (from 24-bit node, shift bits)
                    case WirelessTypes::dataType_uint16_24bitTrunc:
                    {
                        uint32 val = m_nodeMemory->read_uint16(dataEndian);
                        dataPoint = (val << 8);
                        break;
                    }

                    //int16 (from a 20-bit device, shift bits)
                    case WirelessTypes::dataType_int16_20bitTrunc:
                    {
                        int32 val = static_cast<int32>(m_nodeMemory->read_int16(dataEndian));
                        dataPoint = (val << 6);
                        break;
                    }

                    //int16 value (calibrated value multiplied by 10, needs divided by 10)
                    case WirelessTypes::dataType_int16_x10:
                    {
                        dataPoint = static_cast<float>(m_nodeMemory->read_int16(dataEndian)) / 10.0f;
                        break;
                    }

                    //int24 (get as a int32)
                    case WirelessTypes::dataType_int24_20bit:
                        dataPoint = m_nodeMemory->read_int24(dataEndian);
                        break;

                    //uint16
                    case WirelessTypes::dataType_uint16_shifted:
                    case WirelessTypes::dataType_uint16_12bitRes:
                    case WirelessTypes::dataType_uint16:
                    default:
                        dataPoint = m_nodeMemory->read_uint16(dataEndian);
                        break;
                }

                //create a WirelessDataPoint and add it to the ChannelData vector
                chData.push_back(WirelessDataPoint(static_cast<WirelessChannel::ChannelId>(chItr), chItr, m_sessionInfo.valueType, dataPoint));
            }
        }

        //calculate the timestamp and tick for the sweep
        uint64 sweepTime = m_sessionInfo.tsCounter.time();
        m_sessionInfo.tsCounter.advance();
        uint64 sweepTick = m_sweepCount;

        //increment the sweep count
        m_sweepCount++;

        //return the LoggedDataSweep object containing the data that was downloaded
        return LoggedDataSweep(Timestamp(sweepTime), sweepTick, chData, calsApplied);
    }

    LoggedDataSweep DatalogDownloader::parseNextMathSweep()
    {
        ChannelData chData;

        Utils::Endianness dataEndian = Utils::bigEndian;
        if(m_datalogDownloadVersion == 2)
        {
            dataEndian = Utils::littleEndian;
        }

        uint8 lastChEnabled = 0;
        uint8 chNum = 0;
        for(auto& meta : m_mathMetaDeta)
        {
            lastChEnabled = meta.channelMask.lastChEnabled();

            for(chNum = 1; chNum <= lastChEnabled; ++chNum)
            {
                if(meta.channelMask.enabled(chNum))
                {
                    //TODO: once we get math channels that have different data than float, will need to parse different based on the meta id
                    float value = m_nodeMemory->read_float(dataEndian);

                    //create a WirelessDataPoint and add it to the ChannelData vector
                    WirelessChannel::ChannelId channelId = WirelessDataPacket::getMathChannelId(static_cast<WirelessTypes::DerivedDataPacketAlgorithmId>(meta.algorithmId), chNum);

                    //create the ChannelMask property indicating which channel it was derived from
                    ChannelMask propertyChMask;
                    propertyChMask.enable(chNum);
                    WirelessDataPoint::ChannelProperties properties({
                        {std::make_pair(WirelessDataPoint::channelPropertyId_derivedFrom, Value(valueType_ChannelMask, propertyChMask))},
                        {std::make_pair(WirelessDataPoint::channelPropertyId_derivedAlgorithmId, Value(valueType_uint8, static_cast<uint8>(meta.algorithmId)))}
                    });

                    chData.push_back(WirelessDataPoint(channelId, chNum, valueType_float, anyType(value), properties));
                }
            }
        }

        //calculate the timestamp and tick for the sweep
        uint64 sweepTime = m_sessionInfo.tsCounter.time();
        m_sessionInfo.tsCounter.advance();
        uint64 sweepTick = m_sweepCount;

        //increment the sweep count
        m_sweepCount++;

        //return the LoggedDataSweep object containing the data that was downloaded
        //(Note: calibrations are always applied already for Math data)
        return LoggedDataSweep(Timestamp(sweepTime), sweepTick, chData, true);
    }

    LoggedDataSweep DatalogDownloader::getNextData()
    {
        if(complete())
        {
            throw Error_NoData("There is no more data available to download from the Node.");
        }

        const uint32 startReadIndex = m_nodeMemory->readIndex();
        ChannelData chData;

        try
        {
            //check if the next group of bytes look like the start of a trigger
            if(m_nodeMemory->isNextByteNewHeader())
            {
                //Download Version 1
                if(m_datalogDownloadVersion == 1)
                {
                    //parse the trigger header and update all of the trigger session info
                    parseTriggerHeader_v1();

                    m_foundFirstTrigger = true;
                }
                //Download Version 2
                else
                {
                    //parse the trigger header for v2 and update any new trigger session info
                    parseTriggerHeader_v2();

                    m_foundFirstTrigger = true;
                }
            }
            else
            {
                //if the first trigger hasn't been found yet
                if(!m_foundFirstTrigger)
                {
                    //the start of trigger isn't at the first memory location on the Node
                    m_outOfMemory = true;
                    throw Error_NoData("No triggers were found on the Node.");
                }

                //set the startOfTrigger flag to false
                m_sessionInfo.startOfTrigger = false;

                m_sessionInfo.sessionInfoUpdated = false;
            }

            if(m_isMathData)
            {
                return parseNextMathSweep();
            }
            else
            {
                return parseNextSweep();
            }
        }
        catch(Error_Communication&)
        {
            //downloader v1 needs to reset the memory position on comm failure
            if(m_datalogDownloadVersion == 1)
            {
                //set the read address back so that we the user can retry
                m_nodeMemory->setAddress(startReadIndex);
            }

            //then rethrow the exception
            throw;
        }
    }

    bool DatalogDownloader::metaDataUpdated() const
    {
        return m_sessionInfo.sessionInfoUpdated;
    }

    bool DatalogDownloader::calCoefficientsUpdated() const
    {
        return m_sessionInfo.calCoefficientsUpdated;
    }

    bool DatalogDownloader::startOfSession() const
    {
        return m_sessionInfo.startOfTrigger;
    }

    uint16 DatalogDownloader::sessionIndex() const
    {
        return m_sessionInfo.sessionIndex;
    }

    const SampleRate& DatalogDownloader::sampleRate() const
    {
        if(m_isMathData)
        {
            return m_sessionInfo.derivedRate;
        }
        else
        {
            return m_sessionInfo.sampleRate;
        }
    }

    const std::string& DatalogDownloader::userString() const
    {
        return m_sessionInfo.userString;
    }

    const ChannelCalMap& DatalogDownloader::calCoefficients() const
    {
        return m_sessionInfo.calCoefficients;
    }
}