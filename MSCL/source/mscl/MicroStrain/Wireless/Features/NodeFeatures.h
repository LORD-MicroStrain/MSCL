/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include <memory>
#include <tuple>
#include <vector>

#include "mscl/MicroStrain/Wireless/WirelessTypes.h"
#include "mscl/MicroStrain/Wireless/WirelessModels.h"
#include "mscl/MicroStrain/Wireless/WirelessChannel.h"
#include "mscl/MicroStrain/Wireless/Configuration/InputRange.h"
#include "mscl/MicroStrain/SampleRate.h"
#include "mscl/Types.h"
#include "ChannelGroup.h"
#include "NodeInfo.h"

namespace mscl
{    
    //forward declarations
    class ChannelMask;

    //API Class: NodeFeatures
    //    Contains information on which features are supported by a <WirelessNode>.
    class NodeFeatures
    {
        friend class DatalogDownloader;
        friend class NodeEepromHelper;
        friend class WirelessNodeConfig;
        friend class WirelessNode_Impl;
        friend class WirelessProtocol;
        friend class NodeEeprom;

    private:
        NodeFeatures();                                    //disabled default constructor
        NodeFeatures(const NodeFeatures&);                //disabled copy constructor
        NodeFeatures& operator=(const NodeFeatures&);    //disable assignment operator

    public:
        virtual ~NodeFeatures() {};

    private:
        //Wireless Node FW version to ASPP version lookup
        static const Version MIN_NODE_FW_PROTOCOL_1_5;
        static const Version MIN_NODE_FW_PROTOCOL_1_4;
        static const Version MIN_NODE_FW_PROTOCOL_1_2;
        static const Version MIN_NODE_FW_PROTOCOL_1_1;

        //Base Station FW version to ASPP version lookup
        static const Version MIN_BASE_FW_PROTOCOL_1_3;
        static const Version MIN_BASE_FW_PROTOCOL_1_1;

    protected:
        //Constructor: NodeFeatures
        //    Creates a NodeFeatures object.
        //
        //Parameters:
        //    info - A <NodeInfo> object representing standard information of the <WirelessNode>.
        NodeFeatures(const NodeInfo& info);

        //Variable: m_nodeInfo
        //    The <NodeInfo> object containing basic information retreived from eeprom about the Node.
        NodeInfo m_nodeInfo;

        //Variable: m_channels
        //    Contains all of the supported channels for this Node.
        WirelessChannels m_channels;

        //Variable: m_channelGroups
        //    Contains all of the <ChannelGroups> that are supported by this Node.
        ChannelGroups m_channelGroups;

    public:
#ifndef SWIG
        //Function: create
        //    Builds and returns a NodeFeatures pointer based on the given parameters.
        //
        //Parameters:
        //    info - A <NodeInfo> object representing standard information of the <WirelessNode>.
        //
        //Returns:
        //    A NodeFeatures unique_ptr.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The Node model is not supported by MSCL.
        static std::unique_ptr<NodeFeatures> create(const NodeInfo& info);
#endif

    protected:
        //Function: addCalCoeffChannelGroup
        //    Adds a cal coefficient (Linear Equation, unit, equation type) to the channel groups for the specified channel.
        void addCalCoeffChannelGroup(uint8 channelNumber, const std::string& name, const EepromLocation& slopeEeprom, const EepromLocation& actionIdEeprom);

        //Function: addCalCoeffChannelGroup_withFactoryCal
        //    Adds a cal coefficient with factory cal values (Linear Equation, unit, equation type, factory cal) to the channel groups for the specified channel.
        void addCalCoeffChannelGroup_withFactoryCal(uint8 channelNumber, const std::string& name, const EepromLocation& slopeEeprom, const EepromLocation& actionIdEeprom, const EepromLocation& factorySlopeEeprom, const EepromLocation& factoryActionIdEeprom);

        //Function: maxFilterSettlingTime_A
        //    Gets the max filter settling time allowed by the given <SampleRate>. 
        //    This is version A of this function. Different nodes use different versions.
        static WirelessTypes::SettlingTime maxFilterSettlingTime_A(const SampleRate& rate);

        //Function: maxFilterSettlingTime_B
        //    Gets the max filter settling time allowed by the given <SampleRate>. 
        //    This is version B of this function. Different nodes use different versions.
        static WirelessTypes::SettlingTime maxFilterSettlingTime_B(const SampleRate& rate);

        //Function: maxSampleRateForSettlingTime_A
        //  Gets the max <WirelessTypes::WirelessSampleRate> allowed by the given <WirelessTypes::SettlingTime>.
        //  This is version A of this function. Different nodes use different versions.
        //
        //Parameters:
        //  settlingTime - The settling time to get the max sample rate for.
        //  rates - The <WirelessTypes::WirelessSampleRates> available for the Node (presumably for a specific sampling mode).
        static WirelessTypes::WirelessSampleRate maxSampleRateForSettlingTime_A(WirelessTypes::SettlingTime settlingTime, const WirelessTypes::WirelessSampleRates& rates);

        //Function: maxSampleRateForSettlingTime_B
        //  Gets the max <WirelessTypes::WirelessSampleRate> allowed by the given <WirelessTypes::SettlingTime>.
        //  This is version B of this function. Different nodes use different versions.
        //
        //Parameters:
        //  settlingTime - The settling time to get the max sample rate for.
        //  rates - The <WirelessTypes::WirelessSampleRates> available for the Node (presumably for a specific sampling mode).
        static WirelessTypes::WirelessSampleRate maxSampleRateForSettlingTime_B(WirelessTypes::SettlingTime settlingTime, const WirelessTypes::WirelessSampleRates& rates);

    public:
        //API Function: normalizeNumSweeps
        //    Normalizes the number of sweeps so that it is within range and a multiple of 100 (rounds up to next multiple).
        //
        //Parameters:
        //    sweeps - the value to normalize. This will be updated to hold the normalized result.
        uint32 normalizeNumSweeps(uint32 sweeps) const;

        //API Function: normalizeTimeBetweenBursts
        //    Normalizes a <TimeSpan> so that it is within an acceptable range for setting the timeBetweenBursts.
        //    A valid range is between 1 second and 24 hours. Seconds above 32767 will be rounded to minutes.
        //    When setting the time between bursts, you should also call <minTimeBetweenBursts> and verify it is greater than this.
        //
        //Parameters:
        //    time - <TimeSpan> to normalize. This will be updated to hold the normalized result.
        TimeSpan normalizeTimeBetweenBursts(const TimeSpan& time) const;

    private:
        //Function: findEeprom
        //    Finds the <EepromLocation> for the provided setting and channel mask pair.
        //
        //Parameters:
        //    setting - The <WirelessTypes::ChannelGroupSetting> to search for.
        //    mask - The <ChannelMask> of the setting to search for.
        //
        //Returns:
        //    The <EepromLocation> for the found option.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The <WirelessTypes::ChannelGroupSetting> or <ChannelMask> is not supported.
        const EepromLocation& findEeprom(WirelessTypes::ChannelGroupSetting setting, const ChannelMask& mask) const;

