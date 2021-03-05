/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include <map>
#include <boost/optional.hpp>

#include "WirelessParser.h"
#include "WirelessModels.h"
#include "Commands/AutoBalance_v2.h"
#include "Commands/AutoCal.h"
#include "Commands/BeaconStatus.h"
#include "Commands/LongPing.h"
#include "Commands/SetToIdleStatus.h"
#include "Configuration/BaseStationEeprom.h"
#include "Configuration/BaseStationEepromHelper.h"
#include "Packets/WirelessPacketCollector.h"
#include "mscl/Version.h"
#include "mscl/Communication/Connection.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/Timestamp.h"
#include "mscl/Types.h"

namespace mscl
{
    //forward declarations
    class AutoBalanceResult;
    class AutoCalResult;
    class BaseStation;
    class BaseStationFeatures;
    class BaseStationConfig;
    struct DatalogSessionInfoResult;
    class WirelessResponsePattern;
    struct AutoCalCmdDetails;
    class WirelessProtocol;

    //Class: BaseStation_Impl
    //    Contains the implementation for a <BaseStation> object.
    class BaseStation_Impl
    { 
        friend class WirelessProtocol;

    public:
        //Constructor: BaseStation_Impl
        //  Creates a BaseStation_Impl object.
        //    Note: This will communicate with the BaseStation to get device information, as well as start the data collection thread.
        //    
        //Parameters:
        //    connection - The <Connection> object used for communication.
        //    baseTimeout - The timeout (in milliseconds) to use for base station commands.
        //
        //Exceptions:
        //    - <Error_Connection>: Failed to communicate with the BaseStation.
        //    
        //See Also:
        //    <Connection>, <SerialConnection>
        explicit BaseStation_Impl(Connection connection, uint64 baseTimeout);

        explicit BaseStation_Impl(Connection connection);

        //Destructor: ~BaseStation_Impl
        //    Destroys the BaseStation object
        virtual ~BaseStation_Impl();

    private:
        BaseStation_Impl() = delete;                                    //default constructor disabled
        BaseStation_Impl(const BaseStation_Impl&) = delete;             //copy constructor disabled
        BaseStation_Impl& operator=(const BaseStation_Impl&) = delete;  //assignement operator disabled

    protected:
        //Variable: m_connection
        //    The <Connection> object used for communication
        Connection m_connection;

        //Variable: m_packetCollector
        //    The wireless packet collector used to store wireless data packets
        WirelessPacketCollector m_packetCollector;

        //Variable: m_responseCollector
        //    The response collector used to find and store wireless command responses
        std::shared_ptr<ResponseCollector> m_responseCollector;

        //Variable: m_rawBytePacketCollector
        //    The <RawBytePacketCollector> associated with this parser and its parent device
        mutable RawBytePacketCollector m_rawBytePacketCollector;

        //Variable: m_parser
        //    The wireless parser in charge of parsing all incoming data to this base station
        std::unique_ptr<WirelessParser> m_parser;

        //Variable: m_baseCommandsTimeout
        //    The timeout (in milliseconds) to use for base station commands.
        uint64 m_baseCommandsTimeout;

        //Variable: m_nodeCommandsTimeout
        //    The timeout (in milliseconds) to use for node commands.
        uint64 m_nodeCommandsTimeout;

        //Variable: m_frequency
        //    The last known radio frequency (<WirelessTypes::Frequency>) that the BaseStation was known to be on
        mutable WirelessTypes::Frequency m_frequency;

        //Variable: m_commProtocol
        //  The last known state of the <WirelessTypes::CommProtocol> for the BaseStation.
        mutable std::unique_ptr<WirelessTypes::CommProtocol> m_commProtocol;

        //Variable: m_eeprom
        //    The <BaseStationEeprom> that handles reading and writing eeprom values with the BaseStation and eeprom cache.
        mutable std::unique_ptr<BaseStationEeprom> m_eeprom;

        //Variable: m_eepromHelper
        //    The <BaseStationEepromHelper> used for high level eeprom reads and writes on the BaseStation.
        mutable std::unique_ptr<BaseStationEepromHelper> m_eepromHelper;

        //Variable: m_features
        //    The <BaseStationFeatures> containing the features for this BaseStation.
        mutable std::unique_ptr<BaseStationFeatures> m_features;

        //Variable: m_protocolMutex
        //    The mutex used when determining the device protocol.
        mutable std::recursive_mutex m_protocolMutex;

        //Variable: m_protocol_lxrs
        //    The <WirelessProtocol> containing all of the protocol commands for the LXRS Radio Configuration.
        mutable std::unique_ptr<WirelessProtocol> m_protocol_lxrs;

        //Variable: m_protocol_lxrsPlus
        //    The <WirelessProtocol> containing all of the protocol commands for the LXRS+ Radio Configuration.
        mutable std::unique_ptr<WirelessProtocol> m_protocol_lxrsPlus;

        //Variable: m_lastCommTime
        //    A <Timestamp> representing the last time communication was achieved with the BaseStation.
        Timestamp m_lastCommTime;

    private:
        //Function: getTimeForBeacon
        //    Gets the system time in UTC seconds since Unix Epoch as close to 0 milliseconds as possible
        //
        //Returns:
        //    The system time in UTC seconds since Unix Epoch to enable the beacon with
        static uint32 getTimeForBeacon();

