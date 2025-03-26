/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Commands/WirelessResponsePattern.h"

#include "mscl/MicroStrain/Wireless/Commands/WirelessProtocol.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{
    WirelessResponsePattern::WirelessResponsePattern(uint16 commandId, NodeAddress nodeAddress) :
        ResponsePattern(),
        m_commandId(commandId),
        m_nodeAddress(nodeAddress),
        m_baseReceived(false),
        m_baseReceivedWaitTime(0)
    {}

    WirelessResponsePattern::WirelessResponsePattern(std::weak_ptr<ResponseCollector> collector, uint16 commandId, NodeAddress nodeAddress) :
        ResponsePattern(collector),
        m_commandId(commandId),
        m_nodeAddress(nodeAddress),
        m_baseReceived(false),
        m_baseReceivedWaitTime(0)
    {}

    WirelessResponsePattern::~WirelessResponsePattern()
    {}

    bool WirelessResponsePattern::matchBaseReceivedResponse(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //check the main bytes of the packet
        if(!packet.deliveryStopFlags().pc ||                                    //delivery stop flag
           packet.type() != WirelessPacket::packetType_baseReceived ||          //app data type
           packet.nodeAddress() != WirelessProtocol::BASE_STATION_ADDRESS       //node address
           )
        {
            //failed to match some of the bytes
            return false;
        }

        if(packet.asppVersion() == WirelessPacket::aspp_v3)
        {
            if(payload.size() != 11 ||
               payload.read_uint16(0) != m_commandId ||
               payload.read_uint32(7) != m_nodeAddress)
            {
                return false;
            }
        }
        else
        {
            if(payload.size() != 9 ||
               payload.read_uint16(0) != m_commandId ||
               payload.read_uint16(7) != m_nodeAddress)
            {
                return false;
            }
        }

        m_baseReceived = true;

        //store the new time we should wait for the Node response (in milliseconds)
        m_baseReceivedWaitTime = static_cast<uint64>(payload.read_float(3) * 1000.0);

        //if we made it here, the packet matches the response pattern
        return true;
    }

    bool WirelessResponsePattern::baseReceived() const
    {
        return m_baseReceived;
    }

    uint64 WirelessResponsePattern::baseReceivedWaitTime() const
    {
        return m_baseReceivedWaitTime;
    }
} // namespace mscl
