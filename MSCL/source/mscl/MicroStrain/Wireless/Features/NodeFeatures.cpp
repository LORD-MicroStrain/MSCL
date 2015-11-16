/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include <functional>
#include <memory>

#include "mscl/Exceptions.h"

#include "NodeFeatures.h"
#include "NodeFeatures_dvrtlink.h"
#include "NodeFeatures_envlinkMini.h"
#include "NodeFeatures_envlinkPro.h"
#include "NodeFeatures_glink.h"
#include "NodeFeatures_glink2External.h"
#include "NodeFeatures_glink2Internal.h"
#include "NodeFeatures_iepeLink.h"
#include "NodeFeatures_mvpervlink.h"
#include "NodeFeatures_rtdlink.h"
#include "NodeFeatures_sglink.h"
#include "NodeFeatures_sglink8ch.h"
#include "NodeFeatures_sglinkoem.h"
#include "NodeFeatures_sglinkoemHermetic.h"
#include "NodeFeatures_sglinkoemNoXR.h"
#include "NodeFeatures_sglinkMicro.h"
#include "NodeFeatures_sglinkrgd.h"
#include "NodeFeatures_shmlink.h"
#include "NodeFeatures_shmlink2.h"
#include "NodeFeatures_tclink1ch.h"
#include "NodeFeatures_tclink3ch.h"
#include "NodeFeatures_tclink6ch.h"
#include "NodeFeatures_vlink.h"
#include "NodeFeatures_vlink_legacy.h"

#include "mscl/Utils.h"
#include "AvailableSampleRates.h"
#include "mscl/MicroStrain/Wireless/SyncSamplingFormulas.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"
#include "mscl/MicroStrain/Wireless/Configuration/HardwareGain.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromHelper.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"

namespace mscl
{
    NodeFeatures::NodeFeatures(const NodeInfo& info):
        m_nodeInfo(info)
    {
    }

    std::unique_ptr<NodeFeatures> NodeFeatures::create(const NodeInfo& info)
    {
        switch(info.model)
        {
        case WirelessModels::node_dvrtLink:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_dvrtlink(info));

        case WirelessModels::node_envLink_mini:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_envlinkMini(info));

