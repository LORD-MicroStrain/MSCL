/*****************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the included
LICENSE.txt file for a copy of the full GNU General Public License.
*****************************************************************************/
#pragma once

#include <map>

#include "WirelessParser.h"
#include "WirelessModels.h"
#include "Commands/BaseStation_BeaconStatus.h"
#include "Commands/LongPing.h"
#include "Commands/SetToIdleStatus.h"
#include "Configuration/BaseStationEeprom.h"
#include "Configuration/BaseStationEepromHelper.h"
#include "Packets/WirelessPacketCollector.h"
#include "mscl/Version.h"
#include "mscl/Communication/Connection.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/Timestamp.h"

namespace mscl
{
	//forward declarations
	class BaseStation;
	class BaseStationFeatures;
	class BaseStationConfig;
	class AutoCalResult;
	class WirelessProtocol;
	class ResponsePattern;

	//Class: BaseStation_Impl
	//	Contains the implementation for a <BaseStation> object.
	class BaseStation_Impl
	{ 
		friend class WirelessProtocol;

	public:
		//Constructor: BaseStation_Impl
		//  Creates a BaseStation_Impl object.
		//	Note: This will communicate with the BaseStation to get device information, as well as start the data collection thread.
		//	
		//Parameters:
		//	connection - The <Connection> object used for communication.
		//	baseTimeout - The timeout (in milliseconds) to use for base station commands.
		//
		//Exceptions:
		//	- <Error_Connection>: Failed to communicate with the BaseStation.
		//	
		//See Also:
		//	<Connection>, <SerialConnection>
		explicit BaseStation_Impl(Connection connection, uint64 baseTimeout);

		//Destructor: ~BaseStation_Impl
		//	Destroys the BaseStation object
		~BaseStation_Impl();

	private:
		BaseStation_Impl();										//default constructor disabled
		BaseStation_Impl(const BaseStation_Impl&);				//copy constructor disabled
		BaseStation_Impl& operator=(const BaseStation_Impl&);	//assignement operator disabled

	private:
		//Variable: m_connection
		//	The <Connection> object used for communication
		Connection m_connection;

		//Variable: m_packetCollector
		//	The wireless packet collector used to store wireless data packets
		WirelessPacketCollector m_packetCollector;

		//Variable: m_responseCollector
		//	The response collector used to find and store wireless command responses
		std::shared_ptr<ResponseCollector> m_responseCollector;

		//Variable: m_parser
		//	The wireless parser in charge of parsing all incoming data to this base station
		std::unique_ptr<WirelessParser> m_parser;

		//Variable: m_baseCommandsTimeout
		//	The timeout (in milliseconds) to use for base station commands.
		uint64 m_baseCommandsTimeout;

		//Variable: m_nodeCommandsTimeout
		//	The timeout (in milliseconds) to use for node commands.
		uint64 m_nodeCommandsTimeout;

		//Variable: m_frequency
		//	The last known radio frequency (<WirelessTypes::Frequency>) that the BaseStation was known to be on
		mutable WirelessTypes::Frequency m_frequency;

		//Variable: m_eeprom
		//	The <BaseStationEeprom> that handles reading and writing eeprom values with the BaseStation and eeprom cache.
		mutable std::unique_ptr<BaseStationEeprom> m_eeprom;

		//Variable: m_eepromHelper
		//	The <BaseStationEepromHelper> used for high level eeprom reads and writes on the BaseStation.
		mutable std::unique_ptr<BaseStationEepromHelper> m_eepromHelper;

		//Variable: m_features
		//	The <BaseStationFeatures> containing the features for this BaseStation.
		mutable std::unique_ptr<BaseStationFeatures> m_features;

		//Variable: m_protocol
		//	The <WirelessProtocol> containing all of the protocol commands and info for this BaseStation.
		std::unique_ptr<WirelessProtocol> m_protocol;

		//Variable: m_lastCommTime
		//	A <Timestamp> representing the last time communication was achieved with the BaseStation.
		Timestamp m_lastCommTime;

		//Variable: m_nodesLastCommTime
		//	A map of <NodeAddress> to <Timestamp> objects, holding the last communication time for nodes with this BaseStation.
		std::map<NodeAddress, Timestamp> m_nodesLastCommTime;

