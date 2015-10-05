/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include <chrono>
#include "mscl/Exceptions.h"
#include "WirelessPacketCollector.h"
#include "LdcPacket.h"
#include "SyncSamplingPacket.h"
#include "BufferedLdcPacket.h"
#include "LdcPacket_16ch.h"
#include "SyncSamplingPacket_16ch.h"
#include "BufferedLdcPacket_16ch.h"
#include "AsyncDigitalPacket.h"
#include "AsyncDigitalAnalogPacket.h"
#include "ShmPacket.h"
#include "HclSmartBearing_RawPacket.h"

namespace mscl
{
	WirelessPacketCollector::WirelessPacketCollector():
		m_dataPackets(MAX_DATA_BUFFER_SIZE),
		m_nodeDiscoveryPackets(MAX_DISCOVERY_BUFFER_SIZE)
	{
	}

	//required (if taken out, causes runtime error on destruction of WirelessPacketCollector)
	WirelessPacketCollector::~WirelessPacketCollector()
	{
	}

	void WirelessPacketCollector::addDataPacket(const WirelessPacket& packet)
	{
		//create a boost_lock for thread safety
		mutex_lock_guard lock(m_packetMutex);

		try
		{

			//add a different packet depending on its type
			switch(packet.type())
			{
				//Low Duty Cycle packet
				case WirelessPacket::packetType_LDC:
					m_dataPackets.push_back(LdcPacket(packet));
					break;

				//Sync Sampling Packet
				case WirelessPacket::packetType_SyncSampling:
					m_dataPackets.push_back(SyncSamplingPacket(packet));
					break;

				//Buffered LDC packet
				case WirelessPacket::packetType_BufferedLDC:
					m_dataPackets.push_back(BufferedLdcPacket(packet));
					break;

				//Low Duty Cycle with 16 channels packet
				case WirelessPacket::packetType_LDC_16ch:
					m_dataPackets.push_back(LdcPacket_16ch(packet));
					break;

				//Sync Sampling with 16 channels packet
				case WirelessPacket::packetType_SyncSampling_16ch:
					m_dataPackets.push_back(SyncSamplingPacket_16ch(packet));
					break;

				//Buffered LDC with 16 channels packet
				case WirelessPacket::packetType_BufferedLDC_16ch:
					m_dataPackets.push_back(BufferedLdcPacket_16ch(packet));
					break;

				//Asynchronous Digital packet
				case WirelessPacket::packetType_AsyncDigital:
					m_dataPackets.push_back(AsyncDigitalPacket(packet));
					break;

				//Asynchronous Digital/Analog packet
				case WirelessPacket::packetType_AsyncDigitalAnalog:
					m_dataPackets.push_back(AsyncDigitalAnalogPacket(packet));
					break;

				//Structural Health Monitor packet
				case WirelessPacket::packetType_SHM:
					m_dataPackets.push_back(ShmPacket(packet));
					break;

				//HclSmartBearing Raw packet
				case WirelessPacket::packetType_HclSmartBearing_Raw:
					m_dataPackets.push_back(HclSmartBearing_RawPacket(packet));
					break;

				//bad packet type, this function shouldn't have been called
				default:
					throw Error("Unknown Packet Type");
			}

			//notify the read thread, if it is waiting for data to be put into the buffer
			m_emptyBufferCondition.notify_one();
		}
		catch(Error&)
		{
			//there was an error building one of the packets, just return
		}
	}

	void WirelessPacketCollector::addNodeDiscoveryPacket(const WirelessPacket& packet)
	{
		//create a boost_lock for thread safety
		mutex_lock_guard lock(m_nodeDiscoveryMutex);

		//add a Node Discovery packet to the node discovery packet container
		m_nodeDiscoveryPackets.push_back( NodeDiscovery(packet) );
	}

	WirelessDataPacket WirelessPacketCollector::getNextDataPacket(int timeout)
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

		//Get the WirelessDataPacket to be returned as the result
		WirelessDataPacket resultPacket = m_dataPackets.front();

		//remove this packet from the front of the circular buffer (moves everything else in the array down one)
		m_dataPackets.pop_front();

		//return the WirelessDataPacket 
		return resultPacket;
	}

	void WirelessPacketCollector::getNextDataSweep(DataSweep& sweep, int timeout)
	{
		//if there are more sweeps to be read in the packet
		if(m_currentDataPacket.moreSweeps())
		{
			//get the next sweep in the current data packet
			m_currentDataPacket.getNextSweep(sweep);
		}
		else
		{
			//if we got here, m_currentDataPacket has no more sweeps

			//read the next WirelessDataPacket, store it in our m_currentDataPacket
			m_currentDataPacket = getNextDataPacket(timeout);

			//get the next sweep in the new data packet
			m_currentDataPacket.getNextSweep(sweep);
		}
	}

	void WirelessPacketCollector::getDataSweeps(std::vector<DataSweep>& sweeps, uint32 timeout, uint32 maxSweeps)
	{
		uint32 sweepCount = 0;

		//create a scoped_lock for thread safety
		std::unique_lock<std::mutex> lock(m_packetMutex);

		//while we still need to get more sweeps (or we want to get all the sweeps)
		while((sweepCount < maxSweeps) || (maxSweeps == 0))
		{
			//if there are no more sweeps in the current packet
			if(!m_currentDataPacket.moreSweeps())
			{
				//if there are no packets 
				if(m_dataPackets.size() <= 0)
				{
					//if there is a timeout and we haven't received any data
					if(timeout > 0 && sweepCount == 0)
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

				//set the current data packet to the next data packet in the buffer
				m_currentDataPacket = m_dataPackets.front();

				//remove this packet from the front of the circular buffer (moves everything else in the array down one)
				m_dataPackets.pop_front();
			}

			//add the next sweep to the result
			sweeps.push_back(DataSweep());
			m_currentDataPacket.getNextSweep(sweeps.back());

			sweepCount++;
		}
	}

	uint32 WirelessPacketCollector::totalSweeps()
	{
		size_t total = 0;

		//create a scoped_lock for thread safety
		mutex_lock_guard lock(m_packetMutex);

		//add the sweeps that are left to be read in the current data packet 
		total += m_currentDataPacket.numSweepsRemaining();

		circular_data_buffer::iterator itr;
		circular_data_buffer::iterator end = m_dataPackets.end();

		//loop over all the data packets that we have collected
		for(itr = m_dataPackets.begin(); itr != end; ++itr)
		{
			//add the sweeps of the data packet
			total += itr->numSweeps();
		}

		return static_cast<uint32>(total);
	}

	NodeDiscoveries WirelessPacketCollector::getNodeDiscoveries()
	{
		//create a scoped_lock for thread safety
		mutex_lock_guard lock(m_nodeDiscoveryMutex);

		NodeDiscoveries result;

		//loop through the buffer, removing items until it is empty
		while(!m_nodeDiscoveryPackets.empty())
		{
			//get the Node Discovery packet at the start of the buffer and store it in the result container
			result.push_back(m_nodeDiscoveryPackets.front());

			//remove the packet at the start of the buffer, move on to the next
			m_nodeDiscoveryPackets.pop_front();
		}

		//return the vector container
		return result;
	}
}