/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "AvailableSampleRates.h"

namespace mscl
{
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //NOTE: These sample rates must always been in order from fastest to slowest rate.
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous = {
            {WirelessTypes::sampleRate_512Hz},
            {WirelessTypes::sampleRate_256Hz},
            {WirelessTypes::sampleRate_128Hz},
            {WirelessTypes::sampleRate_64Hz},
            {WirelessTypes::sampleRate_32Hz},
            {WirelessTypes::sampleRate_16Hz},
            {WirelessTypes::sampleRate_8Hz},
            {WirelessTypes::sampleRate_4Hz},
            {WirelessTypes::sampleRate_2Hz},
            {WirelessTypes::sampleRate_1Hz},
            {WirelessTypes::sampleRate_2Sec},
            {WirelessTypes::sampleRate_5Sec},
            {WirelessTypes::sampleRate_10Sec},
            {WirelessTypes::sampleRate_30Sec},
            {WirelessTypes::sampleRate_1Min},
            {WirelessTypes::sampleRate_2Min},
            {WirelessTypes::sampleRate_5Min},
            {WirelessTypes::sampleRate_10Min},
            {WirelessTypes::sampleRate_30Min},
            {WirelessTypes::sampleRate_60Min}};

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::burst = {
            {WirelessTypes::sampleRate_4096Hz},
            {WirelessTypes::sampleRate_2048Hz},
            {WirelessTypes::sampleRate_1024Hz},
            {WirelessTypes::sampleRate_512Hz},
            {WirelessTypes::sampleRate_256Hz},
            {WirelessTypes::sampleRate_128Hz},
            {WirelessTypes::sampleRate_64Hz},
            {WirelessTypes::sampleRate_32Hz}};

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::armedDatalog = AvailableSampleRates::burst;    //same as burst

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::derivedOnly = {
            {WirelessTypes::sampleRate_4096Hz},
            {WirelessTypes::sampleRate_2048Hz},
            {WirelessTypes::sampleRate_1024Hz},
            {WirelessTypes::sampleRate_512Hz},
            {WirelessTypes::sampleRate_256Hz},
            {WirelessTypes::sampleRate_128Hz},
            {WirelessTypes::sampleRate_64Hz},
            {WirelessTypes::sampleRate_32Hz},
            {WirelessTypes::sampleRate_16Hz},
            {WirelessTypes::sampleRate_8Hz},
            {WirelessTypes::sampleRate_4Hz},
            {WirelessTypes::sampleRate_2Hz},
            {WirelessTypes::sampleRate_1Hz}};


