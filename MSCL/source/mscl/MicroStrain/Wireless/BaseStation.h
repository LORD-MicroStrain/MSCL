/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/Communication/Connection.h"
#include "mscl/MicroStrain/Wireless/DataSweep.h"
#include "mscl/MicroStrain/Wireless/NodeDiscovery.h"
#include "Commands/BeaconStatus.h"
#include "Commands/PingResponse.h"
#include "Commands/SetToIdleStatus.h"
#include "Configuration/ConfigIssue.h"
#include "BaseStationButton.h"
#include "BaseStationAnalogPair.h"
#include "WirelessTypes.h"
#include "WirelessModels.h"
#include "mscl/Version.h"

#include <memory>

namespace mscl
{
    //forward declarations
    class AutoBalanceResult;
    class AutoCalResult;
    class BaseStation_Impl;
    class BaseStationFeatures;
    class BaseStationEeprom;
    class BaseStationEepromHelper;
    class BaseStationConfig;
    struct BaseStationInfo;
    struct DatalogSessionInfoResult;
    class WirelessResponsePattern;
    struct AutoCalCmdDetails;
    class WirelessProtocol;

    //API Class: BaseStation
    //    Represents a MicroStrain Base Station object
    class BaseStation
    { 
    public:
        //=====================================================================================================
        //API Constants: Default Timeouts
        //    BASE_COMMANDS_DEFAULT_TIMEOUT     - 20 ms     - The default timeout for a base station command (in milliseconds) used by USB Bases
        //    EXT_BASE_COMMANDS_DEFAULT_TIMEOUT - 500 ms    - The extended default timeout for a base station command (in milliseconds)
        //    BROADCAST_NODE_ADDRESS            - 65535      - The address to use for performing Broadcast commands that will be heard by all <WirelessNode>s on the frequency.
        //    BROADCAST_NODE_ADDRESS_ASPP3      - 0xFFFFFFFF - The address to use for performing Broadcast commands that will be heard by all <WirelessNode>s on the frequency (ASPP 3.X).
        //=====================================================================================================
        static const uint64 BASE_COMMANDS_DEFAULT_TIMEOUT = 20;
        static const uint64 ETHERNET_BASE_COMMANDS_DEFAULT_TIMEOUT = 500;
        static const NodeAddress BROADCAST_NODE_ADDRESS = 0xFFFF;
        static const NodeAddress BROADCAST_NODE_ADDRESS_ASPP3 = 0xFFFFFFFF;

    public:
        //API Constructor: BaseStation
        //  Creates a BaseStation object.
        //  Note: this will use a default timeout of <BASE_COMMANDS_DEFAULT_TIMEOUT> for serial connections
        //        and a default timeout of <ETHERNET_BASE_COMMANDS_DEFAULT_TIMEOUT> for ethernet/websocket connections
        //    
        //Parameters:
        //    connection - The <Connection> object used for communication
        //
        //Exceptions:
        //    - <Error_Connection>: A problem occured with the Connection.
        explicit BaseStation(Connection& connection);

        //API Constructor: BaseStation
        //  Creates a BaseStation object.
        //    
        //Parameters:
        //    connection - The <Connection> object used for communication
        //    baseTimeout - The timeout to use for base station commands
        //
        //Exceptions:
        //    - <Error_Connection>: A problem occured with the Connection.
        explicit BaseStation(Connection& connection, uint64 baseTimeout);

        //Destructor: ~BaseStation
        //    Destroys a BaseStation object
        virtual ~BaseStation() {};

        //API Function: Mock
        //  Static function to create a Mock BaseStation (won't actually talk to a physical device).
        //
        //Parameters:
        //  info - The <BaseStationInfo> to use for creating the Mock BaseStation.
        //
        //Returns:
        //  A <BaseStation> object with a mock implementation.
        static BaseStation Mock(const BaseStationInfo& info);

        //API Function: Mock
        //  Static function to create a Mock BaseStation (won't actually talk to a physical device) using the following default info:
        //      Firmware version: 5.0
        //      Model: WSDA-Base 104 USB
        //      Region: USA
        //      asppVersion_LXRS: 1.7
        //      asppVersion_LXRS+: 3.0
        //
        //Returns:
        //  A <BaseStation> object with a mock implementation.
        static BaseStation Mock();

#ifndef SWIG
        BaseStation(std::shared_ptr<BaseStation_Impl> impl); //constructor with direct underlying implementation for this class.

