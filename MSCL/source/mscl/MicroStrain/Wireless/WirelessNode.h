/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "Commands/AutoCalResult.h"
#include "Commands/PingResponse.h"
#include "Configuration/ActivitySense.h"
#include "Configuration/ConfigIssue.h"
#include "Configuration/DataModeMask.h"
#include "Configuration/EventTriggerOptions.h"
#include "Configuration/FatigueOptions.h"
#include "Configuration/HistogramOptions.h"
#include "Configuration/TempSensorOptions.h"
#include "mscl/Version.h"
#include "mscl/BitMask.h"
#include "ChannelMask.h"
#include "BaseStation.h"
#include "RadioFeatures.h"
#include "WirelessModels.h"
#include "WirelessDataPoint.h"
#include "mscl/MicroStrain/LinearEquation.h"

namespace mscl
{
    //forward declarations
    class WirelessNode_Impl;
    class NodeFeatures;
    class NodeEepromHelper;
    struct ShuntCalCmdInfo;
    class WirelessNodeConfig;
    class WirelessProtocol;
    struct NodeInfo;

    //API Class: WirelessNode
    //    A class representing a MicroStrain wireless node
    //
    //See Also:
    //    <InertialNode>
    class WirelessNode
    {
    private:
        WirelessNode();                                    //default constructor disabled

    public:
        //API Constructor: WirelessNode
        //    Creates a WirelessNode object
        //
        //Parameters:
        //    nodeAddress - the node address of the node
        //    basestation - the node's parent Base Station
        WirelessNode(NodeAddress nodeAddress, const BaseStation& basestation);

        //Destructor: ~WirelessNode
        //    Destroys a WirelessNode object
        virtual ~WirelessNode(){};

        //API Function: Mock
        //  Static function to create a Mock WirelessNode (won't actually talk to a physical device).
        //
        //Parameters:
        //  nodeAddress - the node address of the node
        //  basestation - the node's parent Base Station (should be a Mock BaseStation).
        //  info - The <NodeInfo> to use for creating the mock Node.
        //
        //Returns:
        //  A <WirelessNode> object with a mock implementation.
        static WirelessNode Mock(NodeAddress nodeAddress, const BaseStation& basestation, const NodeInfo& info);

        //API Function: Mock
        //  Static function to create a Mock WirelessNode (won't actually talk to a physical device).
        //
        //Parameters:
        //  nodeAddress - the node address of the node
        //  basestation - the node's parent Base Station (should be a Mock BaseStation).
        //  info - The <NodeInfo> to use for creating the mock Node.
        //  initialEepromCache - The <WirelessTypes::EepromMap> to use as the Node's initial eeprom cache.
        //
        //Returns:
        //  A <WirelessNode> object with a mock implementation.
        static WirelessNode Mock(NodeAddress nodeAddress, const BaseStation& basestation, const NodeInfo& info, const WirelessTypes::EepromMap& initialEepromCache);

    private:
        //Variable: m_impl
        //    The <WirelessNode_Impl> class that contains all the implementation logic for the WirelessNode class.
        std::shared_ptr<WirelessNode_Impl> m_impl;

    public:
#ifndef SWIG
        WirelessNode(std::shared_ptr<WirelessNode_Impl> impl); //constructor with direct underlying implementation for this class.

        //changes/sets the underlying implementation for this class.
        void setImpl(std::shared_ptr<WirelessNode_Impl> impl);    

        //gets a reference to the NodeEepromHelper for the Node.
        NodeEepromHelper& eepromHelper() const;    

        //gets a reference to the WirelessProtocol for the Node for the given CommProtocol.
        const WirelessProtocol& protocol(WirelessTypes::CommProtocol commProtocol) const;
#endif

        //API Function: deviceName
        //    Static function for creating the universal sensor name that should be used for SensorCloud.
        //
        //Parameters:
        //    nodeAddress - The node address of the wireless node. This should be identical to calling the <nodeAddress> function on a <WirelessNode> object.
        //
        //Returns:
        //    The universal sensor name.
        static std::string deviceName(NodeAddress nodeAddress);

        //API Function: features
        //    Gets a reference to the <NodeFeatures> for this Node.
        //    Note: This will be invalid when the WirelessNode is destroyed.
        //
        //Returns:
        //    A <NodeFeatures> reference containing the features for this Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The Node model is not supported by MSCL.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        const NodeFeatures& features() const;

        //API Function: lastCommunicationTime
        //    Gets the <Timestamp> for the last time MSCL communicated with the Node.
        //    Note: EEPROM reads using the cache will not update this timestamp.
        //
        //Returns:
        //    A <Timestamp> representing the last time MSCL communicated with the Node.
        //
        //Exceptions:
        //  - <Error_NoData>: There is no communication time logged for this Node.
        const Timestamp& lastCommunicationTime() const;

        //API Function: lastDeviceState
        //  Gets the last known <DeviceState> for the Node.
        //  This device state is updated by diagnostic packets, as well as when operations are performed by MSCL, such as setting a Node to idle.
        //
        //Returns:
        //  The last known <DeviceState>.
        DeviceState lastDeviceState() const;

        //API Function: setBaseStation
        //    Sets the node's parent Base Station, which will perform all communication with the node
        //
        //Parameters:
        //    base - the BaseStation object to be assigned to the node, which will perform all communication with the node
        void setBaseStation(const BaseStation& basestation);

