/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/WirelessNode_Impl.h"

#include "mscl/MicroStrain/Wireless/Commands/AutoCal.h"
#include "mscl/MicroStrain/Wireless/Commands/DatalogSessionInfoResult.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "mscl/MicroStrain/Wireless/Configuration/WirelessNodeConfig.h"
#include "mscl/MicroStrain/Wireless/Features/NodeInfo.h"
#include "mscl/MicroStrain/Wireless/NodeCommTimes.h"
#include "mscl/MicroStrain/Wireless/NodeMemory_v1.h"
#include "mscl/ScopeHelper.h"

namespace mscl
{
    WirelessNode_Impl::WirelessNode_Impl(NodeAddress nodeAddress, const BaseStation& basestation) :
        m_address(nodeAddress),
        m_baseStation(basestation),
        m_eepromHelper(new NodeEepromHelper(this))
    {}

    void WirelessNode_Impl::determineProtocols() const
    {
        Version asppVersion_lxrs;
        Version asppVersion_lxrsPlus;

        //we don't want to use retries when determining protocol
        NodeEepromSettings tempSettings = m_eepromSettings;
        tempSettings.numRetries = 0;
        tempSettings.useGroupRead = false;

        rec_mutex_lock_guard lock(m_protocolMutex);

        //=========================================================================
        // Determine the firmware version by attempting to use multiple protocols
        try
        {
            //try reading with protocol v1.1 (has read eeprom v2)
            m_protocol_lxrs = WirelessProtocol::v1_1();
            m_protocol_lxrsPlus = WirelessProtocol::v1_1();

            eeprom().updateSettings(tempSettings);

            asppVersion_lxrs = m_eepromHelper->read_asppVersion(WirelessTypes::commProtocol_lxrs);
            asppVersion_lxrsPlus = m_eepromHelper->read_asppVersion(WirelessTypes::commProtocol_lxrsPlus);
        }
        catch(Error_Communication&)
        {
            //Failed reading with protocol v1.1 - Now try v1.0 (has read eeprom v1)

            try
            {
                //try reading with protocol v1.0
                m_protocol_lxrs = WirelessProtocol::v1_0();
                m_protocol_lxrsPlus = WirelessProtocol::v1_0();

                asppVersion_lxrs = m_eepromHelper->read_asppVersion(WirelessTypes::commProtocol_lxrs);
                asppVersion_lxrsPlus = m_eepromHelper->read_asppVersion(WirelessTypes::commProtocol_lxrsPlus);
            }
            catch(Error_Communication&)
            {
                //we failed to determine the protocol
                //need to clear out the protocol and eeprom variables
                m_protocol_lxrs.reset();
                m_protocol_lxrsPlus.reset();

                //set back the original eeprom settings
                eeprom().updateSettings(m_eepromSettings);

                //rethrow the exception
                throw;
            }
        }
        //=========================================================================

        //set back the original eeprom settings
        eeprom().updateSettings(m_eepromSettings);

        m_protocol_lxrs = WirelessProtocol::getProtocol(asppVersion_lxrs);
        m_protocol_lxrsPlus = WirelessProtocol::getProtocol(asppVersion_lxrsPlus);
    }

    NodeEeprom& WirelessNode_Impl::eeprom() const
    {
        rec_mutex_lock_guard lock(m_protocolMutex);

        //if the eeprom variable hasn't been set yet
        if(m_eeprom == nullptr)
        {
            //create the eeprom variable
            m_eeprom.reset(new NodeEeprom(this, m_baseStation, m_eepromSettings));
        }

        return *m_eeprom.get();
    }

    const WirelessProtocol& WirelessNode_Impl::wirelessProtocol()
    {
        //use the BaseStation's current comm protocol setting as we always will talk
        //to the Node using whatever the BaseStation's protocol is set to.
        return protocol(m_baseStation.communicationProtocol());
    }

    NodeEepromHelper& WirelessNode_Impl::eeHelper() const
    {
        return *m_eepromHelper.get();
    }

    const NodeFeatures& WirelessNode_Impl::features() const
    {
        //if the features variable hasn't been set yet
        if(m_features == nullptr)
        {
            //create the NodeInfo to give to the features
            NodeInfo info(this);

            //set the features variable by creating a new NodeFeatures pointer
            m_features = NodeFeatures::create(info);
        }

        return *m_features.get();
    }

    const WirelessProtocol& WirelessNode_Impl::protocol(WirelessTypes::CommProtocol commProtocol) const
    {
        rec_mutex_lock_guard lock(m_protocolMutex);

        //if the protocol variable hasn't been set yet
        if(m_protocol_lxrs == nullptr || m_protocol_lxrsPlus == nullptr)
        {
            //determine and assign the protocols for this Node
            determineProtocols();

            //protocol was updated so set m_eeprom as well
            //m_eeprom.reset(new NodeEeprom(this, m_baseStation, m_eepromSettings));
        }

        switch(commProtocol)
        {
            case WirelessTypes::commProtocol_lxrsPlus:
                return *m_protocol_lxrsPlus.get();

            case WirelessTypes::commProtocol_lxrs:
                return *m_protocol_lxrs.get();

            default:
                throw Error("Invalid RadioMode");
        }
    }

