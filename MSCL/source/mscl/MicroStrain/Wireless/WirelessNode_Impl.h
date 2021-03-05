/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "BaseStation.h"
#include "WirelessModels.h"
#include "WirelessChannel.h"
#include "WirelessDataPoint.h"
#include "RadioFeatures.h"
#include "mscl/Version.h"
#include "Commands/AutoBalanceResult.h"
#include "Commands/AutoCalResult.h"
#include "Commands/WirelessProtocol.h"
#include "Configuration/ActivitySense.h"
#include "Configuration/ConfigIssue.h"
#include "Configuration/DataModeMask.h"
#include "Configuration/EventTriggerOptions.h"
#include "Configuration/FatigueOptions.h"
#include "Configuration/HistogramOptions.h"
#include "Configuration/NodeEeprom.h"
#include "Configuration/NodeEepromHelper.h"
#include "Configuration/TempSensorOptions.h"
#include "Features/NodeFeatures.h"

namespace mscl
{
    //forward declarations
    struct ShuntCalCmdInfo;
    class WirelessNode;
    class WirelessNodeConfig;

    //Class: WirelessNode_Impl
    //    Contains the implementation logic for a WirelessNode.
    //    Most WirelessNode commands call these commands.
    class WirelessNode_Impl
    {
        friend class WirelessProtocol;

    public:
        WirelessNode_Impl() = delete;                                       //default constructor disabled
        WirelessNode_Impl(const WirelessNode_Impl&) = delete;               //copy constructor disabled
        WirelessNode_Impl& operator=(const WirelessNode_Impl&) = delete;    //assignment operator disabled

    public:
        //Constructor: WirelessNode_Impl
        //    Creates a WirelessNode_Impl object.
        //
        //Parameters:
        //    nodeAddress - the node address of the node
        //    basestation - the node's parent Base Station
        WirelessNode_Impl(NodeAddress nodeAddress, const BaseStation& basestation);

        virtual ~WirelessNode_Impl() {}

    protected:
        //Variable: m_address
        //    The address of the Node.
        NodeAddress m_address;

        //Variable: m_baseStation
        //    The Node's parent BaseStation.
        BaseStation m_baseStation;

        //Variable: m_eepromSettings
        //    The eeprom settings to use for the <NodeEeprom> object.
        NodeEepromSettings m_eepromSettings;

        //Variable: m_protocolMutex
        //    The mutex used when determining the device protocol.
        mutable std::recursive_mutex m_protocolMutex;

        //Variable: m_protocol_lxrs
        //    The <WirelessProtocol> containing all of the protocol commands and info for this Node when the Node is in LXRS radio mode.
        mutable std::unique_ptr<WirelessProtocol> m_protocol_lxrs;

        //Variable: m_protocol_lxrsPlus
        //    The <WirelessProtocol> containing all of the protocol commands and info for this Node when the Node is in LXRS+ radio mode.
        mutable std::unique_ptr<WirelessProtocol> m_protocol_lxrsPlus;

        //Variable: m_eeprom
        //    The <NodeEeprom> that handles reading and writing eeprom values with the Node and eeprom cache.
        mutable std::unique_ptr<NodeEeprom> m_eeprom;

        //Variable: m_eepromHelper
        //    The <NodeEepromHelper> used for high level reads and writes on the Node.
        mutable std::unique_ptr<NodeEepromHelper> m_eepromHelper;

        //Variable: m_features
        //    The <NodeFeatures> containing the features for this Node.
        mutable std::unique_ptr<NodeFeatures> m_features;

    protected:
        //Function: determineProtocols
        //    Determines the <WirelessProtocol>s to use based on the Node's ASPP version.
        //    All <WirelessProtocol> member variables will be updated.
        void determineProtocols() const;

        //Function: eeprom
        //    Gets a reference to the <NodeEeprom> for this Node.
        virtual NodeEeprom& eeprom() const;