        //Function: parseData
        //    Callback function that parses any bytes that are in the read buffer to find packets or command responses
        //
        //Parameters:
        //    data - The <DataBuffer> containing all the data to be parsed
        void parseData(DataBuffer& data);

        //Function: determineProtocols
        //    Determines the <WirelessProtocol> to use based on the BaseStation's ASPP version.
        //    All <WirelessProtocol> member variables will be updated.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_Communication>: Failed to communicate with the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        void determineProtocols() const;

    public:
        //Function: eeHelper
        //    Gets a reference to the <BaseStationEepromHelper> for this BaseStation.
        //
        //Returns:
        //    A reference to the <BaseStationEepromHelper>.
        BaseStationEepromHelper& eeHelper() const;

        //Function: doCommand
        //    Performs a custom command and waits for the response.
        //
        //Parameters:
        //    response - A reference to a custom class that was inherited from the <WirelessResponsePattern> base class.
        //    cmdBytes - The <ByteStream> containing the command bytes to send.
        //    timeout - The maximum timeout to use for waiting for the response.
        //
        //Returns:
        //    true if the command was successful (response.success() is true), false otherwise.
        bool doCommand(WirelessResponsePattern& response, const ByteStream& cmdBytes, uint64 timeout);

        //Function: connection
        //    Gets the <Connection> object that this BaseStation is using.
        Connection& connection();

        //Function: features
        //    Gets a reference to the <BaseStationFeatures> for this BaseStation.
        //
        //Returns:
        //    <BaseStationFeatures> containing the features for this BaseStation.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The BaseStation model, or firmware version, is not supported by MSCL.
        //    - <Error_Communication>: Failed to communicate with the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        virtual const BaseStationFeatures& features() const;

        //Function: protocol
        //    Gets a reference to the <WirelessProtocol> for this BaseStation.
        //    Note: This requires communicating to the BaseStation if
        //          creating the protocol for the first time.
        //
        //Parameters:
        //  commProtocol - The <WirelessTypes::CommProtocol> to get the protocol for.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_Communication>: Failed to communicate with the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual const WirelessProtocol& protocol(WirelessTypes::CommProtocol commProtocol) const;

        //Function: lastCommunicationTime
        //    Gets the <Timestamp> for the last time we communicated with the BaseStation.
        //
        //Exceptions:
        //  - <Error_NoData>: There is no communication time logged for this device.
        const Timestamp& lastCommunicationTime() const;

        //Function: read
        //    Reads the value from the BaseStation for a specified eeprom location.
        //
        //Parameters:
        //    eepromAddress - The Eeprom address to get the value for.
        //    result - The value that was read from Eeprom if successful.
        //
        //Returns:
        //    true if the read was successful, false otherwise.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Unsupported eeprom location.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual bool read(uint16 eepromAddress, uint16& result);

        //Function: write
        //    Writes a value to the BaseStation at a specified eeprom location.
        //
        //Parameters:
        //    eepromAddress - The Eeprom address to set the value for.
        //    value - The value to write to the Eeprom.
        //
        //Returns:
        //    true if the write was successful, false otherwise.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Unsupported eeprom location or value.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual bool write(uint16 eepromAddress, uint16 value);

        //Function: setReadWriteRetries
        //    Sets the number of retry attempts for reading and writing with the BaseStation.
        //
        //Parameters:
        //    numRetries - The number of retries to set for all reading and writing with the BaseStation.
        void setReadWriteRetries(uint8 numRetries);

        //Function: getReadWriteRetries
        //    Gets the number of retry attempts for reading and writing with the BaseStation.
        uint8 getReadWriteRetries() const;

        //Function: useEepromCache
        //    Sets whether or not to utilize the eeprom cache when configuring this BaseStation (default of enabled). This can be enabled/disabled at any time.
        //    Note:    The eeprom cache stores the last known value that was written to / read from the BaseStation for each eeprom location. If this is enabled,
        //            any reads will get the last known value from the cache if it exists, and any writes will not write to the BaseStation if the
        //            value attempting to be written is the same as that stored in the cache. Caching of these values will still be performed if this is disabled,
        //            however, read and write operations will then always reach out to the actual device.
        //
        //Parameters:
        //    useCache - whether the eeprom cache should be used (true) or not (false).
        void useEepromCache(bool useCache);

        //Function: clearEepromCache
        //    Clears the eeprom cache for this BaseStation.
        void clearEepromCache();

        //Function: frequency
        //    Gets the <WirelessTypes::Frequency> representing the radio frequency of this BaseStation.
        //    If the frequency is unknown, it will be read from the BaseStation.
        //
        //Returns:
        //    The <WirelessTypes::Frequency> that this BaseStation is on.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_Communication>: Failed to read the value from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        WirelessTypes::Frequency frequency() const;

        //Function: communicationProtocol
        //  Gets the <WirelessTypes::CommProtocol> that the BaseStation is currently set to use.
        //
        //Returns:
        //  The <WirelessTypes::CommProtocol> that the BaseStation is currently set to use.
        //
        //Exceptions:
        //    - <Error_Communication>: Failed to read the value from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual WirelessTypes::CommProtocol communicationProtocol() const;

        //Function: regionCode
        //    Gets the <WirelessTypes::RegionCode> representing the region of this BaseStation.
        //
        //Returns:
        //    The <WirelessTypes::RegionCode> of this BaseStation.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_Communication>: Failed to read the value from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        WirelessTypes::RegionCode regionCode() const;