        //Function: eepromHelper
        //    Gets a reference to the <BaseStationEepromHelper> for this BaseStation.
        BaseStationEepromHelper& eepromHelper() const;

        //Function: doCommand
        //    Performs a custom command and waits for the response.
        //    When completed, the <ResponsePattern> parameter will contain any result information.
        //    For a full explanation, see the <ResponsePattern> class.
        //
        //Parameters:
        //    response - A reference to a custom class that was inherited from the <WirelessResponsePattern> base class.
        //    cmdBytes - The <ByteStream> containing the command bytes to send.
        //    timeout - The maximum timeout to use for waiting for the response.
        //
        //Returns:
        //    true if the command was successful (response.success() is true), false otherwise.
        bool doCommand(WirelessResponsePattern& response, const ByteStream& cmdBytes, uint64 timeout);

        //Operator: ==
        //    Checks that two BaseStation objects are equal.
        //
        //Returns:
        //    true if the two BaseStation objects are identical, false otherwise.
        bool operator==(const BaseStation& src) const;

        //Operator: !=
        //    Checks that two BaseStation objects are not equal.
        //
        //Returns:
        //    true if the two BaseStation are not identical, false otherwise.
        bool operator!=(const BaseStation& src) const;
#endif

    private:
        BaseStation();        //default constructor disabled

    private:
        //Variable: m_impl
        //    The <BaseStation_Impl> class that contains all the implementation logic for the BaseStation class.
        std::shared_ptr<BaseStation_Impl> m_impl;

    public:
        //API Function: deviceName
        //    Static function for creating the universal basestation name that should be used for SensorCloud.
        //
        //Parameters:
        //    serial - The serial of the basestation. This should be identical to calling the <serial> function on a <BaseStation> object.
        //
        //Returns:
        //    The universal basestationName.
        static std::string deviceName(const std::string& serial);

        //API Function: connection
        //    Gets the <Connection> object that this BaseStation is using.
        //
        //Returns:
        //    The <Connection> object that this BaseStation is using.
        Connection& connection() const;

        //API Function: features
        //    Gets a reference to the <BaseStationFeatures> for this BaseStation.
        //    Note: This will be invalid when the BaseStation is destroyed.
        //
        //Returns:
        //    <BaseStationFeatures> containing the features for this BaseStation.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The BaseStation model is not supported by MSCL.
        //    - <Error_Communication>: Failed to communicate with the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        const BaseStationFeatures& features() const;

        //API Function: lastCommunicationTime
        //    Gets the <Timestamp> for the last time MSCL communicated with the BaseStation.
        //    Note: EEPROM reads using the cache, and data collection, will not update this timestamp.
        //
        //Returns:
        //    A <Timestamp> representing the last time MSCL communicated with the BaseStation. This will be a Timestamp of 0 if never communicated with.
        //
        //Exceptions:
        //  - <Error_NoData>: There is no communication time logged for this device.
        const Timestamp& lastCommunicationTime() const;

        //API Function: readWriteRetries
        //    Sets the number of retry attempts for reading and writing config options on the BaseStation.
        //    By default, the number of retries is 0.
        //    Note:    The timeout that is set per command will be per read and write attempt, meaning
        //            this retry number is multiplied by the timeout for your overall timeout.
        //
        //Parameters:
        //    numRetries - The number of retries to set for reading and writing config options on the BaseStation.
        void readWriteRetries(uint8 numRetries);

        //API Function: readWriteRetries
        //    Gets the number of retry attempts for reading and writing config options on the BaseStation.
        //    By default, the number of retries is 0.
        //    Note:    The timeout that is set per command will be per read and write attempt, meaning
        //            this retry number is multiplied by the timeout for your overall timeout.
        //
        //Returns:
        //    The number of retries to set for all reading and writing config options on the BaseStation.
        uint8 readWriteRetries() const;

        //API Function: useEepromCache
        //    Sets whether or not to utilize the eeprom cache when configuring this BaseStation (enabled by default). This can be enabled/disabled at any time.
        //    It is highly recommended to have eeprom caching be enabled.
        //    Note:    The eeprom cache stores the last known value that was written to / read from the BaseStation for each eeprom location. If this is enabled,
        //            any reads will get the last known value from the cache if it exists, and any writes will not write to the BaseStation if the
        //            value attempting to be written is the same as that stored in the cache. Caching of these values will still be performed if this is disabled,
        //            however, read and write operations will then always reach out to the actual device.
        //
        //Parameters:
        //    useCache - whether the eeprom cache should be used (true) or not (false).
        void useEepromCache(bool useCache);

