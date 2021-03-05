/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/Wireless/DeliveryStopFlags.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"

namespace mscl
{
    //Class: WirelessPacket
    //    Represents a MicroStrain wireless packet
    class WirelessPacket
    {
    public:
        //Typedef: Payload
        //    typedef for the bytes that make up a payload in a packet
        typedef ByteStream Payload;

        //=====================================================================================================
        //Constants: Wireless Packet Bytes
        //    ASPP_V1_SOP      - 0xAA      - The "Start of Packet" byte for the ASPP v1 packets
        //    ASPP_V2_SOP      - 0xAB      - The "Start of Packet" byte for the ASPP v2 packets
        //    ASPP_V3_SOP      - 0xAC      - The "Start of Packet" byte for the ASPP v3 packets
        //=====================================================================================================
        static const uint8 ASPP_V1_SOP       = 0xAA;
        static const uint8 ASPP_V2_SOP       = 0xAB;
        static const uint8 ASPP_V3_SOP       = 0xAC;

        //=====================================================================================================
        //Constants: Wireless Packet Information
        //    ASPP_MIN_RESPONSE_PACKET_SIZE     - 10    - The minimum number of bytes to make a valid ASPP Response packet (Payload len + NODE RSSI + BASE RSSI + Checksum)
        //    ASPP_V1_NUM_BYTES_BEFORE_PAYLOAD  - 6     - The number of bytes in the ASPPv1 packets before the payload
        //    ASPP_V1_NUM_BYTES_AFTER_PAYLOAD   - 4     - The number of bytes in the ASPPv1 packets after the payload
        //    ASPP_V2_NUM_BYTES_BEFORE_PAYLOAD  - 9     - The number of bytes in the ASPPv2 packets before the payload
        //    ASPP_V2_NUM_BYTES_AFTER_PAYLOAD   - 4     - The number of bytes in the ASPPv2 packets after the payload
        //    ASPP_V3_NUM_BYTES_BEFORE_PAYLOAD  - 9     - The number of bytes in the ASPPv3 packets before the payload
        //    ASPP_V3_NUM_BYTES_AFTER_PAYLOAD   - 6     - The number of bytes in the ASPPv3 packets after the payload
        //=====================================================================================================
        static const uint16 ASPP_MIN_RESPONSE_PACKET_SIZE       = 10;
        static const uint16 ASPP_V1_NUM_BYTES_BEFORE_PAYLOAD    = 6;
        static const uint16 ASPP_V1_NUM_BYTES_AFTER_PAYLOAD     = 4;
        static const uint16 ASPP_V2_NUM_BYTES_BEFORE_PAYLOAD    = 9;
        static const uint16 ASPP_V2_NUM_BYTES_AFTER_PAYLOAD     = 4;
        static const uint16 ASPP_V3_NUM_BYTES_BEFORE_PAYLOAD    = 9;
        static const uint16 ASPP_V3_NUM_BYTES_AFTER_PAYLOAD     = 6;

        //=====================================================================================================
        //Enums: PacketType
        
        //  packetType_NotFound                     - -2   - No Packet Found
        //  packetType_unknown                      - -1   - Unknown Packet Type
        //  packetType_nodeCommand                  - 0x00 - Node Command Packet
        //  packetType_nodeErrorReply               - 0x02 - Node Command Error Reply Packet
        //  packetType_LDC                          - 0x04 - Standard Low Duty Cycle Packet
        //  packetType_nodeDiscovery                - 0x07 - Node Discovery Packet (version 1)
        //  packetType_TCLinkLDC                    - 0x09 - TC-Link Low Duty Cycle packet
        //  packetType_SyncSampling                 - 0x0A - Synchronized Sampling Packet
        //  packetType_BufferedLDC                  - 0x0D - Buffered LDC Packet
        //  packetType_AsyncDigital                 - 0x0E - Asynchronous Digital (Event) Packet
        //  packetType_AsyncDigitalAnalog           - 0x0F - Asynchronous Digital and Analog (Event) Packet
        //  packetType_beaconEcho                   - 0x10 - Beacon Echo Packet
        //  packetType_diagnostic                   - 0x11 - Diagnostic Packet
        //  packetType_LDC_16ch                     - 0x14 - LDC Packet with 16 channel support
        //  packetType_LDC_math                     - 0x15 - LDC Math Packet
        //  packetType_nodeDiscovery_v4             - 0x16 - Node Discovery Packet (version 4)
        //  packetType_nodeDiscovery_v2             - 0x17 - Node Discovery Packet (version 2)
        //  packetType_nodeDiscovery_v3             - 0x18 - Node Discovery Packet (version 3)
        //  packetType_SyncSampling_16ch            - 0x1A - Synchronized Sampling Packet with 16 channel support
        //  packetType_SyncSampling_math            - 0x1B - Synchronized Sampling Math Packet
        //  packetType_nodeDiscovery_v5             - 0x1C - Node Discovery Packet (version 5)
        //  packetType_BufferedLDC_16ch             - 0x1D - Buffered LDC Packet with 16 channel support
        //  packetType_nodeReceived                 - 0x20 - Initial response from a command targeting a Node
        //  packetType_nodeSuccessReply             - 0x22 - Node Command Success Reply Packet
        //  packetType_baseCommand                  - 0x30 - Base Station Command Packet
        //  packetType_baseSuccessReply             - 0x31 - Base Station Command Reply Packet
        //  packetType_baseErrorReply               - 0x32 - Base Station Command Error Reply Packet
        //  packetType_rfScanSweep                  - 0x33 - RF Sweep Packet sent from the BaseStation in RF Scan Mode
        //  packetType_baseReceived                 - 0x34 - Initial response from a command targeting the Base Station
        //  packetType_SHM                          - 0xA0 - Structural Health Monitoring Packet
        //  packetType_HclSmartBearing_Calibrated   - 0xA1 - HclSmartBearing Calibrated data Packet
        //  packetType_HclSmartBearing_Raw          - 0xA2 - HclSmartBearing Raw data Packet
        //  packetType_rawAngleStrain               - 0xA3 - Raw Angle Strain data Packet
        //  packetType_roller                       - 0xA4 - Roller data Packet
        //=====================================================================================================
        enum PacketType
        {
            packetType_NotFound                     = -2,
            packetType_unknown                      = -1,
        
