/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "SyncSamplingFormulas.h"

#include "mscl/MicroStrain/SampleRate.h"
#include "mscl/Utils.h"

namespace mscl
{

#ifndef SWIG
    
namespace SyncSamplingFormulas
{
    double bytesPerSecond(const SampleRate& sampleRate, uint16 numChs, uint8 bytesPerSample)
    {
        return sampleRate.samplesPerSecond() * numChs * bytesPerSample;
    }

    uint32 maxBytesPerPacket(const SampleRate& sampleRate, bool lossless, bool highBandwidth)
    {
        if(highBandwidth)
        {
            //for high bandwidth, we always want to return 32 bytes per packet
            return 32;
        }

        //if the sample rate is less than 512 Hz
        if(sampleRate < SampleRate::Hertz(512))
        {
            if(lossless)
            {
                return 64;
            }
            else
            {
                return 96;
            }
        }
        else
        {
            return 48;
        }
    }

    uint32 groupSize(double bytesPerSecond, uint32 maxBytesPerPacket, bool highCapacity)
    {
        static uint32 MAX_GROUP_SIZE = 16;
        uint32 groupSize;

        //high capacity
        if(highCapacity)
        {
            if(bytesPerSecond <= std::floor(static_cast<double>(maxBytesPerPacket / 2)))
            {
                groupSize = Utils::roundDownToNearestBase2( std::floor(maxBytesPerPacket / bytesPerSecond) );
            }
            else
            {
                groupSize = 1;
            }
        }
        //standard capacity
        else
        {
            //standard capacity always has a group size of 1 second
            groupSize = 1;
        }

        //group size is limited to a max of 16 seconds
        Utils::checkBounds_max(groupSize, MAX_GROUP_SIZE);

        return groupSize;
    }

    uint32 txPerGroup(double bytesPerSecond, uint32 maxBytesPerPacket, uint32 groupSize)
    {
        return Utils::roundUpToNearestBase2( std::ceil( (bytesPerSecond * groupSize) / maxBytesPerPacket) );
    }

    float txPerSecond(uint32 txPerGroup, uint32 groupSize)
    {
        //if the group size is 0
        if(groupSize == 0)
        {
            //0 transmissions per second
            return 0.0f;
        }

        return static_cast<float>(txPerGroup) / static_cast<float>(groupSize);
    }

    uint16 slotSpacing()
    {
        return 8;    //always returning 8 for now
    }

    uint32 maxTdmaAddress(uint32 txPerGroup, uint32 groupSize)
    {
        uint32 address = static_cast<uint32>(Utils::round( ((groupSize * MAX_SLOTS) / static_cast<float>(txPerGroup)) - slotSpacing() ));

        //make sure its a minimum of MIN_TDMA
        Utils::checkBounds_min(address, static_cast<uint32>(MIN_TDMA));

        return address;
    }

    float percentBandwidth(float txPerSecond)
    {
        return ((txPerSecond * slotSpacing()) / static_cast<float>(MAX_SLOTS - MIN_TDMA)) * 100;
    }

    double sampleDuration(uint32 numSweeps, const SampleRate& sampleRate)
    {
        return (static_cast<double>(numSweeps) / sampleRate.samplesPerSecond());
    }

    uint32 bytesPerSweep(uint8 bytesPerSample, uint16 numChs)
    {
        return bytesPerSample * numChs;
    }

    bool checkSamplingDelay(WirelessTypes::SyncSamplingMode samplingMode, const SampleRate& sampleRate, WirelessModels::NodeModel nodeModel)
    {
        //if the sampling mode is not Burst mode
        if(samplingMode != WirelessTypes::syncMode_burst)
        {
            //if the sample rate is 16hz or slower, or the 32hz or faster and a tclink1ch or rtdlink, or the model is SHM-Link
            if( (sampleRate <= SampleRate::Hertz(16)) ||
                (sampleRate >= SampleRate::Hertz(32) && (nodeModel == WirelessModels::node_tcLink_1ch || nodeModel == WirelessModels::node_rtdLink)) ||
                (nodeModel == WirelessModels::node_shmLink || nodeModel == WirelessModels::node_shmLink2 || nodeModel == WirelessModels::node_shmLink2_cust1)
              )
            {
                return true;
            }
        }

        return false;
    }