	private:
		//Function: getTimeForBeacon
		//	Gets the system time in UTC seconds since Unix Epoch as close to 0 milliseconds as possible
		//
		//Returns:
		//	The system time in UTC seconds since Unix Epoch to enable the beacon with
		static uint32 getTimeForBeacon();

		//Function: parseData
		//	Callback function that parses any bytes that are in the read buffer to find packets or command responses
		//
		//Parameters:
		//	data - The <DataBuffer> containing all the data to be parsed
		void parseData(DataBuffer& data);

		//Function: determineProtocol
		//	Determines the <WirelessProtocol> to use based on the BaseStation's firmware version.
		//
		//Returns:
		//	A unique_ptr containing the <WirelessProtocol> to use.
		std::unique_ptr<WirelessProtocol> determineProtocol();

	public:
		//Function: eeHelper
		//	Gets a reference to the <BaseStationEepromHelper> for this BaseStation.
		//
		//Returns:
		//	A reference to the <BaseStationEepromHelper>.
		BaseStationEepromHelper& eeHelper() const;

		//Function: doCommand
		//	Performs a custom command and waits for the response.
		//
		//Parameters:
		//	response - A reference to a custom class that was inherited from the <ResponsePattern> base class.
		//	cmdBytes - The <ByteStream> containing the command bytes to send.
		//	timeout - The maximum timeout to use for waiting for the response.
		//
		//Returns:
		//	true if the command was successful (response.success() is true), false otherwise.
		bool doCommand(ResponsePattern& response, const ByteStream& cmdBytes, uint64 timeout);

		//Function: features
		//	Gets a reference to the <BaseStationFeatures> for this BaseStation.
		//
		//Returns:
		//	<BaseStationFeatures> containing the features for this BaseStation.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The BaseStation model is not supported by MSCL.
		//	- <Error_Communication>: Failed to communicate with the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		virtual const BaseStationFeatures& features() const;

		//Function: protocol
		//	Gets a reference to the <WirelessProtocol> for this BaseStation.
		//	Note: This requires communicating to the BaseStation if
		//		  creating the protocol for the first time.
		//
		//Exceptions:
		//	- <Error_Communication>: Failed to communicate with the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		virtual const WirelessProtocol& protocol();

		//Function: lastCommunicationTime
		//	Gets the <Timestamp> for the last time we communicated with the BaseStation.
		const Timestamp& lastCommunicationTime() const;

		//Function: read
		//	Reads the value from the BaseStation for a specified eeprom location.
		//
		//Parameters:
		//	eepromAddress - The Eeprom address to get the value for.
		//	result - The value that was read from Eeprom if successful.
		//
		//Returns:
		//	true if the read was successful, false otherwise.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		bool read(uint16 eepromAddress, uint16& result);

		//Function: write
		//	Writes a value to the BaseStation at a specified eeprom location.
		//
		//Parameters:
		//	eepromAddress - The Eeprom address to set the value for.
		//	value - The value to write to the Eeprom.
		//
		//Returns:
		//	true if the write was successful, false otherwise.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		bool write(uint16 eepromAddress, uint16 value);

		//Function: useEepromCache
		//	Sets whether or not to utilize the eeprom cache when configuring this BaseStation (default of enabled). This can be enabled/disabled at any time.
		//	Note:	The eeprom cache stores the last known value that was written to / read from the BaseStation for each eeprom location. If this is enabled,
		//			any reads will get the last known value from the cache if it exists, and any writes will not write to the BaseStation if the
		//			value attempting to be written is the same as that stored in the cache. Caching of these values will still be performed if this is disabled,
		//			however, read and write operations will then always reach out to the actual device.
		//
		//Parameters:
		//	useCache - whether the eeprom cache should be used (true) or not (false).
		void useEepromCache(bool useCache);

		//Function: clearEepromCache
		//	Clears the eeprom cache for this BaseStation.
		void clearEepromCache();

		//Function: frequency
		//	Gets the <WirelessTypes::Frequency> representing the radio frequency of this BaseStation.
		//	If the frequency is unknown, it will be read from the BaseStation.
		//
		//Returns:
		//	The <WirelessTypes::Frequency> that this BaseStation is on.
		//
		//Exceptions:
		//	- <Error_Communication>: Failed to read the value from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		WirelessTypes::Frequency frequency() const;