            packetType_nodeCommand                  = 0x00,
            packetType_nodeErrorReply               = 0x02,
            packetType_LDC                          = 0x04,
            packetType_nodeDiscovery                = 0x07,
            packetType_TCLinkLDC                    = 0x09,
            packetType_SyncSampling                 = 0x0A,
            packetType_BufferedLDC                  = 0x0D,
            packetType_AsyncDigital                 = 0x0E,
            packetType_AsyncDigitalAnalog           = 0x0F,
            packetType_beaconEcho                   = 0x10,
            packetType_diagnostic                   = 0x11,
            packetType_LDC_16ch                     = 0x14,
            packetType_LDC_math                     = 0x15,
            packetType_nodeDiscovery_v4             = 0x16,
            packetType_nodeDiscovery_v2             = 0x17,
            packetType_nodeDiscovery_v3             = 0x18,
            packetType_SyncSampling_16ch            = 0x1A,
            packetType_SyncSampling_math            = 0x1B,
            packetType_nodeDiscovery_v5             = 0x1C,
            packetType_BufferedLDC_16ch             = 0x1D,
            packetType_nodeReceived                 = 0x20,
            packetType_nodeSuccessReply             = 0x22,
            packetType_baseCommand                  = 0x30,
            packetType_baseSuccessReply             = 0x31,
            packetType_baseErrorReply               = 0x32,
            packetType_rfScanSweep                  = 0x33,
            packetType_baseReceived                 = 0x34,
            packetType_SHM                          = 0xA0,
            packetType_HclSmartBearing_Calibrated   = 0xA1,
            packetType_HclSmartBearing_Raw          = 0xA2,
            packetType_rawAngleStrain               = 0xA3,
            packetType_roller                       = 0xA4,
        };

        //Enum: AsppVersion
        //  The possible ASPP versions
        //
        //  aspp_v1 - 0 - ASPP v1.X
        //  aspp_v2 - 1 - ASPP v2.X
        //  aspp_v3 - 2 - ASPP v3.X
        enum AsppVersion
        {
            aspp_v1 = 0,
            aspp_v2 = 1,
            aspp_v3 = 2
        };

        //===================================================
        //Enums: ResponseErrorCode
        //    Possible error codes from response packets.
        //
        //    error_none            - 0x00 - No Error.
        //    error_unknownEeprom   - 0x01 - An Unknown/Unsupported Eeprom was attempted to be accessed.
        //    error_outOfBounds     - 0x02 - An out of bounds value was attempted to be used.
        //    error_readOnly        - 0x03 - Attempted to write to a read only Eeprom location.
        //    error_hardwareError   - 0x04 - A hardware error has occurred.
        //===================================================
        enum ResponseErrorCode
        {
            error_none            = 0x00,
            error_unknownEeprom   = 0x01,
            error_outOfBounds     = 0x02,
            error_readOnly        = 0x03,
            error_hardwareError   = 0x04
        };

    public:
        //Constructor: WirelessPacket
        //    The default constructor for a wireless packet
        WirelessPacket();

        virtual ~WirelessPacket() {};

        //Function: throwEepromResponseError
        //    Throws an exception based on a <ResponseErrorCode> from a read/write eeprom command.
        //    Not all error codes will cause an exception.
        //
        //Parameters:
        //    errorCode - The <ResponseErrorCode> to use for potentially throwing an exception.
        //    location - The eeprom location associated with the command.
        //
        //Exceptions:
        //    - <Error_NotSupported> - invalid eeprom location, value out of bounds, or read only eeprom location.
        static void throwEepromResponseError(ResponseErrorCode errorCode, uint16 location);

