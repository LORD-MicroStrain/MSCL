/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/MicroStrain/MIP/MipNodeInfo.h"
#include "mscl/MicroStrain/MIP/MipChannel.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MipCmdResponse.h"
#include "mscl/MicroStrain/MIP/Packets/MipDataPacket.h"
#include "mscl/Communication/Connection.h"
#include "mscl/MicroStrain/Inertial/PositionOffset.h"
#include "mscl/MicroStrain/Inertial/EulerAngles.h"
#include "mscl/MicroStrain/Inertial/ExposedInertialTypes.h"

namespace mscl
{
    //forward declarations
    class MipNode_Impl;
    class MipNodeFeatures;

    //API Class: InertialNode
    //    A class representing a MicroStrain Inertial Node
    //
    //See Also:
    //    <WirelessNode>
    class InertialNode
    {
    private:
        InertialNode();        //default constructor disabled

    public:
        //API Constructor: InertialNode
        //    Creates an InertialNode object.
        //
        //Parameters:
        //    connection - The Connection object used for communication.
        //
        //Exceptions:
        //    - <Error_Connection>: A problem occurred with the Connection.
        explicit InertialNode(Connection connection);

        virtual ~InertialNode() {}

#ifndef SWIG
        InertialNode(std::shared_ptr<MipNode_Impl> impl); //constructor with direct underlying implementation for this class.
#endif

    private:
        //Variable: m_impl
        //    The <MipNode_Impl> class that contains all the implementation logic for the InertialNode class.
        std::shared_ptr<MipNode_Impl> m_impl;

    public:   
#ifndef SWIG
        //Function: doCommand
        //    Performs a generic Inertial Command, sending the command bytes and waiting for the response.
        //
        //Parameters:
        //    response - A <GenericMipCommand::Response> that will be used to wait and contain all the command/result information.
        //    command - The <ByteStream> containing the bytes to send for the command.
        //    verifySupported - Whether to verify if the command is supported before performing the command (default of true).
        //
        //Returns:
        //    The <GenericMipCmdResponse> that contains the actual data from the response
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_MipCmdFailed>: The command has failed.
        virtual GenericMipCmdResponse doCommand(GenericMipCommand::Response& response, const ByteStream& command, bool verifySupported = true) const;
#endif

        //API Function: deviceName
        //    Static function for creating the universal sensor name that should be used for SensorCloud.
        //
        //Parameters:
        //    serial - The serial number of the inertial node. This should be identical to calling the <serialNumber> function on an <MipNodeInfo> object (see <InertialNode::info>).
        //
        //Returns:
        //    The universal sensor name.
        static std::string deviceName(const std::string& serial);

        //API Function: connection
        //    Gets the <Connection> object that this InertialNode is using.
        //
        //Returns:
        //    The <Connection> object that this InertialNode is using.
        Connection& connection();

        //API Function: features
        //    Gets a reference to the <MipNodeFeatures> for this device.
        //    Note: This will be invalid when the InertialNode is destroyed.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The model is not supported by MSCL.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: Information failed to be loaded for this Node.
        const MipNodeFeatures& features() const;

        //API Function: lastCommunicationTime
        //    Gets the <Timestamp> for the last time MSCL communicated with the InertialNode.
        //
        //Returns:
        //    A <Timestamp> representing the last time MSCL communicated with the Node.
        //
        //Exceptions:
        //  - <Error_NoData>: There is no communication time logged for this device.
        const Timestamp& lastCommunicationTime() const;

        //API Function: lastDeviceState
        //  Gets the last known <DeviceState> for the InertialNode.
        //  This device state is updated by MSCL when data packets are received, as well as when operations are performed, such as setting a Node to idle.
        //
        //Returns:
        //  The last known <DeviceState>.
        DeviceState lastDeviceState() const;

        //API Function: firmwareVersion
        //    Gets the firmware <Version> of the InertialNode.
        //
        //Returns:
        //    The firmware <Version> of the InertialNode.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: Information failed to be loaded for this Node.
        Version firmwareVersion() const;

        //API Function: model
        //    Gets the <InertialModels::NodeModel> of the InertialNode.
        //
        //Returns:
        //    The <InertialModels::NodeModel> of the InertialNode.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: Information failed to be loaded for this Node.
        InertialModels::NodeModel model() const;

        //API Function: modelName
        //    Gets the model name of the InertialNode (ie. "3DM-GX3-45").
        //
        //Returns:
        //    The model name of the InertialNode.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: Information failed to be loaded for this Node.
        std::string modelName() const;

        //API Function: modelNumber
        //    Gets the model number of the InertialNode (ie. "6225-4220").
        //
        //Returns:
        //    The model number of the InertialNode.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: Information failed to be loaded for this Node.
        std::string modelNumber() const;

        //API Function: serialNumber
        //    Gets the serial number of the InertialNode (ie. "6225-01319").
        //
        //Returns:
        //    The serial number of the InertialNode.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: Information failed to be loaded for this Node.
        std::string serialNumber() const;

        //API Function: lotNumber
        //    Gets the lot number of the InertialNode (ie. "I042Y").
        //
        //Returns:
        //    The lot number of the InertialNode.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: Information failed to be loaded for this Node.
        std::string lotNumber() const;

        //API Function: deviceOptions
        //    Gets the device options of the InertialNode (ie. "5g, 300d/s").
        //
        //Returns:
        //    The device options of the InertialNode.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: Information failed to be loaded for this Node.
        std::string deviceOptions() const;
        
