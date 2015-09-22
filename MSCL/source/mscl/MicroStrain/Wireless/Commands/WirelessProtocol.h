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
#pragma once

#include <functional>
#include <memory>
#include "mscl/Timestamp.h"
#include "BaseStation_BeaconStatus.h"

namespace mscl
{
	//forward declarations
	class BaseStation_Impl;

	//Class: WirelessProtocol
	//	Class containing protocol information for a device.
	class WirelessProtocol
	{
		friend class BaseStation_Impl;
		friend class NodeEeprom;

	private:
		WirelessProtocol();										//default constructor disabled
		WirelessProtocol(const WirelessProtocol&);				//copy constructor disabled
		WirelessProtocol& operator=(const WirelessProtocol&);	//assignment operator disabled

		//Variable: m_pingBase
		//	The function pointer for the Ping BaseStation protocol command.
		std::function<bool(BaseStation_Impl*)> m_pingBase;

		//Variable: m_readBaseEeprom
		//	The function pointer for the Read BaseStation EEPROM protocol command.
		std::function<bool(BaseStation_Impl*, uint16, uint16&)> m_readBaseEeprom;

		//Variable: m_writeBaseEeprom
		//	The function pointer for the Write BaseStation EEPROM protocol command.
		std::function<bool(BaseStation_Impl*, uint16, uint16)> m_writeBaseEeprom;

		//Variable: m_enableBeacon
		//	The function pointer for the Enable Beacon protocol command.
		std::function<Timestamp(BaseStation_Impl*, uint32)> m_enableBeacon;

		//Variable: m_beaconStatus
		//	The function pointer for the Beacon Status protocol command.
		std::function<BeaconStatus(BaseStation_Impl*)> m_beaconStatus;

		//Variable: m_readNodeEeprom
		//	The function pointer for the Read Node Eeprom protocol command.
		std::function<bool(BaseStation_Impl*, NodeAddress, uint16, uint16&)> m_readNodeEeprom;

		//Variable: m_writeNodeEeprom
		//	The function pointer for the Write Node Eeprom protocol command.
		std::function<bool(BaseStation_Impl*, NodeAddress, uint16, uint16)> m_writeNodeEeprom;

		//Variable: m_pageDownload
		//	The function pointer for the Node Page Download protocol command.
		std::function<bool(BaseStation_Impl*, NodeAddress, uint16, ByteStream&)> m_pageDownload;

	public:
		//Constant: BASE_STATION_ADDRESS
		//	The address of our generic Base Station.
		static const uint16 BASE_STATION_ADDRESS = 0x1234;

		//Function: v1_0
		//	Static function to create a WirelessProtocol with version 1.0.
		static std::unique_ptr<WirelessProtocol> v1_0();

		//Function: v1_1
		//	Static function to create a WirelessProtocol with version 1.1.
		static std::unique_ptr<WirelessProtocol> v1_1();
	};
}