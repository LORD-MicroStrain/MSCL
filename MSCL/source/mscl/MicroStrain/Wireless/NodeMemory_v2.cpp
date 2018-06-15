/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "NodeMemory_v2.h"
#include "WirelessNode.h"

namespace mscl
{
    NodeMemory_v2::NodeMemory_v2(WirelessNode& node, const FlashInfo& flashInfo, uint32 startAddress, uint32 size):
        NodeMemory(node),
        m_flashInfo(flashInfo),
        m_startAddress(startAddress),
        m_downloadAddress(startAddress),
        m_previousDownloadAddress(startAddress),
        m_readIndex(0),
        m_checksumIndex(0),
        m_sweepSize(0),
        m_derivedSweepSize(0),
        m_isMathData(false),
        m_partialDownload(false),
        m_doneDownloading(false),
        m_startedDownloading(false)
    {
        m_totalBytes = size;

        //calculate the last flash address
        uint64 lastFlashLocation = m_startAddress + m_totalBytes;
        if(lastFlashLocation > m_flashInfo.storageSize)
        {
            lastFlashLocation -= m_flashInfo.storageSize;
        }
        m_lastAddress = static_cast<uint32>(lastFlashLocation);
    }

    uint32 NodeMemory_v2::nextBlockAddress(uint32 currentAddress) const
    {
        return currentAddress + (m_flashInfo.blockSize - currentAddress % m_flashInfo.blockSize);
    }

    uint32 NodeMemory_v2::bytesLeftToDownload() const
    {
        //if we haven't rolled over
        if(m_downloadAddress >= m_startAddress)
        {
            //we've come back around to the start address, should be done downloading
            if((m_downloadAddress == m_startAddress) && m_startedDownloading)
            {
                return 0;
            }

            uint32 bytesRead = m_downloadAddress - m_startAddress;
            if(m_totalBytes > bytesRead)
            {
                return m_totalBytes - bytesRead;
            }
            else
            {
                return 0;
            }
        }
        //a rollover has occurred
        else
        {
            uint32 totalReadBytes = m_flashInfo.storageSize - m_startAddress + m_downloadAddress;

            if(totalReadBytes >= m_totalBytes)
            {
                return 0;
            }
            else
            {
                return m_totalBytes - totalReadBytes;
            }
        }
    }

    void NodeMemory_v2::normalizeAddress()
    {
        if(m_downloadAddress > m_flashInfo.storageSize)
        {
            m_downloadAddress %= m_flashInfo.storageSize;
        }
    }