        //API Function: getDataPackets
        //    Gets up to the requested amount of data packets that have been collected.
        //
        //Parameters:
        //    timeout - The timeout, in milliseconds, to wait for data if necessary (default of 0).
        //    maxPackets - The maximum number of packets to return. If this is 0 (default), all packets will be returned.
        //
        //Returns:
        //    A vector of <MipDataPacket>s containing all the data packets that are available up to the requested number of packets. 
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        MipDataPackets getDataPackets(uint32 timeout = 0, uint32 maxPackets = 0);

        //API Function: totalPackets
        //    Gets the total number of data packets that are currently in the buffer.
        //
        //Returns:
        //    The total number of data packets that are currently in the buffer.
        uint32 totalPackets();

        //API Function: timeout
        //    Sets the timeout to use when waiting for responses from Inertial commands.
        //
        //Parameters:
        //    timeout - The timeout (in milliseconds) to set for Inertial commands.
        void timeout(uint64 timeout);

        //API Function: timeout
        //    Gets the timeout to use when waiting for responses from Inertial commands.
        //
        //Returns:
        //    The timeout (in milliseconds) used for Inertial commands.
        uint64 timeout() const;

        //API Function: name
        //    Gets the name of the InertialNode. This is the universal sensor name that should be used for uploading to SensorCloud.
        //    This is the same as calling <InertialNode::deviceName>.
        //
        //Returns:
        //    The universal sensor name.
        std::string name();

        //API Function: ping
        //    Pings the Node to check for communication. 
        //    Sends the "Ping" command to the device.
        //
        //Returns:
        //    true if successfully pinged the node, false if failed.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        bool ping();

        //API Function: setToIdle
        //    Suspends streaming (if enabled) or wakes the device from sleep (if sleeping), putting the device in an idle mode.
        //    After this command is used, the <resume> command may be used to put the Node back into the mode it was previously in before setToIdle was called.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setToIdle();

        //API Function: cyclePower
        //  Performs the "Device Reset" Inertial command.
        //  Note: This is essentially the same as unplugging and plugging the device back in.
        //
        //Exceptions:
        //  - <Error_Communication>: There was no response to the command. The command timed out.
        //  - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //  - <Error_Connection>: A connection error has occurred with the InertialNode.
        bool cyclePower();

        //API Function: resume
        //    Places the Node back in the mode it was in before issuing the <setToIdle> command.
        //    If the <setToIdle> command was not issued, then the device is placed in default mode.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void resume();

        //API Function: saveSettingsAsStartup
        //  Saves all of the current settings as the Node's startup settings.
        //  Note: A brief data disturbance may occur when calling this command.
        //
        //Exceptions:
        //  - <Error_Communication>: There was no response to the command. The command timed out.
        //  - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //  - <Error_Connection>: A connection error has occurred with the InertialNode.
        void saveSettingsAsStartup();

        //API Function: loadStartupSettings
        //  Loads the saved startup settings onto the Node as its current settings.
        //  This function is useful if you have powered on the Node, made changes to its settings, and
        //  want to get back to its startup settings.
        //
        //Exceptions:
        //  - <Error_Communication>: There was no response to the command. The command timed out.
        //  - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //  - <Error_Connection>: A connection error has occurred with the InertialNode.
        void loadStartupSettings();

        //API Function: loadFactoryDefaultSettings
        //  Loads the factory default settings onto the Node as its current settings.
        //
        //Exceptions:
        //  - <Error_Communication>: There was no response to the command. The command timed out.
        //  - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //  - <Error_Connection>: A connection error has occurred with the InertialNode.
        void loadFactoryDefaultSettings();

        //API Function: pollData
        //  Polls the device for a message with the specified fields, for the specified data class.
        //  This will cause the device to send a single data packet.
        //
        //Parameters:
        //  dataClass - The <MipTypes::DataClass> to poll the data for.
        //  fields - The <MipTypes::MipChannelFields> to poll. If this is empty, the device will use its stored format.
        //
        //Exceptions:
        //  - <Error_Communication>: There was no response to the command. The command timed out.
        //  - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //  - <Error_NotSupported>: Unsupported Data Class.
        //  - <Error_Connection>: A connection error has occurred with the InertialNode.
        void pollData(MipTypes::DataClass dataClass, const MipTypes::MipChannelFields& fields = MipTypes::MipChannelFields());

        //Function: getConfigCommandBytes
        //    Gets the byte string for the commands to set the node's current settings.
        //
        //Returns:
        //    A <MipCommandSet> containing supported config descriptors and the set command bytes.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        MipCommandSet getConfigCommandBytes();

        //Function: sendCommandBytes
        //    Sends the <MipCommandSet> byte strings. The <MipCommandBytes> responseSuccess is updated to indicate success/failure.
        //    Note: Unsupported commands, as indicated by the <MipCommandBytes> id, will not be sent.
        //    Important: if the UART Baud Rate is changed the connection to the port will be automatically closed and re-opened at the new baud rate.
        //
        //Parameters:
        //    cmds - The <MipCommandSet> of command IDs and bytes. The responseSuccess value of each will be set to true if the sent command does not error.
        void sendCommandBytes(MipCommandSet& cmds);