		//Function: regionCode
		//	Gets the <WirelessTypes::RegionCode> representing the region of this BaseStation.
		//
		//Returns:
		//	The <WirelessTypes::RegionCode> of this BaseStation.
		//
		//Exceptions:
		//	- <Error_Communication>: Failed to read the value from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		WirelessTypes::RegionCode regionCode() const;

		//Function: firmwareVersion
		//	Gets the firmware version of the BaseStation.
		//
		//Returns:
		//	A <Version> representing the firmware version of the BaseStation.
		//
		//Exceptions:
		//	- <Error_Communication>: Failed to read the value from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		Version firmwareVersion() const;

		//Function: model
		//	Gets the model of the BaseStation.
		//
		//Returns:
		//	A <WirelessModels::BaseModel> representing the model of the BaseStation.
		//
		//Exceptions:
		//	- <Error_Communication>: Failed to read the value from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessModels::BaseModel model() const;

		//Function: serial
		//	Gets the serial number of the BaseStation.
		//
		//Returns:
		//	A string representing the serial number of the BaseStation.
		//
		//Exceptions:
		//	- <Error_Communication>: Failed to read the value from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		std::string serial() const;

		//Function: microcontroller
		//	Gets the microcontroller of the BaseStation.
		//
		//Returns:
		//	A <WirelessTypes::MicroControllerType> representing the microcontroller of the BaseStation.
		//
		//Exceptions:
		//	- <Error_Communication>: Failed to read the value from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::MicroControllerType microcontroller() const;

		//Function: getNextData
		//	Gets the next single <DataSweep> of sampled data (LDC, Sync Sampling, etc) collected by this BaseStation.
		//
		//Parameters:
		//	sweep - The <DataSweep> to hold the result.
		//	timeout - the timeout, in milliseconds, to wait for the next data packet if necessary (default of 0)
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		//	- <Error_NoData>: No data packets were found
		void getNextData(DataSweep& sweep, uint32 timeout = 0);

		//Function: getData
		//	Gets up to the requested amount of <DataSweep>s of sampled data that was collected by this BaseStation.
		//
		//Parameters:
		//	sweeps - The vector of <DataSweep> to hold the result.
		//	timeout - The timeout, in milliseconds, to wait for data if necessary (default of 0).
		//	maxSweeps - The maximum number of sweeps to return. If this is 0 (default), all sweeps will be returned.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		void getData(std::vector<DataSweep>& sweeps, uint32 timeout = 0, uint32 maxSweeps = 0);

		//Function: totalData
		//	Gets the number of <DataSweep>s that are currently in the data buffer.
		//
		//Returns:
		//	The number of <DataSweep>s that are currently in the data buffer.
		uint32 totalData();

		//Function: getNodeDiscoveries
		//	Gets the group of Node Discoveries that were collected by this base station.
		//	Calling this function clears out the Node Discovery buffer, so repeatedly calling this will give you any new Node Discoveries.
		//
		//Returns:
		//	A <NodeDiscoveries> container, holding all the Node Discoveries that were collected by this base station.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		NodeDiscoveries getNodeDiscoveries();

		//Function: baseCommandsTimeout
		//	Sets the timeout to use when waiting for responses from base station commands
		//
		//Parameters:
		//	timeout - The timeout (in milliseconds) to set for base station commands
		void baseCommandsTimeout(uint64 timeout);

		//Function: nodeCommandsTimeout
		//	Sets the timeout to use when waiting for responses from node commands
		//
		//Parameters:
		//	timeout - The timeout (in milliseconds) to set for node commands
		void nodeCommandsTimeout(uint64 timeout);

		//Function: baseCommandsTimeout
		//	Gets the current timeout to use when waiting for responses from base station commands.
		//
		//Returns:
		//	The timeout (in milliseconds) set for base station commands.
		uint64 baseCommandsTimeout() const;

		//Function: nodeCommandsTimeout
		//	Gets the current timeout to use when waiting for responses from node commands
		//
		//Returns:
		//	A <TimeSpan> representing the timeout set for node commands
		uint64 nodeCommandsTimeout() const;

