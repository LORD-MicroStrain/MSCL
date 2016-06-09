/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include <iomanip>

#include "mscl/ScopeHelper.h"
#include "mscl/Utils.h"
#include "WirelessNode_Impl.h"
#include "Features/NodeInfo.h"
#include "Features/NodeFeatures.h"
#include "Commands/WirelessProtocol.h"
#include "Configuration/NodeEeprom.h"
#include "Configuration/NodeEepromMap.h"
#include "Configuration/WirelessNodeConfig.h"
#include "NodeCommTimes.h"

namespace mscl
{
    WirelessNode_Impl::WirelessNode_Impl(uint16 nodeAddress, const BaseStation& basestation):
        m_address(checked_cast<NodeAddress>(nodeAddress, "Node Address")),
        m_baseStation(basestation),
        m_eepromHelper(new NodeEepromHelper(this))
    {
    }

    std::unique_ptr<WirelessProtocol> WirelessNode_Impl::determineProtocol() const
    {
        Version fwVersion;

        NodeEepromSettings tempSettings = m_eepromSettings;
        tempSettings.numRetries = 0;

        bool success = false;
        uint8 retryCount = 0;

        do
        {
            //=========================================================================
            // Determine the firmware version by attempting to use multiple protocols
            try
            {
                //try reading with protocol v1.1
                m_protocol = WirelessProtocol::v1_1();

                //set the NodeEeprom with the temporary protocol
                m_eeprom.reset(new NodeEeprom(m_address, m_baseStation, *(m_protocol.get()), tempSettings));

                fwVersion = firmwareVersion();
                success = true;
            }
            catch(Error_Communication&)
            {
                //Failed reading with protocol v1.1 - Now try v1.0

                //we know this uses the same group read (page download) as the previous protocol, so skip it
                tempSettings.useGroupRead = false;

                try
                {
                    //try reading with protocol v1.0
                    m_protocol = WirelessProtocol::v1_0();

                    //set the NodeEeprom with the temporary protocol
                    m_eeprom.reset(new NodeEeprom(m_address, m_baseStation, *(m_protocol.get()), tempSettings));

                    fwVersion = firmwareVersion();
                    success = true;
                }
                catch(Error_Communication&)
                {
                    //if this was the last retry
                    if(retryCount >= m_eepromSettings.numRetries)
                    {
                        //we failed to determine the protocol
                        //need to clear out the protocol and eeprom variables
                        m_protocol.reset();
                        m_eeprom.reset();

                        //rethrow the exception
                        throw;
                    }
                }
            }
            //=========================================================================
        }
        while(!success && (retryCount++ < m_eepromSettings.numRetries));

        //get the protocol to use for the node's fw version
        return WirelessProtocol::chooseNodeProtocol(fwVersion);
    }

    NodeEeprom& WirelessNode_Impl::eeprom() const
    {
        //if the eeprom variable hasn't been set yet
        if(m_eeprom == NULL)
        {
            //create the eeprom variable
            //Note that this requires communicating with the Node via the protocol() function
            m_eeprom.reset(new NodeEeprom(m_address, m_baseStation, protocol(), m_eepromSettings));
        }

        return *(m_eeprom.get());
    }

    NodeEepromHelper& WirelessNode_Impl::eeHelper() const
    {
        return *(m_eepromHelper.get());
    }

    const NodeFeatures& WirelessNode_Impl::features() const
    {
        //if the features variable hasn't been set yet
        if(m_features == NULL)
        {
            //create the NodeInfo to give to the features
            NodeInfo info(this);

            //set the features variable by creating a new NodeFeatures pointer
            m_features = NodeFeatures::create(info);
        }

        return *(m_features.get());
    }

    const WirelessProtocol& WirelessNode_Impl::protocol() const
    {
        //if the protocol variable hasn't been set yet
        if(m_protocol == NULL)
        {
            //determine and assign the protocol for this BaseStation
            m_protocol = determineProtocol();
        }

        return *(m_protocol.get());
    }

    const Timestamp& WirelessNode_Impl::lastCommunicationTime() const
    {
        return NodeCommTimes::getLastCommTime(m_address);
    }

    void WirelessNode_Impl::setBaseStation(const BaseStation& basestation)
    {
        //if the base station is already set as the parent base station
        if(m_baseStation == basestation)
        {
            //just return, nothing is changing
            return;
        }

        //update this Node's base station
        m_baseStation = basestation;

        if(m_eeprom != NULL)
        {
            //update the base station in the eeprom object
            eeprom().setBaseStation(m_baseStation);
        }
    }