        //Function: sendCommandBytes
        //    Sends the <MipCommandBytes> byte strings. The <MipCommandBytes> responseSuccess is updated to indicate success/failure.
        //    Note: Unsupported commands, as indicated by the <MipCommandBytes> id, will not be sent.
        //    Important: if the UART Baud Rate is changed the connection to the port will be automatically closed and re-opened at the new baud rate.
        //
        //Parameters:
        //    cmd - The <MipCommandBytes> to send to the device. The responseSuccess value will be set to true if the sent command does not error.
        void sendCommandBytes(MipCommandBytes& cmd);

        //API Function: getDataRateBase
        //    Gets the Data decimation base for the data rate calculations of the specified <InertialType>.
        //
        //Parameters:
        //    type - The <MipTypes::DataClass> to get the Data decimation base for.
        //
        //Returns:
        //    The decimation base for the data rate calculations.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command or <MipTypes::DataClass> is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        uint16 getDataRateBase(MipTypes::DataClass dataClass);

        //API Function: getActiveChannelFields
        //    Gets the current active channel fields for the specified <MipTypes::DataClass>.
        //
        //Parameters:
        //    dataClass - The <MipTypes::DataClass> to get the current message format for.
        //
        //Returns:
        //    An <MipChannels> object containing the channels that make up the data message format for the specified <MipTypes::DataClass>.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command or <MipTypes::DataClass> is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        MipChannels getActiveChannelFields(MipTypes::DataClass dataClass);

        //API Function: setActiveChannelFields
        //    Sets the current active channel fields for the specified <MipTypes::DataClass>.
        //    Note that this function does not add to the existing message format (active channels), but overwrites it entirely.
        //
        //Parameters:
        //    dataClass - The <MipTypes::DataClass> to set the message format for.
        //    channels - The <MipChannels> object containing the channels to set the message format to. Passing an empty <MipChannels> object will effectively disable all channels.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command or <MipTypes::DataClass> is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        //    - <Error>: An <MipChannel> in the channels parameter is not part of the specified <MipTypes::DataClass>'s descriptor set.
        void setActiveChannelFields(MipTypes::DataClass dataClass, const MipChannels& channels);

        //Function: saveActiveChannelFields
        //    Saves the current message format of the specified <MipTypes::DataClass>'s data packet.
        //
        //Parameters:
        //    dataClass - The <MipTypes::DataClass> to set the message format for.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command or <MipTypes::DataClass> is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        //    - <Error>: An <MipChannel> in the channels parameter is not part of the specified <MipTypes::DataClass>'s descriptor set.
        void saveActiveChannelFields(MipTypes::DataClass dataClass);

        //API Function: getCommunicationMode
        //    Gets the current communication mode that the node is in.
        //
        //Returns:
        //    The communication mode the node is in. This is an advanced command, and therefore the communication modes for your device should be researched to determine what each communication mode is.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command or <MipTypes::DataClass> is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        uint8 getCommunicationMode();

        //API Function: setCommunicationMode
        //    Sets the communication mode for the node. 
        //    Note: The node info will be reset when doing this and therefore will require being fetched again the next time it is requested.
        //
        //Parameters:
        //    communicationMode - The communication mode to set. This is an advanced command, and therefore the communication modes for your device should be researched to determine what each communication mode is.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setCommunicationMode(uint8 communicationMode);

        //API Function: isDataStreamEnabled
        //    Checks whether continuous data streaming is enabled for the specified data class.
        //
        //Parameters:
        //    dataClass - The <MipTypes::DataClass> to enable/disable streaming for.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command or <MipTypes::DataClass> is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        bool isDataStreamEnabled(MipTypes::DataClass dataClass);

        //API Function: enableDataStream
        //    Enables or disables continuous data streaming for the node.
        //
        //Parameters:
        //    dataClass - The <MipTypes::DataClass> to enable/disable streaming for.
        //    enable - Whether to enable (true) or disable (false) continuous streaming (Default of true).
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command or <MipTypes::DataClass> is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void enableDataStream(MipTypes::DataClass dataClass, bool enable = true);

        //API Function: resetFilter
        //    Resets the filter to the initialize state.
        //    Note: If the auto-initialization feature is disabled, the initial attitude or heading must
        //          be set in order to enter the run state after a reset.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void resetFilter();

        //API Function: getAutoInitialization
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

        //API Function: setAutoInitialization
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

        //API Function: getAltitudeAid
        //    Gets the state of the altitude aid upon device startup.
        //
        //Returns:
        //    true if altitude aiding is enabled, false if it is disabled.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        bool getAltitudeAid();

        //API Function: setAltitudeAid
        //    Sets the state of the altitude aid upon device startup.
        //
        //Parameters:
        //    enable - Whether to enable (true) or disable(false) altitude aiding.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setAltitudeAid(bool enable);

        //API Function: getPitchRollAid
        //    Gets the state of the pitch/roll aid upon device startup.
        //
        //Returns:
        //    true if pitch/roll aiding is enabled, false if it is disabled.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        bool getPitchRollAid();

        //API Function: setPitchRollAid
        //    Sets the state of the pitch/roll aid upon device startup.
        //
        //Parameters:
        //    enable - Whether to enable (true) or disable(false) pitch/roll aiding.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setPitchRollAid(bool enable);

        //API Function: setVelocityZUPT
        //    Sets the state of the velocity ZUPT control.
        //
        //Parameters:
        //    ZUPTSettings - the ZUPTSettingsData object containing whether ZUPT is enabled and the threshold.
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setVelocityZUPT(const ZUPTSettingsData& ZUPTSettings);

