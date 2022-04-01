/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "NodeDiscovery.h"
#include "Configuration/NodeEepromMap.h"
#include "Packets/WirelessPacket.h"
#include "Packets/NodeDiscoveryPacket.h"
#include "Packets/NodeDiscoveryPacket_v2.h"
#include "Packets/NodeDiscoveryPacket_v3.h"
#include "Packets/NodeDiscoveryPacket_v4.h"
#include "Packets/NodeDiscoveryPacket_v5.h"

namespace mscl
{
    NodeDiscovery::NodeDiscovery():
        m_nodeAddress(0),
        m_radioChannel(WirelessTypes::freq_unknown),
        m_panId(0),
        m_model(static_cast<WirelessModels::NodeModel>(0)),
        m_serialNumber(0),
        m_firmwareVersion(0, 0, 0),
        m_defaultMode(static_cast<WirelessTypes::DefaultMode>(999)),
        m_commProtocol(WirelessTypes::commProtocol_lxrs),
        m_asppVersionLxrs(0, 0),
        m_asppVersionLxrsPlus(0, 0),
        m_bitResult(0),
        m_baseRssi(WirelessTypes::UNKNOWN_RSSI),
        m_timestamp(0)
    {
    }

    NodeDiscovery::NodeDiscovery(const WirelessPacket& packet):
        m_nodeAddress(packet.nodeAddress()),
        m_radioChannel(WirelessTypes::freq_unknown),
        m_panId(0),
        m_model(static_cast<WirelessModels::NodeModel>(0)),
        m_serialNumber(0),
        m_firmwareVersion(0, 0, 0),
        m_defaultMode(static_cast<WirelessTypes::DefaultMode>(999)),
        m_commProtocol(WirelessTypes::commProtocol_lxrs),
        m_asppVersionLxrs(0, 0),
        m_asppVersionLxrsPlus(0, 0),
        m_bitResult(0),
        m_baseRssi(packet.baseRSSI()),
        m_timestamp(Timestamp::timeNow())
    {
        switch(packet.type())
        {
            case WirelessPacket::packetType_nodeDiscovery:
                initFromPacket_v1(packet);
                break;

            case WirelessPacket::packetType_nodeDiscovery_v2:
                initFromPacket_v2(packet);
                break;

            case WirelessPacket::packetType_nodeDiscovery_v3:
                initFromPacket_v3(packet);
                break;

            case WirelessPacket::packetType_nodeDiscovery_v4:
                initFromPacket_v4(packet);
                break;

            case WirelessPacket::packetType_nodeDiscovery_v5:
            {
                //we've added a version to this packet from here on out
                uint8 version = packet.payload().read_uint8(0);

                if(version == 5)
                {
                    initFromPacket_v5(packet);
                }
            }  
            break;

            default:
                break;
        }
    }

    void NodeDiscovery::initFromPacket_v1(const WirelessPacket& packet)
    {
        typedef NodeDiscoveryPacket Info;

        const WirelessPacket::Payload& payload = packet.payload();

        //Frequency
        m_radioChannel = static_cast<WirelessTypes::Frequency>(payload.read_uint8(Info::PAYLOAD_OFFSET_RADIO_CHANNEL));

        //Model (convert from legacy to current model number)
        uint16 legacyModel = payload.read_uint16(Info::PAYLOAD_OFFSET_MODEL_NUMBER);
        m_model = WirelessModels::nodeFromLegacyModel(legacyModel);


        //build the eeprom map for importing to cache
        m_eepromMap[NodeEepromMap::FREQUENCY.location()] = static_cast<uint16>(m_radioChannel);
        m_eepromMap[NodeEepromMap::LEGACY_MODEL_NUMBER.location()] = legacyModel;
    }

    void NodeDiscovery::initFromPacket_v2(const WirelessPacket& packet)
    {
        typedef NodeDiscoveryPacket_v2 Info;

        const WirelessPacket::Payload& payload = packet.payload();

        //Frequency
        m_radioChannel = static_cast<WirelessTypes::Frequency>(payload.read_uint8(Info::PAYLOAD_OFFSET_RADIO_CHANNEL));

        //PAN Id
        m_panId = payload.read_uint16(Info::PAYLOAD_OFFSET_PAN_ID);

        //Model
        uint16 model = payload.read_uint16(Info::PAYLOAD_OFFSET_MODEL_NUMBER);
        uint16 modelOption = payload.read_uint16(Info::PAYLOAD_OFFSET_MODEL_OPTION);
        m_model = static_cast<WirelessModels::NodeModel>((model * 10000) + modelOption);

        //Serial
        m_serialNumber = payload.read_uint32(Info::PAYLOAD_OFFSET_SERIAL_NUMBER);

        //Firmware Version
        uint16 fwVersion = payload.read_uint16(Info::PAYLOAD_OFFSET_FIRMWARE_VER);
        m_firmwareVersion = Version(Utils::msb(fwVersion), Utils::lsb(fwVersion));


        //build the eeprom map for importing to cache
        m_eepromMap[NodeEepromMap::FREQUENCY.location()] = static_cast<uint16>(m_radioChannel);
        m_eepromMap[NodeEepromMap::MODEL_NUMBER.location()] = model;
        m_eepromMap[NodeEepromMap::MODEL_OPTION.location()] = modelOption;
        m_eepromMap[NodeEepromMap::SERIAL_ID.location()] = m_serialNumber >> 16;
        m_eepromMap[NodeEepromMap::SERIAL_ID.location() + 2] = m_serialNumber & 0xFFFF;
        m_eepromMap[NodeEepromMap::FIRMWARE_VER.location()] = fwVersion;
    }

