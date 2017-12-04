/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include <map>
#include <boost/optional.hpp>

#include "mscl/MicroStrain/Wireless/Configuration/DataModeMask.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"
#include "mscl/MicroStrain/Wireless/WirelessModels.h"
#include "mscl/MicroStrain/Wireless/LinearEquation.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"
#include "mscl/Exceptions.h"
#include "mscl/TimeSpan.h"
#include "ActivitySense.h"
#include "ConfigIssue.h"
#include "EventTriggerOptions.h"
#include "FatigueOptions.h"
#include "HistogramOptions.h"

namespace mscl
{
    //forward declarations
    class WirelessNode;
    class NodeFeatures;
    class NodeEepromHelper;

    //API Class: WirelessNodeConfig
    //    Class used for setting the configuration of <WirelessNode> objects.
    //    Set all the configuration values that you want to change, then verify and apply them to a Node.
    //
    //See also:
    //    <WirelessNode::applyConfig>
    class WirelessNodeConfig
    {
        friend class WirelessNode_Impl;

    public:
        //API Constructor: WirelessNodeConfig
        //    Creates a blank WirelessNodeConfig.
        WirelessNodeConfig();

        //API Constant: 
        //  SENSOR_DELAY_ALWAYS_ON - 0xFFFFFFFF - Value representing that the sensor delay is always on.
        static const uint32 SENSOR_DELAY_ALWAYS_ON = 0xFFFFFFFF;

    private:
        //Variable: m_defaultMode
        //    The <WirelessTypes::DefaultMode> to set.
        boost::optional<WirelessTypes::DefaultMode> m_defaultMode;

        //Variable: m_inactivityTimeout
        //    The inactivity timeout to set.
        boost::optional<uint16> m_inactivityTimeout;

        //Variable: m_checkRadioInterval
        //    The check radio interval to set.
        boost::optional<uint8> m_checkRadioInterval;

        //Variable: m_transmitPower
        //    The <WirelessTypes::TransmitPower> to set.
        boost::optional<WirelessTypes::TransmitPower> m_transmitPower;

        //Variable: m_samplingMode
        //    The <WirelessTypes::SamplingMode> to set.
        boost::optional<WirelessTypes::SamplingMode> m_samplingMode;

        //Variable: m_sampleRate
        //    The <WirelessTypes::WirelessSampleRate> to set.
        boost::optional<WirelessTypes::WirelessSampleRate> m_sampleRate;

        //Variable: m_activeChannels
        //    The <ChannelMask> to set.
        boost::optional<ChannelMask> m_activeChannels;

        //Variable: m_numSweeps
        //    The numbers of sweeps to set.
        boost::optional<uint32> m_numSweeps;

        //Variable: m_unlimitedDuration
        //    The unlimited duration flag to set.
        boost::optional<bool> m_unlimitedDuration;

        //Variable: m_dataFormat
        //    The <WirelessTypes::DataFormat> to set.
        boost::optional<WirelessTypes::DataFormat> m_dataFormat;

        //Variable: m_dataCollectionMethod
        //    The <WirelessTypes::DataCollectionMethod> to set.
        boost::optional<WirelessTypes::DataCollectionMethod> m_dataCollectionMethod;

        //Variable: m_timeBetweenBursts
        //    The amount of time between each burst to set.
        boost::optional<TimeSpan> m_timeBetweenBursts;

        //Variable: m_lostBeaconTimeout
        //    The lost beacon timeout to set.
        boost::optional<uint16> m_lostBeaconTimeout;

        //Variable: m_fatigueOptions
        //    The <FatigueOptions> to set.
        boost::optional<FatigueOptions> m_fatigueOptions;

        //Variable: m_histogramOptions
        //    The <HistogramOptions> to set.
        boost::optional<HistogramOptions> m_histogramOptions;

        //Variable: m_activitySense
        //    The <ActivitySense> to set.
        boost::optional<ActivitySense> m_activitySense;

        //Variable: m_eventTriggerOptions
        //  The <EventTriggerOptions> to set.
        boost::optional<EventTriggerOptions> m_eventTriggerOptions;

        //Variable: m_diagnosticInterval
        //  The interval of the diagnostic packet to set.
        boost::optional<uint16> m_diagnosticInterval;

        //Variable: m_storageLimitMode
        //  The <WirelessTypes::StorageLimitMode> to set.
        boost::optional<WirelessTypes::StorageLimitMode> m_storageLimitMode;

