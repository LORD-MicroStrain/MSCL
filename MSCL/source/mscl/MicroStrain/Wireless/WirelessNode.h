/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "Commands/AutoCalResult.h"
#include "Commands/LongPing.h"
#include "Configuration/ActivitySense.h"
#include "Configuration/ConfigIssue.h"
#include "Configuration/EventTriggerOptions.h"
#include "Configuration/FatigueOptions.h"
#include "Configuration/HistogramOptions.h"
#include "mscl/Version.h"
#include "mscl/BitMask.h"
#include "ChannelMask.h"
#include "BaseStation.h"
#include "RadioFeatures.h"
#include "WirelessModels.h"
#include "LinearEquation.h"

namespace mscl
{
    //forward declarations
    class WirelessNode_Impl;
    class NodeFeatures;
    class NodeEepromHelper;
    class WirelessNodeConfig;
    class WirelessProtocol;

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
        //    base - the node's parent Base Station
        WirelessNode(uint16 nodeAddress, const BaseStation& basestation);

        //Destructor: ~WirelessNode
        //    Destroys a WirelessNode object
        virtual ~WirelessNode(){};

    private:
        //Variable: m_impl
        //    The <WirelessNode_Impl> class that contains all the implementation logic for the WirelessNode class.
        std::shared_ptr<WirelessNode_Impl> m_impl;

    public:
#ifndef SWIG
        //changes/sets the underlying implementation for this class.
        void setImpl(std::shared_ptr<WirelessNode_Impl> impl);    

        //gets a reference to the NodeEepromHelper for the Node.
        NodeEepromHelper& eepromHelper() const;    

        //gets a reference to the WirelessProtocol for the Node.
        const WirelessProtocol& protocol() const;
#endif

        //API Function: deviceName
        //    Static function for creating the universal sensor name that should be used for SensorCloud.
        //
        //Parameters:
        //    nodeAddress - The node address of the wireless node. This should be identical to calling the <nodeAddress> function on a <WirelessNode> object.
        //
        //Returns:
        //    The universal sensor name.
        static std::string deviceName(uint16 nodeAddress);

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
        //    Sets the number of retry attempts for reading and writing with the Node.
        //    By default, the number of retries is 0.
        //    Note:    The timeout that is set per command will be per read and write attempt, meaning
        //            this retry number is multiplied by the timeout for your overall timeout.
        //
        //Parameters:
        //    numRetries - The number of retries to set for all reading and writing with the Node.
        void readWriteRetries(uint8 numRetries);

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

        //API Function: nodeAddress
        //    Gets the node address of the Node.
        //
        //Returns:
        //    The node address of the Node
        uint16 nodeAddress() const;

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

        //API Function: quickPing
        //    Performs a Quick Ping (Short Ping) command on the Node.
        //    The Base Station itself responds with a quick success/fail on the Node.
        //    Note: Use the standard <ping> command instead of this if you want to obtain RSSI values.
        //
        //Returns:
        //    true if the quick ping was successful, false otherwise.
        //
        //Exceptions:
        //    - <Error_Communication>: Failed to determine the protocol version of the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        bool quickPing();

        //API Function: ping
        //    Performs a Long Ping command on the Node to check the communication between the Base Station and the Node.
        //    The response to this command contains the Node and BaseStation RSSI values.
        //    Note: You may want to use the <quickPing> command instead of this if RSSI values are not of importance.
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
        //    - <Error_NodeCommunication>: Failed to write the value to the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        void cyclePower();

        //API Function: resetRadio
        //    Resets the radio on the Node. 
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to write an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to write the value to the Node.
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
        //    This command may take up to 2 minutes. The returned <SetToIdleStatus> object
        //    may be used to determine the current status of the Set to Idle operation.
        //
        //Returns:
        //    A <SetToIdleStatus> object which can be used to get the current status of the 
        //    ongoing Set to Idle operation, as well as cancel the operation altogether.
        //
        //Exceptions:
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
        void startNonSyncSampling();

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
        //    See Also: <NodeFeatures::supportsAutoCal>
        //
        //Returns:
        //    The <AutoCalResult_shmLink> containing the result of the auto cal operation.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Autocal configuration is not supported by the Node or The node is an invalid model for this command.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        AutoCalResult_shmLink autoCal_shmLink();

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

        //API Function: getHardwareGain
        //    Reads the hardware gain of the specified <ChannelMask> currently set on the Node.
        //    See Also: <NodeFeatures::channelGroups>, <NodeFeatures::supportsHardwareGain>
        //
        //Parameters:
        //    mask - The <ChannelMask> of the hardware gain to read.
        //
        //Returns:
        //    The hardware gain currently set on the Node for the <ChannelMask>.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Hardware gain is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        double getHardwareGain(const ChannelMask& mask) const;

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

        //API Function: getLowPassFilter
        //    Reads the Low Pass Filter of the specified <ChannelMask> currently set on the Node.
        //    See Also: <NodeFeatures::channelGroups>, <NodeFeatures::supportsLowPassFilter>
        //
        //Parameters:
        //    mask - The <ChannelMask> of the low pass filter to read.
        //
        //Returns:
        //    The Low Pass <WirelessTypes::Filter> currently set on the Node for the <ChannelMask>.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Low Pass Filter is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::Filter getLowPassFilter(const ChannelMask& mask) const;

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
        //    The <WirelessTypes::ThermocoupleType> currently set on the Node for the <ChannelMask.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Thermocouple Type is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::ThermocoupleType getThermocoupleType(const ChannelMask& mask) const;

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
        //  Rates the <WirelessTypes::StorageLimitMode> that the Node is configured for.
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
    };

}
