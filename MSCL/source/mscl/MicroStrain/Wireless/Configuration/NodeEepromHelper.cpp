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
#include "NodeEepromHelper.h"

#include "FatigueOptions.h"
#include "HardwareGain.h"
#include "HistogramOptions.h"
#include "NodeEepromMap.h"
#include "mscl/MicroStrain/Wireless/WirelessNode_Impl.h"
#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"
#include "mscl/Utils.h"

namespace mscl
{
	const uint16 NodeEepromHelper::TIME_BETWEEN_BURSTS_MAX_SECS = 0x7FFF;
	const uint16 NodeEepromHelper::BYTES_PER_DATALOG_PAGE = 264;
	const uint16 NodeEepromHelper::MIN_SLEEP_INTERVAL_EEVAL = 512;
	const uint16 NodeEepromHelper::MAX_SLEEP_INTERVAL_EEVAL = 7680;
	const uint16 NodeEepromHelper::MIN_LOST_BEACON_TIMEOUT = 2;
	const uint16 NodeEepromHelper::MAX_LOST_BEACON_TIMEOUT = 600;
	const uint16 NodeEepromHelper::LOST_BEACON_TIMEOUT_DISABLED = 0;

	NodeEepromHelper::NodeEepromHelper(WirelessNode_Impl* node):
		m_node(node)
	{
	}

	Value NodeEepromHelper::read(const EepromLocation& location) const
	{
		return m_node->readEeprom(location);
	}

	void NodeEepromHelper::write(const EepromLocation& location, const Value& val)
	{
		m_node->writeEeprom(location, val);
	}

	uint16 NodeEepromHelper::nodeAddress() const
	{
		return m_node->nodeAddress();
	}

	WirelessTypes::Frequency NodeEepromHelper::read_frequency() const
	{
		//read the frequency of the node
		return static_cast<WirelessTypes::Frequency>(read(NodeEepromMap::FREQUENCY).as_uint16());
	}

	WirelessTypes::RegionCode NodeEepromHelper::read_regionCode() const
	{
		//Note: this function can never use the NodeFeatures/NodeInfo call, as NodeInfo relies on this function.

		//read the value from eeprom
		uint16 code = read(NodeEepromMap::REGION_CODE).as_uint16();

		//if set to an "uninitialized" value
		if(code == 0xAAAA || code == 0xFFFF)
		{
			code = WirelessTypes::region_usa;
		}
		//to support legacy nodes, a code of 0xFFFE should be treated as Europe
		else if(code == 0xFFFE)
		{
			code = WirelessTypes::region_europe;
		}

		return static_cast<WirelessTypes::RegionCode>(code);
	}

	Version NodeEepromHelper::read_fwVersion() const
	{
		//Note: this function can never use the NodeFeatures/NodeInfo call, as NodeInfo relies on this function.

		//read the firmware version eeprom
		uint16 fwValue1 = read(NodeEepromMap::FIRMWARE_VER).as_uint16();

		uint8 major = Utils::msb(fwValue1);

		//firmware versions < 10 use the scheme [Major].[Minor]
		if(major < 10)
		{
			uint8 minor = Utils::lsb(fwValue1);

			return Version(major, minor);
		}
		//firmware versions >= 10 use the scheme [Major].[svnRevision]
		else
		{
			uint16 fwValue2 = read(NodeEepromMap::FIRMWARE_VER2).as_uint16();

			//make the svn revision from the lsb of the first fw value, and the entire second fw value 
			uint32 svnRevision = Utils::make_uint32(0, Utils::lsb(fwValue1), Utils::msb(fwValue2), Utils::lsb(fwValue2));

			return Version(major, svnRevision);
		}
	}

	WirelessModels::NodeModel NodeEepromHelper::read_model() const
	{
		//Note: this function can never use the NodeFeatures/NodeInfo call, as NodeInfo relies on this function.

		//read the model number from eeprom
		uint16 model = read(NodeEepromMap::MODEL_NUMBER).as_uint16();

		//if the model stored in eeprom is invalid (uninitialized)
		if(model == 0xFFFF || model == 0xAAAA || model == 0)
		{
			//this node uses the legacy model number

			//read the model from the legacy model eeprom location
			model = read(NodeEepromMap::LEGACY_MODEL_NUMBER).as_uint16();

			//convert the legacy model to the new model number and return it
			return WirelessModels::nodeFromLegacyModel(model);
		}
		else
		{
			//read the model option from eeprom
			uint16 modelOption = read(NodeEepromMap::MODEL_OPTION).as_uint16();

			//build the model and model class together to form the model number
			return static_cast<WirelessModels::NodeModel>((model * 10000) + modelOption);
		}
	}

