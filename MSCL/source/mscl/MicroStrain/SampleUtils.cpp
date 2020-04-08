/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "SampleUtils.h"
#include "mscl/Exceptions.h"

namespace mscl
{
    //build the sample rate map
    const std::map<SampleRate, WirelessTypes::WirelessSampleRate> SampleUtils::WIRELESS_SAMPLE_RATE_MAP(
    {
        {SampleRate::Hertz(104170), WirelessTypes::sampleRate_104170Hz},
        {SampleRate::Hertz(78125), WirelessTypes::sampleRate_78125Hz},
        {SampleRate::Hertz(62500), WirelessTypes::sampleRate_62500Hz},
        {SampleRate::Hertz(25000), WirelessTypes::sampleRate_25000Hz},
        {SampleRate::Hertz(12500), WirelessTypes::sampleRate_12500Hz},
        {SampleRate::Hertz(3200), WirelessTypes::sampleRate_3200Hz},
        {SampleRate::Hertz(1600), WirelessTypes::sampleRate_1600Hz},
        {SampleRate::Hertz(800), WirelessTypes::sampleRate_800Hz},
        {SampleRate::Hertz(300), WirelessTypes::sampleRate_300Hz},

        {SampleRate::KiloHertz(1), WirelessTypes::sampleRate_1kHz},
        {SampleRate::KiloHertz(2), WirelessTypes::sampleRate_2kHz},
        {SampleRate::KiloHertz(3), WirelessTypes::sampleRate_3kHz},
        {SampleRate::KiloHertz(4), WirelessTypes::sampleRate_4kHz},
        {SampleRate::KiloHertz(5), WirelessTypes::sampleRate_5kHz},
        {SampleRate::KiloHertz(6), WirelessTypes::sampleRate_6kHz},
        {SampleRate::KiloHertz(7), WirelessTypes::sampleRate_7kHz},
        {SampleRate::KiloHertz(8), WirelessTypes::sampleRate_8kHz},
        {SampleRate::KiloHertz(9), WirelessTypes::sampleRate_9kHz},
        {SampleRate::KiloHertz(10), WirelessTypes::sampleRate_10kHz},
        {SampleRate::KiloHertz(20), WirelessTypes::sampleRate_20kHz},
        {SampleRate::KiloHertz(30), WirelessTypes::sampleRate_30kHz},
        {SampleRate::KiloHertz(40), WirelessTypes::sampleRate_40kHz},
        {SampleRate::KiloHertz(50), WirelessTypes::sampleRate_50kHz},
        {SampleRate::KiloHertz(60), WirelessTypes::sampleRate_60kHz},
        {SampleRate::KiloHertz(70), WirelessTypes::sampleRate_70kHz},
        {SampleRate::KiloHertz(80), WirelessTypes::sampleRate_80kHz},
        {SampleRate::KiloHertz(90), WirelessTypes::sampleRate_90kHz},
        {SampleRate::KiloHertz(100), WirelessTypes::sampleRate_100kHz},

        {SampleRate::Hertz(8192), WirelessTypes::sampleRate_8192Hz},
        {SampleRate::Hertz(4096), WirelessTypes::sampleRate_4096Hz},
        {SampleRate::Hertz(2048), WirelessTypes::sampleRate_2048Hz},
        {SampleRate::Hertz(1024), WirelessTypes::sampleRate_1024Hz},
        {SampleRate::Hertz(887), WirelessTypes::sampleRate_887Hz},
        {SampleRate::Hertz(512), WirelessTypes::sampleRate_512Hz},
        {SampleRate::Hertz(256), WirelessTypes::sampleRate_256Hz},
        {SampleRate::Hertz(128), WirelessTypes::sampleRate_128Hz},
        {SampleRate::Hertz(64), WirelessTypes::sampleRate_64Hz},
        {SampleRate::Hertz(32), WirelessTypes::sampleRate_32Hz},
        {SampleRate::Hertz(16), WirelessTypes::sampleRate_16Hz},
        {SampleRate::Hertz(8), WirelessTypes::sampleRate_8Hz},
        {SampleRate::Hertz(4), WirelessTypes::sampleRate_4Hz},
        {SampleRate::Hertz(2), WirelessTypes::sampleRate_2Hz},
        {SampleRate::Hertz(1), WirelessTypes::sampleRate_1Hz},

        {SampleRate::Seconds(2), WirelessTypes::sampleRate_2Sec},
        {SampleRate::Seconds(5), WirelessTypes::sampleRate_5Sec},
        {SampleRate::Seconds(10), WirelessTypes::sampleRate_10Sec},
        {SampleRate::Seconds(30), WirelessTypes::sampleRate_30Sec},
        {SampleRate::Seconds(60), WirelessTypes::sampleRate_1Min},
        {SampleRate::Seconds(2 * 60), WirelessTypes::sampleRate_2Min},
        {SampleRate::Seconds(5 * 60), WirelessTypes::sampleRate_5Min},
        {SampleRate::Seconds(10 * 60), WirelessTypes::sampleRate_10Min},
        {SampleRate::Seconds(30 * 60), WirelessTypes::sampleRate_30Min},
        {SampleRate::Seconds(60 * 60), WirelessTypes::sampleRate_60Min},

        {SampleRate::Seconds(60 * 60 * 24), WirelessTypes::sampleRate_24Hours}
    });

