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
#include "BaseStationButton.h"

namespace mscl
{
	BaseStationButton::BaseStationButton():
		m_command(btn_disabled),
		m_nodeAddress(0)
	{
	}

	BaseStationButton::BaseStationButton(Command cmd, uint16 nodeAddress):
		m_command(cmd),
		m_nodeAddress(nodeAddress)
	{
	}

	BaseStationButton::Command BaseStationButton::command() const
	{
		return m_command;
	}

	void BaseStationButton::command(Command cmd)
	{
		m_command = cmd;
	}

	uint16 BaseStationButton::nodeAddress() const
	{
		return m_nodeAddress;
	}

	void BaseStationButton::nodeAddress(uint16 address)
	{
		m_nodeAddress = address;
	}
}