        case WirelessModels::node_envLink_pro:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_envlinkPro(info));

        case WirelessModels::node_gLink_2g:
        case WirelessModels::node_gLink_10g:
        case WirelessModels::node_gLink_rgd_10g:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_glink(info));

        case WirelessModels::node_gLinkII_10g_ex:
        case WirelessModels::node_gLinkII_2g_ex:
        case WirelessModels::node_gLinkII_cust_ex:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_glink2External(info));

        case WirelessModels::node_gLinkII_10g_in:
        case WirelessModels::node_gLinkII_2g_in:
        case WirelessModels::node_gLinkII_cust_in:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_glink2Internal(info));

        case WirelessModels::node_iepeLink:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_iepeLink(info));

        case WirelessModels::node_rtdLink:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_rtdlink(info));

        case WirelessModels::node_sgLink:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_sglink(info));

        case WirelessModels::node_sgLink_8ch:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_sglink8ch(info));

        case WirelessModels::node_sgLink_oem:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_sglinkoem(info));

        case WirelessModels::node_sgLink_micro:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_sglinkMicro(info));

        case WirelessModels::node_sgLink_herm:
        case WirelessModels::node_sgLink_herm_2600:
        case WirelessModels::node_sgLink_herm_2700:
        case WirelessModels::node_sgLink_herm_2800:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_sglinkoemHermetic(info));

        case WirelessModels::node_sgLink_oem_S:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_sglinkoemNoXR(info));

        case WirelessModels::node_sgLink_rgd:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_sglinkrgd(info));

        case WirelessModels::node_shmLink:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_shmlink(info));

        case WirelessModels::node_shmLink2:
        case WirelessModels::node_shmLink2_cust1:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_shmlink2(info));

        case WirelessModels::node_tcLink_1ch:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_tclink1ch(info));

        case WirelessModels::node_tcLink_3ch:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_tclink3ch(info));

        case WirelessModels::node_tcLink_6ch:
        case WirelessModels::node_tcLink_6ch_ip67:
        case WirelessModels::node_tcLink_6ch_ip67_rht:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_tclink6ch(info));

        case WirelessModels::node_vLink:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_vlink(info));

        case WirelessModels::node_vLink_legacy:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_vlink_legacy(info));

        case WirelessModels::node_mvPerVLink:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_mvpervlink(info));

        //TODO: add Watt-Link

        default:
            //we don't know anything about this node, throw an exception
            throw Error_NotSupported("The Node model (" + Utils::toStr(info.model) + ") is not supported by MSCL.");
        }
    }

    void NodeFeatures::addCalCoeffChannelGroup(uint8 channelNumber, const EepromLocation& slopeEeprom, const EepromLocation& actionIdEeprom)
    {
        //create the channel mask
        ChannelMask mask;
        mask.enable(channelNumber);

        //create the name
        std::string name = "Channel " + Utils::toStr(channelNumber);

        m_channelGroups.emplace_back(mask, name,
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_linearEquation, slopeEeprom},
                                         {WirelessTypes::chSetting_unit, actionIdEeprom},
                                         {WirelessTypes::chSetting_equationType, actionIdEeprom}}
        );
    }

    WirelessTypes::SettlingTime NodeFeatures::maxFilterSettlingTime_A(const SampleRate& rate)
    {
        if(rate >= SampleRate::Hertz(8))        //8 Hz
        {
            return WirelessTypes::settling_4ms;
        }
        else if(rate >= SampleRate::Hertz(4))    //4 Hz
        {
            return WirelessTypes::settling_8ms;
        }
        else if(rate >= SampleRate::Hertz(2))    //2 Hz
        {
            return WirelessTypes::settling_16ms;
        }
        else if(rate >= SampleRate::Hertz(1))    //1 Hz
        {
            return WirelessTypes::settling_60ms;
        }
        else
        {
            return WirelessTypes::settling_200ms;
        }
    }

    WirelessTypes::SettlingTime NodeFeatures::maxFilterSettlingTime_B(const SampleRate& rate)
    {
        if(rate >= SampleRate::Hertz(64))        //64 Hz
        {
            return WirelessTypes::settling_4ms;
        }
        else if(rate >= SampleRate::Hertz(32))    //32 Hz
        {
            return WirelessTypes::settling_8ms;
        }
        else if(rate >= SampleRate::Hertz(16))    //16 Hz
        {
            return WirelessTypes::settling_16ms;
        }
        else if(rate >= SampleRate::Hertz(8))    //8 Hz
        {
            return WirelessTypes::settling_32ms;
        }
        else
        {
            return WirelessTypes::settling_200ms;
        }
    }

    uint32 NodeFeatures::normalizeNumSweeps(uint32 sweeps) const
    {
        //make sure it is greater than the min value (max requires more information)
        Utils::checkBounds_min(sweeps, minSweeps());

        //the number of sweeps needs to be a multiple of 100
        //this rounds up to multiples of 100, so if the user wanted 505 sweeps, they will get 600. If they wanted 500 sweeps they will get 500.
        return static_cast<uint32>(std::ceil(static_cast<float>(sweeps / 100.0f))) * 100;
    }

    TimeSpan NodeFeatures::normalizeTimeBetweenBursts(const TimeSpan& time) const
    {
        static const TimeSpan MAX_TIME_BETWEEN_BURSTS = TimeSpan::Hours(24);
        static const TimeSpan MIN_TIME_BETWEEN_BURSTS = TimeSpan::Seconds(1);

        TimeSpan result = time;

        //make the TimeSpan be within the bounds
        Utils::checkBounds_min(result, MIN_TIME_BETWEEN_BURSTS);
        Utils::checkBounds_max(result, MAX_TIME_BETWEEN_BURSTS);

        uint64 timeInSeconds = result.getSeconds();

        //if the total seconds in the timespan is more than we can set when using "seconds"
        if(timeInSeconds > NodeEepromHelper::TIME_BETWEEN_BURSTS_MAX_SECS)
        {
            //convert from seconds to minutes (rounding up)
            uint16 timeInMinutes = static_cast<uint16>(std::ceil(static_cast<float>(timeInSeconds / 60.0f)));

            //update the original timespan for reference
            result = TimeSpan::Minutes(timeInMinutes);
        }

        //return the updated TimeSpan
        return result;
    }

    const EepromLocation& NodeFeatures::findEeprom(WirelessTypes::ChannelGroupSetting setting, const ChannelMask& mask) const
    {
        //loop over all of the channel groups
        for(const auto& group : m_channelGroups)
        {
            //if the group has the channel mask we are looking for
            if(group.channels() == mask)
            {
                try
                {
                    return group.getSettingEeprom(setting);
                }
                catch(Error_NotSupported&)
                {
                    //Since a Node can have multiple groups with the same channel mask
                    //some of the groups might not have the given setting.
                    //This catch will skip that group and move to the next group.
                }
            }
        }

        //no option was found that matched the requested id/mask pair
        throw Error_NotSupported("The requested ChannelMask is not supported for this Node.");
    }

    bool NodeFeatures::anyChannelGroupSupports(WirelessTypes::ChannelGroupSetting setting) const
    {
        //loop over all of the groups
        for(const auto& group : m_channelGroups)
        {
            //loop over every setting in the group
            for(const auto& chSetting : group.settings())
            {
                //check if the setting matches the one we are looking for
                if(chSetting == setting)
                {
                    return true;
                }
            }
        }

        return false;
    }

    bool NodeFeatures::anyChannelGroupSupports(WirelessTypes::ChannelGroupSetting setting, uint8 channelNumber) const
    {
        //loop over all of the groups
        for(const auto& group : m_channelGroups)
        {
            //loop over every setting in the group
            for(const auto& chSetting : group.settings())
            {
                //check if the setting matches the one we are looking for
                //and that the channels in the group have the requested channel in it
                if(chSetting == setting && group.channels().enabled(channelNumber))
                {
                    return true;
                }
            }
        }

        return false;
    }

    const WirelessChannels& NodeFeatures::channels() const
    {
        return m_channels;
    }

    ChannelGroups NodeFeatures::channelGroups() const
    {
        return m_channelGroups;
    }

    bool NodeFeatures::supportsChannelSetting(WirelessTypes::ChannelGroupSetting setting, const ChannelMask& mask) const
    {
        try
        {
            //if we can find the eeprom for this setting, it is supported :)
            findEeprom(setting, mask);

            //no exception thrown, the setting is supported
            return true;
        }
        catch(Error_NotSupported&)
        {
            //the setting, or channel mask wasn't supported
            return false;
        }
    }

    bool NodeFeatures::supportsHardwareGain() const
    {
        return anyChannelGroupSupports(WirelessTypes::chSetting_hardwareGain);
    }

    bool NodeFeatures::supportsHardwareOffset() const
    {
        return anyChannelGroupSupports(WirelessTypes::chSetting_hardwareOffset);
    }

    bool NodeFeatures::supportsGaugeFactor() const
    {
        return anyChannelGroupSupports(WirelessTypes::chSetting_gaugeFactor);
    }

    bool NodeFeatures::supportsLostBeaconTimeout() const
    {
        //if the node supports sync sampling, it supports lost beacon timeout
        return (supportsSamplingMode(WirelessTypes::samplingMode_sync) ||
                supportsSamplingMode(WirelessTypes::samplingMode_syncBurst));
    }

    bool NodeFeatures::supportsFilterSettlingTime() const
    {
        return anyChannelGroupSupports(WirelessTypes::chSetting_filterSettlingTime);
    }

    bool NodeFeatures::supportsThermocoupleType() const
    {
        return anyChannelGroupSupports(WirelessTypes::chSetting_thermocoupleType);
    }

    bool NodeFeatures::supportsFatigueConfig() const
    {
        return false;
    }

    bool NodeFeatures::supportsYoungsModConfig() const
    {
        return false;
    }

    bool NodeFeatures::supportsPoissonsRatioConfig() const
    {
        return false;
    }

    bool NodeFeatures::supportsFatigueDebugModeConfig() const
    {
        return false;
    }

    bool NodeFeatures::supportsFatigueModeConfig() const
    {
        return false;
    }

    bool NodeFeatures::supportsHistogramConfig() const
    {
        return false;
    }

    bool NodeFeatures::supportsHistogramRateConfig() const
    {
        return false;
    }

    bool NodeFeatures::supportsHistogramEnableConfig() const
    {
        return false;
    }

    bool NodeFeatures::supportsActivitySense() const
    {
        return false;
    }

    bool NodeFeatures::supportsAutoCal() const
    {
        return false;
    }

    bool NodeFeatures::supportsLimitedDuration() const
    {
        return true;
    }

    bool NodeFeatures::supportsAutoBalance() const
    {
        return anyChannelGroupSupports(WirelessTypes::chSetting_autoBalance);
    }

    bool NodeFeatures::supportsChannel(uint8 channelNumber) const
    {
        //try to find the channel number in the vector of channels
        for(const auto& ch : m_channels)
        {
            if(ch.channelNumber() == channelNumber)
            {
                return true;
            }
        }

        //didn't find the channel
        return false;
    }

    bool NodeFeatures::supportsSamplingMode(WirelessTypes::SamplingMode samplingMode) const
    {
        //get the supported sampling modes
        const WirelessTypes::SamplingModes supportedModes = samplingModes();

        //return the result of trying to find the sampling mode in the vector
        return (std::find(supportedModes.begin(), supportedModes.end(), samplingMode) != supportedModes.end());
    }

    bool NodeFeatures::supportsSampleRate(WirelessTypes::WirelessSampleRate sampleRate, WirelessTypes::SamplingMode samplingMode) const
    {
        try
        {
            //get the supported sample rates
            const WirelessTypes::WirelessSampleRates supportedRates = sampleRates(samplingMode);

            //return the result of trying to find the sample rate in the vector
            return (std::find(supportedRates.begin(), supportedRates.end(), sampleRate) != supportedRates.end());
        }
        catch(Error&)
        {
            //the sampling mode is not supported
            return false;
        }
    }

    bool NodeFeatures::supportsDataFormat(WirelessTypes::DataFormat dataFormat) const
    {
        //get the supported data formats
        const WirelessTypes::DataFormats supportedFormats = dataFormats();

        //return the result of trying to find the data format in the vector
        return (std::find(supportedFormats.begin(), supportedFormats.end(), dataFormat) != supportedFormats.end());
    }

    bool NodeFeatures::supportsDefaultMode(WirelessTypes::DefaultMode mode) const
    {
        //get the supported boot modes
        const WirelessTypes::DefaultModes supportedModes = defaultModes();

        //return the result of trying to find the boot mode in the vector
        return (std::find(supportedModes.begin(), supportedModes.end(), mode) != supportedModes.end());
    }

    bool NodeFeatures::supportsDataCollectionMethod(WirelessTypes::DataCollectionMethod collectionMethod) const
    {
        //get the supported data collection methods
        const WirelessTypes::DataCollectionMethods supportedMethods = dataCollectionMethods();

        //return the result of trying to find the collection method in the vector
        return (std::find(supportedMethods.begin(), supportedMethods.end(), collectionMethod) != supportedMethods.end());
    }

    bool NodeFeatures::supportsTransmitPower(WirelessTypes::TransmitPower power) const
    {
        //get the supported powers
        const WirelessTypes::TransmitPowers supportedPowers = transmitPowers();

        //return the result of trying to find the power in the vector
        return (std::find(supportedPowers.begin(), supportedPowers.end(), power) != supportedPowers.end());
    }

    bool NodeFeatures::supportsFatigueMode(WirelessTypes::FatigueMode mode) const
    {
        //get the supported fatigue modes
        const WirelessTypes::FatigueModes modes = fatigueModes();

        //result the result of trying to find the mode in the vector
        return (std::find(modes.begin(), modes.end(), mode) != modes.end());
    }

    WirelessTypes::WirelessSampleRate NodeFeatures::maxSampleRate(WirelessTypes::SamplingMode samplingMode, const ChannelMask& channels) const
    {
        //get all the sample rates supported
        WirelessTypes::WirelessSampleRates rates = sampleRates(samplingMode);

        //get the first rate in the sample rates, which should be the fastest
        WirelessTypes::WirelessSampleRate maxRate = rates.front();

        //4096 is a special case that is only allowed with 1 active channel
        if(channels.count() > 1 && maxRate == WirelessTypes::sampleRate_4096Hz)
        {
            maxRate = *(rates.begin() + 1);
        }

        //return the max sample rate that was found
        return maxRate;
    }

    WirelessTypes::SettlingTime NodeFeatures::maxFilterSettlingTime(const SampleRate& rate) const
    {
        throw Error_NotSupported("Filter Settling Time is not supported by this Node.");
    }

    uint16 NodeFeatures::minInactivityTimeout() const
    {
        return 5;
    }

    uint16 NodeFeatures::minLostBeaconTimeout() const
    {
        return NodeEepromHelper::MIN_LOST_BEACON_TIMEOUT;
    }

    uint16 NodeFeatures::maxLostBeaconTimeout() const
    {
        return NodeEepromHelper::MAX_LOST_BEACON_TIMEOUT;
    }

    uint8 NodeFeatures::minCheckRadioInterval() const
    {
        return 1;
    }

    uint8 NodeFeatures::maxCheckRadioInterval() const
    {
        return 60;
    }

    uint32 NodeFeatures::minSweeps() const
    {
        if(!supportsLimitedDuration())
        {
            return 0;
        }

        return 100;
    }

    uint32 NodeFeatures::maxSweeps(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataFormat dataFormat, const ChannelMask& channels) const
    {
        if(!supportsLimitedDuration())
        {
            return 0;
        }

        //if this is burst mode
        if(samplingMode == WirelessTypes::samplingMode_syncBurst)
        {
            //get the max sweeps per burst
            return maxSweepsPerBurst(dataFormat, channels);
        }
        else
        {
            //get the max sweeps (total duration)
            return maxSweeps(dataFormat, channels);
        }
    }

    uint32 NodeFeatures::maxSweeps(WirelessTypes::DataFormat dataFormat, const ChannelMask& channels) const
    {
        if(!supportsLimitedDuration())
        {
            return 0;
        }

        //get the max number of bytes this node can store to memory
        uint64 maxBytes = m_nodeInfo.dataStorageSize;

        //get the number of bytes per sample
        uint8 bytesPerSample = WirelessTypes::dataFormatSize(dataFormat);

        //calculate and return the max number of sweeps
        return static_cast<uint32>(maxBytes / (bytesPerSample * static_cast<uint16>(channels.count())));
    }

    uint32 NodeFeatures::maxSweepsPerBurst(WirelessTypes::DataFormat dataFormat, const ChannelMask& channels) const
    {
        //the max number of bytes per burst
        static const uint32 maxBytes = 260000;

        //get the number of bytes per sample
        uint8 bytesPerSample = WirelessTypes::dataFormatSize(dataFormat);

        //calculate and return the max number of sweeps per burst
        return static_cast<uint32>(maxBytes / (bytesPerSample * static_cast<uint16>(channels.count())));
    }

    TimeSpan NodeFeatures::minTimeBetweenBursts(WirelessTypes::DataFormat dataFormat, const ChannelMask& channels, const SampleRate& sampleRate, uint32 sweepsPerBurst) const
    {
        return SyncSamplingFormulas::minTimeBetweenBursts(dataFormat, channels.count(), sampleRate, sweepsPerBurst);
    }

    double NodeFeatures::minHardwareGain() const
    {
        return HardwareGain::minGain(m_nodeInfo.model);
    }

    double NodeFeatures::maxHardwareGain() const
    {
        return HardwareGain::maxGain(m_nodeInfo.model);
    }

    double NodeFeatures::normalizeHardwareGain(double gain) const
    {
        return HardwareGain::normalizeGain(gain, m_nodeInfo.model);
    }

    uint8 NodeFeatures::numDamageAngles() const
    {
        return 0;
    }

    uint8 NodeFeatures::numSnCurveSegments() const
    {
        return 0;
    }

    const WirelessTypes::DefaultModes NodeFeatures::defaultModes() const
    {
        //build and return the boot modes that are supported (all for generic)
        WirelessTypes::DefaultModes result;

        result.push_back(WirelessTypes::defaultMode_idle);
        result.push_back(WirelessTypes::defaultMode_sleep);

        if(supportsSamplingMode(WirelessTypes::samplingMode_nonSync))
        {
            result.push_back(WirelessTypes::defaultMode_ldc);
        }

        if(supportsSamplingMode(WirelessTypes::samplingMode_armedDatalog))
        {
            result.push_back(WirelessTypes::defaultMode_datalog);
        }
        
        if(supportsSamplingMode(WirelessTypes::samplingMode_sync) ||
           supportsSamplingMode(WirelessTypes::samplingMode_syncBurst))
        {
            result.push_back(WirelessTypes::defaultMode_sync);
        }

        return result;
    }

    const WirelessTypes::DataCollectionMethods NodeFeatures::dataCollectionMethods() const
    {
        //build and return the data collection methods that are supported (all for generic)
        WirelessTypes::DataCollectionMethods result;

        result.push_back(WirelessTypes::collectionMethod_logOnly);
        result.push_back(WirelessTypes::collectionMethod_transmitOnly);
        result.push_back(WirelessTypes::collectionMethod_logAndTransmit);

        return result;
    }
    
    const WirelessTypes::DataFormats NodeFeatures::dataFormats() const
    {
        //build and return the data formats that are supported (all for generic)
        WirelessTypes::DataFormats result;

        result.push_back(WirelessTypes::dataFormat_2byte_uint);
        result.push_back(WirelessTypes::dataFormat_4byte_float);

        return result;
    }

    const WirelessTypes::SamplingModes NodeFeatures::samplingModes() const
    {
        //build and return the sampling modes that are supported (all for generic)
        WirelessTypes::SamplingModes result;

        result.push_back(WirelessTypes::samplingMode_sync);
        result.push_back(WirelessTypes::samplingMode_syncBurst);
        result.push_back(WirelessTypes::samplingMode_nonSync);
        result.push_back(WirelessTypes::samplingMode_armedDatalog);

        return result;
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures::sampleRates(WirelessTypes::SamplingMode samplingMode) const
    {
        //the list of sample rates varies for each sampling mode
        switch(samplingMode)
        {
        case WirelessTypes::samplingMode_nonSync:
        case WirelessTypes::samplingMode_sync:
            return AvailableSampleRates::continuous;
        
        case WirelessTypes::samplingMode_syncBurst:
            return AvailableSampleRates::burst;

        case WirelessTypes::samplingMode_armedDatalog:
            return AvailableSampleRates::armedDatalog;

        default:
            throw Error("Invalid SamplingMode");
        }
    }

    const WirelessTypes::TransmitPowers NodeFeatures::transmitPowers() const
    {
        WirelessTypes::TransmitPowers result;

        //find the max transmit power for the node's region code
        WirelessTypes::TransmitPower maxPower = WirelessTypes::maxTransmitPower(m_nodeInfo.regionCode);

        //add the power levels based on the max power we determined above
        if(maxPower >= WirelessTypes::power_20dBm && supportsNewTransmitPowers())
        {
            result.push_back(WirelessTypes::power_20dBm);
        }

        if(maxPower >= WirelessTypes::power_16dBm)
        {
            result.push_back(WirelessTypes::power_16dBm);
        }

        if(maxPower >= WirelessTypes::power_10dBm)
        {
            result.push_back(WirelessTypes::power_10dBm);
        }

        if(maxPower >= WirelessTypes::power_5dBm)
        {
            result.push_back(WirelessTypes::power_5dBm);
        }

        if(maxPower >= WirelessTypes::power_0dBm)
        {
            result.push_back(WirelessTypes::power_0dBm);
        }

        return result;
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures::histogramTransmitRates() const
    {
        //empty by default
        WirelessTypes::WirelessSampleRates result;
        return result;
    }

    const WirelessTypes::FatigueModes NodeFeatures::fatigueModes() const
    {
        //empty by default
        WirelessTypes::FatigueModes result;
        return result;
    }

    bool NodeFeatures::supportsNewTransmitPowers() const
    {
        static const Version MIN_NEW_TX_POWER_FW(10, 0);

        return (m_nodeInfo.firmwareVersion >= MIN_NEW_TX_POWER_FW);
    }

    bool NodeFeatures::supportsAutoBalance2() const
    {
        static const Version MIN_AUTOBALANCE_2_FW(10, 0);

        //if it supports autobalance in general, and has the correct firmware
        if(supportsAutoBalance() &&
           m_nodeInfo.firmwareVersion >= MIN_AUTOBALANCE_2_FW)
        {
            return true;
        }

        return false;
    }
}