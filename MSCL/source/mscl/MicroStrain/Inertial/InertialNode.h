/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "InertialNodeInfo.h"
#include "InertialChannel.h"
#include "InertialTypes.h"
#include "Commands/InertialCmdResponse.h"
#include "Packets/InertialDataPacket.h"
#include "mscl/Communication/Connection.h"
#include "mscl/MicroStrain/Inertial/PositionOffset.h"
#include "mscl/MicroStrain/Inertial/EulerAngles.h"
#include "mscl/MicroStrain/Inertial/ExposedInertialTypes.h"

namespace mscl
{
    //forward declarations
    class InertialNode_Impl;
    class InertialNodeFeatures;

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
        //    - <Error_Connection>: A problem occured with the Connection.
        explicit InertialNode(Connection connection);

        virtual ~InertialNode() {}

#ifndef SWIG
        InertialNode(std::shared_ptr<InertialNode_Impl> impl); //constructor with direct underlying implementation for this class.
#endif

    private:
        //Variable: m_impl
        //    The <InertialNode_Impl> class that contains all the implementation logic for the InertialNode class.
        std::shared_ptr<InertialNode_Impl> m_impl;

    public:   
#ifndef SWIG
        //Function: doCommand
        //    Performs a generic Inertial Command, sending the command bytes and waiting for the response.
        //
        //Parameters:
        //    response - A <GenericInertialCommand::Response> that will be used to wait and contain all the command/result information.
        //    command - The <ByteStream> containing the bytes to send for the command.
        //    verifySupported - Whether to verify if the command is supported before performing the command (default of true).
        //
        //Returns:
        //    The <GenericInertialCommandResponse> that contains the actual data from the response
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_InertialCmdFailed>: The command has failed.
        virtual GenericInertialCommandResponse doCommand(GenericInertialCommand::Response& response, const ByteStream& command, bool verifySupported = true) const;
#endif

        //API Function: deviceName
        //    Static function for creating the universal sensor name that should be used for SensorCloud.
        //
        //Parameters:
        //    serial - The serial number of the inertial node. This should be identical to calling the <serialNumber> function on an <InertialNodeInfo> object (see <InertialNode::info>).
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
        //    Gets a reference to the <InertialNodeFeatures> for this device.
        //    Note: This will be invalid when the InertialNode is destroyed.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The model is not supported by MSCL.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: Information failed to be loaded for this Node.
        const InertialNodeFeatures& features();

        //API Function: lastCommunicationTime
        //    Gets the <Timestamp> for the last time MSCL communicated with the InertialNode.
        //
        //Returns:
        //    A <Timestamp> representing the last time MSCL communicated with the Node.
        //
        //Exceptions:
        //  - <Error_NoData>: There is no communication time logged for this device.
        const Timestamp& lastCommunicationTime() const;

        //API Function: firmwareVersion
        //    Gets the firmware <Version> of the InertialNode.
        //
        //Returns:
        //    The firmware <Version> of the InertialNode.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    A vector of <InertialDataPacket>s containing all the data packets that are available up to the requested number of packets. 
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        InertialDataPackets getDataPackets(uint32 timeout = 0, uint32 maxPackets = 0);

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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setToIdle();

        //API Function: cyclePower
        //  Performs the "Device Reset" Inertial command.
        //  Note: This is essentially the same as unplugging and plugging the device back in.
        //
        //Exceptions:
        //  - <Error_Communication>: There was no response to the command. The command timed out.
        //  - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //  - <Error_Connection>: A connection error has occurred with the InertialNode.
        bool cyclePower();

        //API Function: resume
        //    Places the Node back in the mode it was in before issuing the <setToIdle> command.
        //    If the <setToIdle> command was not issued, then the device is placed in default mode.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void resume();

        //API Function: saveSettingsAsStartup
        //  Saves all of the current settings as the Node's startup settings.
        //  Note: A brief data disturbance may occur when calling this command.
        //
        //Exceptions:
        //  - <Error_Communication>: There was no response to the command. The command timed out.
        //  - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //  - <Error_Connection>: A connection error has occurred with the InertialNode.
        void saveSettingsAsStartup();

        //API Function: loadStartupSettings
        //  Loads the saved startup settings onto the Node as its current settings.
        //  This function is useful if you have powered on the Node, made changes to its settings, and
        //  want to get back to its startup settings.
        //
        //Exceptions:
        //  - <Error_Communication>: There was no response to the command. The command timed out.
        //  - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //  - <Error_Connection>: A connection error has occurred with the InertialNode.
        void loadStartupSettings();