    uint16 slotsBetweenTx(uint32 txPerGroup, uint32 groupSize)
    {
        return static_cast<uint16>((MAX_SLOTS * groupSize) / txPerGroup);
    }

    bool canHaveSlot1(WirelessModels::NodeModel nodeModel)
    {
        switch(nodeModel)
        {
        //certain node types are not allowed to have slot 1
        case WirelessModels::node_tcLink_6ch:
        case WirelessModels::node_tcLink_6ch_ip67:
        case WirelessModels::node_tcLink_1ch:
        case WirelessModels::node_tcLink_3ch:
        case WirelessModels::node_envLink_pro:
        case WirelessModels::node_envLink_mini:
        case WirelessModels::node_rtdLink:
            return false;

        default:
            return true;
        }
    }




    uint32 totalBytesPerBurst(uint32 bytesPerSweep, uint32 numSweeps)
    {
        return bytesPerSweep * numSweeps;
    }

    uint32 maxDataBytesPerPacket(uint32 bytesPerSweep, bool lossless)
    {
        float numBytes = 96.0f;

        if(lossless)
        {
            numBytes = 80.0f;
        }

        return static_cast<uint32>( std::floor( (numBytes / static_cast<float>(bytesPerSweep)) ) * bytesPerSweep );
    }

    uint32 totalNeededBurstTx(uint32 totalBytesPerBurst, uint32 maxBurstBytesPerPacket)
    {
        return static_cast<uint32>( std::ceil( static_cast<float>(totalBytesPerBurst) / static_cast<float>(maxBurstBytesPerPacket) ) );
    }

    uint32 minTimeBetweenBursts(uint32 totalNeededTx, double sampleDuration, bool lossless)
    {
        float txPerSec = 64.0f;

        if(lossless)
        {
            txPerSec = 32.0f;
        }

        return static_cast<uint32>( std::ceil( (static_cast<float>(totalNeededTx) / txPerSec ) + 4 + sampleDuration ) );
    }

    TimeSpan minTimeBetweenBursts(WirelessTypes::DataFormat dataFormat, uint8 numActiveChs, const mscl::SampleRate& sampleRate, uint32 sweepsPerBurst)
    {
        uint32 bytesPerSweep = WirelessTypes::dataFormatSize(dataFormat) * static_cast<uint16>(numActiveChs);

        uint32 bytesPerBurst = totalBytesPerBurst(bytesPerSweep, sweepsPerBurst);

        uint32 maxBytesPerPacket = maxDataBytesPerPacket(bytesPerSweep, true);

        uint32 totalNeededTx = totalNeededBurstTx(bytesPerBurst, maxBytesPerPacket);

        double duration = sampleDuration(sweepsPerBurst, sampleRate);

        return TimeSpan::Seconds(minTimeBetweenBursts(totalNeededTx, duration, true));
    }

    uint32 burstTxPerSecond(uint32 totalNeededTx, uint32 timeBetweenBursts, double sampleDuration, bool lossless)
    {
        uint32 txPerSec = Utils::roundUpToNearestBase2( (static_cast<double>(totalNeededTx) / (timeBetweenBursts - 4 - sampleDuration)) );

        //must be within range 1 - 64
        Utils::checkBounds_min(txPerSec, static_cast<uint32>(1));
        Utils::checkBounds_max(txPerSec, static_cast<uint32>(64));

        if(lossless && (txPerSec < 64))
        {
            if(timeBetweenBursts < ( ((2 * totalNeededTx) / txPerSec) + 4 + sampleDuration) )
            {
                txPerSec *= 2;
            }
        }

        return txPerSec;
    }
}
#endif

}