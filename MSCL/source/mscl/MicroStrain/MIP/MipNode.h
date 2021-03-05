/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/MicroStrain/MIP/MipNodeInfo.h"
#include "mscl/MicroStrain/MIP/MipChannel.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/Inertial/ExposedInertialTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MipCmdResponse.h"
#include "mscl/MicroStrain/MIP/Packets/MipDataPacket.h"
#include "mscl/MicroStrain/MIP/MipModels.h"
#include "mscl/Communication/Connection.h"

namespace mscl
{
    //forward declarations
    class MipNode_Impl;
    class MipNodeFeatures;

    //API Class: MipNode
    //    Abstract base class for Inertial or RTK (MIP) devices
    class MipNode
    {
    protected:
        MipNode() {};  //default constructor disabled
        virtual ~MipNode() {}

        MipNode(Connection connection);

#ifndef SWIG
        MipNode(std::shared_ptr<MipNode_Impl> impl);
#endif

    protected:
        //Variable: m_impl
        //    The <MipNode_Impl> class that contains all the implementation logic for the MipNode class.
        std::shared_ptr<MipNode_Impl> m_impl;

    public:

#ifndef SWIG
        //Function: doCommand
        //  Note: This is an ADVANCED COMMAND. Most users will not need to use this.
        //  Performs a generic Mip Command, sending the command bytes and waiting for the response.
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

        //API Function: doCommand
        //  Note: This is an ADVANCED COMMAND. Most users will not need to use this.
        //  Allows sending custom data as a MIP packet to the device, and receiving custom data as a response.
        //
        //Parameters:
        //  descriptorSet - The MIP descriptor set byte.
        //  cmdDescriptor - The MIP command field descriptor byte.
        //  fieldData - The MIP field data to send in the command (pass an empty <Bytes> container if none).
        //  ackNackResponse - Whether or not a MIP ack/nack response field is expected.
        //  dataResponse - Whether or not a MIP data response field is expected.
        //  responseDataDescriptor - The MIP response data field descriptor byte (only required if dataResponse flag is true)
        //
        //Returns:
        //  The response field <Bytes> from a successful response (empty if no dataResponse).
        //
        //Exceptions:
        //  - <Error_Communication>: There was no response to the command. The command timed out.
        //  - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //  - <Error_Connection>: There was an error with the connection.
        virtual Bytes doCommand(uint8 descriptorSet, uint8 cmdDescriptor, const Bytes& fieldData, bool ackNackResponse, bool dataResponse, uint8 responseDataDescriptor = 0) const;

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

        //API Function: deviceName
        //    Static function for creating the universal sensor name that should be used for SensorCloud.
        //
        //Parameters:
        //    serial - The serial number of the node. This should be identical to calling the <serialNumber> function on an <MipNodeInfo> object (see <MipNode::info>).
        //
        //Returns:
        //    The universal sensor name.
        static std::string deviceName(const std::string& serial);

        //API Function: connection
        //    Gets the <Connection> object that this MipNode is using.
        //
        //Returns:
        //    The <Connection> object that this MipNode is using.
        Connection& connection();

        //API Function: features
        //    Gets a reference to the <MipNodeFeatures> for this device.
        //    Note: This will be invalid when the MipNode is destroyed.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The model is not supported by MSCL.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: Information failed to be loaded for this Node.
        const MipNodeFeatures& features() const;

        //API Function: clearDeviceInfo
        //    Clears cached device info (ie fw version, model number, receiver info, etc.), forcing it to be re-read from the device the next time it is used.
        void clearDeviceInfo();

        //API Function: lastCommunicationTime
        //    Gets the <Timestamp> for the last time MSCL communicated with the MipNode.
        //
        //Returns:
        //    A <Timestamp> representing the last time MSCL communicated with the Node.
        //
        //Exceptions:
        //  - <Error_NoData>: There is no communication time logged for this device.
        const Timestamp& lastCommunicationTime() const;

        //API Function: lastDeviceState
        //  Gets the last known <DeviceState> for the MipNode.
        //  This device state is updated by MSCL when data packets are received, as well as when operations are performed, such as setting a Node to idle.
        //
        //Returns:
        //  The last known <DeviceState>.
        DeviceState lastDeviceState() const;