    SampleRate SampleUtils::convertToSampleRate(WirelessTypes::WirelessSampleRate rate)
    {
        switch(rate)
        {
        case WirelessTypes::sampleRate_104170Hz:        return SampleRate::Hertz(104170);
        case WirelessTypes::sampleRate_78125Hz:         return SampleRate::Hertz(78125);
        case WirelessTypes::sampleRate_62500Hz:         return SampleRate::Hertz(62500);
        case WirelessTypes::sampleRate_25000Hz:         return SampleRate::Hertz(25000);
        case WirelessTypes::sampleRate_12500Hz:         return SampleRate::Hertz(12500);

        case WirelessTypes::sampleRate_3200Hz:          return SampleRate::Hertz(3200);
        case WirelessTypes::sampleRate_1600Hz:          return SampleRate::Hertz(1600);
        case WirelessTypes::sampleRate_800Hz:           return SampleRate::Hertz(800);
        case WirelessTypes::sampleRate_300Hz:           return SampleRate::Hertz(300);

        case WirelessTypes::sampleRate_1kHz:            return SampleRate::KiloHertz(1);
        case WirelessTypes::sampleRate_2kHz:            return SampleRate::KiloHertz(2);
        case WirelessTypes::sampleRate_3kHz:            return SampleRate::KiloHertz(3);
        case WirelessTypes::sampleRate_4kHz:            return SampleRate::KiloHertz(4);
        case WirelessTypes::sampleRate_5kHz:            return SampleRate::KiloHertz(5);
        case WirelessTypes::sampleRate_6kHz:            return SampleRate::KiloHertz(6);
        case WirelessTypes::sampleRate_7kHz:            return SampleRate::KiloHertz(7);
        case WirelessTypes::sampleRate_8kHz:            return SampleRate::KiloHertz(8);
        case WirelessTypes::sampleRate_9kHz:            return SampleRate::KiloHertz(9);
        case WirelessTypes::sampleRate_10kHz:           return SampleRate::KiloHertz(10);
        case WirelessTypes::sampleRate_20kHz:           return SampleRate::KiloHertz(20);
        case WirelessTypes::sampleRate_30kHz:           return SampleRate::KiloHertz(30);
        case WirelessTypes::sampleRate_40kHz:           return SampleRate::KiloHertz(40);
        case WirelessTypes::sampleRate_50kHz:           return SampleRate::KiloHertz(50);
        case WirelessTypes::sampleRate_60kHz:           return SampleRate::KiloHertz(60);
        case WirelessTypes::sampleRate_70kHz:           return SampleRate::KiloHertz(70);
        case WirelessTypes::sampleRate_80kHz:           return SampleRate::KiloHertz(80);
        case WirelessTypes::sampleRate_90kHz:           return SampleRate::KiloHertz(90);
        case WirelessTypes::sampleRate_100kHz:          return SampleRate::KiloHertz(100);
    
        case WirelessTypes::sampleRate_8192Hz:          return SampleRate::Hertz(8192);
        case WirelessTypes::sampleRate_4096Hz:          return SampleRate::Hertz(4096);
        case WirelessTypes::sampleRate_2048Hz:          return SampleRate::Hertz(2048);
        case WirelessTypes::sampleRate_1024Hz:          return SampleRate::Hertz(1024);
        case WirelessTypes::sampleRate_887Hz:           return SampleRate::Hertz(887);
        case WirelessTypes::sampleRate_512Hz:           return SampleRate::Hertz(512);
        case WirelessTypes::sampleRate_256Hz:           return SampleRate::Hertz(256);
        case WirelessTypes::sampleRate_128Hz:           return SampleRate::Hertz(128);
        case WirelessTypes::sampleRate_64Hz:            return SampleRate::Hertz(64);
        case WirelessTypes::sampleRate_32Hz:            return SampleRate::Hertz(32);
        case WirelessTypes::sampleRate_16Hz:            return SampleRate::Hertz(16);
        case WirelessTypes::sampleRate_8Hz:             return SampleRate::Hertz(8);
        case WirelessTypes::sampleRate_4Hz:             return SampleRate::Hertz(4);
        case WirelessTypes::sampleRate_2Hz:             return SampleRate::Hertz(2);
        case WirelessTypes::sampleRate_1Hz:             return SampleRate::Hertz(1);
    
        case WirelessTypes::sampleRate_2Sec:            return SampleRate::Seconds(2);
        case WirelessTypes::sampleRate_5Sec:            return SampleRate::Seconds(5);
        case WirelessTypes::sampleRate_10Sec:           return SampleRate::Seconds(10);
        case WirelessTypes::sampleRate_30Sec:           return SampleRate::Seconds(30);
        case WirelessTypes::sampleRate_1Min:            return SampleRate::Seconds(60);
        case WirelessTypes::sampleRate_2Min:            return SampleRate::Seconds(120);
        case WirelessTypes::sampleRate_5Min:            return SampleRate::Seconds(300);
        case WirelessTypes::sampleRate_10Min:           return SampleRate::Seconds(600);
        case WirelessTypes::sampleRate_30Min:           return SampleRate::Seconds(1800);
        case WirelessTypes::sampleRate_60Min:           return SampleRate::Seconds(3600);
        case WirelessTypes::sampleRate_24Hours:         return SampleRate::Seconds(86400);

        default:
            throw Error_UnknownSampleRate();
        }
    }

    SampleRate SampleUtils::convertToSampleRate(uint16 eepromVal)
    {
        //try to cast to a SampleRateOption and convert
        return convertToSampleRate(static_cast<WirelessTypes::WirelessSampleRate>(eepromVal));
    }

    WirelessTypes::WirelessSampleRate SampleUtils::convertFromSampleRate(const SampleRate& rate)
    {
        //find the requested sample rate in the map
        std::map<SampleRate, WirelessTypes::WirelessSampleRate>::const_iterator itr = WIRELESS_SAMPLE_RATE_MAP.find(rate);

        //check that the sample rate exists in the map
        if(itr == WIRELESS_SAMPLE_RATE_MAP.end())
        {
            //unknown sample rate
            throw Error_UnknownSampleRate();
        }

        //return the eeprom value for this sample rate
        return itr->second;
    }
}