    const Timestamp& WirelessNode_Impl::lastCommunicationTime() const
    {
        return NodeCommTimes::getLastCommTime(m_address);
    }

    DeviceState WirelessNode_Impl::lastDeviceState() const
    {
        return NodeCommTimes::getLastDeviceState(m_address);
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

        rec_mutex_lock_guard lock(m_protocolMutex);

        if(m_eeprom != nullptr)
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
        return basestation == m_baseStation;
    }

    void WirelessNode_Impl::useGroupRead(bool useGroup)
    {
        //will be cached for later in case m_eeprom is null
        m_eepromSettings.useGroupRead = useGroup;

        rec_mutex_lock_guard lock(m_protocolMutex);

        if(m_eeprom != nullptr)
        {
            eeprom().updateSettings(m_eepromSettings);
        }
    }

    void WirelessNode_Impl::setReadWriteRetries(uint8 numRetries)
    {
        //will be cached for later in case m_eeprom is null
        m_eepromSettings.numRetries = numRetries;

        rec_mutex_lock_guard lock(m_protocolMutex);

        if(m_eeprom != nullptr)
        {
            eeprom().updateSettings(m_eepromSettings);
        }
    }

    uint8 WirelessNode_Impl::getReadWriteRetries() const
    {
        return m_eepromSettings.numRetries;
    }

    void WirelessNode_Impl::useEepromCache(bool useCache)
    {
        //will be cached for later in case m_eeprom is null
        m_eepromSettings.useEepromCache = useCache;

        rec_mutex_lock_guard lock(m_protocolMutex);

        if(m_eeprom != nullptr)
        {
            eeprom().updateSettings(m_eepromSettings);
        }
    }

    void WirelessNode_Impl::clearEepromCache()
    {
        rec_mutex_lock_guard lock(m_protocolMutex);

        //don't need to clear anything if it doesn't exist
        if(m_eeprom != nullptr)
        {
            m_eeprom->clearCache();
        }

        //features may need to be reset if firmware version or model changed
        if(m_features != nullptr)
        {
            m_features.reset();
        }

        //protocols may need to be reset if ASPP of firmware version changed
        if(m_protocol_lxrs != nullptr)
        {
            m_protocol_lxrs.reset();
        }
        if(m_protocol_lxrsPlus != nullptr)
        {
            m_protocol_lxrsPlus.reset();
        }
    }

    void WirelessNode_Impl::clearEepromCacheLocation(uint16 location)
    {
        if(m_eeprom != nullptr)
        {
            m_eeprom->clearCacheLocation(location);
        }
    }

    void WirelessNode_Impl::updateEepromCacheFromNodeDiscovery(const NodeDiscovery& nodeDiscovery)
    {
        //import the Node Discovery eeprom map
        eeprom().importCache(nodeDiscovery.eepromMap());

        //features may need to be reset if firmware version or model changed
        if(m_features != nullptr)
        {
            m_features.reset();
        }

        rec_mutex_lock_guard lock(m_protocolMutex);
        //protocols may need to be reset if ASPP of firmware version changed
        if(m_protocol_lxrs != nullptr)
        {
            m_protocol_lxrs.reset();
        }
        if(m_protocol_lxrsPlus != nullptr)
        {
            m_protocol_lxrsPlus.reset();
        }
    }

    WirelessTypes::EepromMap WirelessNode_Impl::getEepromCache() const
    {
        return eeprom().getCache();
    }

    NodeAddress WirelessNode_Impl::nodeAddress() const
    {
        return m_address;
    }

    WirelessTypes::Frequency WirelessNode_Impl::frequency() const
    {
        return m_eepromHelper->read_frequency();
    }

    WirelessTypes::CommProtocol WirelessNode_Impl::communicationProtocol() const
    {
        return m_eepromHelper->read_commProtocol();
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
        //reset the hasWritten flag so that we can tell if
        //eeproms were actually changed (and not ignored due to the cache).
        eeprom().resetHasWritten();

        config.apply(features(), eeHelper());

        //if an actual eeprom has been written
        if(eeprom().didWrite())
        {
            //if the apply succeeded, we need to cycle the power
            //for some eeproms to actually take the changes
            m_eepromHelper->applyEepromChanges();
        }
    }

