/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "MipParser.h"

#include "mscl/Utils.h"
#include "Packets/MipPacketCollector.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/DataBuffer.h"
#include "mscl/MicroStrain/ChecksumBuilder.h"

namespace mscl
{
    MipParser::MipParser(MipPacketCollector* packetCollector, std::weak_ptr<ResponseCollector> responseCollector):
        m_packetCollector(packetCollector),
        m_responseCollector(responseCollector)
    {
    }

    void MipParser::processPacket(MipPacket& packet)
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

    void MipParser::findMatchingResponse(MipPacket& packet)
    {
        //attempt to get the pointer from the weak_ptr
        std::shared_ptr<ResponseCollector> collector(m_responseCollector.lock());

        //if we got the shared_ptr
        if(collector)
        {
            //parse out the fields
            MipDataFields fields = parseFields(packet);

            //if the response collector is waiting for any responses
            if(collector->waitingForResponse())
            {
                //check each field in the packet
                for(MipDataField field : fields)
                {
                    //try to match the expected response in the response collector
                    collector->matchExpected(field);
                }
            }
        }
    }

    MipDataFields MipParser::parseFields(MipPacket& packet)
    {
        MipDataFields result;

        uint8 fieldDescriptor;
        uint16 fieldType;
        uint32 fieldLen;

        uint8 descriptorSet = packet.descriptorSet();

        //create a DataBuffer to make parsing easier
        DataBuffer payloadData(packet.payload());

        while(payloadData.moreToRead())
        {
            try
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
                MipDataField tempField(fieldType, fieldBytes);
                result.push_back(tempField);
            }
            catch(...)
            {
                //possible corrupted packet, just break out and skip trying to parse anything else
                break;
            }
        }

        return result;
    }

    void MipParser::parse(DataBuffer& data)
    {
        MipParseResult parseResult;    //holds the result of verifying whether it was a valid packet or not

        MipPacket packet;

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
            if(currentByte == MipPacketInfo::MIP_PACKET_SOP1)
            {
                //check if the packet is a valid MIP packet, starting at this byte
                parseResult = parseAsPacket(data, packet);

                //check the result of the parseAsPacket command
                switch(parseResult)
                {
                    //good packet, process it and then look for the next
                    case mipParserResult_completePacket:
                        processPacket(packet);
                        continue;    //packet has been processed, move to the next byte after the packet

                    //somethings incorrect in the packet, move passed this start byte and start looking for the next packet
                    case mipParserResult_invalidPacket:
                    case mipParserResult_badChecksum:
                        break;

                    //ran out of data, return and wait for more
                    case mipParserResult_notEnoughData:
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

    bool MipParser::findPacketInBytes(DataBuffer& data)
    {
        //create a read save point for the DataBuffer
        ReadBufferSavePoint savePoint(&data);

        //while there are enough bytes remaining to make a MIP packet
        while(data.bytesRemaining() > MipPacketInfo::MIP_MIN_PACKET_SIZE)
        {
            //move to the next byte
            data.read_uint8();

            MipPacket packet;

            //if we found a packet within the bytes
            if(parseAsPacket(data, packet) == mipParserResult_completePacket)
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

    MipParseResult MipParser::parseAsPacket(DataBuffer& data, MipPacket& packet)
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
        if(totalBytesAvailable < MipPacketInfo::MIP_MIN_PACKET_SIZE)
        {
            //Not Enough Data to tell if valid packet
            return mipParserResult_notEnoughData;
        }

        //read the first 2 bytes
        uint16 startOfPacket = data.read_uint16();                //Start of Packet

        //verify that the Start of Packet value is correct
        if(startOfPacket != MipPacketInfo::MIP_PACKET_START_OF_PACKET)
        {
            //Invalid Packet
            return mipParserResult_invalidPacket;
        }

        //read byte 3
        uint8 descriptorSet = data.read_uint8();                //Descriptor Set

        //read byte 4
        uint8 payloadLen = data.read_uint8();                    //Payload Length

        //determine the full packet length
        uint32 packetLength = payloadLen + MipPacketInfo::MIP_NUM_BYTES_BEFORE_PAYLOAD + MipPacketInfo::MIP_NUM_BYTES_AFTER_PAYLOAD;

        //the DataBuffer must be large enough to hold the rest of the packet
        if(totalBytesAvailable < packetLength)
        {
            //Not Enough Data to tell if valid packet
            return mipParserResult_notEnoughData;
        }

        //create the Bytes vector to hold the payload bytes
        Bytes payload;
        payload.reserve(payloadLen);

        uint16 fieldLengthTotal = 0;
        uint16 nextFieldLenPos = 0;

        //loop through the payload
        for(uint8 payloadItr = 0; payloadItr < payloadLen; payloadItr++)
        {
            uint8 currentByte = data.read_uint8();

            //if this byte is suppossed to be the field length byte
            if(payloadItr == nextFieldLenPos)
            {
                //add up the total field length bytes to verify they look correct
                fieldLengthTotal += currentByte;
                nextFieldLenPos += currentByte;
            }

            //store the payload bytes
            payload.push_back(currentByte);                //Payload Bytes
        }

        //verify that the total field lengths add up to the payload length
        if(fieldLengthTotal != payloadLen)
        {
            //Invalid Packet
            return mipParserResult_invalidPacket;
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
            return mipParserResult_badChecksum;
        }


        //add all the info about the packet to the MipPacket reference passed in
        packet.descriptorSet(descriptorSet);
        packet.payload(payload);

        //we have a complete packet, commit the bytes that we just read (move the read pointer)
        savePoint.commit();

        return mipParserResult_completePacket;
    }
}