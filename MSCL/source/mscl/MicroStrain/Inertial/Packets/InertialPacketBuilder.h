/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/Types.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include <vector>

namespace mscl
{
    //Title: InertialPacketBuilder

    //Class: InertialPacketBuilder
    //    A helper class to make it simple to create Inertial Packets
    class InertialPacketBuilder
    {
    public:
        //Constructor: InertialPacketBuilder
        //    Creates an InertialPacketBuilder object
        //
        //Parameters:
        //    descriptorSet - The 1-byte Descriptor Set
        //    field - The initial <InertialDataField> to add
        InertialPacketBuilder(uint8 descriptorSet, const InertialDataField& field);

    private:
        InertialPacketBuilder();                                        //default constructor disabled
        InertialPacketBuilder(const InertialPacketBuilder&);            //copy constructor disabled
        InertialPacketBuilder& operator=(const InertialPacketBuilder&); //assignment operator disabled

    private:
        //Variable: m_descriptorSet
        //    The MIP Descriptor Set for the packet
        uint8 m_descriptorSet;

        //Variable: m_fields
        //    The vector of <InertialDataField>s that are in the Inertial Packet
        std::vector<InertialDataField> m_fields;

    public:
        //Function: addField
        //    Adds a field to the vector of fields for this packet
        //
        //Parameters:
        //    field - The <InertialDataField> object to add
        void addField(const InertialDataField& field);

        //Function: buildPacket
        //    Takes the given packet information, including all fields, and builds an Inertial Packet as a <ByteStream>
        //
        //Returns:
        //    A <ByteStream> containing the bytes that make up an Inertial Packet
        ByteStream buildPacket();
    };
}