        //Function: firmwareVersion
        //    Gets the firmware version of the BaseStation.
        //
        //Returns:
        //    A <Version> representing the firmware version of the BaseStation.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_Communication>: Failed to read the value from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        Version firmwareVersion() const;

        //Function: model
        //    Gets the model of the BaseStation.
        //
        //Returns:
        //    A <WirelessModels::BaseModel> representing the model of the BaseStation.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_Communication>: Failed to read the value from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessModels::BaseModel model() const;

        //Function: serial
        //    Gets the serial number of the BaseStation.
        //
        //Returns:
        //    A string representing the serial number of the BaseStation.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_Communication>: Failed to read the value from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        std::string serial() const;

        //Function: microcontroller
        //    Gets the microcontroller of the BaseStation.
        //
        //Returns:
        //    A <WirelessTypes::MicroControllerType> representing the microcontroller of the BaseStation.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_Communication>: Failed to read the value from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::MicroControllerType microcontroller() const;

        //Function: getData
        //    Gets up to the requested amount of <DataSweep>s of sampled data that was collected by this BaseStation.
        //
        //Parameters:
        //    sweeps - The vector of <DataSweep> to hold the result.
        //    timeout - The timeout, in milliseconds, to wait for data if necessary (default of 0).
        //    maxSweeps - The maximum number of sweeps to return. If this is 0 (default), all sweeps will be returned.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation
        void getData(std::vector<DataSweep>& sweeps, uint32 timeout = 0, uint32 maxSweeps = 0);

        //Function: getRawBytePackets
        //    Gets up to the requested amount of raw byte packets that have been collected.
        //
        //Parameters:
        //    packets - A vector of <RawBytePacket> to hold the result.
        //    timeout - the timeout, in milliseconds, to wait for the data if necessary (default of 0)
        //    maxPackets - The maximum number of packets to return. If this is 0 (default), all packets will be returned.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the Node.
        void getRawBytePackets(RawBytePackets& packets, uint32 timeout = 0, uint32 maxPackets = 0);

        //Function: totalData
        //    Gets the number of <DataSweep>s that are currently in the data buffer.
        //
        //Returns:
        //    The number of <DataSweep>s that are currently in the data buffer.
        uint32 totalData();

        //Function: getNodeDiscoveries
        //    Gets the group of Node Discoveries that were collected by this base station.
        //    Calling this function clears out the Node Discovery buffer, so repeatedly calling this will give you any new Node Discoveries.
        //
        //Returns:
        //    A <NodeDiscoveries> container, holding all the Node Discoveries that were collected by this base station.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation
        NodeDiscoveries getNodeDiscoveries();

        //Function: timeout
        //    Sets the timeout to use when waiting for responses from commands.
        //
        //Parameters:
        //    timeout - The timeout (in milliseconds) to set.
        void timeout(uint64 timeout);

        //Function: timeout
        //    Gets the current timeout to use when waiting for responses from commands.
        //
        //Returns:
        //    The timeout (in milliseconds) set.
        uint64 timeout() const;

        //Function: ping
        //    Pings the base station
        //
        //Returns:
        //    true if successfully pinged the base station, false otherwise
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation
        virtual bool ping();

        //Function: readEeprom
        //    Reads a specific EEPROM address on the BaseStation.
        //    If the value stored in the eeprom cache is still valid, this will be returned instead.
        //
        //Parameters:
        //    eepromAddress - The EEPROM address to be read.
        //
        //Returns:
        //    The uint16 value read from the specified EEPROM location.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported eeprom location.
        //    - <Error_Communication>: Failed to read the value from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual uint16 readEeprom(uint16 eepromAddress) const;

        //Function: readEeprom
        //    Reads a value from the given <EepromLocation> of the BaseStation.
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
        //    - <Error_Communication>: Failed to read the value from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with BaseStation.
        virtual Value readEeprom(const EepromLocation& location) const;

        //Function: writeEeprom
        //    Writes the specified uint16 value to a specific EEPROM address on the BaseStation.
        //    If successful, the cache will be updated with the changed value as well.
        //
        //Parameters:
        //    eepromAddress - The EEPROM address to write to.
        //    value - The value to write to the EEPROM address.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Unsupported eeprom location or value.
        //    - <Error_Communication>: Failed to write the value to the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual void writeEeprom(uint16 eepromAddress, uint16 value);

        //Function: writeEeprom
        //    Writes a value to the given <EepromLocation> of the BaseStation.
        //    If successful, the cache will be updated with the changed value as well.
        //
        //Parameters:
        //    location - The specific <EepromLocation> to write to.
        //    value - The value to write to the eeprom location, as a <Value>.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Unsupported eeprom location or value.
        //    - <Error_Communication>: Failed to write the value to the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual void writeEeprom(const EepromLocation& location, const Value& val);

        //Function: enableBeacon
        //    Enables the beacon on the base station using the system time (UTC) as its starting timestamp.
        //
        //Returns:
        //    A <Timestamp> representing the initial time that was sent to start the beacon
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation
        //    - <Error_Communication>: The enable beacon command has failed.
        virtual Timestamp enableBeacon();

