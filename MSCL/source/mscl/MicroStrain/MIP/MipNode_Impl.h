/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include <memory>

#include "mscl/MicroStrain/MIP/MipChannel.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/Ping.h"
#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"
#include "mscl/MicroStrain/MIP/Commands/GetDeviceInfo.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketCollector.h"
#include "mscl/Communication/Connection.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/Inertial/EulerAngles.h"
#include "mscl/MicroStrain/Inertial/PositionOffset.h"
#include "mscl/Timestamp.h"
#include "mscl/MicroStrain/Inertial/ExposedInertialTypes.h"
#include "mscl/MicroStrain/LinearEquation.h"

namespace mscl
{
    //forward declarations
    class MipParser;
    class MipNodeInfo;
    class MipNodeFeatures;
    class MipCommand;

    //Class: MipNode_Impl
    //     Contains the implementation for an <InertialNode>.
    class MipNode_Impl
    {
    private:
        //Constant: COMMANDS_DEFAULT_TIMEOUT
        //    The default timeout for Inertial commands (250 milliseconds)
        static const uint64 COMMANDS_DEFAULT_TIMEOUT = 250;

    public:
        //Constructor: MipNode_Impl
        //    Creates an MipNode_Impl object.
        //
        //Parameters:
        //    connection - The Connection object used for communication.
        explicit MipNode_Impl(Connection connection);

        //Destructor: ~InertialNode
        //    Destroys the InertialNode object
        ~MipNode_Impl();

    private:
        MipNode_Impl();                                    //default constructor disabled
        MipNode_Impl(const MipNode_Impl&);            //copy constructor disabled
        MipNode_Impl& operator=(const MipNode_Impl&);    //assignment operator disabled

    private:
        //Variable: m_connection
        //    The Connection object used for communication
        Connection m_connection;

        //Variable: m_packetCollector
        //    The <MipPacketCollector> used to store interial data packets
        MipPacketCollector m_packetCollector;

        //Variable: m_responseCollector
        //    The response collector used to find and store wireless command responses
        std::shared_ptr<ResponseCollector> m_responseCollector;

        //Variable: m_parser
        //    The <MipParser> in charge of parsing all incoming data to this device
        std::unique_ptr<MipParser> m_parser;

        //Variable: m_commandsTimeout
        //    The timeout to use for MIP commands
        uint64 m_commandsTimeout;

        //Variable: m_nodeInfo
        //    The <MipNodeInfo> object that gives access to information of the Node
        mutable std::unique_ptr<MipNodeInfo> m_nodeInfo;

        //Variable: m_features
        //    The <MipNodeFeatures> containing the features for this device.
        mutable std::unique_ptr<MipNodeFeatures> m_features;

        //Variable: m_sensorRateBase
        //    The Sensor sample rate base (if any).
        mutable uint16 m_sensorRateBase;

        //Variable: m_gnssRateBase
        //    The GNSS sample rate base (if any).
        mutable uint16 m_gnssRateBase;

        //Variable: m_sensorRateBase
        //    The Estimation Filter sample rate base (if any).
        mutable uint16 m_estfilterRateBase;

        //Variable: m_lastCommTime
        //    A <Timestamp> representing the last time communication was achieved with the Node.
        Timestamp m_lastCommTime;

    private:
        //Function: parseData
        //    Callback function that parses any bytes that are in the read buffer to find packets or command responses
        //
        //Parameters:
        //    data - The <DataBuffer> containing all the data to be parsed
        void parseData(DataBuffer& data);

        //Function: info
        //    Gets the <MipNodeInfo> for this Node. 
        //    The first time this function is called, it will send multiple commands to the device to get all required information.
        //
        //Returns:
        //    A reference to the <MipNodeInfo> for this Node.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: Information failed to be loaded for this Node.
        const MipNodeInfo& info() const;

