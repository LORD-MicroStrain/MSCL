/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "BaseStation.h"
#include "WirelessModels.h"
#include "WirelessChannel.h"
#include "RadioFeatures.h"
#include "mscl/Version.h"
#include "Commands/AutoCal.h"
#include "Commands/WirelessProtocol.h"
#include "Configuration/ConfigIssue.h"
#include "Configuration/FatigueOptions.h"
#include "Configuration/HistogramOptions.h"
#include "Configuration/NodeEeprom.h"
#include "Configuration/NodeEepromHelper.h"

namespace mscl
{
	//forward declarations
	class NodeFeatures;	
	class WirelessNode;
	class WirelessNodeConfig;

	//Class: WirelessNode_Impl
	//	Contains the implementation logic for a WirelessNode.
	//	Most WirelessNode commands call these commands.
	class WirelessNode_Impl
	{
		friend class WirelessProtocol;

	private:
		WirelessNode_Impl();										//default constructor disabled
		WirelessNode_Impl(const WirelessNode_Impl&);				//copy constructor disabled
		WirelessNode_Impl& operator=(const WirelessNode_Impl&);		//assignment operator disabled

	public:
		//Constructor: WirelessNode_Impl
		//	Creates a WirelessNode_Impl object.
		//
		//Parameters:
		//	nodeAddress - the node address of the node
		//	basestation - the node's parent Base Station
		//	nodeFrequency - the <WirelessTypes::Frequency> that this node is believed to be on.
		WirelessNode_Impl(uint16 nodeAddress, const BaseStation& basestation, WirelessTypes::Frequency nodeFrequency);

	private:
		//Variable: m_address
		//	The address of the Node.
		NodeAddress m_address;

		//Variable: m_baseStation
		//	The Node's parent BaseStation.
		BaseStation m_baseStation;

		//Variable: m_eepromSettings
		//	The eeprom settings to use for the <NodeEeprom> object.
		NodeEepromSettings m_eepromSettings;

		//Variable: m_frequency
		//	The <WirelessTypes::Frequency> that this Node is believed to be on.
		mutable WirelessTypes::Frequency m_frequency;

		//Variable: m_protocol
		//	The <WirelessProtocol> containing all of the protocol commands and info for this Node.
		mutable std::unique_ptr<WirelessProtocol> m_protocol;

		//Variable: m_eeprom
		//	The <NodeEeprom> that handles reading and writing eeprom values with the Node and eeprom cache.
		mutable std::unique_ptr<NodeEeprom> m_eeprom;

		//Variable: m_eepromHelper
		//	The <NodeEepromHelper> used for high level reads and writes on the Node.
		mutable std::unique_ptr<NodeEepromHelper> m_eepromHelper;

		//Variable: m_features
		//	The <NodeFeatures> containing the features for this Node.
		mutable std::unique_ptr<NodeFeatures> m_features;

	private:
		//Function: determineProtocol
		//	Determines the <WirelessProtocol> to use based on the Node's firmware version.
		//
		//Returns:
		//	A unique_ptr containing the <WirelessProtocol> to use.
		std::unique_ptr<WirelessProtocol> determineProtocol() const;

		//Function: eeprom
		//	Gets a reference to the <NodeEeprom> for this Node.
		NodeEeprom& eeprom() const;

	public:
		//Function: eeHelper
		//	Gets a reference to the <NodeEepromHelper> for this Node.
		NodeEepromHelper& eeHelper() const;

		//Function: features
		//	Gets a reference to the <NodeFeatures> for this Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The Node model is not supported by MSCL.
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		virtual const NodeFeatures& features() const;

		//Function: protocol
		//	Gets a reference to the <WirelessProtocol> for this Node.
		//	Note: This requires communicating to the Node if
		//		  creating the protocol for the first time.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		virtual const WirelessProtocol& protocol() const;

		//Function: lastCommunicationTime
		//	Gets the <Timestamp> for the last time MSCL communicated with the Node.
		const Timestamp& lastCommunicationTime() const;

		//Function: setBaseStation
		//	Sets the node's parent Base Station, which will perform all communication with the Node.
		//
		//Parameters:
		//	basestation - the <BaseStation> object to be assigned to the Node, which will perform all communication with the Node.
		void setBaseStation(const BaseStation& basestation);

		//Function: getBaseStation
		//	Gets a reference to the <BaseStation> that is assigned to this Node.
		BaseStation& getBaseStation();