        //Variable: m_sensorDelay
        //  The sensor delay to set.
        boost::optional<uint32> m_sensorDelay;

        //Variable: m_gaugeResistance
        //  The gauge resistance to set.
        boost::optional<uint16> m_gaugeResistance;

        //Variable: m_numActiveGauges
        //  The number of active gauges to set.
        boost::optional<uint16> m_numActiveGauges;

        //Variable: m_dataMode
        //  The <DataMode> to set.
        boost::optional<WirelessTypes::DataMode> m_dataMode;

        //Variable: m_derivedDataRate
        //  The <WirelessTypes::WirelessSampleRate> for all Derived Channels to set.
        boost::optional<WirelessTypes::WirelessSampleRate> m_derivedDataRate;

        //Variable: m_commProtocol
        //  The <WirelessTypes::CommProtocol> to set.
        boost::optional<WirelessTypes::CommProtocol> m_commProtocol;

        //Variable: m_derivedChannelMasks
        //  The map of <WirelessTypes::DerivedChannelType> to <ChannelMask> to set for Derived Channels' Masks.
        std::map<WirelessTypes::DerivedChannelType, ChannelMask> m_derivedChannelMasks;

        //Variable: m_inputRanges
        //    The map of <ChannelMask> to <WirelessTypes::InputRange> to set.
        std::map<ChannelMask, WirelessTypes::InputRange> m_inputRanges;

        //Variable: m_hardwareOffsets
        //    The map of <ChannelMask> to hardware offsets to set.
        std::map<ChannelMask, uint16> m_hardwareOffsets;

        //Variable: m_antiAliasingFilters
        //  The map of <ChannelMask> to anti-aliasing filters to set.
        std::map<ChannelMask, WirelessTypes::Filter> m_antiAliasingFilters;

        //Variable: m_lowPassFilters
        //  The map of <ChannelMask> to low-pass filters to set.
        std::map<ChannelMask, WirelessTypes::Filter> m_lowPassFilters;

        //Variable: m_highPassFilters
        //  The map of <ChannelMask> to high-pass filters to set.
        std::map<ChannelMask, WirelessTypes::HighPassFilter> m_highPassFilters;

        //Variable: m_gaugeFactors
        //    The map of <ChannelMask> to gauge factors to set.
        std::map<ChannelMask, float> m_gaugeFactors;

        //Variable: m_settlingTimes
        //    The map of <ChannelMask> to <WirelessTypes::SettlingTime> to set.
        std::map<ChannelMask, WirelessTypes::SettlingTime> m_settlingTimes;

        //Variable: m_thermoTypes
        //    The map of <ChannelMask> to <WirelessTypes::ThermocoupleType> to set.
        std::map<ChannelMask, WirelessTypes::ThermocoupleType> m_thermoTypes;

        //Variable: m_linearEquations
        //    The map of <ChannelMask> to <LinearEquation> to set.
        std::map<ChannelMask, LinearEquation> m_linearEquations;

        //Variable: m_units
        //    The map of <ChannelMask> to <WirelessTypes::CalCoef_Unit> to set.
        std::map<ChannelMask, WirelessTypes::CalCoef_Unit> m_units;

        //Variable: m_equationTypes
        //    The map of <ChannelMask> to <WirelessTypes::CalCoef_EquationType> to set.
        std::map<ChannelMask, WirelessTypes::CalCoef_EquationType> m_equationTypes;

    private:
        //Function: curCommProtocol
        //    Gets the communication protocol currently set, or from the node if not set.
        WirelessTypes::CommProtocol curCommProtocol(const NodeEepromHelper& eeprom) const;

        //Function: curSamplingMode
        //    Gets the sampling mode currently set, or from the node if not set.
        WirelessTypes::SamplingMode curSamplingMode(const NodeEepromHelper& eeprom) const;

        //Function: curSampleRate
        //    Gets the sample rate currently set, or from the node if not set.
        WirelessTypes::WirelessSampleRate curSampleRate(const NodeEepromHelper& eeprom) const;

        //Function: curActiveChs
        //    Gets the active channels currently set, or from the node if not set.
        ChannelMask curActiveChs(const NodeEepromHelper& eeprom) const;

        //Function: curNumSweeps
        //    Gets the number of sweeps currently set, or from the node if not set.
        uint32 curNumSweeps(const NodeEepromHelper& eeprom) const;