        //Function: anyChannelGroupSupports
        //    Checks if any channel group on the Node supports the given <WirelessTypes::ChannelGroupSetting>.
        //
        //Parameters:
        //    setting - The <WirelessTypes::ChannelGroupSetting> to check if any channel group supports.
        //
        //Returns:
        //    true if at least 1 channel group supports the setting, false otherwise.
        bool anyChannelGroupSupports(WirelessTypes::ChannelGroupSetting setting) const;

        //Function: ramBufferSize
        //  Gets the RAM buffer size (in bytes) for the Node.
        virtual uint32 ramBufferSize() const;

    protected:
        //Function: anyChannelGroupSupports
        //    Checks if any channel group, with the specified channel number, supports the given <WirelessTypes::ChannelGroupSetting>.
        //
        //Parameters:
        //    setting - The <WirelessTypes::ChannelGroupSetting> to check if any channel group supports.
        //    channelNumber - The channel number (ch1 = 1, ch8 = 8) to check if it is in the mask for the found setting.
        //
        //Returns:
        //    true if at least 1 channel group, containing the specified channel number, supports the setting, false otherwise.
        bool anyChannelGroupSupports(WirelessTypes::ChannelGroupSetting setting, uint8 channelNumber) const;

    public:
        //API Function: channels
        //    Gets a reference to the <WirelessChannels> of this Node.
        //
        //Returns:
        //    A reference to the <WirelessChannels> of this Node.
        const WirelessChannels& channels() const;

        //API Function: channelGroups
        //    Gets the <ChannelGroups> supported by this Node.
        //
        //Returns:
        //    A <ChannelGroups> container containing each group supported by this Node.
        ChannelGroups channelGroups() const;

        //API Function: channelType
        //  Gets the <WirelessTypes::ChannelType> for the requested channel number.
        //
        //Parameters:
        //  channelNumber - The channel number to find the type for (ch1 = 1, ch8 = 8).
        //
        //Returns:
        //  The <WirelessTypes::ChannelType> for the requested channel number.
        //
        //Exceptions:
        //  - <Error_NotSupported>: The channel number is not supported by this Node.
        virtual WirelessTypes::ChannelType channelType(uint8 channelNumber) const;

        //API Function: supportsChannelSetting
        //    Checks if the Node supports a given <WirelessTypes::ChannelGroupSetting> for the given <ChannelMask>.
        //
        //Parameters:
        //    setting - The <WirelessTypes::ChannelGroupSetting> to check for.
        //    mask - The <ChannelMask> to check if the setting is supported for.
        //
        //Returns:
        //    true if the <WirelessTypes::ChannelGroupSetting> is supported for the <ChannelMask>, false otherwise.
        virtual bool supportsChannelSetting(WirelessTypes::ChannelGroupSetting setting, const ChannelMask& mask) const;

        //API Function: supportsInputRange
        //    Checks if the Node supports Input Range for any of its <ChannelGroups>.
        //    
        //Returns:
        //    true if the Node supports Input Range for at least one <ChannelGroup>, false otherwise.
        virtual bool supportsInputRange() const;

        //API Function: supportsInputRange
        //  Checks if the Node supports Input Range for any of its <ChannelGroups>,
        //  and has different input ranges depending on a configurable excitation voltage.
        //    
        //Returns:
        //  true if the Node supports Input Range for at least one <ChannelGroup>, false otherwise.
        virtual bool supportsInputRangePerExcitationVoltage() const;

        //API Function: supportsHardwareOffset
        //    Checks if the Node supports Hardware Offset for any of its <ChannelGroups>.
        //    
        //Returns:
        //    true if the Node supports Hardware Offset for at least one <ChannelGroup>, false otherwise.
        virtual bool supportsHardwareOffset() const;

        //API Function: supportsAntiAliasingFilter
        //  Checks if the Node supports Anti-Aliasing Filter for any of its <ChannelGroups>.
        //
        //Returns:
        //  true if the Node supports Anti-Aliasing Filter for at least one <ChannelGroup>, false otherwise.
        virtual bool supportsAntiAliasingFilter() const;

        //API Function: supportsLowPassFilter
        //  Checks if the Node supports Low-Pass Filter for any of its <ChannelGroups>.
        //
        //Returns:
        //  true if the Node supports Low-Pass Filter for at least one <ChannelGroup>, false otherwise.
        virtual bool supportsLowPassFilter() const;

        //API Function: supportsHighPassFilter
        //  Checks if the Node supports High-Pass Filter for any of its <ChannelGroups>.
        //
        //Returns:
        //  true if the Node supports High-Pass Filter for at least one <ChannelGroup>, false otherwise.
        virtual bool supportsHighPassFilter() const;

        //API Function: supportsGaugeFactor
        //    Checks if the Node supports Gauge Factor for any of its <ChannelGroups>.
        //
        //Returns:
        //    true if the Node support Gauge Factor for at least on <ChannelGroup>, false otherwise.
        virtual bool supportsGaugeFactor() const;

        //API Function: supportsGaugeResistance
        //  Checks if the Node supports the Gauge Resistance option.
        //
        //Returns:
        //  true if the Node supports Gauge Resistance, false otherwise.
        virtual bool supportsGaugeResistance() const;

        //API Function: supportsNumActiveGauges
        //  Checks if the Node supports the Number of Active Gauges option.
        //
        //Returns:
        //  true if the Node supports the Number of Active Gauges option, false otherwise.
        virtual bool supportsNumActiveGauges() const;

        //API Function: supportsLostBeaconTimeout
        //    Checks if the Node supports the Lost Beacon Timeout option.
        //
        //Returns:
        //    true if the Node supports Lost Beacon Timeout, false otherwise.
        virtual bool supportsLostBeaconTimeout() const;

        //API Function: supportsPullUpResistor
        //  Checks if the Node supports the Pull-up Resistor option.
        //
        //Returns:
        //  true if the Node supports Pull-up Registor, false otherwise.
        virtual bool supportsPullUpResistor() const;

        //API Function: supportsFilterSettlingTime
        //    Checks if the Node supports Filter Settling Time for any of its <ChannelGroups>.
        //
        //Returns:
        //    true if the Node supports Filter Settling Time for at least one <ChannelGroup>, false otherwise.
        virtual bool supportsFilterSettlingTime() const;

        //API Function: supportsThermocoupleType
        //    Checks if the Node supports the Thermocouple Type for any of its <ChannelGroups>.
        //
        //Returns:
        //    true if the Node supports Thermocouple Type for at least one <ChannelGroup>, false otherwise.
        virtual bool supportsThermocoupleType() const;

