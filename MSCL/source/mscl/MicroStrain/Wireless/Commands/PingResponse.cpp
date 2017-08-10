/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "PingResponse.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"

namespace mscl
{
    PingResponse::PingResponse() :
        m_success(false),
        m_nodeRssi(WirelessTypes::UNKNOWN_RSSI),
        m_baseRssi(WirelessTypes::UNKNOWN_RSSI)
    {
    }

    PingResponse::PingResponse(bool success, int16 nodeRssi, int16 baseRssi):
        m_success(success),
        m_nodeRssi(nodeRssi),
        m_baseRssi(baseRssi)
    {
    }

    PingResponse PingResponse::ResponseSuccess(int16 nodeRssi, int16 baseRssi)
    {
        return PingResponse(true, nodeRssi, baseRssi);
    }

    PingResponse PingResponse::ResponseFail()
    {
        return PingResponse(false, WirelessTypes::UNKNOWN_RSSI, WirelessTypes::UNKNOWN_RSSI);
    }

    bool PingResponse::success() const
    {
        return m_success;
    }

    int16 PingResponse::nodeRssi() const
    {
        return m_nodeRssi;
    }

    int16 PingResponse::baseRssi() const
    {
        return m_baseRssi;
    }
}