/*****************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the included
LICENSE.txt file for a copy of the full GNU General Public License.
*****************************************************************************/
#include "stdafx.h"
#include "NodeMemory.h"
#include "WirelessNode.h"

namespace mscl
{
	NodeMemory::NodeMemory(WirelessNode& node, uint16 logPage, uint16 pageOffset) :
		m_node(node),
		m_logPage(logPage),
		m_pageOffset(pageOffset),
		m_totalBytes(0),
		m_currentPageNumber(0)
	{
		//if page offset >= PAGE_SIZE
		if(m_pageOffset >= PAGE_SIZE)
		{
			//need to increment the log page by 1
			m_logPage += 1;

			//need to reduce the page offset by the PAGE_SIZE
			m_pageOffset -= PAGE_SIZE;
		}

		//eeproms take up the first 2 pages
		uint16 lastPage = 0;
		if(m_logPage >= START_PAGE)
		{
			lastPage = m_logPage - START_PAGE;
		}

		//each physical page is equal to 1 virtual page. This has no bearing on how we access memory we just need to know this when calculating the size.
		m_totalBytes = (lastPage * PAGE_SIZE) + (m_pageOffset);
	}

	void NodeMemory::findPageAndOffset(uint64 bytePosition, uint16& page, uint16& offset) const
	{
		//calculate the page and offset
		page = static_cast<uint16>((bytePosition / PAGE_SIZE) + START_PAGE);
		offset = bytePosition % PAGE_SIZE;
	}

	ByteStream* NodeMemory::getByteStream(uint16 page)
	{
		//if the requested data is in the currently downloaded data buffer
		if(page == m_currentPageNumber && !m_currentPageData.empty())
		{
			//just return the address of m_currentPageData
			return &m_currentPageData;
		}

		//if the requested data is in the previously downloaded data buffer
		if(page == m_previousPageNumber && !m_previousPageData.empty())
		{
			//just return the address of m_previousPageData
			return &m_previousPageData;
		}

		//if we made it here, the page requested is data we don't already have

		//request the current page data
		ByteStream tempData;
		if(!m_node.getBaseStation().node_pageDownload(m_node.protocol(), m_node.nodeAddress(), page, tempData))
		{
			//the page download failed, throw an exception
			throw Error_NodeCommunication(m_node.nodeAddress(), "Failed to download data from the Node.");
		}

		//if there is current data that needs move to previous data
		if(!m_currentPageData.empty())
		{
			//copy the current data into the previous data buffer
			m_previousPageData.clear();
			m_previousPageData = m_currentPageData;
			m_previousPageNumber = m_currentPageNumber;
		}

		//copy the data that was just read into m_currentPageData
		m_currentPageData = tempData;
		m_currentPageNumber = page;

		//we successfully downloaded data that is in m_currentPageData
		return &m_currentPageData;
	}

	void NodeMemory::findData(uint64 bytePosition, ByteStream** data, uint16& offset)
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

	uint8 NodeMemory::at(uint64 bytePosition)
	{
		ByteStream* data = nullptr;
		uint16 offset = 0;

		//find the data to read from
		findData(bytePosition, &data, offset);

		//read the data starting at the offset
		return data->read_uint8(offset);
	}

	uint64 NodeMemory::bytesRemaining(uint64 currentByte)
	{
		//if the current byte is past the end of the total bytes
		if(currentByte > m_totalBytes)
		{
			//no bytes remaining
			return 0;
		}

		//return the difference between the total bytes and the current byte
		return m_totalBytes - currentByte;
	}
}