        //Function: curUnlimitedDuration
        //    Gets the unlimited duration flag currently set, or from the node if not set.
        bool curUnlimitedDuration(const NodeEepromHelper& eeprom) const;

        //Function: curDataFormat
        //    Gets the data format currently set, or from the node if not set.
        WirelessTypes::DataFormat curDataFormat(const NodeEepromHelper& eeprom) const;

        //Function: curDataModeMask
        //    Gets the <DataModeMask> currently set, or from the node if not set.
        DataModeMask curDataModeMask(const NodeEepromHelper& eeprom) const;

        //Function: curDerivedRate
        //    Gets the derived <WirelessTypes::WirelessSampleRate> currently set, or from the node if not set.
        WirelessTypes::WirelessSampleRate curDerivedRate(const NodeEepromHelper& eeprom) const;

        //Function: curDataCollectionMethod
        //    Gets the data collection method currently set, or from the node if not set.
        WirelessTypes::DataCollectionMethod curDataCollectionMethod(const NodeEepromHelper& eeprom) const;

        //Function: curTimeBetweenBursts
        //    Gets the time between bursts currently set, or from the node if not set.
        TimeSpan curTimeBetweenBursts(const NodeEepromHelper& eeprom) const;

        //Function: curSettlingTime
        //    Gets the filter settling time currently set for the given <ChannelMask>, or from the node if not set.
        WirelessTypes::SettlingTime curSettlingTime(const ChannelMask& mask, const NodeEepromHelper& eeprom) const;

        //Function: curEventTriggerDuration
        //  Gets the event trigger options currently set, or from the node if not set.
        void curEventTriggerDurations(const NodeEepromHelper& eeprom, uint32& pre, uint32& post) const;

        //Function: curEventTriggerMask
        //  Gets the event trigger mask currently set, or from the node if not set.
        BitMask curEventTriggerMask(const NodeEepromHelper& eeprom) const;

        //Function: curLinearEquation
        //  Gets the linear equation currently set for the given <ChannelMask>, or from the node if not set.
        LinearEquation curLinearEquation(const ChannelMask& mask, const NodeEepromHelper& eeprom) const;

        //Function: curDerivedMask
        //  Gets the derived <ChannelMask> currently set for the given <WirelessTypes::DerivedChannelType>
        ChannelMask curDerivedMask(WirelessTypes::DerivedChannelType derivedChannel, const NodeEepromHelper& eeprom) const;

        //Function: curDerivedChannelMasks
        //  Gets the <WirelessTypes::DerivedChannelMasks> for all supported derived channel types.
        WirelessTypes::DerivedChannelMasks curDerivedChannelMasks(const NodeEepromHelper& eeprom, const NodeFeatures& features) const;

        //Function: isDerivedChannelEnabled
        //  Checks whether any channels are enabled for the <WirelessTypes::DerivedChannelType>.
        //  This first checks the config object, and the Node if not set in the config object.
        bool isDerivedChannelEnabled(WirelessTypes::DerivedChannelType derivedChannel, const NodeEepromHelper& eeprom, const NodeFeatures& features) const;

    private:
        //Function: checkValue
        //    Throws an exception if an optional value isn't set.
        //
        //Parameters:
        //    opt - The boost::optional value to check if it is set.
        //    valueName - The name of the value being checked. This will be included in the exception description if not set.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        template<typename T>
        void checkValue(const boost::optional<T>& opt, const std::string& valueName) const
        {
            if(!isSet(opt))
            {
                throw Error_NoData("The " + valueName + " option has not been set");
            }
        }

        //Function: isSet
        //    Checks whether the optional value is set.
        //
        //Parameters:
        //    opt - The boost::optional value to check if it is set.
        //
        //Returns:
        //    true if the value is set, false if it is not set.
        template<typename T>
        bool isSet(const boost::optional<T>& opt) const
        {
            return static_cast<bool>(opt);
        }

        //Function: isSet
        //    Checks whether a value is set in the ChannelMask option map for the given <ChannelMask>.
        //
        //Parameters:
        //    val - The map to check if any values are set within.
        //
        //Returns:
        //    true if the map contains at least 1 setting, false if it is empty.
        template<typename T>
        bool isSet(const std::map<ChannelMask, T>& map, const ChannelMask& mask) const
        {
            if(map.find(mask) == map.end())
            {
                return false;
            }

            return true;
        }