        //API Function: firmwareVersion
        //    Gets the firmware <Version> of the MipNode.
        //
        //Returns:
        //    The firmware <Version> of the MipNode.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: Information failed to be loaded for this Node.
        Version firmwareVersion() const;

        //API Function: model
        //    Gets the <MipModels::NodeModel> of the MipNode.
        //
        //Returns:
        //    The <MipModels::NodeModel> of the MipNode.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: Information failed to be loaded for this Node.
        MipModels::NodeModel model() const;

        //API Function: modelName
        //    Gets the model name of the MipNode (ie. "3DM-GX3-45").
        //
        //Returns:
        //    The model name of the MipNode.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: Information failed to be loaded for this Node.
        std::string modelName() const;

        //API Function: modelNumber
        //    Gets the model number of the MipNode (ie. "6225-4220").
        //
        //Returns:
        //    The model number of the MipNode.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: Information failed to be loaded for this Node.
        std::string modelNumber() const;

        //API Function: serialNumber
        //    Gets the serial number of the MipNode (ie. "6225-01319").
        //
        //Returns:
        //    The serial number of the MipNode.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: Information failed to be loaded for this Node.
        std::string serialNumber() const;

        //API Function: lotNumber
        //    Gets the lot number of the MipNode (ie. "I042Y").
        //
        //Returns:
        //    The lot number of the MipNode.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: Information failed to be loaded for this Node.
        std::string lotNumber() const;

        //API Function: deviceOptions
        //    Gets the device options of the MipNode (ie. "5g, 300d/s").
        //
        //Returns:
        //    The device options of the MipNode.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: Information failed to be loaded for this Node.
        std::string deviceOptions() const;

        //API Function: timeout
        //    Sets the timeout to use when waiting for responses from commands.
        //
        //Parameters:
        //    timeout - The timeout (in milliseconds) to set for commands.
        void timeout(uint64 timeout);

        //API Function: timeout
        //    Gets the timeout to use when waiting for responses from commands.
        //
        //Returns:
        //    The timeout (in milliseconds) used for commands.
        uint64 timeout() const;

        //API Function: name
        //    Gets the name of the MipNode. This is the universal sensor name that should be used for uploading to SensorCloud.
        //    This is the same as calling <MipNode::deviceName>.
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
        //    - <Error_Connection>: A connection error has occurred with the MipNode.
        bool ping();

        //API Function: setToIdle
        //    Suspends streaming (if enabled) or wakes the device from sleep (if sleeping), putting the device in an idle mode.
        //    After this command is used, the <resume> command may be used to put the Node back into the mode it was previously in before setToIdle was called.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the MipNode.
        void setToIdle();

        //API Function: cyclePower
        //  Performs the "Device Reset" command.
        //  Note: This is essentially the same as unplugging and plugging the device back in.
        //
        //Exceptions:
        //  - <Error_Communication>: There was no response to the command. The command timed out.
        //  - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //  - <Error_Connection>: A connection error has occurred with the MipNode.
        bool cyclePower();

        //API Function: resume
        //    Places the Node back in the mode it was in before issuing the <setToIdle> command.
        //    If the <setToIdle> command was not issued, then the device is placed in default mode.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the MipNode.
        void resume();

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
        virtual uint8 getCommunicationMode() = 0;

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
        //    - <Error_NotSupported>: The command is not supported.
        virtual void setCommunicationMode(uint8 communicationMode) = 0;

        //API Function: saveSettingsAsStartup
        //    Save the current value of the specified settings commands as a startup setting.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void saveSettingsAsStartup();

        //API Function: saveSettingsAsStartup
        //    Save the current value of the specified settings commands as a startup setting.
        //
        //Parameters:
        //  cmdIds - (Optional) <MipTypes::MipCommands> list of IDs of the settings commands to save
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void saveSettingsAsStartup(MipTypes::MipCommands cmdIds);

        //API Function: saveSettingsAsStartup
        //    Save the current value of the specified settings commands as a startup setting.
        //
        //Parameters:
        //  cmdParams - (Optional) <MipCommandParameters> map of command IDs with associated parameters to save (if required, ie: message format, comm port speed, etc.)
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void saveSettingsAsStartup(MipCommandParameters cmdParams);

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

