/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Commands/WriteEeprom.h"

#include "mscl/MicroStrain/Wireless/Commands/WirelessProtocol.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{
    ByteStream WriteEeprom::buildCommand(NodeAddress nodeAddress, uint16 eepromAddress, uint16 valueToWrite)
    {
        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint8(0xAA);                                 //Start of Packet
        cmd.append_uint8(0x05);                                 //Delivery Stop Flag
        cmd.append_uint8(0x00);                                 //App Data Type
        cmd.append_uint16(static_cast<uint16>(nodeAddress));    //Node address    (2 bytes)
        cmd.append_uint8(0x06);                                 //Payload length
        cmd.append_uint16(WirelessProtocol::cmdId_writeEeprom); //Command ID    (2 bytes)
        cmd.append_uint16(eepromAddress);                       //EEPROM Address (2 bytes)
        cmd.append_uint16(valueToWrite);                        //EEPROM Address (2 bytes)

        //calculate the checsum of bytes 2-12
        uint16 checksum = cmd.calculateSimpleChecksum(1, 11);

        cmd.append_uint16(checksum);        //Checksum        (2 bytes)

        return cmd;
    }

    WriteEeprom::Response::Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector) :
        WirelessResponsePattern(collector, WirelessProtocol::cmdId_writeEeprom, nodeAddress),
        m_nodeAddress(nodeAddress)
    {}

    bool WriteEeprom::Response::matchSuccessResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if( packet.deliveryStopFlags().toInvertedByte() != 0x00 ||          //delivery stop flag
            packet.type() != 0x00 ||                                        //app data type
            packet.nodeAddress() != m_nodeAddress ||                        //node address
            payload.size() != 0x02 ||                                       //payload length
            payload.read_uint16(0) != WirelessProtocol::cmdId_writeEeprom   //cmd id
            )
        {
            //failed to match some of the bytes
            return false;
        }

        //if we made it here, the packet matches the response pattern
        return true;
    }
} // namespace mscl