	std::string NodeEepromHelper::read_serial() const
	{
		//read the serial number 
		uint32 serial = read(NodeEepromMap::SERIAL_ID).as_uint32();

		//if the serial stored in eeprom is invalid (uninitialized)
		if(serial == 0xFFFFFFFF || serial == 0xAAAAAAAA || serial == 0)
		{
			//this node uses the legacy serial number

			//read the serial from the legacy serial id eeprom location
			serial = read(NodeEepromMap::LEGACY_SERIAL_ID).as_uint16();
		}

		//get the model number of the node
		WirelessModels::NodeModel fullModel = read_model();

		//split the model into its 2 pieces
		uint16 model = static_cast<uint16>(fullModel / 10000);
		uint16 modelClass = fullModel % 10000;

		//build the string result
		std::stringstream modelStr;
		modelStr << std::setfill('0') << std::setw(4) << model;

		std::stringstream modelClassStr;
		modelClassStr << std::setfill('0') << std::setw(4) << modelClass;

		std::stringstream serialStr;
		serialStr << std::setfill('0') << std::setw(5) << serial;

		return modelStr.str() + "-" + modelClassStr.str() + "-" + serialStr.str();
	}

	WirelessTypes::MicroControllerType NodeEepromHelper::read_microcontroller() const
	{
		//read the value from eeprom
		return static_cast<WirelessTypes::MicroControllerType>(read(NodeEepromMap::MICROCONTROLLER).as_uint16());
	}

	RadioFeatures NodeEepromHelper::read_radioFeatures() const
	{
		//read the value from eeprom
		uint16 radioVal = read(NodeEepromMap::RADIO_OPTIONS).as_uint16();

		//build a RadioFeatures object and return
		return RadioFeatures(radioVal);
	}

	uint64 NodeEepromHelper::read_dataStorageSize() const
	{
		//Note: this function can never use the NodeFeatures/NodeInfo call, as NodeInfo relies on this function.

		return read(NodeEepromMap::MAX_MEMORY).as_uint16() * BYTES_PER_DATALOG_PAGE;
	}

	WirelessTypes::SettlingTime NodeEepromHelper::read_filter1() const
	{
		//read the eeprom and convert to a WirelessTypes::SettlingTime
		return static_cast<WirelessTypes::SettlingTime>(read(NodeEepromMap::FILTER_1).as_uint16());
	}

	WirelessTypes::SettlingTime NodeEepromHelper::read_filter2() const
	{
		//read the eeprom and convert to a WirelessTypes::SettlingTime
		return static_cast<WirelessTypes::SettlingTime>(read(NodeEepromMap::FILTER_2).as_uint16());
	}

	void NodeEepromHelper::write_channelMask(const ChannelMask& channels)
	{
		//convert the ChannelMask object to the mask to write
		write(NodeEepromMap::ACTIVE_CHANNEL_MASK, Value::UINT16(channels.toMask()));
	}

	ChannelMask NodeEepromHelper::read_channelMask() const
	{
		//build the ChannelMask object from the result of the readEeprom command
		ChannelMask result;
		result.fromMask(read(NodeEepromMap::ACTIVE_CHANNEL_MASK).as_uint16());

		return result;
	}

	void NodeEepromHelper::write_numSweeps(uint32 sweeps)
	{
		//divide by 100 to write to eeprom
		write( NodeEepromMap::NUM_SWEEPS, Value::UINT16(static_cast<uint16>(sweeps / 100)) );
	}

	uint32 NodeEepromHelper::read_numSweeps() const
	{
		//read the number of sweeps and multiple by 100
		return read(NodeEepromMap::NUM_SWEEPS).as_uint16() * 100;
	}

	void NodeEepromHelper::write_unlimitedDuration(bool unlimitedDuration, WirelessTypes::SamplingMode samplingMode)
	{
		//set the original eeprom location for unlimited sampling
		EepromLocation unlimitedSamplingLocation = NodeEepromMap::UNLIMITED_SAMPLING;

		//if the sampling mode is set to armed datalogging
		if(samplingMode == WirelessTypes::samplingMode_armedDatalog)
		{
			//the unlimited sampling location is different for armed datalogging
			unlimitedSamplingLocation = NodeEepromMap::UNLIMITED_DATALOG;
		}

		//write the value to the correct eeprom location
		write( unlimitedSamplingLocation, Value::UINT16(static_cast<uint16>(unlimitedDuration)) );
	}

	bool NodeEepromHelper::read_unlimitedDuration(WirelessTypes::SamplingMode samplingMode) const
	{
		//set the original eeprom location for unlimited sampling
		EepromLocation unlimitedSamplingLocation = NodeEepromMap::UNLIMITED_SAMPLING;

		//if the sampling mode is set to armed datalogging
		if(samplingMode == WirelessTypes::samplingMode_armedDatalog)
		{
			//the unlimited sampling location is different for armed datalogging
			unlimitedSamplingLocation = NodeEepromMap::UNLIMITED_DATALOG;
		}

		//read the value from the correct eeprom location
		return (read(unlimitedSamplingLocation).as_uint16() == 1);
	}