        //API Function: clearEepromCache
        //    Clears the eeprom cache for this BaseStation.
        void clearEepromCache();

        //API Function: frequency
        //    Gets the <WirelessTypes::Frequency> representing the radio frequency of this BaseStation.
        //
        //Returns:
        //    The <WirelessTypes::Frequency> that this BaseStation is on.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_Communication>: Failed to read the value from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        WirelessTypes::Frequency frequency() const;

        //API Function: communicationProtocol
        //  Gets the <WirelessTypes::CommProtocol> that the BaseStation is currently set to use.
        //
        //Returns:
        //  The <WirelessTypes::CommProtocol> that the BaseStation is currently set to use.
        //
        //Exceptions:
        //    - <Error_Communication>: Failed to read the value from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        WirelessTypes::CommProtocol communicationProtocol() const;

        //API Function: firmwareVersion
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

        //API Function: model
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

        //API Function: serial
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

        //API Function: name
        //    Gets the name of the BaseStation. This is the universal basestation name that should be used for SensorCloud.
        //    This is the same as calling <BaseStation::deviceName>.
        //
        //Returns:
        //    The universal basestation name.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_Communication>: Failed to read the value from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        std::string name() const;

        //API Function: microcontroller
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

        //API Function: regionCode
        //    Gets the region code currently set on the BaseStation.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::RegionCode regionCode() const;

        //API Function: getData
        //    Gets up to the requested amount of <DataSweep>s of sampled data that was collected by this BaseStation.
        //
        //Parameters:
        //    timeout - The timeout, in milliseconds, to wait for data if necessary (default of 0).
        //    maxSweeps - The maximum number of sweeps to return. If this is 0 (default), all sweeps will be returned.
        //
        //Returns:
        //    A <DataSweeps> object containing all the data sweeps that are available up to the requested number of max sweeps. 
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation
        DataSweeps getData(uint32 timeout = 0, uint32 maxSweeps = 0);

        //API Function: totalData
        //    Gets the number of <DataSweep>s that are currently in the data buffer.
        //
        //Returns:
        //    The number of <DataSweep>s that are currently in the data buffer.
        uint32 totalData();

        //API Function: getNodeDiscoveries
        //    Gets the group of Node Discoveries that were collected by this base station.
        //    Calling this function clears out the Node Discovery buffer, so successively calling this will give you new Node Discoveries.
        //
        //Returns:
        //    A <NodeDiscoveries> container, holding all the Node Discoveries that were collected by this base station.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation
        NodeDiscoveries getNodeDiscoveries();

        //API Function: timeout
        //    Sets the timeout to use when waiting for responses from commands.
        //    This timeout is used directly for BaseStation commands, while some additional time is added for Node commands.
        //    Note: Some commands have a minimum timeout that will override this if set lower than the minimum.
        //
        //Parameters:
        //    timeout - The timeout (in milliseconds) to set for commands.
        void timeout(uint64 timeout);

        //API Function: timeout
        //    Gets the current timeout to use when waiting for responses from base station commands.
        //    This timeout is used directly for BaseStation commands, while some additional time is added for Node commands.
        //    Note: Some commands have a minimum timeout that will override this if set lower than the minimum.
        //
        //Returns:
        // The timeout (in milliseconds) set for base station commands.
        uint64 timeout() const;

        //API Function: ping
        //    Pings the base station
        //
        //Returns:
        //    true if successfully pinged the base station, false otherwise
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation
        //
        //Example Use:
        //    (start code)
        //        BaseStation baseStation(&connection);
        //        baseStation.ping();
        //    (end code)
        bool ping();

        //API Function: readEeprom
        //    Reads a specific EEPROM address on the Base Station.
        //    If the value stored in the eeprom cache is still valid, this will be returned instead.
        //
        //Parameters:
        //    eepromAddress - The EEPROM address to be read.
        //
        //Returns:
        //    The uint16 value read from the specified EEPROM location.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Unsupported eeprom location.
        //    - <Error_Communication>: Failed to read the value from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        uint16 readEeprom(uint16 eepromAddress) const;