        //API Function: loadStartupSettings
        //  Loads the saved startup settings onto the Node as its current settings.
        //  This function is useful if you have powered on the Node, made changes to its settings, and
        //  want to get back to its startup settings.
        //
        //Parameters:
        //  cmdIds - (Optional) <MipTypes::MipCommands> list of IDs of the settings commands to load
        //
        //Exceptions:
        //  - <Error_Communication>: There was no response to the command. The command timed out.
        //  - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //  - <Error_Connection>: A connection error has occurred with the InertialNode.
        void loadStartupSettings(MipTypes::MipCommands cmdIds);

        //API Function: loadStartupSettings
        //  Loads the saved startup settings onto the Node as its current settings.
        //  This function is useful if you have powered on the Node, made changes to its settings, and
        //  want to get back to its startup settings.
        //
        //Parameters:
        //  cmdParams - (Optional) <MipCommandParameters> map of command IDs with associated parameters to load (if required, ie: message format, comm port speed, etc.)
        //
        //Exceptions:
        //  - <Error_Communication>: There was no response to the command. The command timed out.
        //  - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //  - <Error_Connection>: A connection error has occurred with the InertialNode.
        void loadStartupSettings(MipCommandParameters cmdParams);

        //API Function: loadFactoryDefaultSettings
        //  Loads the factory default settings onto the Node as its current settings.
        //
        //Exceptions:
        //  - <Error_Communication>: There was no response to the command. The command timed out.
        //  - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //  - <Error_Connection>: A connection error has occurred with the InertialNode.
        void loadFactoryDefaultSettings();

        //API Function: loadFactoryDefaultSettings
        //  Loads the factory default settings onto the Node as its current settings.
        //
        //Parameters:
        //  cmdIds - (Optional) <MipTypes::MipCommands> list of IDs of the settings commands to load
        //
        //Exceptions:
        //  - <Error_Communication>: There was no response to the command. The command timed out.
        //  - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //  - <Error_Connection>: A connection error has occurred with the InertialNode.
        void loadFactoryDefaultSettings(MipTypes::MipCommands cmdIds);

        //API Function: loadFactoryDefaultSettings
        //  Loads the factory default settings onto the Node as its current settings.
        //
        //Parameters:
        //  cmdParams - (Optional) <MipCommandParameters> map of command IDs with associated parameters to load (if required, ie: message format, comm port speed, etc.)
        //
        //Exceptions:
        //  - <Error_Communication>: There was no response to the command. The command timed out.
        //  - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //  - <Error_Connection>: A connection error has occurred with the InertialNode.
        void loadFactoryDefaultSettings(MipCommandParameters cmdParams);

        //API Function: setUARTBaudRate
        //    Sets the baud rate.  The device can be unresponsive for as much as 250 ms following this command.
        //    Important: The connection to the port will be automatically closed and re-opened at the new baud rate unless resetConnection parameter is false.
        //
        //Parameters:
        //    baudRate - The new baud rate.
        //    resetConnection - (Optional) Specifies whether the connection to the port should be automatically closed and re-opened at the new baud rate.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void setUARTBaudRate(uint32 baudRate, bool resetConnection = true);

        //API Function: setUARTBaudRate
        //    Sets the baud rate.  The device can be unresponsive for as much as 250 ms following this command.
        //    Important: The connection to the port will be automatically closed and re-opened at the new baud rate unless resetConnection parameter is false.
        //
        //Parameters:
        //    baudRate - The new baud rate.
        //    portId - Specify the port id to set the baud rate. This value is ignored if device does not support command: Comm Port Speed (0x01,0x09)
        //    resetConnection - (Optional) Specifies whether the connection to the port should be automatically closed and re-opened at the new baud rate.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void setUARTBaudRate(uint32 baudRate, uint8 portId, bool resetConnection = true);

        //API Function: getUARTBaudRate
        //    Gets the current baud rate for the inertial device.
        //
        //Parameters:
        //  portId - (Optional) Specify the port id to read the baud rate. This value is ignored if device does not support command: Comm Port Speed (0x01,0x09)
        //
        //Return:
        //    uint8 current baud rate.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        uint32 getUARTBaudRate(uint8 portId = 1);

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
    };
}