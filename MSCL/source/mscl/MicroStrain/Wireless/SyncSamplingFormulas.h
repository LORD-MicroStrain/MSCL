/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/Types.h"
#include "mscl/TimeSpan.h"
#include "WirelessTypes.h"
#include "WirelessModels.h"

namespace mscl
{
    //Title: SyncSamplingFormulas

    class SampleRate;    //forward declaration

#ifndef SWIG
    //Namespace: SyncSamplingFormulas
    //    Contains formulas for determining Sync Sampling configuration
    namespace SyncSamplingFormulas
    {
        //====================================================================================================
        //Constants: Sync Sampling Constants
        //
        //MAX_SLOTS                    - 1024        - The maximum number of slots for normal capacity mode
        //MAX_SLOTS_HIGH_CAPACITY    - 1024 * 16 - The maximum number of slots for high capacity mode
        //MIN_TDMA                    - 1            - The minimum TDMA address allowed to be assigned to a Node
        //====================================================================================================
        static const uint16 MAX_SLOTS = 1024;
        static const uint16 MAX_SLOTS_HIGH_CAPACITY = 1024 * 16;
        static const uint8 MIN_TDMA = 1;

        //Function: bytesPerSecond
        //    Calculates the number of bytes per second
        //
        //Parameters:
        //    sampleRate - The <SampleRate>
        //    numChs - The number of active channels
        //    bytesPerSample - The number of bytes per sample
        //
        //Returns:
        //    The number of bytes per second
        double bytesPerSecond(const SampleRate& sampleRate, uint16 numChs, uint8 bytesPerSample);

        //Function: maxBytesPerPacket
        //    Calculates the maximum number of bytes per packet
        //
        //Parameters:
        //    sampleRate - The <SampleRate>
        //    lossless - Whether the network is using lossless or not
        //    highBandwidth - Whether we are attempting to optimize bandwidth or not
        //    syncFormulaVersion - The version of the Sync Sampling formula to use
        uint32 maxBytesPerPacket(const SampleRate& sampleRate, bool lossless, bool highBandwidth, uint8 syncFormulaVersion);

        //Function: groupSize
        //    Calculates the group size
        //
        //Parameters:
        //    bytesPerSecond - The number of bytes per second
        //    maxBytesPerPacket - The maximum number of bytes per packet
        //    highCapacity - Whether the network is using high capacity mode or not
        //
        //Returns:
        //    The group size for the network
        uint32 groupSize(double bytesPerSecond, uint32 maxBytesPerPacket, bool highCapacity);

        //Function: txPerGroup
        //    Calculates the transmissions per group
        //
        //Parameters:
        //    bytesPerSecond - The number of bytes per second
        //    maxBytesPerPacket - The maximum number of bytes per packet
        //    groupSize - The group size for the network
        //
        //Returns:
        //    The transmissions per group
        uint32 txPerGroup(double bytesPerSecond, uint32 maxBytesPerPacket, uint32 groupSize);

        //Function: txPerSecond
        //    Calculates the number of transmissions per second
        //
        //Parameters:
        //    txPerGroup - The number of transmissions per group
        //    groupSize - The group size for the network
        //
        //Returns:
        //    The number of transmissions per second
        float txPerSecond(uint32 txPerGroup, uint32 groupSize);

        //Function: slotSpacing
        //    Gets the slot spacing for the network
        //
        //Returns:
        //    The slot spacing for the network
        uint16 slotSpacing();

        //Function: maxTdmaAddress
        //    Gets the maximum TDMA address that is allowed
        //
        //Returns:
        //    The maximum TDMA address that is allowed
        uint32 maxTdmaAddress(uint32 txPerGroup, uint32 groupSize);

        //Function: percentBandwidth
        //    Calculates the percent of bandwidth for a single node
        //
        //Parametesr:
        //    txPerSecond - The number of transmissions per second
        //
        //Returns:
        //    The percent of bandwidth
        float percentBandwidth(float txPerSecond);

        //Function: sampleDuration
        //    Calculates the sample duration for a given sample rate and number of sweeps
        //
        //Parameters:
        //    numSweeps - The number of sweeps
        //    sampleRate The <SampleRate>
        double sampleDuration(uint32 numSweeps, const SampleRate& sampleRate);

        //Function: bytesPerSweep
        //    Gets the total number of bytes per data sweep
        //
        //Parameters:
        //    bytesPerSample - The number of bytes per sample
        //    numChs - The number of active channels
        //
        //Returns:
        //    The total number of bytes per data sweep
        uint32 bytesPerSweep(uint8 bytesPerSample, uint16 numChs);

