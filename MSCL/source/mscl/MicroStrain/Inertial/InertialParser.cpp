/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "InertialParser.h"

#include "mscl/Utils.h"
#include "Packets/InertialPacketCollector.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/DataBuffer.h"
#include "mscl/MicroStrain/ChecksumBuilder.h"

namespace mscl
{
    
    InertialParser::InertialParser(InertialPacketCollector* packetCollector, std::weak_ptr<ResponseCollector> responseCollector):
        m_packetCollector(packetCollector),
        m_responseCollector(responseCollector)
    {
    }

    void InertialParser::processPacket(InertialPacket& packet)
    {
        //if this is a data packet
        if(packet.isDataPacket())
        {
            //store the data packet with the packet collector
            m_packetCollector->addDataPacket(packet);
        }
        //if this is not a data packet
        else
        {
            //this could be a valid command response
            findMatchingResponse(packet);
        }
    }

    void InertialParser::findMatchingResponse(InertialPacket& packet)
    {
        //attempt to get the pointer from the weak_ptr
        std::shared_ptr<ResponseCollector> collector(m_responseCollector.lock());

        //if we got the shared_ptr
        if(collector)
        {
            //parse out the fields
            InertialDataFields fields = parseFields(packet);

            //if the response collector is waiting for any responses
            if(collector->waitingForResponse())
            {
                //check each field in the packet
                for(InertialDataField field : fields)
                {
                    //try to match the expected response in the response collector
                    collector->matchExpected(field);
                }
            }
        }
    }

    InertialDataFields InertialParser::parseFields(InertialPacket& packet)
    {
        InertialDataFields result;

        uint8 fieldDescriptor;
        uint16 fieldType;
        uint32 fieldLen;

        uint8 descriptorSet = packet.descriptorSet();

        //create a DataBuffer to make parsing easier
        DataBuffer payloadData(packet.payload());

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

            fieldType = Utils::make_uint16(descriptorSet, fieldDescriptor);

            //add the field to the m_dataFields vector
            InertialDataField tempField(fieldType, fieldBytes);
            result.push_back(tempField);
        }

