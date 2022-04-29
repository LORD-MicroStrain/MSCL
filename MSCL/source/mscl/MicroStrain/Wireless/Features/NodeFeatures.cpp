/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"

#include <functional>
#include <memory>

#include "mscl/Exceptions.h"

#include "NodeFeatures.h"
#include "NodeFeatures_wirelessImpactSensor.h"
#include "NodeFeatures_cfBearingTempLink.h"
#include "NodeFeatures_dvrtlink.h"
#include "NodeFeatures_envlinkMini.h"
#include "NodeFeatures_envlinkPro.h"
#include "NodeFeatures_glink.h"
#include "NodeFeatures_glink2External.h"
#include "NodeFeatures_glink2Internal.h"
#include "NodeFeatures_glink200.h"
#include "NodeFeatures_glink200r.h"
#include "NodeFeatures_iepeLink.h"
#include "NodeFeatures_ptlink200.h"
#include "NodeFeatures_rtdlink.h"
#include "NodeFeatures_rtdlink200.h"
#include "NodeFeatures_sglink.h"
#include "NodeFeatures_sglinkoem.h"
#include "NodeFeatures_sglinkoemHermetic.h"
#include "NodeFeatures_sglinkoemNoXR.h"
#include "NodeFeatures_sglinkMicro.h"
#include "NodeFeatures_sglinkrgd.h"
#include "NodeFeatures_sglink200.h"
#include "NodeFeatures_sglink200oem.h"
#include "NodeFeatures_shmlink.h"
#include "NodeFeatures_shmlink2.h"
#include "NodeFeatures_shmlink200.h"
#include "NodeFeatures_shmlink201.h"
#include "NodeFeatures_shmlink201FullBridge.h"
#include "NodeFeatures_shmlink210.h"
#include "NodeFeatures_tclink1ch.h"
#include "NodeFeatures_tclink200.h"
#include "NodeFeatures_tclink200oem.h"
#include "NodeFeatures_tclink3ch.h"
#include "NodeFeatures_tclink6ch.h"
#include "NodeFeatures_torqueLink.h"
#include "NodeFeatures_torqueLink200.h"
#include "NodeFeatures_torqueLink200_3ch.h"
#include "NodeFeatures_torqueLink200_3ch_s.h"
#include "NodeFeatures_vlink200.h"
#include "NodeFeatures_vlink.h"
#include "NodeFeatures_vlink_legacy.h"

#include "mscl/Utils.h"
#include "AvailableSampleRates.h"
#include "AvailableTransmitPowers.h"
#include "mscl/MicroStrain/Wireless/SyncSamplingFormulas.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"
#include "mscl/MicroStrain/Wireless/Configuration/InputRange.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromHelper.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "mscl/MicroStrain/Wireless/Configuration/WirelessNodeConfig.h"

namespace mscl
{
    NodeFeatures::NodeFeatures(const NodeInfo& info):
        m_nodeInfo(info)
    {
    }

    const Version NodeFeatures::MIN_NODE_FW_PROTOCOL_1_5(10, 33392);
    const Version NodeFeatures::MIN_NODE_FW_PROTOCOL_1_4(10, 31758);
    const Version NodeFeatures::MIN_NODE_FW_PROTOCOL_1_2(10, 0);
    const Version NodeFeatures::MIN_NODE_FW_PROTOCOL_1_1(8, 21);

    const Version NodeFeatures::MIN_BASE_FW_PROTOCOL_1_3(4, 30448);
    const Version NodeFeatures::MIN_BASE_FW_PROTOCOL_1_1(4, 0);

    std::unique_ptr<NodeFeatures> NodeFeatures::create(const NodeInfo& info)
    {
        switch(info.model())
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

        case WirelessModels::node_gLink_200_8g:
        case WirelessModels::node_gLink_200_8g_oem:
        case WirelessModels::node_gLink_200_40g:
        case WirelessModels::node_gLink_200_40g_oem:
        case WirelessModels::node_gLink_200_8g_oem_mmcx:
        case WirelessModels::node_gLink_200_40g_oem_mmcx:
        case WirelessModels::node_gLink_200_8g_oem_u_fl:
        case WirelessModels::node_gLink_200_40g_oem_u_fl:
        case WirelessModels::node_gLink_200_40g_s:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_glink200(info));

