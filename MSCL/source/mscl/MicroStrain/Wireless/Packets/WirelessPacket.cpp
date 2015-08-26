/*****************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the included
LICENSE.txt file for a copy of the full GNU General Public License.
*****************************************************************************/
#include "stdafx.h"
#include "WirelessPacket.h"

namespace mscl
{
	//=================================================================================================
	//WirelessPacket
	//=================================================================================================

	//default constructor for WirelessPacket
	WirelessPacket::WirelessPacket() :
		m_type(packetType_unknown),
		m_nodeAddress(0),
		m_nodeRSSI(WirelessTypes::UNKNOWN_RSSI),
		m_baseRSSI(WirelessTypes::UNKNOWN_RSSI),
		m_frequency(WirelessTypes::freq_unknown)
	{}

	bool WirelessPacket::isDataPacket() const
	{
		switch(m_type)
		{
		//the following packet types are considered data packets
		case packetType_LDC:
		case packetType_TCLinkLDC:
		case packetType_SyncSampling:
		case packetType_BufferedLDC:
		case packetType_LDC_16ch:
		case packetType_SyncSampling_16ch:
		case packetType_BufferedLDC_16ch:
		case packetType_AsyncDigital:
		case packetType_AsyncDigitalAnalog:
		case packetType_SHM:
		case packetType_HclSmartBearing_Calibrated:
		case packetType_HclSmartBearing_Raw:
			return true;

		//any other packet type is not a data packet
		default:
			return false;
		}
	}

	bool WirelessPacket::isDiscoveryPacket() const
	{
		switch(m_type)
		{
			case packetType_nodeDiscovery:
			case packetType_nodeDiscovery_v2:
			case packetType_nodeDiscovery_v3:
				return true;

			default:
				return false;
		}
	}

	//delivery Stop Flags getter
	DeliveryStopFlags WirelessPacket::deliveryStopFlags() const
	{
		return m_deliveryStopFlags;
	}

	//delivery Stop Flags setter
	void WirelessPacket::deliveryStopFlags(DeliveryStopFlags flags)
	{
		m_deliveryStopFlags.appBoard = flags.appBoard;
		m_deliveryStopFlags.baseStation = flags.baseStation;
		m_deliveryStopFlags.linkBoard = flags.linkBoard;
		m_deliveryStopFlags.pc = flags.pc;
	}
	
	//type getter
	WirelessPacket::PacketType WirelessPacket::type() const
	{
		return m_type;
	}

	//type setter
	void WirelessPacket::type(PacketType packetType)
	{
		m_type = packetType;
	}

	//node address getter
	NodeAddress WirelessPacket::nodeAddress() const
	{
		return m_nodeAddress;
	}

	//node address setter
	void WirelessPacket::nodeAddress(NodeAddress address)
	{
		m_nodeAddress = address;
	}

	//node rssi getter
	int16 WirelessPacket::nodeRSSI() const
	{
		return m_nodeRSSI;
	}

	//node rssi setter
	void WirelessPacket::nodeRSSI(int16 rssi)
	{
		m_nodeRSSI = rssi;
	}

	//base rssi getter
	int16 WirelessPacket::baseRSSI() const
	{
		return m_baseRSSI;
	}

	//base rssi setter
	void WirelessPacket::baseRSSI(int16 rssi)
	{
		m_baseRSSI = rssi;
	}

	WirelessTypes::Frequency WirelessPacket::frequency() const
	{
		return m_frequency;
	}

	void WirelessPacket::frequency(WirelessTypes::Frequency freq)
	{
		m_frequency = freq;
	}

	//payload getter
	const WirelessPacket::Payload& WirelessPacket::payload() const
	{
		return m_payload;
	}

	//payload setter
	void WirelessPacket::payload(const Bytes& bytes)
	{
		m_payload.set(bytes);
	}
}