/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/SampleRate.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"
#include "mscl/TimeSpan.h"
#include "mscl/MicroStrain/Wireless/WirelessNode.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromHelper.h"

namespace mscl
{
    //forward declarations
    class SyncNetworkInfo;

    //Class: SyncNodeConfig
    //    A helper class for reading and writing values used for Synchronized Sampling configuration
    class SyncNodeConfig
    {
    private:
        SyncNodeConfig();    //disabled default constructor

    public:
        //Constructor: SyncNodeConfig
        //    Creates a SyncNodeConfig object
        //
        //Parameters:
        //    networkInfo - A <SyncNetworkInfo> object containing information on a Node in the Sync Sampling network.
        SyncNodeConfig(const SyncNetworkInfo* networkInfo);

    private:
        //Variable: m_networkInfo
        //    The <SyncNetworkInfo> object containing information on the Node in the Sync Sampling network.
        const SyncNetworkInfo* m_networkInfo;

        //Variable: m_eepromHelper
        //    The <NodeEepromHelper> to use in reading and writing eeproms.
        NodeEepromHelper m_eepromHelper;

    public:
        //Function: sampleRate
        //    Gets the <SampleRate> of the node.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        //    - <Error_UnknownSampleRate>: The sample rate value read from the node is not a valid SampleRate.
        SampleRate sampleRate();

        //Function: activeChannels
        //    Gets the <ChannelMask> of the node.
        //
        //Returns:
        //    A <ChannelMask> object representing the active channels of the node.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        ChannelMask activeChannels();

        //Function: activeChannelCount
        //    Gets the number of active channels on the node for use in Sync Sampling formulas.
        //    Note: this does not necessarily return the true active channel count, as some channels
        //          on some nodes don't count towards active channels in Sync Sampling formulas.
        //
        //Returns:
        //    The number of active channels on the node for use in Sync Sampling formulas.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        uint16 activeChannelCount();

        //Function: commProtocol
        //  Gets the <WirelessTypes::CommProtocol> of the Node.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::CommProtocol commProtocol();

        //Function: dataFormat
        //    Gets the <WirelessTypes::DataFormat> of the node.
        //
        //Returns:
        //    A <WirelessTypes::DataFormat> object representing the data format of the node.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::DataFormat dataFormat();

        //Function: collectionMethod
        //    Gets the <WirelessTypes::DataCollectionMethod> of the node.
        //
        //Returns:
        //    A <WirelessTypes::DataCollectionMethod> object representing the collection method of the Node.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::DataCollectionMethod collectionMethod();

        //Function: sweepsPerSession
        //    Gets the number of sweeps per session of the node.
        //
        //Returns:
        //    The number of sweeps per session of the node.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        uint32 sweepsPerSession();

        //Function: samplingMode
        //    Gets the <WirelessTypes::SamplingMode> ofthe node.
        //
        //Returns:
        //    The <WirelessTypes::SamplingMode> of the node.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::SamplingMode samplingMode();

        //Function: sensorDelay
        //    Gets the value stored in eeprom for the sensor delay of the node.
        //
        //Returns:
        //    The sensor delay of the node as a <TimeSpan>.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        uint32 sensorDelay();

        //Function: timeBetweenBursts
        //    Gets the time between bursts of the node.
        //
        //Returns:
        //    A <TimeSpan> representing the time between bursts of the node.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        TimeSpan timeBetweenBursts();

        //Function: filterSettlingTime
        //  Gets the <WirelessTypes::SettlingTime> of the node for a specific channel number.
        //
        //Parameters:
        //  channelNumber - The channel number to get the settling time for (ch1 = 1, ch8 = 8).
        //
        //Returns:
        //  A <WirelessTypes::SettlingTime>.
        //
        //Exceptions:
        //  - <Error_NodeCommunication>: Failed to read the value from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::SettlingTime filterSettlingTime(uint8 channelNumber);

        //Function: dataMode
        //    Gets the <DataModeMask> of the node.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        DataModeMask dataMode();

        //Function: derivedDataRate
        //  Gets the derived data rate as a <SampleRate> object.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        SampleRate derivedDataRate();

        //Function: derivedChannelMask
        //  Gets the channel mask for the specified <WirelessTypes::DerivedCategory> as a <ChannelMask>.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        ChannelMask derivedChannelMask(WirelessTypes::DerivedCategory category);

        //Function: diagnosticInterval
        //  Gets the diagnostic interval set on the Node.
        uint16 diagnosticInterval();

    public:
        //Function: txPerGroup
        //    Writes the transmissions per group to the node.
        //
        //Parameters:
        //    txPerGroup - The number of transmissions per group value to write to the node.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to write the value to the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        void txPerGroup(uint32 txPerGroup);

        //Function: groupSize
        //    Writes the group size to the node.
        //
        //Parameters:
        //    groupSize - The group size value to write to the node.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to write the value to the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        void groupSize(uint32 groupSize);

        //Function: tdmaAddress
        //    Writes the TDMA address to the node.
        //
        //Parameters:
        //    address - The TDMA address value to write to the node.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to write the value to the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        void tdmaAddress(uint32 address);

        //Function: retransmission
        //    Writes the retransmission value to the node.
        //
        //Parameters:
        //    reTx - The <WirelessTypes::NodeRetransmission> value to write to the node.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to write the value to the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        void retransmission(WirelessTypes::NodeRetransmission reTx);

        //Function: maxRetransPerBurst
        //    Writes the maximum retransmissions per burst to the node.
        //
        //Parameters:
        //    maxReTxPerBurst - The maximum retransmissions per burst value to write to the node.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to write the value to the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        void maxRetransPerBurst(uint32 maxReTxPerBurst);

        //Function: applyEepromChanges
        //    Resets the radio/power on the Node to apply eeprom changes that have been made.
        void applyEepromChanges();
    };
}