    bool NodeMemory_v2::verifyBlock(const ByteStream& buffer, uint32& checksumPos, bool& needMoreData)
    {
        needMoreData = false;

        //assumes that the header starts at position 0 in buffer

        if(buffer.empty())
        {
            needMoreData = true;
            return false;
        }

        uint8 headerId = buffer.read_uint8(0);

        //TODO: if this is the first block being requested, must be a BLOCK_HEADER_ID ?

        //check the header id is ok
        if(headerId != BLOCK_HEADER_ID &&
           headerId != REFRESH_HEADER_ID &&
           headerId != SESSION_CHANGE_HEADER_ID &&
           headerId != SESSION_CHANGE_HEADER_ID_V2)
        {
            return false;
        }

        //verify more Block Header bytes
        if(headerId == BLOCK_HEADER_ID)
        {
            //make sure we can at least read the version number
            if(buffer.size() < 2)
            {
                return false;
            }

            uint8 version = buffer.read_uint8(1);

            //verify the header version is one we support
            if(version > 1)
            {
                return false;
            }

            if(version == 0)
            {
                m_isMathData = false;

                //Verify Block Header version 0

                static const uint8 HEADER_CHECK_SIZE = 20;
                if(buffer.size() < HEADER_CHECK_SIZE)
                {
                    //not enough bytes in the buffer to verify a block header
                    needMoreData = true;
                    return false;
                }

                static const uint8 MIN_BYTES_B4_DATA = 27;      //the minimum value ever supported for '# bytes before data' (if 1 channel active)
                static const uint8 MAX_BYTES_B4_DATA = 177;     //the maximum value ever supported for '# bytes before data' (if 16 channels active)

                //verify the # of bytes before channel data value
                uint8 bytesBeforeData = buffer.read_uint8(2);
                if(bytesBeforeData < MIN_BYTES_B4_DATA ||
                   bytesBeforeData > MAX_BYTES_B4_DATA)
                {
                    return false;
                }

                //verify the sample rate is a valid rate
                WirelessTypes::WirelessSampleRate sampleRateVal = static_cast<WirelessTypes::WirelessSampleRate>(buffer.read_uint8(16));
                try
                {
                    //check that we can convert it to a SampleRate object
                    SampleRate::FromWirelessEepromValue(sampleRateVal);
                }
                catch(Error_UnknownSampleRate&)
                {
                    return false;
                }

                uint8 numSweeps = buffer.read_uint8(3);
                uint8 numActiveChs = ChannelMask(buffer.read_uint16(17, Utils::littleEndian)).count();
                uint16 dataTypeSize = WirelessTypes::dataTypeSize(static_cast<WirelessTypes::DataType>(buffer.read_uint8(19)));

                m_sweepSize = numActiveChs * dataTypeSize;

                //calculate the index into buffer where the checksum should be located
                //  3 bytes + bytesBeforeData in header + data
                checksumPos = 3 + bytesBeforeData + (m_sweepSize * numSweeps);
            }
            else if(version == 1)
            {
                //Verify Block Header version 1

                static const uint8 HEADER_CHECK_SIZE = 26;
                if(buffer.size() < HEADER_CHECK_SIZE)
                {
                    //not enough bytes in the buffer to verify a block header
                    needMoreData = true;
                    return false;
                }

                static const uint8 MIN_BYTES_B4_DATA = 26;      //the minimum value ever supported for '# bytes before data' (if 1 math channel active)

                //verify the # of bytes before channel data value
                uint8 bytesBeforeData = buffer.read_uint8(2);
                if(bytesBeforeData < MIN_BYTES_B4_DATA)
                {
                    return false;
                }

                //verify the sample rate is a valid rate
                WirelessTypes::WirelessSampleRate sampleRateVal = static_cast<WirelessTypes::WirelessSampleRate>(buffer.read_uint8(17));
                try
                {
                    //check that we can convert it to a SampleRate object
                    SampleRate::FromWirelessEepromValue(sampleRateVal);
                }
                catch(Error_UnknownSampleRate&)
                {
                    return false;
                }

                //verify the sweep type is one we know how to parse
                SweepType sweepType = static_cast<SweepType>(buffer.read_uint8(4));
                if(sweepType != sweepType_raw &&
                   sweepType != sweepType_derived)
                {
                    return false;
                }

                uint8 numSweeps = buffer.read_uint8(3);
                uint8 numRawChs = ChannelMask(buffer.read_uint16(18, Utils::littleEndian)).count();

                uint16 dataTypeSize = WirelessTypes::dataTypeSize(static_cast<WirelessTypes::DataType>(buffer.read_uint8(20)));
                m_sweepSize = numRawChs * dataTypeSize;

                uint8 numActiveAlgorithms = buffer.read_uint8(21);
                const uint16 NUM_RAW_CAL_INFO_BYTES = numRawChs * 10;    //10 bytes per raw active channel
                const size_t ALG_META_OFFSET = 26 + NUM_RAW_CAL_INFO_BYTES;
                uint16 numAlgChannelBytes = 0;

                if(numActiveAlgorithms > 0)
                {
                    if(static_cast<uint64>(buffer.size()) < (ALG_META_OFFSET + (static_cast<uint64>(numActiveAlgorithms) * 3)))
                    {
                        //not enough bytes in the buffer to verify a block header
                        needMoreData = true;
                        return false;
                    }
                }

                uint8 i = 0;
                uint8 algorithmId;
                ChannelMask chMask;
                for(i = 0; i < numActiveAlgorithms; ++i)
                {
                    algorithmId = buffer.read_uint8(ALG_META_OFFSET + (i * 3));       //3 bytes per derived active channel
                    chMask.fromMask(buffer.read_uint16(ALG_META_OFFSET + (i * 3) + 1, Utils::littleEndian));

                    try
                    {
                        //add up the number of bytes for all the active algorithms
                        //  (# of bytes for the algorithm type) * (# of channels that are active)
                        numAlgChannelBytes += WirelessTypes::bytesPerDerivedChannel(static_cast<WirelessTypes::DerivedChannelType>(algorithmId)) * chMask.count();
                    }
                    catch(Error_NotSupported&)
                    {
                        //invalid algorithm ID
                        return false;
                    }
                }
                m_derivedSweepSize = numAlgChannelBytes;

                //calculate the index into buffer where the checksum should be located
                //  3 bytes + bytesBeforeData in header + data
                if(sweepType == sweepType_raw)
                {
                    m_isMathData = false;
                    checksumPos = 3 + bytesBeforeData + (m_sweepSize * numSweeps);
                }
                else if(sweepType == sweepType_derived)
                {
                    m_isMathData = true;
                    checksumPos = 3 + bytesBeforeData + (m_derivedSweepSize * numSweeps);
                }
            }
        }
        else if(headerId == REFRESH_HEADER_ID)
        {
            static const uint8 HEADER_CHECK_SIZE = 2;
            if(buffer.size() < HEADER_CHECK_SIZE)
            {
                //not enough bytes in the buffer to verify a refresh header
                needMoreData = true;
                return false;
            }

            uint8 numSweeps = buffer.read_uint8(1);

            //calculate the index into buffer where the checksum should be located
            //  2 bytes in header + data
            if(m_isMathData)
            {
                checksumPos = 2 + (m_derivedSweepSize * numSweeps);
            }
            else
            {
                checksumPos = 2 + (m_sweepSize * numSweeps);
            }
        }
        else if(headerId == SESSION_CHANGE_HEADER_ID)
        {
            static const uint8 HEADER_CHECK_SIZE = 12;
            if(buffer.size() < HEADER_CHECK_SIZE)
            {
                //not enough bytes in the buffer to verify a session header
                needMoreData = true;
                return false;
            }

            uint8 numSweeps = buffer.read_uint8(1);

            //calculate the index into buffer where the checksum should be located
            //  12 bytes in header + data
            checksumPos = 12 + (m_sweepSize * numSweeps);
        }
        else if(headerId == SESSION_CHANGE_HEADER_ID_V2)
        {
            static const uint8 HEADER_CHECK_SIZE = 13;
            if(buffer.size() < HEADER_CHECK_SIZE)
            {
                //not enough bytes in the buffer to verify a session header
                needMoreData = true;
                return false;
            }

            //verify the sweep type is one we know how to parse
            SweepType sweepType = static_cast<SweepType>(buffer.read_uint8(2));
            if(sweepType == sweepType_raw)
            {
                m_isMathData = false;
            }
            else if(sweepType == sweepType_derived)
            {
                m_isMathData = true;
            }
            else
            {
                //unsupported sweep type
                return false;
            }

            uint8 numSweeps = buffer.read_uint8(1);

            if(m_isMathData)
            {
                //calculate the index into buffer where the checksum should be located
                //  13 bytes in header + data
                checksumPos = 13 + (m_derivedSweepSize * numSweeps);
            }
            else
            {
                //calculate the index into buffer where the checksum should be located
                //  13 bytes in header + data
                checksumPos = 13 + (m_sweepSize * numSweeps);
            }
        }

        //verify we have all the data we need, including the checksum
        if(checksumPos + 1 >= buffer.size())
        {
            needMoreData = true;
            return false;
        }

        //verify the checksum of all the bytes is correct
        if(buffer.calculateFletcherChecksum(0, checksumPos - 1) != buffer.read_uint16(checksumPos, Utils::littleEndian))
        {
            //failed the checksum
            return false;
        }

        return true;
    }