		//Function: ping
		//	Pings the base station
		//
		//Returns:
		//	true if successfully pinged the base station, false otherwise
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		virtual bool ping();

		//Function: readEeprom
		//	Reads a specific EEPROM address on the BaseStation.
		//	If the value stored in the eeprom cache is still valid, this will be returned instead.
		//
		//Parameters:
		//	eepromAddress - The EEPROM address to be read.
		//
		//Returns:
		//	The uint16 value read from the specified EEPROM location.
		//
		//Exceptions:
		//	- <Error_Communication>: Failed to read the value from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		virtual uint16 readEeprom(uint16 eepromAddress) const;

		//Function: readEeprom
		//	Reads a value from the given <EepromLocation> of the BaseStation.
		//	If the value stored in the eeprom cache is still valid, this will be returned instead.
		//
		//Parameters:
		//	location - The <EepromLocation> to read from.
		//
		//Returns:
		//	The value read from the specified EEPROM location as a <Value> object.
		//
		//Exceptions:
		//	- <Error_Communication>: Failed to read the value from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with BaseStation.
		virtual Value readEeprom(const EepromLocation& location) const;

		//Function: writeEeprom
		//	Writes the specified uint16 value to a specific EEPROM address on the BaseStation.
		//	If successful, the cache will be updated with the changed value as well.
		//
		//Parameters:
		//	eepromAddress - The EEPROM address to write to.
		//	value - The value to write to the EEPROM address.
		//
		//Exceptions:
		//	- <Error_Communication>: Failed to write the value to the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		virtual void writeEeprom(uint16 eepromAddress, uint16 value);

		//Function: writeEeprom
		//	Writes a value to the given <EepromLocation> of the BaseStation.
		//	If successful, the cache will be updated with the changed value as well.
		//
		//Parameters:
		//	location - The specific <EepromLocation> to write to.
		//	value - The value to write to the eeprom location, as a <Value>.
		//
		//Exceptions:
		//	- <Error_Communication>: Failed to write the value to the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		virtual void writeEeprom(const EepromLocation& location, const Value& val);

		//Function: enableBeacon
		//	Enables the beacon on the base station using the system time (UTC) as its starting timestamp.
		//
		//Returns:
		//	A <Timestamp> representing the initial time that was sent to start the beacon
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		//	- <Error_Communication>: The enable beacon command has failed.
		virtual Timestamp enableBeacon();

		//Function: enableBeacon
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
		virtual Timestamp enableBeacon(uint32 utcTime);

		//Function: disableBeacon
		//	Disables the beacon on the base station.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		//	- <Error_Communication>: The disable beacon command has failed.
		virtual void disableBeacon();

		//Function: beaconStatus
		//	Gets the <BeaconStatus> of the beacon on the BaseStation.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		//	- <Error_Communication>: The beacon status command has failed.
		virtual BeaconStatus beaconStatus();

		//Function: cyclePower
		//	Cycles the power on the base station.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		//	- <Error_Communication>: Failed to cycle the power on the BaseStation.
		void cyclePower();

		//Function: resetRadio
		//	Resets the radio on the base station.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		//	- <Error_Communication>: Failed to cycle the power on the BaseStation.
		void resetRadio();

		//Function: changeFrequency
		//	Changes the radio frequency of the base station.
		//
		//Parameters:
		//	frequency - The <WirelessTypes::Frequency> to change the base station to.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		//	- <Error_Communication>: Failed to change the frequency.
		void changeFrequency(WirelessTypes::Frequency frequency);

		//Function: verifyConfig
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
		//	- <Error_Communication>: Failed to communicate with the BaseStation.
		//	- <Error_Connection>: A connection error has occurred.
		bool verifyConfig(const BaseStationConfig& config, ConfigIssues& outIssues) const;

		//Function: applyConfig
		//	Applies a <BaseStationConfig> to the Node.
		//
		//Parameters:
		//	config - The <BaseStationConfig> to apply to the Node.
		//
		//Exceptions:
		//	- <Error_InvalidConfig>: Invalid Configuration. Check the exception for specific details.
		//	- <Error_Communication>: Failed to write to the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void applyConfig(const BaseStationConfig& config);

