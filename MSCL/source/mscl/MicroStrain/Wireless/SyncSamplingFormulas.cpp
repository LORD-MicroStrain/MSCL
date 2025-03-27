/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/SyncSamplingFormulas.h"

#include "mscl/MicroStrain/SampleRate.h"

namespace mscl
{
#ifndef SWIG
namespace SyncSamplingFormulas
{
    double bytesPerSecond(const SampleRate& sampleRate, uint16 numChs, uint8 bytesPerSample)
    {
        return sampleRate.samplesPerSecond() * numChs * bytesPerSample;
    }

    uint32 maxBytesPerPacket(const SampleRate& sampleRate, bool lossless, bool highBandwidth, uint8 syncFormulaVersion, WirelessTypes::CommProtocol commProtocol)
    {
        if(commProtocol == WirelessTypes::commProtocol_lxrs)
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

            return 96;
        }

        if(highBandwidth)
        {
            return 69;
        }

        if(lossless)
        {
            return 138;
        }

        return 138; //keep the same bandwidth limitations as lossless
    }

    uint32 groupSize()
    {
        //always returning 1 for now
        //previously, when high capacity was supported, this would use different logic

        return 1;
    }

    uint32 txPerGroup(double bytesPerSecond, uint32 maxBytesPerPacket, uint32 groupSize)
    {
        return Utils::ceilBase2( std::ceil( bytesPerSecond * groupSize / maxBytesPerPacket) );
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

    uint16 slotSpacing(WirelessTypes::CommProtocol protocol)
    {
        switch(protocol)
        {
            case WirelessTypes::commProtocol_lxrsPlus:
                return 4;

            case WirelessTypes::commProtocol_lxrs:
            default:
                return 8;
        }
    }

    uint32 maxTdmaAddress(uint32 txPerGroup, uint32 groupSize, bool legacyNwk, WirelessTypes::CommProtocol protocol)
    {
        if(txPerGroup == 0)
        {
            return 1;
        }

        uint8 disallowedSlots = 0;

        if(legacyNwk)
        {
            disallowedSlots = 1;
        }

        uint32 address = static_cast<uint32>(Utils::round( groupSize * MAX_SLOTS / static_cast<float>(txPerGroup) - slotSpacing(protocol) * disallowedSlots ));

        //make sure it's a minimum of MIN_TDMA
        Utils::checkBounds_min(address, static_cast<uint32>(MIN_TDMA));

        return address;
    }

    float percentBandwidth(float txPerSecond, bool legacyNwk, WirelessTypes::CommProtocol protocol)
    {
        uint8 disallowedSlots = 0;

        if(legacyNwk)
        {
            disallowedSlots = 1;
        }

        return txPerSecond * slotSpacing(protocol) / static_cast<float>(MAX_SLOTS - disallowedSlots) * 100;
    }

    double sampleDuration(uint32 numSweeps, const SampleRate& sampleRate)
    {
        return static_cast<double>(numSweeps) / sampleRate.samplesPerSecond();
    }

    uint32 bytesPerSweep(uint8 bytesPerSample, uint16 numChs)
    {
        return bytesPerSample * numChs;
    }

    bool checkSamplingDelay(WirelessTypes::SamplingMode samplingMode, const SampleRate& sampleRate, WirelessModels::NodeModel nodeModel)
    {
        bool isShmLink = false;

        switch(nodeModel)
        {
            case WirelessModels::node_shmLink:
            case WirelessModels::node_shmLink2_cust1:
            case WirelessModels::node_shmLink2_cust1_oldNumber:
            case WirelessModels::node_shmLink200:
            case WirelessModels::node_shmLink201:
            case WirelessModels::node_shmLink201_qbridge_1K:
            case WirelessModels::node_shmLink201_qbridge_348:
            case WirelessModels::node_shmLink201_hbridge_1K:
            case WirelessModels::node_shmLink201_hbridge_348:
            case WirelessModels::node_shmLink201_fullbridge:
                isShmLink = true;
                break;

            default:
                break;
        }

        //if the sampling mode is not Burst mode
        if(samplingMode != WirelessTypes::samplingMode_syncBurst)
        {
            //if the sample rate is 16hz or slower, or the 32hz or faster and a tclink1ch or rtdlink, or the model is SHM-Link
            if( isShmLink ||
                sampleRate <= SampleRate::Hertz(16) ||
                (sampleRate >= SampleRate::Hertz(32) && (nodeModel == WirelessModels::node_tcLink_1ch || nodeModel == WirelessModels::node_rtdLink))
              )
            {
                return true;
            }
        }

        return false;
    }

    uint16 slotsBetweenTx(uint32 txPerGroup, uint32 groupSize)
    {
        return static_cast<uint16>(MAX_SLOTS * groupSize / txPerGroup);
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

    uint32 maxBytesPerBurstPacket(uint32 bytesPerSweep, bool lossless, WirelessTypes::CommProtocol commProtocol)
    {
        if(commProtocol == WirelessTypes::commProtocol_lxrsPlus)
        {
            return 207;//432;
        }

        float numBytes = 96.0f;

        if(lossless)
        {
            numBytes = 80.0f;
        }

        //prevent divide by 0
        Utils::checkBounds_min(bytesPerSweep, 1u);

        return static_cast<uint32>(std::floor(numBytes / static_cast<float>(bytesPerSweep)) * bytesPerSweep);
    }

    uint32 totalNeededBurstTx(uint32 totalBytesPerBurst, uint32 maxBurstBytesPerPacket)
    {
        Utils::checkBounds_min(maxBurstBytesPerPacket, 1u);

        return static_cast<uint32>( std::ceil( static_cast<float>(totalBytesPerBurst) / static_cast<float>(maxBurstBytesPerPacket) ) );
    }

    uint32 minTimeBetweenBursts(uint32 totalNeededTx, double sampleDuration, bool lossless)
    {
        //Note: this does not consider possible benefits of LXRS+ - could update to have values be 128 (no lossless) and 64 (lossless)

        float txPerSec = 64.0f;

        if(lossless)
        {
            txPerSec = 32.0f;
        }

        return static_cast<uint32>( std::ceil( static_cast<float>(totalNeededTx) / txPerSec + 4 + sampleDuration ) );
    }

    TimeSpan minTimeBetweenBursts(uint32 numRawBytesPerSweep, uint32 numDerivedBytesPerSweep, const SampleRate& rawSampleRate, uint32 sweepsPerBurst, WirelessTypes::CommProtocol commProtocol)
    {
        //Note: we are passing true for all the lossless parameters because burst limits to the same numbers as lossless

        uint32 totalNeededTx_raw = 0;
        uint32 totalNeededTx_derived = 0;

        if(numRawBytesPerSweep > 0)
        {
            uint32 bytesPerBurst = totalBytesPerBurst(numRawBytesPerSweep, sweepsPerBurst);

            uint32 maxBytesPerPacket = maxBytesPerBurstPacket(numRawBytesPerSweep, true, commProtocol);

            totalNeededTx_raw = totalNeededBurstTx(bytesPerBurst, maxBytesPerPacket);
        }

        if(numDerivedBytesPerSweep > 0)
        {
            totalNeededTx_derived = static_cast<uint32>(2 * std::ceil(static_cast<float>(numDerivedBytesPerSweep) / 96.0f));
        }

        double duration = sampleDuration(sweepsPerBurst, rawSampleRate);

        return TimeSpan::Seconds(minTimeBetweenBursts(totalNeededTx_raw + totalNeededTx_derived, duration, true));
    }

    uint32 burstTxPerSecond(uint32 totalNeededTx, uint32 timeBetweenBursts, double sampleDuration, bool lossless)
    {
        uint32 txPerSec = Utils::ceilBase2( static_cast<double>(totalNeededTx) / (timeBetweenBursts - 4 - sampleDuration) );

        //must be within range 1 - 64
        Utils::checkBounds_min(txPerSec, static_cast<uint32>(1));
        Utils::checkBounds_max(txPerSec, static_cast<uint32>(64));

        if(lossless && txPerSec < 64)
        {
            if(timeBetweenBursts < 2 * totalNeededTx / txPerSec + 4 + sampleDuration )
            {
                txPerSec *= 2;
            }
        }

        return txPerSec;
    }

    float overheadFactor(bool lossless, bool optimizeBandwidth, bool diagnosticPacketEnabled, const SampleRate& sampleRate, uint8 syncFormulaVersion)
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

        if(diagnosticPacketEnabled)
        {
            return 1.05f;
        }

        return 1.0f;
    }
}
#endif // !SWIG
} // namespace SyncSamplingFormulas
