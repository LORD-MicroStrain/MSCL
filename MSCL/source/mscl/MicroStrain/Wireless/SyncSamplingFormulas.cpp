/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

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

    uint32 maxBytesPerPacket(const SampleRate& sampleRate, bool lossless, bool highBandwidth, uint8 syncFormulaVersion)
    {
        if(highBandwidth)
        {
            //for high bandwidth, we always want to return 32 bytes per packet
            return 32;
        }

        //special cases for sync version 1
        if(syncFormulaVersion == 1)
        {
            if(sampleRate >= SampleRate::Hertz(512))
            {
                return 48;
            }
        }

        if(lossless)
        {
            return 64;
        }
        else
        {
            return 96;
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
                groupSize = Utils::floorBase2( std::floor(maxBytesPerPacket / bytesPerSecond) );
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
        return Utils::ceilBase2( std::ceil( (bytesPerSecond * groupSize) / maxBytesPerPacket) );
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

    uint32 maxTdmaAddress(uint32 txPerGroup, uint32 groupSize, bool legacyNwk)
    {
        uint8 disallowedSlots = 0;

        if(legacyNwk)
        {
            disallowedSlots = 1;
        }

        uint32 address = static_cast<uint32>(Utils::round( ((groupSize * MAX_SLOTS) / static_cast<float>(txPerGroup)) - (slotSpacing() * disallowedSlots) ));

        //make sure its a minimum of MIN_TDMA
        Utils::checkBounds_min(address, static_cast<uint32>(MIN_TDMA));

        return address;
    }

    float percentBandwidth(float txPerSecond, bool legacyNwk)
    {
        uint8 disallowedSlots = 0;

        if(legacyNwk)
        {
            disallowedSlots = 1;
        }

        return ((txPerSecond * slotSpacing()) / static_cast<float>(MAX_SLOTS - disallowedSlots)) * 100;
    }

    double sampleDuration(uint32 numSweeps, const SampleRate& sampleRate)
    {
        return (static_cast<double>(numSweeps) / sampleRate.samplesPerSecond());
    }

    uint32 bytesPerSweep(uint8 bytesPerSample, uint16 numChs)
    {
        return bytesPerSample * numChs;
    }

    bool checkSamplingDelay(WirelessTypes::SamplingMode samplingMode, const SampleRate& sampleRate, WirelessModels::NodeModel nodeModel)
    {
        //if the sampling mode is not Burst mode
        if(samplingMode != WirelessTypes::samplingMode_syncBurst)
        {
            //if the sample rate is 16hz or slower, or the 32hz or faster and a tclink1ch or rtdlink, or the model is SHM-Link
            if( (sampleRate <= SampleRate::Hertz(16)) ||
                (sampleRate >= SampleRate::Hertz(32) && (nodeModel == WirelessModels::node_tcLink_1ch || nodeModel == WirelessModels::node_rtdLink)) ||
                (nodeModel == WirelessModels::node_shmLink || nodeModel == WirelessModels::node_shmLink200 || nodeModel == WirelessModels::node_shmLink2_cust1)
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

    bool canHaveFirstSlot(WirelessModels::NodeModel nodeModel, uint8 syncVersion)
    {
        if(syncVersion > 1)
        {
            return true;
        }

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

    uint32 maxBytesPerBurstPacket(uint32 bytesPerSweep, bool lossless)
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

    TimeSpan minTimeBetweenBursts(uint32 numRawBytesPerSweep, uint32 numDerivedBytesPerSweep, const mscl::SampleRate& rawSampleRate, uint32 sweepsPerBurst)
    {
        uint32 totalNeededTx_raw = 0;
        uint32 totalNeededTx_derived = 0;

        if(numRawBytesPerSweep > 0)
        {
            uint32 bytesPerBurst = totalBytesPerBurst(numRawBytesPerSweep, sweepsPerBurst);

            uint32 maxBytesPerPacket = maxBytesPerBurstPacket(numRawBytesPerSweep, true);

            totalNeededTx_raw = totalNeededBurstTx(bytesPerBurst, maxBytesPerPacket);
        }

        if(numDerivedBytesPerSweep > 0)
        {
            totalNeededTx_derived = static_cast<uint32>(2 * std::ceil(static_cast<float>(numDerivedBytesPerSweep) / 96.0f));
        }

        double duration = sampleDuration(sweepsPerBurst, rawSampleRate);

        return TimeSpan::Seconds(minTimeBetweenBursts((totalNeededTx_raw + totalNeededTx_derived), duration, true));
    }

    uint32 burstTxPerSecond(uint32 totalNeededTx, uint32 timeBetweenBursts, double sampleDuration, bool lossless)
    {
        uint32 txPerSec = Utils::ceilBase2( (static_cast<double>(totalNeededTx) / (timeBetweenBursts - 4 - sampleDuration)) );

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

    float overheadFactor(bool lossless, bool optimizeBandwidth, const SampleRate& sampleRate, uint8 syncFormulaVersion)
    {
        //special cases for sync version 1
        if(syncFormulaVersion == 1)
        {
            if(sampleRate >= SampleRate::Hertz(512))
            {
                return 2.0f;
            }
        }

        if(optimizeBandwidth)
        {
            return 2.0f;
        }

        if(lossless)
        {
            return 1.5f;
        }
        
        return 1.0f;
    }
}
#endif

}