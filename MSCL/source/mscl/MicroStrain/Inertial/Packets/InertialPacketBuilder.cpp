/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "InertialPacketBuilder.h"
#include "InertialPacket.h"

namespace mscl
{
    InertialPacketBuilder::InertialPacketBuilder(uint8 descriptorSet, const InertialDataField& field):
        m_descriptorSet(descriptorSet)
    {
        //add the field to the vector of fields
        m_fields.push_back(field);
    }

    void InertialPacketBuilder::addField(const InertialDataField& field)
    {
        m_fields.push_back(field);
    }

    ByteStream InertialPacketBuilder::buildPacket()
    {
        uint8 payloadLen = 0;

        ByteStream payloadBytes;

        //loop through all the fields
        for(InertialDataField field : m_fields)
        {
            //field length = (1 field len byte + 1 field desc byte + n field data bytes)
            size_t fieldLen = (1 + 1 + field.fieldData().size());
            
            //increase the payload length 
            payloadLen += static_cast<uint8>(fieldLen);

            //add the field length byte to the payloadBytes
            payloadBytes.append_uint8(static_cast<uint8>(fieldLen));

            //add the field descriptor byte to the payloadBytes
            payloadBytes.append_uint8(field.fieldDescriptor());

            //add the field data bytes to the payloadBytes (if any)
            payloadBytes.appendByteStream(field.fieldData());
        }

        ByteStream result;

        //add the first two "Sync" bytes
        result.append_uint16(InertialPacketInfo::INERTIAL_PACKET_START_OF_PACKET);

        //add the descriptor set byte
        result.append_uint8(m_descriptorSet);

        //add the payload length byte
        result.append_uint8(payloadLen);

        //add the payloadBytes that we just built up
        result.appendByteStream(payloadBytes);

        //calculate the checksum for the packet from all the bytes
        uint16 checksum = result.calculateFletcherChecksum(0, result.size() - 1);

        //add the checksum bytes
        result.append_uint16(checksum);

        //return the result bytes that we created
        return result;
    }
}