    const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous_nonSync_vlink200 = {
        {WirelessTypes::sampleRate_512Hz},
        {WirelessTypes::sampleRate_256Hz},
        {WirelessTypes::sampleRate_128Hz},
        {WirelessTypes::sampleRate_64Hz},
        {WirelessTypes::sampleRate_32Hz},
        {WirelessTypes::sampleRate_16Hz},
        {WirelessTypes::sampleRate_8Hz},
        {WirelessTypes::sampleRate_4Hz},
        {WirelessTypes::sampleRate_2Hz},
        {WirelessTypes::sampleRate_1Hz},
        {WirelessTypes::sampleRate_2Sec},
        {WirelessTypes::sampleRate_5Sec},
        {WirelessTypes::sampleRate_10Sec},
        {WirelessTypes::sampleRate_30Sec},
        {WirelessTypes::sampleRate_1Min},
        {WirelessTypes::sampleRate_2Min},
        {WirelessTypes::sampleRate_5Min},
        {WirelessTypes::sampleRate_10Min},
        {WirelessTypes::sampleRate_30Min},
        {WirelessTypes::sampleRate_60Min}};

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous_sync_vlink200 = {
        {WirelessTypes::sampleRate_4096Hz},
        {WirelessTypes::sampleRate_2048Hz},
        {WirelessTypes::sampleRate_1024Hz},
        {WirelessTypes::sampleRate_512Hz},
        {WirelessTypes::sampleRate_256Hz},
        {WirelessTypes::sampleRate_128Hz},
        {WirelessTypes::sampleRate_64Hz},
        {WirelessTypes::sampleRate_32Hz},
        {WirelessTypes::sampleRate_16Hz},
        {WirelessTypes::sampleRate_8Hz},
        {WirelessTypes::sampleRate_4Hz},
        {WirelessTypes::sampleRate_2Hz},
        {WirelessTypes::sampleRate_1Hz},
        {WirelessTypes::sampleRate_2Sec},
        {WirelessTypes::sampleRate_5Sec},
        {WirelessTypes::sampleRate_10Sec},
        {WirelessTypes::sampleRate_30Sec},
        {WirelessTypes::sampleRate_1Min},
        {WirelessTypes::sampleRate_2Min},
        {WirelessTypes::sampleRate_5Min},
        {WirelessTypes::sampleRate_10Min},
        {WirelessTypes::sampleRate_30Min},
        {WirelessTypes::sampleRate_60Min}};

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous_log_vlink200 = {
        {WirelessTypes::sampleRate_8192Hz},
        {WirelessTypes::sampleRate_4096Hz},
        {WirelessTypes::sampleRate_2048Hz},
        {WirelessTypes::sampleRate_1024Hz},
        {WirelessTypes::sampleRate_512Hz},
        {WirelessTypes::sampleRate_256Hz},
        {WirelessTypes::sampleRate_128Hz},
        {WirelessTypes::sampleRate_64Hz},
        {WirelessTypes::sampleRate_32Hz},
        {WirelessTypes::sampleRate_16Hz},
        {WirelessTypes::sampleRate_8Hz},
        {WirelessTypes::sampleRate_4Hz},
        {WirelessTypes::sampleRate_2Hz},
        {WirelessTypes::sampleRate_1Hz},
        {WirelessTypes::sampleRate_2Sec},
        {WirelessTypes::sampleRate_5Sec},
        {WirelessTypes::sampleRate_10Sec},
        {WirelessTypes::sampleRate_30Sec},
        {WirelessTypes::sampleRate_1Min},
        {WirelessTypes::sampleRate_2Min},
        {WirelessTypes::sampleRate_5Min},
        {WirelessTypes::sampleRate_10Min},
        {WirelessTypes::sampleRate_30Min},
        {WirelessTypes::sampleRate_60Min}};

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::burst_vlink200 = {
        {WirelessTypes::sampleRate_8192Hz},
        {WirelessTypes::sampleRate_4096Hz},
        {WirelessTypes::sampleRate_2048Hz},
        {WirelessTypes::sampleRate_1024Hz},
        {WirelessTypes::sampleRate_512Hz},
        {WirelessTypes::sampleRate_256Hz},
        {WirelessTypes::sampleRate_128Hz},
        {WirelessTypes::sampleRate_64Hz},
        {WirelessTypes::sampleRate_32Hz}};

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous_nonSync_glink200 = {
        {WirelessTypes::sampleRate_512Hz},
        {WirelessTypes::sampleRate_256Hz},
        {WirelessTypes::sampleRate_128Hz},
        {WirelessTypes::sampleRate_64Hz},
        {WirelessTypes::sampleRate_32Hz},
        {WirelessTypes::sampleRate_16Hz},
        {WirelessTypes::sampleRate_8Hz},
        {WirelessTypes::sampleRate_4Hz},
        {WirelessTypes::sampleRate_2Hz},
        {WirelessTypes::sampleRate_1Hz},
        {WirelessTypes::sampleRate_2Sec},
        {WirelessTypes::sampleRate_5Sec},
        {WirelessTypes::sampleRate_10Sec},
        {WirelessTypes::sampleRate_30Sec},
        {WirelessTypes::sampleRate_1Min},
        {WirelessTypes::sampleRate_2Min},
        {WirelessTypes::sampleRate_5Min},
        {WirelessTypes::sampleRate_10Min},
        {WirelessTypes::sampleRate_30Min},
        {WirelessTypes::sampleRate_60Min}};

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous_sync_glink200 = {
        {WirelessTypes::sampleRate_4096Hz},
        {WirelessTypes::sampleRate_2048Hz},
        {WirelessTypes::sampleRate_1024Hz},
        {WirelessTypes::sampleRate_512Hz},
        {WirelessTypes::sampleRate_256Hz},
        {WirelessTypes::sampleRate_128Hz},
        {WirelessTypes::sampleRate_64Hz},
        {WirelessTypes::sampleRate_32Hz},
        {WirelessTypes::sampleRate_16Hz},
        {WirelessTypes::sampleRate_8Hz},
        {WirelessTypes::sampleRate_4Hz},
        {WirelessTypes::sampleRate_2Hz},
        {WirelessTypes::sampleRate_1Hz},
        {WirelessTypes::sampleRate_2Sec},
        {WirelessTypes::sampleRate_5Sec},
        {WirelessTypes::sampleRate_10Sec},
        {WirelessTypes::sampleRate_30Sec},
        {WirelessTypes::sampleRate_1Min},
        {WirelessTypes::sampleRate_2Min},
        {WirelessTypes::sampleRate_5Min},
        {WirelessTypes::sampleRate_10Min},
        {WirelessTypes::sampleRate_30Min},
        {WirelessTypes::sampleRate_60Min}};

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous_log_glink200 = {
        {WirelessTypes::sampleRate_4096Hz},
        {WirelessTypes::sampleRate_2048Hz},
        {WirelessTypes::sampleRate_1024Hz},
        {WirelessTypes::sampleRate_512Hz},
        {WirelessTypes::sampleRate_256Hz},
        {WirelessTypes::sampleRate_128Hz},
        {WirelessTypes::sampleRate_64Hz},
        {WirelessTypes::sampleRate_32Hz},
        {WirelessTypes::sampleRate_16Hz},
        {WirelessTypes::sampleRate_8Hz},
        {WirelessTypes::sampleRate_4Hz},
        {WirelessTypes::sampleRate_2Hz},
        {WirelessTypes::sampleRate_1Hz},
        {WirelessTypes::sampleRate_2Sec},
        {WirelessTypes::sampleRate_5Sec},
        {WirelessTypes::sampleRate_10Sec},
        {WirelessTypes::sampleRate_30Sec},
        {WirelessTypes::sampleRate_1Min},
        {WirelessTypes::sampleRate_2Min},
        {WirelessTypes::sampleRate_5Min},
        {WirelessTypes::sampleRate_10Min},
        {WirelessTypes::sampleRate_30Min},
        {WirelessTypes::sampleRate_60Min}};

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::burst_glink200 = {
        {WirelessTypes::sampleRate_4096Hz},
        {WirelessTypes::sampleRate_2048Hz},
        {WirelessTypes::sampleRate_1024Hz},
        {WirelessTypes::sampleRate_512Hz},
        {WirelessTypes::sampleRate_256Hz},
        {WirelessTypes::sampleRate_128Hz},
        {WirelessTypes::sampleRate_64Hz},
        {WirelessTypes::sampleRate_32Hz}};

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::derivedOnly_glink200 = {
        {WirelessTypes::sampleRate_4096Hz},
        {WirelessTypes::sampleRate_2048Hz},
        {WirelessTypes::sampleRate_1024Hz},
        {WirelessTypes::sampleRate_512Hz},
        {WirelessTypes::sampleRate_256Hz},
        {WirelessTypes::sampleRate_128Hz},
        {WirelessTypes::sampleRate_64Hz},
        {WirelessTypes::sampleRate_32Hz},
        {WirelessTypes::sampleRate_16Hz},
        {WirelessTypes::sampleRate_8Hz},
        {WirelessTypes::sampleRate_4Hz},
        {WirelessTypes::sampleRate_2Hz},
        {WirelessTypes::sampleRate_1Hz},
        {WirelessTypes::sampleRate_2Sec},
        {WirelessTypes::sampleRate_5Sec},
        {WirelessTypes::sampleRate_10Sec},
        {WirelessTypes::sampleRate_30Sec},
        {WirelessTypes::sampleRate_1Min},
        {WirelessTypes::sampleRate_2Min},
        {WirelessTypes::sampleRate_5Min},
        {WirelessTypes::sampleRate_10Min},
        {WirelessTypes::sampleRate_30Min},
        {WirelessTypes::sampleRate_60Min}};

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous_nonSync_glink200r = {
        { WirelessTypes::sampleRate_512Hz },
        { WirelessTypes::sampleRate_256Hz },
        { WirelessTypes::sampleRate_128Hz } };

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous_sync_glink200r = {
        { WirelessTypes::sampleRate_1024Hz },
        { WirelessTypes::sampleRate_512Hz },
        { WirelessTypes::sampleRate_256Hz },
        { WirelessTypes::sampleRate_128Hz } };

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous_log_glink200r = {
        { WirelessTypes::sampleRate_1024Hz },
        { WirelessTypes::sampleRate_512Hz },
        { WirelessTypes::sampleRate_256Hz },
        { WirelessTypes::sampleRate_128Hz } };

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous_glink2 = {
            {WirelessTypes::sampleRate_512Hz},
            {WirelessTypes::sampleRate_256Hz},
            {WirelessTypes::sampleRate_128Hz},
            {WirelessTypes::sampleRate_64Hz},
            {WirelessTypes::sampleRate_32Hz}};

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::burst_glink2 = {
            {WirelessTypes::sampleRate_10kHz},
            {WirelessTypes::sampleRate_9kHz},
            {WirelessTypes::sampleRate_8kHz},
            {WirelessTypes::sampleRate_7kHz},
            {WirelessTypes::sampleRate_6kHz},
            {WirelessTypes::sampleRate_5kHz},
            {WirelessTypes::sampleRate_4kHz},
            {WirelessTypes::sampleRate_3kHz},
            {WirelessTypes::sampleRate_2kHz},
            {WirelessTypes::sampleRate_1kHz},
            {WirelessTypes::sampleRate_512Hz},
            {WirelessTypes::sampleRate_256Hz},
            {WirelessTypes::sampleRate_128Hz},
            {WirelessTypes::sampleRate_64Hz},
            {WirelessTypes::sampleRate_32Hz}};

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::armedDatalog_glink2 = AvailableSampleRates::burst_glink2; //same as burst