        //API Function: writeEeprom
        //    Writes the specified value to a specific EEPROM address on the Base Station.
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
        void writeEeprom(uint16 eepromAddress, uint16 value);

        //API Function: enableBeacon
        //    Enables the beacon on the base station using the system time (UTC) as its starting timestamp.
        //
        //Returns:
        //    A <Timestamp> representing the initial time that was sent to start the beacon
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation
        //    - <Error_Communication>: The enable beacon command has failed.
        //
        //Example Use:
        //    (start code)
        //        BaseStation baseStation(connection);
        //        baseStation.enableBeacon();
        //    (end code)
        Timestamp enableBeacon();

        //API Function: enableBeacon
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
        //
        //Example Use:
        //    (start code)
        //        BaseStation baseStation(connection);
        //        baseStation.enableBeacon(1357846020);
        //    (end code)
        Timestamp enableBeacon(uint32 utcTime);

        //API Function: disableBeacon
        //    Disables the beacon on the base station.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation
        //    - <Error_Communication>: The disable beacon command has failed.
        //
        //Example Use:
        //    (start code)
        //        BaseStation baseStation(connection);
        //        baseStation.disableBeacon();
        //    (end code)
        void disableBeacon();

        //API Function: beaconStatus
        //    Gets the <BeaconStatus> of the beacon on the base station.
        //
        //Returns:
        //    A <BeaconStatus> object containing status information of the beacon.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Beacon Status is not supported by this BaseStation.
        //    - <Error_Communication>: Failed to get the beacon status.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        BeaconStatus beaconStatus();

        //API Function: startRfSweepMode
        //  Starts the BaseStation in a fixed RF Sweep Mode, which will sweep over all the supported operating frequencies of the BaseStation.
        //  Note: To exit this Mode, send any command to the BaseStation (such as ping).
        //
        //Exceptions:
        //    - <Error_NotSupported>: RF Sweep Mode is not supported by this BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        //    - <Error_Communication>: The command has failed.
        void startRfSweepMode();

        //API Function: startRfSweepMode
        //  Starts the BaseStation in a custom RF Sweep Mode across the provided frequencies.
        //  Note: To exit this Mode, send any command to the BaseStation (such as ping).
        //
        //Parameters:
        //  minFreq - The minimum frequency to use in the scan in kHz (2400000 = 2.4GHz).
        //  maxFreq - The maximum frequency to use in the scan in kHz (2400000 = 2.4GHz).
        //  interval - The interval between frequencies.
        //  options - This is currently an Advanced setting, used internally.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Raw RF Sweep Mode is not supported by this BaseStation.
        //  - <Error_Connection>: A connection error has occurred with the BaseStation.
        //  - <Error_Communication>: The command has failed.
        void startRfSweepMode(uint32 minFreq, uint32 maxFreq, uint32 interval, uint16 options=0);

        //API Function: cyclePower
        //    Cycles the power on the base station.
        //
        //Parameters:
        //  checkComm - Whether to check for communication (ping) after cycling power before returning from this function.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to write an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        //    - <Error_Communication>: Failed to cycle the power.
        void cyclePower(bool checkComm=true);

        //API Function: resetRadio
        //    Resets the radio on the base station.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to write an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        //    - <Error_Communication>: Failed to cycle the power.
        void resetRadio();

        //API Function: changeFrequency
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

        //API Function: broadcastSetToIdle
        //  Broadcasts the Set to Idle command (will be heard by all nodes on the BaseStation's frequency).
        //
        //Returns:
        //  A <SetToIdleStatus> object that can be used to cancel the operation.
        //  Note that this status object will never complete as it is not targeting a specific Node.
        //
        //Exceptions:
        //  - <Error_Connection>: A connection error has occurred with the BaseStation.
        mscl::SetToIdleStatus broadcastSetToIdle();

        //API Function: verifyConfig
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
        //    - <Error_NotSupported>: The BaseStation model, or firmware version, is not supported by MSCL.
        //    - <Error_Communication>: Failed to communicate with the BaseStation.
        //    - <Error_Connection>: A connection error has occurred.
        bool verifyConfig(const BaseStationConfig& config, ConfigIssues& outIssues) const;