        //Function: enableBeacon
        //    Enables the beacon on the base station using the given UTC timestamp.
        //
        //Parameters:
        //    utcTime - The start time for the beacon in UTC seconds from the Unix Epoch (01/01/1970) 
        //
        //Returns:
        //    A <Timestamp> representing the initial time that was sent to start the beacon
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation
        //    - <Error_Communication>: The enable beacon command has failed.
        virtual Timestamp enableBeacon(uint32 utcTime);

        //Function: disableBeacon
        //    Disables the beacon on the base station.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation
        //    - <Error_Communication>: The disable beacon command has failed.
        virtual void disableBeacon();

        //Function: beaconStatus
        //    Gets the <BeaconStatus> of the beacon on the BaseStation.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        //    - <Error_Communication>: The beacon status command has failed.
        virtual BeaconStatus beaconStatus();

        //Function: startRfSweepMode
        //  Starts the BaseStation in a fixed RF Sweep Mode, which will sweep over all the supported operating frequencies of the BaseStation.
        //
        //Exceptions:
        //    - <Error_NotSupported>: RF Sweep Mode is not supported by this BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        //    - <Error_Communication>: The beacon status command has failed.
        virtual void startRfSweepMode();

        //Function: startRfSweepMode
        //    Starts the BaseStation in RF Sweep Mode.
        //
        //Exceptions:
        //    - <Error_NotSupported>: RF Sweep Mode is not supported by this BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        //    - <Error_Communication>: The beacon status command has failed.
        virtual void startRfSweepMode(uint32 minFreq, uint32 maxFreq, uint32 interval, uint16 options);

        //Function: cyclePower
        //    Cycles the power on the base station.
        //
        //Parameters:
        //  checkComm - Whether to check for communication (ping) after cycling power before returning from this function.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to write an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        //    - <Error_Communication>: Failed to cycle the power on the BaseStation.
        virtual void cyclePower(bool checkComm=true);

        //Function: resetRadio
        //    Resets the radio on the base station.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to write an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        //    - <Error_Communication>: Failed to cycle the power on the BaseStation.
        virtual void resetRadio();

        //Function: changeFrequency
        //    Changes the radio frequency of the base station.
        //
        //Parameters:
        //    frequency - The <WirelessTypes::Frequency> to change the base station to.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to write an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation
        //    - <Error_Communication>: Failed to change the frequency.
        void changeFrequency(WirelessTypes::Frequency frequency);

        //Function: verifyConfig
        //    Checks whether the settings in the given <BaseStationConfig> are ok to be written to the BaseStation.
        //    Options that are set will also be validated against each other. If an option that needs to be validated isn't
        //    currently set, it will be read from the BaseStation.
        //
        //Parameters:
        //    config - The <BaseStationConfig> to verify.
        //    outIssues - The <ConfigIssues> that will hold any resulting issues that are found with the configuration.
        //
        //Returns:
        //    true if the configuration is valid. false if the configuration is invalid and outIssues should be checked for more information.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_Communication>: Failed to communicate with the BaseStation.
        //    - <Error_Connection>: A connection error has occurred.
        bool verifyConfig(const BaseStationConfig& config, ConfigIssues& outIssues) const;

        //Function: applyConfig
        //    Applies a <BaseStationConfig> to the Node.
        //
        //Parameters:
        //    config - The <BaseStationConfig> to apply to the Node.
        //
        //Exceptions:
        //    - <Error_InvalidConfig>: Invalid Configuration. Check the exception for specific details.
        //    - <Error_Communication>: Failed to write to the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        void applyConfig(const BaseStationConfig& config);

        //Function: getTransmitPower
        //    Reads the <WirelessTypes::TransmitPower> that is currently set on the BaseStation.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        WirelessTypes::TransmitPower getTransmitPower() const;

        //Function: getButtonLongPress
        //    Gets the current button settings for a long press action, as a <BaseStationButton>.
        //
        //Parameters:
        //    buttonNumber - The button number (1 = button 1) to get the value for.
        //
        //Exceptions:
        //    - <Error_NotSupported> - The BaseStation does not support the requested button.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        BaseStationButton getButtonLongPress(uint8 buttonNumber) const;

        //Function: getButtonShortPress
        //    Gets the current button settings for a short press action, as a <BaseStationButton>.
        //
        //Parameters:
        //    buttonNumber - The button number (1 = button 1) to get the value for.
        //
        //Exceptions:
        //    - <Error_NotSupported> - The BaseStation does not support the requested button.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        BaseStationButton getButtonShortPress(uint8 buttonNumber) const;

        //Function: getAnalogPairingEnabled
        //    Gets the current setting for if Analog Pairing is enabled or not.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The BaseStation does not support Analog Pairing.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        bool getAnalogPairingEnabled() const;

        //Function: getAnalogTimeoutTime
        //    Reads the Analog Timeout Time in seconds that is currently set on the BaseStation.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The BaseStation does not support Analog Pairing.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        uint16 getAnalogTimeoutTime() const;

        //Function: getAnalogTimeoutVoltage
        //    Reads the Analog Timeout Voltage that is currently set on the BaseStation.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The BaseStation does not support Analog Pairing.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        float getAnalogTimeoutVoltage() const;

        //Function: getAnalogExceedanceEnabled
        //    Reads the Analog Exceedance enabled/disabled setting that is currently set on the BaseStation.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The BaseStation does not support Analog Pairing.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        bool getAnalogExceedanceEnabled() const;

