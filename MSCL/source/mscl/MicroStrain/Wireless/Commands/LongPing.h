/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
//PUBLIC_HEADER
#pragma once

#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/ResponsePattern.h"

namespace mscl
{
	class WirelessPacket;

	//Title: LongPing
	
	//API Class: PingResponse
	//	Represents the response to a Long Ping Node command
	class PingResponse
	{
	public:
		//Constructor: PingResponse
		//	Creates a PingResponse with default values
		PingResponse();

	private:
		//Constructor: PingResponse
		//	Creates a PingResponse with the given parameters
		//
		//Parameters:
		//	success - Whether or not the Long Ping response was a success
		//	nodeRssi - The node RSSI value received in the Long Ping response
		//	baseRssi - The base station RSSI value received in the Long Ping response
		PingResponse(bool success, int16 nodeRssi, int16 baseRssi);

#ifndef SWIG
	public:
		//Function: ResponseSuccess
		//	Creates a PingResponse with a successful response
		//
		//Parameters:
		//	nodeRssi - the node RSSI from the response
		//	baseRssi - the base station RSSI from the response
		//
		//Returns:
		//	A <PingResponse> representing a success response from the LongPing node command
		static PingResponse ResponseSuccess(int16 nodeRssi, int16 baseRssi);

		//Function: ResponseFail
		//	Creates a PingResponse with a fail response
		//
		//Returns:
		//	A <PingResponse> representing a failed response from the LongPing Node command
		static PingResponse ResponseFail();
#endif

	private:
		//Variable: m_success
		//	Whether or not the Long Ping response was a success
		bool m_success;

		//Variable: m_nodeRssi
		//	The node RSSI value received in the Long Ping response
		int16 m_nodeRssi;

		//Variable: m_baseRssi
		//	The base station RSSI value received in the Long Ping response
		int16 m_baseRssi;

	public:
		//API Function: success
		//	Gets whether or not the Long Ping command was a success (the node responded).
		//
		//Returns:
		//	true if the Long Ping command was a success, false otherwise.
		bool success() const;

		//API Function: nodeRssi
		//	Gets the node RSSI that was returned with the response (if success() returns true).
		//	This is the signal strength at which the Node received the BaseStation's command packet.
		//
		//Returns:
		//	The node RSSI that was returned with the response
		int16 nodeRssi() const;

		//API Function: baseRssi
		//	Gets the base station RSSI that was returned with the response (if success() returns true).
		//	This is the signal strength at which the BaseStation received the Nodes's response packet.
		//
		//Returns:
		//	The base station RSSI that was returned with the response.
		int16 baseRssi() const;
	};



#ifndef SWIG

	//Class: LongPing
	//	Contains logic for the LongPing Node command
	class LongPing
	{
	private:
		LongPing();								//default constructor disabled
		LongPing(const LongPing&);				//copy constructor disabled
		LongPing& operator=(const LongPing&);	//assignment operator disabled 

	public:
		//Function: buildCommand
		//	Builds the LongPing command packet
		//
		//Parameters:
		//	nodeAddress - the address of the Node to build the command for
		//
		//Returns:
		//	A <ByteStream> containing the LongPing command packet
		static ByteStream buildCommand(NodeAddress nodeAddress);

		//Class: Response
		//	Handles the response to the LongPing Node command
		class Response : public ResponsePattern
		{
		public:
			//Constructor: Response
			//	Creates a LongPing Response object
			//
			//Parameters:
			//	nodeAddress - the node address to check for
			//	collector - The <ResponseCollector> used to register and unregister the response
			Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector);

		private:
			//Variable: m_nodeAddress
			//	The node address to look for in the Long Ping response
			NodeAddress m_nodeAddress;

			//Variable: m_result
			//	The <PingResponse> that holds the result of the LongPing Node command
			PingResponse m_result;

		public:
			//Function: match
			//	Checks if the <WirelessPacket> passed in matches the expected response pattern's bytes
			//
			//Parameters:
			//	packet - The <WirelessPacket> in which to try to find the pattern
			//
			//Returns:
			//	true if the packet matches a response pattern, false otherwise
			virtual bool match(const WirelessPacket& packet) override;

			//Function: result
			//	Gets the <PingResponse> that holds the result of the response
			//
			//Returns:
			//	A <PingResponse> that holds the result of the response
			PingResponse result();
		};
	};

#endif
}