        //API Function: getBaseStation
        //    Gets a reference to the <BaseStation> that is assigned to this Node.
        //
        //Returns:
        //    A reference to the <BaseStation> that is assigned to this Node.
        BaseStation& getBaseStation();

        //API Function: hasBaseStation
        //    Checks whether the given <BaseStation> is the same <BaseStation> that is assigned to this Node.
        //
        //Parameters:
        //    basestation - The <BaseStation> to check if it is the same as this Node's parent <BaseStation>.
        //
        //Returns:
        //    true if the basestation is the same as this Node's parent <BaseStation>, false if it is different.
        bool hasBaseStation(const BaseStation& basestation) const;

        //API Function: useGroupRead
        //    Enables or disables the use of group eeprom read when trying to read a single value (enabled by default).
        //    Note:    In most cases, leaving this enabled will provide better performance, allowing the cache to be built
        //            quicker, requiring less communication to the actual device. However, in some cases such as with very high
        //            traffic, it may be beneficial to restrict reads to use the single commands, as the packets are smaller over the air.
        //
        //Parameters:
        //    useGroup - Whether the group eeprom read commands can be used (true) or whether to restrict to single eeprom reads (false).
        void useGroupRead(bool useGroup);

        //API Function: readWriteRetries
        //    Sets the number of retry attempts for reading and writing config options with the Node.
        //    By default, the number of retries is 0.
        //    Note:   The timeout that is set per command will be per read and write attempt, meaning
        //            this retry number is multiplied by the timeout for your overall timeout.
        //
        //Parameters:
        //    numRetries - The number of retries to set for reading and writing config options with the Node.
        void readWriteRetries(uint8 numRetries);

        //API Function: readWriteRetries
        //    Gets the number of retry attempts for reading and writing config options with the Node.
        //    By default, the number of retries is 0.
        //    Note:   The timeout that is set per command will be per read and write attempt, meaning
        //            this retry number is multiplied by the timeout for your overall timeout.
        //
        //Returns:
        //    The number of retries to set for reading and writing config options with the Node.
        uint8 readWriteRetries() const;

        //API Function: useEepromCache
        //    Sets whether or not to utilize the eeprom cache when configuring this Node (enabled by default). This can be enabled/disabled at any time.
        //    It is highly recommended to have eeprom caching be enabled.
        //    Note:    The eeprom cache stores the last known value that was written to / read from the Node for each eeprom location. If this is enabled,
        //            any reads will get the last known value from the cache if it exists, and any writes will not write to the Node if the
        //            value attempting to be written is the same as that stored in the cache. Caching of these values will still be performed if this is disabled,
        //            however, read and write operations will then always reach out to the actual device.
        //
        //Parameters:
        //    useCache - whether the eeprom cache should be used (true) or not (false).
        void useEepromCache(bool useCache);

        //API Function: clearEepromCache
        //    Clears the eeprom cache for this Node.
        void clearEepromCache();

        //API Function: updateEepromCacheFromNodeDiscovery
        //  Updates the Node's eeprom cache with information from the <NodeDiscovery> object.
        //  Note: Take caution when using this function that the NodeDiscovery object actually belongs
        //        to this <WirelessNode>.
        //
        //Parameters:
        //  nodeDiscovery - The <NodeDiscovery> object to update the cache with.
        void updateEepromCacheFromNodeDiscovery(const NodeDiscovery& nodeDisovery);

        //API Function: getEepromCache
        //  Gets a copy of the eeprom cache as a <WirelessTypes::EepromMap>.
        //
        //Returns:
        //  A <WirelessTypes::EepromMap> of the current eeprom cache.
        WirelessTypes::EepromMap getEepromCache() const;

        //API Function: nodeAddress
        //    Gets the node address of the Node.
        //
        //Returns:
        //    The node address of the Node
        NodeAddress nodeAddress() const;

        //API Function: frequency
        //    Gets the frequency that the Node is on.
        //
        //Returns:
        //    A <WirelessTypes::Frequency> that the Node is on.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::Frequency frequency() const;

        //API Function: communicationProtocol
        //  Gets the <WirelessTypes::CommProtocol> that the Node is currently set to use.
        //
        //Returns:
        //  The <WirelessTypes::CommProtocol> that the Node is currently set to use.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::CommProtocol communicationProtocol() const;

        //API Function: firmwareVersion
        //    Gets the firmware version of the Node.
        //
        //Returns:
        //    A <Version> representing the firmware version of the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        Version firmwareVersion() const;

        //API Function: model
        //    Gets the model of the Node.
        //
        //Returns:
        //    A <WirelessModels::NodeModel> representing the model of the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessModels::NodeModel model() const;

        //API Function: serial
        //    Gets the serial number of the Node.
        //
        //Returns:
        //    A string representing the serial number of the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        std::string serial() const;

        //API Function: name
        //    Gets the name of the Node. This is the universal sensor name that should be used for uploading to SensorCloud.
        //    This is the same as calling <WirelessNode::deviceName>.
        //
        //Returns:
        //    The universal sensor name.
        std::string name() const;

        //API Function: microcontroller
        //    Gets the microcontroller of the Node.
        //
        //Returns:
        //    A <WirelessTypes::MicroControllerType> representing the microcontroller of the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::MicroControllerType microcontroller() const;

