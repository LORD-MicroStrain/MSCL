/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/MicroStrain/MIP/MipNodeInfo.h"
#include "mscl/MicroStrain/MIP/MipChannel.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MipCmdResponse.h"
#include "mscl/MicroStrain/MIP/Packets/MipDataPacket.h"
#include "DisplacementModels.h"
#include "mscl/Communication/Connection.h"
#include "mscl/MicroStrain/LinearEquation.h"

namespace mscl
{
    //forward declarations
    class MipNode_Impl;
    class MipNodeFeatures;

    //API Class: DisplacementNode
    //    A class representing a MicroStrain Displacement Node
    class DisplacementNode
    {
    private:
        DisplacementNode();        //default constructor disabled

    public:
        //API Constructor: DisplacementNode
        //    Creates an DisplacementNode object.
        //
        //Parameters:
        //    connection - The Connection object used for communication.
        //
        //Exceptions:
        //    - <Error_Connection>: A problem occured with the Connection.
        explicit DisplacementNode(Connection connection);

        virtual ~DisplacementNode() {}

#ifndef SWIG
        DisplacementNode(std::shared_ptr<MipNode_Impl> impl); //constructor with direct underlying implementation for this class.
#endif

    private:
        //Variable: m_impl
        //    The <MipNode_Impl> class that contains all the implementation logic for the DisplacementNode class.
        std::shared_ptr<MipNode_Impl> m_impl;

    public:   
#ifndef SWIG
        //Function: doCommand
        //    Performs a generic Mip Command, sending the command bytes and waiting for the response.
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

        //API Function: deviceName
        //    Static function for creating the universal sensor name that should be used for SensorCloud.
        //
        //Parameters:
        //    serial - The serial number of the node. This should be identical to calling the <serialNumber> function on an <MipNodeInfo> object (see <DisplacementNode::info>).
        //
        //Returns:
        //    The universal sensor name.
        static std::string deviceName(const std::string& serial);

        //API Function: connection
        //    Gets the <Connection> object that this DisplacementNode is using.
        //
        //Returns:
        //    The <Connection> object that this DisplacementNode is using.
        Connection& connection();

        //API Function: features
        //    Gets a reference to the <MipNodeFeatures> for this device.
        //    Note: This will be invalid when the DisplacementNode is destroyed.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The model is not supported by MSCL.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: Information failed to be loaded for this Node.
        const MipNodeFeatures& features();

        //API Function: lastCommunicationTime
        //    Gets the <Timestamp> for the last time MSCL communicated with the DisplacementNode.
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
        //    Gets the firmware <Version> of the DisplacementNode.
        //
        //Returns:
        //    The firmware <Version> of the DisplacementNode.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: Information failed to be loaded for this Node.
        Version firmwareVersion() const;

        //API Function: model
        //    Gets the <DisplacementModels::NodeModel> of the DisplacementNode.
        //
        //Returns:
        //    The <DisplacementModels::NodeModel> of the DisplacementNode.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: Information failed to be loaded for this Node.
        DisplacementModels::NodeModel model() const;

        //API Function: modelName
        //    Gets the model name of the DisplacementNode (ie. "3DM-GX3-45").
        //
        //Returns:
        //    The model name of the DisplacementNode.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: Information failed to be loaded for this Node.
        std::string modelName() const;

        //API Function: modelNumber
        //    Gets the model number of the DisplacementNode (ie. "6225-4220").
        //
        //Returns:
        //    The model number of the DisplacementNode.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: Information failed to be loaded for this Node.
        std::string modelNumber() const;

        //API Function: serialNumber
        //    Gets the serial number of the DisplacementNode (ie. "6225-01319").
        //
        //Returns:
        //    The serial number of the DisplacementNode.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: Information failed to be loaded for this Node.
        std::string serialNumber() const;

        //API Function: lotNumber
        //    Gets the lot number of the DisplacementNode (ie. "I042Y").
        //
        //Returns:
        //    The lot number of the DisplacementNode.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: Information failed to be loaded for this Node.
        std::string lotNumber() const;

        //API Function: deviceOptions
        //    Gets the device options of the DisplacementNode (ie. "5g, 300d/s").
        //
        //Returns:
        //    The device options of the DisplacementNode.
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
        //    - <Error_Connection>: A connection error has occurred with the DisplacementNode.
        MipDataPackets getDataPackets(uint32 timeout = 0, uint32 maxPackets = 0);

        //API Function: totalPackets
        //    Gets the total number of data packets that are currently in the buffer.
        //
        //Returns:
        //    The total number of data packets that are currently in the buffer.
        uint32 totalPackets();

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
        //    Gets the name of the DisplacementNode. This is the universal sensor name that should be used for uploading to SensorCloud.
        //    This is the same as calling <DisplacementNode::deviceName>.
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
        //    - <Error_Connection>: A connection error has occurred with the DisplacementNode.
        bool ping();

        //API Function: setToIdle
        //    Suspends streaming (if enabled) or wakes the device from sleep (if sleeping), putting the device in an idle mode.
        //    After this command is used, the <resume> command may be used to put the Node back into the mode it was previously in before setToIdle was called.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the DisplacementNode.
        void setToIdle();

        //API Function: cyclePower
        //  Performs the "Device Reset" command.
        //  Note: This is essentially the same as unplugging and plugging the device back in.
        //
        //Exceptions:
        //  - <Error_Communication>: There was no response to the command. The command timed out.
        //  - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //  - <Error_Connection>: A connection error has occurred with the DisplacementNode.
        bool cyclePower();

        //API Function: resume
        //    Places the Node back in the mode it was in before issuing the <setToIdle> command.
        //    If the <setToIdle> command was not issued, then the device is placed in default mode.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the DisplacementNode.
        void resume();

        //API Function: getDisplacementOutputDataRate
        //  Gets the output data rate for the displacement data.
        //
        //Returns:
        //  A <SampleRate>.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the DisplacementNode.
        SampleRate getDisplacementOutputDataRate() const;

        //API Function: getAnalogToDisplacementCal
        //  Gets the Analog to Displacement calibration coefficients.
        //
        //Returns:
        //  A <LinearEquation> containing the slope and offset.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the DisplacementNode.
        LinearEquation getAnalogToDisplacementCal() const;

        //API Function: setDeviceTime
        //  Seeds the device time with the current system time. 
        //  This time will be reflected in the timestamp field that can come with data from the device.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the DisplacementNode.
        void setDeviceTime();

        //API Function: setDeviceTime
        //  Seeds the device time with a specific time.
        //  This time will be reflected in the timestamp field that can come with data from the device.
        //
        //Parameters:
        //  nanoseconds - The number of nanoseconds since Unix Epoch.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the DisplacementNode.
        void setDeviceTime(uint64 nanoseconds);
    };
    
}
