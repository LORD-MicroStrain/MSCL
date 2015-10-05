/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
//PUBLIC_HEADER
#pragma once

#include "mscl/Communication/Connection.h"
#include "mscl/MicroStrain/Wireless/DataSweep.h"
#include "mscl/MicroStrain/Wireless/NodeDiscovery.h"
#include "Commands/BaseStation_BeaconStatus.h"
#include "Commands/LongPing.h"
#include "Commands/SetToIdleStatus.h"
#include "Configuration/ConfigIssue.h"
#include "BaseStationButton.h"
#include "BaseStationAnalogPair.h"
#include "WirelessTypes.h"
#include "WirelessModels.h"
#include "mscl/Version.h"

namespace mscl
{
	//forward declarations
	class AutoCalResult;
	class BaseStation_Impl;
	class BaseStationFeatures;
	class BaseStationEeprom;
	class BaseStationEepromHelper;
	class BaseStationConfig;
	class ResponsePattern;
	class WirelessProtocol;

	//API Class: BaseStation
	//	Represents a MicroStrain Base Station object
	class BaseStation
	{ 
	public:
		//=====================================================================================================
		//API Constants: Default Timeouts
		//	BASE_COMMANDS_DEFAULT_TIMEOUT	- 1100 ms	- The default timeout for a base station command (in milliseconds)
		//	NODE_COMMANDS_DEFAULT_TIMEOUT	- 1000 ms	- The default timeout for a node command (in milliseconds)
		//	BROADCAST_NODE_ADDRESS			- 65535		- The address to use for performing Broadcast commands that will be heard by all <WirelessNode>s on the frequency.
		//=====================================================================================================
		static const uint64 BASE_COMMANDS_DEFAULT_TIMEOUT = 1100;
		static const uint64 NODE_COMMANDS_DEFAULT_TIMEOUT = 1000;
		static const NodeAddress BROADCAST_NODE_ADDRESS = 65535;

	public:
		//API Constructor: BaseStation
		//  Creates a BaseStation object.
		//	
		//Parameters:
		//	connection - The <Connection> object used for communication
		//	baseTimeout - The timeout to use for base station commands (optional, default of <BASE_COMMANDS_DEFAULT_TIMEOUT> (2 seconds))
		//
		//Exceptions:
		//	- <Error_Connection>: A problem occured with the Connection.
		explicit BaseStation(Connection& connection, uint64 baseTimeout = BASE_COMMANDS_DEFAULT_TIMEOUT);

		//Destructor: ~BaseStation
		//	Destroys a BaseStation object
		virtual ~BaseStation() {};

#ifndef SWIG
		BaseStation(std::shared_ptr<BaseStation_Impl> impl); //constructor with direct underlying implementation for this class.

		//Function: eepromHelper
		//	Gets a reference to the <BaseStationEepromHelper> for this BaseStation.
		BaseStationEepromHelper& eepromHelper() const;

		//Function: doCommand
		//	Performs a custom command and waits for the response.
		//	When completed, the <ResponsePattern> parameter will contain any result information.
		//	For a full explanation, see the <ResponsePattern> class.
		//
		//Parameters:
		//	response - A reference to a custom class that was inherited from the <ResponsePattern> base class.
		//	cmdBytes - The <ByteStream> containing the command bytes to send.
		//	timeout - The maximum timeout to use for waiting for the response.
		//
		//Returns:
		//	true if the command was successful (response.success() is true), false otherwise.
		bool doCommand(ResponsePattern& response, const ByteStream& cmdBytes, uint64 timeout);

		//Operator: ==
		//	Checks that two BaseStation objects are equal.
		//
		//Returns:
		//	true if the two BaseStation objects are identical, false otherwise.
		bool operator==(const BaseStation& src) const;

		//Operator: !=
		//	Checks that two BaseStation objects are not equal.
		//
		//Returns:
		//	true if the two BaseStation are not identical, false otherwise.
		bool operator!=(const BaseStation& src) const;
#endif

	private:
		BaseStation();		//default constructor disabled

	private:
		//Variable: m_impl
		//	The <BaseStation_Impl> class that contains all the implementation logic for the BaseStation class.
		std::shared_ptr<BaseStation_Impl> m_impl;

