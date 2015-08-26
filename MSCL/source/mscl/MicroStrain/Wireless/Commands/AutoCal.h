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
//PUBLIC_HEADER
#pragma once

#include "mscl/Types.h"
#include "mscl/Version.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/ResponsePattern.h"
#include "mscl/MicroStrain/Wireless/WirelessModels.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"

namespace mscl
{
	//API Title: AutoCal

	class WirelessPacket;

	//API Class: AutoCalResult
	//	Abstract base class for AutoCal result classes.
	class AutoCalResult
	{
		friend class BaseStation_Impl;

	public:
		AutoCalResult();

		//API Function: completionFlag
		//	Gets the <WirelessTypes::AutoCalCompletionFlag> of the AutoCal operation result.
		WirelessTypes::AutoCalCompletionFlag completionFlag() const;

	protected:
		//Function: parse
		//	Parses the auto cal info bytes sent in the successful response packet.
		//
		//Parameters:
		//	autoCalInfo - The bytes from a successful auto cal command.
		virtual void parse(const Bytes& autoCalInfo) = 0;

		//Variable: m_completionFlag
		//	The <WirelessTypes::AutoCalCompletionFlag> of the AutoCal operation.
		WirelessTypes::AutoCalCompletionFlag m_completionFlag;
	};

	//API Class: AutoCalResult_shmLink
	//	Holds the result information from an autoCal_shmLink command.
	class AutoCalResult_shmLink : public AutoCalResult
	{
	private:
		//Variable: m_errorFlagCh1
		//	The <WirelessTypes::AutoCalErrorFlag> for the channel 1 strain sensor.
		WirelessTypes::AutoCalErrorFlag m_errorFlagCh1;

		//Variable: m_errorFlagCh2
		//	The <WirelessTypes::AutoCalErrorFlag> for the channel 2 strain sensor.
		WirelessTypes::AutoCalErrorFlag m_errorFlagCh2;

		//Variable: m_errorFlagCh3
		//	The <WirelessTypes::AutoCalErrorFlag> for the channel 3 strain sensor.
		WirelessTypes::AutoCalErrorFlag m_errorFlagCh3;

		//Variable: m_offsetCh1
		//	The offset applied for the channel 1 strain sensor.
		float m_offsetCh1;

		//Variable: m_offsetCh2
		//	The offset applied for the channel 2 strain sensor.
		float m_offsetCh2;

		//Variable: m_offsetCh3
		//	The offset applied for the channel 3 strain sensor.
		float m_offsetCh3;

		//Variable: m_temperature
		//	The temperature at the time of calibration.
		float m_temperature;

	public:
		AutoCalResult_shmLink();

		//API Function: errorFlagCh1
		//	Gets the <WirelessTypes::AutoCalErrorFlag> for the channel 1 strain sensor.
		WirelessTypes::AutoCalErrorFlag errorFlagCh1() const;

		//API Function: errorFlagCh2
		//	Gets the <WirelessTypes::AutoCalErrorFlag> for the channel 2 strain sensor.
		WirelessTypes::AutoCalErrorFlag errorFlagCh2() const;

		//API Function: errorFlagCh3
		//	Gets the <WirelessTypes::AutoCalErrorFlag> for the channel 3 strain sensor.
		WirelessTypes::AutoCalErrorFlag errorFlagCh3() const;

		//API Function: offsetCh1
		//	Gets the offset applied for the channel 1 strain sensor.
		float offsetCh1() const;

		//API Function: offsetCh2
		//	Gets the offset applied for the channel 2 strain sensor.
		float offsetCh2() const;

		//API Function: offsetCh3
		//	Gets the offset applied for the channel 3 strain sensor.
		float offsetCh3() const;

		//API Function: temperature
		//	Gets the temperature (in °C) at the time of the calibration.
		float temperature() const;

	protected:
		//Function: parse
		//	Parses the auto cal info bytes for the shm-link.
		virtual void parse(const Bytes& autoCalInfo) final;
	};

	

#ifndef SWIG
	//Class: AutoCal
	//	Contains logic for the AutoCal Node command.
	class AutoCal
	{
	private:
		AutoCal();								//default constructor disabled
		AutoCal(const AutoCal&);				//copy constructor disabled
		AutoCal& operator=(const AutoCal&);		//assignment operator disabled 

