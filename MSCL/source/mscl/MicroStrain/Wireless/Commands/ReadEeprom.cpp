/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Commands/ReadEeprom.h"

#include "mscl/MicroStrain/Wireless/Commands/WirelessProtocol.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{
    ByteStream ReadEeprom::buildCommand(NodeAddress nodeAddress, uint16 eepromAddress)
    {
        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint8(0xAA);                                 //Start of Packet
        cmd.append_uint8(0x05);                                 //Delivery Stop Flag
        cmd.append_uint8(0x00);                                 //App Data Type
        cmd.append_uint16(static_cast<uint16>(nodeAddress));    //Node address    (2 bytes)
        cmd.append_uint8(0x04);                                 //Payload length
        cmd.append_uint16(WirelessProtocol::cmdId_readEeprom);  //Command ID    (2 bytes)
        cmd.append_uint16(eepromAddress);                       //EEPROM Address (2 bytes)

        //calculate the checksum of bytes 2-10
        uint16 checksum = cmd.calculateSimpleChecksum(1, 9);

        cmd.append_uint16(checksum);        //Checksum        (2 bytes)

        return cmd;
    }

    ReadEeprom::Response::Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector):
        WirelessResponsePattern(collector, WirelessProtocol::cmdId_readEeprom, nodeAddress),
        m_nodeAddress(nodeAddress),
        m_eepromValue(0)
    {
    }

    bool ReadEeprom::Response::matchSuccessResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if( packet.deliveryStopFlags().toInvertedByte() != 0x00 ||    //delivery stop flag
            packet.type() != 0x00 ||                                  //app data type
            packet.nodeAddress() != m_nodeAddress ||                  //node address
            payload.size() != 0x02                                    //payload length
            )
        {
            //failed to match some of the bytes
            return false;
        }

        //if we made it here, the packet matches the response pattern

        //get the eeprom value from the response
        m_eepromValue = payload.read_uint16(0);

        return true;
    }

    uint16 ReadEeprom::Response::eepromValue() const
    {
        //throw an exception if the command failed
        throwIfFailed("Read Node EEPROM");

        return m_eepromValue;
    }
}