	public:
		//API Function: deviceName
		//	Static function for creating the universal basestation name that should be used for SensorCloud.
		//
		//Parameters:
		//	serial - The serial of the basestation. This should be identical to calling the <serial> function on a <BaseStation> object.
		//
		//Returns:
		//	The universal basestationName.
		static std::string deviceName(const std::string& serial);

		//API Function: features
		//	Gets a reference to the <BaseStationFeatures> for this BaseStation.
		//	Note: This will be invalid when the BaseStation is destroyed.
		//
		//Returns:
		//	<BaseStationFeatures> containing the features for this BaseStation.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The BaseStation model is not supported by MSCL.
		//	- <Error_Communication>: Failed to communicate with the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		const BaseStationFeatures& features() const;

		//API Function: lastCommunicationTime
		//	Gets the <Timestamp> for the last time MSCL communicated with the BaseStation.
		//	Note: EEPROM reads using the cache, and data collection, will not update this timestamp.
		//
		//Returns:
		//	A <Timestamp> representing the last time MSCL communicated with the BaseStation. This will be a Timestamp of 0 if never communicated with.
		const Timestamp& lastCommunicationTime() const;

		//API Function: readWriteRetries
		//	Sets the number of retry attempts for reading and writing with the BaseStation.
		//	By default, the number of retries is 0.
		//	Note:	The timeout that is set per command will be per read and write attempt, meaning
		//			this retry number is multiplied by the timeout for your overall timeout.
		//
		//Parameters:
		//	numRetries - The number of retries to set for all reading and writing with the BaseStation.
		void readWriteRetries(uint8 numRetries);

		//API Function: useEepromCache
		//	Sets whether or not to utilize the eeprom cache when configuring this BaseStation (enabled by default). This can be enabled/disabled at any time.
		//	It is highly recommended to have eeprom caching be enabled.
		//	Note:	The eeprom cache stores the last known value that was written to / read from the BaseStation for each eeprom location. If this is enabled,
		//			any reads will get the last known value from the cache if it exists, and any writes will not write to the BaseStation if the
		//			value attempting to be written is the same as that stored in the cache. Caching of these values will still be performed if this is disabled,
		//			however, read and write operations will then always reach out to the actual device.
		//
		//Parameters:
		//	useCache - whether the eeprom cache should be used (true) or not (false).
		void useEepromCache(bool useCache);

		//API Function: clearEepromCache
		//	Clears the eeprom cache for this BaseStation.
		void clearEepromCache();

		//API Function: frequency
		//	Gets the <WirelessTypes::Frequency> representing the radio frequency of this BaseStation.
		//	If the frequency is unknown, it will be read from the BaseStation.
		//
		//Returns:
		//	The <WirelessTypes::Frequency> that this BaseStation is on.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_Communication>: Failed to read the value from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		WirelessTypes::Frequency frequency() const;

		//API Function: firmwareVersion
		//	Gets the firmware version of the BaseStation.
		//
		//Returns:
		//	A <Version> representing the firmware version of the BaseStation.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_Communication>: Failed to read the value from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		Version firmwareVersion() const;

		//API Function: model
		//	Gets the model of the BaseStation.
		//
		//Returns:
		//	A <WirelessModels::BaseModel> representing the model of the BaseStation.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_Communication>: Failed to read the value from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessModels::BaseModel model() const;

		//API Function: serial
		//	Gets the serial number of the BaseStation.
		//
		//Returns:
		//	A string representing the serial number of the BaseStation.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_Communication>: Failed to read the value from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		std::string serial() const;

		//API Function: name
		//	Gets the name of the BaseStation. This is the universal basestation name that should be used for SensorCloud.
		//	This is the same as calling <BaseStation::deviceName>.
		//
		//Returns:
		//	The universal basestation name.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_Communication>: Failed to read the value from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		std::string name() const;

		//API Function: microcontroller
		//	Gets the microcontroller of the BaseStation.
		//
		//Returns:
		//	A <WirelessTypes::MicroControllerType> representing the microcontroller of the BaseStation.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_Communication>: Failed to read the value from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::MicroControllerType microcontroller() const;

