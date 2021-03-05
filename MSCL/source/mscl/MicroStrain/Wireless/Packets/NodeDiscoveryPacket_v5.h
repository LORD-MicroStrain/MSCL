/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "WirelessPacket.h"

namespace mscl
{
    //Class: NodeDiscoveryPacket_v5
    //    A class representing a MicroStrain "node discovery" packet (version 5).
    class NodeDiscoveryPacket_v5: public WirelessPacket
    {
    public:
        //=====================================================================================================
        //Constants: Node Discovery v3 Packet Information
        //    PAYLOAD_OFFSET_RADIO_MODE          - 1    - The offset into the payload to get the radio mode.
        //    PAYLOAD_OFFSET_RADIO_CHANNEL       - 2    - The offset into the payload to get the radio channel.
        //    PAYLOAD_OFFSET_PAN_ID              - 3    - The offset into the payload to get the PAN id.
        //    PAYLOAD_OFFSET_MODEL_NUMBER        - 5    - The offset into the payload to get the Model Number.
        //    PAYLOAD_OFFSET_MODEL_OPTION        - 7    - The offset into the payload to get the Model Option.
        //    PAYLOAD_OFFSET_SERIAL_NUMBER       - 9    - The offset into the payload to get the Serial Number.
        //    PAYLOAD_OFFSET_FIRMWARE_VER        - 13   - The offset into the payload to get the Firmware Version (part 1).
        //    PAYLOAD_OFFSET_FIRMWARE_2          - 15   - The offset into the payload to get the Firmware Version (part 2).
        //    PAYLOAD_OFFSET_ASPP_LXRS           - 17   - The offset into the payload to get the ASPP version used by LXRS Configurations.
        //    PAYLOAD_OFFSET_ASPP_LXRS_PLUS      - 19   - The offset into the payload to get the ASPP version used by LXRS+ Configurations.
        //    PAYLOAD_OFFSET_DEFAULT_MODE        - 21   - The offset into the payload to get the Default Mode.
        //    PAYLOAD_OFFSET_BUILT_IN_TEST       - 23   - The offset into the payload to get the Built in Test.
        //=====================================================================================================
        static const int PAYLOAD_OFFSET_RADIO_MODE      = 1;
        static const int PAYLOAD_OFFSET_RADIO_CHANNEL   = 2;
        static const int PAYLOAD_OFFSET_PAN_ID          = 3;
        static const int PAYLOAD_OFFSET_MODEL_NUMBER    = 5;
        static const int PAYLOAD_OFFSET_MODEL_OPTION    = 7;
        static const int PAYLOAD_OFFSET_SERIAL_NUMBER   = 9;
        static const int PAYLOAD_OFFSET_FIRMWARE_VER    = 13;
        static const int PAYLOAD_OFFSET_FIRMWARE_VER2   = 15;
        static const int PAYLOAD_OFFSET_ASPP_LXRS       = 17;
        static const int PAYLOAD_OFFSET_ASPP_LXRS_PLUS  = 19;
        static const int PAYLOAD_OFFSET_DEFAULT_MODE    = 21;
        static const int PAYLOAD_OFFSET_BUILT_IN_TEST   = 23;

    private:
        NodeDiscoveryPacket_v5();    //default constructor disabled

    public:
        //Constant: stopFlags_nodeDiscovery
        //    The delivery stop flags that are expected in the node discovery command.
        static const DeliveryStopFlags stopFlags_nodeDiscovery;

        //Function: integrityCheck
        //    Verifies that the packet is a well formed Node Discovery (v4) packet.
        //
        //Parameters:
        //    packet - The fully formed Wireless Packet to check the integrity of.
        //
        //Returns:
        //    true is the packet is a well-formed Node Discovery (v4) Packet, false otherwise.
        static bool integrityCheck(const WirelessPacket& packet);
    };
}