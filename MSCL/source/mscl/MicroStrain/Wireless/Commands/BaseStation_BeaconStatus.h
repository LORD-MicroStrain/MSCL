/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
//PUBLIC_HEADER
#pragma once

#include "mscl/MicroStrain/ResponsePattern.h"
#include "mscl/Timestamp.h"

namespace mscl
{
	//Title: BaseStation_BeaconStatus

	//API Class: BeaconStatus
	//	Represents the status of a BaseStation beacon.
	//	See also <BaseStation::beaconStatus>.
	class BeaconStatus
	{
	public:
		//Constructor: BeaconStatus
		//	Creates a default BeaconStatus object.
		BeaconStatus();

		//Constructor: BeaconStatus
		//	Creates a BeaconStatus object with the given parameters.
		//
		//Parameters:
		//	beaconEnabled - Whether the beacon is enabled or disabled.
		//	currentTimestamp - The current <Timestamp> of the beacon.
		BeaconStatus(bool beaconEnabled, const Timestamp& currentTimestamp);

	private:
		//Variable: m_enabled
		//	Whether the beacon is enabled or disabled.
		bool m_enabled;

		//Variable: m_timestamp
		//	The current <Timestamp> of the beacon.
		Timestamp m_timestamp;

	public:
		//API Function: enabled
		//	Gets whether the beacon is enabled (true) or disabled (false).
		bool enabled();

		//API Function: timestamp;
		//	Gets the current <Timestamp> of the beacon.
		const Timestamp& timestamp();
	};

#ifndef SWIG

	//Class: BaseStation_BeaconStatus
	//	Contains logic for the base station Get Beacon Status command.
	class BaseStation_BeaconStatus
	{
	private:
		BaseStation_BeaconStatus();												//default constructor disabled
		BaseStation_BeaconStatus(const BaseStation_BeaconStatus&);				//copy constructor disabled
		BaseStation_BeaconStatus& operator=(const BaseStation_BeaconStatus&);	//assignement operator disabled

	public:
		//Function: buildCommand
		//	Builds the beacon status command.
		//
		//Returns:
		//	A <ByteStream> containing the base station beacon status command.
		static ByteStream buildCommand();

		//Class: Response
		//	Handles the response to the command
		class Response : public ResponsePattern
		{
		public:
			//Constructor: Response
			//	Creates a get beacon status Response object
			//
			//Parameters:
			//	collector - The <ResponseCollector> used to register and unregister the response
			Response(std::weak_ptr<ResponseCollector> collector);

		private:
			//Variable: m_result
			//	The <BeaconStatus> that holds the result of the command.
			BeaconStatus m_result;

		public:
			//Function: match
			//	Checks if the packet passed in matches either the success or failure response.
			//
			//Parameters:
			//	packet - The <WirelessPacket> to try to match.
			//
			//Returns:
			//	true if the response pattern was found, false otherwise.
			virtual bool match(const WirelessPacket& packet) override;

			//Function: result
			//	Gets the <BeaconStatus> that holds the result of the response.
			BeaconStatus result();

		private:
			//Function: matchSuccessResponse
			//	Checks if the packet passed in matches the success response.
			//
			//Parameters:
			//	packet - The <WirelessPacket> to try to match.
			//
			//Returns:
			//	true if the success response pattern was found, false otherwise
			bool matchSuccessResponse(const WirelessPacket& packet);

			//Function: matchFailResponse
			//	Checks if the packet passed in matches the failure response.
			//
			//Parameters:
			//	packet - The <WirelessPacket> to try to match.
			//
			//Returns:
			//	true if the failure response pattern was found, false otherwise
			bool matchFailResponse(const WirelessPacket& packet);
		};
	};

#endif

}