	public:
        //Function: doCommand
        //    Performs a generic MIP Command, sending the command bytes and waiting for the response.
        //
        //Parameters:
        //    response - A <GenericMipCommand::Response> that will be used to wait and contain all the command/result information.
        //    command - The <ByteStream> containing the bytes to send for the command.
        //    minimumTimeout - The <uint64> minimum time needed for the response.  Will always use at least COMMANDS_DEFAULT_TIMEOUT.
        //    verifySupported - Whether to verify if the command is supported before performing the command (default of true).
        //
        //Returns:
        //    The <GenericMipCmdResponse> that contains the actual data from the response
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_MipCmdFailed>: The command has failed.
        virtual GenericMipCmdResponse doCommand(GenericMipCommand::Response& response, const ByteStream& command, bool verifySupported = true) const;

        virtual Bytes doCommand(uint8 descriptorSet, uint8 cmdDescriptor, const Bytes& fieldData, bool ackNackResponse, bool dataResponse, uint8 responseDataDescriptor = 0) const;

        //Function: features
        //    Gets a reference to the <MipNodeFeatures> for this device.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The model is not supported by MSCL.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: Information failed to be loaded for this Node.
        virtual const MipNodeFeatures& features() const;

        //Function: connection
        //    Gets the <Connection> object that this BaseStation is using.
        Connection& connection();

        //Function: lastCommunicationTime
        //    Gets the <Timestamp> for the last time we communicated with the Node.
        //
        //Exceptions:
        //  - <Error_NoData>: There is no communication time logged for this device.
        const Timestamp& lastCommunicationTime() const;

        //Function: firmwareVersion
        //    Gets the firmware <Version> of the Node.
        Version firmwareVersion() const;

        //Function: modelName
        //    Gets the model name of the Node (ie. "3DM-GX3-45").
        std::string modelName() const;

        //Function: modelNumber
        //    Gets the model number of the Node (ie. "6225-4220").
        std::string modelNumber() const;

        //Function: serialNumber
        //    Gets the serial number of the Node (ie. "6225-01319").
        std::string serialNumber() const;

        //Function: lotNumber
        //    Gets the lot number of the Node (ie. "I042Y").
        std::string lotNumber() const;

        //Function: deviceOptions
        //    Gets the device options of the Node (ie. "5g, 300d/s").
        std::string deviceOptions() const;

        //Function: supportedSampleRates
        //    Gets a list of the supported sample rates for an <MipTypes::DataClass>.
        //
        //Parameters:
        //    category - The <MipTypes::DataClass> to get the sample rate list for.
        //
        //Returns:
        //    A <SampleRates> list containing all the supported sample rates for the provided channel.
        //
        //Exceptions:
        //    - <Error>: The <MipTypes::DataClass> is invalid.
        SampleRates supportedSampleRates(MipTypes::DataClass category) const;

        //Function: getDataPackets
        //    Gets up to the requested amount of data packets that have been collected.
        //
        //Parameters:
        //    packets - A vector of <MipDataPacket> to hold the result.
        //    timeout - the timeout, in milliseconds, to wait for the data if necessary (default of 0)
        //    maxPackets - The maximum number of packets to return. If this is 0 (default), all packets will be returned.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the Node.
        void getDataPackets(std::vector<MipDataPacket>& packets, uint32 timeout = 0, uint32 maxPackets = 0);

        //Function: totalPackets
        //    Gets the total number of data packets that are currently in the buffer.
        //
        //Returns:
        //    The total number of data packets that are currently in the buffer.
        uint32 totalPackets();

        //Function: timeout
        //    Sets the timeout to use when waiting for responses from commands.
        //
        //Parameters:
        //    timeout - The timeout (in milliseconds) to set for commands.
        void timeout(uint64 timeout);

        //Function: timeout
        //    Gets the timeout to use when waiting for responses from commands.
        //
        //Returns:
        //    The timeout (in milliseconds) used for commands.
        uint64 timeout();