        case WirelessModels::node_gLink_200_r:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_glink200r(info));

        case WirelessModels::node_iepeLink:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_iepeLink(info));

        case WirelessModels::node_rtdLink:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_rtdlink(info));

        case WirelessModels::node_rtdLink200:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_rtdlink200(info));

        case WirelessModels::node_sgLink:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_sglink(info));

        case WirelessModels::node_sgLink_oem:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_sglinkoem(info));

        case WirelessModels::node_sgLink_micro:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_sglinkMicro(info));

        case WirelessModels::node_sgLink_herm:
        case WirelessModels::node_sgLink_herm_2600:
        case WirelessModels::node_sgLink_herm_2700:
        case WirelessModels::node_sgLink_herm_2800:
        case WirelessModels::node_sgLink_herm_2900:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_sglinkoemHermetic(info));

        case WirelessModels::node_sgLink_oem_S:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_sglinkoemNoXR(info));

        case WirelessModels::node_sgLink_rgd:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_sglinkrgd(info));

        case WirelessModels::node_sgLink200:
        case WirelessModels::node_sgLink200_hbridge_1K:
        case WirelessModels::node_sgLink200_hbridge_350:
        case WirelessModels::node_sgLink200_hbridge_120:
        case WirelessModels::node_sgLink200_qbridge_1K:
        case WirelessModels::node_sgLink200_qbridge_350:
        case WirelessModels::node_sgLink200_qbridge_120:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_sglink200(info));

        case WirelessModels::node_sgLink200_oem:
        case WirelessModels::node_sgLink200_oem_ufl:
        case WirelessModels::node_sgLink200_oem_hbridge_1K:
        case WirelessModels::node_sgLink200_oem_hbridge_1K_ufl:
        case WirelessModels::node_sgLink200_oem_hbridge_120:
        case WirelessModels::node_sgLink200_oem_hbridge_120_ufl:
        case WirelessModels::node_sgLink200_oem_hbridge_350:
        case WirelessModels::node_sgLink200_oem_hbridge_350_ufl:
        case WirelessModels::node_sgLink200_oem_qbridge_1K:
        case WirelessModels::node_sgLink200_oem_qbridge_1K_ufl:
        case WirelessModels::node_sgLink200_oem_qbridge_120:
        case WirelessModels::node_sgLink200_oem_qbridge_120_ufl:
        case WirelessModels::node_sgLink200_oem_qbridge_350:
        case WirelessModels::node_sgLink200_oem_qbridge_350_ufl:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_sglink200oem(info));

        case WirelessModels::node_ptLink200:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_ptlink200(info));

        case WirelessModels::node_shmLink:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_shmlink(info));

        case WirelessModels::node_shmLink2_cust1_oldNumber:
        case WirelessModels::node_shmLink2_cust1:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_shmlink2(info));

        case WirelessModels::node_shmLink200:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_shmlink200(info));

        case WirelessModels::node_shmLink201:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_shmlink201(info));

        case WirelessModels::node_shmLink201_qbridge_1K:
        case WirelessModels::node_shmLink201_qbridge_348:
        case WirelessModels::node_shmLink201_hbridge_1K:
        case WirelessModels::node_shmLink201_hbridge_348:
        case WirelessModels::node_shmLink201_fullbridge:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_shmlink201FullBridge(info));

        case WirelessModels::node_shmLink210_fullbridge:
        case WirelessModels::node_shmLink210_qbridge_3K:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_shmlink210(info));

        case WirelessModels::node_tcLink_1ch:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_tclink1ch(info));

        case WirelessModels::node_tcLink_3ch:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_tclink3ch(info));

        case WirelessModels::node_tcLink_6ch:
        case WirelessModels::node_tcLink_6ch_ip67:
        case WirelessModels::node_tcLink_6ch_ip67_rht:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_tclink6ch(info));

        case WirelessModels::node_tcLink200:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_tclink200(info));

        case WirelessModels::node_tcLink200_oem:
        case WirelessModels::node_tcLink200_oem_ufl:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_tclink200oem(info));

        case WirelessModels::node_vLink200:
        case WirelessModels::node_vLink200_qbridge_1K:
        case WirelessModels::node_vLink200_qbridge_120:
        case WirelessModels::node_vLink200_qbridge_350:
        case WirelessModels::node_vLink200_hbridge_1K:
        case WirelessModels::node_vLink200_hbridge_120:
        case WirelessModels::node_vLink200_hbridge_350:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_vlink200(info));

        case WirelessModels::node_vLink:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_vlink(info));

        case WirelessModels::node_vLink_legacy:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_vlink_legacy(info));

        case WirelessModels::node_wirelessImpactSensor:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_wirelessImpactSensor(info));

        case WirelessModels::node_cfBearingTempLink:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_cfBearing(info));

        case WirelessModels::node_torqueLink:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_torqueLink(info));

        case WirelessModels::node_torqueLink200_3ch:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_torqueLink200_3ch(info));

        case WirelessModels::node_torqueLink200:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_torqueLink200(info));

        case WirelessModels::node_torqueLink200_3ch_s:
            return std::unique_ptr<NodeFeatures>(new NodeFeatures_torqueLink200_3ch_s(info));

        //TODO: add Watt-Link

        default:
            //we don't know anything about this node, throw an exception
            throw Error_NotSupported("The Node model (" + Utils::toStr(info.model()) + ") is not supported by MSCL.");
        }
    }

    void NodeFeatures::addCalCoeffChannelGroup(uint8 channelNumber, const std::string& name, const EepromLocation& slopeEeprom, const EepromLocation& actionIdEeprom)
    {
        //create the channel mask
        ChannelMask mask;
        mask.enable(channelNumber);

        m_channelGroups.emplace_back(mask, name,
                                     ChannelGroup::SettingsMap{
                                         {WirelessTypes::chSetting_linearEquation, slopeEeprom},
                                         {WirelessTypes::chSetting_unit, actionIdEeprom},
                                         {WirelessTypes::chSetting_equationType, actionIdEeprom}}
        );
    }

    void NodeFeatures::addCalCoeffChannelGroup_withFactoryCal(uint8 channelNumber, const std::string& name, const EepromLocation& slopeEeprom, const EepromLocation& actionIdEeprom, const EepromLocation& factorySlopeEeprom, const EepromLocation& factoryActionIdEeprom)
    {
        //create the channel mask
        ChannelMask mask;
        mask.enable(channelNumber);

        m_channelGroups.emplace_back(mask, name,
            ChannelGroup::SettingsMap{
                { WirelessTypes::chSetting_linearEquation, slopeEeprom },
                { WirelessTypes::chSetting_unit, actionIdEeprom },
                { WirelessTypes::chSetting_equationType, actionIdEeprom },
                { WirelessTypes::chSetting_factoryLinearEq, factorySlopeEeprom },
                { WirelessTypes::chSetting_factoryUnit, factoryActionIdEeprom },
                { WirelessTypes::chSetting_factoryEqType, factoryActionIdEeprom } }
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

    WirelessTypes::WirelessSampleRate NodeFeatures::maxSampleRateForSettlingTime_A(WirelessTypes::SettlingTime settlingTime, const WirelessTypes::WirelessSampleRates& rates)
    {
        //find the max sample rate allowed for the settling time
        SampleRate maxRate;
        if(settlingTime <= WirelessTypes::settling_4ms)
        {
            return rates.at(0);
        }
        else if(settlingTime <= WirelessTypes::settling_8ms)
        {
            maxRate = SampleRate::Hertz(4);
        }
        else if(settlingTime <= WirelessTypes::settling_16ms)
        {
            maxRate = SampleRate::Hertz(2);
        }
        else if(settlingTime <= WirelessTypes::settling_60ms)
        {
            maxRate = SampleRate::Hertz(1);
        }
        else
        {
            maxRate = SampleRate::Seconds(2);
        }

        //even though we found the max rate, that sample rate might not actually be supported by the Node.
        //look through all the supported rates and find the max one supported below the given rate.
        for(const auto& rate : rates)
        {
            if(SampleRate::FromWirelessEepromValue(rate) <= maxRate)
            {
                return rate;
            }
        }

        //should never get to this if this function is used correctly (passed in valid sample rates)
        //and node features are built correctly.
        assert(false);
        return rates.at(rates.size() - 1);
    }

    WirelessTypes::WirelessSampleRate NodeFeatures::maxSampleRateForSettlingTime_B(WirelessTypes::SettlingTime settlingTime, const WirelessTypes::WirelessSampleRates& rates)
    {
        //find the max sample rate allowed for the settling time
        SampleRate maxRate;
        if(settlingTime <= WirelessTypes::settling_4ms)
        {
            return rates.at(0);
        }
        else if(settlingTime <= WirelessTypes::settling_8ms)
        {
            maxRate = SampleRate::Hertz(32);
        }
        else if(settlingTime <= WirelessTypes::settling_16ms)
        {
            maxRate = SampleRate::Hertz(16);
        }
        else if(settlingTime <= WirelessTypes::settling_32ms)
        {
            maxRate = SampleRate::Hertz(8);
        }
        else
        {
            maxRate = SampleRate::Hertz(4);
        }

        //even though we found the max rate, that sample rate might not actually be supported by the Node.
        //look through all the supported rates and find the max one supported below the given rate.
        for(const auto& rate : rates)
        {
            if(SampleRate::FromWirelessEepromValue(rate) <= maxRate)
            {
                return rate;
            }
        }

        //should never get to this if this function is used correctly (passed in valid sample rates)
        //and node features are built correctly.
        assert(false);
        return rates.at(rates.size() - 1);
    }

    uint32 NodeFeatures::normalizeNumSweeps(uint32 sweeps) const
    {
        //make sure it is >= the min value (max requires more information)
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

    uint32 NodeFeatures::ramBufferSize() const
    {
        if(m_nodeInfo.firmwareVersion() >= Version(10, 0))
        {
            return 131072;  // 2^17
        }

        return 262144;  // 2^18
    }

    const WirelessChannels& NodeFeatures::channels() const
    {
        return m_channels;
    }

    ChannelGroups NodeFeatures::channelGroups() const
    {
        return m_channelGroups;
    }

    WirelessTypes::ChannelType NodeFeatures::channelType(uint8 channelNumber) const
    {
        //find the channel number in the list of supported channels
        const auto& chs = channels();
        for(const auto& ch : chs)
        {
            if(ch.channelNumber() == channelNumber)
            {
                return ch.type();
            }
        }

        throw Error_NotSupported("The requested Channel is not supported by this Node");
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

    bool NodeFeatures::supportsInputRange() const
    {
        return anyChannelGroupSupports(WirelessTypes::chSetting_inputRange);
    }

    bool NodeFeatures::supportsInputRangePerExcitationVoltage() const
    {
        return supportsInputRange() && supportsExcitationVoltageConfig();
    }

    bool NodeFeatures::supportsHardwareOffset() const
    {
        return anyChannelGroupSupports(WirelessTypes::chSetting_hardwareOffset);
    }

    bool NodeFeatures::supportsAntiAliasingFilter() const
    {
        return anyChannelGroupSupports(WirelessTypes::chSetting_antiAliasingFilter);
    }

    bool NodeFeatures::supportsLowPassFilter() const
    {
        return anyChannelGroupSupports(WirelessTypes::chSetting_lowPassFilter);
    }

    bool NodeFeatures::supportsHighPassFilter() const
    {
        return anyChannelGroupSupports(WirelessTypes::chSetting_highPassFilter);
    }

    bool NodeFeatures::supportsGaugeFactor() const
    {
        return anyChannelGroupSupports(WirelessTypes::chSetting_gaugeFactor);
    }

    bool NodeFeatures::supportsGaugeResistance() const
    {
        return false;
    }

    bool NodeFeatures::supportsNumActiveGauges() const
    {
        return false;
    }

    bool NodeFeatures::supportsLostBeaconTimeout() const
    {
        //if the node supports sync sampling, it supports lost beacon timeout
        return (supportsSamplingMode(WirelessTypes::samplingMode_sync) ||
                supportsSamplingMode(WirelessTypes::samplingMode_syncBurst) ||
                supportsSamplingMode(WirelessTypes::samplingMode_syncEvent));
    }

    bool NodeFeatures::supportsPullUpResistor() const
    {
        return anyChannelGroupSupports(WirelessTypes::chSetting_pullUpResistor);
    }

    bool NodeFeatures::supportsFilterSettlingTime() const
    {
        return anyChannelGroupSupports(WirelessTypes::chSetting_filterSettlingTime);
    }

    bool NodeFeatures::supportsThermocoupleType() const
    {
        return anyChannelGroupSupports(WirelessTypes::chSetting_thermocoupleType);
    }

    bool NodeFeatures::supportsTempSensorOptions() const
    {
        return anyChannelGroupSupports(WirelessTypes::chSetting_tempSensorOptions);
    }

    bool NodeFeatures::supportsDebounceFilter() const
    {
        return anyChannelGroupSupports(WirelessTypes::chSetting_debounceFilter);
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

    bool NodeFeatures::supportsAutoCal_shm() const
    {
        return false;
    }

    bool NodeFeatures::supportsAutoCal_shm201() const
    {
        return false;
    }

    bool NodeFeatures::supportsAutoShuntCal() const
    {
        return anyChannelGroupSupports(WirelessTypes::chSetting_autoShuntCal);
    }

    bool NodeFeatures::supportsLimitedDuration() const
    {
        return true;
    }

    bool NodeFeatures::supportsEventTrigger() const
    {
        return (supportsSamplingMode(WirelessTypes::samplingMode_nonSyncEvent) ||
                supportsSamplingMode(WirelessTypes::samplingMode_syncEvent));
    }

    bool NodeFeatures::supportsDiagnosticInfo() const
    {
        static const Version MIN_DIAGNOSTIC_SUPPORT(10, 30957);

        return (m_nodeInfo.firmwareVersion() >= MIN_DIAGNOSTIC_SUPPORT);
    }

    bool NodeFeatures::supportsLoggedData() const
    {
        //check if it supports any of the logging methods
        if(supportsDataCollectionMethod(WirelessTypes::collectionMethod_logOnly) ||
           supportsDataCollectionMethod(WirelessTypes::collectionMethod_logAndTransmit) ||
           supportsSamplingMode(WirelessTypes::samplingMode_armedDatalog))
        {
            return true;
        }

        return false;
    }

    bool NodeFeatures::supportsPoll() const
    {
        return false;
    }

    bool NodeFeatures::supportsSensorDelayConfig() const
    {
        return false;
    }

    bool NodeFeatures::supportsSensorDelayAlwaysOn() const
    {
        //most nodes that support sensor delay also support always on
        if(supportsSensorDelayConfig())
        {
            return true;
        }

        return false;
    }

    bool NodeFeatures::supportsSensorOutputMode() const
    {
        return (sensorOutputModes().size() > 0);
    }

    bool NodeFeatures::supportsCfcFilterConfiguration() const
    {
        return (cfcFilters().size() > 0);
    }

    bool NodeFeatures::supportsAutoBalance() const
    {
        return anyChannelGroupSupports(WirelessTypes::chSetting_autoBalance);
    }

    bool NodeFeatures::supportsLegacyShuntCal() const
    {
        return anyChannelGroupSupports(WirelessTypes::chSetting_legacyShuntCal);
    }

    bool NodeFeatures::supportsGetFactoryCal() const
    {
        return anyChannelGroupSupports(WirelessTypes::chSetting_factoryLinearEq) && anyChannelGroupSupports(WirelessTypes::chSetting_factoryUnit);
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
        const WirelessTypes::SamplingModes& supportedModes = samplingModes();

        //return the result of trying to find the sampling mode in the vector
        return (std::find(supportedModes.begin(), supportedModes.end(), samplingMode) != supportedModes.end());
    }

    bool NodeFeatures::supportsSampleRate(WirelessTypes::WirelessSampleRate sampleRate, WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const
    {
        try
        {
            //get the supported sample rates
            const WirelessTypes::WirelessSampleRates& supportedRates = sampleRates(samplingMode, dataCollectionMethod, dataMode);

            //return the result of trying to find the sample rate in the vector
            return (std::find(supportedRates.begin(), supportedRates.end(), sampleRate) != supportedRates.end());
        }
        catch(Error_NotSupported&)
        {
            //the sampling mode is not supported
            return false;
        }
    }

    bool NodeFeatures::supportsCommunicationProtocol(WirelessTypes::CommProtocol protocol) const
    {
        const WirelessTypes::CommProtocols& supportedProtocols = commProtocols();
        return (std::find(supportedProtocols.begin(), supportedProtocols.end(), protocol) != supportedProtocols.end());
    }

    bool NodeFeatures::supportsDataFormat(WirelessTypes::DataFormat dataFormat) const
    {
        //get the supported data formats
        const WirelessTypes::DataFormats& supportedFormats = dataFormats();

        //return the result of trying to find the data format in the vector
        return (std::find(supportedFormats.begin(), supportedFormats.end(), dataFormat) != supportedFormats.end());
    }

    bool NodeFeatures::supportsDefaultMode(WirelessTypes::DefaultMode mode) const
    {
        //get the supported boot modes
        const WirelessTypes::DefaultModes& supportedModes = defaultModes();

        //return the result of trying to find the boot mode in the vector
        return (std::find(supportedModes.begin(), supportedModes.end(), mode) != supportedModes.end());
    }

    bool NodeFeatures::supportsDataCollectionMethod(WirelessTypes::DataCollectionMethod collectionMethod) const
    {
        //get the supported data collection methods
        const WirelessTypes::DataCollectionMethods& supportedMethods = dataCollectionMethods();

        //return the result of trying to find the collection method in the vector
        return (std::find(supportedMethods.begin(), supportedMethods.end(), collectionMethod) != supportedMethods.end());
    }

    bool NodeFeatures::supportsTransmitPower(WirelessTypes::TransmitPower power, WirelessTypes::CommProtocol commProtocol) const
    {
        //get the supported powers
        const WirelessTypes::TransmitPowers& supportedPowers = transmitPowers(commProtocol);

        //return the result of trying to find the power in the vector
        return (std::find(supportedPowers.begin(), supportedPowers.end(), power) != supportedPowers.end());
    }

    bool NodeFeatures::supportsDataMode(WirelessTypes::DataMode dataMode) const
    {
        //get the supported data modes
        const WirelessTypes::DataModes& supportedModes = dataModes();

        //return the result of trying to find the mode in the vector
        return (std::find(supportedModes.begin(), supportedModes.end(), dataMode) != supportedModes.end());
    }

    bool NodeFeatures::supportsTransducerType(WirelessTypes::TransducerType transducerType) const
    {
        const WirelessTypes::TransducerTypes& supportedTypes = transducerTypes();
        return (std::find(supportedTypes.begin(), supportedTypes.end(), transducerType) != supportedTypes.end());
    }

    bool NodeFeatures::supportsFatigueMode(WirelessTypes::FatigueMode mode) const
    {
        //get the supported fatigue modes
        const WirelessTypes::FatigueModes& modes = fatigueModes();

        //result the result of trying to find the mode in the vector
        return (std::find(modes.begin(), modes.end(), mode) != modes.end());
    }

    bool NodeFeatures::supportsInputRange(WirelessTypes::InputRange range, const ChannelMask& channels) const
    {
        const InputRanges& ranges = inputRanges(channels);

        return (std::find_if(ranges.begin(), ranges.end(), [&range](const InputRangeEntry& r)->bool { return r.inputRange == range; }) != ranges.end());
    }

    bool NodeFeatures::supportsInputRange(WirelessTypes::InputRange range, const ChannelMask& channels, WirelessTypes::Voltage excitationVoltage) const
    {
        const InputRanges& ranges = inputRanges(channels, excitationVoltage);

        return (std::find_if(ranges.begin(), ranges.end(), [&range](const InputRangeEntry& r)->bool { return r.inputRange == range; }) != ranges.end());
    }

    bool NodeFeatures::supportsCentisecondEventDuration() const
    {
        static const Version MIN_SUB_SECOND_FW(10, 0);

        return (m_nodeInfo.firmwareVersion() >= MIN_SUB_SECOND_FW);
    }

    bool NodeFeatures::supportsGetDiagnosticInfo() const
    {
        static const Version MIN_GET_DIAG_INFO_FW(10, 33392);

        return (m_nodeInfo.firmwareVersion() >= MIN_GET_DIAG_INFO_FW);
    }

    bool NodeFeatures::supportsNonSyncLogWithTimestamps() const
    {
        if(!supportsDataCollectionMethod(WirelessTypes::collectionMethod_logOnly) &&
           !supportsDataCollectionMethod(WirelessTypes::collectionMethod_logAndTransmit))
        {
            //doesn't support any type of logging, so return false for this
            return false;
        }

        //ASPP v1.5 added support for this
        return (m_nodeInfo.firmwareVersion() >= MIN_NODE_FW_PROTOCOL_1_5);
    }

    bool NodeFeatures::supportsDerivedCategory(WirelessTypes::DerivedCategory category) const
    {
        WirelessTypes::DerivedChannelMasks cats = channelsPerDerivedCategory();

        //return the result of trying to find the math channel in the vector
        return (cats.find(category) != cats.end());
    }

    bool NodeFeatures::supportsRawDataMode() const
    {
        const WirelessTypes::DataModes modes = dataModes();

        //check if any raw mode is available
        if(std::find(modes.begin(), modes.end(), WirelessTypes::dataMode_raw) != modes.end() ||
           std::find(modes.begin(), modes.end(), WirelessTypes::dataMode_raw_derived) != modes.end())
        {
            return true;
        }

        return false;
    }

    bool NodeFeatures::supportsDerivedDataMode() const
    {
        //if any derived channels are avaiable, derived data mode should be available
        return (channelsPerDerivedCategory().size() > 0);
    }

    bool NodeFeatures::supportsDerivedVelocityUnitConfig() const
    {
        return supportsDerivedCategory(WirelessTypes::derivedCategory_velocity) && m_nodeInfo.firmwareVersion() >= Version(12, 41110);
    }

    bool NodeFeatures::supportsExcitationVoltageConfig() const
    {
        return false;
    }

    bool NodeFeatures::supportsLowBatteryThresholdConfig() const
    {
        return false;
    }

    WirelessTypes::WirelessSampleRate NodeFeatures::maxSampleRate(WirelessTypes::SamplingMode samplingMode, const ChannelMask& channels, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const
    {
        //get all the sample rates supported
        WirelessTypes::WirelessSampleRates rates = sampleRates(samplingMode, dataCollectionMethod, dataMode);

        //get the first rate in the sample rates, which should be the fastest
        WirelessTypes::WirelessSampleRate maxRate = rates.front();

        //gen 2 nodes don't have any sample rate limits
        static const Version MIN_GEN_2_NODES(10, 0);
        if(m_nodeInfo.firmwareVersion() >= MIN_GEN_2_NODES)
        {
            return maxRate;
        }

        //4096 is a special case that is only allowed with 1 active channel
        if(channels.count() > 1 && maxRate == WirelessTypes::sampleRate_4096Hz)
        {
            maxRate = *(rates.begin() + 1);
        }

        //return the max sample rate that was found
        return maxRate;
    }

    WirelessTypes::WirelessSampleRate NodeFeatures::maxSampleRateForSettlingTime(WirelessTypes::SettlingTime filterSettlingTime, WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const
    {
        return sampleRates(samplingMode, dataCollectionMethod, dataMode).at(0);
    }

    WirelessTypes::WirelessSampleRate NodeFeatures::maxSampleRateForLowPassFilter(WirelessTypes::Filter lowPassFilter, WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode, const ChannelMask& channels) const
    {
        return sampleRates(samplingMode, dataCollectionMethod, dataMode).at(0);
    }

    WirelessTypes::SettlingTime NodeFeatures::maxFilterSettlingTime(const SampleRate& rate) const
    {
        throw Error_NotSupported("Filter Settling Time is not supported by this Node.");
    }

    uint16 NodeFeatures::minInactivityTimeout() const
    {
        return 30;
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

    uint32 NodeFeatures::maxSweeps(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataMode dataMode, WirelessTypes::DataFormat dataFormat, const ChannelMask& channels) const
    {
        if(!supportsLimitedDuration())
        {
            return 0;
        }

        //if this is burst mode
        if(samplingMode == WirelessTypes::samplingMode_syncBurst)
        {
            //get the max sweeps per burst
            return maxSweepsPerBurst(dataMode, dataFormat, channels);
        }
        else
        {
            return 6553400;
        }
    }

    uint32 NodeFeatures::maxSweepsPerBurst(WirelessTypes::DataMode dataMode, WirelessTypes::DataFormat dataFormat, const ChannelMask& channels) const
    {
        uint32 maxBytes = ramBufferSize();

        //TODO?: bytesPerSample could be reduced to 3 for float when G-Link-200 or V-Link-200 if needed
        uint8 bytesPerSample = WirelessTypes::dataFormatSize(dataFormat);

        uint32 bytesPerSweep = bytesPerSample * static_cast<uint16>(channels.count());

        //don't allow divide by 0
        if(bytesPerSweep == 0)
        {
            bytesPerSweep = 1;
        }

        if(m_nodeInfo.firmwareVersion() >= Version(10, 0))
        {
            DataModeMask mode(dataMode);
            if(mode.rawModeEnabled)
            {
                return static_cast<uint32>((maxBytes - 300) / bytesPerSweep);
            }
            else //if(mode.derivedModeEnabled)
            {
                return 6553400;
            }
        }
        else
        {
            //calculate and return the max number of sweeps per burst
            return static_cast<uint32>(maxBytes / bytesPerSweep);
        }
    }

    TimeSpan NodeFeatures::minTimeBetweenBursts(WirelessTypes::DataMode dataMode,
                                                WirelessTypes::DataFormat dataFormat,
                                                const ChannelMask& rawChannels,
                                                WirelessTypes::DerivedChannelMasks derivedChannelMasks,
                                                const SampleRate& rawSampleRate,
                                                uint32 sweepsPerBurst,
                                                WirelessTypes::CommProtocol commProtocol) const
    {
        uint32 rawBytesPerSweep = 0;
        uint32 derivedBytesPerSweep = 0;

        DataModeMask mode(dataMode);
        if(mode.rawModeEnabled)
        {
            rawBytesPerSweep = WirelessTypes::dataFormatSize(dataFormat) * static_cast<uint16>(rawChannels.count());
        }
        if(mode.derivedModeEnabled)
        {
            derivedBytesPerSweep = WirelessTypes::derivedBytesPerSweep(derivedChannelMasks);
        }

        return SyncSamplingFormulas::minTimeBetweenBursts(rawBytesPerSweep, derivedBytesPerSweep, rawSampleRate, sweepsPerBurst, commProtocol);
    }

    const uint32 NodeFeatures::minSensorDelay() const
    {
        if(!supportsSensorDelayConfig())
        {
            throw Error_NotSupported("Sensor Delay is not supported by this Node.");
        }

        //V1 - Milliseconds
        //V2 - Microseconds
        //V3 - Seconds or Milliseconds
        //V4 - Seconds, Milliseconds, or Microseconds
        switch (sensorDelayVersion())
        {
            case WirelessTypes::delayVersion_v1:
            case WirelessTypes::delayVersion_v3:
                return static_cast<uint32>(TimeSpan::MilliSeconds(1).getMicroseconds());     //1 millisecond

            case WirelessTypes::delayVersion_v2:
            case WirelessTypes::delayVersion_v4:
                return 600;                                                                             //600 microseconds

            default:
                assert(false);  //need to add a case for a new sensor delay version
                throw Error_NotSupported("Unknown Sensor Delay Version");
        }
    }

    const uint32 NodeFeatures::maxSensorDelay() const
    {
        if(!supportsSensorDelayConfig())
        {
            throw Error_NotSupported("Sensor Delay is not supported by this Node.");
        }

        // writing limit of 16 bits (65,535)
        //V1 - Milliseconds
        //V2 - Microseconds
        //V3 - Seconds or Milliseconds
        //V4 - Seconds, Milliseconds, or Microseconds
        switch (sensorDelayVersion())
        {
            case WirelessTypes::delayVersion_v2:
                return 65000;                                                           //65,000 microseconds, max writing limit rounded

            case WirelessTypes::delayVersion_v1:
                return static_cast<uint32>(TimeSpan::Minutes(1).getMicroseconds());     //1 minute, max writing limit rounded (60,000 ms)

            case WirelessTypes::delayVersion_v3:
            case WirelessTypes::delayVersion_v4:
                return static_cast<uint32>(TimeSpan::Minutes(5).getMicroseconds());     //5 minutes

            default:
                assert(false);  //need to add a case for a new sensor delay version
                throw Error_NotSupported("Unknown Sensor Delay Version");
        }
    }

    const uint32 NodeFeatures::defaultSensorDelay() const
    {
        if (!supportsSensorDelayConfig())
        {
            throw Error_NotSupported("Sensor Delay is not supported by this Node.");
        }
        
        return static_cast<uint32>(TimeSpan::MilliSeconds(1).getMicroseconds());    //1 millisecond
    }

    uint32 NodeFeatures::maxEventTriggerTotalDuration(WirelessTypes::DataMode dataMode,
                                                      WirelessTypes::DataFormat dataFormat,
                                                      const ChannelMask& rawChannels,
                                                      WirelessTypes::DerivedChannelMasks derivedChannelMasks,
                                                      const SampleRate& rawSampleRate,
                                                      const SampleRate& derivedDataRate) const
    {
        uint32 ramSize = ramBufferSize();

        //TODO?: bytesPerSample could be reduced to 3 for float when G-Link-200 or V-Link-200 if needed
        uint8 bytesPerSample = WirelessTypes::dataFormatSize(dataFormat);

        uint32 rawBytesPerSweep = bytesPerSample * static_cast<uint16>(rawChannels.count());

        //don't allow divide by 0
        if(rawBytesPerSweep == 0)
        {
            rawBytesPerSweep = 1;
        }

        uint32 mathBytesPerSweep = WirelessTypes::derivedBytesPerSweep(derivedChannelMasks);

        switch(dataMode)
        {
            //Raw Only
            case WirelessTypes::dataMode_raw:
                return static_cast<uint32>((ramSize - 300) / (rawBytesPerSweep * rawSampleRate.samplesPerSecond()) * 1000);

            //Derived Only
            case WirelessTypes::dataMode_derived:
            {
                uint32 mathSweeps = (ramSize - 300) / mathBytesPerSweep;
                return static_cast<uint32>((mathSweeps / derivedDataRate.samplesPerSecond()) * 1000);
            }

            //Raw + Derived
            case WirelessTypes::dataMode_raw_derived:
            {
                double superSweepSize = (1 / derivedDataRate.samplesPerSecond()) * rawBytesPerSweep * rawSampleRate.samplesPerSecond() + 26 + mathBytesPerSweep;
                double superSweepsPerBuffer = (ramSize - 300) / superSweepSize;
                double numSweeps = std::floor(superSweepsPerBuffer * rawSampleRate.samplesPerSecond() / derivedDataRate.samplesPerSecond());
                return static_cast<uint32>(numSweeps / rawSampleRate.samplesPerSecond() * 1000);
            }

            default:
                assert(false);  //Need to add case for new derived type
                return 0;
        }
    }

    uint32 NodeFeatures::normalizeEventDuration(uint32 duration) const
    {
        uint32 result;

        if(supportsCentisecondEventDuration())
        {
            //the duration needs to be in 10s of milliseconds (0.01 seconds), rounding up
            result = static_cast<uint32>(std::ceil(static_cast<float>(duration / 10.0f))) * 10;

            //make sure it is <= the max milliseconds value
            Utils::checkBounds_max(result, static_cast<uint32>(655350));
        }
        else
        {
            //the duration is in seconds
            result = static_cast<uint32>(std::ceil(static_cast<float>(duration / 1000.0f))) * 1000;

            //make sure it is <= the max
            Utils::checkBounds_max(result, static_cast<uint32>(65535000));
        }

        return result;
    }

    uint32 NodeFeatures::normalizeSensorDelay(uint32 delay) const
    {
        if(!supportsSensorDelayConfig())
        {
            throw Error_NotSupported("Sensor Delay is not supported by this Node.");
        }

        if(delay == 0 || delay == WirelessNodeConfig::SENSOR_DELAY_ALWAYS_ON)
        {
            return delay;
        }

        uint32 result = 0;

        //V1 - Milliseconds
        //V2 - Microseconds
        //V3 - Seconds or Milliseconds
        //V4 - Seconds, Milliseconds, or Microseconds
        switch(sensorDelayVersion())
        {
            //milliseconds only
            case WirelessTypes::delayVersion_v1:
                result = static_cast<uint32>(std::ceil(static_cast<float>(delay / 1000.0f))) * 1000;
                break;

            //microseconds only
            case WirelessTypes::delayVersion_v2:
                result = delay;
                break;

            //milliseconds or seconds
            case WirelessTypes::delayVersion_v3:
            {
                //if <= 500 milliseconds then keep as milliseconds
                if(delay <= 500000)
                {
                    //set in milliseconds
                    result = static_cast<uint32>(std::ceil(static_cast<float>(delay / 1000.0f))) * 1000;
                    Utils::checkBounds_min(result, static_cast<uint32>(1000));      //1 millisecond
                    Utils::checkBounds_max(result, static_cast<uint32>(500000));    //500 milliseconds
                }
                //round up to seconds
                else
                {
                    //set in seconds (PWUWU)
                    result = static_cast<uint32>(std::ceil(static_cast<float>(delay / 1000000.0f))) * 1000000;
                    Utils::checkBounds_min(result, static_cast<uint32>(1000000));   //1 second
                }
                break;
            }

            //microseconds, milliseconds, or seconds
            case WirelessTypes::delayVersion_v4:
            {
                //keep the value in microseconds
                if(delay <= 16383)
                {
                    result = delay;
                }
                //round up to milliseconds
                else if(delay <= 16383000)
                {
                    result = static_cast<uint32>(std::ceil(static_cast<float>(delay / 1000.0f))) * 1000;
                }
                //round up to seconds
                else
                {
                    result = static_cast<uint32>(std::ceil(static_cast<float>(delay / 1000000.0f))) * 1000000;
                }
                break;
            }
        }

        //verify the result we calculated is within range
        Utils::checkBounds_min(result, minSensorDelay());
        Utils::checkBounds_max(result, maxSensorDelay());

        return result;
    }

    uint8 NodeFeatures::numDamageAngles() const
    {
        return 0;
    }

    uint8 NodeFeatures::numSnCurveSegments() const
    {
        return 0;
    }

    uint8 NodeFeatures::numEventTriggers() const
    {
        if(!supportsEventTrigger())
        {
            return 0;
        }

        return 8;
    }

    const WirelessTypes::DefaultModes NodeFeatures::defaultModes() const
    {
        //build and return the boot modes that are supported (all for generic)
        WirelessTypes::DefaultModes result;

        result.push_back(WirelessTypes::defaultMode_idle);
        result.push_back(WirelessTypes::defaultMode_sleep);

        if(supportsSamplingMode(WirelessTypes::samplingMode_nonSync) ||
           supportsSamplingMode(WirelessTypes::samplingMode_nonSyncEvent))
        {
            result.push_back(WirelessTypes::defaultMode_ldc);
        }

        if(supportsSamplingMode(WirelessTypes::samplingMode_armedDatalog))
        {
            result.push_back(WirelessTypes::defaultMode_datalog);
        }
        
        if(supportsSamplingMode(WirelessTypes::samplingMode_sync) ||
           supportsSamplingMode(WirelessTypes::samplingMode_syncBurst) ||
           supportsSamplingMode(WirelessTypes::samplingMode_syncEvent))
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

        result.push_back(WirelessTypes::dataFormat_raw_uint16);
        result.push_back(WirelessTypes::dataFormat_cal_float);

        return result;
    }

    const WirelessTypes::SamplingModes NodeFeatures::samplingModes() const
    {
        //build and return the sampling modes that are supported (all but event for generic)
        WirelessTypes::SamplingModes result;

        result.push_back(WirelessTypes::samplingMode_sync);
        result.push_back(WirelessTypes::samplingMode_syncBurst);
        result.push_back(WirelessTypes::samplingMode_nonSync);
        result.push_back(WirelessTypes::samplingMode_armedDatalog);

        return result;
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures::sampleRates(WirelessTypes::SamplingMode samplingMode, WirelessTypes::DataCollectionMethod dataCollectionMethod, WirelessTypes::DataMode dataMode) const
    {
        if(!supportsDataCollectionMethod(dataCollectionMethod))
        {
            throw Error_NotSupported("The data collection method is not supported by this Node");
        }

        if(!supportsDataMode(dataMode))
        {
            throw Error_NotSupported("The data mode is not supported by this Node");
        }

        //derived only has a higher list of rates
        if(dataMode == WirelessTypes::dataMode_derived)
        {
            return AvailableSampleRates::derivedOnly;
        }

        //the list of sample rates varies for each sampling mode
        switch(samplingMode)
        {
        case WirelessTypes::samplingMode_nonSync:
        case WirelessTypes::samplingMode_sync:
        case WirelessTypes::samplingMode_nonSyncEvent:
        case WirelessTypes::samplingMode_syncEvent:
            return AvailableSampleRates::continuous;
        
        case WirelessTypes::samplingMode_syncBurst:
            return AvailableSampleRates::burst;

        case WirelessTypes::samplingMode_armedDatalog:
            return AvailableSampleRates::armedDatalog;

        default:
            throw Error_NotSupported("Invalid SamplingMode");
        }
    }

    const WirelessTypes::WirelessSampleRates NodeFeatures::derivedDataRates() const
    {
        WirelessTypes::WirelessSampleRates derivedRates;

        //as of now, all nodes that support derived have a set list of sample rates
        if(supportsDerivedDataMode())
        {
            derivedRates = {
                {WirelessTypes::sampleRate_1Hz},
                {WirelessTypes::sampleRate_2Sec},
                {WirelessTypes::sampleRate_5Sec},
                {WirelessTypes::sampleRate_10Sec},
                {WirelessTypes::sampleRate_30Sec},
                {WirelessTypes::sampleRate_1Min},
                {WirelessTypes::sampleRate_2Min},
                {WirelessTypes::sampleRate_5Min},
                {WirelessTypes::sampleRate_10Min},
                {WirelessTypes::sampleRate_30Min},
                {WirelessTypes::sampleRate_60Min}
            };
        }

        return derivedRates;
    }

    const WirelessTypes::TransmitPowers NodeFeatures::transmitPowers(WirelessTypes::CommProtocol commProtocol) const
    {
        return AvailableTransmitPowers::get(m_nodeInfo, commProtocol);
    }

    const WirelessTypes::TransmitPowers NodeFeatures::transmitPowers(WirelessTypes::RegionCode region, WirelessTypes::CommProtocol commProtocol) const
    {
        //make a NodeInfo object with all the actual node's info, but with the given region instead
        NodeInfo tempInfo(m_nodeInfo.firmwareVersion(), m_nodeInfo.model(), region);

        return AvailableTransmitPowers::get(tempInfo, commProtocol);
    }

    const WirelessTypes::CommProtocols NodeFeatures::commProtocols() const
    {
        WirelessTypes::CommProtocols result;

        result.push_back(WirelessTypes::commProtocol_lxrs);

        static const Version MIN_LXRS_PLUS_FW(11, 0);
        if(m_nodeInfo.firmwareVersion() >= MIN_LXRS_PLUS_FW)
        {
            result.push_back(WirelessTypes::commProtocol_lxrsPlus);
        }

        return result;
    }

    const WirelessTypes::SensorOutputModes NodeFeatures::sensorOutputModes() const
    {
        WirelessTypes::SensorOutputModes result;
        return result;
    }

    const WirelessTypes::CfcFilters NodeFeatures::cfcFilters() const
    {
        WirelessTypes::CfcFilters result;
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

    const WirelessTypes::Filters NodeFeatures::antiAliasingFilters() const
    {
        //empty by default
        WirelessTypes::Filters result;
        return result;
    }

    const WirelessTypes::Filters NodeFeatures::lowPassFilters() const
    {
        //empty by default
        WirelessTypes::Filters result;
        return result;
    }

    const WirelessTypes::HighPassFilters NodeFeatures::highPassFilters() const
    {
        //empty by default
        WirelessTypes::HighPassFilters result;
        return result;
    }

    const WirelessTypes::StorageLimitModes NodeFeatures::storageLimitModes() const
    {
        WirelessTypes::StorageLimitModes result;

        //don't add any modes if the node doesn't support logged data at all
        if(supportsLoggedData())
        {
            result.push_back(WirelessTypes::storageLimit_stop);
        }

        return result;
    }

    const InputRanges NodeFeatures::inputRanges(const ChannelMask& channels) const
    {
        InputRanges result;

        if(supportsInputRange())
        {
            InputRangeHelper::getRangeVector(m_nodeInfo.model(), channelType(channels.lastChEnabled()), result);
        }

        return result;
    }

    const InputRanges NodeFeatures::inputRanges(const ChannelMask& channels, WirelessTypes::Voltage excitationVoltage) const
    {
        InputRanges result;

        if(supportsInputRange() && supportsExcitationVoltageConfig())
        {
            InputRangeHelper::getRangeVector(m_nodeInfo.model(), channelType(channels.lastChEnabled()), excitationVoltage, result);
        }

        return result;
    }

    const WirelessTypes::DerivedChannelMasks NodeFeatures::channelsPerDerivedCategory() const
    {
        WirelessTypes::DerivedChannelMasks result;
        return result;
    }

    const WirelessTypes::Voltages NodeFeatures::excitationVoltages() const
    {
        WirelessTypes::Voltages result;
        return result;
    }

    const WirelessTypes::VoltageType NodeFeatures::adcVoltageInputType() const
    {
        return WirelessTypes::VoltageType::voltageType_singleEnded;
    }

    WirelessTypes::TransmitPower NodeFeatures::maxTransmitPower(WirelessTypes::RegionCode region, WirelessTypes::CommProtocol commProtocol) const
    {
        //transmit powers are always sorted max to min
        return transmitPowers(region, commProtocol).at(0);
    }

    WirelessTypes::TransmitPower NodeFeatures::maxTransmitPower(WirelessTypes::CommProtocol commProtocol) const
    {
        return maxTransmitPower(m_nodeInfo.regionCode(), commProtocol);
    }

    WirelessTypes::TransmitPower NodeFeatures::minTransmitPower(WirelessTypes::RegionCode region, WirelessTypes::CommProtocol commProtocol) const
    {
        //transmit powers are always sorted max to min
        auto txPowers = transmitPowers(region, commProtocol);
        return txPowers.at(txPowers.size() - 1);
    }

    WirelessTypes::TransmitPower NodeFeatures::minTransmitPower(WirelessTypes::CommProtocol commProtocol) const
    {
        return minTransmitPower(m_nodeInfo.regionCode(), commProtocol);
    }

    const WirelessTypes::DataModes NodeFeatures::dataModes() const
    {
        WirelessTypes::DataModes result;

        //all nodes currently support raw data mode
        result.push_back(WirelessTypes::dataMode_raw);

        if(channelsPerDerivedCategory().size() > 0)
        {
            result.push_back(WirelessTypes::dataMode_derived);

            //all nodes that currently support derived, also support raw + derived
            result.push_back(WirelessTypes::dataMode_raw_derived);
        }

        return result;
    }

    const WirelessTypes::TransducerTypes NodeFeatures::transducerTypes() const
    {
        WirelessTypes::TransducerTypes result;
        return result;
    }

    bool NodeFeatures::supportsNewTransmitPowers() const
    {
        static const Version MIN_NEW_TX_POWER_FW(10, 0);

        return (m_nodeInfo.firmwareVersion() >= MIN_NEW_TX_POWER_FW);
    }

    bool NodeFeatures::hasMaxSampleRatePerFilterAndAdcChCount() const
    {
        return false;
    }

    bool NodeFeatures::supportsAutoBalance2() const
    {
        static const Version MIN_AUTOBALANCE_2_FW(10, 0);

        //if it supports autobalance in general, and has the correct firmware
        if(supportsAutoBalance() &&
           m_nodeInfo.firmwareVersion() >= MIN_AUTOBALANCE_2_FW)
        {
            return true;
        }

        return false;
    }

    bool NodeFeatures::supportsSleepIntervalSeconds() const
    {
        static const Version MIN_SLEEP_INTERVAL_SECONDS_FW(10, 0);

        return (m_nodeInfo.firmwareVersion() >= MIN_SLEEP_INTERVAL_SECONDS_FW);
    }

    bool NodeFeatures::supportsEepromCommitViaRadioReset() const
    {
        static const Version MIN_EEPROM_COMMIT_RADIO_FW(10, 30072);

        return (m_nodeInfo.firmwareVersion() >= MIN_EEPROM_COMMIT_RADIO_FW);
    }

    bool NodeFeatures::supportsFlashId() const
    {
        if(!supportsLoggedData())
        {
            return false;
        }

        static const Version MIN_FLASH_ID_FW(10, 31758);

        return (m_nodeInfo.firmwareVersion() >= MIN_FLASH_ID_FW);
    }

    bool NodeFeatures::supportsStorageLimitModeConfig() const
    {
        if(!supportsLoggedData())
        {
            return false;
        }

        static const Version MIN_STORAGE_LIMIT_FW(10, 31758);

        return (m_nodeInfo.firmwareVersion() >= MIN_STORAGE_LIMIT_FW);
    }

    
    uint8 NodeFeatures::datalogDownloadVersion() const
    {
        static const Version DL_V2(10, 31758);

        if(m_nodeInfo.firmwareVersion() < DL_V2)
        {
            return 1;
        }

        return 2;
    }

    WirelessTypes::DelayVersion NodeFeatures::sensorDelayVersion() const
    {
        //V1 - Milliseconds
        //V2 - Microseconds
        //V3 - Seconds or Milliseconds
        //V4 - Seconds, Milliseconds, or Microseconds

        static const Version V4(10, 31758);

        if (m_nodeInfo.firmwareVersion() >= V4)
        {
            return WirelessTypes::delayVersion_v4;
        }

        switch (m_nodeInfo.model())
        {
            //certain models support Sensor Delay v3 (Seconds or Milliseconds)
            case WirelessModels::node_vLink:
            case WirelessModels::node_iepeLink:
                return WirelessTypes::delayVersion_v3;

            //certain models support Sensor Delay v2 (Microseconds)
            case WirelessModels::node_shmLink:
            case WirelessModels::node_shmLink200:
            case WirelessModels::node_shmLink201:
            case WirelessModels::node_shmLink201_qbridge_1K:
            case WirelessModels::node_shmLink201_qbridge_348:
            case WirelessModels::node_shmLink201_hbridge_1K:
            case WirelessModels::node_shmLink201_hbridge_348:
            case WirelessModels::node_shmLink201_fullbridge:
            case WirelessModels::node_shmLink2_cust1_oldNumber:
            case WirelessModels::node_shmLink2_cust1:
            case WirelessModels::node_sgLink_herm:
            case WirelessModels::node_sgLink_herm_2600:
            case WirelessModels::node_sgLink_herm_2700:
            case WirelessModels::node_sgLink_herm_2800:
            case WirelessModels::node_sgLink_herm_2900:
            case WirelessModels::node_sgLink_rgd:
                return WirelessTypes::delayVersion_v2;

            //everything else supports Sensor Delay v1 (Milliseconds)
            default:
                return WirelessTypes::delayVersion_v1;
        }
    }

    bool NodeFeatures::usesLegacySensorDelayAlwaysOn() const
    {
        //8.20+ supports 0xFFFF as always on, instead of 10,000
        static const Version FFFF_ALWAYS_ON(8, 20);

        if(m_nodeInfo.firmwareVersion() < FFFF_ALWAYS_ON)
        {
            return true;
        }

        return false;
    }

    bool NodeFeatures::usesFloatEventTriggerVal() const
    {
        static const Version FLOAT_EVENT_VAL(10, 31758);

        if(m_nodeInfo.firmwareVersion() >= FLOAT_EVENT_VAL)
        {
            return true;
        }

        return false;
    }

    bool NodeFeatures::onlySupportsRawDataMode() const
    {
        const WirelessTypes::DataModes modes = dataModes();

        if(modes.size() == 1)
        {
            if(modes.at(0) == WirelessTypes::dataMode_raw)
            {
                return true;
            }
        }

        return false;
    }

    bool NodeFeatures::supportsDataModeEeprom() const
    {
        static const Version DATA_MODE_FW(10, 34862);

        return (m_nodeInfo.firmwareVersion() >= DATA_MODE_FW);
    }

    bool NodeFeatures::supportsCommProtocolEeprom() const
    {
        static const Version COMM_PROTOCOL_FW(11, 0);

        return (m_nodeInfo.firmwareVersion() >= COMM_PROTOCOL_FW);
    }

    bool NodeFeatures::supportsEeprom1024AndAbove() const
    {
        static const Version HIGH_EEPROM_FW(10, 0);

        return (m_nodeInfo.firmwareVersion() >= HIGH_EEPROM_FW);
    }
}