    const WirelessTypes::WirelessSampleRates AvailableSampleRates::burst_vlink = {
            {WirelessTypes::sampleRate_10kHz},
            {WirelessTypes::sampleRate_9kHz},
            {WirelessTypes::sampleRate_8kHz},
            {WirelessTypes::sampleRate_7kHz},
            {WirelessTypes::sampleRate_6kHz},
            {WirelessTypes::sampleRate_5kHz},
            {WirelessTypes::sampleRate_4kHz},
            {WirelessTypes::sampleRate_3kHz},
            {WirelessTypes::sampleRate_2kHz},
            {WirelessTypes::sampleRate_1kHz},
            {WirelessTypes::sampleRate_512Hz},
            {WirelessTypes::sampleRate_256Hz},
            {WirelessTypes::sampleRate_128Hz},
            {WirelessTypes::sampleRate_64Hz},
            {WirelessTypes::sampleRate_32Hz}};

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::armedDatalog_vlink = AvailableSampleRates::burst_vlink;    //same as burst

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::burst_iepeLink = {
            {WirelessTypes::sampleRate_104170Hz},
            {WirelessTypes::sampleRate_78125Hz},
            {WirelessTypes::sampleRate_62500Hz},
            {WirelessTypes::sampleRate_50kHz},
            {WirelessTypes::sampleRate_25000Hz},
            {WirelessTypes::sampleRate_12500Hz},
            {WirelessTypes::sampleRate_10kHz},
            {WirelessTypes::sampleRate_1kHz}};


