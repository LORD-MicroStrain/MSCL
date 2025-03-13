/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "MipPacketCollector.h"

#include <chrono>
#include "mscl/Exceptions.h"

namespace mscl
{
    MipPacketCollector::MipPacketCollector():
        m_dataPackets(MAX_DATA_BUFFER_SIZE)
    {
    }

    //required (if taken out, causes runtime error on destruction of WirelessPacketCollector)
    MipPacketCollector::~MipPacketCollector()
    {
    }

    void MipPacketCollector::adjustPacketTimestamp(MipDataPacket& packet)
    {
        MipTypes::DataClass packetDataClass = static_cast<MipTypes::DataClass>(packet.descriptorSet());

        if(!packet.hasDeviceTime())
        {
            //if we aren't getting time fields in every packet, we want to clear out the last time field we stored
            //so that we don't end up with some points being spaced out differently than others
            m_previousPackets.erase(packetDataClass);

            //packet doesn't have any time fields in it, nothing we can use to adjust (best is time of arrival)
            return;
        }

        //now we know the new packet has a device time in it's packet so let's try to use
        //it to correct bunched up pc collected timestamps caused by buffering

        try
        {
            //find the last packet in the same DataClass as this packet
            const MipDataPacket& lastPacket = m_previousPackets.at(packetDataClass);

            //if the last packet didn't have a time field included in it
            if(!lastPacket.hasDeviceTime())
            {
                //this packet has a time field if we got this far, so store this for the next packet to be incremented from
                m_previousPackets[packetDataClass] = packet;

                //we can't adjust anything because we don't have a previous packet device time
                return;
            }

            const uint64 newDeviceTime = packet.deviceTimestamp().nanoseconds();
            const uint64 lastDeviceTime = lastPacket.deviceTimestamp().nanoseconds();

            //if this packet's timestamp is before the previous packet's timestamp (went back in time)
            if(newDeviceTime < lastDeviceTime)
            {
                //nothing we can adjust (use time of arrival)
                m_previousPackets[packetDataClass] = packet;
                return;
            }

            //the time between the device time in the last packet, and the device time in the new packet
            uint64 deltaDeviceTime = newDeviceTime - lastDeviceTime;

            //add the deltaDeviceTime to the last packet's PC collected timestamp
            uint64 updatedPcTime = lastPacket.collectedTimestamp().nanoseconds() + deltaDeviceTime;

            //calculate the difference between the updated pc time (calculated from deltaDeviceTime), and the pc collected time that was assigned to the new packet
            uint64 packetCollectedTime = packet.collectedTimestamp().nanoseconds();
            uint64 diff = (updatedPcTime < packetCollectedTime) ? (packetCollectedTime - updatedPcTime) : (updatedPcTime - packetCollectedTime);

            //if the difference between the calculated pc time, and the collected pc time is greater than we'd expect
            const uint64 MAX_DELTA_BETWEEN_ESTIMATE_AND_PC_TIME = 500000000; //0.5 seconds   //TODO: does this number need to be adjusted?
            if(diff > MAX_DELTA_BETWEEN_ESTIMATE_AND_PC_TIME)
            {
                //nothing we can adjust (use time of arrival)
                m_previousPackets[packetDataClass] = packet;
                return;
            }

            //we made it! we have all the info we need to adjust the pc collected timestamp
            const double FILTER_CONSTANT = 0.999;
            packet.m_collectedTime.setTime(static_cast<uint64>( FILTER_CONSTANT * static_cast<double>(updatedPcTime) + (1.0 - FILTER_CONSTANT) * static_cast<double>(packet.collectedTimestamp().nanoseconds()) ));

            //TODO: ok to just cast to uint64 above, or do I need to round?
            //TODO: ok to cast the uint64 nanoseconds to doubles above?

            m_previousPackets[packetDataClass] = packet;
        }
        catch(std::out_of_range&)
        {
            //we didn't have a last packet stored for this DataClass, store this one
            m_previousPackets[packetDataClass] = packet;
        }
    }

    void MipPacketCollector::requestDataAddedNotification(std::function<void()> fnToCall)
    {
        m_notifyDataAddedFn = fnToCall;
    }

    void MipPacketCollector::addDataPacket(const MipPacket& packet)
    {
        //build a data packet from the MipPacket
        MipDataPacket dataPacket(packet);

        adjustPacketTimestamp(dataPacket);

        //create a boost_lock for thread safety
        mutex_lock_guard lock(m_packetMutex);

        //add the data packet to the container
        m_dataPackets.push_back(dataPacket);

        //call the notification function if its been set
        if(m_notifyDataAddedFn)
        {
            m_notifyDataAddedFn();
        }

        //notify the read thread, if it is waiting for data to be put into the buffer
        m_emptyBufferCondition.notify_one();
    }

    void MipPacketCollector::getDataPackets(std::vector<MipDataPacket>& packets, uint32 timeout, uint32 maxPackets)
    {
        uint32 packetCount = 0;

        //create a scoped_lock for thread safety
        std::unique_lock<std::mutex> lock(m_packetMutex);

        //while we still need to get more packets (or we want to get all the packets)
        while((packetCount < maxPackets) || (maxPackets == 0))
        {
            //if there are no more packets
            if(m_dataPackets.size() <= 0)
            {
                //if there is a timeout and we haven't recevied any data
                if(timeout > 0 && packetCount == 0)
                {
                    //wait for the timeout or data to come in
                    m_emptyBufferCondition.wait_for(lock, std::chrono::milliseconds(timeout));

                    //if there is no data (we timed out)
                    if(m_dataPackets.size() <= 0)
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

            //add the MipDataPacket to the packets vector
            packets.push_back(m_dataPackets.front());
            packetCount++;

            //remove the packet from the front of the circular buffer (moves everything else in the array down one)
            m_dataPackets.pop_front();
        }
    }

    uint32 MipPacketCollector::totalPackets()
    {
        //return the number of packets in the buffer
        return static_cast<uint32>(m_dataPackets.size());
    }
}