	void NodeEepromHelper::write_sampleRate(WirelessTypes::WirelessSampleRate rate, WirelessTypes::SamplingMode samplingMode)
	{
		//set the original eeprom location for sample rate
		EepromLocation sampleRateLocation = NodeEepromMap::SAMPLE_RATE;
		uint16 eepromValue = static_cast<uint16>(rate);

		//if the sampling mode is set to armed datalogging
		if(samplingMode == WirelessTypes::samplingMode_armedDatalog)
		{
			//the sample rate location is different for armed datalogging
			sampleRateLocation = NodeEepromMap::DATALOG_SAMPLE_RATE;

			//convert to the datalogging eeprom value
			eepromValue = WirelessTypes::sampleRateToDataloggingRate(rate);
		}

		//write the value to the correct eeprom location
		write(sampleRateLocation, Value::UINT16(eepromValue));
	}

	WirelessTypes::WirelessSampleRate NodeEepromHelper::read_sampleRate(WirelessTypes::SamplingMode samplingMode) const
	{
		//if the sampling mode is set to armed datalogging
		if(samplingMode == WirelessTypes::samplingMode_armedDatalog)
		{
			//read the value from the datalogging eeprom location
			return WirelessTypes::dataloggingRateToSampleRate(read(NodeEepromMap::DATALOG_SAMPLE_RATE).as_uint16());
		}
		else
		{
			//read the value from the eeprom location
			return static_cast<WirelessTypes::WirelessSampleRate>(read(NodeEepromMap::SAMPLE_RATE).as_uint16());
		}
	}

	void NodeEepromHelper::write_dataFormat(WirelessTypes::DataFormat dataFormat)
	{
		write( NodeEepromMap::DATA_FORMAT, Value::UINT16(static_cast<uint16>(dataFormat)) );
	}

	WirelessTypes::DataFormat NodeEepromHelper::read_dataFormat() const
	{
		return static_cast<WirelessTypes::DataFormat>(read(NodeEepromMap::DATA_FORMAT).as_uint16());
	}

	void NodeEepromHelper::write_collectionMode(WirelessTypes::DataCollectionMethod collectionMode)
	{
		write( NodeEepromMap::COLLECTION_MODE, Value::UINT16(static_cast<uint16>(collectionMode)) );
	}

	WirelessTypes::DataCollectionMethod NodeEepromHelper::read_collectionMode() const
	{
		return static_cast<WirelessTypes::DataCollectionMethod>(read(NodeEepromMap::COLLECTION_MODE).as_uint16());
	}

	void NodeEepromHelper::write_syncSamplingMode(WirelessTypes::SyncSamplingMode syncMode)
	{
		write(NodeEepromMap::SYNC_SAMPLE_SETTING, Value::UINT16(static_cast<uint16>(syncMode)));
	}

	WirelessTypes::SyncSamplingMode NodeEepromHelper::read_syncSamplingMode() const
	{
		return static_cast<WirelessTypes::SyncSamplingMode>(read(NodeEepromMap::SYNC_SAMPLE_SETTING).as_uint16());
	}

	void NodeEepromHelper::write_samplingDelay(TimeSpan delay)
	{
		uint64 valueToWrite = 0;

		//get the type of node
		WirelessModels::NodeModel nodeType = m_node->model();

		switch(nodeType)
		{
			//these nodes all store the sampling delay in microseconds
			case WirelessModels::node_shmLink:
			case WirelessModels::node_shmLink2:
			case WirelessModels::node_sgLink_herm:
			case WirelessModels::node_sgLink_herm_2600:
			case WirelessModels::node_sgLink_herm_2700:
			case WirelessModels::node_sgLink_herm_2800:
			case WirelessModels::node_sgLink_rgd:
				valueToWrite = delay.getMicroseconds();
				break;

			default:
				break;
		}

		//if the delay is 1 second or more
		if(delay >= TimeSpan::Seconds(1))
		{
			//the delay should be stored as seconds
			valueToWrite = delay.getSeconds();
			valueToWrite += 32768;	//set the most significant bit on
		}
		else
		{
			//the delay should be stored as milliseconds
			valueToWrite = delay.getMilliseconds();
		}

		write(NodeEepromMap::SAMPLING_DELAY, Value::UINT16(static_cast<uint16>(valueToWrite)));
	}

	TimeSpan NodeEepromHelper::read_samplingDelay() const
	{
		//get the type of node
		WirelessModels::NodeModel nodeType = m_node->model();

		//read the value that is in eeprom
		uint16 samplingDelay = read(NodeEepromMap::SAMPLING_DELAY).as_uint16();

		switch(nodeType)
		{
			//these nodes all read the sampling delay in microseconds
			case WirelessModels::node_shmLink:
			case WirelessModels::node_shmLink2:
			case WirelessModels::node_sgLink_herm:
			case WirelessModels::node_sgLink_herm_2600:
			case WirelessModels::node_sgLink_herm_2700:
			case WirelessModels::node_sgLink_herm_2800:
			case WirelessModels::node_sgLink_rgd:
				return TimeSpan::MicroSeconds(samplingDelay);

			default:
				break;
		}

		//if the most significant bit is set
		if(Utils::bitIsSet(samplingDelay, 15))
		{
			//the value is in seconds, and we need to subtract out the most significant bit
			return TimeSpan::Seconds(samplingDelay - 32768);
		}
		else
		{
			//the value is in milliseconds
			return TimeSpan::MilliSeconds(samplingDelay);
		}
	}