        //API Function: supportsTempSensorOptions
        //    Checks if the Node supports the TempSensorOptions configuration for any of its <ChannelGroups>.
        //
        //Returns:
        //    true if the Node supports TempSensorOptions configuration for at least one <ChannelGroup>, false otherwise.
        virtual bool supportsTempSensorOptions() const;

        //API Function: supportsDebounceFilter
        //    Checks if the Node supports the Debounce Filter configuration for any of its <ChannelGroups>.
        //
        //Returns:
        //    true if the Node supports Debounce Filter configuration for at least one <ChannelGroup>, false otherwise.
        virtual bool supportsDebounceFilter() const;

        //API Function: supportsFatigueConfig
        //    Checks if the Node supports <FatigueOptions> configuration.
        //
        //Returns:
        //    true if the Node supports <FatigueOptions>, false otherwise.
        virtual bool supportsFatigueConfig() const;

        //API Function: supportsYoungsModConfig
        //    Checks if the Node supports Young's Modulus (part of <FatigueOptions>) configuration.
        //
        //Returns:
        //    true if the Node supports Young's Modulus configuration, false otherwise.
        virtual bool supportsYoungsModConfig() const;

        //API Function: supportsPoissonsRatioConfig
        //    Checks if the Node supports Poisson's Ratio (part of <FatigueOptions>) configuration.
        //
        //Returns:
        //    true if the Node supports Poisson's Ratio configuration, false otherwise.
        virtual bool supportsPoissonsRatioConfig() const;

        //API Function: supportsFatigueDebugModeConfig
        //    Checks if the Node supports enabling Debug Mode (part of <FatigueOptions>) configuration.
        //
        //Returns:
        //    true if the Node supports Debug Mode configuration, false otherwise.
        virtual bool supportsFatigueDebugModeConfig() const;

        //API Function: supportsFatigueModeConfig
        //    Checks if the Node supports Fatigue Mode (part of <FatigueOptions>) configuration.
        //
        //Returns:
        //    true if the Node supports Fatigue Mode configuration, false otherwise.
        virtual bool supportsFatigueModeConfig() const;

        //API Function: supportsHistogramConfig
        //    Checks if the Node supports <HistogramOptions> configuration.
        //
        //Returns:
        //    true if the Node supports <HistogramOptions>, false otherwise.
        virtual bool supportsHistogramConfig() const;

        //API Function: supportsHistogramRateConfig
        //    Checks if the Node supports Histogram transmit rate (part of <HistogramOptions>) configuration.
        //
        //Returns:
        //    true if the Node supports Histogram transmit rate configuration, false otherwise.
        virtual bool supportsHistogramRateConfig() const;

        //API Function: supportsHistogramEnableConfig
        //    Checks if the Node supports turning Histograms on and off (part of <FatigueOptions>).
        //
        //Returns:
        //    true if the Node supports turning Histograms on and off, false otherwise.
        virtual bool supportsHistogramEnableConfig() const;

        //API Function: supportsActivitySense
        //    Checks if the Node supports the <ActivitySense> feature.
        //
        //Returns:
        //    true if the Node supports <ActivitySense> and can be configured for it.
        virtual bool supportsActivitySense() const;

        //API Function: supportsAutoBalance
        //    Checks if the Node supports the Auto Balance command for any of its <ChannelGroups>.
        //
        //Returns:
        //    true if the Node supports Auto Balance for at least 1 <ChannelGroup>, false otherwise.
        virtual bool supportsAutoBalance() const;

        //API Function: supportsLegacyShuntCal
        //  Checks if the Node supports the legacy Shunt Cal for any of its <ChannelGroups>.
        //
        //Returns:
        //  true if the Node supports Shunt Cal for at least 1 <ChannelGroup>, false otherwise.
        virtual bool supportsLegacyShuntCal() const;

        //API Function: supportsAutoCal_shm
        //    Checks if the Node supports the AutoCal SHM-Link command.
        //
        //Returns:
        //    true if the Node supports the AutoCal SHM-Link command, false otherwise.
        virtual bool supportsAutoCal_shm() const;

        //API Function: supportsAutoCal_shm201
        //    Checks if the Node supports the AutoCal SHM-Link-201 command.
        //
        //Returns:
        //    true if the Node supports the AutoCal SHM-Link-201 command, false otherwise.
        virtual bool supportsAutoCal_shm201() const;

        //API Function: supportsAutoShuntCal
        //  Checks if the Node supports AutoShuntCal on any of this <ChannelGroups>.
        //
        //Returns:
        //  true if the Node supports Auto Shunt Cal for at least 1 <ChannelGroup>, false otherwise.
        virtual bool supportsAutoShuntCal() const;

        //API Function: supportsGetFactoryCal
        //  Checks if the Node has factory calibrations stored for any of its <ChannelGroups>.
        //
        //Returns:
        //  true if the Node has factory calibration values for at least 1 <ChannelGroup>, false otherwise.
        virtual bool supportsGetFactoryCal() const;

        //API Function: supportsLimitedDuration
        //    Checks if the Node supports setting a limited duration of sampling.
        //
        //Returns:
        //    true if the Node supported limited duration, false if the Node only supports unlimited sampling.
        virtual bool supportsLimitedDuration() const;

        //API Function: supportsEventTrigger
        //  Checks if the Node supports Event Trigger sampling.
        //
        //Returns:
        //  true if the Node supports Event Trigger, false otherwise.
        virtual bool supportsEventTrigger() const;

        //API Function: supportsDiagnosticInfo
        //  Checks if the Node supports sending Diagnostic Info.
        //
        //Returns:
        //  true if the Node can be configured to send diagnostic info, false otherwise.
        virtual bool supportsDiagnosticInfo() const;

        //API Function: supportsLoggedData
        //  Checks if the Node supports logging to internal memory.
        //
        //Returns:
        //  true if the Node can store logged data, false otherwise.
        virtual bool supportsLoggedData() const;

        //API Function: supportsPoll
        //  Checks if the Node supports the poll command.
        //
        //Returns:
        //  true if the Node supporting the poll command, false otherwise.
        virtual bool supportsPoll() const;

        //API Function: supportsSensorDelayConfig
        //  Checks if the Node supports configuration of sensor delay.
        //
        //Returns:
        //  true if the Node supports configuration of sensor delay, false otherwise.
        virtual bool supportsSensorDelayConfig() const;

        //API Function: supportsSensorDelayAlwaysOn
        //  Checks if the Node supports setting the sensor delay value to "Always On."
        //
        //Returns:
        //  true if the Node supports setting the sensor delay to "Always On", false otherwise
        virtual bool supportsSensorDelayAlwaysOn() const;

        //API Function: supportsSensorOutputMode
        //  Checks if the Node supports configuration of the Sensor Output Mode.
        //
        //Returns:
        //  true if the Node supports setting the Sensor Output Mode, false otherwise
        virtual bool supportsSensorOutputMode() const;

