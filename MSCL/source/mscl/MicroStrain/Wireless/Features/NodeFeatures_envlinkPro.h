/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_envlinkPro
    //    Contains information on features for the ENV-Link Pro Node.
    class NodeFeatures_envlinkPro : public NodeFeatures
    {
    public:
        virtual ~NodeFeatures_envlinkPro() {};

        //Constructor: NodeFeatures_envlinkPro
        //    Creates a NodeFeatures_envlinkPro object.
        NodeFeatures_envlinkPro(const NodeInfo& info);

        virtual bool supportsSensorDelayConfig() const override;

        virtual const WirelessTypes::SamplingModes samplingModes() const override;

        virtual const WirelessTypes::DataFormats dataFormats() const override;

        virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        virtual WirelessTypes::SettlingTime maxFilterSettlingTime(const SampleRate& rate) const override;

        virtual WirelessTypes::WirelessSampleRate maxSampleRateForSettlingTime(WirelessTypes::SettlingTime filterSettlingTime, WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;
    };
}