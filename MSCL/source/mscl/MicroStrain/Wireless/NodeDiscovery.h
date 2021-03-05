/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/Timestamp.h"
#include "WirelessTypes.h"
#include "WirelessModels.h"
#include "mscl/Version.h"

namespace mscl
{
    class WirelessPacket;

    //API Class: NodeDiscovery
    //    Represents 1 node discovery, which is created when a Wireless Node Discovery packet is sent from a Node.
    //    Note: There are multiple versions of Node Discovery packets which have been developed over time.
    //          Each version has added more useful information. If an earlier version of the Node Discovery packet is
    //          heard, this NodeDiscovery object will have some information be invalid (set to default values).
    class NodeDiscovery
    {
        friend class WirelessNode_Impl;

#ifndef SWIG
    public:
        NodeDiscovery();

        //Constructor: NodeDiscovery
        //    Creates a NodeDiscovery object from a WirelessPacket
        //
        //Parameters:
        //    packet - The <WirelessPacket> to create the NodeDiscovery object from
        explicit NodeDiscovery(const WirelessPacket& packet);
#endif

    private:
        //Variable: m_eepromMap
        //  Contains an eeprom map to use for updating a WirelessNode's eeprom cache with the Node Discovery info, if desired.
        WirelessTypes::EepromMap m_eepromMap;

        //Variable: m_nodeAddress
        //    The node address of the node that sent the Node Discovery packet.
        NodeAddress m_nodeAddress;

        //Variable: m_radioChannel
        //    The radio channel (<WirelessTypes::Frequency>) that the node was on that sent the Node Discovery packet.
        WirelessTypes::Frequency m_radioChannel;

        //Variable: m_panId
        //    The PAN id of the Node that send the Node Discovery packet.
        uint16 m_panId;

        //Variable: m_model
        //    The model of the node that sent the Node Discovery packet.
        WirelessModels::NodeModel m_model;

        //Variable: m_serialNumber
        //    The serial number of the node that sent the Node Discovery packet.
        uint32 m_serialNumber;

        //Variable: m_firmwareVersion
        //    The firmware version of the node that sent the Node Discovery packet.
        Version m_firmwareVersion;

        //Variable: m_defaultMode
        //    The <WirelessTypes::DefaultMode> of the node that sent the Node Discovery packet.
        WirelessTypes::DefaultMode m_defaultMode;

        //Variable: m_commProtocol
        //  The <WirelessTypes::CommProtocol> of the node that sent the Node Discovery packet.
        WirelessTypes::CommProtocol m_commProtocol;

        //Variable: m_asppVersionLxrs
        //  The ASPP <Version> of the node when in LXRS mode.
        Version m_asppVersionLxrs;

        //Variable: m_asppVersionLxrsPlus
        //  The ASPP <Version> of the node when in LXRS+ mode.
        Version m_asppVersionLxrsPlus;

        //Variable: m_bitResult
        //    The Built In Test result that was sent in the packet.
        uint32 m_bitResult;

        //Variable: m_baseRssi
        //    The Base Station RSSI that identifies the received signal strength at the Base Station.
        int16 m_baseRssi;

        //Variable: m_timestamp
        //    The <Timestamp> of when the NodeDiscovery packet was received by MSCL.
        Timestamp m_timestamp;

    protected:
        const WirelessTypes::EepromMap& eepromMap() const;

    private:
        //Function: initFromPacket_v1
        //    Initializes the NodeDiscovery object from a version 1 Node Discovery packet.
        //
        //Parameters:
        //    packet - The <WirelessPacket> which is a version 1 Node Discovery packet.
        void initFromPacket_v1(const WirelessPacket& packet);

        //Function: initFromPacket_v2
        //    Initializes the NodeDiscovery object from a version 2 Node Discovery packet.
        //
        //Parameters:
        //    packet - The <WirelessPacket> which is a version 2 Node Discovery packet.
        void initFromPacket_v2(const WirelessPacket& packet);

