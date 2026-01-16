/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/MIP/MipDataField.h"

namespace mscl
{
    //Title: MipPacketBuilder

    //Class: MipPacketBuilder
    //    A helper class to make it simple to create Inertial Packets
    class MipPacketBuilder
    {
    public:
        //Constructor: MipPacketBuilder
        //    Creates a MipPacketBuilder object
        //
        //Parameters:
        //    descriptorSet - The 1-byte Descriptor Set
        //    field - The initial <MipDataField> to add
        MipPacketBuilder(const uint8 descriptorSet, const MipDataField& field);

    private:
        MipPacketBuilder();                                        //default constructor disabled
        MipPacketBuilder(const MipPacketBuilder&);            //copy constructor disabled
        MipPacketBuilder& operator=(const MipPacketBuilder&); //assignment operator disabled

        //Variable: m_descriptorSet
        //    The MIP Descriptor Set for the packet
        uint8 m_descriptorSet;

        //Variable: m_fields
        //    The vector of <MipDataField>s that are in the Inertial Packet
        std::vector<MipDataField> m_fields;

    public:
        //Function: addField
        //    Adds a field to the vector of fields for this packet
        //
        //Parameters:
        //    field - The <MipDataField> object to add
        void addField(const MipDataField& field);

        //Function: buildPacket
        //    Takes the given packet information, including all fields, and builds an Inertial Packet as a <ByteStream>
        //
        //Returns:
        //    A <ByteStream> containing the bytes that make up an Inertial Packet
        ByteStream buildPacket();
    };
} // namespace mscl