        //API Function: getVelocityZUPT
        //    Gets the state of the velocity ZUPT control.
        //
        //Returns:
        //    the ZUPTSettingsData object containing whether ZUPT is enabled and the threshold.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        ZUPTSettingsData getVelocityZUPT();

        //API Function: setAngularRateZUPT
        //    Sets the state of the angular rate ZUPT control.
        //
        //Parameters:
        //    ZUPTSettings - the ZUPTSettingsData object containing whether ZUPT is enabled and the threshold.
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setAngularRateZUPT(const ZUPTSettingsData& ZUPTSettings);

        //API Function: getAngularRateZUPT
        //    Gets the state of the angular rate ZUPT control.
        //
        //Returns:
        //    the ZUPTSettingsData object containing whether ZUPT is enabled and the threshold.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        ZUPTSettingsData getAngularRateZUPT();

        //API Function: setInitialAttitude
        //    Sets the initial attitude.
        //    Note: This command can only be issued in the "INIT" state and should be used with a
        //          good estimate of the vehicle attitude.
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

        //API Function: setInitialHeading
        //    Sets the initial heading.
        //    Note: This command can only be issued in the "INIT" state and should be used with a
        //          good estimate of heading. The device will use this value in conjunction with the
        //          output of the accelerometers to determine the initial attitude estimate.
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

        //API Function: getInitialFilterConfiguration
        //    Gets the initial filter configuration values.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        FilterInitializationValues getInitialFilterConfiguration();

        //API Function: setInitialFilterConfiguration
        //    Sets the initial filter configuration values.
        //    Note: Changes from this command will only be applied if the filter is in the Initialization state (not Running) or on filter reset.
        //
        //Parameters:
        //  filterConfig - The <FilterInitializationValues> to set.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setInitialFilterConfiguration(FilterInitializationValues filterConfig);

        //API Function: getSensorToVehicleTransformation
        //    Gets the sensor to vehicle frame transformation matrix using roll, pitch, and yaw Euler angles.
        //    These angles define the rotation from the sensor body from to the fixed vehicle frame.
        //
        //Returns:
        //    The <EulerAngles> object containing the roll, pitch, and yaw result (in radians).
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        EulerAngles getSensorToVehicleTransformation();

        //API Function: setSensorToVehicleTransformation
        //    Sets the sensor to vehicle frame transformation matrix using roll, pitch, and yaw Euler angles (in radians).
        //    These angles define the rotation from the sensor body from to the fixed vehicle frame.
        //
        //Parameters:
        //    angles - The <EulerAngles> object containing the roll, pitch, and yaw (in radians) to set.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setSensorToVehicleTransformation(const EulerAngles& angles);

        //API Function: getSensorToVehicleOffset
        //    Gets the sensor to vehicle frame offset, expressed in the sensor frame.
        //
        //Returns:
        //    The <PositionOffset> object containing the x, y, and z position (in meters) result.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        PositionOffset getSensorToVehicleOffset();

        //API Function: setSensorToVehicleOffset
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

        //API Function: getAntennaOffset
        //    Gets the antenna offset, expressed in the sensor frame.
        //
        //Returns:
        //    The <PositionOffset> object containing the x, y, and z position (in meters) result.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        PositionOffset getAntennaOffset();

        //API Function: setAntennaOffset
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

        //API Function: getGNSSAssistedFixControl
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

        //API Function: setGNSSAssistedFixControl
        //    Sets the GNSS Assisted Fix Control.
        //
        //Parameters:
        //    enableAssistedFix - bool to either enable or disable assisted fix control for GNSS (true == enable).
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
		void setGNSSAssistedFixControl(bool enableAssistedFix);

        //API Function: getGNSSAssistTimeUpdate
        //    Gets the GNSS Assisted Time Update.
        //
        //Returns:
        //    The GNSS Assist <TimeUpdate>.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        TimeUpdate getGNSSAssistTimeUpdate();

        //API Function: setGNSSAssistTimeUpdate
        //    Sets the GNSS Assist Time Update.
        //
        //Parameters:
        //    timeUpdate - The <TimeUpdate> object containing the new time to set.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setGNSSAssistTimeUpdate(const TimeUpdate& timeUpdate);

        //API Function: getGPSTimeUpdate
        //    Gets the GPS time update.
        //
        //Parameters:
        //    timeFrame - The <MipTypes::TimeFrame> object specifying what current time value to get, either weeks or seconds.
        //
        //Returns:
        //    The current time for the specified value type.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        mscl::uint32 getGPSTimeUpdate(MipTypes::TimeFrame timeFrame);

        //API Function: setGPSTimeUpdate
        //    Sets the GPS Time Update.
        //
        //Parameters:
        //    offset - The <TimeFrame> object specifying what current time value to set, either weeks or seconds.
        //    time - the current time.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setGPSTimeUpdate(MipTypes::TimeFrame, mscl::uint32 timeData);

        //API Function: setConstellationSettings
        //    Sets the GNSS Constellation Settings.
        //
        //Parameters:
        //    dataToUse - The <ConstellationSettingsData> object containing the data to set.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void setConstellationSettings(const ConstellationSettingsData& dataToUse);

        //API Function: constellationSettings
        //    Gets the GNSS Constellation Settings.
        //
        //Return:
        //    The <ConstellationSettingsData> object containing the data.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        ConstellationSettingsData getConstellationSettings();