	void NodeEepromHelper::write_retransmission(WirelessTypes::NodeRetransmission reTx)
	{
		write(NodeEepromMap::NODE_RETRANSMIT, Value::UINT16(static_cast<uint16>(reTx)));
	}

	WirelessTypes::NodeRetransmission NodeEepromHelper::read_retransmission() const
	{
		//read the value from eeprom
		uint16 retransmissionsVal = read(NodeEepromMap::NODE_RETRANSMIT).as_uint16();

		//if the retransmission value is outside the range
		if(retransmissionsVal > WirelessTypes::retransmission_disabled)
		{
			//it is "disabled"
			retransmissionsVal = WirelessTypes::retransmission_disabled;
		}

		//convert to a NodeRetransmission enum and return
		return static_cast<WirelessTypes::NodeRetransmission>(retransmissionsVal);
	}

	void NodeEepromHelper::write_timeBetweenBursts(const TimeSpan& timespan)
	{
		//get the time in seconds from the TimeSpan
		uint64 timeInSeconds = timespan.getSeconds();

		//0 = seconds, 1 = minutes
		uint16 timeResolution = 0;

		//if the total seconds in the timespan is more than we can set when using "seconds"
		if(timeInSeconds > TIME_BETWEEN_BURSTS_MAX_SECS)
		{
			//convert from seconds to minutes (rounding up)
			timeInSeconds = static_cast<uint16>(std::ceil(static_cast<float>(timeInSeconds / 60.0f)));

			//set the resolution to minutes
			timeResolution = 1;
		}

		//build the value to write from the resolution bit and the time in seconds
		uint16 valToWrite = (timeResolution << 15) + static_cast<uint16>(timeInSeconds);

		//write the value we calculated
		write(NodeEepromMap::TIME_BETW_SESSIONS, Value::UINT16(valToWrite));
	}

	TimeSpan NodeEepromHelper::read_timeBetweenBursts() const
	{
		//read the value that is stored in EEPROM
		uint16 eepromVal = read(NodeEepromMap::TIME_BETW_SESSIONS).as_uint16();

		//pull off the time resolution bit
		uint8 timeResolution = eepromVal >> 15;

		//pull off the actual time value
		uint16 time = eepromVal & (TIME_BETWEEN_BURSTS_MAX_SECS);

		//if the time resolution is in minutes
		if(timeResolution == 1)
		{
			//return the minutes timespan
			return TimeSpan::Minutes(time);
		}
		else
		{
			//return the seconds timespan
			return TimeSpan::Seconds(time);
		}
	}

	void NodeEepromHelper::write_samplingMode(WirelessTypes::SamplingMode samplingMode)
	{
		write(NodeEepromMap::SAMPLING_MODE, Value::UINT16(static_cast<uint16>(samplingMode)));
	}

	WirelessTypes::SamplingMode NodeEepromHelper::read_samplingMode() const
	{
		//read the sampling mode eeprom value
		uint16 samplingModeVal = read(NodeEepromMap::SAMPLING_MODE).as_uint16();

		//if the sampling mode value is not set
		if(samplingModeVal == 0 || samplingModeVal == 0xFFFF || samplingModeVal == 0xAAAA)
		{
			//need to check if burst is enabled
			WirelessTypes::SyncSamplingMode mode = read_syncSamplingMode();
			if(mode == WirelessTypes::syncMode_burst)
			{
				return WirelessTypes::samplingMode_syncBurst;
			}

			//default to the first sampling mode (sync sampling)
			return WirelessTypes::samplingMode_sync;
		}

		//cast to a sampling mode and return
		return static_cast<WirelessTypes::SamplingMode>(samplingModeVal);
	}

	void NodeEepromHelper::write_channelLinearEquation(const ChannelMask& mask, const LinearEquation& equation)
	{
		//find the eeproms
		const EepromLocation& slopeEeprom = m_node->features().findEeprom(WirelessTypes::chSetting_linearEquation, mask);
		const EepromLocation& offsetEeprom = NodeEepromMap::getOffsetEeprom(slopeEeprom);

		//write the slope to eeprom
		write(slopeEeprom, Value::FLOAT(equation.slope()));

		//write the offset to eeprom
		write(offsetEeprom, Value::FLOAT(equation.offset()));
	}

	void NodeEepromHelper::read_channelLinearEquation(const ChannelMask& mask, LinearEquation& result)
	{
		//find the eeproms
		const EepromLocation& slopeEeprom = m_node->features().findEeprom(WirelessTypes::chSetting_linearEquation, mask);
		const EepromLocation& offsetEeprom = NodeEepromMap::getOffsetEeprom(slopeEeprom);

		//read the slope from eeprom
		result.slope(read(slopeEeprom).as_float());

		//read the offset from eeprom
		result.offset(read(offsetEeprom).as_float());
	}