        //API Function: supportsCfcFilterConfiguration
        //  Checks if the Node supports configuration of the channel frequency class filter.
        //
        //Returns:
        //  true if the Node supports setting the channel frequency class filter, false otherwise
        virtual bool supportsCfcFilterConfiguration() const;

        //API Function: supportsChannel
        //    Checks if a specific channel is supported (can be enabled) by this Node.
        //
        //Parameters:
        //    channelNumber - The channel to check if it is supported.
        //
        //Returns:
        //    true if the channel is supported, false otherwise.
        virtual bool supportsChannel(uint8 channelNumber) const;

        //API Function: supportsSamplingMode
        //    Checks if a <WirelessTypes::SamplingMode> is supported by this Node.
        //
        //Parameters:
        //    samplingMode - The <WirelessTypes::SamplingMode> to check if supported.
        //
        //Returns:
        //    true if the sampling mode is supported, false otherwise.
        virtual bool supportsSamplingMode(WirelessTypes::SamplingMode samplingMode) const;

        //API Function: supportsSampleRate
        //    Checks if a sample rate is supported by the Node for the given <WirelessTypes::SamplingMode>.
        //
        //Parameters:
        //    sampleRate - The <WirelessTypes::WirelessSampleRate> to check if supported.
        //    samplingMode - The <WirelessTypes::SamplingMode> to check if the sample rate is supported for.
        //    dataCollectionMethod - The <WirelessTypes::DataCollectionMethod dataCollectionMethod> to check if the sample rate is supported for.
        //    dataMode - The <WirelessTypes::DataMode> to check if the sample rate is supported for
        //
        //Returns:
        //    true if the sample rate is supported for the given sampling mode, false otherwise.
        virtual bool supportsSampleRate(WirelessTypes::WirelessSampleRate sampleRate, WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const;

        //API Function: supportsCommunicationProtocol
        //    Checks if a <WirelessTypes::CommProtocol> is supported by this Node.
        //
        //Parameters:
        //    protocol - The <WirelessTypes::CommProtocol> to check if supported.
        //
        //Returns:
        //    true if the protocol is supported, false otherwise.
        virtual bool supportsCommunicationProtocol(WirelessTypes::CommProtocol protocol) const;

        //API Function: supportsDataFormat
        //    Checks if a <WirelessTypes::DataFormat> is supported by this Node.
        //
        //Parameters:
        //    dataFormat - The <WirelessTypes::DataFormat> to check if supported.
        //
        //Returns:
        //    true if the data format is supported, false otherwise.
        virtual bool supportsDataFormat(WirelessTypes::DataFormat dataFormat) const;

        //API Function: supportsDefaultMode
        //    Checks if a <WirelessTypes::DefaultMode> is supported by this Node.
        //
        //Parameters:
        //    mode - The <WirelessTypes::DefaultMode> to check if supported.
        //
        //Returns:
        //    true if the default is supported, false otherwise.
        virtual bool supportsDefaultMode(WirelessTypes::DefaultMode mode) const;

        //API Function: supportsDataCollectionMethod
        //    Checks if a <WirelessTypes::DataCollectionMethod> is supported by this Node.
        //
        //Parameters:
        //    collectionMethod - The <WirelessTypes::DataCollectionMethod> to check if supported.
        //
        //Returns:
        //    true if the data collection method is supported, false otherwise.
        virtual bool supportsDataCollectionMethod(WirelessTypes::DataCollectionMethod collectionMethod) const;

        //API Function: supportsTransmitPower
        //    Checks if a <WirelessTypes::TransmitPower> is supported by this Node.
        //
        //Parameters:
        //    power - The <WirelessTypes::TransmitPower> to check if supported.
        //    commProtocol - The <WirelessTypes::CommProtocol> to check if the power is supported in.
        //
        //Returns:
        //    true if the transmit power is supported, false otherwise.
        virtual bool supportsTransmitPower(WirelessTypes::TransmitPower power, WirelessTypes::CommProtocol commProtocol) const;

        //API Function: supportsDataMode
        //    Checks if a <WirelessTypes::DataMode> is supported by this Node.
        //
        //Parameters:
        //    power - The <WirelessTypes::DataMode> to check if supported.
        //
        //Returns:
        //    true if the data mode is supported, false otherwise.
        virtual bool supportsDataMode(WirelessTypes::DataMode dataMode) const;

        //API Function: supportsTransducerType
        //  Checks if a <WirelessTypes::TransducerType> is supported by this Node.
        //
        //Parameters 
        //  transducerType - The <WirelessTypes::TransducerType> to check if supported.
        //
        //Returns:
        //  true if the transducer type is supported, false otherwise.
        virtual bool supportsTransducerType(WirelessTypes::TransducerType transducerType) const;

        //API Function: supportsFatigueMode
        //    Checks if a <WirelessTypes::FatigueMode> is supported by this Node.
        //
        //Parameters:
        //    mode - The <WirelessTypes::FatigueMode> to check if supported.
        //
        //Returns:
        //    true if the fatigue mode is supported, false otherwise.
        virtual bool supportsFatigueMode(WirelessTypes::FatigueMode mode) const;

        //API function: supportsInputRange
        //  Checks if a <WirelessTypes::InputRange> is supported by this Node for the given <ChannelMask>.
        //
        //Parameters:
        //  range - The <WirelessTypes::InputRange> to check if supported.
        //  channels - The <ChannelMask> to check for.
        //
        //Returns:
        //  true if the input range is supported, false if it is not.
        virtual bool supportsInputRange(WirelessTypes::InputRange range, const ChannelMask& channels) const;


        //API function: supportsInputRange
        //  Checks if a <WirelessTypes::InputRange> is supported by this Node for the given <ChannelMask>.
        //
        //Parameters:
        //  range - The <WirelessTypes::InputRange> to check if supported.
        //  channels - The <ChannelMask> to check for.
        //  excitationVoltage - The Excitation <WirelessTypes::Voltage> to check for.
        //
        //Returns:
        //  true if the input range is supported, false if it is not.
        virtual bool supportsInputRange(WirelessTypes::InputRange range, const ChannelMask& channels, WirelessTypes::Voltage excitationVoltage) const;

        //API Function: supportsCentisecondEventDuration
        //  Checks if the Node configures event duration in 10s of milliseconds or not.
        //
        //Returns:
        //  true if the Node uses 10s of milliseconds for event duration, false if it uses seconds for event duration.
        virtual bool supportsCentisecondEventDuration() const;

        //API Function: supportsGetDiagnosticInfo
        //  Checks if the Node supports the Get Diagnostic Info command.
        //
        //Returns:
        //  true if the Get Diagnostic Info command is supported, false if it is not.
        virtual bool supportsGetDiagnosticInfo() const;

        //API Function: supportsNonSyncLogWithTimestamps
        //  Checks if the Node supports the version of Non-Sync Sampling that will add timestamps when logging.
        //  If the Node does not support this, when downloading logged data from the Node, no timestamp information will be given.
        //
        //Returns:
        //  true if the Node supports Non-Sync logging with timestamps.
        virtual bool supportsNonSyncLogWithTimestamps() const;

        //API Function: supportsDerivedCategory
        //  Checks if the Node supports a specific <WirelessTypes::DerivedCategory>.
        //
        //Parameters:
        //  derivedChannelOption - The <WirelessTypes::DerivedChannelOption> to check if it is supported.
        //
        //Returns:
        //  true if the specific derived channel is supported, false otherwise.
        virtual bool supportsDerivedCategory(WirelessTypes::DerivedCategory category) const;

        //API Function: supportsRawDataMode
        //  Checks if the Node supports any form of the Raw Data Mode (raw only, raw + derived, etc).
        //
        //Returns:
        //  true if the Node supports any form of the Raw Data Mode.
        virtual bool supportsRawDataMode() const;

        //API Function: supportsDerivedDataMode
        //  Checks if the Node supports any form of the Derived Data Mode (derived only, raw + derived, etc).
        //
        //Returns:
        //  true if the Node supports any form of the Derived Data Mode.
        virtual bool supportsDerivedDataMode() const;

        //API Function: supportsDerivedVelocityUnitConfig
        //  Checks if the Node supports configuration of the Derived Velocity Unit.
        //
        //Returns:
        //  true if the Node supports configuration of the Derived Velocity unit, false otherwise.
        virtual bool supportsDerivedVelocityUnitConfig() const;

        //API Function: supportsExcitationVoltageConfig
        //  Checks if the Node supports configuration of its Excitation Voltage.
        //
        //Returns:
        //  true if the Node supports configuration of its Excitation Voltage, false otherwise.
        virtual bool supportsExcitationVoltageConfig() const;

        //API Function: supportsLowBatteryThresholdConfig
        //  Checks if the Node supports configuration of its low battery threshold.
        //
        //Returns:
        //  true if the Node supports configuration of its low battery threshold, false otherwise.
        virtual bool supportsLowBatteryThresholdConfig() const;

        //API Function: maxSampleRate
        //    Gets the maximum <SampleRate> value that is supported by this Node with the given <SamplingMode>, <ChannelMask>, and <WirelessTypes::DataCollectionMethod>.
        //
        //Parameters:
        //    samplingMode - The <WirelessTypes::SamplingMode> to check the max sample rate for.
        //    channels - The <ChannelMask> to check the max sample rate for.
        //    dataCollectionMethod - The <WirelessTypes::DataCollectionMethod> to check the max sample rate for.
        //    dataMode - The <WirelessTypes::DataMode> to check the max sample rate for.
        //
        //Returns:
        //    The max <WirelessTypes::WirelessSampleRate> that is supported by this Node with the given <WirelessTypes::SamplingMode> and <ChannelMask>.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The <WirelessTypes::SamplingMode> is not supported by this Node.
        //                            The <WirelessTypes::DataCollectionMethod> is not supported by this Node.
        virtual WirelessTypes::WirelessSampleRate maxSampleRate(WirelessTypes::SamplingMode samplingMode, const ChannelMask& channels, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const;

        //API Function: maxSampleRateForSettlingTime
        //  Gets the maximum <SampleRate> value that is supported by this Node with the given <WirelessTypes::SettlingTime>.
        //
        //Parameters:
        //  filterSettlingTime - The <WirelessTypes::SettlingTime> to check the max sample rate for.
        //  samplingMode - The <WirelessTypes::SamplingMode> that the Node will be in for determining sample rates.
        //  dataCollectionMethod - The <WirelessTypes::DataCollectionMethod> that the Node will be set for in determining sample rates.
        //  dataMode - The <WirelessTypes::DataMode> that the Node will be set for in determining sampling rates.
        //
        //Returns:
        //    The max <WirelessTypes::WirelessSampleRate> that is supported by this Node with the given <WirelessTypes::SettlingTime>.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The Filter Settling Time feature is not supported by this Node.
        virtual WirelessTypes::WirelessSampleRate maxSampleRateForSettlingTime(WirelessTypes::SettlingTime filterSettlingTime, WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const;

        //API Function: maxSampleRateForLowPassFilter
        //  Gets the maximum <SampleRate> value that is supported by this Node with the given Low Pass Filter.
        //
        //Parameters:
        //  lowPassFilter - The <WirelessTypes::Filter> to check the max sample rate for.
        //  samplingMode - The <WirelessTypes::SamplingMode> that the Node will be in for determining sample rates.
        //  dataCollectionMethod - The <WirelessTypes::DataCollectionMethod> that the Node will be set for in determining sample rates.
        //  dataMode - The <WirelessTypes::DataMode> that the Node will be set for in determining sampling rates.
        //  channels - A <ChannelMask> representing the active raw channels.
        //
        //Returns:
        //    The max <WirelessTypes::WirelessSampleRate> that is supported by this Node with the given <WirelessTypes::SettlingTime>.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The Low Pass Filter feature is not supported by this Node, or an invalid filter was used.
        virtual WirelessTypes::WirelessSampleRate maxSampleRateForLowPassFilter(WirelessTypes::Filter lowPassFilter, WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode, const ChannelMask& channels) const;

        //API Function: maxFilterSettlingTime
        //    Gets the maximum <WirelessTypes::SettlingTime> available for the given <SampleRate>.
        //
        //Parameters:
        //    rate - The <SampleRate> to check the max filter settling time for.
        //
        //Returns:
        //    The max <WirelessTypes::SettlingTime> available.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The Filter Settling Time feature is not supported by this Node.
        virtual WirelessTypes::SettlingTime maxFilterSettlingTime(const SampleRate& rate) const;

        //API Function: minInactivityTimeout
        //    Gets the minimum inactivity timeout (in seconds) that is supported.
        //
        //Returns:
        //    The min inactivity timeout in seconds.
        virtual uint16 minInactivityTimeout() const;

        //API Function: minLostBeaconTimeout
        //    Gets the minimum lost beacon timeout (in minutes) that is supported.
        //    Note: A value of 0 disable the lost beacon timeout.
        //
        //Returns:
        //    The min lost beacon timeout in minutes.
        virtual uint16 minLostBeaconTimeout() const;

        //API Function: maxLostBeaconTimeout
        //    Gets the maximum lost beacon timeout (in minutes) that is supported.
        //
        //Returns:
        //    The max lost beacon timeout in minutes.
        virtual uint16 maxLostBeaconTimeout() const;

        //API Function: minCheckRadioInterval
        //    Gets the minimum check radio interval (in seconds) that is supported.
        //
        //Returns:
        //    The min check radio interval in seconds.
        virtual uint8 minCheckRadioInterval() const;

        //API Function: maxCheckRadioInterval
        //    Gets the maximum check radio interval (in seconds) that is supported.
        //
        //Returns:
        //    The maximum check radio interval in seconds.
        virtual uint8 maxCheckRadioInterval() const;

        //API Function: minSweeps
        //    Gets the minimum number of sweeps that can be assigned for the duration of a continuous sampling session.
        //
        //Returns:
        //    The minimum number of sweeps for a sampling session.
        virtual uint32 minSweeps() const;

        //API Function: maxSweeps
        //    Gets the maximum number of sweeps that can be assigned for a given <WirelessTypes::SamplingMode>. 
        //    This is the duration of each burst if in Burst Sync Sampling mode, or the total duration of sampling in other sampling modes.
        //
        //Parameters:
        //    samplingMode - The <WirelessTypes::SamplingMode> of the sampling session.
        //    dataMode - The <WirelessTypes::DataMode> of the sampling session.
        //    dataFormat - The <WirelessTypes::DataFormat> of the sampling session.
        //    channels - The <ChannelMask> of the raw channels for the sampling session.
        //
        //Returns:
        //    The maximum number of sweeps, or sweeps per burst, for a sampling session.
        virtual uint32 maxSweeps(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataMode dataMode, WirelessTypes::DataFormat dataFormat, const ChannelMask& channels) const;

        //API Function: maxSweepsPerBurst
        //    Gets the maximum number of sweeps per burst that can be assigned for a Burst Sync Sampling session.
        //
        //Parameters:
        //    dataMode - The <WirelessTypes::DataMode> of the sampling session.
        //    dataFormat - The <WirelessTypes::DataFormat> of the sampling session.
        //    channels - The <ChannelMask> of the raw channels for the sampling session.
        //
        //Returns:
        //    The maximum number of sweeps per burst for a Burst Sync Sampling session.
        virtual uint32 maxSweepsPerBurst(WirelessTypes::DataMode dataMode, WirelessTypes::DataFormat dataFormat, const ChannelMask& channels) const;

        //API Function: minTimeBetweenBursts
        //    Gets the minimum time that can be assigned for a Burst Sync Sampling session.
        //
        //Parameters:
        //    dataMode - The <WirelessTypes::DataMode> of the sampling session.
        //    dataFormat - The <WirelessTypes::DataFormat> of the sampling session.
        //    rawChannels - The <ChannelMask> representing active raw channels for the sampling session.
        //    derivedChannelMasks - The <WirelessTypes::DerivedChannelMasks> containing ALL enabled derived channels for the sampling session.
        //    rawSampleRate - The <SampleRate> of the raw channels for the sampling session.
        //    sweepsPerBurst - The number of sweeps per burst for the sampling session.
        //    commProtocol - The <WirelessTypes::CommProtocol> that the Node will use for sampling.
        //
        //Returns:
        //    A <TimeSpan> representing the minimum time that can be assigned for a Burst Sync Sampling session.
        virtual TimeSpan minTimeBetweenBursts(WirelessTypes::DataMode dataMode,
                                              WirelessTypes::DataFormat dataFormat,
                                              const ChannelMask& rawChannels,
                                              WirelessTypes::DerivedChannelMasks derivedChannelMasks,
                                              const SampleRate& rawSampleRate,
                                              uint32 sweepsPerBurst,
                                              WirelessTypes::CommProtocol commProtocol) const;

        //API Function: minSensorDelay
        //  Gets the minimum sensor delay value (in microseconds) that is supported.
        //
        //Returns:
        //  The minimum sensor delay value, in microseconds.
        //
        //Exceptions:
        //  - <Error_NotSupported>: The sensor delay feature is not supported by this Node.
        virtual uint32 minSensorDelay() const;

        //API Function: maxSensorDelay
        //  Gets the maximum sensor delay value (in microseconds) that is supported.
        //
        //Returns:
        //  The maximum sensor delay value, in microseconds.
        //
        //Exceptions:
        //  - <Error_NotSupported>: The sensor delay feature is not supported by this Node.
        virtual uint32 maxSensorDelay() const;

        //API Function: maxEventTriggerTotalDuration
        //  Gets the max event trigger duration (in milliseconds) that can be applied for both the pre and post event durations (combined).
        //
        //Parameters:
        //  dataMode - The <WirelessTypes::DataMode> of the sampling session.
        //  dataFormat - The <WirelessTypes::DataFormat> of the sampling session.
        //  rawChannels - The <ChannelMask> representing active raw channels for the sampling session.
        //  derivedChannelMasks - The <WirelessTypes::DerivedChannelMasks> containing ALL enabled derived channels for the sampling session.
        //  rawSampleRate - The raw <SampleRate> for the sampling session.
        //  derivedSampleRate - The <SampleRate> representing the derived data rate for the sampling session.
        //
        //Returns:
        //  The max event trigger total duration, in milliseconds.
        virtual uint32 maxEventTriggerTotalDuration(WirelessTypes::DataMode dataMode,
                                            WirelessTypes::DataFormat dataFormat,
                                            const ChannelMask& rawChannels,
                                            WirelessTypes::DerivedChannelMasks derivedChannelMasks,
                                            const SampleRate& rawSampleRate,
                                            const SampleRate& derivedDataRate) const;

        //API Function: normalizeEventDuration
        //  Normalizes the Event Trigger duration so that it is an acceptable value.
        //
        //Parameters:
        //  duration - The pre or post duration (in milliseconds) to normalize.
        //
        //Returns:
        //  The normalized event duration (in milliseconds) that can be stored on the Node.
        virtual uint32 normalizeEventDuration(uint32 duration) const;

        //API Function: normalizeSensorDelay
        //  Normalizes the sensor delay so that it is an acceptable value.
        //
        //Parameters:
        //  delay - The sensor delay (in microseconds) to normalize.
        //
        //Returns:
        //  The normalized sensor delay (in microseconds) that can be stored on the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The sensor delay feature is not supported by this Node.
        virtual uint32 normalizeSensorDelay(uint32 delay) const;

        //API Function: numDamageAngles
        //    Gets the number of damage angles (see <FatigueOptions>) on this Node.
        //
        //Returns:
        //    The number of damage angles on this Node.
        virtual uint8 numDamageAngles() const;

        //API Function: numSnCurveSegments
        //    Gets the number of Sn Curve segments (see <FatigueOptions>) on this Node.
        //
        //Returns:
        //    The number of Sn Curve segments on this Node.
        virtual uint8 numSnCurveSegments() const;

        //API Function: numEventTriggers
        //  Gets the number of supported event triggers on this Node.
        //
        //Returns:
        //  The number of event triggers on this Node (0 if event sampling is not supported).
        virtual uint8 numEventTriggers() const;

        //API Function: defaultModes
        //    Gets a list of the <WirelessTypes::DefaultMode>s that are supported by this Node.
        //
        //Returns:
        //    A vector of <WirelessTypes::DefaultMode>s that are supported by this Node.
        virtual const WirelessTypes::DefaultModes defaultModes() const;

        //API Function: dataCollectionMethods
        //    Gets a list of the <WirelessTypes::DataCollectionMethod>s that are supported by this Node.
        //
        //Returns:
        //    A vector of <WirelessTypes::DataCollectionMethod>s that are supported by this Node.
        virtual const WirelessTypes::DataCollectionMethods dataCollectionMethods() const;

        //API Function: dataFormats
        //    Gets a list of the <WirelessTypes::DataFormat>s that are supported by this Node.
        //
        //Returns:
        //    A vector of <WirelessTypes::DataFormat>s that are supported by this Node.
        virtual const WirelessTypes::DataFormats dataFormats() const;

        //API Function: samplingModes
        //    Gets a list of the <WirelessTypes::SamplingMode>s that are supported by this Node.
        //
        //Returns:
        //    A vector of <WirelessTypes::SamplingMode>s that are supported by this Node.
        virtual const WirelessTypes::SamplingModes samplingModes() const;

        //API Function: sampleRates
        //    Gets a list of the <WirelessTypes::WirelessSampleRate>s that are supported by this Node for the given sampling mode.
        //
        //Parameters:
        //    samplingMode - The <WirelessTypes::SamplingMode> to get the sample rates for.
        //    dataCollectionMethod - The <WirelessTypes::DataCollectionMethod> to get the sample rates for.
        //    dataMode - The <WirelessTypes::DataMode> to get the sample rates for.
        //
        //Returns:
        //    A vector of <WirelessTypes::WirelessSampleRate>s that are supported by this Node for the given sampling mode and data collection method.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The <WirelessTypes::SamplingMode> is not supported by this Node.
        //                            The <WirelessTypes::DataCollectionMethod> is not supported by this Node.
        virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const;

        //API Function: derivedDataRates
        //  Gets a list of the <WirelessTypes::WirelessSampleRate>s that are supported by this Node for Derived Channels.
        //  These are the rates that the Derived Data will be calculated/sent. The standard <sampleRates> still apply
        //  in derived mode and control the sample rate of the raw channels used in the derived data calculations.
        //
        //Returns:
        //  A vector of <WirelessTypes::WirelessSampleRate>s that are supported by this Node for Derived Channels.
        virtual const WirelessTypes::WirelessSampleRates derivedDataRates() const;

        //API Function: transmitPowers
        //    Gets a list of the <WirelessTypes::TransmitPowers> that are supported by this Node, for the given <WirelessTypes::CommProtocol>.
        //    Note: This list is dependent on the <WirelessTypes::RegionCode> of the device. If this changes, this function should be called again.
        //
        //Parameters:
        //  commProtocol - The <WirelessTypes::CommProtocol> to get the transmit powers for.
        //
        //Returns:
        //    A vector of <WirelessTypes::TransmitPowers> that are supported by this Node.
        virtual const WirelessTypes::TransmitPowers transmitPowers(WirelessTypes::CommProtocol commProtocol) const;

        //API Function: transmitPowers
        //    Gets a list of the <WirelessTypes::TransmitPowers> that are supported by this Node, for the given <WirelessTypes::RegionCode> and <WirelessTypes::CommProtocol>.
        //
        //Parameters:
        //  region - The <WirelessTypes::RegionCode> to get the transmit powers for.
        //  commProtocol - The <WirelessTypes::CommProtocol> to get the transmit powers for.
        //
        //Returns:
        //    A vector of <WirelessTypes::TransmitPowers> that are supported by this Node.
        virtual const WirelessTypes::TransmitPowers transmitPowers(WirelessTypes::RegionCode region, WirelessTypes::CommProtocol commProtocol) const;

        //API Function: commProtocols
        //  Gets a list of <WirelessTypes::CommProtocols> that are supported by this Node.
        //
        //Returns:
        //  A vector of <WirelessTypes::CommProtocols> that are supported by this Node.
        virtual const WirelessTypes::CommProtocols commProtocols() const;

        //API Function: sensorOutputModes
        //  Gets a list of <WirelessTypes::SensorOutputModes> that are supported by this Node.
        //
        //Returns:
        //  A vector of <WirelessTypes::SensorOutputModes> that are supported by this Node.
        virtual const WirelessTypes::SensorOutputModes sensorOutputModes() const;

        //API Function: cfcFilters
        //  Gets a list of <WirelessTypes::ChannelFrequencyClass> options that are supportedby this Node.
        //
        //Returns:
        //  A vector of <WirelessTypes::ChannelFrequencyClass> options that are supported by this Node.
        virtual const WirelessTypes::CfcFilters cfcFilters() const;

        //API Function: histogramTransmitRates
        //    Gets a list of the Histogram Transmit Rates that are supported by this Node.
        //
        //Returns:
        //    A vector of <WirelessTypes::WirelessSampleRate>s representing the Histogram Transmit Rates that are supported by this Node.
        virtual const WirelessTypes::WirelessSampleRates histogramTransmitRates() const;

        //API Function: fatigueModes
        //    Gets a list of the <WirelessTypes::FatigueMode>s that are supported by this Node.
        //
        //Returns:
        //    A vector of <WirelessTypes::FatigueModes> supported by the Node.
        virtual const WirelessTypes::FatigueModes fatigueModes() const;

        //API Function: antiAliasingFilters
        //    Gets a list of the Anti-Aliasing <WirelessTypes::Filter>s that are supported by this Node.
        //
        //Returns:
        //    A vector of Anti-Aliasing <WirelessTypes::Filters> supported by the Node.
        virtual const WirelessTypes::Filters antiAliasingFilters() const;

        //API Function: lowPassFilters
        //    Gets a list of the Low-Pass <WirelessTypes::Filter>s that are supported by this Node.
        //
        //Returns:
        //    A vector of Low-Pass <WirelessTypes::Filters> supported by the Node.
        virtual const WirelessTypes::Filters lowPassFilters() const;

        //API Function: highPassFilters
        //    Gets a list of the High-Pass <WirelessTypes::Filter>s that are supported by this Node.
        //
        //Returns:
        //    A vector of <WirelesTypes::HighPassFilters> supported by the Node.
        virtual const WirelessTypes::HighPassFilters highPassFilters() const;

        //API Function: storageLimitModes
        //  Gets a list of the <WirelessTypes::StorageLimitModes> that are supported by this Node.
        //
        //Returns:
        //  A vector of <WirelessTypes::StorageLimitModes> supported by the Node.
        virtual const WirelessTypes::StorageLimitModes storageLimitModes() const;

        //API Function: inputRanges
        //  Gets a list of <InputRanges> that are supported by this Node for the specified channel mask.
        //
        //Parameters:
        //  channels - The <ChannelMask> of the channel group to get the supported input ranges for.
        //
        //Returns:
        //  A vector of <InputRanges> that are supported by this Node.
        virtual const InputRanges inputRanges(const ChannelMask& channels) const;

        //API Function: inputRanges
        //  Gets a list of <WirelessTypes::InputRanges> that are supported by this Node for the specified channel mask, for the given Excitation <WirelessTypes::Voltage>.
        //
        //Parameters:
        //  channels - The <ChannelMask> of the channel group to get the supported input ranges for.
        //  excitationVoltage - The Excitation <WirelessTypes::Voltage> to get the input ranges for.
        //
        //Returns:
        //  A vector of <InputRanges> that are supported by this Node.
        virtual const InputRanges inputRanges(const ChannelMask& channels, WirelessTypes::Voltage excitationVoltage) const;

        //API Function: dataModes
        //  Gets a list of <WirelessTypes::DataModes> that are supported by this Node.
        //
        //Returns:
        //  A vector of <WirelessTypes::DataModes> supported by the Node.
        virtual const WirelessTypes::DataModes dataModes() const;

        //API Function: transducerTypes
        //  Gets a list of <WirelessTypes::TransducerTypes> that are supported by this Node.
        //
        //Returns:
        //  A vector of <WirelessTypes::TransducerTypes> supported by the Node.
        virtual const WirelessTypes::TransducerTypes transducerTypes() const;

        //API Function: channelsPerDerivedCategory
        //  Gets a map of <WirelessTypes::DerivedCategory> to <ChannelMask>s that are supported by this Node.
        //  The ChannelMask indicates the raw channels that are available for the derived category.
        //
        //Returns:
        //  A <WirelessTypes::DerivedChannelMasks> map of <WirelessTypes::DerivedCategory> to supported <ChannelMask>s.
        virtual const WirelessTypes::DerivedChannelMasks channelsPerDerivedCategory() const;

        //API Function: excitationVoltages
        //  Gets a list of <WirelessTypes::Voltages> that are supported by the Node for configuration.
        //
        //Returns:
        //  A vector of <WirelessTypes::Voltage>s supported by the Node for configuration
        virtual const WirelessTypes::Voltages excitationVoltages() const;

        //API Function: adcVoltageInputType
        //  Gets the input voltage type of the ADC for this node.
        //
        //Returns:
        //  The <WirelessTypes::VoltageType> that represents the structure of the node's ADC.
        virtual const WirelessTypes::VoltageType adcVoltageInputType() const;

        //API Function: maxTransmitPower
        //  Gets the maximum <WirelessTypes::TransmitPower> that is supported for the given parameters.
        //
        //Parameters:
        //  region - The <WirelessTypes::RegionCode> of the device.
        //  commProtocol - The <WirelessTypes::CommProtocol> of the device.
        //
        //Returns:
        //  The max <WirelessTypes::TransmitPower> that is suppported for the given parameters.
        virtual WirelessTypes::TransmitPower maxTransmitPower(WirelessTypes::RegionCode region, WirelessTypes::CommProtocol commProtocol) const;

        //API Function: maxTransmitPower
        //  Gets the maximum <WirelessTypes::TransmitPower> that is supported for the given parameters, using the Node's current region code.
        //
        //Parameters:
        //  commProtocol - The <WirelessTypes::CommProtocol> of the device.
        //
        //Returns:
        //  The max <WirelessTypes::TransmitPower> that is suppported for the given parameters, and the Node's current region code.
        virtual WirelessTypes::TransmitPower maxTransmitPower(WirelessTypes::CommProtocol commProtocol) const;

        //API Function: minTransmitPower
        //  Gets the minimum <WirelessTypes::TransmitPower> that is supported for the given parameters.
        //
        //Parameters:
        //  region - The <WirelessTypes::RegionCode> of the device.
        //  commProtocol - The <WirelessTypes::CommProtocol> of the device.
        //
        //Returns:
        //  The min <WirelessTypes::TransmitPower> that is suppported for the given parameters.
        virtual WirelessTypes::TransmitPower minTransmitPower(WirelessTypes::RegionCode region, WirelessTypes::CommProtocol commProtocol) const;

        //API Function: minTransmitPower
        //  Gets the minimum <WirelessTypes::TransmitPower> that is supported for the given parameters, using the Node's current region code.
        //
        //Parameters:
        //  commProtocol - The <WirelessTypes::CommProtocol> of the device.
        //
        //Returns:
        //  The min <WirelessTypes::TransmitPower> that is suppported for the given parameters, and the Node's current region code.
        virtual WirelessTypes::TransmitPower minTransmitPower(WirelessTypes::CommProtocol commProtocol) const;

    protected:
        virtual bool hasMaxSampleRatePerFilterAndAdcChCount() const;

        //Function: supportsNewTransmitPowers
        //    Checks if the Node supports the new transmit powers (true), or the old ones (false).
        virtual bool supportsNewTransmitPowers() const;

        //Function: supportsAutoBalance2
        //    Checks if the Node supports the AutoBalance (Version 2) command.
        virtual bool supportsAutoBalance2() const;

        //Function: supportsSleepIntervalSeconds
        //    Checks if the Node supports a sleep interval eeprom directly in seconds.
        virtual bool supportsSleepIntervalSeconds() const;

        //Function: supportsEepromCommitViaRadioReset
        //    Checks if eeprom changes can be committed by only cycling the radio, instead of cycling power.
        virtual bool supportsEepromCommitViaRadioReset() const;

        //Function: supportsFlashId
        //  Checks if the Node supports the Flash ID eeprom.
        virtual bool supportsFlashId() const;

        //Function: supportsStorageLimitModeConfig
        //  Checks if the Node supports configuring storage limit mode.
        virtual bool supportsStorageLimitModeConfig() const;

        //Function: datalogDownloadVersion
        //  Gets the version of datalogging download to use.
        virtual uint8 datalogDownloadVersion() const;

        //Function: sensorDelayVersion
        //  Gets the version of sensor delay that the Node supports.
        virtual uint8 sensorDelayVersion() const;

        //Function: usesLegacySensorDelayAlwaysOn
        //  Checks if the Node uses the legacy value of 10,000 for always on (true)
        //  or the new value of 65,535 for always on (false).
        virtual bool usesLegacySensorDelayAlwaysOn() const;

        //Function: usesFloatEventTriggerVal
        //  Checks if the Node uses floating point for event trigger values.
        //  Older nodes used uint16 (bits).
        virtual bool usesFloatEventTriggerVal() const;

        //Function: onlySupportsRawDataMode
        //  Checks if the raw data mode is the only data mode supported.
        virtual bool onlySupportsRawDataMode() const;

        //Function: supportsDataModeEeprom
        //  Checks if the Data Mode eeprom location is supported.
        virtual bool supportsDataModeEeprom() const;

        //Function: supportsCommProtocolEeprom
        //  Checks if the Communication Protocol eeprom location is supported.
        virtual bool supportsCommProtocolEeprom() const;

        //Function: supportsEeprom1024AndAbove
        //  Checks if the Node supports reading eeprom location 1024 and above.
        virtual bool supportsEeprom1024AndAbove() const;
    };
}