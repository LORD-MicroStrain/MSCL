/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "WirelessParser.h"
#include "Packets/AsyncDigitalAnalogPacket.h"
#include "Packets/AsyncDigitalPacket.h"
#include "Packets/BufferedLdcPacket.h"
#include "Packets/BufferedLdcPacket_16ch.h"
#include "Packets/DiagnosticPacket.h"
#include "Packets/HclSmartBearing_RawPacket.h"
#include "Packets/HclSmartBearing_CalPacket.h"
#include "Packets/LdcPacket.h"
#include "Packets/LdcPacket_16ch.h"
#include "Packets/RawAngleStrainPacket.h"
#include "Packets/RollerPacket.h"
#include "Packets/SyncSamplingPacket.h"
#include "Packets/SyncSamplingPacket_16ch.h"
#include "Packets/WirelessPacket.h"
#include "Packets/WirelessPacketCollector.h"
#include "Packets/WirelessPacketUtils.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/ChecksumBuilder.h"


namespace mscl
{
    WirelessParser::WirelessParser(WirelessPacketCollector& packetCollector, std::weak_ptr<ResponseCollector> responseCollector):
        m_packetCollector(packetCollector),
        m_responseCollector(responseCollector)
    {}

    void WirelessParser::processPacket(const WirelessPacket& packet, std::size_t lastReadPos)
    {
        //if this is a data packet
        if(packet.isDataPacket())
        {
            //store the data packet with the packet collector
            m_packetCollector.addDataPacket(packet);
        }
        else if(packet.isDiscoveryPacket())
        {
            //store the node discovery packet with the packet collector
            m_packetCollector.addNodeDiscoveryPacket(packet);
        }
        //if this is not a data packet
        else
        {
            //this could be a valid ASPP command response
            findMatchingResponse(packet, lastReadPos);
        }
    }
    
    bool WirelessParser::findMatchingResponse(DataBuffer& data)
    {
        //attempt to get the pointer from the weak_ptr
        std::shared_ptr<ResponseCollector> collector(m_responseCollector.lock());

        //if we got the shared_ptr
        if(collector)
        {
            //if the response collector is waiting for any responses
            if(collector->waitingForResponse())
            {
                //if the bytes match an expected response in the response collector
                if(collector->matchExpected(data))
                {
                    return true;
                }
            }
        }

        //we didn't match any expected responses
        return false;
    }

    bool WirelessParser::findMatchingResponse(const WirelessPacket& packet, std::size_t lastReadPos)
    {
        //attempt to get the pointer from the weak_ptr
        std::shared_ptr<ResponseCollector> collector(m_responseCollector.lock());

        //if we got the shared_ptr
        if(collector)
        {
            //if the response collector is waiting for any responses
            if(collector->waitingForResponse())
            {
                //if the bytes match an expected response in the response collector
                if(collector->matchExpected(packet, lastReadPos))
                {
                    return true;
                }
            }
        }

        //we didn't match any expected responses
        return false;
    }