    BaseStation& WirelessNode_Impl::getBaseStation()
    {
        return m_baseStation;
    }

    bool WirelessNode_Impl::hasBaseStation(const BaseStation& basestation) const
    {
        return (basestation == m_baseStation);
    }

    void WirelessNode_Impl::useGroupRead(bool useGroup)
    {
        //will be cached for later in case m_eeprom is null
        m_eepromSettings.useGroupRead = useGroup;

        if(m_eeprom != NULL)
        {
            eeprom().updateSettings(m_eepromSettings);
        }
    }

    void WirelessNode_Impl::readWriteRetries(uint8 numRetries)
    {
        //will be cached for later in case m_eeprom is null
        m_eepromSettings.numRetries = numRetries;

        if(m_eeprom != NULL)
        {
            eeprom().updateSettings(m_eepromSettings);
        }
    }

    void WirelessNode_Impl::useEepromCache(bool useCache)
    {
        //will be cached for later in case m_eeprom is null
        m_eepromSettings.useEepromCache = useCache;

        if(m_eeprom != NULL)
        {
            eeprom().updateSettings(m_eepromSettings);
        }
    }

    void WirelessNode_Impl::clearEepromCache()
    {
        //don't need to clear anything if it doesn't exist
        if(m_eeprom != NULL)
        {
            eeprom().clearCache();
        }
    }

    uint16 WirelessNode_Impl::nodeAddress() const
    {
        return m_address;
    }

    WirelessTypes::Frequency WirelessNode_Impl::frequency() const
    {
        return m_eepromHelper->read_frequency();
    }

    Version WirelessNode_Impl::firmwareVersion() const
    {
        return m_eepromHelper->read_fwVersion();
    }

    WirelessModels::NodeModel WirelessNode_Impl::model() const
    {
        return m_eepromHelper->read_model();
    }

    std::string WirelessNode_Impl::serial() const
    {
        return m_eepromHelper->read_serial();
    }

    WirelessTypes::MicroControllerType WirelessNode_Impl::microcontroller() const
    {
        return m_eepromHelper->read_microcontroller();
    }

    RadioFeatures WirelessNode_Impl::radioFeatures() const
    {
        return m_eepromHelper->read_radioFeatures();
    }

    uint64 WirelessNode_Impl::dataStorageSize() const
    {
        return m_eepromHelper->read_dataStorageSize();
    }

    WirelessTypes::RegionCode WirelessNode_Impl::regionCode() const
    {
        return m_eepromHelper->read_regionCode();
    }

    bool WirelessNode_Impl::verifyConfig(const WirelessNodeConfig& config, ConfigIssues& outIssues) const
    {
        return config.verify(features(), eeHelper(), outIssues);
    }

    void WirelessNode_Impl::applyConfig(const WirelessNodeConfig& config)
    {
        config.apply(features(), eeHelper());

        //if the apply succeeded, we need to cycle the power
        //for some eeproms to actually take the changes
        m_eepromHelper->applyEepromChanges();
    }

    uint16 WirelessNode_Impl::getNumDatalogSessions() const
    {
        return m_eepromHelper->read_numDatalogSessions();
    }

    WirelessTypes::DefaultMode WirelessNode_Impl::getDefaultMode() const
    {
        return m_eepromHelper->read_defaultMode();
    }

    uint16 WirelessNode_Impl::getInactivityTimeout() const
    {
        return m_eepromHelper->read_inactivityTimeout();
    }

    uint8 WirelessNode_Impl::getCheckRadioInterval() const
    {
        return m_eepromHelper->read_checkRadioInterval();
    }

    WirelessTypes::TransmitPower WirelessNode_Impl::getTransmitPower() const
    {
        return m_eepromHelper->read_transmitPower();
    }

    WirelessTypes::SamplingMode WirelessNode_Impl::getSamplingMode() const
    {
        return m_eepromHelper->read_samplingMode();
    }

    ChannelMask WirelessNode_Impl::getActiveChannels() const
    {
        return m_eepromHelper->read_channelMask();
    }

    WirelessTypes::WirelessSampleRate WirelessNode_Impl::getSampleRate() const
    {
        return m_eepromHelper->read_sampleRate(getSamplingMode());
    }

    uint32 WirelessNode_Impl::getNumSweeps() const
    {
        //if the node doesn't support limited number of sweeps
        if(!features().supportsLimitedDuration())
        {
            throw Error_NotSupported("The Number of Sweeps is not supported by this Ndoe.");
        }

        return m_eepromHelper->read_numSweeps();
    }