        //Function: wirelessProtocol
        //  Gets a reference to the <WirelessProtocol> for this Node for the parent BaseStation's current comm protocol setting.
        const WirelessProtocol& wirelessProtocol();

    public:
        //Function: eeHelper
        //    Gets a reference to the <NodeEepromHelper> for this Node.
        NodeEepromHelper& eeHelper() const;

        //Function: features
        //    Gets a reference to the <NodeFeatures> for this Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The Node model is not supported by MSCL.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual const NodeFeatures& features() const;

        //Function: protocol
        //    Gets a reference to the <WirelessProtocol> for this Node.
        //    Note: This requires communicating to the Node if creating the protocol for the first time.
        //
        //Parameters:
        //  commProtocol - The <WirelessTypes::CommProtocol> to get the protocol for.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual const WirelessProtocol& protocol(WirelessTypes::CommProtocol commProtocol) const;

        //Function: lastCommunicationTime
        //    Gets the <Timestamp> for the last time MSCL communicated with the Node.
        const Timestamp& lastCommunicationTime() const;

        //Function: lastDeviceState
        //  Gets the last known <DeviceState> for the Node.
        DeviceState lastDeviceState() const;

        //Function: setBaseStation
        //    Sets the node's parent Base Station, which will perform all communication with the Node.
        //
        //Parameters:
        //    basestation - the <BaseStation> object to be assigned to the Node, which will perform all communication with the Node.
        void setBaseStation(const BaseStation& basestation);

        //Function: getBaseStation
        //    Gets a reference to the <BaseStation> that is assigned to this Node.
        BaseStation& getBaseStation();

        //Function: hasBaseStation
        //    Checks whether the given <BaseStation> is the same <BaseStation> that is assigned to this Node.
        //
        //Parameters:
        //    basestation - The <BaseStation> to check if it is the same as this Node's parent <BaseStation>.
        //
        //Returns:
        //    true if the basestation is the same as this Node's parent <BaseStation>, false if it is different.
        bool hasBaseStation(const BaseStation& basestation) const;

        //Function: useGroupRead
        //    Enables or disables the use of group eeprom read when trying to read a single value (enabled by default).
        //
        //Parameters:
        //    useGroup - Whether the group eeprom read commands can be used (true) or whether to restrict to single eeprom reads (false).
        void useGroupRead(bool useGroup);

        //Function: setReadWriteRetries
        //    Sets the number of retry attempts for reading and writing with the Node.
        //
        //Parameters:
        //    numRetries - The number of retries to set for all reading and writing with the Node.
        void setReadWriteRetries(uint8 numRetries);

        //Function: getReadWriteRetries
        //    Gets the number of retry attempts for reading and writing config options with the Node.
        uint8 getReadWriteRetries() const;

        //Function: useEepromCache
        //    Sets whether or not to utilize the eeprom cache when configuring this Node (default of enabled).
        //
        //Parameters:
        //    useCache - whether the eeprom cache should be used (true) or not (false).
        void useEepromCache(bool useCache);

        //Function: clearEepromCache
        //    Clears the eeprom cache for this Node.
        void clearEepromCache();

        void clearEepromCacheLocation(uint16 location);

        void updateEepromCacheFromNodeDiscovery(const NodeDiscovery& nodeDisovery);

        //Function: getEepromCache
        //  Gets a copy of the eeprom cache as a <WirelessTypes::EepromMap>.
        WirelessTypes::EepromMap getEepromCache() const;

        //Function: nodeAddress
        //    Gets the node address of the Node.
        //
        //Returns:
        //    The node address of the Node.
        NodeAddress nodeAddress() const;

        //Function: frequency
        //    Gets the <WirelessTypes::Frequency> that the Node is believed to be on.
        //    If the frequency is unknown, it will be read from Eeprom.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::Frequency frequency() const;

        //Function: communicationProtocol
        //  Gets the <WirelessTypes::CommProtocol> that the Node is currently set to use.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::CommProtocol communicationProtocol() const;

