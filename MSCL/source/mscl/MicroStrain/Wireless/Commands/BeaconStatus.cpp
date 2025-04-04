/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Commands/BeaconStatus.h"

namespace mscl
{
    BeaconStatus::BeaconStatus() :
        m_enabled(false),
        m_timestamp(0)
    {}

    BeaconStatus::BeaconStatus(bool beaconEnabled, const Timestamp& currentTimestamp) :
        m_enabled(beaconEnabled),
        m_timestamp(currentTimestamp)
    {}

    bool BeaconStatus::enabled()
    {
        return m_enabled;
    }

    const Timestamp& BeaconStatus::timestamp()
    {
        return m_timestamp;
    }
} // namespace mscl