        //Function: isAnySet
        //    Checks whether there are any values set in the ChannelMask option map.
        //
        //Parameters:
        //    map - The map to check if any values are set within.
        //
        //Returns:
        //    true if the map contains at least 1 setting, false if it is empty.
        template<typename T>
        bool isAnySet(const std::map<ChannelMask, T>& map) const
        {
            return !map.empty();
        }

        //Function: getChannelMapVal
        //    Returns the value in the given map for the provided channel mask, and throws an exception if not found.
        //
        //Parameters:
        //    map - The map of <ChannelMask> to T value to search in.
        //    mask - The <ChannelMask> to look for.
        //    valueName - The name of the value being checked. This will be included in the exception description if not set.
        //
        //Returns:
        //    The value found for the <ChannelMask> in the provided map.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set for the provided <ChannelMask>.
        template<typename T>
        const T& getChannelMapVal(const std::map<ChannelMask, T>& map, const ChannelMask& mask, const std::string& valueName) const
        {
            try
            {
                return map.at(mask);
            }
            catch(std::out_of_range&)
            {
                throw Error_NoData("The " + valueName + " option has not been set for this ChannelMask.");
            }
        }
        
        //Function: setChannelMapVal
        //    Sets the value in the given map for the provided channel mask.
        //    This will update it if it already exists, and add an item to the map if it does not.
        //
        //Parameters:
        //    map - The map of <ChannelMask> to T value to add the value to.
        //    mask - The <ChannelMask> to set the value for.
        //    value - The value to set in the map.
        template<typename T>
        void setChannelMapVal(std::map<ChannelMask, T>& map, const ChannelMask& mask, T value)
        {
            auto itr = map.find(mask);

            if(itr != map.end())
            {
                itr->second = value;
            }
            else
            {
                map.emplace(mask, value);
            }
        }


        //Function: verifySupported
        //    Checks whether all the configuration values are supported by the node.
        //
        //Parameters:
        //    features - The <NodeFeatures> of the WirelessNode to verify the configuration for.
        //    eeprom - The <NodeEepromHelper> of the WirelessNode to use for communication.
        //    outIssues - The <ConfigIssues> holding any resulting issues that are found with the configuration. Must be empty when calling.
        //
        //Returns:
        //    true if no issues were found, false otherwise. If false, the outIssues parameter will hold all issues that were found.
        bool verifySupported(const NodeFeatures& features, const NodeEepromHelper& eeprom, ConfigIssues& outIssues) const;

        //Function: verifyConflicts
        //    Checks whether configuration values conflict with each other.
        //    If any of the config values that need to be checked aren't currently set,
        //    they will be read from the Node for verification.
        //
        //Parameters:
        //    features - The <NodeFeatures> of the WirelessNode to verify the configuration for.
        //    eeprom - The <NodeEepromHelper> of the WirelessNode to use for communication.
        //    outIssues - The <ConfigIssues> holding any resulting issues that are found with the configuration. Must be empty when calling.
        //
        //Returns:
        //    true if no issues were found, false otherwise. If false, the outIssues parameter will hold all issues that were found.
        bool verifyConflicts(const NodeFeatures& features, const NodeEepromHelper& eeprom, ConfigIssues& outIssues) const;

        //Function: findDerivedMaskConfigIssue
        //  Finds the <ConfigIssue::ConfigOption> for the provided <WirelessTypes::DerivedChannelType>.
        static ConfigIssue::ConfigOption findDerivedMaskConfigIssue(WirelessTypes::DerivedChannelType channel);

        //Function: apply
        //    Writes all of the configuration values that are set to a WirelessNode.
        //
        //Parameters:
        //    features - The <NodeFeatures> of the WirelessNode to write the config to.
        //    eeprom - The <NodeEepromHelper> of the WirelessNode to write the config to.
        //
        //Exceptions:
        //    - <Error_InvalidNodeConfig>: Invalid Configuration for the Node. Check the exception for specific details.
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        void apply(const NodeFeatures& features, NodeEepromHelper& eeprom) const;

        //Function: verify
        //    Checks whether the current settings are ok to be written to a given <WirelessNode>.
        //
        //Parameters:
        //    features - The <NodeFeatures> of the WirelessNode to verify the configuration for.
        //    eeprom - The <NodeEepromHelper> of the WirelessNode to use for communication.
        //    outIssues - The <ConfigIssues> holding any resulting issues that are found with the configuration.
        //
        //Returns:
        //    true if the configuration is valid. false if the configuration is invalid and outIssues should be checked for more information.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        bool verify(const NodeFeatures& features, const NodeEepromHelper& eeprom, ConfigIssues& outIssues) const;