        //Function: getDeviceInfo
        //    Gets information about the Node.
        //    Sends the "Get Device Information" command to the device.
        //
        //Returns:
        //    A <MipDeviceInfo> object that holds the response of the "Get Device Information" command.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        virtual MipDeviceInfo getDeviceInfo() const;

        //Function: getDescriptorSets
        //    Gets the supported descriptor sets for this node, representing which commands and data sets are available.
        //    Sends the "Get Device Descriptor Sets" command to the device. 
        //
        //Returns:
        //    The supported descriptors retrieved from the "Get Device Descriptor Sets" command.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        virtual std::vector<uint16> getDescriptorSets() const;

    public:
        //Function: ping
        //    Pings the node to check for communication. 
        //    Sends the "Ping" command to the device.
        //
        //Returns:
        //    true if successfully pinged the node, false if failed.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        bool ping();

        //Function: setToIdle
        //    Suspends streaming (if enabled) or wakes the device from sleep (if sleeping), putting the device in an idle mode.
        //    After this command is used, the <resume> command may be used to put the Node back into the mode it was previously in before setToIdle was called.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setToIdle();

        //Function: cyclePower
        //  Performs the "Device Reset" Inertial command.
        //
        //Exceptions:
        //  - <Error_Communication>: There was no response to the command. The command timed out.
        //  - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //  - <Error_Connection>: A connection error has occurred with the InertialNode.
        bool cyclePower();

        //Function: resume
        //    Places the Node back in the mode it was in before issuing the <setToIdle> command.
        //    If the <setToIdle> command was not issues, then the device is placed in default mode.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void resume();

        //Function: saveSettingsAsStartup
        //  Saves all of the current settings as the Node's startup settings.
        //  Note: A brief data disturbance may occur when calling this command.
        //
        //Exceptions:
        //  - <Error_Communication>: There was no response to the command. The command timed out.
        //  - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //  - <Error_Connection>: A connection error has occurred with the InertialNode.
        void saveSettingsAsStartup();

        //Function: loadStartupSettings
        //  Loads the saved startup settings onto the Node as its current settings.
        //  This function is useful if you have powered on the Node, made changes to its settings, and
        //  want to get back to its startup settings.
        //
        //Exceptions:
        //  - <Error_Communication>: There was no response to the command. The command timed out.
        //  - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //  - <Error_Connection>: A connection error has occurred with the InertialNode.
        void loadStartupSettings();

        //Function: loadFactoryDefaultSettings
        //  Loads the factory default settings onto the Node as its current settings.
        //
        //Exceptions:
        //  - <Error_Communication>: There was no response to the command. The command timed out.
        //  - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //  - <Error_Connection>: A connection error has occurred with the InertialNode.
        void loadFactoryDefaultSettings();

        //Function: getDataRateBase
        //    Gets the Data decimation base for the data rate calculations of the specified <MipTypes::DataClass>.
        //
        //Parameters:
        //    category - The <MipTypes::DataClass> to get the Data decimation base for.
        //
        //Returns:
        //    The decimation base for the data rate calculations.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command or <MipTypes::DataClass> is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        virtual uint16 getDataRateBase(MipTypes::DataClass category) const;

        //Function: getMessageFormat
        //    Gets the current message format of the specified <MipTypes::DataClass>'s data packet. 
        //
        //Parameters:
        //    category - The <MipTypes::DataClass> to get the current message format for.
        //
        //Returns:
        //    An <MipChannels> object containing the channels that make up the data message format for the specified <MipTypes::DataClass>
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command or <MipTypes::DataClass> is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        virtual MipChannels getMessageFormat(MipTypes::DataClass category);

        //Function: setMessageFormat
        //    Sets the current message format of the specified <MipTypes::DataClass>'s data packet.
        //    Note that this function does not add to the existing message format, but overwrites it entirely.
        //
        //Parameters:
        //    category - The <MipTypes::DataClass> to set the message format for.
        //    channels - The <MipChannels> object containing the channels to set the message format to. Passing an empty <MipChannels> object will effectively disable all channels.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command or <MipTypes::DataClass> is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        //    - <Error>: An <MipChannel> in the channels parameter is not part of the specified <MipTypes::DataClass>'s descriptor set.
        virtual void setMessageFormat(MipTypes::DataClass category, const MipChannels& channels);