        //Function: getAnalogPair
        //    Reads the <BaseStationAnalogPair> for the specified port number that is currently set on the BaseStation.
        //
        //Parameters:
        //    portNumber - The port number (1 = port 1) to get the value for.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The BaseStation does not support Analog Pairing.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        BaseStationAnalogPair getAnalogPair(uint8 portNumber) const;

    private:
        uint16 timeoutToAdd();

        //Function: doBaseCommand
        //  Performs a BaseStation command with the given parameters.
        bool doBaseCommand(const ByteStream& command, WirelessResponsePattern& response, uint64 minTimeout = 0);

        //Function: doNodeCommand
        //  Performs a Wireless Node command with the given parameters.
        bool doNodeCommand(NodeAddress nodeAddress, const ByteStream& command, WirelessResponsePattern& response, uint64 minTimeout = 0);

        //Function: protocol_ping_v1
        //    Performs version 1 of the Ping BaseStation command.
        bool protocol_ping_v1();

        //Function: protocol_ping_v2
        //    Performs version 2 of the Ping BaseStation command.
        bool protocol_ping_v2(WirelessPacket::AsppVersion asppVer);

        //Function: protocol_hardReset_v2
        //  Performs Version 2 of the Hard BaseStation Reset command.
        void protocol_hardReset_v2();

        //Function: protocol_softReset_v2
        //  Performs Version 2 of the Soft BaseStation Reset command.
        void protocol_softReset_v2();

        //Function: protocol_read_v1
        //    Performs version 1 of the Read BaseStation EEPROM command.
        bool protocol_read_v1(uint16 eepromAddress, uint16& result);

        //Function: protocol_read_v2
        //    Performs version 2 of the Read BaseStation EEPROM command.
        bool protocol_read_v2(WirelessPacket::AsppVersion asppVer, uint16 eepromAddress, uint16& result);

        //Function: protocol_write_v1
        //    Performs version 1 of the Write BaseStation EEPROM command.
        bool protocol_write_v1(uint16 eepromAddress, uint16 value);

        //Function: protocol_write_v2
        //    Performs version 2 of the Write BaseStation EEPROM command.
        bool protocol_write_v2(WirelessPacket::AsppVersion asppVer, uint16 eepromAddress, uint16 value);

        //Function: protocol_enableBeacon_v1
        //    Performs version 1 of the Enable Beacon command.
        Timestamp protocol_enableBeacon_v1(uint32 utcTime);

        //Function: protocol_enableBeacon_v2
        //    Performs version 2 of the Enable Beacon command.
        Timestamp protocol_enableBeacon_v2(WirelessPacket::AsppVersion asppVer, uint32 utcTime);

        //Function: protocol_beaconStatus_v1
        //    Performs version 1 of the Beacon Status command.
        BeaconStatus protocol_beaconStatus_v1(WirelessPacket::AsppVersion asppVer);

        //Function: protocol_startRfSweepMode_v1
        //    Starts the BaseStation in RF Sweep Mode.
        void protocol_startRfSweepMode_v1(WirelessPacket::AsppVersion asppVer, uint32 minFreq, uint32 maxFreq, uint32 interval, uint16 options);

        //Function: protocol_node_pageDownload_v1
        //    Performs Version 1 of the Node Page Download command.
        bool protocol_node_pageDownload_v1(NodeAddress nodeAddress, uint16 pageIndex, ByteStream& data);

        //Function: protocol_node_datalogInfo_v1
        //  Performs Version 1 of the Get Datalog Session Info command.
        bool protocol_node_datalogInfo_v1(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, DatalogSessionInfoResult& result);

        //Function: protocol_node_getDatalogData_v1
        //  Performs Version 1 of the Get Datalog Data command.
        bool protocol_node_getDatalogData_v1(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, uint32 flashAddress, ByteStream& data, uint16& numBytesDownloaded);

        //Function: protocol_node_longPing_v1
        //  Performs Version 1 of the Node Long Ping command.
        PingResponse protocol_node_longPing_v1(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress);

        //Function: protocol_node_hardReset_v2
        //  Performs Version 2 of the Node Hard Reset command.
        void protocol_node_hardReset_v2(NodeAddress nodeAddress);

        //Function: protocol_node_softReset_v2
        //  Performs Version 2 of the Node Soft Reset command.
        void protocol_node_softReset_v2(NodeAddress nodeAddress);

        //Function: protocol_node_sleep_v1
        //  Performs Version 1 of the Node Sleep command.
        bool protocol_node_sleep_v1(NodeAddress nodeAddress);

        //Function: protocol_node_sleep_v2
        //  Performs Version 2 of the Node Sleep command.
        bool protocol_node_sleep_v2(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress);

        //Function: protocol_node_setToIdle_v1
        //    Performs Version 1 of the Node Set to Idle command.
        SetToIdleStatus protocol_node_setToIdle_v1(NodeAddress nodeAddress, const BaseStation& base);

        //Function: protocol_node_setToIdle_v2
        //    Performs Version 2 of the Node Set to Idle command.
        SetToIdleStatus protocol_node_setToIdle_v2(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, const BaseStation& base);

        //Function: protocol_node_readEeprom_v1
        //    Performs Version 1 of the Node Read Eeprom command.
        bool protocol_node_readEeprom_v1(NodeAddress nodeAddress, uint16 eepromAddress, uint16& eepromValue);

