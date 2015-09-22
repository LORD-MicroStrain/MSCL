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
#include "stdafx.h"
#include "WirelessProtocol.h"
#include "mscl/MicroStrain/Wireless/BaseStation_Impl.h"

namespace mscl
{
	WirelessProtocol::WirelessProtocol()
	{
	}

	std::unique_ptr<WirelessProtocol> WirelessProtocol::v1_0()
	{
		std::unique_ptr<WirelessProtocol> result(new WirelessProtocol());

		//BaseStation Commands
		result->m_pingBase			= std::mem_fn(&BaseStation_Impl::ping_v1);
		result->m_readBaseEeprom	= std::mem_fn(&BaseStation_Impl::read_v1);
		result->m_writeBaseEeprom	= std::mem_fn(&BaseStation_Impl::write_v1);
		result->m_enableBeacon		= std::mem_fn(&BaseStation_Impl::enableBeacon_v1);
		result->m_beaconStatus		= nullptr;

		//Node Commands
		result->m_readNodeEeprom	= std::mem_fn(&BaseStation_Impl::node_readEeprom_v1);
		result->m_writeNodeEeprom	= std::mem_fn(&BaseStation_Impl::node_writeEeprom_v1);
		result->m_pageDownload		= std::mem_fn(&BaseStation_Impl::node_pageDownload_v1);

		return result;
	}

	std::unique_ptr<WirelessProtocol> WirelessProtocol::v1_1()
	{
		std::unique_ptr<WirelessProtocol> result(new WirelessProtocol());

		//BaseStation Commands
		result->m_pingBase			= std::mem_fn(&BaseStation_Impl::ping_v2);
		result->m_readBaseEeprom	= std::mem_fn(&BaseStation_Impl::read_v2);
		result->m_writeBaseEeprom	= std::mem_fn(&BaseStation_Impl::write_v2);
		result->m_enableBeacon		= std::mem_fn(&BaseStation_Impl::enableBeacon_v2);
		result->m_beaconStatus		= std::mem_fn(&BaseStation_Impl::beaconStatus_v1);

		//Node Commands
		result->m_readNodeEeprom	= std::mem_fn(&BaseStation_Impl::node_readEeprom_v2);
		result->m_writeNodeEeprom	= std::mem_fn(&BaseStation_Impl::node_writeEeprom_v2);
		result->m_pageDownload		= std::mem_fn(&BaseStation_Impl::node_pageDownload_v1);

		return result;
	}
}