/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "BatchEepromRead.h"
#include "WirelessProtocol.h"
#include "mscl/MicroStrain/ByteStream.h"

namespace mscl
{
    ByteStream BatchEepromRead::buildCommand(NodeAddress nodeAddress, uint16 startAddress)
    {
        //build the command ByteStream
        ByteStream cmd;

        cmd.append_uint8(WirelessPacket::ASPP_V3_SOP);              //Start of Packet
        cmd.append_uint8(0x04);                                     //Delivery Stop Flag
        cmd.append_uint8(0x00);                                     //App Data Type
        cmd.append_uint32(nodeAddress);                             //Node address
        cmd.append_uint16(0x0004);                                  //Payload length
        cmd.append_uint16(WirelessProtocol::cmdId_batchEepromRead); //Command ID
        cmd.append_uint16(startAddress);                            //EEPROM Address
        cmd.append_uint16(0x7F7F);                                  //dummy RSSI bytes
        cmd.append_uint32(cmd.calculateCrcChecksum());              //Checksum

        return cmd;
    }

    BatchEepromRead::Response::Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector):
        WirelessResponsePattern(collector, WirelessProtocol::cmdId_batchEepromRead, nodeAddress),
        m_nodeAddress(nodeAddress)
    {
    }

    bool BatchEepromRead::Response::matchSuccessResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(packet.nodeAddress() != m_nodeAddress ||                             //node address
           !packet.deliveryStopFlags().pc ||                                    //delivery stop flags
           packet.type() != WirelessPacket::packetType_nodeSuccessReply ||      //app data type
           payload.size() < 2 ||                                                //payload length
           payload.read_uint16(0) != WirelessProtocol::cmdId_batchEepromRead    //command ID
           )
        {
            //failed to match some of the bytes
            return false;
        }

        //if we made it here, the packet matches the response pattern

        //parse the eeprom address/value pairs into a map
        DataBuffer data(payload);
        data.skipBytes(2);  //skip command ID bytes

        while(data.moreToRead())
        {
            uint16 location = data.read_uint16();
            uint16 value = data.read_uint16();

            m_eepromMap.emplace(std::make_pair(location, value));
        }

        return true;
    }

    const std::map<uint16, uint16>& BatchEepromRead::Response::eepromMap() const
    {
        //get a lock on the parsing mutex
        mutex_lock_guard lock(m_parsingMutex);

        return m_eepromMap;
    }
}