        //API Function: radioFeatures
        //    Gets the <RadioFeatures> of the Node.
        //
        //Returns:
        //    The <RadioFeatures> of the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        RadioFeatures radioFeatures() const;

        //API Function: dataStorageSize
        //    Gets the number of bytes available for data storage on the Node.
        //
        //Returns:
        //    The number of bytes avaialbe
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        uint64 dataStorageSize() const;

        //API Function: regionCode
        //    Gets the region code currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::RegionCode regionCode() const;

        //API Function: ping
        //    Performs a Long Ping command on the Node to check the communication between the Base Station and the Node.
        //    The response to this command contains the Node and BaseStation RSSI values.
        //
        //Returns:
        //    A <PingResponse> object that can be queried to get details of the ping command's response, including RSSI values.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation
        PingResponse ping();

        //API Function: sleep
        //    Puts the Node into a low power, sleep mode.
        //    This command attempts to ping the node before sending the sleep command, to verify communication.
        //
        //Returns:
        //    true if the sleep command was successful, false otherwise.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        bool sleep();

        //API Function: cyclePower
        //    Cycles the power on the Node. 
        //    Many configuration changes that are applied to the node do not take affect until the power is cycled.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to write an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to reset the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        void cyclePower();

        //API Function: resetRadio
        //    Resets the radio on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to write an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to reset the Node
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        void resetRadio();

        //API Function: changeFrequency
        //    Changes the radio frequency of the Node.
        //    Note: If successful, the Node will be put onto a different frequency than its parent base station.
        //          It is up to the user of MSCL to switch the base station to this frequency if you wish to communicate with it.
        //
        //Parameters:
        //    frequency - The <WirelessTypes::Frequency> to change the Node to.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to write an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to write the value to the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        void changeFrequency(WirelessTypes::Frequency frequency);

        //API Function: setToIdle
        //    Attempts to set the Node to the Idle state.
        //    This will stop the node from sampling or sleeping, and put it into an idle state
        //    so that it may be communicated with (configured, started sampling, etc).
        //    This operation may take several seconds to complete. The returned <SetToIdleStatus> object
        //    may be used to determine the current status of the Set to Idle operation.
        //
        //Returns:
        //    A <SetToIdleStatus> object which can be used to get the current status of the 
        //    ongoing Set to Idle operation, as well as cancel the operation altogether.
        //
        //Exceptions:
        //    - <Error_Communication>: Failed to communicate with the parent BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        SetToIdleStatus setToIdle();

        //API Function: erase
        //    Erases all logged data on the Node.
        //    Note: Erasing the data on the Node may take up to 30 seconds to complete for some devices.
        //          This command will return immediately while the Node is being erased. 
        //          If you wish to check the status of the Erase operation, you can continuously ping the Node. A successful ping means the erase has completed.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to erase the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        void erase();

        //API Function: startNonSyncSampling
        //    Starts the Node in Non-Synchronized Sampling Mode.
        //    This will immediately start the Node sampling, with the current Sampling settings that are applied to the Node.
        //    Note: To start the Node in Synchronized Sampling Mode, use the <SyncSamplingNetwork> class.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        //    - <Error_InvalidNodeConfig>: The Configuration of the Node is not set for Non-Sync Sampling Mode.
        bool startNonSyncSampling();

        //API Function: resendStartSyncSampling
        //  Important!: Use the <SyncSamplingNetwork> to start a Node in Sync Sampling mode.
        //  Advanced Function that sends the Start Sync Sampling command to the individual Node. This command is useful when you have already used the <SyncSamplingNetwork>
        //  object to start a network of Nodes, but need to resend the start command to a Node. For instance, if you had to set a node to idle, and haven't
        //  changed any configuration settings. Note that this command does not enable a beacon, which is needed for a Sync Sampling network to be running.
        //  Warning: This function is rarely what you want to use to start Sync Sampling. Instead, you should create a <SyncSamplingNetwork> object.
        //           Failing to use the SyncSamplingNetwork object can cause the network to be misconfigured, and result in loss of data.
        //
        //Returns:
        //  true if the node is known to have started sampling, false otherwise.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        //    - <Error_InvalidNodeConfig>: The Configuration of the Node is not set for Sync Sampling Mode.
        bool resendStartSyncSampling();

        //API Function: clearHistogram
        //    Clears the Histogram on the Node.
        //    See Also: <NodeFeatures::supportsHistogramConfig>
        //
        //Exceptions:
        //    - <Error_NotSupported>: Histogram configuration is not supported by the Node.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        void clearHistogram();

        //API Function: autoBalance
        //    Performs an Auto Balance command on a specified channel on the Node.
        //    This adjusts the sensor offset for differential channels to affect range.
        //    
        //    See Also: <getHardwareOffset>, <WirelessNodeConfig::hardwareOffset>
        //
        //Parameters:
        //    mask - The <ChannelMask> to perform the auto balance command on.
        //    targetPercent - The percentage (0.0 - 100.0) of the range to balance to (low = 25%, midscale = 50%, high = 75%).
        //
        //Returns:
        //    The <AutoBalanceResult> containing information from the auto balance command.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Autobalance is not supported by the Node or channel mask specified.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        AutoBalanceResult autoBalance(const ChannelMask& mask, float targetPercent);

