/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeMemory.h"
#include "Features/FlashInfo.h"
#include "mscl/Types.h"
#include "mscl/MicroStrain/ByteStream.h"

namespace mscl
{
    class WirelessNode;

    //Class: NodeMemory_v2
    //  Provides easy access to the datalogging memory (v2) on a WirelessNode.
    class NodeMemory_v2 : public NodeMemory
    {
    public:
        //Constructor: NodeMemory_v2
        //  Creates a NodeMemory_v2 object.
        //
        //Parameters:
        //  node - The <WirelessNode> to access the memory of.
        //  flashInfo - The <FlashInfo> of the Node.
        //  startAddress - The flash address of the first log header.
        //  size - The number of logged bytes to read.
        //
        //Exceptions:
        //  - <Error_NodeCommunication>: Failed to read info from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        NodeMemory_v2(WirelessNode& node, const FlashInfo& flashInfo, uint32 startAddress, uint32 size);

        //Constants: Node Memory Constants
        //  BLOCK_HEADER_ID             - 0xBB  - Block Header ID
        //  REFRESH_HEADER_ID           - 0xBA  - Refresh Header ID
        //  SESSION_CHANGE_HEADER_ID    - 0xBC  - Session Change Header ID (Version 1)
        //  SESSION_CHANGE_HEADER_ID_V2 - 0xBD  - Session Change Header ID (Version 2)
        static const uint8 BLOCK_HEADER_ID              = 0xBB;
        static const uint8 REFRESH_HEADER_ID            = 0xBA;
        static const uint8 SESSION_CHANGE_HEADER_ID     = 0xBC;
        static const uint8 SESSION_CHANGE_HEADER_ID_V2  = 0xBD;

        enum SweepType
        {
            sweepType_raw,
            sweepType_derived
        };

    private:
        NodeMemory_v2() = delete;                                   //disabled default constructor
        NodeMemory_v2(const NodeMemory_v2&) = delete;               //disabled copy constructor
        NodeMemory_v2& operator=(const NodeMemory_v2&) = delete;    //disabled assignment operator

        //Destructor: ~NodeMemory_v2
        //  Destroys a NodeMemory_v2 object.
        virtual ~NodeMemory_v2() {};
        
    private:
        //Variable: m_flashInfo
        //  The <FlashInfo> of the Node.
        FlashInfo m_flashInfo;

        //Variable: m_startAddress
        //  The flash address of the first log header.
        const uint32 m_startAddress;

        //Variable: m_lastAddress
        //  The address of the last flash memory location.
        uint32 m_lastAddress;

        //Variable: m_downloadAddress
        //  The flash address to use for the next download command.
        uint32 m_downloadAddress;

        //Variable: m_previousDownloadAddress
        //  The flash address of the previous download command.
        uint32 m_previousDownloadAddress;

        //Variable: m_readIndex
        //  The index into the current data buffer to read from.
        uint32 m_readIndex;

        //Variable: m_checksumIndex
        //  The index of the first checksum byte in the current data buffer.
        uint32 m_checksumIndex;

        //Variable: m_sweepSize
        //  The size of a single sweep of data (used for smaller header parsing).
        uint16 m_sweepSize;

        //Variable: m_derivedSweepSize
        //  The size of a single sweep of derived data (used for smaller header parsing).
        uint16 m_derivedSweepSize;

        //Variable: m_isMathData
        //  True if the current data being parsed is math data, false if it is raw data.
        bool m_isMathData;

        //Variable: m_partialDownload
        //  Flag used to know if a download of data has been started, but not fully completed.
        bool m_partialDownload;

        //Variable: m_doneDownloading
        //  Flag to store whether we have downloaded all the data or not.
        bool m_doneDownloading;

        //Variable: m_startedDownloading
        //  true if we've downloaded at least some data.
        bool m_startedDownloading;

        //Variable: m_nextData
        //  <ByteStream> to hold the next valid block.
        ByteStream m_nextData;

        //Variable: m_extraData
        //  <ByteStream> to hold extra bytes before being pushed into m_nextData.
        ByteStream m_extraData;

    private:
        //Function: nextBlockAddress
        //  Gets the address of the next block from the given address.
        //
        //Parameters:
        //  currentAddress - The current address to look for the next block from.
        uint32 nextBlockAddress(uint32 currentAddress) const;

        //Function: bytesLeftToDownload
        //  Gets the number of bytes left to download based on the current download address.
        //  Note: this does not include bytes left to read in the current data buffer, just to download.
        uint32 bytesLeftToDownload() const;

        //Function: normalizeAddress
        //  Normalizes the download address so that it wraps around (circular buffer) in the case of overflowing the max memory.
        void normalizeAddress();

        //Function: verifyBlock
        //  Verifies that the buffer passed in contains a full, valid block.
        //
        //Parameters:
        //  buffer - The <ByteStream> buffer to check for a full block.
        //  checksumPos - Will be set to the read index of the checksum when it is known where the checksum will be located.
        //                Note: this may be set even if all the data hasn't been found in the buffer, indicating we need to read more data.
        //  needMoreData - Whether or not more data is needed to verify the block.
        //
        //Returns:
        //  true if the buffer contains a full, valid block from its start position. False if it hasn't been verified.
        bool verifyBlock(const ByteStream& buffer, uint32& checksumPos, bool& needMoreData );

        //Function: fillBuffer
        //  Fills the given buffer with the next valid block, if found.
        //
        //Parameters:
        //  buffer - The <ByteStream> buffer to hold the data, if any is found.
        void fillBuffer(ByteStream& buffer);

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
        //    Calculates how many bytes are remaining in the Node's datalogging memory, based on the current byte position.
        //
        //Returns:
        //    The number of bytes remaining before the end of the Node's datalogging memory.
        virtual uint32 bytesRemaining() override;

        //Function: percentComplete
        //    Calculates the percentage complete based on the current byte position.
        //
        //Returns:
        //  The percentage complete (0 - 100).
        virtual float percentComplete() override;
    };
}