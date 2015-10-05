/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/Wireless/DeliveryStopFlags.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"

namespace mscl
{
	//Class: WirelessPacket
	//	Represents a MicroStrain wireless packet
	class WirelessPacket
	{
	public:
		//Typedef: Payload
		//	typedef for the bytes that make up a payload in a packet
		typedef ByteStream Payload;

		//=====================================================================================================
		//Constants: Wireless Packet Bytes
		//	ASPP_START_OF_PACKET_BYTE	- 0xAA		- The "Start of Packet" byte for the ASPP packets
		//	ASPP_POS_START_OF_PACKET	- 0;		- The byte position for the Start of Packet byte
		//	ASPP_POS_DELIVERY_FLAGS		- 1;		- The byte position for the Delivery Stop Flags
		//	ASPP_POS_APP_DATA_TYPE		- 2;		- The byte position for the App Data Type
		//	ASPP_POS_NODE_ADDRESS		- 3;		- The byte position for the Node Address
		//	ASPP_POS_PAYLOAD_LEN		- 5;		- The byte position for the payload length
		//	ASPP_POS_PAYLOAD_START		- 6;		- The byte position for the start of the payload bytes
		//=====================================================================================================
		static const uint8 ASPP_START_OF_PACKET_BYTE	= 0xAA;
		static const short ASPP_POS_START_OF_PACKET		= 0;
		static const short ASPP_POS_DELIVERY_FLAGS		= 1;
		static const short ASPP_POS_APP_DATA_TYPE		= 2;
		static const short ASPP_POS_NODE_ADDRESS		= 3;
		static const short ASPP_POS_PAYLOAD_LEN			= 5;
		static const short ASPP_POS_PAYLOAD_START		= 6;

		//=====================================================================================================
		//Constants: Wireless Packet Information
		//  ASPP_MIN_RESPONSE_PACKET_SIZE	- 10	- The minimum number of bytes to make a valid ASPP Response packet (Payload len + LQI + RSSI + Checksum)
		//	ASPP_NUM_BYTES_BEFORE_PAYLOAD	- 6		- The number of bytes in the ASPP packets before the payload
		//	ASPP_NUM_BYTES_AFTER_PAYLOAD	- 4		- The number of bytes in the ASPP packets after the payload
		//	ASPP_NUM_COMMAND_BYTES			- 2		- The number of command bytes in the ASPP packets
		//	START_CHECKSUM_POS				- 1		- The starting position for calculating the checksum in ASPP packets
		//=====================================================================================================
		static const uint16 ASPP_MIN_RESPONSE_PACKET_SIZE	= 10;
		static const uint16 ASPP_NUM_BYTES_BEFORE_PAYLOAD	= 6;
		static const uint16 ASPP_NUM_BYTES_AFTER_PAYLOAD	= 4;
		static const uint16 ASPP_NUM_COMMAND_BYTES			= 2;
		static const uint16 START_CHECKSUM_POS				= 1;

