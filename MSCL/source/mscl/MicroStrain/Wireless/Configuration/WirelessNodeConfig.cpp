/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "WirelessNodeConfig.h"
#include "mscl/MicroStrain/Wireless/WirelessNode.h"
#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"
#include "mscl/MicroStrain/Wireless/SyncSamplingFormulas.h"
#include "NodeEepromHelper.h"

namespace mscl
{
    WirelessNodeConfig::WirelessNodeConfig()
    {
    }

    WirelessTypes::Voltage WirelessNodeConfig::curExcitationVoltage(const NodeEepromHelper& eeprom) const
    {
        //if its currently set in the config, return the set value
        if(isSet(m_excitationVoltage)) { return *m_excitationVoltage; }

        //not set, so read the value from the node
        return eeprom.read_excitationVoltage();
    }

    WirelessTypes::TransmitPower WirelessNodeConfig::curTransmitPower(const NodeEepromHelper& eeprom) const
    {
        //if its currently set in the config, return the set value
        if(isSet(m_transmitPower)) { return *m_transmitPower; }

        //not set, so read the value from the node
        return eeprom.read_transmitPower();
    }

    WirelessTypes::CommProtocol WirelessNodeConfig::curCommProtocol(const NodeEepromHelper& eeprom) const
    {
        //if its currently set in the config, return the set value
        if(isSet(m_commProtocol)) { return *m_commProtocol; }

        //not set, so read the value from the node
        return eeprom.read_commProtocol();
    }

    WirelessTypes::SamplingMode WirelessNodeConfig::curSamplingMode(const NodeEepromHelper& eeprom) const
    {
        //if its currently set in the config, return the set value
        if(isSet(m_samplingMode)) { return *m_samplingMode; }

        //not set, so read the value from the node
        return eeprom.read_samplingMode();
    }

    WirelessTypes::WirelessSampleRate WirelessNodeConfig::curSampleRate(const NodeEepromHelper& eeprom) const
    {
        //if its currently set in the config, return the set value
        if(isSet(m_sampleRate)) { return *m_sampleRate; }

        //not set, so read the value from the node, with the sampling mode
        return eeprom.read_sampleRate(curSamplingMode(eeprom));
    }

    ChannelMask WirelessNodeConfig::curActiveChs(const NodeEepromHelper& eeprom) const
    {
        //if its currently set in the config, return the set value
        if(isSet(m_activeChannels)) { return *m_activeChannels; }

        //not set, so read the value from the node
        return eeprom.read_channelMask();
    }

    uint32 WirelessNodeConfig::curNumSweeps(const NodeEepromHelper& eeprom) const
    {
        //if its currently set in the config, return the set value
        if(isSet(m_numSweeps)) { return *m_numSweeps; }

        //not set, so read the value from the node
        return eeprom.read_numSweeps();
    }

    bool WirelessNodeConfig::curUnlimitedDuration(const NodeEepromHelper& eeprom) const
    {
        //if its currently set in the config, return the set value
        if(isSet(m_unlimitedDuration)) { return *m_unlimitedDuration; }

        //not set, so read the value from the node
        return eeprom.read_unlimitedDuration(curSamplingMode(eeprom));
    }

    WirelessTypes::DataFormat WirelessNodeConfig::curDataFormat(const NodeEepromHelper& eeprom) const
    {
        //if its currently set in the config, return the set value
        if(isSet(m_dataFormat)) { return *m_dataFormat; }

        //not set, so read the value from the node
        return eeprom.read_dataFormat();
    }

    WirelessTypes::FatigueMode WirelessNodeConfig::curFatigueMode(const NodeEepromHelper& eeprom) const
    {
        if(isSet(m_fatigueOptions)) { return (*m_fatigueOptions).fatigueMode(); }

        return eeprom.read_fatigueMode();
    }

    DataModeMask WirelessNodeConfig::curDataModeMask(const NodeEepromHelper& eeprom) const
    {
        //if its currently set in the config, return the set value
        if(isSet(m_dataMode)) 
        { 
            return DataModeMask(*m_dataMode); 
        }

        //not set, so read the value from the node
        return DataModeMask(eeprom.read_dataMode());
    }

    WirelessTypes::WirelessSampleRate WirelessNodeConfig::curDerivedRate(const NodeEepromHelper& eeprom) const
    {
        //if its currently set in the config, return the set value
        if(isSet(m_derivedDataRate)) { return *m_derivedDataRate; }

        //not set, so read the value from the node
        return eeprom.read_derivedSampleRate();
    }

    WirelessTypes::DataCollectionMethod WirelessNodeConfig::curDataCollectionMethod(const NodeEepromHelper& eeprom) const
    {
        //if its currently set in the config, return the set value
        if(isSet(m_dataCollectionMethod)) { return *m_dataCollectionMethod; }

        //not set, so read the value from the node
        return eeprom.read_collectionMode();
    }

    TimeSpan WirelessNodeConfig::curTimeBetweenBursts(const NodeEepromHelper& eeprom) const
    {
        //if its currently set in the config, return the set value
        if(isSet(m_timeBetweenBursts)) { return *m_timeBetweenBursts; }

        //not set, so read the value from the node
        return eeprom.read_timeBetweenBursts();
    }

    WirelessTypes::SettlingTime WirelessNodeConfig::curSettlingTime(const ChannelMask& mask, const NodeEepromHelper& eeprom) const
    {
        //if its currently set in the config, return the set value
        if(isSet(m_settlingTimes, mask)) { return m_settlingTimes.at(mask); }

        //not set, so read the value from the node
        return eeprom.read_settlingTime(mask);
    }

    WirelessTypes::Filter WirelessNodeConfig::curLowPassFilter(const ChannelMask& mask, const NodeEepromHelper& eeprom) const
    {
        //if its currently set in the config, return the set value
        if(isSet(m_lowPassFilters, mask)) { return m_lowPassFilters.at(mask); }

        //not set, so read the value from the node
        return eeprom.read_lowPassFilter(mask);
    }

    void WirelessNodeConfig::curEventTriggerDurations(const NodeEepromHelper& eeprom, uint32& pre, uint32& post) const
    {
        //if its currently set in the config, return the set value
        if(isSet(m_eventTriggerOptions)) 
        { 
            pre = m_eventTriggerOptions->preDuration();
            post = m_eventTriggerOptions->postDuration();
        }
        else
        {
            //read the values from eeprom
            eeprom.read_eventTriggerDurations(pre, post);
        }
    }

    BitMask WirelessNodeConfig::curEventTriggerMask(const NodeEepromHelper& eeprom) const
    {
        if(isSet(m_eventTriggerOptions))
        {
            return m_eventTriggerOptions->triggerMask();
        }
        else
        {
            //read the value from eeprom
            return eeprom.read_eventTriggerMask();
        }
    }

    LinearEquation WirelessNodeConfig::curLinearEquation(const ChannelMask& mask, const NodeEepromHelper& eeprom) const
    {
        //if its currently set in the config, return the set value
        if(isSet(m_linearEquations, mask)) { return m_linearEquations.at(mask); }

        //not set, so read the value from the node
        LinearEquation result;
        eeprom.read_channelLinearEquation(mask, result);

        return result;
    }

    ChannelMask WirelessNodeConfig::curDerivedMask(WirelessTypes::DerivedCategory category, const NodeEepromHelper& eeprom) const
    {
        const auto& mask = m_derivedChannelMasks.find(category);

        //if its currently set in the config, return the set value
        if(mask != m_derivedChannelMasks.end())
        {
            return mask->second;
        }

        //not set, so read the value from the node
        return eeprom.read_derivedChannelMask(category);
    }

    WirelessTypes::DerivedChannelMasks WirelessNodeConfig::curDerivedChannelMasks(const NodeEepromHelper& eeprom, const NodeFeatures& features) const
    {
        WirelessTypes::DerivedChannelMasks derivedChMasks;
        const WirelessTypes::DerivedChannelMasks& derivedChs = features.channelsPerDerivedCategory();
        for(const auto& dc : derivedChs)
        {
            derivedChMasks.emplace(dc.first, curDerivedMask(dc.first, eeprom));
        }

        return derivedChMasks;
    }

    bool WirelessNodeConfig::isDerivedChannelEnabled(WirelessTypes::DerivedCategory category, const NodeEepromHelper& eeprom, const NodeFeatures& features) const
    {
        if(!features.supportsDerivedCategory(category))
        {
            return false;
        }

        return (curDerivedMask(category, eeprom).count() > 0);
    }

    bool WirelessNodeConfig::findGroupWithChannelAndSetting(const ChannelMask& mask, WirelessTypes::ChannelGroupSetting setting, const NodeFeatures& features, ChannelGroup& foundGroup) const
    {
        //loop through all supported channel groups
        for(const auto& group : features.channelGroups())
        {
            for(uint8 ch = 1; ch <= ChannelMask::MAX_CHANNELS; ch++)
            {
                //check each channel in the group
                if(mask.enabled(ch))
                {
                    //if this group has the requested setting, and at least one of the the same channels as the mask
                    if(group.hasSettingAndChannel(setting, ch))
                    {
                        foundGroup = group;
                        return true;
                    }
                }
            }
        }

        return false;
    }