    void WirelessParser::parse(DataBuffer& data, WirelessTypes::Frequency freq)
    {
        ParsePacketResult parseResult;    //holds the result of verifying whether it was a valid ASPP packet or not

        WirelessPacket packet;

        size_t bytesRemaining;    //holds how many bytes we have remaining, helps determine if the buffer has been moved by an external function

        //make a save point so we can revert if need be
        ReadBufferSavePoint savepoint(&data);

        std::size_t lastReadPosition;

        //while there is more data to be read in the DataBuffer
        while(data.moreToRead())
        {
            lastReadPosition = data.readPosition();

            //read the next byte (doesn't move data's read position)
            uint8 currentByte = data.peekByte();

            //skipByte is set to false when we don't want to skip to the next byte after we are done looking at the current byte
            bool moveToNextByte = true;

            //notEnoughData is true when the bytes could be a valid packet, but there isn't enough bytes to be sure
            bool notEnoughData = false;

            //if this is any ASPP Start of Packet byte
            if(currentByte == WirelessPacket::ASPP_V1_START_OF_PACKET_BYTE ||
               currentByte == WirelessPacket::ASPP_V2_START_OF_PACKET_BYTE)
            {
                //check if the packet is a valid ASPP packet, starting at this byte
                parseResult = parseAsPacket(data, packet, freq);

                //check the result of the parseAsPacket command
                switch(parseResult)
                {
                    //good packet, process it and then look for the next
                    case parsePacketResult_completePacket:
                        processPacket(packet, lastReadPosition);
                        savepoint.commit();
                        continue;    //packet has been processed, move to the next byte after the packet

                    case parsePacketResult_duplicate:
                        savepoint.commit();
                        continue;    //packet is a duplicate, but byte position has been moved. Move to the next byte after the packet
                    
                    //somethings incorrect in the packet, move passed the AA and start looking for the next packet
                    case parsePacketResult_invalidPacket:
                    case parsePacketResult_badChecksum:
                        savepoint.commit();
                        break;

                    //ran out of data, return and wait for more
                    case parsePacketResult_notEnoughData:
                        moveToNextByte = false;
                        notEnoughData = true;
                        break;

                    default:
                        assert(false); //unhandled verifyResult,  need to add a case for it
                }
            }

                
            //data is not a packet at this point

            bytesRemaining = data.bytesRemaining();

            //check if the bytes we currently have match an expected response
            //    This isn't perfect (could possibly use part of a partial ASPP packet as a cmd response), 
            //    but unfortunately its the best we can do with single byte responses being part of our protocol
            if(findMatchingResponse(data))
            {
                //the bytes have already moved, don't move to the next byte in the next iteration
                savepoint.commit();        
                moveToNextByte = false;
            }
            else
            {
                //failed to match 

                //if we didn't have enough data for a full packet, and it didn't match any expected responses
                if(notEnoughData)
                {
                    //look for packets after the current byte.
                    //    Even though this looks like it could be the start of an ASPP packet,
                    //    if we find any full ASPP packets inside of the these bytes, we need 
                    //    to pick them up and move on.
                    if(!findPacketInBytes(data, freq))
                    {
                        //if the read position in the bytes has been moved external to this function
                        if(data.bytesRemaining() != bytesRemaining)
                        {
                            //read position has moved somewhere else, so bytes have been committed. Commit in our local savepoint as well.
                            savepoint.commit();
                        }

                        //we didn't find a packet within this, so return from this function as we need to wait for more data
                        return;
                    }
                    else
                    {
                        savepoint.commit();
                    }
                }
            }

            //if we need to move to the next byte
            if (moveToNextByte)
            {
                //if the read position in the bytes has been moved external to this function
                if(data.bytesRemaining() != bytesRemaining)
                {
                    //read position has moved somewhere else, so bytes have been committed. Commit in our local savepoint as well.
                    savepoint.commit();
                }
                else
                {
                    //move to the next byte
                    data.read_uint8();
                }
            }
        }
    }

    bool WirelessParser::findPacketInBytes(DataBuffer& data, WirelessTypes::Frequency freq)
    {
        //create a read save point for the DataBuffer
        ReadBufferSavePoint savePoint(&data);

        std::size_t lastReadPosition;

        //while there are enough bytes remaining to make an ASPP response packet
        while(data.bytesRemaining() > WirelessPacket::ASPP_MIN_RESPONSE_PACKET_SIZE)
        {
            lastReadPosition = data.readPosition();

            //move to the next byte
            data.read_uint8();

            WirelessPacket packet;

            //if we found a packet within the bytes
            if(parseAsPacket(data, packet, freq) == parsePacketResult_completePacket)
            {
                //commit the data that was read
                savePoint.commit();

                //process the packet
                processPacket(packet, lastReadPosition);
                return true;
            }
        }

        //we didn't find any packet in the bytes buffer
        return false;
    }