    bool WirelessNode_Impl::getUnlimitedDuration() const
    {
        return m_eepromHelper->read_unlimitedDuration(getSamplingMode());
    }

    WirelessTypes::DataFormat WirelessNode_Impl::getDataFormat() const
    {
        return m_eepromHelper->read_dataFormat();
    }

    WirelessTypes::DataCollectionMethod WirelessNode_Impl::getDataCollectionMethod() const
    {
        return m_eepromHelper->read_collectionMode();
    }

    TimeSpan WirelessNode_Impl::getTimeBetweenBursts() const
    {
        //if the node doesn't support burst mode
        if(!features().supportsSamplingMode(WirelessTypes::samplingMode_syncBurst))
        {
            throw Error_NotSupported("Burst Sampling is not supported by this Node.");
        }

        return m_eepromHelper->read_timeBetweenBursts();
    }

    uint16 WirelessNode_Impl::getLostBeaconTimeout() const
    {
        //if the node doesn't support lost beacon timeout
        if(!features().supportsLostBeaconTimeout())
        {
            throw Error_NotSupported("Lost Beacon Timeout is not supported by this Node.");
        }

        return m_eepromHelper->read_lostBeaconTimeout();
    }

    double WirelessNode_Impl::getHardwareGain(const ChannelMask& mask) const
    {
        return m_eepromHelper->read_hardwareGain(mask);
    }

    uint16 WirelessNode_Impl::getHardwareOffset(const ChannelMask& mask) const
    {
        return m_eepromHelper->read_hardwareOffset(mask);
    }

    WirelessTypes::Filter WirelessNode_Impl::getLowPassFilter(const ChannelMask& mask) const
    {
        return m_eepromHelper->read_lowPassFilter(mask);
    }

    float WirelessNode_Impl::getGaugeFactor(const ChannelMask& mask) const
    {
        return m_eepromHelper->read_gaugeFactor(mask);
    }

    LinearEquation WirelessNode_Impl::getLinearEquation(const ChannelMask& mask) const
    {
        LinearEquation result;
        m_eepromHelper->read_channelLinearEquation(mask, result);
        return result;
    }

    WirelessTypes::CalCoef_Unit WirelessNode_Impl::getUnit(const ChannelMask& mask) const
    {
        return m_eepromHelper->read_channelUnit(mask);
    }

    WirelessTypes::CalCoef_EquationType WirelessNode_Impl::getEquationType(const ChannelMask& mask) const
    {
        return m_eepromHelper->read_channelEquation(mask);
    }

    WirelessTypes::SettlingTime WirelessNode_Impl::getFilterSettlingTime(const ChannelMask& mask) const
    {
        return m_eepromHelper->read_settlingTime(mask);
    }

    WirelessTypes::ThermocoupleType WirelessNode_Impl::getThermocoupleType(const ChannelMask& mask) const
    {
        return m_eepromHelper->read_thermoType(mask);
    }

    FatigueOptions WirelessNode_Impl::getFatigueOptions() const
    {
        //if the node doesn't support fatigue options
        if(!features().supportsFatigueConfig())
        {
            throw Error_NotSupported("FatigueOptions configuration is not supported by this Node.");
        }

        FatigueOptions result;
        m_eepromHelper->read_fatigueOptions(result);
        return result;
    }

    HistogramOptions WirelessNode_Impl::getHistogramOptions() const
    {
        //if the node doesn't support histogram options
        if(!features().supportsHistogramConfig())
        {
            throw Error_NotSupported("HistogramOptions configuration is not supported by this Node.");
        }

        HistogramOptions result;
        m_eepromHelper->read_histogramOptions(result);
        return result;
    }

    ActivitySense WirelessNode_Impl::getActivitySense() const
    {
        //if the node doesn't support activity sense options
        if(!features().supportsActivitySense())
        {
            throw Error_NotSupported("ActivitySense configuration is not supported by this Node.");
        }

        ActivitySense result;
        m_eepromHelper->read_activitySense(result);
        return result;
    }

    EventTriggerOptions WirelessNode_Impl::getEventTriggerOptions() const
    {
        //if the node doesn't support event trigger options
        if(!features().supportsEventTrigger())
        {
            throw Error_NotSupported("Event Trigger is not supported by this Node.");
        }

        EventTriggerOptions result;
        m_eepromHelper->read_eventTriggerOptions(result);
        return result;
    }

