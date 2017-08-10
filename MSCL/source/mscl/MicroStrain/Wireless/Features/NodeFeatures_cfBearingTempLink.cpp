/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "NodeFeatures_cfBearingTempLink.h"

#include "mscl/Exceptions.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "AvailableSampleRates.h"

namespace mscl
{
    NodeFeatures_cfBearing::NodeFeatures_cfBearing(const NodeInfo& info) :
        NodeFeatures(info)
    {
        //Channels
        m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_temperature, "Temperature 1");
        m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_temperature, "Temperature 2");
    }

    const WirelessTypes::SamplingModes NodeFeatures_cfBearing::samplingModes() const
    {
        //build and return the sampling modes that are supported
        WirelessTypes::SamplingModes result;

        result.push_back(WirelessTypes::samplingMode_nonSync);

        //no support for sync
        //no support for burst
        //no support for armed datalogging

        return result;
    }

    const WirelessTypes::DataCollectionMethods NodeFeatures_cfBearing::dataCollectionMethods() const
    {
        //build and return the data collection methods that are supported
        WirelessTypes::DataCollectionMethods result;
        result.push_back(WirelessTypes::collectionMethod_transmitOnly);
        return result;
    }

    const WirelessTypes::DataFormats NodeFeatures_cfBearing::dataFormats() const
    {
        //build and return the data formats that are supported
        WirelessTypes::DataFormats result;

        result.push_back(WirelessTypes::dataFormat_cal_float);

        //no support for uint16
        
        return result;
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures_cfBearing::sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const
    {
        //the list of sample rates varies for each sampling mode
        switch(samplingMode)
        {
            case WirelessTypes::samplingMode_nonSync:
                return AvailableSampleRates::continuous_cfBearing;

            default:
                throw Error_NotSupported("The sampling mode is not supported by this Node");
        }
    }
}