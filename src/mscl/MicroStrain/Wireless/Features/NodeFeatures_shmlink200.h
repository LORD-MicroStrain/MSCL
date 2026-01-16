/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Features/NodeFeatures_200series.h"

namespace mscl
{
    //Class: NodeFeatures_shmlink200
    //    Contains information on features for the SHM-Link 200 node.
    class NodeFeatures_shmlink200 : public NodeFeatures_200series
    {
        NodeFeatures_shmlink200();    //disabled default constructor

    public:
        ~NodeFeatures_shmlink200() override = default;

        //Constructor: NodeFeatures_shmlink200
        //    Creates a NodeFeatures_shmlink200 object.
        NodeFeatures_shmlink200(const NodeInfo& info);

        const WirelessTypes::DataFormats dataFormats() const final;

        const WirelessTypes::SamplingModes samplingModes() const final;

        const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        bool supportsHistogramConfig() const final;

        bool supportsHistogramRateConfig() const final;

        bool supportsHistogramEnableConfig() const override;

        bool supportsActivitySense() const final;

        bool supportsAutoCal_shm() const override;

        bool supportsSensorDelayConfig() const override;

        bool supportsSensorDelayAlwaysOn() const override;

        const WirelessTypes::WirelessSampleRates histogramTransmitRates() const final;
    };
} // namespace mscl