		//=====================================================================================================
		//Enums: PacketType
		//	packetType_unknown						- -1	- Unknown Packet Type
		//	packetType_nodeCommand					- 0x00	- Node Command Packet
		//	packetType_nodeErrorReply				- 0x02	- Node Command Error Reply Packet
		//	packetType_LDC							- 0x04	- Standard Low Duty Cycle Packet
		//	packetType_nodeDiscovery				- 0x07	- Node Discovery Packet (version 1)
		//	packetType_TCLinkLDC					- 0x09	- TC-Link Low Duty Cycle packet
		//	packetType_SyncSampling					- 0x0A	- Synchronized Sampling Packet
		//	packetType_BufferedLDC					- 0x0D	- Buffered LDC Packet
		//	packetType_AsyncDigital					- 0x0E	- Asynchronous Digital (Event) Packet
		//	packetType_AsyncDigitalAnalog			- 0x0F	- Asynchronous Digital and Analog (Event) Packet
		//	packetType_LDC_16ch						- 0x14	- LDC Packet with 16 channel support
		//	packetType_nodeDiscovery_v2				- 0x17	- Node Discovery Packet (version 2)
		//	packetType_nodeDiscovery_v3				- 0x18	- Node Discovery Packet (version 3)
		//	packetType_SyncSampling_16ch			- 0x1A	- Synchronized Sampling Packet with 16 channel support
		//	packetType_BufferedLDC_16ch				- 0x1D	- Buffered LDC Packet with 16 channel support
		//	packetType_NodeReceived					- 0x20	- Node Received the command
		//	packetType_nodeSuccessReply				- 0x22	- Node Command Success Reply Packet
		//	packetType_baseCommand					- 0x30	- Base Station Command Packet
		//	packetType_baseSuccessReply				- 0x31	- Base Station Command Reply Packet
		//	packetType_baseErrorReply				- 0x32	- Base Station Command Error Reply Packet
		//	packetType_SHM							- 0xA0	- Structural Health Monitoring Packet
		//	packetType_HclSmartBearing_Calibrated	- 0xA1	- HclSmartBearing Calibrated data Packet
		//	packetType_HclSmartBearing_Raw			- 0xA2	- HclSmartBearing Raw data Packet
		//=====================================================================================================
		enum PacketType
		{
			packetType_unknown						= -1,
			
			packetType_nodeCommand					= 0x00,
			packetType_nodeErrorReply				= 0x02,
			packetType_LDC							= 0x04,
			packetType_nodeDiscovery				= 0x07,
			packetType_TCLinkLDC					= 0x09,
			packetType_SyncSampling					= 0x0A,
			packetType_BufferedLDC					= 0x0D,
			packetType_AsyncDigital					= 0x0E,
			packetType_AsyncDigitalAnalog			= 0x0F,
			packetType_LDC_16ch						= 0x14,
			packetType_nodeDiscovery_v2				= 0x17,
			packetType_nodeDiscovery_v3				= 0x18,
			packetType_SyncSampling_16ch			= 0x1A,
			packetType_BufferedLDC_16ch				= 0x1D,
			packetType_nodeReceived					= 0x20,
			packetType_nodeSuccessReply				= 0x22,
			packetType_baseCommand					= 0x30,
			packetType_baseSuccessReply				= 0x31,
			packetType_baseErrorReply				= 0x32,
			packetType_SHM							= 0xA0,
			packetType_HclSmartBearing_Calibrated	= 0xA1,
			packetType_HclSmartBearing_Raw			= 0xA2
		};

		//===================================================
		//Enums: ResponseErrorCode
		//	Possible error codes from response packets.
		//
		//	error_none			- 0x00 - No Error.
		//	error_unknownEeprom - 0x01 - An Unknown/Unsupported Eeprom was attempted to be accessed.
		//	error_outOfBounds	- 0x02 - An out of bounds value was attempted to be used.
		//	error_readOnly		- 0x03 - Attempted to write to a read only Eeprom location.
		//	error_hardwareError - 0x04 - A hardware error has occurred.
		//===================================================
		enum ResponseErrorCode
		{
			error_none			= 0x00,
			error_unknownEeprom = 0x01,
			error_outOfBounds	= 0x02,
			error_readOnly		= 0x03,
			error_hardwareError = 0x04
		};

	public:
		//Constructor: WirelessPacket
		//	The default constructor for a wireless packet
		WirelessPacket();

		virtual ~WirelessPacket() {};

		//Function: throwResponseError
		//	Throws an exception based on a <ResponseErrorCode>.
		//	Not all error codes will cause an exception.
		//
		//Parameters:
		//	errorCode - The <ResponseErrorCode> to use for potentially throwing an exception.
		//
		//Exceptions:
		//	- <Error_NotSupported> - invalid eeprom location, value out of bounds, or read only eeprom location.
		static void throwResponseError(ResponseErrorCode errorCode);

	protected:
		//Variable: m_deliveryStopFlags
		//	The delivery stop flags of the packet
		DeliveryStopFlags m_deliveryStopFlags;