        //Function: saveMessageFormat
        //    Saves the current message format of the specified <MipTypes::DataClass>'s data packet.
        //    Note that this function does not add to the existing message format, but overwrites it entirely.
        //
        //Parameters:
        //    category - The <MipTypes::DataClass> to set the message format for.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command or <MipTypes::DataClass> is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        //    - <Error>: An <MipChannel> in the channels parameter is not part of the specified <MipTypes::DataClass>'s descriptor set.
        void saveMessageFormat(MipTypes::DataClass type);

        //Function: getCommunicationMode
        //    Gets the current communication mode that the node is in.
        //
        //Returns:
        //    The communication mode the node is in. This is an advanced command, and therefore the communication modes for your device should be researched to determine what each communication mode is.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        virtual uint8 getCommunicationMode();

        //Function: setCommunicationMode
        //    Sets the communication mode for the node. 
        //    Note: The node info will be reset when doing this and therefore will require being fetched again the next time it is requested.
        //
        //Parameters:
        //    communicationMode - The communication mode to set. This is an advanced command, and therefore the communication modes for your device should be researched to determine what each communication mode is.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        virtual void setCommunicationMode(uint8 communicationMode);

        //Function: enableDataStream
        //    Enables or disables continuous data streaming for the node.
        //
        //Parameters:
        //    category - The <MipTypes::DataClass> to enable/disable streaming for.
        //    enable - Whether to enable (true) or disable (false) continuous streaming (Default of true).
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command, or <MipTypes::InertialTypeCategory>, is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void enableDataStream(MipTypes::DataClass category, bool enable);

        //Function: resetFilter
        //    Resets the filter to the initialize state.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void resetFilter();

        //Function: getAutoInitialization
        //    Gets the state of the automatic initialization upon device startup.
        //
        //Returns:
        //    true if auto-initialization is enabled, false if it is disabled.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        bool getAutoInitialization();

        //Function: setAutoInitialization
        //    Sets the state of the automatic initialization upon device startup.
        //
        //Parameters:
        //    enable - Whether to enable (true) or disable(false) auto-initialization.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setAutoInitialization(bool enable);

        //Function: setInitialAttitude
        //    Sets the initial attitude.
        //
        //Parameters:
        //  attitude - The <EulerAngles> (in radians) representing the sensor body frame with respect to the local NED frame.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setInitialAttitude(const EulerAngles& attitude);

        //Function: setInitialHeading
        //    Sets the initial heading.
        //
        //Parameters:
        //  heading - The heading to set (in radians).
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setInitialHeading(float heading);

        //Function: getSensorToVehicleTransformation
        //    Gets the sensor to vehicle frame transformation matrix using roll, pitch, and yaw Euler angles (in radians).
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command or <MipTypes::DataClass> is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        EulerAngles getSensorToVehicleTransformation();

        //Function: setSensorToVehicleTransformation
        //    Sets the sensor to vehicle frame transformation matrix using roll, pitch, and yaw Euler angles (in radians).
        //
        //Parameters:
        //    angles - The <EulerAngles> object containing the roll, pitch, and yaw to set.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setSensorToVehicleTransformation(const EulerAngles& angles);

        //Function: getSensorToVehicleOffset
        //    Gets the sensor to vehicle frame offset, expressed in the sensor frame.
        //
        //Returns:
        //    A <PositionOffset> representing the sensor to vehicle frame offset, expressed in the sensor frame.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        PositionOffset getSensorToVehicleOffset();

        //Function: setSensorToVehicleTransformation
        //    Sets the sensor to vehicle frame offset, expressed in the sensor frame.
        //
        //Parameters:
        //    offset - The <PositionOffset> object containing the x, y, and z position (in meters) to set.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setSensorToVehicleOffset(const PositionOffset& offset);