        //Function: firmwareVersion
        //    Gets the firmware <Version> of the Node. 
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual Version firmwareVersion() const;

        //Function: model
        //    Gets the <WirelessModels::NodeModel> of the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual WirelessModels::NodeModel model() const;

        //Function: serial
        //    Gets the serial number of the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual std::string serial() const;

        //Function: microcontroller
        //    Gets the <WirelessTypes::MicroControllerType> of the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual WirelessTypes::MicroControllerType microcontroller() const;

        //Function: radioFeatures
        //    Gets the <RadioFeatures> of the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual RadioFeatures radioFeatures() const;

        //Function: dataStorageSize
        //    Gets the number of bytes available for data storage on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual uint64 dataStorageSize() const;

        //Function: regionCode
        //    Gets the region code currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual WirelessTypes::RegionCode regionCode() const;

        //Function: verifyConfig
        //    Checks whether the settings in the given <WirelessNodeConfig> are ok to be written to the Node.
        //    Options that are set will also be validated against each other. If an option that needs to be validated isn't
        //    currently set, it will be read from the Node.
        //
        //Parameters:
        //    config - The <WirelessNodeConfig> to verify the configuration for.
        //    outIssues - The <ConfigIssues> that will hold any resulting issues that are found with the configuration.
        //
        //Returns:
        //    true if the configuration is valid. false if the configuration is invalid and outIssues should be checked for more information.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        bool verifyConfig(const WirelessNodeConfig& config, ConfigIssues& outIssues) const;

        //Function: applyConfig
        //    Applies a <WirelessNodeConfig> to the Node.
        //
        //Parameters:
        //    config - The <WirelessNodeConfig> to apply to the Node.
        //
        //Exceptions:
        //    - <Error_InvalidNodeConfig>: Invalid Configuration. Check the exception for specific details.
        //    - <Error_NotSupported>: Attempted to write an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to write to the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        void applyConfig(const WirelessNodeConfig& config);

        //Function: getNumDatalogSessions
        //    Reads the number of datalog sessions that are currently stored on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual uint16 getNumDatalogSessions();

        //Function: percentFull
        //  Gets the internal datalogging memory percentage that is currently stored on the Node.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual float percentFull();

        //Function: getDefaultMode
        //    Reads the <WirelessTypes::DefaultMode> that is currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::DefaultMode getDefaultMode() const;

        //Function: getInactivityTimeout
        //    Reads the user inactivity timeout (in seconds) that is currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        uint16 getInactivityTimeout() const;

        //Function: getCheckRadioInterval
        //    Reads the check radio interval that is currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        uint8 getCheckRadioInterval() const;

        //Function: getTransmitPower
        //    Reads the <WirelessTypes::TransmitPower> that is currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::TransmitPower getTransmitPower() const;

        //Function: getSamplingMode
        //    Gets the <WirelessTypes::SamplingMode> that is currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::SamplingMode getSamplingMode() const;

        //Function: getActiveChannels
        //    Gets the <ChannelMask> currently set on the Node, representing which channels are enabled and disabled.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        ChannelMask getActiveChannels() const;

        //Function: getSampleRate
        //    Gets the <WirelessTypes::WirelessSampleRate> currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::WirelessSampleRate getSampleRate() const;

        //Function: getNumSweeps
        //    Gets the number of sweeps currently set on the Node, which affects the duration of sampling if unlimited duration is disabled, 
        //    or the duration of each burst if the sampling mode is Sync Sampling Burst.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        uint32 getNumSweeps() const;

        //Function: getUnlimitedDuration
        //    Gets whether or not unlimited sampling duration is enabled on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        bool getUnlimitedDuration() const;

        //Function: getDataFormat
        //    Gets the <WirelessTypes::DataFormat> that is currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::DataFormat getDataFormat() const;

        //Function: getDataCollectionMethod
        //    Gets the <WirelessTypes::DataCollectionMethod> that is currently set on the Node, representing how the data will be collected.
        //    Note: this has no affect if the sampling mode is Armed Datalogging, as this mode only operates in "log only".
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::DataCollectionMethod getDataCollectionMethod() const;

