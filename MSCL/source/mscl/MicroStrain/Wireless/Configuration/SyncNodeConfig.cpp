/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

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

    uint16 SyncNodeConfig::activeChannelCount()
    {
        ChannelMask mask = activeChannels();

        uint16 totalChannelCount = mask.count();

        WirelessModels::NodeModel model = m_networkInfo->m_model;

        //if this is the iepe-link, and channel 4 (temp) is enabled
        if(mask.enabled(4) && model == WirelessModels::node_iepeLink)
        {
            //channel 4 doesn't count as a channel in calculations (it transmits at a rate of once per burst)
            totalChannelCount -= 1;
        }

        return totalChannelCount;
    }

    WirelessTypes::CommProtocol SyncNodeConfig::commProtocol()
    {
        try
        {
            //try to read the value from the pending config
            return m_networkInfo->getPendingConfig().communicationProtocol();
        }
        catch(Error_NoData&)
        {
            //not set in the config, read the value from eeprom
            return m_eepromHelper.read_commProtocol();
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

    uint32 SyncNodeConfig::sensorDelay()
    {
        try
        {
            //try to read the value from the pending config
            return m_networkInfo->getPendingConfig().sensorDelay();
        }
        catch(Error_NoData&)
        {
            //read the value from eeprom
            return m_eepromHelper.read_sensorDelay();
        }
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

    WirelessTypes::SettlingTime SyncNodeConfig::filterSettlingTime(uint8 channelNumber)
    {
        ChannelMask mask;
        
        //find the ChannelMask for the filterSettlingTime that contains the requested channel number
        auto groups = m_networkInfo->channelGroups();
        for(auto i : groups)
        {
            if(i.hasSetting(mscl::WirelessTypes::chSetting_filterSettlingTime))
            {
                if(i.channels().enabled(channelNumber))
                {
                    mask = i.channels();
                }
            }
        }

        try
        {
            //try to read the value from the pending config
            return m_networkInfo->getPendingConfig().filterSettlingTime(mask);
        }
        catch(Error_NoData&)
        {
            //read the value from eeprom
            return m_eepromHelper.read_settlingTime(mask);
        }
    }

    DataModeMask SyncNodeConfig::dataMode()
    {
        try
        {
            //try to read the value from the pending config
            return DataModeMask(m_networkInfo->getPendingConfig().dataMode());
        }
        catch(Error_NoData&)
        {
            return DataModeMask(m_eepromHelper.read_dataMode());
        }
    }

    SampleRate SyncNodeConfig::derivedDataRate()
    {
        WirelessTypes::WirelessSampleRate sampleRateVal;

        try
        {
            //try to read the value from the pending config
            sampleRateVal = m_networkInfo->getPendingConfig().derivedDataRate();
        }
        catch(Error_NoData&)
        {
            sampleRateVal = m_eepromHelper.read_derivedSampleRate();
        }

        return SampleUtils::convertToSampleRate(sampleRateVal);
    }

    ChannelMask SyncNodeConfig::derivedChannelMask(WirelessTypes::DerivedCategory category)
    {
        try
        {
            //try to read the value from the pending config
            return m_networkInfo->getPendingConfig().derivedChannelMask(category);
        }
        catch(Error_NoData&)
        {
            return m_eepromHelper.read_derivedChannelMask(category);
        }
    }

    uint16 SyncNodeConfig::diagnosticInterval()
    {
        try
        {
            return m_networkInfo->getPendingConfig().diagnosticInterval();
        }
        catch(Error_NoData&)
        {
            return m_eepromHelper.read_diagnosticInterval();
        }
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

    void SyncNodeConfig::applyEepromChanges()
    {
        m_eepromHelper.applyEepromChanges();
    }
}