/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "SyncNodeConfig.h"

#include "mscl/MicroStrain/Wireless/WirelessModels.h"
#include "mscl/MicroStrain/Wireless/SyncNetworkInfo.h"
#include "mscl/MicroStrain/SampleUtils.h"
#include "WirelessNodeConfig.h"

namespace mscl
{
	SyncNodeConfig::SyncNodeConfig(const SyncNetworkInfo* networkInfo):
		m_networkInfo(networkInfo),
		m_eepromHelper(networkInfo->m_node.eepromHelper())
	{
	}

	SampleRate SyncNodeConfig::sampleRate()
	{
		WirelessTypes::WirelessSampleRate sampleRateVal;

		try
		{
			//try to read the value from the pending config
			sampleRateVal = m_networkInfo->getPendingConfig().sampleRate();
		}
		catch(Error_NoData&)
		{
			//not set in the config, read the value from eeprom
			sampleRateVal = m_eepromHelper.read_sampleRate(WirelessTypes::samplingMode_sync);
		}

		//convert to a SampleRate object and return
		return SampleUtils::convertToSampleRate(sampleRateVal);
	}

	ChannelMask SyncNodeConfig::activeChannels()
	{
		try
		{
			//try to read the value from the pending config
			return m_networkInfo->getPendingConfig().activeChannels();
		}
		catch(Error_NoData&)
		{
			//not set in the config, read the value from eeprom
			return m_eepromHelper.read_channelMask();
		}
	}

	WirelessTypes::DataFormat SyncNodeConfig::dataFormat()
	{
		try
		{
			//try to read the value from the pending config
			return m_networkInfo->getPendingConfig().dataFormat();
		}
		catch(Error_NoData&)
		{
			//not set in the config, read the value from eeprom
			return m_eepromHelper.read_dataFormat();
		}
	}

	WirelessTypes::DataCollectionMethod SyncNodeConfig::collectionMethod()
	{
		try
		{
			//try to read the value from the pending config
			return m_networkInfo->getPendingConfig().dataCollectionMethod();
		}
		catch(Error_NoData&)
		{
			//not set in the config, read the value from eeprom
			return m_eepromHelper.read_collectionMode();
		}
	}

	uint32 SyncNodeConfig::sweepsPerSession()
	{
		try
		{
			//try to read the value from the pending config
			return m_networkInfo->getPendingConfig().numSweeps();
		}
		catch(Error_NoData&)
		{
			//not set in the config, read the value from eeprom
			return m_eepromHelper.read_numSweeps();
		}
	}

	WirelessTypes::SyncSamplingMode SyncNodeConfig::syncSamplingMode()
	{
		try
		{
			//try to read the value from the pending config
			WirelessTypes::SamplingMode samplingMode = m_networkInfo->getPendingConfig().samplingMode();
			
			//the sampling config only has the WirelessTypes::SamplingMode, so we need
			//to convert it to the corresponding WirelessTypes::SyncSamplingMode 
			switch(samplingMode)
			{
			case WirelessTypes::samplingMode_syncBurst:
				return WirelessTypes::syncMode_burst;

			case WirelessTypes::samplingMode_sync:
			default:
				return WirelessTypes::syncMode_continuous;
			}
		}
		catch(Error_NoData&)
		{
			//read the value from eeprom
			return m_eepromHelper.read_syncSamplingMode();
		}
	}

	WirelessTypes::SamplingMode SyncNodeConfig::samplingMode()
	{
		try
		{
			//try to read the value from the pending config
			return m_networkInfo->getPendingConfig().samplingMode();
		}
		catch(Error_NoData&)
		{
			//read the value from eeprom
			return m_eepromHelper.read_samplingMode();
		}
	}

	TimeSpan SyncNodeConfig::samplingDelay()
	{
		//not part of sampling configuration

		//read the value from eeprom
		return m_eepromHelper.read_samplingDelay();
	}

	TimeSpan SyncNodeConfig::timeBetweenBursts()
	{
		try
		{
			//try to read the value from the pending config
			return m_networkInfo->getPendingConfig().timeBetweenBursts();
		}
		catch(Error_NoData&)
		{
			//read the value from eeprom
			return m_eepromHelper.read_timeBetweenBursts();
		}
	}

	WirelessTypes::NodeRetransmission SyncNodeConfig::retransmission()
	{
		//not part of sampling configuration

		//read the value from eeprom
		return m_eepromHelper.read_retransmission();
	}

	WirelessTypes::SettlingTime SyncNodeConfig::filter1()
	{
		//read the value from eeprom
		return m_eepromHelper.read_filter1();
	}

	WirelessTypes::SettlingTime SyncNodeConfig::filter2()
	{
		//read the value from eeprom
		return m_eepromHelper.read_filter2();
	}

	void SyncNodeConfig::txPerGroup(uint32 txPerGroup)
	{
		//write the transmissions per group value to eeprom
		m_eepromHelper.write_txPerGroup(static_cast<uint16>(txPerGroup));
	}

	void SyncNodeConfig::groupSize(uint32 groupSize)
	{
		//write the group size value to eeprom
		m_eepromHelper.write_groupSize(static_cast<uint16>(groupSize));
	}

	void SyncNodeConfig::tdmaAddress(uint32 address)
	{
		//write the TDMA address to eeprom
		m_eepromHelper.write_tdmaAddress(static_cast<uint16>(address));
	}

	void SyncNodeConfig::retransmission(WirelessTypes::NodeRetransmission reTx)
	{
		//write the retransmission option to eeprom
		m_eepromHelper.write_retransmission(reTx);
	}

	void SyncNodeConfig::maxRetransPerBurst(uint32 maxReTxPerBurst)
	{
		//write the max retransmissions per burst to eeprom
		m_eepromHelper.write_maxRetransPerBurst(static_cast<uint16>(maxReTxPerBurst));
	}
}