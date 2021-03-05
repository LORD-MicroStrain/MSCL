/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include <memory>

#include "mscl/MicroStrain/SampleRate.h"
#include "mscl/Timestamp.h"
#include "WirelessDataPoint.h"
#include "WirelessTypes.h"

namespace mscl
{
    //API Class: DataSweep
    //    Represents 1 data sweep, including data for each channel, a timestamp, and a sample rate
    class DataSweep
    {
    public:

        //============================================================================
        //API Enums: SamplingType
        //    samplingType_NonSync                   - 0 - NonSynchronized sampling type
        //    samplingType_NonSync_Buffered          - 1 - Buffered NonSynchronized sampling type
        //    samplingType_SyncSampling              - 2 - Synchronized Sampling sampling type
        //    samplingType_SyncSampling_Burst        - 3 - Synchronized Sampling Burst sampling type
        //    samplingType_AsyncDigital              - 4 - Asynchronous Digital sampling type
        //    samplingType_AsyncDigitalAnalog        - 5 - Asynchronous Digital + Analog sampling type
        //    samplingType_SHM                       - 6 - Structural Health Monitoring type
        //    samplingType_BeaconEcho                - 7 - Beacon Echo
        //    samplingType_RfSweep                   - 8 - RF Scan Sweep
        //    samplingType_Diagnostic                - 9 - Diagnostic Packet
        //============================================================================
        enum SamplingType
        {
            samplingType_NonSync                    = 0,
            samplingType_NonSync_Buffered           = 1,
            samplingType_SyncSampling               = 2,
            samplingType_SyncSampling_Burst         = 3,
            samplingType_AsyncDigital               = 4,
            samplingType_AsyncDigitalAnalog         = 5,
            samplingType_SHM                        = 6,
            samplingType_BeaconEcho                 = 7,
            samplingType_RfSweep                    = 8,
            samplingType_Diagnostic                 = 9
        };

        //API Constructor: DataSweep
        //    Creates a default constructed DataSweep.
        DataSweep();

    private:
        //Variable: m_timestamp
        //    The <Timestamp> of the data sweep.
        Timestamp m_timestamp;

        //Variable: m_tick
        //    The tick value that was contained in the packet (increments for each sweep)
        uint32 m_tick;

        //Variable: m_sampleRate
        //    The <SampleRate> that was contained in the packet
        SampleRate m_sampleRate;

        //Variable: m_nodeAddress
        //    The node address that was contained in the packet (identifies the node this packet came from)
        NodeAddress m_nodeAddress;

        //Variable: m_data
        //    Contains one or more <WirelessDataPoint>s, corresponding to each channel's data for this sweep
        ChannelData m_data;

        //Variable: m_samplingMode
        //    The <SamplingType> that identifies the sampling mode for this data sweep 
        SamplingType m_samplingMode;

        //Variable:: m_nodeRssi
        //    The Node RSSI that identifies the received signal strength at the Node
        int16 m_nodeRssi;

        //Variable: m_baseRssi
        //    The Base Station RSSI that identifies the received signal strength at the Base Station
        int16 m_baseRssi;

        //Variable: m_frequency
        //    The <WirelessTypes::Frequency> representing the radio frequency that this DataSweep was collected on
        WirelessTypes::Frequency m_frequency;

        //Variable: m_calsApplied
        //  Whether calibration coefficients have been applied to the data or not.
        bool m_calsApplied;

    public:
        //API Function: timestamp
        //    Gets the timestamp of the sweep as a <Timestamp>
        //
        //Returns:
        //    A <Timestamp> representing the timestamp of the sweep
        const Timestamp& timestamp() const;

        //API Function: tick
        //    Gets the tick value of the sweep
        //
        //Returns:
        //    The tick value of the sweep
        uint32 tick() const;