        //Function: getAntennaOffset
        //    Gets the antenna offset, expressed in the sensor frame.
        //
        //Returns:
        //    The <PositionOffset> of the antenna, expressed in the sensor frame.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        PositionOffset getAntennaOffset();

        //Function: setAntennaOffset
        //    Sets the antenna offset, expressed in the sensor frame.
        //
        //Parameters:
        //    offset - The <PositionOffset> object containing the x, y, and z position (in meters) to set.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setAntennaOffset(const PositionOffset& offset);

        //Function: getGNSSAssistedFixControl
        //    Gets the GNSS Assisted Fix Control.
        //
        //Returns:
        //    bool indicating if assisted fix is enabled.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        bool getGNSSAssistedFixControl();

        //Function: setGNSSAssistedFixControl
        //    Sets the GNSS Assisted Fix Control.
        //
        //Parameters:
        //    enableAssistedFix - boolean value.  If true, enables the assisted fix option.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
		void setGNSSAssistedFixControl(bool enableAssistedFix);

        //Function: getGNSSAssistTimeUpdate
        //    Gets the GNSS Assisted Time Update.
        //Returns:
        //    The GNSS Assist <TimeUpdate>.
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        TimeUpdate getGNSSAssistTimeUpdate();

        //Function: setGNSSAssistTimeUpdate
        //    Sets the GNSS Assist Time Update.
        //
        //Parameters:
        //    TimeUpdate - The <TimeUpdate> object containing the new time to set.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setGNSSAssistTimeUpdate(TimeUpdate update);

        //Function: getGPSTimeUpdateWeeks
        //    Gets the GPS weeks time update.
        //
        //Returns:
        //    time - the current weeks time.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        uint32 getGPSTimeUpdateWeeks();

        //Function: getGPSTimeUpdateSeconds
        //    Gets the GPS seconds time update.
        //
        //Returns:
        //    time - the current seconds time.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        uint32 getGPSTimeUpdateSeconds();

        //Function: setGPSTimeUpdate
        //    Sets the GPS Time Update.
        //
        //Parameters:
        //    timeFrame - The <TimeFrame> object specifying what current time value to set, either weeks or seconds.
        //    timeData - the current time.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setGPSTimeUpdate(MipTypes::TimeFrame timeFrame, uint32 timeData);

        //Function: setConstellationSettings
        //    Sets the GNSS Constellation Settings.
        //
        //Parameters:
        //    The <ConstellationSettingsData> object containing the data to set.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setConstellationSettings(const ConstellationSettingsData&);

        //Function: getConstellationSettings
        //    Gets the GNSS Constellation Settings.
        //
        //Returns:
        //    The <ConstellationSettingsData> object containing the data.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        ConstellationSettingsData getConstellationSettings();

        //Function: setSBASSettings
        //    Sets the GNSS SBAS Settings.
        //
        //Parameters:
        //    dataToUse - The <SBASSettingsData> object containing the data to set.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setSBASSettings(const SBASSettingsData& dataToUse);

        //Function: getSBASSettings
        //    Gets the GNSS SBAS Settings.
        //
        //Returns:
        //    The <SBASSettingsData> object containing the data.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        SBASSettingsData getSBASSettings();

        //Function: setAccelerometerBias
        //    Sets the Accelerometer Bias.
        //
        //Parameters:
        //    biasVector - The <GeometricVector> object containing the vector to set.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setAccelerometerBias(const GeometricVector& biasVector);

        //Function: getAccelerometerBias
        //    Gets the Accelerometer Bias.
        //
        //Return:
        //    The <GeometricVector> object containing the vector.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        GeometricVector getAccelerometerBias();

        //Function: setGyroBias
        //    Sets the Gyro Bias.
        //
        //Parameters:
        //    The <GeometricVector> object containing the vector to set.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setGyroBias(const GeometricVector& biasVector);

