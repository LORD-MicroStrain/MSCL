/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "WriteEeprom_v2.h"
#include "WirelessProtocol.h"
#include "mscl/MicroStrain/ByteStream.h"

namespace mscl
{
    ByteStream WriteEeprom_v2::buildCommand(NodeAddress nodeAddress, uint16 eepromAddress, uint16 valueToWrite)
    {
        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint8(0xAA);                                           //Start of Packet
        cmd.append_uint8(0x05);                                           //Delivery Stop Flag
        cmd.append_uint8(0x00);                                           //App Data Type
        cmd.append_uint16(nodeAddress);                                   //Node address    (2 bytes)
        cmd.append_uint8(0x06);                                           //Payload length
        cmd.append_uint16(WirelessProtocol::cmdId_writeEeprom_v2);        //Command ID    (2 bytes)
        cmd.append_uint16(eepromAddress);                                 //EEPROM Address (2 bytes)
        cmd.append_uint16(valueToWrite);                                  //EEPROM Address (2 bytes)

        //calculate the checsum of bytes 2-12
        uint16 checksum = cmd.calculateSimpleChecksum(1, 11);

        cmd.append_uint16(checksum);        //Checksum        (2 bytes)

        return cmd;
    }

    WriteEeprom_v2::Response::Response(NodeAddress nodeAddress, uint16 eepromAddress, uint16 valueWritten, std::weak_ptr<ResponseCollector> collector):
        ResponsePattern(collector),
        m_nodeAddress(nodeAddress),
        m_eepromAddress(eepromAddress),
        m_eepromValue(valueWritten),
        m_errorCode(WirelessPacket::error_none)
    {
    }

    bool WriteEeprom_v2::Response::matchSuccessResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        uint8 dsf = packet.deliveryStopFlags().toInvertedByte();

        //check the main bytes of the packet
        if(packet.type() != 0x00 ||                        //app data type
           packet.nodeAddress() != m_nodeAddress ||        //node address
           payload.size() != 0x06                        //payload length
           )
        {
            //failed to match some of the bytes
            return false;
        }

        //stop flag of 0x07 -> look for command id of 0x0008
        if(dsf == 0x07)
        {
            //check command ID
            if(payload.read_uint16(0) != WirelessProtocol::cmdId_writeEeprom_v2)    //this is the correct packet
            {
                return false;
            }
        }
        //stop flag of 0x00 -> look for command id of 0x0007
        else if(dsf == 0x00)
        {
            //check command ID
            if(payload.read_uint16(0) != 0x0007)        //Unfortunately, some nodes report 0x0007 as a cmd byte, which is wrong
            {
                return false;
            }
        }

        //Check EEPROM Address
        if(payload.read_uint16(2) != m_eepromAddress)
        {
            return false;
        }

        //Check EEPROM Value
        if(payload.read_uint16(4) != m_eepromValue)
        {
            return false;
        }

        //if we made it here, the packet matches the response pattern

        //set the result
        m_success = true;

        //we have fully matched the response
        m_fullyMatched = true;

        //notify that the response was matched
        m_matchCondition.notify();

        return true;
    }

    bool WriteEeprom_v2::Response::matchFailResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(packet.deliveryStopFlags().toInvertedByte() != 0x07 ||                    //delivery stop flag
           packet.type() != WirelessPacket::packetType_nodeErrorReply ||             //app data type
           packet.nodeAddress() != m_nodeAddress ||                                  //node address
           payload.size() != 0x07 ||                                                 //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_writeEeprom_v2 ||       //command ID
           payload.read_uint16(2) != m_eepromAddress ||                              //eeprom address
           payload.read_uint16(4) != m_eepromValue                                   //eeprom value
           )
        {
            //failed to match some of the bytes
            return false;
        }

        //if we made it here, the packet matches the response pattern

        //get the error code from the response
        m_success = false;
        m_errorCode = static_cast<WirelessPacket::ResponseErrorCode>(packet.payload().read_uint8(6));

        return true;
    }

    bool WriteEeprom_v2::Response::match(const WirelessPacket& packet)
    {
        //if the bytes match the success response
        if(matchSuccessResponse(packet))
        {
            //we have fully matched the response
            m_fullyMatched = true;

            //notify that the response was matched
            m_matchCondition.notify();
            return true;
        }
        //if the bytes match the fail response
        else if(matchFailResponse(packet))
        {
            //we have fully matched the response
            m_fullyMatched = true;

            //notify that the response was matched
            m_matchCondition.notify();
            return true;
        }

        //the bytes don't match any response
        return false;
    }

    WirelessPacket::ResponseErrorCode WriteEeprom_v2::Response::errorCode() const
    {
        return m_errorCode;
    }
}