        //Function: protocol_node_readEeprom_v2
        //    Performs Version 2 of the Node Read Eeprom command.
        bool protocol_node_readEeprom_v2(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, uint16 eepromAddress, uint16& eepromValue);

        //Function: protocol_node_writeEeprom_v1
        //    Performs Version 1 of the Node Write Eeprom command.
        bool protocol_node_writeEeprom_v1(NodeAddress nodeAddress, uint16 eepromAddress, uint16 value);

        //Function: protocol_node_writeEeprom_v2
        //    Performs Version 2 of the Node Write Eeprom command.
        bool protocol_node_writeEeprom_v2(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, uint16 eepromAddress, uint16 value);

        //Function: protocol_node_autoBalance_v1
        //    Performs Version 1 of the Node AutoBalance command.
        bool protocol_node_autoBalance_v1(NodeAddress nodeAddress, uint8 channelNumber, float targetPercent, AutoBalanceResult& result);

        //Function: protocol_node_autoBalance_v2
        //    Performs Version 2 of the Node AutoBalance command.
        bool protocol_node_autoBalance_v2(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, uint8 channelNumber, float targetPercent, AutoBalanceResult& result);

        //Function: protocol_node_autocal_shm_v1
        //  Performs Version 1 of the Node AutoCal SHM command.
        bool protocol_node_autocal_shm_v1(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, AutoCalResult& result);

        //Function: protocol_node_autocal_shm201_v1
        //  Performs Version 1 of the Node AutoCal SHM-Link-201 command.
        bool protocol_node_autocal_shm201_v1(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, AutoCalResult& result);

        //Function: protocol_node_autoshuntcal_v1
        //  Performs Version 1 of the Node AutoShuntCal command.
        bool protocol_node_autoshuntcal_v1(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, const AutoCalCmdDetails& commandDetails, AutoCalResult& result);

        //Function: protocol_node_getDiagnosticInfo_v1
        //  Performs Version 1 of the Node Get Diagnostic Info command.
        bool protocol_node_getDiagnosticInfo_v1(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, ChannelData& result);

        //Function: protocol_node_erase_v1
        //    Performs Version 1 of the Node erase command.
        bool protocol_node_erase_v1(NodeAddress nodeAddress);

        //Function: protocol_node_erase_v2
        //    Performs Version 2 of the Node erase command.
        bool protocol_node_erase_v2(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress);

        //Function: protocol_node_startSync_v1
        //  Performs Version 1 of the Node Start Sync Sampling command.
        bool protocol_node_startSync_v1(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress);

        //Function: protocol_node_startNonSync_v1
        //  Performs Version 1 of the Start Non Sync Sampling command.
        bool protocol_node_startNonSync_v1(NodeAddress nodeAddress);

        //Function: protocol_node_startNonSync_v2
        //  Performs Version 2 of the Start Non Sync Sampling command.
        bool protocol_node_startNonSync_v2(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress);

        //Function: protocol_node_batchEepromRead_v1
        //    Performs Version 1 of the Node Batch Eeprom Read command.
        bool protocol_node_batchEepromRead_v1(NodeAddress nodeAddress, uint16 startEeprom, std::map<uint16, uint16>& result);

        //Function: protocol_node_testCommProtocol
        //    Performs Version 1 of the Node Test Communication Protocol command.
        bool protocol_node_testCommProtocol(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, WirelessTypes::CommProtocol protocol);

        //Function: protocol_node_poll
        //    Performs Version 1 of the Node Poll command.
        bool protocol_node_poll(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, const ChannelMask& chs, WirelessPollData& result);

    public:
        //Function: node_ping
        //    Pings the specified Node.
        //
        //Parameters:
        //    nodeProtocol - the <WirelessProtocol> for the Node.
        //    nodeAddress - the node address of the Node to ping.
        //
        //Returns:
        //    A <PingResponse> object that can be queried to get details of the ping command's response.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual PingResponse node_ping(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress);

        //Function: node_hardReset
        //    Performs a hard reset on the specified Node.
        //
        //Parameters:
        //    nodeProtocol - the <WirelessProtocol> for the Node.
        //    nodeAddress - the node address to perform the hard reset on
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to reset the Node.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        void node_hardReset(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress);

        //Function: node_softReset
        //    Performs a soft reset on the specified Node.
        //
        //Parameters:
        //    nodeProtocol - the <WirelessProtocol> for the Node.
        //    nodeAddress - the node address to perform the soft reset on
        //
        //Returns:
        //    true if the reset was successful, false otherwise.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to reset the Node.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        void node_softReset(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress);

        //Function: node_sleep
        //    Puts the Node into a low power, sleep mode.
        //    This command attempts to ping the node before sending the sleep command, to verify communication.
        //
        //Parameters:
        //    nodeProtocol - the <WirelessProtocol> for the Node.
        //    nodeAddress - The node adderss of the Node to put to sleep.
        //
        //Returns:
        //    true if the sleep command was successful, false otherwise.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual bool node_sleep(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress);

        //Function: node_setToIdle
        //    Attempts to set the node to idle so that it can be communicated with.
        //
        //Parameters:
        //    nodeAddress - the node address of the node to ping.
        //    base - A reference to the <BaseStation> that will be used for setting the node to idle.
        //
        //Returns:
        //    A <SetToIdleStatus> object that can be queried to get the status of the Set to Idle operation.
        //
        //Exceptions:
        //    - <Error_Communication>: Failed to communicate with the parent BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual SetToIdleStatus node_setToIdle(NodeAddress nodeAddress, const BaseStation& base);