    public:
        //API Function: defaultMode
        //    Gets the <WirelessTypes::DefaultMode> value in the Config, if set.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        WirelessTypes::DefaultMode defaultMode() const;

        //API Function: defaultMode
        //    Sets the <WirelessTypes::DefaultMode> value in the Config.
        void defaultMode(WirelessTypes::DefaultMode mode);

        //API Function: inactivityTimeout
        //    Gets the user inactivity timeout value in the Config, if set.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        uint16 inactivityTimeout() const;

        //API Function: inactivityTimeout
        //    Sets the user inactivity timeout value in the Config.
        //    This controls how many seconds before the Node goes to sleep when idle. (min of 5 seconds)
        //    Note: A value of 65535 (0xFFFF) disables the inactivity timeout so that the Node never goes to sleep.
        void inactivityTimeout(uint16 timeout);

        //API Function: checkRadioInterval
        //    Gets the check radio interval value in the Config, if set.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        uint8 checkRadioInterval() const;

        //API Function: checkRadioInterval
        //    Sets the check radio interval value (in seconds) in the Config.
        //    This controls how often the Node wakes up from sleep to check for commands.
        void checkRadioInterval(uint8 interval);

        //API Function: transmitPower
        //    Gets the <WirelessTypes::TransmitPower> value in the Config, if set.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        WirelessTypes::TransmitPower transmitPower() const;

        //API Function: transmitPower
        //    Sets the <WirelessTypes::TransmitPower> value in the Config.
        void transmitPower(WirelessTypes::TransmitPower power);

        //API Function: samplingMode
        //    Gets the <WirelessTypes::SamplingMode> value in the Config, if set.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        WirelessTypes::SamplingMode samplingMode() const;

        //API Function: samplingMode
        //    Sets the <WirelessTypes::SamplingMode> value in the Config.
        void samplingMode(WirelessTypes::SamplingMode mode);

        //API Function: sampleRate
        //    Gets the <WirelessTypes::WirelessSampleRate> value in the Config, if set.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        WirelessTypes::WirelessSampleRate sampleRate() const;

        //API Function: sampleRate
        //    Sets the <WirelessTypes::WirelessSampleRate> value in the Config.
        void sampleRate(WirelessTypes::WirelessSampleRate rate);

        //API Function: activeChannels
        //    Gets the <ChannelMask> value in the Config, if set.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        ChannelMask activeChannels() const;

        //API Function: activeChannels
        //    Sets the <ChannelMask> value in the Config.
        void activeChannels(const ChannelMask& channels);

        //API Function: numSweeps
        //    Gets the number of sweeps value in the Config, if set.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        uint32 numSweeps() const;

        //API Function: numSweeps
        //    Sets the number of sweeps value in the Config.
        //    This affects the duration of sampling if unlimited duration is disabled, or the duration of each burst if the sampling mode is Sync Sampling Burst.
        //  Note: The number of sweeps should be normalized before it is set, using <NodeFeatures::normalizeNumSweeps>.
        void numSweeps(uint32 sweeps);

        //API Function: unlimitedDuration
        //    Gets the value of the unlimited duration flag in the Config, if set.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        bool unlimitedDuration() const;

        //API Function: unlimitedDuration
        //    Sets the value of the unlimited duration flag in the Config.
        void unlimitedDuration(bool enable);

        //API Function: dataFormat
        //    Gets the <WirelessTypes::DataFormat> value in the Config, if set.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        WirelessTypes::DataFormat dataFormat() const;

        //API Function: dataFormat
        //    Sets the <WirelessTypes::DataFormat> in the Config.
        void dataFormat(WirelessTypes::DataFormat format);

        //API Function: dataCollectionMethod
        //    Gets the <WirelessTypes::DataCollectionMethod> value in the Config, if set.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        WirelessTypes::DataCollectionMethod dataCollectionMethod() const;

        //API Function: dataCollectionMethod
        //    Sets the <WirelessTypes::DataCollectionMethod> in the Config, representing how the data will be collected.
        //    Note: this has no affect if the sampling mode is Armed Datalogging, as this mode only operates in "log only".
        void dataCollectionMethod(WirelessTypes::DataCollectionMethod method);

        //API Function: timeBetweenBursts
        //    Gets the amount of time between each burst value in the Config, if set.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        TimeSpan timeBetweenBursts() const;