    void NodeMemory_v2::fillBuffer(ByteStream& buffer)
    {
        uint32 checksumPos = 0;
        uint32 prevAddress = m_previousDownloadAddress;
        bool downloadedData = false;
        bool needMoreData = true;

        m_partialDownload = true;

        BaseStation& base = m_node.getBaseStation();

        uint16 numBytesRead = 0;

        //while we haven't found a full block of data in m_extraData
        while(!verifyBlock(m_extraData, checksumPos, needMoreData))
        {
            //check for address passed the end of the data
            if(bytesLeftToDownload() == 0)
            {
                m_partialDownload = false;
                m_doneDownloading = true;
                m_extraData.clear();
                return;
            }

            numBytesRead = 0;

            //get the datalog data from the current memory address, appending it to m_extraData
            if(!base.node_getDatalogData(m_node.protocol(base.communicationProtocol()), m_node.nodeAddress(), m_downloadAddress, m_extraData, numBytesRead))
            {
                //the download failed, throw an exception
                throw Error_NodeCommunication(m_node.nodeAddress(), "Failed to download data from the Node.");
            }

            prevAddress = m_previousDownloadAddress;
            m_previousDownloadAddress = m_downloadAddress;
            downloadedData = true;

            //if we need more data to tell if its a valid block
            if(needMoreData)
            {
                //if the checksum position changed, we parsed a valid header
                if(checksumPos != 0)
                {
                    //need to download more bytes after the header

                    //TODO: can make this more efficient by downloading data in a loop here until (m_extraData.size() > checksumPos + 1)
                    //      which would prevent verifyBlock from being called repeatedly when not needed
                }

                //move the address to the next point we need to download from
                m_downloadAddress += numBytesRead;
                normalizeAddress();
            }
            else
            {
                //determined the data in m_extraData is junk, clear it out
                m_extraData.clear();

                //move the address pointer to the next block address from before this download
                m_downloadAddress = nextBlockAddress(prevAddress);
                normalizeAddress();
            }
        }

        m_partialDownload = false;

        //now that we moved the download address, if we are done downloading
        if(downloadedData && bytesLeftToDownload() == 0)
        {
            //throw away any extra bytes we downloaded passed the last address
            m_extraData.resize(m_extraData.size() - (m_downloadAddress - m_lastAddress));
        }

        //copy the bytes from m_extraData into the provided buffer (throw away the checksum)
        buffer = m_extraData;
        buffer.resize(checksumPos);

        //push the data we just copied off and resize m_extraData
        std::copy(m_extraData.begin() + checksumPos + 2,
                  m_extraData.end(),
                  m_extraData.begin());

        m_extraData.resize(m_extraData.size() - checksumPos - 2);
    }

