/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
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
	class WirelessPacket;

	//API Class: AutoCalResult
	//	Abstract base class for AutoCal result classes.
	class AutoCalResult
	{
		friend class BaseStation_Impl;

	public:
		AutoCalResult();
		virtual ~AutoCalResult() {};

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
		virtual ~AutoCalResult_shmLink() {};

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
}