		//API Function: getNextData
		//	Gets the next single <DataSweep> of sampled data (LDC, Sync Sampling, etc) collected by this BaseStation.
		//	See the <getData> function for getting all available data packets that are in the buffer.
		//
		//Parameters:
		//	timeout - the timeout, in milliseconds, to wait for the next data sweep if necessary (default of 0)
		//
		//Returns:
		//	The next <DataSweep> that was collected by this BaseStation object
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		//	- <Error_NoData>: No data packets were found
		DataSweep getNextData(uint32 timeout = 0);

		//API Function: getData
		//	Gets up to the requested amount of <DataSweep>s of sampled data that was collected by this BaseStation.
		//
		//Parameters:
		//	timeout - The timeout, in milliseconds, to wait for data if necessary (default of 0).
		//	maxSweeps - The maximum number of sweeps to return. If this is 0 (default), all sweeps will be returned.
		//
		//Returns:
		//	A <DataSweeps> object containing all the data sweeps that are available up to the requested number of max sweeps. 
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		DataSweeps getData(uint32 timeout = 0, uint32 maxSweeps = 0);

		//API Function: totalData
		//	Gets the number of <DataSweep>s that are currently in the data buffer.
		//
		//Returns:
		//	The number of <DataSweep>s that are currently in the data buffer.
		uint32 totalData();

		//API Function: getNodeDiscoveries
		//	Gets the group of Node Discoveries that were collected by this base station.
		//	Calling this function clears out the Node Discovery buffer, so successively calling this will give you new Node Discoveries.
		//
		//Returns:
		//	A <NodeDiscoveries> container, holding all the Node Discoveries that were collected by this base station.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		NodeDiscoveries getNodeDiscoveries();

		//API Function: baseCommandsTimeout
		//	Sets the timeout to use when waiting for responses from base station commands
		//
		//Parameters:
		//	timeout - The timeout (in milliseconds) to set for base station commands
		void baseCommandsTimeout(uint64 timeout);

		//API Function: nodeCommandsTimeout
		//	Sets the timeout to use when waiting for responses from node commands
		//
		//Parameters:
		//	timeout - The timeout (in milliseconds) to set for node commands
		void nodeCommandsTimeout(uint64 timeout);

		//API Function: baseCommandsTimeout
		//	Gets the current timeout to use when waiting for responses from base station commands.
		//
		//Returns:
		// The timeout (in milliseconds) set for base station commands.
		uint64 baseCommandsTimeout() const;

		//API Function: nodeCommandsTimeout
		//	Gets the current timeout to use when waiting for responses from node commands.
		//
		//Returns:
		// The timeout (in milliseconds) set for node commands.
		uint64 nodeCommandsTimeout() const;

		//API Function: ping
		//	Pings the base station
		//
		//Returns:
		//	true if successfully pinged the base station, false otherwise
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		//
		//Example Use:
		//	(start code)
		//		BaseStation baseStation(&connection);
		//		baseStation.ping();
		//	(end code)
		bool ping();

		//API Function: readEeprom
		//	Reads a specific EEPROM address on the Base Station.
		//	If the value stored in the eeprom cache is still valid, this will be returned instead.
		//
		//Parameters:
		//	eepromAddress - The EEPROM address to be read.
		//
		//Returns:
		//	The uint16 value read from the specified EEPROM location.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Unsupported eeprom location.
		//	- <Error_Communication>: Failed to read the value from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		uint16 readEeprom(uint16 eepromAddress) const;

		//API Function: writeEeprom
		//	Writes the specified value to a specific EEPROM address on the Base Station.
		//	If successful, the cache will be updated with the changed value as well.
		//
		//Parameters:
		//	eepromAddress - The EEPROM address to write to.
		//	value - The value to write to the EEPROM address.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Unsupported eeprom location or value.
		//	- <Error_Communication>: Failed to write the value to the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		void writeEeprom(uint16 eepromAddress, uint16 value);

		//API Function: enableBeacon
		//	Enables the beacon on the base station using the system time (UTC) as its starting timestamp.
		//
		//Returns:
		//	A <Timestamp> representing the initial time that was sent to start the beacon
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		//	- <Error_Communication>: The enable beacon command has failed.
		//
		//Example Use:
		//	(start code)
		//		BaseStation baseStation(connection);
		//		baseStation.enableBeacon();
		//	(end code)
		Timestamp enableBeacon();

