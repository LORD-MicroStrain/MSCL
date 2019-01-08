/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "AsyncDigitalAnalogPacket.h"
#include "AsyncDigitalPacket.h"
#include "BeaconEchoPacket.h"
#include "BufferedLdcPacket.h"
#include "BufferedLdcPacket_v2.h"
#include "DiagnosticPacket.h"
#include "HclSmartBearing_RawPacket.h"
#include "HclSmartBearing_CalPacket.h"
#include "LdcPacket.h"
#include "LdcMathPacket.h"
#include "LdcMathPacket_aspp3.h"
#include "LdcPacket_v2.h"
#include "LdcPacket_v2_aspp3.h"
#include "NodeDiscoveryPacket.h"
#include "NodeDiscoveryPacket_v2.h"
#include "NodeDiscoveryPacket_v3.h"
#include "NodeDiscoveryPacket_v4.h"
#include "NodeDiscoveryPacket_v5.h"
#include "RawAngleStrainPacket.h"
#include "RfSweepPacket.h"
#include "RollerPacket.h"
#include "ShmPacket.h"
#include "ShmPacket_v2_aspp3.h"
#include "SyncSamplingPacket.h"
#include "SyncSamplingPacket_v2.h"
#include "SyncSamplingPacket_v2_aspp3.h"
#include "SyncSamplingMathPacket.h"
#include "SyncSamplingMathPacket_aspp3.h"
#include "WirelessPacketUtils.h"

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
            else
            {
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
        }
        catch(mscl::Error&)
        {
            assert(false);  //error parsing in integrityCheck function
            return false;
        }
    }
}