        //API Function: setSBASSettings
        //    Sets the GNSS SBAS Settings.
        //
        //Parameters:
        //    dataToUse - The <SBASSettingsData> object containing the data to set.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void setSBASSettings(const SBASSettingsData& dataToUse);

        //API Function: getSBASSettings
        //    Gets the GNSS SBAS Settings.
        //
        //Return:
        //    The <SBASSettingsData> object containing the data.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        SBASSettingsData getSBASSettings();

        //API Function: setAccelerometerBias
        //    Sets the Accelerometer Bias.
        //
        //Parameters:
        //    biasVector - The <GeometricVector> object containing the vector to set.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void setAccelerometerBias(const GeometricVector& biasVector);

        //API Function: getAccelerometerBias
        //    Gets the Accelerometer Bias.
        //
        //Returns:
        //    The <GeometricVector> object containing the vector.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        GeometricVector getAccelerometerBias();

        //API Function: setGyroBias
        //    Sets the Gyro Bias.
        //
        //Parameters:
        //    biasVector - The <GeometricVector> object containing the vector to set.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void setGyroBias(const GeometricVector& biasVector);

        //API Function: getGyroBias
        //    Gets the Gyro Bias vector.
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

        //API Function: captureGyroBias
        //    Runs the Gyro Bias capture routine on the inertial device.
        //
        //Parameters:
        //    The <uint16> samplingTime.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        GeometricVector captureGyroBias(const uint16& samplingTime);

        //Function: findMagnetometerCaptureAutoCalibration
        //    Runs the Magnetometer auto calibration routine on the inertial device.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void findMagnetometerCaptureAutoCalibration();

        //Function: saveMagnetometerCaptureAutoCalibration
        //    Runs the Magnetometer auto calibration routine and saves result as startup settings.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void saveMagnetometerCaptureAutoCalibration();

        //API Function: setMagnetometerSoftIronMatrix
        //    Sets the Magnetometer Soft Iron matrix.
        //
        //Parameters:
        //    matrix - The <Matrix_3x3> object containing the matrix to set.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void setMagnetometerSoftIronMatrix(const Matrix_3x3& matrix);

        //API Function: getMagnetometerSoftIronMatrix
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

        //API Function: setMagnetometerHardIronOffset
        //    Sets the magnetometer hard iron offset vector.
        //
        //Parameters:
        //    offsetVector - The <GeometricVector> object containing the vector to set.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void setMagnetometerHardIronOffset(const GeometricVector& offsetVector);

        //API Function: getMagnetometerHardIronOffset
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

        //API Function: setConingAndScullingEnable
        //    Enables/disables coning and sculling.
        //
        //Parameters:
        //    enable - whether to enable coning and sculling.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void setConingAndScullingEnable(bool enable);

        //API Function: getConingAndScullingEnable
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

        //API Function: setUARTBaudRate
        //    Sets the baud rate.  The device can be unresponsive for as much as 250 ms following this command.
        //    Important: The connection to the port will be automatically closed and re-opened at the new baud rate unless resetConnection parameter is false.
        //
        //Parameters:
        //    baudRate - The new baud rate.
        //    resetConnection - Specifies whether the connection to the port should be automatically closed and re-opened at the new baud rate.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void setUARTBaudRate(uint32 baudRate, bool resetConnection = true);

        //API Function: getUARTBaudRate
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

        //API Function: setAdvancedLowPassFilterSettings
        //    Sets the advanced low-pass filter settings.
        //
        //Parameters:
        //    data - the new settings to set.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void setAdvancedLowPassFilterSettings(const AdvancedLowPassFilterConfig& data);

        //API Function: getAdvancedLowPassFilterSettings
        //    Gets the current advanced low-pass filter settings for the given data descriptors
        //
        //Parameter:
        //    dataDescriptors - the <MipType::ChannelField> data descriptors for which to return the current advanced low-pass filter settings.
        //
        //Return:
        //    <AdvancedLowPassFilterData> settings.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        AdvancedLowPassFilterConfig getAdvancedLowPassFilterSettings(const MipTypes::MipChannelFields& dataDescriptors);
        
        //API Function: setComplementaryFilterSettings
        //    Sets the complementary filter settings.
        //
        //Parameter:
        //    data - the new settings to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void setComplementaryFilterSettings(const ComplementaryFilterData& data);

        //API Function: getComplementaryFilterSettings
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

        //API Function: getBasicDeviceStatus
        //    Gets the basic device status.
        //
        //Return:
        //    DeviceStatusData - The new settings.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        DeviceStatusData getBasicDeviceStatus();

        //API Function: getDiagnosticDeviceStatus
        //    Gets the diagnostic device status.
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
        
        //API Function: sendRawRTCM_2_3Message
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

        //API Function: setVehicleDynamicsMode
        //    Sets the vehicle dynamics mode.
        //
        //Parameter:
        //    mode - the new mode to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void setVehicleDynamicsMode(const InertialTypes::VehicleModeType& mode);

        //API Function: getVehicleDynamicsMode
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

        //API Function: setEstimationControlFlags
        //    Sets the estimation control flags.
        //
        //Parameter:
        //    flags - the new flags to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void setEstimationControlFlags(const EstimationControlOptions& flags);

        //API Function: getEstimationControlFlags
        //    Gets the estimation control flags.
        //
        //Return:
        //    EstimationControlOptions - The current flags.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        EstimationControlOptions getEstimationControlFlags();

