/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "NodeMemory_v1.h"
#include "WirelessNode.h"
#include "mscl/ScopeHelper.h"

namespace mscl
{
    NodeMemory_v1::NodeMemory_v1(WirelessNode& node, uint16 logPage, uint16 pageOffset) :
        NodeMemory(node),
        m_currentAddress(0),
        m_logPage(logPage),
        m_pageOffset(pageOffset),
        m_currentPageNumber(0),
        m_previousPageNumber(0)
    {
        m_totalBytes = calcTotalBytes(m_logPage, m_pageOffset);
    }

    uint32 NodeMemory_v1::calcTotalBytes(uint16 logPage, uint16 pageOffset)
    {
        //if page offset >= DPAGE_SIZE
        if(pageOffset >= DPAGE_SIZE)
        {
            //need to increment the log page by 1
            logPage += 1;

            //need to reduce the page offset by the DPAGE_SIZE
            pageOffset -= DPAGE_SIZE;
        }

        //eeproms take up the first 2 pages
        uint16 lastPage = 0;
        if(logPage >= START_PAGE)
        {
            lastPage = logPage - START_PAGE;
        }

        //each physical page is equal to 1 virtual page.
        return (lastPage * DPAGE_SIZE) + (pageOffset);
    }

    void NodeMemory_v1::findPageAndOffset(uint32 bytePosition, uint16& page, uint16& offset) const
    {
        //calculate the page and offset
        page = static_cast<uint16>((bytePosition / DPAGE_SIZE) + START_PAGE);
        offset = bytePosition % DPAGE_SIZE;
    }

    ByteStream* NodeMemory_v1::getByteStream(uint16 page)
    {
        //if the requested data is in the currently downloaded data buffer
        if(page == m_currentPageNumber && !m_currentData.empty())
        {
            //just return the address of m_currentPageData
            return &m_currentData;
        }

        //if the requested data is in the previously downloaded data buffer
        if(page == m_previousPageNumber && !m_previousData.empty())
        {
            //just return the address of m_previousPageData
            return &m_previousData;
        }

        //if we made it here, the page requested is data we don't already have

        BaseStation& base = m_node.getBaseStation();

        //request the current page data
        ByteStream tempData;
        if(!base.node_pageDownload(m_node.protocol(base.communicationProtocol()), m_node.nodeAddress(), page, tempData))
        {
            //the page download failed, throw an exception
            throw Error_NodeCommunication(m_node.nodeAddress(), "Failed to download data from the Node.");
        }

        //if there is current data that needs move to previous data
        if(!m_currentData.empty())
        {
            //copy the current data into the previous data buffer
            m_previousData.clear();
            m_previousData = m_currentData;
            m_previousPageNumber = m_currentPageNumber;
        }

        //copy the data that was just read into m_currentData
        m_currentData = tempData;
        m_currentPageNumber = page;

        //we successfully downloaded data that is in m_currentData
        return &m_currentData;
    }

    void NodeMemory_v1::findData(uint32 bytePosition, ByteStream** data, uint16& offset)
    {
        //check if we are trying to read outside the bounds of logged data
        if(bytePosition > m_totalBytes)
        {
            throw Error_NoData("There is no more data available to download from the Node.");
        }

        //find the page and offset from the byte position
        uint16 page = 0;
        findPageAndOffset(bytePosition, page, offset);

        //get the ByteStream data to read
        *data = getByteStream(page);
    }

    void NodeMemory_v1::setAddress(uint32 newAddress)
    {
        m_currentAddress = newAddress;
    }

    uint8 NodeMemory_v1::nextByte()
    {
        ByteStream* data = nullptr;
        uint16 offset = 0;

        //find the data to read from
        findData(m_currentAddress, &data, offset);

        m_currentAddress++;

        //read the data starting at the offset
        return data->read_uint8(offset);
    }

    bool NodeMemory_v1::isNextByteNewHeader()
    {
        //store the current address so we can revert back to it
        uint32 startAddress = m_currentAddress;

        //set m_currentAddress back to the start address when we are done in this function
        ScopeHelper writeBackAddress(std::bind(&NodeMemory_v1::setAddress, this, startAddress));

        static const uint16 START_OF_TRIGGER = 0xFFFF;            //the start of trigger
        static const uint8 TRIGGER_HEADER_ID = 0xFD;            //the trigger header id
        static const uint8 MAX_TRIGGER_TYPE = 0x04;                //the max trigger type supported
        static const uint16 MIN_BYTES_B4_DATA = 0x0A;            //the minimum value ever supported for '# bytes before data'
        static const uint16 MAX_BYTES_B4_DATA = 0x3E;            //the maximum value ever supported for '# bytes before data'

        static const Version HEADER_VERSION_1_0(1, 0);
        static const Version HEADER_VERSION_2_0(2, 0);
        static const Version HEADER_VERSION_2_1(2, 1);

        try
        {
            //verify the start of trigger
            if(read_uint16() != START_OF_TRIGGER)
            {
                return false;
            }

            //verify the trigger header id
            if(read_uint8() != TRIGGER_HEADER_ID)
            {
                return false;
            }

            //verify the trigger type is within range
            if(read_uint8() > MAX_TRIGGER_TYPE)
            {
                return false;
            }

            uint8 versionMajor = read_uint8();
            uint8 versionMinor = read_uint8();

            //verify the header version is one that we support
            Version headerVersion(versionMajor, versionMinor);
            if(headerVersion != HEADER_VERSION_2_1 &&
               headerVersion != HEADER_VERSION_2_0 &&
               headerVersion != HEADER_VERSION_1_0)
            {
                return false;
            }

            //verify the # of bytes before channel data value
            uint16 bytesBeforeData = read_uint16();
            if(bytesBeforeData < MIN_BYTES_B4_DATA ||
               bytesBeforeData > MAX_BYTES_B4_DATA)
            {
                return false;
            }

            m_currentAddress += 6;    //move to the sample rate bytes

            //verify the sample rate is a valid rate
            uint16 sampleRateVal = read_uint16();
            try
            {
                //if it is an armed datalogging rate, we need to convert it to a WirelessSampleRate
                //Note: if not a datalogging rate, this will just cast it to a WirelessSampleRate without conversion.
                WirelessTypes::WirelessSampleRate rate = WirelessTypes::dataloggingRateToSampleRate(sampleRateVal);

                //check that we can convert it to a SampleRate object
                SampleRate::FromWirelessEepromValue(rate);
            }
            catch(Error_UnknownSampleRate&)
            {
                return false;
            }

            //everthing looks like it is the start of a trigger
            return true;
        }
        catch(Error_NoData&)
        {
            //don't throw the exception, just return false as this isn't the start of a trigger
            return false;
        }
    }

    uint32 NodeMemory_v1::readIndex() const
    {
        return m_currentAddress;
    }

    uint32 NodeMemory_v1::bytesRemaining()
    {
        //if the current byte is past the end of the total bytes
        if(m_currentAddress > m_totalBytes)
        {
            //no bytes remaining
            return 0;
        }

        //return the difference between the total bytes and the current byte
        return m_totalBytes - m_currentAddress;
    }

    float NodeMemory_v1::percentComplete()
    {
        //if we have completed
        if(m_currentAddress > m_totalBytes)
        {
            return 100.0;
        }

        return (static_cast<float>(m_currentAddress) / static_cast<float>(m_totalBytes)) * 100.0f;
    }
}