    ConfigIssue::ConfigOption WirelessNodeConfig::findDerivedMaskConfigIssue(WirelessTypes::DerivedCategory category)
    {
        switch(category)
        {
            case WirelessTypes::derivedCategory_rms:
                return ConfigIssue::CONFIG_DERIVED_MASK_RMS;

            case WirelessTypes::derivedCategory_peakToPeak:
                return ConfigIssue::CONFIG_DERIVED_MASK_P2P;

            case WirelessTypes::derivedCategory_velocity:
                return ConfigIssue::CONFIG_DERIVED_MASK_IPS;

            case WirelessTypes::derivedCategory_crestFactor:
                return ConfigIssue::CONFIG_DERIVED_MASK_CREST_FACTOR;

            case WirelessTypes::derivedCategory_mean:
                return ConfigIssue::CONFIG_DERIVED_MASK_MEAN;

            default:
                assert(false);  //need to add support for new DerivedChannel
                return ConfigIssue::CONFIG_DERIVED_MASK_RMS;
        }
    }

    bool WirelessNodeConfig::isSyncSamplingMode(WirelessTypes::SamplingMode mode)
    {
        switch(mode)
        {
            case WirelessTypes::samplingMode_sync:
            case WirelessTypes::samplingMode_syncBurst:
            case WirelessTypes::samplingMode_syncEvent:
                return true;

            default:
                return false;
        }
    }