    protected:
        //Variable: m_asppVersion
        //  The <AsppVersion> for the packet.
        AsppVersion m_asppVersion;

        //Variable: m_deliveryStopFlags
        //    The delivery stop flags of the packet
        DeliveryStopFlags m_deliveryStopFlags;

        //Variable: m_type
        //    The packet type of the packet
        PacketType m_type;

        //Variable: m_nodeAddress
        //    The node address in the packet
        NodeAddress m_nodeAddress;

        //Variable: m_nodeRSSI
        //    The node received signal strength indicator (strength of which the node received the command from the base station).
        //    This value will be set to -200 if the packet contains a legacy junk lqi byte that should be thrown out.
        int16 m_nodeRSSI;

        //Variable: m_baseRSSI
        //    The base received signal strength indicator (strength of which the base station received the response from the node).
        int16 m_baseRSSI;

        //Variable: m_frequency
        //    The <WirelessTypes::Frequency> that this packet was collected on.
        WirelessTypes::Frequency m_frequency;

        //Variable: m_payload
        //    The payload bytes in the packet
        Payload m_payload;

    public:
        //Function: isDataPacket
        //    Gets whether or not the packet is a Data packet.
        //
        //Returns:
        //    true if the packet is a data packet, false otherwise.
        //bool isDataPacket() const;

        //Function: isDataPacket
        //    Gets whether or not the packet is a Data packet.
        //
        //Returns:
        //    true if the packet is a data packet, false otherwise.
        static bool isDataPacket(PacketType type);

        //Function: isDiscoveryPacket
        //    Gets whether or not the packet is a Node Discovery packet.
        //
        //Returns:
        //    true if the packet is a discovery packet, false otherwise.
        bool isDiscoveryPacket() const;

        //Function: asppVersion
        //  Gets the ASPP version of the packet.
        AsppVersion asppVersion() const;

        //Function: asppVersion
        //  Sets the ASPP version of the packet.
        void asppVersion(AsppVersion ver);

        //Function: deliveryStopFlags
        //    Gets the delivery stop flags for the packet
        //
        //Returns:
        //    The delivery stop flags as a <DeliveryStopFlags> object
        DeliveryStopFlags deliveryStopFlags() const;

        //Function: deliveryStopFlags
        //    Sets the delivery stop flags to the passed in flags
        //    
        //Parameters:
        //    flags - the delivery stop flags to set
        void deliveryStopFlags(DeliveryStopFlags flags);
        
        //Function: type
        //    Gets the packet type of the packet
        //
        //Returns:
        //    The packet type as a <PacketType> enumeration
        PacketType type() const;

        //Function: type
        //    Sets the packet type of the packet
        //
        //Parameters:
        //    packetType - The packet type to set, as a <PacketType> enumeration
        void type(PacketType packetType);

        //Function: nodeAddress
        //    Gets the node address of the packet
        //
        //Returns:
        //    The node address of the packet
        NodeAddress nodeAddress() const;

        //Function: nodeAddress
        //    Sets the node address of the packet
        //
        //Parameters:
        //    address - The node address to set 
        void nodeAddress(NodeAddress address);

        //Function: nodeRSSI
        //    Gets the node RSSI of the packet
        //
        //Returns:
        //    The node RSSI
        int16 nodeRSSI() const;

        //Function: nodeRSSI
        //    Sets the node RSSI of the packet
        //
        //Parameters:
        //    rssi - The node rssi to set
        void nodeRSSI(int16 rssi);

        //Function: baseRSSI
        //    Gets the base station RSSI of the packet
        //
        //Returns:
        //    The base station RSSI
        int16 baseRSSI() const;

        //Function: baseRSSI
        //    Sets the base station RSSI of the packet
        //
        //Parameters:
        //    rssi - The base station RSSI
        void baseRSSI(int16 rssi);

        //Function: frequency
        //    Gets the <WirelessTypes::Frequency> that the packet was collected on
        //
        //Returns:
        //    The <WirelessTypes::Frequency> that the packet was collected on
        WirelessTypes::Frequency frequency() const;

        //Function: frequency
        //    Sets the <WirelessTypes::Frequency> that the packet was collected on
        //
        //Parameters:
        //    freq - The <WirelessTypes::Frequency> that the packet was collected on
        void frequency(WirelessTypes::Frequency freq);

        //Function: payload
        //    Gets the payload bytes of the packet
        //
        //Returns:
        //    The payload of the packet, as a vector of bytes
        const Payload& payload() const;

        //Function: payload
        //    Sets the payload bytes of the packet
        //
        //Parameters:
        //    bytes - The payload of the packet, as a vector of bytes
        void payload(const Bytes& bytes);
    };
}