    WirelessParser::ParsePacketResult WirelessParser::parseAsPacket_ASPP_v1(DataBuffer& data, WirelessPacket& packet, WirelessTypes::Frequency freq)
    {
        //Assume we are at the start of the packet, read the packet header
        //byte 1        - Start Of Packet
        //byte 2        - Delivery Stop Flag
        //byte 3        - App Data Type
        //byte 4 - 5    - Node Address (uint16)
        //byte 6        - Payload Length
        //byte 7 to N-4 - Payload
        //byte N-3      - Node RSSI
        //byte N-2      - Base RSSI
        //byte N-1      - Simple Checksum (MSB)
        //byte N        - Simple Checksum (LSB)

        //create a save point for the DataBuffer
        ReadBufferSavePoint savePoint(&data);

        std::size_t totalBytesAvailable = data.bytesRemaining();

        //we need at least 10 bytes for any ASPP v1 packet
        if(totalBytesAvailable < 10)
        {
            //Not Enough Data to tell if valid packet
            return parsePacketResult_notEnoughData;
        }

        //read byte 1
        uint8 startOfPacket = data.read_uint8();                        //Start Of Packet

        //verify that the first byte is the Start Of Packet
        if(startOfPacket != WirelessPacket::ASPP_V1_START_OF_PACKET_BYTE)
        {    
            //Invalid Packet
            return parsePacketResult_invalidPacket;
        }

        //read byte 2
        uint8 deliveryStopFlag = data.read_uint8();                    //Delivery Stop Flag

        //read byte 3
        uint8 appDataType = data.read_uint8();                         //App Data Type

        //read bytes 4 and 5
        uint16 nodeAddress = data.read_uint16();                  //Node Address

        //read byte 6
        uint8 payloadLength = data.read_uint8();                       //Payload Length (max of 255)

        //determine the full packet length 
        uint32 packetLength = payloadLength + WirelessPacket::ASPP_V1_NUM_BYTES_BEFORE_PAYLOAD + WirelessPacket::ASPP_V1_NUM_BYTES_AFTER_PAYLOAD;

        //the DataBuffer must be large enough to hold the rest of the packet
        if(totalBytesAvailable < packetLength)
        {
            //Not Enough Data to tell if valid packet
            return parsePacketResult_notEnoughData;
        }

        //create the Bytes vector to hold the payload bytes
        Bytes payload;
        payload.reserve(payloadLength);

        //loop through the payload
        for(uint8 payloadItr = 0; payloadItr < payloadLength; payloadItr++)
        {
            //store the payload bytes
            payload.push_back(data.read_uint8());                        //Payload Bytes
        }

        //read the node RSSI
        int16 nodeRSSI = data.read_int8();                                //Node RSSI
        
        //read the base station rssi
        int16 baseRSSI = data.read_int8();                                //Base RSSI

        //get the checksum sent in the packet
        uint16 checksum = data.read_uint16();                            //Checksum

        //build the checksum to calculate from all the bytes
        ChecksumBuilder calcChecksum;
        calcChecksum.append_uint8(deliveryStopFlag);
        calcChecksum.append_uint8(appDataType);
        calcChecksum.append_uint16(nodeAddress);
        calcChecksum.append_uint8(payloadLength);
        calcChecksum.appendBytes(payload);

        //verify that the returned checksum is the same as the one we calculated
        if(checksum != calcChecksum.simpleChecksum())
        {
            //Bad Checksum
            return parsePacketResult_badChecksum;
        }

        DeliveryStopFlags flags = DeliveryStopFlags::fromInvertedByte(deliveryStopFlag);

        //add all the info about the packet to the WirelessPacket reference passed in
        packet.deliveryStopFlags(flags);
        packet.type(static_cast<WirelessPacket::PacketType>(appDataType));
        packet.nodeAddress(static_cast<uint32>(nodeAddress));
        packet.payload(payload);
        packet.nodeRSSI(nodeRSSI);
        packet.baseRSSI(baseRSSI);
        packet.frequency(freq);

        //Correct the packet type if it is incorrect
        WirelessPacketUtils::correctPacketType(packet);

        //make sure the packet is valid based on its specific type
        if(!WirelessPacketUtils::packetIntegrityCheck(packet))
        {
            //not a valid packet, failed integrity check
            return parsePacketResult_invalidPacket;
        }

        //check if the packet is a duplicate
        if(isDuplicate(packet))
        {
            //even though it is a duplicate, we still have a complete packet so commit the bytes to skip over them
            savePoint.commit();

            //duplicate packet
            return parsePacketResult_duplicate;
        }

        //we have a complete packet, commit the bytes that we just read (move the read pointer)
        savePoint.commit();

        return parsePacketResult_completePacket;
    }