    uint16 WirelessNode_Impl::getDiagnosticInterval() const
    {
        if(!features().supportsDiagnosticInfo())
        {
            throw Error_NotSupported("Diagnostic Info is not supported by this Node.");
        }

        return m_eepromHelper->read_diagnosticInterval();
    }

    WirelessTypes::StorageLimitMode WirelessNode_Impl::getStorageLimitMode() const
    {
        if(!features().supportsLoggedData())
        {
            throw Error_NotSupported("Datalogging is not supported by this Node.");
        }

        if(!features().supportsStorageLimitModeConfig())
        {
            //legacy nodes don't support this eeprom, but are
            //hard coded to stop when the storage limit is reached.
            return WirelessTypes::storageLimit_stop;
        }

        return m_eepromHelper->read_storageLimitMode();
    }

    /*
    bool WirelessNode_Impl::shortPing()
    {
        if(m_baseStation == NULL)
        {
            throw mscl::Error("No Base Station");
        }

        return m_baseStation.node_shortPing(m_address);
    }
    */

    bool WirelessNode_Impl::quickPing()
    {
        return m_baseStation.node_shortPing(m_address);
    }

    PingResponse WirelessNode_Impl::ping()
    {
        //send the node_ping command to this node's parent base station
        return m_baseStation.node_ping(m_address);
    }

    bool WirelessNode_Impl::sleep()
    {
        //send the sleep command to this node's parent base station
        return m_baseStation.node_sleep(m_address);
    }

    void WirelessNode_Impl::cyclePower()
    {
        static const uint16 RESET_NODE = 0x01;

        //cycle the power on the node by writing a 1 to the CYCLE_POWER location
        writeEeprom(NodeEepromMap::CYCLE_POWER, Value::UINT16(RESET_NODE));

        Utils::threadSleep(250);

        //attempt to ping the node a few times to see if its back online
        bool pingSuccess = false;
        uint8 retries = 0;
        while(!pingSuccess && retries <= 15)
        {
            pingSuccess = ping().success();
            retries++;
        }
    }

    void WirelessNode_Impl::resetRadio()
    {
        static const uint16 RESET_RADIO = 0x02;

        //cycle the radio on the node by writing a 2 to the CYCLE_POWER location
        writeEeprom(NodeEepromMap::CYCLE_POWER, Value::UINT16(RESET_RADIO));

        Utils::threadSleep(100);
    }

    void WirelessNode_Impl::changeFrequency(WirelessTypes::Frequency frequency)
    {
        //make sure the frequency is within the correct range, change if not
        Utils::checkBounds_min(frequency, WirelessTypes::freq_11);
        Utils::checkBounds_max(frequency, WirelessTypes::freq_26);

        //write the new frequency to the node
        writeEeprom(NodeEepromMap::FREQUENCY, Value::UINT16(static_cast<uint16>(frequency)));

        //reset the radio on the node to commit the change
        resetRadio();
    }

    SetToIdleStatus WirelessNode_Impl::setToIdle()
    {
        //call the node_setToIdle command from the parent BaseStation
        return m_baseStation.node_setToIdle(m_address);
    }

    void WirelessNode_Impl::erase()
    {
        //call the node_erase command from the parent BaseStation
        bool success = m_baseStation.node_erase(protocol(), m_address);

        //if the erase command failed
        if(!success)
        {
            throw Error_NodeCommunication(m_address, "Failed to erase the Node.");
        }
    }

    void WirelessNode_Impl::startNonSyncSampling()
    {
        WirelessTypes::SamplingMode mode = eeHelper().read_samplingMode();

        //verify that the node is configured for nonSyncSampling mode
        if(mode != WirelessTypes::samplingMode_nonSync &&
           mode != WirelessTypes::samplingMode_nonSyncEvent)
        {
            ConfigIssues issues;
            issues.push_back(ConfigIssue(ConfigIssue::CONFIG_SAMPLING_MODE, "Configuration is not set for Non-Synchronized Sampling Mode."));
            throw Error_InvalidNodeConfig(issues, m_address);
        }

        //call the node_startNonSyncSampling command from the parent BaseStation
        m_baseStation.node_startNonSyncSampling(m_address);
    }

    void WirelessNode_Impl::clearHistogram()
    {
        //if the node doesn't support histogram options
        if(!features().supportsHistogramConfig())
        {
            throw Error_NotSupported("Histogram configuration is not supported by this Node.");
        }

        m_eepromHelper->clearHistogram();

        //must cycle power for the clearing to take affect
        cyclePower();
    }

