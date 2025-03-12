/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "NodeFeatures_200series.h"
#include "AvailableSampleRates.h"
#include "AvailableTransmitPowers.h"

namespace mscl
{
    NodeFeatures_200series::NodeFeatures_200series(const NodeInfo& info):
        NodeFeatures(info)
    {
    }

    const WirelessTypes::TransmitPowers NodeFeatures_200series::transmitPowers(WirelessTypes::CommProtocol commProtocol) const
    {
        return AvailableTransmitPowers::get200series(m_nodeInfo, commProtocol);
    }

    const WirelessTypes::TransmitPowers NodeFeatures_200series::transmitPowers(WirelessTypes::RegionCode region, WirelessTypes::CommProtocol commProtocol) const
    {
        //make a NodeInfo object with all the actual node's info, but with the given region instead
        NodeInfo tempInfo(m_nodeInfo.firmwareVersion(), m_nodeInfo.model(), region);

        return AvailableTransmitPowers::get200series(tempInfo, commProtocol);
    }

    const WirelessTypes::SamplingModes NodeFeatures_200series::samplingModes() const
    {
        //build and return the sampling modes that are supported
        WirelessTypes::SamplingModes result;

        result.push_back(WirelessTypes::samplingMode_sync);
        result.push_back(WirelessTypes::samplingMode_syncBurst);
        result.push_back(WirelessTypes::samplingMode_nonSync);
        result.push_back(WirelessTypes::samplingMode_syncEvent);

        //no more support for armed datalogging

        return result;
    }

    const WirelessTypes::DataFormats NodeFeatures_200series::dataFormats() const
    {
        //build and return the data formats that are supported
        WirelessTypes::DataFormats result;
        result.push_back(WirelessTypes::dataFormat_raw_uint16);
        result.push_back(WirelessTypes::dataFormat_raw_uint24);
        result.push_back(WirelessTypes::dataFormat_cal_float);
        return result;
    }

    const WirelessTypes::StorageLimitModes NodeFeatures_200series::storageLimitModes() const
    {
        WirelessTypes::StorageLimitModes modes;

        //don't add any modes if the node doesn't support logged data at all
        if(supportsLoggedData())
        {
            modes.push_back(WirelessTypes::storageLimit_stop);
            modes.push_back(WirelessTypes::storageLimit_overwrite);
        }

        return modes;
    }
}