        //API Function: autoCal_shmLink
        //    Performs automatic calibration for the SHM-Link Wireless Node.
        //    See Also: <NodeFeatures::supportsAutoCal_shm>
        //
        //Returns:
        //    The <AutoCalResult_shmLink> containing the result of the auto cal operation.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Autocal is not supported by the Node or The node is an invalid model for this command.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        AutoCalResult_shmLink autoCal_shmLink();

        //API Function: autoCal_shmLink201
        //    Performs automatic calibration for the SHM-Link-201 Wireless Node.
        //    See Also: <NodeFeatures::supportsAutoCal_shm201>
        //
        //Returns:
        //    The <AutoCalResult_shmLink201> containing the result of the auto cal operation.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Autocal is not supported by the Node or The node is an invalid model for this command.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        AutoCalResult_shmLink201 autoCal_shmLink201();

        //API Function: autoShuntCal
        //  Performs automatic shunt calibration for a specified <ChannelMask> on supported Nodes.
        //
        //Parameters:
        //  mask - The <ChannelMask> to perform the auto cal shunt command on.
        //  commandInfo - The <ShuntCalCmdInfo> to use for the shunt cal operation.
        //
        //Returns:
        //  The <AutoShuntCalResult> containing the result of the auto cal operation.
        //  Note: The resulting slope and offset is not applied to the Node. You need to manually apply it if desired.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Autocal shunt is not supported by the Node or ChannelMask.
        //  - <Error_NodeCommunication>: Failed to communicate with the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        AutoShuntCalResult autoShuntCal(const ChannelMask& mask, const ShuntCalCmdInfo& commandInfo);

        //API Function: poll
        //  Polls the WirelessNode to get a single sweep of calibrated data.
        //
        //Parameters:
        //  chs - The <ChannelMask> to poll data for. Note: if a channel is active that isn't supported by the Node, it will be ignored.
        //
        //Returns:
        //  A <WirelessPollData> map holding the result of the poll.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Autocal shunt is not supported by the Node or ChannelMask.
        //  - <Error_NodeCommunication>: Failed to communicate with the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessPollData poll(const ChannelMask& mask);

        //API Function: readEeprom
        //    Reads a uint16 from the given eeprom location of the node. This may use a page download or a read eeprom command.
        //    If the value stored in the eeprom cache is still valid, this will be returned instead.
        //    Note: This is an advanced command. In most cases you should use the built in commands for reading a Node's configuration options.
        //
        //Parameters:
        //    location - The specific eeprom location to read from
        //
        //Returns:
        //    The uint16 value read from the specified EEPROM location
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported eeprom location.
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        uint16 readEeprom(uint16 location) const;

        //API Function: writeEeprom
        //    Writes a uint16 to the given eeprom location of the node.
        //    If successful, the cache will be updated with the changed value as well.
        //    Note: This is an advanced command. In most cases you should use the built in commands for changing a Node's configuration options.
        //
        //Parameters:
        //    location - The specific eeprom location to write to
        //    value - The uint16 value to write to the eeprom location
        //
        //Exceptions:
        //    - <Error_NotSupported>: Unsupported eeprom location or value.
        //    - <Error_NodeCommunication>: Failed to write the value to the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        void writeEeprom(uint16 location, uint16 value);

        //API Function: getDiagnosticInfo
        //  Performs an immediate request for the Node's Diagnostic Info.
        //  Note: Nodes can also be configured to transmit Diagnostic Info data packets at
        //        a specified Diagnostic Interval via the <WirelessNodeConfig> object.
        //
        //Returns:
        //  A <ChannelData> object containing a <WirelessDataPoint> for each piece of information that was in the Diagnostic Info result.
        //
        //Exceptions:
        //  - <Error_NotSupported>: The Get Diagnostic Info command is not supported.
        //  - <Error_NodeCommunication>: Failed to communicate with the Wireless Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        ChannelData getDiagnosticInfo();

        //API Function: testCommunicationProtocol
        //  Tests if the Node will still be able to communicate after changing the Node's communication protocol.
        //  This is recommended to be used before changing communication protocol as the range can change between protocol modes.
        //  Note: Both the Node and BaseStation will return to the current protocol after this test.
        //
        //Parameters:
        //  protocol - The <WirelessTypes::CommProtocol> to test.
        //
        //Returns:
        //  true if the Node had good communication (responded to pings) in the new protocol.
        //
        //Exceptions:
        //  - <Error_NotSupported>: The given communication protocol, or the test communication protocol function, is not supported by the Node or BaseStation.
        //  - <Error_NodeCommunication>: Failed to communicate with the Wireless Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        bool testCommunicationProtocol(WirelessTypes::CommProtocol protocol);

        //API Function: verifyConfig
        //    Checks whether the settings in the given <WirelessNodeConfig> are ok to be written to the Node.
        //    Options that are set will also be validated against each other. If an option that needs to be validated isn't
        //    currently set, it will be read from the Node.
        //    (ex. if sample rate is set, but sampling mode isn't, the sampling mode will be read from the Node for validating the sample rate)
        //
        //Parameters:
        //    config - The <WirelessNodeConfig> to verify.
        //    outIssues - The <ConfigIssues> that will hold any resulting issues that are found with the configuration.
        //
        //Returns:
        //    true if the configuration is valid. false if the configuration is invalid and outIssues should be checked for more information.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The Node model, or firmware version, is not supported by MSCL.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        bool verifyConfig(const WirelessNodeConfig& config, ConfigIssues& outIssues) const;

