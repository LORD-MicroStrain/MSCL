/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/NodeMemory.h"

#include "mscl/MicroStrain/Wireless/WirelessNode.h"

namespace mscl
{
    NodeMemory::NodeMemory(WirelessNode& node) :
        m_node(node),
        m_totalBytes(0)
    {}

    void NodeMemory::skipBytes(uint32 numBytesToSkip)
    {
        for(uint32 i = 0; i < numBytesToSkip; i++)
        {
            read_uint8();
        }
    }

    uint8 NodeMemory::read_uint8()
    {
        //read the single byte from Node's memory
        return nextByte();
    }

    int16 NodeMemory::read_int16(Utils::Endianness endian /*= Utils::bigEndian*/)
    {
        //read single bytes from the Node's memory
        uint8 b1 = nextByte();
        uint8 b2 = nextByte();

        //build into a uint16 and return
        return make_int16(b1, b2, endian);
    }

    uint16 NodeMemory::read_uint16(Utils::Endianness endian /*= Utils::bigEndian*/)
    {
        //read single bytes from the Node's memory
        uint8 b1 = nextByte();
        uint8 b2 = nextByte();

        //build into a uint16 and return
        return make_uint16(b1, b2, endian);
    }

    uint32 NodeMemory::read_uint24(Utils::Endianness endian /*= Utils::bigEndian*/)
    {
        //read single bytes from the Node's memory
        uint8 b1 = nextByte();
        uint8 b2 = nextByte();
        uint8 b3 = nextByte();

        //build into a uint32 and return
        if(endian == Utils::Endianness::bigEndian)
        {
            return make_uint32(0, b1, b2, b3, endian);
        }

        return make_uint32(b1, b2, b3, 0, endian);
    }

    uint32 NodeMemory::read_uint32(Utils::Endianness endian /*= Utils::bigEndian*/)
    {
        //read single bytes from the Node's memory
        uint8 b1 = nextByte();
        uint8 b2 = nextByte();
        uint8 b3 = nextByte();
        uint8 b4 = nextByte();

        //build into a uint32 and return
        return make_uint32(b1, b2, b3, b4, endian);
    }

    int32 NodeMemory::read_int24(Utils::Endianness endian /*= Utils::bigEndian*/)
    {
        //read single bytes from the Node's memory
        uint8 b1 = nextByte();
        uint8 b2 = nextByte();
        uint8 b3 = nextByte();

        if(endian == Utils::bigEndian)
        {
            //if negative
            if(Utils::bitIsSet(b1, 7))
            {
                //build an int32 from the 3 bytes (flip the upper bytes to make negative)
                return make_int32(0xFF, b1, b2, b3, endian);
            }

            //build an int32 from the 3 bytes (flip the upper bytes to make negative)
            return make_int32(0x00, b1, b2, b3, endian);
        }

        //if negative
        if(Utils::bitIsSet(b3, 7))
        {
            //build an int32 from the 3 bytes (flip the upper bytes to make negative)
            return make_int32(b1, b2, b3, 0xFF, endian);
        }

        //build an int32 from the 3 bytes (flip the upper bytes to make negative)
        return make_int32(b1, b2, b3, 0x00, endian);
    }

    uint64 NodeMemory::read_uint64(Utils::Endianness endian /*= Utils::bigEndian*/)
    {
        //read single bytes from the Node's memory
        uint8 b1 = nextByte();
        uint8 b2 = nextByte();
        uint8 b3 = nextByte();
        uint8 b4 = nextByte();
        uint8 b5 = nextByte();
        uint8 b6 = nextByte();
        uint8 b7 = nextByte();
        uint8 b8 = nextByte();

        return make_uint64(b1, b2, b3, b4, b5, b6, b7, b8, endian);
    }

    float NodeMemory::read_float(Utils::Endianness endian /*= Utils::bigEndian*/)
    {
        //read single bytes from the Node's memory
        uint8 b1 = nextByte();
        uint8 b2 = nextByte();
        uint8 b3 = nextByte();
        uint8 b4 = nextByte();

        //build into a float and return
        return make_float(b1, b2, b3, b4, endian);
    }

    std::string NodeMemory::read_string(uint32 length)
    {
        std::string result;

        //read 1 byte for the length of the string
        for(uint32 itr = 0; itr < length; ++itr)
        {
            //append the characters to the string
            result.append(1, nextByte());
        }

        return result;
    }
} // namespace mscl
