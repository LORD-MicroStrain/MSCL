/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/Types.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"

namespace mscl
{
    //API Class: MipPacket
    //    A class that contains packet information about an Inertial packet
    class MipPacket
    {
    public:
        //=====================================================================================================
        //API Enums: Response State
        //    MIP_ACK_NACK_ERROR_NONE                        - 0    - No Error
        //    MIP_ACK_NACK_ERROR_UNKNOWN_COMMAND            - 1    - Error: Unknown command was sent to the device
        //    MIP_ACK_NACK_ERROR_CHECKSUM_INVALID            - 2    - Error: Invalid checksum was recieved by the device
        //    MIP_ACK_NACK_ERROR_PARAMETER_INVALID        - 3    - Error: Invalid parameter was received by the device
        //    MIP_ACK_NACK_ERROR_COMMAND_FAILED            - 4    - Error: The command has failed
        //    MIP_ACK_NACK_ERROR_COMMAND_TIMEOUT            - 5    - Error: The command has timed out
        //    MIP_ACK_NACK_ERROR_UNKNOWN_DESCRIPTOR_SET    - 6    - Error: Unknown descriptor set was recieved by the device
        //=====================================================================================================
        enum MipAckNack
        {
            MIP_ACK_NACK_ERROR_NONE                     = 0,

            MIP_ACK_NACK_ERROR_UNKNOWN_COMMAND          = 1,
            MIP_ACK_NACK_ERROR_CHECKSUM_INVALID         = 2,
            MIP_ACK_NACK_ERROR_PARAMETER_INVALID        = 3,
            MIP_ACK_NACK_ERROR_COMMAND_FAILED           = 4,
            MIP_ACK_NACK_ERROR_COMMAND_TIMEOUT          = 5,
            MIP_ACK_NACK_ERROR_UNKNOWN_DESCRIPTOR_SET   = 6
        };

    public:
        //Default Constructor: MipPacket
        //    The default constructor for a MipPacket object
        MipPacket();

#ifndef SWIG
    public:
        //Typedef: Payload
        //    typedef for the bytes that make up a payload in a packet
        typedef ByteStream Payload;

    protected:
        //Variable: m_descriptorSet
        //    The descriptor set (packet type) of the MipPacket
        uint8 m_descriptorSet;

        //Variable: m_payload
        //    The payload bytes in the packet
        Payload m_payload;

    public:
        //Function: payload
        //    Sets the payload bytes of the packet
        //
        //Parameters:
        //    bytes - The payload of the packet, as a vector of bytes
        void payload(const Bytes& bytes);

        //Function: type
        //    Sets the descriptor set of the MipPacket
        //
        //Parameters:
        //    set - The descriptor set value to set
        void descriptorSet(uint8 set);
#endif
        //API Function: isDataPacket
        //    Gets whether or not the packet is a data packet
        //
        //Returns:
        //    true if the packet is a data packet, false otherwise
        static bool isDataPacket(uint8 descriptorSet);

        //API Function: descriptorSet
        //    Gets the descriptor set of the MipPacket
        //
        //Returns:
        //    The descriptor set value of the packet
        uint8 descriptorSet() const;

        //API Function: payload
        //    Gets the payload bytes of the packet
        //
        //Returns:
        //    The payload of the packet, as a vector of bytes
        const std::vector<uint8> payload() const;
    };

#ifndef SWIG
    //Struct: MipPacketInfo
    //    Contains constants representing information on MIP Packets
    struct MipPacketInfo
    {
        //=====================================================================================================
        //Enums: MIP Packet Bytes
        //    MIP_PACKET_START_OF_PACKET        - 0x7565    - The full start of packet value of any inertial packet
        //    MIP_PACKET_SOP1                   - 0x75      - The first (start of packet) byte of any inertial packet
        //    MIP_PACKET_SOP2                   - 0x65      - The second (start of packet) byte of any inertial packet
        //    COMMAND_SET_BASE                  - 0x01      - The Base command set is common to many MicroStrain devices.
        //    COMMAND_SET_3DM                   - 0x0C      - The 3DM command set is common to the MicroStrain Inertial sensors that support the MIP packet protocol.
        //    COMMAND_SET_NAV_FILTER            - 0x0D      - The Navigation Filter command set is specific to MicroStrain Inertial Navigation sensors.
        //    COMMAND_SET_GNSS                  - 0x0E      - The GNSS command set is specific to newer Microstrain Inertial sensors that have GNSS receivers.
        //    COMMAND_SET_RTK                   - 0x0F      - The RTK command set is specific to communication with MIP RTK devices.
        //    COMMAND_SET_SYSTEM                - 0x7F      - The System Command set provides a set of advanced commands that are specific to devices.
        //=====================================================================================================
        enum
        {
            MIP_PACKET_START_OF_PACKET      = 0x7565,
            MIP_PACKET_SOP1                 = 0x75,
            MIP_PACKET_SOP2                 = 0x65,
            COMMAND_SET_BASE                = 0x01,
            COMMAND_SET_3DM                 = 0x0C,
            COMMAND_SET_NAV_FILTER          = 0x0D,
            COMMAND_SET_GNSS                = 0x0E,
            COMMAND_SET_RTK                 = 0x0F,
            COMMAND_SET_SYSTEM              = 0x7F
        };