        //API Function: applyConfig
        //    Applies a <BaseStationConfig> to the Node.
        //    Note: This applies all options that have been set in the <BaseStationConfig>. 
        //          Before applying, the options will be validated. It is recommended that you perform
        //          this validation yourself first by using <verifyConfig>.
        //
        //Parameters:
        //    config - The <BaseStationConfig> to apply to the Node.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The BaseStation model, or firmware version, is not supported by MSCL.
        //    - <Error_InvalidConfig>: Invalid Configuration. Check the exception for specific details.
        //    - <Error_Communication>: Failed to write to the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        void applyConfig(const BaseStationConfig& config);

        //API Function: getTransmitPower
        //    Reads the <WirelessTypes::TransmitPower> that is currently set on the BaseStation.
        //
        //Returns:
        //    The <WirelessTypes::TransmitPower> that is currently set on the BaseStation.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Attempted to read an unsupported option. The device firmware is not compatible with this version of MSCL.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        WirelessTypes::TransmitPower getTransmitPower() const;

        //API Function: getButtonLongPress
        //    Reads the button settings for a long press action that are currently set on the BaseStation.
        //
        //Parameters:
        //    buttonNumber - The button number (1 = button 1) to get the value for.
        //
        //Returns:
        //    A <BaseStationButton> object holding the current long press settings for the requested button number.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The BaseStation does not support the requested button.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        BaseStationButton getButtonLongPress(uint8 buttonNumber) const;

        //API Function: getButtonShortPress
        //    Reads the button settings for a short press action that are currently set on the BaseStation.
        //
        //Parameters:
        //    buttonNumber - The button number (1 = button 1) to get the value for.
        //
        //Returns:
        //    A <BaseStationButton> object holding the current short press settings for the requested button number.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The BaseStation does not support the requested button.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        BaseStationButton getButtonShortPress(uint8 buttonNumber) const;

        //API Function: getAnalogPairingEnabled
        //    Reads the Analog Pairing enabled/disabled setting that is currently set on the BaseStation.
        //    If this is disabled, all other analog pairing settings will be disabled.
        //
        //Returns:
        //    true if Analog Pairing is enabled, false otherwise.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The BaseStation does not support Analog Pairing.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        bool getAnalogPairingEnabled() const;

        //API Function: getAnalogTimeoutTime
        //    Reads the Analog Timeout Time in seconds that is currently set on the BaseStation.
        //
        //Returns:
        //    The analog timeout time in seconds.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The BaseStation does not support Analog Pairing.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        uint16 getAnalogTimeoutTime() const;

        //API Function: getAnalogTimeoutVoltage
        //    Reads the Analog Timeout Voltage that is currently set on the BaseStation.
        //
        //Returns:
        //    The analog timeout voltage.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The BaseStation does not support Analog Pairing.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        float getAnalogTimeoutVoltage() const;

        //API Function: getAnalogExceedanceEnabled
        //    Reads the Analog Exceedance enabled/disabled setting that is currently set on the BaseStation.
        //
        //Returns:
        //    true if Analog Exceedance is enabled, false otherwise.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The BaseStation does not support Analog Pairing.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        bool getAnalogExceedanceEnabled() const;

        //API Function: getAnalogPair
        //    Reads the <BaseStationAnalogPair> for the specified port number that is currently set on the BaseStation.
        //
        //Parameters:
        //    portNumber - The port number (1 = port 1) to get the value for.
        //
        //Returns:
        //    The <BaseStationAnalogPair> for the specified port number that is currently set on the BaseStation.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The BaseStation does not support Analog Pairing.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        BaseStationAnalogPair getAnalogPair(uint8 portNumber) const;

//all the node functions in the base station class should not be exposed to SWIG
#ifndef SWIG
    public:
        //Function: node_ping
        //    Pings the specified Node.
        //
        //Parameters:
        //    nodeProtocol - the <WirelessProtocol> for the Node.
        //    nodeAddress - the node address of the node to ping.
        //
        //Returns:
        //    A <PingResponse> object that can be queried to get details of the ping command's response.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        PingResponse node_ping(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress);

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
        bool node_sleep(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress);

        //Function: node_setToIdle
        //    Attempts to set the node to idle so that it can be communicated with.
        //
        //Parameters:
        //    nodeAddress - the node address of the node to set to idle.
        //
        //Returns:
        //    A <SetToIdleStatus> object that can be queried to get the status of the Set to Idle operation.
        //
        //Exceptions:
        //    - <Error_Communication>: Failed to communicate with the parent BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        SetToIdleStatus node_setToIdle(NodeAddress nodeAddress);

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
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        bool node_readEeprom(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, uint16 eepromAddress, uint16& eepromValue);

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
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        bool node_writeEeprom(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, uint16 eepromAddress, uint16 value);

