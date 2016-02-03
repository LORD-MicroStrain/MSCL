/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "ReadEeprom_v2.h"
#include "mscl/MicroStrain/ByteStream.h"

namespace mscl
{
    ByteStream ReadEeprom_v2::buildCommand(NodeAddress nodeAddress, uint16 eepromAddress)
    {
        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint8(0xAA);                //Start of Packet
        cmd.append_uint8(0x05);                //Delivery Stop Flag
        cmd.append_uint8(0x00);                //App Data Type
        cmd.append_uint16(nodeAddress);        //Node address    (2 bytes)
        cmd.append_uint8(0x04);                //Payload length
        cmd.append_uint16(0x0007);            //Command ID    (2 bytes)
        cmd.append_uint16(eepromAddress);    //EEPROM Address (2 bytes)

        //calculate the checksum of bytes 2-10
        uint16 checksum = cmd.calculateSimpleChecksum(1, 9);

        cmd.append_uint16(checksum);        //Checksum        (2 bytes)

        return cmd;
    }

    ReadEeprom_v2::Response::Response(NodeAddress nodeAddress, uint16 eepromAddress, std::weak_ptr<ResponseCollector> collector):
        ResponsePattern(collector),
        m_nodeAddress(nodeAddress),
        m_eepromAddress(eepromAddress),
        m_eepromValue(0),
        m_errorCode(WirelessPacket::error_none)
    {
    }

    bool ReadEeprom_v2::Response::matchSuccessResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        uint8 dsf = packet.deliveryStopFlags().toByte();

        //check the main bytes of the packet
        if((dsf != 0x07 && dsf != 0x00) ||                    //delivery stop flag (Unfortunately some nodes report 0x00 and some report 0x07)
           packet.type() != 0x00 ||                            //app data type
           packet.nodeAddress() != m_nodeAddress ||            //node address
           payload.size() != 0x06 ||                        //payload length
           payload.read_uint16(0) != 0x0007 ||                //command ID
           payload.read_uint16(2) != m_eepromAddress        //eeprom address
           )
        {
            //failed to match some of the bytes
            return false;
        }

        //if we made it here, the packet matches the response pattern

        //get the eeprom value from the response
        m_success = true;
        m_errorCode = WirelessPacket::error_none;
        m_eepromValue = packet.payload().read_uint16(4);

        return true;
    }

    bool ReadEeprom_v2::Response::matchFailResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(packet.deliveryStopFlags().toByte() != 0x07 ||                    //delivery stop flag
           packet.type() != WirelessPacket::packetType_nodeErrorReply ||    //app data type
           packet.nodeAddress() != m_nodeAddress ||                            //node address
           payload.size() != 0x05 ||                                        //payload length
           payload.read_uint16(0) != 0x0007 ||                                //command ID
           payload.read_uint16(2) != m_eepromAddress                        //eeprom address
           )
        {
            //failed to match some of the bytes
            return false;
        }

        //if we made it here, the packet matches the response pattern

        //get the error code from the response
        m_success = false;
        m_errorCode = static_cast<WirelessPacket::ResponseErrorCode>(packet.payload().read_uint8(4));

        return true;
    }

    bool ReadEeprom_v2::Response::match(const WirelessPacket& packet)
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

    uint16 ReadEeprom_v2::Response::eepromValue() const
    {
        //throw an exception if the command failed
        throwIfFailed("Read Node EEPROM");

        return m_eepromValue;
    }

    WirelessPacket::ResponseErrorCode ReadEeprom_v2::Response::errorCode() const
    {
        return m_errorCode;
    }
}