		//Function: hasBaseStation
		//	Checks whether the given <BaseStation> is the same <BaseStation> that is assigned to this Node.
		//
		//Parameters:
		//	basestation - The <BaseStation> to check if it is the same as this Node's parent <BaseStation>.
		//
		//Returns:
		//	true if the basestation is the same as this Node's parent <BaseStation>, false if it is different.
		bool hasBaseStation(const BaseStation& basestation) const;

		//Function: useGroupRead
		//	Enables or disables the use of group eeprom read when trying to read a single value (enabled by default).
		//
		//Parameters:
		//	useGroup - Whether the group eeprom read commands can be used (true) or whether to restrict to single eeprom reads (false).
		void useGroupRead(bool useGroup);

		//Function: readWriteRetries
		//	Sets the number of retry attempts for reading and writing with the Node.
		//
		//Parameters:
		//	numRetries - The number of retries to set for all reading and writing with the Node.
		void readWriteRetries(uint8 numRetries);

		//Function: useEepromCache
		//	Sets whether or not to utilize the eeprom cache when configuring this Node (default of enabled).
		//
		//Parameters:
		//	useCache - whether the eeprom cache should be used (true) or not (false).
		void useEepromCache(bool useCache);

		//Function: clearEepromCache
		//	Clears the eeprom cache for this Node.
		void clearEepromCache();

		//Function: nodeAddress
		//	Gets the node address of the Node.
		//
		//Returns:
		//	The node address of the Node.
		uint16 nodeAddress() const;

		//Function: frequency
		//	Gets the <WirelessTypes::Frequency> that the Node is believed to be on.
		//	If the frequency is unknown, it will be read from Eeprom.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::Frequency frequency() const;

		//Function: firmwareVersion
		//	Gets the firmware <Version> of the Node. 
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		virtual Version firmwareVersion() const;

		//Function: model
		//	Gets the <WirelessModels::NodeModel> of the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessModels::NodeModel model() const;

		//Function: serial
		//	Gets the serial number of the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		std::string serial() const;

		//Function: microcontroller
		//	Gets the <WirelessTypes::MicroControllerType> of the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::MicroControllerType microcontroller() const;

		//Function: radioFeatures
		//	Gets the <RadioFeatures> of the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		RadioFeatures radioFeatures() const;

		//Function: dataStorageSize
		//	Gets the number of bytes available for data storage on the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		uint64 dataStorageSize() const;

		//Function: regionCode
		//	Gets the region code currently set on the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::RegionCode regionCode() const;

		//Function: verifyConfig
		//	Checks whether the settings in the given <WirelessNodeConfig> are ok to be written to the Node.
		//	Options that are set will also be validated against each other. If an option that needs to be validated isn't
		//	currently set, it will be read from the Node.
		//
		//Parameters:
		//	config - The <WirelessNodeConfig> to verify the configuration for.
		//	outIssues - The <ConfigIssues> that will hold any resulting issues that are found with the configuration.
		//
		//Returns:
		//	true if the configuration is valid. false if the configuration is invalid and outIssues should be checked for more information.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		bool verifyConfig(const WirelessNodeConfig& config, ConfigIssues& outIssues) const;

		//Function: applyConfig
		//	Applies a <WirelessNodeConfig> to the Node.
		//
		//Parameters:
		//	config - The <WirelessNodeConfig> to apply to the Node.
		//
		//Exceptions:
		//	- <Error_InvalidNodeConfig>: Invalid Configuration. Check the exception for specific details.
		//	- <Error_NotSupported>: Attempted to write an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_NodeCommunication>: Failed to write to the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void applyConfig(const WirelessNodeConfig& config);

		//Function: getNumDatalogSessions
		//	Reads the number of datalog sessions that are currently stored on the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		uint16 getNumDatalogSessions() const;

		//Function: getDefaultMode
		//	Reads the <WirelessTypes::DefaultMode> that is currently set on the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::DefaultMode getDefaultMode() const;

		//Function: getInactivityTimeout
		//	Reads the user inactivity timeout (in seconds) that is currently set on the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		uint16 getInactivityTimeout() const;

		//Function: getCheckRadioInterval
		//	Reads the check radio interval that is currently set on the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		uint8 getCheckRadioInterval() const;

		//Function: getTransmitPower
		//	Reads the <WirelessTypes::TransmitPower> that is currently set on the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::TransmitPower getTransmitPower() const;

		//Function: getSamplingMode
		//	Gets the <WirelessTypes::SamplingMode> that is currently set on the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::SamplingMode getSamplingMode() const;

