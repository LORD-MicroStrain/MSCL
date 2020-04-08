/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "BeaconStatus.h"
#include "WirelessProtocol.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{
    BeaconStatus::BeaconStatus():
        m_enabled(false),
        m_timestamp(0)
    {
    }

    BeaconStatus::BeaconStatus(bool beaconEnabled, const Timestamp& currentTimestamp):
        m_enabled(beaconEnabled),
        m_timestamp(currentTimestamp)
    {
    }

    bool BeaconStatus::enabled()
    {
        return m_enabled;
    }

    const Timestamp& BeaconStatus::timestamp()
    {
        return m_timestamp;
    }
}