        //Function: getTimeBetweenBursts
        //    Gets the amount of time between each burst currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Burst Sampling mode is not supported by the Node.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        TimeSpan getTimeBetweenBursts() const;

        //Function: getLostBeaconTimeout
        //    Gets the lost beacon timeout, in minutes, currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        uint16 getLostBeaconTimeout() const;

        //Function: getPullUpResistor
        //    Gets whether or not the pull-up resistor is enabled on the Node.
        //
        //Parameters:
        //    mask - The <ChannelMask> of the pull-up resistor to read.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        bool getPullUpResistor(const ChannelMask& mask) const;

        //Function: getSensorOutputMode
        //  Gets the <WirelessTypes::SensorOutputMode> currently set on the Node.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Attempted to read an unsupported option.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::SensorOutputMode getSensorOutputMode() const;

        //Function: getInputRange
        //    Reads the input range of the specified <ChannelMask>.
        //
        //Parameters:
        //    mask - The <ChannelMask> of the input range to read.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Input Range is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::InputRange getInputRange(const ChannelMask& mask) const;

        //Function: getHardwareOffset
        //    Reads the hardware offset of the specified <ChannelMask> currently set on the Node.
        //
        //Parameters:
        //    mask - The <ChannelMask> of the hardware offset to read.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Hardware offset is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        uint16 getHardwareOffset(const ChannelMask& mask) const;

        //Function: getAntiAliasingFilter
        //    Reads the Anti-Aliasing Filter of the specified <ChannelMask> currently set on the Node.
        //
        //Parameters:
        //    mask - The <ChannelMask> of the filter to read.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Anti-Aliasing Filter is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::Filter getAntiAliasingFilter(const ChannelMask& mask) const;

        //Function: getLowPassFilter
        //    Reads the Low-Pass Filter of the specified <ChannelMask> currently set on the Node.
        //
        //Parameters:
        //    mask - The <ChannelMask> of the low-pass filter to read.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Low-Pass Filter is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::Filter getLowPassFilter(const ChannelMask& mask) const;

        //Function: getHighPassFilter
        //    Reads the High-Pass Filter of the specified <ChannelMask> currently set on the Node.
        //
        //Parameters:
        //    mask - The <ChannelMask> of the high-pass filter to read.
        //
        //Exceptions:
        //    - <Error_NotSupported>: High-Pass Filter is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::HighPassFilter getHighPassFilter(const ChannelMask& mask) const;

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

        //Function: getDebounceFilter
        //  Reads the Debounce Filter of the specified <ChannelMask> currently set on the Node.
        //
        //Parameters:
        //  mask - The <ChannelMask> of the debounce filter to read.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Debounce Filter is not supported for the provided <ChannelMask>.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        uint16 getDebounceFilter(const ChannelMask& mask) const;

        //Function: getGaugeFactor
        //    Reads the gauge factor of the specified <ChannelMask> currently set on the Node.
        //
        //Parameters:
        //    mask - The <ChannelMask> of the gauge factor to read.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Gauge Factor is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        float getGaugeFactor(const ChannelMask& mask) const;

        //Function: getExcitationVoltage
        //  Reads the Excitation <WirelessTypes::Voltage> currently set on the Node.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Excitation Voltage is not supported.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::Voltage getExcitationVoltage() const;

        //Function: getAdcVoltageRef
        //  Reads the ADC <WirelessTypes::Voltage> Reference of the Node.
        //
        //
        //Exceptions:
        //  - <Error_NotSupported>: ADC Voltage is not supported.
        WirelessTypes::Voltage getAdcVoltageRef() const;

        //Function: getGainAmplifierVoltageRef
        //  Reads the Gain Amplifier <WirelessTypes::Voltage> Reference of the Node.
        //
        //Exceptions:
        //  - <Error_NotSupported>: ADC Voltage is not supported.
        WirelessTypes::Voltage getGainAmplifierVoltageRef() const;