		//Function: getTransmitPower
		//	Reads the <WirelessTypes::TransmitPower> that is currently set on the BaseStation.
		//
		//Exceptions:
		//	- <Error_Communication>: Failed to read from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		WirelessTypes::TransmitPower getTransmitPower() const;

		//Function: getButtonLongPress
		//	Gets the current button settings for a long press action, as a <BaseStationButton>.
		//
		//Parameters:
		//	buttonNumber - The button number (1 = button 1) to get the value for.
		//
		//Exceptions:
		//	- <Error_NotSupported> - The BaseStation does not support the requested button.
		//	- <Error_Communication>: Failed to read from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		BaseStationButton getButtonLongPress(uint8 buttonNumber) const;

		//Function: getButtonShortPress
		//	Gets the current button settings for a short press action, as a <BaseStationButton>.
		//
		//Parameters:
		//	buttonNumber - The button number (1 = button 1) to get the value for.
		//
		//Exceptions:
		//	- <Error_NotSupported> - The BaseStation does not support the requested button.
		//	- <Error_Communication>: Failed to read from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		BaseStationButton getButtonShortPress(uint8 buttonNumber) const;

		//Function: getAnalogPairingEnabled
		//	Gets the current setting for if Analog Pairing is enabled or not.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The BaseStation does not support Analog Pairing.
		//	- <Error_Communication>: Failed to read from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		bool getAnalogPairingEnabled() const;

		//Function: getAnalogTimeoutTime
		//	Reads the Analog Timeout Time in seconds that is currently set on the BaseStation.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The BaseStation does not support Analog Pairing.
		//	- <Error_Communication>: Failed to read from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		uint16 getAnalogTimeoutTime() const;

		//Function: getAnalogTimeoutVoltage
		//	Reads the Analog Timeout Voltage that is currently set on the BaseStation.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The BaseStation does not support Analog Pairing.
		//	- <Error_Communication>: Failed to read from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		float getAnalogTimeoutVoltage() const;

		//Function: getAnalogExceedanceEnabled
		//	Reads the Analog Exceedance enabled/disabled setting that is currently set on the BaseStation.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The BaseStation does not support Analog Pairing.
		//	- <Error_Communication>: Failed to read from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		bool getAnalogExceedanceEnabled() const;

		//Function: getAnalogPair
		//	Reads the <BaseStationAnalogPair> for the specified port number that is currently set on the BaseStation.
		//
		//Parameters:
		//	portNumber - The port number (1 = port 1) to get the value for.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The BaseStation does not support Analog Pairing.
		//	- <Error_Communication>: Failed to read from the BaseStation.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		BaseStationAnalogPair getAnalogPair(uint8 portNumber) const;

	private:
		//Function: ping_v1
		//	Performs version 1 of the Ping BaseStation command.
		//
		//Returns:
		//	true if successfully pinged the base station, false otherwise.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		bool ping_v1();

		//Function: ping_v2
		//	Performs version 2 of the Ping BaseStation command.
		//
		//Returns:
		//	true if successfully pinged the base station, false otherwise.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		bool ping_v2();

		//Function: read_v1
		//	Performs version 1 of the Read BaseStation EEPROM command.
		//
		//Parameters:
		//	eepromAddress - The Eeprom address to get the value for.
		//	result - The value that was read from Eeprom if successful.
		//
		//Returns:
		//	true if the read was successful, false otherwise.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		bool read_v1(uint16 eepromAddress, uint16& result);

		//Function: read_v2
		//	Performs version 2 of the Read BaseStation EEPROM command.
		//
		//Parameters:
		//	eepromAddress - The Eeprom address to get the value for.
		//	result - The value that was read from Eeprom if successful.
		//
		//Returns:
		//	true if the read was successful, false otherwise.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		bool read_v2(uint16 eepromAddress, uint16& result);

		//Function: write_v1
		//	Performs version 1 of the Write BaseStation EEPROM command.
		//
		//Parameters:
		//	eepromAddress - The Eeprom address to set the value for.
		//	value - The value to write to the Eeprom.
		//
		//Returns:
		//	true if the write was successful, false otherwise.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		bool write_v1(uint16 eepromAddress, uint16 value);