        //API Function: applyConfig
        //    Applies a <WirelessNodeConfig> to the Node.
        //    Note: This applies all options that have been set in the <WirelessNodeConfig>. 
        //          Before applying, the options will be validated. It is recommended that you perform
        //          this validation yourself first by using <verifyConfig>.
        //
        //Parameters:
        //    config - The <WirelessNodeConfig> to apply to the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The Node model, or firmware version, is not supported by MSCL.
        //    - <Error_InvalidNodeConfig>: Invalid Configuration. Check the exception for specific details.
        //    - <Error_NodeCommunication>: Failed to write to the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        void applyConfig(const WirelessNodeConfig& config);

        //API Function: getNumDatalogSessions
        //    Reads the number of datalog sessions that are currently stored on the Node.
        //
        //Returns:
        //    The number of datalog sessions that are stored on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        uint16 getNumDatalogSessions() const;

        //API Function: percentFull
        //  Gets the internal datalogging memory percentage that is currently stored on the Node.
        //
        //Returns:
        //  The percentage (0.0 to 100.0) of datalogging memory that is currently used.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        float percentFull() const;

        //API Function: getDefaultMode
        //    Reads the <WirelessTypes::DefaultMode> that is currently set on the Node.
        //
        //Returns:
        //    The default mode that is currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::DefaultMode getDefaultMode() const;

        //API Function: getInactivityTimeout
        //    Reads the user inactivity timeout that is currently set on the Node.
        //    This controls how many seconds before the Node goes to sleep when idle.
        //
        //Returns:
        //    The user inactivity timeout (in seconds) that is currently set on the Node.
        //    Note: A value of 65535 (0xFFFF) disables the inactivity timeout so that the Node never goes to sleep.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        uint16 getInactivityTimeout() const;

        //API Function: getCheckRadioInterval
        //    Reads the check radio interval that is currently set on the Node.
        //    This controls how often the Node wakes up from sleep to check for commands.
        //
        //Returns:
        //    The check radio interval (in seconds) that is currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        uint8 getCheckRadioInterval() const;

        //API Function: getTransmitPower
        //    Reads the <WirelessTypes::TransmitPower> that is currently set on the Node.
        //
        //Returns:
        //    The <WirelessTypes::TransmitPower> that is currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::TransmitPower getTransmitPower() const;

        //API Function: getSamplingMode
        //    Gets the <WirelessTypes::SamplingMode> that is currently set on the Node.
        //
        //Returns:
        //    The <WirelessTypes::SamplingMode> that is currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::SamplingMode getSamplingMode() const;

        //API Function: getActiveChannels
        //    Gets the <ChannelMask> currently set on the Node, representing which channels are enabled and disabled.
        //
        //Returns:
        //    The <ChannelMask> currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        ChannelMask getActiveChannels() const;

        //API Function: getSampleRate
        //    Gets the <WirelessTypes::WirelessSampleRate> currently set on the Node.
        //
        //Returns:
        //    A <WirelessTypes::WirelessSampleRate> that is currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::WirelessSampleRate getSampleRate() const;

        //API Function: getNumSweeps
        //    Gets the number of sweeps currently set on the Node, which affects the duration of sampling if unlimited duration is disabled, 
        //    or the duration of each burst if the sampling mode is Sync Sampling Burst.
        //
        //Returns:
        //    The number of sweeps currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        uint32 getNumSweeps() const;

        //API Function: getUnlimitedDuration
        //    Gets whether or not unlimited sampling duration is enabled on the Node.
        //
        //Returns:
        //    true if unlimited sampling duration is enabled on the Node, false if it is disabled.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        bool getUnlimitedDuration() const;

        //API Function: getDataFormat
        //    Gets the <WirelessTypes::DataFormat> that is currently set on the Node.
        //
        //Returns:
        //    The <WirelessTypes::DataFormat> currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::DataFormat getDataFormat() const;

        //API Function: getDataCollectionMethod
        //    Gets the <WirelessTypes::DataCollectionMethod> that is currently set on the Node, representing how the data will be collected.
        //    Note: this has no affect if the sampling mode is Armed Datalogging, as this mode only operates in "log only".
        //
        //Returns:
        //    The <WirelessTypes::DataCollectionMethod> currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::DataCollectionMethod getDataCollectionMethod() const;

        //API Function: getTimeBetweenBursts
        //    Gets the amount of time between each burst currently set on the Node. 
        //    This is only used if the sampling mode is Synchronized Sampling Burst.
        //
        //Returns:
        //    A <TimeSpan> representing the amount of time between each burst currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Burst Sampling mode is not supported by the Node.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        TimeSpan getTimeBetweenBursts() const;

        //API Function: getLostBeaconTimeout
        //    Gets the lost beacon timeout, in minutes, currently set on the Node.
        //    If the Node is Sync Sampling and loses the beacon for a length of time
        //    greater than this value, then the node drops into a sleep mode. The Node
        //    will re-enter sync sampling within 2 minutes of the beacon reappearing.
        //    Note: A value of 0 means the lost beacon timeout is disabled.
        //    See Also: <NodeFeatures::supportsLostBeaconTimeout>
        //
        //Returns:
        //    The lost beacon timeout, in minutes, currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        uint16 getLostBeaconTimeout() const;

