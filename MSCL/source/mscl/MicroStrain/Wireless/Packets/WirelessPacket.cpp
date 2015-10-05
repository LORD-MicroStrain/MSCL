/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
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

	void WirelessPacket::throwResponseError(ResponseErrorCode errorCode)
	{
		switch(errorCode)
		{
			case ResponseErrorCode::error_unknownEeprom:
				throw Error_NotSupported("An unsupported EEPROM location was attempted to be accessed.");

			case ResponseErrorCode::error_outOfBounds:
				throw Error_NotSupported("The value is out of bounds.");

			case ResponseErrorCode::error_readOnly:
				throw Error_NotSupported("Attempted to write to a read-only EEPROM location.");

			case ResponseErrorCode::error_hardwareError:	//for now, not turning hardware error into an exception
			case ResponseErrorCode::error_none:
			default:
				return;
		}
	}

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