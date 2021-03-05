/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

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
        //    continuous    - standard continuous sample rates
        //    burst         - standard burst sample rates
        //    armedDatalog  - standard armed datalogging sample rates
        //    derivedOnly   - standard sample rates when derived only mode is active
        static const WirelessTypes::WirelessSampleRates continuous;
        static const WirelessTypes::WirelessSampleRates burst;
        static const WirelessTypes::WirelessSampleRates armedDatalog;
        static const WirelessTypes::WirelessSampleRates derivedOnly;

        //Constants: V-Link-200 Sample Rates
        //  continuous_nonSync_vlink200 - standard continuous NonSync sample rates
        //  continuous_sync_vlink200    - standard continuous Sync sample rates
        //  continuous_log_vlink200     - standard continuous Log Only sample rates
        //  burst_vlink200              - standard burst sample rates
        static const WirelessTypes::WirelessSampleRates continuous_nonSync_vlink200;
        static const WirelessTypes::WirelessSampleRates continuous_sync_vlink200;
        static const WirelessTypes::WirelessSampleRates continuous_log_vlink200;
        static const WirelessTypes::WirelessSampleRates burst_vlink200;

        //Constants: G-Link-200 Sample Rates
        //  continuous_nonSync_glink200 - continuous NonSync sample rates for the G-Link-200
        //  continuous_sync_glink200    - continuous Sync sample rates for the G-Link-200
        //  continuous_log_glink200     - continuous Log Only sample rates for the G-Link-200
        //  burst_glink200              - burst sample rates for the G-Link-200
        //  derivedOnly_glink200        - derived only sample rates for the G-Link-200
        static const WirelessTypes::WirelessSampleRates continuous_nonSync_glink200;
        static const WirelessTypes::WirelessSampleRates continuous_sync_glink200;
        static const WirelessTypes::WirelessSampleRates continuous_log_glink200;
        static const WirelessTypes::WirelessSampleRates burst_glink200;
        static const WirelessTypes::WirelessSampleRates derivedOnly_glink200;

        //Constants: G-Link-200-R Sample Rates
        //  continuous_nonSync_glink200r - continuous NonSync sample rates for the G-Link-200-R
        //  continuous_sync_glink200r    - continuous Sync sample rates for the G-Link-200-R
        //  continuous_log_glink200r     - continuous Log Only sample rates for the G-Link-200-R
        static const WirelessTypes::WirelessSampleRates continuous_nonSync_glink200r;
        static const WirelessTypes::WirelessSampleRates continuous_sync_glink200r;
        static const WirelessTypes::WirelessSampleRates continuous_log_glink200r;

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

        //Constants: TC-Link-200 SampleRates
        //    continuous_tclink1ch - continuous sample rates for the TC-Link-200 node.
        static const WirelessTypes::WirelessSampleRates continuous_tclink200;
        
        //Constants: RTD-Link-200 SampleRates
        //    continuous_rtdlink200 - continuous sample rates for the RTD-Link-200 node.
        static const WirelessTypes::WirelessSampleRates continuous_rtdlink200;

        //Constants: ENV-Link SampleRates
        //    continuous_envlink - continuous sample rates for the ENV-Link nodes.
        static const WirelessTypes::WirelessSampleRates continuous_envlink;

        static const WirelessTypes::WirelessSampleRates continuous_sglink200;
        static const WirelessTypes::WirelessSampleRates burst_sglink200;

        //Constants: SHM-Link2 SampleRates
        //    continuous_shmLink2 - continuous sample rates for the SHM-Link nodes.
        static const WirelessTypes::WirelessSampleRates continuous_shmLink2;
        static const WirelessTypes::WirelessSampleRates continuous_shmLink2_2;
        static const WirelessTypes::WirelessSampleRates continuous_shmLink201;

        //Constants: CF-Bearing-Temp-Link SampleRates
        //    continuous_cfBearing - continuous sample rates for the CF-Bearing-Temp-Link node.
        static const WirelessTypes::WirelessSampleRates continuous_cfBearing;

        //Constants: Wireless Impact Sensor Sample Rates
        //    continuous_nonSync_impact - continuous non-sync sample rates for the Wireless Impact Sensor
        //    continuous_sync_impact    - continuous sync sample rates for the Wireless Impact Sensor
        //    burst_impact              - burst sample rates for the Wireless Impact Sensor
        static const WirelessTypes::WirelessSampleRates continuous_nonSync_impact;
        static const WirelessTypes::WirelessSampleRates continuous_sync_impact;
        static const WirelessTypes::WirelessSampleRates burst_impact;
    };
}