        //API Function: loadFactoryDefaultSettings
        //  Loads the factory default settings onto the Node as its current settings.
        //
        //Exceptions:
        //  - <Error_Communication>: There was no response to the command. The command timed out.
        //  - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //  - <Error_Connection>: A connection error has occurred with the InertialNode.
        void loadFactoryDefaultSettings();

        //API Function: getDataRateBase
        //    Gets the Data decimation base for the data rate calculations of the specified <InertialType>.
        //
        //Parameters:
        //    type - The <InertialTypes::InertialCategory> to get the Data decimation base for.
        //
        //Returns:
        //    The decimation base for the data rate calculations.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command or <InertialTypes::InertialCategory> is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        uint16 getDataRateBase(InertialTypes::InertialCategory category);

        //API Function: getActiveChannelFields
        //    Gets the current active channel fields for the specified <InertialTypes::InertialCategory>.
        //
        //Parameters:
        //    category - The <InertialTypes::InertialCategory> to get the current message format for.
        //
        //Returns:
        //    An <InertialChannels> object containing the channels that make up the data message format for the specified <InertialTypes::InertialCategory>.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command or <InertialTypes::InertialCategory> is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        InertialChannels getActiveChannelFields(InertialTypes::InertialCategory category);

        //API Function: setActiveChannelFields
        //    Sets the current active channel fields for the specified <InertialTypes::InertialCategory>.
        //    Note that this function does not add to the existing message format (active channels), but overwrites it entirely.
        //
        //Parameters:
        //    category - The <InertialTypes::InertialCategory> to set the message format for.
        //    channels - The <InertialChannels> object containing the channels to set the message format to. Passing an empty <InertialChannels> object will effectively disable all channels.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command or <InertialTypes::InertialCategory> is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        //    - <Error>: An <InertialChannel> in the channels parameter is not part of the specified <InertialTypes::InertialCategory>'s descriptor set.
        void setActiveChannelFields(InertialTypes::InertialCategory category, const InertialChannels& channels);

        //Function: saveActiveChannelFields
        //    Saves the current message format of the specified <InertialTypes::InertialCategory>'s data packet.
        //    Note that this function does not add to the existing message format, but overwrites it entirely.
        //
        //Parameters:
        //    category - The <InertialTypes::InertialCategory> to set the message format for.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command or <InertialTypes::InertialCategory> is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        //    - <Error>: An <InertialChannel> in the channels parameter is not part of the specified <InertialTypes::InertialCategory>'s descriptor set.
        void saveActiveChannelFields(InertialTypes::InertialCategory category);

        //API Function: getCommunicationMode
        //    Gets the current communication mode that the node is in.
        //
        //Returns:
        //    The communication mode the node is in. This is an advanced command, and therefore the communication modes for your device should be researched to determine what each communication mode is.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command or <InertialTypes::InertialCategory> is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setCommunicationMode(uint8 communicationMode);

        //API Function: enableDataStream
        //    Enables or disables continuous data streaming for the node.
        //
        //Parameters:
        //    category - The <InertialTypes::InertialCategory> to enable/disable streaming for.
        //    enable - Whether to enable (true) or disable (false) continuous streaming (Default of true).
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command or <InertialTypes::InertialCategory> is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void enableDataStream(InertialTypes::InertialCategory category, bool enable = true);

        //API Function: resetFilter
        //    Resets the filter to the initialize state.
        //    Note: If the auto-initialization feature is disabled, the initial attitude or heading must
        //          be set in order to enter the run state after a reset.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed.
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
        //    - <Error_InertialCmdFailed>: The command has failed.
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
        //    - <Error_InertialCmdFailed>: The command has failed.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setAutoInitialization(bool enable);

        //API Function: setInitialAttitude
        //    Sets the initial attitude.
        //    Node: This command can only be issues in the "INIT" state and should be used with a
        //          good estimate of the vehicle attitude.
        //
        //Parameters:
        //  attitude - The <EulerAngles> (in radians) representing the sensor body frame with respect to the local NED frame.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setInitialAttitude(const EulerAngles& attitude);