        //Function: node_readEeprom
        //    Reads a value from EEPROM on the specified Node.
        //
        //Parameters:
        //    nodeProtocol - the <WirelessProtocol> for the Node.
        //    nodeAddress - the node address of the Node to read from.
        //    eepromAddress - the EEPROM address to read the value from.
        //    eepromValue - holds the result value read from EEPROM if successful.
        //
        //Returns:
        //    true if the command was successful, false otherwise.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Unsupported eeprom location.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation
        virtual bool node_readEeprom(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, uint16 eepromAddress, uint16& eepromValue);

        //Function: node_writeEeprom
        //    Writes a value to EEPROM on the specified Node.
        //
        //Parameters:
        //    nodeProtocol - the <WirelessProtocol> for the Node.
        //    nodeAddress - the node address of the node to write to.
        //    eepromAddress - the EEPROM address to write the value to.
        //    value - the value to write to EEPROM.
        //
        //Returns:
        //    true if the write eeprom command succeeded, false otherwise.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Unsupported eeprom location or value.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation
        virtual bool node_writeEeprom(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, uint16 eepromAddress, uint16 value);

        //Function: node_pageDownload
        //    Download a page of logged data from the Node
        //
        //Parameters:
        //    nodeProtocol - The <WirelessProtocol> for the Node.
        //    nodeAddress - The node address of the Node to download data from
        //    pageIndex - The page index to download from the Node
        //    data - Output parameter that contains the resulting data downloaded from the Node, if any
        //
        //Returns:
        //    true if the page download command succeeded, false otherwise
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual bool node_pageDownload(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, uint16 pageIndex, ByteStream& data);

        //Function: node_batchEepromRead
        //  Reads a batch of eeprom values from the Node
        //
        //Parameters:
        //  nodeProtocol - The <WirelessProtocol> for the Node.
        //  nodeAddress - The node address of the Node to download data from.
        //  startEeprom - The eeprom address to start the batch eeprom read from.
        //  result - The eeprom location/value map that will hold the result.
        //
        //Exceptions:
        //  - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual bool node_batchEepromRead(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, uint16 startEeprom, std::map<uint16, uint16>& result);

        //Function: node_getDatalogSessionInfo
        //  Gets info about the datalog sessions on the Node.
        //
        //Parameters:
        //  nodeProtocol - The <WirelessProtocol> for the Node.
        //  nodeAddress - The node address of the Node to download data from.
        //  result - The <DatalogSessionInfoResult> containing the result info on success.
        //
        //Returns:
        //  true if the command succeded, false otherwise
        //
        //Exceptions:
        //  - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual bool node_getDatalogSessionInfo(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, DatalogSessionInfoResult& result);

        //Function: node_getDatalogData
        //  Gets a section of logged data from the Node.
        //
        //Parameters:
        //  nodeProtocol - The <WirelessProtocol> for the Node.
        //  nodeAddress - The node address of the Node to download data from.
        //  flashAddress - The flash address to read from.
        //  result - The <ByteStream> containing the resulting data bytes from the Node on success.
        //  numBytesRead - The number of bytes that were read from the command and appended to the result <ByteStream>. 
        //
        //Returns:
        //  true if the command succeded, false otherwise
        //
        //Exceptions:
        //  - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual bool node_getDatalogData(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, uint32 flashAddress, ByteStream& result, uint16& numBytesRead);

        //Function: node_erase
        //    Sends the Erase command to a Node.
        //
        //Parameters:
        //    nodeProtocol - The <WirelessProtocol> for the Node.
        //    nodeAddress - The node address of the Node to send the command to.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual bool node_erase(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress);

        //Function: node_startSyncSampling
        //    Sends the Start Synchronized Sampling command to a Node.
        //
        //Parameters:
        //    nodeProtocol - The <WirelessProtocol> for the Node.
        //    nodeAddress - The node address of the Node to send the command to.
        //
        //Returns:
        //    true if the Start Sync Sampling command succeeded, false otherwise.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual bool node_startSyncSampling(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress);

        //Function: node_startNonSyncSampling
        //    Sends the Start Non-Synchronized Sampling command to a Node.
        //
        //Parameters:
        //    nodeProtocol - The <WirelessProtocol> for the Node.
        //    nodeAddress - The node address of the Node to send the command to.
        //
        //Returns:
        //  true if the Start Non Sync Sampling command succeded, false otherwise.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual bool node_startNonSyncSampling(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress);

        //Function: node_armForDatalogging
        //    Sends the Arm For Datalogging command to a Node.
        //
        //Parameters:
        //    nodeAddress - The node address of the Node to send the command to.
        //    message - A message, up to 50 characters, to send with the arm command. This message can be downloaded with the data. Will be trimmed to 50 chars if longer.
        //
        //Returns:
        //    true if the Arm For Datalogging command succeeded, false otherwise.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual bool node_armForDatalogging(NodeAddress nodeAddress, const std::string& message);

        //Function: node_triggerArmedDatalogging
        //    Sends the Trigger Armed Datalogging command to a Node.
        //
        //Parameters:
        //    nodeAddress - The node address of the Node to send the command to.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual void node_triggerArmedDatalogging(NodeAddress nodeAddress);

