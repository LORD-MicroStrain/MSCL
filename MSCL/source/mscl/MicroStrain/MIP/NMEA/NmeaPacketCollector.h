/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#pragma once

#include <condition_variable>
#include <boost/circular_buffer.hpp>

#include "NmeaPacket.h"

namespace mscl
{
    //Class: NmeaPacketCollector
    //    Class that sets/matches expected responses, and stores all the NMEA packets
    class NmeaPacketCollector
    {
    public:
        //Constructor: NmeaPacketCollector
        //    The default constructor for the NmeaPacketCollector
        NmeaPacketCollector();

        //Destructor: NmeaPacketCollector
        //    The destructor for the NmeaPacketCollector
        ~NmeaPacketCollector();

        NmeaPacketCollector(const NmeaPacketCollector&) = delete;             //copy constructor disabled
        NmeaPacketCollector& operator=(const NmeaPacketCollector&) = delete;  //assignment operator disabled

    private:
        //Typedef: circular_data_buffer
        //    Typedef for a circular buffer of a <NmeaPacket>
        typedef boost::circular_buffer_space_optimized<NmeaPacket> circular_data_buffer;

        //Constant: MAX_DATA_BUFFER_SIZE = 1024 * 100
        //    The maximum number of data packets that can be stored in the circular buffer
        static const int MAX_DATA_BUFFER_SIZE = 1024 * 100;

    private:
        //Variable: m_dataPackets
        //    A circular buffer that holds <NmeaPacket>s 
        circular_data_buffer m_packets;

        //Variable: m_packetMutex
        //    A mutex used for thread safety when accessing/modifying the m_dataPackets buffer
        std::mutex m_packetMutex;

        //Variable: m_emptyBufferCondition
        //    Allows the write to buffer thread to tell the reading thread when data is available
        std::condition_variable m_emptyBufferCondition;

        //Variable: m_notifyDataAddedFn
        //  The function to call when data packets are added.
        std::function<void()> m_notifyDataAddedFn;

    public:
        //Function: requestDataAddedNotification
        //  Register a function to call when data packets arrive
        void requestDataAddedNotification(std::function<void()> fnToCall);

        //Function: addDataPacket
        //    Adds a data packet to the data packets circular buffer
        //
        //Parameters:
        //    packet - The <NmeaPacket> to be added to the buffer
        void addPacket(const NmeaPacket& packet);

        //Function: getDataPackets
        //    Gets up to the requested amount of data packets that have been collected.
        //
        //Parameters:
        //    packets - A vector of <NmeaPacket> to hold the result.
        //    maxPackets - The maximum number of packets to return. If this is 0 (default), all sweeps will be returned.
        void getPackets(std::vector<NmeaPacket>& packets, uint32 timeout = 0, uint32 maxPackets = 0);

        //Function: totalPackets
        //    Gets the total number of data packets that are currently in the buffer.
        //
        //Returns:
        //    The total number of data packets that are currently in the buffer.
        uint32 totalPackets();
    };
}