        //API Function: timeBetweenBursts
        //    Sets the amount of time between each burst in the Config.
        //    Note: This value should be normalized before it is set, using <NodeFeatures::normalizeTimeBetweenBursts>.
        void timeBetweenBursts(const TimeSpan& time);

        //API Function: lostBeaconTimeout
        //    Gets the lost beacon timeout in the Config, if set.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        uint16 lostBeaconTimeout() const;

        //API Function: lostBeaconTimeout
        //    Sets the lost beacon timeout in the Config.
        //    Note: This value should be within <NodeFeatures::minLostBeaconTimeout> and <NodeFeatures::maxLostBeaconTimeout>.
        //    Note: A value of 0 disables the lost beacon timeout.
        void lostBeaconTimeout(uint16 minutes);

        //API Function: inputRange
        //    Gets the <WirelessTypes::InputRange> for the given <ChannelMask> in the Config, if set.
        //
        //Parameters:
        //    mask - The <ChannelMask> to set the input range for.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        WirelessTypes::InputRange inputRange(const ChannelMask& mask) const;

        //API Function: inputRange
        //    Sets the input range for the given <ChannelMask> in the Config.
        void inputRange(const ChannelMask& mask, WirelessTypes::InputRange range);

        //API Function: hardwareOffset
        //    Gets the hardware offset for the given <ChannelMask> in the Config, if set.
        //
        //Parameters:
        //    mask - The <ChannelMask> to set the hardware offset for.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        uint16 hardwareOffset(const ChannelMask& mask) const;

        //API Function: hardwareOffset
        //    Sets the hardware offset for the given <ChannelMask> in the Config.
        void hardwareOffset(const ChannelMask& mask, uint16 offset);

        //API Function: antiAliasingFilter
        //    Gets the anti-aliasing <WirelessTypes::Filter> for the given <ChannelMask> in the Config, if set.
        //
        //Parameters:
        //    mask - The <ChannelMask> to set the anti-aliasing filter for.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        WirelessTypes::Filter antiAliasingFilter(const ChannelMask& mask) const;

        //API Function: antiAliasingFilter
        //    Sets the anti-aliasing filter for the given <ChannelMask> in the Config.
        void antiAliasingFilter(const ChannelMask& mask, WirelessTypes::Filter filter);

        //API Function: lowPassFilter
        //    Gets the low pass <WirelessTypes::Filter> for the given <ChannelMask> in the Config, if set.
        //
        //Parameters:
        //    mask - The <ChannelMask> to set the low pass filter for.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        WirelessTypes::Filter lowPassFilter(const ChannelMask& mask) const;

        //API Function: lowPassFilter
        //    Sets the low-pass filter for the given <ChannelMask> in the Config.
        void lowPassFilter(const ChannelMask& mask, WirelessTypes::Filter filter);

        //API Function: highPassFilter
        //    Gets the <WirelessTypes::HighPassFilter> for the given <ChannelMask> in the Config, if set.
        //
        //Parameters:
        //    mask - The <ChannelMask> to set the high pass filter for.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        WirelessTypes::HighPassFilter highPassFilter(const ChannelMask& mask) const;

        //API Function: highPassFilter
        //    Sets the high-pass filter for the given <ChannelMask> in the Config.
        void highPassFilter(const ChannelMask& mask, WirelessTypes::HighPassFilter filter);

        //API Function: gaugeFactor
        //    Gets the gauge factor for the given <ChannelMask> in the Config, if set.
        //
        //Parameters:
        //    mask - The <ChannelMask> to set the gauge factor for.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        float gaugeFactor(const ChannelMask& mask) const;

        //API Function: gaugeFactor
        //    Sets the gauge Factor for the given <ChannelMask> in the Config.
        void gaugeFactor(const ChannelMask& mask, float factor);

        //API Function: gaugeResistance
        //    Gets the gauge resistance in the Config, if set.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        uint16 gaugeResistance() const;

        //API Function: gaugeResistance
        //    Sets the gauge resistance in the Config.
        void gaugeResistance(uint16 resistance);

        //API Function: numActiveGauges
        //    Gets the number of active gauges in the Config, if set.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        uint16 numActiveGauges() const;

        //API Function: numActiveGauges
        //    Sets the number of active gauges in the Config.
        void numActiveGauges(uint16 numGauges);

        //API Function: linearEquation
        //    Gets the <LinearEquation> for the given <ChannelMask> in the Config, if set.
        //
        //Parameters:
        //    mask - The <ChannelMask> to set the linear equation for.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        const LinearEquation& linearEquation(const ChannelMask& mask) const;