	public:
		//Function: buildCommand_shmLink
		//	Builds the AutoCal command packet for the SHM-Link node.
		//
		//Parameters:
		//	nodeAddress - The address of the Node to build the command for.
		//
		//Returns:
		//	A <ByteStream> containing the command packet.
		static ByteStream buildCommand_shmLink(NodeAddress nodeAddress);

		//Class: Response
		//	Handles the response to the LongPing Node command
		class Response : public ResponsePattern
		{
		public:
			//Constructor: Response
			//	Creates a AutoCal Response object
			//
			//Parameters:
			//	nodeAddress - The node address to check for.
			//	model - The <WirelessModels::NodeModel> of the Node we are expecting a response for.
			//	fwVersion - The firmware version of the Node we are expecting a response for.
			//	collector - The <ResponseCollector> used to register and unregister the response.
			Response(NodeAddress nodeAddress, WirelessModels::NodeModel model, const Version& fwVersion, std::weak_ptr<ResponseCollector> collector);

		private:
			//Variable: m_nodeAddress
			//	The node address to look for in the response.
			NodeAddress m_nodeAddress;

			//Variable: m_model
			//	The <WirelessModels::NodeModel> of the Node we are expecting a response for.
			WirelessModels::NodeModel m_model;

			//Variable: m_fwVersion
			//	The firmware version of the Node we are expecting a response for.
			Version m_fwVersion;

			//Variable: m_calStarted
			//	Whether the AutoCal has been successfully started or not (as reported by the Node).
			bool m_calStarted;

			//Variable: m_completionFlag
			//	The <AutoCalCompletionFlag> representing the final autocal status.
			WirelessTypes::AutoCalCompletionFlag m_completionFlag;

			//Variable: m_timeUntilCompletion
			//	The amount of time (in seconds) that the autocal operation will take to complete.
			//	This value gets reported by the Node before starting the calibration.
			float m_timeUntilCompletion;

			//Variable: m_infoBytes
			//	Contains all of the information bytes from the completion response.
			Bytes m_infoBytes;

		public:
			//Function: calStarted
			//	Gets whether the AutoCal operation has started or not.
			//
			//Returns:
			//	true if the Node indicated that the AutoCal operation has started, false otherwise.
			bool calStarted() const;

			//Function: calTime
			//	Gets the total time (in seconds) that the Node reported it will take to complete the AutoCal operation.
			//
			//Returns:
			//	The time (in seconds) that the Node reported it will take to complete AutoCal.
			float calTime() const;

			//Function: completionFlag
			//	Gets the <WirelessTypes::AutoCalCompletionFlag> of the AutoCal operation.
			//
			//Returns:
			//	The <WirelessTypes::AutoCalCompletionFlag> of the AutoCal operation.
			WirelessTypes::AutoCalCompletionFlag completionFlag() const;

			//Function: infoBytes
			//	Gets the information bytes returned from the AutoCal completion packet.
			//
			//Returns:
			//	The information <Bytes> from the AutoCal completion packet.
			const Bytes& infoBytes() const;

			//Function: match
			//	Checks if the <WirelessPacket> passed in matches the expected response pattern's bytes.
			//
			//Parameters:
			//	packet - The <WirelessPacket> in which to try to find the pattern
			//
			//Returns:
			//	true if the packet matches a response pattern, false otherwise
			virtual bool match(const WirelessPacket& packet) override;

			//Function: match_nodeReceived
			//	Checks if the <WirelessPacket> passed in matches the "Node Received" packet.
			//
			//Parmeters:
			//	packet - The <WirelessPacket> to try to match.
			//
			//Returns:
			//	true if the packet matches the Node Received packet, false otherwise.
			bool match_nodeReceived(const WirelessPacket& packet);

			//Function: match_shmLink
			//	Checks if the <WirelessPacket> matches the SHM-Link AutoCal packet.
			//
			//Parameters:
			//	packet - The <WirelessPacket> to try to match.
			//
			//Returns:
			//	true if the packet matches the SHM-Link AutoCal packet, false otherwise.
			bool match_shmLink(const WirelessPacket& packet);
		};
	};
#endif

}