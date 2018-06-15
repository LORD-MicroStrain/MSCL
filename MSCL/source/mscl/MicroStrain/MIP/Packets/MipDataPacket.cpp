/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "MipDataPacket.h"

#include "mscl/Utils.h"
#include "MipFieldParser.h"
#include "mscl/MicroStrain/DataBuffer.h"

namespace mscl
{                    
    MipDataPacket::MipDataPacket():
        m_collectedTime(0),
        m_utcTime(0),
        m_utcTimeValid(false),
        m_utcTimeFlags(0)
    {
    }

    MipDataPacket::MipDataPacket(const MipPacket& packet):
        m_collectedTime(Timestamp::timeNow()),
        m_utcTime(0),
        m_utcTimeValid(false),
        m_utcTimeFlags(0)
    {
        //construct the data packet from the MipPacket passed in
        m_descriptorSet     = packet.descriptorSet();
        m_payload           = Payload(packet.payload());

        //parse the data fields in the packet
        parseDataFields();
    }

    void MipDataPacket::parseDataFields()
    {
        uint8 fieldDescriptor;
        uint16 fieldType;
        uint32 fieldLen;

        //create a DataBuffer to make parsing easier
        DataBuffer payloadData(m_payload.data());

        while(payloadData.moreToRead())
        {
            Bytes fieldBytes;

            //read the field length byte
            fieldLen = payloadData.read_uint8();

            //read the field descriptor byte
            fieldDescriptor = payloadData.read_uint8();

            //read all the bytes for the current field (up to the field length)
            for(uint32 itr = 0; itr < fieldLen - 2; itr++)
            {
                //add the field bytes to a container
                fieldBytes.push_back(payloadData.read_uint8());
            } 

            fieldType = Utils::make_uint16(m_descriptorSet, fieldDescriptor);

            //add the field to the m_dataFields vector
            MipDataField tempField(fieldType, fieldBytes);
            m_dataFields.push_back(tempField);

            //parse the data points that are in the existing field that we just created
            parsePointsInField(tempField);
        }
    }

    bool MipDataPacket::isFieldTimestamp(const MipDataField& field)
    {
        switch(field.fieldId())
        {
            //fields that we want to treat as timestamps for the whole packet
            case MipTypes::CH_FIELD_DISP_DISPLACEMENT_TS:
                return true;

            default:
                return false;
        }
    }

    void MipDataPacket::parsePointsInField(const MipDataField& field)
    {
        if(isFieldTimestamp(field))
        {
            parseTimeStamp(field);
        }
        else
        {
            MipFieldParser::parseField(field, m_points);
        }
    }

    void MipDataPacket::parseTimeStamp(const MipDataField& field)
    {
        DataBuffer bytes(field.fieldData());

        if(field.fieldId() == MipTypes::CH_FIELD_DISP_DISPLACEMENT_TS)
        {
            m_utcTimeFlags = bytes.read_uint8();

            m_utcTimeValid = (m_utcTimeFlags == 1);
            m_utcTime.setTime(bytes.read_uint64());
        }
    }

    const MipDataPoints& MipDataPacket::data() const
    {
        return m_points;
    }

    const Timestamp& MipDataPacket::collectedTimestamp() const
    {
        return m_collectedTime;
    }

    const Timestamp& MipDataPacket::utcTimestamp() const
    {
        return m_utcTime;
    }

    bool MipDataPacket::utcTimeValid() const
    {
        return m_utcTimeValid;
    }

    uint16 MipDataPacket::utcTimeFlags() const
    {
        return m_utcTimeFlags;
    }
}