        //Function: checkSamplingDelay
        //    Whether or not the sampling delay should be checked when finding slots in the Sync Sampling network
        //
        //Parameters:
        //    samplingMode - The <WirelessTypes::SyncSamplingMode> of the node
        //    sampleRate - The <SampleRate> of the node
        //    nodeModel - The <WirelessModels::NodeModel> of the node
        //
        //Returns:
        //    true if the sampling delay should be checked, false if it should not be checked
        bool checkSamplingDelay(WirelessTypes::SyncSamplingMode samplingMode, const SampleRate& sampleRate, WirelessModels::NodeModel nodeModel);

        //Function: slotsBetweenTx
        //    Calculates the number of slots that need to be between each transmission
        //
        //Parameters:
        //    txPerGroup - The number of transmissions per group
        //    groupSize - The group size for the network
        //
        //Returns:
        //    The number of slots that need to be between each transmission
        uint16 slotsBetweenTx(uint32 txPerGroup, uint32 groupSize);

        //Function: canHaveSlot1
        //    Checks whether the node can be assigned slot 1 in the Sync Sampling network
        //
        //Parameters:
        //    nodeModel - The <WirelessModels::NodeModel> of the node
        //    syncVersion - The version of the Sync Sampling formulas supported by the node
        //
        //Returns:
        //    true if the node can be assigned slot 1, false if it cannot be assigned slot 1
        bool canHaveSlot1(WirelessModels::NodeModel nodeModel, uint8 syncVersion);

        
        //==================================================================
        //BURST FORMULAS
        //==================================================================

        //Function: totalBytesPerBurst
        //    Gets the total number of bytes per burst
        //
        //Parameters:
        //    bytesPerSweep - The total number of bytes per data sweep
        //    numSweeps - The number of sweeps
        //
        //Returns:
        //    The total number of bytes per burst
        uint32 totalBytesPerBurst(uint32 bytesPerSweep, uint32 numSweeps);

        //Function: maxDataBytesPerPacket
        //    Gets the maximum number of bytes per packet
        //
        //Parameters:
        //    bytesPerSweep - The total number of bytes per data sweep
        //    lossless - Whether the network is using lossless or not
        //
        //Returns:
        //    The maximum number of bytes per packet
        uint32 maxDataBytesPerPacket(uint32 bytesPerSweep, bool lossless);

        //Function: totalNeededBurstTx
        //    Calculates the total needed transmissions for bursts
        //
        //Parameters:
        //    totalBytesPerBurst - The total number of bytes per burst
        //    maxBurstBytesPerPacket - The maximum number of bytes per packet
        //
        //Returns:
        //    The total needed transmissions for Bursts
        uint32 totalNeededBurstTx(uint32 totalBytesPerBurst, uint32 maxBurstBytesPerPacket);

        //Function: minTimeBetweenBursts
        //    Calculates the minimum amount of time allowed between bursts
        //
        //Parameters:
        //    totalNeededTx - The total needed transmissions for bursts
        //    sampleDuration - The sample duration
        //    lossless - Whether the network is using lossless or not
        //
        //Returns:
        //    The minimum amount of time allowed between bursts
        uint32 minTimeBetweenBursts(uint32 totalNeededTx, double sampleDuration, bool lossless);

        //Function: minTimeBetweenBursts
        //    Gets the minimum time that can be assigned for a Burst Sync Sampling session.
        //
        //Parameters:
        //    dataFormat - The <WirelessTypes::DataFormat> of the sampling session.
        //    numChannels - The number of active channels for the sampling session.
        //    sampleRate - The <SampleRate> that for the sampling session.
        //    sweepsPerBurst - The number of sweeps per burst for the sampling session.
        //
        //Returns:
        //    A <TimeSpan> representing the minimum time that can be assigned for a Burst Sync Sampling session.
        TimeSpan minTimeBetweenBursts(WirelessTypes::DataFormat dataFormat, uint8 numActiveChs, const mscl::SampleRate& sampleRate, uint32 sweepsPerBurst);

        //Function: burstTxPerSecond
        //    Calculates the burst transmissions per second
        //
        //Parameters:
        //    totalNeededTx - The total needed transmissions for bursts
        //    timeBetweenBursts - The time between each burst
        //    sampleDuration - The sample duration
        //    lossless - Whether the network is using lossless or not
        //
        //Returns:
        //    The burst transmissions per second
        uint32 burstTxPerSecond(uint32 totalNeededTx, uint32 timeBetweenBursts, double sampleDuration, bool lossless);
    }
#endif
}