        //API Function: getInputRange
        //    Reads the Input Range of the specified <ChannelMask> currently set on the Node.
        //    See Also: <NodeFeatures::channelGroups>, <NodeFeatures::supportsInputRange>
        //
        //Parameters:
        //    mask - The <ChannelMask> of the Input Range to read.
        //
        //Returns:
        //    The <WirelessTypes::InputRange> currently set on the Node for the <ChannelMask>.
        //    Note: if the input range in eeprom is not supported, <WirelessTypes::InputRange::range_invalid> will be returned.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Input range is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::InputRange getInputRange(const ChannelMask& mask) const;

        //API Function: getHardwareOffset
        //    Reads the hardware offset of the specified <ChannelMask> currently set on the Node.
        //    See Also: <NodeFeatures::channelGroups>, <NodeFeatures::supportsHardwareOffset>
        //
        //Parameters:
        //    mask - The <ChannelMask> of the hardware offset to read.
        //
        //Returns:
        //    The hardware offset currently set on the Node for the <ChannelMask>.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Hardware offset is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        uint16 getHardwareOffset(const ChannelMask& mask) const;

        //API Function: getAntiAliasingFilter
        //    Reads the Anti-Aliasing Filter of the specified <ChannelMask> currently set on the Node.
        //    See Also: <NodeFeatures::channelGroups>, <NodeFeatures::supportsAntiAliasingFilter>
        //
        //Parameters:
        //    mask - The <ChannelMask> of the anti-aliasing filter to read.
        //
        //Returns:
        //    The Anti-Aliasing <WirelessTypes::Filter> currently set on the Node for the <ChannelMask>.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Anti-Aliasing Filter is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::Filter getAntiAliasingFilter(const ChannelMask& mask) const;

        //API Function: getCfcFilterConfiguration
        //    Reads the channel frequency class filter option set on the Node.
        //    See Also: <NodeFeatures::supportsCfcFilterConfiguration>
        //
        //Returns:
        //    The <WirelessTypes::ChannelFrequencyClass> currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: High-Pass Filter is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::ChannelFrequencyClass getCfcFilterConfiguration() const;

        //API Function: getLowPassFilter
        //    Reads the Low-Pass Filter of the specified <ChannelMask> currently set on the Node.
        //    See Also: <NodeFeatures::channelGroups>, <NodeFeatures::supportsLowPassFilter>
        //
        //Parameters:
        //    mask - The <ChannelMask> of the low-pass filter to read.
        //
        //Returns:
        //    The Low-Pass <WirelessTypes::Filter> currently set on the Node for the <ChannelMask>.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Low-Pass Filter is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::Filter getLowPassFilter(const ChannelMask& mask) const;

        //API Function: getHighPassFilter
        //    Reads the High-Pass Filter of the specified <ChannelMask> currently set on the Node.
        //    See Also: <NodeFeatures::channelGroups>, <NodeFeatures::supportsHighPassFilter>
        //
        //Parameters:
        //    mask - The <ChannelMask> of the high-pass filter to read.
        //
        //Returns:
        //    The <WirelessTypes::HighPassFilter> currently set on the Node for the <ChannelMask>.
        //
        //Exceptions:
        //    - <Error_NotSupported>: High-Pass Filter is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::HighPassFilter getHighPassFilter(const ChannelMask& mask) const;

        //API Function: getDebounceFilter
        //  Reads the Debounce Filter of the specified <ChannelMask> currently set on the Node.
        //  See Also: <NodeFeatures::channelGroups>, <NodeFeatures::supportsDebounceFilter>
        //
        //Parameters:
        //  mask - The <ChannelMask> of the debounce filter to read.
        //
        //Returns:
        //  The debounce filter currently set on the Node, in milliseconds.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Debounce Filter is not supported for the provided <ChannelMask>.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        uint16 getDebounceFilter(const ChannelMask& mask) const;

        //API Function: getPullUpResistor
        //    Gets whether or not the pull-up resistor is enabled on the Node.
        //
        //Parameters:
        //  mask - The <ChannelMask> of the pull-up resistor to read.
        //
        //Returns:
        //    true if the pull-up resistor is enabled on the Node, false if it is disabled.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        bool getPullUpResistor(const ChannelMask& mask) const;

        //API Function: getSensorOutputMode
        //  Gets the <WirelessTypes::SensorOutputMode> currently set on the Node.
        //
        //Returns:
        //  The <WirelessTypes::SensorOutputMode> currently set on the Node.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Attempted to read an unsupported option.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::SensorOutputMode getSensorOutputMode() const;

        //API Function: getGaugeFactor
        //    Reads the gauge factor of the specified <ChannelMask> currently set on the Node.
        //    See Also: <NodeFeatures::channelGroups>, <NodeFeatures::supportsGaugeFactor>
        //
        //Parameters:
        //    mask - The <ChannelMask> of the gauge factor to read.
        //
        //Returns:
        //    The gauge factor currently set on the Node for the <ChannelMask>.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Gauge Factor is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        float getGaugeFactor(const ChannelMask& mask) const;

        //API Function: getExcitationVoltage
        //  Reads the Excitation <WirelessTypes::Voltage> currently set on the Node.
        //
        //Returns:
        //  The <WirelessTypes::Voltage> currently set on the Node.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Excitation Voltage is not supported.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::Voltage getExcitationVoltage() const;