    const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous_tclink = {
            {WirelessTypes::sampleRate_8Hz},
            {WirelessTypes::sampleRate_4Hz},
            {WirelessTypes::sampleRate_2Hz},
            {WirelessTypes::sampleRate_1Hz},
            {WirelessTypes::sampleRate_2Sec},
            {WirelessTypes::sampleRate_5Sec},
            {WirelessTypes::sampleRate_10Sec},
            {WirelessTypes::sampleRate_30Sec},
            {WirelessTypes::sampleRate_1Min},
            {WirelessTypes::sampleRate_2Min},
            {WirelessTypes::sampleRate_5Min},
            {WirelessTypes::sampleRate_10Min},
            {WirelessTypes::sampleRate_30Min},
            {WirelessTypes::sampleRate_60Min}};



    const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous_tclink1ch = {
            {WirelessTypes::sampleRate_64Hz},
            {WirelessTypes::sampleRate_32Hz},
            {WirelessTypes::sampleRate_16Hz},
            {WirelessTypes::sampleRate_8Hz},
            {WirelessTypes::sampleRate_4Hz},
            {WirelessTypes::sampleRate_2Hz},
            {WirelessTypes::sampleRate_1Hz},
            {WirelessTypes::sampleRate_2Sec},
            {WirelessTypes::sampleRate_5Sec},
            {WirelessTypes::sampleRate_10Sec},
            {WirelessTypes::sampleRate_30Sec},
            {WirelessTypes::sampleRate_1Min},
            {WirelessTypes::sampleRate_2Min},
            {WirelessTypes::sampleRate_5Min},
            {WirelessTypes::sampleRate_10Min},
            {WirelessTypes::sampleRate_30Min},
            {WirelessTypes::sampleRate_60Min}};

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous_tclink200 = {
        {WirelessTypes::sampleRate_128Hz},
        {WirelessTypes::sampleRate_64Hz},
        {WirelessTypes::sampleRate_32Hz},
        {WirelessTypes::sampleRate_16Hz},
        {WirelessTypes::sampleRate_8Hz},
        {WirelessTypes::sampleRate_4Hz},
        {WirelessTypes::sampleRate_2Hz},
        {WirelessTypes::sampleRate_1Hz},
        {WirelessTypes::sampleRate_2Sec},
        {WirelessTypes::sampleRate_5Sec},
        {WirelessTypes::sampleRate_10Sec},
        {WirelessTypes::sampleRate_30Sec},
        {WirelessTypes::sampleRate_1Min},
        {WirelessTypes::sampleRate_2Min},
        {WirelessTypes::sampleRate_5Min},
        {WirelessTypes::sampleRate_10Min},
        {WirelessTypes::sampleRate_30Min},
        {WirelessTypes::sampleRate_60Min}};

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous_rtdlink200 = {
        {WirelessTypes::sampleRate_64Hz},
        {WirelessTypes::sampleRate_32Hz},
        {WirelessTypes::sampleRate_16Hz},
        {WirelessTypes::sampleRate_8Hz},
        {WirelessTypes::sampleRate_4Hz},
        {WirelessTypes::sampleRate_2Hz},
        {WirelessTypes::sampleRate_1Hz},
        {WirelessTypes::sampleRate_2Sec},
        {WirelessTypes::sampleRate_5Sec},
        {WirelessTypes::sampleRate_10Sec},
        {WirelessTypes::sampleRate_30Sec},
        {WirelessTypes::sampleRate_1Min},
        {WirelessTypes::sampleRate_2Min},
        {WirelessTypes::sampleRate_5Min},
        {WirelessTypes::sampleRate_10Min},
        {WirelessTypes::sampleRate_30Min},
        {WirelessTypes::sampleRate_60Min}};


