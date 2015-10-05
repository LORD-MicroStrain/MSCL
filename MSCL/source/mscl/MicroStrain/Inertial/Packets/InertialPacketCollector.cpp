/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "InertialPacketCollector.h"

#include <chrono>
#include "mscl/Exceptions.h"

namespace mscl
{
	InertialPacketCollector::InertialPacketCollector()
		:m_dataPackets(MAX_DATA_BUFFER_SIZE)
	{
	}

	//required (if taken out, causes runtime error on destruction of WirelessPacketCollector)
	InertialPacketCollector::~InertialPacketCollector()
	{
	}

	void InertialPacketCollector::addDataPacket(const InertialPacket& packet)
	{
		//build a data packet from the InertialPacket
		InertialDataPacket dataPacket(packet);

		//create a boost_lock for thread safety
		mutex_lock_guard lock(m_packetMutex);

		//add the data packet to the container
		m_dataPackets.push_back(dataPacket);

		//notify the read thread, if it is waiting for data to be put into the buffer
		m_emptyBufferCondition.notify_one();
	}

	void InertialPacketCollector::getNextDataPacket(InertialDataPacket& packet, uint32 timeout)
	{
		//create a scoped_lock for thread safety
		std::unique_lock<std::mutex> lock(m_packetMutex);

		//if there is no data to read and there is a timeout
		if(m_dataPackets.size() <= 0 && timeout > 0)
		{
			//wait for the timeout or data to come in
			m_emptyBufferCondition.wait_for(lock, std::chrono::milliseconds(timeout));
		}
		
		//make sure there are packets in the container
		if(m_dataPackets.size() <= 0)
		{
			throw Error_NoData();
		}

		//Get the packet to be returned as the result
		packet = m_dataPackets.front();

		//remove this packet from the front of the circular buffer (moves everything else in the array down one)
		m_dataPackets.pop_front();
	}

	void InertialPacketCollector::getDataPackets(std::vector<InertialDataPacket>& packets, uint32 timeout, uint32 maxPackets)
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

			//add the InertialDataPacket to the packets vector
			packets.push_back(m_dataPackets.front());
			packetCount++;

			//remove the packet from the front of the circular buffer (moves everything else in the array down one)
			m_dataPackets.pop_front();
		}
	}

	uint32 InertialPacketCollector::totalPackets()
	{
		//return the number of packets in the buffer
		return static_cast<uint32>(m_dataPackets.size());
	}
}