	void NodeEepromHelper::write_channelUnit(const ChannelMask& mask, WirelessTypes::CalCoef_Unit unit)
	{
		//unit and equation are the same eeprom location, so have to read the currently set equation
		WirelessTypes::CalCoef_EquationType currentEquation = read_channelEquation(mask);

		//write the full channel unit and eqaution
		write_channelUnitAndEquation(mask, unit, currentEquation);
	}

	void NodeEepromHelper::write_channelEquation(const ChannelMask& mask, WirelessTypes::CalCoef_EquationType equation)
	{
		//unit and equation are the same eeprom location, so have to read the currently set unit
		WirelessTypes::CalCoef_Unit currentUnit = read_channelUnit(mask);

		//write the full channel unit and eqaution
		write_channelUnitAndEquation(mask, currentUnit, equation);
	}

	void NodeEepromHelper::write_channelUnitAndEquation(const ChannelMask& mask, WirelessTypes::CalCoef_Unit unit, WirelessTypes::CalCoef_EquationType equation)
	{
		//calculate the correct unit eeprom location for this channel
		const EepromLocation& eepromLocation = m_node->features().findEeprom(WirelessTypes::chSetting_unit, mask);

		//make the action id from the equation (msb) and unit (lsb) values
		uint16 actionIdVal = Utils::make_uint16(static_cast<uint8>(equation), static_cast<uint8>(unit));
		
		//write the action id to eeprom
		write(eepromLocation, Value::UINT16(actionIdVal));
	}

	WirelessTypes::CalCoef_Unit NodeEepromHelper::read_channelUnit(const ChannelMask& mask) const
	{
		//calculate the correct unit eeprom location for this channel
		const EepromLocation& eepromLocation = m_node->features().findEeprom(WirelessTypes::chSetting_unit, mask);

		//read the action id from eeprom
		uint16 actionIdVal = read(eepromLocation).as_uint16();

		//the unit is the lsb of the actionId
		return static_cast<WirelessTypes::CalCoef_Unit>(Utils::lsb(actionIdVal));
	}

	WirelessTypes::CalCoef_EquationType NodeEepromHelper::read_channelEquation(const ChannelMask& mask) const
	{
		//calculate the correct unit eeprom location for this channel
		const EepromLocation& eepromLocation = m_node->features().findEeprom(WirelessTypes::chSetting_equationType, mask);

		//read the action id from eeprom
		uint16 actionIdVal = read(eepromLocation).as_uint16();

		//the unit is the lsb of the actionId
		return static_cast<WirelessTypes::CalCoef_EquationType>(Utils::msb(actionIdVal));
	}

	WirelessTypes::TransmitPower NodeEepromHelper::read_transmitPower() const
	{
		//read and return the transmit power level
		return static_cast<WirelessTypes::TransmitPower>(read(NodeEepromMap::TX_POWER_LEVEL).as_uint16());
	}

	void NodeEepromHelper::write_transmitPower(WirelessTypes::TransmitPower power)
	{
		//write the transmit power level to the node
		write(NodeEepromMap::TX_POWER_LEVEL, Value::UINT16(static_cast<uint16>(power)));
	}

	uint16 NodeEepromHelper::read_inactivityTimeout() const
	{
		//read and return the inactivity timeout
		return read(NodeEepromMap::INACTIVE_TIMEOUT).as_uint16();
	}

	void NodeEepromHelper::write_inactivityTimeout(uint16 timeout)
	{
		//write the timeout value to the node
		write(NodeEepromMap::INACTIVE_TIMEOUT, Value::UINT16(timeout));
	}

	uint8 NodeEepromHelper::read_checkRadioInterval() const
	{
		//read the value stored in eeprom
		uint16 eeVal = read(NodeEepromMap::SLEEP_INTERVAL).as_uint16();

		uint16 seconds = 5;
		if(eeVal != 0)
		{
			seconds = (MAX_SLEEP_INTERVAL_EEVAL / eeVal);
		}		

		//if the seconds value is more than 60 seconds
		if(seconds > 60)
		{
			//the node defaults to 5 seconds
			seconds = 5;
		}

		return static_cast<uint8>(seconds);
	}

	void NodeEepromHelper::write_checkRadioInterval(uint8 interval)
	{
		//calculate the eeprom value to write
		uint16 eepromVal = (MAX_SLEEP_INTERVAL_EEVAL / interval);

		//write the value to the node
		write(NodeEepromMap::SLEEP_INTERVAL, Value::UINT16(eepromVal));
	}

	WirelessTypes::DefaultMode NodeEepromHelper::read_defaultMode() const
	{
		uint16 val = read(NodeEepromMap::DEFAULT_MODE).as_uint16();

		//anything out of range of the boot modes is considered normal boot mode (idle)
		if(val > WirelessTypes::defaultMode_sync)
		{
			val = WirelessTypes::defaultMode_idle;
		}

		//read and return the boot mode value
		return static_cast<WirelessTypes::DefaultMode>(val);
	}

