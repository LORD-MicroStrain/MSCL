/*****************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the included
LICENSE.txt file for a copy of the full GNU General Public License.
*****************************************************************************/
#pragma once

#include "mscl/MicroStrain/Wireless/WirelessTypes.h"

namespace mscl
{
	//Class: AvailableSampleRates
	//	Contains the available sample rates for the Wireless products
	class AvailableSampleRates
	{
	public:
		//Constants: Standard Sample Rates
		//	continuous		- standard continuous sample rates
		//	burst			- standard burst sample rates
		//	armedDatalog	- standard armed datalogging sample rates
		static const WirelessTypes::WirelessSampleRates continuous;
		static const WirelessTypes::WirelessSampleRates burst;
		static const WirelessTypes::WirelessSampleRates armedDatalog;

		//Constants: G-Link-2 Sample Rates
		//	continuous_glink2	- continuous sample rates for the G-Link 2
		//	burst_glink2		- burst sample rates for the G-Link 2
		//	armedDatalog_glink2 - armed datalogging sample rates for the G-Link 2
		static const WirelessTypes::WirelessSampleRates continuous_glink2;
		static const WirelessTypes::WirelessSampleRates burst_glink2;
		static const WirelessTypes::WirelessSampleRates armedDatalog_glink2;

		//Constants: V-Link Sample Rates
		//	burst_vlink - burst sample rates for the V-Link
		//	armedDatalog_vlink - armed datalogging sample rates for the V-Link
		static const WirelessTypes::WirelessSampleRates burst_vlink;
		static const WirelessTypes::WirelessSampleRates armedDatalog_vlink;

		//Constants: IEPE-Link Sample Rates
		//	burst_iepe - burst sample rates for the IEPE-Link
		static const WirelessTypes::WirelessSampleRates burst_iepeLink;

		//Constants: TC-Link SampleRates
		//	continuous_tclink - continuous sample rates for the TC-Link nodes.
		static const WirelessTypes::WirelessSampleRates continuous_tclink;

		//Constants: TC-Link-1ch SampleRates
		//	continuous_tclink1ch - continuous sample rates for the TC-Link 1-ch node.
		static const WirelessTypes::WirelessSampleRates continuous_tclink1ch;

		//Constants: ENV-Link SampleRates
		//	continuous_envlink - continuous sample rates for the ENV-Link nodes.
		static const WirelessTypes::WirelessSampleRates continuous_envlink;
	};
}