    AutoBalanceResult WirelessNode_Impl::autoBalance(const ChannelMask& mask, float targetPercent)
    {
        Utils::checkBounds_min(targetPercent, 0.0f);
        Utils::checkBounds_max(targetPercent, 100.0f);

        //attempt a ping first 
        //(legacy (v1) autobalance doesn't have a response packet, so need to check communication)
        if(!ping().success())
        {
            throw Error_NodeCommunication(nodeAddress());
        }

        //find the eeprom location that the autobalance will adjust
        //Note: this also verifies that it is supported for this mask
        const EepromLocation& eepromLoc = features().findEeprom(WirelessTypes::chSetting_autoBalance, mask);

        //currently, autobalance is always per channel, so get the channel from the mask
        uint8 channelNumber = mask.lastChEnabled();

        AutoBalanceResult result;

        //perform the autobalance command with the parent base station
        m_baseStation.node_autoBalance(protocol(), m_address, channelNumber, targetPercent, result);

        //clear the cache of the hardware offset eeprom location we adjusted
        eeprom().clearCacheLocation(eepromLoc.location());

        Utils::threadSleep(200);

        //if we used the legacy command, we don't get result info, need to do more work to get it
        if(result.m_errorCode == WirelessTypes::autobalance_legacyNone)
        {
            result.m_errorCode = WirelessTypes::autobalance_maybeInvalid;

            //force the read eeprom retries to a minimum of 3
            uint8 startRetries = m_eepromSettings.numRetries;

            //when this goes out of scope, it will change back the original retries value
            ScopeHelper writebackRetries(std::bind(&WirelessNode_Impl::readWriteRetries, this, startRetries));

            //if there are less than 10 retries
            if(startRetries < 10)
            {
                //we want to retry at least a few times
                readWriteRetries(10);
            }
            else
            {
                //don't need to write back the retries since we didn't make a change
                writebackRetries.cancel();
            }

            //read the updated hardware offset from the node
            result.m_hardwareOffset = readEeprom(eepromLoc).as_uint16();

            bool readSensorSuccess = false;

            uint8 readSensorTry = 0;
            do
            {
                //perform the read single sensor command
                uint16 sensorVal = 0;
                readSensorSuccess = m_baseStation.node_readSingleSensor(m_address, channelNumber, sensorVal);

                if(readSensorSuccess)
                {
                    //find the max bits value of the node
                    uint32 maxBitsVal = 0;
                    switch(model())
                    {
                        case WirelessModels::node_vLink:
                        case WirelessModels::node_sgLink_rgd:
                        case WirelessModels::node_shmLink:
                            maxBitsVal = 65536;
                            break;

                        default:
                            maxBitsVal = 4096;
                            break;
                    }

                    //calculate and store the percent achieved
                    result.m_percentAchieved = static_cast<float>(sensorVal) / static_cast<float>(maxBitsVal) * 100.0f;
                }

                readSensorTry++;
            }
            while(!readSensorSuccess && readSensorTry <= 3);

            if(readSensorSuccess)
            {
                result.m_errorCode = WirelessTypes::autobalance_success;
            }
        }

        return result;
    }

    AutoCalResult_shmLink WirelessNode_Impl::autoCal_shmLink()
    {
        WirelessModels::NodeModel nodeModel = features().m_nodeInfo.model();
        const Version& fwVers = features().m_nodeInfo.firmwareVersion();

        //verify the node supports autocal
        if(!features().supportsAutoCal())
        {
            throw Error_NotSupported("AutoCal is not supported by this Node.");
        }

        //verify the node is the correct model
        if(nodeModel != WirelessModels::node_shmLink2 &&
           nodeModel != WirelessModels::node_shmLink2_cust1)
        {
            throw Error_NotSupported("autoCal_shmLink is not supported by this Node's model.");
        }

        //perform the autocal command by the base station
        AutoCalResult_shmLink result;
        bool success = m_baseStation.node_autocal(m_address, nodeModel, fwVers, result);

        if(!success)
        {
            throw Error_NodeCommunication(m_address, "AutoCal has failed.");
        }

        return result;
    }

    Value WirelessNode_Impl::readEeprom(const EepromLocation& location) const
    {
        return eeprom().readEeprom(location);
    }

    void WirelessNode_Impl::writeEeprom(const EepromLocation& location, const Value& val)
    {
        eeprom().writeEeprom(location, val);
    }

    uint16 WirelessNode_Impl::readEeprom(uint16 location) const
    {
        return eeprom().readEeprom(location);
    }

    void WirelessNode_Impl::writeEeprom(uint16 location, uint16 value)
    {
        eeprom().writeEeprom(location, value);
    }
}