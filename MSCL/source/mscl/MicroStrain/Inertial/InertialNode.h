/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
//PUBLIC_HEADER
#pragma once

#include "InertialNodeInfo.h"
#include "InertialChannel.h"
#include "InertialTypes.h"
#include "Commands/InertialCmdResponse.h"
#include "Packets/InertialDataPacket.h"
#include "mscl/Communication/Connection.h"

namespace mscl
{
	class InertialNode_Impl;

	//API Class: InertialNode
	//	A class representing a MicroStrain Inertial Node
	//
	//See Also:
	//	<WirelessNode>
	class InertialNode
	{
	private:
		InertialNode();		//default constructor disabled

	public:
		//API Constructor: InertialNode
		//	Creates an InertialNode object.
		//
		//Parameters:
		//	connection - The Connection object used for communication.
		//
		//Exceptions:
		//	- <Error_Connection>: A problem occured with the Connection.
		explicit InertialNode(Connection connection);

#ifndef SWIG
		InertialNode(std::shared_ptr<InertialNode_Impl> impl); //constructor with direct underlying implementation for this class.
#endif

	private:
		//Variable: m_impl
		//	The <InertialNode_Impl> class that contains all the implementation logic for the InertialNode class.
		std::shared_ptr<InertialNode_Impl> m_impl;

	public:
		//API Function: deviceName
		//	Static function for creating the universal sensor name that should be used for SensorCloud.
		//
		//Parameters:
		//	serial - The serial number of the inertial node. This should be identical to calling the <serialNumber> function on an <InertialNodeInfo> object (see <InertialNode::info>).
		//
		//Returns:
		//	The universal sensor name.
		static std::string deviceName(const std::string& serial);

		//API Function: lastCommunicationTime
		//	Gets the <Timestamp> for the last time MSCL communicated with the InertialNode.
		//
		//Returns:
		//	A <Timestamp> representing the last time MSCL communicated with the Node. This will be a Timestamp of 0 if never communicated with.
		const Timestamp& lastCommunicationTime() const;

		//API Function: supportedSampleRates
		//	Gets a list of the supported sample rates for an <InertialTypes::InertialCategory>.
		//
		//Parameters:
		//	category - The <InertialTypes::InertialCategory> to get the sample rate list for.
		//
		//Returns:
		//	A <SampleRates> list containing all the supported sample rates for the provided channel.
		//
		//Exceptions:
		//	- <Error_InertialCmdFailed>: The command has failed.
		//	- <Error_Timeout>: Timed out waiting for a response.
		//	- <Error_NotSupported>: The <InertialTypes::InertialCategory> is not supported by this node.
		//	- <Error_Connection>: A connection error has occurred with the InertialNode.
		//	- <Error>: The <InertialTypes::ChannelField> is invalid.
		const SampleRates& supportedSampleRates(InertialTypes::InertialCategory category);

		//API Function: getNextDataPacket
		//	Gets the next <InertialDataPacket> containing sampled data sent from this Inertial device.
		//	See the <getDataPackets> function for getting all available data packets that are in the buffer.
		//
		//Parameters:
		//	timeout - the timeout, in milliseconds, to wait for the next data packet if necessary (default of 0).
		//
		//Returns:
		//	The next <InertialDataPacket> that was collected by this Inertial device.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the InertialNode.
		//	- <Error_NoData>: No data was collected for this device.
		InertialDataPacket getNextDataPacket(uint32 timeout = 0);

		//API Function: getDataPackets
		//	Gets up to the requested amount of data packets that have been collected.
		//
		//Parameters:
		//	timeout - The timeout, in milliseconds, to wait for data if necessary (default of 0).
		//	maxPackets - The maximum number of packets to return. If this is 0 (default), all packets will be returned.
		//
		//Returns:
		//	A vector of <InertialDataPacket>s containing all the data packets that are available up to the requested number of packets. 
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the InertialNode.
		InertialDataPackets getDataPackets(uint32 timeout = 0, uint32 maxPackets = 0);

		//API Function: totalPackets
		//	Gets the total number of data packets that are currently in the buffer.
		//
		//Returns:
		//	The total number of data packets that are currently in the buffer.
		uint32 totalPackets();

		//API Function: commandsTimeout
		//	Sets the timeout to use when waiting for responses from Inertial commands.
		//
		//Parameters:
		//	timeout - The timeout (in milliseconds) to set for Inertial commands.
		void commandsTimeout(uint64 timeout);

		//API Function: info
		//	Gets <InertialNodeInfo> for this Node. 
		//	The first time this function is called, it will send multiple commands to the device to get all required information.
		//
		//Returns:
		//	A reference to the <InertialNodeInfo> for this Node.
		//
		//Exceptions:
		//	- <Error_Timeout>: There was no response to the command. The command timed out.
		//	- <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
		//	- <Error_Connection>: Information failed to be loaded for this Node.
		const InertialNodeInfo& info();

		//API Function: name
		//	Gets the name of the InertialNode. This is the universal sensor name that should be used for uploading to SensorCloud.
		//	This is the same as calling <InertialNode::deviceName>.
		//
		//Returns:
		//	The universal sensor name.
		std::string name();

