/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

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
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to read info from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        NodeMemory(WirelessNode& node);

        //Destructor: ~NodeMemory
        //  Destroys a NodeMemory object.
        virtual ~NodeMemory() {};

    private:
        NodeMemory();                               //disabled default constructor
        NodeMemory(const NodeMemory&);              //disabled copy constructor
        NodeMemory& operator=(const NodeMemory&);   //disabled assignment operator

    protected:
        //Variable: m_node
        //    The <WirelessNode> to access the memory of.
        WirelessNode& m_node;

        //Variable: m_totalBytes
        //    The total number of bytes that can be downloaded.
        uint32 m_totalBytes;

        //Variable: m_currentData
        //    Contains data for the current page that has been downloaded.
        ByteStream m_currentData;

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
        virtual uint8 nextByte() = 0;

    public:
        //Function: isNextByteNewHeader
        //  Checks if the next byte will be the start of a new header.
        //  Note: upon returning from this function, the read position will not have changed.
        //
        //Returns:
        //  true if the next byte starts a new header, false if it does not.
        virtual bool isNextByteNewHeader() = 0;

        //Function: readIndex
        //  Returns the current read index for the data.
        virtual uint32 readIndex() const = 0;

        //Function: setAddress
        //  Sets the read address to the specified value.
        //
        //Parameters:
        //  newAddress - The address to set the read address to.
        virtual void setAddress(uint32 newAddress) = 0;

        //Function: bytesRemaining
        //    Calculates how many bytes are remaining in the Node's datalogging memory, based on the current byte position.
        //
        //Returns:
        //    The number of bytes remaining before the end of the Node's datalogging memory.
        virtual uint32 bytesRemaining() = 0;

        //Function: percentComplete
        //    Calculates the percentage complete based on the current byte position.
        //
        //Returns:
        //  The percentage complete (0 - 100).
        virtual float percentComplete() = 0;

        //Function: skipBytes
        //    Moves the read pointer ahead by the number of bytes specified (calls read_uint8).
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to download data from the Node.
        //    - <Error_NoData>: The requested bytePosition is outside the range of the datalogged data.
        //    - <Error_Connection>: A connection error has occurred.
        void skipBytes(uint32 numBytesToSkip);

        //Function: read_uint8
        //    Reads a 1-byte unsigned integer from the Node's memory.
        //
        //Returns:
        //    The 1-byte uint8 at the next position in the Node's memory.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to download data from the Node.
        //    - <Error_NoData>: The requested bytePosition is outside the range of the datalogged data.
        //    - <Error_Connection>: A connection error has occurred.
        uint8 read_uint8();

        //Function: read_int16
        //    Reads a 2-byte signed integer from the Node's memory.
        //
        //Parameters:
        //    endian - The <Utils::Endianness> to read the bytes in.
        //
        //Returns:
        //    The int16 at the next position in the Node's memory.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to download data from the Node.
        //    - <Error_NoData>: The requested bytePosition is outside the range of the datalogged data.
        //    - <Error_Connection>: A connection error has occurred.
        int16 read_int16(Utils::Endianness endian = Utils::bigEndian);

        //Function: read_uint16
        //    Reads a 2-byte unsigned integer from the Node's memory.
        //
        //Parameters:
        //    endian - The <Utils::Endianness> to read the bytes in.
        //
        //Returns:
        //    The uint16 at the next position in the Node's memory.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to download data from the Node.
        //    - <Error_NoData>: The requested bytePosition is outside the range of the datalogged data.
        //    - <Error_Connection>: A connection error has occurred.
        uint16 read_uint16(Utils::Endianness endian = Utils::bigEndian);

        //Function: read_uint24
        //    Reads a 3-byte unsigned integer from the Node's memory.
        //
        //Parameters:
        //    endian - The <Utils::Endianness> to read the bytes in.
        //
        //Returns:
        //    A uint32 containing the uint24 value at the next position in the Node's memory.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to download data from the Node.
        //    - <Error_NoData>: The requested bytePosition is outside the range of the datalogged data.
        //    - <Error_Connection>: A connection error has occurred.
        uint32 read_uint24(Utils::Endianness endian = Utils::bigEndian);

        //Function: read_int24
        //    Reads a 3-byte signed integer from the Node's memory.
        //
        //Parameters:
        //    endian - The <Utils::Endianness> to read the bytes in.
        //
        //Returns:
        //    An int32 containing the int24 value at the next position in the Node's memory.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to download data from the Node.
        //    - <Error_NoData>: The requested bytePosition is outside the range of the datalogged data.
        //    - <Error_Connection>: A connection error has occurred.
        int32 read_int24(Utils::Endianness endian = Utils::bigEndian);

        //Function: read_uint32
        //    Reads a 4-byte unsigned integer from the Node's memory.
        //
        //Parameters:
        //    endian - The <Utils::Endianness> to read the bytes in.
        //
        //Returns:
        //    The uint32 at the next position in the Node's memory.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to download data from the Node.
        //    - <Error_NoData>: The requested bytePosition is outside the range of the datalogged data.
        //    - <Error_Connection>: A connection error has occurred.
        uint32 read_uint32(Utils::Endianness endian = Utils::bigEndian);

        //Function: read_uint64
        //    Reads an 8-byte unsigned integer from the Node's memory.
        //
        //Parameters:
        //    endian - The <Utils::Endianness> to read the bytes in.
        //
        //Returns:
        //    The uint32 at the next position in the Node's memory.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to download data from the Node.
        //    - <Error_NoData>: The requested bytePosition is outside the range of the datalogged data.
        //    - <Error_Connection>: A connection error has occurred.
        uint64 read_uint64(Utils::Endianness endian = Utils::bigEndian);

        //Function: read_float
        //    Reads a 4-byte float from the Node's memory.
        //
        //Parameters:
        //    endian - The <Utils::Endianness> to read the bytes in.
        //
        //Returns:
        //    The float at the next position in the Node's memory.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to download data from the Node.
        //    - <Error_NoData>: The requested bytePosition is outside the range of the datalogged data.
        //    - <Error_Connection>: A connection error has occurred.
        float read_float(Utils::Endianness endian = Utils::bigEndian);

        //Function: read_string
        //    Reads a string of the specified length from the Node's memory.
        //
        //Parameters:
        //    length - The size (number of characters) to read for.
        //
        //Returns:
        //    The string at the next position in the Node's memory, of the requested length.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to download data from the Node.
        //    - <Error_NoData>: The requested bytePosition is outside the range of the datalogged data.
        //    - <Error_Connection>: A connection error has occurred.
        std::string read_string(uint32 length);
    };
}