        //Function: initFromPacket_v3
        //    Initializes the NodeDiscovery object from a version 3 Node Discovery packet.
        //
        //Parameters:
        //    packet - The <WirelessPacket> which is a version 3 Node Discovery packet.
        void initFromPacket_v3(const WirelessPacket& packet);

        //Function: initFromPacket_v4
        //    Initializes the NodeDiscovery object from a version 4 Node Discovery packet.
        //
        //Parameters:
        //    packet - The <WirelessPacket> which is a version 4 Node Discovery packet.
        void initFromPacket_v4(const WirelessPacket& packet);

        //Function: initFromPacket_v5
        //    Initializes the NodeDiscovery object from a version 5 Node Discovery packet.
        //
        //Parameters:
        //    packet - The <WirelessPacket> which is a version 5 Node Discovery packet.
        void initFromPacket_v5(const WirelessPacket& packet);

    public:
        //API Function: nodeAddress
        //    Gets the node address of the discovered Node.
        //
        //Returns:
        //    The node address of the discovered Node.
        NodeAddress nodeAddress() const;

        //API Function: frequency
        //    Gets the <WirelessTypes::Frequency> of the discovered Node.
        //
        //Returns:
        //    The <WirelessTypes::Frequency> of the discovered Node.
        WirelessTypes::Frequency frequency() const;

        //API Function: panId
        //    Gets the PAN Id of the discovered Node.
        //    Note: Returns 0 if not present in the packet.
        //
        //Returns:
        //    The PAN Id of the discovered Node.
        uint16 panId() const;

        //API Function: model
        //    Gets the model of the discovered Node.
        //
        //Returns:
        //    The <WirelessModels::NodeModel> of the discovered Node.
        WirelessModels::NodeModel model() const;

        //API Function: serialNumber
        //    Gets the serial number of the discovered Node.
        //    Note: Returns 0 if not present in the packet.
        //
        //Returns:
        //    The serial number of the discovered Node.
        uint32 serialNumber() const;

        //API Function: firmwareVersion
        //    Gets the firmware version of the discovered Node.
        //    Note: Returns 0.0.0 if not present in the packet.
        //
        //Returns:
        //    The firmware version of the discovered Node.
        Version firmwareVersion() const;

        //API Function: defaultMode
        //    Gets the <WirelessTypes::DefaultMode> of the discovered Node.
        //    Note: Returns 999 if not present in the packet.
        //
        //Returns:
        //    The <WirelessTypes::DefaultMode> of the discovered Node.
        WirelessTypes::DefaultMode defaultMode() const;

        //API Function: builtInTestResult
        //    Gets the result bitmask of the built in test.
        //
        //Returns:
        //  A uint32 bitmask representing the result of the built in test.
        uint32 builtInTestResult() const;

        //API Function: communicationProtocol
        //  Gets the <WirelessTypes::CommProtocol> of the discovered Node.
        //
        //Returns:
        //  The <WirelessTypes::CommProtocol> that the Node is currently in.
        WirelessTypes::CommProtocol communicationProtocol() const;

        //API Function: asppVersion_lxrs
        //  Gets the ASPP protocol <Version> of the Node when it is in LXRS RadioMode.
        Version asppVersion_lxrs() const;

        //API Function: asppVersion_lxrsPlus
        //  Gets the ASPP protocol <Version> of the Node when it is in LXRS+ RadioMode.
        Version asppVersion_lxrsPlus() const;

        //API Function: baseRssi
        //    Gets the base station rssi of the discovered Node.
        //
        //Returns:
        //    The base station rssi of the discovered Node.
        int16 baseRssi() const;

        //API Function: timestamp
        //    Gets the <Timestamp> of when the NodeDiscovery packet was received by MSCL.
        //
        //Returns:
        //    The <Timestamp> of when the NodeDiscovery packet was received by MSCL.
        Timestamp timestamp() const;
    };

    //API Typedef: NodeDiscoveries
    //    typedef for a vector of <NodeDiscovery> objects
    typedef std::vector<NodeDiscovery> NodeDiscoveries;
}