        //API Function: getAdcVoltageRef
        //  Reads the ADC <WirelessTypes::Voltage> Reference of the Node.
        //
        //Returns:
        //  The ADC <WirelessTypes::Voltage> Reference of the Node.
        //
        //Exceptions:
        //  - <Error_NotSupported>: ADC Voltage is not supported.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::Voltage getAdcVoltageRef() const;

        //API Function: getGainAmplifierVoltageRef
        //  Reads the Gain Amplifier <WirelessTypes::Voltage> Reference of the Node.
        //
        //Returns:
        //  The Gain Amplifier <WirelessTypes::Voltage> Reference of the Node.
        //
        //Exceptions:
        //  - <Error_NotSupported>: ADC Voltage is not supported.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::Voltage getGainAmplifierVoltageRef() const;

        //API Function: getGaugeResistance
        //  Reads the gauge resistance currently set on the Node.
        //  See Also: <NodeFeatures::supportsGaugeResistance>
        //
        //Returns:
        //  The gauge resistance currently set on the Node.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Gauge Resistance is not supported.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        uint16 getGaugeResistance() const;

        //API Function: getNumActiveGauges
        //  Reads the Number of Active Gauges currently set on the Node.
        //  See Also: <NodeFeatures::supportsNumActiveGauges>
        //
        //Returns:
        //  The Number of Active Gauges currently set on the Node.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Number of Active Gauges is not supported.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        uint16 getNumActiveGauges() const;

        //API Function: getLowBatteryThreshold
        //  Reads the threshold at which the low battery diagnostic flag is sent.
        //
        //Returns:
        //  The low battery threshold, in Volts.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Low Battery Threshold is not supported.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        float getLowBatteryThreshold() const;

        //API Function: getLinearEquation
        //    Gets the linear equation of the specified <ChannelMask> currently set on the Node.
        //
        //Parameters:
        //    mask - The <ChannelMask> of the linear equation to read.
        //
        //Returns:
        //    A <LinearEquation> object representing the linear equation that is applied to this <ChannelMask>.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Linear Equation is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        LinearEquation getLinearEquation(const ChannelMask& mask) const;

        //API Function: getUnit
        //    Reads the unit of the specified <ChannelMask> currently set on the Node.
        //    Note: This unit is just used for reference (such as when downloading logged data) and does not affect the actual data value.
        //
        //Parameters:
        //    mask - The <ChannelMask> of the unit to read.
        //
        //Returns:
        //    The <WirelessTypes::CalCoef_Unit> that is applied to this <ChannelMask>
        //
        //Exceptions:
        //    - <Error_NotSupported>: Unit is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::CalCoef_Unit getUnit(const ChannelMask& mask) const;

        //Function: getEquationType
        //    Reads the <WirelessTypes::CalCoef_EquationType> of the specified <ChannelMask> currently set on the Node.
        //
        //Parameters:
        //    mask - The <ChannelMask> of the equation type to read.
        //
        //Returns:
        //    The <WirelessTypes::CalCoef_EquationType> currently set on the Node for this <ChannelMask>.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The Equation Type setting is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::CalCoef_EquationType getEquationType(const ChannelMask& mask) const;

        //API Function: getFactoryCalibrationLinearEq
        //    Gets the factory-calibrated linear equation for the specified <ChannelMask>.
        //
        //Parameters:
        //    mask - The <ChannelMask> of the linear equation to read.
        //
        //Returns:
        //    A <LinearEquation> object representing the linear equation that was set during factory calibration.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Linear Equation is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        LinearEquation getFactoryCalibrationLinearEq(const ChannelMask& mask) const;

        //API Function: getFactoryCalibrationUnit
        //    Reads the factory calibration unit for the specified <ChannelMask>.
        //
        //Parameters:
        //    mask - The <ChannelMask> of the unit to read.
        //
        //Returns:
        //    The <WirelessTypes::CalCoef_Unit> used during factory calibration of this <ChannelMask>
        //
        //Exceptions:
        //    - <Error_NotSupported>: Unit is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::CalCoef_Unit getFactoryCalibrationUnit(const ChannelMask& mask) const;

        //Function: getFactoryCalibrationEqType
        //    Reads the factory calibration <WirelessTypes::CalCoef_EquationType> for the specified <ChannelMask>.
        //
        //Parameters:
        //    mask - The <ChannelMask> of the equation type to read.
        //
        //Returns:
        //    The <WirelessTypes::CalCoef_EquationType> set during factory calibration for this <ChannelMask>.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The Equation Type setting is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::CalCoef_EquationType getFactoryCalibrationEqType(const ChannelMask& mask) const;

        //API Function: getFilterSettlingTime
        //    Gets the filter settling time of the specified <ChannelMask> currently set on the Node.
        //    See Also: <NodeFeatures::channelGroups>
        //
        //Parameters:
        //    mask - The <ChannelMask> of the filter settling time to read.
        //
        //Returns:
        //    The <WirelessTypes::SettlingTime> currently set on the Node for the <ChannelMask>.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Filter Settling Time is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::SettlingTime getFilterSettlingTime(const ChannelMask& mask) const;

        //API Function: getThermocoupleType
        //    Reads the <WirelessTypes::ThermocoupleType> of the specified <ChannelMask> currently set on the Node.
        //    See Also: <NodeFeatures::channelGroups>
        //
        //Parameters:
        //    mask - The <ChannelMask> of the thermocouple type to read.
        //
        //Returns:
        //    The <WirelessTypes::ThermocoupleType> currently set on the Node for the <ChannelMask>.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Thermocouple Type is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::ThermocoupleType getThermocoupleType(const ChannelMask& mask) const;

