/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

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