        //Function: setInclinationSource
        //    Sets the source for the inclination geographic source command.
        //
        //Parameter:
        //    options - the GeographicSourceOptions to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setInclinationSource(const GeographicSourceOptions& options);

        //Function: getInclinationSource
        //    Gets the source for the inclination geographic source command.
        //
        //Return:
        //    GeographicSourceOptions - the current GeographicSourceOptions for the inclination.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        GeographicSourceOptions getInclinationSource();

        //Function: setDeclinationSource
        //    Sets the source for the declination geographic source command.
        //
        //Parameter:
        //    options - the GeographicSourceOptions to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setDeclinationSource(const GeographicSourceOptions& options);

        //Function: getDeclinationSource
        //    Gets the source for the declination geographic source command.
        //
        //Return:
        //    GeographicSourceOptions - the current GeographicSourceOptions for the declination.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        GeographicSourceOptions getDeclinationSource();

        //Function: setMagneticFieldMagnitudeSource
        //    Sets the source for the magnetic field magnitude geographic source command.
        //
        //Parameter:
        //    options - the GeographicSourceOptions to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setMagneticFieldMagnitudeSource(const GeographicSourceOptions& options);

        //Function: getMagneticFieldMagnitudeSource
        //    Gets the source for the field magnitude geographic source command.
        //
        //Return:
        //    GeographicSourceOptions - the current GeographicSourceOptions for the magnetic field magnitude.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        GeographicSourceOptions getMagneticFieldMagnitudeSource();

        //API Function: setEstimationControlFlags
        //    Sets the estimation control flags.
        //
        //Parameter:
        //    gnssSource - the new mode to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void setGNSS_SourceControl(const InertialTypes::GNSS_Source& gnssSource);

        //API Function: getEstimationControlFlags
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

        //API Function: sendExternalGNSSUpdate
        //    sends the external GNSS update command.
        //
        //Parameter:
        //    gnssUpdateData - the data to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void sendExternalGNSSUpdate(const ExternalGNSSUpdateData& gnssUpdateData);

        //API Function: setHeadingUpdateControl
        //    Sets the heading update control flags.
        //
        //Parameter:
        //    headingUpdateOptions - the new options to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void setHeadingUpdateControl(const HeadingUpdateOptions& headingUpdateOptions);

        //API Function: tareOrientation
        //     uses device orientation relative to the NED frame as the sensor to vehicle transformation.
        //
        //Parameters:
        //    axisValue - the <TareAxisValues> object indicating which axes to tare.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void tareOrientation(const TareAxisValues& axisValue);

        //API Function: getHeadingUpdateControl
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

        //API Function: setGravityErrorAdaptiveMeasurement
        //    Sets the gravity magnitude error adaptive measurement settings.
        //
        //Parameter:
        //    data - the adaptive measurement settings to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setGravityErrorAdaptiveMeasurement(const AdaptiveMeasurementData& data);

        //API Function: getGravityErrorAdaptiveMeasurement
        //    Gets the gravity magnitude error adaptive measurement settings.
        //
        //Return:
        //    <AdaptiveMeasurementData> - The current adaptive measurement settings.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        AdaptiveMeasurementData getGravityErrorAdaptiveMeasurement();

        //API Function: setMagnetometerErrorAdaptiveMeasurement
        //    Sets the magnetometer magnitude error adaptive measurement settings.
        //
        //Parameter:
        //    data - the adaptive measurement settings to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setMagnetometerErrorAdaptiveMeasurement(const AdaptiveMeasurementData& data);

        //API Function: getMagnetometerErrorAdaptiveMeasurement
        //    Gets the magnetometer magnitude error adaptive measurement settings.
        //
        //Return:
        //    <AdaptiveMeasurementData> - The current adaptive measurement settings.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        AdaptiveMeasurementData getMagnetometerErrorAdaptiveMeasurement();

        //API Function: setMagDipAngleErrorAdaptiveMeasurement
        //    Sets the magnetometer dip angle error adaptive measurement settings.
        //
        //Parameter:
        //    data - the adaptive measurement settings to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setMagDipAngleErrorAdaptiveMeasurement(const AdaptiveMeasurementData& data);

        //API Function: getMagDipAngleErrorAdaptiveMeasurement
        //    Gets the magnetometer dip angle error adaptive measurement settings.
        //
        //Return:
        //    <AdaptiveMeasurementData> - The current adaptive measurement settings.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        AdaptiveMeasurementData getMagDipAngleErrorAdaptiveMeasurement();

        //API Function: setMagNoiseStandardDeviation
        //    Sets the magnetometer noise standard deviation.
        //
        //Parameter:
        //    data - the <GeometricVector> to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setMagNoiseStandardDeviation(const GeometricVector& data);

        //API Function: getMagNoiseStandardDeviation
        //    Gets the magnetometer noise standard deviation.
        //
        //Return:
        //    <GeometricVector> - The current magnetometer noise standard deviation.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        GeometricVector getMagNoiseStandardDeviation();

        //API Function: setGravNoiseStandardDeviation
        //    Sets the gravity noise standard deviation.
        //
        //Parameter:
        //    data - the <GeometricVector> to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setGravNoiseStandardDeviation(const GeometricVector& data);

        //API Function: getGravNoiseStandardDeviation
        //    Gets the gravity noise standard deviation.
        //
        //Return:
        //    <GeometricVector> - The current gravity noise standard deviation.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        GeometricVector getGravNoiseStandardDeviation();