        //API Function: linearEquation
        //    Sets the <LinearEquation> for the given <ChannelMask> in the Config.
        void linearEquation(const ChannelMask& mask, const LinearEquation& linearEquation);

        //API Function: unit
        //    Gets the <WirelessTypes::CalCoef_Unit> for the given <ChannelMask> in the Config, if set.
        //
        //Parameters:
        //    mask - The <ChannelMask> to set the linear equation for.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        WirelessTypes::CalCoef_Unit unit(const ChannelMask& mask) const;

        //API Function: unit
        //    Sets the <WirelessTypes::CalCoef_Unit> for the given <ChannelMask> in the Config.
        void unit(const ChannelMask& mask, WirelessTypes::CalCoef_Unit unit);

        //API Function: equationType
        //    Gets the <WirelessTypes::CalCoef_EquationType> for the given <ChannelMask> in the Config, if set.
        //
        //Parameters:
        //    mask - The <ChannelMask> to set the linear equation for.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        WirelessTypes::CalCoef_EquationType equationType(const ChannelMask& mask) const;

        //API Function: equationType
        //    Sets the <WirelessTypes::CalCoef_EquationType> for the given <ChannelMask> in the Config.
        void equationType(const ChannelMask& mask, WirelessTypes::CalCoef_EquationType equation);

        //API Function: filterSettlingTime
        //    Gets the <WirelessTypes::SettlingTime> for the given <ChannelMask> in the Config, if set.
        //
        //Parameters:
        //    mask - The <ChannelMask> to set the filter settling time for.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        WirelessTypes::SettlingTime filterSettlingTime(const ChannelMask& mask) const;

        //API Function: filterSettlingTime
        //    Sets the <WirelessTypes::SettlingTime> for the given <ChannelMask> in the Config.
        void filterSettlingTime(const ChannelMask& mask, WirelessTypes::SettlingTime settlingTime);

        //API Function: thermocoupleType
        //    Gets the <WirelessTypes::ThermocoupleType> for the given <ChannelMask> in the Config, if set.
        //
        //Parameters:
        //    mask - The <ChannelMask> to set the thermocouple type for.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        WirelessTypes::ThermocoupleType thermocoupleType(const ChannelMask& mask) const;

        //API Function: thermocoupleType
        //    Sets the <WirelessTypes::ThermocoupleType> for the given <ChannelMask> in the Config.
        void thermocoupleType(const ChannelMask& mask, WirelessTypes::ThermocoupleType type);

        //API Function: fatigueOptions
        //    Gets the <FatigueOptions> currently set in the Config.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        const FatigueOptions& fatigueOptions() const;

        //Api Function: fatigueOptions
        //    Sets the <FatigueOptions> in the Config.
        void fatigueOptions(const FatigueOptions& fatigueOpts);

        //API Function: histogramOptions
        //    Gets the <HistogramOptions> currently set in the Config.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        const HistogramOptions& histogramOptions() const;

        //API Function: histogramOptions
        //    Sets the <HistogramOptions> in the Config.
        void histogramOptions(const HistogramOptions& histogramOpts);

        //API Function: activitySense
        //    Gets the <ActivitySense> currently set in the Config.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        const ActivitySense& activitySense() const;

        //API Function: activitySense
        //    Sets the <ActivitySense> in the Config.
        void activitySense(const ActivitySense& activitySenseOpts);

        //API Function: eventTriggerOptions
        //  Gets the <EventTriggerOptions> currently set in the Config.
        //
        //Exceptions:
        //  <Error_NoData> - The requested value has not been set.
        const EventTriggerOptions& eventTriggerOptions() const;

        //API Function: eventTriggerOptions
        //  Sets the <EventTriggerOptions> in the Config.
        void eventTriggerOptions(const EventTriggerOptions& eventTriggerOpts);

        //API Function: diagnosticInterval
        //  Gets the diagnostic info interval (in seconds) currently set in the Config.
        //  A value of 0 is disabled.
        //
        //Exceptions:
        //  <Error_NoData> - The requested value has not been set.
        uint16 diagnosticInterval() const;

        //API Function: diagnosticInterval
        //  Sets the diagnostic info interval (in seconds) in the Config.
        //  A value of 0 disables the diagnostic info.
        void diagnosticInterval(uint16 interval);