		//API Function: enableBeacon
		//	Enables the beacon on the base station using the given UTC timestamp.
		//
		//Parameters:
		//	utcTime - The start time for the beacon in UTC seconds from the Unix Epoch (01/01/1970) 
		//
		//Returns:
		//	A <Timestamp> representing the initial time that was sent to start the beacon
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		//	- <Error_Communication>: The enable beacon command has failed.
		//
		//Example Use:
		//	(start code)
		//		BaseStation baseStation(connection);
		//		baseStation.enableBeacon(1357846020);
		//	(end code)
		Timestamp enableBeacon(uint32 utcTime);

		//API Function: disableBeacon
		//	Disables the beacon on the base station.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		//	- <Error_Communication>: The disable beacon command has failed.
		//
		//Example Use:
		//	(start code)
		//		BaseStation baseStation(connection);
		//		baseStation.disableBeacon();
		//	(end code)
		void disableBeacon();

		//API Function: beaconStatus
		//	Gets the <BeaconStatus> of the beacon on the base station.
		//
		//Returns:
		//	A <BeaconStatus> object containing status information of the beacon.
		//
		//Exceptions:
		//	- <Error_Communication>: Failed to get the beacon status.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		BeaconStatus beaconStatus();

		//API Function: cyclePower
		//	Cycles the power on the base station.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to write an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		//	- <Error_Communication>: Failed to cycle the power.
		void cyclePower();

		//API Function: resetRadio
		//	Resets the radio on the base station.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to write an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		//	- <Error_Communication>: Failed to cycle the power.
		void resetRadio();

		//API Function: changeFrequency
		//	Changes the radio frequency of the base station.
		//
		//Parameters:
		//	frequency - The <WirelessTypes::Frequency> to change the base station to.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to write an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		//	- <Error_Communication>: Failed to change the frequency.
		void changeFrequency(WirelessTypes::Frequency frequency);

		//API Function: verifyConfig
		//	Checks whether the settings in the given <BaseStationConfig> are ok to be written to the BaseStation.
		//	Options that are set will also be validated against each other. If an option that needs to be validated isn't
		//	currently set, it will be read from the BaseStation.
		//
		//Parameters:
		//	config - The <BaseStationConfig> to verify.
		//	outIssues - The <ConfigIssues> that will hold any resulting issues that are found with the configuration.
		//
		//Returns:
		//	true if the configuration is valid. false if the configuration is invalid and outIssues should be checked for more information.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The BaseStation model, or firmware version, is not supported by MSCL.
		//	- <Error_Communication>: Failed to communicate with the BaseStation.
		//	- <Error_Connection>: A connection error has occurred.
		bool verifyConfig(const BaseStationConfig& config, ConfigIssues& outIssues) const;

		//API Function: applyConfig
		//	Applies a <BaseStationConfig> to the Node.
		//	Note: This applies all options that have been set in the <BaseStationConfig>. 
		//		  Before applying, the options will be validated. It is recommended that you perform
		//		  this validation yourself first by using <verifyConfig>.
		//
		//Parameters:
		//	config - The <BaseStationConfig> to apply to the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The BaseStation model, or firmware version, is not supported by MSCL.
		//	- <Error_InvalidConfig>: Invalid Configuration. Check the exception for specific details.
		//	- <Error_Communication>: Failed to write to the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void applyConfig(const BaseStationConfig& config);

		//API Function: getTransmitPower
		//	Reads the <WirelessTypes::TransmitPower> that is currently set on the BaseStation.
		//
		//Returns:
		//	The <WirelessTypes::TransmitPower> that is currently set on the BaseStation.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
		//	- <Error_Communication>: Failed to read from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		WirelessTypes::TransmitPower getTransmitPower() const;

		//API Function: getButtonLongPress
		//	Reads the button settings for a long press action that are currently set on the BaseStation.
		//
		//Parameters:
		//	buttonNumber - The button number (1 = button 1) to get the value for.
		//
		//Returns:
		//	A <BaseStationButton> object holding the current long press settings for the requested button number.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The BaseStation does not support the requested button.
		//	- <Error_Communication>: Failed to read from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		BaseStationButton getButtonLongPress(uint8 buttonNumber) const;

