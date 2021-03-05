/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "SampleRate.h"
#include "mscl/Types.h"
#include "Wireless/WirelessTypes.h"
#include <map>

namespace mscl
{
    //Title: SampleUtils

    //Class: SampleUtils
    //    Contains utilities/functions related to sampling
    class SampleUtils
    {
    private:
        //Variable: WIRELESS_SAMPLE_RATE_MAP
        //    A static map of <SampleRate> objects to their <WirelessTypes::WirelessSampleRate> (eeprom value) equivalent
        static const std::map<SampleRate, WirelessTypes::WirelessSampleRate> WIRELESS_SAMPLE_RATE_MAP;

    public:
        //Function: convertToSampleRate
        //    Converts a <WirelessTypes::WirelessSampleRate> enum to its corresponding <SampleRate>
        //
        //Parameters:
        //    rate - The <WirelessTypes::WirelessSampleRate> enum to find the <SampleRate> of
        //
        //Returns:
        //    A <SampleRate> corresponding to the passed in rate enum
        //
        //Exceptions:
        //    - <Error_UnknownSampleRate>: The given <WirelessTypes::WirelessSampleRate> is invalid or unknown.
        static SampleRate convertToSampleRate(WirelessTypes::WirelessSampleRate rate);

        //Function: convertToSampleRate
        //    Converts a value from eeprom to its corresponding <SampleRate>
        //
        //Parameters:
        //    eepromVal - The value that represents the sample rate in eeprom to convert to a <SampleRate>
        //
        //Returns:
        //    A <SampleRate> corresponding to the passed in rate eeprom value
        //
        //Exceptions:
        //    - <Error_UnknownSampleRate>: The given eeprom values does not correspond with a SampleRate.
        static SampleRate convertToSampleRate(uint16 eepromVal);

        //Function: convertFromSampleRate
        //    Converts a <SampleRate> object to its <WirelessTypes::WirelessSampleRate> (eeprom value) equivalent
        //
        //Parameters:
        //    rate - The <SampleRate> to get the eeprom value for
        //
        //Returns:
        //    The <WirelessTypes::WirelessSampleRate> that is associated with the given <SampleRate>
        //
        //Exceptions:
        //    - <Error_UnknownSampleRate>: The given <SampleRate> does not match a <WirelessTypes::WirelessSampleRate>.
        static WirelessTypes::WirelessSampleRate convertFromSampleRate(const SampleRate& rate);
    };

}