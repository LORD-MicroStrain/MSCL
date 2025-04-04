/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{
    //Class: NodeDiscoveryPacket_v3
    //    A class representing a MicroStrain "node discovery" packet (version 3).
    class NodeDiscoveryPacket_v3: public WirelessPacket
    {
    public:
        //=====================================================================================================
        //Constants: Node Discovery v3 Packet Information
        //    PAYLOAD_OFFSET_RADIO_CHANNEL       - 0    - The offset into the payload to get the radio channel.
        //    PAYLOAD_OFFSET_PAN_ID              - 1    - The offset into the payload to get the PAN id.
        //    PAYLOAD_OFFSET_MODEL_NUMBER        - 3    - The offset into the payload to get the Model Number.
        //    PAYLOAD_OFFSET_MODEL_OPTION        - 5    - The offset into the payload to get the Model Option.
        //    PAYLOAD_OFFSET_SERIAL_NUMBER       - 7    - The offset into the payload to get the Serial Number.
        //    PAYLOAD_OFFSET_FIRMWARE_VER        - 11   - The offset into the payload to get the Firmware Version (part 1).
        //    PAYLOAD_OFFSET_FIRMWARE_2          - 13   - The offset into the payload to get the Firmware Version (part 2).
        //    PAYLOAD_OFFSET_DEFAULT_MODE        - 15   - The offset into the payload to get the Default Mode.
        //=====================================================================================================
        static const int PAYLOAD_OFFSET_RADIO_CHANNEL   = 0;
        static const int PAYLOAD_OFFSET_PAN_ID          = 1;
        static const int PAYLOAD_OFFSET_MODEL_NUMBER    = 3;
        static const int PAYLOAD_OFFSET_MODEL_OPTION    = 5;
        static const int PAYLOAD_OFFSET_SERIAL_NUMBER   = 7;
        static const int PAYLOAD_OFFSET_FIRMWARE_VER    = 11;
        static const int PAYLOAD_OFFSET_FIRMWARE_VER2   = 13;
        static const int PAYLOAD_OFFSET_DEFAULT_MODE    = 15;

    private:
        NodeDiscoveryPacket_v3();    //default constructor disabled

    public:
        //Constant: stopFlags_nodeDiscovery
        //    The delivery stop flags that are expected in the node discovery command.
        static const DeliveryStopFlags stopFlags_nodeDiscovery;

        //Function: integrityCheck
        //    Verifies that the packet is a well formed Node Discovery (v2) packet.
        //
        //Parameters:
        //    packet - The fully formed Wireless Packet to check the integrity of.
        //
        //Returns:
        //    true if the packet is a well-formed Node Discovery (v2) Packet, false otherwise.
        static bool integrityCheck(const WirelessPacket& packet);
    };
} // namespace mscl
