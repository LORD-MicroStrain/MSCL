/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include <condition_variable>
#include <boost/circular_buffer.hpp>

#include "WirelessDataPacket.h"
#include "mscl/MicroStrain/Wireless/NodeDiscovery.h"

namespace mscl
{
    //Class: WirelessPacketCollector
    //    Class that sets/matches expected responses, and stores all the wireless packets
    class WirelessPacketCollector
    {
    public:
        //Typedefs: 
        //    circular_data_buffer - Typedef for a circular buffer of a <WirelessDataPacket>
        //    circular_discovery_buffer - Typedef for a circular buffer of <NodeDiscovery> objects
        typedef boost::circular_buffer_space_optimized<WirelessDataPacket> circular_data_buffer;
        typedef boost::circular_buffer_space_optimized<NodeDiscovery> circular_discovery_buffer;

    private:
        //Constants: 
        //    MAX_DATA_BUFFER_SIZE        - 1024 * 100    -The maximum number of data packets that can be stored in the circular buffer
        //    MAX_DISCOVERY_BUFFER_SIZE    - 100            -The maximum number of node discovery packets that can be stored in the circular buffer
        static const uint32 MAX_DATA_BUFFER_SIZE        = 1024 * 100; 
        static const uint32 MAX_DISCOVERY_BUFFER_SIZE    = 100;

    public:
        //Constructor: WirelessPacketCollector
        //    The default constructor for the WirelessPacketCollector
        WirelessPacketCollector();

        //Destructor: WirelessPacketCollector
        //    The destructor for the WirelessPacketCollector
        ~WirelessPacketCollector();

    private:
        WirelessPacketCollector(const WirelessPacketCollector&);                //copy constructor disabled
        WirelessPacketCollector& operator=(const WirelessPacketCollector&);        //assignement operator disabled

    private:
        //Variable: m_dataPackets
        //    A circular buffer that holds <WirelessDataPacket>s 
        circular_data_buffer m_dataPackets;

        //Variable: m_nodeDiscoveryPackets
        //    A circular buffer that holds <NodeDiscovery> objects
        circular_discovery_buffer m_nodeDiscoveryPackets;

        //Variable: m_currentDataPacket
        //    The current <WirelessDataPacket> in the buffer
        WirelessDataPacket m_currentDataPacket;

        //Variable: m_packetMutex
        //    A mutex used for thread safety when accessing/modifying the <m_dataPackets> buffer
        std::mutex m_packetMutex;

        //Variable: m_nodeDiscoveryMutex
        //    A mutex used for thread safety when accessing/modifying the <m_nodeDiscoveryPackets> buffer
        std::mutex m_nodeDiscoveryMutex;

        //Variable: m_emptyBufferCondition
        //    Allows the write to buffer thread to tell the reading thread when data is available
        std::condition_variable m_emptyBufferCondition;

    public:
        //Function: addDataPacket
        //    Adds a data packet to the data packets circular buffer.
        //
        //Parameters:
        //    packet - The <WirelessPacket> to be added to the buffer.
        void addDataPacket(const WirelessPacket& packet);

        //Function: addNodeDiscoveryPacket
        //    Adds a Node Discovery packet to the circular buffer.
        //    The provided WirelessPacket must be a valid Node Discovery packet.
        //
        //Parameters:
        //    packet - The <WirelessPacket> to be added to the buffer.
        void addNodeDiscoveryPacket(const WirelessPacket& packet);

        //Function: getDataSweeps
        //    Gets up to the requested amount of data sweeps that have been collected.
        //    
        //Parameters:
        //    sweeps - A vector of <DataSweep> objects to hold the result.
        //    timeout - The timeout, in milliseconds, to wait for data if necessary (default of 0).
        //    maxSweeps - The maximum number of sweeps to return. If this is 0 (default), all sweeps will be returned.
        void getDataSweeps(std::vector<DataSweep>& sweeps, uint32 timeout = 0, uint32 maxSweeps = 0);

        //Function: totalSweeps
        //    Gets the total number of data sweeps that are currently in the buffer.
        //
        //Returns:
        //    The total number of data sweeps that are currently in the buffer.
        uint32 totalSweeps();

        //Function: getNodeDiscoveries
        //    Gets a vector of <NodeDiscovery> objects that were collected
        //
        //Returns:
        //    A <NodeDiscoveries> object contain all the NodeDiscovery objects that were collected
        NodeDiscoveries getNodeDiscoveries();

    private:
        //Function: getNextDataPacket
        //    Gets the next WirelessDataPacket in the buffer
        //
        //Parameters:
        //    timeout - the timeout, in milliseconds, to wait for the next data packet if necessary
        //
        //Returns:
        //    The next WirelessDataPacket that was collected
        //
        //Exceptions:
        //    - <Error_NoData>: There are no more data packets to obtain
        WirelessDataPacket getNextDataPacket(int timeout);
    };
}