        //Function: getGaugeResistance
        //  Reads the gauge resistance currently set on the Node.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Gauge Resistance is not supported.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        uint16 getGaugeResistance() const;

        //Function: getNumActiveGauges
        //  Reads the Number of Active Gauges currently set on the Node.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Number of Active Gauges is not supported.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        uint16 getNumActiveGauges() const;

        float getLowBatteryThreshold() const;

        //Function: getLinearEquation
        //    Gets the linear equation of the specified <ChannelMask> currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Linear Equation is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        LinearEquation getLinearEquation(const ChannelMask& mask) const;

        //Function: getUnit
        //    Reads the unit of the specified <ChannelMask> currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The Unit setting is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::CalCoef_Unit getUnit(const ChannelMask& mask) const;

        //Function: getEquationType
        //    Reads the <WirelessTypes::CalCoef_EquationType> of the specified <ChannelMask> currently set on the Node.
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

        //Function: getFilterSettlingTime
        //    Reads the filter settling time of the specified <ChannelMask>.
        //
        //Parameters:
        //    mask - The <ChannelMask> of the filter settling time to read.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Filter Settling Time is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::SettlingTime getFilterSettlingTime(const ChannelMask& mask) const;

        //Function: getThermocoupleType
        //    Reads the <WirelessTypes::ThermocoupleType> of the specified <ChannelMask> currently set on the Node.
        //
        //Parameters:
        //    mask - The <ChannelMask> of the thermocouple type to read.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Thermocouple Type is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::ThermocoupleType getThermocoupleType(const ChannelMask& mask) const;

        //Function: getTempSensorOptions
        //    Reads the <TempSensorOptions> of the specified <ChannelMask> currently set on the Node.
        //
        //Parameters:
        //    mask - The <ChannelMask> of the TempSensorOptions to read.
        //
        //Exceptions:
        //    - <Error_NotSupported>: TempSensorOptions is not supported for the provided <ChannelMask>.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        TempSensorOptions getTempSensorOptions(const ChannelMask& mask) const;

        //Function: getFatigueOptions
        //    Reads the <FatigueOptions> currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: FatigueOptions configuration is not supported by this Node.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        FatigueOptions getFatigueOptions() const;

        //Function: getHistogramOptions
        //    Reads the <HistogramOptions> currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: HistogramOptions configuration is not supported by this Node.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        HistogramOptions getHistogramOptions() const;

        //Function: getActivitySense
        //    Reads the <ActivitySense> options currently set on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: ActivitySense configuration is not supported by this Node.
        //    - <Error_NodeCommunication>: Failed to read from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        ActivitySense getActivitySense() const;

        //Function: getEventTriggerOptions
        //  Reads the <EventTriggerOptions> currently set on the Node.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Event Trigger configuration is not supported by this Node.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        EventTriggerOptions getEventTriggerOptions() const;

        //Function: getDiagnosticInterval
        //  Reads the interval (in seconds) at which the diagnostic info is configured to be sent.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Diagnostic Info is not supported by this Node.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        uint16 getDiagnosticInterval() const;

        //Function: getStorageLimitMode
        //  Rates the <WirelessTypes::StorageLimitMode> that the Node is configured for.
        //  This determines what happens when the datalogging storage limit is reached on the Node.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Storage Limit Mode (or datalogging) is not supported by this Node.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::StorageLimitMode getStorageLimitMode() const;

        //Function: getSensorDelay
        //  Reads the sensor delay (in microseconds) that is currently set on the Node.
        //
        //Exceptions:
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        uint32 getSensorDelay() const;

        //Function: getDataMode
        //  Reads the <WirelessTypes::DataMode> that is currently set on the Node.
        //
        //Exceptions:
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::DataMode getDataMode() const;

        //Function: getDerivedDataRate
        //  Reads the <WirelessTypes::WirelessSampleRate> for all Derived Data Channels that is currently set on the Node.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Derived Channels are not supported by this Node.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::WirelessSampleRate getDerivedDataRate() const;

