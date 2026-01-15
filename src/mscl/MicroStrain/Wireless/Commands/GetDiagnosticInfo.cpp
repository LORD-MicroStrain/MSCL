/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Commands/GetDiagnosticInfo.h"

#include "mscl/MicroStrain/Wireless/Commands/WirelessProtocol.h"
#include "mscl/MicroStrain/Wireless/Packets/DiagnosticPacket.h"

namespace mscl
{
    ByteStream GetDiagnosticInfo::buildCommand(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress)
    {
        //build the command ByteStream
        ByteStream cmd;

        if(asppVer == WirelessPacket::aspp_v3)
        {
            cmd.append_uint8(WirelessPacket::ASPP_V3_SOP);              //Start of Packet
            cmd.append_uint8(0x04);                                     //Delivery Stop Flag
            cmd.append_uint8(0x00);                                     //App Data Type
            cmd.append_uint32(nodeAddress);                             //Node address
            cmd.append_uint16(0x0002);                                  //Payload length
            cmd.append_uint16(WirelessProtocol::cmdId_getDiagInfo_v1);  //Command ID
            cmd.append_uint16(0x7F7F);                                  //dummy RSSI bytes
            cmd.append_uint32(cmd.calculateCrcChecksum());              //Checksum
        }
        else
        {
            cmd.append_uint8(WirelessPacket::ASPP_V1_SOP);              //Start of Packet
            cmd.append_uint8(0x05);                                     //Delivery Stop Flag
            cmd.append_uint8(0x00);                                     //App Data Type
            cmd.append_uint16(static_cast<uint16>(nodeAddress));        //Node address
            cmd.append_uint8(0x02);                                     //Payload length
            cmd.append_uint16(WirelessProtocol::cmdId_getDiagInfo_v1);  //Command ID
            cmd.append_uint16(cmd.calculateSimpleChecksum(1, 7));       //Checksum
        }

        return cmd;
    }

    GetDiagnosticInfo::Response::Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector) :
        WirelessResponsePattern(collector, WirelessProtocol::cmdId_getDiagInfo_v1, nodeAddress),
        m_nodeAddress(nodeAddress)
    {}

    bool GetDiagnosticInfo::Response::matchSuccessResponse(const WirelessPacket& packet)
    {
        //check the main bytes of the packet
        if( !packet.deliveryStopFlags().pc ||                               //delivery stop flag
            packet.type() != WirelessPacket::packetType_nodeSuccessReply || //app data type
            packet.nodeAddress() != m_nodeAddress                           //node address
            )
        {
            //failed to match some of the bytes
            return false;
        }

        DataBuffer bytes(packet.payload());

        if(bytes.read_uint16() != WirelessProtocol::cmdId_getDiagInfo_v1)
        {
            return false;
        }

        //verify the payload is correct
        while(bytes.moreToRead())
        {
            uint8 infoLen = bytes.read_uint8();

            if(infoLen == 0)
            {
                //no info length should be 0 (invalid payload)
                return false;
            }

            //verify we can read all the bytes in the length described
            if(bytes.bytesRemaining() < infoLen)
            {
                //can't read all the bytes (invalid payload)
                return false;
            }

            //skip passed the bytes being asked to read
            bytes.skipBytes(infoLen);
        }

        //if we made it here, the packet matches the response pattern

        //get the payload again so we can actually parse the bytes out
        DataBuffer payload(packet.payload());
        size_t numInfoItemBytes = payload.size() - 2;
        payload.skipBytes(2);   //skip the command id bytes
        size_t infoByteCounter = 0;

        //add all the data to the result vector
        uint8 infoLen = 0;
        uint8 infoId = 0;
        while(infoByteCounter < numInfoItemBytes)
        {
            infoLen = payload.read_uint8();

            infoId = payload.read_uint8();

            DiagnosticPacket::addDataPoint(m_result, payload, infoLen - 1, infoId, packet.nodeAddress());

            infoByteCounter += infoLen + 1;
        }

        return true;
    }

    const ChannelData& GetDiagnosticInfo::Response::result() const
    {
        //get a lock on the parsing mutex
        mutex_lock_guard lock(m_parsingMutex);

        return m_result;
    }
} // namespace mscl