		//API Function: getButtonShortPress
		//	Reads the button settings for a short press action that are currently set on the BaseStation.
		//
		//Parameters:
		//	buttonNumber - The button number (1 = button 1) to get the value for.
		//
		//Returns:
		//	A <BaseStationButton> object holding the current short press settings for the requested button number.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The BaseStation does not support the requested button.
		//	- <Error_Communication>: Failed to read from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		BaseStationButton getButtonShortPress(uint8 buttonNumber) const;

		//API Function: getAnalogPairingEnabled
		//	Reads the Analog Pairing enabled/disabled setting that is currently set on the BaseStation.
		//	If this is disabled, all other analog pairing settings will be disabled.
		//
		//Returns:
		//	true if Analog Pairing is enabled, false otherwise.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The BaseStation does not support Analog Pairing.
		//	- <Error_Communication>: Failed to read from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		bool getAnalogPairingEnabled() const;

		//API Function: getAnalogTimeoutTime
		//	Reads the Analog Timeout Time in seconds that is currently set on the BaseStation.
		//
		//Returns:
		//	The analog timeout time in seconds.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The BaseStation does not support Analog Pairing.
		//	- <Error_Communication>: Failed to read from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		uint16 getAnalogTimeoutTime() const;

		//API Function: getAnalogTimeoutVoltage
		//	Reads the Analog Timeout Voltage that is currently set on the BaseStation.
		//
		//Returns:
		//	The analog timeout voltage.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The BaseStation does not support Analog Pairing.
		//	- <Error_Communication>: Failed to read from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		float getAnalogTimeoutVoltage() const;

		//API Function: getAnalogExceedanceEnabled
		//	Reads the Analog Exceedance enabled/disabled setting that is currently set on the BaseStation.
		//
		//Returns:
		//	true if Analog Exceedance is enabled, false otherwise.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The BaseStation does not support Analog Pairing.
		//	- <Error_Communication>: Failed to read from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		bool getAnalogExceedanceEnabled() const;

		//API Function: getAnalogPair
		//	Reads the <BaseStationAnalogPair> for the specified port number that is currently set on the BaseStation.
		//
		//Parameters:
		//	portNumber - The port number (1 = port 1) to get the value for.
		//
		//Returns:
		//	The <BaseStationAnalogPair> for the specified port number that is currently set on the BaseStation.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The BaseStation does not support Analog Pairing.
		//	- <Error_Communication>: Failed to read from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		BaseStationAnalogPair getAnalogPair(uint8 portNumber) const;

//all the node functions in the base station class should not be exposed to SWIG
#ifndef SWIG
	public:
		//Function: node_lastCommunicationTime
		//	Gets the <Timestamp> for the last time MSCL communicated with the given node address.
		//
		//Parameters:
		//	nodeAddress - The node address of the Node to check for.
		//
		//Returns:
		//	A <Timestamp> representing the last time MSCL communicated with the Node, through this BaseStation.
		const Timestamp& node_lastCommunicationTime(NodeAddress nodeAddress) const;

		//Function: node_shortPing
		//	Pings a specific node
		//
		//Parameters:
		//	nodeAddress - the node address of the node to ping
		//
		//Returns:
		//	true if successfully pinged the node, false otherwise
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		bool node_shortPing(NodeAddress nodeAddress);

		//Function: node_ping
		//	Pings the specified Node.
		//
		//Parameters:
		//	nodeAddress - the node address of the node to ping.
		//
		//Returns:
		//	A <PingResponse> object that can be queried to get details of the ping command's response.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		PingResponse node_ping(NodeAddress nodeAddress);

		//Function: node_sleep
		//	Puts the Node into a low power, sleep mode.
		//	This command attempts to ping the node before sending the sleep command, to verify communication.
		//
		//Parameters:
		//	nodeAddress - The node adderss of the Node to put to sleep.
		//
		//Returns:
		//	true if the sleep command was successful, false otherwise.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		bool node_sleep(NodeAddress nodeAddress);

		//Function: node_setToIdle
		//	Attempts to set the node to idle so that it can be communicated with.
		//
		//Parameters:
		//	nodeAddress - the node address of the node to set to idle.
		//
		//Returns:
		//	A <SetToIdleStatus> object that can be queried to get the status of the Set to Idle operation.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		SetToIdleStatus node_setToIdle(NodeAddress nodeAddress);