        //Function: node_pageDownload
        //    Downloads a page of logged data from the Node.
        //
        //Parameters:
        //    nodeProtocol - The <WirelessProtocol> for the Node.
        //    nodeAddress - The node address of the Node to download data from.
        //    pageIndex - The page index to download from the Node.
        //    data - Output parameter that contains the resulting data downloaded from the Node, if any.
        //
        //Returns:
        //    true if the page download command succeeded, false otherwise.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        bool node_pageDownload(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, uint16 pageIndex, ByteStream& data);

        //Function: node_batchEepromRead
        //  Reads a batch of eeprom values from the Node
        //
        //Parameters:
        //  nodeProtocol - The <WirelessProtocol> for the Node.
        //  nodeAddress - The node address of the Node to download data from.
        //  startEeprom - The eeprom address to start the batch eeprom read from.
        //  result - The eeprom location/value map that will hold the result.
        //
        //Returns:
        //  true if the command succeeded, false otherwise.
        //
        //Exceptions:
        //  - <Error_Connection>: A connection error has occurred with the BaseStation.
        bool node_batchEepromRead(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, uint16 startEeprom, std::map<uint16, uint16>& result);

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
        bool node_getDatalogSessionInfo(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, DatalogSessionInfoResult& result);

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
        bool node_getDatalogData(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, uint32 flashAddress, ByteStream& result, uint16& numBytesRead);

        //Function: node_erase
        //    Sends the Erase command to a Node.
        //
        //Parameters:
        //    nodeProtocol - The <WirelessProtocol> for the Node.
        //    nodeAddress - The node address of the Node to send the command to.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        bool node_erase(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress);

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
        bool node_startSyncSampling(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress);

        //Function: node_startNonSyncSampling
        //    Sends the Start Non-Synchronized Sampling command to a Node.
        //
        //Parameters:
        //    nodeProtocol - The <WirelessProtocol> for the Node.
        //    nodeAddress - The node address of the Node to send the command to.
        //
        //Returns:
        //  true if the Start Non Sync Sampling command succeeded, false otherwise.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        bool node_startNonSyncSampling(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress);

        //Function: node_armForDatalogging
        //    Sends the Arm For Datalogging command to a Node.
        //
        //Parameters:
        //    nodeAddress - The node address of the Node to send the command to.
        //    message - A message, up to 50 characters, to send with the arm command. This message can be downloaded with the data. Will be trimmed to 50 chars if longer. (Default of "")
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        bool node_armForDatalogging(NodeAddress nodeAddress, const std::string& message = "");

        //Function: node_triggerArmedDatalogging
        //    Sends the Trigger Armed Datalogging command to a Node.
        //
        //Parameters:
        //    nodeAddress - The node address of the Node to send the command to.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        void node_triggerArmedDatalogging(NodeAddress nodeAddress);

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
        bool node_autoBalance(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, uint8 channelNumber, float targetPercent, AutoBalanceResult& result);

        //Function: node_autocal_shm
        //    Performs automatic calibration for an SHM-Link.
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
        //    Performs automatic calibration for an SHM-Link-201.
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
        //  true if the auto shunt cal command was successful, false otherwise.
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
        //  protocol - The <WirelessTypes::CommProtocol> to test.
        //
        //Returns:
        //  true if communication in the new protocol mode was successful, false otherwise.
        //
        //Exceptions:
        //  - <Error_Connection>: A connection error has occurred with the BaseStation.
        bool node_testCommProtocol(NodeAddress nodeAddress, WirelessTypes::CommProtocol protocol);

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

        //API Function: getRawBytePackets
        //    Gets up to the requested amount of raw byte packets that have been collected.
        //
        //Parameters:
        //    packets - A vector of <RawBytePacket> to hold the result.
        //    timeout - the timeout, in milliseconds, to wait for the data if necessary (default of 0)
        //    maxPackets - The maximum number of packets to return. If this is 0 (default), all packets will be returned.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the Node.
        RawBytePackets getRawBytePackets(uint32 timeout = 0, uint32 maxPackets = 0);
#endif

    };
}