		//Function: getActiveChannels
		//	Gets the <ChannelMask> currently set on the Node, representing which channels are enabled and disabled.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		ChannelMask getActiveChannels() const;

		//Function: getSampleRate
		//	Gets the <WirelessTypes::WirelessSampleRate> currently set on the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::WirelessSampleRate getSampleRate() const;

		//Function: getNumSweeps
		//	Gets the number of sweeps currently set on the Node, which affects the duration of sampling if unlimited duration is disabled, 
		//	or the duration of each burst if the sampling mode is Sync Sampling Burst.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		uint32 getNumSweeps() const;

		//Function: getUnlimitedDuration
		//	Gets whether or not unlimited sampling duration is enabled on the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		bool getUnlimitedDuration() const;

		//Function: getDataFormat
		//	Gets the <WirelessTypes::DataFormat> that is currently set on the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::DataFormat getDataFormat() const;

		//Function: getDataCollectionMethod
		//	Gets the <WirelessTypes::DataCollectionMethod> that is currently set on the Node, representing how the data will be collected.
		//	Note: this has no affect if the sampling mode is Armed Datalogging, as this mode only operates in "log only".
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::DataCollectionMethod getDataCollectionMethod() const;

		//Function: getTimeBetweenBursts
		//	Gets the amount of time between each burst currently set on the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Burst Sampling mode is not supported by the Node.
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		TimeSpan getTimeBetweenBursts() const;

		//Function: getLostBeaconTimeout
		//	Gets the lost beacon timeout, in minutes, currently set on the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		uint16 getLostBeaconTimeout() const;

		//Function: getHardwareGain
		//	Reads the hardware gain of the specified <ChannelMask>.
		//
		//Parameters:
		//	mask - The <ChannelMask> of the hardware gain to read.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Hardware gain is not supported for the provided <ChannelMask>.
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		double getHardwareGain(const ChannelMask& mask) const;

		//Function: getHardwareOffset
		//	Reads the hardware offset of the specified <ChannelMask> currently set on the Node.
		//	See Also: <NodeFeatures::channelGroups>
		//
		//Parameters:
		//	mask - The <ChannelMask> of the hardware offset to read.
		//
		//Returns:
		//	The hardware offset currently set on the Node for the <ChannelMask>.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Hardware offset is not supported for the provided <ChannelMask>.
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		uint16 getHardwareOffset(const ChannelMask& mask) const;

		//Function: getLinearEquation
		//	Gets the linear equation of the specified <ChannelMask> currently set on the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Linear Equation is not supported for the provided <ChannelMask>.
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		LinearEquation getLinearEquation(const ChannelMask& mask) const;

		//Function: getUnit
		//	Reads the unit of the specified <ChannelMask> currently set on the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The Unit setting is not supported for the provided <ChannelMask>.
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::CalCoef_Unit getUnit(const ChannelMask& mask) const;

		//Function: getEquationType
		//	Reads the <WirelessTypes::CalCoef_EquationType> of the specified <ChannelMask> currently set on the Node.
		//
		//Returns:
		//	The <WirelessTypes::CalCoef_EquationType> currently set on the Node for this <ChannelMask>.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The Equation Type setting is not supported for the provided <ChannelMask>.
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::CalCoef_EquationType getEquationType(const ChannelMask& mask) const;

		//Function: getFilterSettlingTime
		//	Reads the filter settling time of the specified <ChannelMask>.
		//
		//Parameters:
		//	mask - The <ChannelMask> of the filter settling time to read.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Filter Settling Time is not supported for the provided <ChannelMask>.
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::SettlingTime getFilterSettlingTime(const ChannelMask& mask) const;

		//Function: getThermocoupleType
		//	Reads the <WirelessTypes::ThermocoupleType> of the specified <ChannelMask> currently set on the Node.
		//
		//Parameters:
		//	mask - The <ChannelMask> of the thermocouple type to read.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Thermocouple Type is not supported for the provided <ChannelMask>.
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::ThermocoupleType getThermocoupleType(const ChannelMask& mask) const;

		//Function: getFatigueOptions
		//	Reads the <FatigueOptions> currently set on the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: FatigueOptions configuration is not supported by this Node.
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		FatigueOptions getFatigueOptions() const;

		//Function: getHistogramOptions
		//	Reads the <HistogramOptions> currently set on the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: HistogramOptions configuration is not supported by this Node.
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		HistogramOptions getHistogramOptions() const;

	public:
		//Function: ping
		//	Performs a Long Ping command on the Node to check the communication between the Base Station and the Node.
		//
		//Returns:
		//	A <PingResponse> object that can be queried to get details of the ping command's response.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		virtual PingResponse ping();

