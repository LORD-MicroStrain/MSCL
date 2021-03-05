/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeMemory.h"
#include "mscl/Types.h"
#include "mscl/MicroStrain/ByteStream.h"

namespace mscl
{
    class WirelessNode;

    //Class: NodeMemory_v1
    //    Provides easy access to the datalogging memory on a WirelessNode.
    class NodeMemory_v1 : public NodeMemory
    {
    public:
        //Constructor: NodeMemory_v1
        //    Creates a NodeMemory_v1 object.
        //
        //Parameters:
        //    node - The <WirelessNode> to access the memory of.
        //    logPage - The last log page that contains datalogging data.
        //    pageOffset - The byte offset into the last log page containing datalogging data.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to read info from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        NodeMemory_v1(WirelessNode& node, uint16 logPage, uint16 pageOffset);

        //Destructor: ~NodeMemory_v1
        //  Destroys a NodeMemory_v1 object.
        virtual ~NodeMemory_v1() {};

    private:
        NodeMemory_v1();                                //disabled default constructor
        NodeMemory_v1(const NodeMemory_v1&);                //disabled copy constructor
        NodeMemory_v1& operator=(const NodeMemory_v1&);    //disabled assignment operator

    private:
        //Constants: Node Memory Constants
        //    DPAGE_SIZE    - 264   - The size of a single datalogging page (in bytes).
        //    START_PAGE    - 2     - The first page on the Node that has actual datalogging data.
        static const uint16 DPAGE_SIZE = 264;
        static const uint16 START_PAGE = 2;

        //Variable: m_currentAddress
        //  The current address to read data from.
        uint32 m_currentAddress;

        //Variable: m_logPage
        //    The last log page that contains datalogging data.
        uint16 m_logPage;

        //Variable: m_pageOffset
        //    The byte offset into the last log page containing datalogging data.
        uint16 m_pageOffset;

        //Variable: m_currentPageNumber
        //    Holds the page number of the data that is stored in m_currentData
        uint16 m_currentPageNumber;

        //Variable: m_previousPageNumbers
        //    Holds the page number of the data that is stored in m_previousData
        uint16 m_previousPageNumber;

        //Variable: m_previousData
        //   Holds the previously downloaded page data for easily returning to it
        ByteStream m_previousData;

    private:
        //Function: findPageAndOffset
        //    Gets the page and offset from the memory position.
        //
        //Parameters:
        //    bytePosition - The byte position in the Node's datalogging memory.
        //    page - Holds the page index result.
        //    offset - Holds the offset position result;
        void findPageAndOffset(uint32 bytePosition, uint16& page, uint16& offset) const;

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
        void findData(uint32 bytePosition, ByteStream** data, uint16& offset);

    protected:
        //Function: nextByte
        //    Reads the next byte from the datalogging data.
        //
        //Returns:
        //    The 1-byte uint8 at the next position.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to download data from the Node.
        //    - <Error_NoData>: The requested bytePosition is outside the range of the datalogged data.
        //    - <Error_Connection>: A connection error has occurred.
        virtual uint8 nextByte() override;

    public:
        //Function: calcTotalBytes
        //  Calculates the total number of bytes currently logged to memory.
        //
        //Parameters:
        //  logPage - The log page from the Node.
        //  pageOffset - The log page offset from the Node.
        //
        //Returns:
        //  The total number of bytes currently logged to memory.
        static uint32 calcTotalBytes(uint16 logPage, uint16 pageOffset);

        //Function: isNextByteNewHeader
        //  Checks if the next byte will be the start of a new header.
        //  Note: upon returning from this function, the read position will not have changed.
        //
        //Returns:
        //  true if the next byte starts a new header, false if it does not.
        virtual bool isNextByteNewHeader() override;

        //Function: readIndex
        //  Returns the current read index for the data.
        virtual uint32 readIndex() const override;

        //Function: setAddress
        //  Sets the read address to the specified value.
        //
        //Parameters:
        //  newAddress - The address to set the read address to.
        virtual void setAddress(uint32 newAddress) override;

        //Function: bytesRemaining
        //    Calculates how many bytes are remaining in the Node's datalogging memory, based on the given byte position.
        //
        //Parameters:
        //    address - The byte position to check against the total bytes to calculate the number of bytes remaining.
        //
        //Returns:
        //    The number of bytes remaining before the end of the Node's datalogging memory.
        //virtual uint32 bytesRemaining(uint32 address) const override;
        virtual uint32 bytesRemaining() override;

        //Function: percentComplete
        //    Calculates the percentage complete based on the given byte position.
        //
        //Parameters:
        //    address - The byte position to check against the total bytes to calculate the percent complete.
        //
        //Returns:
        //  The percentage complete (0 - 100).
        //virtual float percentComplete(uint32 address) const override;
        virtual float percentComplete() override;
    };
}