        return result;
    }

    void InertialParser::parse(DataBuffer& data)
    {
        InertialParseResult parseResult;    //holds the result of verifying whether it was a valid packet or not

        InertialPacket packet;

        //moveToNextByte is set to false when we don't want to skip to the next byte after we are done looking at the current byte
        bool moveToNextByte = true;

        //notEnoughData is true when the bytes could be a valid packet, but there isn't enough bytes to be sure
        bool notEnoughData = false;

        //while there is more data to be read in the DataBuffer
        while(data.moreToRead())
        {
            //read the next byte (doesn't move data's read position)
            uint8 currentByte = data.peekByte();

            //if this is a MIP Start of Packet byte 
            if(currentByte == InertialPacketInfo::INERTIAL_PACKET_SOP1)
            {
                //check if the packet is a valid MIP Inertial packet, starting at this byte
                parseResult = parseAsPacket(data, packet);

                //check the result of the parseAsPacket command
                switch(parseResult)
                {
                    //good packet, process it and then look for the next
                    case inertialParserResult_completePacket:
                        processPacket(packet);
                        continue;    //packet has been processed, move to the next byte after the packet

                    //somethings incorrect in the packet, move passed this start byte and start looking for the next packet
                    case inertialParserResult_invalidPacket:
                    case inertialParserResult_badChecksum:
                        break;

                    //ran out of data, return and wait for more
                    case inertialParserResult_notEnoughData:
                        moveToNextByte = false;
                        notEnoughData = true;
                        break;

                    default:
                        assert(false);    //unhandled verifyResult, need to add a case for it
                }
            }

            //data is not a packet at this point

            //if we didn't have enough data for a full packet
            if(notEnoughData)
            {
                //look for packets after the current byte.
                //    Even though this looks like it could be the start of a MIP packet,
                //    if we find any full MIP packets inside of the these bytes, we need 
                //    to pick them up and move on.
                if(!findPacketInBytes(data))
                {
                    //we didn't find a packet within this, so return from this function as we need to wait for more data
                    return;
                }
            }

            //if we need to move to the next byte
            if (moveToNextByte)
            {
                //move to the next byte
                data.read_uint8();
            }
        }
    }

    bool InertialParser::findPacketInBytes(DataBuffer& data)
    {
        //create a read save point for the DataBuffer
        ReadBufferSavePoint savePoint(&data);

        //while there are enough bytes remaining to make a MIP packet
        while(data.bytesRemaining() > InertialPacketInfo::MIP_MIN_PACKET_SIZE)
        {
            //move to the next byte
            data.read_uint8();

            InertialPacket packet;

            //if we found a packet within the bytes
            if(parseAsPacket(data, packet) == inertialParserResult_completePacket)
            {
                //commit the data that was read
                savePoint.commit();

                //process the packet
                processPacket(packet);
                return true;
            }
        }

        //we didn't find any packet in the bytes buffer
        return false;
    }

    InertialParseResult InertialParser::parseAsPacket(DataBuffer& data, InertialPacket& packet)
    {
        //Assume that we are at the start of a packet
        //byte 1        - Start of Packet 1 (0x75)
        //byte 2        - Start of Packet 2 (0x65)
        //byte 3        - Descriptor Set
        //byte 4        - Payload Length
        //byte 5 to N-2 - Payload
        //byte N-1        - Checksum (MSB)
        //byte N        - Checksum (LSB)

        //create a save point for the DataBuffer
        ReadBufferSavePoint savePoint(&data);

        std::size_t totalBytesAvailable = data.bytesRemaining();

        //make sure we have enough bytes to even be a MIP packet
        if(totalBytesAvailable < InertialPacketInfo::MIP_MIN_PACKET_SIZE)
        {
            //Not Enough Data to tell if valid packet
            return inertialParserResult_notEnoughData;
        }

        //read the first 2 bytes
        uint16 startOfPacket = data.read_uint16();                //Start of Packet

        //verify that the Start of Packet value is correct
        if(startOfPacket != InertialPacketInfo::INERTIAL_PACKET_START_OF_PACKET)
        {
            //Invalid Packet
            return inertialParserResult_invalidPacket;
        }

        //read byte 3
        uint8 descriptorSet = data.read_uint8();                //Descriptor Set

        //read byte 4
        uint8 payloadLen = data.read_uint8();                    //Payload Length


        //determine the full packet length
        uint32 packetLength = payloadLen + InertialPacketInfo::MIP_NUM_BYTES_BEFORE_PAYLOAD + InertialPacketInfo::MIP_NUM_BYTES_AFTER_PAYLOAD;

        //the DataBuffer must be large enough to hold the rest of the packet
        if(totalBytesAvailable < packetLength)
        {
            //Not Enough Data to tell if valid packet
            return inertialParserResult_notEnoughData;
        }

        //create the Bytes vector to hold the payload bytes
        Bytes payload;
        payload.reserve(payloadLen);

        //loop through the payload
        for(uint8 payloadItr = 0; payloadItr < payloadLen; payloadItr++)
        {
            //store the payload bytes
            payload.push_back(data.read_uint8());                //Payload Bytes
        }

        //get the checksum sent in the packet
        uint16 checksum = data.read_uint16();                    //Checksum


        //build the checksum to calculate from all the bytes
        ChecksumBuilder calcChecksum;
        calcChecksum.append_uint16(startOfPacket);
        calcChecksum.append_uint8(descriptorSet);
        calcChecksum.append_uint8(payloadLen);
        calcChecksum.appendBytes(payload);

        if(checksum != calcChecksum.fletcherChecksum())
        {
            //Bad Checksum
            return inertialParserResult_badChecksum;
        }


        //add all the info about the packet to the InertialPacket reference passed in
        packet.descriptorSet(descriptorSet);
        packet.payload(payload);

        //we have a complete packet, commit the bytes that we just read (move the read pointer)
        savePoint.commit();

        return inertialParserResult_completePacket;
    }
}