	void NodeEepromHelper::write_defaultMode(WirelessTypes::DefaultMode mode)
	{
		//write the boot mode value to the node
		write(NodeEepromMap::DEFAULT_MODE, Value::UINT16(static_cast<uint16>(mode)));
	}

	uint16 NodeEepromHelper::read_logPage() const
	{
		//read the current log page, always multiply by 2 to get the real log page
		return read(NodeEepromMap::CURRENT_LOG_PAGE).as_uint16() * 2;
	}

	uint16 NodeEepromHelper::read_logPageOffset() const
	{
		//read and return the current log page offset
		return read(NodeEepromMap::CURRENT_PAGE_OFFSET).as_uint16();
	}

	uint16 NodeEepromHelper::read_numDatalogSessions() const
	{
		//read and return the number of datalog sessions value
		return read(NodeEepromMap::DATA_SETS_STORED).as_uint16();
	}

	void NodeEepromHelper::write_txPerGroup(uint16 txPerGroup)
	{
		//write the transmissions per group value to eeprom
		write(NodeEepromMap::TX_PER_GROUP, Value::UINT16(txPerGroup));
	}

	void NodeEepromHelper::write_groupSize(uint16 groupSize)
	{
		//write the group size value to eeprom
		write(NodeEepromMap::GROUP_SIZE, Value::UINT16(groupSize));
	}

	void NodeEepromHelper::write_tdmaAddress(uint16 address)
	{
		//write the TDMA address to eeprom
		write(NodeEepromMap::TDMA_ADDRESS, Value::UINT16(address));
	}

	void NodeEepromHelper::write_maxRetransPerBurst(uint16 maxReTxPerBurst)
	{
		//write the max retransmissions per burst to eeprom
		write(NodeEepromMap::MAX_RETRANS_BURST, Value::UINT16(maxReTxPerBurst));
	}

	double NodeEepromHelper::read_hardwareGain(const ChannelMask& mask) const
	{
		//find the eeprom location
		const EepromLocation& eeprom = m_node->features().findEeprom(WirelessTypes::chSetting_hardwareGain, mask);

		//read the bits value stored in eeprom
		uint16 bitsVal = read(eeprom).as_uint16();

		//convert the bits value to gain and return
		return HardwareGain::bitsToGain(bitsVal, m_node->model());
	}

	uint16 NodeEepromHelper::read_hardwareOffset(const ChannelMask& mask) const
	{
		//find the eeprom location
		const EepromLocation& eeprom = m_node->features().findEeprom(WirelessTypes::chSetting_hardwareOffset, mask);

		//return the result read from eeprom
		return read(eeprom).as_uint16();
	}

	void NodeEepromHelper::write_hardwareGain(const ChannelMask& mask, double gain)
	{
		//find the eeprom location
		const EepromLocation& eeprom = m_node->features().findEeprom(WirelessTypes::chSetting_hardwareGain, mask);

		//convert the gain value to bits, which is what gets written to eeprom
		uint16 bitsVal = HardwareGain::gainToBits(gain, m_node->model());

		//write the hardware gain (in bits) to eeprom
		write(eeprom, Value::UINT16(bitsVal));
	}

	void NodeEepromHelper::write_hardwareOffset(const ChannelMask& mask, uint16 offset)
	{
		//find the eeprom location
		const EepromLocation& eeprom = m_node->features().findEeprom(WirelessTypes::chSetting_hardwareOffset, mask);

		//write the hardware gain (in bits) to eeprom
		write(eeprom, Value::UINT16(offset));
	}

	WirelessTypes::ThermocoupleType NodeEepromHelper::read_thermoType(const ChannelMask& mask) const
	{
		//find the eeprom location
		const EepromLocation& eeprom = m_node->features().findEeprom(WirelessTypes::chSetting_thermocoupleType, mask);

		//read and return the thermocouple type
		return static_cast<WirelessTypes::ThermocoupleType>(read(eeprom).as_uint16());
	}

	void NodeEepromHelper::write_thermoType(const ChannelMask& mask, WirelessTypes::ThermocoupleType thermocouple)
	{
		//find the eeprom location
		const EepromLocation& eeprom = m_node->features().findEeprom(WirelessTypes::chSetting_thermocoupleType, mask);

		//write the thermocouple type to the Node
		write(eeprom, Value::UINT16(static_cast<uint16>(thermocouple)));
	}

