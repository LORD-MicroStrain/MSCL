/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/Communication/RawBytePacketCollector.h"

namespace mscl
{
    RawBytePacketCollector::RawBytePacketCollector() :
        m_rawBytePackets(MAX_DATA_BUFFER_SIZE)
    {}

    //required (if taken out, causes runtime error on destruction of WirelessPacketCollector)
    RawBytePacketCollector::~RawBytePacketCollector()
    {}

    void RawBytePacketCollector::requestRawBytePacketAddedNotification(std::function<void()> fnToCall)
    {
        m_notifyDataAddedFn = fnToCall;
    }

    void RawBytePacketCollector::addRawBytePacket(const RawBytePacket& packet)
    {
        //create a boost_lock for thread safety
        mutex_lock_guard lock(m_packetMutex);

        //add the data packet to the container
        m_rawBytePackets.push_back(packet);

        //call the notification function if its been set
        if (m_notifyDataAddedFn)
        {
            m_notifyDataAddedFn();
        }

        //notify the read thread, if it is waiting for data to be put into the buffer
        m_emptyBufferCondition.notify_one();
    }

    void RawBytePacketCollector::getRawBytePackets(RawBytePackets& packets, uint32 timeout, uint32 maxPackets)
    {
        uint32 packetCount = 0;

        //create a scoped_lock for thread safety
        std::unique_lock<std::mutex> lock(m_packetMutex);

        //while we still need to get more packets (or we want to get all the packets)
        while (packetCount < maxPackets || maxPackets == 0)
        {
            //if there are no more packets
            if (m_rawBytePackets.size() <= 0)
            {
                //if there is a timeout and we haven't recevied any data
                if (timeout > 0 && packetCount == 0)
                {
                    //wait for the timeout or data to come in
                    m_emptyBufferCondition.wait_for(lock, std::chrono::milliseconds(timeout));

                    //if there is no data (we timed out)
                    if (m_rawBytePackets.size() <= 0)
                    {
                        //break out of the while loop (we have no more data to give)
                        break;
                    }
                }
                //if there is no timeout, or if there is a timeout and we already got data
                else
                {
                    //break out of the while loop (we have no more data to give)
                    break;
                }
            }

            //add the RawBytePacket to the packets vector
            packets.push_back(m_rawBytePackets.front());
            packetCount++;

            //remove the packet from the front of the circular buffer (moves everything else in the array down one)
            m_rawBytePackets.pop_front();
        }
    }

    uint32 RawBytePacketCollector::totalPackets()
    {
        //return the number of packets in the buffer
        return static_cast<uint32>(m_rawBytePackets.size());
    }
} // namespace mscl