        //=====================================================================================================
        //Enums: MIP Packet Information
        //  MIP_MIN_PACKET_SIZE             - 8        - The minimum number of bytes to make a valid MIP packet (0x75, 0x65, Descriptor Set, Payload Len, Payload, Checksum)
        //  MIP_NUM_BYTES_BEFORE_PAYLOAD    - 4        - The number of bytes in the MIP packets before the payload
        //  MIP_NUM_BYTES_AFTER_PAYLOAD     - 2        - The number of bytes in the MIP packets after the payload
        //=====================================================================================================
        enum
        {
            MIP_MIN_PACKET_SIZE             = 8,
            MIP_NUM_BYTES_BEFORE_PAYLOAD    = 4,
            MIP_NUM_BYTES_AFTER_PAYLOAD     = 2,
            MIP_DESCRIPTOR_BYTE             = 2
        };
    };

    //Struct: DescriptorSet
    //    Contains enums representing Descriptor sets for Inertial Packets
    struct DescriptorSet
    {
    public:
        //=====================================================================================================
        //Enums: MIP Packet Descriptor Sets
        //    DESC_SET_CMD_BASE         - 0x01    - Command Packet, Base Set
        //    DESC_SET_CMD_3DM          - 0x0C    - Command Packet, 3DM Set
        //    DESC_SET_CMD_NAV          - 0x0D    - Command Packet, Navigation Filter Set
        //    DESC_SET_CMD_GNSS         - 0x0E    - Command Packet, GNSS Set
        //    DESC_SET_CMD_RTK          - 0x0F    - Command Packet, RTK Set
        //    DESC_SET_CMD_SYS          - 0x7F    - Command Packet, System Set
        //    DESC_SET_DATA_SENSOR      - 0x80    - Data Packet, Sensor Set
        //    DESC_SET_DATA_GNSS        - 0x81    - Data Packet, GNSS Set
        //    DESC_SET_DATA_EST_FILTER  - 0x82    - Data Packet, Estimation Filter Set
        //    DESC_SET_DATA_DISPLACEMENT- 0x90    - Data Packet, Displacement Set
        //    DESC_SET_DATA_GNSS_1      - 0x91    - Data Packet, GNSS 1 Set
        //    DESC_SET_DATA_GNSS_2      - 0x92    - Data Packet, GNSS 2 Set
        //    DESC_SET_DATA_GNSS_3      - 0x93    - Data Packet, GNSS 3 Set
        //    DESC_SET_DATA_RTK         - 0x93    - Data Packet, RTK (GNSS 3) Set
        //    DESC_SET_DATA_GNSS_4      - 0x94    - Data Packet, GNSS 4 Set
        //    DESC_SET_DATA_GNSS_5      - 0x95    - Data Packet, GNSS 5 Set
        //=====================================================================================================
        enum
        {
            DESC_SET_CMD_BASE            = MipPacketInfo::COMMAND_SET_BASE,
            DESC_SET_CMD_3DM             = MipPacketInfo::COMMAND_SET_3DM,
            DESC_SET_CMD_NAV             = MipPacketInfo::COMMAND_SET_NAV_FILTER,
            DESC_SET_CMD_GNSS            = MipPacketInfo::COMMAND_SET_GNSS,
            DESC_SET_CMD_RTK             = MipPacketInfo::COMMAND_SET_RTK,
            DESC_SET_CMD_SYS             = MipPacketInfo::COMMAND_SET_SYSTEM,
            DESC_SET_DATA_SENSOR         = MipTypes::CLASS_AHRS_IMU,
            DESC_SET_DATA_GNSS           = MipTypes::CLASS_GNSS,
            DESC_SET_DATA_EST_FILTER     = MipTypes::CLASS_ESTFILTER,
            DESC_SET_DATA_DISPLACEMENT   = MipTypes::CLASS_DISPLACEMENT,
            DESC_SET_DATA_GNSS_1         = MipTypes::CLASS_GNSS1,
            DESC_SET_DATA_GNSS_2         = MipTypes::CLASS_GNSS2,
            DESC_SET_DATA_GNSS_3         = MipTypes::CLASS_GNSS3,
            DESC_SET_DATA_RTK            = MipTypes::CLASS_RTK,
            DESC_SET_DATA_GNSS_4         = MipTypes::CLASS_GNSS4,
            DESC_SET_DATA_GNSS_5         = MipTypes::CLASS_GNSS5
        };
    };
#endif
}