	void NodeEepromHelper::read_fatigueOptions(FatigueOptions& result) const
	{
		const NodeFeatures& features = m_node->features();

		uint8 numDamageAngles = features.numDamageAngles();
		uint8 numSnCurveSegments = features.numSnCurveSegments();

		//the legacy SHM-Link has different eeproms for damage angles
		bool hasLegacyAngles = (features.m_nodeInfo.model == WirelessModels::node_shmLink);

		//Young's Modulus
		if(features.supportsYoungsModConfig())
		{
			result.youngsModulus(read(NodeEepromMap::YOUNGS_MODULUS).as_float());
		}

		//Poisson's Ratio
		if(features.supportsPoissonsRatioConfig())
		{
			result.poissonsRatio(read(NodeEepromMap::POISSONS_RATIO).as_float());
		}

		//Peak/Valley Threshold
		result.peakValleyThreshold(read(NodeEepromMap::PEAK_VALLEY_THRES).as_uint16());

		//Raw Mode
		if(features.supportsFatigueRawModeConfig())
		{
			bool rawModeEnabled = (read(NodeEepromMap::HISTOGRAM_RAW_FLAG).as_uint16() == 1);
			result.rawMode(rawModeEnabled);
		}

		//=============================
		//Damage Angles
		if(hasLegacyAngles)
		{
			if(numDamageAngles >= 1)
			{
				result.damageAngle(0, read(NodeEepromMap::LEGACY_DAMAGE_ANGLE_1).as_float());	//convert uint16 to float
			}

			if(numDamageAngles >= 2)
			{
				result.damageAngle(1, read(NodeEepromMap::LEGACY_DAMAGE_ANGLE_2).as_float());	//covert uint16 to float
			}

			if(numDamageAngles >= 3)
			{
				result.damageAngle(2, read(NodeEepromMap::LEGACY_DAMAGE_ANGLE_3).as_float());	//convert uint16 to float
			}
		}
		else
		{
			if(numDamageAngles >= 1)
			{
				result.damageAngle(0, read(NodeEepromMap::DAMAGE_ANGLE_1).as_float());
			}

			if(numDamageAngles >= 2)
			{
				result.damageAngle(1, read(NodeEepromMap::DAMAGE_ANGLE_2).as_float());
			}

			if(numDamageAngles >= 3)
			{
				result.damageAngle(2, read(NodeEepromMap::DAMAGE_ANGLE_3).as_float());
			}
		}
		//=============================

		//=============================
		//SN Curve Segments
		if(numSnCurveSegments >= 1)
		{
			result.snCurveSegment(0, SnCurveSegment(read(NodeEepromMap::SNCURVE_M_1).as_float(), read(NodeEepromMap::SNCURVE_LOGA_1).as_float()));
		}

		if(numSnCurveSegments >= 2)
		{
			result.snCurveSegment(1, SnCurveSegment(read(NodeEepromMap::SNCURVE_M_2).as_float(), read(NodeEepromMap::SNCURVE_LOGA_2).as_float()));
		}

		if(numSnCurveSegments >= 3)
		{
			result.snCurveSegment(2, SnCurveSegment(read(NodeEepromMap::SNCURVE_M_3).as_float(), read(NodeEepromMap::SNCURVE_LOGA_3).as_float()));
		}
		//=============================
	}

	void NodeEepromHelper::write_fatigueOptions(const FatigueOptions& options)
	{
		const NodeFeatures& features = m_node->features();

		uint8 numDamageAngles = features.numDamageAngles();
		uint8 numSnCurveSegments = features.numSnCurveSegments();

		//the legacy SHM-Link has different eeproms for damage angles
		bool hasLegacyAngles = (features.m_nodeInfo.model == WirelessModels::node_shmLink);

		//Young's Modulus
		if(features.supportsYoungsModConfig())
		{
			write(NodeEepromMap::YOUNGS_MODULUS, Value::FLOAT(options.youngsModulus()));
		}

		//Poisson's Ratio
		if(features.supportsPoissonsRatioConfig())
		{
			write(NodeEepromMap::POISSONS_RATIO, Value::FLOAT(options.poissonsRatio()));
		}

		//Peak/Valley Threshold
		write(NodeEepromMap::PEAK_VALLEY_THRES, Value::UINT16(options.peakValleyThreshold()));

		//Raw Mode
		if(features.supportsFatigueRawModeConfig())
		{
			write(NodeEepromMap::HISTOGRAM_RAW_FLAG, Value::UINT16(static_cast<uint16>(options.rawMode())));
		}

		//=============================
		//Damage Angles
		const auto& angles = options.damageAngles();
		const auto& anglesEnd = angles.end();

		if(hasLegacyAngles)
		{
			auto angle = angles.find(0);
			if(numDamageAngles >= 1 && angle != anglesEnd)
			{
				write(NodeEepromMap::LEGACY_DAMAGE_ANGLE_1, Value::UINT16(static_cast<uint16>(angle->second)));	//convert float to uint16
			}

			angle = angles.find(1);
			if(numDamageAngles >= 2 && angle != anglesEnd)
			{
				write(NodeEepromMap::LEGACY_DAMAGE_ANGLE_2, Value::UINT16(static_cast<uint16>(angle->second)));	//convert float to uint16
			}

			angle = angles.find(2);
			if(numDamageAngles >= 3 && angle != anglesEnd)
			{
				write(NodeEepromMap::LEGACY_DAMAGE_ANGLE_3, Value::UINT16(static_cast<uint16>(angle->second)));	//convert float to uint16
			}
		}
		else
		{
			auto angle = angles.find(0);
			if(numDamageAngles >= 1 && angle != anglesEnd)
			{
				write(NodeEepromMap::DAMAGE_ANGLE_1, Value::FLOAT(angle->second));
			}

			angle = angles.find(1);
			if(numDamageAngles >= 2 && angle != anglesEnd)
			{
				write(NodeEepromMap::DAMAGE_ANGLE_2, Value::FLOAT(angle->second));
			}

			angle = angles.find(2);
			if(numDamageAngles >= 3 && angle != anglesEnd)
			{
				write(NodeEepromMap::DAMAGE_ANGLE_3, Value::FLOAT(angle->second));
			}
		}
		//=============================

		//=============================
		//SN Curve Segments
		const auto& segments = options.snCurveSegments();

		auto segment = segments.find(0);
		if(numSnCurveSegments >= 1 && segment != segments.end())
		{
			write(NodeEepromMap::SNCURVE_M_1, Value::FLOAT(segment->second.m()));
			write(NodeEepromMap::SNCURVE_LOGA_1, Value::FLOAT(segment->second.logA()));
		}

		segment = segments.find(1);
		if(numSnCurveSegments >= 2 && segment != segments.end())
		{
			write(NodeEepromMap::SNCURVE_M_2, Value::FLOAT(segment->second.m()));
			write(NodeEepromMap::SNCURVE_LOGA_2, Value::FLOAT(segment->second.logA()));
		}

		segment = segments.find(2);
		if(numSnCurveSegments >= 3 && segment != segments.end())
		{
			write(NodeEepromMap::SNCURVE_M_3, Value::FLOAT(segment->second.m()));
			write(NodeEepromMap::SNCURVE_LOGA_3, Value::FLOAT(segment->second.logA()));
		}
		//=============================
	}

