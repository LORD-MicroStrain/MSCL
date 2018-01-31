/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "StartNonSyncSampling_v2.h"
#include "WirelessProtocol.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{

    ByteStream StartNonSyncSampling_v2::buildCommand(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress)
    {
        //build the command ByteStream
        ByteStream cmd;

        if(asppVer == WirelessPacket::aspp_v3)
        {
            cmd.append_uint8(WirelessPacket::ASPP_V3_SOP);                  //Start of Packet
            cmd.append_uint8(0x04);                                         //Delivery Stop Flag
            cmd.append_uint8(0x00);                                         //App Data Type
            cmd.append_uint32(nodeAddress);                                 //Node Address
            cmd.append_uint16(0x000A);                                      //Payload Length
            cmd.append_uint16(WirelessProtocol::cmdId_startLdc_v2);         //Command ID
            cmd.append_uint64(Utils::getCurrentSystemTime());
            cmd.append_uint16(0x7F7F);                                      //rssi dummy bytes
            cmd.append_uint32(cmd.calculateCrcChecksum());                  //Checksum
        }
        else
        {
            cmd.append_uint8(WirelessPacket::ASPP_V1_SOP);                  //Start of Packet
            cmd.append_uint8(0x05);                                         //Delivery Stop Flag
            cmd.append_uint8(0x00);                                         //App Data Type
            cmd.append_uint16(static_cast<uint16>(nodeAddress));            //Node Address
            cmd.append_uint8(10);                                           //Payload Length
            cmd.append_uint16(WirelessProtocol::cmdId_startLdc_v2);         //Command ID
            cmd.append_uint64(Utils::getCurrentSystemTime());
            cmd.append_uint16(cmd.calculateSimpleChecksum(1, 15));          //Checksum        (2 bytes)
        }

        return cmd;
    }

    StartNonSyncSampling_v2::Response::Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector):
        WirelessResponsePattern(collector, WirelessProtocol::cmdId_startLdc_v2, nodeAddress),
        m_nodeAddress(nodeAddress)
    {
    }

    bool StartNonSyncSampling_v2::Response::matchSuccessResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if( !packet.deliveryStopFlags().pc ||                                           //delivery stop flag
            packet.type() != WirelessPacket::packetType_nodeSuccessReply ||             //app data type
            packet.nodeAddress() != m_nodeAddress ||                                    //node address
            payload.size() != 0x02 ||                                                   //payload length
            payload.read_uint16(0) != WirelessProtocol::cmdId_startLdc_v2               //Command ID
            )            
        {
            //failed to match some of the bytes
            return false;
        }

        //if we made it here, the packet matches the response pattern
        return true;
    }
}