		//Function: write_v2
		//	Performs version 2 of the Write BaseStation EEPROM command.
		//
		//Parameters:
		//	eepromAddress - The Eeprom address to set the value for.
		//	value - The value to write to the Eeprom.
		//
		//Returns:
		//	true if the write was successful, false otherwise.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		bool write_v2(uint16 eepromAddress, uint16 value);

		//Function: enableBeacon_v1
		//	Performs version 1 of the Enable Beacon command.
		//
		//Parameters:
		//	utcTime - The start time for the beacon in UTC seconds from the Unix Epoch (01/01/1970).
		//
		//Returns:
		//	A <Timestamp> representing the initial time that was sent to start the beacon.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		//	- <Error_Communication>: The enable beacon command has failed.
		Timestamp enableBeacon_v1(uint32 utcTime);

		//Function: enableBeacon_v2
		//	Performs version 2 of the Enable Beacon command.
		//
		//Parameters:
		//	utcTime - The start time for the beacon in UTC seconds from the Unix Epoch (01/01/1970).
		//
		//Returns:
		//	A <Timestamp> representing the initial time that was sent to start the beacon.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		//	- <Error_Communication>: The enable beacon command has failed.
		Timestamp enableBeacon_v2(uint32 utcTime);

		//Function: beaconStatus_v1
		//	Performs version 1 of the Beacon Status command.
		//
		//Returns:
		//	A <BeaconStatus> object containing status information of the beacon.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		//	- <Error_Communication>: The beacon status command has failed.
		BeaconStatus beaconStatus_v1();

		//Function: node_pageDownload_v1
		//	Performs Version 1 of the Node Page Download command.
		//
		//Parameters:
		//	nodeAddress - The node address of the Node to download data from
		//	pageIndex - The page index to download from the Node
		//	data - Output parameter that contains the resulting data downloaded from the Node, if any
		//
		//Returns:
		//	true if the page download command succeeded, false otherwise
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		bool node_pageDownload_v1(NodeAddress nodeAddress, uint16 pageIndex, ByteStream& data);

		//Function: node_readEeprom_v1
		//	Performs Version 1 of the Node Read Eeprom command.
		//
		//Parameters:
		//	nodeAddress - the node address of the node to read from.
		//	eepromAddress - the EEPROM address to read the value from.
		//	eepromValue - holds the result value read from EEPROM if successful.
		//
		//Returns:
		//	true if the command was successful, false otherwise.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		bool node_readEeprom_v1(NodeAddress nodeAddress, uint16 eepromAddress, uint16& eepromValue);

		//Function: node_readEeprom_v2
		//	Performs Version 2 of the Node Read Eeprom command.
		//
		//Parameters:
		//	nodeAddress - the node address of the node to read from.
		//	eepromAddress - the EEPROM address to read the value from.
		//	eepromValue - holds the result value read from EEPROM if successful.
		//
		//Returns:
		//	true if the command was successful, false otherwise.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		bool node_readEeprom_v2(NodeAddress nodeAddress, uint16 eepromAddress, uint16& eepromValue);

		//Function: node_writeEeprom_v1
		//	Performs Version 1 of the Node Write Eeprom command.
		//
		//Parameters:
		//	nodeAddress - the node address of the node to write to.
		//	eepromAddress - the EEPROM address to write the value to.
		//	value - the value to write to EEPROM.
		//
		//Returns:
		//	true if the write eeprom command succeeded, false otherwise.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		bool node_writeEeprom_v1(NodeAddress nodeAddress, uint16 eepromAddress, uint16 value);

		//Function: node_writeEeprom_v2
		//	Performs Version 2 of the Node Write Eeprom command.
		//
		//Parameters:
		//	nodeAddress - the node address of the node to write to.
		//	eepromAddress - the EEPROM address to write the value to.
		//	value - the value to write to EEPROM.
		//
		//Returns:
		//	true if the write eeprom command succeeded, false otherwise.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		bool node_writeEeprom_v2(NodeAddress nodeAddress, uint16 eepromAddress, uint16 value);

