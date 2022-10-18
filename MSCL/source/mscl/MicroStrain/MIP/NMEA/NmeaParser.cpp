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

    bool NmeaParser::isNmeaStartByte(uint8 byte)
    {
        switch (byte)
        {
        case NmeaPacketInfo::NMEA_START_OF_PACKET:
        case NmeaPacketInfo::NMEA_START_OF_PACKET_ALT:
            return true;

        default:
            return false;
        }
    }

    void NmeaParser::parse(DataBuffer& data)
    {
        NmeaParserResult parseResult;    //holds the result of verifying whether it was a valid packet or not
        NmeaPacket packet;

        //while there is more data to be read in the DataBuffer
        while(data.moreToRead())
        {
            //read the next byte (doesn't move data's read position)
            uint8 currentByte = data.peekByte();

            //if this is a NMEA Start of Packet byte 
            if(isNmeaStartByte(currentByte))
            {
                mscl::ReadBufferSavePoint savePoint(&data);
                
                //check if the packet is a valid NMEA packet, starting at this byte
                parseResult = parseAsPacket(data, packet);

                // revert read cursor to start of packet
                savePoint.revert();

                //check the result of the parseAsPacket command
                switch(parseResult)
                {
                    //good packet, process it and then look for the next
                    case NmeaParserResult_completePacket:

                        // advance cursor to end of packet
                        data.skipBytes(packet.size());

                        processPacket(packet);
                        continue;

                    //somethings incorrect in the packet, move past this start byte and start looking for the next packet
                    case NmeaParserResult_invalidPacket:
                    case NmeaParserResult_badChecksum:
                        // advance cursor to next byte
                        data.read_uint8();
                        break;

                    //ran out of data, return and wait for more
                    case NmeaParserResult_notEnoughData:
                        return;
                        break;

                    default:
                        assert(false);    //unhandled verifyResult, need to add a case for it
                }
            }
        }
    }

    NmeaParserResult NmeaParser::parseAsPacket(DataBuffer& data, NmeaPacket& packet)
    {
        // store packet start index
        const size_t startPacketIndex = data.readPosition();

        //read the first byte
        uint8 startOfPacket = data.read_uint8();

        // save point for start of payload (w/ out start byte)
        ReadBufferSavePoint savePayloadStart(&data);

        /////////// Validate Packet features ///////////

        //verify that the Start of Packet value is correct
        if(!isNmeaStartByte(startOfPacket))
        {
            //Invalid Packet
            return NmeaParserResult_invalidPacket;
        }
        
        //make sure we have enough bytes to even be a NMEA packet
        if(data.bytesRemaining() < NmeaPacketInfo::NMEA_MIN_PACKET_SIZE)
        {
            //Not Enough Data to tell if valid packet
            return NmeaParserResult_notEnoughData;
        }

        // check if end of packet indicator (\r\n) occurs before end of read buffer
        const size_t endPacketIndex = data.find_uint16(NmeaPacketInfo::NMEA_END_OF_PACKET);
        if (endPacketIndex >= data.appendPosition())
        {
            //Not Enough Data to tell if valid packet
            return NmeaParserResult_notEnoughData;
        }

        // check for checksum indicator, invalid if not present
        const size_t startChecksumIndex = data.find_uint8(NmeaPacketInfo::NMEA_CHECKSUM_DELIM, endPacketIndex);

        // add 2 to index, need to read out indices i + 1 and i + 2 for actual checksum value
        if (startChecksumIndex + 2 >= endPacketIndex)
        {
            return NmeaParserResult_invalidPacket;
        }

        /////////// Calculate Checksum ///////////

        // revert back to payload start for checksum calculation
        savePayloadStart.revert();

        // looping through each byte anyway, attempt to identify talker ID and sentence type
        bool talkerIdFound = false;
        bool sentenceTypeFound = false;
        std::string talkerId;
        std::string sentenceType;

        uint8 calculatedChecksum = 0;

        while (data.readPosition() < startChecksumIndex)
        {
            // read byte, XOR w/ calculated checksum
            uint8 readByte = data.read_uint8();
            calculatedChecksum ^= readByte;

            // other info parsing complete, continue
            if (talkerIdFound && sentenceTypeFound)
            {
                continue;
            }

            // if we find data start, talker ID and sentence type can no longer be found
            if (readByte == NmeaPacketInfo::NMEA_DATA_START_DELIM)
            {
                talkerIdFound = true;
                sentenceTypeFound = true;
                continue;
            }

            if (!talkerIdFound)
            {
                // append char to talkerId str
                talkerId += static_cast<char>(readByte);

                // talker ID complete if single char proprietary indicator or two chars
                if (readByte == NmeaPacketInfo::NMEA_PROPRIETARY_INDICATOR
                    || talkerId.size() >= NmeaPacketInfo::NMEA_TALKER_ID_LEN)
                {
                    talkerIdFound = true;
                }
            }
            else if (!sentenceTypeFound) // talker id has been found, start appending to sentence type
            {
                // append char to sentenceType str
                sentenceType += static_cast<char>(readByte);
            }
        }

        /////////// Validate Checksum ///////////

        // confirm start checksum indicator
        uint8 startChecksum = data.read_uint8();
        if (startChecksum != NmeaPacketInfo::NMEA_CHECKSUM_DELIM)
        {
            return NmeaParserResult_invalidPacket;
        }

        const std::string packetChecksumStr = data.read_string(2);
        const uint8 packetChecksum = static_cast<uint8>(std::stoi(packetChecksumStr, nullptr, 16));

        if (packetChecksum != calculatedChecksum)
        {
            return NmeaParserResult_badChecksum;
        }

        /////////// Finalize ///////////

        // add two to total length to include end bytes (\r\n)
        packet.message(data.bytesToRead(startPacketIndex, (endPacketIndex - startPacketIndex) + 2));
        packet.talkerId(talkerId);
        packet.sentenceType(sentenceType);

        return NmeaParserResult_completePacket;
    }
}