		//API Function: ping
		//	Pings the Node to check for communication. 
		//	Sends the "Ping" command to the device.
		//
		//Returns:
		//	true if successfully pinged the node, false if failed.
		//
		//Exceptions:
		//	- <Error_Connection>: A connection error has occurred with the InertialNode.
		bool ping();

		//API Function: setToIdle
		//	Suspends streaming (if enabled) or wakes the device from sleep (if sleeping), putting the device in an idle mode.
		//	After this command is used, the <resume> command may be used to put the Node back into the mode it was previously in before setToIdle was called.
		//
		//Exceptions:
		//	- <Error_Timeout>: There was no response to the command. The command timed out.
		//	- <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
		//	- <Error_Connection>: A connection error has occurred with the InertialNode.
		void setToIdle();

		//API Function: resume
		//	Places the Node back in the mode it was in before issuing the <setToIdle> command.
		//	If the <setToIdle> command was not issued, then the device is placed in default mode.
		//
		//Exceptions:
		//	- <Error_Timeout>: There was no response to the command. The command timed out.
		//	- <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
		//	- <Error_Connection>: A connection error has occurred with the InertialNode.
		void resume();

		//API Function: getDataRateBase
		//	Gets the Data decimation base for the data rate calculations of the specified <InertialType>.
		//
		//Parameters:
		//	type - The <InertialTypes::InertialCategory> to get the Data decimation base for.
		//
		//Returns:
		//	The decimation base for the data rate calculations.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The command or <InertialTypes::InertialCategory> is not supported by this Node.
		//	- <Error_Timeout>: There was no response to the command. The command timed out.
		//	- <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
		//	- <Error_Connection>: A connection error has occurred with the InertialNode.
		uint16 getDataRateBase(InertialTypes::InertialCategory category);

		//API Function: getActiveChannelFields
		//	Gets the current active channel fields for the specified <InertialTypes::InertialCategory>.
		//
		//Parameters:
		//	category - The <InertialTypes::InertialCategory> to get the current message format for.
		//
		//Returns:
		//	An <InertialChannels> object containing the channels that make up the data message format for the specified <InertialTypes::InertialCategory>.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The command or <InertialTypes::InertialCategory> is not supported by this Node.
		//	- <Error_Timeout>: There was no response to the command. The command timed out.
		//	- <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
		//	- <Error_Connection>: A connection error has occurred with the InertialNode.
		InertialChannels getActiveChannelFields(InertialTypes::InertialCategory category);

		//API Function: setActiveChannelFields
		//	Sets the current active channel fields for the specified <InertialTypes::InertialCategory>.
		//	Note that this function does not add to the existing message format (active channels), but overwrites it entirely.
		//
		//Parameters:
		//	category - The <InertialTypes::InertialCategory> to set the message format for.
		//	channels - The <InertialChannels> object containing the channels to set the message format to. Passing an empty <InertialChannels> object will effectively disable all channels.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The command or <InertialTypes::InertialCategory> is not supported by this Node.
		//	- <Error_Timeout>: There was no response to the command. The command timed out.
		//	- <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
		//	- <Error_Connection>: A connection error has occurred with the InertialNode.
		//	- <Error>: An <InertialChannel> in the channels parameter is not part of the specified <InertialTypes::InertialCategory>'s descriptor set.
		void setActiveChannelFields(InertialTypes::InertialCategory category, const InertialChannels& channels);

		//API Function: getCommunicationMode
		//	Gets the current communication mode that the node is in.
		//
		//Returns:
		//	The communication mode the node is in. This is an advanced command, and therefore the communication modes for your device should be researched to determine what each communication mode is.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The command or <InertialTypes::InertialCategory> is not supported by this Node.
		//	- <Error_Timeout>: There was no response to the command. The command timed out.
		//	- <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
		//	- <Error_Connection>: A connection error has occurred with the InertialNode.
		uint8 getCommunicationMode();

		//API Function: setCommunicationMode
		//	Sets the communication mode for the node. 
		//	Note: The node info will be reset when doing this and therefore will require being fetched again the next time it is requested.
		//
		//Parameters:
		//	communicationMode - The communication mode to set. This is an advanced command, and therefore the communication modes for your device should be researched to determine what each communication mode is.
		//
		//Exceptions:
		//	- <Error_Timeout>: There was no response to the command. The command timed out.
		//	- <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
		//	- <Error_Connection>: A connection error has occurred with the InertialNode.
		void setCommunicationMode(uint8 communicationMode);

		//API Function: enableDataStream
		//	Enables or disables continuous data streaming for the node.
		//
		//Parameters:
		//	category - The <InertialTypes::InertialCategory> to enable/disable streaming for.
		//	enable - Whether to enable (true) or disable (false) continuous streaming (Default of true).
		//
		//Exceptions:
		//	- <Error_NotSupported>: The command or <InertialTypes::InertialCategory> is not supported by this Node.
		//	- <Error_Timeout>: There was no response to the command. The command timed out.
		//	- <Error_InertialCmdFailed>: The command has failed. Check the error code for more details.
		//	- <Error_Connection>: A connection error has occurred with the InertialNode.
		void enableDataStream(InertialTypes::InertialCategory category, bool enable = true);
	};

}