        //API Function: sampleRate
        //    Gets the sample rate of the sweep as a <SampleRate>
        //
        //Returns:
        //    A <SampleRate> representing the sample rate of the sweep
        SampleRate sampleRate() const;

        //API Function: nodeAddress
        //    Gets the node address that this sweep is associated with
        //
        //Returns:
        //    The node address this sweep is associated with
        NodeAddress nodeAddress() const;

        //API Function: data
        //    Gets the channel data in this sweep as a <WirelessDataPoint::ChannelData> container.
        //
        //Returns:
        //    A <WirelessDataPoint::ChannelData> container holding the data for the sweep.
        const ChannelData& data() const;

        //API Function: samplingType
        //    Gets the <SamplingType> for this sweep
        //
        //Returns:
        //    A <SamplingType> enum representing the sampling type of this sweep
        SamplingType samplingType() const;

        //API Function: nodeRssi
        //    Gets the Node RSSI value that identifies the received signal strength at the Node
        //
        //Returns:
        //    The Node RSSI value that identifies the received signal strength at the Node
        int16 nodeRssi() const;

        //API Function: baseRssi
        //    Gets the Base Station RSSI value that identifies the received signal strength at the BaseStation for this sweep
        //
        //Returns:
        //    The Base Station RSSI value that identifies the received signal strength at the Base Station for this sweep
        int16 baseRssi() const;

        //API Function: frequency
        //    Gets the radio frequency that this DataSweep was collected on
        //
        //Returns:
        //    A <WirelessTypes::Frequency> representing the radio frequency that this DataSweep was collected on
        WirelessTypes::Frequency frequency() const;

        //API Function: calApplied
        //  Gets whether calibration coefficients have been applied to the data already.
        //
        //Returns:
        //  true if the data already has cal coefficients applied to it, false if it does not have any cal coefficients applied.
        bool calApplied() const;

#ifndef SWIG
        //Function: timestamp
        //    Sets the timestamp of the sweep
        //
        //Parameters:
        //    time - The <Timestamp> to set
        void timestamp(const Timestamp& time);

        //Function: tick
        //    Sets the tick of the sweep
        //
        //Parameters:
        //    tick - The tick to set
        void tick(uint32 tick);

        //Function: sampleRate
        //    Sets the sample rate of the sweep
        //
        //Parameters:
        //    rate - The <SampleRate> to set
        void sampleRate(SampleRate rate);

        //Function: nodeAddress
        //    Sets the node address of the sweep
        //
        //Parameters:
        //    address - The node address to set
        void nodeAddress(NodeAddress address);

        //Function: data
        //    Sets the data of the sweep
        //
        //Parameters:
        //    data - The <ChannelData> to set
        void data(const ChannelData& data);

        //Function: samplingMode
        //    Sets the sampling mode of the sweep
        //
        //Parameters:
        //    mode - The <SamplingType> to set
        void samplingType(SamplingType type);

        //Function: nodeRssi
        //    Sets the Node RSSI value that identifies the received signal strength at the Node
        //
        //Parameters:
        //    rssi - The Node RSSI to set
        void nodeRssi(int16 rssi);

        //Function: baseRssi
        //    Sets the Base Station RSSI value that identifies the received signal strength at the Base Station for this sweep
        //
        //Parameters:
        //    rssi - The Base Station RSSI to set
        void baseRssi(int16 rssi);

        //Function: frequency
        //    Sets the radio frequency that this DataSweep was collected on
        //
        //Parameters:
        //    freq - The <WirelessTypes::Frequency> that this DataSweep was collected on
        void frequency(WirelessTypes::Frequency freq);

        //Function: calApplied
        //  Sets whether calibration coefficients have been applied to the data already.
        //
        //Parameters:
        //  applied - Whether the cals have been applied or not.
        void calApplied(bool applied);
#endif
    };

    //API Typedef: DataSweeps
    //    Typedef for a vector of <DataSweep> objects.
    typedef std::vector<DataSweep> DataSweeps;

}