        //API Function: setAccelNoiseStandardDeviation
        //    Sets the accelerometer noise standard deviation.
        //
        //Parameter:
        //    data - the <GeometricVector> to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setAccelNoiseStandardDeviation(const GeometricVector& data);

        //API Function: getAccelNoiseStandardDeviation
        //    Gets the accelerometer noise standard deviation.
        //
        //Return:
        //    <GeometricVector> - The current accelerometer noise standard deviation.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        GeometricVector getAccelNoiseStandardDeviation();

        //API Function: setGyroNoiseStandardDeviation
        //    Sets the gyroscope noise standard deviation.
        //
        //Parameter:
        //    data - the <GeometricVector> to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setGyroNoiseStandardDeviation(const GeometricVector& data);

        //API Function: getGyroNoiseStandardDeviation
        //    Gets the gyroscope noise standard deviation.
        //
        //Return:
        //    <GeometricVector> - The current gyroscope noise standard deviation.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        GeometricVector getGyroNoiseStandardDeviation();

        //API Function: setPressureAltNoiseStandardDeviation
        //    Sets the pressure altitude noise standard deviation.
        //
        //Parameter:
        //    data - the float to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setPressureAltNoiseStandardDeviation(const float& data);

        //API Function: getPressureAltNoiseStandardDeviation
        //    Gets the pressure altitude noise standard deviation.
        //
        //Return:
        //    float - The current pressure altitude noise standard deviation.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        float getPressureAltNoiseStandardDeviation();

        //API Function: setHardIronOffsetProcessNoise
        //    Sets the hard iron offset process noise.
        //
        //Parameter:
        //    data - the <GeometricVector> to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setHardIronOffsetProcessNoise(const GeometricVector& data);

        //API Function: getHardIronOffsetProcessNoise
        //    Gets the hard iron offset process noise.
        //
        //Return:
        //    <GeometricVector> - The current hard iron offset process noise.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        GeometricVector getHardIronOffsetProcessNoise();

        //API Function: setAccelBiasModelParams
        //    Sets the accelerometer bias model parameters.
        //
        //Parameter:
        //    data - the collection of <GeometricVector> to send - contains two data points: bias beta values, and bias noise values.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setAccelBiasModelParams(const GeometricVectors& data);

        //API Function: getAccelBiasModelParams
        //    Gets the accelerometer bias model parameters.
        //
        //Return:
        //    <GeometricVector> - The current accelerometer bias model parameters - returns two data points: bias beta values, and bias noise values.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        GeometricVectors getAccelBiasModelParams();

        //API Function: setGyroBiasModelParams
        //    Sets the gyroscope bias model parameters.
        //
        //Parameter:
        //    data - the collection of <GeometricVector> to send - contains two data points: bias beta values, and bias noise values.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setGyroBiasModelParams(const GeometricVectors& data);

        //API Function: getGyroBiasModelParams
        //    Gets the gyroscope bias model parameters.
        //
        //Return:
        //    <GeometricVector> - The current gyroscope bias model parameters - returns two data points: bias beta values, and bias noise values.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        GeometricVectors getGyroBiasModelParams();

        //API Function: setSoftIronMatrixProcessNoise
        //    Sets the soft iron matrix process noise.
        //
        //Parameter:
        //    data - the collection of <Matrix_3x3> to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setSoftIronMatrixProcessNoise(const Matrix_3x3& data);

        //API Function: getSoftIronMatrixProcessNoise
        //    Gets the soft iron matrix process noise.
        //
        //Return:
        //    <Matrix_3x3> - The current soft iron matrix process noise.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        Matrix_3x3 getSoftIronMatrixProcessNoise();

        //API Function: setFixedReferencePosition
        //    Sets the <FixedReferencePositionData> data for the specified command.
        //
        //Parameter:
        //    data - the <FixedReferencePositionData> data to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setFixedReferencePosition(const FixedReferencePositionData& data);

        //API Function: FixedReferencePositionData
        //    Gets the <FixedReferencePositionData> data for the specified command.
        //
        //Return:
        //    <FixedReferencePositionData> - the current fixed reference position settings.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        FixedReferencePositionData getFixedReferencePosition();

        //API Function: setGPSDynamicsMode
        //    Sets the <GPSDynamicsMode>.
        //
        //Parameter:
        //    data - the <GPSDynamicsMode> data to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setGPSDynamicsMode(const InertialTypes::GPSDynamicsMode& data);

        //API Function: getGPSDynamicsMode
        //    Gets the <GPSDynamicsMode> data for this device.
        //
        //Return:
        //    <GPSDynamicsMode> - the current GPS dynamics mode setting.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        InertialTypes::GPSDynamicsMode getGPSDynamicsMode() const;

        //API Function: setDevicePowerState
        //    Sets the <PowerState> for the specified device.
        //
        //Parameter:
        //    device - the <DeviceSelector> for which to set the power state.
        //    data - the <PowerState> to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setDevicePowerState(const InertialTypes::DeviceSelector& device, const InertialTypes::PowerState& data);

        //API Function: getDevicePowerState
        //    Gets the <PowerState> for the specified device.
        //
        //Parameter:
        //    device - the <DeviceSelector> for which to get the power state.
        //
        //Return:
        //    <PowerState> - the current power state of the specified device.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        InertialTypes::PowerState getDevicePowerState(const InertialTypes::DeviceSelector& device) const;