        //Function: getGyroBias
        //    Gets the Gyro Bias.
        //
        //Return:
        //    The <GeometricVector> object containing the vector.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        GeometricVector getGyroBias();
        
        //Function: captureGyroBias
        //    Runs the Gyro Bias capture routine on the inertial device.
        //
        //Parameters:
        //    The <uint16> samplingTime.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        GeometricVector captureGyroBias(const uint16& samplingTime);

        //Function: setMagnetometerSoftIronMatrix
        //    Sets the Magnetometer Soft Iron matrix.
        //
        //Parameters:
        //    The <Matrix_3x3> object containing the matrix to set.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setMagnetometerSoftIronMatrix(const Matrix_3x3& biasVector);

        //Function: getMagnetometerSoftIronMatrix
        //    Gets the Magnetometer Soft Iron matrix.
        //
        //Return:
        //    The <GeometricVector> object containing the matrix.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        Matrix_3x3 getMagnetometerSoftIronMatrix();


        //Function: setMagnetometerHardIronOffset
        //    Sets the magnetometer hard iron offset vector.
        //
        //Parameters:
        //    offsetVector - The <GeometricVector> object containing the vector to set.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setMagnetometerHardIronOffset(const GeometricVector& offsetVector);

        //Function: setMagnetometerHardIronOffset
        //    Gets the magnetometer hard iron offset vector.
        //
        //Return:
        //    The <GeometricVector> object containing the offset vector.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        GeometricVector getMagnetometerHardIronOffset();

        //Function: setConingAndScullingEnable
        //    Enables/disables coning and sculling.
        //
        //Parameters:
        //    bool indicating whether to enable coning and sculling.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setConingAndScullingEnable(bool enable);

        //Function: getConingAndScullingEnable
        //    determines whether coning and sculling are enabled.
        //
        //Return:
        //    bool indicating whether coning and sculling are enabled.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        bool getConingAndScullingEnable();

        //Function: setUARTBaudRate
        //    Sets the baud rate.  The device can be unresponsive for as much as 250 ms following this command.
        //
        //Parameters:
        //    baudRate - The new baud rate.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setUARTBaudRate(uint32 baudRate);

        //Function: getUARTBaudRate
        //    Gets the current baud rate for the inertial device.
        //
        //Return:
        //    uint8 current baud rate.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        uint32 getUARTBaudRate();

        //Function: setAdvancedLowPassFilterSettings
        //    Sets the advanced low-pass filter settings.
        //
        //Parameters:
        //    data - the new settings to set.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setAdvancedLowPassFilterSettings(const AdvancedLowPassFilterData& data);

        //Function: getAdvancedLowPassFilterSettings
        //    AdvancedLowPassFilterData new settings.  The <AdvancedLowPassFilterData::DataDescriptor> field
        //    from the passed in data is used to set the type of data to be returned.
        //
        //Parameters:
        //    data - The <AdvancedLowPassFilterData::DataDescriptor> field from
        //    the passed in data is used to set the type of data to be returned.
        //
        //Return:
        //    AdvancedLowPassFilterData new settings.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        AdvancedLowPassFilterData getAdvancedLowPassFilterSettings(const AdvancedLowPassFilterData& data);

        //Function: setComplementaryFilterSettings
        //    Sets the complementary filter settings.
        //
        //Parameter:
        //    data - the new settings to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setComplementaryFilterSettings(const ComplementaryFilterData& data);

        //Function: getComplementaryFilterSettings
        //    Gets the current complementary filter settings.
        //
        //Return:
        //    ComplementaryFilterData - The new settings.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        ComplementaryFilterData getComplementaryFilterSettings();

        //Function: getBasicDeviceStatus
        //    Gets the basic device status settings.
        //
        //Return:
        //    DeviceStatusData - The new settings.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        DeviceStatusData getBasicDeviceStatus();