    const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous_envlink = {
            {WirelessTypes::sampleRate_2Hz},
            {WirelessTypes::sampleRate_1Hz},
            {WirelessTypes::sampleRate_2Sec},
            {WirelessTypes::sampleRate_5Sec},
            {WirelessTypes::sampleRate_10Sec},
            {WirelessTypes::sampleRate_30Sec},
            {WirelessTypes::sampleRate_1Min},
            {WirelessTypes::sampleRate_2Min},
            {WirelessTypes::sampleRate_5Min},
            {WirelessTypes::sampleRate_10Min},
            {WirelessTypes::sampleRate_30Min},
            {WirelessTypes::sampleRate_60Min}};

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous_shmLink2 = {
            {WirelessTypes::sampleRate_128Hz},
            {WirelessTypes::sampleRate_64Hz},
            {WirelessTypes::sampleRate_32Hz},
            {WirelessTypes::sampleRate_16Hz},
            {WirelessTypes::sampleRate_8Hz},
            {WirelessTypes::sampleRate_4Hz},
            {WirelessTypes::sampleRate_2Hz},
            {WirelessTypes::sampleRate_1Hz}};

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous_shmLink2_2 = {
        {WirelessTypes::sampleRate_300Hz},
        {WirelessTypes::sampleRate_128Hz},
        {WirelessTypes::sampleRate_64Hz},
        {WirelessTypes::sampleRate_32Hz},
        {WirelessTypes::sampleRate_16Hz},
        {WirelessTypes::sampleRate_8Hz},
        {WirelessTypes::sampleRate_4Hz},
        {WirelessTypes::sampleRate_2Hz},
        {WirelessTypes::sampleRate_1Hz}};

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous_shmLink201 = {
        {WirelessTypes::sampleRate_887Hz},
        {WirelessTypes::sampleRate_512Hz},
        {WirelessTypes::sampleRate_256Hz},
        {WirelessTypes::sampleRate_128Hz},
        {WirelessTypes::sampleRate_64Hz},
        {WirelessTypes::sampleRate_32Hz},
        {WirelessTypes::sampleRate_16Hz},
        {WirelessTypes::sampleRate_8Hz},
        {WirelessTypes::sampleRate_4Hz},
        {WirelessTypes::sampleRate_2Hz},
        {WirelessTypes::sampleRate_1Hz}};

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous_cfBearing = {
        {WirelessTypes::sampleRate_16Hz},
        {WirelessTypes::sampleRate_8Hz},
        {WirelessTypes::sampleRate_4Hz},
        {WirelessTypes::sampleRate_2Hz},
        {WirelessTypes::sampleRate_1Hz},
        {WirelessTypes::sampleRate_2Sec},
        {WirelessTypes::sampleRate_5Sec},
        {WirelessTypes::sampleRate_10Sec}};

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous_nonSync_impact = {
        {WirelessTypes::sampleRate_512Hz},
        {WirelessTypes::sampleRate_256Hz},
        {WirelessTypes::sampleRate_128Hz},
        {WirelessTypes::sampleRate_64Hz},
        {WirelessTypes::sampleRate_32Hz}};

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous_sync_impact = {
        {WirelessTypes::sampleRate_4096Hz},
        {WirelessTypes::sampleRate_2048Hz},
        {WirelessTypes::sampleRate_1024Hz},
        {WirelessTypes::sampleRate_512Hz},
        {WirelessTypes::sampleRate_256Hz},
        {WirelessTypes::sampleRate_128Hz},
        {WirelessTypes::sampleRate_64Hz},
        {WirelessTypes::sampleRate_32Hz}};

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::burst_impact = {
        {WirelessTypes::sampleRate_8192Hz},
        {WirelessTypes::sampleRate_4096Hz},
        {WirelessTypes::sampleRate_2048Hz},
        {WirelessTypes::sampleRate_1024Hz},
        {WirelessTypes::sampleRate_512Hz},
        {WirelessTypes::sampleRate_256Hz},
        {WirelessTypes::sampleRate_128Hz},
        {WirelessTypes::sampleRate_64Hz},
        {WirelessTypes::sampleRate_32Hz}};

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous_sglink200 = {
        {WirelessTypes::sampleRate_1024Hz},
        {WirelessTypes::sampleRate_512Hz},
        {WirelessTypes::sampleRate_256Hz},
        {WirelessTypes::sampleRate_128Hz},
        {WirelessTypes::sampleRate_64Hz},
        {WirelessTypes::sampleRate_32Hz},
        {WirelessTypes::sampleRate_16Hz},
        {WirelessTypes::sampleRate_8Hz},
        {WirelessTypes::sampleRate_4Hz},
        {WirelessTypes::sampleRate_2Hz},
        {WirelessTypes::sampleRate_1Hz},
        {WirelessTypes::sampleRate_2Sec},
        {WirelessTypes::sampleRate_5Sec},
        {WirelessTypes::sampleRate_10Sec},
        {WirelessTypes::sampleRate_30Sec},
        {WirelessTypes::sampleRate_1Min},
        {WirelessTypes::sampleRate_2Min},
        {WirelessTypes::sampleRate_5Min},
        {WirelessTypes::sampleRate_10Min},
        {WirelessTypes::sampleRate_30Min},
        {WirelessTypes::sampleRate_60Min}};

    const WirelessTypes::WirelessSampleRates AvailableSampleRates::burst_sglink200 = {
        {WirelessTypes::sampleRate_1024Hz},
        {WirelessTypes::sampleRate_512Hz},
        {WirelessTypes::sampleRate_256Hz},
        {WirelessTypes::sampleRate_128Hz},
        {WirelessTypes::sampleRate_64Hz},
        {WirelessTypes::sampleRate_32Hz}};
}