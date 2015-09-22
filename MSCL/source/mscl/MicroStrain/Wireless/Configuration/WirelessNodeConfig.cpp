/*****************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the included
LICENSE.txt file for a copy of the full GNU General Public License.
*****************************************************************************/
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

	bool WirelessNodeConfig::verifySupported(const NodeFeatures& features, const NodeEepromHelper& eeprom, ConfigIssues& outIssues) const
	{
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
			//verify the sweeps are normalized
			if(*m_numSweeps != features.normalizeNumSweeps(*m_numSweeps))
			{
				outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_SWEEPS, "The number of Sweeps needs to be normalized."));
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

			//verify the timeout is within range
			if((val < features.minLostBeaconTimeout() && val != NodeEepromHelper::LOST_BEACON_TIMEOUT_DISABLED) ||
			    val > features.maxLostBeaconTimeout()
				)
			{
				outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_LOST_BEACON_TIMEOUT, "The Lost Beacon Timeout value is out of range."));
			}
		}

		//Transmit Power
		if(isSet(m_transmitPower))
		{
			//verify the transmit power is supported
			if(!features.supportsTransmitPower(*m_transmitPower))
			{
				outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_TRANSMIT_POWER, "The Transmit Power is not supported by this Node."));
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
						outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_FATIGUE, "Damage Angle ID " + Utils::toStr(angle.first) + " is not supported by this Node."));
					}
				}

				//check for unsupported sn curve segments
				const uint8 maxSegment = features.numSnCurveSegments() - 1;
				for(const auto& segment : m_fatigueOptions->snCurveSegments())
				{
					if(segment.first > maxSegment)
					{
						outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_FATIGUE, "SN Curve Segment " + Utils::toStr(segment.first) + " is not supported by this Node."));
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
					outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_HISTOGRAM, "The Histogram Transmit Rate is not supported by this Node."));
				}
			}
		}

		//Hardware Gain(s)
		for(const auto& gain : m_hardwareGains)
		{
			//verify hardware gain is supported for the channel mask
			if(!features.supportsChannelSetting(WirelessTypes::chSetting_hardwareGain, gain.first))
			{
				outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_HARDWARE_GAIN, "Hardware Gain is not supported for the provided Channel Mask.", gain.first));
			}
			//verify hardware gain is normalized
			else if(gain.second != features.normalizeHardwareGain(gain.second))
			{
				outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_HARDWARE_GAIN, "The Hardware Gain needs to be normalized.", gain.first));
			}
		}

		//Hardware Offsets(s)
		for(const auto& offset : m_hardwareOffsets)
		{
			//verify hardware offset is supported for the channel mask
			if(!features.supportsChannelSetting(WirelessTypes::chSetting_hardwareOffset, offset.first))
			{
				outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_HARDWARE_OFFSET, "Hardware Offset is not supported for the provided Channel Mask.", offset.first));
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

		//return true if no issues
		return outIssues.size() == 0;
	}

	bool WirelessNodeConfig::verifyConflicts(const NodeFeatures& features, const NodeEepromHelper& eeprom, ConfigIssues& outIssues) const
	{
		//if any sampling options are set
		if(isSet(m_samplingMode) ||
		   isSet(m_sampleRate) ||
		   isSet(m_activeChannels) ||
		   isSet(m_numSweeps) ||
		   isSet(m_dataFormat) ||
		   isAnySet(m_settlingTimes))
		{
			//read in all of the sampling values, either from the config or from the Node if not set
			WirelessTypes::SamplingMode samplingMode =  curSamplingMode(eeprom);
			WirelessTypes::WirelessSampleRate sampleRate = curSampleRate(eeprom);
			ChannelMask channels = curActiveChs(eeprom);
			uint32 numSweeps = curNumSweeps(eeprom);
			WirelessTypes::DataFormat dataFormat = curDataFormat(eeprom);

			//verify there is at least 1 channel enabled
			if(channels.count() == 0)
			{
				outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_ACTIVE_CHANNELS, "There are no active channels."));

				//need to just return this issue instead of continuing as
				//other issue checks require the number of channels to be > 0
				return false;
			}

			//verify Sample Rate with Sampling Mode
			if(isSet(m_sampleRate) || isSet(m_samplingMode))
			{
				//verify the sample rate and sampling mode
				if(!features.supportsSampleRate(sampleRate, samplingMode))
				{
					outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_SAMPLE_RATE, "The Sample Rate is not supported for the current Sampling Mode."));
					outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_SAMPLING_MODE, "The Sample Rate is not supported for the current Sampling Mode."));
				}
			}

			//verify the max Sample Rate with the mode and active channels
			if(isSet(m_sampleRate) || isSet(m_samplingMode) || isSet(m_activeChannels))
			{
				//get the max sample rate that can be set with these settings
				WirelessTypes::WirelessSampleRate maxRate = features.maxSampleRate(samplingMode, channels);

				//verify the sample rate works with the sampling mode and active channels
				if(SampleRate::FromWirelessEepromValue(sampleRate) > SampleRate::FromWirelessEepromValue(maxRate))
				{
					outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_ACTIVE_CHANNELS, "The Sample Rate exceeds the max for the current number of active channels."));
					outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_SAMPLE_RATE, "The Sample Rate exceeds the max for the current number of active channels."));
				}
			}

			if(isSet(m_numSweeps) || isSet(m_samplingMode) || isSet(m_dataFormat) || isSet(m_activeChannels))
			{
				bool unlimitedDuration = curUnlimitedDuration(eeprom);

				//don't check if unlimited duration
				//unless sampling mode is burst, which ignores unlimited duration
				if(!unlimitedDuration || samplingMode == WirelessTypes::samplingMode_syncBurst)
				{
					//verify the number of sweeps works with the other sampling settings
					if(numSweeps > features.maxSweeps(samplingMode, dataFormat, channels))
					{
						outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_SWEEPS, "The number of Sweeps exceeds the max for this Configuration."));
					}
				}
			}

			//if the sampling mode is burst
			if(samplingMode == WirelessTypes::samplingMode_syncBurst)
			{
				//verify the time between bursts is within range with all the other settings
				if(curTimeBetweenBursts(eeprom) < features.minTimeBetweenBursts(dataFormat, channels, SampleRate::FromWirelessEepromValue(sampleRate), numSweeps))
				{
					outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_TIME_BETWEEN_BURSTS, "The Time Between Bursts is less than the min for this Configuration."));
				}
			}

			//verify Filter Settling Time with Sample Rate
			if(features.supportsFilterSettlingTime() && (isSet(m_sampleRate) || isAnySet(m_settlingTimes)))
			{
				WirelessTypes::SettlingTime settlingTime;

				//get the max filter settling time for the sample rate
				WirelessTypes::SettlingTime maxSettlingTime = features.maxFilterSettlingTime(SampleRate::FromWirelessEepromValue(sampleRate));

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

		if(isSet(m_samplingMode)) 
		{ 
			WirelessTypes::SamplingMode tempMode = *m_samplingMode;

			//write the sampling mode
			eeprom.write_samplingMode(tempMode);

			//if we need to set the "sync sampling mode"
			if(tempMode == WirelessTypes::samplingMode_sync ||
			   tempMode == WirelessTypes::samplingMode_syncBurst)
			{
				//find the SyncSamplingMode that we need to set (burst or not burst)
				WirelessTypes::SyncSamplingMode syncMode = WirelessTypes::syncMode_continuous;
				if(tempMode == WirelessTypes::samplingMode_syncBurst)
				{
					syncMode = WirelessTypes::syncMode_burst;
				}

				//save the sync sampling mode 
				eeprom.write_syncSamplingMode(syncMode);
			}
		}

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

		//write Fatigue Options
		if(isSet(m_fatigueOptions)) { eeprom.write_fatigueOptions(*m_fatigueOptions); }

		//write Histogram Options
		if(isSet(m_histogramOptions)) { eeprom.write_histogramOptions(*m_histogramOptions); }

		//write Hardware Gain(s)
		for(const auto& gain : m_hardwareGains)
		{
			eeprom.write_hardwareGain(gain.first, gain.second);
		}

		//write Hardware Offset(s)
		for(const auto& offset : m_hardwareOffsets)
		{
			eeprom.write_hardwareOffset(offset.first, offset.second);
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
	}

	WirelessTypes::DefaultMode WirelessNodeConfig::defaultMode() const
	{
		checkValue(m_defaultMode, "Default Mode");	//verify the value is set
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

	void WirelessNodeConfig::activeChannels(ChannelMask channels)
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

	double WirelessNodeConfig::hardwareGain(const ChannelMask& mask) const
	{
		return getChannelMapVal(m_hardwareGains, mask, "Hardware Gain");
	}

	void WirelessNodeConfig::hardwareGain(const ChannelMask& mask, double gain)
	{
		setChannelMapVal(m_hardwareGains, mask, gain);
	}

	uint16 WirelessNodeConfig::hardwareOffset(const ChannelMask& mask) const
	{
		return getChannelMapVal(m_hardwareOffsets, mask, "Hardware Offset");
	}

	void WirelessNodeConfig::hardwareOffset(const ChannelMask& mask, uint16 offset)
	{
		setChannelMapVal(m_hardwareOffsets, mask, offset);
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
}