/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "NmeaParser.h"

#include "mscl/Utils.h"
#include "NmeaPacketCollector.h"
#include "mscl/MicroStrain/DataBuffer.h"
#include "mscl/MicroStrain/ChecksumBuilder.h"

namespace mscl
{
    NmeaParser::NmeaParser(NmeaPacketCollector* packetCollector):
        m_packetCollector(packetCollector)
    {
    }

    void NmeaParser::processPacket(NmeaPacket& packet)
    {
        //store the data packet with the packet collector
        m_packetCollector->addPacket(packet);
    }

    void NmeaParser::parse(DataBuffer& data)
    {
        mscl::Bytes rawBytes;

        NmeaParserResult parseResult;    //holds the result of verifying whether it was a valid packet or not

        NmeaPacket packet;

        //moveToNextByte is set to false when we don't want to skip to the next byte after we are done looking at the current byte
        bool moveToNextByte = true;

        //notEnoughData is true when the bytes could be a valid packet, but there isn't enough bytes to be sure
        bool notEnoughData = false;

        //while there is more data to be read in the DataBuffer
        while(data.moreToRead())
        {
            //read the next byte (doesn't move data's read position)
            uint8 currentByte = data.peekByte();

            std::string byteStr(1, static_cast<char>(currentByte));

            //if this is a NMEA Start of Packet byte 
            if(byteStr == NmeaPacketInfo::NMEA_START_OF_PACKET)
            {
                mscl::ReadBufferSavePoint savePoint(&data);
                
                //check if the packet is a valid NMEA packet, starting at this byte
                parseResult = parseAsPacket(data, packet);

                size_t position = data.readPosition();
                uint8 nextByte;
                //check the result of the parseAsPacket command
                switch(parseResult)
                {
                    //good packet, process it and then look for the next
                    case NmeaParserResult_completePacket:
                        position = data.readPosition();
                        savePoint.revert();

                        //Read out the "in packet" bytes into the rawBytes buffer...
                        nextByte = data.peekByte();
                        while (data.readPosition() < position) 
                        {
                            rawBytes.push_back(data.read_uint8());
                        }
                        savePoint.commit();

                        processPacket(packet);
                        continue;    //packet has been processed, move to the next byte after the packet

                    //somethings incorrect in the packet, move passed this start byte and start looking for the next packet
                    case NmeaParserResult_invalidPacket:
                    case NmeaParserResult_badChecksum:
                        break;

                    //ran out of data, return and wait for more
                    case NmeaParserResult_notEnoughData:
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
                mscl::ReadBufferSavePoint savePoint(&data);
                //look for packets after the current byte.
                //    Even though this looks like it could be the start of a NMEA packet,
                //    if we find any full NMEA packets inside of the these bytes, we need 
                //    to pick them up and move on.
                if(!findPacketInBytes(data))
                {
                    //we didn't find a packet within this, so return from this function as we need to wait for more data
                    return;
                }
            }
        }
    }

    bool NmeaParser::findPacketInBytes(DataBuffer& data)
    {
        //create a read save point for the DataBuffer
        ReadBufferSavePoint savePoint(&data);

        //while there are enough bytes remaining to make a NMEA packet
        while(data.bytesRemaining() > NmeaPacketInfo::NMEA_MIN_PACKET_SIZE)
        {
            //move to the next byte
            data.read_uint8();

            NmeaPacket packet;

            //if we found a packet within the bytes
            if(parseAsPacket(data, packet) == NmeaParserResult_completePacket)
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

    NmeaParserResult NmeaParser::parseAsPacket(DataBuffer& data, NmeaPacket& packet)
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

        //make sure we have enough bytes to even be a NMEA packet
        if(totalBytesAvailable < NmeaPacketInfo::NMEA_MIN_PACKET_SIZE)
        {
            //Not Enough Data to tell if valid packet
            return NmeaParserResult_notEnoughData;
        }

        //read the first 2 bytes
        uint8 startOfPacket = data.read_uint8();                //Start of Packet
        std::string startOfPacketStr(1, static_cast<char>(startOfPacket));

        //verify that the Start of Packet value is correct
        if(startOfPacketStr != NmeaPacketInfo::NMEA_START_OF_PACKET)
        {
            //Invalid Packet
            return NmeaParserResult_invalidPacket;
        }

        //read byte 3
        uint8 descriptorSet = data.read_uint8();                //Descriptor Set

        //read byte 4
        uint8 payloadLen = data.read_uint8();                    //Payload Length

        //determine the full packet length
        uint32 packetLength = payloadLen + NmeaPacketInfo::NMEA_NUM_BYTES_BEFORE_PAYLOAD + NmeaPacketInfo::NMEA_NUM_BYTES_AFTER_PAYLOAD;

        //the DataBuffer must be large enough to hold the rest of the packet
        if(totalBytesAvailable < packetLength)
        {
            //Not Enough Data to tell if valid packet
            return NmeaParserResult_notEnoughData;
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

            //if this byte is supposed to be the field length byte
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
            return NmeaParserResult_invalidPacket;
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
            return NmeaParserResult_badChecksum;
        }


        //add all the info about the packet to the NmeaPacket reference passed in
        packet.payload(payload);

        //we have a complete packet, commit the bytes that we just read (move the read pointer)
        savePoint.commit();

        return NmeaParserResult_completePacket;
    }
}