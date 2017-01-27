/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "NodeEepromHelper.h"

#include "ActivitySense.h"
#include "EventTriggerOptions.h"
#include "FatigueOptions.h"
#include "HistogramOptions.h"
#include "InputRange.h"
#include "NodeEepromMap.h"
#include "WirelessNodeConfig.h"
#include "mscl/MicroStrain/Wireless/WirelessNode_Impl.h"
#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"
#include "mscl/MicroStrain/Wireless/Features/FlashInfo.h"
#include "mscl/Utils.h"

namespace mscl
{
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

    void NodeEepromHelper::applyEepromChanges()
    {
        //if we can just reset the radio to commit the changes
        if(m_node->features().supportsEepromCommitViaRadioReset())
        {
            m_node->resetRadio();
        }
        else
        {
            m_node->cyclePower();
        }
    }

    WirelessTypes::Frequency NodeEepromHelper::read_frequency() const
    {
        //read the frequency of the node
        return static_cast<WirelessTypes::Frequency>(read(NodeEepromMap::FREQUENCY).as_uint16());
    }

    WirelessTypes::RegionCode NodeEepromHelper::read_regionCode() const
    {
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

    Version NodeEepromHelper::read_asppVersion() const
    {
        uint16 asppValue = 0;

        try
        {
            //read the ASPP vesrion eeprom
            asppValue = read(NodeEepromMap::ASPP_VER).as_uint16();
        }
        catch(Error_NotSupported&)
        {
            //if the eeprom isn't supported, just leave it as 0
            //which will then fall back to the firmware version to
            //determine the ASPP version number
        }

        //if the aspp version is uninitialized
        if(asppValue == 0xFFFF || asppValue == 0xAAAA || asppValue == 0)
        {
            Version fwVersion = read_fwVersion();

            //convert the firmware version of the ASPP version
            return WirelessProtocol::asppVersionFromNodeFw(fwVersion);
        }
        else
        {
            //ASPP version is good in eeprom, just return that version number
            return Version(Utils::msb(asppValue), Utils::lsb(asppValue));
        }
    }

    WirelessModels::NodeModel NodeEepromHelper::read_model() const
    {
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
        if(m_node->features().supportsFlashId())
        {
            return read_flashInfo().storageSize;
        }
        else
        {
            return read(NodeEepromMap::MAX_MEMORY).as_uint16() * BYTES_PER_DATALOG_PAGE;
        }
    }

    FlashInfo NodeEepromHelper::read_flashInfo() const
    {
        return FlashInfo::FROM_FLASH_ID(read(NodeEepromMap::FLASH_ID).as_uint16());
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
        write(NodeEepromMap::NUM_SWEEPS, Value::UINT16(static_cast<uint16>(sweeps / 100)));
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
        write(unlimitedSamplingLocation, Value::UINT16(static_cast<uint16>(unlimitedDuration)));
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
        write(NodeEepromMap::DATA_FORMAT, Value::UINT16(static_cast<uint16>(dataFormat)));
    }

    WirelessTypes::DataFormat NodeEepromHelper::read_dataFormat() const
    {
        return static_cast<WirelessTypes::DataFormat>(read(NodeEepromMap::DATA_FORMAT).as_uint16());
    }

    void NodeEepromHelper::write_collectionMode(WirelessTypes::DataCollectionMethod collectionMode)
    {
        write(NodeEepromMap::COLLECTION_MODE, Value::UINT16(static_cast<uint16>(collectionMode)));
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

    void NodeEepromHelper::write_sensorDelay(uint32 microseconds)
    {
        uint16 valueToWrite = 0;

        //if the user is setting the value to Always On
        if(microseconds == WirelessNodeConfig::SENSOR_DELAY_ALWAYS_ON)
        {
            //check "always on" is supported
            if(!m_node->features().supportsSensorDelayAlwaysOn())
            {
                throw Error_NotSupported("Sensor Delay Always On is not supported.");
            }

            if(m_node->features().usesLegacySensorDelayAlwaysOn())
            {
                valueToWrite = 10000;
            }
            else
            {
                valueToWrite = 0xFFFF;
            }
        }
        else
        {
            uint8 delayVersion = m_node->features().sensorDelayVersion();

            TimeSpan delay{TimeSpan::MicroSeconds(microseconds)};

            //Milliseconds only
            if(delayVersion == 1)
            {
                valueToWrite = static_cast<uint16>(delay.getMilliseconds());
            }
            //Microseconds only
            else if(delayVersion == 2)
            {
                valueToWrite = static_cast<uint16>(delay.getMicroseconds());
            }
            //Seconds or Milliseconds
            else if(delayVersion == 3)
            {
                //if the delay is 1 second or more
                if(delay >= TimeSpan::Seconds(1))
                {
                    //the delay needs to be stored as seconds
                    valueToWrite = static_cast<uint16>(delay.getSeconds());

                    //set the most significant bit on to signify seconds
                    Utils::setBit(valueToWrite, 15, true);
                }
                else
                {
                    //the delay needs to be stored as milliseconds
                    valueToWrite = static_cast<uint16>(delay.getMilliseconds());

                    //set the most significant bit off to signify milliseconds
                    Utils::setBit(valueToWrite, 15, false);
                }
            }
            //Seconds, Milliseconds, or Microseconds
            else if(delayVersion == 4)
            {
                //if the delay is 1 second or more
                if(delay >= TimeSpan::Seconds(1))
                {
                    //the delay needs to be stored as seconds
                    valueToWrite = static_cast<uint16>(delay.getSeconds());

                    //0b10 - Seconds
                    Utils::setBit(valueToWrite, 15, true);
                    Utils::setBit(valueToWrite, 14, false);
                }
                //less than 1 second but more than 1 millisecond
                else if(delay >= TimeSpan::MilliSeconds(1))
                {
                    valueToWrite = static_cast<uint16>(delay.getMilliseconds());

                    //0b01 - Milliseconds
                    Utils::setBit(valueToWrite, 15, false);
                    Utils::setBit(valueToWrite, 14, true);
                }
                //less than 1 millisecond
                else
                {
                    valueToWrite = static_cast<uint16>(delay.getMicroseconds());

                    //0b00 - Microseconds
                    Utils::setBit(valueToWrite, 15, false);
                    Utils::setBit(valueToWrite, 14, false);
                }
            }
        }

        write(NodeEepromMap::SAMPLING_DELAY, Value::UINT16(static_cast<uint16>(valueToWrite)));
    }

    uint32 NodeEepromHelper::read_sensorDelay() const
    {
        //read the value that is in eeprom
        uint16 eeVal = read(NodeEepromMap::SAMPLING_DELAY).as_uint16();

        //check for the "always on" value, if supported
        if(m_node->features().supportsSensorDelayAlwaysOn())
        {
            if(m_node->features().usesLegacySensorDelayAlwaysOn())
            {
                if(eeVal == 10000)
                {
                    return WirelessNodeConfig::SENSOR_DELAY_ALWAYS_ON;
                }
            }
            else
            {
                if(eeVal == 0xFFFF)
                {
                    return WirelessNodeConfig::SENSOR_DELAY_ALWAYS_ON;
                }
            }
        }

        uint8 delayVersion = m_node->features().sensorDelayVersion();

        //Milliseconds only
        if(delayVersion == 1)
        {
            //if outside the max milliseconds range, defaults to 5ms
            if(eeVal > 500)
            {
                eeVal = 5;
            }

            return static_cast<uint32>(TimeSpan::MilliSeconds(eeVal).getMicroseconds());
        }
        //Microseconds only
        else if(delayVersion == 2)
        {
            return static_cast<uint32>(eeVal);
        }
        //Seconds or Milliseconds
        else if(delayVersion == 3)
        {
            //if the most significant bit is set, the value is in Seconds
            if(Utils::bitIsSet(eeVal, 15))
            {
                //ignore the most significant bit
                Utils::setBit(eeVal, 15, false);

                //if outside the max seconds (10 minutes), defaults to 5ms
                if(eeVal > 600)
                {
                    return static_cast<uint32>(TimeSpan::MilliSeconds(5).getMicroseconds());
                }

                return static_cast<uint32>(TimeSpan::Seconds(eeVal).getMicroseconds());
            }
            else
            {
                //the value is in milliseconds
                return static_cast<uint32>(TimeSpan::MilliSeconds(eeVal).getMicroseconds());
            }
        }
        //Seconds, Milliseconds, or Microseconds
        else if(delayVersion == 4)
        {
            //0b10 - Seconds
            if(Utils::bitIsSet(eeVal, 15))
            {
                //ignore the top 2 bits
                Utils::setBit(eeVal, 15, false);
                Utils::setBit(eeVal, 14, false);

                //max of 10 minutes
                if(eeVal > 600)
                {
                    //defaults back to the max
                    eeVal = 600;
                }

                return static_cast<uint32>(TimeSpan::Seconds(eeVal).getMicroseconds());
            }
            else
            {
                //0b01 - Milliseconds
                if(Utils::bitIsSet(eeVal, 14))
                {
                    //ignore the top 2 bits 
                    Utils::setBit(eeVal, 15, false);
                    Utils::setBit(eeVal, 14, false);

                    return static_cast<uint32>(TimeSpan::MilliSeconds(eeVal).getMicroseconds());
                }
                //0b00 - Microseconds
                else
                {
                    //ignore the top 2 bits
                    Utils::setBit(eeVal, 15, false);
                    Utils::setBit(eeVal, 14, false);

                    return static_cast<uint32>(eeVal);
                }
            }
        }

        assert(false);  //should never happen, need to add a new sensor delay version handler
        throw Error("Unknown Sensor Delay Version!");
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

        //if we need to set the "sync sampling mode"
        if(samplingMode == WirelessTypes::samplingMode_sync ||
           samplingMode == WirelessTypes::samplingMode_syncEvent ||
           samplingMode == WirelessTypes::samplingMode_syncBurst)
        {
            //find the SyncSamplingMode that we need to set (burst or not burst)
            WirelessTypes::SyncSamplingMode syncMode = WirelessTypes::syncMode_continuous;
            if(samplingMode == WirelessTypes::samplingMode_syncBurst)
            {
                syncMode = WirelessTypes::syncMode_burst;
            }

            //write the sync sampling mode 
            write_syncSamplingMode(syncMode);
        }
    }

    WirelessTypes::SamplingMode NodeEepromHelper::read_samplingMode() const
    {
        //read the sampling mode eeprom value
        uint16 samplingModeVal = read(NodeEepromMap::SAMPLING_MODE).as_uint16();

        //if the sampling mode value is not set (uninitialized, legacy nodes)
        if(samplingModeVal == 0 || samplingModeVal == 0xFFFF || samplingModeVal == 0xAAAA)
        {
            if(m_node->features().supportsSamplingMode(WirelessTypes::samplingMode_sync) || 
               m_node->features().supportsSamplingMode(WirelessTypes::samplingMode_syncBurst))
            {
                //need to check if burst is enabled
                WirelessTypes::SyncSamplingMode mode = read_syncSamplingMode();
                if(mode == WirelessTypes::syncMode_burst)
                {
                    //default to burst
                    return WirelessTypes::samplingMode_syncBurst;
                }

                //if any event triggers are enabled
                if(m_node->features().supportsEventTrigger() && (read_eventTriggerMask().enabledCount() != 0))
                {
                    //default to sync + event
                    return WirelessTypes::samplingMode_syncEvent;
                }

                //default to the sync
                return WirelessTypes::samplingMode_sync;
            }
            else if(m_node->features().supportsSamplingMode(WirelessTypes::samplingMode_nonSync))
            {
                //if any event triggers are enabled
                if(m_node->features().supportsEventTrigger() && (read_eventTriggerMask().enabledCount() != 0))
                {
                    //default to non-sync + event
                    return WirelessTypes::samplingMode_nonSyncEvent;
                }

                //default to non-sync
                return WirelessTypes::samplingMode_nonSync;
            }
            else
            {
                //default to armed datalogging
                return WirelessTypes::samplingMode_armedDatalog;
            }
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

    void NodeEepromHelper::read_channelLinearEquation(const ChannelMask& mask, LinearEquation& result) const
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
        WirelessTypes::CalCoef_Unit unitVal = static_cast<WirelessTypes::CalCoef_Unit>(Utils::lsb(actionIdVal));

        //check for uninitialized value
        if(unitVal == 0xAA || unitVal == 0xFF)
        {
            unitVal = WirelessTypes::unit_none;
        }

        return unitVal;
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
        //TODO: this is currently defined as an int16 so that negative dBm values
        //      can be supported in the future. 

        int16 val = read(NodeEepromMap::TX_POWER_LEVEL).as_int16();

        if(m_node->features().supportsNewTransmitPowers())
        {
            return static_cast<WirelessTypes::TransmitPower>(val);
        }
        else
        {
            //legacy value, convert to current value before returning

            //read and return the transmit power level
            return WirelessTypes::legacyToTransmitPower(static_cast<WirelessTypes::LegacyTransmitPower>(val));
        }
    }

    void NodeEepromHelper::write_transmitPower(WirelessTypes::TransmitPower power)
    {
        int16 valToWrite = 0;

        if(m_node->features().supportsNewTransmitPowers())
        {
            valToWrite = static_cast<int16>(power);
        }
        else
        {
            //need to write the legacy value for the device to understand it
            valToWrite = static_cast<int16>(WirelessTypes::transmitPowerToLegacy(power));
        }

        //write the transmit power level to the node
        write(NodeEepromMap::TX_POWER_LEVEL, Value(valueType_int16, valToWrite));
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

        //value stored in eeprom is direct seconds
        if(m_node->features().supportsSleepIntervalSeconds())
        {
            seconds = eeVal;
        }
        else
        {
            if(eeVal != 0)
            {
                seconds = (MAX_SLEEP_INTERVAL_EEVAL / eeVal);
            }
        }

        //if the seconds value is more than 60 seconds
        if(seconds > 60 || seconds == 0)
        {
            //the node defaults to 5 seconds
            seconds = 5;
        }

        return static_cast<uint8>(seconds);
    }

    void NodeEepromHelper::write_checkRadioInterval(uint8 interval)
    {
        uint16 valToWrite;

        //value stored in eeprom is direct seconds
        if(m_node->features().supportsSleepIntervalSeconds())
        {
            valToWrite = interval;
        }
        else
        {
            //calculate the eeprom value to write
            valToWrite = (MAX_SLEEP_INTERVAL_EEVAL / interval);
        }

        //write the value to the node
        write(NodeEepromMap::SLEEP_INTERVAL, Value::UINT16(valToWrite));
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

    WirelessTypes::InputRange NodeEepromHelper::read_inputRange(const ChannelMask& mask) const
    {
        //find the type of the last channel enabled in the mask
        //  TODO: clean this up so that masks can tell you what the type is themselves?
        uint8 lastCh = mask.lastChEnabled();
        WirelessTypes::ChannelType chType = m_node->features().channelType(lastCh);

        //find the eeprom location
        const EepromLocation& eeprom = m_node->features().findEeprom(WirelessTypes::chSetting_inputRange, mask);

        //read the bits value stored in eeprom
        uint16 bitsVal = read(eeprom).as_uint16();

        //convert the bits value to gain and return
        return InputRange::eepromValToInputRange(bitsVal, m_node->model(), chType);
    }

    uint16 NodeEepromHelper::read_hardwareOffset(const ChannelMask& mask) const
    {
        //find the eeprom location
        const EepromLocation& eeprom = m_node->features().findEeprom(WirelessTypes::chSetting_hardwareOffset, mask);

        //return the result read from eeprom
        return read(eeprom).as_uint16();
    }

    void NodeEepromHelper::write_inputRange(const ChannelMask& mask, WirelessTypes::InputRange range)
    {
        //find the type of the last channel enabled in the mask
        //  TODO: clean this up so that masks can tell you what the type is themselves
        uint8 lastCh = mask.lastChEnabled();
        WirelessTypes::ChannelType chType = m_node->features().channelType(lastCh);

        //find the eeprom location
        const EepromLocation& eeprom = m_node->features().findEeprom(WirelessTypes::chSetting_inputRange, mask);

        //convert the gain value to bits, which is what gets written to eeprom
        uint16 bitsVal = InputRange::inputRangeToEepromVal(range, m_node->model(), chType);

        //write the hardware gain (in bits) to eeprom
        write(eeprom, Value::UINT16(bitsVal));
    }

    void NodeEepromHelper::write_hardwareOffset(const ChannelMask& mask, uint16 offset)
    {
        //find the eeprom location
        const EepromLocation& eeprom = m_node->features().findEeprom(WirelessTypes::chSetting_hardwareOffset, mask);

        //write the hardware offset to eeprom
        write(eeprom, Value::UINT16(offset));
    }

    WirelessTypes::Filter NodeEepromHelper::read_antiAliasingFilter(const ChannelMask& mask) const
    {
        //find the eeprom location
        const EepromLocation& eeprom = m_node->features().findEeprom(WirelessTypes::chSetting_antiAliasingFilter, mask);

        //return the result read from eeprom
        return static_cast<WirelessTypes::Filter>(read(eeprom).as_uint16());
    }

    void NodeEepromHelper::write_antiAliasingFilter(const ChannelMask& mask, WirelessTypes::Filter filter)
    {
        //find the eeprom location
        const EepromLocation& eeprom = m_node->features().findEeprom(WirelessTypes::chSetting_antiAliasingFilter, mask);

        //write the filter to eeprom
        write(eeprom, Value::UINT16(static_cast<uint16>(filter)));
    }

    WirelessTypes::Filter NodeEepromHelper::read_lowPassFilter(const ChannelMask& mask) const
    {
        //find the eeprom location
        const EepromLocation& eeprom = m_node->features().findEeprom(WirelessTypes::chSetting_lowPassFilter, mask);

        //return the result read from eeprom
        return static_cast<WirelessTypes::Filter>(read(eeprom).as_uint16());
    }

    void NodeEepromHelper::write_lowPassFilter(const ChannelMask& mask, WirelessTypes::Filter filter)
    {
        //find the eeprom location
        const EepromLocation& eeprom = m_node->features().findEeprom(WirelessTypes::chSetting_lowPassFilter, mask);

        //write the low pass filter to eeprom
        write(eeprom, Value::UINT16(static_cast<uint16>(filter)));
    }

    WirelessTypes::HighPassFilter NodeEepromHelper::read_highPassFilter(const ChannelMask& mask) const
    {
        //find the eeprom location
        const EepromLocation& eeprom = m_node->features().findEeprom(WirelessTypes::chSetting_highPassFilter, mask);

        //return the result read from eeprom
        return static_cast<WirelessTypes::HighPassFilter>(read(eeprom).as_uint16());
    }

    void NodeEepromHelper::write_highPassFilter(const ChannelMask& mask, WirelessTypes::HighPassFilter filter)
    {
        //find the eeprom location
        const EepromLocation& eeprom = m_node->features().findEeprom(WirelessTypes::chSetting_highPassFilter, mask);

        //write the high pass filter to eeprom
        write(eeprom, Value::UINT16(static_cast<uint16>(filter)));
    }

    float NodeEepromHelper::read_gaugeFactor(const ChannelMask& mask) const
    {
        //find the eeprom location
        const EepromLocation& eeprom = m_node->features().findEeprom(WirelessTypes::chSetting_gaugeFactor, mask);

        //read the gauge factor from eeprom
        return read(eeprom).as_float();
    }

    void NodeEepromHelper::write_gaugeFactor(const ChannelMask& mask, float gaugeFactor)
    {
        //find the eeprom location
        const EepromLocation& eeprom = m_node->features().findEeprom(WirelessTypes::chSetting_gaugeFactor, mask);

        //write the gauge factor to eeprom
        write(eeprom, Value::FLOAT(gaugeFactor));
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

    void NodeEepromHelper::read_activitySense(ActivitySense& result) const
    {
        //Enable/Disable
        result.enabled(read(NodeEepromMap::ACT_SENSE_ENABLE).as_bool());

        //Activity Threshold
        result.activityThreshold(read(NodeEepromMap::ACT_SENSE_ACTIVE_THRES).as_float());

        //Inactivity Threshold
        result.inactivityThreshold(read(NodeEepromMap::ACT_SENSE_INACTIVE_THRES).as_float());

        //Activity Time
        result.activityTime(read(NodeEepromMap::ACT_SENSE_ACTIVE_TIME).as_float());

        //Inactivity Timeout
        result.inactivityTimeout(read(NodeEepromMap::ACT_SENSE_INACTIVE_TIMEOUT).as_float());
    }

    void NodeEepromHelper::write_activitySense(const ActivitySense& options)
    {
        //Enable/Disable
        write(NodeEepromMap::ACT_SENSE_ENABLE, Value::UINT16(static_cast<uint16>(options.enabled())));

        //Activity Threshold
        write(NodeEepromMap::ACT_SENSE_ACTIVE_THRES, Value::FLOAT(options.activityThreshold()));

        //Inactivity Threshold
        write(NodeEepromMap::ACT_SENSE_INACTIVE_THRES, Value::FLOAT(options.inactivityThreshold()));

        //Activity Time
        write(NodeEepromMap::ACT_SENSE_ACTIVE_TIME, Value::FLOAT(options.activityTime()));

        //Inactivity Timeout
        write(NodeEepromMap::ACT_SENSE_INACTIVE_TIMEOUT, Value::FLOAT(options.inactivityTimeout()));
    }

    void NodeEepromHelper::read_fatigueOptions(FatigueOptions& result) const
    {
        const NodeFeatures& features = m_node->features();

        uint8 numDamageAngles = features.numDamageAngles();
        uint8 numSnCurveSegments = features.numSnCurveSegments();

        //the legacy SHM-Link has different eeproms for damage angles
        bool hasLegacyAngles = (features.m_nodeInfo.model() == WirelessModels::node_shmLink);

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
        if(features.supportsFatigueDebugModeConfig())
        {
            bool debugModeEnabled = (read(NodeEepromMap::HISTOGRAM_RAW_FLAG).as_uint16() == 1);
            result.debugMode(debugModeEnabled);
        }

        //=============================
        //Damage Angles
        if(hasLegacyAngles)
        {
            if(numDamageAngles >= 1)
            {
                result.damageAngle(0, read(NodeEepromMap::LEGACY_DAMAGE_ANGLE_1).as_float());    //convert uint16 to float
            }

            if(numDamageAngles >= 2)
            {
                result.damageAngle(1, read(NodeEepromMap::LEGACY_DAMAGE_ANGLE_2).as_float());    //covert uint16 to float
            }

            if(numDamageAngles >= 3)
            {
                result.damageAngle(2, read(NodeEepromMap::LEGACY_DAMAGE_ANGLE_3).as_float());    //convert uint16 to float
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

        //=============================
        //Fatigue Mode / Distributed Angle Settings
        if(features.supportsFatigueModeConfig())
        {
            result.fatigueMode(static_cast<WirelessTypes::FatigueMode>(read(NodeEepromMap::FATIGUE_MODE).as_uint16()));
        }

        //=============================
        //Distributed Angle Settings
        if(features.supportsFatigueMode(WirelessTypes::fatigueMode_distributedAngle))
        {
            result.distributedAngleMode_numAngles(read(NodeEepromMap::DIST_ANGLE_NUM_ANGLES).as_uint8());

            result.distributedAngleMode_lowerBound(read(NodeEepromMap::DIST_ANGLE_LOWER_BOUND).as_float());

            result.distributedAngleMode_upperBound(read(NodeEepromMap::DIST_ANGLE_UPPER_BOUND).as_float());
        }
        //=============================

        //Histogram Toggle
        if(features.supportsHistogramEnableConfig())
        {
            result.histogramEnable(read(NodeEepromMap::HISTOGRAM_ENABLE).as_bool());
        }
    }

    void NodeEepromHelper::write_fatigueOptions(const FatigueOptions& options)
    {
        const NodeFeatures& features = m_node->features();

        uint8 numDamageAngles = features.numDamageAngles();
        uint8 numSnCurveSegments = features.numSnCurveSegments();

        //the legacy SHM-Link has different eeproms for damage angles
        bool hasLegacyAngles = (features.m_nodeInfo.model() == WirelessModels::node_shmLink);

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
        if(features.supportsFatigueDebugModeConfig())
        {
            write(NodeEepromMap::HISTOGRAM_RAW_FLAG, Value::UINT16(static_cast<uint16>(options.debugMode())));
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
                write(NodeEepromMap::LEGACY_DAMAGE_ANGLE_1, Value::UINT16(static_cast<uint16>(angle->second)));    //convert float to uint16
            }

            angle = angles.find(1);
            if(numDamageAngles >= 2 && angle != anglesEnd)
            {
                write(NodeEepromMap::LEGACY_DAMAGE_ANGLE_2, Value::UINT16(static_cast<uint16>(angle->second)));    //convert float to uint16
            }

            angle = angles.find(2);
            if(numDamageAngles >= 3 && angle != anglesEnd)
            {
                write(NodeEepromMap::LEGACY_DAMAGE_ANGLE_3, Value::UINT16(static_cast<uint16>(angle->second)));    //convert float to uint16
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

        //=============================
        //Fatigue Mode
        if(features.supportsFatigueModeConfig())
        {
            write(NodeEepromMap::FATIGUE_MODE, Value::UINT16(static_cast<uint16>(options.fatigueMode())));
        }

        //=============================
        //Distributed Angle Settings
        if(features.supportsFatigueMode(WirelessTypes::fatigueMode_distributedAngle))
        {
            write(NodeEepromMap::DIST_ANGLE_NUM_ANGLES, Value::UINT16(static_cast<uint16>(options.distributedAngleMode_numAngles())));

            write(NodeEepromMap::DIST_ANGLE_LOWER_BOUND, Value::FLOAT(options.distributedAngleMode_lowerBound()));

            write(NodeEepromMap::DIST_ANGLE_UPPER_BOUND, Value::FLOAT(options.distributedAngleMode_upperBound()));
        }
        //=============================

        //Histogram Toggle
        if(features.supportsHistogramEnableConfig())
        {
            write(NodeEepromMap::HISTOGRAM_ENABLE, Value::UINT16(static_cast<uint16>(options.histogramEnable())));
        }
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

    BitMask NodeEepromHelper::read_eventTriggerMask() const
    {
        return BitMask(read(NodeEepromMap::EVENT_TRIGGER_MASK).as_uint16());
    }

    void NodeEepromHelper::read_eventTriggerOptions(EventTriggerOptions& result) const
    {
        const uint8 numTriggers = m_node->features().numEventTriggers();

        //Trigger Mask
        BitMask mask(read(NodeEepromMap::EVENT_TRIGGER_MASK).as_uint16());

        uint32 pre;
        uint32 post;

        //Pre and Post Event Duration
        read_eventTriggerDurations(pre, post);

        result.preDuration(pre);
        result.postDuration(post);

        bool usesFloatVal = m_node->features().usesFloatEventTriggerVal();

        EepromLocation channelEeprom = NodeEepromMap::EVENT_SRC_1;
        EepromLocation typeEeprom = NodeEepromMap::EVENT_OPER_1;
        EepromLocation valueEeprom = NodeEepromMap::EVENT_VAL1_1;

        uint8 triggerChannel;
        WirelessTypes::EventTriggerType triggerType;
        float triggerValue;

        for(uint8 i = 0; i < numTriggers; i++)
        {
            //get the eeproms for this trigger
            NodeEepromMap::getEventTriggerEeproms(i, usesFloatVal, channelEeprom, typeEeprom, valueEeprom);

            //build the trigger mask using the one read in above
            result.enableTrigger(i, mask.enabled(i));

            triggerChannel = read(channelEeprom).as_uint8();
            triggerType = static_cast<WirelessTypes::EventTriggerType>(read(typeEeprom).as_uint16());

            if(usesFloatVal)
            {
                triggerValue = read(valueEeprom).as_float();
            }
            else
            {
                //this is a legacy node that sets the Event Trigger value as bits.
                //We need to read it and convert it a floating point value using
                //the linear calibration coefficents that are applied for the specific channel number.
                uint16 triggerValInBits = read(valueEeprom).as_uint16();

                LinearEquation eq(1.0f, 0.0f);

                //find the group that contains the channel for this trigger
                WirelessTypes::ChannelGroupSettings::const_iterator itr;
                ChannelGroups groups = m_node->features().channelGroups();
                for(const auto& group : groups)
                {
                    if(group.hasSetting(WirelessTypes::ChannelGroupSetting::chSetting_linearEquation) && 
                       group.channels().enabled(triggerChannel))
                    {
                        //read the current linear equation set on the Node
                        read_channelLinearEquation(group.channels(), eq);
                        break;
                    }
                }

                //convert from bits to calibrated value
                triggerValue = eq.slope() * triggerValInBits + eq.offset();
            }

            Trigger tempTrigger(triggerChannel, triggerType, triggerValue);

            result.trigger(i, tempTrigger);
        }
    }

    void NodeEepromHelper::write_eventTriggerOptions(const EventTriggerOptions& options, const std::map<uint8, LinearEquation> calibrations)
    {
        const uint8 numTriggers = m_node->features().numEventTriggers();

        uint16 preVal;
        uint16 postVal;

        if(m_node->features().supportsCentisecondEventDuration())
        {
            //value is in 10s of milliseconds
            preVal = static_cast<uint16>(options.preDuration() / 10);
            postVal = static_cast<uint16>(options.postDuration() / 10);
        }
        else
        {
            //value is in seconds
            preVal = static_cast<uint16>(options.preDuration() / 1000);
            postVal = static_cast<uint16>(options.postDuration() / 1000);
        }

        //Pre Event Duration
        write(NodeEepromMap::EVENT_PRE_DURATION, Value::UINT16(preVal));

        //Post Event Duration
        write(NodeEepromMap::EVENT_POST_DURATION, Value::UINT16(postVal));

        bool usesFloatVal = m_node->features().usesFloatEventTriggerVal();

        EepromLocation channelEeprom = NodeEepromMap::EVENT_SRC_1;
        EepromLocation typeEeprom = NodeEepromMap::EVENT_OPER_1;
        EepromLocation valueEeprom = NodeEepromMap::EVENT_VAL1_1;

        BitMask mask;
        Trigger tempTrigger;

        for(uint8 i = 0; i < numTriggers; i++)
        {
            //get the eeproms for this trigger
            NodeEepromMap::getEventTriggerEeproms(i, usesFloatVal, channelEeprom, typeEeprom, valueEeprom);

            //build the trigger mask to write
            mask.enable(i, options.triggerEnabled(i));

            tempTrigger = options.trigger(i);

            //Trigger Channel
            write(channelEeprom, Value::UINT16(tempTrigger.channelNumber()));

            //Trigger Type
            write(typeEeprom, Value::UINT16(static_cast<uint16>(tempTrigger.triggerType())));

            if(usesFloatVal)
            {
                //Trigger Value
                write(valueEeprom, Value::FLOAT(tempTrigger.triggerValue()));
            }
            else
            {
                //convert the value to bits using the provided cal coefficients
                uint16 valInBits = static_cast<uint16>(((tempTrigger.triggerValue() - calibrations.at(i).offset()) / calibrations.at(i).slope()) + 0.5f);

                //Trigger Value
                write(valueEeprom, Value::UINT16(valInBits));
            }
        }

        //Trigger Mask
        write(NodeEepromMap::EVENT_TRIGGER_MASK, Value::UINT16(mask.toMask()));
    }

    void NodeEepromHelper::read_eventTriggerDurations(uint32& pre, uint32& post) const
    {
        //Pre Event Duration
        uint16 preVal = read(NodeEepromMap::EVENT_PRE_DURATION).as_uint16();

        //Post Event Duration
        uint16 postVal = read(NodeEepromMap::EVENT_POST_DURATION).as_uint16();

        if(m_node->features().supportsCentisecondEventDuration())
        {
            //value is in 10s of milliseconds
            pre = static_cast<uint32>(preVal) * 10;
            post = static_cast<uint32>(postVal) * 10;
        }
        else
        {
            //value is in seconds
            pre = static_cast<uint32>(preVal) * 1000;
            post = static_cast<uint32>(postVal) * 1000;
        }
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

    uint16 NodeEepromHelper::read_diagnosticInterval() const
    {
        return read(NodeEepromMap::DIAGNOSTIC_INTERVAL).as_uint16();
    }

    void NodeEepromHelper::write_diagnosticInterval(uint16 seconds)
    {
        write(NodeEepromMap::DIAGNOSTIC_INTERVAL, Value::UINT16(seconds));
    }

    WirelessTypes::StorageLimitMode NodeEepromHelper::read_storageLimitMode() const
    {
        return static_cast<WirelessTypes::StorageLimitMode>(read(NodeEepromMap::STORAGE_LIMIT_MODE).as_uint16());
    }

    void NodeEepromHelper::write_storageLimitMode(WirelessTypes::StorageLimitMode mode)
    {
        write(NodeEepromMap::STORAGE_LIMIT_MODE, Value::UINT16(static_cast<uint16>(mode)));
    }

    DataMode NodeEepromHelper::read_dataMode() const
    {
        if(m_node->features().onlySupportsRawDataMode())
        {
            //return a data mode with just raw mode enabled (read-only-like setting)
            return DataMode(true, false);
        }

        BitMask mask(read(NodeEepromMap::DATA_MODE).as_uint16());
        return DataMode::FromMask(mask);
    }

    void NodeEepromHelper::write_dataMode(const DataMode& dataMode)
    {
        write(NodeEepromMap::DATA_MODE, Value::UINT16(dataMode.toMask().toMask()));
    }

    EepromLocation NodeEepromHelper::findDerivedChannelEeprom(WirelessTypes::DerivedChannel derivedChannel)
    {
        switch(derivedChannel)
        {
            case WirelessTypes::derived_rms:
                return NodeEepromMap::DERIVED_RMS_MASK;

            case WirelessTypes::derived_peakToPeak:
                return NodeEepromMap::DERIVED_P2P_MASK;

            case WirelessTypes::derived_ips:
                return NodeEepromMap::DERIVED_IPS_MASK;

            case WirelessTypes::derived_crestFactor:
                return NodeEepromMap::DERIVED_CREST_FACTOR_MASK;

            default:
                assert(false);  //need to add another derived channel type
                throw Error("Invalid WirelessTypes::DerivedChannel.");
        }
    }

    WirelessTypes::WirelessSampleRate NodeEepromHelper::read_derivedSampleRate() const
    {
        return static_cast<WirelessTypes::WirelessSampleRate>(read(NodeEepromMap::DERIVED_DATA_RATE).as_uint16());
    }

    void NodeEepromHelper::write_derivedSampleRate(WirelessTypes::WirelessSampleRate rate)
    {
        write(NodeEepromMap::DERIVED_DATA_RATE, Value::UINT16(static_cast<uint16>(rate)));
    }

    ChannelMask NodeEepromHelper::read_derivedChannelMask(WirelessTypes::DerivedChannel derivedChannel) const
    {
        const EepromLocation eeprom = findDerivedChannelEeprom(derivedChannel);

        return ChannelMask(read(eeprom).as_uint16());
    }

    void NodeEepromHelper::write_derivedChannelMask(WirelessTypes::DerivedChannel derivedChannel, const ChannelMask& mask)
    {
        const EepromLocation eeprom = findDerivedChannelEeprom(derivedChannel);

        write(eeprom, Value::UINT16(mask.toMask()));
    }
}