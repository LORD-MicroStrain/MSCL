/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "NodeFeatures_200series.h"
#include "AvailableSampleRates.h"

namespace mscl
{
    NodeFeatures_200series::NodeFeatures_200series(const NodeInfo& info):
        NodeFeatures(info)
    {
    }

    WirelessTypes::TransmitPower NodeFeatures_200series::maxTransmitPower(WirelessTypes::RegionCode region, WirelessTypes::CommProtocol commProtocol) const
    {
        if(region == WirelessTypes::region_japan)
        {
            WirelessTypes::TransmitPowers result;

            if(commProtocol == WirelessTypes::commProtocol_lxrs)
            {
                return WirelessTypes::power_16dBm;
            }

            return WirelessTypes::power_12dBm;
        }

        return NodeFeatures::maxTransmitPower(region, commProtocol);
    }

    WirelessTypes::TransmitPower NodeFeatures_200series::minTransmitPower(WirelessTypes::RegionCode region, WirelessTypes::CommProtocol commProtocol) const
    {
        if(region == WirelessTypes::region_japan)
        {
            WirelessTypes::TransmitPowers result;

            if(commProtocol == WirelessTypes::commProtocol_lxrs)
            {
                return WirelessTypes::power_5dBm;
            }

            return WirelessTypes::power_1dBm;
        }

        return NodeFeatures::minTransmitPower(region, commProtocol);
    }

    const WirelessTypes::TransmitPowers NodeFeatures_200series::transmitPowers(WirelessTypes::CommProtocol commProtocol) const
    {
        WirelessTypes::RegionCode region = m_nodeInfo.regionCode();

        //japan has a custom list of transmit powers for 200-series Nodes
        if(region == WirelessTypes::region_japan)
        {
            if(commProtocol == WirelessTypes::commProtocol_lxrs)
            {
                WirelessTypes::TransmitPowers result{
                    WirelessTypes::power_16dBm,
                    WirelessTypes::power_10dBm,
                    WirelessTypes::power_5dBm
                };

                return result;
            }
            else
            {
                WirelessTypes::TransmitPowers result{
                    WirelessTypes::power_12dBm,
                    WirelessTypes::power_5dBm,
                    WirelessTypes::power_1dBm
                };

                return result;
            }
        }

        return NodeFeatures::transmitPowers(commProtocol);
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