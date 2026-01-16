/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Packets/NodeDiscoveryPacket_v3.h"

namespace mscl
{
    const DeliveryStopFlags NodeDiscoveryPacket_v3::stopFlags_nodeDiscovery(true, false, false, false);

    bool NodeDiscoveryPacket_v3::integrityCheck(const WirelessPacket& packet)
    {
        const uint8 RADIO_CHANNEL_MIN = 11;
        const uint8 RADIO_CHANNEL_MAX = 26;

        //verify the payload size is correct
        if(packet.payload().size() != 17)
        {
            return false;
        }

        //read what should be the radio channel byte
        uint8 radioChannel = packet.payload().read_uint8(PAYLOAD_OFFSET_RADIO_CHANNEL);

        //verify that the radio channel byte is valid
        if(radioChannel < RADIO_CHANNEL_MIN || radioChannel > RADIO_CHANNEL_MAX)
        {
            return false;
        }

        //verify the delivery stop flags are what we expected
        if(packet.deliveryStopFlags() != stopFlags_nodeDiscovery)
        {
            //packet not intended for the PC
            return false;
        }

        //verify the packet type is correct
        if(packet.type() != packetType_nodeDiscovery_v3)
        {
            //packet is not a node discovery packet
            return false;
        }

        //packet looks valid
        return true;
    }
} // namespace mscl
