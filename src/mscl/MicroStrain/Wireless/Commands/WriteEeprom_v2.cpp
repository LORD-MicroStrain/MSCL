/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Commands/WriteEeprom_v2.h"

#include "mscl/MicroStrain/Wireless/Commands/WirelessProtocol.h"

namespace mscl
{
    ByteStream WriteEeprom_v2::buildCommand(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, uint16 eepromAddress, uint16 valueToWrite)
    {
        //build the command ByteStream
        ByteStream cmd;

        if(asppVer == WirelessPacket::aspp_v3)
        {
            cmd.append_uint8(WirelessPacket::ASPP_V3_SOP);                  //Start of Packet
            cmd.append_uint8(0x04);                                         //Delivery Stop Flag
            cmd.append_uint8(0x00);                                         //App Data Type
            cmd.append_uint32(nodeAddress);                                 //Node address
            cmd.append_uint16(0x0006);                                      //Payload length
            cmd.append_uint16(WirelessProtocol::cmdId_writeEeprom_v2);      //Command ID
            cmd.append_uint16(eepromAddress);                               //EEPROM Address
            cmd.append_uint16(valueToWrite);                                //EEPROM Address
            cmd.append_uint16(0x7F7F);                                      //dummy RSSI bytes
            cmd.append_uint32(cmd.calculateCrcChecksum());                  //Checksum
        }
        else
        {
            cmd.append_uint8(WirelessPacket::ASPP_V1_SOP);                  //Start of Packet
            cmd.append_uint8(0x05);                                         //Delivery Stop Flag
            cmd.append_uint8(0x00);                                         //App Data Type
            cmd.append_uint16(static_cast<uint16>(nodeAddress));            //Node address    (2 bytes)
            cmd.append_uint8(0x06);                                         //Payload length
            cmd.append_uint16(WirelessProtocol::cmdId_writeEeprom_v2);      //Command ID    (2 bytes)
            cmd.append_uint16(eepromAddress);                               //EEPROM Address (2 bytes)
            cmd.append_uint16(valueToWrite);                                //EEPROM Address (2 bytes)
            cmd.append_uint16(cmd.calculateSimpleChecksum(1, 11));          //Checksum        (2 bytes)
        }

        return cmd;
    }

    WriteEeprom_v2::Response::Response(NodeAddress nodeAddress, uint16 eepromAddress, uint16 valueWritten, std::weak_ptr<ResponseCollector> collector) :
        WirelessResponsePattern(collector, WirelessProtocol::cmdId_writeEeprom_v2, nodeAddress),
        m_nodeAddress(nodeAddress),
        m_eepromAddress(eepromAddress),
        m_eepromValue(valueWritten),
        m_errorCode(WirelessPacket::error_none)
    {}

    bool WriteEeprom_v2::Response::matchSuccessResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(packet.nodeAddress() != m_nodeAddress ||                             //node address
           payload.size() != 6 ||                                               //payload length
           payload.read_uint16(2) != m_eepromAddress ||                         //eeprom address
           payload.read_uint16(4) != m_eepromValue                              //eeprom value
           )
        {
            //failed to match some of the bytes
            return false;
        }

        if(packet.asppVersion() == WirelessPacket::aspp_v3)
        {
            //check the main bytes of the packet
            if(!packet.deliveryStopFlags().pc ||                                    //delivery stop flag
               packet.type() != WirelessPacket::packetType_nodeSuccessReply ||      //app data type
               payload.read_uint16(0) != WirelessProtocol::cmdId_writeEeprom_v2     //command ID
               )
            {
                //failed to match some of the bytes
                return false;
            }
        }
        else
        {
            //check the main bytes of the packet
            if(packet.type() != 0x00)
            {
                //failed to match some of the bytes
                return false;
            }

            uint8 dsf = packet.deliveryStopFlags().toInvertedByte();
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
        }

        //if we made it here, the packet matches the response pattern
        return true;
    }

    bool WriteEeprom_v2::Response::matchFailResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(!packet.deliveryStopFlags().pc ||                                        //delivery stop flag
            packet.type() != WirelessPacket::packetType_nodeErrorReply ||            //app data type
            packet.nodeAddress() != m_nodeAddress ||                                 //node address
            payload.size() != 0x07 ||                                                //payload length
            payload.read_uint16(0) != WirelessProtocol::cmdId_writeEeprom_v2 ||      //command ID
            payload.read_uint16(2) != m_eepromAddress ||                             //eeprom address
            payload.read_uint16(4) != m_eepromValue                                  //eeprom value
            )
        {
            //failed to match some of the bytes
            return false;
        }

        //if we made it here, the packet matches the response pattern

        //get the error code from the response
        m_errorCode = static_cast<WirelessPacket::ResponseErrorCode>(packet.payload().read_uint8(6));

        return true;
    }

    WirelessPacket::ResponseErrorCode WriteEeprom_v2::Response::errorCode() const
    {
        return m_errorCode;
    }
} // namespace mscl
