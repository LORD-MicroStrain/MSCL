/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/Wireless/WirelessTypes.h"

namespace mscl
{
    //Class: AvailableSampleRates
    //    Contains the available sample rates for the Wireless products
    class AvailableSampleRates
    {
    public:
        //Constants: Standard Sample Rates
        //    continuous        - standard continuous sample rates
        //    burst            - standard burst sample rates
        //    armedDatalog    - standard armed datalogging sample rates
        static const WirelessTypes::WirelessSampleRates continuous;
        static const WirelessTypes::WirelessSampleRates burst;
        static const WirelessTypes::WirelessSampleRates armedDatalog;

        //Constants: G-Link-2 Sample Rates
        //    continuous_glink2    - continuous sample rates for the G-Link 2
        //    burst_glink2        - burst sample rates for the G-Link 2
        //    armedDatalog_glink2 - armed datalogging sample rates for the G-Link 2
        static const WirelessTypes::WirelessSampleRates continuous_glink2;
        static const WirelessTypes::WirelessSampleRates burst_glink2;
        static const WirelessTypes::WirelessSampleRates armedDatalog_glink2;

        //Constants: V-Link Sample Rates
        //    burst_vlink - burst sample rates for the V-Link
        //    armedDatalog_vlink - armed datalogging sample rates for the V-Link
        static const WirelessTypes::WirelessSampleRates burst_vlink;
        static const WirelessTypes::WirelessSampleRates armedDatalog_vlink;

        //Constants: V-Link2 Sample Rates
        //    continuous_vlink2 - continuous sample rates for the V-Link2.
        //    burst_vlink2 - burst sample rates for the V-Link
        //    armedDatalog_vlink2 - armed datalogging sample rates for the V-Link
        static const WirelessTypes::WirelessSampleRates continuous_vlink2;
        static const WirelessTypes::WirelessSampleRates burst_vlink2;
        static const WirelessTypes::WirelessSampleRates armedDatalog_vlink2;

        //Constants: IEPE-Link Sample Rates
        //    burst_iepe - burst sample rates for the IEPE-Link
        static const WirelessTypes::WirelessSampleRates burst_iepeLink;

        //Constants: TC-Link SampleRates
        //    continuous_tclink - continuous sample rates for the TC-Link nodes.
        static const WirelessTypes::WirelessSampleRates continuous_tclink;

        //Constants: TC-Link-1ch SampleRates
        //    continuous_tclink1ch - continuous sample rates for the TC-Link 1-ch node.
        static const WirelessTypes::WirelessSampleRates continuous_tclink1ch;

        //Constants: ENV-Link SampleRates
        //    continuous_envlink - continuous sample rates for the ENV-Link nodes.
        static const WirelessTypes::WirelessSampleRates continuous_envlink;

        //Constants: SHM-Link2 SampleRates
        //    continuous_envlink - continuous sample rates for the SHM-Link 2 nodes.
        static const WirelessTypes::WirelessSampleRates continuous_shmLink2;

        //Constants: CF-Bearing-Temp-Link SampleRates
        //    continuous_envlink - continuous sample rates for the CF-Bearing-Temp-Link node.
        static const WirelessTypes::WirelessSampleRates continuous_cfBearing;

        //Constants: Blade-Impact-Link Sample Rates
        //    continuous_blade   - continuous sample rates for the Blade-Impact-Link
        //    burst_blade        - burst sample rates for the Blade-Impact-Link
        //    event_blade        - event trigger sample rates for the Blade-Impact-Link
        static const WirelessTypes::WirelessSampleRates continuous_blade;
        static const WirelessTypes::WirelessSampleRates burst_blade;
        static const WirelessTypes::WirelessSampleRates event_blade;
    };
}