    void NodeDiscovery::initFromPacket_v3(const WirelessPacket& packet)
    {
        typedef NodeDiscoveryPacket_v3 Info;

        const WirelessPacket::Payload& payload = packet.payload();

        //Frequency
        m_radioChannel = static_cast<WirelessTypes::Frequency>(payload.read_uint8(Info::PAYLOAD_OFFSET_RADIO_CHANNEL));

        //PAN Id
        m_panId = payload.read_uint16(Info::PAYLOAD_OFFSET_PAN_ID);

        //Model
        uint16 model = payload.read_uint16(Info::PAYLOAD_OFFSET_MODEL_NUMBER);
        uint16 modelOption = payload.read_uint16(Info::PAYLOAD_OFFSET_MODEL_OPTION);
        m_model = static_cast<WirelessModels::NodeModel>((model * 10000) + modelOption);

        //Serial
        m_serialNumber = payload.read_uint32(Info::PAYLOAD_OFFSET_SERIAL_NUMBER);

        //Firmware Version
        uint16 fwVersion1 = payload.read_uint16(Info::PAYLOAD_OFFSET_FIRMWARE_VER);
        uint16 fwVersion2 = payload.read_uint16(Info::PAYLOAD_OFFSET_FIRMWARE_VER2);

        //make the svn revision from the lsb of the first fw value, and the entire second fw value
        uint32 svnRevision = Utils::make_uint32(0, Utils::lsb(fwVersion1), Utils::msb(fwVersion2), Utils::lsb(fwVersion2));

        m_firmwareVersion = Version(Utils::msb(fwVersion1), svnRevision);

        //Default Mode
        m_defaultMode = static_cast<WirelessTypes::DefaultMode>(payload.read_uint16(Info::PAYLOAD_OFFSET_DEFAULT_MODE));


        //build the eeprom map for importing to cache
        m_eepromMap[NodeEepromMap::FREQUENCY.location()] = static_cast<uint16>(m_radioChannel);
        m_eepromMap[NodeEepromMap::MODEL_NUMBER.location()] = model;
        m_eepromMap[NodeEepromMap::MODEL_OPTION.location()] = modelOption;
        m_eepromMap[NodeEepromMap::SERIAL_ID.location()] = m_serialNumber >> 16;
        m_eepromMap[NodeEepromMap::SERIAL_ID.location() + 2] = m_serialNumber & 0xFFFF;
        m_eepromMap[NodeEepromMap::FIRMWARE_VER.location()] = fwVersion1;
        m_eepromMap[NodeEepromMap::FIRMWARE_VER2.location()] = fwVersion2;
        m_eepromMap[NodeEepromMap::DEFAULT_MODE.location()] = static_cast<uint16>(m_defaultMode);
    }

    void NodeDiscovery::initFromPacket_v4(const WirelessPacket& packet)
    {
        //same first bytes as v3 packet
        initFromPacket_v3(packet);

        m_bitResult = packet.payload().read_uint32(NodeDiscoveryPacket_v4::PAYLOAD_OFFSET_BUILT_IN_TEST);
    }