        //Function: getDerivedChannelMask
        //  Reads the <ChannelMask> for an individual <WirelessTypes::DerivedCategory> that is currently set on the Node.
        //  This represents which of the actual Node's channels are set to be mapped to derived channels.
        //  For example, if the mask for RMS has ch1 and ch3 active, ch1RMS and ch3RMS channels will be output.
        //
        //Parameters:
        //  category - The <WirelessTypes::DerivedCategory> to read the channel mask for.
        //
        //Returns:
        //  A <ChannelMask> that is currently set on the Node for the requested <WirelessTypes::DerivedChannel>.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Derived Channels are not supported by this Node.
        //  - <Error_NodeCommunication>: Failed to read from the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        ChannelMask getDerivedChannelMask(WirelessTypes::DerivedCategory category) const;

        //Function: getDerivedVelocityUnit
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

    public:
        //Function: ping
        //    Performs a Long Ping command on the Node to check the communication between the Base Station and the Node.
        //
        //Returns:
        //    A <PingResponse> object that can be queried to get details of the ping command's response.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual PingResponse ping();

        //Function: sleep
        //    Puts the Node into a low power, sleep mode.
        //    This command attempts to ping the node before sending the sleep command, to verify communication.
        //
        //Returns:
        //    true if the sleep command was successful, false otherwise.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual bool sleep();

        //Function: cyclePower
        //    Cycles the power on the Node. 
        //    Many configuration changes that are applied to the node do not take affect until the power is cycled.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to write an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to reset the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual void cyclePower();

        //Function: resetRadio
        //    Resets the radio on the Node. 
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to reset the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual void resetRadio();

        //Function: changeFrequency
        //    Changes the radio frequency of the Node.
        //
        //Parameters:
        //    frequency - The <WirelessTypes::Frequency> to change the Node to.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to write an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_NodeCommunication>: Failed to write the value to the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual void changeFrequency(WirelessTypes::Frequency frequency);

        //Function: setToIdle
        //    Attempts to set the Node to the Idle state so that it can be communicated with (stops it sampling, wakes it up if asleep).
        //
        //Returns:
        //    A <SetToIdleStatus> object that can be queried to get the status of the Set to Idle operation.
        //
        //Exceptions:
        //    - <Error_Communication>: Failed to communicate with the parent BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual SetToIdleStatus setToIdle();

        //Function: erase
        //    Erases all logged data on the Node.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to erase the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual void erase();

        //Function: startNonSyncSampling
        //    Starts the Node in Non-Synchronized Sampling Mode.
        //
        //Exceptions:
        //    - <Error_InvalidNodeConfig>: The Configuration of the Node is not set for Non-Sync Sampling Mode.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation
        virtual bool startNonSyncSampling();

        virtual bool startSyncSampling();

        //Function: clearHistogram
        //    Clears the Histogram on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Histogram configuration is not supported by the Node.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual void clearHistogram();

        //Function: autoBalance
        //    Performs an Auto Balance command on a specified channel on the Node.
        //
        //Parameters:
        //    mask - The <ChannelMask> to perform the auto balance command on.
        //    targetPercent - The percentage (0.0 - 100.0) of the range to balance to.
        //
        //Returns:
        //    The <AutoBalanceResult> containing information from the auto balance command.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Autobalance is not supported by the Node or channel specified.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual AutoBalanceResult autoBalance(const ChannelMask& mask, float targetPercent);

        //Function: autoCal_shmLink
        //    Performs automatic calibration for the SHM-Link Wireless Node.
        //
        //Returns:
        //    The <AutoCalResult_shmLink> containing the result of the auto cal operation.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Autocal is not supported by the Node or The node is an invalid model for this command.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual AutoCalResult_shmLink autoCal_shmLink();