	public:
		//Function: node_lastCommunicationTime
		//	Gets the <Timestamp> for the last time MSCL communicated with the given node address.
		//
		//Parameters:
		//	nodeAddress - The node address of the Node to check for.
		const Timestamp& node_lastCommunicationTime(NodeAddress nodeAddress);

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
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		bool node_shortPing(NodeAddress nodeAddress);

		//Function: node_ping
		//	Pings the specified Node.
		//
		//Parameters:
		//	nodeAddress - the node address of the Node to ping.
		//
		//Returns:
		//	A <PingResponse> object that can be queried to get details of the ping command's response.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		virtual PingResponse node_ping(NodeAddress nodeAddress);

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
		virtual bool node_sleep(NodeAddress nodeAddress);

		//Function: node_setToIdle
		//	Attempts to set the node to idle so that it can be communicated with.
		//
		//Parameters:
		//	nodeAddress - the node address of the node to ping.
		//	base - A reference to the <BaseStation> that will be used for setting the node to idle.
		//
		//Returns:
		//	A <SetToIdleStatus> object that can be queried to get the status of the Set to Idle operation.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		virtual SetToIdleStatus node_setToIdle(NodeAddress nodeAddress, const BaseStation& base);

		//Function: node_readEeprom
		//	Reads a value from EEPROM on the specified Node.
		//
		//Parameters:
		//	nodeProtocol - the <WirelessProtocol> for the Node.
		//	nodeAddress - the node address of the Node to read from.
		//	eepromAddress - the EEPROM address to read the value from.
		//	eepromValue - holds the result value read from EEPROM if successful.
		//
		//Returns:
		//	true if the command was successful, false otherwise.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		virtual bool node_readEeprom(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, uint16 eepromAddress, uint16& eepromValue);

		//Function: node_writeEeprom
		//	Writes a value to EEPROM on the specified Node.
		//
		//Parameters:
		//	nodeProtocol - the <WirelessProtocol> for the Node.
		//	nodeAddress - the node address of the node to write to.
		//	eepromAddress - the EEPROM address to write the value to.
		//	value - the value to write to EEPROM.
		//
		//Returns:
		//	true if the write eeprom command succeeded, false otherwise.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		virtual bool node_writeEeprom(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, uint16 eepromAddress, uint16 value);

		//Function: node_pageDownload
		//	Download a page of logged data from the Node
		//
		//Parameters:
		//	nodeProtocol - The <WirelessProtocol> for the Node.
		//	nodeAddress - The node address of the Node to download data from
		//	pageIndex - The page index to download from the Node
		//	data - Output parameter that contains the resulting data downloaded from the Node, if any
		//
		//Returns:
		//	true if the page download command succeeded, false otherwise
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation
		virtual bool node_pageDownload(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, uint16 pageIndex, ByteStream& data);

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
		virtual bool node_startSyncSampling(NodeAddress nodeAddress);

		//Function: node_startSyncSampling
		//	Sends the Start Non-Synchronized Sampling command to a Node.
		//
		//Parameters:
		//	nodeAddress - The node address of the Node to send the command to.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		virtual void node_startNonSyncSampling(NodeAddress nodeAddress);

		//Function: node_armForDatalogging
		//	Sends the Arm For Datalogging command to a Node.
		//
		//Parameters:
		//	nodeAddress - The node address of the Node to send the command to.
		//	message - A message, up to 50 characters, to send with the arm command. This message can be downloaded with the data. Will be trimmed to 50 chars if longer.
		//
		//Returns:
		//	true if the Arm For Datalogging command succeeded, false otherwise.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		virtual bool node_armForDatalogging(NodeAddress nodeAddress, const std::string& message);

		//Function: node_triggerArmedDatalogging
		//	Sends the Trigger Armed Datalogging command to a Node.
		//
		//Parameters:
		//	nodeAddress - The node address of the Node to send the command to.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		virtual void node_triggerArmedDatalogging(NodeAddress nodeAddress);

		//Function: node_erase
		//	Sends the Erase command to a Node.
		//
		//Parameters:
		//	nodeAddress - The node address of the Node to send the command to.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		virtual bool node_erase(NodeAddress nodeAddress);

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
		virtual void node_autoBalance(NodeAddress nodeAddress, uint8 channelNumber, uint16 targetVal);

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
	};
}