    uint16 WirelessNode_Impl::getNumDatalogSessions()
    {
        if(features().datalogDownloadVersion() == 1)
        {
            return m_eepromHelper->read_numDatalogSessions();
        }

        //datalog v2+ doesn't support the num datalog sessions eeprom

        //use the getDatalogSessionInfo command to obtain this information
        DatalogSessionInfoResult info;
        if(!m_baseStation.node_getDatalogSessionInfo(wirelessProtocol(), m_address, info))
        {
            throw Error_NodeCommunication(nodeAddress(), "Failed to get the Datalogging Session Info");
        }

        return info.sessionCount;
    }

    float WirelessNode_Impl::percentFull()
    {
        uint32 numBytesLogged = 0;
        uint64 dataStorageSize = m_eepromHelper->read_dataStorageSize();

        if(dataStorageSize == 0)
        {
            return 0.0f;
        }

        if(features().datalogDownloadVersion() == 1)
        {
            numBytesLogged = NodeMemory_v1::calcTotalBytes(m_eepromHelper->read_logPage(), m_eepromHelper->read_logPageOffset());
        }
        else
        {
            //use the getDatalogSessionInfo command to obtain this information
            DatalogSessionInfoResult info;
            if(!m_baseStation.node_getDatalogSessionInfo(wirelessProtocol(), m_address, info))
            {
                throw Error_NodeCommunication(nodeAddress(), "Failed to get the Datalogging Session Info");
            }

            numBytesLogged = info.maxLoggedBytes;
        }

        float result = static_cast<float>(numBytesLogged) / static_cast<float>(dataStorageSize) * 100.0f;

        //make sure it is within 0 to 100 %
        Utils::checkBounds_min(result, 0.0f);
        Utils::checkBounds_max(result, 100.0f);

        return result;
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
            throw Error_NotSupported("The Number of Sweeps is not supported by this Node.");
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

    bool WirelessNode_Impl::getPullUpResistor(const ChannelMask& mask) const
    {
        return m_eepromHelper->read_pullUpResistor(mask);
    }

    WirelessTypes::SensorOutputMode WirelessNode_Impl::getSensorOutputMode() const
    {
        return m_eepromHelper->read_sensorMode();
    }

    WirelessTypes::InputRange WirelessNode_Impl::getInputRange(const ChannelMask& mask) const
    {
        return m_eepromHelper->read_inputRange(mask);
    }

    uint16 WirelessNode_Impl::getHardwareOffset(const ChannelMask& mask) const
    {
        return m_eepromHelper->read_hardwareOffset(mask);
    }

    WirelessTypes::Filter WirelessNode_Impl::getAntiAliasingFilter(const ChannelMask& mask) const
    {
        return m_eepromHelper->read_antiAliasingFilter(mask);
    }

    WirelessTypes::Filter WirelessNode_Impl::getLowPassFilter(const ChannelMask& mask) const
    {
        return m_eepromHelper->read_lowPassFilter(mask);
    }

    WirelessTypes::HighPassFilter WirelessNode_Impl::getHighPassFilter(const ChannelMask& mask) const
    {
        return m_eepromHelper->read_highPassFilter(mask);
    }

    WirelessTypes::ChannelFrequencyClass WirelessNode_Impl::getCfcFilterConfiguration() const
    {
        return m_eepromHelper->read_cfcFilterConfig();
    }

    uint16 WirelessNode_Impl::getDebounceFilter(const ChannelMask& mask) const
    {
        return m_eepromHelper->read_debounceFilter(mask);
    }

    float WirelessNode_Impl::getGaugeFactor(const ChannelMask& mask) const
    {
        return m_eepromHelper->read_gaugeFactor(mask);
    }

    WirelessTypes::Voltage WirelessNode_Impl::getExcitationVoltage() const
    {
        //if this is in eeprom
        if(features().supportsExcitationVoltageConfig())
        {
            return m_eepromHelper->read_excitationVoltage();
        }

        //not in eeprom, use a lookup table
        switch(model())
        {
            case WirelessModels::node_vLink200:
            case WirelessModels::node_vLink200_hbridge_120:
            case WirelessModels::node_vLink200_hbridge_1K:
            case WirelessModels::node_vLink200_hbridge_350:
            case WirelessModels::node_vLink200_qbridge_120:
            case WirelessModels::node_vLink200_qbridge_1K:
            case WirelessModels::node_vLink200_qbridge_350:
                return WirelessTypes::voltage_4096mV;

            case WirelessModels::node_dvrtLink:
            case WirelessModels::node_sgLink:
            case WirelessModels::node_sgLink_oem:
            case WirelessModels::node_sgLink_oem_S:
            case WirelessModels::node_sgLink_rgd:
            case WirelessModels::node_sgLink_micro:
            case WirelessModels::node_vLink:
            case WirelessModels::node_vLink_legacy:
                return WirelessTypes::voltage_3000mV;

            case WirelessModels::node_sgLink_herm:
            case WirelessModels::node_sgLink_herm_2600:
            case WirelessModels::node_sgLink_herm_2700:
            case WirelessModels::node_sgLink_herm_2800:
            case WirelessModels::node_sgLink_herm_2900:
                return WirelessTypes::voltage_2800mV;

            case WirelessModels::node_shmLink:
            case WirelessModels::node_torqueLink:
                return WirelessTypes::voltage_2700mV;

            case WirelessModels::node_ptLink200:
            case WirelessModels::node_shmLink201:
            case WirelessModels::node_shmLink201_qbridge_1K:
            case WirelessModels::node_shmLink201_qbridge_348:
            case WirelessModels::node_shmLink201_hbridge_1K:
            case WirelessModels::node_shmLink201_hbridge_348:
            case WirelessModels::node_shmLink201_fullbridge:
            case WirelessModels::node_shmLink210_fullbridge:
            case WirelessModels::node_shmLink210_qbridge_3K:
            case WirelessModels::node_torqueLink200_3ch_s:
                return WirelessTypes::voltage_2500mV;

            case WirelessModels::node_sgLink200:
            case WirelessModels::node_sgLink200_hbridge_1K:
            case WirelessModels::node_sgLink200_hbridge_350:
            case WirelessModels::node_sgLink200_hbridge_120:
            case WirelessModels::node_sgLink200_qbridge_1K:
            case WirelessModels::node_sgLink200_qbridge_350:
            case WirelessModels::node_sgLink200_qbridge_120:
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
            case WirelessModels::node_torqueLink200:
            case WirelessModels::node_torqueLink200_3ch:
                assert(false);
                throw Error("This Node should read Excitation Voltage from EEPROM!");

            default:
                throw Error_NotSupported("Unknown Excitation voltage for this Node.");
        }

    }

    WirelessTypes::Voltage WirelessNode_Impl::getAdcVoltageRef() const
    {
        switch(model())
        {
            case WirelessModels::node_vLink200:
            case WirelessModels::node_vLink200_hbridge_120:
            case WirelessModels::node_vLink200_hbridge_1K:
            case WirelessModels::node_vLink200_hbridge_350:
            case WirelessModels::node_vLink200_qbridge_120:
            case WirelessModels::node_vLink200_qbridge_1K:
            case WirelessModels::node_vLink200_qbridge_350:
                return WirelessTypes::voltage_5120mV;

            case WirelessModels::node_dvrtLink:
            case WirelessModels::node_sgLink:
            case WirelessModels::node_sgLink_oem:
            case WirelessModels::node_sgLink_oem_S:
            case WirelessModels::node_sgLink_rgd:
            case WirelessModels::node_sgLink_micro:
            case WirelessModels::node_vLink:
            case WirelessModels::node_vLink_legacy:
                return WirelessTypes::voltage_3000mV;

            case WirelessModels::node_sgLink_herm:
            case WirelessModels::node_sgLink_herm_2600:
            case WirelessModels::node_sgLink_herm_2700:
            case WirelessModels::node_sgLink_herm_2800:
            case WirelessModels::node_sgLink_herm_2900:
                return WirelessTypes::voltage_2800mV;

            case WirelessModels::node_iepeLink:
                return WirelessTypes::voltage_2750mV;

            case WirelessModels::node_shmLink:
            case WirelessModels::node_torqueLink:
                return WirelessTypes::voltage_2700mV;

            case WirelessModels::node_sgLink200:
            case WirelessModels::node_sgLink200_hbridge_1K:
            case WirelessModels::node_sgLink200_hbridge_350:
            case WirelessModels::node_sgLink200_hbridge_120:
            case WirelessModels::node_sgLink200_qbridge_1K:
            case WirelessModels::node_sgLink200_qbridge_350:
            case WirelessModels::node_sgLink200_qbridge_120:
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
            case WirelessModels::node_torqueLink200:
            case WirelessModels::node_torqueLink200_3ch:
            case WirelessModels::node_shmLink210_fullbridge:
            case WirelessModels::node_shmLink210_qbridge_3K:
                return m_eepromHelper->read_excitationVoltage();        //gain amplifier voltage is the same as the excitation, which is read from eeprom

            case WirelessModels::node_ptLink200:
            case WirelessModels::node_shmLink201:
            case WirelessModels::node_shmLink201_qbridge_1K:
            case WirelessModels::node_shmLink201_qbridge_348:
            case WirelessModels::node_shmLink201_hbridge_1K:
            case WirelessModels::node_shmLink201_hbridge_348:
            case WirelessModels::node_shmLink201_fullbridge:
            case WirelessModels::node_torqueLink200_3ch_s:
                return WirelessTypes::voltage_2500mV;

            default:
                throw Error_NotSupported("Unknown ADC voltage reference for this Node.");
        }
    }

    WirelessTypes::Voltage WirelessNode_Impl::getGainAmplifierVoltageRef() const
    {
        switch(model())
        {
            case WirelessModels::node_vLink200:
            case WirelessModels::node_vLink200_hbridge_120:
            case WirelessModels::node_vLink200_hbridge_1K:
            case WirelessModels::node_vLink200_hbridge_350:
            case WirelessModels::node_vLink200_qbridge_120:
            case WirelessModels::node_vLink200_qbridge_1K:
            case WirelessModels::node_vLink200_qbridge_350:
                return WirelessTypes::voltage_5000mV;

            case WirelessModels::node_dvrtLink:
            case WirelessModels::node_sgLink:
            case WirelessModels::node_sgLink_oem:
            case WirelessModels::node_sgLink_oem_S:
            case WirelessModels::node_sgLink_rgd:
            case WirelessModels::node_sgLink_micro:
            case WirelessModels::node_vLink:
            case WirelessModels::node_vLink_legacy:
                return WirelessTypes::voltage_3000mV;

            case WirelessModels::node_sgLink_herm:
            case WirelessModels::node_sgLink_herm_2600:
            case WirelessModels::node_sgLink_herm_2700:
            case WirelessModels::node_sgLink_herm_2800:
            case WirelessModels::node_sgLink_herm_2900:
                return WirelessTypes::voltage_2800mV;

            case WirelessModels::node_iepeLink:
                return WirelessTypes::voltage_2750mV;

            case WirelessModels::node_shmLink:
            case WirelessModels::node_torqueLink:
                return WirelessTypes::voltage_2700mV;

            case WirelessModels::node_sgLink200:
            case WirelessModels::node_sgLink200_hbridge_1K:
            case WirelessModels::node_sgLink200_hbridge_350:
            case WirelessModels::node_sgLink200_hbridge_120:
            case WirelessModels::node_sgLink200_qbridge_1K:
            case WirelessModels::node_sgLink200_qbridge_350:
            case WirelessModels::node_sgLink200_qbridge_120:
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
            case WirelessModels::node_torqueLink200:
            case WirelessModels::node_torqueLink200_3ch:
            case WirelessModels::node_shmLink210_fullbridge:
            case WirelessModels::node_shmLink210_qbridge_3K:
                return m_eepromHelper->read_excitationVoltage();        //gain amplifier voltage is the same as the excitation, which is read from eeprom

            case WirelessModels::node_ptLink200:
            case WirelessModels::node_shmLink201:
            case WirelessModels::node_shmLink201_qbridge_1K:
            case WirelessModels::node_shmLink201_qbridge_348:
            case WirelessModels::node_shmLink201_hbridge_1K:
            case WirelessModels::node_shmLink201_hbridge_348:
            case WirelessModels::node_shmLink201_fullbridge:
            case WirelessModels::node_torqueLink200_3ch_s:
                return WirelessTypes::voltage_2500mV;

            default:
                throw Error_NotSupported("Unknown Gain Amplifier voltage reference for this Node.");
        }
    }

    uint16 WirelessNode_Impl::getGaugeResistance() const
    {
        return m_eepromHelper->read_gaugeResistance();
    }

    uint16 WirelessNode_Impl::getNumActiveGauges() const
    {
        return m_eepromHelper->read_numActiveGauges();
    }

    float WirelessNode_Impl::getLowBatteryThreshold() const
    {
        return m_eepromHelper->read_lowBatteryThreshold();
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

    LinearEquation WirelessNode_Impl::getFactoryCalibrationLinearEq(const ChannelMask& mask) const
    {
        //if the node doesn't support read factory calibration
        if (!features().supportsGetFactoryCal())
        {
            throw Error_NotSupported("Read Factory Calibration is not supported by this Node.");
        }

        LinearEquation result;
        m_eepromHelper->read_channelFactoryLinearEq(mask, result);
        return result;
    }

    WirelessTypes::CalCoef_Unit WirelessNode_Impl::getFactoryCalibrationUnit(const ChannelMask& mask) const
    {
        //if the node doesn't support read factory calibration
        if (!features().supportsGetFactoryCal())
        {
            throw Error_NotSupported("Read Factory Calibration is not supported by this Node.");
        }

        return m_eepromHelper->read_channelFactoryUnit(mask);
    }

    WirelessTypes::CalCoef_EquationType WirelessNode_Impl::getFactoryCalibrationEqType(const ChannelMask& mask) const
    {
        //if the node doesn't support read factory calibration
        if (!features().supportsGetFactoryCal())
        {
            throw Error_NotSupported("Read Factory Calibration is not supported by this Node.");
        }

        return m_eepromHelper->read_channelFactoryEquationType(mask);
    }

    WirelessTypes::SettlingTime WirelessNode_Impl::getFilterSettlingTime(const ChannelMask& mask) const
    {
        return m_eepromHelper->read_settlingTime(mask);
    }

    WirelessTypes::ThermocoupleType WirelessNode_Impl::getThermocoupleType(const ChannelMask& mask) const
    {
        return m_eepromHelper->read_thermoType(mask);
    }

    TempSensorOptions WirelessNode_Impl::getTempSensorOptions(const ChannelMask& mask) const
    {
        return m_eepromHelper->read_tempSensorOptions(mask);
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

    uint32 WirelessNode_Impl::getSensorDelay() const
    {
        return m_eepromHelper->read_sensorDelay();
    }

    WirelessTypes::DataMode WirelessNode_Impl::getDataMode() const
    {
        return m_eepromHelper->read_dataMode();
    }

    WirelessTypes::WirelessSampleRate WirelessNode_Impl::getDerivedDataRate() const
    {
        if(!features().supportsDerivedDataMode())
        {
            throw Error_NotSupported("Derived Data Channels are not supported by this Node.");
        }

        return m_eepromHelper->read_derivedSampleRate();
    }

    ChannelMask WirelessNode_Impl::getDerivedChannelMask(WirelessTypes::DerivedCategory category) const
    {
        if(!features().supportsDerivedDataMode())
        {
            throw Error_NotSupported("Derived Data Channels are not supported by this Node.");
        }

        if(!features().supportsDerivedCategory(category))
        {
            throw Error_NotSupported("The given DerivedCategory (" + Utils::toStr(category) + ") is not supported by this Node.");
        }

        return m_eepromHelper->read_derivedChannelMask(category);
    }

    WirelessTypes::DerivedVelocityUnit WirelessNode_Impl::getDerivedVelocityUnit() const
    {
        if(!features().supportsDerivedCategory(WirelessTypes::derivedCategory_velocity))
        {
            throw Error_NotSupported("The velocity derived data category is not supported by this Node.");
        }

        try
        {
            return m_eepromHelper->read_derivedVelocityUnit();
        }
        catch(Error_NotSupported&)
        {
            //the velocity category is supported, but the configuration eeprom isn't

            //default of IPS
            return WirelessTypes::derivedVelocity_ips;
        }
    }

    PingResponse WirelessNode_Impl::ping()
    {
        PingResponse result;

        try
        {
            //send the node_ping command to this node's parent base station
            result = m_baseStation.node_ping(wirelessProtocol(), m_address);
        }
        catch(Error&)
        {
            //treat errors (such as failing to determine protocol) as if it failed to ping
        }

        return result;
    }

    bool WirelessNode_Impl::sleep()
    {
        //send the sleep command to this node's parent base station
        return m_baseStation.node_sleep(wirelessProtocol(), m_address);
    }

    void WirelessNode_Impl::cyclePower()
    {
        if(wirelessProtocol().supportsNodeHardReset())
        {
            m_baseStation.node_hardReset(wirelessProtocol(), m_address);
        }
        else
        {
            static const uint16 RESET_NODE = 0x01;

            //cycle the power on the node by writing a 1 to the CYCLE_POWER location
            writeEeprom(NodeEepromMap::CYCLE_POWER, Value::UINT16(RESET_NODE));
        }

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
        if(wirelessProtocol().supportsNodeSoftReset())
        {
            m_baseStation.node_softReset(wirelessProtocol(), m_address);
        }
        else
        {
            static const uint16 RESET_RADIO = 0x02;

            //cycle the radio on the node by writing a 2 to the CYCLE_POWER location
            writeEeprom(NodeEepromMap::CYCLE_POWER, Value::UINT16(RESET_RADIO));
        }

        Utils::threadSleep(200);
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
        bool success = m_baseStation.node_erase(wirelessProtocol(), m_address);

        //if the erase command failed
        if(!success)
        {
            throw Error_NodeCommunication(m_address, "Failed to erase the Node.");
        }
    }

    bool WirelessNode_Impl::startNonSyncSampling()
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
        const bool success = m_baseStation.node_startNonSyncSampling(wirelessProtocol(), m_address);

        if(success)
        {
            NodeCommTimes::updateDeviceState(m_address, DeviceState::deviceState_sampling);
        }

        return success;
    }

    bool WirelessNode_Impl::startSyncSampling()
    {
        WirelessTypes::SamplingMode mode = eeHelper().read_samplingMode();

        //verify that the node is configured for nonSyncSampling mode
        if(mode != WirelessTypes::samplingMode_sync &&
           mode != WirelessTypes::samplingMode_syncBurst &&
           mode != WirelessTypes::samplingMode_syncEvent)
        {
            ConfigIssues issues;
            issues.push_back(ConfigIssue(ConfigIssue::CONFIG_SAMPLING_MODE, "Configuration is not set for Synchronized Sampling Mode."));
            throw Error_InvalidNodeConfig(issues, m_address);
        }

        //call the node_startNonSyncSampling command from the parent BaseStation
        const bool success = m_baseStation.node_startSyncSampling(wirelessProtocol(), m_address);

        if(success)
        {
            NodeCommTimes::updateDeviceState(m_address, DeviceState::deviceState_sampling);
        }

        return success;
    }

    void WirelessNode_Impl::clearHistogram()
    {
        //if the node doesn't support histogram options
        if(!features().supportsHistogramConfig())
        {
            throw Error_NotSupported("Histogram configuration is not supported by this Node.");
        }

        m_eepromHelper->clearHistogram();

        //must cycle power for the clearing to take effect
        cyclePower();
    }

    AutoBalanceResult WirelessNode_Impl::autoBalance(const ChannelMask& mask, float targetPercent)
    {
        Utils::checkBounds_min(targetPercent, 0.0f);
        Utils::checkBounds_max(targetPercent, 100.0f);

        //attempt a few pings first
        //(legacy (v1) auto balance doesn't have a response packet, so need to check communication)
        uint8 retryCounter = 0;
        bool pingSuccess = false;
        while(!pingSuccess && retryCounter < 3)
        {
            pingSuccess = ping().success();
            retryCounter++;
        }

        if(!pingSuccess)
        {
            throw Error_NodeCommunication(nodeAddress());
        }

        //find the eeprom location that the auto balance will adjust
        //Note: this also verifies that it is supported for this mask
        const EepromLocation& eepromLoc = features().findEeprom(WirelessTypes::chSetting_autoBalance, mask);

        //currently, auto balance is always per channel, so get the channel from the mask
        uint8 channelNumber = mask.lastChEnabled();

        AutoBalanceResult result;

        //perform the auto balance command with the parent base station
        m_baseStation.node_autoBalance(wirelessProtocol(), m_address, channelNumber, targetPercent, result);

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
            ScopeHelper writebackRetries(std::bind(&WirelessNode_Impl::setReadWriteRetries, this, startRetries));

            //if there are less than 10 retries
            if(startRetries < 10)
            {
                //we want to retry at least a few times
                setReadWriteRetries(10);
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
                        case WirelessModels::node_torqueLink:
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
                //mark as questionable if not close enough to the target percentage
                if(std::abs(result.m_percentAchieved - targetPercent) > 5.0)
                {
                    result.m_errorCode = WirelessTypes::autobalance_maybeInvalid;
                }
                else
                {
                    result.m_errorCode = WirelessTypes::autobalance_success;
                }
            }
        }

        return result;
    }

    AutoCalResult_shmLink WirelessNode_Impl::autoCal_shmLink()
    {
        WirelessModels::NodeModel nodeModel = features().m_nodeInfo.model();

        //verify the node supports autocal
        if(!features().supportsAutoCal_shm())
        {
            throw Error_NotSupported("AutoCal is not supported by this Node.");
        }

        //verify the node is the correct model
        if(nodeModel != WirelessModels::node_shmLink200 &&
           nodeModel != WirelessModels::node_shmLink2_cust1_oldNumber &&
           nodeModel != WirelessModels::node_shmLink2_cust1)
        {
            throw Error_NotSupported("autoCal_shmLink is not supported by this Node's model.");
        }

        //perform the autocal command by the base station
        AutoCalResult_shmLink result;
        bool success = m_baseStation.node_autocal_shm(wirelessProtocol(), m_address, result);

        if(!success)
        {
            throw Error_NodeCommunication(m_address, "AutoCal has failed.");
        }

        return result;
    }

    AutoCalResult_shmLink201 WirelessNode_Impl::autoCal_shmLink201()
    {
        //verify the node supports autocal
        if(!features().supportsAutoCal_shm201())
        {
            throw Error_NotSupported("AutoCal is not supported by this Node.");
        }

        //perform the autocal command by the base station
        AutoCalResult_shmLink201 result;
        bool success = m_baseStation.node_autocal_shm201(wirelessProtocol(), m_address, result);

        if(!success)
        {
            throw Error_NodeCommunication(m_address, "AutoCal has failed.");
        }

        if(result.completionFlag() != WirelessTypes::autocal_maybeInvalid_notApplied)
        {
            //clear out the slope and offset caches for calibration coefficients
            NodeEeprom& ee = eeprom();
            ee.clearCacheLocation(NodeEepromMap::CH_ACTION_ID_1.location());
            ee.clearCacheLocation(NodeEepromMap::CH_ACTION_SLOPE_1.location());
            ee.clearCacheLocation(NodeEepromMap::CH_ACTION_OFFSET_1.location());
            ee.clearCacheLocation(NodeEepromMap::CH_ACTION_ID_2.location());
            ee.clearCacheLocation(NodeEepromMap::CH_ACTION_SLOPE_2.location());
            ee.clearCacheLocation(NodeEepromMap::CH_ACTION_OFFSET_2.location());
            ee.clearCacheLocation(NodeEepromMap::CH_ACTION_ID_3.location());
            ee.clearCacheLocation(NodeEepromMap::CH_ACTION_SLOPE_3.location());
            ee.clearCacheLocation(NodeEepromMap::CH_ACTION_OFFSET_3.location());
        }

        return result;
    }

    AutoShuntCalResult WirelessNode_Impl::autoShuntCal(const ChannelMask& mask, const ShuntCalCmdInfo& commandInfo)
    {
        //verify the node supports this operation
        if(!features().supportsAutoShuntCal())
        {
            throw Error_NotSupported("AutoShuntCal is not supported by this Node.");
        }

        //verify the channel mask supports this operation
        if(!features().supportsChannelSetting(WirelessTypes::chSetting_autoShuntCal, mask))
        {
            throw Error_NotSupported("AutoShuntCal is not supported by the provided channel(s).");
        }

        uint8 channel = mask.lastChEnabled();
        WirelessTypes::ChannelType chType = features().channelType(channel);

        AutoCalCmdDetails details;
        details.nodeAddress = m_address;
        details.commandInfo = commandInfo;
        details.chNum = channel;
        details.nodeType = model();
        details.chType = chType;
        details.firmwareVersion = firmwareVersion();

        //if supported, add excitation voltage details so the autocal command knows how to convert the input range value
        if(features().supportsExcitationVoltageConfig())
        {
            details.useExcitationVoltage = true;
            details.excitationVoltage = commandInfo.excitationVoltage;
        }

        AutoShuntCalResult result;
        bool success = m_baseStation.node_autoShuntCal(wirelessProtocol(), details, result);

        if(!success)
        {
            throw Error_NodeCommunication(m_address, "AutoShuntCal has failed.");
        }

        return result;
    }

    WirelessPollData WirelessNode_Impl::poll(const ChannelMask& mask)
    {
        //verify the node supports this operation
        if(!features().supportsPoll())
        {
            throw Error_NotSupported("The Poll command is not supported by this Node.");
        }

        WirelessPollData result;
        bool success = m_baseStation.node_poll(wirelessProtocol(), m_address, mask, result);

        if(!success)
        {
            throw Error_NodeCommunication(m_address, "The Poll command has failed.");
        }

        return result;
    }

    Value WirelessNode_Impl::readEeprom(const EepromLocation& location) const
    {
        try
        {
            return eeprom().readEeprom(location);
        }
        catch(Error_NodeCommunication& e)
        {
            throw Error_NodeCommunication(e.nodeAddress(), "Failed to read the " + location.description() + " from Node " + Utils::toStr(e.nodeAddress()));
        }
        catch(Error_NotSupported&)
        {
            throw Error_NotSupported("Node " + Utils::toStr(nodeAddress()) + " does not support reading the " + location.description());
        }
    }

    void WirelessNode_Impl::writeEeprom(const EepromLocation& location, const Value& val)
    {
        try
        {
            eeprom().writeEeprom(location, val);
        }
        catch(Error_NodeCommunication& e)
        {
            throw Error_NodeCommunication(e.nodeAddress(), "Failed to write the " + location.description() + " to Node " + Utils::toStr(e.nodeAddress()));
        }
        catch(Error_NotSupported&)
        {
            throw Error_NotSupported("Node " + Utils::toStr(nodeAddress()) + " does not support writing the " + location.description());
        }
    }

    uint16 WirelessNode_Impl::readEeprom(uint16 location) const
    {
        return eeprom().readEeprom(location);
    }

    void WirelessNode_Impl::writeEeprom(uint16 location, uint16 value)
    {
        eeprom().writeEeprom(location, value);
    }

    void WirelessNode_Impl::getDiagnosticInfo(ChannelData& result)
    {
        //verify the node supports this operation
        if(!features().supportsGetDiagnosticInfo())
        {
            throw Error_NotSupported("The Get Diagnostic Info command is not supported by this Node.");
        }

        bool success = m_baseStation.node_getDiagnosticInfo(wirelessProtocol(), m_address, result);

        if(!success)
        {
            throw Error_NodeCommunication(m_address, "Get Diagnostic Info has failed.");
        }
    }

    bool WirelessNode_Impl::testCommProtocol(WirelessTypes::CommProtocol commProtocol)
    {
        if(!features().supportsCommunicationProtocol(commProtocol))
        {
            throw Error_NotSupported("The Communication Protocol is not supported by this Node.");
        }

        if(!wirelessProtocol().supportsTestCommProtocol())
        {
            throw Error_NotSupported("The Test Communication Protocol is not supported by this Node.");
        }

        return m_baseStation.node_testCommProtocol(m_address, commProtocol);
    }
} // namespace mscl