        //API Function: setDeviceStreamFormat
        //    Sets the <StreamFormat> for the specified device.
        //
        //Parameter:
        //    device - the <DeviceSelector> for which to set the data stream format.
        //    data - the <StreamFormat> to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setDeviceStreamFormat(const InertialTypes::DeviceSelector& device, const InertialTypes::StreamFormat& data);

        //API Function: getDeviceStreamFormat
        //    Gets the <StreamFormat> for the specified device.
        //
        //Parameter:
        //    device - the <DeviceSelector> for which to get the data stream format.
        //
        //Return:
        //    <StreamFormat> - the current data stream format of the specified device.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        InertialTypes::StreamFormat getDeviceStreamFormat(const InertialTypes::DeviceSelector& device) const;

        //API Function: setSignalConditioningSettings
        //    Sets the signal conditioning settings for the node.
        //
        //Parameter:
        //    data - the signal conditioning settings to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setSignalConditioningSettings(const SignalConditioningValues& data);

        //API Function: getSignalConditioningSettings
        //    Gets the signal conditioning settings for the node.
        //
        //Return:
        //    <SignalConditioningValues> - The current signal conditioning settings.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        SignalConditioningValues getSignalConditioningSettings() const;

        //API Function: setEnableDisableMeasurements
        //    Enables/disables estimation filter measurement options for the node.
        //
        //Parameter:
        //    data - the measurement options to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setEnableDisableMeasurements(const EnableDisableMeasurements& data);

        //API Function: getEnableDisableMeasurements
        //    Gets the currently enabled estimation filter measurement options for the node.
        //
        //Return:
        //    <EnableDisableMeasurements> - The currently enabled measurement options.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        EnableDisableMeasurements getEnableDisableMeasurements() const;

        //API Function: setGravityNoiseMinimum
        //    Sets the gravity noise minimum for the device.
        //
        //Parameter:
        //    data - the gravity noise minimum to set
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setGravityNoiseMinimum(const GeometricVector& data);

        //API Function: getGravityNoiseMinimum
        //    Gets the current gravity noise minimum for the device.
        //
        //Return:
        //    <GeometricVector> - The current gravity noise minimum.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        GeometricVector getGravityNoiseMinimum() const;

        //API Function: sendExternalHeadingUpdate
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

        //API Function: sendExternalHeadingUpdate
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

        //API Function: aidingMeasurementEnabled
        //    sends the Aiding Measurement Enable command (0x0D, 0x50) to check whether the specified aiding source is currently enabled.
        //
        //Parameter:
        //    aidingSource - the <AidingMeasurementSource> to check.
        //
        //Return:
        //    bool - The current state of the specified aiding measurement source - true: enabled, false: disabled.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        bool aidingMeasurementEnabled(InertialTypes::AidingMeasurementSource aidingSource) const;

        //API Function: enableDisableAidingMeasurement
        //    sends the Aiding Measurement Enable command (0x0D, 0x50) to enable/disable the specified aiding source.
        //
        //Parameter:
        //    aidingSource - the <AidingMeasurementSource> to enable/disable.
        //    enable - true: enable, false: disable
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void enableDisableAidingMeasurement(InertialTypes::AidingMeasurementSource aidingSource, bool enable);

        //API Function: getKinematicConstraints
        //    sends the Kinematic Constraint command (0x0D, 0x51) to get the currently configured acceleration, velocity, and angular rate constraint options.
        //
        //Return:
        //    <KinematicConstraints> - The current kinematic constraint options set on the device.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        KinematicConstraints getKinematicConstraints() const;

        //API Function: setKinematicConstraints
        //    sends the Kinematic Constraint command (0x0D, 0x51) to set the acceleration, velocity, and angular rate constraints to the specified options.
        //
        //Parameter:
        //    constraintOptions - the <KinematicConstraints> to set.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setKinematicConstraints(KinematicConstraints constraintOptions);

        //API Function: getAdaptiveFilterOptions
        //    sends the Adaptive Filter Options command (0x0D, 0x53) to get the currently configured auto-adaptive filtering options.
        //
        //Return:
        //    <AutoAdaptiveFilterOptions> - The current auto-adaptive filter options set on the device.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        AutoAdaptiveFilterOptions getAdaptiveFilterOptions() const;

        //API Function: setAdaptiveFilterOptions
        //    sends the Adaptive Filter Options command (0x0D, 0x53) to set the auto-adaptive filtering options to the specified values.
        //
        //Parameter:
        //    options - the <AutoAdaptiveFilterOptions> to set.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setAdaptiveFilterOptions(AutoAdaptiveFilterOptions options);

        //API Function: getMultiAntennaOffset
        //    sends the Multi Antenna Offset command (0x0D, 0x54) to get the currently configured antenna offset for the specified receiver ID.
        //
        //Parameter:
        //    receiverId - the receiver ID to return the offset of.
        //
        //Return:
        //    <PositionOffset> - The currently configured antenna offset of the specified receiver.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        PositionOffset getMultiAntennaOffset(uint8 receiverId) const;

        //API Function: setMultiAntennaOffset
        //    sends the Aiding Measurement Enable command (0x0D, 0x50) to set the position offset of the specified receiver ID.
        //
        //Parameter:
        //    receiverId - the receiver ID.
        //    offset - the <PositionOffset> of the specified receiver.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setMultiAntennaOffset(uint8 receiverId, PositionOffset offset);
    };
    
}
