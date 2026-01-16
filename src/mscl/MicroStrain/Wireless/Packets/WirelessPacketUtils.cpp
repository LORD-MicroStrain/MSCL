/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Packets/WirelessPacketUtils.h"

#include "mscl/MicroStrain/Wireless/Packets/AsyncDigitalAnalogPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/AsyncDigitalPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/BeaconEchoPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/BufferedLdcPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/BufferedLdcPacket_v2.h"
#include "mscl/MicroStrain/Wireless/Packets/DiagnosticPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/HclSmartBearing_CalPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/HclSmartBearing_RawPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/LdcMathPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/LdcMathPacket_aspp3.h"
#include "mscl/MicroStrain/Wireless/Packets/LdcPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/LdcPacket_v2.h"
#include "mscl/MicroStrain/Wireless/Packets/LdcPacket_v2_aspp3.h"
#include "mscl/MicroStrain/Wireless/Packets/NodeDiscoveryPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/NodeDiscoveryPacket_v2.h"
#include "mscl/MicroStrain/Wireless/Packets/NodeDiscoveryPacket_v3.h"
#include "mscl/MicroStrain/Wireless/Packets/NodeDiscoveryPacket_v4.h"
#include "mscl/MicroStrain/Wireless/Packets/NodeDiscoveryPacket_v5.h"
#include "mscl/MicroStrain/Wireless/Packets/RawAngleStrainPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/RfSweepPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/RollerPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/ShmPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/ShmPacket_v2_aspp3.h"
#include "mscl/MicroStrain/Wireless/Packets/SyncSamplingMathPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/SyncSamplingMathPacket_aspp3.h"
#include "mscl/MicroStrain/Wireless/Packets/SyncSamplingPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/SyncSamplingPacket_v2.h"
#include "mscl/MicroStrain/Wireless/Packets/SyncSamplingPacket_v2_aspp3.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{
    void WirelessPacketUtils::correctPacketType(WirelessPacket& packet)
    {
        WirelessPacket::PacketType packetType = packet.type();
        const WirelessPacket::Payload& payload = packet.payload();

        //The command packet type is erroneously used in many packets
        if(packetType == WirelessPacket::packetType_nodeCommand)
        {
            //CHECK IF NODE DISCOVERY PACKET
            {
                //if the delivery stop flags match a node discovery packet
                if(packet.deliveryStopFlags() == NodeDiscoveryPacket::stopFlags_nodeDiscovery)
                {
                    //if the payload length is 3
                    if(payload.size() == 3)
                    {
                        //change the app type to Node Discovery
                        packet.type(WirelessPacket::packetType_nodeDiscovery);
                    }
                }
            }
        }
        //Sync Sampling packets originally used the wrong packet ID which was the same as the original TC-Link.
        //The first byte of the Sync Sampling payload is 0x02.
        //The first byte of the TC-Link LDC payload is 0x03.
        else if(packetType == WirelessPacket::packetType_TCLinkLDC)
        {
            if(payload.size() > 0)
            {
                //if the first byte in the payload is 0x02
                if(payload[0] == 0x02)
                {
                    //change the app type to Sync Sampling
                    packet.type(WirelessPacket::packetType_SyncSampling);
                }
            }
        }
        //The Histogram packet comes through as an LDC packet
        else if(packetType == WirelessPacket::packetType_LDC)
        {
            if(payload.size() > 0)
            {
                if(payload[0] == WirelessPacket::packetType_SHM)
                {
                    //change the app type to Histogram
                    packet.type(WirelessPacket::packetType_SHM);
                }
            }
        }
    }

    bool WirelessPacketUtils::packetIntegrityCheck(const WirelessPacket& packet)
    {
        try
        {

            //packets that we don't have integrity checks for
            switch(packet.type())
            {
                case WirelessPacket::packetType_nodeCommand:
                case WirelessPacket::packetType_nodeSuccessReply:
                case WirelessPacket::packetType_nodeErrorReply:
                case WirelessPacket::packetType_nodeReceived:
                case WirelessPacket::packetType_baseCommand:
                case WirelessPacket::packetType_baseReceived:
                case WirelessPacket::packetType_baseSuccessReply:
                case WirelessPacket::packetType_baseErrorReply:
                    return true;

                default:
                    break;
            }

            if(packet.asppVersion() == WirelessPacket::aspp_v3)
            {
                //ASPP v3 Packets

                //check the packet type of the given WirelessPacket
                switch(packet.type())
                {
                    //perform an integrity check based on the type of packet
                    case WirelessPacket::packetType_LDC_16ch:                   return LdcPacket_v2_aspp3::integrityCheck(packet);
                    case WirelessPacket::packetType_LDC_math:                   return LdcMathPacket_aspp3::integrityCheck(packet);
                    case WirelessPacket::packetType_SyncSampling_16ch:          return SyncSamplingPacket_v2_aspp3::integrityCheck(packet);
                    case WirelessPacket::packetType_SyncSampling_math:          return SyncSamplingMathPacket_aspp3::integrityCheck(packet);
                    case WirelessPacket::packetType_SHM:                        return ShmPacket_v2_aspp3::integrityCheck(packet);
                    case WirelessPacket::packetType_rawAngleStrain:             return RawAngleStrainPacket::integrityCheck(packet);    //same payload, no new parser
                    case WirelessPacket::packetType_diagnostic:                 return DiagnosticPacket::integrityCheck(packet);        //same payload, no new parser
                    case WirelessPacket::packetType_rfScanSweep:                return RfSweepPacket::integrityCheck(packet);           //same payload, no new parser
                    case WirelessPacket::packetType_beaconEcho:                 return BeaconEchoPacket::integrityCheck(packet);        //same payload, no new parser
                    case WirelessPacket::packetType_nodeDiscovery_v5:           return NodeDiscoveryPacket_v5::integrityCheck(packet);  //same payload, no new parser

                    //This packet is not supported by MSCL
                    default:
                        return false;
                }
            }

            //ASPP v1 and v2 Packets

            //check the packet type of the given WirelessPacket
            switch(packet.type())
            {
                //perform an integrity check based on the type of packet
                case WirelessPacket::packetType_LDC:                        return LdcPacket::integrityCheck(packet);
                case WirelessPacket::packetType_SyncSampling:               return SyncSamplingPacket::integrityCheck(packet);
                case WirelessPacket::packetType_BufferedLDC:                return BufferedLdcPacket::integrityCheck(packet);
                case WirelessPacket::packetType_LDC_16ch:                   return LdcPacket_v2::integrityCheck(packet);
                case WirelessPacket::packetType_LDC_math:                   return LdcMathPacket::integrityCheck(packet);
                case WirelessPacket::packetType_SyncSampling_16ch:          return SyncSamplingPacket_v2::integrityCheck(packet);
                case WirelessPacket::packetType_SyncSampling_math:          return SyncSamplingMathPacket::integrityCheck(packet);
                case WirelessPacket::packetType_BufferedLDC_16ch:           return BufferedLdcPacket_v2::integrityCheck(packet);
                case WirelessPacket::packetType_AsyncDigital:               return AsyncDigitalPacket::integrityCheck(packet);
                case WirelessPacket::packetType_AsyncDigitalAnalog:         return AsyncDigitalAnalogPacket::integrityCheck(packet);
                case WirelessPacket::packetType_nodeDiscovery:              return NodeDiscoveryPacket::integrityCheck(packet);
                case WirelessPacket::packetType_nodeDiscovery_v2:           return NodeDiscoveryPacket_v2::integrityCheck(packet);
                case WirelessPacket::packetType_nodeDiscovery_v3:           return NodeDiscoveryPacket_v3::integrityCheck(packet);
                case WirelessPacket::packetType_nodeDiscovery_v4:           return NodeDiscoveryPacket_v4::integrityCheck(packet);
                case WirelessPacket::packetType_nodeDiscovery_v5:           return NodeDiscoveryPacket_v5::integrityCheck(packet);
                case WirelessPacket::packetType_SHM:                        return ShmPacket::integrityCheck(packet);
                case WirelessPacket::packetType_HclSmartBearing_Calibrated: return HclSmartBearing_CalPacket::integrityCheck(packet);
                case WirelessPacket::packetType_HclSmartBearing_Raw:        return HclSmartBearing_RawPacket::integrityCheck(packet);
                case WirelessPacket::packetType_rawAngleStrain:             return RawAngleStrainPacket::integrityCheck(packet);
                case WirelessPacket::packetType_beaconEcho:                 return BeaconEchoPacket::integrityCheck(packet);
                case WirelessPacket::packetType_rfScanSweep:                return RfSweepPacket::integrityCheck(packet);
                case WirelessPacket::packetType_diagnostic:                 return DiagnosticPacket::integrityCheck(packet);
                case WirelessPacket::packetType_roller:                     return RollerPacket::integrityCheck(packet);

                //This packet is not supported by MSCL
                default:
                    return false;
            }
        }
        catch(Error&)
        {
            assert(false);  //error parsing in integrityCheck function
            return false;
        }
    }
} // namespace mscl