		//Variable: m_type
		//	The packet type of the packet
		PacketType	m_type;

		//Variable: m_nodeAddress
		//	The node address in the packet
		NodeAddress m_nodeAddress;

		//Variable: m_nodeRSSI
		//	The node received signal strength indicator (strength of which the node received the command from the base station).
		//	This value will be set to -200 if the packet contains a legacy junk lqi byte that should be thrown out.
		int16 m_nodeRSSI;

		//Variable: m_baseRSSI
		//	The base received signal strength indicator (strength of which the base station received the response from the node).
		int16 m_baseRSSI;

		//Variable: m_frequency
		//	The <WirelessTypes::Frequency> that this packet was collected on.
		WirelessTypes::Frequency m_frequency;

		//Variable: m_payload
		//	The payload bytes in the packet
		Payload m_payload;

	public:
		//Function: isDataPacket
		//	Gets whether or not the packet is a Data packet.
		//
		//Returns:
		//	true if the packet is a data packet, false otherwise.
		bool isDataPacket() const;

		//Function: isDiscoveryPacket
		//	Gets whether or not the packet is a Node Discovery packet.
		//
		//Returns:
		//	true if the packet is a discovery packet, false otherwise.
		bool isDiscoveryPacket() const;

		//Function: deliveryStopFlags
		//	Gets the delivery stop flags for the packet
		//
		//Returns:
		//	The delivery stop flags as a <DeliveryStopFlags> object
		DeliveryStopFlags deliveryStopFlags() const;

		//Function: deliveryStopFlags
		//	Sets the delivery stop flags to the passed in flags
		//	
		//Parameters:
		//	flags - the delivery stop flags to set
		void deliveryStopFlags(DeliveryStopFlags flags);
		
		//Function: type
		//	Gets the packet type of the packet
		//
		//Returns:
		//	The packet type as a <PacketType> enumeration
		PacketType type() const;

		//Function: type
		//	Sets the packet type of the packet
		//
		//Parameters:
		//	packetType - The packet type to set, as a <PacketType> enumeration
		void type(PacketType packetType);

		//Function: nodeAddress
		//	Gets the node address of the packet
		//
		//Returns:
		//	The node address of the packet
		NodeAddress nodeAddress() const;

		//Function: nodeAddress
		//	Sets the node address of the packet
		//
		//Parameters:
		//	address - The node address to set 
		void nodeAddress(NodeAddress address);

		//Function: nodeRSSI
		//	Gets the node RSSI of the packet
		//
		//Returns:
		//	The node RSSI
		int16 nodeRSSI() const;

		//Function: nodeRSSI
		//	Sets the node RSSI of the packet
		//
		//Parameters:
		//	rssi - The node rssi to set
		void nodeRSSI(int16 rssi);

		//Function: baseRSSI
		//	Gets the base station RSSI of the packet
		//
		//Returns:
		//	The base station RSSI
		int16 baseRSSI() const;

		//Function: baseRSSI
		//	Sets the base station RSSI of the packet
		//
		//Parameters:
		//	rssi - The base station RSSI
		void baseRSSI(int16 rssi);

		//Function: frequency
		//	Gets the <WirelessTypes::Frequency> that the packet was collected on
		//
		//Returns:
		//	The <WirelessTypes::Frequency> that the packet was collected on
		WirelessTypes::Frequency frequency() const;

		//Function: frequency
		//	Sets the <WirelessTypes::Frequency> that the packet was collected on
		//
		//Parameters:
		//	freq - The <WirelessTypes::Frequency> that the packet was collected on
		void frequency(WirelessTypes::Frequency freq);

		//Function: payload
		//	Gets the payload bytes of the packet
		//
		//Returns:
		//	The payload of the packet, as a vector of bytes
		const Payload& payload() const;

		//Function: payload
		//	Sets the payload bytes of the packet
		//
		//Parameters:
		//	bytes - The payload of the packet, as a vector of bytes
		void payload(const Bytes& bytes);
	};
}