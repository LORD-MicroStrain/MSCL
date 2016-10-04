/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "AsyncDigitalAnalogPacket.h"
#include "AsyncDigitalPacket.h"
#include "BeaconEchoPacket.h"
#include "BufferedLdcPacket.h"
#include "BufferedLdcPacket_16ch.h"
#include "DiagnosticPacket.h"
#include "HclSmartBearing_RawPacket.h"
#include "HclSmartBearing_CalPacket.h"
#include "LdcPacket.h"
#include "LdcPacket_16ch.h"
#include "NodeDiscoveryPacket.h"
#include "NodeDiscoveryPacket_v2.h"
#include "NodeDiscoveryPacket_v3.h"
#include "NodeDiscoveryPacket_v4.h"
#include "RawAngleStrainPacket.h"
#include "RfSweepPacket.h"
#include "RollerPacket.h"
#include "ShmPacket.h"
#include "SyncSamplingPacket.h"
#include "SyncSamplingPacket_16ch.h"
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
        //check the packet type of the given WirelessPacket
        switch(packet.type())
        {
            //perform an integrity check based on the type of packet
            case WirelessPacket::packetType_LDC:                        return LdcPacket::integrityCheck(packet);
            case WirelessPacket::packetType_SyncSampling:               return SyncSamplingPacket::integrityCheck(packet);
            case WirelessPacket::packetType_BufferedLDC:                return BufferedLdcPacket::integrityCheck(packet);
            case WirelessPacket::packetType_LDC_16ch:                   return LdcPacket_16ch::integrityCheck(packet);
            case WirelessPacket::packetType_SyncSampling_16ch:          return SyncSamplingPacket_16ch::integrityCheck(packet);
            case WirelessPacket::packetType_BufferedLDC_16ch:           return BufferedLdcPacket_16ch::integrityCheck(packet);
            case WirelessPacket::packetType_AsyncDigital:               return AsyncDigitalPacket::integrityCheck(packet);
            case WirelessPacket::packetType_AsyncDigitalAnalog:         return AsyncDigitalAnalogPacket::integrityCheck(packet);
            case WirelessPacket::packetType_nodeDiscovery:              return NodeDiscoveryPacket::integrityCheck(packet);
            case WirelessPacket::packetType_nodeDiscovery_v2:           return NodeDiscoveryPacket_v2::integrityCheck(packet);
            case WirelessPacket::packetType_nodeDiscovery_v3:           return NodeDiscoveryPacket_v3::integrityCheck(packet);
            case WirelessPacket::packetType_nodeDiscovery_v4:           return NodeDiscoveryPacket_v4::integrityCheck(packet);
            case WirelessPacket::packetType_SHM:                        return ShmPacket::integrityCheck(packet);
            case WirelessPacket::packetType_HclSmartBearing_Calibrated: return HclSmartBearing_CalPacket::integrityCheck(packet);
            case WirelessPacket::packetType_HclSmartBearing_Raw:        return HclSmartBearing_RawPacket::integrityCheck(packet);
            case WirelessPacket::packetType_rawAngleStrain:             return RawAngleStrainPacket::integrityCheck(packet);
            case WirelessPacket::packetType_beaconEcho:                 return BeaconEchoPacket::integrityCheck(packet);
            case WirelessPacket::packetType_rfScanSweep:                return RfSweepPacket::integrityCheck(packet);
            case WirelessPacket::packetType_diagnostic:                 return DiagnosticPacket::integrityCheck(packet);
            case WirelessPacket::packetType_roller:                     return RollerPacket::integrityCheck(packet);

            case WirelessPacket::packetType_nodeCommand:
            case WirelessPacket::packetType_nodeSuccessReply:
            case WirelessPacket::packetType_nodeErrorReply:
            case WirelessPacket::packetType_nodeReceived:
            case WirelessPacket::packetType_baseCommand:
            case WirelessPacket::packetType_baseSuccessReply:
            case WirelessPacket::packetType_baseErrorReply:
                return true;

            //This packet is not supported by MSCL
            default:
                return false;
        }
    }
}