		//Function: sleep
		//	Puts the Node into a low power, sleep mode.
		//	This command attempts to ping the node before sending the sleep command, to verify communication.
		//
		//Returns:
		//	true if the sleep command was successful, false otherwise.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		bool sleep();

		//Function: cyclePower
		//	Cycles the power on the Node. 
		//	Many configuration changes that are applied to the node do not take affect until the power is cycled.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to write an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_NodeCommunication>: Failed to write the value to the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void cyclePower();

		//Function: resetRadio
		//	Resets the radio on the Node. 
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to write the value to the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void resetRadio();

		//Function: changeFrequency
		//	Changes the radio frequency of the Node.
		//
		//Parameters:
		//	frequency - The <WirelessTypes::Frequency> to change the Node to.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to write an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_NodeCommunication>: Failed to write the value to the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		virtual void changeFrequency(WirelessTypes::Frequency frequency);

		//Function: setToIdle
		//	Attempts to set the Node to the Idle state so that it can be communicated with (stops it sampling, wakes it up if asleep).
		//
		//Returns:
		//	A <SetToIdleStatus> object that can be queried to get the status of the Set to Idle operation.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		virtual SetToIdleStatus setToIdle();

		//Function: erase
		//	Erases all logged data on the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to erase the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		virtual	void erase();

		//Function: startNonSyncSampling
		//	Starts the Node in Non-Synchronized Sampling Mode.
		//
		//Exceptions:
		//	- <Error_InvalidNodeConfig>: The Configuration of the Node is not set for Non-Sync Sampling Mode.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		virtual void startNonSyncSampling();

		//Function: clearHistogram
		//	Clears the Histogram on the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Histogram configuration is not supported by the Node.
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void clearHistogram();

		//Function: autoBalance
		//	Performs an Auto Balance command on a specified channel on the Node.
		//
		//Parameters:
		//	channelNumber - The channel number (ch1 = 1, ch8 = 8) to balance.
		//	option - The <WirelessTypes::AutoBalanceOption> to use (low, midscale, high).
		//
		//Exceptions:
		//	- <Error_NotSupported>: Autobalance is not supported by the Node or channel specified.
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void autoBalance(uint8 channelNumber, WirelessTypes::AutoBalanceOption option);

		//Function: autoCal_shmLink
		//	Performs automatic calibration for the SHM-Link Wireless Node.
		//
		//Returns:
		//	The <AutoCalResult_shmLink> containing the result of the auto cal operation.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Autocal configuration is not supported by the Node or The node is an invalid model for this command.
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		AutoCalResult_shmLink autoCal_shmLink();

		//Function: readEeprom
		//	Reads a uint16 from the given eeprom location of the node. This may use a page download or a read eeprom command.
		//	If the value stored in the eeprom cache is still valid, this will be returned instead.
		//
		//Parameters:
		//	location - The specific eeprom location to read from
		//
		//Returns:
		//	The uint16 value read from the specified EEPROM location
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported eeprom location.
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		virtual uint16 readEeprom(uint16 location) const;

		//Function: readEeprom
		//	Reads a value from the given <EepromLocation> of the node. This may use a page download or a read eeprom command.
		//	If the value stored in the eeprom cache is still valid, this will be returned instead.
		//
		//Parameters:
		//	location - The <EepromLocation> to read from.
		//
		//Returns:
		//	The value read from the specified EEPROM location as a <Value> object.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported eeprom location.
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		virtual Value readEeprom(const EepromLocation& location) const;

		//Function: writeEeprom
		//	Writes a uint16 to the given eeprom location of the node.
		//	If successful, the cache will be updated with the changed value as well.
		//
		//Parameters:
		//	location - The specific eeprom location to write to
		//	value - The uint16 value to write to the eeprom location
		//
		//Exceptions:
		//	- <Error_NotSupported>: Unsupported eeprom location or value.
		//	- <Error_NodeCommunication>: Failed to write the value to the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		virtual void writeEeprom(uint16 location, uint16 value);

		//Function: writeEeprom
		//	Writes a value to the given <EepromLocation> of the node.
		//	If successful, the cache will be updated with the changed value as well.
		//
		//Parameters:
		//	location - The specific <EepromLocation> to write to.
		//	value - The value to write to the eeprom location, as a <Value>.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Unsupported eeprom location or value.
		//	- <Error_NodeCommunication>: Failed to write the value to the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		virtual void writeEeprom(const EepromLocation& location, const Value& val);
	};
}