        //Function: autoCal_shmLink201
        //    Performs automatic calibration for the SHM-Link-201 Wireless Node.
        //
        //Returns:
        //    The <AutoCalResult_shmLink201> containing the result of the auto cal operation.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Autocal is not supported by the Node or The node is an invalid model for this command.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual AutoCalResult_shmLink201 autoCal_shmLink201();

        //Function: autoShuntCal
        //  Performs automatic shunt calibration for a specified <ChannelMask> on supported Nodes.
        //
        //Parameters:
        //  mask - The <ChannelMask> to perform the auto cal shunt command on.
        //  commandInfo - The <ShuntCalCmdInfo> to use for the shunt cal operation.
        //
        //Returns:
        //  The <AutoShuntCalResult> containing the result of the auto cal operation.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Autocal shunt is not supported by the Node or ChannelMask.
        //  - <Error_NodeCommunication>: Failed to communicate with the Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual AutoShuntCalResult autoShuntCal(const ChannelMask& mask, const ShuntCalCmdInfo& commandInfo);

        //Function: poll
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

        //Function: readEeprom
        //    Reads a uint16 from the given eeprom location of the node. This may use a page download or a read eeprom command.
        //    If the value stored in the eeprom cache is still valid, this will be returned instead.
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
        virtual uint16 readEeprom(uint16 location) const;

        //Function: readEeprom
        //    Reads a value from the given <EepromLocation> of the node. This may use a page download or a read eeprom command.
        //    If the value stored in the eeprom cache is still valid, this will be returned instead.
        //
        //Parameters:
        //    location - The <EepromLocation> to read from.
        //
        //Returns:
        //    The value read from the specified EEPROM location as a <Value> object.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported eeprom location.
        //    - <Error_NodeCommunication>: Failed to read the value from the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual Value readEeprom(const EepromLocation& location) const;

        //Function: writeEeprom
        //    Writes a uint16 to the given eeprom location of the node.
        //    If successful, the cache will be updated with the changed value as well.
        //
        //Parameters:
        //    location - The specific eeprom location to write to
        //    value - The uint16 value to write to the eeprom location
        //
        //Exceptions:
        //    - <Error_NotSupported>: Unsupported eeprom location or value.
        //    - <Error_NodeCommunication>: Failed to write the value to the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual void writeEeprom(uint16 location, uint16 value);

        //Function: writeEeprom
        //    Writes a value to the given <EepromLocation> of the node.
        //    If successful, the cache will be updated with the changed value as well.
        //
        //Parameters:
        //    location - The specific <EepromLocation> to write to.
        //    value - The value to write to the eeprom location, as a <Value>.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Unsupported eeprom location or value.
        //    - <Error_NodeCommunication>: Failed to write the value to the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual void writeEeprom(const EepromLocation& location, const Value& val);

        //Function: getDiagnosticInfo
        //  Performs an immediate request for the Node's Diagnostic Info.
        //
        //Parameters:
        //  result - The <ChannelData> container that will be filled with the result upon success.
        //
        //Exceptions:
        //  - <Error_NotSupported>: The Get Diagnostic Info command is not supported.
        //  - <Error_NodeCommunication>: Failed to communicate with the Wireless Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual void getDiagnosticInfo(ChannelData& result);

        //Function: testCommProtocol
        //  Tests if the Node will still be able to communicate after changing the Node's communication protocol.
        //  This is recommended to be used before changing communication protocol as the range can change between protocol modes.
        //  Note: Both the Node and BaseStation will return to the current protocol after this test.
        //
        //Parameters:
        //  commProtocol - The <WirelessTypes::CommProtocol> to test.
        //
        //Returns:
        //  true if the Node had good communication (responded to pings) in the new protocol.
        //
        //Exceptions:
        //  - <Error_NotSupported>: The given communication protocol is not supported by the Node or BaseStation.
        //  - <Error_NodeCommunication>: Failed to communicate with the Wireless Node.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual bool testCommProtocol(WirelessTypes::CommProtocol commProtocol);
    };
}