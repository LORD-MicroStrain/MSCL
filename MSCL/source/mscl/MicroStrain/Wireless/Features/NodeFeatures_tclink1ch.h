/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "NodeFeatures.h"

namespace mscl
{
    //Class: NodeFeatures_tclink1ch
    //    Contains information on features for the TC-Link 1CH Node.
    class NodeFeatures_tclink1ch : public NodeFeatures
    {
    public:
        virtual ~NodeFeatures_tclink1ch() {};

        //Constructor: NodeFeatures_tclink1ch
        //    Creates a NodeFeatures_tclink1ch object.
        NodeFeatures_tclink1ch(const NodeInfo& info);

        virtual const WirelessTypes::SamplingModes samplingModes() const override;

        virtual const WirelessTypes::DataFormats dataFormats() const override;

        virtual const WirelessTypes::WirelessSampleRates sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;

        virtual WirelessTypes::SettlingTime maxFilterSettlingTime(const SampleRate& rate) const override;

        virtual WirelessTypes::WirelessSampleRate maxSampleRateForSettlingTime(WirelessTypes::SettlingTime filterSettlingTime, WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const override;
    };
}