    WirelessParser::ParsePacketResult WirelessParser::parseAsPacket_ASPP_v2(DataBuffer& data, WirelessPacket& packet, WirelessTypes::Frequency freq)
    {
        //Assume we are at the start of the packet, read the packet header
        //byte 1         - Start Of Packet
        //byte 2         - Delivery Stop Flag
        //byte 3         - App Data Type
        //byte 4 - 7     - Node Address (uint32)
        //byte 8 - 9     - Payload Length
        //byte 10 to N-4 - Payload
        //byte N-3       - Node RSSI
        //byte N-2       - Base RSSI
        //byte N-1       - Fletcher Checksum (MSB)
        //byte N         - Fletcher Checksum (LSB)

        //create a save point for the DataBuffer
        ReadBufferSavePoint savePoint(&data);

        std::size_t totalBytesAvailable = data.bytesRemaining();

        //we need at least 13 bytes for any ASPP v2 packet (if empty payload)
        if(totalBytesAvailable < 13)
        {
            //Not Enough Data to tell if valid packet
            return parsePacketResult_notEnoughData;
        }

        //read byte 1
        uint8 startOfPacket = data.read_uint8();                        //Start Of Packet

        //verify that the first byte is the Start Of Packet
        if(startOfPacket != WirelessPacket::ASPP_V2_START_OF_PACKET_BYTE)
        {
            //Invalid Packet
            return parsePacketResult_invalidPacket;
        }

        //read byte 2
        uint8 deliveryStopFlag = data.read_uint8();                     //Delivery Stop Flag

        //read byte 3
        uint8 appDataType = data.read_uint8();                          //App Data Type

        //read bytes 4 - 7 
        uint32 nodeAddress = data.read_uint32();                        //Node Address

        //read bytes 8 and 9
        uint16 payloadLength = data.read_uint16();                      //Payload Length

        //determine the full packet length 
        size_t packetLength = payloadLength + WirelessPacket::ASPP_V2_NUM_BYTES_BEFORE_PAYLOAD + WirelessPacket::ASPP_V2_NUM_BYTES_AFTER_PAYLOAD;

        //the DataBuffer must be large enough to hold the rest of the packet
        if(totalBytesAvailable < packetLength)
        {
            //Not Enough Data to tell if valid packet
            return parsePacketResult_notEnoughData;
        }

        //create the Bytes vector to hold the payload bytes
        Bytes payload;
        payload.reserve(payloadLength);

        //loop through the payload
        for(uint16 payloadItr = 0; payloadItr < payloadLength; payloadItr++)
        {
            //store the payload bytes
            payload.push_back(data.read_uint8());                        //Payload Bytes
        }

        //read the node RSSI
        uint8 nodeRSSI = data.read_uint8();                             //Node RSSI

        //read the base station rssi
        uint8 baseRSSI = data.read_uint8();                             //Base RSSI

        //get the checksum sent in the packet
        uint16 checksum = data.read_uint16();                           //Checksum

        //build the checksum to calculate from all the bytes
        ChecksumBuilder calcChecksum;
        calcChecksum.append_uint8(startOfPacket);
        calcChecksum.append_uint8(deliveryStopFlag);
        calcChecksum.append_uint8(appDataType);
        calcChecksum.append_uint32(nodeAddress);
        calcChecksum.append_uint16(payloadLength);
        calcChecksum.appendBytes(payload);
        calcChecksum.append_uint8(nodeRSSI);
        calcChecksum.append_uint8(baseRSSI);

        //verify that the returned checksum is the same as the one we calculated
        if(checksum != calcChecksum.fletcherChecksum())
        {
            //Bad Checksum
            return parsePacketResult_badChecksum;
        }

        DeliveryStopFlags flags = DeliveryStopFlags::fromByte(deliveryStopFlag);

        //add all the info about the packet to the WirelessPacket reference passed in
        packet.deliveryStopFlags(flags);
        packet.type(static_cast<WirelessPacket::PacketType>(appDataType));
        packet.nodeAddress(nodeAddress);
        packet.payload(payload);
        packet.nodeRSSI(static_cast<int16>(nodeRSSI) - 205);
        packet.baseRSSI(static_cast<int16>(baseRSSI) - 205);
        packet.frequency(freq);

        //Correct the packet type if it is incorrect
        WirelessPacketUtils::correctPacketType(packet);

        //make sure the packet is valid based on its specific type
        if(!WirelessPacketUtils::packetIntegrityCheck(packet))
        {
            //not a valid packet, failed integrity check
            return parsePacketResult_invalidPacket;
        }

        //check if the packet is a duplicate
        if(isDuplicate(packet))
        {
            //even though it is a duplicate, we still have a complete packet so commit the bytes to skip over them
            savePoint.commit();

            //duplicate packet
            return parsePacketResult_duplicate;
        }

        //we have a complete packet, commit the bytes that we just read (move the read pointer)
        savePoint.commit();

        return parsePacketResult_completePacket;
    }