        //Function: node_autoBalance
        //    Sends the AutoBalance command to a Node.
        //
        //Parameters:
        //    nodeProtocol - The <WirelessProtocol> for the Node.
        //    nodeAddress - The node address of the Node to send the command to.
        //    channelNumber - The channel number (ch1 = 1, ch8 = 8) to balance.
        //    targetPercent - The target percentage (0 - 100) to balance to.
        //    result - The <AutoBalanceResult> of the command.
        //
        //Returns:
        //    true if the command succeeded, false if it failed.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        virtual bool node_autoBalance(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, uint8 channelNumber, float targetPercent, AutoBalanceResult& result);

        //Function: node_autocal_shm
        //    Performs automatic calibration for a Wireless Node.
        //
        //Parameters:
        //    nodeProtocol - The <WirelessProtocol> for the Node.
        //    nodeAddress - The node address of the Node to send the command to.
        //    result - The <AutoCalResult> reference to hold the result.
        //
        //Returns:
        //    true if the AutoCal command was successful, false otherwise.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        bool node_autocal_shm(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, AutoCalResult& result);

        //Function: node_autocal_shm201
        //    Performs automatic calibration for a Wireless Node.
        //
        //Parameters:
        //    nodeProtocol - The <WirelessProtocol> for the Node.
        //    nodeAddress - The node address of the Node to send the command to.
        //    result - The <AutoCalResult> reference to hold the result.
        //
        //Returns:
        //    true if the AutoCal command was successful, false otherwise.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        bool node_autocal_shm201(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, AutoCalResult& result);

        //Function: node_autoShuntCal
        //  Performs automatic shunt calibration for a Wireless Node.
        //
        //Parameters:
        //  nodeProtocol - The <WirelessProtocol> for the Node.
        //  commandDetails - The <AutoCalCmdDetails> for this command.
        //  result - The <AutoCalResult> reference to hold the result.
        //
        //Returns:
        //  true if the AutoCal command was successful, false otherwise.
        //
        //Exceptions:
        //  - <Error_Connection>: A connection error has occurred with the BaseStation.
        bool node_autoShuntCal(const WirelessProtocol& nodeProtocol,
                               const AutoCalCmdDetails& commandDetails,
                               AutoCalResult& result);

        //Function: node_readSingleSensor
        //    Reads the bits value for a single channel on a Wireless Node.
        //
        //Parameters:
        //    nodeAddress - The node address of the Node to send the command to.
        //    channelNumber - The channel number (ch1 = 1, ch8 = 8) to read.
        //    result - Holds the bits value result from the channel on the Node.
        //
        //Returns:
        //    true if the Read Single Sensor command was successful, false otherwise.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        bool node_readSingleSensor(NodeAddress nodeAddress, uint8 channelNumber, uint16& result);

        //Function: node_getDiagnosticInfo
        //  Performs an immediate request for the Node's Diagnostic Info.
        //
        //Parameters:
        //  nodeProtocol - The <WirelessProtocol> for the Node.
        //  nodeAddress - The node address of the Node to send the command to.
        //  result - The <ChannelData> container that will be filled with the result upon success.
        //
        //Returns:
        //  true if the command was successful, false otherwise.
        //
        //Exceptions:
        //  - <Error_Connection>: A connection error has occurred with the BaseStation.
        bool node_getDiagnosticInfo(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, ChannelData& result);

        //Function: node_testCommProtocol
        //  Tests if a Node will still be able to communicate after changing the Node's communication protocol.
        //
        //Parameters:
        //  nodeAddress - The node address of the Node to send the command to.
        //  commProtocol - The <WirelessTypes::CommProtocol> to test.
        //
        //Returns:
        //  true if communication in the new protocol mode was successful, false otherwise.
        //
        //Exceptions:
        //  - <Error_NotSupported>: The given communication protocol is not supported by the BaseStation.
        //  - <Error_Connection>: A connection error has occurred with the BaseStation.
        bool node_testCommProtocol(NodeAddress nodeAddress, WirelessTypes::CommProtocol commProtocol);

        //Function: node_poll
        //  Polls the WirelessNode to get a single sweep of calibrated data.
        //
        //Parameters:
        //  nodeProtocol - The <WirelessProtocol> for the Node.
        //  nodeAddress - The node address of the Node to send the command to.
        //  chs - The <ChannelMask> to poll data for. Note: if a channel is active that isn't supported by the Node, it will be ignored.
        //  result - The <WirelessPollData> map holding the result of the poll.
        //
        //Returns:
        //  true if the command was successful, false otherwise.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        bool node_poll(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, const ChannelMask& chs, WirelessPollData& result);

    private:
        //Function: node_autocal
        //  Performs automatic calibration for a Wireless Node.
        //
        //Parameters:
        //  nodeAddress - The node address of the Node to send the command to.
        //  command - The <ByteStream> containing the autocal command to send.
        //  response - The <AutoCal::Response> to use for parsing the response.
        //  result - The <AutoCalResult> reference to hold the result.
        //
        //Exceptions:
        //  - <Error_Connection>: A connection error has occurred with the BaseStation.
        bool node_autocal(NodeAddress nodeAddress, const ByteStream& command, AutoCal::Response& response, AutoCalResult& result);
    };
}