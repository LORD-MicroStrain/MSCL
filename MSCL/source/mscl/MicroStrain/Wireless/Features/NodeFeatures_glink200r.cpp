/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "NodeFeatures_glink200r.h"

#include "mscl/Exceptions.h"
#include "AvailableSampleRates.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"

namespace mscl
{
    NodeFeatures_glink200r::NodeFeatures_glink200r(const NodeInfo& info):
        NodeFeatures_200series(info)
    {
        addCalCoeffChannelGroup(1, "Acceleration X", NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
        addCalCoeffChannelGroup(2, "Acceleration Y", NodeEepromMap::CH_ACTION_SLOPE_2, NodeEepromMap::CH_ACTION_ID_2);
        addCalCoeffChannelGroup(3, "Acceleration Z", NodeEepromMap::CH_ACTION_SLOPE_3, NodeEepromMap::CH_ACTION_ID_3);

        //Channels
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_acceleration, "Acceleration X", 20);
        m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_acceleration, "Acceleration Y", 20);
        m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_acceleration, "Acceleration Z", 20);
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_glink200r::sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const
    {
        //the list of sample rates varies for each sampling mode
        switch(samplingMode)
        {
        case WirelessTypes::samplingMode_nonSync:
            if(dataCollectionMethod == WirelessTypes::collectionMethod_logOnly)
            {
                return AvailableSampleRates::continuous_log_glink200r;
            }
            else
            {
                return AvailableSampleRates::continuous_nonSync_glink200r;
            }

        case WirelessTypes::samplingMode_sync:
        case WirelessTypes::samplingMode_syncEvent:
            if(dataCollectionMethod == WirelessTypes::collectionMethod_logOnly) 
            {
                return AvailableSampleRates::continuous_log_glink200r;
            }
            else
            {
                return AvailableSampleRates::continuous_sync_glink200r;
            }

        case WirelessTypes::samplingMode_syncBurst:
        default:
            throw Error_NotSupported("The sampling mode is not supported by this Node");
        }
    }

    const WirelessTypes::SamplingModes NodeFeatures_glink200r::samplingModes() const
    {
        WirelessTypes::SamplingModes result;
        result.push_back(WirelessTypes::samplingMode_sync);
        result.push_back(WirelessTypes::samplingMode_nonSync);
        result.push_back(WirelessTypes::samplingMode_syncEvent);

        return result;
    }

    const WirelessTypes::DataFormats NodeFeatures_glink200r::dataFormats() const
    {
        //build and return the data formats that are supported
        WirelessTypes::DataFormats result;
        result.push_back(WirelessTypes::dataFormat_raw_int16);
        result.push_back(WirelessTypes::dataFormat_raw_int24);
        result.push_back(WirelessTypes::dataFormat_cal_float);

        return result;
    }

    const WirelessTypes::CfcFilters NodeFeatures_glink200r::cfcFilters() const
    {
        //build and return the data formats that are supported
        WirelessTypes::CfcFilters result;
        result.push_back(WirelessTypes::cfc_10);
        result.push_back(WirelessTypes::cfc_21);
        result.push_back(WirelessTypes::cfc_60);

        return result;
    }
}