		//Function: node_readEeprom
		//	Reads a value from EEPROM on the specified Node.
		//
		//Parameters:
		//	protocol - the <WirelessProtocol> for the Node.
		//	nodeAddress - the node address of the Node to read from.
		//	eepromAddress - the EEPROM address to read the value from.
		//	eepromValue - holds the result value read from EEPROM if successful.
		//
		//Returns:
		//	true if the command was successful, false otherwise.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Unsupported eeprom location.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		bool node_readEeprom(const WirelessProtocol& protocol, NodeAddress nodeAddress, uint16 eepromAddress, uint16& eepromValue);

		//Function: node_writeEeprom
		//	Writes a value to EEPROM on the specified Node.
		//
		//Parameters:
		//	protocol - the <WirelessProtocol> for the Node.
		//	nodeAddress - the node address of the node to write to.
		//	eepromAddress - the EEPROM address to write the value to.
		//	value - the value to write to EEPROM.
		//
		//Returns:
		//	true if the write eeprom command succeeded, false otherwise.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Unsupported eeprom location or value.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		bool node_writeEeprom(const WirelessProtocol& protocol, NodeAddress nodeAddress, uint16 eepromAddress, uint16 value);

		//Function: node_pageDownload
		//	Downloads a page of logged data from the Node.
		//
		//Parameters:
		//	protocol - The <WirelessProtocol> for the Node.
		//	nodeAddress - The node address of the Node to download data from.
		//	pageIndex - The page index to download from the Node.
		//	data - Output parameter that contains the resulting data downloaded from the Node, if any.
		//
		//Returns:
		//	true if the page download command succeded, false otherwise
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		bool node_pageDownload(const WirelessProtocol& protocol, NodeAddress nodeAddress, uint16 pageIndex, ByteStream& data);

		//Function: node_startSyncSampling
		//	Sends the Start Synchronized Sampling command to a Node.
		//
		//Parameters:
		//	nodeAddress - The node address of the Node to send the command to.
		//
		//Returns:
		//	true if the Start Sync Sampling command succeeded, false otherwise.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		bool node_startSyncSampling(NodeAddress nodeAddress);

		//Function: node_startNonSyncSampling
		//	Sends the Start Non-Synchronized Sampling command to a Node.
		//
		//Parameters:
		//	nodeAddress - The node address of the Node to send the command to.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		void node_startNonSyncSampling(NodeAddress nodeAddress);

		//Function: node_armForDatalogging
		//	Sends the Arm For Datalogging command to a Node.
		//
		//Parameters:
		//	nodeAddress - The node address of the Node to send the command to.
		//	message - A message, up to 50 characters, to send with the arm command. This message can be downloaded with the data. Will be trimmed to 50 chars if longer. (Default of "")
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		bool node_armForDatalogging(NodeAddress nodeAddress, const std::string& message = "");

		//Function: node_triggerArmedDatalogging
		//	Sends the Trigger Armed Datalogging command to a Node.
		//
		//Parameters:
		//	nodeAddress - The node address of the Node to send the command to.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		void node_triggerArmedDatalogging(NodeAddress nodeAddress);

		//Function: node_erase
		//	Sends the Erase command to a Node.
		//
		//Parameters:
		//	nodeAddress - The node address of the Node to send the command to.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		bool node_erase(NodeAddress nodeAddress);

		//Function: node_autoBalance
		//	Sends the AutoBalance command to a Node.
		//
		//Parameters:
		//	nodeAddress - The node address of the Node to send the command to.
		//	channelNumber - The channel number (ch1 = 1, ch8 = 8) to balance.
		//	targetVal - The target value to balance to.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		void node_autoBalance(NodeAddress nodeAddress, uint8 channelNumber, uint16 targetVal);

		//Function: node_autocal
		//	Performs automatic calibration for a Wireless Node.
		//
		//Parameters:
		//	nodeAddress - The node address of the Node to send the command to.
		//	model - The <WirelessModels::NodeModel> of the Node.
		//	fwVersion - The firmware <Version> of the Node.
		//	result - The <AutoCalResult> reference to hold the result.
		//
		//Returns:
		//	true if the AutoCal command was successful, false otherwise.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		bool node_autocal(NodeAddress nodeAddress, WirelessModels::NodeModel model, const Version& fwVersion, AutoCalResult& result);
#endif

	};
}