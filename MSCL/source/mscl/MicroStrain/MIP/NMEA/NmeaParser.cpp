/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "NmeaParser.h"

#include "mscl/Utils.h"
#include "NmeaPacketCollector.h"

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
        data.copyBytesTo(m_pendingData);

        DataBuffer pendingData(m_pendingData);

        //while there is more data to be read in the DataBuffer
        while(pendingData.moreToRead())
        {
            //read the next byte (doesn't move data's read position)
            uint8 currentByte = pendingData.peekByte();

            size_t advanceBytes = 1;

            //if this is a NMEA Start of Packet byte 
            if(isNmeaStartByte(currentByte))
            {
                mscl::ReadBufferSavePoint savePoint(&pendingData);
                
                //check if the packet is a valid NMEA packet, starting at this byte
                NmeaPacket packet;
                NmeaParserResult parseResult = parseAsPacket(pendingData, packet);

                // revert read cursor to start of packet
                savePoint.revert();

                //check the result of the parseAsPacket command
                bool continueParsing = true;
                switch(parseResult)
                {
                    //good packet, process it and then look for the next
                    case NmeaParserResult_completePacket:
                        processPacket(packet);

                        // advance cursor to end of packet
                        advanceBytes = packet.size();
                        break;

                    //ran out of data, return and wait for more
                    case NmeaParserResult_notEnoughData:
                        continueParsing = false;
                        break;

                    //somethings incorrect in the packet, move past this start byte and start looking for the next packet
                    case NmeaParserResult_invalidPacket:
                    case NmeaParserResult_badChecksum:
                        break;

                    default:
                        assert(false);    //unhandled verifyResult, need to add a case for it
                }

                if (!continueParsing)
                {
                    break;
                }
            }

            pendingData.skipBytes(advanceBytes);
        }

        // ensure we're not holding on to more data than the max packet size
        int trimBytes = static_cast<int>(pendingData.bytesRemaining()) - NmeaPacketInfo::NMEA_MAX_PACKET_SIZE;
        trimBytes = trimBytes < 0 ? 0 : trimBytes;
        pendingData.skipBytes(static_cast<size_t>(trimBytes));

        // throw out data that's no longer needed
        pendingData.shiftExtraToStart();

        // resize pending ByteStream to only hold onto data that's still relevant
        m_pendingData.resize(pendingData.bytesRemaining());
    }

    NmeaParserResult NmeaParser::parseAsPacket(DataBuffer& data, NmeaPacket& packet)
    {
        // store packet start index
        const size_t startPacketIndex = data.readPosition();
        const size_t endBufferIndex = data.appendPosition();

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

        // check if end of packet indicator (\r\n) occurs within packet size limit
        size_t maxIndex = data.readPosition() + NmeaPacketInfo::NMEA_MAX_PACKET_SIZE;
        maxIndex = maxIndex <= endBufferIndex ? maxIndex : endBufferIndex;
        const size_t endPacketIndex = data.find_uint16(NmeaPacketInfo::NMEA_END_OF_PACKET, maxIndex);
        if (endPacketIndex >= maxIndex)
        {
            // if maxIndex is within bytes remaining in buffer but indicator not found, invalid packet
            if (maxIndex < endBufferIndex)
            {
                return NmeaParserResult_invalidPacket;
            }

            // Not Enough Data to tell if valid packet
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