        //Function: getDiagnosticDeviceStatus
        //    Gets the diagnostic device status settings.
        //
        //Return:
        //    DeviceStatusData - The new settings.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        DeviceStatusData getDiagnosticDeviceStatus();

        //Function: sendRawRTCM_2_3Message
        //    Sends a raw RTCM 2.3 message.
        //
        //Parameter:
        //    theMessage - the RTCM message to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void sendRawRTCM_2_3Message(const RTCMMessage& theMessage);

        //Function: setVehicleDynamicsMode
        //    Sets the vehicle dynamics mode.
        //
        //Parameter:
        //    mode - the new mode to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setVehicleDynamicsMode(const InertialTypes::VehicleModeType& mode);

        //Function: getVehicleDynamicsMode
        //    Gets the vehicle dynamics mode.
        //
        //Return:
        //    VehicleModeType - The new mode.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        InertialTypes::VehicleModeType getVehicleDynamicsMode();

        //Function: setEstimationControlFlags
        //    Sets the estimation control flags.
        //
        //Parameter:
        //    mode - the new mode to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setEstimationControlFlags(const uint16& flags);

        //Function: getEstimationControlFlags
        //    Gets the estimation control flags.
        //
        //Return:
        //    uint16 - The new flags.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        uint16 getEstimationControlFlags();

        //Function: setEstimationControlFlags
        //    Sets the estimation control flags.
        //
        //Parameter:
        //    gnssSource - the new mode to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setGNSS_SourceControl(const InertialTypes::GNSS_Source& gnssSource);

        //Function: getEstimationControlFlags
        //    Gets the estimation control flags.
        //
        //Return:
        //    <GNSS_Source> - The new source.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        InertialTypes::GNSS_Source getGNSS_SourceControl();

        //Function: sendExternalGNSSUpdate
        //    sends the external GNSS update command.
        //
        //Parameter:
        //    gnssUpdateData - the data to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void sendExternalGNSSUpdate(const ExternalGNSSUpdateData& gnssUpdateData);

        //Function: setHeadingUpdateControl
        //    Sets the heading update control flags.
        //
        //Parameter:
        //    headingUpdateOptions - the new options to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setHeadingUpdateControl(const HeadingUpdateOptions& headingUpdateOptions);

        //Function: getHeadingUpdateControl
        //    Gets the heading update control flags.
        //
        //Return:
        //    <HeadingUpdateOptions> - The current options.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        HeadingUpdateOptions getHeadingUpdateControl();

        //Function: sendExternalHeadingUpdate
        //    sends the external heading update command.
        //
        //Parameter:
        //    headingData - the new heading.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void sendExternalHeadingUpdate(const HeadingData& headingData);

        //Function: sendExternalHeadingUpdate
        //    sends the external heading update command.
        //
        //Parameter:
        //    headingData - the new heading.
        //    timestamp - the timestamp.  Improves accuracy in situations of high angular rate.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void sendExternalHeadingUpdate(const HeadingData& headingData, const TimeUpdate& timestamp);

        LinearEquation getAnalogToDisplacementCal() const;

        SampleRate getDisplacementOutputDataRate() const;

        //Function: setDeviceTime
        //  Seeds the device time with the current system time. 
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the DisplacementNode.
        void setDeviceTime();

        //API Function: setDeviceTime
        //  Seeds the device time with a specific time.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the DisplacementNode.
        void setDeviceTime(uint64 nanoseconds);

private:
       //Function: SendCommand
       //    Generic send command.
       //
       //Parameters:
       //    The <MipCommand> command.
       //
       //Return:
       //    The <GenericMipCmdResponse> response from the sent command.
       //
       //Exceptions:
       //    - <Error_NotSupported>: The command is not supported by this Node.
       //    - <Error_Communication>: There was no response to the command. The command timed out.
       //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
       //    - <Error_Connection>: A connection error has occurred with the InertialNode.
       GenericMipCmdResponse SendCommand(MipCommand& command);
    };
}