    WirelessParser::ParsePacketResult WirelessParser::parseAsPacket(DataBuffer& data, WirelessPacket& packet, WirelessTypes::Frequency freq)
    {
        std::size_t totalBytesAvailable = data.bytesRemaining();

        if(totalBytesAvailable == 0)
        {
            //Not Enough Data to tell if valid packet
            return parsePacketResult_notEnoughData;
        }

        //choose the correct ASPP version parser
        switch(data.peekByte())
        {
            case WirelessPacket::ASPP_V1_START_OF_PACKET_BYTE:
                return parseAsPacket_ASPP_v1(data, packet, freq);

            case WirelessPacket::ASPP_V2_START_OF_PACKET_BYTE:
                return parseAsPacket_ASPP_v2(data, packet, freq);

            default:
                return parsePacketResult_invalidPacket;
        }
    }

    bool WirelessParser::isDuplicate(const WirelessPacket& packet)
    {
        uint16 uniqueId;
        uint32 packetsNode = packet.nodeAddress();

        //check the packet type
        switch(packet.type())
        {
            //get the unique id depending on the type of packet
            case WirelessPacket::packetType_LDC:                        uniqueId = LdcPacket::getUniqueId(packet);                      break;
            case WirelessPacket::packetType_SyncSampling:               uniqueId = SyncSamplingPacket::getUniqueId(packet);             break;
            case WirelessPacket::packetType_BufferedLDC:                uniqueId = BufferedLdcPacket::getUniqueId(packet);              break;
            case WirelessPacket::packetType_AsyncDigital:               uniqueId = AsyncDigitalPacket::getUniqueId(packet);             break;
            case WirelessPacket::packetType_AsyncDigitalAnalog:         uniqueId = AsyncDigitalAnalogPacket::getUniqueId(packet);       break;
            case WirelessPacket::packetType_diagnostic:                 uniqueId = DiagnosticPacket::getUniqueId(packet);               break;
            case WirelessPacket::packetType_LDC_16ch:                   uniqueId = LdcPacket_16ch::getUniqueId(packet);                 break;
            case WirelessPacket::packetType_SyncSampling_16ch:          uniqueId = SyncSamplingPacket_16ch::getUniqueId(packet);        break;
            case WirelessPacket::packetType_BufferedLDC_16ch:           uniqueId = BufferedLdcPacket_16ch::getUniqueId(packet);         break;
            case WirelessPacket::packetType_HclSmartBearing_Calibrated: uniqueId = HclSmartBearing_CalPacket::getUniqueId(packet);      break;
            case WirelessPacket::packetType_HclSmartBearing_Raw:        uniqueId = HclSmartBearing_RawPacket::getUniqueId(packet);      break;
            case WirelessPacket::packetType_rawAngleStrain:             uniqueId = RawAngleStrainPacket::getUniqueId(packet);           break;
            case WirelessPacket::packetType_roller:                     uniqueId = RollerPacket::getUniqueId(packet);                   break;

            //isn't a valid data packet that has a unique id, so we can't check for duplicates
            case WirelessPacket::packetType_nodeCommand:
            case WirelessPacket::packetType_nodeErrorReply:
            case WirelessPacket::packetType_nodeDiscovery:
            case WirelessPacket::packetType_TCLinkLDC:
            case WirelessPacket::packetType_beaconEcho:
            case WirelessPacket::packetType_nodeDiscovery_v2:
            case WirelessPacket::packetType_nodeDiscovery_v3:
            case WirelessPacket::packetType_nodeDiscovery_v4:
            case WirelessPacket::packetType_nodeReceived:
            case WirelessPacket::packetType_nodeSuccessReply:
            case WirelessPacket::packetType_baseCommand:
            case WirelessPacket::packetType_baseSuccessReply:
            case WirelessPacket::packetType_baseErrorReply:
            case WirelessPacket::packetType_rfScanSweep:
            case WirelessPacket::packetType_SHM:
                return false;

            default:
                assert(false); //unhandled packet type, need to add a case for it
                return false;
        }

        //if we found the packet's node address in the lastPacketMap
        if(m_lastPacketMap.find(packetsNode) != m_lastPacketMap.end())
        {
            //if the unique id in the lastPacketMap matches the uniqueId from this packet
            if(m_lastPacketMap[packetsNode] == uniqueId)
            {
                //it is a duplicate packet
                return true;
            }
        }

        //update or set m_lastPacketMap's uniqueId for this node
        m_lastPacketMap[packetsNode] = uniqueId;

        //it is not a duplicate packet
        return false;    
    }
}