        //API Function: setInitialHeading
        //    Sets the initial heading.
        //    Node: This command can only be issues in the "INIT" state and should be used with a
        //          good estimate of heading. The device will use this value in conjunction with the
        //          output of the accelerometers to determine the initial attitude estimate.
        //
        //Parameters:
        //  heading - The heading to set (in radians).
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setInitialHeading(float heading);

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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setGNSSAssistTimeUpdate(const TimeUpdate& timeUpdate);

        //API Function: getGPSTimeUpdate
        //    Gets the GPS time update.
        //
        //Parameters:
        //    timeFrame - The <InertialTypes::TimeFrame> object specifying what current time value to get, either weeks or seconds.
        //
        //Returns:
        //    The current time for the specified value type.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        mscl::uint32 getGPSTimeUpdate(InertialTypes::TimeFrame timeFrame);

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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        void setGPSTimeUpdate(InertialTypes::TimeFrame, mscl::uint32 timeData);

        //API Function: setConstellationSettings
        //    Sets the GNSS Constellation Settings.
        //
        //Parameters:
        //    dataToUse - The <ConstellationSettingsData> object containing the data to set.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        GeometricVector captureGyroBias(const uint16& samplingTime);

        //API Function: setMagnetometerSoftIronMatrix
        //    Sets the Magnetometer Soft Iron matrix.
        //
        //Parameters:
        //    matrix - The <Matrix_3x3> object containing the matrix to set.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        bool getConingAndScullingEnable();

        //API Function: setUARTBaudRate
        //    Sets the baud rate.  The device can be unresponsive for as much as 250 ms following this command.
        //
        //Parameters:
        //    baudRate - The new baud rate.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void setUARTBaudRate(uint32 baudRate);

        //API Function: getUARTBaudRate
        //    Gets the current baud rate for the inertial device.
        //
        //Return:
        //    uint8 current baud rate.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void setAdvancedLowPassFilterSettings(const AdvancedLowPassFilterData& data);

        //API Function: getAdvancedLowPassFilterSettings
        //    Gets the current advanced low-pass filter settings.
        //
        //Parameter:
        //    data - The <AdvancedLowPassFilterData::DataDescriptor> field from
        //    the passed in data is used to set the type of data to be returned.
        //
        //Return:
        //    AdvancedLowPassFilterData new settings.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        AdvancedLowPassFilterData getAdvancedLowPassFilterSettings(const AdvancedLowPassFilterData& data);
        
        //API Function: setComplementaryFilterSettings
        //    Sets the complementary filter settings.
        //
        //Parameter:
        //    data - the new settings to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void setVehicleDynamicsMode(const VehicleModeType& mode);

        //API Function: getVehicleDynamicsMode
        //    Gets the vehicle dynamics mode.
        //
        //Return:
        //    VehicleModeType - The new mode.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        VehicleModeType getVehicleDynamicsMode();

        //API Function: setEstimationControlFlags
        //    Sets the estimation control flags.
        //
        //Parameter:
        //    mode - the new flags to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void setEstimationControlFlags(const uint16& flags);

        //API Function: getEstimationControlFlags
        //    Gets the estimation control flags.
        //
        //Return:
        //    uint16 - The new flags.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        uint16 getEstimationControlFlags();

        //API Function: setEstimationControlFlags
        //    Sets the estimation control flags.
        //
        //Parameter:
        //    gnssSource - the new mode to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void setGNSS_SourceControl(const GNSS_Source& gnssSource);

        //API Function: getEstimationControlFlags
        //    Gets the estimation control flags.
        //
        //Return:
        //    <GNSS_Source> - The new source.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        GNSS_Source getGNSS_SourceControl();

        //API Function: sendExternalGNSSUpdate
        //    sends the external GNSS update command.
        //
        //Parameter:
        //    gnssUpdateData - the data to send.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void setHeadingUpdateControl(const HeadingUpdateOptions& headingUpdateOptions);

        //API Function: getHeadingUpdateControl
        //    Gets the heading update control flags.
        //
        //Return:
        //    <HeadingUpdateOptions> - The current options.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        HeadingUpdateOptions getHeadingUpdateControl();

        //API Function: sendExternalHeadingUpdate
        //    sends the external heading update command.
        //
        //Parameter:
        //    headingData - the new heading.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
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
        //    - <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.ConstellationSettingsData
        void sendExternalHeadingUpdate(const HeadingData& headingData, const TimeUpdate& timestamp);
    };
    
}