    uint8 NodeMemory_v2::nextByte()
    {
        if(bytesRemaining() == 0)
        {
            throw Error_NoData("There is no more data available to download from the Node.");
        }

        if(m_currentData.empty())
        {
            //fill m_currentData if its empty
            fillBuffer(m_currentData);

            //fill m_nextData if its empty
            //  (this should only ever be empty if m_currentData is also empty)
            if(m_nextData.empty())
            {
                fillBuffer(m_nextData);
            }

            m_readIndex = 0;
        }

        //if we didn't finish filling the buffer
        //  (this should only ever happen with m_nextData, not m_currentData)
        if(m_partialDownload)
        {
            fillBuffer(m_nextData);
        }

        //if we read all of the data in m_currentData
        if(m_readIndex >= m_currentData.size())
        {
            //copy the data in m_nextData to m_currentData
            m_currentData = m_nextData;

            m_readIndex = 0;

            m_nextData.clear();

            if(!m_doneDownloading)
            {
                //fill up m_nextData now that it's empty
                fillBuffer(m_nextData);
            }
        }

        m_startedDownloading = true;

        return m_currentData.read_uint8(m_readIndex++);
    }

    bool NodeMemory_v2::isNextByteNewHeader()
    {
        if(bytesRemaining() == 0)
        {
            return false;
        }

        if(m_partialDownload)
        {
            return true;
        }

        return (m_readIndex >= m_currentData.size());
    }

    uint32 NodeMemory_v2::readIndex() const
    {
        return m_readIndex;
    }

    void NodeMemory_v2::setAddress(uint32 newAddress)
    {
        //setAddress is not supported by NodeMemory_v2! (TODO?)
        assert(false);
        return;
    }

    uint32 NodeMemory_v2::bytesRemaining()
    {
        size_t bytesLeftToRead = m_nextData.size() + 
                                 m_extraData.size() +
                                 (m_currentData.size() - m_readIndex);

        //total bytes remaining = bytesLeftToDownload + bytes left to read in the buffers
        return bytesLeftToDownload() + static_cast<uint32>(bytesLeftToRead);
    }

    float NodeMemory_v2::percentComplete()
    {
        if(m_totalBytes == 0)
        {
            return 100.0f;
        }

        return (static_cast<float>(m_totalBytes - bytesRemaining()) / static_cast<float>(m_totalBytes)) * 100.0f;
    }
}