        //API Function: storageLimitMode
        //  Gets the <WirelessTypes::StorageLimitMode> currently set in the Config.
        //
        //Exceptions:
        //  <Error_NoData> - The requested value has not been set.
        WirelessTypes::StorageLimitMode storageLimitMode() const;

        //API Function: storageLimitMode
        //  Sets the <WirelessTypes::StorageLimitMode> in the Config.
        void storageLimitMode(WirelessTypes::StorageLimitMode mode);

        //API Function: sensorDelay
        //  Gets the sensor delay (in microseconds) currently set in the Config.
        //  Note: A value of <WirelessNodeConfig::SENSOR_DELAY_ALWAYS_ON> indicates that the sensor is always on.
        //
        //Exceptions:
        //  <Error_NoData> - The requested value has not been set.
        uint32 sensorDelay() const;

        //API Function: sensorDelay
        //  Sets the sensor delay (in microseconds) in the Config.
        //  Note: Use a value of <WirelessNodeConfig::SENSOR_DELAY_ALWAYS_ON> to set the sensor always on.
        void sensorDelay(uint32 delay);

        //API Function: dataMode
        //  Gets the <WirelessTypes::DataMode> currently set in the Config.
        //
        //Exceptions:
        //  <Error_NoData> - The requested value has not been set.
        WirelessTypes::DataMode dataMode() const;

        //API Function: dataMode
        //  Sets the <WirelessTypes::DataMode> in the Config.
        void dataMode(WirelessTypes::DataMode mode);

        //API Function: derivedDataRate
        //  Gets the <WirelessTypes::WirelessSampleRate> for the Derived Channels currently set in the Config.
        //
        //Exceptions:
        //  <Error_NoData> - The requested value has not been set.
        WirelessTypes::WirelessSampleRate derivedDataRate() const;

        //API Function: derivedDataRate
        //  Sets the <WirelessTypes::WirelessSampleRate> for the Derived Channels in the Config.
        void derivedDataRate(WirelessTypes::WirelessSampleRate rate);

        //API Function: derivedChannelMask
        //  Gets the <ChannelMask> for a specified <WirelessTypes::DerivedChannelType> currently set in the Config.
        //
        //Exceptions:
        //  <Error_NoData> - The requested value has not been set.
        ChannelMask derivedChannelMask(WirelessTypes::DerivedChannelType derivedChannelType) const;

        //API Function: derivedChannelMask
        //  Sets the <ChannelMask> for a specified <WirelessTypes::DerivedChannelType> in the Config.
        void derivedChannelMask(WirelessTypes::DerivedChannelType derivedChannelType, const ChannelMask& mask);

        //API Function: communicationProtocol
        //  Gets the <WirelessTypes::CommProtocol> currently set in the Config.
        //
        //Exceptions:
        //  <Error_NoData> - The requested value has not been set.
        WirelessTypes::CommProtocol communicationProtocol() const;

        //API Function: communicationProtocol
        //  Sets the <WirelessTypes::CommProtocol> in the Config.
        void communicationProtocol(WirelessTypes::CommProtocol commProtocol);

    public:
        //Function: flashBandwidth
        //  Gets the flash bandwidth that is used by the provided settings.
        //
        //Parameters:
        //  rawSampleRate - The <WirelessTypes::WirelessSampleRate>.
        //  dataFormat - The <WirelessTypes::DataFormat>.
        //  numRawChannels - The number of active channels.
        static float flashBandwidth(WirelessTypes::WirelessSampleRate rawSampleRate, WirelessTypes::DataFormat dataFormat, uint8 numRawChannels, uint32 derivedBytesPerSweep, WirelessTypes::WirelessSampleRate derivedRate);

        //Function: flashBandwidth
        //  Gets the flash bandwidth that is used by the provided settings.
        //
        //Parameters:
        //  rawSampleRate - The <WirelessTypes::WirelessSampleRate>.
        //  dataFormat - The <WirelessTypes::DataFormat>.
        //  numRawChannels - The number of active channels.
        //  numSweeps - The number of sweeps per burst.
        //  timeBetweenBursts - The <TimeSpan> representing the time between bursts.
        static float flashBandwidth_burst(WirelessTypes::WirelessSampleRate rawSampleRate,
                                          WirelessTypes::DataFormat dataFormat,
                                          uint8 numRawChannels,
                                          uint32 derivedBytesPerSweep,
                                          uint32 numSweeps,
                                          const TimeSpan& timeBetweenBursts);
    };
}