    void NodeDiscovery::initFromPacket_v5(const WirelessPacket& packet)
    {
        typedef NodeDiscoveryPacket_v5 Info;

        const WirelessPacket::Payload& payload = packet.payload();

        //Radio Mode
        m_commProtocol = static_cast<WirelessTypes::CommProtocol>(payload.read_uint8(Info::PAYLOAD_OFFSET_RADIO_MODE));

        //Frequency
        m_radioChannel = static_cast<WirelessTypes::Frequency>(payload.read_uint8(Info::PAYLOAD_OFFSET_RADIO_CHANNEL));

        //PAN Id
        m_panId = payload.read_uint16(Info::PAYLOAD_OFFSET_PAN_ID);

        //Model
        uint16 model = payload.read_uint16(Info::PAYLOAD_OFFSET_MODEL_NUMBER);
        uint16 modelOption = payload.read_uint16(Info::PAYLOAD_OFFSET_MODEL_OPTION);
        m_model = static_cast<WirelessModels::NodeModel>((model * 10000) + modelOption);

        //Serial
        m_serialNumber = payload.read_uint32(Info::PAYLOAD_OFFSET_SERIAL_NUMBER);

        //Firmware Version
        uint16 fwVersion1 = payload.read_uint16(Info::PAYLOAD_OFFSET_FIRMWARE_VER);
        uint16 fwVersion2 = payload.read_uint16(Info::PAYLOAD_OFFSET_FIRMWARE_VER2);

        //make the svn revision from the lsb of the first fw value, and the entire second fw value
        uint32 svnRevision = Utils::make_uint32(0, Utils::lsb(fwVersion1), Utils::msb(fwVersion2), Utils::lsb(fwVersion2));

        m_firmwareVersion = Version(Utils::msb(fwVersion1), svnRevision);

        //ASPP versions
        uint16 asppVersionLxrs = payload.read_uint16(Info::PAYLOAD_OFFSET_ASPP_LXRS);
        uint16 asppVersionLxrsPlus = payload.read_uint16(Info::PAYLOAD_OFFSET_ASPP_LXRS_PLUS);

        m_asppVersionLxrs = Version(Utils::msb(asppVersionLxrs), Utils::lsb(asppVersionLxrs));
        m_asppVersionLxrsPlus = Version(Utils::msb(asppVersionLxrsPlus), Utils::lsb(asppVersionLxrsPlus));

        //Default Mode
        m_defaultMode = static_cast<WirelessTypes::DefaultMode>(payload.read_uint16(Info::PAYLOAD_OFFSET_DEFAULT_MODE));


        //build the eeprom map for importing to cache
        m_eepromMap[NodeEepromMap::FREQUENCY.location()] = static_cast<uint16>(m_radioChannel);
        m_eepromMap[NodeEepromMap::MODEL_NUMBER.location()] = model;
        m_eepromMap[NodeEepromMap::MODEL_OPTION.location()] = modelOption;
        m_eepromMap[NodeEepromMap::SERIAL_ID.location()] = m_serialNumber >> 16;
        m_eepromMap[NodeEepromMap::SERIAL_ID.location() + 2] = m_serialNumber & 0xFFFF;
        m_eepromMap[NodeEepromMap::FIRMWARE_VER.location()] = fwVersion1;
        m_eepromMap[NodeEepromMap::FIRMWARE_VER2.location()] = fwVersion2;
        m_eepromMap[NodeEepromMap::DEFAULT_MODE.location()] = static_cast<uint16>(m_defaultMode);
        m_eepromMap[NodeEepromMap::ASPP_VER_LXRS.location()] = asppVersionLxrs;
        m_eepromMap[NodeEepromMap::ASPP_VER_LXRS_PLUS.location()] = asppVersionLxrsPlus;
        m_eepromMap[NodeEepromMap::COMM_PROTOCOL.location()] = static_cast<uint16>(m_commProtocol);
    }

    const WirelessTypes::EepromMap& NodeDiscovery::eepromMap() const
    {
        return m_eepromMap;
    }

    NodeAddress NodeDiscovery::nodeAddress() const
    {
        return m_nodeAddress;
    }

    WirelessTypes::Frequency NodeDiscovery::frequency() const
    {
        return m_radioChannel;
    }

    uint16 NodeDiscovery::panId() const
    {
        return m_panId;
    }

    WirelessModels::NodeModel NodeDiscovery::model() const
    {
        return m_model;
    }

    uint32 NodeDiscovery::serialNumber() const
    {
        return m_serialNumber;
    }

    Version NodeDiscovery::firmwareVersion() const
    {
        return m_firmwareVersion;
    }

    WirelessTypes::DefaultMode NodeDiscovery::defaultMode() const
    {
        return m_defaultMode;
    }

    uint32 NodeDiscovery::builtInTestResult() const
    {
        return m_bitResult;
    }

    WirelessTypes::CommProtocol NodeDiscovery::communicationProtocol() const
    {
        return m_commProtocol;
    }

    Version NodeDiscovery::asppVersion_lxrs() const
    {
        return m_asppVersionLxrs;
    }

    Version NodeDiscovery::asppVersion_lxrsPlus() const
    {
        return m_asppVersionLxrsPlus;
    }

    int16 NodeDiscovery::baseRssi() const
    {
        return m_baseRssi;
    }

    Timestamp NodeDiscovery::timestamp() const
    {
        return m_timestamp;
    }
}