        //API Function: getTempSensorOptions
        //    Reads the <TempSensorOptions> of the specified <ChannelMask> currently set on the Node.
        //    See Also: <NodeFeatures::channelGroups>
        //
        //Parameters:
        //    mask - The <ChannelMask> indication which channel(s) the TempSensorOptions should be read for.
        //
        //Returns:
        //    The <TempSensorOptions> currently set on the Node for the <ChannelMask>.
        //
        //Exceptions:
        //    - <Error_NotSupported>: TempSensorOptions are not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        TempSensorOptions getTempSensorOptions(const ChannelMask& mask) const;

        //API Function: getFatigueOptions
        //    Reads the <FatigueOptions> currently set on the Node.
        //    See Also: <NodeFeatures::supportsFatigueConfig>
        //
        //Returns:
        //    The <FatigueOptions> currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: FatigueOptions configuration is not supported by this Node.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        FatigueOptions getFatigueOptions() const;

        //API Function: getHistogramOptions
        //    Reads the <HistogramOptions> currently set on the Node.
        //    See Also: <NodeFeatures::supportsHistogramConfig>
        //
        //Returns:
        //    The <HistogramOptions> currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: HistogramOptions configuration is not supported by this Node.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        HistogramOptions getHistogramOptions() const;

        //API Function: getActivitySense
        //    Reads the <ActivitySense> options currently set on the Node.
        //    See Also: <NodeFeatures::supportsActivitySense>
        //
        //Returns:
        //    The <ActivitySense> options currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: ActivitySense configuration is not supported by this Node.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        ActivitySense getActivitySense() const;

        //API Function: getEventTriggerOptions
        //  Reads the <EventTriggerOptions> currently set on the Node.
        //  See Also: <NodeFeatures::supportsEventTrigger>
        //
        //Returns:
        //  The <EventTriggerOptions> currently set on the Node.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Event Triggering is not supported by this Node.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        EventTriggerOptions getEventTriggerOptions() const;

        //API Function: getDiagnosticInterval
        //  Reads the interval (in seconds) at which the diagnostic info is configured to be sent.
        //  See Also: <NodeFeatures::supportsDiagnosticInfo>
        //
        //Returns:
        //  The interval (in seconds) at which the diagnostic info is sent. 0 is disabled.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Diagnostic Info is not supported by this Node.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        uint16 getDiagnosticInterval() const;

        //API Function: getStorageLimitMode
        //  Reads the <WirelessTypes::StorageLimitMode> that the Node is configured for.
        //  This determines what happens when the datalogging storage limit is reached on the Node.
        //
        //Returns:
        //  The <WirelessTypes::StorageLimitMode> that the Node is configured for.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Storage Limit Mode (or datalogging) is not supported by this Node.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::StorageLimitMode getStorageLimitMode() const;

        //API Function: getSensorDelay
        //  Reads the sensor delay (in microseconds) that is currently set on the Node.
        //  Note: A value of <WirelessNodeConfig::SENSOR_DELAY_ALWAYS_ON> indicates that the sensor is always on.
        //
        //Returns:
        //  The sensor delay (in microseconds) that the sensor delay is set for. 
        //  This will be <WirelessNodeConfig::SENSOR_DELAY_ALWAYS_ON> if the sensor is set to Always On.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Sensor Delay is not supported by this Node.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        uint32 getSensorDelay() const;

        //API Function: getDataMode
        //  Reads the <WirelessTypes::DataMode> that is currently set on the Node.
        //
        //Returns:
        //  The <WirelessTypes::DataMode> currently set on the Node.
        //
        //Exceptions:
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::DataMode getDataMode() const;

        //API Function: getDerivedDataRate
        //  Reads the <WirelessTypes::WirelessSampleRate> for all Derived Data Channels that is currently set on the Node.
        //
        //Returns:
        //  A <WirelessTypes::WirelessSampleRate> for all Derived Data Channels that is currently set on the Node.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Derived Channels are not supported by this Node.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::WirelessSampleRate getDerivedDataRate() const;

        //API Function: getDerivedChannelMask
        //  Reads the <ChannelMask> for an individual <WirelessTypes::DerivedCategory> that is currently set on the Node.
        //  This represents which of the actual Node's channels are set to be mapped to derived channels.
        //  For example, if the mask for RMS has ch1 and ch3 active, ch1RMS and ch3RMS channels will be output.
        //
        //Parameters:
        //  category - The <WirelessTypes::DerivedCategory> to read the channel mask for.
        //
        //Returns:
        //  A <ChannelMask> that is currently set on the Node for the requested <WirelessTypes::DerivedCategory>.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Derived Channels are not supported by this Node.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        ChannelMask getDerivedChannelMask(WirelessTypes::DerivedCategory category) const;

        //API Function: getDerivedVelocityUnit
        //  Reads the <WirelessTypes::DerivedVelocityUnit> which indicates which unit the Velocity derived channel is set to.
        //
        //Returns:
        //  A <WirelessTypes::DerivedVelocityUnit>.
        //
        //Exceptions:
        //  - <Error_NotSupported>: The Derived Velocity channel is not supported by this Node.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::DerivedVelocityUnit getDerivedVelocityUnit() const;
    };
}