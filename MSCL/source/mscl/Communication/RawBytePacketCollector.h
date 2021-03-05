/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include <condition_variable>
#include <boost/circular_buffer.hpp>

#include "RawBytePacket.h"


namespace mscl
{
    //Class: RawBytePacketCollector
    //    Class that sets/matches expected responses, and stores all the Inertial packets
    class RawBytePacketCollector
    {
    public:
        //Constructor: RawBytePacketCollector
        //    The default constructor for the RawBytePacketCollector
        RawBytePacketCollector();

        //Destructor: RawBytePacketCollector
        //    The destructor for the RawBytePacketCollector
        ~RawBytePacketCollector();

        RawBytePacketCollector(const RawBytePacketCollector&) = delete;             //copy constructor disabled
        RawBytePacketCollector& operator=(const RawBytePacketCollector&) = delete;  //assignment operator disabled

    private:
        //Typedef: circular_data_buffer
        //    Typedef for a circular buffer of a <MipDataPacket>
        typedef boost::circular_buffer_space_optimized<RawBytePacket> circular_data_buffer;

        //Constant: MAX_DATA_BUFFER_SIZE = 1024 * 100
        //    The maximum number of raw byte packets that can be stored in the circular buffer
        static const int MAX_DATA_BUFFER_SIZE = 1024 * 100;

    private:
        //Variable: m_rawBytePackets
        //    A circular buffer that holds <RawBytePacket>s 
        circular_data_buffer m_rawBytePackets;

        //Variable: m_packetMutex
        //    A mutex used for thread safety when accessing/modifying the m_rawBytePackets buffer
        std::mutex m_packetMutex;

        //Variable: m_emptyBufferCondition
        //    Allows the write to buffer thread to tell the reading thread when data is available
        std::condition_variable m_emptyBufferCondition;

        //Variable: m_notifyDataAddedFn
        //  The function to call when raw byte packets are added.
        std::function<void()> m_notifyDataAddedFn;

    public:
        //Function: requestRawBytePacketAddedNotification
        //  Register a function to call when raw byte packets arrive
        void requestRawBytePacketAddedNotification(std::function<void()> fnToCall);

        //Function: addRawBytePacket
        //    Adds a raw byte packet to the raw byte packets circular buffer
        //
        //Parameters:
        //    packet - The <MipPacket> to be added to the buffer
        void addRawBytePacket(const RawBytePacket& packet);

        //Function: getRawBytePackets
        //    Gets up to the requested amount of raw byte packets that have been collected.
        //
        //Parameters:
        //    packets - A vector of <RawBytePackets> to hold the result.
        //    maxPackets - The maximum number of packets to return. If this is 0 (default), all sweeps will be returned.
        void getRawBytePackets(RawBytePackets& packets, uint32 timeout = 0, uint32 maxPackets = 0);

        //Function: totalPackets
        //    Gets the total number of raw byte packets that are currently in the buffer.
        //
        //Returns:
        //    The total number of raw byte packets that are currently in the buffer.
        uint32 totalPackets();
    };
}