	void NodeEepromHelper::read_histogramOptions(HistogramOptions& result) const
	{
		//Transmit Rate
		if(m_node->features().supportsHistogramRateConfig())
		{
			auto rate = static_cast<mscl::WirelessTypes::WirelessSampleRate>(read(NodeEepromMap::HISTOGRAM_SAMPLE_RATE).as_uint16());

			result.transmitRate(rate);
		}

		//Bin Start
		result.binsStart(read(NodeEepromMap::BIN_START).as_uint16());

		//Bin Size
		result.binsSize(read(NodeEepromMap::BIN_SIZE).as_uint16());
	}

	void NodeEepromHelper::write_histogramOptions(const HistogramOptions& options)
	{
		uint16 rateVal = static_cast<uint16>(options.transmitRate());

		//Transmit Rate
		if(m_node->features().supportsHistogramRateConfig())
		{
			write(NodeEepromMap::HISTOGRAM_SAMPLE_RATE, Value::UINT16(rateVal));
		}

		//Bin Start
		write(NodeEepromMap::BIN_START, Value::UINT16(options.binsStart()));

		//Bin Size
		write(NodeEepromMap::BIN_SIZE, Value::UINT16(options.binsSize()));
	}

	void NodeEepromHelper::clearHistogram()
	{
		//histogram is cleared by writing a 1 to the RESET_BINS eeprom location
		write(NodeEepromMap::RESET_BINS, Value::UINT16(1));
	}

	WirelessTypes::SettlingTime NodeEepromHelper::read_settlingTime(const ChannelMask& mask) const
	{
		//find the eeprom location
		const EepromLocation& eeprom = m_node->features().findEeprom(WirelessTypes::chSetting_filterSettlingTime, mask);

		//read the eeprom and convert to a WirelessTypes::SettlingTime
		return static_cast<WirelessTypes::SettlingTime>(read(eeprom).as_uint16());
	}

	void NodeEepromHelper::write_settlingTime(const ChannelMask& mask, WirelessTypes::SettlingTime settlingTime)
	{
		//find the eeprom location
		const EepromLocation& eeprom = m_node->features().findEeprom(WirelessTypes::chSetting_filterSettlingTime, mask);

		//cast to a uint16 and write to the node
		write(eeprom, Value::UINT16(static_cast<uint16>(settlingTime)));
	}

	uint16 NodeEepromHelper::read_lostBeaconTimeout() const
	{
		//read the value from eeprom
		uint16 minutes = read(NodeEepromMap::LOST_BEACON_TIMEOUT).as_uint16();

		if(minutes == 1)
		{	
			//the minimum timeouts is 2 minutes
			//the node changes 1 minute to 2 minutes
			minutes = MIN_LOST_BEACON_TIMEOUT;
		}
		else if(minutes > MAX_LOST_BEACON_TIMEOUT)
		{
			//if the timeout is greater than 600, it is disabled (0)
			minutes = LOST_BEACON_TIMEOUT_DISABLED;
		}

		return minutes;
	}

	void NodeEepromHelper::write_lostBeaconTimeout(uint16 minutes)
	{
		//write the value to eeprom
		write(NodeEepromMap::LOST_BEACON_TIMEOUT, Value::UINT16(minutes));
	}
}