    bool WirelessNodeConfig::verifySupported(const NodeFeatures& features, const NodeEepromHelper& eeprom, ConfigIssues& outIssues) const
    {
        //Communication Protocol
        if(isSet(m_commProtocol))
        {
            if(!features.supportsCommunicationProtocol(*m_commProtocol))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_COMM_PROTOCOL, "The Communication Protocol is not supported by this Node."));
            }
        }

        //Default Mode
        if(isSet(m_defaultMode))
        {
            //verify the boot mode is supported
            if(!features.supportsDefaultMode(*m_defaultMode))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_DEFAULT_MODE, "The Default Mode is not supported by this Node."));
            }
        }

        //Inactivity Timeout
        if(isSet(m_inactivityTimeout))
        {
            //verify the inactivity timeout is within range
            if(*m_inactivityTimeout < features.minInactivityTimeout())
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_INACTIVITY_TIMEOUT, "The Inactivity Timeout is out of range."));
            }
        }

        //Check Radio Interval
        if(isSet(m_checkRadioInterval))
        {
            //verify the check radio interval is within range
            if(*m_checkRadioInterval < features.minCheckRadioInterval() || *m_checkRadioInterval > features.maxCheckRadioInterval())
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_CHECK_RADIO_INTERVAL, "The Check Radio Interval is out of range."));
            }
        }

        //Sampling Mode
        if(isSet(m_samplingMode))
        {
            //verify the sampling mode is supported by this node
            if(!features.supportsSamplingMode(*m_samplingMode))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_SAMPLING_MODE, "The Sampling Mode is not supported by this Node."));
            }
        }

        //Active Channels
        if(isSet(m_activeChannels))
        {
            uint8 lastActiveCh = m_activeChannels->lastChEnabled();

            //verify each channel is supported by this node
            uint8 channelItr;
            for(channelItr = 1; channelItr <= lastActiveCh; ++channelItr)
            {
                //if this channel is enabled in the channel mask
                if(m_activeChannels->enabled(channelItr))
                {
                    //if this channel is not supported by the Node
                    if(!features.supportsChannel(channelItr))
                    {
                        outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_ACTIVE_CHANNELS, "Channel " + Utils::toStr(channelItr) + " is not supported by this Node."));
                    }
                }
            }
        }

        //Number of Sweeps
        if(isSet(m_numSweeps))
        {    
            //verify that we supported setting num sweeps
            if(!features.supportsLimitedDuration())
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_SWEEPS, "Number of Sweeps is not supported by this Node."));
            }
            //verify the sweeps are normalized
            else if(*m_numSweeps != features.normalizeNumSweeps(*m_numSweeps))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_SWEEPS, "The number of Sweeps needs to be normalized."));
            }
        }

        //Unlimited Duration
        if(isSet(m_unlimitedDuration))
        {
            //if the node only supports unlimited duration and the user turned it off
            if(!features.supportsLimitedDuration() && (*m_unlimitedDuration == false))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_UNLIMITED_DURATION, "Unlimited duration cannot be disabled for this Node."));
            }
        }

        //Data Format
        if(isSet(m_dataFormat))
        {
            //verify the data format is supported
            if(!features.supportsDataFormat(*m_dataFormat))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_DATA_FORMAT, "The Data Format is not supported by this Node."));
            }
        }

        //Data Collection Method
        if(isSet(m_dataCollectionMethod))
        {
            //verify the data collection method is supported
            if(!features.supportsDataCollectionMethod(*m_dataCollectionMethod))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_DATA_COLLECTION_METHOD, "The Data Collection Method is not supported by this Node."));
            }
        }

        //Time Between Bursts
        if(isSet(m_timeBetweenBursts))
        {
            //verify the burst sampling mode is supported
            if(!features.supportsSamplingMode(WirelessTypes::samplingMode_syncBurst))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_TIME_BETWEEN_BURSTS, "Time Between Bursts is not supported by this Node."));
            }
            //verify time between bursts is normalized
            else if(*m_timeBetweenBursts != features.normalizeTimeBetweenBursts(*m_timeBetweenBursts))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_TIME_BETWEEN_BURSTS, "The Time Between Bursts needs to be normalized."));
            }
        }

        //Lost Beacon Timeout
        if(isSet(m_lostBeaconTimeout))
        {
            uint16 val = *m_lostBeaconTimeout;

            //verify lost beacon timeout is supported
            if(!features.supportsLostBeaconTimeout())
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_LOST_BEACON_TIMEOUT, "Lost Beacon Timeout is not supported by this Node."));
            }
            //verify the timeout is within range
            else if((val < features.minLostBeaconTimeout() && val != NodeEepromHelper::LOST_BEACON_TIMEOUT_DISABLED) || 
                    val > features.maxLostBeaconTimeout()
                    )
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_LOST_BEACON_TIMEOUT, "The Lost Beacon Timeout value is out of range."));
            }
        }

        //Gauge Resistance
        if(isSet(m_gaugeResistance))
        {
            if(!features.supportsGaugeResistance())
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_GAUGE_RESISTANCE, "Gauge Resistance is not supported by this Node."));
            }
        }

        //Excitation Voltage
        if(isSet(m_excitationVoltage))
        {
            if(!features.supportsExcitationVoltageConfig())
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_EXCITATION_VOLTAGE, "Excitation Voltage is not supported by this Node."));
            }
        }

        //Number of Active Gauges
        if(isSet(m_numActiveGauges))
        {
            uint16 val = *m_numActiveGauges;

            if(!features.supportsNumActiveGauges())
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_NUM_ACTIVE_GAUGES, "The Number of Active Gauges is not supported by this Node."));
            }
            else if(val < 1 || val > 255)
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_NUM_ACTIVE_GAUGES, "The Number of Active Gauges is out of range (1-255)."));
            }
        }

        //Low Battery Threshold
        if(isSet(m_lowBatteryThreshold))
        {
            if(!features.supportsLowBatteryThresholdConfig())
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_LOW_BATTERY_THRESHOLD, "Low Battery Threshold configuration is not supported by this Node."));
            }
        }

        //Transmit Power
        if(isSet(m_transmitPower) || isSet(m_commProtocol))
        {
            mscl::WirelessTypes::TransmitPower txPower = curTransmitPower(eeprom);
            mscl::WirelessTypes::CommProtocol protocol = curCommProtocol(eeprom);

            //verify the transmit power is supported
            if(!features.supportsTransmitPower(txPower, protocol))
            {
                //allow the user to still set a transmit power that might not be in our list, as long as its below the max
                if(txPower > features.maxTransmitPower(protocol))
                {
                    outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_TRANSMIT_POWER, "The Transmit Power is not supported by this Node for the current Comm Protocol."));
                }
            }
        }

        //Fatigue Options
        if(isSet(m_fatigueOptions))
        {
            //check that FatigueOptions is supported
            if(!features.supportsFatigueConfig())
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_FATIGUE, "FatigueOptions configuration is not supported by this Node."));
            }
            else
            {
                //check for unsupported angle ids
                const uint8 maxAngle = features.numDamageAngles() - 1;
                for(const auto& angle : m_fatigueOptions->damageAngles())
                {
                    if(angle.first > maxAngle)
                    {
                        outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_FATIGUE_ANGLE_ID, "Damage Angle ID " + Utils::toStr(angle.first) + " is not supported by this Node."));
                    }
                }

                //check for unsupported sn curve segments
                const uint8 maxSegment = features.numSnCurveSegments() - 1;
                for(const auto& segment : m_fatigueOptions->snCurveSegments())
                {
                    if(segment.first > maxSegment)
                    {
                        outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_FATIGUE_SN_CURVE, "SN Curve Segment " + Utils::toStr(segment.first) + " is not supported by this Node."));
                    }
                }

                //if we plan on writing the fatigue mode
                if(features.supportsFatigueModeConfig())
                {
                    //check the fatigue mode is supported
                    if(!features.supportsFatigueMode(m_fatigueOptions->fatigueMode()))
                    {
                        outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_FATIGUE_MODE, "The Fatigue Mode is not supported by this Node."));
                    }
                }

                //if we plan on writing distributed angle mode settings
                if(features.supportsFatigueMode(WirelessTypes::fatigueMode_distributedAngle))
                {
                    //check for distributed angle mode invalid number of angles
                    uint8 numAngles = m_fatigueOptions->distributedAngleMode_numAngles();
                    if(numAngles < 4 || numAngles > 16)
                    {
                        outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_FATIGUE_DIST_NUM_ANGLES, "Number of Distributed Angles is out of range (4-16)."));
                    }

                    float normUpper = Utils::normalizeAngle(m_fatigueOptions->distributedAngleMode_upperBound());
                    float normLower = Utils::normalizeAngle(m_fatigueOptions->distributedAngleMode_lowerBound());

                    //check if upper and lower bounds are within 1 degree
                    float diff = std::abs(normUpper - normLower);
                    bool lowGreaterThanUpper = normUpper < normLower;

                    if(diff < 1.0f || (lowGreaterThanUpper && diff > 359.0f))
                    {
                        outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_FATIGUE_DIST_ANGLE, "Lower and Upper Distributed Angle bounds cannot be within 1 degree of each other."));
                    }
                }
            }
        }

        //Histogram Options
        if(isSet(m_histogramOptions))
        {
            //check that HistogramOptions is supported
            if(!features.supportsHistogramConfig())
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_HISTOGRAM, "HistogramOptions configuration is not supported by this Node."));
            }
            else
            {
                const WirelessTypes::WirelessSampleRates txRates = features.histogramTransmitRates();

                //check the tx rate is supported
                if(std::find(txRates.begin(), txRates.end(), m_histogramOptions->transmitRate()) == txRates.end())
                {
                    outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_HISTOGRAM_TX_RATE, "The Histogram Transmit Rate is not supported by this Node."));
                }
            }
        }

        //Activity Sense
        if(isSet(m_activitySense))
        {
            //check that ActivitySense is supported
            if(!features.supportsActivitySense())
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_ACTIVITY_SENSE, "ActivitySense configuration is not supported by this Node."));
            }
        }

        //Event Trigger
        if(isSet(m_eventTriggerOptions))
        {
            if(!features.supportsEventTrigger())
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_EVENT_TRIGGER, "Event Triggering is not supported by this Node."));
            }
            //verify the pre duration is normalized
            else if((*m_eventTriggerOptions).preDuration() != features.normalizeEventDuration((*m_eventTriggerOptions).preDuration()))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_EVENT_TRIGGER, "The pre event duration needs to be normalized."));
            }
            //verify the post duration is normalized
            else if((*m_eventTriggerOptions).postDuration() != features.normalizeEventDuration((*m_eventTriggerOptions).postDuration()))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_EVENT_TRIGGER, "The post event duration needs to be normalized."));
            }
        }

        //Diagnostic Interval
        if(isSet(m_diagnosticInterval))
        {
            if(!features.supportsDiagnosticInfo())
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_DIAGNOSTIC_INTERVAL, "Diagnostic Info is not supported by this Node."));
            }
        }

        //Storage Limit Mode
        if(isSet(m_storageLimitMode))
        {
            const WirelessTypes::StorageLimitModes limitModes = features.storageLimitModes();

            //if the storage limit mode is not supported
            if(std::find(limitModes.begin(), limitModes.end(), *m_storageLimitMode) == limitModes.end())
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_STORAGE_LIMIT_MODE, "The Storage Limit Mode is not supported by this Node."));
            }
        }

        //Sensor Delay
        if(isSet(m_sensorDelay))
        {
            if(!features.supportsSensorDelayConfig())
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_SENSOR_DELAY, "Sensor Delay configuration is not supported by this Node."));
            }
            else if(*m_sensorDelay == WirelessNodeConfig::SENSOR_DELAY_ALWAYS_ON && !features.supportsSensorDelayAlwaysOn())
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_SENSOR_DELAY, "Sensor Delay Always On is not supported by this Node."));
            }
            else if(*m_sensorDelay != features.normalizeSensorDelay(*m_sensorDelay))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_SENSOR_DELAY, "The Sensor Delay needs to be normalized."));
            }
        }

        //Sensor Output Mode
        if(isSet(m_sensorOutputMode))
        {
            if(!features.supportsSensorOutputMode())
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_SENSOR_OUTPUT_MODE, "Sensor Output Mode is not supported by the Node."));
            }
        }

        //Data Mode
        bool dataModeValid = true;
        if(isSet(m_dataMode))
        {
            DataModeMask dataModeMask(*m_dataMode);

            if(dataModeMask.toMask().enabledCount() == 0)
            {
                dataModeValid = false;
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_DATA_MODE, "At least one Data Mode must be enabled."));
            }
            else if(dataModeMask.derivedModeEnabled && !features.supportsDerivedDataMode())
            {
                dataModeValid = false;
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_DATA_MODE, "Derived Data Mode is not supported by this Node."));
            }
            else if(dataModeMask.rawModeEnabled && !features.supportsRawDataMode())
            {
                dataModeValid = false;
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_DATA_MODE, "Raw Data Mode is not supported by this Node."));
            }
        }

        if(dataModeValid)
        {
            //Derived Channels Sample Rate
            if(isSet(m_derivedDataRate))
            {
                if(!features.supportsDerivedDataMode())
                {
                    outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_DERIVED_DATA_RATE, "Derived Data Mode is not supported by this Node."));
                }
                else
                {
                    //make sure the sample rate is a valid derived rate
                    const auto& derivedRates = features.derivedDataRates();
                    if(std::find(derivedRates.begin(), derivedRates.end(), *m_derivedDataRate) == derivedRates.end())
                    {
                        outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_DERIVED_DATA_RATE, "The Derived Data Rate is out of range."));
                    }
                }
            }

            //Derived Velocity Unit
            if(isSet(m_derivedVelocityUnit))
            {
                if(!features.supportsDerivedVelocityUnitConfig())
                {
                    outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_DERIVED_UNIT, "Derived Velocity Unit configuration is not supported by the Node."));
                }
            }

            //Derived Channels Masks
            if(!m_derivedChannelMasks.empty())
            {
                //for each derived channel in the map
                for(auto& mask : m_derivedChannelMasks)
                {
                    if(!features.supportsDerivedCategory(mask.first))
                    {
                        outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_DERIVED_MASK, "The Derived Channel category is not supported by this Node."));
                        break;
                    }
                    else
                    {
                        ChannelMask maskChs = mask.second;
                        ChannelMask allowedChs = features.channelsPerDerivedCategory().at(mask.first);

                        uint8 lastActiveCh = mask.second.lastChEnabled();

                        //check if any channels are enable that aren't allowed by this category
                        for(uint8 i = 1; i <= lastActiveCh; ++i)
                        {
                            if(maskChs.enabled(i) && !allowedChs.enabled(i))
                            {
                                outIssues.push_back(ConfigIssue(findDerivedMaskConfigIssue(mask.first), "The Channel Mask is invalid for the Derived Channel."));
                                break;
                            }
                        }
                    }
                }
            }
        }

        //Input Range(s)
        for(const auto& range : m_inputRanges)
        {
            //verify input range is supported for the channel mask
            if(!features.supportsChannelSetting(WirelessTypes::chSetting_inputRange, range.first))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_INPUT_RANGE, "Input Range is not supported for the provided Channel Mask.", range.first));
            }
            //verify the specific input range is acceptable for the channel mask
            else if(!features.supportsExcitationVoltageConfig() && !features.supportsInputRange(range.second, range.first))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_INPUT_RANGE, "The provided Input Range is not valid for the provided Channel Mask.", range.first));
            }
            else if (features.supportsExcitationVoltageConfig() && !features.supportsInputRange(range.second, range.first, curExcitationVoltage(eeprom))) {

                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_INPUT_RANGE, "The provided Input Range is not valid for the provided Channel Mask and Excitation Voltage", range.first));
            }
        }

        //Hardware Offset(s)
        for(const auto& offset : m_hardwareOffsets)
        {
            //verify hardware offset is supported for the channel mask
            if(!features.supportsChannelSetting(WirelessTypes::chSetting_hardwareOffset, offset.first))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_HARDWARE_OFFSET, "Hardware Offset is not supported for the provided Channel Mask.", offset.first));
            }
        }

        //Anti-Aliasing Filter(s)
        for(const auto& filter : m_antiAliasingFilters)
        {
            //verify anti-aliasing filter is supported for the channel mask
            if(!features.supportsChannelSetting(WirelessTypes::chSetting_antiAliasingFilter, filter.first))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_ANTI_ALIASING_FILTER, "Anti-Aliasing Filter is not supported for the provided Channel Mask.", filter.first));
            }
        }

        //Channel Frequency Class Filter
        if (isSet(m_cfcFilterConfig))
        {
            if (!features.supportsCfcFilterConfiguration())
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_CFC_FILTER, "CFC Filter Configuration is not supported by the Node."));
            }
        }

        //Low-Pass Filter(s)
        for(const auto& filter : m_lowPassFilters)
        {
            //verify low-pass filter is supported for the channel mask
            if(!features.supportsChannelSetting(WirelessTypes::chSetting_lowPassFilter, filter.first))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_LOW_PASS_FILTER, "Low-Pass Filter is not supported for the provided Channel Mask.", filter.first));
            }
        }

        //High-Pass Filter(s)
        for(const auto& filter : m_highPassFilters)
        {
            //verify high-pass filter is supported for the channel mask
            if(!features.supportsChannelSetting(WirelessTypes::chSetting_highPassFilter, filter.first))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_HIGH_PASS_FILTER, "High-Pass Filter is not supported for the provided Channel Mask.", filter.first));
            }
        }

        //Gauge Factors
        for(const auto& factor : m_gaugeFactors)
        {
            //verify gauge factor is supported for the channel mask
            if(!features.supportsChannelSetting(WirelessTypes::chSetting_gaugeFactor, factor.first))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_GAUGE_FACTOR, "Gauge Factor is not supported for the provided Channel Mask.", factor.first));
            }
        }

        //Linear Equation(s)
        for(const auto& eq : m_linearEquations)
        {
            //verify linear equation is supported for the channel mask
            if(!features.supportsChannelSetting(WirelessTypes::chSetting_linearEquation, eq.first))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_LINEAR_EQUATION, "Linear Equation is not supported for the provided Channel Mask.", eq.first));
            }
        }

        //Filter Settling Time(s)
        for(const auto& time : m_settlingTimes)
        {
            //verify settling time is supported for the channel mask
            if(!features.supportsChannelSetting(WirelessTypes::chSetting_filterSettlingTime, time.first))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_FILTER_SETTLING_TIME, "Filter Settling Time is not supported for the provided Channel Mask.", time.first));
            }
        }

        //Thermocouple Types
        for(const auto& type : m_thermoTypes)
        {
            //verify thermocouple type is supported for the channel mask
            if(!features.supportsChannelSetting(WirelessTypes::chSetting_thermocoupleType, type.first))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_THERMOCOUPLE_TYPE, "Thermocouple Type is not supported for the provided Channel Mask.", type.first));
            }
        }

        //Temp Sensor Options
        for(const auto& opts : m_tempSensorOptions)
        {
            //verify TempSensorOptions are supported for the channel mask
            if(!features.supportsChannelSetting(WirelessTypes::chSetting_tempSensorOptions, opts.first))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_TEMP_SENSOR_OPTS, "TempSensorOptions are not supported for the provided Channel Mask.", opts.first));
            }
            //verify the transducer type is supported by this Node
            else if(!features.supportsTransducerType(opts.second.transducerType()))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_TEMP_SENSOR_OPTS, "The provided Transducer Type is not supported by the Node.", opts.first));
            }
        }

        //Debounce Filters
        for(const auto& filters : m_debounceFilters)
        {
            if(!features.supportsChannelSetting(WirelessTypes::chSetting_debounceFilter, filters.first))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_DEBOUNCE_FILTER, "Debounce Filter is not supported for the provided Channel Mask.", filters.first));
            }
        }

        //Pull-up Resistors
        for(const auto& flags : m_pullUpResistors)
        {
            if(!features.supportsChannelSetting(WirelessTypes::chSetting_pullUpResistor, flags.first))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_PULLUP_RESISTOR, "Pull-Up Resistor is not supported for the provided Channel Mask.", flags.first));
            }
        }

        //return true if no issues
        return outIssues.size() == 0;
    }

    bool WirelessNodeConfig::verifyConflicts(const NodeFeatures& features, const NodeEepromHelper& eeprom, ConfigIssues& outIssues) const
    {
        if(isSet(m_dataMode) || isSet(m_activeChannels) || !m_derivedChannelMasks.empty())
        {
            DataModeMask mode = curDataModeMask(eeprom);

            //if raw enabled, verify raw channel mask is set
            if(mode.rawModeEnabled)
            {
                if(curActiveChs(eeprom).count() == 0)
                {
                    outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_ACTIVE_CHANNELS, "Raw Mode is enabled, but no raw channels are active."));
                }
            }

            //if derived enabled, verify derived channel mask is set
            if(mode.derivedModeEnabled)
            {
                if(!isDerivedChannelEnabled(WirelessTypes::derivedCategory_rms, eeprom, features) &&
                   !isDerivedChannelEnabled(WirelessTypes::derivedCategory_peakToPeak, eeprom, features) &&
                   !isDerivedChannelEnabled(WirelessTypes::derivedCategory_velocity, eeprom, features) &&
                   !isDerivedChannelEnabled(WirelessTypes::derivedCategory_crestFactor, eeprom, features) &&
                   !isDerivedChannelEnabled(WirelessTypes::derivedCategory_mean, eeprom, features)
                   )
                {
                    //no derived channels are enabled
                    outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_DERIVED_MASK, "Derived Mode is enabled, but no Derived channels are active."));
                }
            }
        }

        //verify derived sample rate is ok with normal sample rate
        if(features.supportsDerivedDataMode() &&
           (isSet(m_derivedDataRate) || isSet(m_sampleRate))
          )
        {
            if(curDataModeMask(eeprom).derivedModeEnabled)
            {
                const SampleRate derivedRate = SampleRate::FromWirelessEepromValue(curDerivedRate(eeprom));
                const SampleRate sampleRate = SampleRate::FromWirelessEepromValue(curSampleRate(eeprom));

                if(derivedRate.samplesPerSecond() > (sampleRate.samplesPerSecond() / 32.0))
                {
                    //derived rate must be at least 32x slower than normal sample rate
                    outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_SAMPLE_RATE, "The Derived Data Rate must be at least 32x slower than the raw sample rate."));
                    outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_DERIVED_DATA_RATE, "The Derived Data Rate must be at least 32x slower than the raw sample rate."));
                }
            }
        }

        //verify sampling mode with event trigger settings
        if(isSet(m_samplingMode) || isSet(m_eventTriggerOptions))
        {
            WirelessTypes::SamplingMode samplingMode = curSamplingMode(eeprom);

            //if trying to set the sampling mode to an event trigger mode
            if(samplingMode == WirelessTypes::samplingMode_nonSyncEvent ||
                samplingMode == WirelessTypes::samplingMode_syncEvent)
            {
                //verify at least 1 event trigger is enabled
                if(curEventTriggerMask(eeprom).enabledCount() == 0)
                {
                    outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_EVENT_TRIGGER_MASK, "The Sampling Mode includes Event Triggering, but no Events are enabled."));
                    outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_SAMPLING_MODE, "The Sampling Mode includes Event Triggering, but no Events are enabled."));
                }
            }
            //if trying to set the sampling mode to a non-event trigger mode
            else
            {
                //verify all event trigger are disabled
                if(features.supportsEventTrigger() && (curEventTriggerMask(eeprom).enabledCount() != 0))
                {
                    outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_EVENT_TRIGGER_MASK, "Event Triggers are enabled, but the Sampling Mode does not include Event Triggering."));
                    outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_SAMPLING_MODE, "Event Triggers are enabled, but the Sampling Mode does not include Event Triggering."));
                }
            }
        }

        //verify sampling mode with data collection method
        if(isSet(m_samplingMode) || isSet(m_dataCollectionMethod))
        {
            WirelessTypes::SamplingMode samplingMode = curSamplingMode(eeprom);

            //Event sampling can't be used with transmit only
            if(samplingMode == WirelessTypes::samplingMode_nonSyncEvent ||
                samplingMode == WirelessTypes::samplingMode_syncEvent)
            {
                if(curDataCollectionMethod(eeprom) == WirelessTypes::collectionMethod_transmitOnly)
                {
                    outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_DATA_COLLECTION_METHOD, "Event Triggered sampling cannot be used with Transmit Only."));
                    outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_SAMPLING_MODE, "Event Triggered sampling cannot be used with Transmit Only."));
                }
            }
        }

        //verify Sample Rate with Sampling Mode and Data collection method
        if(isSet(m_sampleRate) || isSet(m_samplingMode) || isSet(m_dataCollectionMethod) || isSet(m_dataMode))
        {
            //verify the sample rate and sampling mode
            if(!features.supportsSampleRate(curSampleRate(eeprom), curSamplingMode(eeprom), curDataCollectionMethod(eeprom), curDataModeMask(eeprom).toDataModeEnum()))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_SAMPLE_RATE, "The Sample Rate is not supported for the current Sampling Mode."));
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_SAMPLING_MODE, "The Sample Rate is not supported for the current Sampling Mode."));
            }
        }

        //verify the max Sample Rate with the mode and active channels
        if(isSet(m_sampleRate) || isSet(m_samplingMode) || isSet(m_activeChannels) || isSet(m_dataCollectionMethod) || isSet(m_dataMode))
        {
            //get the max sample rate that can be set with these settings
            WirelessTypes::WirelessSampleRate maxRate = features.maxSampleRate(curSamplingMode(eeprom), curActiveChs(eeprom), curDataCollectionMethod(eeprom), curDataModeMask(eeprom).toDataModeEnum());

            //verify the sample rate works with the sampling mode and active channels
            if(SampleRate::FromWirelessEepromValue(curSampleRate(eeprom)) > SampleRate::FromWirelessEepromValue(maxRate))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_ACTIVE_CHANNELS, "The Sample Rate exceeds the max for the current number of active channels."));
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_SAMPLE_RATE, "The Sample Rate exceeds the max for the current number of active channels."));
            }
        }

        if(features.supportsLimitedDuration())
        {
            if(isSet(m_numSweeps) || isSet(m_samplingMode) || isSet(m_dataFormat) || isSet(m_activeChannels))
            {
                bool unlimitedDuration = curUnlimitedDuration(eeprom);
                WirelessTypes::SamplingMode samplingMode = curSamplingMode(eeprom);

                //don't check if unlimited duration
                //unless sampling mode is burst, which ignores unlimited duration
                if(!unlimitedDuration || samplingMode == WirelessTypes::samplingMode_syncBurst)
                {
                    const uint32 maxSweeps = features.maxSweeps(samplingMode, curDataModeMask(eeprom).toDataModeEnum(), curDataFormat(eeprom), curActiveChs(eeprom));

                    //verify the number of sweeps works with the other sampling settings
                    if(curNumSweeps(eeprom) > maxSweeps)
                    {
                        outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_SWEEPS, "The number of Sweeps exceeds the max (" + Utils::toStr(maxSweeps) + ") for this Configuration."));
                    }
                }
            }
        }

        //verify time between bursts
        if(isSet(m_samplingMode) ||
            isSet(m_dataMode) ||
            !m_derivedChannelMasks.empty() ||
            isSet(m_dataFormat) ||
            isSet(m_activeChannels) ||
            isSet(m_sampleRate) ||
            isSet(m_numSweeps) ||
            isSet(m_commProtocol) ||
            isSet(m_timeBetweenBursts))
        {

            //if the sampling mode is burst
            if(curSamplingMode(eeprom) == WirelessTypes::samplingMode_syncBurst)
            {
                DataModeMask mode = curDataModeMask(eeprom);

                //build up the DerivedChannelMasks
                WirelessTypes::DerivedChannelMasks derivedChMasks;
                if(mode.derivedModeEnabled)
                {
                    //leave default so we don't unnecessarily read eeproms (they won't be used if derived off)
                    derivedChMasks = curDerivedChannelMasks(eeprom, features);
                }

                auto minTime = features.minTimeBetweenBursts(mode.toDataModeEnum(),
                                                                curDataFormat(eeprom),
                                                                curActiveChs(eeprom),
                                                                derivedChMasks,
                                                                SampleRate::FromWirelessEepromValue(curSampleRate(eeprom)),
                                                                curNumSweeps(eeprom),
                                                                curCommProtocol(eeprom));

                //verify the time between bursts is within range with all the other settings
                if(curTimeBetweenBursts(eeprom) < minTime)
                {
                    outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_TIME_BETWEEN_BURSTS, "The Time Between Bursts is less than the min for this Configuration."));
                }
            }
        }

        //verify Filter Settling Time with Sample Rate
        if(features.supportsFilterSettlingTime() && (isSet(m_sampleRate) || isAnySet(m_settlingTimes)))
        {
            WirelessTypes::SettlingTime settlingTime;

            //get the max filter settling time for the sample rate
            WirelessTypes::SettlingTime maxSettlingTime = features.maxFilterSettlingTime(SampleRate::FromWirelessEepromValue(curSampleRate(eeprom)));

            for(const auto& group : features.channelGroups())
            {
                for(const auto& setting : group.settings())
                {
                    //filter settling time setting
                    if(setting == WirelessTypes::chSetting_filterSettlingTime)
                    {
                        //get the current settling time for this channel group
                        settlingTime = curSettlingTime(group.channels(), eeprom);

                        //verify the settling time isn't out of range
                        if(settlingTime > maxSettlingTime)
                        {
                            outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_FILTER_SETTLING_TIME, "The Filter Settling Time exceeds the max for the current Sample Rate.",group.channels()));
                            outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_SAMPLE_RATE,"The Filter Settling Time exceeds the max for the current Sample Rate.",group.channels()));
                        }
                    }
                }
            }
        }

        //verify Low Pass Filters with Sample Rate
        if(features.supportsLowPassFilter() && 
            (isSet(m_sampleRate) ||
             isAnySet(m_lowPassFilters) ||
             isSet(m_samplingMode) || 
             isSet(m_dataCollectionMethod) ||
             isSet(m_dataMode) ||
             isSet(m_activeChannels))
           )
        {
            WirelessTypes::SamplingMode samplingMode = curSamplingMode(eeprom);
            WirelessTypes::DataCollectionMethod collectionMethod = curDataCollectionMethod(eeprom);
            WirelessTypes::DataMode dataMode = curDataModeMask(eeprom).toDataModeEnum();
            ChannelMask activeChs = curActiveChs(eeprom);

            for(const auto& group : features.channelGroups())
            {
                for(const auto& setting : group.settings())
                {
                    //low pass filter setting
                    if(setting == WirelessTypes::chSetting_lowPassFilter)
                    {
                        WirelessTypes::WirelessSampleRate maxRateEnum =  features.maxSampleRateForLowPassFilter(curLowPassFilter(group.channels(), eeprom),
                                                                                                            samplingMode,
                                                                                                            collectionMethod,
                                                                                                            dataMode,
                                                                                                            activeChs);
                        SampleRate maxSampleRate = SampleRate::FromWirelessEepromValue(maxRateEnum);

                        if(SampleRate::FromWirelessEepromValue(curSampleRate(eeprom)) > maxSampleRate)
                        {
                            if(features.hasMaxSampleRatePerFilterAndAdcChCount())
                            {
                                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_LOW_PASS_FILTER, "The Sample Rate exceeds the max (" + maxSampleRate.prettyStr() + ") for the selected Low Pass Filter and Active Channels.", group.channels()));
                                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_SAMPLE_RATE, "The Sample Rate exceeds the max (" + maxSampleRate.prettyStr() + ") for the selected Low Pass Filter and Active Channels.", group.channels()));
                                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_ACTIVE_CHANNELS, "The Sample Rate exceeds the max (" + maxSampleRate.prettyStr() + ") for the selected Low Pass Filter and Active Channels.", group.channels()));
                            }
                            else
                            {
                                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_LOW_PASS_FILTER, "The Sample Rate exceeds the max (" + maxSampleRate.prettyStr() + ") for the selected Low Pass Filter.", group.channels()));
                                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_SAMPLE_RATE, "The Sample Rate exceeds the max (" + maxSampleRate.prettyStr() + ") for the selected Low Pass Filter.", group.channels()));
                            }
                        }
                    }
                }
            }
        }

        if(features.supportsFatigueConfig() &&
           (isSet(m_dataFormat) ||
           isSet(m_fatigueOptions)))
        {
            WirelessTypes::FatigueMode fatigueMode = curFatigueMode(eeprom);

            if((fatigueMode == WirelessTypes::fatigueMode_angleStrain || fatigueMode == WirelessTypes::fatigueMode_distributedAngle) &&
               curDataFormat(eeprom) != WirelessTypes::dataFormat_cal_float)
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_DATA_FORMAT, "Angle mode only supports the 4-byte float calibrated data format."));
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_FATIGUE_MODE, "Angle mode only supports the 4-byte float calibrated data format."));
            }
        }

        //verify Event Trigger settings
        if(features.supportsEventTrigger() && 
            (isSet(m_eventTriggerOptions) ||
            isSet(m_sampleRate) ||
            isSet(m_activeChannels) ||
            isSet(m_dataFormat) ||
            isSet(m_dataMode) ||
            !m_derivedChannelMasks.empty() ||
            isSet(m_derivedDataRate)))
        {
            //only verify event trigger settings if a trigger is enabled
            if(curEventTriggerMask(eeprom).enabledCount() > 0)
            {
                uint32 preDuration;
                uint32 postDuration;

                //get the current durations
                curEventTriggerDurations(eeprom, preDuration, postDuration);

                //build up the DerivedChannelMasks
                WirelessTypes::DerivedChannelMasks derivedChMasks;
                WirelessTypes::WirelessSampleRate derivedRate = WirelessTypes::sampleRate_1Hz;

                DataModeMask mode = curDataModeMask(eeprom);

                if(mode.derivedModeEnabled)
                {
                    //leave these default so we don't unnecessarily read eeproms (they won't be used if derived off)
                    derivedChMasks = curDerivedChannelMasks(eeprom, features);
                    derivedRate = curDerivedRate(eeprom);
                }

                uint32 maxDuration = features.maxEventTriggerTotalDuration(mode.toDataModeEnum(),
                                                                            curDataFormat(eeprom),
                                                                            curActiveChs(eeprom),
                                                                            derivedChMasks,
                                                                            SampleRate::FromWirelessEepromValue(curSampleRate(eeprom)),
                                                                            SampleRate::FromWirelessEepromValue(derivedRate));

                //verify the pre+post duration is within range
                if((preDuration + postDuration) > maxDuration)
                {
                    outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_EVENT_TRIGGER_DURATION, "The total event duration exceeds the max for this Configuration."));
                }
            }
        }

        //only check the flash bandwidth if no other errors
        if(outIssues.size() == 0)
        {
            //verify flash bandwidth
            if(features.supportsFlashId() &&
                (isSet(m_dataFormat) ||
                isSet(m_activeChannels) ||
                isSet(m_numSweeps) ||
                isSet(m_sampleRate) ||
                isSet(m_samplingMode) ||
                isSet(m_timeBetweenBursts) ||
                isSet(m_dataMode) ||
                isSet(m_dataCollectionMethod) ||
                !m_derivedChannelMasks.empty() ||
                isSet(m_derivedDataRate)))
            {
                WirelessTypes::DataCollectionMethod method = curDataCollectionMethod(eeprom);

                //only check this if configured for logging
                if(method == WirelessTypes::collectionMethod_logAndTransmit ||
                   method == WirelessTypes::collectionMethod_logOnly)
                {

                    WirelessTypes::SamplingMode samplingMode = curSamplingMode(eeprom);

                    if(samplingMode != WirelessTypes::samplingMode_nonSyncEvent &&
                       samplingMode != WirelessTypes::samplingMode_syncEvent)
                    {
                        WirelessTypes::WirelessSampleRate sampleRate = curSampleRate(eeprom);
                        ChannelMask channels = curActiveChs(eeprom);
                        WirelessTypes::DataFormat dataFormat = curDataFormat(eeprom);

                        uint32 derivedBytesPerSweep = 0;
                        WirelessTypes::WirelessSampleRate derivedDataRate = WirelessTypes::sampleRate_1Hz;
                        if(curDataModeMask(eeprom).derivedModeEnabled)
                        {
                            derivedBytesPerSweep = WirelessTypes::derivedBytesPerSweep(curDerivedChannelMasks(eeprom, features));
                            derivedDataRate = curDerivedRate(eeprom);
                        }

                        //calculate the flash bandwidth used by the current settings
                        float flashBw = 0.0f;
                        if(samplingMode == WirelessTypes::samplingMode_syncBurst)
                        {
                            flashBw = flashBandwidth_burst(sampleRate, dataFormat, channels.count(), derivedBytesPerSweep, curNumSweeps(eeprom), curTimeBetweenBursts(eeprom));
                        }
                        else
                        {
                            flashBw = flashBandwidth(sampleRate, dataFormat, channels.count(), derivedBytesPerSweep, derivedDataRate);
                        }

                        //verify we aren't using more flash bandwidth than allowed
                        if(flashBw > eeprom.read_flashInfo().maxBandwidth)
                        {
                            outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_DATA_FORMAT, "The current configuration exceeds the flash bandwidth for the Node."));
                            outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_ACTIVE_CHANNELS, "The current configuration exceeds the flash bandwidth for the Node."));
                            outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_SAMPLE_RATE, "The current configuration exceeds the flash bandwidth for the Node."));
                            outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_SAMPLING_MODE, "The current configuration exceeds the flash bandwidth for the Node."));

                            if(samplingMode == WirelessTypes::samplingMode_syncBurst)
                            {
                                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_SWEEPS, "The current configuration exceeds the flash bandwidth for the Node."));
                                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_TIME_BETWEEN_BURSTS, "The current configuration exceeds the flash bandwidth for the Node."));
                            }
                        }
                    }
                }
            }
        }

        //return true if no issues
        return outIssues.size() == 0;
    }

    bool WirelessNodeConfig::verify(const NodeFeatures& features, const NodeEepromHelper& eeprom, ConfigIssues& outIssues) const
    {
        //clear out the config issues container
        outIssues.clear();

        //verify the node supports all the set options
        if(!verifySupported(features, eeprom, outIssues))
        {
            //config options themselves aren't supported, just return without checking for the conflicts
            return false;
        }

        //verify there are no conflicts with the settings in the template for this node
        return verifyConflicts(features, eeprom, outIssues);
    }

    void WirelessNodeConfig::apply(const NodeFeatures& features, NodeEepromHelper& eeprom) const
    {
        //verify the config can be applied to the node
        ConfigIssues issues;
        if(!verify(features, eeprom, issues))
        {
            //invalid configuration, throw an exception
            throw Error_InvalidNodeConfig(issues, eeprom.nodeAddress());
        }

        //write default mode
        if(isSet(m_defaultMode)) { eeprom.write_defaultMode(*m_defaultMode); }

        //write inactivity timeout
        if(isSet(m_inactivityTimeout)) { eeprom.write_inactivityTimeout(*m_inactivityTimeout); }

        //write check radio interval
        if(isSet(m_checkRadioInterval)) { eeprom.write_checkRadioInterval(*m_checkRadioInterval); }

        //write transmit power
        if(isSet(m_transmitPower)) { eeprom.write_transmitPower(*m_transmitPower); }

        //write the sample mode (also updates the hidden SyncSamplingMode
        if(isSet(m_samplingMode)) { eeprom.write_samplingMode(*m_samplingMode); }

        //write sample rate
        if(isSet(m_sampleRate)) { eeprom.write_sampleRate(*m_sampleRate, curSamplingMode(eeprom)); }

        //write active channels
        if(isSet(m_activeChannels)) { eeprom.write_channelMask(*m_activeChannels); }

        //write number of sweeps
        if(isSet(m_numSweeps)) { eeprom.write_numSweeps(*m_numSweeps); }

        //write unlimited duration flag
        if(isSet(m_unlimitedDuration)) { eeprom.write_unlimitedDuration(*m_unlimitedDuration, curSamplingMode(eeprom)); }

        //write data format
        if(isSet(m_dataFormat)) { eeprom.write_dataFormat(*m_dataFormat); }

        //write data collection method
        if(isSet(m_dataCollectionMethod)) { eeprom.write_collectionMode(*m_dataCollectionMethod); }

        //write time between bursts
        if(isSet(m_timeBetweenBursts)) { eeprom.write_timeBetweenBursts(*m_timeBetweenBursts); }

        //write lost beacon timeout
        if(isSet(m_lostBeaconTimeout)) { eeprom.write_lostBeaconTimeout(*m_lostBeaconTimeout); }

        //write gauge resistance
        if(isSet(m_gaugeResistance)) { eeprom.write_gaugeResistance(*m_gaugeResistance); }

        //write excitation voltage
        if(isSet(m_excitationVoltage)) { eeprom.write_excitationVoltage(*m_excitationVoltage); }

        //write number of active gauges
        if(isSet(m_numActiveGauges)) { eeprom.write_numActiveGauges(*m_numActiveGauges); }

        //write Fatigue Options
        if(isSet(m_fatigueOptions)) { eeprom.write_fatigueOptions(*m_fatigueOptions); }

        //write Low Battery Threshold
        if(isSet(m_lowBatteryThreshold)) { eeprom.write_lowBatteryThreshold(*m_lowBatteryThreshold); }

        //write Histogram Options
        if(isSet(m_histogramOptions)) { eeprom.write_histogramOptions(*m_histogramOptions); }

        //write Activity Sense Options
        if(isSet(m_activitySense)) { eeprom.write_activitySense(*m_activitySense); }

        //write Event Trigger Options
        if(isSet(m_eventTriggerOptions)) 
        {
            const uint8 numTriggers = features.numEventTriggers();
            std::map<uint8, LinearEquation> equations;

            if(!features.usesFloatEventTriggerVal())
            {
                uint8 chNumber;
                for(uint8 i = 0; i < numTriggers; i++)
                {
                    LinearEquation eq(1.0f, 0.0f);
                    chNumber = m_eventTriggerOptions->trigger(i).channelNumber();

                    //find the group that contains the channel for this trigger
                    WirelessTypes::ChannelGroupSettings::const_iterator itr;
                    ChannelGroups groups = features.channelGroups();
                    for(const auto& group : groups)
                    {
                        if(group.hasSetting(WirelessTypes::ChannelGroupSetting::chSetting_linearEquation) &&
                           group.channels().enabled(chNumber))
                        {
                            //legacy node, need to get the currently set (or about to be set) cal coefficients
                            //for the event trigger's channel so that the value can be converted to bits
                            eq = curLinearEquation(group.channels(), eeprom);
                            break;
                        }
                    }

                    //add the equation to the map
                    equations[i] = eq;
                }
            }

            eeprom.write_eventTriggerOptions(*m_eventTriggerOptions, equations);
        }

        //write Diagnostic Interval
        if(isSet(m_diagnosticInterval)) { eeprom.write_diagnosticInterval(*m_diagnosticInterval); }

        //write Storage Limit Mode
        if(isSet(m_storageLimitMode))
        {
            //since old nodes don't support this eeprom, but do support
            //one of the modes, if the config is valid and got here, the user
            //must be trying to set to the only one it supports, so fake it and don't apply
            if(features.supportsStorageLimitModeConfig())
            {
                eeprom.write_storageLimitMode(*m_storageLimitMode);
            }
        }

        //write Sensor Delay
        if(isSet(m_sensorDelay)) { eeprom.write_sensorDelay(*m_sensorDelay); }

        //write Data Mode
        if(isSet(m_dataMode)) 
        {
            //if the Node doesn't support this eeprom, the verifyConfig will verify
            //that only raw mode is selected, and we will just skip writing anything
            if(features.supportsDataModeEeprom())
            {
                eeprom.write_dataMode(*m_dataMode);
            }
        }

        //write Sensor Output Mode
        if(isSet(m_sensorOutputMode))
        {
            eeprom.write_sensorMode(*m_sensorOutputMode);
        }

        //write Derived Channels Sample Rate
        if(isSet(m_derivedDataRate)) { eeprom.write_derivedSampleRate(*m_derivedDataRate); }

        //write Derived Velocity Unit
        if(isSet(m_derivedVelocityUnit)) { eeprom.write_derivedVelocityUnit(*m_derivedVelocityUnit); }

        //write Derived Channel Mask(s)
        for(const auto& mask : m_derivedChannelMasks)
        {
            eeprom.write_derivedChannelMask(mask.first, mask.second);
        }

        if(!m_inputRanges.empty())
        {
            //write Input Range(s)
            if(features.supportsExcitationVoltageConfig())
            {
                WirelessTypes::Voltage exVoltage = curExcitationVoltage(eeprom);
                for(const auto& range : m_inputRanges)
                {
                    eeprom.write_inputRange(range.first, exVoltage, range.second);
                }
            }
            else
            {
                for(const auto& range : m_inputRanges)
                {
                    eeprom.write_inputRange(range.first, range.second);
                }
            }
        }

        //write Hardware Offset(s)
        for(const auto& offset : m_hardwareOffsets)
        {
            eeprom.write_hardwareOffset(offset.first, offset.second);
        }

        //write anti-aliasing filter(s)
        for(const auto& filter : m_antiAliasingFilters)
        {
            eeprom.write_antiAliasingFilter(filter.first, filter.second);
        }

        //write CFC config option
        if (isSet(m_cfcFilterConfig)) { eeprom.write_cfcFilterConfig(*m_cfcFilterConfig); }

        //write low-pass filter(s)
        for(const auto& filter : m_lowPassFilters)
        {
            eeprom.write_lowPassFilter(filter.first, filter.second);
        }

        //write high-pass filter(s)
        for(const auto& filter : m_highPassFilters)
        {
            eeprom.write_highPassFilter(filter.first, filter.second);
        }

        //write Gauge Factor(s)
        for(const auto& factor : m_gaugeFactors)
        {
            eeprom.write_gaugeFactor(factor.first, factor.second);
        }

        //write Linear Equation(s)
        for(const auto& eq : m_linearEquations)
        {
            eeprom.write_channelLinearEquation(eq.first, eq.second);
        }

        //write Unit(s)
        for(const auto& unit : m_units)
        {
            eeprom.write_channelUnit(unit.first, unit.second);
        }

        //write Equation Type(s)
        for(const auto& eq : m_equationTypes)
        {
            eeprom.write_channelEquation(eq.first, eq.second);
        }

        //write Filter Settling Time(s)
        for(const auto& time : m_settlingTimes)
        {
            eeprom.write_settlingTime(time.first, time.second);
        }

        //write Thermocouple Type(s)
        for(const auto& type : m_thermoTypes)
        {
            eeprom.write_thermoType(type.first, type.second);
        }

        //write Temp Sensor Options
        for(const auto& opts : m_tempSensorOptions)
        {
            eeprom.write_tempSensorOptions(opts.first, opts.second);
        }

        //write Debounce Filters
        for(const auto& filters : m_debounceFilters)
        {
            eeprom.write_debounceFilter(filters.first, filters.second);
        }

        //write pull-up resistors
        for(const auto& flags : m_pullUpResistors)
        {
            eeprom.write_pullUpResistor(flags.first, flags.second);
        }

        //write Communication Protocol
        if(isSet(m_commProtocol)) { eeprom.write_commProtocol(*m_commProtocol); }
    }

    WirelessTypes::DefaultMode WirelessNodeConfig::defaultMode() const
    {
        checkValue(m_defaultMode, "Default Mode");    //verify the value is set
        return *m_defaultMode;
    }

    void WirelessNodeConfig::defaultMode(WirelessTypes::DefaultMode mode)
    {
        m_defaultMode = mode;
    }

    uint16 WirelessNodeConfig::inactivityTimeout() const
    {
        checkValue(m_inactivityTimeout, "Inactivity Timeout");
        return *m_inactivityTimeout;
    }

    void WirelessNodeConfig::inactivityTimeout(uint16 timeout)
    {
        m_inactivityTimeout = timeout;
    }

    uint8 WirelessNodeConfig::checkRadioInterval() const
    {
        checkValue(m_checkRadioInterval, "Check Radio Interval");
        return *m_checkRadioInterval;
    }

    void WirelessNodeConfig::checkRadioInterval(uint8 interval)
    {
        m_checkRadioInterval = interval;
    }

    WirelessTypes::TransmitPower WirelessNodeConfig::transmitPower() const
    {
        checkValue(m_transmitPower, "Transmit Power");
        return *m_transmitPower;
    }

    void WirelessNodeConfig::transmitPower(WirelessTypes::TransmitPower power)
    {
        m_transmitPower = power;
    }

    WirelessTypes::SamplingMode WirelessNodeConfig::samplingMode() const
    {
        checkValue(m_samplingMode, "Sampling Mode");
        return *m_samplingMode;
    }

    void WirelessNodeConfig::samplingMode(WirelessTypes::SamplingMode mode)
    {
        m_samplingMode = mode;
    }

    WirelessTypes::WirelessSampleRate WirelessNodeConfig::sampleRate() const
    {
        checkValue(m_sampleRate, "Sample Rate");
        return *m_sampleRate;
    }

    void WirelessNodeConfig::sampleRate(WirelessTypes::WirelessSampleRate rate)
    {
        m_sampleRate = rate;
    }

    ChannelMask WirelessNodeConfig::activeChannels() const
    {
        checkValue(m_activeChannels, "Active Channels");
        return *m_activeChannels;
    }

    void WirelessNodeConfig::activeChannels(const ChannelMask& channels)
    {
        m_activeChannels = channels;
    }

    uint32 WirelessNodeConfig::numSweeps() const
    {
        checkValue(m_numSweeps, "Num Sweeps");
        return *m_numSweeps;
    }

    void WirelessNodeConfig::numSweeps(uint32 sweeps)
    {
        m_numSweeps = sweeps;
    }

    bool WirelessNodeConfig::unlimitedDuration() const
    {
        checkValue(m_unlimitedDuration, "Unlimited Duration");
        return *m_unlimitedDuration;
    }

    void WirelessNodeConfig::unlimitedDuration(bool enable)
    {
        m_unlimitedDuration = enable;
    }

    WirelessTypes::DataFormat WirelessNodeConfig::dataFormat() const
    {
        checkValue(m_dataFormat, "Data Format");
        return *m_dataFormat;
    }

    void WirelessNodeConfig::dataFormat(WirelessTypes::DataFormat format)
    {
        m_dataFormat = format;
    }

    WirelessTypes::DataCollectionMethod WirelessNodeConfig::dataCollectionMethod() const
    {
        checkValue(m_dataCollectionMethod, "Data Collection Method");
        return *m_dataCollectionMethod;
    }

    void WirelessNodeConfig::dataCollectionMethod(WirelessTypes::DataCollectionMethod method)
    {
        m_dataCollectionMethod = method;
    }

    TimeSpan WirelessNodeConfig::timeBetweenBursts() const
    {
        checkValue(m_timeBetweenBursts, "Time Between Bursts");
        return *m_timeBetweenBursts;
    }

    void WirelessNodeConfig::timeBetweenBursts(const TimeSpan& time)
    {
        m_timeBetweenBursts = time;
    }

    uint16 WirelessNodeConfig::lostBeaconTimeout() const
    {
        checkValue(m_lostBeaconTimeout, "Lost Beacon Timeout");
        return *m_lostBeaconTimeout;
    }

    void WirelessNodeConfig::lostBeaconTimeout(uint16 minutes)
    {
        m_lostBeaconTimeout = minutes;
    }

    WirelessTypes::InputRange WirelessNodeConfig::inputRange(const ChannelMask& mask) const
    {
        return getChannelMapVal(m_inputRanges, mask, "Input Range");
    }

    void WirelessNodeConfig::inputRange(const ChannelMask& mask, WirelessTypes::InputRange range)
    {
        setChannelMapVal(m_inputRanges, mask, range);
    }

    uint16 WirelessNodeConfig::hardwareOffset(const ChannelMask& mask) const
    {
        return getChannelMapVal(m_hardwareOffsets, mask, "Hardware Offset");
    }

    void WirelessNodeConfig::hardwareOffset(const ChannelMask& mask, uint16 offset)
    {
        setChannelMapVal(m_hardwareOffsets, mask, offset);
    }

    WirelessTypes::Filter WirelessNodeConfig::antiAliasingFilter(const ChannelMask& mask) const
    {
        return getChannelMapVal(m_antiAliasingFilters, mask, "Anti-Aliasing Filter");
    }

    void WirelessNodeConfig::antiAliasingFilter(const ChannelMask& mask, WirelessTypes::Filter filter)
    {
        setChannelMapVal(m_antiAliasingFilters, mask, filter);
    }

    WirelessTypes::ChannelFrequencyClass WirelessNodeConfig::cfcFilterConfig() const
    {
        checkValue(m_cfcFilterConfig, "Channel Frequency Class Filter");
        return *m_cfcFilterConfig;
    }

    void WirelessNodeConfig::cfcFilterConfig(WirelessTypes::ChannelFrequencyClass cfc)
    {
        m_cfcFilterConfig = cfc;
    }

    WirelessTypes::Filter WirelessNodeConfig::lowPassFilter(const ChannelMask& mask) const
    {
        return getChannelMapVal(m_lowPassFilters, mask, "Low Pass Filter");
    }

    void WirelessNodeConfig::lowPassFilter(const ChannelMask& mask, WirelessTypes::Filter filter)
    {
        setChannelMapVal(m_lowPassFilters, mask, filter);
    }

    WirelessTypes::HighPassFilter WirelessNodeConfig::highPassFilter(const ChannelMask& mask) const
    {
        return getChannelMapVal(m_highPassFilters, mask, "High Pass Filter");
    }

    void WirelessNodeConfig::highPassFilter(const ChannelMask& mask, WirelessTypes::HighPassFilter filter)
    {
        setChannelMapVal(m_highPassFilters, mask, filter);
    }

    float WirelessNodeConfig::gaugeFactor(const ChannelMask& mask) const
    {
        return getChannelMapVal(m_gaugeFactors, mask, "Gauge Factor");
    }

    void WirelessNodeConfig::gaugeFactor(const ChannelMask& mask, float factor)
    {
        setChannelMapVal(m_gaugeFactors, mask, factor);
    }

    uint16 WirelessNodeConfig::gaugeResistance() const
    {
        checkValue(m_gaugeResistance, "Gauge Resistance");
        return *m_gaugeResistance;
    }

    void WirelessNodeConfig::gaugeResistance(uint16 resistance)
    {
        m_gaugeResistance = resistance;
    }

    WirelessTypes::Voltage WirelessNodeConfig::excitationVoltage() const
    {
        checkValue(m_excitationVoltage, "Excitation Voltage");
        return *m_excitationVoltage;
    }

    void WirelessNodeConfig::excitationVoltage(WirelessTypes::Voltage voltage)
    {
        m_excitationVoltage = voltage;
    }

    uint16 WirelessNodeConfig::numActiveGauges() const
    {
        checkValue(m_numActiveGauges, "Number of Active Gauges");
        return *m_numActiveGauges;
    }

    void WirelessNodeConfig::numActiveGauges(uint16 numGauges)
    {
        m_numActiveGauges = numGauges;
    }

    float WirelessNodeConfig::lowBatteryThreshold() const
    {
        checkValue(m_lowBatteryThreshold, "Low Battery Threshold");
        return *m_lowBatteryThreshold;
    }

    void WirelessNodeConfig::lowBatteryThreshold(float voltage)
    {
        m_lowBatteryThreshold = voltage;
    }

    const LinearEquation& WirelessNodeConfig::linearEquation(const ChannelMask& mask) const
    {
        return getChannelMapVal(m_linearEquations, mask, "Linear Equation");
    }

    void WirelessNodeConfig::linearEquation(const ChannelMask& mask, const LinearEquation& linearEquation)
    {
        setChannelMapVal(m_linearEquations, mask, linearEquation);
    }

    WirelessTypes::CalCoef_Unit WirelessNodeConfig::unit(const ChannelMask& mask) const
    {
        return getChannelMapVal(m_units, mask, "Unit");
    }

    void WirelessNodeConfig::unit(const ChannelMask& mask, WirelessTypes::CalCoef_Unit unit)
    {
        setChannelMapVal(m_units, mask, unit);
    }

    WirelessTypes::CalCoef_EquationType WirelessNodeConfig::equationType(const ChannelMask& mask) const
    {
        return getChannelMapVal(m_equationTypes, mask, "Equation Type");
    }

    void WirelessNodeConfig::equationType(const ChannelMask& mask, WirelessTypes::CalCoef_EquationType equation)
    {
        setChannelMapVal(m_equationTypes, mask, equation);
    }

    WirelessTypes::SettlingTime WirelessNodeConfig::filterSettlingTime(const ChannelMask& mask) const
    {
        return getChannelMapVal(m_settlingTimes, mask, "Filter Settling Time");
    }

    void WirelessNodeConfig::filterSettlingTime(const ChannelMask& mask, WirelessTypes::SettlingTime settlingTime)
    {
        setChannelMapVal(m_settlingTimes, mask, settlingTime);
    }

    WirelessTypes::ThermocoupleType WirelessNodeConfig::thermocoupleType(const ChannelMask& mask) const
    {
        return getChannelMapVal(m_thermoTypes, mask, "Thermocouple Type");
    }

    void WirelessNodeConfig::thermocoupleType(const ChannelMask& mask, WirelessTypes::ThermocoupleType type)
    {
        setChannelMapVal(m_thermoTypes, mask, type);
    }

    TempSensorOptions WirelessNodeConfig::tempSensorOptions(const ChannelMask& mask) const
    {
        return getChannelMapVal(m_tempSensorOptions, mask, "Temperature Sensor Options");
    }

    void WirelessNodeConfig::tempSensorOptions(const ChannelMask& mask, const TempSensorOptions& options)
    {
        setChannelMapVal(m_tempSensorOptions, mask, options);
    }

    uint16 WirelessNodeConfig::debounceFilter(const ChannelMask& mask) const
    {
        return getChannelMapVal(m_debounceFilters, mask, "Debounce Filter");
    }

    void WirelessNodeConfig::debounceFilter(const ChannelMask& mask, uint16 milliseconds)
    {
        setChannelMapVal(m_debounceFilters, mask, milliseconds);
    }

    bool WirelessNodeConfig::pullUpResistor(const ChannelMask& mask) const
    {
        return getChannelMapVal(m_pullUpResistors, mask, "Pull-Up Resistor");
    }

    void WirelessNodeConfig::pullUpResistor(const ChannelMask& mask, bool enable)
    {
        setChannelMapVal(m_pullUpResistors, mask, enable);
    }

    const FatigueOptions& WirelessNodeConfig::fatigueOptions() const
    {
        checkValue(m_fatigueOptions, "Fatigue Options");
        return *m_fatigueOptions;
    }

    void WirelessNodeConfig::fatigueOptions(const FatigueOptions& fatigueOpts)
    {
        m_fatigueOptions = fatigueOpts;
    }

    const HistogramOptions& WirelessNodeConfig::histogramOptions() const
    {
        checkValue(m_histogramOptions, "Histogram Options");
        return *m_histogramOptions;
    }

    void WirelessNodeConfig::histogramOptions(const HistogramOptions& histogramOpts)
    {
        m_histogramOptions = histogramOpts;
    }

    const ActivitySense& WirelessNodeConfig::activitySense() const
    {
        checkValue(m_activitySense, "Activity Sense");
        return *m_activitySense;
    }

    void WirelessNodeConfig::activitySense(const ActivitySense& activitySenseOpts)
    {
        m_activitySense = activitySenseOpts;
    }

    const EventTriggerOptions& WirelessNodeConfig::eventTriggerOptions() const
    {
        checkValue(m_eventTriggerOptions, "Event Trigger Options");
        return *m_eventTriggerOptions;
    }

    void WirelessNodeConfig::eventTriggerOptions(const EventTriggerOptions& eventTriggerOpts)
    {
        m_eventTriggerOptions = eventTriggerOpts;
    }

    uint16 WirelessNodeConfig::diagnosticInterval() const
    {
        checkValue(m_diagnosticInterval, "Diagnostic Info Interval");
        return *m_diagnosticInterval;
    }

    void WirelessNodeConfig::diagnosticInterval(uint16 interval)
    {
        m_diagnosticInterval = interval;
    }

    WirelessTypes::StorageLimitMode WirelessNodeConfig::storageLimitMode() const
    {
        checkValue(m_storageLimitMode, "Storage Limit Mode");
        return *m_storageLimitMode;
    }

    void WirelessNodeConfig::storageLimitMode(WirelessTypes::StorageLimitMode mode)
    {
        m_storageLimitMode = mode;
    }

    uint32 WirelessNodeConfig::sensorDelay() const
    {
        checkValue(m_sensorDelay, "Sensor Delay");
        return *m_sensorDelay;
    }

    void WirelessNodeConfig::sensorDelay(uint32 delay)
    {
        m_sensorDelay = delay;
    }

    WirelessTypes::DataMode WirelessNodeConfig::dataMode() const
    {
        checkValue(m_dataMode, "Data Mode");
        return *m_dataMode;
    }

    void WirelessNodeConfig::dataMode(WirelessTypes::DataMode mode)
    {
        m_dataMode = mode;
    }

    WirelessTypes::WirelessSampleRate WirelessNodeConfig::derivedDataRate() const
    {
        checkValue(m_derivedDataRate, "Derived Channels Sample Rate");
        return *m_derivedDataRate;
    }

    void WirelessNodeConfig::derivedDataRate(WirelessTypes::WirelessSampleRate rate)
    {
        m_derivedDataRate = rate;
    }

    ChannelMask WirelessNodeConfig::derivedChannelMask(WirelessTypes::DerivedCategory category) const
    {
        try
        {
            return m_derivedChannelMasks.at(category);
        }
        catch(std::out_of_range&)
        {
            throw Error_NoData("The Derived Channel Mask option has not been set for this DerivedCategory.");
        }
    }

    void WirelessNodeConfig::derivedChannelMask(WirelessTypes::DerivedCategory category, const ChannelMask& mask)
    {
        auto itr = m_derivedChannelMasks.find(category);

        if(itr != m_derivedChannelMasks.end())
        {
            itr->second = mask;
        }
        else
        {
            m_derivedChannelMasks.emplace(category, mask);
        }
    }

    WirelessTypes::DerivedVelocityUnit WirelessNodeConfig::derivedVelocityUnit() const
    {
        checkValue(m_derivedVelocityUnit, "Derived Velocity Unit");
        return *m_derivedVelocityUnit;
    }

    void WirelessNodeConfig::derivedVelocityUnit(WirelessTypes::DerivedVelocityUnit unit)
    {
        m_derivedVelocityUnit = unit;
    }

    WirelessTypes::CommProtocol WirelessNodeConfig::communicationProtocol() const
    {
        checkValue(m_commProtocol, "Communication Protocol");
        return *m_commProtocol;
    }

    void WirelessNodeConfig::communicationProtocol(WirelessTypes::CommProtocol commProtocol)
    {
        m_commProtocol = commProtocol;
    }

    WirelessTypes::SensorOutputMode WirelessNodeConfig::sensorOutputMode() const
    {
        checkValue(m_sensorOutputMode, "Sensor Output Mode");
        return *m_sensorOutputMode;
    }

    void WirelessNodeConfig::sensorOutputMode(WirelessTypes::SensorOutputMode mode)
    {
        m_sensorOutputMode = mode;
    }

    float WirelessNodeConfig::flashBandwidth(WirelessTypes::WirelessSampleRate rawSampleRate, WirelessTypes::DataFormat dataFormat, uint8 numChannels, uint32 derivedBytesPerSweep, WirelessTypes::WirelessSampleRate derivedRate)
    {
        uint8 dataSize = WirelessTypes::dataFormatSize(dataFormat);
        double samplesPerSecond = SampleRate::FromWirelessEepromValue(rawSampleRate).samplesPerSecond();
        return static_cast<float>((dataSize * numChannels * samplesPerSecond) + (derivedBytesPerSweep * SampleRate::FromWirelessEepromValue(derivedRate).samplesPerSecond()));
    }

    float WirelessNodeConfig::flashBandwidth_burst(WirelessTypes::WirelessSampleRate rawSampleRate,
                                                   WirelessTypes::DataFormat dataFormat,
                                                   uint8 numRawChannels,
                                                   uint32 derivedBytesPerSweep,
                                                   uint32 numSweeps,
                                                   const TimeSpan& timeBetweenBursts)
    {
        uint8 dataSize = WirelessTypes::dataFormatSize(dataFormat);
        double samplesPerSecond = SampleRate::FromWirelessEepromValue(rawSampleRate).samplesPerSecond();
        uint64 secondsBetweenBursts = timeBetweenBursts.getSeconds();

        if(samplesPerSecond == 0.0) { samplesPerSecond = 0.1; } //no dividing by 0
        if(secondsBetweenBursts == 0) { secondsBetweenBursts = 1; } //no dividing by 0

        float dutyCycle = static_cast<float>((static_cast<float>(numSweeps) / samplesPerSecond) / timeBetweenBursts.getSeconds());

        return static_cast<float>((dataSize * numRawChannels * samplesPerSecond * dutyCycle) + (derivedBytesPerSweep / timeBetweenBursts.getSeconds()));
    }
}