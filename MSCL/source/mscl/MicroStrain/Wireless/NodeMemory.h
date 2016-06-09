/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once
#include "mscl/Types.h"
#include "mscl/MicroStrain/ByteStream.h"

namespace mscl
{
    class WirelessNode;

    //Class: NodeMemory
    //    Provides easy access to the datalogging memory on a WirelessNode.
    class NodeMemory
    {
    public:
        //Constructor: NodeMemory
        //    Creates a NodeMemory object.
        //
        //Parameters:
        //    node - The <WirelessNode> to access the memory of.
        //    logPage - The last log page that contains datalogging data.
        //    pageOffset - The byte offset into the last log page containing datalogging data.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to read info from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        NodeMemory(WirelessNode& node, uint16 logPage, uint16 pageOffset);

    private:
        NodeMemory();                                //disabled default constructor
        NodeMemory(const NodeMemory&);                //disabled copy constructor
        NodeMemory& operator=(const NodeMemory&);    //disabled assignment operator

    private:
        //Constants: Node Memory Constants
        //    PAGE_SIZE    - 264    - The size of a single datalogging page (in bytes).
        //    START_PAGE    - 2        - The first page on the Node that has actual datalogging data.
        static const uint16 PAGE_SIZE = 264;
        static const uint16 START_PAGE = 2;

        //Variable: m_node
        //    The <WirelessNode> to access the memory of.
        WirelessNode& m_node;

        //Variable: m_logPage
        //    The last log page that contains datalogging data.
        uint16 m_logPage;

        //Variable: m_pageOffset
        //    The byte offset into the last log page containing datalogging data.
        uint16 m_pageOffset;

        //Variable: m_totalBytes
        //    The total number of bytes that can be downloaded.
        uint64 m_totalBytes;

        //Variable: m_currentPageNumber
        //    Holds the page number of the data that is stored in m_currentPageData
        uint16 m_currentPageNumber;

        //Variable: m_previousPageNumbers
        //    Holds the page number of the data that is stored in m_previousPageData
        uint16 m_previousPageNumber;

        //Variable: m_currentPageData
        //    Contains data for the current page that has been downloaded.
        ByteStream m_currentPageData;

        //Variable: m_previousPageData
        //    Contains data for the previous page that was downloaded.
        //    This allows us to grab data from a page, and then look back at previous data (to piece a packet together) without redownloading it.
        ByteStream m_previousPageData;

    private:
        //Function: findPageAndOffset
        //    Gets the page and offset from the memory position.
        //
        //Parameters:
        //    bytePosition - The byte position in the Node's datalogging memory.
        //    page - Holds the page index result.
        //    offset - Holds the offset position result;
        void findPageAndOffset(uint64 bytePosition, uint16& page, uint16& offset) const;

        //Function: getByteStream
        //    Gets a pointer to the ByteStream containing the data for the requested page.
        //    If the data does not exist in a current ByteStream, it will be downloaded from the Node.
        //
        //Parameters:
        //    page - The page index to request data for.
        //
        //Returns:
        //    A ByteStream pointer containing the data for the requested page.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to download data from the Node.
        //    - <Error_Connection>: A connection error has occurred.
        ByteStream* getByteStream(uint16 page);

        //Function: findData
        //    Gets the data ByteStream, and offset into the ByteStream to read from, given the byte position.
        //
        //Parameters:
        //    bytePosition - The byte position requested in the Node's datalogging memory.
        //    data - Holds the ByteStream result containing the data to read.
        //    offset - Holds the offset result, which is the offset into the data to read from.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to download data from the Node.
        //    - <Error_NoData>: The requested bytePosition is outside the range of the datalogged data.
        //    - <Error_Connection>: A connection error has occurred.
        void findData(uint64 bytePosition, ByteStream** data, uint16& offset);

    public:
        //Function: at
        //    Reads a 1-byte unsigned integer from the datalogging data.
        //
        //Parameters:
        //    bytePosition - The 0-based position into the Node's memory to read from.
        //
        //Returns:
        //    The 1-byte uint8 at the requested position.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to download data from the Node.
        //    - <Error_NoData>: The requested bytePosition is outside the range of the datalogged data.
        //    - <Error_Connection>: A connection error has occurred.
        uint8 at(uint64 bytePosition);

        //Function: bytesRemaining
        //    Calculates how many bytes are remaining in the Node's datalogging memory, based on the given byte position.
        //
        //Parameters:
        //    currentByte - The byte position to check against the total bytes to calculate the number of bytes remaining.
        //
        //Returns:
        //    The number of bytes remaining before the end of the Node's datalogging memory.
        uint64 bytesRemaining(uint64 currentByte) const;

        //Function: percentComplete
        //    Calculates the percentage complete based on the given byte position.
        //
        //Parameters:
        //    currentByte - The byte position to check against the total bytes to calculate the percent complete.
        //
        //Returns:
        //  The percentage complete (0 - 100).
        float percentComplete(uint64 currentByte) const;
    };
}