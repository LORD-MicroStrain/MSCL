/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Commands/ReadEeprom_v2.h"

#include "mscl/MicroStrain/Wireless/Commands/WirelessProtocol.h"

namespace mscl
{
    ByteStream ReadEeprom_v2::buildCommand(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, uint16 eepromAddress)
    {
        //build the command ByteStream
        ByteStream cmd;

        if(asppVer == WirelessPacket::aspp_v3)
        {
            cmd.append_uint8(0xAC);                                     //Start of Packet
            cmd.append_uint8(0x04);                                     //Delivery Stop Flag
            cmd.append_uint8(0x00);                                     //App Data Type
            cmd.append_uint32(nodeAddress);                             //Node address
            cmd.append_uint16(0x0004);                                  //Payload length
            cmd.append_uint16(WirelessProtocol::cmdId_readEeprom_v2);   //Command ID
            cmd.append_uint16(eepromAddress);                           //EEPROM Address
            cmd.append_uint16(0x7F7F);                                  //dummy RSSI bytes
            cmd.append_uint32(cmd.calculateCrcChecksum());              //Checksum
        }
        else
        {
            cmd.append_uint8(0xAA);                                     //Start of Packet
            cmd.append_uint8(0x05);                                     //Delivery Stop Flag
            cmd.append_uint8(0x00);                                     //App Data Type
            cmd.append_uint16(static_cast<uint16>(nodeAddress));        //Node address    (2 bytes)
            cmd.append_uint8(0x04);                                     //Payload length
            cmd.append_uint16(WirelessProtocol::cmdId_readEeprom_v2);   //Command ID    (2 bytes)
            cmd.append_uint16(eepromAddress);                           //EEPROM Address (2 bytes)
            cmd.append_uint16(cmd.calculateSimpleChecksum(1, 9));       //Checksum        (2 bytes)
        }

        return cmd;
    }

    ReadEeprom_v2::Response::Response(NodeAddress nodeAddress, uint16 eepromAddress, std::weak_ptr<ResponseCollector> collector) :
        WirelessResponsePattern(collector, WirelessProtocol::cmdId_readEeprom_v2, nodeAddress),
        m_nodeAddress(nodeAddress),
        m_eepromAddress(eepromAddress),
        m_eepromValue(0),
        m_errorCode(WirelessPacket::error_none)
    {}

    bool ReadEeprom_v2::Response::matchSuccessResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(packet.nodeAddress() != m_nodeAddress ||                             //node address
           payload.size() != 6 ||                                               //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_readEeprom_v2 ||   //command ID
           payload.read_uint16(2) != m_eepromAddress                            //eeprom address
           )
        {
            //failed to match some of the bytes
            return false;
        }

        if(packet.asppVersion() == WirelessPacket::aspp_v3)
        {
            //check the main bytes of the packet
            if(!packet.deliveryStopFlags().pc ||                                    //delivery stop flag
               packet.type() != WirelessPacket::packetType_nodeSuccessReply         //app data type
               )
            {
                //failed to match some of the bytes
                return false;
            }
        }
        else
        {
            //check the main bytes of the packet
            uint8 dsf = packet.deliveryStopFlags().toInvertedByte();
            if((dsf != 0x07 && dsf != 0x00) ||                                      //delivery stop flag (Unfortunately some nodes report 0x00 and some report 0x07)
               packet.type() != 0x00                                                //app data type
               )
            {
                //failed to match some of the bytes
                return false;
            }
        }

        //if we made it here, the packet matches the response pattern

        //get the eeprom value from the response
        m_errorCode = WirelessPacket::error_none;
        m_eepromValue = packet.payload().read_uint16(4);

        return true;
    }

    bool ReadEeprom_v2::Response::matchFailResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        if(packet.asppVersion() == WirelessPacket::aspp_v3)
        {
            //check the main bytes of the packet
            if(packet.deliveryStopFlags().toByte() != 0x08 ||                           //delivery stop flag
               packet.type() != WirelessPacket::packetType_nodeErrorReply ||            //app data type
               packet.nodeAddress() != m_nodeAddress ||                                 //node address
               payload.size() != 5 ||                                                   //payload length
               payload.read_uint16(0) != WirelessProtocol::cmdId_readEeprom_v2 ||       //command ID
               payload.read_uint16(2) != m_eepromAddress                                //eeprom address
               )
            {
                //failed to match some of the bytes
                return false;
            }
        }
        else
        {
            //check the main bytes of the packet
            if(packet.deliveryStopFlags().toInvertedByte() != 0x07 ||                   //delivery stop flag
               packet.type() != WirelessPacket::packetType_nodeErrorReply ||            //app data type
               packet.nodeAddress() != m_nodeAddress ||                                 //node address
               payload.size() != 5 ||                                                   //payload length
               payload.read_uint16(0) != WirelessProtocol::cmdId_readEeprom_v2 ||       //command ID
               payload.read_uint16(2) != m_eepromAddress                                //eeprom address
               )
            {
                //failed to match some of the bytes
                return false;
            }
        }

        //if we made it here, the packet matches the response pattern

        //get the error code from the response
        m_errorCode = static_cast<WirelessPacket::ResponseErrorCode>(packet.payload().read_uint8(4));

        return true;
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
} // namespace mscl
